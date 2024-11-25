// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "os_detection.h"
enum my_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)

#define _LO(x) LT(LAYER_LOWER, x)
#define _RA(x) LT(LAYER_RAISE, x)
#define _PT(x) LT(LAYER_POINTER, x)

#define _C(x) CTL_T(x)
#define _A(x) ALT_T(x)
#define _G(x) GUI_T(x)
#define _LS(x) LSFT_T(x)
#define _RS(x) RSFT_T(x)

#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#define LO_SPC  _LO(KC_SPC)
#define LO_COMM _LO(KC_COMM)
#define LO_DOT _LO(KC_DOT)

#define RA_COMM _RA(KC_COMM)
#define RA_DOT _RA(KC_DOT)

#define TO_PT TO(LAYER_POINTER)
#define TO_BA TO(LAYER_BASE)

enum keycodes {
     GO_LEFT = SAFE_RANGE, // ctrl + left, left desktop, win ctrl <
     GO_RGHT, // ctrl + right, right desktop, win ctrl >
     GO_UP, // ctrl + up, mission control, win tab

     WO_LEFT, // next word
     WO_RGHT, // prev word
     OS_LANG, // change language, ctrl + space at mac, right alt at window
     OS_PSCR,

     MC_LCMD, // work lcmd on mac, lctl on win
     MC_LCTL, // work lctl on mac, lgui on win

     VS_BRCK,
};

    /*
     * ┌───┐ ┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐ ┌───┬───┬───┐
     * │Esc│ │F1 │F2 │F3 │F4 ││F5 │F6 │F7 │F8 ││F9 │F10│F11│F12│ │PSc│Scr│Pse│
     * └───┘ └───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┬───┬───┐
     * │   │   │   │   │   │   │   │   │   │   │   │   │   │   │ │Ins│Hom│PgU│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤ ├───┼───┼───┤
     * │esc│esc│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │bs │bs │ │Del│End│PgD│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤ └───┴───┴───┘
     * │ctl│ctl│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ret│ret│ 
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤     ┌───┐
     * │shf│shf│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │shf│shf│     │ ↑ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤ ┌───┼───┼───┐
     * │   │   │   │gui│alt│spc│lwr│rse│nav│gui│alt│   │   │   │ │ ← │ ↓ │ → │
     * └───┘   └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘   └───┘ └───┴───┴───┘
     */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_INS,  KC_HOME, KC_PGUP,
        QK_GESC, QK_GESC, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, KC_BSPC,    KC_DEL,  KC_END,  KC_PGDN,
        MC_LCMD, MC_LCMD, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,  KC_ENT,                             
        KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    LO_COMM, KC_DOT,  PT_SLSH, KC_RSFT, KC_RSFT,             KC_UP,
        XXXXXXX,          XXXXXXX, MC_LCTL, KC_LALT, KC_SPC,  LOWER,   RAISE,   LOWER,   MC_LCTL, KC_LALT, XXXXXXX,          XXXXXXX,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_INS,  KC_HOME, KC_PGUP,
        QK_GESC, QK_GESC, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,  KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, KC_BSLS,    KC_DEL,  KC_END,  KC_PGDN,
        MC_LCMD, MC_LCMD, XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, KC_QUOT, KC_QUOT,                             
        KC_LSFT, KC_LSFT, XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, KC_RSFT, KC_RSFT,             KC_UP,
        XXXXXXX,          XXXXXXX, MC_LCTL, KC_LALT, XXXXXXX, _______, TO_PT,   _______, MC_LCTL, KC_LALT, XXXXXXX,          XXXXXXX,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [2] = LAYOUT(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_PSCR, KC_SCRL, KC_PAUS,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_INS,  KC_HOME, KC_PGUP,
        QK_GESC, QK_GESC, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX, XXXXXXX, KC_INS,  XXXXXXX, OS_PSCR, KC_DEL,  KC_DEL,     KC_DEL,  KC_END,  KC_PGDN,
        MC_LCMD, MC_LCMD, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,  XXXXXXX, KC_RCTL, KC_RSFT, OS_LANG, KC_RGUI, XXXXXXX, XXXXXXX,                             
        KC_LSFT, KC_LSFT, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F12,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT, KC_RSFT,             KC_UP,
        XXXXXXX,          XXXXXXX, MC_LCTL, KC_LALT, XXXXXXX, TO_PT,   _______, _______, MC_LCTL, KC_LALT, XXXXXXX,          XXXXXXX,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [3] = LAYOUT(
        KC_ESC,           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    QK_RBT,  QK_BOOT, EE_CLR,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_INS,  KC_HOME, KC_PGUP,
        KC_ESC,  KC_ESC,  TO_BA,   GO_UP,   XXXXXXX, XXXXXXX, XXXXXXX, QK_RBT,  QK_BOOT, EE_CLR,  XXXXXXX, XXXXXXX, KC_DEL,  KC_DEL,     KC_DEL,  KC_END,  KC_PGDN,
        MC_LCMD, MC_LCMD, GO_LEFT, XXXXXXX, GO_RGHT, XXXXXXX, XXXXXXX, WO_LEFT, XXXXXXX, XXXXXXX, WO_RGHT, XXXXXXX, XXXXXXX, XXXXXXX,                             
        KC_LSFT, KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, VS_BRCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_RSFT, KC_RSFT,             KC_UP,
        XXXXXXX,          XXXXXXX, MC_LCTL, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, MC_LCTL, KC_LALT, XXXXXXX,          XXXXXXX,    WO_LEFT, KC_DOWN, WO_RGHT
    ),
};



