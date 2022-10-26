#ifndef __PLOT_PAGE_H
#define __PLOT_PAGE_H
#include <inttypes.h>

void plot_page_init(void);

void plot_page_show(void);

void plot_page_remove(void);

void plot_page_led_values(int32_t red, int32_t green, int32_t ir);

#endif