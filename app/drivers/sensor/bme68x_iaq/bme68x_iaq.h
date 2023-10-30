#pragma once

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>

#include "bme68x.h"
#include "bme68x_iaq.h"
#include "bsec_interface.h"

#define SENSOR_CHAN_IAQ 		(SENSOR_CHAN_PRIV_START + 1)