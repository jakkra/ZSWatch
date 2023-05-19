#include "chg_event.h"
#include <zephyr/zbus/zbus.h>

ZBUS_CHAN_DEFINE(chg_state_data_chan,
                 struct chg_state_event,
                 NULL,
                 NULL,
                 ZBUS_OBSERVERS(watchface_chg_event, zsw_phone_app_publisher_chg_event),
                 ZBUS_MSG_INIT()
                );