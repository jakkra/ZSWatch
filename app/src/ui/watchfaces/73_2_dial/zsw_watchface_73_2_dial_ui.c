
// File generated by bin2lvgl
// developed by fbiego.
// https://github.com/fbiego
// modified by Daniel Kampert.
// https://github.com/kampi
// Watchface: 73_2_dial

#include <lvgl.h>

#include <zephyr/logging/log.h>

#include "ui/zsw_ui.h"
#include "applications/watchface/watchface_app.h"

LOG_MODULE_REGISTER(watchface_73_2_dial, LOG_LEVEL_WRN);

static lv_obj_t *face_73_2_dial;
static lv_obj_t *face_73_2_dial = NULL;
static watchface_app_evt_listener ui_73_2_dial_evt_cb;

static int last_date = -1;
static int last_day = -1;
static int last_month = -1;
static int last_year = -1;
static int last_weekday = -1;
static int last_hour = -1;
static int last_minute = -1;

static int last_steps = -1;
static int last_distance = -1;
static int last_kcal = -1;

static lv_obj_t *face_73_2_dial_0_1816;
static lv_obj_t *face_73_2_dial_1_61342;
static lv_obj_t *face_73_2_dial_2_85528;
static lv_obj_t *face_73_2_dial_4_1182;
static lv_obj_t *face_73_2_dial_6_110332;
static lv_obj_t *face_73_2_dial_7_59924;
static lv_obj_t *face_73_2_dial_8_59942;
static lv_obj_t *face_73_2_dial_9_59942;
static lv_obj_t *face_73_2_dial_10_59942;
static lv_obj_t *face_73_2_dial_11_59942;
static lv_obj_t *face_73_2_dial_12_59924;
static lv_obj_t *face_73_2_dial_13_59942;
static lv_obj_t *face_73_2_dial_14_59942;
static lv_obj_t *face_73_2_dial_15_59942;
static lv_obj_t *face_73_2_dial_16_59942;
static lv_obj_t *face_73_2_dial_17_110874;
static lv_obj_t *face_73_2_dial_18_110874;
static lv_obj_t *face_73_2_dial_19_110874;
static lv_obj_t *face_73_2_dial_20_110874;
static lv_obj_t *face_73_2_dial_21_110874;
static lv_obj_t *face_73_2_dial_22_112986;
static lv_obj_t *face_73_2_dial_23_112986;
static lv_obj_t *face_73_2_dial_24_112986;
static lv_obj_t *face_73_2_dial_25_112986;
static lv_obj_t *face_73_2_dial_27_127086;

