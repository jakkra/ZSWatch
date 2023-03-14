#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_

#include <zephyr/drivers/sensor.h>

typedef struct pressure_data_evt_t {
    uint32_t    pressure;
    uint32_t    temp;
} pressure_data_evt_t;

int pressure_sensor_init(void);

int pressure_sensor_fetch_pressure(float *pressure, float *temperature);

#endif