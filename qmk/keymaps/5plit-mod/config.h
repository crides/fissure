#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

#define USE_I2C

#define MASTER_LEFT
/* #define MASTER_RIGHT */
// #define EE_HANDS
#define FORCE_NKRO
#define COMBO_COUNT 30
#define TAPPING_TERM 200
/* #define B6_AUDIO */
/* #define NO_MUSIC_MODE */
/* #define AUDIO_CLICKY */
/* #define AUDIO_CLICKY_FREQ_RANDOMNESS 1.0f */

/* #define RGB_DI_PIN D4 */
/* #define RGBLED_NUM 2 */

// From micro_32
#define PREVENT_STUCK_MODIFIERS
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD
#define PERMISSIVE_HOLD

#endif
