/* apds9306.c - Driver for Avago APDS9306 light sensor. */

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

#include "apds9306.h"

#define APDS9306_REGISTER_MAIN_CTRL         0x00
#define APDS9306_REGISTER_ALS_MEAS_RATE     0x04
#define APDS9306_REGISTER_ALS_GAIN          0x05
#define APDS9306_REGISTER_PART_ID           0x06
#define APDS9306_REGISTER_MAIN_STATUS       0x07
#define APDS9306_REGISTER_CLEAR_DATA_0      0x0A
#define APDS9306_REGISTER_CLEAR_DATA_1      0x0B
#define APDS9306_REGISTER_CLEAR_DATA_2      0x0C
#define APDS9306_REGISTER_ALS_DATA_0        0x0D
#define APDS9306_REGISTER_ALS_DATA_1        0x0E
#define APDS9306_REGISTER_ALS_DATA_2        0x0F
#define APDS9306_REGISTER_INT_CFG           0x19
#define APDS9306_REGISTER_INT_PERSISTENCE   0x1A
#define APDS9306_REGISTER_ALS_THRES_UP_0    0x21
#define APDS9306_REGISTER_ALS_THRES_UP_1    0x22
#define APDS9306_REGISTER_ALS_THRES_UP_2    0x23
#define APDS9306_REGISTER_ALS_THRES_LOW_0   0x24
#define APDS9306_REGISTER_ALS_THRES_LOW_1   0x25
#define APDS9306_REGISTER_ALS_THRES_LOW_2   0x26
#define APDS9306_REGISTER_ALS_THRES_VAR     0x27

#define ADPS9306_BIT_ALS_EN                 (0x01 << 0x01)
#define ADPS9306_BIT_ALS_DATA_STATUS        (0x01 << 0x03)
#define APDS9306_BIT_SW_RESET               (0x01 << 0x04)
#define ADPS9306_BIT_ALS_INTERRUPT_STATUS   (0x01 << 0x03)
#define APDS9306_BIT_POWER_ON_STATUS        (0x01 << 0x05)

#if CONFIG_APDS9306_IS_APDS9306_065
    #define APDS_9306_CHIP_ID               0xB3
#else
    #define APDS_9306_CHIP_ID               0xB1
#endif

LOG_MODULE_REGISTER(apds9306, CONFIG_SENSOR_LOG_LEVEL);

#if(DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0)
    #warning "apds9306 driver enabled without any devices"
#endif

struct apds9306_data {
	uint32_t light;
};

struct apds9306_config {
	struct i2c_dt_spec i2c;
    uint8_t Resolution;
    uint8_t Rate;
    uint8_t Gain;
};								

/** @brief          Enable the ALS measurement.
 *  @param p_Dev    Pointer to sensor device
 *  @return         0 when successful
*/
static int apds9306_enable(const struct device* p_Dev)
{
	const struct apds9306_config* Config = p_Dev->config;

	if(i2c_reg_update_byte_dt(&Config->i2c, APDS9306_REGISTER_MAIN_CTRL, ADPS9306_BIT_ALS_EN, ADPS9306_BIT_ALS_EN))
    {
		return -EIO;
	}

    return 0;
}

/** @brief          Disable the ALS measurement.
 *  @param p_Dev    Pointer to sensor device
 *  @return         0 when successful
*/
static int apds9306_standby(const struct device* p_Dev)
{
	const struct apds9306_config* Config = p_Dev->config;

	if(i2c_reg_update_byte_dt(&Config->i2c, APDS9306_REGISTER_MAIN_CTRL, ADPS9306_BIT_ALS_EN, 0x00))
    {
		LOG_ERR("Can not disable ALS!");
		return -EIO;
	}

    return 0;
}

