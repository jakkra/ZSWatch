#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/rtc.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <zsw_clock.h>

#include "zsw_alarm.h"

LOG_MODULE_REGISTER(zsw_alarm, LOG_LEVEL_DBG);

#define RTC_ALARM_MASK_COMPARE_ALL (RTC_ALARM_TIME_MASK_SECOND | RTC_ALARM_TIME_MASK_MINUTE | RTC_ALARM_TIME_MASK_HOUR)

static int find_free_alarm_slot(void);
static void start_earliest_alarm(void);
static int find_earliest_alarm(void);
static void rtc_alarm_triggered_callback(const struct device *dev, uint16_t id, void *user_data);
int compare(const void* rtc_time_a, const void* rtc_time_b);
static void copy_rtc_time_to_tm(struct rtc_time *rtc_time, struct tm *tm_time);
static void copy_tm_to_rtc_time(struct tm *tm_time, struct rtc_time *rtc_time);

static const struct device *rtc = DEVICE_DT_GET(DT_ALIAS(rtc));

static zsw_alarm_t alarms[ZSW_MAX_ALARMS];

int zsw_alarm_add(struct rtc_time expiry_time, alarm_cb callback, void* user_data)
{
    int alarm_index = find_free_alarm_slot();

    if (alarm_index < 0) {
        return -ENOMEM;
    }

    alarms[alarm_index].expiry_time = expiry_time;
    alarms[alarm_index].expiry_time.tm_year -= 1900;
    alarms[alarm_index].used = true;
    alarms[alarm_index].enabled = true;
    alarms[alarm_index].cb = callback;
    alarms[alarm_index].user_data = user_data;

    start_earliest_alarm();

    return alarm_index;
}

int zsw_alarm_add_timer(uint16_t hour, uint16_t min, uint16_t sec, alarm_cb callback, void* user_data)
{
    int ret;
    struct rtc_time alarm_time;
    struct tm tm_alarm_time;

    ret = rtc_get_time(rtc, &alarm_time);
    __ASSERT(ret == 0, "Failed to get current time");

    copy_rtc_time_to_tm(&alarm_time, &tm_alarm_time);

    tm_alarm_time.tm_hour += hour;
    tm_alarm_time.tm_min += min;
    tm_alarm_time.tm_sec += sec;

    // This normalizes the time, i.e. if second gets to 80,
    // it will add one to minute and adjust the seconds to 20.
    if(mktime(&tm_alarm_time) == -1) {
        LOG_ERR("Failed to convert time to epoch: %d", ret);
        return -EINVAL;
    }

    copy_tm_to_rtc_time(&tm_alarm_time, &alarm_time);

    int alarm_index = find_free_alarm_slot();

    if (alarm_index < 0) {
        return -ENOMEM;
    }

    alarms[alarm_index].expiry_time = alarm_time;
    alarms[alarm_index].used = true;
    alarms[alarm_index].enabled = true;
    alarms[alarm_index].cb = callback;
    alarms[alarm_index].user_data = user_data;

    start_earliest_alarm();

    return alarm_index;
}

int zsw_alarm_set_enabled(uint32_t alarm_id, bool enabled)
{
    if (alarm_id >= ZSW_MAX_ALARMS) {
        return -EINVAL;
    }

    if (!alarms[alarm_id].used) {
        return -EINVAL;
    }

    if (alarms[alarm_id].enabled == enabled) {
        return 0;
    }

    alarms[alarm_id].enabled = enabled;

    start_earliest_alarm();

    return 0;
}

int zsw_alarm_get_enabled(uint32_t alarm_id, bool* enabled)
{
    if (alarm_id >= ZSW_MAX_ALARMS) {
        return -EINVAL;
    }

    if (!alarms[alarm_id].used) {
        return -EINVAL;
    }

    *enabled = alarms[alarm_id].enabled;

    return 0;
}

