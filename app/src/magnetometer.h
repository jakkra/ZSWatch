#ifndef __MAGNETOMETER_H_
#define __MAGNETOMETER_H_
#include <stdbool.h>

void magnetometer_init(void);
void magnetometer_set_enable(bool enabled);
double magnetometer_get_heading(void);

#endif