#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Crides
#define PRODUCT         Fissure
#define DESCRIPTION     36 key split keyboard

/* #define USE_I2C */
#define SOFT_SERIAL_PIN D0
#define EE_HANDS

#define RGB_DI_PIN B5
#define RGBLED_NUM 2
#define RGBLED_SPLIT {1, 1}
#define RGBLIGHT_SPLIT

// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS { F4, F5, F6, F7 }
#define MATRIX_COL_PINS { D4, C6, D7, E6, B4 }

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCING_DELAY 5
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
#define PREVENT_STUCK_MODIFIERS

#endif
