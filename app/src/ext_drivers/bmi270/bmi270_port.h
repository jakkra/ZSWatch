/**\
 * Copyright (c) 2021 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#ifndef _BMI270_PORT_H
#define _BMI270_PORT_H

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/types.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>

#include "bmi2.h"
#include "bmi270.h"

#define CONFIG_BMI270_TRIGGER
#define CONFIG_BMI270_TRIGGER_GLOBAL_THREAD

struct bmi270_data {
    int16_t ax, ay, az, gx, gy, gz;
    uint8_t acc_range, acc_odr, gyr_odr;
    uint16_t gyr_range;
};

struct bmi270_config {
    struct i2c_dt_spec i2c;
#ifdef CONFIG_BMI270_TRIGGER
    struct gpio_dt_spec int1_gpio;
    struct gpio_dt_spec int2_gpio;
#endif
};

static const struct sensor_driver_api bmi270_driver_api = {
    /*
    #if CONFIG_BMP581_TRIGGER
        .attr_set = bmi270_attr_set,
        .trigger_set = bmi270_trigger_set,
    #endif
        .sample_fetch = bmi270_sample_fetch,
        .channel_get = bmi270_channel_get,
    */
};

typedef void(*bmi270_on_isr)(void);

/*!
 *  @brief Function for reading the sensor's registers through I2C bus.
 *
 *  @param[in] reg_addr     : Register address.
 *  @param[out] reg_data    : Pointer to the data buffer to store the read data.
 *  @param[in] length       : No of bytes to read.
 *  @param[in] intf_ptr     : Interface pointer
 *
 *  @return Status of execution
 *  @retval = BMI2_INTF_RET_SUCCESS -> Success
 *  @retval != BMI2_INTF_RET_SUCCESS  -> Failure Info
 *
 */
BMI2_INTF_RETURN_TYPE bmi2_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);

/*!
 *  @brief Function for writing the sensor's registers through I2C bus.
 *
 *  @param[in] reg_addr     : Register address.
 *  @param[in] reg_data     : Pointer to the data buffer whose value is to be written.
 *  @param[in] length       : No of bytes to write.
 *  @param[in] intf_ptr     : Interface pointer
 *
 *  @return Status of execution
 *  @retval = BMI2_INTF_RET_SUCCESS -> Success
 *  @retval != BMI2_INTF_RET_SUCCESS  -> Failure Info
 *
 */
BMI2_INTF_RETURN_TYPE bmi2_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);

/*!
 *  @brief Function for reading the sensor's registers through SPI bus.
 *
 *  @param[in] reg_addr     : Register address.
 *  @param[out] reg_data    : Pointer to the data buffer to store the read data.
 *  @param[in] length       : No of bytes to read.
 *  @param[in] intf_ptr     : Interface pointer
 *
 *  @return Status of execution
 *  @retval = BMI2_INTF_RET_SUCCESS -> Success
 *  @retval != BMI2_INTF_RET_SUCCESS  -> Failure Info
 *
 */
BMI2_INTF_RETURN_TYPE bmi2_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);

/*!
 *  @brief Function for writing the sensor's registers through SPI bus.
 *
 *  @param[in] reg_addr     : Register address.
 *  @param[in] reg_data     : Pointer to the data buffer whose data has to be written.
 *  @param[in] length       : No of bytes to write.
 *  @param[in] intf_ptr     : Interface pointer
 *
 *  @return Status of execution
 *  @retval = BMI2_INTF_RET_SUCCESS -> Success
 *  @retval != BMI2_INTF_RET_SUCCESS  -> Failure Info
 *
 */
BMI2_INTF_RETURN_TYPE bmi2_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);

/*!
 * @brief This function provides the delay for required time (Microsecond) as per the input provided in some of the
 * APIs.
 *
 *  @param[in] period       : The required wait time in microsecond.
 *  @param[in] intf_ptr     : Interface pointer
 *
 *  @return void.
 *
 */
void bmi2_delay_us(uint32_t period, void *intf_ptr);

/*!
 *  @brief Function to select the interface between SPI and I2C.
 *
 *  @param[in] bma  : Structure instance of bmi2_dev
 *  @param[in] intf : Interface selection parameter
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval < 0 -> Failure Info
 */
int8_t bmi2_interface_init(struct bmi2_dev *bma, uint8_t intf);

/*!
 *  @brief Prints the execution status of the APIs.
 *
 *  @param[in] rslt     : Error code returned by the API whose execution status has to be printed.
 *
 *  @return void.
 */
void bmi2_error_codes_print_result(int8_t rslt);


#ifdef __cplusplus
}
#endif /* End of CPP guard */

#endif /* _BMI270_PORT_H */
