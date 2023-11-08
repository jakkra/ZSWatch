#pragma once

#include "../bosch_bmi270.h"

#define BOSCH_BMI270_ACC_RANGE_2G       0x00
#define BOSCH_BMI270_ACC_RANGE_4G       0x01
#define BOSCH_BMI270_ACC_RANGE_8G       0x02
#define BOSCH_BMI270_ACC_RANGE_16G      0x03

#define BOSCH_BMI270_GYR_ODR_25_HZ      0x06
#define BOSCH_BMI270_GYR_ODR_50_HZ      0x07
#define BOSCH_BMI270_GYR_ODR_100_HZ     0x08
#define BOSCH_BMI270_GYR_ODR_200_HZ     0x09
#define BOSCH_BMI270_GYR_ODR_400_HZ     0x0A
#define BOSCH_BMI270_GYR_ODR_800_HZ     0x0B
#define BOSCH_BMI270_GYR_ODR_1600_HZ    0x0C
#define BOSCH_BMI270_GYR_ODR_3200_HZ    0x0D

/** @brief              
 *  @param p_bmi2_dev   
 *  @return             0 when successful
*/
int8_t bmi2_configure_enable_all(struct bmi2_dev *p_bmi2_dev);

/** @brief 
*/
int bmi2_set_accel_range(const struct device *p_dev, const struct sensor_value *p_range);

/** @brief 
*/
int bmi2_set_accel_odr_osr(const struct device *p_dev, const struct sensor_value *p_odr, const struct sensor_value *p_osr);

/** @brief 
*/
int bmi2_set_gyro_range(const struct device *p_dev, const struct sensor_value *p_range);

/** @brief 
*/
int bmi2_set_gyro_odr_osr(const struct device *p_dev, const struct sensor_value *p_odr, const struct sensor_value *p_osr);