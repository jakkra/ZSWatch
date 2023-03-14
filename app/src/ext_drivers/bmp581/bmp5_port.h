/**\
 * Copyright (c) 2022 Bosch Sensortec GmbH. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 **/

#ifndef _BMP5_COMMON_H
#define _BMP5_COMMON_H

/*! CPP guard */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/sys/util.h>
#include <zephyr/types.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include "bmp5.h"

#define CONFIG_BMP581_TRIGGER
#define CONFIG_BMP581_TRIGGER_GLOBAL_THREAD

struct bmp581_data {
    int16_t x_sample;
    int16_t y_sample;
    int16_t z_sample;
    int8_t temp_sample;

#ifdef CONFIG_BMP581_TRIGGER
    const struct device *dev;
    struct gpio_callback gpio_cb;
    struct k_work work;
#endif /* CONFIG_BMP581_TRIGGER */
};

struct bmp581_config {
    struct i2c_dt_spec i2c;
#ifdef CONFIG_BMP581_TRIGGER
    struct gpio_dt_spec int1_gpio;
#endif
};

static const struct sensor_driver_api bmp581_driver_api = {
    /*
    #if CONFIG_BMP581_TRIGGER
        .attr_set = bmp581_attr_set,
        .trigger_set = bmp581_trigger_set,
    #endif
        .sample_fetch = bmp581_sample_fetch,
        .channel_get = bmp581_channel_get,
    */
};

typedef void(*bmp5_on_isr)(void);


/***************************************************************************/

/*!                 User function prototypes
 ****************************************************************************/

/*!
 *  @brief Function for reading the sensor's registers through SPI bus.
 *
 *  @param[in] reg_addr      : Register address.
 *  @param[out] reg_data     : Pointer to the data buffer to store the read data.
 *  @param[in] length        : No of bytes to read.
 *  @param[in, out] intf_ptr : Void pointer that can enable the linking of descriptors
 *                             for interface related call backs.
 *
 *  @return Status of execution
 *
 *  @retval BMP5_INTF_RET_SUCCESS -> Success.
 *  @retval != BMP5_INTF_RET_SUCCESS -> Fail.
 *
 */
BMP5_INTF_RET_TYPE bmp5_spi_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr);

/*!
 *  @brief Function for reading the sensor's registers through I2C bus.
 *
 *  @param[in] reg_addr      : Register address.
 *  @param[out] reg_data     : Pointer to the data buffer to store the read data.
 *  @param[in] length        : No of bytes to read.
 *  @param[in, out] intf_ptr : Void pointer that can enable the linking of descriptors
 *                             for interface related call backs.
 *
 *  @return Status of execution
 *
 *  @retval BMP5_INTF_RET_SUCCESS -> Success.
 *  @retval != BMP5_INTF_RET_SUCCESS -> Fail.
 *
 */
BMP5_INTF_RET_TYPE bmp5_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr);

/*!
 *  @brief Function for writing the sensor's registers through SPI bus.
 *
 *  @param[in] reg_addr      : Register address.
 *  @param[in] reg_data      : Pointer to the data buffer whose data has to be written.
 *  @param[in] length        : No of bytes to write.
 *  @param[in, out] intf_ptr : Void pointer that can enable the linking of descriptors
 *                             for interface related call backs.
 *
 *  @return Status of execution
 *
 *  @retval BMP5_INTF_RET_SUCCESS -> Success.
 *  @retval  != BMP5_INTF_RET_SUCCESS -> Fail.
 *
 */
BMP5_INTF_RET_TYPE bmp5_spi_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr);

/*!
 *  @brief Function for writing the sensor's registers through I2C bus.
 *
 *  @param[in] reg_addr      : Register address.
 *  @param[in] reg_data      : Pointer to the data buffer whose value is to be written.
 *  @param[in] length        : No of bytes to write.
 *  @param[in, out] intf_ptr : Void pointer that can enable the linking of descriptors
 *                             for interface related call backs.
 *
 *  @return Status of execution
 *
 *  @retval BMP5_INTF_RET_SUCCESS -> Success.
 *  @retval != BMP5_INTF_RET_SUCCESS -> Failure.
 *
 */
BMP5_INTF_RET_TYPE bmp5_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr);

/*!
 * @brief This function provides the delay for required time (Microsecond) as per the input provided in some of the
 * APIs.
 *
 *  @param[in] period_us      : The required wait time in microsecond.
 *  @param[in, out] intf_ptr  : Void pointer that can enable the linking of descriptors
 *                             for interface related call backs.
 *  @return void.
 *
 */
void bmp5_delay_us(uint32_t period_us, void *intf_ptr);

/*!
 *  @brief Function to select the interface between SPI and I2C.
 *
 *  @param[in] bmp5_dev : Structure instance of bmp5_dev
 *  @param[in] intf     : Interface selection parameter
 *
 *  @return Status of execution
 *  @retval 0 -> Success
 *  @retval < 0 -> Failure Info
 */
int8_t bmp5_interface_init(struct bmp5_dev *bmp5_dev, uint8_t intf);

/*!
 *  @brief Prints the execution status of the APIs.
 *
 *  @param[in] api_name : Name of the API whose execution status has to be printed.
 *  @param[in] rslt     : Error code returned by the API whose execution status has to be printed.
 *
 *  @return void.
 */
void bmp5_error_codes_print_result(const char api_name[], int8_t rslt);

#ifdef __cplusplus
}
#endif /* End of CPP guard */

#endif /* _BMI270_PORT_H */