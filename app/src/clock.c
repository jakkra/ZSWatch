#include "clock.h"
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

void clock_init(uint64_t start_time_seconds)
{
    setenv("TZ", "CET-1CEST", 1);
    tzset();

    struct timespec tspec;
    tspec.tv_sec = start_time_seconds;
    tspec.tv_nsec = 0;
    clock_settime(CLOCK_REALTIME, &tspec);
}

struct tm *clock_get_time(void)
{
    struct timeval tv;
    struct tm *tm;
    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec);

    return tm;
}

time_t clock_get_time_unix(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);

    return tv.tv_sec;
}