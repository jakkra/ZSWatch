#include <vibration_motor.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(vibration_motor, LOG_LEVEL_WRN);

static const struct pwm_dt_spec vib_motor = PWM_DT_SPEC_GET_OR(DT_ALIAS(vibrator_pwm), {});
static const struct gpio_dt_spec enable_gpio = GPIO_DT_SPEC_GET_OR(DT_NODELABEL(vib_pwr), enable_gpios, {});

void vibration_motor_init(void)
{
    int rc;

    if (!device_is_ready(vib_motor.dev)) {
        LOG_WRN("Vibration motor control not supported");
        return;
    }
    if (!device_is_ready(enable_gpio.port)) {
        LOG_WRN("Vibration motor enable/disable not supported");
        return;
    }
    rc = gpio_pin_configure_dt(&enable_gpio, GPIO_OUTPUT_LOW);
    if (rc != 0) {
        printk("Failed init vibration motor enable pin\n");
    }
}

void vibration_motor_set_power(uint8_t percent)
{
    int ret;
    uint32_t step = vib_motor.period / 100;
    uint32_t pulse_width = step * percent;

    if (!device_is_ready(vib_motor.dev)) {
        return;
    }

    ret = pwm_set_pulse_dt(&vib_motor, pulse_width);
    __ASSERT(ret == 0, "pwm error: %d for pulse: %d", ret, pulse_width);
}

void vibration_motor_set_on(bool on)
{
    if (!device_is_ready(enable_gpio.port)) {
        return;
    }
    gpio_pin_set_dt(&enable_gpio, on);
}
