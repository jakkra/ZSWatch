#ifndef __CLOCK_H
#define __CLOCK_H
#include <inttypes.h>
#include <time.h>

void clock_init(uint64_t start_time_seconds);
struct tm *clock_get_time(void);
time_t clock_get_time_unix(void);

#endif