ZSW_LV_IMG_DECLARE(face_73_2_dial_0_1816_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_1_61342_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_1_61342_1);
ZSW_LV_IMG_DECLARE(face_73_2_dial_1_61342_2);
ZSW_LV_IMG_DECLARE(face_73_2_dial_1_61342_3);
ZSW_LV_IMG_DECLARE(face_73_2_dial_1_61342_4);
ZSW_LV_IMG_DECLARE(face_73_2_dial_1_61342_5);
ZSW_LV_IMG_DECLARE(face_73_2_dial_1_61342_6);
ZSW_LV_IMG_DECLARE(face_73_2_dial_1_61342_7);
ZSW_LV_IMG_DECLARE(face_73_2_dial_1_61342_8);
ZSW_LV_IMG_DECLARE(face_73_2_dial_1_61342_9);
ZSW_LV_IMG_DECLARE(face_73_2_dial_1_61342_10);
ZSW_LV_IMG_DECLARE(face_73_2_dial_2_85528_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_2_85528_1);
ZSW_LV_IMG_DECLARE(face_73_2_dial_2_85528_2);
ZSW_LV_IMG_DECLARE(face_73_2_dial_2_85528_3);
ZSW_LV_IMG_DECLARE(face_73_2_dial_2_85528_4);
ZSW_LV_IMG_DECLARE(face_73_2_dial_2_85528_5);
ZSW_LV_IMG_DECLARE(face_73_2_dial_2_85528_6);
ZSW_LV_IMG_DECLARE(face_73_2_dial_2_85528_7);
ZSW_LV_IMG_DECLARE(face_73_2_dial_2_85528_8);
ZSW_LV_IMG_DECLARE(face_73_2_dial_2_85528_9);
ZSW_LV_IMG_DECLARE(face_73_2_dial_2_85528_10);
ZSW_LV_IMG_DECLARE(face_73_2_dial_3_564_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_3_564_1);
ZSW_LV_IMG_DECLARE(face_73_2_dial_4_1182_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_4_1182_1);
ZSW_LV_IMG_DECLARE(face_73_2_dial_5_109714_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_5_109714_1);
ZSW_LV_IMG_DECLARE(face_73_2_dial_6_110332_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_6_110332_1);
ZSW_LV_IMG_DECLARE(face_73_2_dial_7_59924_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_8_59942_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_8_59942_1);
ZSW_LV_IMG_DECLARE(face_73_2_dial_8_59942_2);
ZSW_LV_IMG_DECLARE(face_73_2_dial_8_59942_3);
ZSW_LV_IMG_DECLARE(face_73_2_dial_8_59942_4);
ZSW_LV_IMG_DECLARE(face_73_2_dial_8_59942_5);
ZSW_LV_IMG_DECLARE(face_73_2_dial_8_59942_6);
ZSW_LV_IMG_DECLARE(face_73_2_dial_8_59942_7);
ZSW_LV_IMG_DECLARE(face_73_2_dial_8_59942_8);
ZSW_LV_IMG_DECLARE(face_73_2_dial_8_59942_9);
ZSW_LV_IMG_DECLARE(face_73_2_dial_17_110874_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_17_110874_1);
ZSW_LV_IMG_DECLARE(face_73_2_dial_17_110874_2);
ZSW_LV_IMG_DECLARE(face_73_2_dial_17_110874_3);
ZSW_LV_IMG_DECLARE(face_73_2_dial_17_110874_4);
ZSW_LV_IMG_DECLARE(face_73_2_dial_17_110874_5);
ZSW_LV_IMG_DECLARE(face_73_2_dial_17_110874_6);
ZSW_LV_IMG_DECLARE(face_73_2_dial_17_110874_7);
ZSW_LV_IMG_DECLARE(face_73_2_dial_17_110874_8);
ZSW_LV_IMG_DECLARE(face_73_2_dial_17_110874_9);
ZSW_LV_IMG_DECLARE(face_73_2_dial_22_112986_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_22_112986_1);
ZSW_LV_IMG_DECLARE(face_73_2_dial_22_112986_2);
ZSW_LV_IMG_DECLARE(face_73_2_dial_22_112986_3);
ZSW_LV_IMG_DECLARE(face_73_2_dial_22_112986_4);
ZSW_LV_IMG_DECLARE(face_73_2_dial_22_112986_5);
ZSW_LV_IMG_DECLARE(face_73_2_dial_22_112986_6);
ZSW_LV_IMG_DECLARE(face_73_2_dial_22_112986_7);
ZSW_LV_IMG_DECLARE(face_73_2_dial_22_112986_8);
ZSW_LV_IMG_DECLARE(face_73_2_dial_22_112986_9);
ZSW_LV_IMG_DECLARE(face_73_2_dial_26_123614_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_26_123614_1);
ZSW_LV_IMG_DECLARE(face_73_2_dial_26_123614_2);
ZSW_LV_IMG_DECLARE(face_73_2_dial_26_123614_3);
ZSW_LV_IMG_DECLARE(face_73_2_dial_26_123614_4);
ZSW_LV_IMG_DECLARE(face_73_2_dial_26_123614_5);
ZSW_LV_IMG_DECLARE(face_73_2_dial_26_123614_6);
ZSW_LV_IMG_DECLARE(face_73_2_dial_27_127086_0);
ZSW_LV_IMG_DECLARE(face_73_2_dial_27_127086_1);
ZSW_LV_IMG_DECLARE(face_73_2_dial_27_127086_2);
ZSW_LV_IMG_DECLARE(face_73_2_dial_27_127086_3);
ZSW_LV_IMG_DECLARE(face_73_2_dial_27_127086_4);
ZSW_LV_IMG_DECLARE(face_73_2_dial_27_127086_5);
ZSW_LV_IMG_DECLARE(face_73_2_dial_27_127086_6);
ZSW_LV_IMG_DECLARE(face_73_2_dial_preview_0);

#if CONFIG_LV_COLOR_DEPTH_16 != 1
#error "CONFIG_LV_COLOR_DEPTH_16 should be 16 bit for watchfaces"
#endif
#if CONFIG_LV_COLOR_16_SWAP != 1
#error "CONFIG_LV_COLOR_16_SWAP should be 1 for watchfaces"
#endif

