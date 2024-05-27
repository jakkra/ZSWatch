/* microcrystal_rv8263c8.h - Driver for Micro Crystal RV-8263-C8 RTC. */

/*
 * Copyright (c 2024, Daniel Kampert
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

/** @brief
*/
typedef enum {
    RV8263C8_OUT_32KHZ      = 0,
    RV8263C8_OUT_16KHZ,
    RV8263C8_OUT_8KHZ,
    RV8263C8_OUT_4KHZ,
    RV8263C8_OUT_2KHZ,
    RV8263C8_OUT_1KHZ,
    RV8263C8_OUT_1HZ,
    RV8263C8_OUT_LOW,
} rv_8263_c8_clkout_t;