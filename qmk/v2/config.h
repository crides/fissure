#ifndef CONFIG_H
#define CONFIG_H

#ifdef __AVR__
#include "config_common.h"
#endif

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Crides
#define PRODUCT         Fissure
#define DESCRIPTION     36 key split keyboard

#ifdef __AVR__
#define USE_I2C
#endif
/* #define USE_SERIAL */
/* #define SOFT_SERIAL_PIN D0 */
#define EE_HANDS

#define RGBLED_NUM 2
#ifdef __AVR__
#define RGB_DI_PIN B5
#else
#define RGB_DI_PIN 38
#endif
#define RGBLED_SPLIT {1, 1}
#define RGBLIGHT_SPLIT

// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

/* #define MATRIX_ROW_PINS { F4, F5, F6, F7 } */
/* #define MATRIX_COL_PINS { D4, C6, D7, E6, B4 } */
#ifdef __AVR__
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#define MATRIX_COL_PINS { D3, D2, B1, B3, B2 }
#else
#define BLE_NUS_MIN_INTERVAL 10 // default 60
#define BLE_NUS_MAX_INTERVAL 30 // default 75
#define BLE_HID_MAX_INTERVAL 30 // default 90
#define BLE_HID_SLAVE_LATENCY 4 // default 4
#endif

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCING_DELAY 5
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
#define PREVENT_STUCK_MODIFIERS
#define COMBO_COUNT 28
#define COMBO_TERM 50

#endif
