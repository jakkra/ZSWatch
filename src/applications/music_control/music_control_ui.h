#pragma once

#include <inttypes.h>
#include <lvgl.h>

typedef void(*on_ui_close_cb_t)(void);

void music_control_ui_show(lv_obj_t *root, on_ui_close_cb_t close_cb);

void music_control_ui_remove(void);

void music_control_ui_music_info(char *track, char *artist);

void music_control_ui_set_track_progress(int percent_played);

void music_control_ui_set_time(int hour, int min, int second);

void music_control_ui_set_music_state(bool playing, int percent_played, bool shuffle);
