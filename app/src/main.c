#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <zephyr/sys/reboot.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <buttons.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/settings/settings.h>
#include <zephyr/drivers/led.h>
#include <zephyr/logging/log.h>
#include <zsw_clock.h>
#include <lvgl.h>
#include <sys/time.h>
#include <ram_retention_storage.h>
#include <zsw_vibration_motor.h>
#include <display_control.h>
#include <zephyr/zbus/zbus.h>
#include <zsw_cpu_freq.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/task_wdt/task_wdt.h>
#include <zephyr/arch/cpu.h>
#include <zephyr/logging/log_ctrl.h>
#include <zephyr/fatal.h>
#include <zephyr/input/input.h>

#include "dfu.h"
#include "ui/zsw_ui.h"
#include "ble/ble_comm.h"
#include "ble/ble_aoa.h"
#include "battery/battery.h"
#include "battery/zsw_charger.h"
#include "events/accel_event.h"
#include "events/ble_data_event.h"
#include "sensors/zsw_imu.h"
#include "sensors/zsw_magnetometer.h"
#include "sensors/zsw_pressure_sensor.h"
#include "manager/zsw_power_manager.h"
#include "manager/application_manager.h"
#include "manager/notification_manager.h"
#include "applications/watchface/watchface_app.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_WRN);

#define TASK_WDT_FEED_INTERVAL_MS  3000

typedef enum ui_state {
    INIT_STATE,
    WATCHFACE_STATE,
    APPLICATION_MANAGER_STATE,
} ui_state_t;

static struct input_worker_item_t {
    struct k_work work;
    struct input_event data;
} input_worker_item;

static void run_input_work(struct k_work *item);
static void run_init_work(struct k_work *item);

static void run_wdt_work(struct k_work *item);
static void enable_bluetoth(void);
static bool load_retention_ram(void);
static void enocoder_read(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data);
static void click_feedback(struct _lv_indev_drv_t *drv, uint8_t e);
static void open_notification_popup(void *data);
static void async_turn_off_buttons_allocation(void *unused);
static void open_application_manager_page(void *app_name);

static void on_ApplicationManager_Close(void);
static void on_PopupNotifcation_Closed(uint32_t id);
static void on_BLEDAta_Callback(ble_comm_cb_data_t *cb);
static void on_zbusBLECommData_Callback(const struct zbus_channel *chan);
static void on_InputSyubsys_Callback(struct input_event *evt);
static void on_ScreenGestureEvent_Callback(lv_event_t *e);
static void on_WatchfaceAppEvent_Callback(watchface_app_evt_t evt);

static int kernal_wdt_id;

static bool buttons_allocated = false;
static lv_group_t *input_group;
static lv_group_t *temp_group;

static lv_indev_drv_t enc_drv;
static lv_indev_t *enc_indev;
static buttonId_t last_pressed;

static bool pending_not_open;

static ui_state_t watch_state = INIT_STATE;

K_WORK_DELAYABLE_DEFINE(wdt_work, run_wdt_work);
K_WORK_DEFINE(init_work, run_init_work);
K_WORK_DEFINE(input_work, run_input_work);

ZBUS_CHAN_DECLARE(ble_comm_data_chan);
ZBUS_LISTENER_DEFINE(main_ble_comm_lis, on_zbusBLECommData_Callback);

static void run_input_work(struct k_work *item)
{
    struct input_worker_item_t *container = CONTAINER_OF(item, struct input_worker_item_t, work);

    LOG_WRN("Worker, Button %u", container->data.code);

    // Don't process the press if it caused wakeup.
    if (zsw_power_manager_reset_idle_timout()) {
        return;
    }

    // Handle the input events. We have to take care about the screen orientation for the touch events.
    switch (container->data.code) {
        // Touch event
        // Slide from right to left.
        case INPUT_BTN_NORTH: {
            break;
        }
        // Touch event
        // Slide from left to right.
        case INPUT_BTN_SOUTH: {
            break;
        }
        // Touch event
        // Slide from bottom to top.
        case INPUT_BTN_WEST: {
            break;
        }
        // Touch event
        // Slide from top to bottom.
        case INPUT_BTN_EAST: {
            break;
        }
        // Button event
        // Always allow force restart.
        case (INPUT_KEY_Y): {
            LOG_INF("Force restart");

            retained.off_count += 1;
            retained_update();
            sys_reboot(SYS_REBOOT_COLD);

            break;
        }
        // Button event
        case INPUT_KEY_3: {
            if (zsw_notification_popup_is_shown()) {
                zsw_notification_popup_remove();
            } else if (watch_state == APPLICATION_MANAGER_STATE) {
                application_manager_exit_app();

                return;
            }

            break;
        }
        case INPUT_KEY_4: {
            if (watch_state == WATCHFACE_STATE) {
                zsw_vibration_run_pattern(ZSW_VIBRATION_PATTERN_CLICK);
                lv_async_call(open_application_manager_page, NULL);
            }

            break;
        }
    }

    if (buttons_allocated) {
        // Handled by LVGL.
        return;
    }
}

