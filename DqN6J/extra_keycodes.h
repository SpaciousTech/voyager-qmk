// extra_keycodes.h

#pragma once
#include QMK_KEYBOARD_H

// Short aliases for Home row mods and other tap-hold keys
#define HRM_A LGUI_T(KC_A)
#define HRM_S LSFT_T(KC_S)
#define HRM_D LOPT_T(KC_D)
#define HRM_F LCTL_T(KC_F)
#define HRM_J RCTL_T(KC_J)
#define HRM_K ROPT_T(KC_K)
#define HRM_L RSFT_T(KC_L)
#define HRM_SCLN RGUI_T(KC_SCLN)                     // semicolon (; :)
#define LCG_EQUAL MT(MOD_LCTL | MOD_LGUI, KC_EQUAL)  // =
#define RCLA_T(kc) MT(MOD_RCTL | MOD_LALT, kc)
// #define RCALT_BSLS MT(MOD_RCTL | MOD_RALT, KC_BSLS)
#define LT_ESC LT(SYM, KC_ESC)  // Layer-Tap Escape
#define LT_REP LT(SYM, KC_0)    // Layer-Tap Repeat
#define KC_EURO LSA(KC_2)       // Euro symbol
#define KC_GBP LALT(KC_3)       // British Pound symbol