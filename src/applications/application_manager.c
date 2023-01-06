#include <applications/application_manager.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(APP_MANAGER, LOG_LEVEL_DBG);

#define MAX_APPS     10

static application_t *apps[MAX_APPS];
static uint8_t num_apps;
static uint8_t current_app;
static lv_obj_t *root_obj;
static lv_group_t *group_obj;
static on_application_manager_cb_fn close_cb_func;
static lv_obj_t *grid;

static void delete_application_picker(void)
{
    if (grid != NULL) {
        lv_obj_del(grid);
        grid = NULL;
    }
}

static void async_start(lv_timer_t *timer)
{
    LOG_DBG("Start %d", current_app);
    apps[current_app]->start_func(root_obj, group_obj);
}

static void app_clicked(lv_event_t *e)
{
    int app_id = (int)lv_event_get_user_data(e);
    delete_application_picker();
    current_app = app_id;
    // This function may be called within a lvgl callback such
    // as a button click. If we create a new ui in this callback
    // which registers a button press callback then that callback
    // may get called, but we don't want that. So delay the opening
    // of the new application some time.
    lv_timer_t *timer = lv_timer_create(async_start, 250,  NULL);
    lv_timer_set_repeat_count(timer, 1);
}

static void close_button_pressed(lv_event_t *e)
{
    close_cb_func();
}

static void draw_application_picker(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_flex_flow(&style, LV_FLEX_FLOW_ROW_WRAP);
    lv_style_set_flex_main_place(&style, LV_FLEX_ALIGN_SPACE_EVENLY);
    lv_style_set_layout(&style, LV_LAYOUT_FLEX);

    lv_obj_set_scrollbar_mode(lv_scr_act(), LV_SCROLLBAR_MODE_OFF);

    assert(grid == NULL);
    grid = lv_obj_create(root_obj);
    lv_obj_add_style(grid, &style, 0);
    lv_obj_set_scrollbar_mode(root_obj, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scrollbar_mode(grid, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_side(grid, LV_BORDER_SIDE_NONE, 0);
    lv_obj_set_style_pad_top(grid, 30, LV_PART_MAIN);

    lv_obj_set_size(grid, LV_PCT(100), LV_PCT(100));
    lv_obj_center(grid);
    lv_obj_set_flex_flow(grid, LV_FLEX_FLOW_ROW_WRAP);

    for (int i = 0; i < num_apps; i++) {
        LOG_DBG("Apps[%d]: %s", i, apps[i]->name);
        lv_obj_t *cont = lv_obj_create(grid);
        lv_obj_center(cont);
        lv_obj_set_size(cont, 70, 70);
        lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_NONE, 0);
        lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

        lv_obj_t *button = lv_btn_create(cont);
        lv_obj_set_size(button, 65, 65);
        lv_obj_set_scrollbar_mode(button, LV_SCROLLBAR_MODE_OFF);
        lv_obj_add_event_cb(button, app_clicked, LV_EVENT_PRESSED, (void *)i);
        lv_obj_center(button);

        lv_obj_t *icon = lv_img_create(button);
        lv_img_set_src(icon, apps[i]->icon);
        lv_obj_center(icon);
        lv_obj_align(icon, LV_ALIGN_TOP_MID, 0, 0);
        lv_obj_set_scrollbar_mode(icon, LV_SCROLLBAR_MODE_OFF);

        lv_obj_t *label = lv_label_create(button);
        lv_label_set_text_fmt(label, "%s", apps[i]->name);
        lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, 0);
        lv_obj_set_style_text_color(label, lv_color_black(), LV_PART_MAIN);
        lv_obj_set_scrollbar_mode(label, LV_SCROLLBAR_MODE_OFF);

    }

    lv_obj_t *float_btn = lv_btn_create(grid);
    lv_obj_set_size(float_btn, 50, 50);
    lv_obj_add_flag(float_btn, LV_OBJ_FLAG_FLOATING);
    lv_obj_align(float_btn, LV_ALIGN_BOTTOM_RIGHT, 0, -lv_obj_get_style_pad_right(grid, LV_PART_MAIN));
    lv_obj_add_event_cb(float_btn, close_button_pressed, LV_EVENT_PRESSED, grid);
    lv_obj_set_style_radius(float_btn, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_bg_img_src(float_btn, LV_SYMBOL_CLOSE, 0);
    lv_obj_set_style_text_font(float_btn, lv_theme_get_font_large(float_btn), 0);
}

void application_manager_show(on_application_manager_cb_fn close_cb, lv_obj_t *root, lv_group_t *group)
{
    close_cb_func = close_cb;
    root_obj = root;
    group_obj = group;
    draw_application_picker();
}

void application_manager_delete(void)
{
    if (current_app < num_apps) {
        LOG_DBG("Stop force %d", current_app);
        apps[current_app]->stop_func();
    }
    delete_application_picker();
}

void application_manager_add_application(application_t *app)
{
    __ASSERT_NO_MSG(num_apps < MAX_APPS);
    apps[num_apps] = app;
    num_apps++;
}

void application_manager_exit_app(void)
{
    LOG_DBG("Stop %d", current_app);
    apps[current_app]->stop_func();

    draw_application_picker();
}

void application_manager_app_close_request(application_t *app)
{
    LOG_DBG("application_manager_app_close_request");
    application_manager_exit_app();
}

static int application_manager_init(const struct device *arg)
{
    memset(apps, 0, sizeof(apps));
    num_apps = 0;
    current_app = 0;

    return 0;
}

SYS_INIT(application_manager_init, POST_KERNEL, CONFIG_APPLICATION_INIT_PRIORITY);
