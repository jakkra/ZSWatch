#include <compass/compass_ui.h>
#include <application_manager.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zsw_magnetometer.h>
#include <zsw_popup_window.h>

LOG_MODULE_REGISTER(compass_app, LOG_LEVEL_DBG);

#define SENSOR_REFRESH_INTERVAL_MS  50
#define SENSOR_CALIBRATION_TIME_MS  10000

// Functions needed for all applications
static void compass_app_start(lv_obj_t *root, lv_group_t *group);
static void compass_app_stop(void);

// Functions related to app functionality
static void timer_callback(lv_timer_t *timer);

LV_IMG_DECLARE(move);

static application_t app = {
    .name = "Compass",
    .icon = &move,
    .start_func = compass_app_start,
    .stop_func = compass_app_stop
};

static lv_timer_t *refresh_timer;
static bool is_calibrating;
static uint32_t cal_start_ms;

static void compass_app_start(lv_obj_t *root, lv_group_t *group)
{
    compass_ui_show(root);
    refresh_timer = lv_timer_create(timer_callback, SENSOR_REFRESH_INTERVAL_MS,  NULL);
    zsw_magnetometer_set_enable(true);
    zsw_magnetometer_start_calibration();
    is_calibrating = true;
    cal_start_ms = lv_tick_get();
    zsw_popup_show("Calibration", "Spin around 360 degrees for 10.", NULL, 100);
}

static void compass_app_stop(void)
{
    lv_timer_del(refresh_timer);
    compass_ui_remove();
    zsw_magnetometer_set_enable(false);
    zsw_magnetometer_stop_calibration();
    if (is_calibrating) {
        zsw_popup_remove();
    }
}

static void timer_callback(lv_timer_t *timer)
{
    if (is_calibrating && (lv_tick_elaps(cal_start_ms) >= SENSOR_CALIBRATION_TIME_MS)) {
        zsw_magnetometer_stop_calibration();
        is_calibrating = false;
        zsw_popup_remove();
    }
    if (!is_calibrating) {
        compass_ui_set_heading(zsw_magnetometer_get_heading());
    }
}

static int compass_app_add(void)
{
    application_manager_add_application(&app);
    return 0;
}

SYS_INIT(compass_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
