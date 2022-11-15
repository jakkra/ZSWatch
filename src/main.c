#include <device.h>
#include <drivers/display.h>
#include <zephyr/sys/reboot.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>
#include <buttons.h>
#include <battery.h>
#include <gpio_debug.h>
#include <hr_service.h>
#include <drivers/sensor.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/bluetooth/services/hrs.h>
#include <zephyr/bluetooth/services/bas.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/settings/settings.h>
#include <drivers/led.h>
#include <filesystem.h>
#include <clock.h>
#include <lvgl.h>
#include "watchface.h"
#include "stats_page.h"
#include "plot_page.h"
#include <general_ui.h>
#include <lv_settings.h>
#include <heart_rate_sensor.h>
#include <ble_aoa.h>
#include <sys/time.h>
#include <ram_retention_storage.h>
#include <accelerometer.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(app);

#define RENDER_INTERVAL_LVGL (1000 / 100) // 10 Hz
#define ACCEL_INTERVAL (1000 / 100) // 10 Hz
#define BATTERY_INTERVAL (1000) // 1 Hz

#define COMPUTE_BUILD_HOUR ((__TIME__[0] - '0') * 10 + __TIME__[1] - '0')
#define COMPUTE_BUILD_MIN  ((__TIME__[3] - '0') * 10 + __TIME__[4] - '0')
#define COMPUTE_BUILD_SEC  ((__TIME__[6] - '0') * 10 + __TIME__[7] - '0')

const struct device *ds = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

typedef enum work_type {
    INIT,
    OPEN_SETTINGS,
    UPDATE_CLOCK,
    ENABLE_BUTTON_INOUT,
    BATTERY,
    RENDER,
    ACCEL,
} work_type_t;

typedef struct delayed_work_item {
    struct k_work_delayable   work;
    work_type_t     type;
} delayed_work_item_t;


static delayed_work_item_t battery_work = { .type = BATTERY };
static delayed_work_item_t accel_work = { .type = ACCEL };
static delayed_work_item_t render_work = { .type = RENDER };
static delayed_work_item_t clock_work = { .type = UPDATE_CLOCK };
static delayed_work_item_t general_work_item;

#define MY_STACK_SIZE 2048
#define MY_PRIORITY 5

K_THREAD_STACK_DEFINE(my_stack_area, MY_STACK_SIZE);

struct k_work_q my_work_q;

static bool show_watchface = true;

static void enable_bluetoth(void);

static void onButtonPressCb(buttonPressType_t type, buttonId_t id);

static void clock_handler(struct bt_cts_exact_time_256 *time);

