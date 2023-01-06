#include <music_control/music_control_ui.h>
#include <application_manager.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <events/ble_data_event.h>

// Functions needed for all applications
static void music_control_app_start(lv_obj_t *root, lv_group_t *group);
static void music_control_app_stop(void);
static void on_close_music(void);

LV_IMG_DECLARE(templates);

static application_t app = {
    .name = "Music",
    .icon = &templates,
    .start_func = music_control_app_start,
    .stop_func = music_control_app_stop
};

static bool running;

static void music_control_app_start(lv_obj_t *root, lv_group_t *group)
{
    music_control_ui_show(root, on_close_music);
    running = true;
}

static void music_control_app_stop(void)
{
    running = false;
    music_control_ui_remove();
}

static void on_close_music(void)
{
    application_manager_app_close_request(&app);
}

static bool app_event_handler(const struct app_event_header *aeh)
{
    char buf[5 * MAX_MUSIC_FIELD_LENGTH];
    if (running && is_ble_data_event(aeh)) {
        struct ble_data_event *event = cast_ble_data_event(aeh);
        if (event->data.type == BLE_COMM_DATA_TYPE_MUSTIC_INFO) {
            snprintf(buf, sizeof(buf), "Track: %s\nArtist: %s\nAlbum: %s\nDuration: %d\n%d\n%d",
                     event->data.data.music_info.track_name, event->data.data.music_info.artist, event->data.data.music_info.album,
                     event->data.data.music_info.duration, event->data.data.music_info.track_num, event->data.data.music_info.track_count);
            music_control_ui_set_text(buf);
        }

        return false;
    }

    return false;
}

static int music_control_app_add(const struct device *arg)
{
    application_manager_add_application(&app);
    running = false;

    return 0;
}

SYS_INIT(music_control_app_add, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
APP_EVENT_LISTENER(music_control_app, app_event_handler);
APP_EVENT_SUBSCRIBE(music_control_app, ble_data_event);