bool process_record_user(uint16_t keycode, keyrecord_t *record) 
{
     os_variant_t host = detected_host_os();
     switch (keycode) 
     {
          case OS_LANG:
               if (record->event.pressed)
               {
                    if (host == OS_WINDOWS)
                    {
                         tap_code(KC_RALT);
                    }
                    else
                    {
                         register_code(KC_LCTL);
                         tap_code(KC_SPACE);
                         unregister_code(KC_LCTL);
                    }
               }

               return false;
               break;
          case OS_PSCR:
               if (host == OS_WINDOWS)
               {
                    if (record->event.pressed)
                    {
                         register_code(KC_LGUI);
                         register_code(KC_LSFT);
                         tap_code(KC_S);
                         unregister_code(KC_LGUI);
                         unregister_code(KC_LSFT);
                    }
               }
               else
               {
                    if (record->event.pressed)
                    {
                         register_code(KC_LGUI);
                         register_code(KC_LSFT);
                         tap_code(KC_4);
                         unregister_code(KC_LGUI);
                         unregister_code(KC_LSFT);
                    }
               }

               return false;
               break;
          case WO_LEFT:
               if (record->event.pressed)
               {
                    if (host == OS_WINDOWS)
                    {
                         register_code(KC_LCTL);
                         tap_code(KC_LEFT);
                         unregister_code(KC_LCTL);
                    } 
                    else
                    {
                         register_code(KC_LALT);
                         tap_code(KC_LEFT);
                         unregister_code(KC_LALT);
                    }
               }

               return false;
               break;
          case WO_RGHT:
               if (record->event.pressed)
               {
                    if (host == OS_WINDOWS)
                    {
                         register_code(KC_LCTL);
                         tap_code(KC_RIGHT);
                         unregister_code(KC_LCTL);
                    }
                    else
                    {
                         register_code(KC_LALT);
                         tap_code(KC_RIGHT);
                         unregister_code(KC_LALT);
                    }
               }

               return false;
               break;
          case MC_LCMD:
               if (host == OS_WINDOWS)
               {
                    if (record->event.pressed)
                         register_code(KC_LCTL);
                    else
                         unregister_code(KC_LCTL);
               }
               else
               {
                    if (record->event.pressed)
                         register_code(KC_LGUI);
                    else
                         unregister_code(KC_LGUI);
               }

               return false;
               break;
          case MC_LCTL:
               if (host == OS_WINDOWS)
               {
                    if (record->event.pressed)
                         register_code(KC_LGUI);
                    else
                         unregister_code(KC_LGUI);
               }
               else
               {
                    if (record->event.pressed)
                         register_code(KC_LCTL);
                    else
                         unregister_code(KC_LCTL);
               }

               return false;
               break;
          case GO_LEFT:
               if (host == OS_WINDOWS)
               {
                    if (record->event.pressed)
                    {
                         register_code(KC_LGUI);
                         register_code(KC_LCTL);
                         tap_code(KC_LEFT);
                         unregister_code(KC_LCTL);
                         unregister_code(KC_LGUI);
                    }
               }
               else
               {
                    if (record->event.pressed)
                    {
                         register_code(KC_LCTL);
                         tap_code(KC_LEFT);
                         unregister_code(KC_LCTL);
                    }
               }

               return false;
               break;
          case GO_RGHT:
               if (host == OS_WINDOWS)
               {
                    if (record->event.pressed)
                    {
                         register_code(KC_LGUI);
                         register_code(KC_LCTL);
                         tap_code(KC_RIGHT);
                         unregister_code(KC_LCTL);
                         unregister_code(KC_LGUI);
                    }
               } 
               else
               {
                    if (record->event.pressed)
                    {
                         register_code(KC_LCTL);
                         tap_code(KC_RIGHT);
                         unregister_code(KC_LCTL);
                    }
               }

               return false;
               break;
          case GO_UP:
               if (host == OS_WINDOWS)
               {
                    if (record->event.pressed)
                    {
                         register_code(KC_LGUI);
                         tap_code(KC_TAB);
                         unregister_code(KC_LGUI);
                    }
               }
               else
               {
                    if (record->event.pressed)
                    {
                         register_code(KC_LCTL);
                         tap_code(KC_UP);
                         unregister_code(KC_LCTL);
                    }
               }

               return false;
               break;

          case VS_BRCK:
               if (host == OS_WINDOWS)
               {
                    if (record->event.pressed)
                    {
                         register_code(KC_LCTL);
                         register_code(KC_LALT);
                         tap_code(KC_PAUS);
                         unregister_code(KC_LALT);
                         unregister_code(KC_LCTL);
                    }
               }
               return false;
               break;

               
     }

     return true;
};

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_ENT):
            return true;
        default:
            return false;
    }
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
     // for tapping term 300
    switch (keycode) {
        case LSFT_T(KC_ENT):
            return TAPPING_TERM / 5 * 3;

        default:
            return TAPPING_TERM;
    }
}