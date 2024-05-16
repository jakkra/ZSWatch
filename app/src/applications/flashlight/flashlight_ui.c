#include "flashlight_ui.h"
#include "ui/zsw_ui.h"
#include "ui/utils/zsw_ui_utils.h"

ZSW_LV_IMG_DECLARE(face_goog_20_61728_0);
ZSW_LV_IMG_DECLARE(face_goog_20_61728_1);
ZSW_LV_IMG_DECLARE(face_goog_20_61728_2);
ZSW_LV_IMG_DECLARE(face_goog_20_61728_3);
ZSW_LV_IMG_DECLARE(face_goog_20_61728_4);
ZSW_LV_IMG_DECLARE(face_goog_20_61728_5);
ZSW_LV_IMG_DECLARE(face_goog_20_61728_6);

static const void *face_goog_battery[] = {
    ZSW_LV_IMG_USE(face_goog_20_61728_0),
    ZSW_LV_IMG_USE(face_goog_20_61728_1),
    ZSW_LV_IMG_USE(face_goog_20_61728_2),
    ZSW_LV_IMG_USE(face_goog_20_61728_3),
    ZSW_LV_IMG_USE(face_goog_20_61728_4),
    ZSW_LV_IMG_USE(face_goog_20_61728_5),
    ZSW_LV_IMG_USE(face_goog_20_61728_6),
};

static lv_obj_t *root_page = NULL;
static bool on;

static lv_obj_t *face_goog_41_130994;

static uint8_t icon = 0;

static void on_click(lv_event_t *e)
{
    on = !on;
    if (on) {
        lv_obj_set_style_bg_color(root_page, lv_color_black(), LV_PART_MAIN);
    } else {
        lv_obj_set_style_bg_color(root_page, lv_color_black(), LV_PART_MAIN);
    }

    lv_img_set_src(face_goog_41_130994, face_goog_battery[icon % 7]);

    icon = (icon + 1) % 7;
}

void flashlight_ui_show(lv_obj_t *root)
{
    assert(root_page == NULL);

    root_page = lv_obj_create(root);
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(root_page, LV_PCT(100), LV_PCT(100));

    lv_obj_set_width(root_page, lv_pct(100));
    lv_obj_set_height(root_page, lv_pct(100));
    lv_obj_set_align(root_page, LV_ALIGN_CENTER);
    //lv_obj_clear_flag(root_page, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(root_page, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(root_page, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(root_page, on_click, LV_EVENT_CLICKED, NULL);

    face_goog_41_130994 = lv_img_create(root_page);
    lv_img_set_src(face_goog_41_130994, ZSW_LV_IMG_USE(face_goog_20_61728_0));
    lv_obj_set_width(face_goog_41_130994, LV_SIZE_CONTENT);
    lv_obj_set_height(face_goog_41_130994, LV_SIZE_CONTENT);
    lv_obj_set_x(face_goog_41_130994, 50);
    lv_obj_set_y(face_goog_41_130994, 146);
    lv_obj_add_flag(face_goog_41_130994, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_goog_41_130994, LV_OBJ_FLAG_SCROLLABLE);

    on = true;
}

void flashlight_ui_remove(void)
{
    lv_obj_del(root_page);
    root_page = NULL;
}