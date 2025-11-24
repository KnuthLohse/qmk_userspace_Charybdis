/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_SYMBOLS,
    LAYER_NUM_NAV,
    LAYER_POINTER,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE


enum { TD_SHIFT_CW, };
tap_dance_action_t tap_dance_actions[] = { [TD_SHIFT_CW] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, QK_CAPS_WORD_TOGGLE), };

#define SYMBOLS MO(LAYER_SYMBOLS)
#define NUM_NAV MO(LAYER_NUM_NAV)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)
#define TD_ShiftCapsWord TD(TD_SHIFT_CW)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

#define MT_C_GUI MT(KC_LGUI, KC_C)
#define MT_T_ALT MT(KC_LALT, KC_T)
#define MT_I_CTRL MT(KC_LCTL, KC_I)
#define MT_G_GUI MT(KC_LGUI, KC_G)
#define MT_S_ALT MT(KC_LALT, KC_S)
#define MT_R_CTRL MT(KC_LCTL, KC_R)
#define MT_SYM_NUM MT(MO(SYMBOLS),TG(NUM_NAV))
#define KC_ScrShot LGUI(LSFT(KC_S))


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_J,    KC_D,    KC_U,    KC_A,    KC_X,       KC_P,    KC_H,    KC_L,    KC_M,    KC_W, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_ScrShot,  MT_C_GUI,  MT_T_ALT, MT_I_CTRL,  KC_E, KC_O,   KC_B,   KC_N,   MT_R_CTRL,    MT_S_ALT, MT_G_GUI, KC_Q,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT, KC_F, KC_V, KC_LBRC,    KC_QUOT,    KC_SCLN,       KC_Z,    KC_Y, KC_COMM,  KC_DOT, KC_K, KC_RSFT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                         KC_DEL, TD_ShiftCapsWord,   KC_ENT,     KC_BSPC,  KC_SPACE,
                              KC_RALT, TG(LAYER_POINTER),     MT_SYM_NUM
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_SYMBOLS] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
  //     KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
       KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
  //     RGB_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LBRC,   KC_P7,   KC_P8,   KC_P9, KC_RBRC, XXXXXXX,
       KC_TAB, RALT(KC_E), LSFT(KC_SLASH), RALT(KC_8), RALT(KC_9), KC_GRAVE, LSFT(KC_1), KC_NONUS_BACKSLASH, LSFT(KC_NONUS_BACKSLASH), LSFT(KC_0), LSFT(KC_6),   KC_NO,
  //           €         , _               , [          , ]          , ^       , !             , <                 , >                         , =            , &
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
  //     RGB_TOG, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    KC_PPLS,   KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_PEQL,
       RGB_TOG, RALT(KC_MINS), LSFT(KC_7), RALT(KC_7), RALT(KC_0), LSFT(KC_RBRC), LSFT(KC_MINS), LSFT(KC_8), LSFT(KC_9), KC_SLASH, LSFT(KC_DOT), RALT(KC_Q),
  //        , \\           , /            , {          , }          , *              , ?              , (            , )            , -       , :             , @
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
  //    RGB_RMOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_PAST,   KC_P1,   KC_P2,   KC_P3, KC_PSLS, KC_PDOT,
      RGB_MOD, KC_NONUS_HASH, LSFT(KC_4), RALT(KC_NONUS_BACKSLASH), RALT(KC_RBRC), LSFT(KC_EQL), KC_RBRC, LSFT(KC_5), LSFT(KC_2), LSFT(KC_NONUS_HASH), LSFT(KC_COMMA), KC_NO,
  //.        , #            , $            , |                       , ~            , `             , +      , %            , "            , '                    , ;
      // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
  //                                XXXXXXX, XXXXXXX, _______,    XXXXXXX, _______,
  //                                         XXXXXXX, XXXXXXX,      KC_P0
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,      _______
  
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_NUM_NAV] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
  //     KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU,
  
          _______, KC_NO, KC_PGUP, KC_UP, KC_PGDN, KC_NO,     LSFT(KC_RBRC), KC_7, KC_8, KC_9, KC_RBRC, KC_SLASH,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
  //     KC_MPLY, KC_LEFT,   KC_UP, KC_DOWN, KC_RGHT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_MUTE,
       _______, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,    LSFT(KC_7), KC_4, KC_5, KC_6, KC_COMMA, KC_DOT,
  
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
  LCTL(KC_C), LCTL(KC_V), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, LSFT(KC_DOT), KC_1, KC_2, KC_3, KC_0, LSFT(KC_COMMA),
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  _______, _______, _______,    _______, _______,
                                           _______, _______,    _______
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
       QK_BOOT,  EE_CLR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,  EE_CLR,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD, S_D_MOD,    S_D_MOD, DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,    XXXXXXX, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       XXXXXXX, _______, DRGSCRL, SNIPING, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, SNIPING, DRGSCRL, _______, XXXXXXX,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,    KC_BTN3, KC_BTN1,
                                 XXXXXXX, TG(LAYER_POINTER),    KC_BTN2
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif
