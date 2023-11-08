#include <zephyr/logging/log.h>

#include "bmi2.h"
#include "bmi270.h"
#include "bosch_bmi270_config.h"

//LOG_MODULE_REGISTER(bmi270_config, CONFIG_SENSOR_LOG_LEVEL);
LOG_MODULE_REGISTER(bmi270_config, LOG_LEVEL_INF);

typedef void(*feature_config_func)(struct bmi2_sens_config *p_config);

typedef struct bosch_bmi270_feature_config_set_t {
    uint8_t                 sensor_id;
    feature_config_func     cfg_func;
    bool                    isr_disable;
    bool                    skip_enable;
} bosch_bmi270_feature_config_set_t;

static void bmi2_configure_accel(struct bmi2_sens_config *p_config);
static void bmi2_configure_step_counter(struct bmi2_sens_config *p_config);
static void bmi2_configure_gyro(struct bmi2_sens_config *p_config);
static void bmi2_configure_anymotion(struct bmi2_sens_config *p_config);
static void bmi2_configure_gesture_detect(struct bmi2_sens_config *p_config);
static void bmi2_configure_wrist_wakeup(struct bmi2_sens_config *p_config);
static void bmi2_configure_no_motion(struct bmi2_sens_config *p_config);

static bosch_bmi270_feature_config_set_t bmi270_enabled_features[] = {
    { .sensor_id = BMI2_ACCEL, .cfg_func = bmi2_configure_accel},
    // Gyro not used for now, disable to keep power consumption down
    { .sensor_id = BMI2_GYRO, .cfg_func = bmi2_configure_gyro, .skip_enable = true},
    { .sensor_id = BMI2_STEP_COUNTER, .cfg_func = bmi2_configure_step_counter},
    { .sensor_id = BMI2_SIG_MOTION, .cfg_func = NULL, .isr_disable = true},
    { .sensor_id = BMI2_ANY_MOTION, .cfg_func = bmi2_configure_anymotion, .isr_disable = true, .skip_enable = true},
    { .sensor_id = BMI2_STEP_ACTIVITY, .cfg_func = NULL, .skip_enable = true},
    { .sensor_id = BMI2_WRIST_GESTURE, .cfg_func = bmi2_configure_gesture_detect},
    { .sensor_id = BMI2_WRIST_WEAR_WAKE_UP, .cfg_func = bmi2_configure_wrist_wakeup},
    { .sensor_id = BMI2_NO_MOTION, .cfg_func = bmi2_configure_no_motion},
};

/** @brief              
 *  @param sensor_id       
 *  @return             true when feature available
*/
static bool bmi2_is_sensor_feature(uint8_t sensor_id)
{
    switch (sensor_id) {
        case BMI2_SIG_MOTION:
        case BMI2_WRIST_GESTURE:
        case BMI2_ANY_MOTION:
        case BMI2_NO_MOTION:
        case BMI2_STEP_COUNTER:
        case BMI2_STEP_DETECTOR:
        case BMI2_STEP_ACTIVITY:
        case BMI2_WRIST_WEAR_WAKE_UP:
            return true;
        default:
            return false;
    }
}

