#include "fissure.h"
#include "action_layer.h"
#include "eeconfig.h"

// Layers
#define _BASE   0
#define _SYMBOL1 1
#define _SYMBOL2 2
#define _FUNC 3

#define KEYMAP( \
    L10, L11, L12, L13, L14, 				R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24, 				R20, R21, R22, R23, R24, \
    L30, L31, L32, L33, L34, 				R30, R31, R32, R33, R34, \
                         L42, L43, L44, 			R40, R41, R42 \
    ) \
    { \
        { L10, L11, L12, L13, L14 }, \
        { L20, L21, L22, L23, L24 }, \
        { L30, L31, L32, L33, L34 }, \
        { XXXXXXX, XXXXXXX, L42, L43, L44 }, \
        { R14, R13, R12, R11, R10 }, \
        { R24, R23, R22, R21, R20 }, \
        { R34, R33, R32, R31, R30 }, \
        { XXXXXXX, XXXXXXX, R42, R41, R40 } \
    }

void set_hsv(uint8_t a, uint8_t b, uint8_t c) {
    rgblight_sethsv(a, b, (uint8_t) c * 0.2);
}

void keyboard_pre_init_user() {
    set_hsv(HSV_TEAL);
}

void suspend_power_down_user() {
    set_hsv(0, 0, 0);
}

void suspend_wakeup_init_user() {
    set_hsv(0, 0, 0);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
    case _SYMBOL1:
        set_hsv(HSV_GREEN);
        break;
    case _SYMBOL2:
        set_hsv(HSV_CYAN);
        break;
    case _FUNC:
        set_hsv(HSV_MAGENTA);
        break;
    default: //  for any other layers, or the default layer
        set_hsv(0, 0, 0);
        break;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    /* uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed); */
    // For keylogging
    uprintf("[kl] %u:%u %c\n", record->event.key.row, record->event.key.col, record->event.pressed ? 'p' : 'P');
#endif 
    return true;
}

#define DEL MT(MOD_LGUI, KC_DEL)
#define TAB MT(MOD_LCTL, KC_TAB)
#define ESC LT(_SYMBOL2, KC_ESC)
#define ENT LT(_SYMBOL1, KC_ENT)
#define SPC MT(MOD_LSFT, KC_SPC)
#define BKSP MT(MOD_LALT, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = KEYMAP(
		KC_Q,                    KC_W,         KC_E,           KC_R,         KC_T,         KC_Y,          KC_U,         KC_I,         KC_O,       KC_P,
		KC_A,                    KC_S,         KC_D,           KC_F,         KC_G,         KC_H,          KC_J,         KC_K,         KC_L,       KC_SCLN,
		KC_Z,                    KC_X,         KC_C,           KC_V,         KC_B,         KC_N,          KC_M,         KC_COMM,      KC_DOT,     KC_SLSH,
		DEL,                     TAB,          ESC,            ENT,          SPC,          BKSP),

	[_SYMBOL1] = KEYMAP(
        LGUI(KC_1),              LGUI(KC_2),   LGUI(KC_3),     LGUI(KC_4),   LGUI(KC_5),   LGUI(KC_6),    LGUI(KC_7),   LGUI(KC_8),   KC_F11,     KC_F12,
        KC_1,                    KC_2,         KC_3,           KC_4,         KC_5,         KC_6,          KC_7,         KC_8,         KC_9,       KC_0,
		KC_F1,                   KC_F2,        KC_F3,          KC_F4,        KC_F5,        KC_F6,         KC_F7,        KC_F8,        KC_F9,      KC_F10,
		_______,                 _______,      MO(_FUNC),        _______,    _______,      _______),

	[_SYMBOL2] = KEYMAP(
        KC_TILD,                 KC_GRV,       KC_CIRC,        KC_DLR,       KC_PERC,      KC_BSLS,       KC_LBRC,      KC_RBRC,      KC_LCBR,    KC_RCBR,
        KC_DQUO,                 KC_QUOT,      KC_AMPR,        KC_PIPE,      KC_PLUS,      KC_EQL,        KC_LPRN,      KC_RPRN,      KC_UNDS,    KC_COLN,
        KC_EXLM,                 KC_AT,        KC_HASH,        KC_ASTR,      XXXXXXX,      XXXXXXX,       KC_MINS,      KC_LT,        KC_GT,      KC_QUES,
        _______,                 _______,      _______,      MO(_FUNC),      _______,      _______),

	[_FUNC] = KEYMAP(
		KC_BRID,                 KC_MUTE,      KC_VOLD,        KC_VOLU,      KC_BRIU,      KC_MS_L,       KC_MS_D,      KC_MS_U,      KC_MS_R,    KC_PSCR,
		XXXXXXX,                 KC_BTN1,      KC_BTN3,        KC_BTN2,      XXXXXXX,      KC_LEFT,       KC_DOWN,      KC_UP,        KC_RIGHT,   XXXXXXX,
		XXXXXXX,                 KC_MPRV,      KC_MPLY,        KC_MNXT,      XXXXXXX,      KC_WH_L,       KC_WH_D,      KC_WH_U,      KC_WH_R,    XXXXXXX,
		_______,                 _______,      _______,        _______,      _______,      _______),
};
