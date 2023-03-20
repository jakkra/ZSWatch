#include <pressure_sensor.h>
#include <bmp5_port.h>
#include <bmp5.h>
#include <zephyr/logging/log.h>
#include <events/pressure_event.h>
#include <zephyr/zbus/zbus.h>

LOG_MODULE_REGISTER(bmp581_pressure, LOG_LEVEL_DBG);

ZBUS_CHAN_DECLARE(pressure_data_chan);

static int8_t set_config(struct bmp5_osr_odr_press_config *osr_odr_press_cfg, struct bmp5_dev *dev);
static int bmp581_init_interrupt(void);
static void bmp581_work_cb(struct k_work *work);

static struct bmp5_dev bmp5_dev;
static struct bmp5_osr_odr_press_config osr_odr_press_cfg = { 0 };

// Assumes only one sensor
static const struct gpio_dt_spec int_gpio = GPIO_DT_SPEC_GET(DT_NODELABEL(bmp581), int_gpios);
static K_WORK_DEFINE(int_work, bmp581_work_cb);
static struct gpio_callback gpio_cb;

int pressure_sensor_init(void)
{
    int8_t rslt;

    rslt = bmp5_interface_init(&bmp5_dev, BMP5_I2C_INTF);
    bmp5_error_codes_print_result("bmp5_interface_init", rslt);

    if (rslt == BMP5_OK) {
        rslt = bmp5_init(&bmp5_dev);
        if (rslt == BMP5_E_POWER_UP) {
            // Fails when expecting BMP5_INT_ASSERTED_POR_SOFTRESET_COMPLETE
            // being set, but it's not. Can't see any actual reset being made.
            // For now ignore, works anyway.
            // Do a soft reset just in case.
            rslt = bmp5_soft_reset(&bmp5_dev);

        }
        bmp5_error_codes_print_result("bmp5_init", rslt);

        if (rslt == BMP5_OK) {
            rslt = set_config(&osr_odr_press_cfg, &bmp5_dev);
            bmp5_error_codes_print_result("set_config", rslt);
        }

        if (rslt == BMP5_OK) {
            if (int_gpio.port) {
                if (bmp581_init_interrupt() < 0) {
                    LOG_DBG("Could not initialize interrupts");
                    return -EIO;
                }
            }
        }
    }

    return rslt == BMP5_OK ? 0 : -EIO;
}

int pressure_sensor_set_odr(uint8_t bmp5_odr)
{
    /* Get default odr */
    uint8_t rslt = bmp5_get_osr_odr_press_config(&osr_odr_press_cfg, &bmp5_dev);
    bmp5_error_codes_print_result("bmp5_get_osr_odr_press_config", rslt);

    if (rslt == BMP5_OK) {
        /* Set ODR as 50Hz */
        osr_odr_press_cfg.odr = bmp5_odr;

        /* Enable pressure */
        osr_odr_press_cfg.press_en = BMP5_ENABLE;

        /* Set Over-sampling rate with respect to odr */
        osr_odr_press_cfg.osr_t = BMP5_OVERSAMPLING_64X;
        osr_odr_press_cfg.osr_p = BMP5_OVERSAMPLING_4X;

        rslt = bmp5_set_osr_odr_press_config(&osr_odr_press_cfg, &bmp5_dev);
        bmp5_error_codes_print_result("bmp5_set_osr_odr_press_config", rslt);
    }
    return rslt == BMP5_OK ? 0 : -EIO;
}

int pressure_sensor_fetch_pressure(float *pressure, float *temperature)
{
    int8_t rslt = 0;
    uint8_t idx = 0;
    struct bmp5_sensor_data sensor_data;

    rslt = bmp5_get_sensor_data(&sensor_data, &osr_odr_press_cfg, &bmp5_dev);
    bmp5_error_codes_print_result("bmp5_get_sensor_data", rslt);

    if (rslt == BMP5_OK) {
        printf("%d, %f, %f\n", idx, sensor_data.pressure, sensor_data.temperature);
        *pressure = sensor_data.pressure;
        *temperature = sensor_data.temperature;
    }

    return rslt == BMP5_OK ? 0 : -EIO;
}

static inline void setup_int1(bool enable)
{
    gpio_pin_interrupt_configure_dt(&int_gpio,
                                    (enable ? GPIO_INT_EDGE_TO_ACTIVE : GPIO_INT_DISABLE));
}

static void bmp581_gpio_callback(const struct device *dev,
                                 struct gpio_callback *cb, uint32_t pins)
{
    ARG_UNUSED(pins);

    setup_int1(false);
    k_work_submit(&int_work);
}

