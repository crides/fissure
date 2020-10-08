#ifndef CONFIG_H
#define CONFIG_H

#ifdef __AVR__
#include "config_common.h"
#endif

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6062
#define DEVICE_VER      0x0202
#define MANUFACTURER    Crides
#define PRODUCT         Fissure-v2.2
#define DESCRIPTION     40 key split keyboard

#ifdef __AVR__
#define USE_I2C
#endif
/* #define USE_SERIAL */
/* #define SOFT_SERIAL_PIN D0 */
#define EE_HANDS

#define RGBLED_NUM 2
#ifdef __AVR__
#define RGB_DI_PIN F7
#else
#define RGB_DI_PIN 9
#endif
#define RGBLED_SPLIT {1, 1}
#define RGBLIGHT_SPLIT

// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#ifdef __AVR__
#define MATRIX_ROW_PINS { E6, D7, C6, D4 }
#define MATRIX_COL_PINS { D3, D2, F4, F5, F6 }
#else
#define BLE_NUS_MIN_INTERVAL 10 // default 60
#define BLE_NUS_MAX_INTERVAL 30 // default 75
#define BLE_HID_MAX_INTERVAL 30 // default 90
#define BLE_HID_SLAVE_LATENCY 4 // default 4

#define CONFIG_PIN_SCL 11
#define CONFIG_PIN_SDA 12

#define USE_BATTERY_PIN NRF_SAADC_INPUT_AIN5
#endif

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCING_DELAY 5
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
#define PREVENT_STUCK_MODIFIERS
#define COMBO_COUNT 28
#define COMBO_TERM 50

// Steno stuff
#define CUSTOM_STENO

#define STENO_DEBUG
/* #define DEBUG_FLASH */
/* #define DEBUG_STROKE */
#define DEBUG_HIST

#define RAW_USAGE_PAGE  0xFF60
#define RAW_USAGE_ID    0x61
#define MATRIX_SCAN_MS 20

#ifdef __AVR__
#ifdef CUSTOM_STENO
#undef VIRTSER_ENABLE
#endif
#endif

#define THIS_DEVICE_ROWS MATRIX_ROWS
#define THIS_DEVICE_COLS MATRIX_COLS
#define IS_LEFT_HAND true
#define ENABLE_STARTUP_ADV_NOLIST

#endif
