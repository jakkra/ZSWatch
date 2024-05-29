/* microcrystal_rv8263c8.c - Driver for Micro Crystal RV-8263-C8 RTC.
 *
 * Copyright (c) 2024 Daniel Kampert
 * Author: Daniel Kampert <DanielKampert@kampis-Elektroecke.de>
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/rtc.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/byteorder.h>

#define RV8263C8_REGISTER_CONTROL_1         0x00
#define RV8263C8_REGISTER_CONTROL_2         0x01
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

#define RV8263C8_BM_24H_MODE_ENABLE         (0x00 << 1)
#define RV8263C8_BM_24H_MODE_DISABLE        (0x00 << 1)
#define RV8263C8_BM_CLOCK_ENABLE            (0x00 << 5)
#define RV8263C8_BM_CLOCK_DISABLE           (0x01 << 5)
#define RV8263C8_BM_ALARM_INT_ENABLE        (0x01 << 7)
#define RV8263C8_BM_ALARM_INT_DISABLE       (0x00 << 7)
#define RV8263C8_BM_MINUTE_INT_ENABLE       (0x01 << 5)
#define RV8263C8_BM_MINUTE_INT_DISABLE      (0x00 << 5)
#define RV8263C8_BM_HALF_MINUTE_INT_ENABLE  (0x01 << 4)
#define RV8263C8_BM_HALF_MINUTE_INT_DISABLE (0x00 << 4)
#define RV8263C8_BM_ALARM_ENABLE            (0x00 << 7)
#define RV8263C8_BM_ALARM_DISABLE           (0x01 << 7)
#define RV8263C8_BM_AF                      (0x01 << 6)
#define RV8263C8_BM_TF                      (0x01 << 3)
#define RV8263_BM_MODE                      (0x01 << 7)
#define RV8263C8_BM_SOFTWARE_RESET          (0x58)

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

#if defined(CONFIG_RTC_ALARM) || defined(CONFIG_RTC_UPDATE)
#define RV8263_USE_INT                      1
/**
 * @brief RV-8263-C8 "int_gpios" property must be in the devicetree in order to use the RTC_ALARM or RTC_UPDATE feature.
 */
#if !DT_ANY_INST_HAS_PROP_STATUS_OKAY(int_gpios)
#error int-gpios property not available in devicetree!
#endif
#endif

#ifdef CONFIG_RTC_CALIBRATION
/**
 * @brief RV-8263-C8 "offset" property must be in the devicetree in order to use the RTC_CALIBRATION feature.
 */
#if !DT_ANY_INST_HAS_PROP_STATUS_OKAY(offset)
#error offset-property not available in devicetree!
#endif
#endif

#ifdef CONFIG_RTC_CALIBRATION
/**
 * @brief RV-8263-C8 "fast_mode" property must be in the devicetree in order to use the RTC_CALIBRATION feature.
 */
#if !DT_ANY_INST_HAS_PROP_STATUS_OKAY(fast_mode)
#error fast-mode-property not available in devicetree!
#endif
#endif

LOG_MODULE_REGISTER(microcrystal_rv8263c8, CONFIG_RTC_LOG_LEVEL);

struct rv8263c8_config {
    struct i2c_dt_spec i2c_bus;
    uint8_t clkout;
    bool fast_mode;
    int8_t offset;

#if defined(CONFIG_RTC_ALARM) || defined(CONFIG_RTC_UPDATE)
    struct gpio_dt_spec int_gpio;
#endif
};

