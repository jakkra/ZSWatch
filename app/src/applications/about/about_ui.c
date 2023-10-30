#include "about_ui.h"
#include "app_version.h"

static lv_obj_t *root_page = NULL;

void about_ui_show(lv_obj_t *root)
{
    assert(root_page == NULL);

    root_page = lv_obj_create(root);
    lv_obj_set_style_border_width(root_page, 0, LV_PART_MAIN);
    lv_obj_set_size(root_page, LV_PCT(100), LV_PCT(100));
    lv_obj_set_scrollbar_mode(root_page, LV_SCROLLBAR_MODE_OFF);
}

void about_ui_remove(void)
{
    lv_obj_del(root_page);
    root_page = NULL;
}