#ifndef ACCELEROMETER_H_
#define ACCELEROMETER_H_

#include <zephyr/drivers/sensor.h>

typedef enum accelerometer_evt_type_t {
    ACCELEROMETER_EVT_TYPE_XYZ,
    ACCELEROMETER_EVT_TYPE_DOOUBLE_TAP,
    ACCELEROMETER_EVT_TYPE_STEP,
    ACCELEROMETER_EVT_TYPE_STEP_ACTIVITY,
    ACCELEROMETER_EVT_TYPE_TILT,
    ACCELEROMETER_EVT_TYPE_GESTURE,
    ACCELEROMETER_EVT_TYPE_SIGNIFICANT_MOTION,
    ACCELEROMETER_EVT_TYPE_WRIST_WAKEUP
} accelerometer_evt_type_t;

typedef enum accelerometer_data_step_activity_t {
    ACCELEROMETER_EVT_STEP_ACTIVITY_STILL,
    ACCELEROMETER_EVT_STEP_ACTIVITY_WALK,
    ACCELEROMETER_EVT_STEP_ACTIVITY_RUN,
    ACCELEROMETER_EVT_STEP_ACTIVITY_UNKNOWN,
} accelerometer_data_step_activity_t;

typedef enum accelerometer_data_step_gesture_t {
    ACCELEROMETER_EVT_GESTURE_UNKNOWN,
    ACCELEROMETER_EVT_GESTURE_PUSH_ARM_DOWN,
    ACCELEROMETER_EVT_GESTURE_PIVOT_UP,
    ACCELEROMETER_EVT_GESTURE_WRIST_SHAKE,
    ACCELEROMETER_EVT_GESTURE_FLICK_IN,
    ACCELEROMETER_EVT_GESTURE_FLICK_OUT
} accelerometer_data_step_gesture_t;

typedef struct accelerometer_data_xyz_t {
    int16_t x;
    int16_t y;
    int16_t z;
} accelerometer_data_xyz_t;

typedef struct accelerometer_data_step_t {
    int16_t count;
} accelerometer_data_step_t;

typedef struct accelerometer_evt_t {
    accelerometer_evt_type_t type;
    union {
        accelerometer_data_xyz_t            xyz;
        accelerometer_data_step_t           step;
        accelerometer_data_step_activity_t  step_activity;
        accelerometer_data_step_gesture_t   gesture;
    } data;
} accelerometer_evt_t;

int zsw_accelerometer_init(void);

int zsw_accelerometer_fetch_xyz(int16_t *x, int16_t *y, int16_t *z);

int zsw_accelerometer_fetch_gyro(int16_t *x, int16_t *y, int16_t *z);

int zsw_accelerometer_fetch_temperature(struct sensor_value *temperature);

int zsw_accelerometer_fetch_num_steps(uint32_t *num_steps);

int zsw_accelerometer_reset_step_count(void);


#endif