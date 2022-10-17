#include <stats_page.h>
#include <lvgl.h>

static lv_obj_t * root_page;

static lv_obj_t * bar_acc_x;
static lv_obj_t * bar_acc_y;
static lv_obj_t * bar_acc_z;

static lv_obj_t * acc_x_label;
static lv_obj_t * acc_y_label;
static lv_obj_t * acc_z_label;


void stats_page_init(void)
{
    lv_obj_clean(lv_scr_act());
}

void states_page_show(void)
{
    static lv_style_t style_indic_red;
    static lv_style_t style_indic_green;
    static lv_style_t style_indic_blue;
    
    root_page = lv_obj_create(lv_scr_act());
    lv_obj_set_scrollbar_mode(root_page, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(root_page, LV_OPA_TRANSP, LV_PART_MAIN);
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(root_page, 240, 240);
    lv_obj_center(root_page);
    lv_style_init(&style_indic_red);
    lv_style_init(&style_indic_green);
    lv_style_init(&style_indic_blue);
    
    bar_acc_x = lv_bar_create(root_page);
    lv_style_set_bg_color(&style_indic_red, lv_palette_main(LV_PALETTE_RED));
    lv_obj_add_style(bar_acc_x, &style_indic_red, LV_PART_INDICATOR);
    lv_bar_set_range(bar_acc_x, -20000, 20000);
    lv_obj_set_size(bar_acc_x, 200, 8);
    lv_obj_align(bar_acc_x, LV_ALIGN_CENTER, 0, -40);

    acc_x_label = lv_label_create(root_page);
    lv_label_set_text(acc_x_label, "00000");
    lv_obj_align_to(acc_x_label, bar_acc_x, LV_ALIGN_CENTER, 0, -15);

    bar_acc_y = lv_bar_create(root_page);
    lv_style_set_bg_color(&style_indic_green, lv_palette_main(LV_PALETTE_LIGHT_GREEN));
    lv_obj_add_style(bar_acc_y, &style_indic_green, LV_PART_INDICATOR);
    lv_bar_set_range(bar_acc_y, -20000, 20000);
    lv_obj_set_size(bar_acc_y, 200, 8);
    lv_obj_align(bar_acc_y, LV_ALIGN_CENTER, 0, 0);
    acc_y_label = lv_label_create(root_page);
    lv_label_set_text(acc_y_label, "00000");
    lv_obj_align_to(acc_y_label, bar_acc_y, LV_ALIGN_CENTER, 0, -15);

    bar_acc_z = lv_bar_create(root_page);
    lv_style_set_bg_color(&style_indic_blue, lv_palette_main(LV_PALETTE_LIGHT_BLUE));
    lv_obj_add_style(bar_acc_z, &style_indic_blue, LV_PART_INDICATOR);
    lv_bar_set_range(bar_acc_z, -20000, 20000);
    lv_obj_set_size(bar_acc_z, 200, 8);
    lv_obj_align(bar_acc_z, LV_ALIGN_CENTER, 0, 40);
    acc_z_label = lv_label_create(root_page);
    lv_label_set_text(acc_z_label, "00000");
    lv_obj_align_to(acc_z_label, bar_acc_z, LV_ALIGN_CENTER, 0, -15);

    general_ui_anim_in(root_page, 100);
}

void states_page_remove(void)
{
    root_page = NULL;
    general_ui_anim_out_all(lv_scr_act(), 0);
    //if (!root_page) return;
    //lv_obj_del(root_page);
}

void states_page_accelerometer_values(int32_t x, int32_t y, int32_t z)
{
    char buf[10];
    memset(buf, 0, sizeof(buf));

    if (!root_page) return;
    lv_bar_set_value(bar_acc_x, x, LV_ANIM_ON);
    lv_bar_set_value(bar_acc_y, y, LV_ANIM_ON);
    lv_bar_set_value(bar_acc_z, z, LV_ANIM_ON);

    snprintf(buf, sizeof(buf), "X: %d", x);
    lv_label_set_text(acc_x_label, buf);
    snprintf(buf, sizeof(buf), "Y: %d", y);
    lv_label_set_text(acc_y_label, buf);
    snprintf(buf, sizeof(buf), "Z: %d", z);
    lv_label_set_text(acc_z_label, buf);
}