struct rv8263c8_data {
    struct k_spinlock lock;

#if defined(CONFIG_RTC_RV8263_ALARM_GLOBAL_THREAD) || defined(CONFIG_RTC_RV8263_UPDATE_GLOBAL_THREAD)
    const struct device *dev;
#endif

#if defined(CONFIG_RTC_ALARM) || defined(CONFIG_RTC_UPDATE)
    struct gpio_callback gpio_cb;
#endif

#ifdef CONFIG_RTC_ALARM
    rtc_alarm_callback alarm_cb;
    void *alarm_cb_data;
    bool is_alarm_pending;

#if defined(CONFIG_RTC_RV8263_ALARM_OWN_THREAD)
    struct k_sem alarm_sem;
#elif defined(CONFIG_RTC_RV8263_ALARM_GLOBAL_THREAD)
    struct k_work alarm_work;
#endif
#endif

#ifdef CONFIG_RTC_UPDATE
    rtc_update_callback update_cb;
    void *update_cb_data;

#if defined(CONFIG_RTC_RV8263_UPDATE_OWN_THREAD)
    struct k_sem update_sem;
#elif defined(CONFIG_RTC_RV8263_UPDATE_GLOBAL_THREAD)
    struct k_work update_work;
#endif
#endif
};

#ifdef CONFIG_RTC_RV8263_ALARM_OWN_THREAD
static K_KERNEL_STACK_MEMBER(rv8263c8_alarm_stack, CONFIG_RTC_RV8263_ALARM_THREAD_STACK_SIZE);
static struct k_thread rv8263c8_alarm_thread;
#endif

#ifdef CONFIG_RTC_RV8263_UPDATE_OWN_THREAD
static K_KERNEL_STACK_MEMBER(rv8263c8_update_stack, CONFIG_RTC_RV8263_UPDATE_THREAD_STACK_SIZE);
static struct k_thread rv8263c8_update_thread;
#endif

#if defined(CONFIG_RTC_ALARM) || defined(CONFIG_RTC_UPDATE)
/**
 * @brief
 *
 * @param p_port
 * @param p_cb
 * @param pins
 */
static void rv8263c8_gpio_callback_handler(const struct device *p_port, struct gpio_callback *p_cb,
    gpio_port_pins_t pins)
{
    ARG_UNUSED(pins);
    ARG_UNUSED(p_port);

    struct rv8263c8_data *data = CONTAINER_OF(p_cb, struct rv8263c8_data, gpio_cb);

#if defined(CONFIG_RTC_RV8263_ALARM_OWN_THREAD)
    k_sem_give(&data->alarm_sem);
#elif defined(CONFIG_RTC_RV8263_ALARM_GLOBAL_THREAD)
    k_work_submit(&data->alarm_work);
#endif

#if defined(CONFIG_RTC_RV8263_UPDATE_OWN_THREAD)
    k_sem_give(&data->update_sem);
#elif defined(CONFIG_RTC_RV8263_UPDATE_GLOBAL_THREAD)
    k_work_submit(&data->update_work);
#endif
}
#endif

#ifdef CONFIG_RTC_ALARM
/**
 * @brief
 *
 * @param p_dev
 */
static void rv8263_process_alarm(const struct device *p_dev)
{
    struct rv8263c8_data *data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    data->is_alarm_pending = true;

    if (data->alarm_cb != NULL) {
        LOG_DBG("Calling alarm callback");
        data->alarm_cb(p_dev, 0, data->alarm_cb_data);
    }

    i2c_reg_update_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_CONTROL_2, RV8263C8_BM_AF, RV8263C8_BM_AF);
}

#if defined(CONFIG_RTC_RV8263_ALARM_OWN_THREAD)
/**
 * @brief
 *
 * @param p_arg1
 * @param p_arg2
 * @param p_arg3
 */
static void rv8263c8_alarm_thread_func(void *p_arg1, void *p_arg2, void *p_arg3)
{
    const struct device *dev = p_arg1;
    struct rv8263c8_data *data = dev->data;

    while (1) {
        k_sem_take(&data->alarm_sem, K_FOREVER);
        rv8263_process_alarm(dev);
    }
}
#elif defined(CONFIG_RTC_RV8263_UPDATE_GLOBAL_THREAD)
/**
 * @brief
 *
 * @param p_work
 */
