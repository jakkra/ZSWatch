#include "battery_event.h"
#include <zephyr/zbus/zbus.h>

ZBUS_CHAN_DEFINE(battery_sample_data_chan,
                 struct battery_sample_event,
                 NULL,
                 NULL,
                 #ifdef CONFIG_APPLICATIONS_USE_BATTERY
                    ZBUS_OBSERVERS(watchface_battery_event, zsw_phone_app_publisher_battery_event, battery_app_battery_event),
                 #else
                    ZBUS_OBSERVERS(watchface_battery_event, zsw_phone_app_publisher_battery_event),
                 #endif
                 ZBUS_MSG_INIT()
                );