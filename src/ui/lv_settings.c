/**
 * @file lv_settings.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_settings.h"
#include "lvgl.h"
#include "logging/log.h"

/*********************
 *      DEFINES
 *********************/
#define LV_SETTINGS_ANIM_TIME   300 /*[ms]*/
#define LV_SETTINGS_MAX_WIDTH   250

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#endif



/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

static on_close_cb_t close_callback;

static lv_obj_t *_menu = NULL;


/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

static void close_button_pressed(lv_event_t *e)
{
    if (lv_menu_back_btn_is_root(_menu, lv_event_get_target(e))) {
        lv_obj_add_flag(_menu, LV_OBJ_FLAG_HIDDEN);
        lv_obj_remove_event_cb(_menu, close_button_pressed);
        close_callback();
    }
}

enum {
    LV_MENU_ITEM_BUILDER_VARIANT_1,
    LV_MENU_ITEM_BUILDER_VARIANT_2
};
typedef uint8_t lv_menu_builder_variant_t;

static lv_obj_t *create_text(lv_obj_t *parent, const char *icon, const char *txt,
                             lv_menu_builder_variant_t builder_variant);
static lv_obj_t *create_slider(lv_obj_t *parent,
                               const char *icon, const char *txt, int32_t min, int32_t max, int32_t val);
static lv_obj_t *create_switch(lv_obj_t *parent,
                               const char *icon, const char *txt, bool chk);

static void slider_event_cb(lv_event_t *e);

static lv_obj_t *create_text(lv_obj_t *parent, const char *icon, const char *txt,
                             lv_menu_builder_variant_t builder_variant)
{
    lv_obj_t *obj = lv_menu_cont_create(parent);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);


    lv_obj_t *img = NULL;
    lv_obj_t *label = NULL;

    if (icon) {
        img = lv_img_create(obj);
        lv_img_set_src(img, icon);
    }

    if (txt) {
        label = lv_label_create(obj);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);
    }

    if (builder_variant == LV_MENU_ITEM_BUILDER_VARIANT_2 && icon && txt) {
        lv_obj_add_flag(img, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
        lv_obj_swap(img, label);
    }

    return obj;
}

static lv_obj_t *create_switch(lv_obj_t *parent, const char *icon, const char *txt, bool chk)
{
    lv_obj_t *obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1);

    lv_obj_t *sw = lv_switch_create(obj);
    lv_obj_add_state(sw, chk ? LV_STATE_CHECKED : 0);

    return sw;
}