int zsw_alarm_get_remaining(uint32_t alarm_id, uint32_t* hour, uint32_t* min, uint32_t* sec)
{
    if (alarm_id >= ZSW_MAX_ALARMS) {
        return -EINVAL;
    }

    if (!alarms[alarm_id].used) {
        return -EINVAL;
    }

    struct tm current_time_tm = {0};
    struct tm alarm_time_tm = {0};
    struct rtc_time current_time;

    int ret = rtc_get_time(rtc, &current_time);
    if (ret != 0) {
        return ret;
    }

    copy_rtc_time_to_tm(&current_time, &current_time_tm);
    copy_rtc_time_to_tm(&alarms[alarm_id].expiry_time, &alarm_time_tm);

    time_t current_epoch = mktime(&current_time_tm);
    time_t alarm_epoch = mktime(&alarm_time_tm);

    int diffSecs = (int)difftime(alarm_epoch, current_epoch);
    LOG_DBG("start: %d, end: %d, diff: %d", current_epoch, alarm_epoch, diffSecs);
    if (diffSecs < 0) {
        LOG_WRN("Alarm is in the past. Indicates RTC alarm was not triggered");
        diffSecs = 0;
    }
    //__ASSERT(diffSecs >= 0, "Alarm is in the past");

    *hour = diffSecs / 3600;
    *min = (diffSecs % 3600) / 60;
    *sec = diffSecs % 60;

    return 0;
}

int zsw_alarm_remove(uint32_t alarm_id)
{
    if (alarm_id >= ZSW_MAX_ALARMS) {
        return -EINVAL;
    }

    if (!alarms[alarm_id].used) {
        return -EINVAL;
    }

    int earliest_alarm_index = find_earliest_alarm();
    __ASSERT(earliest_alarm_index >= 0, "Failed to find earliest alarm");

    memset(&alarms[alarm_id], 0, sizeof(zsw_alarm_t));

    // Check if removed alarm is the earliest, if so change the rtc alarm to next.
    if (earliest_alarm_index == alarm_id) {
        rtc_alarm_set_callback(rtc, 0, NULL, NULL);
        rtc_alarm_set_time(rtc, 0, 0, NULL);
        start_earliest_alarm();
    }

    return 0;
}

static int find_earliest_alarm(void)
{
    zsw_alarm_t* earliest_alarm = NULL;
    int index = -1;

    for (int i = 0; i < ZSW_MAX_ALARMS; i++) {
        if (alarms[i].used && alarms[i].enabled && (earliest_alarm == NULL || compare(&alarms[i], earliest_alarm) < 0)) {
            earliest_alarm = &alarms[i];
            index = i;
        }
    }

    return index;
}

static void start_earliest_alarm(void)
{
    LOG_DBG("start_earliest_alarm");
    struct rtc_time current_alarm_time;
    uint16_t current_alarm_mask;
    int earliest_alarm_index = find_earliest_alarm();

    int ret = rtc_alarm_get_time(rtc, 0, &current_alarm_mask, &current_alarm_time);
    if (ret != 0) {
        LOG_ERR("Failed to get current alarm time");
        return;
    }

    // No alarms active, and RTC have alarm => disable it
    if (earliest_alarm_index < 0 && current_alarm_mask != 0) {
        LOG_DBG("No alarms active, and RTC have alarm => disable it");
        rtc_alarm_set_callback(rtc, 0, NULL, NULL);
        rtc_alarm_set_time(rtc, 0, 0, NULL);
        return;
    } else if (earliest_alarm_index < 0) {
        // No alarms active
        LOG_DBG("No alarms active");
        return;
    }

    if (current_alarm_mask != 0 && compare(&alarms[earliest_alarm_index], &current_alarm_time) > 0) {
        // The current active alarm is already the earliest
        LOG_DBG("Current alarm is already the earliest");
        return;
    } else {
        // RTC alarm should be updated
        LOG_DBG("RTC alarm should be updated");
        rtc_alarm_set_callback(rtc, 0, NULL, NULL);
        rtc_alarm_set_time(rtc, 0, 0, NULL);
        rtc_alarm_set_time(rtc, 0, RTC_ALARM_MASK_COMPARE_ALL, &alarms[earliest_alarm_index].expiry_time);
        int ret = rtc_alarm_set_callback(rtc, 0, rtc_alarm_triggered_callback, (void*)earliest_alarm_index);
        __ASSERT(ret == 0, "Failed to set alarm callback");
    }
}

