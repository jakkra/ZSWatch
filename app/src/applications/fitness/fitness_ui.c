#include "fitness_ui.h"
#include "ui/zsw_ui.h"
#include <lvgl.h>

static lv_obj_t *root_page = NULL;
static lv_obj_t *ui_step_progress_label = NULL;
static lv_obj_t *ui_weekly_chart = NULL;
static lv_obj_t *ui_step_goal_arc = NULL;
static lv_chart_series_t *ui_weekly_chart_series_1 = NULL;

static void event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *chart = lv_event_get_target(e);

    if (code == LV_EVENT_VALUE_CHANGED) {
        lv_obj_invalidate(chart);
    } else if (code == LV_EVENT_DRAW_POST_END) {
        lv_chart_series_t *ser = lv_chart_get_series_next(chart, NULL);
        if (!ser) {
            return;
        }
        int num_points = lv_chart_get_point_count(chart);

        static char *weekdays[] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"}; // TODO correct order ha to come from fitness_app.c
        for (int id = 0; id < num_points; id++) {
            lv_point_t p;
            lv_chart_get_point_pos_by_id(chart, ser, id, &p);

            char buf[16];
            lv_snprintf(buf, sizeof(buf), LV_SYMBOL_DUMMY"%s", weekdays[id]);

            lv_draw_rect_dsc_t draw_rect_dsc;
            lv_draw_rect_dsc_init(&draw_rect_dsc);
            draw_rect_dsc.bg_color = lv_color_black();
            draw_rect_dsc.bg_opa = LV_OPA_50;
            draw_rect_dsc.radius = 3;
            draw_rect_dsc.bg_img_src = buf;
            draw_rect_dsc.bg_img_recolor = lv_color_white();

            lv_area_t a;
            a.x1 = chart->coords.x1 + p.x - 20;
            a.x2 = chart->coords.x1 + p.x + 20;
            a.y1 = chart->coords.y1 + 20 - 30;
            a.y2 = chart->coords.y1 + 20 - 10;

            lv_draw_ctx_t *draw_ctx = lv_event_get_draw_ctx(e);
            lv_draw_rect(draw_ctx, &draw_rect_dsc, &a);
        }

        static int32_t id = LV_CHART_POINT_NONE;
        if (lv_chart_get_pressed_point(chart) != LV_CHART_POINT_NONE) {
            id = lv_chart_get_pressed_point(chart);
        }
        if (id != LV_CHART_POINT_NONE) {
            // Draw a rectangle with the value of the point
            // Keep point value drawn until another bar is clicked.
            lv_point_t p;
            lv_chart_get_point_pos_by_id(chart, ser, id, &p);

            lv_coord_t *y_array = lv_chart_get_y_array(chart, ser);
            lv_coord_t value = y_array[id];

            char buf[16];
            lv_snprintf(buf, sizeof(buf), LV_SYMBOL_DUMMY"%d", value);

            lv_draw_rect_dsc_t draw_rect_dsc;
            lv_draw_rect_dsc_init(&draw_rect_dsc);
            draw_rect_dsc.bg_color = lv_color_white();
            draw_rect_dsc.bg_opa = LV_OPA_30;
            draw_rect_dsc.radius = 5;
            draw_rect_dsc.bg_img_src = buf;
            draw_rect_dsc.bg_img_recolor = lv_color_black();

            lv_area_t a;
            a.x1 = chart->coords.x1 + p.x - 20;
            a.x2 = chart->coords.x1 + p.x + 20;
            a.y1 = chart->coords.y1 + p.y - 30;
            a.y2 = chart->coords.y1 + p.y - 10;

            lv_draw_ctx_t *draw_ctx = lv_event_get_draw_ctx(e);
            lv_draw_rect(draw_ctx, &draw_rect_dsc, &a);
        }
    }
}

