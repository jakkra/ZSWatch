/* microcrystal_rv8263c8_interrupt.c - Driver for Micro Crystal RV-8263-C8 RTC. */

/*
 * Copyright (c) 2024, Daniel Kampert
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

#include "../microcrystal_rv8263c8.h"
#include "../private/microcrystal_rv8263c8_types.h"

LOG_MODULE_REGISTER(microcrystal_rv8263c8_interrupt, CONFIG_MICROCRYSTAL_RV_8263_C8_LOG_LEVEL);

#ifdef CONFIG_RV_8263_C8_TRIGGER_OWN_THREAD
static K_KERNEL_STACK_DEFINE(rv8263c8_thread_stack, CONFIG_RV_8263_C8_THREAD_STACK_SIZE);
static struct k_thread rv8263c8_thread;
#endif

/** @brief
 *  @param p_dev
 *  @param p_cb
 *  @param pins
*/
static void rv8263c8_gpio_on_interrupt_callback(const struct device *p_dev, struct gpio_callback *p_cb, uint32_t pins)
{
    ARG_UNUSED(pins);
    ARG_UNUSED(p_dev);
}

int rv8263c8_init_interrupt(const struct device *p_dev)
{
    struct rv8263c8_data *data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    LOG_DBG("Initialize interrupts...");

    if (!gpio_is_ready_dt(&config->int_gpio)) {
        LOG_ERR("INT GPIO device not ready!");
        return -ENODEV;
    }

    if (gpio_pin_configure_dt(&config->int_gpio, GPIO_INPUT)) {
        return -EFAULT;
    }
    /*
        data->dev = p_dev;

    #ifdef CONFIG_RV_8263_C8_TRIGGER_OWN_THREAD
        k_sem_init(&data->sem, 0, K_SEM_MAX_LIMIT);

        k_thread_create(&bmi2_thread, bmi2_thread_stack, CONFIG_RV_8263_C8_THREAD_STACK_SIZE,
                        bmi2_worker_thread, data, NULL, NULL, K_PRIO_COOP(CONFIG_RV_8263_C8_THREAD_PRIORITY),
                        0, K_NO_WAIT);
    #else
        data->work.handler = bmi2_worker;
    #endif

        gpio_init_callback(&data->gpio_handler, rv8263c8_gpio_on_interrupt_callback, BIT(config->int_gpio.pin));

        if (gpio_add_callback(config->int_gpio.port, &data->gpio_handler)) {
            return -EFAULT;
        }

        LOG_DBG("Interrupts ready!");
    */
    return 0;
}