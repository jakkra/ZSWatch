#pragma once

/*
* The Zephyr RTC API takes an alarm ID as an argument.
* This ID is used to identify the alarm when it is triggered.
* As this ID is not translated into some internal ID, and instead used
* directly as an index in an array, the max value comes from DTS.
* When using the RTC alarm API, the alarm ID must be added in this file.
* Otherwise an alarm may get triggered by someone else.
*/
typedef enum {
    ZSW_RTC_ALARM_ID_IMU_STEP_RESET,
} zsw_rtc_alarm_id_t;