# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(lvgl)

include_directories(src/)

FILE(GLOB app_sources src/*.c)
#target_sources(app PRIVATE ${app_sources})
target_sources(app PRIVATE 
    src/main.c
    #src/img_hand.c
    src/buttons.c
    src/gpio_debug.c
    src/hr_service.c
    src/battery.c
    src/filesystem.c
    src/img_hand.c
    )
