/* bmi270.h - Driver for Bosch bmi270 Inertial Measurement Unit. */

/*
 * Copyright (c) 2023, Daniel Kampert
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <zephyr/drivers/sensor.h>

#define SENSOR_CHAN_STEPS           (SENSOR_CHAN_PRIV_START + 1)

/** @brief 
*/
struct bmi270_data {
	int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
    uint16_t temp;
	uint8_t acc_range;
    uint8_t acc_odr;
    uint8_t gyr_odr;
	uint16_t gyr_range;
};