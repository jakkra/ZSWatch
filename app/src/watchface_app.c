#include <watchface_ui.h>

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/sys/reboot.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/logging/log.h>
#include <lvgl.h>
#include <clock.h>
#include <heart_rate_sensor.h>
#include <accelerometer.h>
#include <vibration_motor.h>
#include <ram_retention_storage.h>
#include <events/ble_data_event.h>
#include <events/accel_event.h>
#include <notification_manager.h>
#include <zephyr/zbus/zbus.h>
#include <zsw_charger.h>
#include <events/chg_event.h>
#include <events/battery_event.h>
#include <events/activity_event.h>
#include <zsw_battery_manager.h>

LOG_MODULE_REGISTER(watcface_app, LOG_LEVEL_WRN);

static void zbus_ble_comm_data_callback(const struct zbus_channel *chan);
static void zbus_accel_data_callback(const struct zbus_channel *chan);
static void zbus_chg_state_data_callback(const struct zbus_channel *chan);
static void zbus_battery_sample_data_callback(const struct zbus_channel *chan);
static void zbus_activity_event_callback(const struct zbus_channel *chan);

ZBUS_CHAN_DECLARE(ble_comm_data_chan);
ZBUS_LISTENER_DEFINE(watchface_ble_comm_lis, zbus_ble_comm_data_callback);

ZBUS_CHAN_DECLARE(accel_data_chan);
ZBUS_LISTENER_DEFINE(watchface_accel_lis, zbus_accel_data_callback);

ZBUS_CHAN_DECLARE(chg_state_data_chan);
ZBUS_LISTENER_DEFINE(watchface_chg_event, zbus_chg_state_data_callback);

ZBUS_CHAN_DECLARE(battery_sample_data_chan);
ZBUS_LISTENER_DEFINE(watchface_battery_event, zbus_battery_sample_data_callback);

ZBUS_CHAN_DECLARE(activity_state_data_chan);
ZBUS_LISTENER_DEFINE(watchface_activity_state_event, zbus_activity_event_callback);

#define WORK_STACK_SIZE 3000
#define WORK_PRIORITY   5

#define RENDER_INTERVAL_LVGL    K_MSEC(100)
#define ACCEL_INTERVAL          K_MSEC(100)
#define DATE_UPDATE_INTERVAL    K_MINUTES(1)

typedef enum work_type {
    UPDATE_CLOCK,
    OPEN_WATCHFACE,
    UPDATE_DATE
} work_type_t;

typedef struct delayed_work_item {
    struct k_work_delayable work;
    work_type_t             type;
} delayed_work_item_t;

void general_work(struct k_work *item);

static void check_notifications(void);
static void update_ui_from_event(struct k_work *item);

static void connected(struct bt_conn *conn, uint8_t err);
static void disconnected(struct bt_conn *conn, uint8_t reason);

BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected    = connected,
    .disconnected = disconnected,
};

static delayed_work_item_t clock_work =     { .type = UPDATE_CLOCK };
static delayed_work_item_t date_work =      { .type = UPDATE_DATE };

static delayed_work_item_t general_work_item;
static struct k_work_sync canel_work_sync;

static K_WORK_DEFINE(update_ui_work, update_ui_from_event);
static ble_comm_cb_data_t last_data_update;
static ble_comm_weather_t last_weather_data;
static struct battery_sample_event last_batt_evt = {.percent = 100, .mV = 4300};
static struct chg_state_event last_chg_evt;

static bool running;
static bool is_connected;
static bool is_suspended;

static int watchface_app_init(void)
{
    k_work_init_delayable(&general_work_item.work, general_work);
    k_work_init_delayable(&clock_work.work, general_work);
    k_work_init_delayable(&date_work.work, general_work);
    running = false;
    is_suspended = false;
    return 0;
}

void watchface_app_start(lv_group_t *group)
{
    general_work_item.type = OPEN_WATCHFACE;
    __ASSERT(0 <= k_work_schedule(&general_work_item.work, K_MSEC(100)), "FAIL schedule");
}

void watchface_app_stop(void)
{
    running = false;
    is_suspended = false;
    k_work_cancel_delayable_sync(&clock_work.work, &canel_work_sync);
    k_work_cancel_delayable_sync(&date_work.work, &canel_work_sync);
    watchface_remove();
}

