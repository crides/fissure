#include "fissure.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_steno.h"

// Layers
#define _BASE   0
#define _STENO  1
#define _SYMBOL1 2
#define _SYMBOL2 3
#define _FUNC 4

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

void keyboard_pre_init_user() {
}

void suspend_power_down_user() {
    /* rgblight_setrgb(RGB_TEAL); */
}

void suspend_wakeup_init_user() {
    /* rgblight_setrgb_at(26, 0, 13, 0); */
    /* rgblight_setrgb_at(RGB_GOLD, 1); */
    /* rgblight_set(); */
    rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
    case _STENO:
        break;
    case _SYMBOL1:
        break;
    case _SYMBOL2:
        break;
    case _FUNC:
        break;
    default: //  for any other layers, or the default layer
        break;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
    return true;
}

void matrix_init_user() {
    steno_set_mode(STENO_MODE_GEMINI);
}

#define DEL MT(MOD_LGUI, KC_DEL)
#define TAB MT(MOD_LCTL, KC_TAB)
#define ESC LT(_SYMBOL2, KC_ESC)
#define ENT LT(_SYMBOL1, KC_ENT)
#define SPC MT(MOD_RSFT, KC_SPC)
#define BKSP MT(MOD_LALT, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = KEYMAP(
		KC_Q,                    KC_W,         KC_E,           KC_R,         KC_T,         KC_Y,          KC_U,         KC_I,         KC_O,       KC_P,
		KC_A,                    KC_S,         KC_D,           KC_F,         KC_G,         KC_H,          KC_J,         KC_K,         KC_L,       KC_SCLN,
		KC_Z,                    KC_X,         KC_C,           KC_V,         KC_B,         KC_N,          KC_M,         KC_COMM,      KC_DOT,     KC_SLSH,
		DEL,                     TAB,          ESC,            ENT,          SPC,          BKSP),

    [_STENO] = KEYMAP(
        STN_N1,                  STN_N2,       STN_N3,         STN_N4,       STN_N5,       STN_N6,        STN_N7,       STN_N8,       STN_N9,     STN_NA,
		STN_S1,                  STN_TL,       STN_PL,         STN_HL,       STN_ST1,      STN_FR,        STN_PR,       STN_LR,       STN_TR,     STN_DR,
		STN_S2,                  STN_KL,       STN_WL,         STN_RL,       STN_ST2,      STN_RR,        STN_BR,       STN_GR,       STN_SR,     STN_ZR,
		STN_A,                   STN_O,        MO(_SYMBOL2),   STN_E,        STN_U,        XXXXXXX),

	[_SYMBOL1] = KEYMAP(
        LGUI(KC_1),              LGUI(KC_2),   LGUI(KC_3),     LGUI(KC_4),   LGUI(KC_5),   LGUI(KC_6),    LGUI(KC_7),   LGUI(KC_8),   KC_F11,     KC_F12,
        KC_1,                    KC_2,         KC_3,           KC_4,         KC_5,         KC_6,          KC_7,         KC_8,         KC_9,       KC_0,
		KC_F1,                   KC_F2,        KC_F3,          KC_F4,        KC_F5,        KC_F6,         KC_F7,        KC_F8,        KC_F9,      KC_F10,
		_______,                 _______,      MO(_FUNC),        _______,    _______,      _______),

	[_SYMBOL2] = KEYMAP(
        KC_TILD,                 KC_GRV,       KC_CIRC,        KC_DLR,       XXXXXXX,      XXXXXXX,       KC_LBRC,      KC_RBRC,      KC_LCBR,    KC_RCBR,
        KC_DQUO,                 KC_QUOT,      KC_AMPR,        KC_PIPE,      KC_PLUS,      KC_EQL,        KC_LPRN,      KC_RPRN,      KC_UNDS,    KC_COLN,
        KC_EXLM,                 KC_AT,        KC_HASH,        KC_ASTR,      KC_PERC,      KC_BSLS,       KC_MINS,      KC_LT,        KC_GT,      KC_QUES,
        _______,                 _______,      _______,      MO(_FUNC),      _______,      TG(_STENO)),

	[_FUNC] = KEYMAP(
		KC_BRID,                 KC_MUTE,      KC_VOLD,        KC_VOLU,      KC_BRIU,      KC_MS_L,       KC_MS_D,      KC_MS_U,      KC_MS_R,    KC_PSCR,
		XXXXXXX,                 KC_BTN1,      KC_BTN3,        KC_BTN2,      XXXXXXX,      KC_LEFT,       KC_DOWN,      KC_UP,        KC_RIGHT,   XXXXXXX,
		XXXXXXX,                 KC_MPRV,      KC_MPLY,        KC_MNXT,      XXXXXXX,      KC_WH_L,       KC_WH_D,      KC_WH_U,      KC_WH_R,    XXXXXXX,
		_______,                 _______,      _______,        _______,      _______,      _______),
};
