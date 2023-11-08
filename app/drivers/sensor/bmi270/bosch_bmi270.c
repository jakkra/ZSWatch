/* bmi270.h - Driver for Bosch bmi270 Inertial Measurement Unit. */

/*
 * Copyright (c) 2023, Daniel Kampert
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/pm/device.h>
#include <zephyr/pm/device_runtime.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/byteorder.h>

#include "bmi2.h"
#include "bmi270.h"
#include "bosch_bmi270.h"
#include "private/bosch_bmi270_config.h"

#define DT_DRV_COMPAT                   bosch_bmi270ext
#define BMI2_GRAVITIY	                9806650LL
#define BMI2_PI		                    3141592LL
#define BMI2_SHUTTLE_ID                 UINT16_C(0x1B8)
#define BMI2_READ_WRITE_LEN             UINT8_C(46)

//LOG_MODULE_REGISTER(bmi270, CONFIG_SENSOR_LOG_LEVEL);
LOG_MODULE_REGISTER(bosch_bmi270, LOG_LEVEL_INF);

#if(DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0)
#warning "bmi270 driver enabled without any devices"
#endif

struct bmi270_config {
    struct i2c_dt_spec i2c;
#ifdef CONFIG_BMI270_TRIGGER
	struct gpio_dt_spec int1_gpio;
	struct gpio_dt_spec int2_gpio;
#endif
};

static struct bmi270_data last_measurement;
static const struct device *device;
static struct bmi2_dev bmi2_dev;

/** @brief              Platform specific i2c read function.
 *  @param reg_addr     Register address
 *  @param p_reg_data   Register data
 *  @param len          Data length
 *  @param p_intf       Pointer to interface
 *  @return             0 when successful
*/
static BMI2_INTF_RETURN_TYPE bmi2_i2c_read(uint8_t reg_addr, uint8_t *p_reg_data, uint32_t len, void *p_intf)
{
    (void)p_intf;

    const struct bmi270_config *config = device->config;
    return i2c_burst_read_dt(&config->i2c, reg_addr, p_reg_data, len);
}

/** @brief              Platform specific i2c write function.
 *  @param reg_addr     Register address
 *  @param p_reg_data   Register data
 *  @param len          Data length
 *  @param p_intf       Pointer to interface
 *  @return             0 when successful
*/
static BMI2_INTF_RETURN_TYPE bmi2_i2c_write(uint8_t reg_addr, const uint8_t *p_reg_data, uint32_t len, void *p_intf)
{
    (void)p_intf;

    const struct bmi270_config *config = device->config;
    return i2c_burst_write_dt(&config->i2c, reg_addr, p_reg_data, len);
}

/** @brief          Platform specific us delay function.
 *  @param period   Sleep period
 *  @param p_intf   Pointer to interface
*/
static void bmi2_delay_us(uint32_t period, void *p_intf)
{
    (void)p_intf;

    k_usleep(period);
}

static void bmi2_raw2accel_convert(struct sensor_value *p_val, int64_t raw_val,
				  uint8_t range)
{
	raw_val = (raw_val * BMI2_GRAVITIY * ((int64_t)range)) / INT16_MAX;

	p_val->val1 = raw_val / 1000000LL;
	p_val->val2 = raw_val % 1000000LL;
}

static void bmi2_raw2gyro_convert(struct sensor_value *p_val, int64_t raw_val,
				 uint16_t range)
{
	p_val->val1 = ((raw_val * ((int64_t)range) * BMI2_PI) / (180LL * INT16_MAX)) / 1000000LL;
	p_val->val2 = ((raw_val * ((int64_t)range) * BMI2_PI) / (180LL * INT16_MAX)) % 1000000LL;
}

