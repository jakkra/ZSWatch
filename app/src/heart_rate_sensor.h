#ifndef __HEART_RATE_SENSOR
#define __HEART_RATE_SENSOR

typedef struct heart_rate_sample {
    int32_t red;
    int32_t green;
    int32_t ir;
} plot_page_led_values_t;

int heart_rate_sensor_init(void);

int heart_rate_sensor_fetch(plot_page_led_values_t *sample);

#endif