/* microcrystal_rv8263c8.c - Driver for Micro Crystal RV-8263-C8 RTC. */

/*
 * Copyright (c) 2024, Daniel Kampert
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "microcrystal_rv8263c8.h"
#include "private/microcrystal_rv8263c8_types.h"
#include "interrupt/microcrystal_rv8263c8_interrupt.h"

#define RV8263C8_REGISTER_CONTROL1          0x00
#define RV8263C8_REGISTER_CONTROL2          0x01
#define RV8263C8_REGISTER_OFFSET            0x02
#define RV8263C8_REGISTER_RAM               0x03
#define RV8263C8_REGISTER_SECONDS           0x04
#define RV8263C8_REGISTER_MINUTES           0x05
#define RV8263C8_REGISTER_HOURS             0x06
#define RV8263C8_REGISTER_DATE              0x07
#define RV8263C8_REGISTER_WEEKDAY           0x08
#define RV8263C8_REGISTER_MONTH             0x09
#define RV8263C8_REGISTER_YEAR              0x0A
#define RV8263C8_REGISTER_SECONDS_ALARM     0x0B
#define RV8263C8_REGISTER_MINUTES_ALARM     0x0C
#define RV8263C8_REGISTER_HOURS_ALARM       0x0D
#define RV8263C8_REGISTER_DATE_ALARM        0x0E
#define RV8263C8_REGISTER_WEEKDAY_ALARM     0x0F
#define RV8263C8_REGISTER_TIMER_VALUE       0x10
#define RV8263C8_REGISTER_TIMER_MODE        0x11

#define RV8263C8_24H_MODE_ENABLE            (0x00 << 0x01)
#define RV8263C8_24H_MODE_DISABLE           (0x00 << 0x01)
#define RV8263C8_CLOCK_ENABLE               (0x00 << 0x05)
#define RV8263C8_CLOCK_DISABLE              (0x01 << 0x05)
#define RV8263C8_ALARM_INT_ENABLE           (0x01 << 0x07)
#define RV8263C8_ALARM_INT_DISABLE          (0x00 << 0x05)
#define RV8263C8_MINUTE_INT_ENABLE          (0x01 << 0x05)
#define RV8263C8_MINUTE_INT_DISABLE         (0x00 << 0x05)
#define RV8263C8_HALF_MINUTE_INT_ENABLE     (0x01 << 0x04)
#define RV8263C8_HALF_MINUTE_INT_DISABLE    (0x00 << 0x04)
#define RV8263C8_ALARM_ENABLE               (0x00 << 0x07)
#define RV8263C8_ALARM_DISABLE              (0x01 << 0x07)
#define RV8263C8_SOFTWARE_RESET             (0x58)

#define SECONDS_BITS                        GENMASK(6, 0)
#define MINUTES_BITS                        GENMASK(7, 0)
#define HOURS_BITS                          GENMASK(5, 0)
#define DATE_BITS                           GENMASK(5, 0)
#define MONTHS_BITS                         GENMASK(4, 0)
#define WEEKDAY_BITS                        GENMASK(2, 0)
#define YEAR_BITS                           GENMASK(7, 0)
#define VALIDATE_24HR                       BIT(6)

#define MIN_SEC                             0
#define MAX_SEC                             59
#define MIN_MIN                             0
#define MAX_MIN                             59
#define MIN_HOUR                            0
#define MAX_HOUR                            23
#define MAX_WDAY                            7
#define MIN_WDAY                            1
#define MAX_MDAY                            31
#define MIN_MDAY                            1
#define MAX_MON                             12
#define MIN_MON                             1
#define MIN_YEAR_DIFF                       0 // YEAR - 1900 */
#define MAX_YEAR_DIFF                       99 // YEAR - 1999 */

#define DT_DRV_COMPAT                       microcrystal_rv_8263_c8

LOG_MODULE_REGISTER(microcrystal_rv8263c8, CONFIG_MICROCRYSTAL_RV_8263_C8_LOG_LEVEL);

static void rv8263c8_isr(const struct device *p_dev)
{
    struct rv8263c8_data *const dev_data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;
}

static int rv8263c8_set_time(const struct device *p_dev, const struct rtc_time *p_tm)
{
    int err;
    uint8_t regs[7];

    struct rv8263c8_data *data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    k_spinlock_key_t key = k_spin_lock(&data->lock);

    LOG_DBG("Set time: year = %u, mon = %u, mday = %u, wday = %u, hour = %u, min = %u, sec = %u",
            p_tm->tm_year, p_tm->tm_mon, p_tm->tm_mday, p_tm->tm_wday, p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec);

    regs[0] = bin2bcd(p_tm->tm_sec) & SECONDS_BITS;
    regs[1] = bin2bcd(p_tm->tm_min);
    regs[2] = bin2bcd(p_tm->tm_hour);
    regs[3] = bin2bcd(p_tm->tm_wday);
    regs[4] = bin2bcd(p_tm->tm_mday);
    regs[5] = bin2bcd(p_tm->tm_mon);
    regs[6] = bin2bcd((p_tm->tm_year % 100));

    err = i2c_burst_write_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS, regs, sizeof(regs));

    k_spin_unlock(&data->lock, key);

    return err;
}

