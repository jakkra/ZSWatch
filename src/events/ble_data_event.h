#include <app_event_manager.h>
#include <ble_comm.h>

struct ble_data_event {
    struct app_event_header header;
    ble_comm_cb_data_t data;
};

APP_EVENT_TYPE_DECLARE(ble_data_event);