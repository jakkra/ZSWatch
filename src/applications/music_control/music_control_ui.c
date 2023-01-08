#include <music_control/music_control_ui.h>
#include <lvgl.h>

static void close_button_pressed(lv_event_t *e);

static lv_obj_t *root_page = NULL;
static lv_obj_t *track_name_label;
static lv_obj_t *artist_name_label;
static lv_obj_t *play_pause_button;
static lv_obj_t *progress_arc;
static lv_obj_t *time_label;

static on_ui_close_cb_t close_callback;

static void create_progress_arc(lv_obj_t *parent)
{
    progress_arc = lv_arc_create(parent);
    lv_arc_set_rotation(progress_arc, 270);
    lv_arc_set_bg_angles(progress_arc, 0, 360);
    lv_arc_set_range(progress_arc, 0, 100); // 0-100% battery
    lv_arc_set_value(progress_arc, 0);

    lv_obj_remove_style(progress_arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(progress_arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_set_style_arc_width(progress_arc, 3, LV_PART_MAIN); // Changes background arc width
    lv_obj_set_style_arc_width(progress_arc, 3, LV_PART_INDICATOR); // Changes set part width
    lv_obj_set_style_arc_color(progress_arc, lv_palette_main(LV_PALETTE_LIGHT_BLUE), LV_PART_INDICATOR);

    lv_obj_set_size(progress_arc, 240, 240);
    lv_obj_center(progress_arc);
}

static void play_event_click_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);

    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_FOCUSED) {
        lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN);
        lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN);
        lv_obj_set_style_border_color(obj, lv_color_black(), LV_PART_MAIN);
    } else if (code == LV_EVENT_DEFOCUSED) {
        lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_NONE, LV_PART_MAIN);
    } else if (code == LV_EVENT_CLICKED) {
        if (lv_obj_has_state(obj, LV_STATE_CHECKED)) {
            printk("Play\n");
        } else {
            printk("Pause\n");
        }
    }
}

