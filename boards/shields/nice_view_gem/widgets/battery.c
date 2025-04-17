#include <zephyr/kernel.h>
#include "battery.h"
#include "../assets/custom_fonts.h"

static uint8_t left_batt = 0;
static uint8_t right_batt = 0;
static bool is_charging = false;
LV_IMG_DECLARE(bolt);

static void draw_level(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_label_dsc_t label_right_dsc;
    init_label_dsc(&label_right_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_RIGHT);

    char text[10] = {};

    sprintf(text, "%i%%", state->battery);
    lv_canvas_draw_text(canvas, 26, 19, 42, &label_right_dsc, text);
}

static void draw_charging_level(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);
    lv_draw_label_dsc_t label_right_dsc;
    init_label_dsc(&label_right_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_RIGHT);

    char text[10] = {};

    sprintf(text, "%i%%", state->battery);
    lv_canvas_draw_text(canvas, 26, 19, 35, &label_right_dsc, text);
    lv_canvas_draw_img(canvas, 62, 21, &bolt, &img_dsc);
}

static void draw_dual_battery(lv_obj_t *canvas) {
    lv_draw_label_dsc_t label_right_dsc;
    init_label_dsc(&label_right_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_RIGHT);

    char text[20] = {};
    sprintf(text, "L:%d%% R:%d%%", left_batt, right_batt);

    lv_canvas_draw_text(canvas, 0, 19, 64, &label_right_dsc, text);
}

    
#void draw_battery_status(lv_obj_t *canvas, const struct status_state *state) {
#    lv_draw_label_dsc_t label_left_dsc;
#    init_label_dsc(&label_left_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);
#    lv_canvas_draw_text(canvas, 0, 19, 25, &label_left_dsc, "BAT");
#
#    if (state->charging) {
#        draw_charging_level(canvas, state);
#    } else {
#        draw_level(canvas, state);
#    }
#}

void draw_battery_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_label_dsc_t label_left_dsc;
    init_label_dsc(&label_left_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);
    lv_canvas_draw_text(canvas, 0, 19, 25, &label_left_dsc, "BAT");

#ifdef CONFIG_ZMK_SPLIT_ROLE_CENTRAL
    // 왼쪽 키보드인 경우만 dual battery 출력
    draw_dual_battery(canvas);
#else
    // 오른쪽 키보드는 그냥 1개만 출력
    if (state->charging) {
        draw_charging_level(canvas, state);
    } else {
        draw_level(canvas, state);
    }
#endif
}
