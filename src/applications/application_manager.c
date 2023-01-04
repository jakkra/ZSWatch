#include <applications/application_manager.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(APP_MANAGER, LOG_LEVEL_DBG);

#define MAX_APPS     3

static application_t* apps[MAX_APPS];
static uint8_t num_apps;
static uint8_t current_app;
static lv_obj_t* root_obj;
static lv_group_t* group_obj;
static on_application_manager_cb_fn close_cb_func;

void application_manager_show(on_application_manager_cb_fn close_cb, lv_obj_t* root, lv_group_t* group)
{
    close_cb_func = close_cb;
    root_obj = root;
    group_obj = group;

    for (int i = 0; i < num_apps; i++) {
        LOG_DBG("Apps[%d]: %s", i, apps[i]->name);
    }
    apps[current_app]->start_func(root_obj, group_obj);
}

void application_manager_delete(void)
{
    if (current_app < num_apps) {
        LOG_DBG("Stop force %d", current_app);
        apps[current_app]->stop_func();
    }
}

void application_manager_add_application(application_t* app)
{
    __ASSERT_NO_MSG(num_apps < MAX_APPS);
    apps[num_apps] = app;
    num_apps++;
}

void async_start(lv_timer_t * timer)
{
    LOG_DBG("Start %d", current_app);
    apps[current_app]->start_func(root_obj, group_obj);
}


void application_manager_exit_app(void)
{
    LOG_DBG("Stop %d", current_app);
    apps[current_app]->stop_func();
    current_app++;
    if (current_app >= num_apps) {
        close_cb_func();
        current_app = 0;
    } else {
        // This function may be called within a lvgl callback such
        // as a button click. If we create a new ui in this callback
        // which registers a button press callback then that callback
        // may get called, but we don't want that. So delay the opening
        // of the new application some time.
        lv_timer_t * timer = lv_timer_create(async_start, 100,  NULL);
        lv_timer_set_repeat_count(timer, 1);
    }
}

void application_manager_app_close_request(application_t* app)
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
