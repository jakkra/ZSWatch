#ifndef __ZSW_CLOCK_H
#define __ZSW_CLOCK_H
#include <inttypes.h>
#include <time.h>

void zsw_clock_init(uint64_t start_time_seconds);
struct tm *zsw_clock_get_time(void);
time_t zsw_clock_get_time_unix(void);

#endif