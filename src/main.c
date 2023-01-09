#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/sys/reboot.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <buttons.h>
#include <battery.h>
#include <gpio_debug.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/settings/settings.h>
#include <zephyr/drivers/led.h>
#include <zephyr/logging/log.h>
#include <filesystem.h>
#include <clock.h>
#include <lvgl.h>
#include "watchface.h"
#include <general_ui.h>
#include <heart_rate_sensor.h>
#include <sys/time.h>
#include <ram_retention_storage.h>
#include <accelerometer.h>
#include <ble_comm.h>
#include <ble_aoa.h>
#include <lv_notifcation.h>
#include <notification_manager.h>
#include <notifications_page.h>
#include <vibration_motor.h>
#include <display_control.h>
#include <applications/application_manager.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_WRN);

//#define DEBUG_NOTIFICATIONS

#define WORK_STACK_SIZE 3000
#define WORK_PRIORITY   5

#define RENDER_INTERVAL_LVGL    K_MSEC(100)
#define ACCEL_INTERVAL          K_MSEC(100)
#define BATTERY_INTERVAL        K_SECONDS(10)
#define SEND_STATUS_INTERVAL    K_SECONDS(30)
#define DATE_UPDATE_INTERVAL    K_MINUTES(1)

typedef enum work_type {
    INIT,
    OPEN_SETTINGS,
    UPDATE_CLOCK,
    OPEN_WATCHFACE,
    OPEN_NOTIFICATIONS,
    BATTERY,
    RENDER,
    OPEN_NOTIFICATION,
    CLOSE_NOTIFICATION,
    DEBUG_NOTIFICATION,
    SEND_STATUS_UPDATE,
    UPDATE_DATE
} work_type_t;

typedef enum ui_state {
    INIT_STATE,
    SETTINGS_STATE,
    WATCHFACE_STATE,
    APPLICATION_MANAGER_STATE,
    NOTIFCATION_STATE,
    NOTIFCATION_LIST_STATE,
} ui_state_t;

typedef struct delayed_work_item {
    struct k_work_delayable work;
    work_type_t             type;
} delayed_work_item_t;

static void enable_bluetoth(void);
static void open_settings(void);
static void open_notifications_page(void);
static bool load_retention_ram(void);
static void enocoder_read(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static void encoder_vibration(struct _lv_indev_drv_t *drv, uint8_t e);
static void accel_evt(accelerometer_evt_t *evt);
static void play_not_vibration(void);
static void check_notifications(void);
static int read_battery(int *batt_mV, int *percent);

static void onButtonPressCb(buttonPressType_t type, buttonId_t id);
static void on_notifcation_closed(lv_event_t *e, uint32_t id);
static void on_notification_page_close(void);
static void on_notification_page_notification_close(uint32_t not_id);
static void on_close_application_manager(void);

static void connected(struct bt_conn *conn, uint8_t err);
static void disconnected(struct bt_conn *conn, uint8_t reason);

BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected    = connected,
    .disconnected = disconnected,
};

static delayed_work_item_t battery_work =   { .type = BATTERY };
static delayed_work_item_t render_work =    { .type = RENDER };
static delayed_work_item_t clock_work =     { .type = UPDATE_CLOCK };
static delayed_work_item_t status_work =    { .type = SEND_STATUS_UPDATE };
static delayed_work_item_t date_work =      { .type = UPDATE_DATE };

static delayed_work_item_t general_work_item;

K_THREAD_STACK_DEFINE(my_stack_area, WORK_STACK_SIZE);

static bool buttons_allocated = false;
static lv_group_t *input_group;
static lv_indev_drv_t enc_drv;
static lv_indev_t *enc_indev;
static buttonId_t last_pressed;

static bool display_on = true;
static bool vibrator_on = false;

struct k_work_q my_work_q;
static ui_state_t watch_state = INIT_STATE;