static int rv8263c8_get_time(const struct device *p_dev, struct rtc_time *p_timeptr)
{
    int err;
    uint8_t regs[7];

    struct rv8263c8_data *data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    k_spinlock_key_t key = k_spin_lock(&data->lock);

    err = i2c_burst_read_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS, regs, sizeof(regs));
    if (err != 0) {
        goto rv8263c8_get_time_exit;
    }

    p_timeptr->tm_sec = bcd2bin(regs[0] & SECONDS_BITS);
    p_timeptr->tm_min = bcd2bin(regs[1] & MINUTES_BITS);
    p_timeptr->tm_hour = bcd2bin(regs[2] & HOURS_BITS);
    p_timeptr->tm_wday = bcd2bin(regs[3] & WEEKDAY_BITS);
    p_timeptr->tm_mday = bcd2bin(regs[4] & DATE_BITS);
    p_timeptr->tm_mon = bcd2bin(regs[5] & MONTHS_BITS);
    p_timeptr->tm_year = bcd2bin(regs[6] & YEAR_BITS);
    p_timeptr->tm_year = p_timeptr->tm_year + 100;

    // Unused
    p_timeptr->tm_nsec = 0;
    p_timeptr->tm_isdst = -1;
    p_timeptr->tm_yday = -1;

    // Validate the chip in 24hr mode
    if (regs[2] & VALIDATE_24HR) {
        err = -ENODATA;
        goto rv8263c8_get_time_exit;
    }

    LOG_DBG("get time: year = %d, mon = %d, mday = %d, wday = %d, hour = %d, min = %d, sec = %d",
            p_timeptr->tm_year, p_timeptr->tm_mon, p_timeptr->tm_mday, p_timeptr->tm_wday, p_timeptr->tm_hour, p_timeptr->tm_min,
            p_timeptr->tm_sec);

rv8263c8_get_time_exit:
    k_spin_unlock(&data->lock, key);

    return err;
}

static int rv8263c8_init(const struct device *p_dev)
{
    int err;
    struct rv8263c8_data *data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    if (!i2c_is_ready_dt(&config->i2c_bus)) {
        LOG_ERR("I2C bus not ready");
        return -ENODEV;
    }

    LOG_DBG("Configure RV-8263-C8:");
    LOG_DBG("	ClkOut: %u", config->clkout);
    LOG_DBG("	Fast Mode: %u", config->fast_mode);
    LOG_DBG("	Offset: %i", config->offset);

    k_spinlock_key_t key = k_spin_lock(&data->lock);

    // Configure the first config register
    err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_CONTROL1,
                                RV8263C8_24H_MODE_DISABLE | RV8263C8_CLOCK_ENABLE);
    if (err < 0) {
        LOG_ERR("Error while writing CONTROL1! Error: %i", err);
        goto rv8263c8_init_exit;
    }

    // Configure the second config register
    err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_CONTROL2,
                                RV8263C8_ALARM_INT_ENABLE | RV8263C8_MINUTE_INT_DISABLE | RV8263C8_HALF_MINUTE_INT_DISABLE | (config->clkout << 0x00));
    if (err < 0) {
        LOG_ERR("Error while writing CONTROL2! Error: %i", err);
        goto rv8263c8_init_exit;
    }

    // Configure the offset register
    err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_OFFSET,
                                config->fast_mode << 0x07 | (config->offset & 0x7F));
    if (err < 0) {
        LOG_ERR("Error while writing CONTROL2! Error: %i", err);
    }

    if (config->int_gpio.port) {
        if (rv8263c8_init_interrupt(p_dev)) {
            LOG_ERR("Could not initialize interrupts!");
            return -EFAULT;
        }
    }

rv8263c8_init_exit:
    k_spin_unlock(&data->lock, key);

    return err;
}

