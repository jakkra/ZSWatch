#include <notification/notification_ui.h>
#include <application_manager.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <notification_manager.h>

// Functions needed for all applications
static void notification_app_start(lv_obj_t *root, lv_group_t *group);
static void notification_app_stop(void);

static application_t app = {
    .name = "Notification",
    .hidden = true,
    .start_func = notification_app_start,
    .stop_func = notification_app_stop
};

static void on_notification_page_notification_close(uint32_t not_id)
{
    // TODO send to phone that the notification was read.
    notification_manager_remove(not_id);
}


static void notification_app_start(lv_obj_t *root, lv_group_t *group)
{
    int num_unread;
    not_mngr_notification_t notifications[NOTIFICATION_MANAGER_MAX_STORED];

    notification_manager_get_all(notifications, &num_unread);
    notifications_page_init(on_notification_page_notification_close);
    notifications_page_create(notifications, num_unread, group);
}

static void notification_app_stop(void)
{
    notifications_page_close();
}

static int notification_app_add(void)
{
    application_manager_add_application(&app);

    return 0;
}

SYS_INIT(notification_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
