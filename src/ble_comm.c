#include <ble_comm.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/services/nus.h>
#include <logging/log.h>

LOG_MODULE_REGISTER(ble_comm, LOG_LEVEL_DBG);


static void connected(struct bt_conn *conn, uint8_t err);
static void disconnected(struct bt_conn *conn, uint8_t reason);
static void param_updated(struct bt_conn *conn, uint16_t interval, uint16_t latency, uint16_t timeout);
static void nus_send_data(char *data);
static void bt_receive_cb(struct bt_conn *conn, const uint8_t *const data, uint16_t len);
BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected    = connected,
    .disconnected = disconnected,
    .le_param_updated = param_updated,
};
static struct bt_conn *currentConn;
static uint32_t nusMaxSendLen;

static on_data_cb_t data_parsed_cb;

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

int ble_comm_init(on_data_cb_t data_cb)
{
    int err = bt_nus_init(&nus_cb);
    if (err) {
        LOG_ERR("Failed to initialize UART service (err: %d)", err);
        return err;
    }
    data_parsed_cb = data_cb;
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
    struct bt_conn_info info;
    bt_conn_get_info(conn, &info);
    LOG_INF("Interval: %d, latency: %d, timeout: %d", info.le.interval, info.le.latency, info.le.timeout);
    /*
    // TODO connection timeout 0x08 after this, why?
    // TODO to this after GATT discovery is done
    struct bt_le_conn_param param = {
		.interval_min = 100,
		.interval_max = 500,
		.latency = 0,
		.timeout = 200,
	};

    err = bt_conn_le_param_update(conn, &param);
    if (err) {
        LOG_ERR("bt_conn_le_param_update failed");
    }
    */
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

static void param_updated(struct bt_conn *conn, uint16_t interval, uint16_t latency, uint16_t timeout)
{
    LOG_INF("Updated => Interval: %d, latency: %d, timeout: %d", interval, latency, timeout);
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
        data_parsed_cb(buf);
        char* needle = "body";
        char* body = strstr(buf, needle);
        if (body) {
        }
        parse_state = WAIT_GB;
    }

    //atHostHandleCommand(data, len, nus_send_data);
}

