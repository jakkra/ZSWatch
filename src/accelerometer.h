#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <drivers/sensor.h>

typedef enum accelerometer_evt_type_t {
    ACCELEROMETER_EVT_TYPE_XYZ,
} accelerometer_evt_type_t;

typedef struct accelerometer_data_xyz_t
{
    int16_t x;
    int16_t y;
    int16_t z;
} accelerometer_data_xyz_t;

typedef struct accelerometer_evt_t {
    accelerometer_evt_type_t type;
    union {
        accelerometer_data_xyz_t xyz;
    } data;
} accelerometer_evt_t;

typedef void(*accel_event_cb)(accelerometer_evt_t* evt);

int accelerometer_init(accel_event_cb accel_cb);

int accelerometer_fetch_xyz(int16_t* x, int16_t* y, int16_t* z);

int accelerometer_fetch_temperature(struct sensor_value* temperature);


#endif