#include <zds/zds_ui.h>
#include <application_manager.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/zbus/zbus.h>
#include <events/accel_event.h>

// Functions needed for all applications
static void zds_app_start(lv_obj_t *root, lv_group_t *group);
static void zds_app_stop(void);

static void zbus_accel_data_callback(const struct zbus_channel *chan);

ZBUS_CHAN_DECLARE(accel_data_chan);
ZBUS_LISTENER_DEFINE(zds_app_accel_lis, zbus_accel_data_callback);

LV_IMG_DECLARE(zephyr_icon_round);

static application_t app = {
    .name = "ZDS App",
    .icon = &zephyr_icon_round,
    .start_func = zds_app_start,
    .stop_func = zds_app_stop
};

static void zds_app_start(lv_obj_t *root, lv_group_t *group)
{
    zds_ui_show(root);
}

static void zds_app_stop(void)
{
    zds_ui_remove();
}

static int zds_app_add(const struct device *arg)
{
    application_manager_add_application(&app);

    return 0;
}

static void zbus_accel_data_callback(const struct zbus_channel *chan)
{
    const struct accel_event *event = zbus_chan_const_msg(chan);
    if (event->data.data.gesture == ACCELEROMETER_EVT_GESTURE_WRIST_SHAKE) {
        zds_ui_reset_rotation();
    }
}

SYS_INIT(zds_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