static void rv8263c8_alarm_worker(struct k_work *p_work)
{
    struct rv8263c8_data *data = CONTAINER_OF(p_work, struct rv8263c8_data, alarm_work);

    LOG_DBG("Process alarm interrupt from worker");

    rv8263_process_alarm(data->dev);
}
#endif
#endif

/**
 * @brief
 *
 * @param p_timeptr
 * @param mask
 * @return true
 * @return false
 */
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
#endif

#ifdef CONFIG_RTC_UPDATE
/**
 * @brief           This function configures and enables the countdown timer.
 *
 * @param p_dev     Pointer to device strucure
 * @return int      0 when successful
 */
static int rv8263c8_update_enable_timer(const struct device *p_dev)
{
    int err;
    uint8_t regs;
    struct rv8263c8_data *data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    if (p_dev == NULL) {
        return -EINVAL;
    }

    regs = 0;
    k_spinlock_key_t key = k_spin_lock(&data->lock);
    err = i2c_burst_write_dt(&config->i2c_bus, RV8263C8_REGISTER_TIMER_VALUE, &regs, sizeof(regs));
    if (err < 0) {
        goto rv8263c8_update_enable_timer_exit;
    }

    // Configure the countdown timer for 1 Hz and enable pulse interrupts.
    regs = (0x02 << 3) | (0x01 << 2) | (0x01 << 1) | (0x01 << 0);
    err = i2c_burst_write_dt(&config->i2c_bus, RV8263C8_REGISTER_TIMER_MODE, &regs, sizeof(regs));

rv8263c8_update_enable_timer_exit:
    k_spin_unlock(&data->lock, key);

    return err;
}

/**
 * @brief
 *
 * @param p_dev
 */
static void rv8263_process_update(const struct device *p_dev)
{
    struct rv8263c8_data *data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    if (data->update_cb != NULL) {
        LOG_DBG("Calling update callback");
        data->update_cb(p_dev, data->update_cb_data);
    }

    rv8263c8_update_enable_timer(p_dev);
    i2c_reg_update_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_CONTROL_2, RV8263C8_BM_TF, RV8263C8_BM_TF);
}

#if defined(CONFIG_RTC_RV8263_UPDATE_OWN_THREAD)
/**
 * @brief
 *
 * @param p_arg1
 * @param p_arg2
 * @param p_arg3
 */
static void rv8263c8_update_thread_func(void *p_arg1, void *p_arg2, void *p_arg3)
{
    const struct device *dev = p_arg1;
    struct rv8263c8_data *data = dev->data;

    while (1) {
        k_sem_take(&data->update_sem, K_FOREVER);
        rv8263_process_update(dev);
    }
}
#elif defined(CONFIG_RTC_RV8263_UPDATE_GLOBAL_THREAD)
/**
 * @brief
 *
 * @param p_work
 */
static void rv8263c8_update_worker(struct k_work *p_work)
{
    struct rv8263c8_data *data = CONTAINER_OF(p_work, struct rv8263c8_data, alarm_work);

    LOG_DBG("Process update interrupt from worker");

    rv8263_process_update(data->dev);
}
#endif
#endif

/**
 * @brief           Set time function for RTC API.
 *
 * @param p_dev     Pointer to device strucure
 * @param p_timeptr
 * @return int      0 when successful
 */
static int rv8263c8_time_set(const struct device *p_dev, const struct rtc_time *p_timeptr)
{
    int err;
    uint8_t regs[7];
    struct rv8263c8_data *data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    if ((p_dev == NULL) || (p_timeptr == NULL)) {
        return -EINVAL;
    }

    LOG_DBG("Set time: year = %u, mon = %u, mday = %u, wday = %u, hour = %u, min = %u, sec = %u",
            p_timeptr->tm_year, p_timeptr->tm_mon, p_timeptr->tm_mday, p_timeptr->tm_wday, p_timeptr->tm_hour, p_timeptr->tm_min,
            p_timeptr->tm_sec);

    regs[0] = bin2bcd(p_timeptr->tm_sec) & SECONDS_BITS;
    regs[1] = bin2bcd(p_timeptr->tm_min);
    regs[2] = bin2bcd(p_timeptr->tm_hour);
    regs[3] = bin2bcd(p_timeptr->tm_wday);
    regs[4] = bin2bcd(p_timeptr->tm_mday);
    regs[5] = bin2bcd(p_timeptr->tm_mon);
    regs[6] = bin2bcd((p_timeptr->tm_year % 100));

    k_spinlock_key_t key = k_spin_lock(&data->lock);
    err = i2c_burst_write_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS, regs, sizeof(regs));
    k_spin_unlock(&data->lock, key);

    return err;
}

