#pragma once

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>

#include "bme68x.h"
#include "bme68x_iaq.h"
#include "bsec_interface.h"

#define SENSOR_CHAN_IAQ 		(SENSOR_CHAN_PRIV_START + 1)

struct bme_sample_result {
	double temperature;
	double humidity;
	double pressure;
	uint16_t air_quality;
};

struct bme68x_iaq_config {
	const struct i2c_dt_spec i2c;
};

struct bme68x_iaq_data {
	/* Variable to store intermediate sample result */
	struct bme_sample_result latest;

	/* Trigger and corresponding handler */
	sensor_trigger_handler_t trg_handler;
	const struct sensor_trigger *trigger;

	/* Internal BSEC thread metadata value. */
	struct k_thread thread;

	/* Buffer used to maintain the BSEC library state. */
	uint8_t state_buffer[BSEC_MAX_STATE_BLOB_SIZE];

	/* Size of the saved state */
	int32_t state_len;

	bsec_sensor_configuration_t required_sensor_settings[BSEC_MAX_PHYSICAL_SENSOR];
	uint8_t n_required_sensor_settings;

	/* some RAM space needed by bsec_get_state and bsec_set_state for (de-)serialization. */
	uint8_t work_buffer[BSEC_MAX_WORKBUFFER_SIZE];

	bool initialized;

	struct bme68x_dev dev;
};