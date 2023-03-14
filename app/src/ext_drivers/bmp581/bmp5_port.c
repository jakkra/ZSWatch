#define DT_DRV_COMPAT bosch_bmp581

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <zephyr/init.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include "bmp5_defs.h"
#include <bmp5_port.h>

LOG_MODULE_REGISTER(BMP581, CONFIG_SENSOR_LOG_LEVEL);

#define BMP5_SHUTTLE_ID_PRIM  UINT16_C(0x1B3)
#define BMP5_SHUTTLE_ID_SEC   UINT16_C(0x1D3)

/*! Macro that defines read write length */
#define READ_WRITE_LEN     UINT8_C(46)

static int bmp581_init_interrupt(const struct device *dev);

static const struct device *device;

int bmp581_init(const struct device *dev)
{
    device = dev;
    const struct bmp581_config *config = device->config;
    if (!device_is_ready(config->i2c.bus)) {
        LOG_ERR("I2C bus device not ready");
        return -ENODEV;
    }

    return 0;
}

BMP5_INTF_RET_TYPE bmp5_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    const struct bmp581_config *config = device->config;
    return i2c_burst_read_dt(&config->i2c, (uint16_t)reg_addr, reg_data, len);
}

BMP5_INTF_RET_TYPE bmp5_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    const struct bmp581_config *config = device->config;
    return i2c_burst_write_dt(&config->i2c, reg_addr, reg_data, len);
}

void bmp5_delay_us(uint32_t period, void *intf_ptr)
{
    k_usleep(period);
}

int8_t bmp5_interface_init(struct bmp5_dev *bmp5_dev, uint8_t intf)
{
    int8_t rslt = BMP5_OK;
    const struct bmp581_config *config = device->config;

    if (bmp5_dev  != NULL) {
        printf("I2C Interface\n");
        bmp5_dev->read = bmp5_i2c_read;
        bmp5_dev->write = bmp5_i2c_write;
        bmp5_dev->intf = BMP5_I2C_INTF;
        bmp5_dev->delay_us = bmp5_delay_us;
    } else {
        rslt = BMP5_E_NULL_PTR;
    }

    return rslt;
}

void bmp5_error_codes_print_result(const char api_name[], int8_t rslt)
{
    if (rslt != BMP5_OK) {
        printk("%s\t", api_name);
        if (rslt == BMP5_E_NULL_PTR) {
            printk("Error [%d] : Null pointer\r\n", rslt);
        } else if (rslt == BMP5_E_COM_FAIL) {
            printk("Error [%d] : Communication failure\r\n", rslt);
        } else if (rslt == BMP5_E_DEV_NOT_FOUND) {
            printk("Error [%d] : Device not found\r\n", rslt);
        } else if (rslt == BMP5_E_INVALID_CHIP_ID) {
            printk("Error [%d] : Invalid chip id\r\n", rslt);
        } else if (rslt == BMP5_E_POWER_UP) {
            printk("Error [%d] : Power up error\r\n", rslt);
        } else if (rslt == BMP5_E_POR_SOFTRESET) {
            printk("Error [%d] : Power-on reset/softreset failure\r\n", rslt);
        } else if (rslt == BMP5_E_INVALID_POWERMODE) {
            printk("Error [%d] : Invalid powermode\r\n", rslt);
        } else {
            /* For more error codes refer "*_defs.h" */
            printk("Error [%d] : Unknown error code\r\n", rslt);
        }
    }
}

#define BMP581_DEFINE(inst)                                 \
    static struct bmp581_data bmp581_data_##inst;                       \
                                                \
    static const struct bmp581_config bmp581_config##inst = {               \
        .i2c = I2C_DT_SPEC_INST_GET(inst),                      \
        IF_ENABLED(CONFIG_BMP581_TRIGGER,                       \
               (.int1_gpio = GPIO_DT_SPEC_INST_GET_OR(inst, int_gpios, { 0 }),))    \
    };                                          \
                                                \
    SENSOR_DEVICE_DT_INST_DEFINE(inst, bmp581_init, NULL, &bmp581_data_##inst,      \
                  &bmp581_config##inst, POST_KERNEL,                \
                  CONFIG_SENSOR_INIT_PRIORITY, &bmp581_driver_api);         \

DT_INST_FOREACH_STATUS_OKAY(BMP581_DEFINE)
