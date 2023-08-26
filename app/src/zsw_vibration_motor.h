#ifndef __ZSW_VIBRATION_MOTOR_H_
#define __ZSW_VIBRATION_MOTOR_H_

typedef enum zsw_vibration_pattern {
    ZSW_VIBRATION_PATTERN_CLICK,
    ZSW_VIBRATION_PATTERN_NOTIFICATION,
} zsw_vibration_pattern_t;

int zsw_vibration_run_pattern(zsw_vibration_pattern_t pattern);

#endif