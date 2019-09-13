#include "fissure.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define KEYMAP( \
    L00, L01, L02, L03, L04, 				R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14, 				R10, R11, R12, R13, R14, \
    L20, L21, L22, L23, L24, 				R20, R21, R22, R23, R24, \
    L30, L31, L32, L33, L34, 				R30, R31, R32, R33, R34 \
    ) \
    { \
        { L00, L01, L02, L03, L04 }, \
        { L10, L11, L12, L13, L14 }, \
        { L20, L21, L22, L23, L24 }, \
        { L30, L31, L32, L33, L34 }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO}, \
        { R04, R03, R02, R01, R00 }, \
        { R14, R13, R12, R11, R10 }, \
        { R24, R23, R22, R21, R20 }, \
        { R34, R33, R32, R31, R30 }, \
        { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
    }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP(
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, 
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
        KC_LALT, KC_LGUI, KC_LCTL, KC_LSFT, MO(1), MO(2), KC_SPC, KC_RCTL, KC_RGUI, KC_RALT),

	KEYMAP(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
        KC_F11, _______, _______, KC_TAB, KC_ESC, KC_BSPC, KC_ENT, _______, KC_DEL, KC_F12,
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, 
		_______, _______, _______, _______, _______, MO(3), _______, _______, _______, _______),

	KEYMAP(
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_TILD, _______, _______, _______, KC_LCBR, KC_RCBR, KC_UNDS, KC_PLUS, KC_DQUO, KC_PIPE,
		KC_GRV, _______, _______, _______, KC_LBRC, KC_RBRC, KC_MINS, KC_EQL, KC_QUOT, KC_BSLS,
		_______, _______, _______, _______, MO(3), _______, _______, _______, _______, _______),

    KEYMAP(
		_______, KC_MPRV, KC_MPLY, KC_MNXT, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______,
		KC_BRID, KC_BTN1, KC_BTN3, KC_BTN2, KC_BRIU, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,
		_______, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
};
