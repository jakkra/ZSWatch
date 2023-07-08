#include <zsw_charger.h>
#include <zephyr/kernel.h>
#include <zephyr/init.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include <events/chg_event.h>
#include <zephyr/zbus/zbus.h>

LOG_MODULE_REGISTER(zsw_charger, LOG_LEVEL_ERR);

ZBUS_CHAN_DECLARE(chg_state_data_chan);


#define CHECK_CHG_INTERVAL_MS  2500

typedef enum {
    CHG_STATE_START,
    CHG_STATE_DETECTING,
    CHG_STATE_CHARGE_DETECTED,
} chg_state_t;

static void charger_status_work_cb(struct k_work *work);
static void charger_status_chg_detected_isr(const struct device *dev, struct gpio_callback *cb, uint32_t pins);

static K_WORK_DELAYABLE_DEFINE(charger_work, charger_status_work_cb);
static const struct gpio_dt_spec is_charging_pin = GPIO_DT_SPEC_GET_BY_IDX_OR(DT_NODELABEL(charging_status), gpios,
                                                                              0, {});
static struct gpio_callback gpio_charger_cb;
static bool is_charging;
static chg_state_t chg_state;

bool zsw_charger_is_charging(void)
{
    return is_charging;
}

static void send_chg_status_event(void)
{
    struct chg_state_event evt = {
        .is_charging = is_charging,
    };
    zbus_chan_pub(&chg_state_data_chan, &evt, K_MSEC(250));
}

static void charger_status_work_cb(struct k_work *work)
{
    switch (chg_state) {
        case CHG_STATE_START: { // Work was scheduled to start a new detect
            if (gpio_pin_get_dt(&is_charging_pin) == 0) {
                // No need to detect, we are charging
                if (!is_charging) {
                    is_charging = true;
                    send_chg_status_event();
                    LOG_DBG("NO_CHARGE => CHARGE");
                }
                // Re-run detect again later
                chg_state = CHG_STATE_START;
                k_work_schedule(&charger_work, K_MSEC(CHECK_CHG_INTERVAL_MS));
            } else {
                chg_state = CHG_STATE_DETECTING;
                gpio_pin_interrupt_configure_dt(&is_charging_pin, GPIO_INT_EDGE_BOTH);
                k_work_schedule(&charger_work, K_MSEC(CHECK_CHG_INTERVAL_MS));
            }
            break;
        }
        case CHG_STATE_DETECTING: { // We started a detect, but the ISR did not trigger, hence not charging
            gpio_pin_interrupt_configure_dt(&is_charging_pin, GPIO_INT_DISABLE);
            if (is_charging) {
                is_charging = false;
                send_chg_status_event();
                LOG_DBG("CHARGE => NO CHARGE");
            }
            // Re-run detect again later
            chg_state = CHG_STATE_START;
            k_work_schedule(&charger_work, K_MSEC(CHECK_CHG_INTERVAL_MS));
            break;
        }
        case CHG_STATE_CHARGE_DETECTED: {
            if (!is_charging) {
                is_charging = true;
                send_chg_status_event();
                LOG_DBG("NO_CHARGE => CHARGE");
            }
            // Re-run detect again later
            chg_state = CHG_STATE_START;
            k_work_schedule(&charger_work, K_MSEC(CHECK_CHG_INTERVAL_MS));
            break;
        }
        default:
            __ASSERT(false, "STATE: %d unhandled!", chg_state);
    }
}

static void charger_status_chg_detected_isr(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    gpio_pin_interrupt_configure_dt(&is_charging_pin, GPIO_INT_DISABLE);
    chg_state = CHG_STATE_CHARGE_DETECTED;
}

static int charger_init(void)
{
    if (!device_is_ready(is_charging_pin.port)) {
        LOG_WRN("Charger status not supported on this board");
        return -ENODEV;
    }

    int rc = gpio_pin_configure_dt(&is_charging_pin, GPIO_INPUT | GPIO_PULL_UP);
    if (rc != 0) {
        LOG_ERR("Failed configure charger status GPIO");
    }

    gpio_init_callback(&gpio_charger_cb, charger_status_chg_detected_isr,  BIT(is_charging_pin.pin));
    rc = gpio_add_callback(is_charging_pin.port, &gpio_charger_cb);
    if (rc != 0) {
        LOG_ERR("Failed gpio_add_callback chg ISR: %d", rc);
    }

    chg_state = CHG_STATE_START;
    k_work_schedule(&charger_work, K_MSEC(1));
    return 0;
}

SYS_INIT(charger_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