const struct device *const buttons_dev = DEVICE_DT_GET(DT_NODELABEL(buttons));
const struct device *const longpress_dev = DEVICE_DT_GET(DT_NODELABEL(longpress));

static void run_init_work(struct k_work *item)
{
    lv_indev_t *touch_indev;

    load_retention_ram();
    notification_manager_init();
    enable_bluetoth();
    zsw_imu_init();
    zsw_magnetometer_init();
    zsw_pressure_sensor_init();
    zsw_clock_init(retained.current_time_seconds);
    // Not to self, PWM consumes like 250uA...
    // Need to disable also when screen is off.
    display_control_init();
    display_control_sleep_ctrl(true);

    INPUT_CALLBACK_DEFINE(NULL, on_InputSyubsys_Callback);

    lv_indev_drv_init(&enc_drv);
    enc_drv.type = LV_INDEV_TYPE_ENCODER;
    enc_drv.read_cb = enocoder_read;
    enc_drv.feedback_cb = click_feedback;
    enc_indev = lv_indev_drv_register(&enc_drv);

    input_group = lv_group_create();
    temp_group = lv_group_create();
    lv_group_set_default(input_group);
    lv_indev_set_group(enc_indev, input_group);

    touch_indev = lv_indev_get_next(NULL);
    while (touch_indev) {
        if (lv_indev_get_type(touch_indev) == LV_INDEV_TYPE_POINTER) {
            // TODO First fix so not all presses everywhere are registered as clicks and cause vibration
            // Clicking anywehere with this below added right now will cause a vibration, which
            // is not what we want
            // touch_indev->driver->feedback_cb = click_feedback;
            break;
        }
        touch_indev = lv_indev_get_next(touch_indev);
    }

    watch_state = WATCHFACE_STATE;
    lv_obj_add_event_cb(lv_scr_act(), on_ScreenGestureEvent_Callback, LV_EVENT_GESTURE, NULL);
    watchface_app_start(input_group, on_WatchfaceAppEvent_Callback);
}

void run_wdt_work(struct k_work *item)
{
    task_wdt_feed(kernal_wdt_id);
    k_work_schedule(&wdt_work, K_MSEC(TASK_WDT_FEED_INTERVAL_MS));
}

int main(void)
{
#if defined(CONFIG_TASK_WDT) && !defined(CONFIG_BOARD_NATIVE_POSIX)
    const struct device *hw_wdt_dev = DEVICE_DT_GET(DT_ALIAS(watchdog0));
    if (!device_is_ready(hw_wdt_dev)) {
        printk("Hardware watchdog %s is not ready; ignoring it.\n",
               hw_wdt_dev->name);
        hw_wdt_dev = NULL;
    }

    task_wdt_init(hw_wdt_dev);
    kernal_wdt_id = task_wdt_add(TASK_WDT_FEED_INTERVAL_MS * 2, NULL, NULL);

    k_work_schedule(&wdt_work, K_NO_WAIT);
#endif
    // The init code requires a bit of stack.
    // So in order to not increase CONFIG_MAIN_STACK_SIZE and loose
    // this RAM forever, instead re-use the system workqueue for init
    // it has the required amount of stack.
    k_work_submit(&init_work);

    int Counter = 0;
    while (1) {
        LOG_ERR("Counter: %u", Counter++);
        k_msleep(1000);
    }

    return 0;
}

static void enable_bluetoth(void)
{
    int err;

#ifdef CONFIG_BOARD_NATIVE_POSIX
    bt_addr_le_t addr;

    err = bt_addr_le_from_str("DE:AD:BE:EF:BA:11", "random", &addr);
    if (err) {
        LOG_ERR("Invalid BT address (err %d)", err);
    }

    err = bt_id_create(&addr, NULL);
    if (err < 0) {
        LOG_ERR("Creating new ID failed (err %d)", err);
    }
#endif

    err = bt_enable(NULL);
    if (err != 0) {
        LOG_ERR("Failed to enable Bluetooth, err: %d", err);
        return;
    }

#ifdef CONFIG_SETTINGS
    settings_load();
#endif

    __ASSERT_NO_MSG(ble_comm_init(on_BLEDAta_Callback) == 0);
    bleAoaInit();
}

static bool load_retention_ram(void)
{
    bool retained_ok = retained_validate();
    //memset(&retained, 0, sizeof(retained));
    /* Increment for this boot attempt and update. */
    retained.boots += 1;
    retained_update();

    LOG_DBG("Retained data: %s\n", retained_ok ? "valid" : "INVALID");
    LOG_DBG("Boot count: %u\n", retained.boots);
    LOG_DBG("uptime_latest: %" PRIu64 "\n", retained.uptime_latest);
    LOG_DBG("Active Ticks: %" PRIu64 "\n", retained.uptime_sum);

    return retained_ok;
}

