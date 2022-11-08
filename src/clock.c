#include "clock.h"
#include <inttypes.h>
#include <sys/time.h>
#include <zephyr.h>
#include <stdio.h>
#include <stdlib.h>
#include <logging/log.h>
#include <errno.h>
#include <unistd.h>
#include <zephyr/kernel.h>
#include <logging/log.h>
#include <zephyr/sys/byteorder.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <bluetooth/gatt_dm.h>
#include <bluetooth/services/cts_client.h>

#include <zephyr/settings/settings.h>


#define DEVICE_NAME CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN (sizeof(DEVICE_NAME) - 1)

#define RUN_STATUS_LED DK_LED1
#define CON_STATUS_LED DK_LED2
#define RUN_LED_BLINK_INTERVAL 1000

#define KEY_READ_TIME DK_BTN1_MSK

static struct bt_cts_client cts_c;

static bool has_cts;

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_GAP_APPEARANCE,
		      (CONFIG_BT_DEVICE_APPEARANCE >> 0) & 0xff,
		      (CONFIG_BT_DEVICE_APPEARANCE >> 8) & 0xff),
	BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_LIMITED | BT_LE_AD_NO_BREDR)),
	BT_DATA_BYTES(BT_DATA_SOLICIT16, BT_UUID_16_ENCODE(BT_UUID_CTS_VAL)),
	BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
};

static const char *day_of_week[] = { "Unknown",	  "Monday",   "Tuesday",
				     "Wednesday", "Thursday", "Friday",
				     "Saturday",  "Sunday" };

static const char *month_of_year[] = { "Unknown",   "January", "February",
				       "March",	    "April",   "May",
				       "June",	    "July",    "August",
				       "September", "October", "November",
				       "December" };


static clock_tick_callback tick_callback;
static struct k_work_delayable tick_work;

static void tick_work_handler(struct k_work *work);

static void read_current_time_cb(struct bt_cts_client *cts_c,
				 struct bt_cts_current_time *current_time,
				 int err);

static bool do_read;
struct bt_cts_exact_time_256 clock_current_time;
 
static void current_time_print(struct bt_cts_current_time *current_time)
{
	LOG_PRINTK("\nCurrent Time:\n");
	LOG_PRINTK("\nDate:\n");

	LOG_PRINTK("\tDay of week   %s\n",
	       day_of_week[current_time->exact_time_256.day_of_week]);

	if (current_time->exact_time_256.day == 0) {
		LOG_PRINTK("\tDay of month  Unknown\n");
	} else {
		LOG_PRINTK("\tDay of month  %u\n",
		       current_time->exact_time_256.day);
	}

	LOG_PRINTK("\tMonth of year %s\n",
	       month_of_year[current_time->exact_time_256.month]);
	if (current_time->exact_time_256.year == 0) {
		LOG_PRINTK("\tYear          Unknown\n");
	} else {
		LOG_PRINTK("\tYear          %u\n",
		       current_time->exact_time_256.year);
	}
	LOG_PRINTK("\nTime:\n");
	LOG_PRINTK("\tHours     %u\n", current_time->exact_time_256.hours);
	LOG_PRINTK("\tMinutes   %u\n", current_time->exact_time_256.minutes);
	LOG_PRINTK("\tSeconds   %u\n", current_time->exact_time_256.seconds);
	LOG_PRINTK("\tFractions %u/256 of a second\n",
	       current_time->exact_time_256.fractions256);

	LOG_PRINTK("\nAdjust reason:\n");
	LOG_PRINTK("\tDaylight savings %x\n",
	       current_time->adjust_reason.change_of_daylight_savings_time);
	LOG_PRINTK("\tTime zone        %x\n",
	       current_time->adjust_reason.change_of_time_zone);
	LOG_PRINTK("\tExternal update  %x\n",
	       current_time->adjust_reason.external_reference_time_update);
	LOG_PRINTK("\tManual update    %x\n",
	       current_time->adjust_reason.manual_time_update);
}

static void notify_current_time_cb(struct bt_cts_client *cts_c,
				   struct bt_cts_current_time *current_time)
{
	//current_time_print(current_time);
	memcpy(&clock_current_time, &current_time->exact_time_256, sizeof(struct bt_cts_exact_time_256));
	if (tick_callback) {
		tick_callback(&clock_current_time);
	}
}

static void enable_notifications(void)
{
	int err;

	LOG_PRINTK("Enable not\n");

	if (has_cts && (bt_conn_get_security(cts_c.conn) >= BT_SECURITY_L2)) {
		err = bt_cts_subscribe_current_time(&cts_c,
						    notify_current_time_cb);
		if (err) {
			LOG_PRINTK("Cannot subscribe to current time value notification (err %d)\n",
			       err);
		}
	}
}

static void discover_completed_cb(struct bt_gatt_dm *dm, void *ctx)
{
	int err;

	LOG_PRINTK("The discovery procedure succeeded\n");

	bt_gatt_dm_data_print(dm);

	err = bt_cts_handles_assign(dm, &cts_c);
	if (err) {
		LOG_PRINTK("Could not assign CTS client handles, error: %d\n", err);
	} else {
		has_cts = true;
		do_read = true;
		if (bt_conn_get_security(cts_c.conn) < BT_SECURITY_L2) {
			err = bt_conn_set_security(cts_c.conn, BT_SECURITY_L2);
			if (err) {
				LOG_PRINTK("Failed to set security (err %d)\n",
				       err);
			}
		} else {
			enable_notifications();
			do_read = true;
		}
	}

	err = bt_gatt_dm_data_release(dm);
	if (err) {
		LOG_PRINTK("Could not release the discovery data, error "
		       "code: %d\n",
		       err);
	}

	err = bt_cts_read_current_time(&cts_c, read_current_time_cb);
	if (err) {
		LOG_PRINTK("Failed reading current time (err: %d)\n", err);
	}
}

