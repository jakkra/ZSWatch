target_include_directories(app PRIVATE .)
target_include_directories(app PRIVATE BMP5-Sensor-API)

target_sources(app PRIVATE
    BMP5-Sensor-API/bmp5.c
    bmp5_port.c
)
