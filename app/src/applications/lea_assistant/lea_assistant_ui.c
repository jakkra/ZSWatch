#include "lea_assistant_ui.h"
#include "managers/zsw_app_manager.h"

static lv_obj_t *root_page = NULL;
static lv_obj_t *spinner = NULL;
static lv_obj_t *mbox = NULL;
static lv_timer_t *timeout_timer = NULL;
static on_button_press_cb_t click_callback;
static on_close_cb_t close_callback;

static void click_popup_event_cb(lv_event_t *e)
{
    if (mbox != NULL) {
        lv_msgbox_close(mbox);
        mbox = NULL;
    }

    close_callback();
}

static void timeout_popup(void)
{
    mbox = lv_msgbox_create(NULL, "Scan timeout!", NULL, NULL, true);
    lv_obj_t *close_btn = lv_msgbox_get_close_btn(mbox);
    // LVGL is not calling for the event cb below, so need to remove all events before adding a new one.
    lv_obj_remove_event_cb(close_btn, NULL);
    lv_obj_add_event_cb(close_btn, click_popup_event_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_center(mbox);
    lv_obj_set_size(mbox, 180, LV_SIZE_CONTENT);
    lv_obj_set_style_radius(mbox, 5, 0);
}

static void timeout_timer_cb(lv_timer_t *timer)
{
    // Title and spinner child objects
    if ((lv_obj_get_child_cnt(root_page) <= 2) && (spinner != NULL)) {
        timeout_popup();
    }
}

static void click_event_cb(lv_event_t *e)
{
    lea_assistant_device_t *selected = (lea_assistant_device_t *)lv_event_get_user_data(e);
    click_callback(selected);
}

static void scroll_event_cb(lv_event_t *e)
{
    lv_obj_t *cont = lv_event_get_target(e);
    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;
    lv_coord_t r = lv_obj_get_height(cont) * 5 / 10;

    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for (i = 0; i < child_cnt; i++) {
        lv_obj_t *child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

        lv_coord_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        /* Get the x of diff_y on a circle. */
        lv_coord_t x;
        /* If diff_y is out of the circle use the last point of the circle (the radius) */
        if (diff_y >= r) {
            x = r;
        } else {
            /* Use Pythagoras theorem to get x from radius and y */
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);   /* Use lvgl's built in sqrt root function */
            x = r - res.i - 20; /* Added - 20 here to pull all a bit more to the left side */
        }

        /* Translate the item by the calculated X coordinate */
        lv_obj_set_style_translate_x(child, x, 0);
        lv_obj_set_style_translate_y(child, -13, 0);

        /* Uncomment if to use some opacity with larger translations */
        //lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        //lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}

static void page_init(lv_obj_t *root, const char *header)
{
    assert(root_page == NULL);
    timeout_timer = lv_timer_create(timeout_timer_cb, 10000, NULL);
    lv_timer_set_repeat_count(timeout_timer, 1);

    root_page = lv_obj_create(root);
    lv_obj_set_style_pad_row(root_page, 2, 0);
    lv_obj_set_style_border_side(root_page, LV_BORDER_SIDE_NONE, 0);
    lv_obj_set_size(root_page, LV_PCT(100), LV_PCT(100));
    lv_obj_center(root_page);
    // May change to a roller and have both on the same screen, need to check if it can be added dynamically: https://docs.lvgl.io/8.3/widgets/core/roller.html
    lv_obj_set_flex_flow(root_page, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_event_cb(root_page, scroll_event_cb, LV_EVENT_SCROLL, NULL);
    lv_obj_set_style_radius(root_page, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_scroll_dir(root_page, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(root_page, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(root_page, LV_SCROLLBAR_MODE_OFF);

    lv_obj_t *title = lv_label_create(root_page);
    lv_obj_set_width(title, LV_PCT(100));
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 55);                 /*Aling to the center of screen*/
    lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER, 0);  /*Allign text center*/
    lv_obj_set_style_text_font(title, &lv_font_montserrat_18, 0); /*Change font size*/
    lv_label_set_text(title, header);

    /*Create a spinner*/
    spinner = lv_spinner_create(lv_layer_top(), 1000, 60);
    lv_obj_set_size(spinner, LV_PCT(40), LV_PCT(40));
    lv_obj_center(spinner);
}

void lea_assistant_ui_add_list_entry(lea_assistant_device_t *device)
{
    if (spinner != NULL) {
        lv_obj_del(spinner);
        spinner = NULL;
    }

    lv_obj_t *btn = lv_obj_create(root_page);
    lv_obj_center(btn);
    lv_obj_set_style_border_side(btn, LV_BORDER_SIDE_NONE, 0);
    lv_obj_set_scrollbar_mode(btn, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_size(btn, LV_PCT(100), LV_PCT(20));
    lv_obj_add_flag(btn, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    lv_obj_t *title = lv_label_create(btn);
    lv_label_set_text(title, device->name);
    lv_obj_set_size(title, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align(title, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);

    lv_obj_set_user_data(btn, title);
    lv_obj_add_event_cb(btn, click_event_cb, LV_EVENT_CLICKED, device);
}

void lea_assistant_ui_show(lv_obj_t *root, on_button_press_cb_t on_button_click_cb, on_close_cb_t close_cb)
{
    click_callback = on_button_click_cb;
    close_callback = close_cb;
    page_init(root, "Audio source:");
}

void lea_assistant_ui_show_sink(on_button_press_cb_t on_button_click_cb)
{
    if (root_page != NULL) {
        lv_obj_del(root_page);
        root_page = NULL;
    }

    click_callback = on_button_click_cb;
    page_init(lv_scr_act(), "Audio sink:");
}

void lea_assistant_ui_remove(void)
{
    if (mbox != NULL) {
        lv_msgbox_close(mbox);
    }

    if (root_page != NULL) {
        lv_obj_del(root_page);
        root_page = NULL;
    }

    if (spinner != NULL) {
        lv_obj_del(spinner);
        spinner = NULL;
    }
}
