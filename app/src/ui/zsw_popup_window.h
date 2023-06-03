#ifndef __ZSW_POPUP_WINDOW_H
#define __ZSW_POPUP_WINDOW_H
#include <lvgl.h>

typedef void(*on_close_popup_cb_t)(void);

void zsw_popup_show(char *title, char *body, on_close_popup_cb_t close_cb, uint32_t close_after_seconds);
void zsw_popup_remove(void);
#endif