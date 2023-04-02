#include <display_control.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/regulator.h>
#include <zephyr/drivers/display.h>
#include <zephyr/logging/log.h>
#include "lvgl.h"
#include <zsw_cpu_freq.h>

LOG_MODULE_REGISTER(display_control, LOG_LEVEL_WRN);

static void lvgl_render(struct k_work *item);

static const struct pwm_dt_spec display_blk = PWM_DT_SPEC_GET_OR(DT_ALIAS(display_blk), {});
static const struct device *const reg_dev = DEVICE_DT_GET_OR_NULL(DT_PATH(regulator_3v3_ctrl));
const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

K_WORK_DELAYABLE_DEFINE(lvgl_work, lvgl_render);

static struct k_work_sync canel_work_sync;
static bool is_on;
static uint8_t last_brightness = 5;

void display_control_init(void)
{
    if (!device_is_ready(display_dev)) {
        LOG_ERR("Device display not ready.");
        return;
    }
    if (!device_is_ready(display_blk.dev)) {
        LOG_WRN("Display brightness control not supported");
        return;
    }
    if (!device_is_ready(reg_dev)) {
        LOG_WRN("Display regulator control not supported");
        return;
    }
}

void display_control_power_on(bool on)
{
    if (on == is_on) {
        return;
    }
    is_on = on;
    if (on) {
        // Turn on 3V3 regulator that powers display related stuff.
        if (device_is_ready(reg_dev)) {
            regulator_enable(reg_dev);
        }
        // Zephyr does not have APIs for re-init or power save for displays.
        // We reuse the blanking API for this functioality for now.
        // This actually re-inits the display.
        display_blanking_on(display_dev);
        // Turn backlight on.
        display_control_set_brightness(last_brightness);
        k_work_schedule(&lvgl_work, K_MSEC(1));
    } else {
        // Turn off 3v3 regulator
        if (device_is_ready(reg_dev)) {
            regulator_disable(reg_dev);
        }
        // Turn off PWM peripheral as it consumes like 200-250uA
        display_control_set_brightness(0);
        // Cancel pending call to lv_task_handler
        // Don't waste resosuces to rendering when display is off anyway.
        k_work_cancel_delayable_sync(&lvgl_work, &canel_work_sync);
        // Prepare for next call to lv_task_handler when screen is enabled again,
        // Since the display will have been powered off, we need to tell LVGL
        // to rerender the complete display.
        lv_obj_invalidate(lv_scr_act());
    }
}

void display_control_set_brightness(uint8_t percent)
{
    if (!device_is_ready(display_blk.dev)) {
        return;
    }
    __ASSERT(percent >= 0 && percent <= 100, "Invalid range for brightness, valid range 0-100, was %d", percent);
    int ret;
    uint32_t step = display_blk.period / 100;
    uint32_t pulse_width = step * (100 - percent);


    last_brightness = percent;
    ret = pwm_set_pulse_dt(&display_blk, pulse_width);
    __ASSERT(ret == 0, "pwm error: %d for pulse: %d", ret, pulse_width);
}

static void lvgl_render(struct k_work *item)
{
    // Running at max CPU freq consumes more power, but rendering we
    // want to do as fast as possible. Also to use 32MHz SPI, CPU has
    // to be running at 128MHz. Meaning this improves both rendering times
    // and the SPI transmit time.
    zsw_cpu_set_freq(ZSW_CPU_FREQ_FAST, true);
    const int64_t next_update_in_ms = lv_task_handler();
    zsw_cpu_set_freq(ZSW_CPU_FREQ_DEFAULT, false);
    k_work_schedule(&lvgl_work, K_MSEC(next_update_in_ms));
}