void general_work(struct k_work *item)
{
    delayed_work_item_t *the_work = CONTAINER_OF(item, delayed_work_item_t, work);
    uint32_t steps;

    switch (the_work->type) {
        case OPEN_WATCHFACE: {
            running = true;
            is_suspended = false;
            watchface_show();
            watchface_set_ble_connected(is_connected);
            watchface_set_battery_percent(last_batt_evt.percent, last_batt_evt.mV);
            if (strlen(last_weather_data.report_text) > 0) {
                watchface_set_weather(last_weather_data.temperature_c, last_weather_data.weather_code);
            }
            if (accelerometer_fetch_num_steps(&steps) == 0) {
                watchface_set_step(steps);
            }

            __ASSERT(0 <= k_work_schedule(&clock_work.work, K_NO_WAIT), "FAIL clock_work");
            __ASSERT(0 <= k_work_schedule(&date_work.work, K_SECONDS(1)), "FAIL clock_work");
            break;
        }
        case UPDATE_CLOCK: {
            struct tm *time = clock_get_time();
            LOG_INF("%d, %d, %d\n", time->tm_hour, time->tm_min, time->tm_sec);
            watchface_set_time(time->tm_hour, time->tm_min, time->tm_sec);

            // TODO move from this file
            retained.current_time_seconds = clock_get_time_unix();
            retained_update();
            check_notifications();

            // Realtime update of steps
            if (accelerometer_fetch_num_steps(&steps) == 0) {
                watchface_set_step(steps);
            }
            __ASSERT(0 <= k_work_schedule(&clock_work.work, K_SECONDS(1)), "FAIL clock_work");
            break;
        }
        case UPDATE_DATE: {
            struct tm *time = clock_get_time();
            watchface_set_date(time->tm_wday, time->tm_mday);
            __ASSERT(0 <= k_work_schedule(&date_work.work, DATE_UPDATE_INTERVAL), "FAIL date_work");
        }
    }
}

static void check_notifications(void)
{
    uint32_t num_unread = notification_manager_get_num();
    watchface_set_num_notifcations(num_unread);
}

static void connected(struct bt_conn *conn, uint8_t err)
{
    is_connected = true;
    if (!running || is_suspended) {
        return;
    }
    if (err) {
        LOG_ERR("Connection failed (err %u)", err);
        return;
    }
    watchface_set_ble_connected(true);
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    is_connected = false;
    if (!running | is_suspended) {
        return;
    }
    watchface_set_ble_connected(false);
}

static void update_ui_from_event(struct k_work *item)
{
    if (running && !is_suspended) {
        if (last_data_update.type == BLE_COMM_DATA_TYPE_WEATHER) {
            LOG_DBG("Weather: %s t: %d hum: %d code: %d wind: %d dir: %d", last_data_update.data.weather.report_text,
                    last_data_update.data.weather.temperature_c, last_data_update.data.weather.humidity,
                    last_data_update.data.weather.weather_code,
                    last_data_update.data.weather.wind,
                    last_data_update.data.weather.wind_direction);
            watchface_set_weather(last_data_update.data.weather.temperature_c, last_data_update.data.weather.weather_code);
        } else if (last_data_update.type == BLE_COMM_DATA_TYPE_SET_TIME) {
            k_work_reschedule(&date_work.work, K_NO_WAIT);
        }
        return;
    }
}

static void zbus_ble_comm_data_callback(const struct zbus_channel *chan)
{
    const struct ble_data_event *event = zbus_chan_const_msg(chan);
    // TODO getting this callback again before workqueue has ran will
    // cause previous to be lost.
    memcpy(&last_data_update, &event->data, sizeof(ble_comm_cb_data_t));
    memcpy(&last_weather_data, &last_data_update.data.weather, sizeof(last_data_update.data.weather));
    if (running && !is_suspended) {
        k_work_submit(&update_ui_work);
    }
}

static void zbus_accel_data_callback(const struct zbus_channel *chan)
{
    if (running && !is_suspended) {
        const struct accel_event *event = zbus_chan_const_msg(chan);
        if (event->data.type == ACCELEROMETER_EVT_TYPE_STEP) {
            watchface_set_step(event->data.data.step.count);
        }
    }
}

static void zbus_chg_state_data_callback(const struct zbus_channel *chan)
{
    const struct chg_state_event *event = zbus_chan_const_msg(chan);
    memcpy(&last_chg_evt, event, sizeof(struct chg_state_event));

    if (running && !is_suspended) {
        // TODO Show some nice animation or similar
    }
}

static void zbus_battery_sample_data_callback(const struct zbus_channel *chan)
{
    const struct battery_sample_event *event = zbus_chan_const_msg(chan);
    memcpy(&last_batt_evt, event, sizeof(struct battery_sample_event));

    if (running && !is_suspended) {
        watchface_set_battery_percent(event->percent, event->mV);
    }
}

static void zbus_activity_event_callback(const struct zbus_channel *chan)
{
    if (running) {
        const struct activity_state_event *event = zbus_chan_const_msg(chan);
        if (event->state == ZSW_ACTIVITY_STATE_INACTIVE) {
            is_suspended = true;
            k_work_cancel_delayable_sync(&clock_work.work, &canel_work_sync);
            k_work_cancel_delayable_sync(&date_work.work, &canel_work_sync);
        } else if (event->state == ZSW_ACTIVITY_STATE_ACTIVE) {
            is_suspended = false;
            watchface_ui_invalidate_cached();
            __ASSERT(0 <= k_work_schedule(&clock_work.work, K_NO_WAIT), "FAIL clock_work");
            __ASSERT(0 <= k_work_schedule(&date_work.work, K_SECONDS(1)), "FAIL clock_work");
        }
    }
}

SYS_INIT(watchface_app_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
