#include <qr_code/qr_code_ui.h>
#include <application_manager.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <display_control.h>

// Functions needed for all applications
static void qr_code_app_start(lv_obj_t *root, lv_group_t *group);
static void qr_code_app_stop(void);

LV_IMG_DECLARE(qr_code_icon);

static application_t app = {
    .name = "QR Code",
    .icon = &qr_code_icon,
    .start_func = qr_code_app_start,
    .stop_func = qr_code_app_stop
};

static uint8_t original_brightness;

static void qr_code_app_start(lv_obj_t *root, lv_group_t *group)
{
    original_brightness = display_control_get_brightness();
    display_control_set_brightness(100);
    qr_code_ui_show(root);
}

static void qr_code_app_stop(void)
{
    display_control_set_brightness(original_brightness);
    qr_code_ui_remove();
}

static int qr_code_app_add(void)
{
    application_manager_add_application(&app);

    return 0;
}

SYS_INIT(qr_code_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
