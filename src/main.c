#include <device.h>
#include <drivers/display.h>
#include <lvgl.h>
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

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <logging/log.h>
LOG_MODULE_REGISTER(app);
const struct device *ds = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

static void onButtonPressCb(buttonPressType_t type, buttonId_t id);

static void example_lvgl_demo_ui(void);
static void set_value(void *indic, int32_t v);
static void test_battery_read(void);
static void test_lis_read(const struct device *sensor);
static void test_vibrator(void);
static void test_display_blk(void);

static lv_obj_t *meter;
//static lv_obj_t * btn;
static lv_meter_indicator_t *indic;

void main(void)
{
	uint32_t count = 0U;
	const struct device *display_dev;

	printk("%p", DEVICE_DT_GET(DT_CHOSEN(zephyr_display)));
	
	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting test");
		return;
	}
	filesystem_test();
	bluetooth_init();

	//gpio_debug_test_all();
	//gpio_debug_init();
	//gpio_debug_test(BAT_MON_EN, 0);
	//gpio_debug_test(DRV_VIB_EN, 1);
	//gpio_debug_test(DRV_VIB_PWM, 1);
	//gpio_debug_test(DRV_VIB_PWM, 0);
	//gpio_debug_test(DRV_VIB_EN, 1);
	//gpio_debug_test(DISPLAY_EN, 1);
	//gpio_debug_test(DISPLAY_BLK, 1);
	//gpio_debug_test(V5_REG_EN, 1);
	//gpio_debug_test(V5_REG_EN, 0);
	//gpio_debug_test(V5_REG_EN, 1);
	//test_vibrator();
	//test_display_blk();
	//k_msleep(600000);
	buttonsInit(&onButtonPressCb);
	

	int rc = battery_measure_enable(true);

	if (rc != 0) {
		printk("Failed initialize battery measurement: %d\n", rc);
		return;
	}

	
	lv_obj_clean(lv_scr_act());
	example_lvgl_demo_ui();
	lv_task_handler();

	const struct device *sensor = device_get_binding(DT_LABEL(DT_INST(0, st_lis2ds12)));
	if (!device_is_ready(sensor)) {
		LOG_ERR("Error: Device \"%s\" is not ready; "
                "check the driver initialization logs for errors.",
                sensor->name);
	}

	while (1) {
		if ((count % 1000) == 0U) {
			//lv_label_set_text(count_label, count_str);
			//set_value(indic, count);
			test_battery_read();
			test_lis_read(sensor);
		}

		/* Tell LVGL how many milliseconds has elapsed */
		//lv_tick_inc(10);
		lv_task_handler();
		lv_timer_handler();
		k_sleep(K_MSEC(2));
		++count;
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

	{ 10000, 3950 },
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
	// From https://github.com/zephyrproject-rtos/zephyr/blob/main/samples/boards/nrf/battery/src/main.c
	int batt_mV = battery_sample();

	if (batt_mV < 0) {
		printk("Failed to read battery voltage: %d\n", batt_mV);
		return;
	}

	unsigned int batt_pptt = battery_level_pptt(batt_mV, levels);

	printk("[%s]: %d mV; %u pptt\n", now_str(), batt_mV, batt_pptt);
}

static void test_lis_read(const struct device *sensor)
{
	struct sensor_value odr;
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
			LOG_INF("\nERROR: Unable to read temperature:%d\n", err);
		} else {
			LOG_INF("Temp (TODO convert from 2 complement) %d\n", temperature.val1);
		}
		err = sensor_channel_get(sensor, SENSOR_CHAN_ACCEL_XYZ, acc_val);
		if (err < 0) {
			LOG_INF("\nERROR: Unable to read accel XYZ:%d\n", err);
		} else {
			int16_t x_scaled = (int16_t)(sensor_value_to_double(&acc_val[0])*(32768/16));
			int16_t y_scaled = (int16_t)(sensor_value_to_double(&acc_val[1])*(32768/16));
			int16_t z_scaled = (int16_t)(sensor_value_to_double(&acc_val[2])*(32768/16));
			LOG_INF("x: %d y: %d z: %d", x_scaled, y_scaled, z_scaled);
		}
	} else {
		LOG_ERR("Failed fetching sample from %s", sensor->name);
	}
}

