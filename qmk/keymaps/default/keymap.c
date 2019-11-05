#include "fissure.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_steno.h"

extern keymap_config_t keymap_config;

void matrix_init_user() {
    steno_set_mode(STENO_MODE_GEMINI);
}

// Layers
#define _BASE   0
#define _STENO  1
#define _GAME   2
#define _SYMBOL 3
#define _ACTION 4

#define KEYMAP( \
    L00, L01, L02, L03, L04, 				R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14, 				R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24, 				R20, R21, R22, R23, R24, \
    L30, L31, L32, L33, L34, 				R30, R31, R32, R33, R34, \
                         L42, L43, L44, 			R40, R41, R42 \
    ) \
    { \
        { L00, L01, L02, L03, L04 }, \
        { L10, L11, L12, L13, L14 }, \
        { L20, L21, L22, L23, L24 }, \
        { L30, L31, L32, L33, L34 }, \
        { KC_NO, KC_NO, L42, L43, L44 }, \
        { R04, R03, R02, R01, R00 }, \
        { R14, R13, R12, R11, R10 }, \
        { R24, R23, R22, R21, R20 }, \
        { R34, R33, R32, R31, R30 }, \
        { KC_NO, KC_NO, R42, R41, R40 } \
    }

void keyboard_pre_init_user() {
    setPinOutput(B3);
    setPinOutput(B2);
    setPinOutput(B6);
    writePinHigh(B2);
    writePinHigh(B3);
    writePinHigh(B6);
}

void suspend_power_down_user() {
    writePinLow(B2);
    writePinLow(B3);
    /* writePinLow(B6); */
}

void suspend_wakeup_init_user() {
    writePinHigh(B2);
    writePinHigh(B3);
    writePinHigh(B6);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (biton32(state)) {
    case _STENO:
        writePinLow(B2);
        writePinHigh(B3);
        writePinHigh(B6);
        break;
    case _GAME:
        writePinLow(B2);
        writePinLow(B3);
        writePinHigh(B6);
        break;
    case _SYMBOL:
        writePinLow(B3);
        writePinHigh(B2);
        writePinHigh(B6);
        break;
    case _ACTION:
        writePinLow(B6);
        writePinHigh(B3);
        writePinHigh(B2);
        break;
    default: //  for any other layers, or the default layer
        writePinHigh(B2);
        writePinHigh(B3);
        writePinHigh(B6);
        break;
    }
    return state;
}

#define DEL MT(MOD_LGUI, KC_DEL)
#define TAB MT(MOD_LCTL, KC_TAB)
#define ESC LT(_SYMBOL, KC_ESC)
#define ENT LT(_ACTION, KC_ENT)
#define SPC MT(MOD_LSFT, KC_SPC)
#define BKSP MT(MOD_LALT, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = KEYMAP(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, 
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
		DEL, TAB, ESC, ENT, SPC, BKSP),

    [_STENO] = KEYMAP(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
		STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR, 
		STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR, 
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, STN_ST3, KC_NO, KC_NO, KC_NO, KC_NO,
		STN_A, STN_O, MO(_SYMBOL), STN_E, STN_U, KC_NO),

    [_GAME] = KEYMAP(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, 
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
		KC_SPC, KC_LSFT, KC_LCTL, ENT, STN_U, KC_NO),

	[_SYMBOL] = KEYMAP(
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, 
        KC_ESC, KC_TILD, _______, _______, _______, KC_UNDS, KC_PLUS, KC_DQUO, KC_PIPE, KC_BSPC,
		KC_TAB, KC_GRV, _______, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, _______, _______, KC_ENT,
        KC_F11, _______, _______, _______, _______, KC_MINS, KC_EQL, KC_QUOT, KC_BSLS, KC_F12,
		_______, _______, _______, _______, _______, TG(_STENO)),

	[_ACTION] = KEYMAP(
        KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_BRID, KC_BRIU, 
		KC_ESC, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BSPC,
		KC_TAB, KC_BTN1, KC_BTN3, KC_BTN2, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_ENT,
		_______, _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,
		_______, _______, _______, _______, _______, _______),
};
