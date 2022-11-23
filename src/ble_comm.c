#include <ble_comm.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/services/nus.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(ble_comm, LOG_LEVEL_DBG);


static void connected(struct bt_conn *conn, uint8_t err);
static void disconnected(struct bt_conn *conn, uint8_t reason);
static void nus_send_data(char *data);
static void bt_receive_cb(struct bt_conn *conn, const uint8_t *const data, uint16_t len);
BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected    = connected,
    .disconnected = disconnected,
};
static struct bt_conn *currentConn;
static uint32_t nusMaxSendLen;

static struct bt_nus_cb nus_cb = {
    .received = bt_receive_cb,
};

static void MTU_exchange_cb(struct bt_conn *conn, uint8_t err, struct bt_gatt_exchange_params *params)
{
	if (!err) {
		LOG_INF("MTU exchange done. %d", bt_gatt_get_mtu(currentConn)-3); 

        nusMaxSendLen = bt_gatt_get_mtu(currentConn)-3;
	} else {
		LOG_WRN("MTU exchange failed (err %" PRIu8 ")", err);
	}
}
static void request_mtu_exchange(void)
{	
    int err;
	static struct bt_gatt_exchange_params exchange_params;
	exchange_params.func = MTU_exchange_cb;

	err = bt_gatt_exchange_mtu(currentConn, &exchange_params);
	if (err) {
		LOG_WRN("MTU exchange failed (err %d)", err);
	} else {
		LOG_INF("MTU exchange pending");
	}
}
int ble_comm_init(void)
{
    int err = bt_nus_init(&nus_cb);
    if (err) {
        LOG_ERR("Failed to initialize UART service (err: %d)", err);
        return err;
    }
    return err;
}

int ble_comm_send(void)
{
    return 0;
}

static void connected(struct bt_conn *conn, uint8_t err)
{
    char addr[BT_ADDR_LE_STR_LEN];

    if (err) {
        LOG_ERR("Connection failed (err %u)", err);
        return;
    }
    currentConn = bt_conn_ref(conn);
    nusMaxSendLen = 20;

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
    LOG_INF("Connected %s", addr);
    request_mtu_exchange();
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    char addr[BT_ADDR_LE_STR_LEN];

    bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

    LOG_INF("Disconnected: %s (reason %u)", addr, reason);

    if (currentConn) {
        bt_conn_unref(currentConn);
    }
}

static void nus_send_data(char *data)
{
    int err = bt_nus_send(currentConn, (uint8_t *)data, strlen(data));
    if (err) {
        LOG_WRN("Failed to send data over BLE connection, err: %d", err);
    }
}

uint8_t buf[300];
static uint8_t brackets = 0;
static uint8_t data_index = 0;
typedef enum parse_state {
    WAIT_GB,
    WAIT_END,
    PARSE_STATE_DONE,
} parse_state_t;

parse_state_t parse_state = WAIT_GB;

extern void show_notification(char* buf, int len);

static void bt_receive_cb(struct bt_conn *conn, const uint8_t *const data, uint16_t len)
{
    //LOG_HEXDUMP_DBG(data, len, "RX");
    LOG_WRN("State: %d\n", parse_state);
    char* gb_start = strstr(data, "GB(");
    if (gb_start && parse_state != WAIT_GB) {
        LOG_ERR("Parsing error, was waiting end, but got GB");
        parse_state = WAIT_GB;
    }
    switch (parse_state) {
        case WAIT_GB:
        {
            if (gb_start) {
                parse_state = WAIT_END;
                brackets = 0;
                data_index = 0;
                memset(buf, 0, sizeof(buf));
                uint8_t index = (void*)gb_start - (void*)data;
                for (int i = index; i < len; i++) {
                    buf[data_index] = data[i];
                    data_index++;
                    if (data[i] == '{') {
                        LOG_WRN("bracket++\n");
                        brackets++;
                    } else if (data[i] == '}') {
                        brackets--;
                        LOG_WRN("bracket--\n");
                        if (brackets == 0) {
                            parse_state = PARSE_STATE_DONE;
                            LOG_WRN("PARSE_STATE_DONE\n");
                            break;
                        }
                    }
                }
            }
            break;
        }
        case WAIT_END:
        {
            
            for (int i = 0; i < len; i++) {
                buf[data_index] = data[i];
                data_index++;
                if (data[i] == '{') {
                    LOG_WRN("bracket++\n");
                    brackets++;
                } else if (data[i] == '}') {
                    brackets--;
                    LOG_WRN("bracket--\n");
                    if (brackets == 0) {
                        parse_state = PARSE_STATE_DONE;
                        LOG_WRN("PARSE_STATE_DONE\n");
                        break;
                    }
                }
            }
            
           LOG_WRN("WAIT END");
            break;
        }
        case PARSE_STATE_DONE:
        {
            LOG_WRN("Busy parsing, ingnoring...");
            break;
        }
        default:
            LOG_WRN("Unhandled state");
            break;
    }
    if (parse_state == PARSE_STATE_DONE) {
        LOG_HEXDUMP_WRN(buf, data_index, "PARSING DONE");
        show_notification(buf, data_index);
        char* needle = "body";
        char* body = strstr(buf, needle);
        if (body) {
        }
        parse_state = WAIT_GB;
    }

    //atHostHandleCommand(data, len, nus_send_data);
}