const void *face_73_2_dial_1_61342_group[] = {
    ZSW_LV_IMG_USE(face_73_2_dial_1_61342_0),
    ZSW_LV_IMG_USE(face_73_2_dial_1_61342_1),
    ZSW_LV_IMG_USE(face_73_2_dial_1_61342_2),
    ZSW_LV_IMG_USE(face_73_2_dial_1_61342_3),
    ZSW_LV_IMG_USE(face_73_2_dial_1_61342_4),
    ZSW_LV_IMG_USE(face_73_2_dial_1_61342_5),
    ZSW_LV_IMG_USE(face_73_2_dial_1_61342_6),
    ZSW_LV_IMG_USE(face_73_2_dial_1_61342_7),
    ZSW_LV_IMG_USE(face_73_2_dial_1_61342_8),
    ZSW_LV_IMG_USE(face_73_2_dial_1_61342_9),
    ZSW_LV_IMG_USE(face_73_2_dial_1_61342_10),
};
const void *face_73_2_dial_2_85528_group[] = {
    ZSW_LV_IMG_USE(face_73_2_dial_2_85528_0),
    ZSW_LV_IMG_USE(face_73_2_dial_2_85528_1),
    ZSW_LV_IMG_USE(face_73_2_dial_2_85528_2),
    ZSW_LV_IMG_USE(face_73_2_dial_2_85528_3),
    ZSW_LV_IMG_USE(face_73_2_dial_2_85528_4),
    ZSW_LV_IMG_USE(face_73_2_dial_2_85528_5),
    ZSW_LV_IMG_USE(face_73_2_dial_2_85528_6),
    ZSW_LV_IMG_USE(face_73_2_dial_2_85528_7),
    ZSW_LV_IMG_USE(face_73_2_dial_2_85528_8),
    ZSW_LV_IMG_USE(face_73_2_dial_2_85528_9),
    ZSW_LV_IMG_USE(face_73_2_dial_2_85528_10),
};
const void *face_73_2_dial_3_564_group[] = {
    ZSW_LV_IMG_USE(face_73_2_dial_3_564_0),
    ZSW_LV_IMG_USE(face_73_2_dial_3_564_1),
};
const void *face_73_2_dial_4_1182_group[] = {
    ZSW_LV_IMG_USE(face_73_2_dial_4_1182_0),
    ZSW_LV_IMG_USE(face_73_2_dial_4_1182_1),
};
const void *face_73_2_dial_5_109714_group[] = {
    ZSW_LV_IMG_USE(face_73_2_dial_5_109714_0),
    ZSW_LV_IMG_USE(face_73_2_dial_5_109714_1),
};
const void *face_73_2_dial_6_110332_group[] = {
    ZSW_LV_IMG_USE(face_73_2_dial_6_110332_0),
    ZSW_LV_IMG_USE(face_73_2_dial_6_110332_1),
};
const void *face_73_2_dial_8_59942_group[] = {
    ZSW_LV_IMG_USE(face_73_2_dial_8_59942_0),
    ZSW_LV_IMG_USE(face_73_2_dial_8_59942_1),
    ZSW_LV_IMG_USE(face_73_2_dial_8_59942_2),
    ZSW_LV_IMG_USE(face_73_2_dial_8_59942_3),
    ZSW_LV_IMG_USE(face_73_2_dial_8_59942_4),
    ZSW_LV_IMG_USE(face_73_2_dial_8_59942_5),
    ZSW_LV_IMG_USE(face_73_2_dial_8_59942_6),
    ZSW_LV_IMG_USE(face_73_2_dial_8_59942_7),
    ZSW_LV_IMG_USE(face_73_2_dial_8_59942_8),
    ZSW_LV_IMG_USE(face_73_2_dial_8_59942_9),
};
const void *face_73_2_dial_17_110874_group[] = {
    ZSW_LV_IMG_USE(face_73_2_dial_17_110874_0),
    ZSW_LV_IMG_USE(face_73_2_dial_17_110874_1),
    ZSW_LV_IMG_USE(face_73_2_dial_17_110874_2),
    ZSW_LV_IMG_USE(face_73_2_dial_17_110874_3),
    ZSW_LV_IMG_USE(face_73_2_dial_17_110874_4),
    ZSW_LV_IMG_USE(face_73_2_dial_17_110874_5),
    ZSW_LV_IMG_USE(face_73_2_dial_17_110874_6),
    ZSW_LV_IMG_USE(face_73_2_dial_17_110874_7),
    ZSW_LV_IMG_USE(face_73_2_dial_17_110874_8),
    ZSW_LV_IMG_USE(face_73_2_dial_17_110874_9),
};
const void *face_73_2_dial_22_112986_group[] = {
    ZSW_LV_IMG_USE(face_73_2_dial_22_112986_0),
    ZSW_LV_IMG_USE(face_73_2_dial_22_112986_1),
    ZSW_LV_IMG_USE(face_73_2_dial_22_112986_2),
    ZSW_LV_IMG_USE(face_73_2_dial_22_112986_3),
    ZSW_LV_IMG_USE(face_73_2_dial_22_112986_4),
    ZSW_LV_IMG_USE(face_73_2_dial_22_112986_5),
    ZSW_LV_IMG_USE(face_73_2_dial_22_112986_6),
    ZSW_LV_IMG_USE(face_73_2_dial_22_112986_7),
    ZSW_LV_IMG_USE(face_73_2_dial_22_112986_8),
    ZSW_LV_IMG_USE(face_73_2_dial_22_112986_9),
};
const void *face_73_2_dial_26_123614_group[] = {
    ZSW_LV_IMG_USE(face_73_2_dial_26_123614_0),
    ZSW_LV_IMG_USE(face_73_2_dial_26_123614_1),
    ZSW_LV_IMG_USE(face_73_2_dial_26_123614_2),
    ZSW_LV_IMG_USE(face_73_2_dial_26_123614_3),
    ZSW_LV_IMG_USE(face_73_2_dial_26_123614_4),
    ZSW_LV_IMG_USE(face_73_2_dial_26_123614_5),
    ZSW_LV_IMG_USE(face_73_2_dial_26_123614_6),
};
const void *face_73_2_dial_27_127086_group[] = {
    ZSW_LV_IMG_USE(face_73_2_dial_27_127086_0),
    ZSW_LV_IMG_USE(face_73_2_dial_27_127086_1),
    ZSW_LV_IMG_USE(face_73_2_dial_27_127086_2),
    ZSW_LV_IMG_USE(face_73_2_dial_27_127086_3),
    ZSW_LV_IMG_USE(face_73_2_dial_27_127086_4),
    ZSW_LV_IMG_USE(face_73_2_dial_27_127086_5),
    ZSW_LV_IMG_USE(face_73_2_dial_27_127086_6),
};

