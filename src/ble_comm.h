#ifndef __BLE_COMM_H
#define __BLE_COMM_H

#include <zephyr/kernel.h>


typedef enum ble_comm_data_type {
    BLE_COMM_DATA_TYPE_NOTIFY,
} ble_comm_data_type_t;

typedef struct ble_comm_notify {
    char* body;
    int body_len;
    char* sender;
    int sender_len;
    char* title;
    int title_len;
    char* src;
    int src_len;
} ble_comm_notify_t;

typedef struct ble_comm_cb_data {
    ble_comm_data_type_t type;
    union {
        ble_comm_notify_t notify;
    } data;
} ble_comm_cb_data_t;

typedef void(*on_data_cb_t)(ble_comm_cb_data_t* data);

int ble_comm_init(on_data_cb_t data_cb);
int ble_comm_send(void);
#endif