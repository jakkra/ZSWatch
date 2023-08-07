#include <zsw_clock.h>
#include <inttypes.h>
#include <sys/time.h>
#include <time.h>
#include <zephyr/kernel.h>
#include <stdio.h>
#include <stdlib.h>
#include <zephyr/logging/log.h>
#include <errno.h>
#include <unistd.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <stdlib.h>
#include <ram_retention_storage.h>
#include <events/periodic_event.h>
#include <zsw_periodic_event.h>

static void zbus_periodic_slow_callback(const struct zbus_channel *chan);

ZBUS_CHAN_DECLARE(periodic_event_slow_chan);
ZBUS_LISTENER_DEFINE(zsw_clock_lis, zbus_periodic_slow_callback);

void zsw_clock_init(uint64_t start_time_seconds)
{
    setenv("TZ", "CET-1CEST", 1);
    tzset();

    struct timespec tspec;
    tspec.tv_sec = start_time_seconds;
    tspec.tv_nsec = 0;
    clock_settime(CLOCK_REALTIME, &tspec);
    zsw_periodic_chan_add_obs(&periodic_event_slow_chan, &zsw_clock_lis);
}

struct tm *zsw_clock_get_time(void)
{
    struct timeval tv;
    struct tm *tm;
    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec);

    return tm;
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
    retained_update();
}