static int32_t getPlaceValue(int32_t num, int32_t place)
{
    int32_t divisor = 1;
    for (uint32_t i = 1; i < place; i++) {
        divisor *= 10;
    }
    return (num / divisor) % 10;
}

static int32_t setPlaceValue(int32_t num, int32_t place, int32_t newValue)
{
    int32_t divisor = 1;
    for (uint32_t i = 1; i < place; i++) {
        divisor *= 10;
    }
    return num - ((num / divisor) % 10 * divisor) + (newValue * divisor);
}

static void watchface_73_2_dial_remove(void)
{
    if (!face_73_2_dial) {
        return;
    }

    lv_obj_del(face_73_2_dial);
    face_73_2_dial = NULL;
}

static void watchface_73_2_dial_invalidate_cached(void)
{
    last_date = -1;
    last_day = -1;
    last_month = -1;
    last_year = -1;
    last_weekday = -1;
    last_hour = -1;
    last_minute = -1;
    last_steps = -1;
    last_distance = -1;
    last_kcal = -1;
}

static const void *watchface_73_2_dial_get_preview_img(void)
{
    return ZSW_LV_IMG_USE(face_73_2_dial_preview_0);
}

static void watchface_73_2_dial_set_datetime(int day_of_week, int date, int day, int month, int year, int weekday,
                                             int hour,
                                             int minute, int second, uint32_t usec, bool am, bool mode)
{
    if (!face_73_2_dial) {
        return;
    }

    if (mode) {
        lv_obj_add_flag(face_73_2_dial_4_1182, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_clear_flag(face_73_2_dial_4_1182, LV_OBJ_FLAG_HIDDEN);
    }
    lv_img_set_src(face_73_2_dial_4_1182, face_73_2_dial_4_1182_group[(am ? 0 : 1) % 2]);
    if (mode) {
        lv_obj_add_flag(face_73_2_dial_6_110332, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_clear_flag(face_73_2_dial_6_110332, LV_OBJ_FLAG_HIDDEN);
    }
    lv_img_set_src(face_73_2_dial_6_110332, face_73_2_dial_6_110332_group[(am ? 0 : 1) % 2]);

    if (getPlaceValue(last_year, 1) != getPlaceValue(year, 1)) {
        last_year = setPlaceValue(last_year, 1, getPlaceValue(year, 1));
        lv_img_set_src(face_73_2_dial_8_59942, face_73_2_dial_8_59942_group[(year / 1) % 10]);
    }

    if (getPlaceValue(last_year, 2) != getPlaceValue(year, 2)) {
        last_year = setPlaceValue(last_year, 2, getPlaceValue(year, 2));
        lv_img_set_src(face_73_2_dial_9_59942, face_73_2_dial_8_59942_group[(year / 10) % 10]);
    }

    if (getPlaceValue(last_year, 3) != getPlaceValue(year, 3)) {
        last_year = setPlaceValue(last_year, 3, getPlaceValue(year, 3));
        lv_img_set_src(face_73_2_dial_10_59942, face_73_2_dial_8_59942_group[(year / 100) % 10]);
    }

    if (getPlaceValue(last_year, 4) != getPlaceValue(year, 4)) {
        last_year = setPlaceValue(last_year, 4, getPlaceValue(year, 4));
        lv_img_set_src(face_73_2_dial_11_59942, face_73_2_dial_8_59942_group[(year / 1000) % 10]);
    }

    if (getPlaceValue(last_month, 1) != getPlaceValue(month, 1)) {
        last_month = setPlaceValue(last_month, 1, getPlaceValue(month, 1));
        lv_img_set_src(face_73_2_dial_13_59942, face_73_2_dial_8_59942_group[(month / 1) % 10]);
    }

    if (getPlaceValue(last_month, 2) != getPlaceValue(month, 2)) {
        last_month = setPlaceValue(last_month, 2, getPlaceValue(month, 2));
        lv_img_set_src(face_73_2_dial_14_59942, face_73_2_dial_8_59942_group[(month / 10) % 10]);
    }

    if (getPlaceValue(last_day, 1) != getPlaceValue(day, 1)) {
        last_day = setPlaceValue(last_day, 1, getPlaceValue(day, 1));
        lv_img_set_src(face_73_2_dial_15_59942, face_73_2_dial_8_59942_group[(day / 1) % 10]);
    }

    if (getPlaceValue(last_day, 2) != getPlaceValue(day, 2)) {
        last_day = setPlaceValue(last_day, 2, getPlaceValue(day, 2));
        lv_img_set_src(face_73_2_dial_16_59942, face_73_2_dial_8_59942_group[(day / 10) % 10]);
    }

    if (getPlaceValue(last_hour, 1) != getPlaceValue(hour, 1)) {
        last_hour = setPlaceValue(last_hour, 1, getPlaceValue(hour, 1));
        lv_img_set_src(face_73_2_dial_22_112986, face_73_2_dial_22_112986_group[(hour / 1) % 10]);
    }

    if (getPlaceValue(last_hour, 2) != getPlaceValue(hour, 2)) {
        last_hour = setPlaceValue(last_hour, 2, getPlaceValue(hour, 2));
        lv_img_set_src(face_73_2_dial_23_112986, face_73_2_dial_22_112986_group[(hour / 10) % 10]);
    }

    if (getPlaceValue(last_minute, 1) != getPlaceValue(minute, 1)) {
        last_minute = setPlaceValue(last_minute, 1, getPlaceValue(minute, 1));
        lv_img_set_src(face_73_2_dial_24_112986, face_73_2_dial_22_112986_group[(minute / 1) % 10]);
    }

    if (getPlaceValue(last_minute, 2) != getPlaceValue(minute, 2)) {
        last_minute = setPlaceValue(last_minute, 2, getPlaceValue(minute, 2));
        lv_img_set_src(face_73_2_dial_25_112986, face_73_2_dial_22_112986_group[(minute / 10) % 10]);
    }

    if (getPlaceValue(last_weekday, 1) != getPlaceValue(weekday, 1)) {
        last_weekday = setPlaceValue(last_weekday, 1, getPlaceValue(weekday, 1));
        lv_img_set_src(face_73_2_dial_27_127086, face_73_2_dial_27_127086_group[((weekday + 6) / 1) % 7]);
    }

}

static void watchface_73_2_dial_set_step(int32_t steps, int32_t distance, int32_t kcal)
{
    if (!face_73_2_dial) {
        return;
    }

    if (getPlaceValue(last_steps, 1) != getPlaceValue(steps, 1)) {
        last_steps = setPlaceValue(last_steps, 1, getPlaceValue(steps, 1));
        lv_img_set_src(face_73_2_dial_17_110874, face_73_2_dial_17_110874_group[(steps / 1) % 10]);
    }

    if (getPlaceValue(last_steps, 2) != getPlaceValue(steps, 2)) {
        last_steps = setPlaceValue(last_steps, 2, getPlaceValue(steps, 2));
        lv_img_set_src(face_73_2_dial_18_110874, face_73_2_dial_17_110874_group[(steps / 10) % 10]);
    }

    if (getPlaceValue(last_steps, 3) != getPlaceValue(steps, 3)) {
        last_steps = setPlaceValue(last_steps, 3, getPlaceValue(steps, 3));
        lv_img_set_src(face_73_2_dial_19_110874, face_73_2_dial_17_110874_group[(steps / 100) % 10]);
    }

    if (getPlaceValue(last_steps, 4) != getPlaceValue(steps, 4)) {
        last_steps = setPlaceValue(last_steps, 4, getPlaceValue(steps, 4));
        lv_img_set_src(face_73_2_dial_20_110874, face_73_2_dial_17_110874_group[(steps / 1000) % 10]);
    }

    if (getPlaceValue(last_steps, 5) != getPlaceValue(steps, 5)) {
        last_steps = setPlaceValue(last_steps, 5, getPlaceValue(steps, 5));
        lv_img_set_src(face_73_2_dial_21_110874, face_73_2_dial_17_110874_group[(steps / 10000) % 10]);
    }

}

static void watchface_73_2_dial_set_hrm(int32_t bpm, int32_t oxygen)
{
    if (!face_73_2_dial) {
        return;
    }

}

static void watchface_73_2_dial_set_weather(int8_t temp, int icon)
{
    if (!face_73_2_dial) {
        return;
    }

}

static void watchface_73_2_dial_set_ble_connected(bool connected)
{
    if (!face_73_2_dial) {
        return;
    }

}

static void watchface_73_2_dial_set_battery_percent(int32_t percent, int32_t battery)
{
    if (!face_73_2_dial) {
        return;
    }

}

static void watchface_73_2_dial_set_num_notifcations(int32_t number)
{
    if (!face_73_2_dial) {
        return;
    }

}

static void watchface_73_2_dial_set_watch_env_sensors(int temperature, int humidity, int pressure, float iaq, float co2)
{
    if (!face_73_2_dial) {
        return;
    }

}

void watchface_73_2_dial_show(watchface_app_evt_listener evt_cb, zsw_settings_watchface_t *settings)
{
    ui_73_2_dial_evt_cb = evt_cb;

    lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE);
    face_73_2_dial = lv_obj_create(lv_scr_act());
    watchface_73_2_dial_invalidate_cached();

    lv_obj_clear_flag(face_73_2_dial, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_scrollbar_mode(face_73_2_dial, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_opa(face_73_2_dial, LV_OPA_TRANSP, LV_PART_MAIN);

    lv_obj_set_style_border_width(face_73_2_dial, 0, LV_PART_MAIN);
    lv_obj_set_size(face_73_2_dial, 240, 240);
    lv_obj_clear_flag(face_73_2_dial, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(face_73_2_dial, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(face_73_2_dial, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(face_73_2_dial, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(face_73_2_dial, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(face_73_2_dial, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(face_73_2_dial, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(face_73_2_dial, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    face_73_2_dial_0_1816 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_0_1816, ZSW_LV_IMG_USE(face_73_2_dial_0_1816_0));
    lv_obj_set_width(face_73_2_dial_0_1816, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_0_1816, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_0_1816, 0);
    lv_obj_set_y(face_73_2_dial_0_1816, 0);
    lv_obj_add_flag(face_73_2_dial_0_1816, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_0_1816, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_1_61342 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_1_61342, ZSW_LV_IMG_USE(face_73_2_dial_1_61342_0));
    lv_obj_set_width(face_73_2_dial_1_61342, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_1_61342, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_1_61342, 202);
    lv_obj_set_y(face_73_2_dial_1_61342, 88);
    lv_obj_add_flag(face_73_2_dial_1_61342, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_1_61342, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_2_85528 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_2_85528, ZSW_LV_IMG_USE(face_73_2_dial_2_85528_0));
    lv_obj_set_width(face_73_2_dial_2_85528, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_2_85528, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_2_85528, 14);
    lv_obj_set_y(face_73_2_dial_2_85528, 88);
    lv_obj_add_flag(face_73_2_dial_2_85528, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_2_85528, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_4_1182 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_4_1182, ZSW_LV_IMG_USE(face_73_2_dial_4_1182_0));
    lv_obj_set_width(face_73_2_dial_4_1182, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_4_1182, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_4_1182, 41);
    lv_obj_set_y(face_73_2_dial_4_1182, 140);
    lv_obj_add_flag(face_73_2_dial_4_1182, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_4_1182, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_6_110332 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_6_110332, ZSW_LV_IMG_USE(face_73_2_dial_6_110332_0));
    lv_obj_set_width(face_73_2_dial_6_110332, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_6_110332, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_6_110332, 180);
    lv_obj_set_y(face_73_2_dial_6_110332, 140);
    lv_obj_add_flag(face_73_2_dial_6_110332, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_6_110332, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_7_59924 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_7_59924, ZSW_LV_IMG_USE(face_73_2_dial_7_59924_0));
    lv_obj_set_width(face_73_2_dial_7_59924, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_7_59924, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_7_59924, 117);
    lv_obj_set_y(face_73_2_dial_7_59924, 60);
    lv_obj_add_flag(face_73_2_dial_7_59924, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_7_59924, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_8_59942 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_8_59942, ZSW_LV_IMG_USE(face_73_2_dial_8_59942_0));
    lv_obj_set_width(face_73_2_dial_8_59942, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_8_59942, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_8_59942, 107);
    lv_obj_set_y(face_73_2_dial_8_59942, 54);
    lv_obj_add_flag(face_73_2_dial_8_59942, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_8_59942, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_9_59942 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_9_59942, ZSW_LV_IMG_USE(face_73_2_dial_8_59942_0));
    lv_obj_set_width(face_73_2_dial_9_59942, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_9_59942, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_9_59942, 98);
    lv_obj_set_y(face_73_2_dial_9_59942, 54);
    lv_obj_add_flag(face_73_2_dial_9_59942, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_9_59942, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_10_59942 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_10_59942, ZSW_LV_IMG_USE(face_73_2_dial_8_59942_0));
    lv_obj_set_width(face_73_2_dial_10_59942, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_10_59942, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_10_59942, 89);
    lv_obj_set_y(face_73_2_dial_10_59942, 54);
    lv_obj_add_flag(face_73_2_dial_10_59942, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_10_59942, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_11_59942 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_11_59942, ZSW_LV_IMG_USE(face_73_2_dial_8_59942_0));
    lv_obj_set_width(face_73_2_dial_11_59942, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_11_59942, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_11_59942, 80);
    lv_obj_set_y(face_73_2_dial_11_59942, 54);
    lv_obj_add_flag(face_73_2_dial_11_59942, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_11_59942, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_12_59924 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_12_59924, ZSW_LV_IMG_USE(face_73_2_dial_7_59924_0));
    lv_obj_set_width(face_73_2_dial_12_59924, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_12_59924, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_12_59924, 142);
    lv_obj_set_y(face_73_2_dial_12_59924, 60);
    lv_obj_add_flag(face_73_2_dial_12_59924, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_12_59924, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_13_59942 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_13_59942, ZSW_LV_IMG_USE(face_73_2_dial_8_59942_0));
    lv_obj_set_width(face_73_2_dial_13_59942, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_13_59942, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_13_59942, 132);
    lv_obj_set_y(face_73_2_dial_13_59942, 54);
    lv_obj_add_flag(face_73_2_dial_13_59942, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_13_59942, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_14_59942 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_14_59942, ZSW_LV_IMG_USE(face_73_2_dial_8_59942_0));
    lv_obj_set_width(face_73_2_dial_14_59942, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_14_59942, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_14_59942, 123);
    lv_obj_set_y(face_73_2_dial_14_59942, 54);
    lv_obj_add_flag(face_73_2_dial_14_59942, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_14_59942, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_15_59942 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_15_59942, ZSW_LV_IMG_USE(face_73_2_dial_8_59942_0));
    lv_obj_set_width(face_73_2_dial_15_59942, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_15_59942, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_15_59942, 157);
    lv_obj_set_y(face_73_2_dial_15_59942, 54);
    lv_obj_add_flag(face_73_2_dial_15_59942, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_15_59942, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_16_59942 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_16_59942, ZSW_LV_IMG_USE(face_73_2_dial_8_59942_0));
    lv_obj_set_width(face_73_2_dial_16_59942, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_16_59942, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_16_59942, 148);
    lv_obj_set_y(face_73_2_dial_16_59942, 54);
    lv_obj_add_flag(face_73_2_dial_16_59942, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_16_59942, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_17_110874 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_17_110874, ZSW_LV_IMG_USE(face_73_2_dial_17_110874_0));
    lv_obj_set_width(face_73_2_dial_17_110874, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_17_110874, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_17_110874, 149);
    lv_obj_set_y(face_73_2_dial_17_110874, 172);
    lv_obj_add_flag(face_73_2_dial_17_110874, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_17_110874, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_18_110874 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_18_110874, ZSW_LV_IMG_USE(face_73_2_dial_17_110874_0));
    lv_obj_set_width(face_73_2_dial_18_110874, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_18_110874, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_18_110874, 138);
    lv_obj_set_y(face_73_2_dial_18_110874, 172);
    lv_obj_add_flag(face_73_2_dial_18_110874, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_18_110874, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_19_110874 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_19_110874, ZSW_LV_IMG_USE(face_73_2_dial_17_110874_0));
    lv_obj_set_width(face_73_2_dial_19_110874, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_19_110874, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_19_110874, 127);
    lv_obj_set_y(face_73_2_dial_19_110874, 172);
    lv_obj_add_flag(face_73_2_dial_19_110874, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_19_110874, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_20_110874 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_20_110874, ZSW_LV_IMG_USE(face_73_2_dial_17_110874_0));
    lv_obj_set_width(face_73_2_dial_20_110874, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_20_110874, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_20_110874, 116);
    lv_obj_set_y(face_73_2_dial_20_110874, 172);
    lv_obj_add_flag(face_73_2_dial_20_110874, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_20_110874, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_21_110874 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_21_110874, ZSW_LV_IMG_USE(face_73_2_dial_17_110874_0));
    lv_obj_set_width(face_73_2_dial_21_110874, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_21_110874, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_21_110874, 105);
    lv_obj_set_y(face_73_2_dial_21_110874, 172);
    lv_obj_add_flag(face_73_2_dial_21_110874, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_21_110874, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_22_112986 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_22_112986, ZSW_LV_IMG_USE(face_73_2_dial_22_112986_0));
    lv_obj_set_width(face_73_2_dial_22_112986, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_22_112986, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_22_112986, 89);
    lv_obj_set_y(face_73_2_dial_22_112986, 94);
    lv_obj_add_flag(face_73_2_dial_22_112986, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_22_112986, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_23_112986 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_23_112986, ZSW_LV_IMG_USE(face_73_2_dial_22_112986_0));
    lv_obj_set_width(face_73_2_dial_23_112986, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_23_112986, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_23_112986, 62);
    lv_obj_set_y(face_73_2_dial_23_112986, 94);
    lv_obj_add_flag(face_73_2_dial_23_112986, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_23_112986, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_24_112986 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_24_112986, ZSW_LV_IMG_USE(face_73_2_dial_22_112986_0));
    lv_obj_set_width(face_73_2_dial_24_112986, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_24_112986, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_24_112986, 154);
    lv_obj_set_y(face_73_2_dial_24_112986, 94);
    lv_obj_add_flag(face_73_2_dial_24_112986, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_24_112986, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_25_112986 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_25_112986, ZSW_LV_IMG_USE(face_73_2_dial_22_112986_0));
    lv_obj_set_width(face_73_2_dial_25_112986, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_25_112986, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_25_112986, 127);
    lv_obj_set_y(face_73_2_dial_25_112986, 94);
    lv_obj_add_flag(face_73_2_dial_25_112986, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_25_112986, LV_OBJ_FLAG_SCROLLABLE);

    face_73_2_dial_27_127086 = lv_img_create(face_73_2_dial);
    lv_img_set_src(face_73_2_dial_27_127086, ZSW_LV_IMG_USE(face_73_2_dial_27_127086_0));
    lv_obj_set_width(face_73_2_dial_27_127086, LV_SIZE_CONTENT);
    lv_obj_set_height(face_73_2_dial_27_127086, LV_SIZE_CONTENT);
    lv_obj_set_x(face_73_2_dial_27_127086, 87);
    lv_obj_set_y(face_73_2_dial_27_127086, 14);
    lv_obj_add_flag(face_73_2_dial_27_127086, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(face_73_2_dial_27_127086, LV_OBJ_FLAG_SCROLLABLE);

}

static watchface_ui_api_t ui_api = {
    .show = watchface_73_2_dial_show,
    .remove = watchface_73_2_dial_remove,
    .set_battery_percent = watchface_73_2_dial_set_battery_percent,
    .set_hrm = watchface_73_2_dial_set_hrm,
    .set_step = watchface_73_2_dial_set_step,
    .set_ble_connected = watchface_73_2_dial_set_ble_connected,
    .set_num_notifcations = watchface_73_2_dial_set_num_notifcations,
    .set_weather = watchface_73_2_dial_set_weather,
    .set_datetime = watchface_73_2_dial_set_datetime,
    .set_watch_env_sensors = watchface_73_2_dial_set_watch_env_sensors,
    .ui_invalidate_cached = watchface_73_2_dial_invalidate_cached,
    .get_preview_img = watchface_73_2_dial_get_preview_img,
    .name = "Digital Fire",
};

static int watchface_73_2_dial_init(void)
{
    watchface_app_register_ui(&ui_api);

    return 0;
}

SYS_INIT(watchface_73_2_dial_init, APPLICATION, WATCHFACE_UI_INIT_PRIO);
