add_subdirectory(accelerometer)
include_directories(accelerometer)

add_subdirectory(settings)
include_directories(settings)

FILE(GLOB app_sources *.c)
target_sources(app PRIVATE ${app_sources})
