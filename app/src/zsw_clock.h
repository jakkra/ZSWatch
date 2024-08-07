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

#pragma once

#include <inttypes.h>
#include <time.h>

typedef void (*zsw_clock_on_update)(void);

typedef struct {
    struct tm   tm;                 /**< Modified time object with 1900 added to the year and the month increased by one. */
    uint32_t    tv_usec;
} zsw_timeval_t;

void zsw_clock_add_update(zsw_clock_on_update callback);

void zsw_clock_set_time(zsw_timeval_t *ztm);

void zsw_clock_get_time(zsw_timeval_t *ztm);

time_t zsw_clock_get_time_unix(void);