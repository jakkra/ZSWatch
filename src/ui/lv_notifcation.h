#ifndef __LV_NOTIFCATION_H
#define __LV_NOTIFCATION_H
#include <lvgl.h>

typedef void(*on_close_not_cb_t)(lv_event_t *e);

void lv_notification_show(char *title, char *body, on_close_not_cb_t close_cb);
void lv_notification_remove(void);
#endif