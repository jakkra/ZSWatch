/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stdio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(zsw_flash, LOG_LEVEL_DBG);

#define SPI_FLASH_TEST_REGION_OFFSET 0xff000
#define SPI_FLASH_SECTOR_SIZE        4096

static int zsw_flash_test(void)
{
    const struct device *flash_dev = DEVICE_DT_GET_OR_NULL(DT_ALIAS(spi_flash0));

    if (!flash_dev || !device_is_ready(flash_dev)) {
        LOG_ERR("No external flash present: %s", flash_dev ? flash_dev->name : "spi_flash0");
        return 0;
    }

    return 0;
}

SYS_INIT(zsw_flash_test, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
