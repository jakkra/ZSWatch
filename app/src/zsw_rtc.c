/*
 * This file is part of ZSWatch project <https://github.com/jakkra/ZSWatch/>.
 * Copyright (c) 2023 Jakob Krantz.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/zbus/zbus.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/rtc.h>
#include <zephyr/devicetree.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "zsw_clock.h"
#include "events/zsw_periodic_event.h"

const struct device *const rtc = DEVICE_DT_GET(DT_NODELABEL(rv_8263_c8));

LOG_MODULE_REGISTER(zsw_clock, LOG_LEVEL_DBG);

void zsw_clock_add_update(zsw_clock_on_update callback)
{

}

void zsw_clock_set_time(zsw_timeval_t *ztm)
{
    struct rtc_time time;

    time.tm_sec = ztm->tm.tm_sec;
    time.tm_min = ztm->tm.tm_min;
    time.tm_hour = ztm->tm.tm_hour;
    time.tm_wday = ztm->tm.tm_wday;
    time.tm_mday = ztm->tm.tm_mday;
    time.tm_mon = ztm->tm.tm_mon - 1;
    time.tm_year = ztm->tm.tm_year - 1900;

    //rtc_set_time(rtc, &time);
}

void zsw_clock_get_time(zsw_timeval_t *ztm)
{
    struct rtc_time time;

    //rtc_get_time(rtc, &time);

    ztm->tm.tm_sec = time.tm_sec;
    ztm->tm.tm_min = time.tm_min;
    ztm->tm.tm_hour = time.tm_hour;
    ztm->tm.tm_wday = time.tm_wday;
    ztm->tm.tm_mday = time.tm_mday;

    // Add one to the month because we want to count from December instead of January
    ztm->tm.tm_mon = time.tm_mon + 1;

    // Add 1900 to the year because we want to count from 0
    ztm->tm.tm_year = time.tm_year + 1900;
}

time_t zsw_clock_get_time_unix(void)
{
    // TODO:
    return 0;
}

void on_rtc_update(const struct device *dev, void *user_data)
{
}

static int zsw_clock_init(void)
{
    if (!device_is_ready(rtc)) {
        LOG_ERR("Device not ready!");
        return -1;
    }

    rtc_update_set_callback(rtc, on_rtc_update, NULL);

    return 0;
}

SYS_INIT(zsw_clock_init, APPLICATION, 2);