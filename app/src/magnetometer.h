#ifndef __MAGNETOMETER_H_
#define __MAGNETOMETER_H_
#include <stdbool.h>

void magnetometer_init(void);
void magnetometer_set_enable(bool enabled);
double magnetometer_get_heading(void);
void magnetometer_get_all(float* x, float* y, float* z);

#endif