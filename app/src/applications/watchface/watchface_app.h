#pragma once

#include <lvgl.h>
#include <zephyr/init.h>

// UI need to be initialized after watchface_app
#define WATCHFACE_UI_INIT_PRIO 99

typedef enum watchface_app_evt_t {
    WATCHFACE_APP_EVT_CLICK_BATT,
    WATCHFACE_APP_EVT_CLICK_STEP,
    WATCHFACE_APP_EVT_CLICK_WEATHER,
} watchface_app_evt_t;

typedef void(*watchface_app_evt_listener)(watchface_app_evt_t);

typedef struct watchface_ui_api_t {
    void (*show)(watchface_app_evt_listener);
    void (*remove)(void);
    void (*set_battery_percent)(int32_t percent, int32_t value);
    void (*set_hrm)(int32_t value);
    void (*set_step)(int32_t value);
    void (*set_time)(int32_t hour, int32_t minute, int32_t second);
    void (*set_ble_connected)(bool connected);
    void (*set_num_notifcations)(int32_t value);
    void (*set_weather)(int8_t temperature, int weather_code);
    void (*set_date)(int day_of_week, int date);
    void (*set_watch_env_sensors)(int temperature, int humidity, int pressure);
    void (*ui_invalidate_cached)(void);
} watchface_ui_api_t;

void watchface_app_start(lv_group_t *group, watchface_app_evt_listener evt_cb);
void watchface_app_stop(void);
void watchface_change(void);
void watchface_app_register_ui(watchface_ui_api_t *ui);
