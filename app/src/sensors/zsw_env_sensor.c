/*
 * This file is part of ZSWatch project <https://github.com/jakkra/ZSWatch/>.
 * Copyright (c) 2023 Jakob Krantz.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#include "sensors/zsw_env_sensor.h"

static const struct device *const bme688 = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(bme688));

int zsw_env_sensor_fetch_all(float *temperature, float *pressure, float *humidity)
{
    struct sensor_value temp_sensor_val;
    float gas_res;

    if (!device_is_ready(bme688)) {
        return -ENODEV;
    }

    if (sensor_sample_fetch(bme688) != 0) {
        return -ENODATA;
    }

    sensor_channel_get(bme688, SENSOR_CHAN_AMBIENT_TEMP, &temp_sensor_val);
    *temperature = sensor_value_to_float(&temp_sensor_val);

    sensor_channel_get(bme688, SENSOR_CHAN_GAS_RES, &temp_sensor_val);
    gas_res = sensor_value_to_float(&temp_sensor_val);

    sensor_channel_get(bme688, SENSOR_CHAN_HUMIDITY, &temp_sensor_val);
    *humidity = sensor_value_to_float(&temp_sensor_val);

    sensor_channel_get(bme688, SENSOR_CHAN_PRESS, &temp_sensor_val);
    *pressure = sensor_value_to_float(&temp_sensor_val);

    return 0;
}