/**
 * @brief           Get time function for RTC API.
 *
 * @param p_dev     Pointer to device strucure
 * @param p_timeptr
 * @return int      0 when successful
 */
static int rv8263c8_time_get(const struct device *p_dev, struct rtc_time *p_timeptr)
{
    int err;
    uint8_t regs[7];
    struct rv8263c8_data *data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    if ((p_dev == NULL) || (p_timeptr == NULL)) {
        return -EINVAL;
    }

    k_spinlock_key_t key = k_spin_lock(&data->lock);
    err = i2c_burst_read_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS, regs, sizeof(regs));
    k_spin_unlock(&data->lock, key);
    if (err < 0) {
        return err;
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
        return -ENODATA;
    }

    LOG_DBG("get time: year = %u, mon = %u, mday = %u, wday = %u, hour = %u, min = %u, sec = %u",
            p_timeptr->tm_year, p_timeptr->tm_mon, p_timeptr->tm_mday, p_timeptr->tm_wday, p_timeptr->tm_hour, p_timeptr->tm_min,
            p_timeptr->tm_sec);

    return 0;
}

/**
 * @brief           Init function for RTC API.
 *
 * @param p_dev     Pointer to device strucure
 * @return int      0 when successful
 */
static int rv8263c8_init(const struct device *p_dev)
{
    int err;
    int temp;
    struct rv8263c8_data *data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    if (p_dev == NULL) {
        return -EINVAL;
    }

    if (!i2c_is_ready_dt(&config->i2c_bus)) {
        LOG_ERR("I2C bus not ready!");
        return -ENODEV;
    }

    LOG_DBG("Configure RV-8263-C8:");
    LOG_DBG("	ClkOut: %u", config->clkout);
    LOG_DBG("	Fast Mode: %u", config->fast_mode);
    LOG_DBG("	Offset: %i", config->offset);

    k_spinlock_key_t key = k_spin_lock(&data->lock);

    // Configure the first config register
    err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_CONTROL_1,
                                RV8263C8_BM_24H_MODE_DISABLE | RV8263C8_BM_CLOCK_ENABLE);
    if (err < 0) {
        LOG_ERR("Error while writing CONTROL_1! Error: %i", err);
        goto rv8263c8_init_exit;
    }

#ifdef CONFIG_RTC_CALIBRATION
    err = i2c_reg_update_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_OFFSET, RV8263_BM_MODE, config->fast_mode << 7);
    if (err < 0) {
        LOG_ERR("Error while setting OFFSET mode! Error: %i", err);
        goto rv8263c8_init_exit;
    }
#endif

    // Configure the second config register
    temp = RV8263C8_BM_MINUTE_INT_DISABLE | RV8263C8_BM_HALF_MINUTE_INT_DISABLE | (config->clkout << 0x00);

#ifdef CONFIG_RTC_ALARM
    temp |= RV8263C8_BM_ALARM_INT_ENABLE;
#endif
    err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_CONTROL_2, temp);
    if (err < 0) {
        LOG_ERR("Error while writing CONTROL_2! Error: %i", err);
        goto rv8263c8_init_exit;
    }

