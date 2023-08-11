#pragma once

#include <lvgl.h>

extern const lv_img_dsc_t *global_watchface_bg_img;

const lv_img_dsc_t *zsw_ui_utils_icon_from_weather_code(int code, lv_color_t *icon_color);