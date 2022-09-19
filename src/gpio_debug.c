/*
 * Copyright 2021 u-blox
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <zephyr.h>
#include <device.h>
#include <sys/__assert.h>
#include <assert.h>
#include <drivers/gpio.h>
#include <logging/log.h>
#include <gpio_debug.h>

LOG_MODULE_REGISTER(gpio_debug, LOG_LEVEL_DBG);

static struct gpio_dt_spec watch_gpios[] = {
    [DISPLAY_EN] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 3 },
    [BTN_1] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 2 },
    [DISPLAY_DC] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 16 },
    [QSPI_1_SO] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 22 },
    [V5_REG_EN] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 31 },
    [MAX30_INT] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 30 },
    [QSPI_0_SO] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio1)), .pin = 9 },
    [DRV_VIB_PWM] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 11 },
    [DRV_VIB_EN] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 12 },

    [DISPLAY_DATA] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio1)), .pin = 0 },
    [BAT_MON] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 5 },
    [BAT_MON_EN] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 4 },
    [INT1_LIS] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 29 },
    [INT2_LIS] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 28 },
    [BTN_2] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 23 },
    [QSPI_2_WP] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 7 },
    [DISPLAY_CLK] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 0 },
    [DISPLAY_CS] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 1 },

    [BTN_3] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 9},
    [SDA_ANNA] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 27 },
    [SCL_ANNA] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 6 },
    [DISPLAY_BLK] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 26 },
    [QSPI_CS] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 15 },
    [QSPI_3_RST] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 20 },
    [QSPI_CLK] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 14 },
    [EVK_RED] = { .port = DEVICE_DT_GET_OR_NULL(DT_NODELABEL(gpio0)), .pin = 13 },
};



void gpio_debug_init(void) {
    int ret;

    for (int i = 0; i < ARRAY_SIZE(watch_gpios); i++) {
        __ASSERT(device_is_ready(watch_gpios[i].port), "Error: button device %s is not ready\n",  watch_gpios[i].port->name);
        ret = gpio_pin_configure_dt(&watch_gpios[i], GPIO_OUTPUT);
        __ASSERT_NO_MSG(ret == 0);
        ret = gpio_pin_set_dt(&watch_gpios[i], 0);
        __ASSERT_NO_MSG(ret == 0);
    }
}

void gpio_debug_test(gpioWatchId_t gpioId)
{
    LOG_INF("Testing %d (%s.%d)", gpioId, watch_gpios[gpioId].port->name, watch_gpios[gpioId].pin);
    gpio_pin_set_dt(&watch_gpios[gpioId], 0);
    __ASSERT_NO_MSG(ret == 0);
    k_msleep(500);
    gpio_pin_set_dt(&watch_gpios[gpioId], 1);
    __ASSERT_NO_MSG(ret == 0);
    k_msleep(500);
    gpio_pin_set_dt(&watch_gpios[gpioId], 0);
    __ASSERT_NO_MSG(ret == 0);
    k_msleep(500);
    gpio_pin_set_dt(&watch_gpios[gpioId], 1);
    __ASSERT_NO_MSG(ret == 0);
    k_msleep(500);
    gpio_pin_set_dt(&watch_gpios[gpioId], 0);
    __ASSERT_NO_MSG(ret == 0);
}