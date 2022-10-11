#ifndef __WATCH_UI_H
#define __WATCH_UI_H
#include <inttypes.h>

void watchface_init(void);

void watchface_show(void);

void watchface_set_battery_percent(int32_t value);

void watchface_set_hrm(int32_t value);

void watchface_set_step(int32_t value);

void watchface_set_value_minute(int32_t value);

void watchface_set_value_hour(int32_t value);

#endif