#ifdef CONFIG_RTC_UPDATE
    uint8_t regs = 0;
    err = i2c_burst_write_dt(&config->i2c_bus, RV8263C8_REGISTER_TIMER_MODE, &regs, sizeof(regs));
    if (err < 0) {
        LOG_ERR("Error while writing CONTROL2! Error: %i", err);
        goto rv8263c8_init_exit;
    }
#endif

#if defined(CONFIG_RTC_ALARM) || defined(CONFIG_RTC_UPDATE)
    if (!gpio_is_ready_dt(&config->int_gpio)) {
        LOG_ERR("GPIO not ready!");
        goto rv8263c8_init_exit;
    }

    err = gpio_pin_configure_dt(&config->int_gpio, GPIO_INPUT);
    if (err < 0) {
        LOG_ERR("Failed to configure GPIO! Error: %u", err);
        goto rv8263c8_init_exit;
    }

    err = gpio_pin_interrupt_configure_dt(&config->int_gpio, GPIO_INT_EDGE_TO_INACTIVE);
    if (err < 0) {
        LOG_ERR("Failed to configure interrupt! Error: %u", err);
        goto rv8263c8_init_exit;
    }

    gpio_init_callback(&data->gpio_cb, rv8263c8_gpio_callback_handler, BIT(config->int_gpio.pin));

    err = gpio_add_callback_dt(&config->int_gpio, &data->gpio_cb);
    if (err < 0) {
        LOG_ERR("Failed to add GPIO callback! Error: %u", err);
        goto rv8263c8_init_exit;
    }
#endif

#ifdef CONFIG_RTC_ALARM
#if defined(CONFIG_RTC_RV8263_ALARM_OWN_THREAD)
    k_sem_init(&data->alarm_sem, 0, K_SEM_MAX_LIMIT);
    k_thread_create(&rv8263c8_alarm_thread, rv8263c8_alarm_stack,
                    K_THREAD_STACK_SIZEOF(rv8263c8_alarm_stack),
                    rv8263c8_alarm_thread_func, (struct device *)p_dev, NULL,
                    NULL, CONFIG_RTC_RV8263_ALARM_THREAD_PRIORITY, 0, K_NO_WAIT);
#elif defined(CONFIG_RTC_RV8263_ALARM_GLOBAL_THREAD)
    data->alarm_work.handler = rv8263c8_alarm_worker;
#endif
#endif

#ifdef CONFIG_RTC_UPDATE
#if defined(CONFIG_RTC_RV8263_UPDATE_OWN_THREAD)
    k_sem_init(&data->update_sem, 0, K_SEM_MAX_LIMIT);
    k_thread_create(&rv8263c8_update_thread, rv8263c8_update_stack,
                    K_THREAD_STACK_SIZEOF(rv8263c8_update_stack),
                    rv8263c8_update_thread_func, (struct device *)p_dev, NULL,
                    NULL, CONFIG_RTC_RV8263_UPDATE_THREAD_PRIORITY, 0, K_NO_WAIT);
#elif defined(CONFIG_RTC_RV8263_UPDATE_GLOBAL_THREAD)
    data->update_work.handler = rv8263c8_update_worker;
#endif
#endif

#if defined(CONFIG_RTC_RV8263_ALARM_GLOBAL_THREAD) || defined(CONFIG_RTC_RV8263_UPDATE_GLOBAL_THREAD)
    data->dev = p_dev;
#endif

rv8263c8_init_exit:
    k_spin_unlock(&data->lock, key);
    return err;
}

#ifdef CONFIG_RTC_ALARM
/**
 * @brief
 *
 * @param p_dev     Pointer to device strucure
 * @param id
 * @param p_mask
 * @return int      0 when successful
 */
static int rv8263c8_alarm_get_supported_fields(const struct device *p_dev, uint16_t id,
    uint16_t *p_mask)
{
    ARG_UNUSED(p_dev);

    if ((p_dev == NULL) || (id != 0)) {
        return -EINVAL;
    }

    (*p_mask) = (RTC_ALARM_TIME_MASK_SECOND | RTC_ALARM_TIME_MASK_MINUTE | RTC_ALARM_TIME_MASK_HOUR |
                 RTC_ALARM_TIME_MASK_MONTHDAY | RTC_ALARM_TIME_MASK_WEEKDAY);

    return 0;
}

