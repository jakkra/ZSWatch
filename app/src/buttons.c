#include "buttons.h"

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/sys/__assert.h>
#include <assert.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(buttons, LOG_LEVEL_DBG);

#define STACKSIZE               1024
#define PRIORITY                7

#define BTN_LONG_PRESS_LIMIT  1000
#define NUM_BUTTONS           BUTTON_END

static void buttonPressedIsr(const struct device *dev, struct gpio_callback *cb, uint32_t pins);
static void handleButtonThread(void);

typedef struct buttons_t {
    struct gpio_dt_spec btn;
    struct gpio_callback callback_data;
    bool fake_pressed;
} buttons_t;

static buttons_t buttons[NUM_BUTTONS] = {
    [BUTTON_TOP_RIGHT] = { .btn = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw_top_right), gpios, {0}) },
    [BUTTON_TOP_LEFT] = { .btn = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw_top_left), gpios, {0}) },
    [BUTTON_BOTTOM_RIGHT] = { .btn = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw_bottom_right), gpios, {0}) },
    [BUTTON_BOTTOM_LEFT] = { .btn = GPIO_DT_SPEC_GET_OR(DT_ALIAS(sw_bottom_left), gpios, {0}) }
};

static buttonHandlerCallback_t callback;
static struct k_sem btnSem;
static uint8_t pressed_button_id;

int button_read(buttonId_t button)
{
    if (button >= NUM_BUTTONS) {
        return -ERANGE;
    }
    if (buttons[button].fake_pressed) {
        buttons[button].fake_pressed = false;
        return 1;
    }
#ifdef CONFIG_BOARD_NATIVE_POSIX
    return 0;
#endif
    return gpio_pin_get_dt(&buttons[button].btn);
}