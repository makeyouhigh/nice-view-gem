#pragma once

#include <lvgl.h>
#include "util.h"

struct battery_status_state {
    uint8_t level;
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    bool usb_present;
#endif

#if IS_ENABLED(CONFIG_ZMK_SPLIT_BLE_CENTRAL_BATTERY_LEVEL_PROXY)
    uint8_t peripheral_level;
    bool peripheral_charging;
#endif
};


void draw_battery_status(lv_obj_t *canvas, const struct status_state *state);
