#ifndef __BUTTONS_H
#define __BUTTONS_H

#include <zephyr/kernel.h>

/**
 * @brief Type of button event
 */
typedef enum buttonPressType_t {
    BUTTONS_SHORT_PRESS,
    BUTTONS_LONG_PRESS
} buttonPressType_t;

/**
 * @brief Button id
 */
typedef enum buttonId_t {
    BUTTON_TOP_RIGHT,
    BUTTON_TOP_LEFT,
    BUTTON_BOTTOM_RIGHT,
    BUTTON_BOTTOM_LEFT,
    BUTTON_END,
} buttonId_t;

typedef void(*buttonHandlerCallback_t)(buttonPressType_t type, buttonId_t id);

/**
 * @brief   Read button state
 * @param   button          Button id to read
 *
 * @return  1 if button is pressed, 0 if not
*/
int button_read(buttonId_t button);

#endif