static void discover_service_not_found_cb(struct bt_conn *conn, void *ctx)
{
	LOG_PRINTK("The service could not be found during the discovery\n");
}

static void discover_error_found_cb(struct bt_conn *conn, int err, void *ctx)
{
	LOG_PRINTK("The discovery procedure failed, err %d\n", err);
}

static const struct bt_gatt_dm_cb discover_cb = {
	.completed = discover_completed_cb,
	.service_not_found = discover_service_not_found_cb,
	.error_found = discover_error_found_cb,
};

static void connected(struct bt_conn *conn, uint8_t err)
{
	char addr[BT_ADDR_LE_STR_LEN];

	if (err) {
		LOG_PRINTK("Connection failed (err 0x%02x)\n", err);
		return;
	}

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	LOG_PRINTK("Connected %s\n", addr);

	has_cts = false;

	err = bt_gatt_dm_start(conn, BT_UUID_CTS, &discover_cb, NULL);
	if (err) {
		LOG_PRINTK("Failed to start discovery (err %d)\n", err);
	}
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));
	LOG_PRINTK("Disconnected from %s (reason 0x%02x)\n", addr, reason);
	do_read = false;
}

static void security_changed(struct bt_conn *conn, bt_security_t level,
			     enum bt_security_err err)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	if (!err) {
		LOG_PRINTK("Security changed: %s level %u\n", addr, level);

		enable_notifications();
	} else {
		LOG_PRINTK("Security failed: %s level %u err %d\n", addr, level,
		       err);
	}
}

BT_CONN_CB_DEFINE(conn_callbacks) = {
	.connected = connected,
	.disconnected = disconnected,
	.security_changed = security_changed,
};

static void auth_cancel(struct bt_conn *conn)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	LOG_PRINTK("Pairing cancelled: %s\n", addr);

	bt_conn_disconnect(conn, BT_HCI_ERR_REMOTE_USER_TERM_CONN);
}

static void pairing_complete(struct bt_conn *conn, bool bonded)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	LOG_PRINTK("Pairing completed: %s, bonded: %d\n", addr, bonded);
}

static void pairing_failed(struct bt_conn *conn, enum bt_security_err reason)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr));

	LOG_PRINTK("Pairing failed conn: %s, reason %d\n", addr, reason);

	bt_conn_disconnect(conn, BT_HCI_ERR_REMOTE_USER_TERM_CONN);
}

static struct bt_conn_auth_cb conn_auth_callbacks = {
	.cancel = auth_cancel,
};

static struct bt_conn_auth_info_cb conn_auth_info_callbacks = {
	.pairing_complete = pairing_complete,
	.pairing_failed = pairing_failed
};

static void read_current_time_cb(struct bt_cts_client *cts_c,
				 struct bt_cts_current_time *current_time,
				 int err)
{
	char addr[BT_ADDR_LE_STR_LEN];

	bt_addr_le_to_str(bt_conn_get_dst(cts_c->conn), addr, sizeof(addr));

	if (err) {
		LOG_PRINTK("Cannot read Current Time: %s, error: %d\n", addr, err);
		return;
	}
	//current_time_print(current_time);
	memcpy(&clock_current_time, &current_time->exact_time_256, sizeof(struct bt_cts_exact_time_256));
	if (tick_callback && current_time) {
		tick_callback(&clock_current_time);
	}
}


void clock_init(clock_tick_callback tick_cb, struct bt_cts_exact_time_256* start_time)
{
	memcpy(&clock_current_time, start_time, sizeof(struct bt_cts_exact_time_256));
	int err = bt_cts_client_init(&cts_c);
	if (err) {
		LOG_PRINTK("CTS client init failed (err %d)\n", err);
		return;
	}

	err = bt_conn_auth_cb_register(&conn_auth_callbacks);
	if (err) {
		LOG_PRINTK("Failed to register authorization callbacks %d\n", err);
		return;
	}

	err = bt_conn_auth_info_cb_register(&conn_auth_info_callbacks);
	if (err) {
		LOG_PRINTK("Failed to register authorization info callbacks.\n");
		return;
	}

	tick_callback = tick_cb;

	k_work_init_delayable(&tick_work, tick_work_handler);
	__ASSERT(k_work_reschedule(&tick_work, K_MSEC(1000)) == 1, "Failed schedule tick work");
}

static void increment_current_time_simple(void)
{
	// TODO The delay is not always 1000ms, take into consideration k_ticks instead to adjust
	// as good as possible!
	if (clock_current_time.seconds == 59) {
		if (clock_current_time.minutes == 59) {
			if (clock_current_time.hours == 23) {
				clock_current_time.hours = 0;
				clock_current_time.minutes = 0;
				clock_current_time.seconds = 0;
				// TODO handle change day etc.
				// clock_current_time.day++;
			} else {
				clock_current_time.hours++;
				clock_current_time.minutes = 0;
				clock_current_time.seconds = 0;
			}
		} else {
			clock_current_time.minutes++;
			clock_current_time.seconds = 0;
		}
	} else {
		clock_current_time.seconds++;
	}
	
}

static void tick_work_handler(struct k_work *work)
{
	if (do_read) {
		int err = bt_cts_read_current_time(&cts_c, read_current_time_cb);
		if (err) {
			LOG_PRINTK("Failed reading current time (err: %d)\n", err);
		}
	} else {
		increment_current_time_simple();
		if (tick_callback) {
			tick_callback(&clock_current_time);
		}
	}
	__ASSERT(k_work_reschedule(&tick_work, K_MSEC(1000)) == 1, "Failed schedule tick work");
}