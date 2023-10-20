target_include_directories(app PRIVATE .)
target_include_directories(app PRIVATE BMI270-Sensor-API)

target_sources(app PRIVATE
    BMI270-Sensor-API/bmi270.c
    BMI270-Sensor-API/bmi2.c
    bmi270_port.c
)
