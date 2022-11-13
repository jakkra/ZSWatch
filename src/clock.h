#ifndef __CLOCK_H
#define __CLOCK_H
#include <inttypes.h>
#include <bluetooth/services/cts_client.h>

typedef void(*clock_tick_callback)(struct bt_cts_exact_time_256 *start_time);

void clock_init(clock_tick_callback tick_cb, struct bt_cts_exact_time_256 *start_time);

#endif