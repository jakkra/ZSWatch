#include <device.h>
#include <drivers/display.h>
#include <stdio.h>
#include <string.h>
#include <zephyr.h>
#include <buttons.h>
#include <battery.h>
#include <gpio_debug.h>
#include <hr_service.h>
#include <drivers/sensor.h>
#include <zephyr/drivers/pwm.h>
#include <drivers/led.h>
#include "lis2ds12_reg.h"
#include <filesystem.h>
#include <clock.h>
#include <lvgl.h>
#include "watchface.h"
#include "stats_page.h"
#include <general_ui.h>

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(app);
const struct device *ds = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

static void onButtonPressCb(buttonPressType_t type, buttonId_t id);

static void clock_handler(int hour, int minute, int second);

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

static void enocoder_read(struct _lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void encoder_vibration(struct _lv_indev_drv_t * drv, uint8_t e);

static lv_group_t * input_group;

static bool buttons_allocated = false;


void main(void)
{
    int rc;
    uint32_t count = 0U;
    lv_indev_drv_t enc_drv;
    lv_indev_t * enc_indev;
    const struct device *display_dev;
    
    display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
    if (!device_is_ready(display_dev)) {
        LOG_ERR("Device not ready, aborting test");
        return;
    }

    watchface_init();
    filesystem_test();
    //bluetooth_init();
    clock_init(clock_handler);
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
    //open_settings();
    
    while (1) {
        if ((count % 100) == 0U) {
            test_battery_read();
            watchface_set_hrm(count % 220);
            watchface_set_step(count % 20000);
        }
        if ((count % 10) == 0U) {
            test_lis_read();
        }

        /* Tell LVGL how many milliseconds has elapsed */
        lv_task_handler();
        lv_timer_handler();
        k_sleep(K_MSEC(10));
        ++count;
    }
    
}

static void clock_handler(int hour, int minute, int second)
{
    watchface_set_value_minute(minute);
    watchface_set_value_hour(minute % 12);
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

    //printk("[%s]: %d mV; %u pptt\n", now_str(), batt_mV, batt_pptt);

    rc = battery_measure_enable(false);
    if (rc != 0) {
        printk("Failed disable battery measurement: %d\n", rc);
        return;
    }

    watchface_set_battery_percent(batt_pptt / 100);
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
        LOG_INF("sensor_attr_set fail: %d", err);
    } else {
        LOG_INF("sensor_attr_set Success");
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
    watchface_show();
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

    lv_settings_create(NULL, input_group, on_close_settings);
    //lv_ex_settings_2(box);
}

static bool show_watchface = true;

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
        if (show_watchface) {
            states_page_remove();
            watchface_show();
        } else {
            watchface_remove();
            states_page_show();
        }
        LOG_DBG("BUTTONS_SHORT_PRESS");
    } else {
        LOG_ERR("BUTTONS_LONG_PRESS, open settings");
        if (id == BUTTON_2) {
            if (show_watchface) {
                watchface_remove();
                open_settings();
            }
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
	//if (e == LV_EVENT_FOCUSED) {
    //    
    //}
}