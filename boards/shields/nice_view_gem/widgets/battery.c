#include <zephyr/kernel.h>
#include "battery.h"
#include "../assets/custom_fonts.h"

LV_IMG_DECLARE(bolt);

void draw_battery_status(lv_obj_t *canvas, const struct status_state *state) {
    // 공통 스타일
    static lv_draw_label_dsc_t dsc = LV_DRAW_LABEL_DSC_INIT();
    static lv_draw_label_dsc_t label_dsc = LV_DRAW_LABEL_DSC_INIT();
    static lv_draw_img_dsc_t img_dsc;
    lv_draw_img_dsc_init(&img_dsc);

    char buf[6] = {};

    // --- Host (왼쪽) ---
    snprintf(buf, sizeof(buf), "%u%%", state->battery);
    lv_canvas_draw_text(canvas, 26, 19, 42, &dsc, buf);            // 퍼센트
    lv_canvas_draw_text(canvas, 0, 19, 25, &label_dsc, "L");       // L 라벨

    if (state->charging) {
        lv_canvas_draw_img(canvas, 62, 21, &bolt, &img_dsc);       // 번개 아이콘
    }

#if IS_ENABLED(CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_PROXY)
    // --- Peripheral (오른쪽) ---
    snprintf(buf, sizeof(buf), "%u%%", state->peripheral_battery);
    lv_canvas_draw_text(canvas, 110, 19, 42, &dsc, buf);           // 퍼센트 (조정 가능)
    lv_canvas_draw_text(canvas, 96, 19, 10, &label_dsc, "R");      // R 라벨

    if (state->peripheral_charging) {
        lv_canvas_draw_img(canvas, 126, 21, &bolt, &img_dsc);      // 번개 아이콘
    }
#endif
}


/*
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

void draw_battery_status(lv_obj_t *canvas, const struct status_state *state) {
    lv_draw_label_dsc_t label_left_dsc;
    init_label_dsc(&label_left_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);
    lv_canvas_draw_text(canvas, 0, 19, 25, &label_left_dsc, "BAT");

    if (state->charging) {
        draw_charging_level(canvas, state);
    } else {
        draw_level(canvas, state);
    }
}
*/
