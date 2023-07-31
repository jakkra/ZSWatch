/*
 * Copyright (c) 2023 Victor Chavez
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <zephyr/mgmt/mcumgr/mgmt/callbacks.h>
#include "ble_comm.h"

static int32_t img_mgmt_event(uint32_t evt_no,
					int32_t rc,
					bool *abort_more,
					void *data,
					size_t data_size)
{
	ARG_UNUSED(rc);
	ARG_UNUSED(abort_more);
	ARG_UNUSED(data);
	ARG_UNUSED(data_size);
	switch (evt_no) {
	case MGMT_EVT_OP_IMG_MGMT_DFU_CHUNK:
		// TODO should we reject image upload
		// if the watch is not e.g. in update mode?
		// otherwise user might get an update if anyone connects
		// to their watch
		//return MGMT_ERR_EACCESSDENIED;
		break;
	case MGMT_EVT_OP_IMG_MGMT_DFU_STARTED:
	case MGMT_EVT_OP_IMG_MGMT_DFU_STOPPED:
	case MGMT_EVT_OP_IMG_MGMT_DFU_CONFIRMED:
	case MGMT_EVT_OP_IMG_MGMT_DFU_PENDING:
	default:
		break;
	}
	return MGMT_ERR_EOK;
}


/**
 * @brief Callback struct for img mgmt
 *
 */
static struct mgmt_callback img_mgmt_cb = {.node = {NULL},
						.callback = img_mgmt_event,
						/** Process all img events **/
						.event_id = MGMT_EVT_OP_IMG_MGMT_ALL};

void dfu_init()
{
	mgmt_callback_register(&img_mgmt_cb);
}
