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

#ifndef __ZSW_NOTIFICATION_MANAGER_H_
#define __ZSW_NOTIFICATION_MANAGER_H_

#include <inttypes.h>

#include "ble/ble_comm.h"

#define NOTIFICATION_MGR_MAX_FIELD_LEN  50
#define NOTIFICATION_MANAGER_MAX_STORED 20

typedef enum zsw_notification_src {
    NOTIFICATION_SRC_MESSENGER,
    NOTIFICATION_SRC_GMAIL,
    NOTIFICATION_SRC_NONE
} zsw_notification_src_t;

typedef struct not_mngr_notification {
    uint32_t id;
    char sender[NOTIFICATION_MGR_MAX_FIELD_LEN];
    char title[NOTIFICATION_MGR_MAX_FIELD_LEN];
    char body[NOTIFICATION_MGR_MAX_FIELD_LEN];
    zsw_notification_src_t src;
} zsw_not_mngr_notification_t;

void zsw_notification_manager_init(void);
zsw_not_mngr_notification_t *zsw_notification_manager_add(ble_comm_notify_t *notification);
int32_t zsw_notification_manager_remove(uint32_t id);
int32_t zsw_notification_manager_get(uint32_t id, zsw_not_mngr_notification_t *notifcation);
int32_t zsw_notification_manager_get_all(zsw_not_mngr_notification_t *notifcations, int *num_notifications);
int32_t zsw_notification_manager_get_num(void);
zsw_not_mngr_notification_t *zsw_notification_manager_get_newest(void);

#endif