/** @brief          Start and wait for a new light measurement.
 *  @param p_Dev    Pointer to sensor device
 *  @param p_Value  Pointer to sensor result
 *  @return         0 when successful
*/
static int apds9306_read_light(const struct device* p_Dev, uint32_t* p_Value)
{
	int Error;
	const struct apds9306_config* Config = p_Dev->config;
	uint8_t Buffer[3];
    uint8_t Temp;
    uint8_t Register = APDS9306_REGISTER_ALS_DATA_0;
    uint32_t Now;

    LOG_DBG("Start a new measurement...");
    if(apds9306_enable(p_Dev) != 0)
    {
		LOG_ERR("Can not enable ALS!");
		return -EIO;
    }

    // Wait for the oscillator power up. This needs typically 5 ms, but we wait a bit longer to be sure.
    // TODO: Better
    k_msleep(400);

    // Wait for the end of the measurement.
    Now = k_uptime_get_32();
    do
    {
        if(i2c_reg_read_byte_dt(&Config->i2c, APDS9306_REGISTER_MAIN_STATUS, &Temp))
        {
            LOG_ERR("Failed to read ALS status!");
            return -EIO;
        }

        // We wait 100 ms maximum for the device to become ready.
        if((k_uptime_get_32() - Now) > 500)
        {
            LOG_ERR("Sensor timeout!");
            return -EIO;
        }

        k_msleep(10);
    } while(Temp & ADPS9306_BIT_ALS_DATA_STATUS);

    if(apds9306_standby(p_Dev) != 0)
    {
		LOG_ERR("Can not disable ALS!");
		return -EIO;
    }

    // Read the results.
	Error = i2c_write_read_dt(&Config->i2c, &Register, sizeof(Register), &Buffer, sizeof(Buffer));
	if(Error < 0)
    {
		return Error;
	}
    
    *p_Value = sys_get_le24(Buffer);

	return 0;
}

static int apds9306_attr_set(const struct device* p_Dev, enum sensor_channel Channel, enum sensor_attribute Attribute, const struct sensor_value* p_Value)
{
    uint8_t Mask;
    uint8_t Value;
    uint8_t Register;
	const struct apds9306_config* Config = p_Dev->config;

	__ASSERT_NO_MSG(p_Value != NULL);

	if(Channel != SENSOR_CHAN_LIGHT)
    {
		return -ENOTSUP;
	}

	if(Attribute == SENSOR_ATTR_SAMPLING_FREQUENCY)
    {
        Register = APDS9306_REGISTER_ALS_MEAS_RATE;
        Mask = (0x07) << 0x00;
        Value = p_Value->val1 & 0x07;
    }
    else if(Attribute == SENSOR_APDS9306_ATTR_GAIN)
    {
        Register = APDS9306_REGISTER_ALS_GAIN;
        Mask = (0x07) << 0x00;
        Value = p_Value->val1 & 0x07;
    }
    else if(Attribute == SENSOR_APDS9306_ATTR_RESOLUTION)
    {
        Register = APDS9306_REGISTER_ALS_MEAS_RATE;
        Mask = (0x07) << 0x04;
        Value = (p_Value->val1 & 0x07) << 0x04;
    }
    else
    {
        return -ENOTSUP;
    }

	if(i2c_reg_update_byte_dt(&Config->i2c, Register, Mask, Value))
    {
		LOG_ERR("Failed to set sensor attribute!");
		return -EIO;
	}

	return 0;
}

static int apds9306_attr_get(const struct device* p_Dev, enum sensor_channel Channel, enum sensor_attribute Attribute, struct sensor_value* p_Value)
{
    uint8_t Mask;
    uint8_t Value;
    uint8_t Register;
	const struct apds9306_config* Config = p_Dev->config;

	__ASSERT_NO_MSG(p_Value != NULL);

	if(Channel != SENSOR_CHAN_LIGHT)
    {
		return -ENOTSUP;
	}

	if(Attribute == SENSOR_ATTR_SAMPLING_FREQUENCY)
    {
        Register = APDS9306_REGISTER_ALS_MEAS_RATE;
        Mask = 0x00;
    }
    else if(Attribute == SENSOR_APDS9306_ATTR_GAIN)
    {
        Register = APDS9306_REGISTER_ALS_GAIN;
        Mask = 0x00;
    }
    else if(Attribute == SENSOR_APDS9306_ATTR_RESOLUTION)
    {
        Register = APDS9306_REGISTER_ALS_MEAS_RATE;
        Mask = 0x04;
    }
    else
    {
        return -ENOTSUP;
    }

	if(i2c_reg_read_byte_dt(&Config->i2c, Register, &Value))
    {
		LOG_ERR("Failed to read sensor attribute!");
		return -EIO;
	}

    LOG_DBG("Attribute value: %u", Value);

    p_Value->val1 = (Value >> Mask) & 0x07;
    p_Value->val2 = 0;

	return 0;
}

static int apds9306_sample_fetch(const struct device* p_Dev, enum sensor_channel Channel)
{
    int Error;
    uint32_t Value;
	struct apds9306_data* Data = p_Dev->data;
	enum pm_device_state pm_state;

	(void)pm_device_state_get(p_Dev, &pm_state);
	if(pm_state != PM_DEVICE_STATE_ACTIVE)
    {
		return -EIO;
	}

	if((Channel != SENSOR_CHAN_ALL) && (Channel != SENSOR_CHAN_LIGHT))
    {
		return -ENOTSUP;
	}

    Error = apds9306_read_light(p_Dev, &Value);
    if(Error < 0)
    {
        return Error;
    }

    Data->light = Value;

    LOG_DBG("Sensor value: %u", Data->light);

	return 0;
}