static void test_battery_read(void);
static void set_vibrator(uint8_t percent);
static void set_display_blk(uint8_t percent);
static void open_settings(void);
static bool load_retention_ram(void);
static void enocoder_read(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static void encoder_vibration(struct _lv_indev_drv_t *drv, uint8_t e);
static void accel_evt(accelerometer_evt_t *evt);

static void on_brightness_changed(lv_setting_value_t value, bool final);
static void on_display_always_on_changed(lv_setting_value_t value, bool final);
static void on_aoa_enable_changed(lv_setting_value_t value, bool final);
static void on_reset_steps_changed(lv_setting_value_t value, bool final);

static lv_settings_item_t general_page_items[] = {
    {
        .type = LV_SETTINGS_TYPE_SLIDER,
        .icon = LV_SYMBOL_SETTINGS,
        .change_callback = on_brightness_changed,
        .item = {
            .slider = {
                .name = "Brightness",
                .inital_val = 10,
                .min_val = 0,
                .max_val = 10,
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = LV_SYMBOL_AUDIO,
        .item = {
            .sw = {
                .name = "Vibrate on click",
                .inital_val = true
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = LV_SYMBOL_TINT,
        .change_callback = on_display_always_on_changed,
        .item = {
            .sw = {
                .name = "Display always on",
                .inital_val = true
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = LV_SYMBOL_REFRESH,
        .change_callback = on_reset_steps_changed,
        .item = {
            .sw = {
                .name = "Reset step counter",
                .inital_val = false
            }
        }
    },
};

static lv_settings_item_t bluetooth_page_items[] = {
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = LV_SYMBOL_BLUETOOTH,
        .change_callback = on_aoa_enable_changed,
        .item = {
            .sw = {
                .name = "Bluetooth",
                .inital_val = true
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = "",
        .change_callback = on_aoa_enable_changed,
        .item = {
            .sw = {
                .name = "AoA",
                .inital_val = false
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SLIDER,
        .icon = LV_SYMBOL_SHUFFLE,
        .item = {
            .slider = {
                .name = "CTE Tx interval",
                .inital_val = 100,
                .min_val = 1,
                .max_val = 10 // Map to array index or something, having 8-5000ms will make slider very slow
            }
        }
    },
};

static lv_settings_page_t settings_menu[] = {
    {
        .name = "General",
        .num_items = ARRAY_SIZE(general_page_items),
        .items = general_page_items
    },
    {
        .name = "Bluetooth",
        .num_items = ARRAY_SIZE(bluetooth_page_items),
        .items = bluetooth_page_items
    },
};

static lv_group_t *input_group;

static bool buttons_allocated = false;
static uint32_t count = 0U;
static lv_indev_drv_t enc_drv;
static lv_indev_t *enc_indev;

void general_work(struct k_work *item)
{
    int res;
    delayed_work_item_t *the_work = CONTAINER_OF(item, delayed_work_item_t, work);

    switch (the_work->type) {
        case INIT: {
            const struct device *display_dev;

            display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
            if (!device_is_ready(display_dev)) {
                LOG_ERR("Device not ready, aborting test");
                return;
            }
            k_msleep(500);
            load_retention_ram();
            k_msleep(500);
            heart_rate_sensor_init();
            res = accelerometer_init(accel_evt);
            __ASSERT(res == 0, "Failed init accelerometer");

            watchface_init();
            filesystem_test();
            enable_bluetoth();

            clock_init(clock_handler, &retained.current_time);

            buttonsInit(&onButtonPressCb);

            gpio_debug_test(DRV_VIB_EN, 0);
            set_display_blk(100);

            lv_indev_drv_init(&enc_drv);


            enc_drv.type = LV_INDEV_TYPE_ENCODER;
            enc_drv.read_cb = enocoder_read;
            enc_drv.feedback_cb = encoder_vibration;
            enc_indev = lv_indev_drv_register(&enc_drv);

            input_group = lv_group_create();
            lv_group_set_default(input_group);
            lv_indev_set_group(enc_indev, input_group);

            watchface_show();
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &battery_work.work, K_NO_WAIT), "FAIL battery_work");
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &render_work.work, K_NO_WAIT), "FAIL render_work");
            //__ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &accel_work.work, K_NO_WAIT), "FAIL accel_work");
            break;
        }
        case OPEN_SETTINGS: {
            watchface_remove();
            open_settings();
            break;
        }
        case UPDATE_CLOCK: {
            LOG_PRINTK("%d, %d, %d\n", retained.current_time.hours, retained.current_time.minutes, retained.current_time.seconds);
            watchface_set_time(retained.current_time.hours, retained.current_time.minutes);
            // Store current time
            retained_update();
            break;
        }
        case ENABLE_BUTTON_INOUT: {
            watchface_show();
            buttons_allocated = false;
            break;
        }
        case BATTERY: {
            test_battery_read();
            bt_hrs_notify(count % 220);
            watchface_set_hrm(count % 220);
            //watchface_set_step(count * 10 % 10000);
            //heart_rate_sensor_fetch(&hr_sample);
            count++;
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &battery_work.work, K_MSEC(BATTERY_INTERVAL)),
                     "FAIL battery_work");
            break;
        }
        case RENDER: {
            lv_task_handler();
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &render_work.work, K_MSEC(RENDER_INTERVAL_LVGL)),
                     "FAIL render_work");
            break;
        }
        case ACCEL: {
            if (!show_watchface) {
                int16_t x;
                int16_t y;
                int16_t z;
                res = accelerometer_fetch_xyz(&x, &y, &z);
                __ASSERT_NO_MSG(res == 0);
                LOG_DBG("x: %d y: %d z: %d", x, y, z);
                states_page_accelerometer_values(x, y, z);
                __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &accel_work.work, K_MSEC(ACCEL_INTERVAL)), "FAIL accel_work");
            }
            break;
        }
    }
}

void main(void)
{
    k_work_queue_init(&my_work_q);

    k_work_queue_start(&my_work_q, my_stack_area,
                       K_THREAD_STACK_SIZEOF(my_stack_area), MY_PRIORITY,
                       NULL);

    k_work_init_delayable(&general_work_item.work, general_work);
    k_work_init_delayable(&battery_work.work, general_work);
    k_work_init_delayable(&accel_work.work, general_work);
    k_work_init_delayable(&render_work.work, general_work); // TODO malloc and free as we can have multiple
    k_work_init_delayable(&clock_work.work, general_work);

    general_work_item.type = INIT;
    __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &general_work_item.work, K_NO_WAIT), "FAIL schedule");
}

static void enable_bluetoth(void)
{
    int err;

    err = bt_enable(NULL);
    if (err != 0) {
        LOG_ERR("Failed to enable Bluetooth, err: %d", err);
        return;
    }

    settings_load();

    ble_hr_init();

    __ASSERT_NO_MSG(bleAoaInit());
}

