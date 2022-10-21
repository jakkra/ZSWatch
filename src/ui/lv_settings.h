/**
 * @file lv_settings.h
 *
 */

#ifndef LV_SETTINGS_H
#define LV_SETTINGS_H

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

typedef enum {
    LV_SETTINGS_TYPE_LIST_BTN,
    LV_SETTINGS_TYPE_BTN,
    LV_SETTINGS_TYPE_SW,
    LV_SETTINGS_TYPE_DDLIST,
    LV_SETTINGS_TYPE_NUMSET,
    LV_SETTINGS_TYPE_SLIDER,

    LV_SETTINGS_TYPE_INV = 0xff,
}lv_settings_type_t;

typedef struct lv_settings_item{
    lv_settings_type_t type;
    char * name;          /*Name or title of the item*/
    char * value;         /*The current value as string*/
    int32_t state;        /*The current state, e.g. slider's value, switch state as a number */
    lv_obj_t * cont;
    void * data;
}lv_settings_item_t;

typedef struct slider_config{
    uint16_t min_step;
    uint16_t max_step;
} slider_config_t;

typedef void(*on_close_cb)(void);


/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**
 * Create a settings application
 * @param root_item descriptor of the settings button. For example:
 * `lv_settings_menu_item_t root_item = {.name = "Settings", .event_cb = root_event_cb};`
 * @return the created settings button
 */
void lv_settings_create(lv_obj_t * root_item, lv_group_t * input_group, on_close_cb close_cb);

/**
 * Automatically add the item to a group to allow navigation with keypad or encoder.
 * Should be called before `lv_settings_create`
 * The group can be change at any time.
 * @param g the group to use. `NULL` to not use this feature.
 */
void lv_settings_set_group(lv_group_t * g);

#endif /*LV_SETTINGS_H*/