static void create_step_chart(lv_obj_t *ui_root_container, uint16_t max_samples)
{
    ui_step_progress_label = lv_label_create(ui_root_container);
    lv_obj_set_width(ui_step_progress_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_step_progress_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_step_progress_label, 0);
    lv_obj_set_y(ui_step_progress_label, -90);
    lv_obj_set_align(ui_step_progress_label, LV_ALIGN_CENTER);
    lv_label_set_text(ui_step_progress_label, "- / 10000");

    ui_weekly_chart = lv_chart_create(ui_root_container);
    lv_obj_set_width(ui_weekly_chart, 231);
    lv_obj_set_height(ui_weekly_chart, 120);
    lv_obj_set_x(ui_weekly_chart, 0);
    lv_obj_set_y(ui_weekly_chart, 10);
    lv_obj_set_align(ui_weekly_chart, LV_ALIGN_CENTER);
    lv_chart_set_type(ui_weekly_chart, LV_CHART_TYPE_BAR);
    lv_chart_set_point_count(ui_weekly_chart, 7);
    lv_chart_set_range(ui_weekly_chart, LV_CHART_AXIS_PRIMARY_Y, 0, 10000);
    lv_chart_set_range(ui_weekly_chart, LV_CHART_AXIS_SECONDARY_Y, 0, 0);
    lv_chart_set_div_line_count(ui_weekly_chart, 0, 0);
    lv_chart_set_axis_tick(ui_weekly_chart, LV_CHART_AXIS_PRIMARY_X, 1, 1, 1, 1, false, 50);
    lv_chart_set_axis_tick(ui_weekly_chart, LV_CHART_AXIS_PRIMARY_Y, 1, 1, 1, 1, false, 50);
    lv_chart_set_axis_tick(ui_weekly_chart, LV_CHART_AXIS_SECONDARY_Y, 1, 1, 1, 1, false, 25);
    ui_weekly_chart_series_1 = lv_chart_add_series(ui_weekly_chart, lv_color_hex(0x9E3939),
                                                   LV_CHART_AXIS_PRIMARY_Y);

    lv_obj_set_style_bg_color(ui_weekly_chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_weekly_chart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_weekly_chart, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_weekly_chart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_weekly_chart, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_step_goal_arc = lv_arc_create(ui_root_container);
    lv_obj_set_width(ui_step_goal_arc, lv_pct(100));
    lv_obj_set_height(ui_step_goal_arc, lv_pct(100));
    lv_obj_set_align(ui_step_goal_arc, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_step_goal_arc, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK |
                      LV_OBJ_FLAG_CLICK_FOCUSABLE);      /// Flags
    lv_arc_set_range(ui_step_goal_arc, 0, 10000);
    lv_arc_set_value(ui_step_goal_arc, 2000);
    lv_arc_set_bg_angles(ui_step_goal_arc, 0, 359);
    lv_arc_set_rotation(ui_step_goal_arc, 270);
    lv_obj_set_style_pad_left(ui_step_goal_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_step_goal_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_step_goal_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_step_goal_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_step_goal_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_step_goal_arc, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_step_goal_arc, lv_color_hex(0x5F6571), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_step_goal_arc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_step_goal_arc, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(ui_step_goal_arc, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_step_goal_arc, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_step_goal_arc, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_step_goal_arc, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_step_goal_arc, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_step_goal_arc, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_step_goal_arc, lv_color_hex(0x00921A), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_step_goal_arc, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_step_goal_arc, 4, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_step_goal_arc, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_step_goal_arc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_t *ui_last_7_days_title_label = lv_label_create(ui_root_container);
    lv_obj_set_width(ui_last_7_days_title_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_last_7_days_title_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_last_7_days_title_label, 0);
    lv_obj_set_y(ui_last_7_days_title_label, -20);
    lv_obj_set_align(ui_last_7_days_title_label, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_last_7_days_title_label, "Last 7 days");

    lv_obj_add_event_cb(ui_weekly_chart, event_cb, LV_EVENT_ALL, NULL);
}

void fitness_ui_show(lv_obj_t *root, uint16_t max_samples)
{
    assert(root_page == NULL);

    root_page = lv_obj_create(root);
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(root_page, LV_PCT(100), LV_PCT(100));

    lv_obj_set_width(root_page, lv_pct(100));
    lv_obj_set_height(root_page, lv_pct(100));
    lv_obj_set_align(root_page, LV_ALIGN_CENTER);
    lv_obj_set_style_pad_all(root_page, 0, LV_PART_MAIN);

    create_step_chart(root_page, max_samples);
}

void fitness_ui_set_weekly_steps(uint16_t *samples, uint16_t num_samples)
{
    assert(ui_weekly_chart_series_1 != NULL);

    for (int i = 0; i < num_samples; i++) {
        lv_chart_set_next_value(ui_weekly_chart, ui_weekly_chart_series_1, samples[i]);
    }
    lv_label_set_text_fmt(ui_step_progress_label, "%d / %d", samples[num_samples - 1], 10000);
    lv_arc_set_value(ui_step_goal_arc, samples[num_samples - 1]);
}

void fitness_ui_remove(void)
{
    lv_obj_del(root_page);
    root_page = NULL;
}