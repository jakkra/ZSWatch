#include <display_control.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/regulator.h>
#include <zephyr/drivers/display.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(display_control, LOG_LEVEL_WRN);


static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));
static const struct device *const reg_dev = DEVICE_DT_GET(DT_PATH(regulator_3v3_ctrl));
const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));

void display_control_init(void)
{
        if (!device_is_ready(display_dev)) {
        LOG_ERR("Device display not ready.");
        return;
    }
    if (!device_is_ready(pwm_led0.dev)) {
        LOG_ERR("Device PWM not ready.");
        return;
    }
    if (!device_is_ready(reg_dev)) {
        LOG_ERR("Regulator device not ready.");
        return;
    }
}

void display_control_power_on(bool on)
{
    if (on) {
        regulator_enable(reg_dev);
        display_control_set_brightness(1);
    } else {
        regulator_disable(reg_dev);
        display_control_set_brightness(0);
    }
}

void display_control_set_brightness(uint8_t percent)
{
    __ASSERT(percent >= 0 && percent <= 100, "Invalid range for brightness, valid range 0-100, was %d", percent);
    int ret;
    uint32_t step = pwm_led0.period / 100;
    uint32_t pulse_width = step * (100 - percent);

    if (!device_is_ready(pwm_led0.dev)) {
        LOG_ERR("Error: PWM device %s is not ready\n",
               pwm_led0.dev->name);
        return;
    }

    ret = pwm_set_pulse_dt(&pwm_led0, pulse_width);
    __ASSERT(ret == 0, "pwm error: %d for pulse: %d", ret, pulse_width);
}