static lv_obj_t *create_slider(lv_obj_t *parent, const char *icon, const char *txt, int32_t min, int32_t max,
                               int32_t val)
{
    lv_obj_t *obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_2);

    lv_obj_t *slider = lv_slider_create(obj);
    lv_obj_set_flex_grow(slider, 1);
    lv_slider_set_range(slider, min, max);
    lv_slider_set_value(slider, val, LV_ANIM_OFF);
    lv_obj_add_flag(slider, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    if (icon == NULL) {
        lv_obj_add_flag(slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    }

    return slider;
}

static void slider_event_cb(lv_event_t *e)
{
    lv_settings_changed_cb_t callback;
    lv_setting_value_t settings_value;
    lv_event_code_t code = lv_event_get_code(e);

    settings_value.item.slider = lv_slider_get_value(lv_event_get_target(e));
    settings_value.type = LV_SETTINGS_TYPE_SLIDER;
    callback = (lv_settings_changed_cb_t)lv_event_get_user_data(e);

    if ((callback != NULL) && ((code == LV_EVENT_VALUE_CHANGED) || (code == LV_EVENT_RELEASED))) {
        callback(settings_value, code == LV_EVENT_RELEASED);
    }
}

static void switch_event_cb(lv_event_t *e)
{
    lv_settings_changed_cb_t callback;
    lv_setting_value_t settings_value;
    lv_event_code_t code = lv_event_get_code(e);
    bool val = lv_obj_has_state(lv_event_get_target(e), LV_STATE_CHECKED);

    settings_value.item.sw = val;
    settings_value.type = LV_SETTINGS_TYPE_SWITCH;
    callback = (lv_settings_changed_cb_t)lv_event_get_user_data(e);

    if ((callback != NULL) && ((code == LV_EVENT_VALUE_CHANGED) || (code == LV_EVENT_RELEASED))) {
        callback(settings_value, code == LV_EVENT_RELEASED);
    }
}

void lv_settings_create(lv_settings_page_t *pages, uint8_t num_pages, const char *title, lv_group_t *input_group,
                        on_close_cb_t close_cb)
{
    lv_obj_t *label;
    lv_obj_t *sub_page;
    lv_obj_t *cont;
    lv_settings_item_t *item;
    lv_obj_t *_mainPage;
    lv_obj_t *obj;

    if (_menu != NULL) {
        lv_obj_clear_flag(_menu, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_event_cb(_menu, close_button_pressed, LV_EVENT_CLICKED, _menu);
        return;
    }

    close_callback = close_cb;

    // Draw menu screen
    _menu = lv_menu_create(lv_scr_act());
    lv_menu_set_mode_root_back_btn(_menu, LV_MENU_ROOT_BACK_BTN_ENABLED);
    lv_obj_add_event_cb(_menu, close_button_pressed, LV_EVENT_CLICKED, _menu);
    lv_obj_set_size(_menu, 180, 180);
    lv_obj_center(_menu);

    // Main page
    _mainPage = lv_menu_page_create(_menu, NULL);

    for (int i = 0; i < num_pages; i++) {
        sub_page = lv_menu_page_create(_menu, "Settings");
        cont = lv_menu_cont_create(sub_page);
        lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
        for (int j = 0; j < pages[i].num_items; j++) {
            item = &pages[i].items[j];
            switch (item->type) {
                case LV_SETTINGS_TYPE_LABEL:
                    create_text(cont, item->icon, item->item.label.name, LV_MENU_ITEM_BUILDER_VARIANT_1);
                    break;
                case LV_SETTINGS_TYPE_SWITCH:
                    obj = create_switch(cont, item->icon, item->item.sw.name, item->item.sw.inital_val);
                    lv_obj_add_event_cb(obj, switch_event_cb, LV_EVENT_ALL, item->change_callback);
                    break;
                case LV_SETTINGS_TYPE_SLIDER:
                    obj = create_slider(cont, item->icon, item->item.slider.name, item->item.slider.min_val, item->item.slider.max_val,
                                        item->item.slider.inital_val);
                    lv_obj_add_event_cb(obj, slider_event_cb, LV_EVENT_ALL, item->change_callback);
                    break;
                default:
                    printf("Unsupported settings type %d\n", item->type);
            }
        }
        // Create a main page item
        cont = lv_menu_cont_create(_mainPage);
        label = lv_label_create(cont);
        lv_label_set_text(label, pages[i].name);
        lv_menu_set_load_page_event(_menu, cont, sub_page);
        lv_group_add_obj(input_group, cont);
        lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_add_flag(cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    }

    lv_menu_set_page(_menu, _mainPage);
    lv_group_focus_next(input_group);
}

/**
 * Automatically add the item to a group to allow navigation with keypad or encoder.
 * Should be called before `lv_settings_create`
 * The group can be change at any time.
 * @param g the group to use. `NULL` to not use this feature.
 */
void lv_settings_set_group(lv_group_t *g)
{
    //group = g;
    //lv_group_set_wrap(group, false);
}

/**
 * Create a new page ask `event_cb` to add the item with `LV_EVENT_REFRESH`
 * @param parent_item pointer to an item which open the the new page. Its `name` will be the title
 * @param event_cb event handler of the menu page
 */
void lv_settings_open_page(lv_settings_item_t *parent_item, lv_event_cb_t event_cb)
{
    /*Create a new page in the menu*/
    //create_page(parent_item, event_cb);

    /*Add the items*/
    //lv_event_send_func(event_cb, NULL, LV_EVENT_REFRESH, parent_item);
}