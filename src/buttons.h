/*
 * Copyright 2021 u-blox
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __BUTTONS_H
#define __BUTTONS_H

#include <zephyr.h>

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
  BUTTON_1,
  BUTTON_2
} buttonId_t;

typedef void(*buttonHandlerCallback_t)(buttonPressType_t type, buttonId_t id);

/**
 * @brief   Init Button press handler
 *
 * @param   handler          Pointer to callback function for button events.
 */
void buttonsInit(buttonHandlerCallback_t handler);

#endif