#define DT_DRV_COMPAT bosch_bmi270_ext

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "bmi270_port.h"
#include "bmi2_defs.h"
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(BMI270, LOG_LEVEL_DBG);

#define BMI2XY_SHUTTLE_ID  UINT16_C(0x1B8)

/*! Macro that defines read write length */
#define READ_WRITE_LEN     UINT8_C(46)

static const struct device *device = NULL;

int bmi270_port_init(const struct device *dev)
{
    device = dev;
    const struct bmi270_config *config = device->config;
    if (!device_is_ready(config->i2c.bus)) {
        LOG_ERR("I2C bus device not ready");
        return -ENODEV;
    }

    return 0;
}

BMI2_INTF_RETURN_TYPE bmi2_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    const struct bmi270_config *config = device->config;
    return i2c_burst_read_dt(&config->i2c, reg_addr, reg_data, len);
}

BMI2_INTF_RETURN_TYPE bmi2_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    const struct bmi270_config *config = device->config;
    return i2c_burst_write_dt(&config->i2c, reg_addr, reg_data, len);
}

void bmi2_delay_us(uint32_t period, void *intf_ptr)
{
    k_usleep(period);
}

int8_t bmi2_interface_init(struct bmi2_dev *bmi_dev, uint8_t intf)
{
    int8_t rslt = BMI2_OK;

    if (bmi_dev != NULL && device != NULL) {
        bmi_dev->intf = BMI2_I2C_INTF;
        bmi_dev->read = bmi2_i2c_read;
        bmi_dev->write = bmi2_i2c_write;
        bmi_dev->delay_us = bmi2_delay_us;
        bmi_dev->read_write_len = READ_WRITE_LEN;
        /* Assign to NULL to load the default config file. */
        bmi_dev->config_file_ptr = NULL;
    } else {
        rslt = BMI2_E_NULL_PTR;
    }

    return rslt;
}

