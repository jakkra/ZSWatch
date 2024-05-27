/* microcrystal_rv8263c8_interrupt.c - Driver for Micro Crystal RV-8263-C8 RTC. */

/*
 * Copyright (c) 2024, Daniel Kampert
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

/** @brief
 *  @param p_dev
 *  @return         0 when successful
*/
int rv8263c8_init_interrupt(const struct device *p_dev);