/** @brief  
 *  @param  
 *  @return 
*/
static int bmi270_attr_set(const struct device *p_dev, enum sensor_channel channel, enum sensor_attribute attribute,
                             const struct sensor_value *p_value)
{
	if ((channel == SENSOR_CHAN_ACCEL_X) || (channel == SENSOR_CHAN_ACCEL_Y) || (channel == SENSOR_CHAN_ACCEL_Z) || (channel == SENSOR_CHAN_ACCEL_XYZ)) {
		switch (attribute) {
		case SENSOR_ATTR_SAMPLING_FREQUENCY:
			return bmi2_set_accel_odr_osr(p_dev, p_value, NULL);
		case SENSOR_ATTR_OVERSAMPLING:
			return bmi2_set_accel_odr_osr(p_dev, NULL, p_value);
		case SENSOR_ATTR_FULL_SCALE:
			return bmi2_set_accel_range(p_dev, p_value);
#if CONFIG_BMI270_TRIGGER
		case SENSOR_ATTR_SLOPE_DUR:
			return bmi270_write_anymo_duration(p_dev, p_value->val1);
		case SENSOR_ATTR_SLOPE_TH:
			return bmi270_write_anymo_threshold(p_dev, *p_value);
#endif
		default:
            return -ENOTSUP;
		}
	} else if ((channel == SENSOR_CHAN_GYRO_X) || (channel == SENSOR_CHAN_GYRO_Y) || (channel == SENSOR_CHAN_GYRO_Z) || (channel == SENSOR_CHAN_GYRO_XYZ)) {
		switch (attribute) {
		case SENSOR_ATTR_SAMPLING_FREQUENCY:
			return bmi2_set_gyro_odr_osr(p_dev, p_value, NULL);
		case SENSOR_ATTR_OVERSAMPLING:
			return bmi2_set_gyro_odr_osr(p_dev, NULL, p_value);
		case SENSOR_ATTR_FULL_SCALE:
			return bmi2_set_gyro_range(p_dev, p_value);
		default:
            return -ENOTSUP;
		}
	}

	return -ENOTSUP;
}

/** @brief
 *  @param
 *  @return
*/
static int bmi270_sample_fetch(const struct device *p_dev, enum sensor_channel channel)
{
    enum pm_device_state pm_state;
    uint16_t temp;
	struct bmi270_data *data = p_dev->data;
    struct bmi2_sens_data sensor_data;

    pm_device_state_get(p_dev, &pm_state);
    if (pm_state != PM_DEVICE_STATE_ACTIVE) {
        return -EIO;
    }

    if ((channel != SENSOR_CHAN_ALL) && (channel != SENSOR_CHAN_ACCEL_XYZ) && (channel != SENSOR_CHAN_GYRO_XYZ) &&
        (channel != SENSOR_CHAN_ACCEL_X) && (channel != SENSOR_CHAN_ACCEL_Y) && (channel != SENSOR_CHAN_ACCEL_Z) &&
        (channel != SENSOR_CHAN_GYRO_X) && (channel != SENSOR_CHAN_GYRO_Y) && (channel != SENSOR_CHAN_GYRO_Z) &&
        (channel != SENSOR_CHAN_AMBIENT_TEMP)) {
        return -ENOTSUP;
    }

    if (bmi2_get_sensor_data(&sensor_data, &bmi2_dev) != BMI2_OK) {
        return -EIO;
    }

    if ((channel == SENSOR_CHAN_ALL) || (channel == SENSOR_CHAN_AMBIENT_TEMP)) {
        if (bmi2_get_temperature_data(&temp, &bmi2_dev) != BMI2_OK) {
            return -EIO;
        }

        data->temp = temp;
    }

    data->ax = sensor_data.acc.x;
    data->ay = sensor_data.acc.y;
    data->az = sensor_data.acc.z;

    data->gx = sensor_data.gyr.x;
    data->gy = sensor_data.gyr.y;
    data->gz = sensor_data.gyr.z;

    return 0;
}

