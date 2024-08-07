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
#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include "zsw_clock.h"
#include "zsw_retained_ram_storage.h"
#include "events/zsw_periodic_event.h"

static void zbus_periodic_slow_callback(const struct zbus_channel *chan);

ZBUS_CHAN_DECLARE(periodic_event_1s_chan);
ZBUS_LISTENER_DEFINE(zsw_clock_lis, zbus_periodic_slow_callback);

void zsw_clock_set_time(zsw_timeval_t *ztm)
{
    struct timespec tspec;

    tspec.tv_sec = ztm->tm.tm_sec;
    tspec.tv_nsec = 0;

    clock_settime(CLOCK_REALTIME, &tspec);
}

void zsw_clock_get_time(zsw_timeval_t *ztm)
{
    struct timeval tv;
    struct tm *tm;
    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec);
    memcpy(ztm, tm, sizeof(struct tm));

    // Add one to the month because we want to count from December instead of January
    ztm->tm.tm_mon += 1;

    // Add 1900 to the year because we want to count from 1900
    ztm->tm.tm_year += 1900;
}

time_t zsw_clock_get_time_unix(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec;
}

static void zbus_periodic_slow_callback(const struct zbus_channel *chan)
{
    retained.current_time_seconds = zsw_clock_get_time_unix();
    zsw_retained_ram_update();
}

static int zsw_clock_init(void)
{
    struct timespec tspec;

    tspec.tv_sec = retained.current_time_seconds;
    tspec.tv_nsec = 0;

    clock_settime(CLOCK_REALTIME, &tspec);
    if (strlen(retained.timezone) > 0) {
        setenv("TZ", retained.timezone, 1);
        tzset();
    }

    zsw_periodic_chan_add_obs(&periodic_event_1s_chan, &zsw_clock_lis);

    return 0;
}

SYS_INIT(zsw_clock_init, APPLICATION, 2);