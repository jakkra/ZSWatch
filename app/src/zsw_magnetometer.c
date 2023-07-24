#include <zsw_magnetometer.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/pm/pm.h>
#include <zephyr/pm/device.h>
#include <zephyr/pm/policy.h>
#include <zephyr/logging/log.h>
#include <inttypes.h>
#include <math.h>

LOG_MODULE_REGISTER(magnetometer, LOG_LEVEL_WRN);

#ifndef M_PI
#define M_PI        3.14159265358979323846
#endif

static const struct device *const magnetometer = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(lis2mdl));

static double xyz_to_rotation(double x, double y, double z);
static void lis2mdl_trigger_handler(const struct device *dev, const struct sensor_trigger *trig);

static double last_heading;
static double last_x;
static double last_y;
static double last_z;
static double max_x;
static double max_y;
static double max_z;
static double min_x;
static double min_y;
static double min_z;
static bool is_calibrating;
static float offset_x;
static float offset_y;
static float offset_z;

int zsw_magnetometer_init(void)
{
    if (!device_is_ready(magnetometer)) {
        LOG_ERR("Device magnetometer is not ready\n");
        return -ENODEV;
    }

    struct sensor_trigger trig;
    struct sensor_value odr_attr;

    odr_attr.val1 = 10; // TODO what value
    odr_attr.val2 = 0;

    if (sensor_attr_set(magnetometer, SENSOR_CHAN_ALL,
                        SENSOR_ATTR_SAMPLING_FREQUENCY, &odr_attr) < 0) {
        LOG_ERR("Cannot set sampling frequency for LIS2MDL\n");
        return -EFAULT;
    }

    trig.type = SENSOR_TRIG_DATA_READY;
    trig.chan = SENSOR_CHAN_MAGN_XYZ;
    sensor_trigger_set(magnetometer, &trig, lis2mdl_trigger_handler);

    // TODO handle power save, enable/disable etc. to save power
    int rc = pm_device_action_run(magnetometer, PM_DEVICE_ACTION_SUSPEND);
    __ASSERT(rc == 0, "Failed to suspend LIS2MDL: %d\n", rc);

    return 0;
}

int zsw_magnetometer_set_enable(bool enabled)
{
    if (!device_is_ready(magnetometer)) {
        return -ENODEV;
    }
    int rc;
    if (enabled) {
        rc = pm_device_action_run(magnetometer, PM_DEVICE_ACTION_RESUME);
        __ASSERT(rc == 0 || rc == -EALREADY, "Failed to resume LIS2MDL: %d\n", rc);
    } else {
        rc = pm_device_action_run(magnetometer, PM_DEVICE_ACTION_SUSPEND);
        __ASSERT(rc == 0 || rc == -EALREADY, "Failed to suspend LIS2MDL: %d\n", rc);
    }
    return 0;
}

int zsw_magnetometer_start_calibration(void)
{
    if (!device_is_ready(magnetometer)) {
        return -ENODEV;
    }

    max_x = -100000;
    max_y = -100000;
    max_z = -100000;
    min_x = 100000;
    min_y = 100000;
    min_z = 100000;
    is_calibrating = true;

    return 0;
}

int zsw_magnetometer_stop_calibration(void)
{
    if (!device_is_ready(magnetometer)) {
        return -ENODEV;
    }

    is_calibrating = false;
    offset_x = (max_x + min_x) / 2;
    offset_y = (max_y + min_y) / 2;
    offset_z = (max_z + min_z) / 2;

    return 0;
}

double zsw_magnetometer_get_heading(void)
{
    return last_heading;
}

int zsw_magnetometer_get_all(float *x, float *y, float *z)
{
    if (!device_is_ready(magnetometer)) {
        return -ENODEV;
    }

    *x = last_x;
    *y = last_y;
    *z = last_z;

    return 0;
}

static void lis2mdl_trigger_handler(const struct device *dev,
                                    const struct sensor_trigger *trig)
{
    struct sensor_value die_temp2;
    struct sensor_value magn[3];
    sensor_sample_fetch_chan(dev, SENSOR_CHAN_ALL);

    sensor_channel_get(magnetometer, SENSOR_CHAN_MAGN_XYZ, magn);
    sensor_channel_get(magnetometer, SENSOR_CHAN_DIE_TEMP, &die_temp2);

    LOG_DBG("LIS2MDL: Magn (gauss): x: %.3f, y: %.3f, z: %.3f\n",
            sensor_value_to_double(&magn[0]),
            sensor_value_to_double(&magn[1]),
            sensor_value_to_double(&magn[2]));

    last_x = sensor_value_to_double(&magn[0]);
    last_y = sensor_value_to_double(&magn[1]);
    last_z = sensor_value_to_double(&magn[2]);

    LOG_DBG("LIS2MDL: Temperature: %.1f C\n",
            sensor_value_to_double(&die_temp2));

    if (is_calibrating) {
        if (last_x < min_x) min_x = last_x;
        if (last_x > max_x) max_x = last_x;

        if (last_y < min_y) min_y = last_y;
        if (last_y > max_y) max_y = last_y;

        if (last_z < min_z) min_z = last_z;
        if (last_z > max_z) max_z = last_z;
    }

    last_x = last_x - offset_x;
    last_y = last_y - offset_y;
    last_z = last_z - offset_z;

    last_heading = xyz_to_rotation(last_x, last_y, last_z);


    LOG_DBG("Rotation: %f", last_heading);
}

// https://arduino.stackexchange.com/questions/18625/converting-three-axis-magnetometer-to-degrees/88707#88707
// Note this assumes watch is flat to eath, TODO use accelerometer to compensate when tilted.
static double xyz_to_rotation(double x, double y, double z)
{
    double heading = atan2(y, x) * 180 / M_PI;
    if (heading < 0) {
        heading = 360 + heading;
    }
    return heading;
}