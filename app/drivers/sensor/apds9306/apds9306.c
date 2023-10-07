/* apds9306.c - Driver for Avago APDS-9306 light sensor. */

/*
 * Copyright (c) 2023, Daniel Kampert
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT avago_apds9306

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/pm/device.h>
#include <zephyr/pm/device_runtime.h>
#include <zephyr/logging/log.h>

//LOG_MODULE_REGISTER(apds9306, CONFIG_SENSOR_LOG_LEVEL);
LOG_MODULE_REGISTER(apds9306, LOG_LEVEL_INF);

#if(DT_NUM_INST_STATUS_OKAY(DT_DRV_COMPAT) == 0)
    #warning "apds9306 driver enabled without any devices"
#endif

struct apds9306_data_t {
	int16_t light;
};

struct apds9306_config_t {
	struct i2c_dt_spec i2c;
};								

static int apds9306_sample_fetch(const struct device* p_Dev, enum sensor_channel Channel)
{
	struct apds9306_data *data = p_Dev->data;
	const struct apds9306_config_t *cfg = p_Dev->config;
	enum pm_device_state pm_state;
	int ret;

	(void)pm_device_state_get(p_Dev, &pm_state);
	if(pm_state != PM_DEVICE_STATE_ACTIVE)
    {
		ret = -EIO;
		return ret;
	}

	switch(Channel)
    {
        case SENSOR_CHAN_ALL:
        case SENSOR_CHAN_LIGHT:
        {
            //ret = lm75_fetch_temp(cfg, data);
            break;
        }
        default:
        {
            ret = -ENOTSUP;
            break;
        }
	}

	return ret;
}

static int apds9306_channel_get(const struct device* p_Dev, enum sensor_channel Channel, struct sensor_value* p_Value)
{
	struct apds9306_data *data = p_Dev->data;

	switch(Channel)
    {
        case SENSOR_CHAN_LIGHT:
        {
            return 0;
        }
        default:
        {
            return -ENOTSUP;
        }
	}
}

static const struct sensor_driver_api apds9306_driver_api = {
	.sample_fetch = apds9306_sample_fetch,
	.channel_get = apds9306_channel_get,
};

static int apds9306_init(const struct device* p_Dev)
{
	int ret = 0;

    LOG_INF("Init driver");

	return ret;
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
	static struct apds9306_data_t apds9306_data_##inst;				    \
									                                    \
	static const struct apds9306_config_t apds9306_config_##inst = {    \
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