static void bmp581_work_cb(struct k_work *work)
{
    int8_t rslt = 0;
    uint8_t int_status;
    struct bmp5_sensor_data sensor_data;

    printf("\nOutput :\n\n");
    printf("Data, Pressure (Pa), Temperature (deg C)\n");

    rslt = bmp5_get_interrupt_status(&int_status, &bmp5_dev);
    bmp5_error_codes_print_result("bmp5_get_interrupt_status", rslt);

    if (int_status & BMP5_INT_ASSERTED_DRDY) {
        rslt = bmp5_get_sensor_data(&sensor_data, &osr_odr_press_cfg, &bmp5_dev);
        bmp5_error_codes_print_result("bmp5_get_sensor_data", rslt);

        if (rslt == BMP5_OK) {
            struct pressure_event evt = {
                .pressure = sensor_data.pressure,
                .temperature = sensor_data.temperature
            };
            zbus_chan_pub(&pressure_data_chan, &evt, K_MSEC(250));
        }
    }

    setup_int1(true);
}

static int bmp581_init_interrupt(void)
{
    /* setup data ready gpio interrupt */
    if (!device_is_ready(int_gpio.port)) {
        LOG_ERR("GPIO device not ready");
        return -ENODEV;
    }

    gpio_pin_configure_dt(&int_gpio, GPIO_INPUT);

    gpio_init_callback(&gpio_cb,
                       bmp581_gpio_callback,
                       BIT(int_gpio.pin));

    if (gpio_add_callback(int_gpio.port, &gpio_cb) < 0) {
        LOG_DBG("Could not set gpio callback");
        return -EIO;
    }

    setup_int1(true);

    return 0;
}

static int8_t set_config(struct bmp5_osr_odr_press_config *osr_odr_press_cfg, struct bmp5_dev *dev)
{
    int8_t rslt;
    struct bmp5_iir_config set_iir_cfg;
    struct bmp5_int_source_select int_source_select;

    rslt = bmp5_set_power_mode(BMP5_POWERMODE_STANDBY, dev);
    bmp5_error_codes_print_result("bmp5_set_power_mode1", rslt);

    if (rslt == BMP5_OK) {
        /* Get default odr */
        rslt = bmp5_get_osr_odr_press_config(osr_odr_press_cfg, dev);
        bmp5_error_codes_print_result("bmp5_get_osr_odr_press_config", rslt);

        if (rslt == BMP5_OK) {
            /* Set ODR as 50Hz */
            osr_odr_press_cfg->odr = BMP5_ODR_0_250_HZ;

            /* Enable pressure */
            osr_odr_press_cfg->press_en = BMP5_ENABLE;

            /* Set Over-sampling rate with respect to odr */
            osr_odr_press_cfg->osr_t = BMP5_OVERSAMPLING_64X;
            osr_odr_press_cfg->osr_p = BMP5_OVERSAMPLING_4X;

            rslt = bmp5_set_osr_odr_press_config(osr_odr_press_cfg, dev);
            bmp5_error_codes_print_result("bmp5_set_osr_odr_press_config", rslt);
        }

        if (rslt == BMP5_OK) {
            set_iir_cfg.set_iir_t = BMP5_IIR_FILTER_COEFF_63;
            set_iir_cfg.set_iir_p = BMP5_IIR_FILTER_COEFF_63;
            set_iir_cfg.shdw_set_iir_t = BMP5_ENABLE;
            set_iir_cfg.shdw_set_iir_p = BMP5_ENABLE;

            rslt = bmp5_set_iir_config(&set_iir_cfg, dev);
            bmp5_error_codes_print_result("bmp5_set_iir_config", rslt);
        }

        if (rslt == BMP5_OK) {
            rslt = bmp5_configure_interrupt(BMP5_PULSED, BMP5_ACTIVE_LOW, BMP5_INTR_OPEN_DRAIN, BMP5_INTR_ENABLE, dev);
            bmp5_error_codes_print_result("bmp5_configure_interrupt", rslt);

            if (rslt == BMP5_OK) {
                /* Note : Select INT_SOURCE after configuring interrupt */
                int_source_select.drdy_en = BMP5_ENABLE;
                rslt = bmp5_int_source_select(&int_source_select, dev);
                bmp5_error_codes_print_result("bmp5_int_source_select", rslt);
            }
        }

        /* Set powermode as normal */
        rslt = bmp5_set_power_mode(BMP5_POWERMODE_NORMAL, dev);
        bmp5_error_codes_print_result("bmp5_set_power_mode", rslt);
    }

    return rslt;
}
