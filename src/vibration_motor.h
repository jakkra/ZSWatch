#ifndef __VIBRATION_MOTOT_H_
#define __VIBRATION_MOTOT_H_
#include <inttypes.h>
#include <stdbool.h>

void vibration_motor_init(void);
void vibration_motor_set_power(uint8_t percent);
void vibration_motor_set_on(bool on);

#endif