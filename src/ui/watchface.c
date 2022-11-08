#include <watchface.h>
#include <lvgl.h>
#include <logging/log.h>

#define SMALL_WATCHFACE_CENTER_OFFSET 37

static lv_obj_t * root_page = NULL;

static lv_obj_t * clock_meter;
static lv_meter_indicator_t * indic_min;
static lv_meter_indicator_t * indic_hour;

static lv_obj_t * battery_label;
static lv_obj_t * battery_arc;

static lv_obj_t * hrm_label;
static lv_obj_t * hrm_arc;

static lv_obj_t * step_label;
static lv_obj_t * step_arc;

static void tick_draw_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    
    if(code == LV_EVENT_DRAW_PART_BEGIN) {
        lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
        if (dsc->type == LV_METER_DRAW_PART_TICK && dsc->text != NULL) {
            if (dsc->value > 0) {
                dsc->text_length = snprintf(dsc->text, 16, "%d", dsc->value / 5);
            } else {
                dsc->text[0] = '\0';
                dsc->text_length = 0;
            }
        }
    }
}

static void add_clock(lv_obj_t* parent)
{
    clock_meter = lv_meter_create(parent);
    lv_obj_set_size(clock_meter, 240, 240);
    lv_obj_center(clock_meter);

    /*Create a scale for the minutes*/
    /*61 ticks in a 360 degrees range (the last and the first line overlaps)*/
    lv_meter_scale_t * scale_min = lv_meter_add_scale(clock_meter);
    lv_obj_set_style_border_color(clock_meter, lv_color_hex(0xFFFFFF), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(clock_meter, LV_OPA_TRANSP, LV_PART_MAIN);
    //lv_obj_set_style_bg_color(clock_meter, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
    lv_obj_set_style_pad_all(clock_meter, 0, LV_PART_MAIN);
    lv_meter_set_scale_ticks(clock_meter, scale_min, 61, 1, 10, lv_palette_main(LV_PALETTE_DEEP_ORANGE));
    lv_meter_set_scale_range(clock_meter, scale_min, 0, 60, 360, 270);

    /*Create another scale for the hours. It's only visual and contains only major ticks*/
    lv_meter_scale_t * scale_hour = lv_meter_add_scale(clock_meter);
    //lv_meter_set_scale_ticks(clock_meter, scale_hour, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));               /*12 ticks*/
    //lv_meter_set_scale_range(clock_meter, scale_hour, 1, 12, 330, 300);       /*[1..12] values in an almost full circle*/
    lv_meter_set_scale_ticks(clock_meter, scale_hour, 61, 1, 10, lv_palette_main(LV_PALETTE_DEEP_ORANGE));
    lv_meter_set_scale_range(clock_meter, scale_hour, 0, 60, 360, 270);
    lv_meter_set_scale_major_ticks(clock_meter, scale_hour, 5, 2, 20, lv_color_black(), 10);    /*Every tick is major*/

    lv_obj_add_event_cb(clock_meter, tick_draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_obj_remove_style(clock_meter, NULL, LV_PART_INDICATOR);
    
    LV_IMG_DECLARE(minute_hand)
    LV_IMG_DECLARE(hour_hand)
    /*Add a the hands from images*/
    
    //lv_meter_indicator_t * indic_min = lv_meter_add_needle_line(clock_meter, scale_min, 2, lv_color_hex(0x00FF00), 1);
    indic_min = lv_meter_add_needle_img(clock_meter, scale_min, &minute_hand, 8, minute_hand.header.h - 8);
    indic_hour = lv_meter_add_needle_img(clock_meter, scale_hour, &hour_hand, 8, hour_hand.header.h - 8);
}

static void add_battery_indicator(lv_obj_t* parent)
{
    /*Create an Arc*/
    battery_arc = lv_arc_create(parent);
    lv_arc_set_rotation(battery_arc, 270);
    lv_arc_set_bg_angles(battery_arc, 0, 360);
    lv_arc_set_range(battery_arc, 0, 100); // 0-100% battery
    lv_obj_remove_style(battery_arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(battery_arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_set_style_arc_width(battery_arc, 3, LV_PART_MAIN); // Changes background arc width
    lv_obj_set_style_arc_width(battery_arc, 3, LV_PART_INDICATOR); // Changes set part width
    lv_obj_set_style_arc_color(battery_arc, lv_palette_main(LV_PALETTE_DEEP_ORANGE), LV_PART_INDICATOR);
    
    lv_obj_set_size(battery_arc, 50, 50);
    lv_obj_align_to(battery_arc, parent, LV_ALIGN_CENTER, -SMALL_WATCHFACE_CENTER_OFFSET, -SMALL_WATCHFACE_CENTER_OFFSET);
    
    LV_IMG_DECLARE(voltage);

    lv_obj_t * charge_icon = lv_img_create(parent);
    lv_img_set_src(charge_icon, &voltage);
    lv_obj_align_to(charge_icon, battery_arc, LV_ALIGN_CENTER, 0, 9);

    battery_label = lv_label_create(parent);
    lv_label_set_text(battery_label, "-%");
    lv_obj_align_to(battery_label, battery_arc, LV_ALIGN_CENTER, 0, -9);

}

static void add_pulse_indicator(lv_obj_t* parent)
{
    hrm_arc = lv_arc_create(parent);
    lv_arc_set_rotation(hrm_arc, 270);
    lv_arc_set_bg_angles(hrm_arc, 0, 360);
    lv_arc_set_range(hrm_arc, 0, 220); // 220 max hrm
    lv_obj_remove_style(hrm_arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(hrm_arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_set_style_arc_width(hrm_arc, 3, LV_PART_MAIN); // Changes background arc width
    lv_obj_set_style_arc_width(hrm_arc, 3, LV_PART_INDICATOR); // Changes set part width
    lv_obj_set_style_arc_color(hrm_arc, lv_palette_main(LV_PALETTE_RED), LV_PART_INDICATOR);
    
    lv_obj_set_size(hrm_arc, 50, 50);
    lv_obj_align_to(hrm_arc, parent, LV_ALIGN_CENTER, -SMALL_WATCHFACE_CENTER_OFFSET, SMALL_WATCHFACE_CENTER_OFFSET);
    
    LV_IMG_DECLARE(heart_beat);

    lv_obj_t * charge_icon = lv_img_create(parent);
    lv_img_set_src(charge_icon, &heart_beat);
    lv_obj_align_to(charge_icon, hrm_arc, LV_ALIGN_CENTER, 0, 9);

    hrm_label = lv_label_create(parent);
    lv_label_set_text(hrm_label, "-");
    lv_obj_align_to(hrm_label, hrm_arc, LV_ALIGN_CENTER, 0, -9);
}

static void add_step_indicator(lv_obj_t* parent)
{
    step_arc = lv_arc_create(parent);
    lv_arc_set_rotation(step_arc, 270);
    lv_arc_set_bg_angles(step_arc, 0, 360);
    lv_arc_set_range(step_arc, 0, 10000); // 10000 daily step goal
    lv_obj_remove_style(step_arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_clear_flag(step_arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_set_style_arc_width(step_arc, 3, LV_PART_MAIN); // Changes background arc width
    lv_obj_set_style_arc_width(step_arc, 3, LV_PART_INDICATOR); // Changes set part width
    lv_obj_set_style_arc_color(step_arc, lv_palette_main(LV_PALETTE_LIGHT_BLUE), LV_PART_INDICATOR);
    
    lv_obj_set_size(step_arc, 50, 50);
    lv_obj_align_to(step_arc, parent, LV_ALIGN_CENTER, SMALL_WATCHFACE_CENTER_OFFSET, SMALL_WATCHFACE_CENTER_OFFSET);
    
    LV_IMG_DECLARE(walk);

    lv_obj_t * charge_icon = lv_img_create(parent);
    lv_img_set_src(charge_icon, &walk);
    lv_obj_align_to(charge_icon, step_arc, LV_ALIGN_CENTER, 0, 9);

    step_label = lv_label_create(parent);
    lv_label_set_text(step_label, "-");
    lv_obj_align_to(step_label, step_arc, LV_ALIGN_CENTER, 0, -9);

}


void watchface_init(void)
{
    lv_obj_clean(lv_scr_act());
}

void watchface_show(void)
{
    if (root_page != NULL) {
        lv_obj_clear_flag(root_page, LV_OBJ_FLAG_HIDDEN);
        return;
    }

    root_page = lv_obj_create(lv_scr_act());
    lv_obj_set_scrollbar_mode(root_page, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(root_page, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(root_page, 240, 240);
    lv_obj_align(root_page, LV_ALIGN_CENTER, 0, 0);
    add_battery_indicator(root_page);
    add_pulse_indicator(root_page);
    add_step_indicator(root_page);
    add_clock(root_page);

    general_ui_anim_in(root_page, 100);
}

void watchface_remove(void)
{
    lv_obj_add_flag(root_page, LV_OBJ_FLAG_HIDDEN);
    //root_page = NULL;
    //general_ui_anim_out_all(lv_scr_act(), 0);

    //if (!root_page) return;
    //lv_obj_del(root_page);
}

void watchface_set_battery_percent(int32_t percent, int32_t value)
{
    if (!root_page) return;
    char buf[5];
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "%dmV", value);
    lv_arc_set_value(battery_arc, percent);
    lv_label_set_text(battery_label, buf);
    lv_obj_align_to(battery_label, battery_arc, LV_ALIGN_CENTER, 0, -9);
}

void watchface_set_hrm(int32_t value)
{
    if (!root_page) return;
    char buf[5];
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "%d", value);
    lv_arc_set_value(hrm_arc, value);
    lv_label_set_text(hrm_label, buf);
    lv_obj_align_to(hrm_label, hrm_arc, LV_ALIGN_CENTER, 0, -9);
}

void watchface_set_step(int32_t value)
{
    if (!root_page) return;
    char buf[6];
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "%d", value);
    lv_arc_set_value(step_arc, value);
    lv_label_set_text(step_label, buf);
    lv_obj_align_to(step_label, step_arc, LV_ALIGN_CENTER, 0, -9);
}

void watchface_set_time(int32_t hour, int32_t minute)
{
    if (!root_page) return;
    hour = (hour + 3) % 12;
    int hour_offset = hour * 5;
    hour_offset += minute / 10;
    if (hour_offset >= 60) {
        hour_offset = 60;
    }
    minute = (minute + 15) % 60;
    //LOG_PRINTK("Offset: %d\n", hour_offset);
    lv_meter_set_indicator_end_value(clock_meter, indic_min, minute);
    lv_meter_set_indicator_end_value(clock_meter, indic_hour, hour_offset);
}
