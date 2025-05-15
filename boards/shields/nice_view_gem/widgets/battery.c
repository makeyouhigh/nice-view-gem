#include <zephyr/kernel.h>
#include "battery.h"
#include "../assets/custom_fonts.h"

LV_IMG_DECLARE(bolt);

static void draw_level_line(lv_obj_t *canvas, const char *label, uint8_t percent, bool charging,
                            int x_label, int y_label, int x_text, int y_text, int x_bolt, int y_bolt) {
    char text[10] = {};
    lv_draw_label_dsc_t label_left_dsc;
    lv_draw_label_dsc_t label_right_dsc;
    lv_draw_img_dsc_t img_dsc;

    init_label_dsc(&label_left_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_LEFT);
    init_label_dsc(&label_right_dsc, LVGL_FOREGROUND, &pixel_operator_mono, LV_TEXT_ALIGN_RIGHT);
    lv_draw_img_dsc_init(&img_dsc);

    // Label (LBAT / RBAT)
    lv_canvas_draw_text(canvas, x_label, y_label, 30, &label_left_dsc, label);

    // Percentage
    snprintf(text, sizeof(text), "%u%%", percent);
    lv_canvas_draw_text(canvas, x_text, y_text, 35, &label_right_dsc, text);

    // Charging icon
    if (charging) {
        lv_canvas_draw_img(canvas, x_bolt, y_bolt, &bolt, &img_dsc);
    }
}

void draw_battery_status(lv_obj_t *canvas, const struct status_state *state) {
    // 첫 줄: LBAT
    draw_level_line(canvas, "BAT", state->battery, state->charging,
                    0, 6,   // label 위치
                    56, 6,  // percent 위치
                    62, 8); // bolt 아이콘 위치

#if IS_ENABLED(CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_PROXY)
    // 둘째 줄: RBAT
    draw_level_line(canvas, "PBAT", state->peripheral_battery, state->peripheral_charging,
                    0, 24,
                    56, 24,
                    62, 26);
#endif
}

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