static void rtc_alarm_triggered_callback(const struct device *dev, uint16_t id, void *user_data)
{
    LOG_DBG("RTC alarm callback");
    int alarm_index = (int)user_data;
    __ASSERT(alarms[alarm_index].used, "Alarm is not used");
    alarms[alarm_index].used = false;
    alarms[alarm_index].enabled = false;
    // Cancel alarm
    rtc_alarm_set_callback(rtc, 0, NULL, NULL);
    rtc_alarm_set_time(rtc, 0, 0, NULL);
    start_earliest_alarm();
    alarms[alarm_index].cb(alarms[alarm_index].user_data);
}

static int find_free_alarm_slot(void)
{
    for (int i = 0; i < ZSW_MAX_ALARMS; i++) {
        if (!alarms[i].used) {
            return i;
        }
    }
    return -ENOMEM;
}

int compare(const void* rtc_time_a, const void* rtc_time_b) {
    zsw_alarm_t *a = (zsw_alarm_t*)rtc_time_a;
    zsw_alarm_t *b = (zsw_alarm_t*)rtc_time_b;

    if (a != NULL && b == NULL) {
        return 1;
    }

    if (b != NULL && a == NULL) {
        return -1;
    }

    if (!a && !b) {
        return 0;
    }

    if (a->expiry_time.tm_year != b->expiry_time.tm_year) {
        return a->expiry_time.tm_year - b->expiry_time.tm_year;
    }
    if (a->expiry_time.tm_mon != b->expiry_time.tm_mon) {
        return a->expiry_time.tm_mon - b->expiry_time.tm_mon;
    }
    if (a->expiry_time.tm_mday != b->expiry_time.tm_mday) {
        return a->expiry_time.tm_mday - b->expiry_time.tm_mday;
    }
    if (a->expiry_time.tm_hour != b->expiry_time.tm_hour) {
        return a->expiry_time.tm_hour - b->expiry_time.tm_hour;
    }
    if (a->expiry_time.tm_min != b->expiry_time.tm_min) {
        return a->expiry_time.tm_min - b->expiry_time.tm_min;
    }
    if (a->expiry_time.tm_sec != b->expiry_time.tm_sec) {
        return a->expiry_time.tm_sec - b->expiry_time.tm_sec;
    }
    return 0;
}

static void copy_rtc_time_to_tm(struct rtc_time *rtc_time, struct tm *tm_time)
{
    tm_time->tm_year = rtc_time->tm_year;
    tm_time->tm_mon = rtc_time->tm_mon;
    tm_time->tm_mday = rtc_time->tm_mday;
    tm_time->tm_hour = rtc_time->tm_hour;
    tm_time->tm_min = rtc_time->tm_min;
    tm_time->tm_sec = rtc_time->tm_sec;
    tm_time->tm_isdst = rtc_time->tm_isdst;
    tm_time->tm_wday = rtc_time->tm_wday;
    tm_time->tm_yday = rtc_time->tm_yday;
}

static void copy_tm_to_rtc_time(struct tm *tm_time, struct rtc_time *rtc_time)
{
    rtc_time->tm_year = tm_time->tm_year;
    rtc_time->tm_mon = tm_time->tm_mon;
    rtc_time->tm_mday = tm_time->tm_mday;
    rtc_time->tm_hour = tm_time->tm_hour;
    rtc_time->tm_min = tm_time->tm_min;
    rtc_time->tm_sec = tm_time->tm_sec;
    rtc_time->tm_isdst = tm_time->tm_isdst;
    rtc_time->tm_wday = tm_time->tm_wday;
    rtc_time->tm_yday = tm_time->tm_yday;
}

static int zsw_alarm_init(void)
{
    memset(alarms, 0, sizeof(alarms));

    return 0;
}

SYS_INIT(zsw_alarm_init, APPLICATION, 2); // Just after zsw_periodic_event init