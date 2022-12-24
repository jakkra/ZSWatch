#include <notifications_page.h>
#include <lvgl.h>

static void close_button_pressed(lv_event_t * e);

static on_notification_page_closed_cb_t closed_callback;
static on_notification_remove_cb_t not_removed_callback;

static lv_obj_t * menu;

void notifications_page_init(on_notification_page_closed_cb_t closed_cb, on_notification_remove_cb_t not_removed_cb)
{
    closed_callback = closed_cb;
    not_removed_callback = not_removed_cb;
}

void notifications_page_create(not_mngr_notification_t* notifications, uint8_t num_notifications, lv_group_t *input_group)
{
    lv_obj_t *label;
    lv_obj_t *cont;
    lv_obj_t *main_page;
    lv_obj_t *obj;
    static lv_style_t outline_primary;

    // Border around selected menu row when focused
    lv_style_init(&outline_primary);
    lv_style_set_border_color(&outline_primary, lv_color_hex(0x001833));
    lv_style_set_border_width(&outline_primary, lv_disp_dpx(lv_disp_get_next(NULL), 3));
    lv_style_set_border_opa(&outline_primary, LV_OPA_50);
    lv_style_set_border_side(&outline_primary, LV_BORDER_SIDE_BOTTOM);

    menu = lv_menu_create(lv_scr_act());
    lv_menu_set_mode_root_back_btn(menu, LV_MENU_ROOT_BACK_BTN_ENABLED);
    lv_obj_add_event_cb(menu, close_button_pressed, LV_EVENT_CLICKED, menu);
    lv_obj_set_size(menu, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));
    lv_obj_center(menu);

    main_page = lv_menu_page_create(menu, NULL);

    for (int i = 0; i < num_notifications; i++) {
        cont = lv_menu_cont_create(main_page);
        lv_obj_add_style(cont, &outline_primary, LV_STATE_FOCUS_KEY);
        label = lv_label_create(cont);
        lv_label_set_text(label, notifications[i].title);
        lv_group_add_obj(input_group, cont);
    }

    lv_menu_set_page(menu, main_page);
    lv_group_focus_next(input_group);
}

void notifications_page_close(void)
{
    lv_obj_del(menu);
}

static void close_button_pressed(lv_event_t * e)
{
    lv_obj_del(menu);
    closed_callback();
}