static uint8_t last_min = 0;
static void clock_handler(struct bt_cts_exact_time_256 *time)
{
    if (last_min != time->minutes) {
        memcpy(&retained.current_time, time, sizeof(struct bt_cts_exact_time_256));
        __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &clock_work.work, K_NO_WAIT), "FAIL schedule");
    }
}


/** A discharge curve specific to the power source. */
static const struct battery_level_point levels[] = {
    /* "Curve" here eyeballed from captured data for the [Adafruit
     * 3.7v 2000 mAh](https://www.adafruit.com/product/2011) LIPO
     * under full load that started with a charge of 3.96 V and
     * dropped about linearly to 3.58 V over 15 hours.  It then
     * dropped rapidly to 3.10 V over one hour, at which point it
     * stopped transmitting.
     *
     * Based on eyeball comparisons we'll say that 15/16 of life
     * goes between 3.95 and 3.55 V, and 1/16 goes between 3.55 V
     * and 3.1 V.
     */

    { 10000, 4150 },
    { 625, 3550 },
    { 0, 3100 },
};

static const char *now_str(void)
{
    static char buf[16]; /* ...HH:MM:SS.MMM */
    uint32_t now = k_uptime_get_32();
    unsigned int ms = now % MSEC_PER_SEC;
    unsigned int s;
    unsigned int min;
    unsigned int h;

    now /= MSEC_PER_SEC;
    s = now % 60U;
    now /= 60U;
    min = now % 60U;
    now /= 60U;
    h = now;

    snprintf(buf, sizeof(buf), "%u:%02u:%02u.%03u",
             h, min, s, ms);
    return buf;
}

static void test_battery_read(void)
{
    int rc = battery_measure_enable(true);
    if (rc != 0) {
        printk("Failed initialize battery measurement: %d\n", rc);
        return;
    }
    // From https://github.com/zephyrproject-rtos/zephyr/blob/main/samples/boards/nrf/battery/src/main.c
    int batt_mV = battery_sample();

    if (batt_mV < 0) {
        printk("Failed to read battery voltage: %d\n", batt_mV);
        return;
    }

    unsigned int batt_pptt = battery_level_pptt(batt_mV, levels);

    printk("[%s]: %d mV; %u pptt\n", now_str(), batt_mV, batt_pptt);

    rc = battery_measure_enable(false);
    if (rc != 0) {
        printk("Failed disable battery measurement: %d\n", rc);
        return;
    }

    watchface_set_battery_percent(batt_pptt / 100, batt_mV);
    bt_bas_set_battery_level(batt_pptt / 100);
}

static const struct pwm_dt_spec pwm_led1 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led1));

static void set_vibrator(uint8_t percent)
{
    int ret;
    uint32_t step = pwm_led1.period / 100;
    uint32_t pulse_width = step * percent;

    if (!device_is_ready(pwm_led1.dev)) {
        printk("Error: PWM device %s is not ready\n",
               pwm_led1.dev->name);
        return;
    }

    ret = pwm_set_pulse_dt(&pwm_led1, pulse_width);
    __ASSERT(ret == 0, "pwm error: %d for pulse: %d", ret, pulse_width);
}

static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));

static void set_display_blk(uint8_t percent)
{
    int ret;
    uint32_t step = pwm_led0.period / 100;
    uint32_t pulse_width = step * percent;

    if (!device_is_ready(pwm_led0.dev)) {
        printk("Error: PWM device %s is not ready\n",
               pwm_led0.dev->name);
        return;
    }

    ret = pwm_set_pulse_dt(&pwm_led0, pulse_width);
    __ASSERT(ret == 0, "pwm error: %d for pulse: %d", ret, pulse_width);
}

void test_max_30101(void)
{
    struct sensor_value green;
    const struct device *dev = DEVICE_DT_GET_ANY(maxim_max30101);

    if (dev == NULL) {
        LOG_INF("Could not get max30101 device\n");
        return;
    }

    if (!device_is_ready(dev)) {
        LOG_INF("max30101 device %s is not ready\n", dev->name);
        return;
    }

    sensor_sample_fetch(dev);
    sensor_channel_get(dev, SENSOR_CHAN_GREEN, &green);

    /* Print green LED data*/
    LOG_INF("GREEN=%d\n", green.val1);

}

static bool load_retention_ram(void)
{
    bool retained_ok = retained_validate();
    //memset(&retained, 0, sizeof(retained));
    /* Increment for this boot attempt and update. */
    retained.boots += 1;
    retained_update();

    printk("Retained data: %s\n", retained_ok ? "valid" : "INVALID");
    printk("Boot count: %u\n", retained.boots);
    printk("uptime_latest: %" PRIu64 "\n", retained.uptime_latest);
    printk("Active Ticks: %" PRIu64 "\n", retained.uptime_sum);

    return retained_ok;
}

