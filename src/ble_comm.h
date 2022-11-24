#ifndef __BLE_COMM_H
#define __BLE_COMM_H

#include <zephyr.h>

typedef void(*on_data_cb_t)(char* data);


int ble_comm_init(on_data_cb_t data_cb);
int ble_comm_send(void);
#endif