static int apds9306_channel_get(const struct device* p_Dev, enum sensor_channel Channel, struct sensor_value* p_Value)
{
	struct apds9306_data* Data = p_Dev->data;

	switch(Channel)
    {
        case SENSOR_CHAN_LIGHT:
        {
            p_Value->val1 = Data->light;
            p_Value->val2 = 0;

            return 0;
        }
        default:
        {
            return -ENOTSUP;
        }
	}
}

static int apds9306_sensor_setup(const struct device* p_Dev)
{
    uint32_t Now;
	uint8_t Temp;
	const struct apds9306_config* Config = p_Dev->config;

    // Wait for the device to become ready after a power cycle.
    Now = k_uptime_get_32();
    do
    {
        i2c_reg_read_byte_dt(&Config->i2c, APDS9306_REGISTER_MAIN_STATUS, &Temp);

        // We wait 100 ms maximum for the device to become ready.
        if((k_uptime_get_32() - Now) > 100)
        {
            LOG_ERR("Sensor timeout!");
            return -EIO;
        }

        k_msleep(10);
    } while(Temp & APDS9306_BIT_POWER_ON_STATUS);

	if(i2c_reg_read_byte_dt(&Config->i2c, APDS9306_REGISTER_PART_ID, &Temp))
    {
		LOG_ERR("Failed reading chip id!");
		return -EIO;
	}

	if(Temp != APDS_9306_CHIP_ID)
    {
		LOG_ERR("Invalid chip id! Found 0x%X, expect 0x%X", Temp, APDS_9306_CHIP_ID);
		return -EIO;
	}

	// Reset the sensor.
	if(i2c_reg_write_byte_dt(&Config->i2c, APDS9306_REGISTER_MAIN_CTRL, APDS9306_BIT_SW_RESET))
    {
		LOG_ERR("Can not reset the sensor!");
		return -EIO;
	}

    k_msleep(10);

	return 0;
}

static int apds9306_interrupt_setup(const struct device* p_Dev)
{
    // TODO

	return 0;
}

static const struct sensor_driver_api apds9306_driver_api = {
    .attr_set = apds9306_attr_set,
	.attr_get = apds9306_attr_get,
	.sample_fetch = apds9306_sample_fetch,
	.channel_get = apds9306_channel_get,
};

static int apds9306_init(const struct device* p_Dev)
{
	const struct apds9306_config* Config = p_Dev->config;

    LOG_DBG("Start to initialize APDS9306...");

	if(device_is_ready(Config->i2c.bus) == false)
    {
		LOG_ERR("Bus device is not ready");
		return -EINVAL;
	}

	if(apds9306_sensor_setup(p_Dev) < 0)
    {
		LOG_ERR("Failed to setup device!");
		return -EIO;
	}

	if(apds9306_interrupt_setup(p_Dev) < 0)
    {
		LOG_ERR("Failed to setup interrupts!");
		return -EIO;
	}

    LOG_DBG("APDS9306 initialization successful!");

	return 0;
}

#ifdef CONFIG_PM_DEVICE
    static int apds9306_pm_action(const struct device* p_Dev, enum pm_device_action Action)
    {
        switch(Action)
        {
            case PM_DEVICE_ACTION_TURN_ON:
            case PM_DEVICE_ACTION_RESUME:
            case PM_DEVICE_ACTION_TURN_OFF:
            case PM_DEVICE_ACTION_SUSPEND:
            {
                break;
            }
            default:
            {
                return -ENOTSUP;
            }
        }

        return 0;
    }
#endif

#define APDS9306_INIT(inst)							                    \
	static struct apds9306_data apds9306_data_##inst;				    \
									                                    \
	static const struct apds9306_config apds9306_config_##inst = {      \
		.i2c = I2C_DT_SPEC_INST_GET(inst),				                \
	};								                                    \
									                                    \
	PM_DEVICE_DT_INST_DEFINE(inst, apds9306_pm_action);                 \
									                                    \
	SENSOR_DEVICE_DT_INST_DEFINE(inst, apds9306_init,			        \
			      PM_DEVICE_DT_INST_GET(inst),			                \
			      &apds9306_data_##inst,				                \
			      &apds9306_config_##inst, POST_KERNEL,		            \
			      CONFIG_SENSOR_INIT_PRIORITY,		                    \
			      &apds9306_driver_api);

DT_INST_FOREACH_STATUS_OKAY(APDS9306_INIT)