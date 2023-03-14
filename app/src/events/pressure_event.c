#include "pressure_event.h"
#include <zephyr/zbus/zbus.h>

ZBUS_CHAN_DEFINE(pressure_data_chan,
    struct pressure_event,
    NULL,
    NULL,
    ZBUS_OBSERVERS_EMPTY,
    ZBUS_MSG_INIT()
);