#include <accelerometer.h>
#include <logging/log.h>
#include "lis2ds12_reg.h"

LOG_MODULE_REGISTER(accel, LOG_LEVEL_WRN);

static void data_ready_xyz(const struct device *dev,
				    const struct sensor_trigger *trig);

static const struct device *sensor;
static accel_event_cb accel_evt_cb;

int accelerometer_init(accel_event_cb cb)
{
    struct sensor_value odr;
    struct sensor_trigger trig;
    sensor = device_get_binding(DT_LABEL(DT_INST(0, st_lis2ds12)));
    if (!device_is_ready(sensor)) {
        LOG_ERR("Error: Device \"%s\" is not ready; "
                "check the driver initialization logs for errors.",
                sensor->name);
        return -ENODEV;
    }

    // Set default to Low Power mode

    odr.val1 = 12; // 12HZ LP
    odr.val2 = 0;
    int err = sensor_attr_set(sensor, SENSOR_CHAN_ACCEL_XYZ, SENSOR_ATTR_SAMPLING_FREQUENCY, &odr);
    if (!err) {
        trig.type = SENSOR_TRIG_DATA_READY;
        trig.chan = SENSOR_CHAN_ALL;
        err = sensor_trigger_set(sensor, &trig, data_ready_xyz);
        if (err == 0) {
            LOG_WRN("sensor_trigger_set OK!");
            accel_evt_cb = cb;
        }
    } else {
        LOG_DBG("sensor_attr_set fail: %d", err);
    }

    return err;
}

int accelerometer_fetch_xyz(int16_t* x, int16_t* y, int16_t* z)
{
    __ASSERT(device_is_ready(sensor), "Accelerometer not initialized correctly");
    int err = sensor_sample_fetch(sensor);
    if (err) {
        LOG_ERR("Could not fetch sample from %s", sensor->name);
    }
    struct sensor_value acc_val[3];
    if (!err) {
        err = sensor_channel_get(sensor, SENSOR_CHAN_ACCEL_XYZ, acc_val);
        if (err < 0) {
            LOG_ERR("\nERROR: Unable to read accel XYZ:%d\n", err);
        } else {
            *x = (int16_t)(sensor_value_to_double(&acc_val[0]) * (32768 / 16));
            *y = (int16_t)(sensor_value_to_double(&acc_val[1]) * (32768 / 16));
            *z = (int16_t)(sensor_value_to_double(&acc_val[2]) * (32768 / 16));
        }
    }

    return err;
}

int accelerometer_fetch_temperature(struct sensor_value* temperature)
{
    __ASSERT(!device_is_ready(sensor), "Accelerometer not initialized correctly");
    stmdev_ctx_t *ctx = (stmdev_ctx_t *)sensor->config;
    int err = lis2ds12_temperature_raw_get(ctx, (uint8_t *)temperature);

    if (err < 0) {
        LOG_ERR("\nERROR: Unable to read temperature:%d\n", err);
    } else {
        LOG_DBG("Temp (TODO convert from 2 complement) %d\n", temperature->val1);
    }

    return err;
}

static void data_ready_xyz(const struct device *dev, const struct sensor_trigger *trig)
{
    accelerometer_evt_t evt;
    struct sensor_value acc_val[3];
	int err = sensor_sample_fetch_chan(dev, SENSOR_CHAN_ACCEL_XYZ);
    int16_t x;
    int16_t y;
    int16_t z;
    if (!err) {
        err = sensor_channel_get(sensor, SENSOR_CHAN_ACCEL_XYZ, acc_val);
        if (err < 0) {
            LOG_ERR("\nERROR: Unable to read accel XYZ:%d\n", err);
        } else {
            x = (int16_t)(sensor_value_to_double(&acc_val[0]) * (32768 / 16));
            y = (int16_t)(sensor_value_to_double(&acc_val[1]) * (32768 / 16));
            z = (int16_t)(sensor_value_to_double(&acc_val[2]) * (32768 / 16));
            if (accel_evt_cb) {
                evt.type = ACCELEROMETER_EVT_TYPE_XYZ;
                evt.data.xyz.x = x;
                evt.data.xyz.y = y;
                evt.data.xyz.z = z;
                accel_evt_cb(&evt);
            }
        }
    }
}