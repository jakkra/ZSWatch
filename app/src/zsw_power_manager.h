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
#ifndef __ZSW_POWER_MANAGER_H_
#define __ZSW_POWER_MANAGER_H_
#include <stdbool.h>

/*
*   Resets the inactivity timeout that will make the watch go
*   into inactive mode with display etc. turned off to save power.
*
*   Return true if the call caused wakup from inactive state, false otherwise.
*/
bool zsw_power_manager_reset_idle_timout(void);

#endif // __ZSW_POWER_MANAGER_H_

