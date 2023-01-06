#include <music_control/music_control_ui.h>
#include <lvgl.h>

static void close_button_pressed(lv_event_t *e);

static lv_obj_t *root_page = NULL;
static lv_obj_t *music_info_label;
static on_ui_close_cb_t close_callback;

void music_control_ui_show(lv_obj_t *root, on_ui_close_cb_t close_cb)
{
    lv_obj_t *float_btn;
    lv_obj_t *title_label;

    assert(root_page == NULL);
    close_callback = close_cb;

    // Create the root container
    root_page = lv_obj_create(root);
    // Remove the default border
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    // Make root container fill the screen
    lv_obj_set_size(root_page, LV_PCT(100), LV_PCT(100));

    float_btn = lv_btn_create(root_page);
    lv_obj_set_size(float_btn, 50, 50);
    lv_obj_add_flag(float_btn, LV_OBJ_FLAG_FLOATING);
    lv_obj_align(float_btn, LV_ALIGN_BOTTOM_RIGHT, 0, -lv_obj_get_style_pad_right(root_page, LV_PART_MAIN));
    lv_obj_add_event_cb(float_btn, close_button_pressed, LV_EVENT_PRESSED, root_page);
    lv_obj_set_style_radius(float_btn, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_img_src(float_btn, LV_SYMBOL_CLOSE, 0);
    lv_obj_set_style_text_font(float_btn, lv_theme_get_font_large(float_btn), 0);

    // Add a label on the button
    title_label = lv_label_create(root_page);
    lv_obj_align_to(title_label, root_page, LV_ALIGN_TOP_MID, 0, 10);
    lv_label_set_text(title_label, "Playing:");
    lv_obj_set_style_text_color(title_label, lv_color_black(), LV_PART_MAIN);

    music_info_label = lv_label_create(root_page);
    lv_obj_center(music_info_label);
    lv_label_set_text(music_info_label, "No music playing...");
    lv_obj_set_style_text_color(music_info_label, lv_color_black(), LV_PART_MAIN);

    lv_group_focus_obj(float_btn);
}

void music_control_ui_remove(void)
{
    lv_obj_del(root_page);
    root_page = NULL;
    music_info_label = NULL;
}

void music_control_ui_set_text(char *text)
{
    lv_label_set_text(music_info_label, text);
}

static void close_button_pressed(lv_event_t *e)
{
    close_callback();
}
