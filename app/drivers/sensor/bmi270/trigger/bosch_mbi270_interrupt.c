#include "../bosch_bmi270.h"

int bmi2_init_interrupt(void)
{
    /*
    if (!device_is_ready(int1_gpio.port)) {
        LOG_ERR("GPIO device not ready");
        return -ENODEV;
    }
    if (!device_is_ready(int2_gpio.port)) {
        LOG_ERR("GPIO device not ready");
        return -ENODEV;
    }

    gpio_pin_configure_dt(&int1_gpio, GPIO_INPUT | GPIO_PULL_DOWN);
    gpio_pin_configure_dt(&int2_gpio, GPIO_INPUT | GPIO_PULL_DOWN);

    gpio_init_callback(&gpio_int1_cb,
                       bmi270_gpio_int1_callback,
                       BIT(int1_gpio.pin));
    gpio_init_callback(&gpio_int2_cb,
                       bmi270_gpio_int2_callback,
                       BIT(int2_gpio.pin));

    if (gpio_add_callback(int1_gpio.port, &gpio_int1_cb) < 0) {
        LOG_DBG("Could not set gpio1 callback");
        return -EIO;
    }
    if (gpio_add_callback(int2_gpio.port, &gpio_int2_cb) < 0) {
        LOG_DBG("Could not set gpio2 callback");
        return -EIO;
    }

    setup_int1(true);
    setup_int2(true);
*/
    return 0;
}