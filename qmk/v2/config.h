#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6063
#define DEVICE_VER      0x0301
#define MANUFACTURER    Crides
#define PRODUCT         Fissure-v3.1
#define DESCRIPTION     40 key split keyboard

#define USE_I2C
#define EE_HANDS
#define SPLIT_USB_DETECT

#define RGBLED_NUM 2
#define RGB_DI_PIN F7
#define RGBLED_SPLIT {1, 1}
#define RGBLIGHT_SPLIT

// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS { E6, B4, B5, D7 }
#define MATRIX_COL_PINS { D3, D2, F4, F5, F6 }

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCING_DELAY 5
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
#define PREVENT_STUCK_MODIFIERS
#define COMBO_COUNT 28
#define COMBO_TERM 60

#endif
