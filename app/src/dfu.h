/*
 * Copyright (c) 2023 Victor Chavez
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef __DFU_H
#define __DFU_H

/**
 * @brief Initialize Device firmware upgrade functionality
 * @details Registers callback to manage image upload
 * 
 */
void dfu_init();

#endif