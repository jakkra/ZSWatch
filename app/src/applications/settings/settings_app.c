#include <settings/settings_ui.h>
#include <application_manager.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <ble_aoa.h>
#include <display_control.h>
#include <accelerometer.h>
#include <ble_comm.h>
#include <zephyr/bluetooth/gap.h>
#include <zephyr/bluetooth/bluetooth.h>

static void settings_app_start(lv_obj_t *root, lv_group_t *group);
static void settings_app_stop(void);

static void on_close_settings(void);
static void on_brightness_changed(lv_setting_value_t value, bool final);
static void on_display_on_changed(lv_setting_value_t value, bool final);
static void on_aoa_enable_changed(lv_setting_value_t value, bool final);
static void on_pairing_enable_changed(lv_setting_value_t value, bool final);
static void on_reset_steps_changed(lv_setting_value_t value, bool final);
static void on_clear_bonded_changed(lv_setting_value_t value, bool final);

LV_IMG_DECLARE(settings);

static application_t app = {
    .name = "Settings",
    .icon = &settings,
    .start_func = settings_app_start,
    .stop_func = settings_app_stop
};


static lv_settings_item_t general_page_items[] = {
    {
        .type = LV_SETTINGS_TYPE_SLIDER,
        .icon = LV_SYMBOL_SETTINGS,
        .change_callback = on_brightness_changed,
        .item = {
            .slider = {
                .name = "Brightness",
                .inital_val = 3,
                .min_val = 1,
                .max_val = 10,
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = LV_SYMBOL_AUDIO,
        .item = {
            .sw = {
                .name = "Vibrate on click",
                .inital_val = true
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = LV_SYMBOL_TINT,
        .change_callback = on_display_on_changed,
        .item = {
            .sw = {
                .name = "Display always on",
                .inital_val = true
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = LV_SYMBOL_REFRESH,
        .change_callback = on_reset_steps_changed,
        .item = {
            .sw = {
                .name = "Reset step counter",
                .inital_val = false
            }
        }
    },
};

static lv_settings_item_t bluetooth_page_items[] = {
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = LV_SYMBOL_BLUETOOTH,
        .change_callback = on_pairing_enable_changed,
        .item = {
            .sw = {
                .name = "Pairable",
                .inital_val = false
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = LV_SYMBOL_BACKSPACE,
        .change_callback = on_clear_bonded_changed,
        .item = {
            .sw = {
                .name = "Delete all bonded peers",
                .inital_val = false
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SWITCH,
        .icon = "",
        .change_callback = on_aoa_enable_changed,
        .item = {
            .sw = {
                .name = "AoA",
                .inital_val = false
            }
        }
    },
    {
        .type = LV_SETTINGS_TYPE_SLIDER,
        .icon = LV_SYMBOL_SHUFFLE,
        .item = {
            .slider = {
                .name = "CTE Tx interval",
                .inital_val = 100,
                .min_val = 1,
                .max_val = 10 // Map to array index or something, having 8-5000ms will make slider very slow
            }
        }
    },
};

static lv_settings_page_t settings_menu[] = {
    {
        .name = "General",
        .num_items = ARRAY_SIZE(general_page_items),
        .items = general_page_items
    },
    {
        .name = "Bluetooth",
        .num_items = ARRAY_SIZE(bluetooth_page_items),
        .items = bluetooth_page_items
    },
};


static void settings_app_start(lv_obj_t *root, lv_group_t *group)
{
    printk("settings_app_start\n");
    lv_settings_create(settings_menu, ARRAY_SIZE(settings_menu), "N/A", group, on_close_settings);
}

static void settings_app_stop(void)
{
    printk("settings_app_stop\n");
    settings_ui_remove();
}

static void on_close_settings(void)
{
    printk("on_close_settings\n");
    application_manager_app_close_request(&app);
}

static void on_brightness_changed(lv_setting_value_t value, bool final)
{
    // Slider have values 0-10 hence multiply with 10 to get brightness in percent
    display_control_set_brightness(value.item.slider * 10);
}

static void on_display_on_changed(lv_setting_value_t value, bool final)
{

}

static void on_aoa_enable_changed(lv_setting_value_t value, bool final)
{
    if (value.item.sw) {
        bleAoaAdvertise(100, 100, 1);
    } else {
        bleAoaAdvertise(100, 100, 0);
    }
}

static void on_pairing_enable_changed(lv_setting_value_t value, bool final)
{
    if (value.item.sw) {
        ble_comm_set_pairable(true);
    } else {
        ble_comm_set_pairable(false);
    }
}

static void on_clear_bonded_changed(lv_setting_value_t value, bool final)
{
    if (final && value.item.sw) {
        int err = bt_unpair(BT_ID_DEFAULT, NULL);
        if (err) {
            printk("Cannot unpair for default ID");
            return;
        }
    }
}

static void on_reset_steps_changed(lv_setting_value_t value, bool final)
{
    if (final && value.item.sw) {
        //watchface_set_step(0);
        accelerometer_reset_step_count();
    }
}

static int settings_app_add(void)
{
    application_manager_add_application(&app);

    return 0;
}

SYS_INIT(settings_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