static void open_notification_popup(void *data)
{
    not_mngr_notification_t *not = notification_manager_get_newest();
    if (not != NULL) {
        lv_group_set_default(temp_group);
        lv_indev_set_group(enc_indev, temp_group);
        zsw_vibration_run_pattern(ZSW_VIBRATION_PATTERN_NOTIFICATION);
        zsw_notification_popup_show(not->title, not->body, not->src, not->id, on_PopupNotifcation_Closed, 10);
        buttons_allocated = true;
    }
    pending_not_open = false;
}

static void open_application_manager_page(void *app_name)
{
    watchface_app_stop();
    buttons_allocated = true;
    watch_state = APPLICATION_MANAGER_STATE;
    application_manager_show(on_ApplicationManager_Close, lv_scr_act(), input_group, (char *)app_name);
}

static void close_popup_notification(lv_timer_t *timer)
{
    int msg_len;
    char buf[100];
    uint32_t id;

    id = (uint32_t)timer->user_data;
    // Notification was dismissed, hence consider it read.
    notification_manager_remove(id);

    lv_group_set_default(input_group);
    lv_indev_set_group(enc_indev, input_group);
    if (watch_state == WATCHFACE_STATE) {
        buttons_allocated = 0;
    } else {
        buttons_allocated = 1;
    }

    memset(buf, 0, sizeof(buf));

    // Send to phone notification read => It will be remove on phone too.
    msg_len = snprintf(buf, sizeof(buf), "{\"t\":\"notify\", \"id\": %d, \"n\": %s} \n", id, "\"DISMISS\"");
    ble_comm_send(buf, msg_len);
}

static void on_PopupNotifcation_Closed(uint32_t id)
{
    lv_timer_t *timer;
    // Changing back input group directly here causes LVGL
    // to not remove the notifcation for some reason.
    // Maybe a bug, or something done wrong.
    // Anyway doing it after a while instead seems to fix
    // the problem.
    timer = lv_timer_create(close_popup_notification, 500,  (void *)id);
    lv_timer_set_repeat_count(timer, 1);
}

static void on_ApplicationManager_Close(void)
{
    application_manager_delete();
    watch_state = WATCHFACE_STATE;
    watchface_app_start(input_group, on_WatchfaceAppEvent_Callback);
    lv_async_call(async_turn_off_buttons_allocation, NULL);
}

static void async_turn_off_buttons_allocation(void *unused)
{
    buttons_allocated = false;
}

static void on_InputSyubsys_Callback(struct input_event *evt)
{
    // Currently you have to define a keycode as binding between buttons and longpress. We skip this binding codes for now.
    // Also touch events will be skipped, because they are handled by LVGL.
    // TODO: Charger is also ignored for now.
    // TODO: Replace this filtering with a propper device filtering setup for the input handler
    if ((evt->code == INPUT_ABS_X) || (evt->code == INPUT_ABS_Y) || (evt->code == INPUT_BTN_TOUCH) ||
        (evt->code == INPUT_KEY_KP0) || (evt->code == INPUT_KEY_POWER) || (evt->value == 1)) {
        return;
    }

    input_worker_item.data = *evt;
    input_worker_item.work = input_work;
    k_work_submit(&input_worker_item.work);
}

static void enocoder_read(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    if (!buttons_allocated) {
        return;
    }
    if (button_read(BUTTON_TOP_LEFT)) {
        data->key = LV_KEY_LEFT;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_TOP_LEFT;
    } else if (button_read(BUTTON_TOP_RIGHT)) {
        data->key = LV_KEY_ENTER;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_TOP_RIGHT;
    } else if (button_read(BUTTON_BOTTOM_LEFT)) {
        data->key = LV_KEY_RIGHT;
        data->state = LV_INDEV_STATE_PR;
        last_pressed = BUTTON_BOTTOM_LEFT;
    } else if (button_read(BUTTON_BOTTOM_RIGHT)) {
        // Not used for now. TODO exit/back button.
    } else {
        if (last_pressed == 0xFF) {
            return;
        }
        data->state = LV_INDEV_STATE_REL;
        switch (last_pressed) {
            case BUTTON_TOP_LEFT:
                data->key = LV_KEY_RIGHT;
                break;
            case BUTTON_TOP_RIGHT:
                data->key = LV_KEY_ENTER;
                break;
            case BUTTON_BOTTOM_LEFT:
                data->key = LV_KEY_LEFT;
                break;
            default:
                break;
        }
        last_pressed = 0xFF;
    }
}

