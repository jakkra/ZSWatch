#include "ble_data_event.h"


APP_EVENT_TYPE_DEFINE(ble_data_event,                  /* Unique event name. */
                      NULL,                                 /* Function logging event data. */
                      NULL,                              /* No event info provided. */
                      APP_EVENT_FLAGS_CREATE());         /* Flags managing event type. */