/**
 * @brief
 *
 * @param p_dev     Pointer to device strucure
 * @param id
 * @param mask
 * @param p_timeptr
 * @return int      0 when successful
 */
static int rv8263c8_alarm_set_time(const struct device *p_dev, uint16_t id, uint16_t mask,
                                   const struct rtc_time *p_timeptr)
{
    int err;
    struct rv8263c8_data *const data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    if ((p_dev == NULL) || (p_timeptr == NULL) || (id != 0) || ((mask > 0) && (p_timeptr == NULL))) {
        return -EINVAL;
    }

    k_spinlock_key_t key = k_spin_lock(&data->lock);

    // Check time valid
    if (!rv8263c8_validate_alarm(p_timeptr, mask)) {
        return -EINVAL;
    }

    if (mask & RTC_ALARM_TIME_MASK_SECOND) {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS_ALARM,
                                    RV8263C8_BM_ALARM_ENABLE | p_timeptr->tm_sec);
    } else {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS_ALARM, RV8263C8_BM_ALARM_DISABLE);
    }

    if (err < 0) {
        LOG_ERR("Error while writing SECONDS alarm! Error: %i", err);
        goto rv8263c8_alarm_set_time_exit;
    }

    if (mask & RTC_ALARM_TIME_MASK_MINUTE) {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_MINUTES_ALARM,
                                    RV8263C8_BM_ALARM_ENABLE | p_timeptr->tm_min);
    } else {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_MINUTES_ALARM, RV8263C8_BM_ALARM_DISABLE);
    }

    if (err < 0) {
        LOG_ERR("Error while writing MINUTE alarm! Error: %i", err);
        goto rv8263c8_alarm_set_time_exit;
    }

    if (mask & RTC_ALARM_TIME_MASK_HOUR) {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_HOURS_ALARM,
                                    RV8263C8_BM_ALARM_ENABLE | p_timeptr->tm_hour);
    } else {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_HOURS_ALARM, RV8263C8_BM_ALARM_DISABLE);
    }

    if (err < 0) {
        LOG_ERR("Error while writing HOUR alarm! Error: %i", err);
        goto rv8263c8_alarm_set_time_exit;
    }

    if (mask & RTC_ALARM_TIME_MASK_MONTHDAY) {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_DATE_ALARM,
                                    RV8263C8_BM_ALARM_ENABLE | p_timeptr->tm_mday);
    } else {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_DATE_ALARM, RV8263C8_BM_ALARM_DISABLE);
    }

    if (err < 0) {
        LOG_ERR("Error while writing MONTHDAY alarm! Error: %i", err);
        goto rv8263c8_alarm_set_time_exit;
    }

    if (mask & RTC_ALARM_TIME_MASK_WEEKDAY) {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_WEEKDAY_ALARM,
                                    RV8263C8_BM_ALARM_ENABLE | p_timeptr->tm_wday);
    } else {
        err = i2c_reg_write_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_WEEKDAY_ALARM, RV8263C8_BM_ALARM_DISABLE);
    }

    if (err < 0) {
        LOG_ERR("Error while writing WEEKDAY alarm! Error: %i", err);
        goto rv8263c8_alarm_set_time_exit;
    }

rv8263c8_alarm_set_time_exit:
    k_spin_unlock(&data->lock, key);

    return err;
}

/**
 * @brief
 *
 * @param p_dev     Pointer to device strucure
 * @param id
 * @param p_mask
 * @param p_timeptr
 * @return int      0 when successful
 */
static int rv8263c8_alarm_get_time(const struct device *p_dev, uint16_t id, uint16_t *p_mask,
                                   struct rtc_time *p_timeptr)
{
    struct rv8263c8_data *const data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;
    uint8_t value[5];

