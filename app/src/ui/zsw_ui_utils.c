#include <ui/zsw_ui_utils.h>
#include <lvgl.h>

#if CONFIG_WATCHFACE_BACKGROUND_SPACE
LV_IMG_DECLARE(space_blur_bg);
const lv_img_dsc_t *global_watchface_bg_img = &space_blur_bg;
#elif CONFIG_WATCHFACE_BACKGROUND_FLOWER
LV_IMG_DECLARE(flower_watchface_bg);
const lv_img_dsc_t *global_watchface_bg_img = &flower_watchface_bg;
#elif CONFIG_WATCHFACE_BACKGROUND_PLANET
LV_IMG_DECLARE(earth_blur_move);
const lv_img_dsc_t *global_watchface_bg_img = &earth_blur_move;
#else
const lv_img_dsc_t *global_watchface_bg_img = NULL;
#endif

LV_IMG_DECLARE(stormy);
LV_IMG_DECLARE(snowy);
LV_IMG_DECLARE(rainy);
LV_IMG_DECLARE(snowy);
LV_IMG_DECLARE(foggy);
LV_IMG_DECLARE(sunny);
LV_IMG_DECLARE(partly_cloudy);
LV_IMG_DECLARE(cloudy);
LV_IMG_DECLARE(unknown);

const lv_img_dsc_t *zsw_ui_utils_icon_from_weather_code(int code, lv_color_t *icon_color)
{
    int code_group = code / 100;

    *icon_color = lv_color_white();

    switch (code_group) {
        case 2:
            *icon_color = lv_color_hex(0xD5DFE7);
            return &stormy;
        case 3:
            *icon_color = lv_color_hex(0xD5DFE7);
            return &cloudy;
        case 5:
            switch (code) {
                case 511:
                    *icon_color = lv_color_white();
                    return &snowy;
                default:
                    *icon_color = lv_color_hex(0x5275A2);
                    return &rainy;
            }
        case 6:
            *icon_color = lv_color_white();
            return &snowy;
        case 7:
            *icon_color = lv_color_hex(0x5275A2);
            return &foggy;
        case 8:
            switch (code) {
                case 800:
                    // TODO if day sunny else moon
                    *icon_color = lv_color_hex(0xFBD92A);
                    return &sunny;
                case 801:
                    *icon_color = lv_color_white();
                    return &partly_cloudy;
                case 802:
                    *icon_color = lv_color_hex(0xD5DFE7);
                    return &partly_cloudy;
                default:
                    *icon_color = lv_color_hex(0xD5DFE7);
                    return &cloudy;
            }
        default: {
            printf("Unhandled weather code: %d", code);
            return &unknown;
        }
    }
}
