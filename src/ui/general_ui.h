#ifndef __GENERAL_UI_H
#define __GENERAL_UI_H
#include <inttypes.h>
#include <lvgl.h>

void general_ui_anim_out_all(lv_obj_t *obj, uint32_t delay);
void general_ui_anim_in(lv_obj_t *obj, uint32_t delay);

#endif