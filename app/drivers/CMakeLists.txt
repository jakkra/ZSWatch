add_subdirectory(display)
add_subdirectory(input)
add_subdirectory(rtc)

add_subdirectory_ifdef(CONFIG_SENSOR sensor)