int8_t bmi2_configure_enable_all(struct bmi2_dev *p_bmi2_dev)
{
    int8_t result;

    // INT setup
    struct bmi2_int_pin_config int_cfg;

    // Structure to define all sensors and their configs
    struct bmi2_sens_config config[ARRAY_SIZE(bmi270_enabled_features)];

    // To enable the sensors the Bosch API expects a list of all features.
    uint8_t all_sensors[ARRAY_SIZE(bmi270_enabled_features)];

    // There is a difference between a "sensor" and a "feature".
    // Accel, Gyro are sensors, but step counter is a feature.
    // We map sensor INT to INT1 pin and feature ISR to INT2 pin.
    // The API needs a list of all those features to do that map.
    struct bmi2_sens_int_config all_features[ARRAY_SIZE(bmi270_enabled_features)];
    uint8_t num_features = 0;
    uint8_t num_enabled_features = 0;

    for (int i = 0; i < ARRAY_SIZE(bmi270_enabled_features); i++) {
        config[i].type = bmi270_enabled_features[i].sensor_id;
        if (!bmi270_enabled_features[i].skip_enable) {
            all_sensors[num_enabled_features] = bmi270_enabled_features[i].sensor_id;
            num_enabled_features++;
        }
        if (bmi2_is_sensor_feature(bmi270_enabled_features[i].sensor_id)) {
            all_features[num_features].type = bmi270_enabled_features[i].sensor_id;
            if (bmi270_enabled_features[i].isr_disable) {
                all_features[num_features].hw_int_pin = BMI2_INT_NONE;
            } else {
                all_features[num_features].hw_int_pin = BMI2_INT2;
            }
            num_features++;
        }
    }

    // Get default configurations for the type of feature selected.
    result = bmi270_get_sensor_config(config, ARRAY_SIZE(bmi270_enabled_features), p_bmi2_dev);
    LOG_DBG("Get sensor config result: %i", result);

    // Map data ready interrupt to interrupt pin.
    // Uncomment to generate DRDY INT on INT1
    // rslt = bmi2_map_data_int(BMI2_DRDY_INT, BMI2_INT1, bmi2_dev);
    // bmi2_error_codes_print_result(rslt);

    for (int i = 0; i < ARRAY_SIZE(bmi270_enabled_features); i++) {
        if (bmi270_enabled_features[i].cfg_func) {
            bmi270_enabled_features[i].cfg_func(&config[i]);
        }
    }

    if (result == BMI2_OK) {
        /* NOTE:
        * Accel and Gyro enable must be done after setting configurations.
        */
        result = bmi270_sensor_enable(all_sensors, num_enabled_features, p_bmi2_dev);
        LOG_DBG("Sensor enable result: %i", result);
    }

    // Setup int
    bmi2_get_int_pin_config(&int_cfg, p_bmi2_dev);

    int_cfg.pin_type = BMI2_INT_BOTH;
    int_cfg.pin_cfg[0].lvl = BMI2_INT_ACTIVE_HIGH;
    int_cfg.pin_cfg[0].od = BMI2_INT_PUSH_PULL;
    int_cfg.pin_cfg[0].output_en = BMI2_INT_OUTPUT_ENABLE;
    int_cfg.pin_cfg[1].lvl = BMI2_INT_ACTIVE_HIGH;
    int_cfg.pin_cfg[1].od = BMI2_INT_PUSH_PULL;
    int_cfg.pin_cfg[1].output_en = BMI2_INT_OUTPUT_ENABLE;

    result = bmi2_set_int_pin_config(&int_cfg, p_bmi2_dev);
    LOG_DBG("Set pin config result: %i", result);

    if (result == BMI2_OK) {
        result = bmi270_set_sensor_config(config, ARRAY_SIZE(bmi270_enabled_features), p_bmi2_dev);
        LOG_DBG("Set sensor config result: %i", result);
    }

    if (result == BMI2_OK) {
        result = bmi270_map_feat_int(all_features, num_features, p_bmi2_dev);
        LOG_DBG("Map feature result: %i", result);
    }

    return 0;
}

/** @brief          
 *  @param p_config 
*/
static void bmi2_configure_accel(struct bmi2_sens_config *p_config)
{
    /* NOTE: The user can change the following configuration parameters according to their requirement. */
    /* Set Output Data Rate */
    p_config->cfg.acc.odr = BMI2_ACC_ODR_100HZ;

    /* Gravity range of the sensor (+/- 2G, 4G, 8G, 16G). */
    p_config->cfg.acc.range = BMI2_ACC_RANGE_2G;

    /* The bandwidth parameter is used to bmi2_configure the number of sensor samples that are averaged
        * if it is set to 2, then 2^(bandwidth parameter) samples
        * are averaged, resulting in 4 averaged samples.
        * Note1 : For more information, refer the datasheet.
        * Note2 : A higher number of averaged samples will result in a lower noise level of the signal, but
        * this has an adverse effect on the power consumed.
        */
    p_config->cfg.acc.bwp = BMI2_ACC_NORMAL_AVG4;

    /* Enable the filter performance mode where averaging of samples
        * will be done based on above set bandwidth and ODR.
        * There are two modes
        *  0 -> Ultra low power mode
        *  1 -> High performance mode(Default)
        * For more info refer datasheet.
        */
    p_config->cfg.acc.filter_perf = BMI2_POWER_OPT_MODE;
}

