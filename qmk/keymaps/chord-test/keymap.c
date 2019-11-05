#include "fissure.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

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

enum combos {
    QA_1,
    WS_2,
    ED_3,
    RF_4,
    TG_5,
    YH_6,
    UJ_7,
    IK_8,
    OL_9,
    PS_0,
    AZ_1,
    SX_2,
    DC_3,
    FV_4,
    GB_5,
    HN_6,
    JM_7,
    _KC_8,
    LD_9,
    SS_0,
};

const uint16_t PROGMEM qa_combo[] = {KC_Q, KC_A, COMBO_END};
const uint16_t PROGMEM ws_combo[] = {KC_W, KC_S, COMBO_END};
const uint16_t PROGMEM ed_combo[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM rf_combo[] = {KC_R, KC_F, COMBO_END};
const uint16_t PROGMEM tg_combo[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM yh_combo[] = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM uj_combo[] = {KC_U, KC_J, COMBO_END};
const uint16_t PROGMEM ik_combo[] = {KC_I, KC_K, COMBO_END};
const uint16_t PROGMEM ol_combo[] = {KC_O, KC_L, COMBO_END};
const uint16_t PROGMEM ps_combo[] = {KC_P, KC_SCLN, COMBO_END};
const uint16_t PROGMEM az_combo[] = {KC_A, KC_Z, COMBO_END};
const uint16_t PROGMEM sx_combo[] = {KC_S, KC_X, COMBO_END};
const uint16_t PROGMEM dc_combo[] = {KC_D, KC_C, COMBO_END};
const uint16_t PROGMEM fv_combo[] = {KC_F, KC_V, COMBO_END};
const uint16_t PROGMEM gb_combo[] = {KC_G, KC_B, COMBO_END};
const uint16_t PROGMEM hn_combo[] = {KC_H, KC_N, COMBO_END};
const uint16_t PROGMEM jm_combo[] = {KC_J, KC_M, COMBO_END};
const uint16_t PROGMEM kc_combo[] = {KC_K, KC_COMM, COMBO_END};
const uint16_t PROGMEM ld_combo[] = {KC_L, KC_DOT, COMBO_END};
const uint16_t PROGMEM ss_combo[] = {KC_SCLN, KC_SLSH, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [QA_1] = COMBO(qa_combo, KC_EXLM),
    [WS_2] = COMBO(ws_combo, KC_AT),
    [ED_3] = COMBO(ed_combo, KC_HASH),
    [RF_4] = COMBO(rf_combo, KC_DLR),
    [TG_5] = COMBO(tg_combo, KC_PERC),
    [YH_6] = COMBO(yh_combo, KC_CIRC),
    [UJ_7] = COMBO(uj_combo, KC_AMPR),
    [IK_8] = COMBO(ik_combo, KC_ASTR),
    [OL_9] = COMBO(ol_combo, KC_LPRN),
    [PS_0] = COMBO(ps_combo, KC_RPRN),
    [AZ_1] = COMBO(az_combo, KC_1),
    [SX_2] = COMBO(sx_combo, KC_2),
    [DC_3] = COMBO(dc_combo, KC_3),
    [FV_4] = COMBO(fv_combo, KC_4),
    [GB_5] = COMBO(gb_combo, KC_5),
    [HN_6] = COMBO(hn_combo, KC_6),
    [JM_7] = COMBO(jm_combo, KC_7),
    [_KC_8] = COMBO(kc_combo, KC_8),
    [LD_9] = COMBO(ld_combo, KC_9),
    [SS_0] = COMBO(ss_combo, KC_0),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    KEYMAP(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, 
		KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, 
		KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, 
		KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
		KC_LCTL, KC_LSFT, MO(1), MO(2), KC_SPC, KC_LGUI),

	KEYMAP(
		KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, 
        KC_ESC, KC_TILD, _______, _______, _______, KC_UNDS, KC_PLUS, KC_DQUO, KC_PIPE, KC_BSPC,
		KC_TAB, KC_GRV, _______, KC_LBRC, KC_LCBR, KC_RCBR, KC_RBRC, _______, _______, KC_ENT,
        KC_F11, _______, _______, _______, _______, KC_MINS, KC_EQL, KC_QUOT, KC_BSLS, KC_F12,
		_______, _______, _______, _______, _______, _______),

	KEYMAP(
        KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, KC_BRID, KC_BRIU, 
		KC_ESC, _______, OUT_BT, OUT_USB, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BSPC,
		KC_TAB, KC_BTN1, KC_BTN3, KC_BTN2, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_ENT,
		_______, _______, _______, _______, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, _______,
		_______, _______, _______, _______, _______, _______),
};
