#pragma once

#include <inttypes.h>
#include <lvgl.h>

typedef void(*on_start_calibraion_cb_t)(void);

void compass_ui_show(lv_obj_t *root, on_start_calibraion_cb_t start_cal_cb);

void compass_ui_remove(void);

void compass_ui_set_heading(double heading);
