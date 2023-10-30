#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <math.h>

#include "sensors_summary_ui.h"
#include "sensors/zsw_pressure_sensor.h"
#include "managers/zsw_app_manager.h"

LOG_MODULE_REGISTER(sensors_summary_app, LOG_LEVEL_DBG);

static void sensors_summary_app_start(lv_obj_t *root, lv_group_t *group);
static void sensors_summary_app_stop(void);
static void on_close_sensors_summary(void);
static void on_ref_set(void);

static void timer_callback(lv_timer_t *timer);

LV_IMG_DECLARE(move);

static application_t app = {
    .name = "Sensors",
    .icon = &move,
    .start_func = sensors_summary_app_start,
    .stop_func = sensors_summary_app_stop
};

static lv_timer_t *refresh_timer;
static float relative_pressure;
static const struct device *const bme688 = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(bme688));
static const struct device *const apds9306 = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(apds9306));

static void sensors_summary_app_start(lv_obj_t *root, lv_group_t *group)
{
    sensors_summary_ui_show(root, on_close_sensors_summary, on_ref_set);
    on_ref_set(); // Set inital relative pressure
    zsw_pressure_sensor_set_odr(PRESSURE_SENSOR_ODR_160_HZ); // Increase ODR since we want high accuracy here
    refresh_timer = lv_timer_create(timer_callback, CONFIG_DEFAULT_CONFIGURATION_SENSORS_SUMMARY_REFRESH_INTERVAL_MS,
                                    NULL);
}

static void sensors_summary_app_stop(void)
{
    // Cleanup after ourselves
    // TODO need mechanism so that multiple user can request ODR without
    // breaking for another when changed.
    zsw_pressure_sensor_set_odr(PRESSURE_SENSOR_ODR_DEFAULT);
    lv_timer_del(refresh_timer);
    sensors_summary_ui_remove();
}

static double get_relative_height_m(double relative_pressure, double new_pressure, double temperature)
{
    return ((powf((relative_pressure / new_pressure), 1.f / 5.257f) - 1.f) * (temperature + 273.15f)) / 0.0065f;
}

static void timer_callback(lv_timer_t *timer)
{
    float temperature = 0.0;
    float pressure = 0.0;
    float humidity = 0.0;
    float light = 0.0;
    float iaq = 0.0;
    struct sensor_value sensor_val;

    if (device_is_ready(bme688)) {
        if (sensor_sample_fetch(bme688) != 0) {
            return;
        }

        sensor_channel_get(bme688, SENSOR_CHAN_AMBIENT_TEMP, &sensor_val);
        temperature = sensor_value_to_float(&sensor_val);

        sensor_channel_get(bme688, SENSOR_CHAN_HUMIDITY, &sensor_val);
        humidity = sensor_value_to_float(&sensor_val);

        sensor_channel_get(bme688, SENSOR_CHAN_PRESS, &sensor_val);
        pressure = sensor_value_to_float(&sensor_val);

        sensor_channel_get(bme688, (SENSOR_CHAN_PRIV_START + 1), &sensor_val);
        iaq = sensor_value_to_float(&sensor_val);
    }

    zsw_pressure_sensor_fetch_pressure(&pressure);

    if (device_is_ready(apds9306)) {
        if (sensor_sample_fetch(apds9306) != 0) {
            return;
        }

        sensor_channel_get(apds9306, SENSOR_CHAN_LIGHT, &sensor_val);
        light = sensor_value_to_float(&sensor_val);
    }

    sensors_summary_ui_set_pressure(pressure);
    sensors_summary_ui_set_temp(temperature);
    sensors_summary_ui_set_humidity(humidity);
    sensors_summary_ui_set_iaq(iaq);
    sensors_summary_ui_set_rel_height(get_relative_height_m(relative_pressure, pressure, temperature));
}

static void on_close_sensors_summary(void)
{
    zsw_app_manager_app_close_request(&app);
}

static void on_ref_set(void)
{
    zsw_pressure_sensor_fetch_pressure(&relative_pressure);
}

static int sensors_summary_app_add(void)
{
    zsw_app_manager_add_application(&app);
    return 0;
}

SYS_INIT(sensors_summary_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);