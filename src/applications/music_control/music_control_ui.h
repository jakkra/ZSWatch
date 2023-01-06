#pragma once

#include <inttypes.h>
#include <lvgl.h>

typedef void(*on_ui_close_cb_t)(void);

void music_control_ui_show(lv_obj_t *root, on_ui_close_cb_t close_cb);

void music_control_ui_remove(void);

void music_control_ui_set_text(char *text);
