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

#include <zephyr/logging/log.h>

#include "sensors/zsw_environment_sensor.h"

LOG_MODULE_REGISTER(bme688_environment, LOG_LEVEL_DBG);

static const struct device *const bme688 = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(bme688));

int zsw_environment_sensor_init(void)
{
    if (!device_is_ready(bme688)) {
        return -ENODEV;
    }

    return 0;
}

int zsw_environment_sensor_fetch(float *temperature, float *humidity, float *pressure)
{
    struct sensor_value sensor_val;

    if (sensor_sample_fetch(bme688) != 0) {
        return -ENODATA;
    }

    if (sensor_channel_get(bme688, SENSOR_CHAN_AMBIENT_TEMP, &sensor_val) != 0) {
        return -ENODATA;
    }
    *temperature = sensor_value_to_float(&sensor_val);

    if (sensor_channel_get(bme688, SENSOR_CHAN_HUMIDITY, &sensor_val) != 0) {
        return -ENODATA;
    }
    *humidity = sensor_value_to_float(&sensor_val);

    if (sensor_channel_get(bme688, SENSOR_CHAN_PRESS, &sensor_val) != 0) {
        return -ENODATA;
    }
    *pressure = sensor_value_to_float(&sensor_val);

    return 0;
}

int zsw_environment_sensor_fetch_iaq(float *iaq)
{
    struct sensor_value sensor_val;

    if (sensor_sample_fetch(bme688) != 0) {
        return -ENODATA;
    }

    if (sensor_channel_get(bme688, (SENSOR_CHAN_PRIV_START + 1), &sensor_val) != 0) {
        return -ENODATA;
    }

    *iaq = sensor_value_to_float(&sensor_val);

    return 0;
}