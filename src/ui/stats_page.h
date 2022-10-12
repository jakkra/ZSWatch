#ifndef __STATS_PAGE_H
#define __STATS_PAGE_H
#include <inttypes.h>

void states_page_init(void);

void states_page_show(void);

void states_page_remove(void);

void states_page_accelerometer_values(int32_t x, int32_t y, int32_t z);

#endif