#ifdef CONFIG_RTC_ALARM
static bool rv8263c8_validate_alarm(const struct rtc_time *p_timeptr, uint32_t mask)
{
    if ((mask & RTC_ALARM_TIME_MASK_SECOND) &&
        (p_timeptr->tm_sec < MIN_SEC || p_timeptr->tm_sec > MAX_SEC)) {
        return false;
    }

    if ((mask & RTC_ALARM_TIME_MASK_MINUTE) &&
        (p_timeptr->tm_min < MIN_MIN || p_timeptr->tm_min > MAX_MIN)) {
        return false;
    }

    if ((mask & RTC_ALARM_TIME_MASK_HOUR) &&
        (p_timeptr->tm_hour < MIN_HOUR || p_timeptr->tm_hour > MAX_HOUR)) {
        return false;
    }

    return true;
}

static int rv8263c8_alarm_get_supported_fields(const struct device *p_dev, uint16_t id,
                                               uint16_t *p_mask)
{
    ARG_UNUSED(p_dev);

    if (id != 0) {
        return -EINVAL;
    }

    (*p_mask) = (RTC_ALARM_TIME_MASK_SECOND
                 | RTC_ALARM_TIME_MASK_MINUTE
                 | RTC_ALARM_TIME_MASK_HOUR);

    return 0;
}

static int rv8263c8_alarm_set_time(const struct device *p_dev, uint16_t id, uint16_t mask,
                                   const struct rtc_time *p_timeptr)
{
    int err;
    struct rv8263c8_data *const dev_data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    k_spinlock_key_t key = k_spin_lock(&dev_data->lock);

    if (id != 0) {
        err = -EINVAL;
        goto rv8263c8_alarm_set_time_exit;
    }

    if ((mask > 0) && (p_timeptr == NULL)) {
        err = -EINVAL;
        goto rv8263c8_alarm_set_time_exit;
    }

    // Check time valid
    if (!rv8263c8_validate_alarm(p_timeptr, mask)) {
        err = -EINVAL;
        goto rv8263c8_alarm_set_time_exit;
    }

    if (mask & RTC_ALARM_TIME_MASK_SECOND) {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS_ALARM,
                                    RV8263C8_ALARM_ENABLE | p_timeptr->tm_sec);
    } else {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS_ALARM, RV8263C8_ALARM_DISABLE);
    }

    if (err < 0) {
        LOG_ERR("Error while writing SECONDS alarm! Error: %i", err);
        goto rv8263c8_alarm_set_time_exit;
    }

    if (mask & RTC_ALARM_TIME_MASK_MINUTE) {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS_ALARM,
                                    RV8263C8_ALARM_ENABLE | p_timeptr->tm_min);
    } else {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS_ALARM, RV8263C8_ALARM_DISABLE);
    }

    if (err < 0) {
        LOG_ERR("Error while writing MINUTE alarm! Error: %i", err);
        goto rv8263c8_alarm_set_time_exit;
    }

    if (mask & RTC_ALARM_TIME_MASK_HOUR) {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS_ALARM,
                                    RV8263C8_ALARM_ENABLE | p_timeptr->tm_hour);
    } else {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS_ALARM, RV8263C8_ALARM_DISABLE);
    }

    if (err < 0) {
        LOG_ERR("Error while writing HOUR alarm! Error: %i", err);
        goto rv8263c8_alarm_set_time_exit;
    }

    err = i2c_reg_update_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_CONTROL2, 0x01 << 0x07, RV8263C8_ALARM_INT_ENABLE);
    if (err < 0) {
        LOG_ERR("Error while writing CONTROL2! Error: %i", err);
        goto rv8263c8_alarm_set_time_exit;
    }

    err = 0;

rv8263c8_alarm_set_time_exit:
    k_spin_unlock(&dev_data->lock, key);

    return err;
}

static int rv8263c8_alarm_get_time(const struct device *p_dev, uint16_t id, uint16_t *p_mask,
                                   struct rtc_time *p_timeptr)
{
    int err;
    struct rv8263c8_data *const dev_data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    rtc_alarm_callback cb;
    void *cb_data;
    rtc_update_callback update_cb;
    void *update_cb_data;
    uint8_t value;

    k_spinlock_key_t key = k_spin_lock(&dev_data->lock);

    if (id != 0) {
        err = -EINVAL;
        goto rv8263c8_alarm_get_time_exit;
    }

    if (p_timeptr == NULL) {
        err = -EINVAL;
        goto rv8263c8_alarm_get_time_exit;
    }

    (*p_mask) = 0;

