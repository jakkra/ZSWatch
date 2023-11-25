#pragma once

#include <inttypes.h>
#include <lvgl.h>

#include "managers/zsw_notification_manager.h"

LV_IMG_DECLARE(ui_img_whatsapp_png);
LV_IMG_DECLARE(ui_img_gadget_png);
LV_IMG_DECLARE(ui_img_mail_png);
LV_IMG_DECLARE(ui_img_call_png);

typedef void(*on_notification_remove_cb_t)(uint32_t id);

void notifications_ui_page_init(on_notification_remove_cb_t not_removed_cb);

void notifications_ui_page_create(zsw_not_mngr_notification_t *notifications, uint8_t num_notifications,
                               lv_group_t *input_group);

void notifications_ui_page_close(void);

void notifications_ui_add_notification(zsw_not_mngr_notification_t *not, lv_group_t *group);