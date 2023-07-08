#include <sensors_summary/sensors_summary_ui.h>
#include <application_manager.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <pressure_sensor.h>
#include <math.h>

LOG_MODULE_REGISTER(sensors_summary_app, LOG_LEVEL_DBG);

#define SENSOR_REFRESH_INTERVAL_MS  100

// Functions needed for all applications
static void sensors_summary_app_start(lv_obj_t *root, lv_group_t *group);
static void sensors_summary_app_stop(void);
static void on_close_sensors_summary(void);
static void on_ref_set(void);

// Functions related to app functionality
static void timer_callback(lv_timer_t *timer);

LV_IMG_DECLARE(move);

static application_t app = {
    .name = "Sensors",
    .icon = &move,
    .start_func = sensors_summary_app_start,
    .stop_func = sensors_summary_app_stop
};

static const struct device *const bme680 = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(bme688));

static lv_timer_t *refresh_timer;

static float relative_pressure;

static void sensors_summary_app_start(lv_obj_t *root, lv_group_t *group)
{
    sensors_summary_ui_show(root, on_close_sensors_summary, on_ref_set);
    on_ref_set(); // Set inital relative pressure
    pressure_sensor_set_odr(PRESSURE_SENSOR_ODR_160_HZ); // Increase ODR since we want high accuracy here
    refresh_timer = lv_timer_create(timer_callback, SENSOR_REFRESH_INTERVAL_MS,  NULL);
}

static void sensors_summary_app_stop(void)
{
    // Cleanup after ourselves
    // TODO need mechanism so that multiple user can request ODR without
    // breaking for another when changed.
    pressure_sensor_set_odr(PRESSURE_SENSOR_ODR_DEFAULT);
    lv_timer_del(refresh_timer);
    sensors_summary_ui_remove();
}

static double get_relative_height_m(double relative_pressure, double new_pressure, double temperature)
{
    return ((powf((relative_pressure / new_pressure), 1.f / 5.257f) - 1.f) * (temperature + 273.15f)) / 0.0065f;
}

static void timer_callback(lv_timer_t *timer)
{
    struct sensor_value temp_sensor_val;
    float temperature;
    float pressure;
    double gas_res;
    double humidity;
    int rc;

    if (!device_is_ready(bme680)) {
        return;
    }

    pressure_sensor_fetch_pressure(&pressure, &temperature);

    rc = sensor_sample_fetch(bme680);
    if (rc != 0) {
        printf("bme680 sensor_sample_fetch error: %d\n", rc);
        return;
    }

    sensor_channel_get(bme680, SENSOR_CHAN_AMBIENT_TEMP, &temp_sensor_val);
    temperature = sensor_value_to_double(&temp_sensor_val);

    sensor_channel_get(bme680, SENSOR_CHAN_GAS_RES, &temp_sensor_val);
    gas_res = sensor_value_to_double(&temp_sensor_val);

    sensor_channel_get(bme680, SENSOR_CHAN_HUMIDITY, &temp_sensor_val);
    humidity = sensor_value_to_double(&temp_sensor_val);

    sensors_summary_ui_set_pressure(pressure);
    sensors_summary_ui_set_temp(temperature);
    sensors_summary_ui_set_gas(gas_res);
    sensors_summary_ui_set_humidity(humidity);
    sensors_summary_ui_set_rel_height(get_relative_height_m(relative_pressure, pressure, temperature));
}

static void on_close_sensors_summary(void)
{
    application_manager_app_close_request(&app);
}

static void on_ref_set(void)
{
    float temperature;

    pressure_sensor_fetch_pressure(&relative_pressure, &temperature);
}

static int sensors_summary_app_add(void)
{
    application_manager_add_application(&app);
    return 0;
}

SYS_INIT(sensors_summary_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
