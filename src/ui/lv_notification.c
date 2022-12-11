#include <lv_notifcation.h>

static void on_notifcation_closed(lv_event_t * e);


static lv_obj_t *mbox;
static on_close_not_cb_t on_close_cb;

void lv_notification_show(char *title, char *body, on_close_not_cb_t close_cb)
{
    on_close_cb = close_cb;
    mbox = lv_msgbox_create(lv_scr_act(), title, body, NULL, true);
    lv_obj_t *close_btn = lv_msgbox_get_close_btn(mbox);
    lv_obj_add_event_cb(close_btn, on_notifcation_closed, LV_EVENT_PRESSED, NULL);
    lv_obj_center(mbox);
    lv_group_focus_obj(close_btn);
    lv_obj_set_size(mbox, 240, 120);
    lv_obj_set_style_radius(mbox, 5, 0);
    lv_obj_clear_flag(mbox, LV_OBJ_FLAG_SCROLLABLE);

    static lv_style_t style_indic_blue;
    lv_style_init(&style_indic_blue);
    lv_style_set_bg_color(&style_indic_blue, lv_palette_main(LV_PALETTE_BLUE));
    lv_obj_add_style(mbox, &style_indic_blue, 0);

    static lv_style_t color_style;

    lv_style_init(&color_style);
    lv_style_set_text_color(&color_style, lv_color_hex(0xFE4644));
    lv_style_set_bg_color(&color_style, lv_color_hex(0xC1C1C1));
    lv_obj_add_style(close_btn, &color_style, 0);

    lv_obj_align_to(mbox, lv_scr_act(), LV_ALIGN_CENTER, 0, 90);
}

void lv_notification_remove(void)
{
    if (mbox) {
        lv_msgbox_close(mbox);
    }
}

static void on_notifcation_closed(lv_event_t * e)
{
    mbox = NULL;
    on_close_cb(e);
}