/**
 * @file lv_settings.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_settings.h"
#include "lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define LV_SETTINGS_ANIM_TIME   300 /*[ms]*/
#define LV_SETTINGS_MAX_WIDTH   250

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

static on_close_cb close_callback;

static lv_obj_t * _menu = NULL;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

static void close_button_pressed(lv_event_t* e)
{
    printk("Close settings\n");
    lv_obj_add_flag(_menu, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_event_cb(_menu, close_button_pressed);
    close_callback();
}

enum {
    LV_MENU_ITEM_BUILDER_VARIANT_1,
    LV_MENU_ITEM_BUILDER_VARIANT_2
};
typedef uint8_t lv_menu_builder_variant_t;

static lv_obj_t * create_text(lv_obj_t * parent, const char * icon, const char * txt,
                              lv_menu_builder_variant_t builder_variant);
static lv_obj_t * create_slider(lv_obj_t * parent,
                                const char * icon, const char * txt, int32_t min, int32_t max, int32_t val);
static lv_obj_t * create_switch(lv_obj_t * parent,
                                const char * icon, const char * txt, bool chk);

                                
static lv_obj_t * create_text(lv_obj_t * parent, const char * icon, const char * txt,
                              lv_menu_builder_variant_t builder_variant)
{
    lv_obj_t * obj = lv_menu_cont_create(parent);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICK_FOCUSABLE);
    

    lv_obj_t * img = NULL;
    lv_obj_t * label = NULL;

    if(icon) {
        img = lv_img_create(obj);
        lv_img_set_src(img, icon);
    }

    if(txt) {
        label = lv_label_create(obj);
        lv_label_set_text(label, txt);
        lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL_CIRCULAR);
        lv_obj_set_flex_grow(label, 1);
    }

    if(builder_variant == LV_MENU_ITEM_BUILDER_VARIANT_2 && icon && txt) {
        lv_obj_add_flag(img, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
        lv_obj_swap(img, label);
    }

    return obj;
}


static lv_obj_t * create_switch(lv_obj_t * parent, const char * icon, const char * txt, bool chk)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_1);

    lv_obj_t * sw = lv_switch_create(obj);
    lv_obj_add_state(sw, chk ? LV_STATE_CHECKED : 0);

    return obj;
}

static void slider_event_cb(lv_event_t * e);

static lv_obj_t * create_slider(lv_obj_t * parent, const char * icon, const char * txt, int32_t min, int32_t max,
                                int32_t val)
{
    lv_obj_t * obj = create_text(parent, icon, txt, LV_MENU_ITEM_BUILDER_VARIANT_2);

    lv_obj_t * slider = lv_slider_create(obj);
    lv_obj_set_flex_grow(slider, 1);
    lv_slider_set_range(slider, min, max);
    lv_slider_set_value(slider, val, LV_ANIM_OFF);
    lv_obj_add_flag(slider, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    if(icon == NULL) {
        lv_obj_add_flag(slider, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK);
    }

    return obj;
}

static void test(lv_obj_t * root_item, lv_group_t * group)
{
    if (_menu != NULL) {
        lv_obj_clear_flag(_menu, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_event_cb(_menu, close_button_pressed, LV_EVENT_CLICKED, _menu);
        return;
    }
    // // draw menu screen //
    lv_obj_t * label;
    lv_obj_t * cont;
    lv_obj_t * _mainPage;
    _menu = lv_menu_create(lv_scr_act());
    lv_menu_set_mode_root_back_btn(_menu, LV_MENU_ROOT_BACK_BTN_ENABLED);
    lv_obj_add_event_cb(_menu, close_button_pressed, LV_EVENT_CLICKED, _menu);
    lv_obj_set_size(_menu, 180, 180);
    lv_obj_center(_menu);
    
    lv_obj_t * sub_1_page = lv_menu_page_create(_menu, "General Settings");

    cont = lv_menu_cont_create(sub_1_page);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    create_slider(cont, LV_SYMBOL_SETTINGS, "Brightness", 0, 150, 120);
    create_switch(cont, LV_SYMBOL_MUTE, "Vibration", false);
    create_slider(cont, LV_SYMBOL_SETTINGS, "Update rate", 0, 150, 50);
    

    lv_obj_t * sub_2_page = lv_menu_page_create(_menu, "Page 2");

    cont = lv_menu_cont_create(sub_2_page);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Hello, I am hiding here on page 2");

    // Create a main page
    _mainPage = lv_menu_page_create(_menu, NULL);

    cont = lv_menu_cont_create(_mainPage);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Item 1");
    lv_menu_set_load_page_event(_menu, cont, sub_1_page);

    lv_group_add_obj(group, cont);
    //lv_obj_clear_flag(cont, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    cont = lv_menu_cont_create(_mainPage);
    label = lv_label_create(cont);
    lv_label_set_text(label, "Item 2");
    lv_menu_set_load_page_event(_menu, cont, sub_2_page);

    lv_group_add_obj(group, cont);
    lv_obj_add_flag(cont, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(cont, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

    //cont = create_slider(_mainPage, "Kd", 0, 150, 120);
    

    lv_menu_set_page(_menu, _mainPage);

    lv_group_focus_next(group);
}

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target(e);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d%%", (int)lv_slider_get_value(slider));
    //lv_label_set_text(slider_label, buf);
    //lv_obj_align_to(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}


/**
 * Create a settings application
 * @param root_item descriptor of the settings button. For example:
 * `lv_settings_menu_item_t root_item = {.name = "Settings", .event_cb = root_event_cb};`
 * @return the created settings button
 */
void lv_settings_create(lv_obj_t * root_item, lv_group_t * input_group, on_close_cb close_cb)
{
    close_callback = close_cb;
    test(root_item, input_group);
}

/**
 * Automatically add the item to a group to allow navigation with keypad or encoder.
 * Should be called before `lv_settings_create`
 * The group can be change at any time.
 * @param g the group to use. `NULL` to not use this feature.
 */
void lv_settings_set_group(lv_group_t * g)
{
    //group = g;
    //lv_group_set_wrap(group, false);
}

/**
 * Create a new page ask `event_cb` to add the item with `LV_EVENT_REFRESH`
 * @param parent_item pointer to an item which open the the new page. Its `name` will be the title
 * @param event_cb event handler of the menu page
 */
void lv_settings_open_page(lv_settings_item_t * parent_item, lv_event_cb_t event_cb)
{
    /*Create a new page in the menu*/
    //create_page(parent_item, event_cb);

    /*Add the items*/
    //lv_event_send_func(event_cb, NULL, LV_EVENT_REFRESH, parent_item);
}