void general_work(struct k_work *item)
{
    int res;
    delayed_work_item_t *the_work = CONTAINER_OF(item, delayed_work_item_t, work);

    switch (the_work->type) {
        case INIT: {
            load_retention_ram();
            filesystem_init();
            heart_rate_sensor_init();
            watchface_init();
            notifications_page_init(on_notification_page_close, on_notification_page_notification_close);
            notification_manager_init();
            enable_bluetoth();

            res = accelerometer_init(accel_evt);
            __ASSERT(res == 0, "Failed init accelerometer");

            clock_init(retained.current_time_seconds);
            buttonsInit(&onButtonPressCb);

            vibration_motor_init();
            vibration_motor_set_on(false);
            display_control_set_brightness(100);

            lv_indev_drv_init(&enc_drv);

            enc_drv.type = LV_INDEV_TYPE_ENCODER;
            enc_drv.read_cb = enocoder_read;
            enc_drv.feedback_cb = encoder_vibration;
            enc_indev = lv_indev_drv_register(&enc_drv);

            input_group = lv_group_create();
            lv_group_set_default(input_group);
            lv_indev_set_group(enc_indev, input_group);

            watchface_show();
            //application_manager_show(on_close_application_manager, lv_scr_act(), input_group);
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &battery_work.work, K_NO_WAIT), "FAIL battery_work");
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &render_work.work, K_NO_WAIT), "FAIL render_work");
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &clock_work.work, K_NO_WAIT), "FAIL clock_work");
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &date_work.work, K_SECONDS(1)), "FAIL clock_work");
            watch_state = WATCHFACE_STATE;
#ifdef DEBUG_NOTIFICATIONS
            general_work_item.type = DEBUG_NOTIFICATION;
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &general_work_item.work, K_SECONDS(5)), "FAIL schedule");
#endif
            break;
        }
        case OPEN_SETTINGS: {
            watch_state = SETTINGS_STATE;
            watchface_remove();
            open_settings();
            break;
        }
        case UPDATE_CLOCK: {
            struct tm *time = clock_get_time();
            LOG_INF("%d, %d, %d\n", time->tm_hour, time->tm_min, time->tm_sec);
            watchface_set_time(time->tm_hour, time->tm_min);

            // Store current time
            retained.current_time_seconds = clock_get_time_unix();
            retained_update();
            check_notifications();
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &clock_work.work, K_SECONDS(1)), "FAIL clock_work");
            break;
        }
        case UPDATE_DATE: {
            struct tm *time = clock_get_time();
            watchface_set_date(time->tm_wday, time->tm_mday);
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &date_work.work, DATE_UPDATE_INTERVAL), "FAIL date_work");
        }
        case OPEN_WATCHFACE: {
            watchface_show();
            buttons_allocated = false;
            watch_state = WATCHFACE_STATE;
            break;
        }
        case OPEN_NOTIFICATIONS: {
            watch_state = NOTIFCATION_LIST_STATE;
            watchface_remove();
            open_notifications_page();
            break;
        }
        case OPEN_NOTIFICATION: {
            not_mngr_notification_t* not = notification_manager_get_newest();
            if (not != NULL) {
                lv_notification_show(not->title, not->body, not->src, not->id, on_notifcation_closed);
                play_not_vibration();
                general_work_item.type = CLOSE_NOTIFICATION;
                __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &general_work_item.work, K_SECONDS(15)), "FAIL schedule");
            } else {
                buttons_allocated = false;
            }
            break;
        }
        case BATTERY: {
            int batt_mv;
            int batt_percent;
            static uint32_t count;

            if (read_battery(&batt_mv, &batt_percent) == 0) {
                watchface_set_battery_percent(batt_percent, batt_mv);
            }
            watchface_set_hrm(count % 220);
            //heart_rate_sensor_fetch(&hr_sample);
            count++;
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &battery_work.work, BATTERY_INTERVAL),
                     "FAIL battery_work");
            break;
        }
        case RENDER: {
            lv_task_handler();
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &render_work.work, RENDER_INTERVAL_LVGL),
                     "FAIL render_work");
            break;
        }
        case SEND_STATUS_UPDATE: {
            int batt_mv;
            int batt_percent;
            int msg_len;
            char buf[100];
            memset(buf, 0, sizeof(buf));

            if (read_battery(&batt_mv, &batt_percent) == 0) {
                msg_len = snprintf(buf, sizeof(buf), "{\"t\":\"status\", \"bat\": %d, \"volt\": %d, \"chg\": %d} \n", batt_percent,
                                   batt_mv, 0);
                ble_comm_send(buf, msg_len);
            }
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &status_work.work, SEND_STATUS_INTERVAL),
                     "Failed schedule status work");
            break;
        }
        case CLOSE_NOTIFICATION: {
            lv_notification_remove();
            buttons_allocated = false;
            break;
        }
        case DEBUG_NOTIFICATION: {
#ifdef DEBUG_NOTIFICATION
            char *body = "This is a body with a longer message that maybe should wrap around or be cut?";
            char *src = "Gmail";
            char *title = "Test Name";
            ble_comm_notify_t raw_not = {
                .body = body,
                .body_len = strlen(body),
                .title = title,
                .title_len = strlen(title),
                .src = src,
                .src_len = strlen(src)
            };
            // Just for debugging faster
            raw_not.id = 0;
            raw_not.title = "Not 0";
            raw_not.title_len = strlen(raw_not.title);
            notification_manager_add(&raw_not);
            raw_not.id = 1;
            raw_not.title = "Not 1";
            raw_not.title_len = strlen(raw_not.title);
            notification_manager_add(&raw_not);
            raw_not.id = 2;
            raw_not.title = "Not 2";
            raw_not.title_len = strlen(raw_not.title);
            notification_manager_add(&raw_not);
            raw_not.id = 3;
            raw_not.title = "Not 3";
            raw_not.title_len = strlen(raw_not.title);
            notification_manager_add(&raw_not);
            raw_not.id = 4;
            raw_not.title = "Not 4";
            raw_not.title_len = strlen(raw_not.title);
            notification_manager_add(&raw_not);
            raw_not.id = 5;
            raw_not.title = "Not 5";
            raw_not.title_len = strlen(raw_not.title);
            buttons_allocated = true;
            play_not_vibration();
            general_work_item.type = OPEN_NOTIFICATIONS;
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &general_work_item.work, K_SECONDS(3)), "FAIL schedule");
#endif
            break;
        }
    }
}

