#ifndef __CLOCK_H
#define __CLOCK_H

typedef void(*clock_tick_callback)(int hour, int minute, int second);

void clock_init(clock_tick_callback tick_cb);

#endif