    err = i2c_reg_read_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS_ALARM, &value);
    if (err < 0) {
        LOG_ERR("Error while reading SECONDS! Error: %i", err);
        goto rv8263c8_alarm_get_time_exit;
    }

    if (value <= MAX_SEC) {
        p_timeptr->tm_sec = value;
        (*p_mask) |= RTC_ALARM_TIME_MASK_SECOND;
    }

    err = i2c_reg_read_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_MINUTES_ALARM, &value);
    if (err < 0) {
        LOG_ERR("Error while reading MINUTES! Error: %i", err);
        goto rv8263c8_alarm_get_time_exit;
    }

    if (value <= MAX_MIN) {
        p_timeptr->tm_hour = value;
        (*p_mask) |= RTC_ALARM_TIME_MASK_MINUTE;
    }

    err = i2c_reg_read_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_HOURS_ALARM, &value);
    if (err < 0) {
        LOG_ERR("Error while reading SECONDS! Error: %i", err);
        goto rv8263c8_alarm_get_time_exit;
    }

    if (value <= MAX_HOUR) {
        p_timeptr->tm_hour = value;
        (*p_mask) |= RTC_ALARM_TIME_MASK_HOUR;
    }

    err = 0;

rv8263c8_alarm_get_time_exit:
    k_spin_unlock(&dev_data->lock, key);

    return err;
}

static int rv8263c8_alarm_set_callback(const struct device *p_dev, uint16_t id,
                                       rtc_alarm_callback callback, void *p_user_data)
{
    int err;
    struct rv8263c8_data *const dev_data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    if (id != 0) {
        return -EINVAL;
    }

    k_spinlock_key_t key = k_spin_lock(&dev_data->lock);

    dev_data->cb = callback;
    dev_data->cb_data = p_user_data;

    if (callback != NULL) {
        err = i2c_reg_update_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_CONTROL2, 0x01 << 0x07, RV8263C8_ALARM_INT_ENABLE);
    } else {
        err = i2c_reg_update_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_CONTROL2, 0x01 << 0x07, RV8263C8_ALARM_INT_DISABLE);
    }

    k_spin_unlock(&dev_data->lock, key);

    if (err < 0) {
        LOG_ERR("Error while writing CONTROL2! Error: %i", err);
        return err;
    }

    return 0;
}

static int rv8263c8_alarm_is_pending(const struct device *p_dev, uint16_t id)
{
    int ret;
    struct rv8263c8_data *const dev_data = p_dev->data;

    if (id != 0) {
        return -EINVAL;
    }

    k_spinlock_key_t key = k_spin_lock(&dev_data->lock);

    ret = dev_data->alarm_pending ? 1 : 0;
    dev_data->alarm_pending = false;

    k_spin_unlock(&dev_data->lock, key);

    return ret;
}
#endif

#ifdef CONFIG_RTC_UPDATE
static int rv8263c8_update_set_callback(const struct device *p_dev,
                                        rtc_update_callback callback, void *p_user_data)
{
    struct rv8263c8_data *const dev_data = p_dev->data;

#error Not supported

    k_spinlock_key_t key = k_spin_lock(&dev_data->lock);

    dev_data->update_cb = callback;
    dev_data->update_cb_data = p_user_data;

    if (callback != NULL) {
        // TODO: Enable
    } else {
        // TODO: Disable
    }

    k_spin_unlock(&dev_data->lock, key);

    return 0;
}
#endif

static const struct rtc_driver_api rv8263c8_driver_api = {
    .set_time = rv8263c8_set_time,
    .get_time = rv8263c8_get_time,
#ifdef CONFIG_RTC_ALARM
    .alarm_get_supported_fields = rv8263c8_alarm_get_supported_fields,
    .alarm_set_time = rv8263c8_alarm_set_time,
    .alarm_get_time = rv8263c8_alarm_get_time,
    .alarm_is_pending = rv8263c8_alarm_is_pending,
    .alarm_set_callback = rv8263c8_alarm_set_callback,
#endif

#ifdef CONFIG_RTC_UPDATE
    .update_set_callback = rv8263c8_update_set_callback,
#endif
};

#define RV_8263_C8_DEFINE(inst)                                                     \
    static struct rv8263c8_data rv8263c8_data_##inst;                               \
    static const struct rv8263c8_config rv8263c8_config_##inst = {                  \
        .i2c_bus = I2C_DT_SPEC_INST_GET(inst),                                      \
        .clkout = DT_INST_PROP(inst, clkout),                                       \
        .fast_mode = DT_INST_PROP(inst, fast_mode),                                 \
        .offset = DT_INST_PROP(inst, offset),                                       \
        IF_ENABLED(CONFIG_BMI270_PLUS_TRIGGER,                                      \
            (.int_gpio = GPIO_DT_SPEC_INST_GET_OR(inst, int_gpios, { 0 }),))        \
    };                                                                              \
    DEVICE_DT_INST_DEFINE(inst, &rv8263c8_init, NULL, &rv8263c8_data_##inst,        \
                  &rv8263c8_config_##inst, POST_KERNEL, CONFIG_RTC_INIT_PRIORITY,   \
                  &rv8263c8_driver_api);

DT_INST_FOREACH_STATUS_OKAY(RV_8263_C8_DEFINE)