void main(void)
{
    k_work_queue_init(&my_work_q);

    k_work_queue_start(&my_work_q, my_stack_area,
                       K_THREAD_STACK_SIZEOF(my_stack_area), WORK_PRIORITY,
                       NULL);

    k_work_init_delayable(&general_work_item.work, general_work);
    k_work_init_delayable(&battery_work.work, general_work);
    k_work_init_delayable(&render_work.work, general_work); // TODO malloc and free as we can have multiple
    k_work_init_delayable(&clock_work.work, general_work);
    k_work_init_delayable(&status_work.work, general_work);
    k_work_init_delayable(&date_work.work, general_work);

    general_work_item.type = INIT;
    __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &general_work_item.work, K_NO_WAIT), "FAIL schedule");
}

static void on_notifcation_closed(lv_event_t *e, uint32_t id)
{
    // Notification was dismissed, hence consider it read.
    notification_manager_remove(id);

    general_work_item.type = OPEN_WATCHFACE;
    __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &general_work_item.work, K_MSEC(500)), "FAIL schedule");
}

static void on_notification_page_close(void)
{
    general_work_item.type = OPEN_WATCHFACE;
    __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &general_work_item.work, K_MSEC(500)), "FAIL schedule");
}

static void on_notification_page_notification_close(uint32_t not_id)
{
    notification_manager_remove(not_id);
}

static void ble_data_cb(ble_comm_cb_data_t *cb)
{
    not_mngr_notification_t *parsed_not;

    switch (cb->type) {
        case BLE_COMM_DATA_TYPE_NOTIFY:
            parsed_not = notification_manager_add(&cb->data.notify);
            if (!parsed_not) {
                return;
            }
            if (buttons_allocated) {
                return;
            }

            buttons_allocated = true;
            general_work_item.type = OPEN_NOTIFICATION;
            __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &general_work_item.work, K_NO_WAIT), "FAIL schedule not");
            break;
        case BLE_COMM_DATA_TYPE_NOTIFY_REMOVE:
            if (notification_manager_remove(cb->data.notify_remove.id) != 0) {
                LOG_WRN("Notification %d not found", cb->data.notify_remove.id);
            }
            break;
        case BLE_COMM_DATA_TYPE_SET_TIME: {
            struct timespec tspec;
            tspec.tv_sec = cb->data.time.seconds;
            tspec.tv_nsec = 0;
            clock_settime(CLOCK_REALTIME, &tspec);
            break;
        }
        case BLE_COMM_DATA_TYPE_WEATHER:
            LOG_DBG("Weather: %s t: %d hum: %d code: %d wind: %d dir: %d", cb->data.weather.report_text,
                    cb->data.weather.temperature_c, cb->data.weather.humidity, cb->data.weather.weather_code, cb->data.weather.wind,
                    cb->data.weather.wind_direction);
            watchface_set_weather(cb->data.weather.temperature_c, cb->data.weather.weather_code);
            break;
        default:
            break;
    }
}

