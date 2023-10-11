#include "manager/zsw_power_manager.h"
#include "ui/popup/zsw_popup_window.h"

static void on_popup_closed(lv_event_t *e);
static void close_popup_timer(lv_timer_t *timer);

static lv_obj_t *mbox;
static on_close_popup_cb_t on_close_cb;
static lv_timer_t *auto_close_timer;

void zsw_popup_show(char *title, char *body, on_close_popup_cb_t close_cb, uint32_t close_after_seconds)
{
    if (mbox) {
        // TODO handle queue of popups
        return;
    }
    zsw_power_manager_reset_idle_timout();
    on_close_cb = close_cb;
    mbox = lv_msgbox_create(lv_scr_act(), title, body, NULL, true);
    lv_obj_set_scrollbar_mode(lv_scr_act(), LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(mbox, LV_SCROLLBAR_MODE_OFF);
    lv_obj_t *close_btn = lv_msgbox_get_close_btn(mbox);
    lv_obj_add_event_cb(close_btn, on_popup_closed, LV_EVENT_PRESSED, NULL);
    lv_obj_center(mbox);
    lv_group_focus_obj(close_btn);
    lv_obj_set_size(mbox, 180, 80);
    lv_obj_set_style_radius(mbox, 5, 0);
    lv_obj_clear_flag(mbox, LV_OBJ_FLAG_SCROLLABLE);

    static lv_style_t style_indic_not_bg;
    lv_style_init(&style_indic_not_bg);
    lv_style_set_bg_color(&style_indic_not_bg, lv_color_hex(0x2C3333));
    lv_obj_add_style(mbox, &style_indic_not_bg, 0);

    static lv_style_t color_style;
    lv_style_init(&color_style);
    lv_style_set_text_color(&color_style, lv_color_hex(0xCBE4DE));
    lv_style_set_bg_color(&color_style, lv_color_hex(0x2C3333));
    lv_obj_add_style(close_btn, &color_style, 0);

    auto_close_timer = lv_timer_create(close_popup_timer, close_after_seconds * 1000,  NULL);
    lv_timer_set_repeat_count(auto_close_timer, 1);
}

void zsw_popup_remove(void)
{
    if (mbox) {
        lv_timer_del(auto_close_timer);
        lv_msgbox_close(mbox);
        mbox = NULL;
    }
}

static void on_popup_closed(lv_event_t *e)
{
    lv_timer_del(auto_close_timer);
    mbox = NULL;
    if (on_close_cb) {
        on_close_cb();
    }
}

static void close_popup_timer(lv_timer_t *timer)
{
    zsw_popup_remove();
    if (on_close_cb) {
        on_close_cb();
    }
}
