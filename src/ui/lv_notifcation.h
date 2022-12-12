#ifndef __LV_NOTIFCATION_H
#define __LV_NOTIFCATION_H
#include <lvgl.h>

typedef void(*on_close_not_cb_t)(lv_event_t *e);

typedef enum notification_icon {
    NOTIFICATION_MESSENGER,
    NOTFICATION_GMAIL,
    NOTFICATION_NONE
} notification_icon_t;

void lv_notification_show(char *title, char *body, notification_icon_t icon, on_close_not_cb_t close_cb);
void lv_notification_remove(void);
#endif