//static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_NODELABEL(vib));
//#define test DT_COMPAT_GET_ANY_STATUS_OKAY(vibration)
static const struct pwm_dt_spec pwm_led1 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led1));

#define NUM_STEPS 50
#define SLEEP_MSEC	50U
static void test_vibrator(void)
{

	if (!device_is_ready(pwm_led1.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led1.dev->name);
		return;
	}

	uint32_t step = pwm_led1.period / NUM_STEPS;
	uint32_t pulse_width = 0;//pwm_led1.period/2;
	uint8_t dir = 1U;
	int ret;

	printk("PWM-based LED fade\n");

	if (!device_is_ready(pwm_led1.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led1.dev->name);
		return;
	}
	ret = pwm_set_pulse_dt(&pwm_led1, pwm_led1.period/10);
}

static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));

static void test_display_blk(void)
{

	if (!device_is_ready(pwm_led0.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
		return;
	}

	uint32_t step = pwm_led0.period / NUM_STEPS;
	uint32_t pulse_width = 0;//pwm_led0.period/2;
	uint8_t dir = 1U;
	int ret;

	printk("PWM-based LED fade\n");

	if (!device_is_ready(pwm_led0.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
		return;
	}
	ret = pwm_set_pulse_dt(&pwm_led0, pwm_led0.period/2);
	__ASSERT_NO_MSG(ret == 0);
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


static void onButtonPressCb(buttonPressType_t type, buttonId_t id) {
    LOG_INF("Pressed %d, type: %d", id, type);

    if (type == BUTTONS_SHORT_PRESS) {
		LOG_DBG("BUTTONS_SHORT_PRESS");
	} else {
		LOG_DBG("BUTTONS_LONG_PRESS");
	}
}

/*
 * SPDX-FileCopyrightText: 2021-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

// This demo UI is adapted from LVGL official example: https://docs.lvgl.io/master/widgets/extra/meter.html#simple-meter


//static lv_disp_rot_t rotation = LV_DISP_ROT_NONE;

static void set_value(void *indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);
}

static void example_lvgl_demo_ui(void)
{
 	meter = lv_meter_create(lv_scr_act());
    lv_obj_set_size(meter, 240, 240);
    lv_obj_center(meter);

    /*Create a scale for the minutes*/
    /*61 ticks in a 360 degrees range (the last and the first line overlaps)*/
    lv_meter_scale_t * scale_min = lv_meter_add_scale(meter);
	lv_obj_set_style_border_color(meter, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
	lv_obj_set_style_pad_all(meter, 0, LV_PART_MAIN);
    lv_meter_set_scale_ticks(meter, scale_min, 61, 1, 10, lv_palette_main(LV_PALETTE_DEEP_ORANGE));
    lv_meter_set_scale_range(meter, scale_min, 0, 60, 360, 270);

    /*Create another scale for the hours. It's only visual and contains only major ticks*/
    lv_meter_scale_t * scale_hour = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale_hour, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));               /*12 ticks*/
    lv_meter_set_scale_major_ticks(meter, scale_hour, 1, 2, 20, lv_color_black(), 10);    /*Every tick is major*/
    lv_meter_set_scale_range(meter, scale_hour, 1, 12, 330, 300);       /*[1..12] values in an almost full circle*/

    LV_IMG_DECLARE(img_hand)

    /*Add a the hands from images*/
	
	//lv_meter_indicator_t * indic_min = lv_meter_add_needle_line(meter, scale_min, 2, lv_color_hex(0x00FF00), 1);
    lv_meter_indicator_t * indic_min = lv_meter_add_needle_img(meter, scale_min, &img_hand, 5, 5);
    lv_meter_indicator_t * indic_hour = lv_meter_add_needle_img(meter, scale_hour, &img_hand, 5, 5);

    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_values(&a, 0, 60);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_set_time(&a, 60000);     /*2 sec for 1 turn of the minute hand (1 hour)*/
    lv_anim_set_var(&a, indic_min);
    lv_anim_start(&a);

    lv_anim_set_var(&a, indic_hour);
    lv_anim_set_time(&a, 60000);    /*24 sec for 1 turn of the hour hand*/
    lv_anim_set_values(&a, 0, 60);
	lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}