    if ((p_dev == NULL) || (p_timeptr == NULL) || (id != 0)) {
        return -EINVAL;
    }

    (*p_mask) = 0;

    k_spinlock_key_t key = k_spin_lock(&data->lock);
    err = i2c_burst_read_dt(&config->i2c_bus, RV8263C8_REGISTER_SECONDS_ALARM, value, sizeof(value));
    k_spin_unlock(&data->lock, key);

    if (err < 0) {
        LOG_ERR("Error while reading alarm! Error: %i", err);
        return err;
    }

    if (value[0] <= MAX_SEC) {
        p_timeptr->tm_sec = value[0];
        (*p_mask) |= RTC_ALARM_TIME_MASK_SECOND;
    }

    if (value[1] <= MAX_MIN) {
        p_timeptr->tm_min = value[1];
        (*p_mask) |= RTC_ALARM_TIME_MASK_MINUTE;
    }

    if (value[2] <= MAX_HOUR) {
        p_timeptr->tm_hour = value[2];
        (*p_mask) |= RTC_ALARM_TIME_MASK_HOUR;
    }

    if (value[3] <= MAX_MDAY) {
        p_timeptr->tm_mday = value[3];
        (*p_mask) |= RTC_ALARM_TIME_MASK_MONTHDAY;
    }

    if (value[4] <= MAX_WDAY) {
        p_timeptr->tm_hour = value[4];
        (*p_mask) |= RTC_ALARM_TIME_MASK_WEEKDAY;
    }

    return 0;
}

/**
 * @brief
 *
 * @param p_dev         Pointer to device strucure
 * @param id
 * @param callback      RTC Alarm callback
 * @param p_user_data   Pointer to user data for alarm callback
 * @return int          0 when successful
 */
static int rv8263c8_alarm_set_callback(const struct device *p_dev, uint16_t id,
                                       rtc_alarm_callback callback, void *p_user_data)
{
    int err;
    struct rv8263c8_data *const data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    if ((p_dev == NULL) || (id != 0)) {
        return -EINVAL;
    }

    k_spinlock_key_t key = k_spin_lock(&data->lock);

    data->alarm_cb = callback;
    data->alarm_cb_data = p_user_data;

    if (callback != NULL) {
        err = i2c_reg_update_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_CONTROL_2, RV8263C8_BM_ALARM_INT_ENABLE,
                                     RV8263C8_BM_ALARM_INT_ENABLE);
    } else {
        err = i2c_reg_update_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_CONTROL_2, RV8263C8_BM_ALARM_INT_ENABLE,
                                     RV8263C8_BM_ALARM_INT_DISABLE);
    }

    k_spin_unlock(&data->lock, key);

    if (err < 0) {
        LOG_ERR("Error while writing CONTROL2! Error: %i", err);
        return err;
    }

    return 0;
}

/**
 * @brief
 *
 * @param p_dev     Pointer to device strucure
 * @param id
 * @return int      0 when successful
 */
static int rv8263c8_alarm_is_pending(const struct device *p_dev, uint16_t id)
{
    int ret;
    struct rv8263c8_data *const data = p_dev->data;

    if ((p_dev == NULL) || (id != 0)) {
        return -EINVAL;
    }

    k_spinlock_key_t key = k_spin_lock(&data->lock);
    ret = data->is_alarm_pending ? 1 : 0;
    data->is_alarm_pending = false;
    k_spin_unlock(&data->lock, key);

    return ret;
}
#endif

#ifdef CONFIG_RTC_UPDATE
/**
 * @brief
 *
 * @param p_dev         Pointer to device strucure
 * @param callback      RTC update callback
 * @param p_user_data   Pointer to user data for update callback
 * @return int          0 when successful
 */