/** @brief
 *  @param
 *  @return
*/
static int bmi270_channel_get(const struct device *p_dev, enum sensor_channel channel, struct sensor_value *p_value)
{
	struct bmi270_data *data = p_dev->data;

	if (channel == SENSOR_CHAN_ACCEL_X) {
		bmi2_raw2accel_convert(p_value, data->ax, data->acc_range);
	} else if (channel == SENSOR_CHAN_ACCEL_Y) {
		bmi2_raw2accel_convert(p_value, data->ay, data->acc_range);
	} else if (channel == SENSOR_CHAN_ACCEL_Z) {
		bmi2_raw2accel_convert(p_value, data->az, data->acc_range);
	} else if (channel == SENSOR_CHAN_ACCEL_XYZ) {
		bmi2_raw2accel_convert(&p_value[0], data->ax, data->acc_range);
		bmi2_raw2accel_convert(&p_value[1], data->ay, data->acc_range);
		bmi2_raw2accel_convert(&p_value[2], data->az, data->acc_range);
	} else if (channel == SENSOR_CHAN_GYRO_X) {
		bmi2_raw2gyro_convert(p_value, data->gx, data->gyr_range);
	} else if (channel == SENSOR_CHAN_GYRO_Y) {
		bmi2_raw2gyro_convert(p_value, data->gy, data->gyr_range);
	} else if (channel == SENSOR_CHAN_GYRO_Z) {
		bmi2_raw2gyro_convert(p_value, data->gz, data->gyr_range);
	} else if (channel == SENSOR_CHAN_GYRO_XYZ) {
		bmi2_raw2gyro_convert(&p_value[0], data->gx, data->gyr_range);
		bmi2_raw2gyro_convert(&p_value[1], data->gy, data->gyr_range);
		bmi2_raw2gyro_convert(&p_value[2], data->gz, data->gyr_range);
	} else if (channel == SENSOR_CHAN_AMBIENT_TEMP) {
        float temperature = (((float)((int16_t)data->temp)) / 512.0) + 23.0;

        p_value->val1 = (int32_t)temperature;
        p_value->val2 = ((int32_t)temperature * 100UL) - (p_value->val1 * 1000UL);
    }
    else if (channel == SENSOR_CHAN_STEPS) {
        // TODO: Shall we move this into the "fetch" call?
        struct bmi2_feat_sensor_data sensor_data;

        sensor_data.type = BMI2_STEP_COUNTER;
        if (bmi270_get_feature_data(&sensor_data, 1, &bmi2_dev) != BMI2_OK) {
            return -EIO;
        }

        p_value->val1 = sensor_data.sens_data.step_counter_output;
    } else {
	    return -ENOTSUP;
    } 

	return 0;
}

static const struct sensor_driver_api bmi270_driver_api = {
    .attr_set = bmi270_attr_set,
    .sample_fetch = bmi270_sample_fetch,
    .channel_get = bmi270_channel_get,
};

/** @brief  
 *  @param  
 *  @return 
*/
static int bmi270_sensor_init(const struct device *p_dev)
{
    int8_t result;
    const struct bmi270_config *config = p_dev->config;

    LOG_DBG("Start to initialize BMP581...");

    if (!device_is_ready(config->i2c.bus)) {
        LOG_ERR("I2C bus device not ready!");
        return -ENODEV;
    }

    bmi2_dev.intf = BMI2_I2C_INTF;
    bmi2_dev.read = bmi2_i2c_read;
    bmi2_dev.write = bmi2_i2c_write;
    bmi2_dev.delay_us = bmi2_delay_us;
    bmi2_dev.read_write_len = BMI2_READ_WRITE_LEN;
    bmi2_dev.config_file_ptr = NULL;

    result = bmi270_init(&bmi2_dev);
    if (result != BMI2_OK) {
        LOG_ERR("Can not initialize BMI270!");
        return -ENODEV;
    }

    if (bmi2_configure_enable_all(&bmi2_dev) != BMI2_OK) {
            return -ENODEV;
    }

#if CONFIG_BMI270_TRIGGER
    if (int1_gpio.port) {
        if (bmi270_sensor_init_interrupt() < 0) {
            LOG_ERR("Could not initialize interrupts!");
            return -EIO;
        }
    }
#endif

    return 0;
}

#ifdef CONFIG_PM_DEVICE
static int bmi270_pm_action(const struct device *p_dev, enum pm_device_action action)
{
    int8_t rslt;

    switch (action) {
        case PM_DEVICE_ACTION_TURN_ON:
        case PM_DEVICE_ACTION_RESUME: {
            break;
        }
        case PM_DEVICE_ACTION_SUSPEND: {
            break;
        }
        case PM_DEVICE_ACTION_TURN_OFF: {
            break;
        }
        default: {
            return -ENOTSUP;
        }
    }

    if(rslt != BMI2_OK) {
        return -EIO;
    }

    return 0;
}
#endif

#define BMI270_INIT(inst)                                                           \
    static struct bmi270_data bmi270_data_##inst;                                   \
                                                                                    \
    static const struct bmi270_config bmi270_config_##inst = {                      \
        .i2c = I2C_DT_SPEC_INST_GET(inst),                                          \
    };                                                                              \
                                                                                    \
    PM_DEVICE_DT_INST_DEFINE(inst, bmi270_pm_action);                               \
                                                                                    \
    SENSOR_DEVICE_DT_INST_DEFINE(inst, bmi270_sensor_init,                          \
                  PM_DEVICE_DT_INST_GET(inst),                                      \
                  &bmi270_data_##inst,                                              \
                  &bmi270_config_##inst, POST_KERNEL,                               \
                  CONFIG_SENSOR_INIT_PRIORITY,                                      \
                  &bmi270_driver_api);

DT_INST_FOREACH_STATUS_OKAY(BMI270_INIT)