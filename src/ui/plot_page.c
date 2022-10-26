#include <plot_page.h>
#include <general_ui.h>
#include <lvgl.h>

static lv_obj_t * root_page = NULL;

static lv_obj_t * chart1;
static lv_chart_series_t * ser1;
static lv_chart_series_t * ser2;

void plot_page_init(void)
{
    lv_obj_clean(lv_scr_act());
}

void plot_page_show(void)
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
    lv_obj_center(root_page);
    
    /*Create a chart1*/
    chart1 = lv_chart_create(root_page);
    lv_obj_set_size(chart1, 240, 240);
    lv_obj_center(chart1);
    lv_chart_set_type(chart1, LV_CHART_TYPE_LINE);   /*Show lines and points too*/
    lv_obj_set_style_size(chart1, 0, LV_PART_INDICATOR);

    //lv_chart_set_div_line_count(chart1, 5, 7);
    lv_chart_set_point_count(chart1, 20);
    /*Add two data series*/
    ser1 = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    ser2 = lv_chart_add_series(chart1, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_SECONDARY_Y);
    lv_chart_set_range(chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 20000);
    lv_chart_set_range(chart1, LV_CHART_AXIS_SECONDARY_Y, 0, 20000);

    lv_chart_set_update_mode(chart1, LV_CHART_UPDATE_MODE_CIRCULAR);


    general_ui_anim_in(root_page, 100);
}

void plot_page_remove(void)
{
    lv_obj_add_flag(root_page, LV_OBJ_FLAG_HIDDEN);
}

void plot_page_led_values(int32_t red, int32_t green, int32_t ir)
{
    if (lv_obj_has_flag(root_page, LV_OBJ_FLAG_HIDDEN)) {
        return;
    }
    lv_chart_set_next_value(chart1, ser1, red);
    lv_chart_set_next_value(chart1, ser2, green);
}