static void enable_bluetoth(void)
{
    int err;

    err = bt_enable(NULL);
    if (err != 0) {
        LOG_ERR("Failed to enable Bluetooth, err: %d", err);
        return;
    }
#ifdef CONFIG_SETTINGS
    settings_load();
#endif

    __ASSERT_NO_MSG(bleAoaInit());
    __ASSERT_NO_MSG(ble_comm_init(ble_data_cb) == 0);
}

/** A discharge curve specific to the power source. */
static const struct battery_level_point levels[] = {
    /*
    Battery supervisor cuts power at 3500mA so treat that as 0%
    TODO analyze more to get a better curve.
    */
    { 10000, 4150 },
    { 0, 3500 },
};

static int read_battery(int *batt_mV, int *percent)
{
    int rc = battery_measure_enable(true);
    if (rc != 0) {
        LOG_ERR("Failed initialize battery measurement: %d\n", rc);
        return -1;
    }
    // From https://github.com/zephyrproject-rtos/zephyr/blob/main/samples/boards/nrf/battery/src/main.c
    *batt_mV = battery_sample();

    if (*batt_mV < 0) {
        LOG_ERR("Failed to read battery voltage: %d\n", *batt_mV);
        return -1;
    }

    unsigned int batt_pptt = battery_level_pptt(*batt_mV, levels);

    LOG_DBG("%d mV; %u pptt\n", *batt_mV, batt_pptt);
    *percent = batt_pptt / 100;

    rc = battery_measure_enable(false);
    if (rc != 0) {
        LOG_ERR("Failed disable battery measurement: %d\n", rc);
        return -1;
    }
    return 0;
}

static bool load_retention_ram(void)
{
    bool retained_ok = retained_validate();
    //memset(&retained, 0, sizeof(retained));
    /* Increment for this boot attempt and update. */
    retained.boots += 1;
    retained_update();

    printk("Retained data: %s\n", retained_ok ? "valid" : "INVALID");
    printk("Boot count: %u\n", retained.boots);
    printk("uptime_latest: %" PRIu64 "\n", retained.uptime_latest);
    printk("Active Ticks: %" PRIu64 "\n", retained.uptime_sum);

    return retained_ok;
}

static void open_settings(void)
{
    buttons_allocated = true;
    //lv_settings_create(settings_menu, ARRAY_SIZE(settings_menu), "N/A", input_group, on_close_settings);
}

static void open_notifications_page(void)
{
    not_mngr_notification_t notifications[NOTIFICATION_MANAGER_MAX_STORED];
    int num_unread = 0;
    buttons_allocated = true;
    notification_manager_get_all(notifications, &num_unread);
    notifications_page_create(notifications, num_unread, input_group);
}

static void play_press_vibration(void)
{
    vibrator_on = true;
    vibration_motor_set_on(true);
    vibration_motor_set_power(80);
    k_msleep(150);
    vibration_motor_set_power(80);
    vibration_motor_set_on(false);
    vibrator_on = false;
}

static void play_not_vibration(void)
{
    vibrator_on = true;
    vibration_motor_set_power(100);
    vibration_motor_set_on(true);
    k_msleep(50);
    vibration_motor_set_on(false);
    k_msleep(50);
    vibration_motor_set_on(true);
    k_msleep(50);
    vibration_motor_set_on(false);
    k_msleep(50);
    vibration_motor_set_power(0);
    vibration_motor_set_on(true);
    k_msleep(50);
    vibration_motor_set_on(false);
    vibrator_on = false;
}

static void check_notifications(void)
{
    uint32_t num_unread = notification_manager_get_num();
    watchface_set_num_notifcations(num_unread);
}

static void on_close_application_manager(void)
{
    application_manager_delete();
    watch_state = WATCHFACE_STATE;
    watchface_show();
    buttons_allocated = false;
}

