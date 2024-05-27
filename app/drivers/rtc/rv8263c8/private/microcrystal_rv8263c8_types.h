/* microcrystal_rv8263c8_types.h - Driver for Micro Crystal RV-8263-C8 RTC. */

/*
 * Copyright (c 2024, Daniel Kampert
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/rtc.h>
#include <zephyr/pm/device.h>
#include <zephyr/pm/device_runtime.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/byteorder.h>

struct rv8263c8_config {
    struct i2c_dt_spec i2c_bus;
    rv_8263_c8_clkout_t clkout;
    bool fast_mode;
    int8_t offset;
    struct gpio_dt_spec int_gpio;
};

struct rv8263c8_data {
    struct k_spinlock lock;
    bool alarm_pending;
    rtc_alarm_callback cb;
    void *cb_data;
    rtc_update_callback update_cb;
    void *update_cb_data;
};