/** @brief          
 *  @param p_config 
*/
static void bmi2_configure_gyro(struct bmi2_sens_config *p_config)
{
    /* The user can change the following configuration parameters according to their requirement. */
    /* Set Output Data Rate */
    p_config->cfg.gyr.odr = BMI2_GYR_ODR_25HZ;

    /* Gyroscope Angular Rate Measurement Range.By default the range is 2000dps. */
    p_config->cfg.gyr.range = BMI2_GYR_RANGE_2000;

    /* Gyroscope bandwidth parameters. By default the gyro bandwidth is in normal mode. */
    p_config->cfg.gyr.bwp = BMI2_GYR_NORMAL_MODE;

    /* Enable/Disable the noise performance mode for precision yaw rate sensing
        * There are two modes
        *  0 -> Ultra low power mode(Default)
        *  1 -> High performance mode
        */
    p_config->cfg.gyr.noise_perf = BMI2_POWER_OPT_MODE;

    /* Enable/Disable the filter performance mode where averaging of samples
        * will be done based on above set bandwidth and ODR.
        * There are two modes
        *  0 -> Ultra low power mode
        *  1 -> High performance mode(Default)
        */
    p_config->cfg.gyr.filter_perf = BMI2_POWER_OPT_MODE;
}

/** @brief          
 *  @param p_config 
*/
static void bmi2_configure_step_counter(struct bmi2_sens_config *p_config)
{
    p_config->cfg.step_counter.watermark_level = 1;
}

/** @brief          
 *  @param p_config 
*/
static void bmi2_configure_anymotion(struct bmi2_sens_config *p_config)
{
    /* 1LSB equals 20ms. Default is 100ms, setting to 80ms. */
    p_config->cfg.any_motion.duration = 0x04;

    /* 1LSB equals to 0.48mg. Default is 83mg, setting to 50mg. */
    p_config->cfg.any_motion.threshold = 0x68;
}

/** @brief          
 *  @param p_config 
*/
static void bmi2_configure_gesture_detect(struct bmi2_sens_config *p_config)
{
    p_config->cfg.wrist_gest.wearable_arm = BMI2_ARM_LEFT;
}

static void bmi2_configure_wrist_wakeup(struct bmi2_sens_config *p_config)
{
    p_config->cfg.wrist_gest_w.device_position = BMI2_ARM_LEFT;
    // TODO many things to bmi2_configure here
}

/** @brief          
 *  @param p_config 
*/
static void bmi2_configure_no_motion(struct bmi2_sens_config *p_config)
{
    // 1LSB equals 20ms. Default is 100ms, setting to 80ms.
    // Max value is 163 seconds, hence below calc. We want max.
    p_config->cfg.no_motion.duration = (160 * 1000) / 20;
}

int bmi2_set_accel_range(const struct device *p_dev, const struct sensor_value *p_range)
{
	struct bmi270_data *data = p_dev->data;
	uint8_t range;
    uint8_t reg;

    // TODO

	/* range->val2 is unused */
	switch (p_range->val1) {
	case 2:
		reg = BOSCH_BMI270_ACC_RANGE_2G;
		data->acc_range = 2;
		break;
	case 4:
		reg = BOSCH_BMI270_ACC_RANGE_4G;
		data->acc_range = 4;
		break;
	case 8:
		reg = BOSCH_BMI270_ACC_RANGE_8G;
		data->acc_range = 8;
		break;
	case 16:
		reg = BOSCH_BMI270_ACC_RANGE_16G;
		data->acc_range = 16;
		break;
	default:
		return -ENOTSUP;
	}

	return 0;
}

int bmi2_set_accel_odr_osr(const struct device *p_dev, const struct sensor_value *p_odr, const struct sensor_value *p_osr)
{
	// TODO

	return 0;
}

int bmi2_set_gyro_range(const struct device *p_dev, const struct sensor_value *p_range)
{
	// TODO

	return 0;
}

int bmi2_set_gyro_odr_osr(const struct device *p_dev, const struct sensor_value *p_odr, const struct sensor_value *p_osr)
{
	// TODO

	return 0;
}