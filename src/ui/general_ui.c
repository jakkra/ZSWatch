#include <general_ui.h>
#include <lvgl.h>

#define ANIM_TIME  (150)

static void general_ui_init(void)
{

}

void general_ui_anim_out_all(lv_obj_t *obj, uint32_t delay)
{
    for (int i = 0; i < lv_obj_get_child_cnt(obj); i++) {
        lv_obj_t *child = lv_obj_get_child(obj, i);
        if (child != lv_scr_act()) {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, child);
            lv_anim_set_time(&a, ANIM_TIME);
            lv_anim_set_delay(&a, delay);

            lv_anim_set_ready_cb(&a, lv_obj_del_anim_ready_cb);
            lv_anim_start(&a);

            lv_obj_fade_out(child, ANIM_TIME - 70, delay + 70);
        }
    }
}

#define WATCH_ANIM_Y (LV_VER_RES / 20)
void general_ui_anim_in(lv_obj_t *obj, uint32_t delay)
{
    if (obj != lv_scr_act()) {
        lv_anim_t a;
        lv_anim_init(&a);
        lv_anim_set_var(&a, obj);
        lv_anim_set_time(&a, ANIM_TIME);
        lv_anim_set_delay(&a, delay);
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_y);
        lv_anim_set_values(&a, lv_obj_get_y(obj) - WATCH_ANIM_Y, lv_obj_get_y(obj));
        lv_anim_start(&a);

        lv_obj_fade_in(obj, ANIM_TIME - 50, delay);
    }
}