int rv8263_update_callback(const struct device *p_dev, rtc_update_callback callback, void *p_user_data)
{
    struct rv8263c8_data *const data = p_dev->data;

    if (p_dev == NULL) {
        return -EINVAL;
    }

    k_spinlock_key_t key = k_spin_lock(&data->lock);
    data->update_cb = callback;
    data->update_cb_data = p_user_data;
    k_spin_unlock(&data->lock, key);

    return rv8263c8_update_enable_timer(p_dev);
}
#endif

#ifdef CONFIG_RTC_CALIBRATION
/**
 * @brief
 *
 * @param p_dev         Pointer to device strucure
 * @param calibration
 * @return int          0 when successful
 */
int rv8263c8_calibration_set(const struct device *p_dev, int32_t calibration)
{
    int err;
    int8_t reg;
    struct rv8263c8_data *const data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    if (p_dev == NULL) {
        return -EINVAL;
    }

    reg = calibration & 0x7F;
    reg = bin2bcd(reg);

    k_spinlock_key_t key = k_spin_lock(&data->lock);
    err = i2c_reg_update_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_OFFSET, 0x7F, reg);
    k_spin_unlock(&data->lock, key);

    return err;
}

/**
 * @brief
 *
 * @param p_dev         Pointer to device strucure
 * @param p_calibration
 * @return int          0 when successful
 */
int rv8263c8_calibration_get(const struct device *p_dev, int32_t *p_calibration)
{
    int err;
    uint8_t value;
    struct rv8263c8_data *const data = p_dev->data;
    const struct rv8263c8_config *config = p_dev->config;

    if ((p_dev == NULL) || (p_calibration ==  NULL)) {
        return -EINVAL;
    }

    k_spinlock_key_t key = k_spin_lock(&data->lock);
    err = i2c_reg_read_byte_dt(&config->i2c_bus, RV8263C8_REGISTER_OFFSET, &value);
    k_spin_unlock(&data->lock, key);
    if (err < 0) {
        LOG_ERR("Error while reading OFFSET! Error: %i", err);
        return err;
    }

    *p_calibration = bcd2bin(value & 0x7F);

    return 0;
}
#endif

static const struct rtc_driver_api rv8263c8_driver_api = {
    .set_time = rv8263c8_time_set,
    .get_time = rv8263c8_time_get,
#ifdef CONFIG_RTC_ALARM
    .alarm_get_supported_fields = rv8263c8_alarm_get_supported_fields,
    .alarm_set_time = rv8263c8_alarm_set_time,
    .alarm_get_time = rv8263c8_alarm_get_time,
    .alarm_is_pending = rv8263c8_alarm_is_pending,
    .alarm_set_callback = rv8263c8_alarm_set_callback,
#endif
#ifdef CONFIG_RTC_UPDATE
    .update_set_callback = rv8263_update_callback,
#endif
#ifdef CONFIG_RTC_CALIBRATION
    .set_calibration = rv8263c8_calibration_set,
    .get_calibration = rv8263c8_calibration_get,
#endif
};

#define RV8263_DEFINE(inst)                                                         \
    static struct rv8263c8_data rv8263c8_data_##inst;                               \
    static const struct rv8263c8_config rv8263c8_config_##inst = {                  \
        .i2c_bus = I2C_DT_SPEC_INST_GET(inst),                                      \
        .clkout = DT_INST_PROP(inst, clkout),                                       \
        .fast_mode = DT_INST_PROP(inst, fast_mode),                                 \
        .offset = DT_INST_PROP(inst, offset),                                       \
        IF_ENABLED(RV8263_USE_INT,                                                  \
            (.int_gpio = GPIO_DT_SPEC_INST_GET_OR(inst, int_gpios, { 0 }),))        \
    };                                                                              \
    DEVICE_DT_INST_DEFINE(inst, &rv8263c8_init, NULL, &rv8263c8_data_##inst,        \
                  &rv8263c8_config_##inst, POST_KERNEL, CONFIG_RTC_INIT_PRIORITY,   \
                  &rv8263c8_driver_api);

DT_INST_FOREACH_STATUS_OKAY(RV8263_DEFINE)