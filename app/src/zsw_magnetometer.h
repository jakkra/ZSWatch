#ifndef __ZSW_MAGNETOMETER_H_
#define __ZSW_MAGNETOMETER_H_
#include <stdbool.h>

int zsw_magnetometer_init(void);
int zsw_magnetometer_set_enable(bool enabled);
double zsw_magnetometer_get_heading(void);
int zsw_magnetometer_get_all(float *x, float *y, float *z);
int zsw_magnetometer_start_calibration(void);
int zsw_magnetometer_stop_calibration(void);
#endif