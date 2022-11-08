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
#include "lis2ds12_reg.h"
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

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(app);

#define RENDER_INTERVAL_LVGL (1000 / 500) // 500 Hz
#define ACCEL_INTERVAL (1000 / 10) // 10 Hz
#define BATTERY_INTERVAL (1000) // 1 Hz

#define COMPUTE_BUILD_HOUR ((__TIME__[0] - '0') * 10 + __TIME__[1] - '0')
#define COMPUTE_BUILD_MIN  ((__TIME__[3] - '0') * 10 + __TIME__[4] - '0')
#define COMPUTE_BUILD_SEC  ((__TIME__[6] - '0') * 10 + __TIME__[7] - '0')

const struct device *ds = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

static bool do_open_settings = false;

static bool update_clock = false;

static void enable_bluetoth(void);

static void onButtonPressCb(buttonPressType_t type, buttonId_t id);

static void clock_handler(struct bt_cts_exact_time_256* time);

static void test_battery_read(void);
static void test_lis_read(void);
static void test_vibrator(void);
static void test_display_blk(void);
static void set_value_minute(int32_t value);
static void set_value_hour(int32_t value);
static void add_battery_indicator(void);
static void add_battery_percent_text(void);
static void set_vibrator(uint8_t percent);
static void set_display_blk(uint8_t percent);
static void open_settings(void);
static bool load_retention_ram(void);
static void enocoder_read(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void encoder_vibration(struct _lv_indev_drv_t * drv, uint8_t e);

static void on_brightness_changed(lv_setting_value_t value, bool final);
static void on_display_always_on_changed(lv_setting_value_t value, bool final);
static void on_aoa_enable_changed(lv_setting_value_t value, bool final);

static lv_settings_item_t general_page_items[] = 
{
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
};

static lv_settings_item_t bluetooth_page_items[] = 
{
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

static lv_group_t * input_group;

static bool buttons_allocated = false;


void main(void)
{
    uint32_t count = 0U;
    lv_indev_drv_t enc_drv;
    lv_indev_t * enc_indev;
    plot_page_led_values_t hr_sample;
    uint32_t render_start_ms;
    bool retention_ok;
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

    watchface_init();
    //plot_page_init();
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

    //plot_page_show();
    watchface_show();
    //open_settings();
    uint32_t last_render = 0;
    uint32_t last_accel = 0;
    uint32_t last_battery = 0;
    uint32_t now;
    bool showed = false;
    while (1) {
        now = k_uptime_get_32();
        if ((now - last_battery) >= BATTERY_INTERVAL) {
            test_battery_read();
            last_battery = k_uptime_get_32();

            bt_hrs_notify(count % 220);
            watchface_set_hrm(count % 220);
            watchface_set_step(count * 10 % 20000);
            //heart_rate_sensor_fetch(&hr_sample);

        }

        if ((now - last_accel) >= ACCEL_INTERVAL) {
            test_lis_read();
            last_accel = k_uptime_get_32();
            //plot_page_led_values(hr_sample.red, hr_sample.green, hr_sample.ir);
        }

        if ((now - last_render) >= RENDER_INTERVAL_LVGL) {
            lv_task_handler();
            last_render = k_uptime_get_32();
            //printk("Render: %d\n", last_render - now);
        }
        if (do_open_settings) {
            //watchface_remove();
            //plot_page_remove();
            open_settings();
            do_open_settings = false;
        }

        if (update_clock) {
            LOG_PRINTK("%d, %d, %d\n", retained.current_time.hours, retained.current_time.minutes, retained.current_time.seconds);
            watchface_set_time(retained.current_time.hours, retained.current_time.minutes);
            // Store current time
            retained_update();
            update_clock = false;
        }
        count++;
        k_msleep(10);

        if (!showed) {
            //open_settings();
            showed = true;
        }
    }
}

static void enable_bluetoth(void)
{
    int err;

    err = bt_enable(NULL);
    __ASSERT(err == 0,"Failed to enable Bluetooth, err: %d", err);

    settings_load();

    ble_hr_init();
    
    __ASSERT_NO_MSG(bleAoaInit());
}

static void clock_handler(struct bt_cts_exact_time_256* time)
{
    memcpy(&retained.current_time, time, sizeof(struct bt_cts_exact_time_256));
    update_clock = true;
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

static void test_lis_read(void)
{
    struct sensor_value odr;
    const struct device *sensor = device_get_binding(DT_LABEL(DT_INST(0, st_lis2ds12)));
    if (!device_is_ready(sensor)) {
        LOG_ERR("Error: Device \"%s\" is not ready; "
                "check the driver initialization logs for errors.",
                sensor->name);
    }

    odr.val1 = 12; // 12HZ LP
    odr.val2 = 0;
    int err = sensor_attr_set(sensor, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_SAMPLING_FREQUENCY, &odr);
    if (err) {
        LOG_DBG("sensor_attr_set fail: %d", err);
    } else {
        LOG_DBG("sensor_attr_set Success");
    }

    err = sensor_sample_fetch(sensor);
    if (err) {
        LOG_ERR("Could not fetch sample from %s", sensor->name);
    }
    struct sensor_value acc_val[3];
    struct sensor_value temperature;
    if (!err) {
        stmdev_ctx_t *ctx = (stmdev_ctx_t *)sensor->config;
        err = lis2ds12_temperature_raw_get(ctx, (uint8_t*)&temperature);
        if (err < 0) {
            //LOG_INF("\nERROR: Unable to read temperature:%d\n", err);
        } else {
            //LOG_INF("Temp (TODO convert from 2 complement) %d\n", temperature.val1);
        }
        err = sensor_channel_get(sensor, SENSOR_CHAN_ACCEL_XYZ, acc_val);
        if (err < 0) {
            //LOG_INF("\nERROR: Unable to read accel XYZ:%d\n", err);
        } else {
            int16_t x_scaled = (int16_t)(sensor_value_to_double(&acc_val[0])*(32768/16));
            int16_t y_scaled = (int16_t)(sensor_value_to_double(&acc_val[1])*(32768/16));
            int16_t z_scaled = (int16_t)(sensor_value_to_double(&acc_val[2])*(32768/16));
            //LOG_INF("x: %d y: %d z: %d", x_scaled, y_scaled, z_scaled);
            states_page_accelerometer_values(x_scaled, y_scaled, z_scaled);
        }
    } else {
        LOG_ERR("Failed fetching sample from %s", sensor->name);
    }
}

//static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_NODELABEL(vib));
//#define test DT_COMPAT_GET_ANY_STATUS_OKAY(vibration)
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

static lv_obj_t * add_title(const char * txt, lv_obj_t * src){
    lv_obj_t * title = lv_label_create(src);
    //lv_theme_apply(title, theme);
    lv_label_set_text(title, txt);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, REFLOW_OVEN_TITLE_PAD);
    return title;
}

static void on_close_settings(void)
{
    printk("on_close_settings\n");
    //watchface_show();
    //plot_page_show();
    buttons_allocated = false;
}

static void open_settings(void)
{
    //general_ui_anim_out_all(lv_scr_act(), 0);

    //lv_obj_t * title = add_title("Settings", lv_scr_act());
    //lv_obj_align(title, LV_ALIGN_TOP_MID, 0, REFLOW_OVEN_TITLE_PAD);

    //lv_coord_t box_w = 160;
    //lv_obj_t * box = lv_obj_create(lv_scr_act());
    //lv_obj_set_size(box, box_w, box_w);
    //lv_obj_align(box, LV_ALIGN_CENTER, 0, 0);

    buttons_allocated = true;

    //lv_group_remove_all_objs(input_group);
    lv_settings_create(settings_menu, ARRAY_SIZE(settings_menu), "N/A", input_group, on_close_settings);
    //lv_settings_create_old(NULL, input_group, on_close_settings);
    //lv_ex_settings_2(box);
}

static bool show_watchface = true;
static int h = 0;
static int m = 0;
static void onButtonPressCb(buttonPressType_t type, buttonId_t id) {
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
        //h = (h + 1) % 12;
        //m = (m + 1) % 60;;
        //LOG_WRN("%d:%d\n", h, m);
        //watchface_set_time(h, m);
        //if (show_watchface) {
        //    states_page_remove();
        //    watchface_show();
        //    //plot_page_show();
        //} else {
        //    watchface_remove();
        //    //plot_page_remove();
        //    states_page_show();
        //}
        LOG_DBG("BUTTONS_SHORT_PRESS");
    } else {
        LOG_ERR("BUTTONS_LONG_PRESS, open settings");
        if (id == BUTTON_2) {
            if (show_watchface) {
                do_open_settings = true;
                //watchface_remove();
                //plot_page_remove();
                //open_settings();
            }
        } else if (id == BUTTON_3) {
            sys_reboot(SYS_REBOOT_COLD);
            retained.off_count += 1;
            retained_update();
        }
    }
}

static buttonId_t last_pressed;

static void enocoder_read(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
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

void encoder_vibration(struct _lv_indev_drv_t * drv, uint8_t e)
{
    // TODO Vibrate motor for example!
	if (e == LV_EVENT_PRESSED) {
        printk("Clicked\n");
        gpio_debug_test(DRV_VIB_EN, 1);
        set_vibrator(65);
        k_msleep(250);
        set_vibrator(65);
        gpio_debug_test(DRV_VIB_EN, 0);
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