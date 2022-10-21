#include "clock.h"
#include <inttypes.h>
#include <sys/time.h>
#include <zephyr.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
static clock_tick_callback tick_callback;

static void clockThread(void);

// TODO just use delayed work or similar, unecessary RAM wasted for a thread.
K_THREAD_DEFINE(clockThreadId, 1024, clockThread, NULL, NULL, NULL, 7, 0, K_TICKS_FOREVER);


void clock_init(clock_tick_callback tick_cb)
{
    tick_callback = tick_cb;
    k_thread_start(clockThreadId);
}


static void clockThread(void)
{
    struct timeval tv;

	while (1) {
		int res = gettimeofday(&tv, NULL);
		time_t now = time(NULL);
		struct tm tm;
		localtime_r(&now, &tm);

		if (res < 0) {
			printf("Error in gettimeofday(): %d\n", errno);
		}
        if (tick_callback) {
            tick_callback(tm.tm_hour, tm.tm_sec, tm.tm_sec);
        }
		k_msleep(1000);
	}
}