static void on_ScreenGestureEvent_Callback(lv_event_t *e)
{
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_GESTURE) {
        lv_dir_t  dir = lv_indev_get_gesture_dir(lv_indev_get_act());

        if (watch_state == WATCHFACE_STATE && !zsw_notification_popup_is_shown()) {
            switch (dir) {
                case LV_DIR_BOTTOM:
                    open_application_manager_page(NULL);
                    break;
                case LV_DIR_TOP:
                    open_application_manager_page("Settings");
                    break;
                case LV_DIR_RIGHT:
                    watchface_change();
                    break;
                case LV_DIR_LEFT:
                    open_application_manager_page("Notification");
                    break;
                default:
                    __ASSERT_NO_MSG(0);
            }
            lv_indev_wait_release(lv_indev_get_act());
        } else if (zsw_notification_popup_is_shown()) {
            zsw_notification_popup_remove();
        } else if (watch_state == APPLICATION_MANAGER_STATE && dir == LV_DIR_RIGHT) {
#ifdef CONFIG_BOARD_NATIVE_POSIX
            // Until there is a better way to go back without access to buttons.
            application_manager_exit_app();
#endif
        }
    }
}

static void on_WatchfaceAppEvent_Callback(watchface_app_evt_t evt)
{
    if (watch_state == WATCHFACE_STATE && !zsw_notification_popup_is_shown()) {
        switch (evt) {
            case WATCHFACE_APP_EVT_CLICK_BATT:
                open_application_manager_page("Battery");
                break;
            case WATCHFACE_APP_EVT_CLICK_STEP:
                break;
            case WATCHFACE_APP_EVT_CLICK_WEATHER:
                break;
            default:
                break;
        }
    }
}

static void click_feedback(struct _lv_indev_drv_t *drv, uint8_t e)
{
    if (e == LV_EVENT_CLICKED) {
        zsw_vibration_run_pattern(ZSW_VIBRATION_PATTERN_CLICK);
    }
}

static void on_BLEDAta_Callback(ble_comm_cb_data_t *cb)
{
    not_mngr_notification_t *parsed_not;

    switch (cb->type) {
        case BLE_COMM_DATA_TYPE_NOTIFY:
            parsed_not = notification_manager_add(&cb->data.notify);
            if (!parsed_not) {
                return;
            }

            if (zsw_notification_popup_is_shown() || pending_not_open) {
                return;
            }

            pending_not_open = true;

            if (zsw_power_manager_get_state() != ZSW_ACTIVITY_STATE_NOT_WORN_STATIONARY) {
                zsw_power_manager_reset_idle_timout();
                lv_async_call(open_notification_popup, NULL);
            }
            break;

        default:
            break;
    }
}

static void on_zbusBLECommData_Callback(const struct zbus_channel *chan)
{
    const struct ble_data_event *event = zbus_chan_const_msg(chan);
    switch (event->data.type) {
        case BLE_COMM_DATA_TYPE_NOTIFY:
            // TODO, this one not supported yet through events
            // Handled in ble_comm callback for now
            break;
        case BLE_COMM_DATA_TYPE_NOTIFY_REMOVE:
            if (notification_manager_remove(event->data.data.notify_remove.id) != 0) {
                LOG_WRN("Notification %d not found", event->data.data.notify_remove.id);
            }
            break;
        case BLE_COMM_DATA_TYPE_SET_TIME: {
            struct timespec tspec;
            tspec.tv_sec = event->data.data.time.seconds;
            tspec.tv_nsec = 0;
            clock_settime(CLOCK_REALTIME, &tspec);
            break;
        }
        case BLE_COMM_DATA_TYPE_WEATHER:
            break;
        case BLE_COMM_DATA_TYPE_REMOTE_CONTROL:
            if (event->data.data.remote_control.button == BUTTON_END) {
                zsw_power_manager_reset_idle_timout();
                if (watch_state == APPLICATION_MANAGER_STATE) {
                    application_manager_delete();
                    application_manager_set_index(0);
                    buttons_allocated = false;
                    watch_state = WATCHFACE_STATE;
                    watchface_app_start(input_group, on_WatchfaceAppEvent_Callback);
                }
            } else {
                // TODO: Can we rework it with triggering input events?
                //button_set_fake_press((buttonId_t)event->data.data.remote_control.button, true);
            }

            break;
        default:
            break;
    }
}

#if defined(CONFIG_WATCHDOG) && !defined(CONFIG_RESET_ON_FATAL_ERROR)
extern void sys_arch_reboot(int type);

void k_sys_fatal_error_handler(unsigned int reason, const z_arch_esf_t *esf)
{
    ARG_UNUSED(esf);
    ARG_UNUSED(reason);

    LOG_PANIC();

    LOG_ERR("Resetting system");
    sys_arch_reboot(0);

    CODE_UNREACHABLE;
}
#endif