static void create_buttons(lv_obj_t *parent, lv_group_t *group)
{
    LV_IMG_DECLARE(play);
    LV_IMG_DECLARE(pause);
    LV_IMG_DECLARE(next);
    LV_IMG_DECLARE(previous);

    play_pause_button = lv_imgbtn_create(parent);
    lv_obj_clear_flag(play_pause_button, LV_OBJ_FLAG_SCROLLABLE);
    lv_imgbtn_set_src(play_pause_button, LV_IMGBTN_STATE_RELEASED, NULL, &play, NULL);
    lv_imgbtn_set_src(play_pause_button, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &pause, NULL);
    lv_obj_set_width(play_pause_button, pause.header.w);
    lv_obj_add_flag(play_pause_button, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(play_pause_button, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_center(play_pause_button);
    lv_obj_set_style_pad_bottom(play_pause_button, 20, LV_PART_MAIN);
    lv_obj_add_event_cb(play_pause_button, play_event_click_cb, LV_EVENT_ALL, NULL);
    lv_group_add_obj(group, play_pause_button);

    lv_obj_t *next_button = lv_imgbtn_create(parent);
    lv_obj_clear_flag(next_button, LV_OBJ_FLAG_SCROLLABLE);
    lv_imgbtn_set_src(next_button, LV_IMGBTN_STATE_RELEASED, NULL, &next, NULL);
    lv_obj_set_width(next_button, next.header.w);
    lv_obj_add_flag(next_button, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(next_button, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_align_to(next_button, play_pause_button, LV_ALIGN_OUT_RIGHT_MID, 10, 0);
    lv_obj_add_event_cb(next_button, play_event_click_cb, LV_EVENT_ALL, NULL);
    lv_group_add_obj(group, next_button);

    lv_obj_t *prev_button = lv_imgbtn_create(parent);
    lv_obj_clear_flag(prev_button, LV_OBJ_FLAG_SCROLLABLE);
    lv_imgbtn_set_src(prev_button, LV_IMGBTN_STATE_RELEASED, NULL, &previous, NULL);
    lv_obj_set_width(prev_button, previous.header.w);
    lv_obj_add_flag(prev_button, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(prev_button, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_align_to(prev_button, play_pause_button, LV_ALIGN_OUT_LEFT_MID, -10, 0);
    lv_obj_add_event_cb(prev_button, play_event_click_cb, LV_EVENT_ALL, NULL);
    lv_group_add_obj(group, prev_button);
}

void music_control_ui_show(lv_obj_t *root, on_ui_close_cb_t close_cb)
{
    lv_obj_t *float_btn;

    assert(root_page == NULL);
    close_callback = close_cb;

    // Create the root container
    root_page = lv_obj_create(root);
    // Remove the default border
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    // Make root container fill the screen
    lv_obj_set_size(root_page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_scrollbar_mode(root_page, LV_SCROLLBAR_MODE_OFF);
    lv_obj_clear_flag(root_page, LV_OBJ_FLAG_SCROLLABLE);

    float_btn = lv_btn_create(root_page);
    lv_obj_set_size(float_btn, 150, 25);
    lv_obj_add_flag(float_btn, LV_OBJ_FLAG_FLOATING);
    lv_obj_align(float_btn, LV_ALIGN_BOTTOM_MID, 0, 10);
    lv_obj_add_event_cb(float_btn, close_button_pressed, LV_EVENT_PRESSED, root_page);
    lv_obj_set_style_radius(float_btn, 0, 0);
    lv_obj_set_style_bg_img_src(float_btn, LV_SYMBOL_NEW_LINE, 0);
    lv_obj_set_style_text_font(float_btn, lv_theme_get_font_large(float_btn), 0);
    lv_obj_set_style_bg_color(float_btn, lv_palette_main(LV_PALETTE_AMBER), LV_PART_MAIN);

    create_progress_arc(root_page);

    create_buttons(root_page, lv_obj_get_group(float_btn));

    lv_group_focus_obj(float_btn);

    track_name_label = lv_label_create(root_page);
    lv_obj_align(track_name_label, LV_ALIGN_TOP_MID, 0, 25);
    lv_obj_set_style_text_align(track_name_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(track_name_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(track_name_label, LV_PCT(50));
    lv_label_set_text(track_name_label, "No music playing...");
    lv_obj_set_style_text_color(track_name_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_anim_speed(track_name_label, 10, 0);

    artist_name_label = lv_label_create(root_page);
    lv_obj_align(artist_name_label, LV_ALIGN_TOP_MID, 0, 45);
    lv_obj_set_style_text_align(artist_name_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_long_mode(artist_name_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(artist_name_label, LV_PCT(50));
    lv_label_set_text(artist_name_label, "Artist");
    lv_obj_set_style_text_color(artist_name_label, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_anim_speed(artist_name_label, 10, 0);

    time_label = lv_label_create(root_page);
    lv_obj_align(time_label, LV_ALIGN_TOP_MID, 0, -5);
    lv_obj_set_style_text_align(time_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_width(time_label, LV_SIZE_CONTENT);
    lv_label_set_text(time_label, "...");
    lv_obj_set_style_text_color(time_label, lv_color_black(), LV_PART_MAIN);
    //lv_obj_set_style_text_decor(time_label, LV_TEXT_DECOR_UNDERLINE, LV_PART_MAIN);
}

void music_control_ui_remove(void)
{
    lv_obj_del(root_page);
    root_page = NULL;
    track_name_label = NULL;
}

void music_control_ui_music_info(char *track, char *artist)
{
    lv_label_set_text(track_name_label, track);
    lv_label_set_text(artist_name_label, artist);
}

void music_control_ui_set_track_progress(int percent_played)
{
    lv_arc_set_value(progress_arc, percent_played);
}

void music_control_ui_set_time(int hour, int min, int second)
{
    char buf[30];
    snprintf(buf, sizeof(buf), "%02d:%02d", hour, min);
    lv_label_set_text(time_label, buf);
}


void music_control_ui_set_music_state(bool playing, int percent_played, bool shuffle)
{
    lv_arc_set_value(progress_arc, percent_played);
    if (playing) {
        lv_imgbtn_set_state(play_pause_button, LV_IMGBTN_STATE_CHECKED_RELEASED);
    } else {
        lv_imgbtn_set_state(play_pause_button, LV_IMGBTN_STATE_RELEASED);
    }
}

static void close_button_pressed(lv_event_t *e)
{
    close_callback();
}