static void onButtonPressCb(buttonPressType_t type, buttonId_t id)
{
    LOG_DBG("Pressed %d, type: %d", id, type);

    // Always allow force restart
    if (type == BUTTONS_LONG_PRESS && id == BUTTON_3) {
        retained.off_count += 1;
        retained_update();
        sys_reboot(SYS_REBOOT_COLD);
    }

    if (type == BUTTONS_LONG_PRESS && id == BUTTON_2 && watch_state == APPLICATION_MANAGER_STATE) {
        // TODO doesn't work, as this press is read later with lvgl and causes extra press in settings.
        // To fix each application must have exit button, maybe we can register long press on the whole view to exit
        // apps without input device
        //application_manager_exit_app();
        //return;
    }

    if (buttons_allocated) {
        // Handled by LVGL
        return;
    }

    if (type == BUTTONS_SHORT_PRESS) {
        if (watch_state == WATCHFACE_STATE) {
            if (id == BUTTON_2) {
                watch_state = NOTIFCATION_LIST_STATE;
            } else {
                watch_state = APPLICATION_MANAGER_STATE;
            }
        } else if (watch_state == APPLICATION_MANAGER_STATE) {
            watch_state = WATCHFACE_STATE;
        }
        play_press_vibration();
        switch (watch_state) {
            case WATCHFACE_STATE:
                application_manager_delete();
                watchface_show();
                break;
            case APPLICATION_MANAGER_STATE:
                watchface_remove();
                buttons_allocated = true;
                application_manager_show(on_close_application_manager, lv_scr_act(), input_group);
                break;
            case NOTIFCATION_LIST_STATE:
                general_work_item.type = OPEN_NOTIFICATIONS;
                __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &general_work_item.work, K_NO_WAIT), "FAIL schedule");
                break;
            default:
                break;
        }
    } else {
        if (id == BUTTON_2) {
            // Not used right now
        } else if (id == BUTTON_3) {
            retained.off_count += 1;
            retained_update();
            sys_reboot(SYS_REBOOT_COLD);
        }
    }
}

static void enocoder_read(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    if (!buttons_allocated) {
        return;
    }
    if (button_read(BUTTON_1)) {
        data->key = LV_KEY_RIGHT;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_1;
    } else if (button_read(BUTTON_2)) {
        data->key = LV_KEY_ENTER;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_2;
    } else if (button_read(BUTTON_3)) {
        data->key = LV_KEY_LEFT;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_3;
    } else {
        if (last_pressed == 0xFF) {
            return;
        }
        data->state = LV_INDEV_STATE_REL;
        switch (last_pressed) {
            case BUTTON_1:
                data->key = LV_KEY_RIGHT;
                break;
            case BUTTON_2:
                data->key = LV_KEY_ENTER;
                break;
            case BUTTON_3:
                data->key = LV_KEY_LEFT;
                break;
        }
        last_pressed = 0xFF;
    }
}

void encoder_vibration(struct _lv_indev_drv_t *drv, uint8_t e)
{
    if (e == LV_EVENT_PRESSED) {
        play_press_vibration();
    }
}

static void connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        LOG_ERR("Connection failed (err %u)", err);
        return;
    }
    __ASSERT(0 <= k_work_reschedule_for_queue(&my_work_q, &status_work.work, K_MSEC(1000)), "FAIL status");

    watchface_set_ble_connected(true);
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    watchface_set_ble_connected(false);
}

static void accel_evt(accelerometer_evt_t *evt)
{
    switch (evt->type) {
        case ACCELEROMETER_EVT_TYPE_DOOUBLE_TAP: {
            if (vibrator_on || (watch_state != WATCHFACE_STATE)) {
                // Vibrator causes false double tap detections.
                // Need more work to not detect when vibration is running, hence for now only allow on watchface page
                break;
            }
            display_on = !display_on;
            if (display_on) {
                display_control_set_brightness(100);
            } else {
                display_control_set_brightness(1);
            }
            break;
        }
        case ACCELEROMETER_EVT_TYPE_STEP: {
            watchface_set_step(evt->data.step.count);
            break;
        }
        case ACCELEROMETER_EVT_TYPE_XYZ: {
            LOG_ERR("x: %d y: %d z: %d", evt->data.xyz.x, evt->data.xyz.y, evt->data.xyz.z);
            break;
        }
        case ACCELEROMETER_EVT_TYPE_TILT: {
            // Tilt detect not working as we want yet, so don't do for now.
            //display_control_set_brightness(100);
            break;
        }
    }
}