void bmi2_error_codes_print_result(int8_t rslt)
{
    switch (rslt) {
        case BMI2_OK:

            /* Do nothing */
            break;

        case BMI2_W_FIFO_EMPTY:
            printk("Warning [%d] : FIFO empty\r\n", rslt);
            break;
        case BMI2_W_PARTIAL_READ:
            printk("Warning [%d] : FIFO partial read\r\n", rslt);
            break;
        case BMI2_E_NULL_PTR:
            printk(
                "Error [%d] : Null pointer error. It occurs when the user tries to assign value (not address) to a pointer,"
                " which has been initialized to NULL.\r\n",
                rslt);
            break;

        case BMI2_E_COM_FAIL:
            printk(
                "Error [%d] : Communication failure error. It occurs due to read/write operation failure and also due "
                "to power failure during communication\r\n",
                rslt);
            break;

        case BMI2_E_DEV_NOT_FOUND:
            printk("Error [%d] : Device not found error. It occurs when the device chip id is incorrectly read\r\n",
                   rslt);
            break;

        case BMI2_E_INVALID_SENSOR:
            printk(
                "Error [%d] : Invalid sensor error. It occurs when there is a mismatch in the requested feature with the "
                "available one\r\n",
                rslt);
            break;

        case BMI2_E_SELF_TEST_FAIL:
            printk(
                "Error [%d] : Self-test failed error. It occurs when the validation of accel self-test data is " "not satisfied\r\n",
                rslt);
            break;

        case BMI2_E_INVALID_INT_PIN:
            printk(
                "Error [%d] : Invalid interrupt pin error. It occurs when the user tries to configure interrupt pins "
                "apart from INT1 and INT2\r\n",
                rslt);
            break;

        case BMI2_E_OUT_OF_RANGE:
            printk(
                "Error [%d] : Out of range error. It occurs when the data exceeds from filtered or unfiltered data from "
                "fifo and also when the range exceeds the maximum range for accel and gyro while performing FOC\r\n",
                rslt);
            break;

        case BMI2_E_ACC_INVALID_CFG:
            printk(
                "Error [%d] : Invalid Accel configuration error. It occurs when there is an error in accel configuration"
                " register which could be one among range, BW or filter performance in reg address 0x40\r\n",
                rslt);
            break;

        case BMI2_E_GYRO_INVALID_CFG:
            printk(
                "Error [%d] : Invalid Gyro configuration error. It occurs when there is a error in gyro configuration"
                "register which could be one among range, BW or filter performance in reg address 0x42\r\n",
                rslt);
            break;

        case BMI2_E_ACC_GYR_INVALID_CFG:
            printk(
                "Error [%d] : Invalid Accel-Gyro configuration error. It occurs when there is a error in accel and gyro"
                " configuration registers which could be one among range, BW or filter performance in reg address 0x40 " "and 0x42\r\n",
                rslt);
            break;

        case BMI2_E_CONFIG_LOAD:
            printk(
                "Error [%d] : Configuration load error. It occurs when failure observed while loading the configuration "
                "into the sensor\r\n",
                rslt);
            break;

        case BMI2_E_INVALID_PAGE:
            printk(
                "Error [%d] : Invalid page error. It occurs due to failure in writing the correct feature configuration "
                "from selected page\r\n",
                rslt);
            break;

        case BMI2_E_SET_APS_FAIL:
            printk(
                "Error [%d] : APS failure error. It occurs due to failure in write of advance power mode configuration " "register\r\n",
                rslt);
            break;

        case BMI2_E_AUX_INVALID_CFG:
            printk(
                "Error [%d] : Invalid AUX configuration error. It occurs when the auxiliary interface settings are not "
                "enabled properly\r\n",
                rslt);
            break;

        case BMI2_E_AUX_BUSY:
            printk(
                "Error [%d] : AUX busy error. It occurs when the auxiliary interface buses are engaged while configuring"
                " the AUX\r\n",
                rslt);
            break;

        case BMI2_E_REMAP_ERROR:
            printk(
                "Error [%d] : Remap error. It occurs due to failure in assigning the remap axes data for all the axes "
                "after change in axis position\r\n",
                rslt);
            break;

        case BMI2_E_GYR_USER_GAIN_UPD_FAIL:
            printk(
                "Error [%d] : Gyro user gain update fail error. It occurs when the reading of user gain update status " "fails\r\n",
                rslt);
            break;

        case BMI2_E_SELF_TEST_NOT_DONE:
            printk(
                "Error [%d] : Self-test not done error. It occurs when the self-test process is ongoing or not " "completed\r\n",
                rslt);
            break;

        case BMI2_E_INVALID_INPUT:
            printk("Error [%d] : Invalid input error. It occurs when the sensor input validity fails\r\n", rslt);
            break;

        case BMI2_E_INVALID_STATUS:
            printk("Error [%d] : Invalid status error. It occurs when the feature/sensor validity fails\r\n", rslt);
            break;

        case BMI2_E_CRT_ERROR:
            printk("Error [%d] : CRT error. It occurs when the CRT test has failed\r\n", rslt);
            break;

        case BMI2_E_ST_ALREADY_RUNNING:
            printk(
                "Error [%d] : Self-test already running error. It occurs when the self-test is already running and "
                "another has been initiated\r\n",
                rslt);
            break;

        case BMI2_E_CRT_READY_FOR_DL_FAIL_ABORT:
            printk(
                "Error [%d] : CRT ready for download fail abort error. It occurs when download in CRT fails due to wrong "
                "address location\r\n",
                rslt);
            break;

        case BMI2_E_DL_ERROR:
            printk(
                "Error [%d] : Download error. It occurs when write length exceeds that of the maximum burst length\r\n",
                rslt);
            break;

        case BMI2_E_PRECON_ERROR:
            printk(
                "Error [%d] : Pre-conditional error. It occurs when precondition to start the feature was not " "completed\r\n",
                rslt);
            break;

        case BMI2_E_ABORT_ERROR:
            printk("Error [%d] : Abort error. It occurs when the device was shaken during CRT test\r\n", rslt);
            break;

        case BMI2_E_WRITE_CYCLE_ONGOING:
            printk(
                "Error [%d] : Write cycle ongoing error. It occurs when the write cycle is already running and another "
                "has been initiated\r\n",
                rslt);
            break;

        case BMI2_E_ST_NOT_RUNING:
            printk(
                "Error [%d] : Self-test is not running error. It occurs when self-test running is disabled while it's " "running\r\n",
                rslt);
            break;

        case BMI2_E_DATA_RDY_INT_FAILED:
            printk(
                "Error [%d] : Data ready interrupt error. It occurs when the sample count exceeds the FOC sample limit "
                "and data ready status is not updated\r\n",
                rslt);
            break;

        case BMI2_E_INVALID_FOC_POSITION:
            printk(
                "Error [%d] : Invalid FOC position error. It occurs when average FOC data is obtained for the wrong" " axes\r\n",
                rslt);
            break;

        default:
            printk("Error [%d] : Unknown error code\r\n", rslt);
            break;
    }
}

#define BMI270_DEFINE(inst)                                 \
    static struct bmi270_data bmi270_data_##inst;                       \
                                                \
    static const struct bmi270_config bmi270_config##inst = {               \
        .i2c = I2C_DT_SPEC_INST_GET(inst),                      \
        IF_ENABLED(CONFIG_BMI270_TRIGGER,                       \
               (.int1_gpio = GPIO_DT_SPEC_INST_GET_OR(inst, int_gpios, { 0 }),  \
                .int2_gpio = GPIO_DT_SPEC_INST_GET_OR(inst, int_gpios, { 0 }),))    \
    };                                          \
                                                \
    SENSOR_DEVICE_DT_INST_DEFINE(inst, bmi270_port_init, NULL, &bmi270_data_##inst,      \
                  &bmi270_config##inst, POST_KERNEL,                \
                  CONFIG_SENSOR_INIT_PRIORITY, &bmi270_driver_api);         \

DT_INST_FOREACH_STATUS_OKAY(BMI270_DEFINE)