#define REFLOW_OVEN_TITLE_PAD 10

static void on_close_settings(void)
{
    general_work_item.type = ENABLE_BUTTON_INOUT;
    __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &general_work_item.work, K_MSEC(250)), "FAIL schedule");
}

static void open_settings(void)
{
    buttons_allocated = true;
    lv_settings_create(settings_menu, ARRAY_SIZE(settings_menu), "N/A", input_group, on_close_settings);
}

static void play_press_vibration(void)
{
    gpio_debug_test(DRV_VIB_EN, 1);
    set_vibrator(80);
    k_msleep(150);
    set_vibrator(80);
    gpio_debug_test(DRV_VIB_EN, 0);
}

static void onButtonPressCb(buttonPressType_t type, buttonId_t id)
{
    LOG_INF("Pressed %d, type: %d", id, type);

    if (buttons_allocated) {
        // Handled by LVGL
        return;
    }
    // TODO only change if not something that needs interaction with is shown.
    /*
        UP down Buttons change screens
        Enter button shows settings?
    */
    if (type == BUTTONS_SHORT_PRESS) {
        show_watchface = !show_watchface;
        play_press_vibration();
        if (show_watchface) {
            states_page_remove();
            watchface_show();
        } else {
            watchface_remove();
            states_page_show();
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &accel_work.work, K_MSEC(1000)), "FAIL accel_work");
        }
        LOG_DBG("BUTTONS_SHORT_PRESS");
    } else {
        LOG_ERR("BUTTONS_LONG_PRESS, open settings");
        if (id == BUTTON_2) {
            if (show_watchface) {
                general_work_item.type = OPEN_SETTINGS;
                __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &general_work_item.work, K_NO_WAIT), "FAIL schedule");
            }
        } else if (id == BUTTON_3) {
            sys_reboot(SYS_REBOOT_COLD);
            retained.off_count += 1;
            retained_update();
        }
    }
}

static buttonId_t last_pressed;

static void enocoder_read(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    if (!buttons_allocated) {
        return;
    }
    if (button_read(BUTTON_1)) {
        data->key = LV_KEY_RIGHT;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_1;
    } else if (button_read(BUTTON_2)) {
        data->key = LV_KEY_ENTER;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_2;
    } else if (button_read(BUTTON_3)) {
        data->key = LV_KEY_LEFT;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_3;
    } else {
        if (last_pressed == 0xFF) {
            return;
        }
        data->state = LV_INDEV_STATE_REL;
        switch (last_pressed) {
            case BUTTON_1:
                data->key = LV_KEY_RIGHT;
                break;
            case BUTTON_2:
                data->key = LV_KEY_ENTER;
                break;
            case BUTTON_3:
                data->key = LV_KEY_LEFT;
                break;
        }
        last_pressed = 0xFF;
    }
}

void encoder_vibration(struct _lv_indev_drv_t *drv, uint8_t e)
{
    if (e == LV_EVENT_PRESSED) {
        play_press_vibration();
    }
}

static void on_brightness_changed(lv_setting_value_t value, bool final)
{
    // Slider have values 0-10 hence multiply with 10 to get brightness in percent
    set_display_blk(value.item.slider * 10);
}

static void on_display_always_on_changed(lv_setting_value_t value, bool final)
{
    if (value.item.sw) {
        set_display_blk(100);
    } else {
        set_display_blk(10);
    }
}

static void on_aoa_enable_changed(lv_setting_value_t value, bool final)
{
    if (value.item.sw) {
        bleAoaAdvertise(100, 100, 1);
    } else {
        bleAoaAdvertise(100, 100, 0);
    }
}

static void on_reset_steps_changed(lv_setting_value_t value, bool final)
{
    if (final && value.item.sw) {
        watchface_set_step(0);
        accelerometer_reset_step_count();
    }
}

static bool display_on = true;
static void accel_evt(accelerometer_evt_t *evt)
{
    switch (evt->type) {
        case ACCELEROMETER_EVT_TYPE_DOOUBLE_TAP: {
            display_on = !display_on;
            if (display_on) {
                set_display_blk(100);
            } else {
                set_display_blk(1);
            }
            break;
        }
        case ACCELEROMETER_EVT_TYPE_STEP: {
            watchface_set_step(evt->data.step.count);
            break;
        }
        case ACCELEROMETER_EVT_TYPE_XYZ: {
            LOG_ERR("x: %d y: %d z: %d", evt->data.xyz.x, evt->data.xyz.y, evt->data.xyz.z);
            break;
        }
        case ACCELEROMETER_EVT_TYPE_TILT: {
            set_display_blk(100);
            break;
        }
    }
}