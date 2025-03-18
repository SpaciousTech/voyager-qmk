#include QMK_KEYBOARD_H
#include "select_word.h"
#include "version.h"
#include "i18n.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

enum custom_keycodes
{
    RGB_SLD = ML_SAFE_RANGE,
    // Adding Keycodes for QMK Select Word 
    SELWORD,
    SELWBAK,
    SELLINE,
};

// Adding Keycodes for QMK Select Word
uint16_t SELECT_WORD_KEYCODE = SELWORD;
uint16_t SELECT_WORD_BACK_KEYCODE = SELWBAK;
uint16_t SELECT_WORD_LINE_KEYCODE = SELLINE;


typedef struct
{
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;
tap_dance_action_t *action;

enum tap_dance_codes
{
    DANCE_0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_voyager(
        MT(MOD_LCTL | MOD_LGUI, KC_EQUAL), KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,
        MT(MOD_LCTL | MOD_LALT, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, MT(MOD_RCTL | MOD_RALT, KC_BSLS),
        LT(2, KC_ESCAPE), MT(MOD_LGUI, KC_A), MT(MOD_LSFT, KC_S), MT(MOD_LALT, KC_D), MT(MOD_LCTL, KC_F), KC_G, KC_H, MT(MOD_RCTL, KC_J), MT(MOD_RALT, KC_K), MT(MOD_RSFT, KC_L), MT(MOD_RGUI, KC_SCLN), LT(6, KC_QUOTE),
        TT(1), MEH_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, ALL_T(KC_SLASH), MT(MOD_RCTL, KC_ENTER),
        LT(3, KC_BSPC), TD(DANCE_0), MT(MOD_RSFT, KC_SPACE), LT(1, KC_TAB)),
    [1] = LAYOUT_voyager(
        KC_TRANSPARENT, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,
        KC_TRANSPARENT, TO(3), CW_TOGG, SELLINE, SELWBAK, SELWORD, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_LEFT_GUI, KC_LEFT_SHIFT, KC_LEFT_ALT, KC_LEFT_CTRL, LGUI(KC_A), LALT(KC_LEFT), KC_LEFT, KC_DOWN, KC_RIGHT, LALT(KC_RIGHT), KC_TRANSPARENT,
        KC_TRANSPARENT, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LGUI(LSFT(KC_Z)), KC_NO, KC_NO, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [2] = LAYOUT_voyager(
        QK_LLCK, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,
        KC_TRANSPARENT, KC_TRANSPARENT, LALT(LGUI(LCTL(LSFT(KC_W)))), LALT(LGUI(LCTL(LSFT(KC_E)))), LALT(LGUI(LCTL(LSFT(KC_R)))), LALT(LGUI(LCTL(LSFT(KC_T)))), LALT(LGUI(LCTL(LSFT(KC_Y)))), LALT(LGUI(LCTL(LSFT(KC_U)))), LALT(LGUI(LCTL(LSFT(KC_I)))), LALT(LGUI(LCTL(LSFT(KC_O)))), LALT(LGUI(LCTL(LSFT(KC_P)))), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, LALT(LGUI(LCTL(LSFT(KC_S)))), LALT(LGUI(LCTL(LSFT(KC_D)))), LGUI(KC_SPACE), LALT(LGUI(LCTL(LSFT(KC_G)))), LALT(LGUI(LCTL(LSFT(KC_H)))), LALT(LGUI(LCTL(LSFT(KC_J)))), LALT(LGUI(LCTL(LSFT(KC_K)))), LALT(LGUI(LCTL(LSFT(KC_L)))), KC_TRANSPARENT, KC_TRANSPARENT,
        TO(0), KC_TRANSPARENT, KC_TRANSPARENT, LALT(LGUI(LCTL(LSFT(KC_C)))), LALT(LGUI(LCTL(LSFT(KC_V)))), KC_TRANSPARENT, LALT(LGUI(LCTL(LSFT(KC_N)))), LALT(LGUI(LCTL(LSFT(KC_M)))), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [3] = LAYOUT_voyager(
        QK_LLCK, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINUS,
        KC_TRANSPARENT, TO(1), CW_TOGG, KC_GRAVE, KC_LPRN, KC_RPRN, KC_EXLM, KC_UNDS, KC_MINUS, KC_EQUAL, KC_PLUS, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_CIRC, KC_TILD, KC_DQUO, KC_LBRC, KC_RBRC, KC_HASH, KC_DLR, LALT(LSFT(KC_2)), LALT(KC_3), KC_COLN, KC_TRANSPARENT,
        TO(0), KC_NO, KC_PIPE, KC_AMPR, KC_LCBR, KC_RCBR, KC_PERC, KC_ASTR, KC_LABK, KC_RABK, KC_QUES, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [4] = LAYOUT_voyager(
        KC_NO, KC_NO, KC_NO, QK_DYNAMIC_TAPPING_TERM_DOWN, QK_DYNAMIC_TAPPING_TERM_UP, QK_DYNAMIC_TAPPING_TERM_PRINT, KC_AUDIO_VOL_UP, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_NO, TO(0),
        RGB_VAI, RGB_TOG, RGB_SLD, RGB_MODE_FORWARD, RGB_SPD, RGB_SPI, KC_AUDIO_VOL_DOWN, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO,
        RGB_VAD, TOGGLE_LAYER_COLOR, RGB_SAD, RGB_SAI, RGB_HUD, RGB_HUI, KC_AUDIO_MUTE, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO,
        TO(0), KC_NO, KC_NO, KC_NO, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_NO, KC_NO, LGUI(KC_COMMA), KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [5] = LAYOUT_voyager(
        KC_NO, KC_NO, LALT(LCTL(KC_LBRC)), KC_NO, LALT(LCTL(KC_RBRC)), KC_NO, KC_NO, LALT(LCTL(KC_LBRC)), KC_NO, LALT(LCTL(KC_RBRC)), KC_NO, TO(0),
        KC_NO, KC_NO, LALT(LCTL(KC_KP_7)), LALT(LCTL(KC_KP_8)), LALT(LCTL(KC_KP_9)), KC_NO, KC_NO, LALT(LCTL(KC_KP_7)), LALT(LCTL(KC_KP_8)), LALT(LCTL(KC_KP_9)), KC_NO, KC_NO,
        KC_TRANSPARENT, KC_NO, LALT(LCTL(KC_4)), LALT(LCTL(KC_KP_5)), LALT(LCTL(KC_6)), KC_NO, KC_NO, LALT(LCTL(KC_4)), LALT(LCTL(KC_KP_5)), LALT(LCTL(KC_6)), KC_NO, KC_NO,
        TO(0), KC_NO, LALT(LCTL(KC_KP_1)), LALT(LCTL(KC_KP_2)), LALT(LCTL(KC_KP_3)), KC_NO, KC_NO, LALT(LCTL(KC_KP_1)), LALT(LCTL(KC_KP_2)), LALT(LCTL(KC_KP_3)), KC_NO, LALT(LCTL(KC_ENTER)),
        LALT(LCTL(KC_DOWN)), LALT(LCTL(US_UNDS)), LALT(LCTL(US_PLUS)), KC_TRANSPARENT),
    [6] = LAYOUT_voyager(
        QK_LLCK, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, LALT(LCTL(LSFT(KC_Q))), LALT(LCTL(LSFT(KC_W))), LGUI(LCTL(KC_SPACE)), LALT(LCTL(LSFT(KC_R))), LALT(LSFT(KC_T)), LALT(LCTL(LSFT(KC_Y))), LALT(LCTL(LSFT(KC_U))), LALT(LCTL(LSFT(KC_I))), LALT(LCTL(LSFT(KC_O))), LALT(LCTL(LSFT(KC_P))), LALT(LCTL(LSFT(KC_BSLS))),
        KC_TRANSPARENT, LALT(LCTL(LSFT(KC_A))), LALT(LCTL(LSFT(KC_S))), LALT(LCTL(LSFT(KC_D))), LGUI(KC_SPACE), LALT(LCTL(LSFT(KC_G))), LALT(LCTL(LSFT(KC_H))), LALT(LCTL(LSFT(KC_J))), LALT(LCTL(LSFT(KC_K))), LALT(LCTL(LSFT(KC_L))), LALT(LCTL(LSFT(KC_SCLN))), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_NO, KC_NO, LALT(LCTL(KC_C)), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
};

const uint16_t PROGMEM combo0[] = {KC_MINUS, KC_0, COMBO_END};
const uint16_t PROGMEM combo1[] = {KC_BSPC, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM combo2[] = {MT(MOD_LCTL | MOD_LGUI, KC_EQUAL), KC_2, COMBO_END};
const uint16_t PROGMEM combo3[] = {MT(MOD_LCTL | MOD_LGUI, KC_EQUAL), KC_3, COMBO_END};
const uint16_t PROGMEM combo4[] = {MT(MOD_LCTL | MOD_LGUI, KC_EQUAL), KC_4, COMBO_END};
const uint16_t PROGMEM combo5[] = {MT(MOD_LCTL | MOD_LGUI, KC_EQUAL), KC_5, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, TO(0)),
    COMBO(combo1, TO(0)),
    COMBO(combo2, TO(2)),
    COMBO(combo3, TO(3)),
    COMBO(combo4, TO(4)),
    COMBO(combo5, TO(5)),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case MT(MOD_LCTL | MOD_LGUI, KC_EQUAL):
        return g_tapping_term - 50;
    case MT(MOD_LCTL | MOD_LALT, KC_TAB):
        return g_tapping_term - 50;
    case LT(2, KC_ESCAPE):
        return g_tapping_term - 50;
    case LT(3, KC_BSPC):
        return g_tapping_term - 25;
    case TD(DANCE_0):
        return g_tapping_term - 50;
    case MT(MOD_RCTL | MOD_RALT, KC_BSLS):
        return g_tapping_term - 50;
    case LT(6, KC_QUOTE):
        return g_tapping_term - 50;
    case ALL_T(KC_SLASH):
        return g_tapping_term - 25;
    case MT(MOD_RCTL, KC_ENTER):
        return g_tapping_term - 50;
    case MT(MOD_RSFT, KC_SPACE):
        return g_tapping_term - 50;
    case LT(1, KC_TAB):
        return g_tapping_term - 50;
    default:
        return g_tapping_term;
    }
}

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void)
{
    rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = {{156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {87, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {87, 255, 255}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {34, 255, 255}, {87, 255, 255}, {0, 255, 219}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {118, 255, 255}, {0, 255, 219}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {87, 255, 255}, {34, 255, 255}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {87, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {0, 255, 219}, {87, 255, 255}, {0, 255, 219}, {118, 255, 255}},

    [1] = {{161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {87, 255, 255}, {87, 255, 255}, {242, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {87, 255, 255}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {203, 255, 255}, {87, 255, 255}, {203, 255, 255}, {203, 255, 255}, {203, 255, 255}, {203, 255, 255}, {203, 255, 255}, {118, 255, 255}, {0, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {0, 0, 0}, {0, 0, 0}, {89, 255, 255}, {0, 0, 0}, {0, 0, 0}, {87, 255, 255}, {146, 255, 255}, {89, 255, 255}, {89, 255, 255}, {89, 255, 255}, {146, 255, 255}, {87, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {87, 255, 255}, {0, 255, 255}, {118, 255, 255}},

    [2] = {{0, 255, 219}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {87, 255, 255}, {0, 0, 0}, {121, 211, 222}, {121, 211, 222}, {121, 211, 222}, {41, 245, 224}, {87, 255, 255}, {0, 0, 0}, {121, 211, 222}, {188, 186, 204}, {108, 255, 255}, {156, 217, 143}, {87, 255, 255}, {236, 255, 255}, {0, 0, 0}, {23, 171, 255}, {9, 255, 199}, {0, 0, 0}, {114, 255, 182}, {0, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {121, 211, 222}, {121, 211, 222}, {121, 211, 222}, {184, 255, 255}, {121, 211, 222}, {87, 255, 255}, {121, 211, 222}, {121, 211, 222}, {121, 211, 222}, {121, 211, 222}, {0, 0, 0}, {87, 255, 255}, {45, 255, 255}, {162, 227, 246}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {87, 255, 255}, {0, 255, 255}, {114, 255, 182}},

    [3] = {{0, 255, 219}, {40, 255, 255}, {40, 255, 255}, {40, 255, 255}, {40, 255, 255}, {40, 255, 255}, {87, 255, 255}, {87, 255, 255}, {0, 246, 255}, {197, 214, 255}, {132, 255, 252}, {132, 255, 252}, {87, 255, 255}, {197, 214, 255}, {197, 214, 255}, {197, 214, 255}, {132, 255, 252}, {132, 255, 252}, {87, 255, 255}, {0, 0, 0}, {197, 214, 255}, {197, 214, 255}, {132, 255, 252}, {132, 255, 252}, {118, 255, 255}, {0, 255, 255}, {40, 255, 255}, {39, 255, 255}, {39, 255, 255}, {39, 255, 255}, {39, 255, 255}, {39, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {87, 255, 255}, {175, 255, 255}, {175, 255, 255}, {147, 255, 255}, {175, 255, 255}, {175, 255, 255}, {87, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {87, 255, 255}, {0, 255, 255}, {118, 255, 255}},

    [4] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {61, 178, 154}, {83, 255, 206}, {202, 211, 219}, {102, 250, 255}, {132, 255, 255}, {116, 255, 255}, {52, 255, 255}, {32, 255, 255}, {15, 255, 255}, {174, 255, 233}, {156, 255, 255}, {190, 255, 255}, {215, 255, 255}, {232, 255, 255}, {0, 255, 255}, {110, 255, 160}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {32, 251, 255}, {32, 251, 255}, {118, 255, 255}, {0, 255, 219}, {199, 255, 255}, {162, 223, 235}, {162, 223, 235}, {162, 223, 235}, {0, 0, 0}, {110, 255, 160}, {207, 174, 226}, {0, 0, 0}, {89, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {217, 219, 170}, {89, 255, 255}, {89, 255, 255}, {89, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {230, 252, 192}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 219}, {118, 255, 255}},

    [5] = {{0, 0, 0}, {0, 0, 0}, {203, 255, 255}, {0, 0, 0}, {203, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 218, 204}, {154, 255, 255}, {0, 218, 204}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {154, 255, 255}, {120, 254, 255}, {154, 255, 255}, {0, 0, 0}, {110, 255, 160}, {0, 0, 0}, {0, 218, 204}, {154, 255, 255}, {0, 218, 204}, {0, 0, 0}, {0, 218, 204}, {0, 255, 219}, {0, 0, 0}, {203, 255, 255}, {0, 0, 0}, {203, 255, 255}, {0, 0, 0}, {110, 255, 160}, {0, 0, 0}, {0, 218, 204}, {154, 255, 255}, {0, 218, 204}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {154, 255, 255}, {120, 254, 255}, {154, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 218, 204}, {154, 255, 255}, {0, 218, 204}, {0, 0, 0}, {0, 218, 204}, {89, 255, 255}, {118, 255, 255}},

    [6] = {{0, 255, 219}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {126, 246, 210}, {126, 246, 210}, {239, 229, 255}, {34, 171, 255}, {60, 254, 255}, {87, 255, 255}, {34, 171, 255}, {34, 171, 255}, {34, 171, 255}, {108, 255, 255}, {34, 171, 255}, {87, 255, 255}, {0, 0, 0}, {0, 0, 0}, {23, 252, 255}, {0, 0, 0}, {0, 0, 0}, {118, 255, 255}, {0, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {34, 171, 255}, {34, 171, 255}, {34, 171, 255}, {34, 171, 255}, {34, 171, 255}, {60, 254, 255}, {34, 171, 255}, {34, 171, 255}, {34, 171, 255}, {34, 171, 255}, {34, 171, 255}, {87, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 255}, {118, 255, 255}},

};

void set_layer_color(int layer)
{
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++)
    {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (!hsv.h && !hsv.s && !hsv.v)
        {
            rgb_matrix_set_color(i, 0, 0, 0);
        }
        else
        {
            RGB rgb = hsv_to_rgb(hsv);
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        }
    }
}

bool rgb_matrix_indicators_user(void)
{
    if (rawhid_state.rgb_control)
    {
        return false;
    }
    if (keyboard_config.disable_layer_led)
    {
        return false;
    }
    switch (biton32(layer_state))
    {
    case 0:
        set_layer_color(0);
        break;
    case 1:
        set_layer_color(1);
        break;
    case 2:
        set_layer_color(2);
        break;
    case 3:
        set_layer_color(3);
        break;
    case 4:
        set_layer_color(4);
        break;
    case 5:
        set_layer_color(5);
        break;
    case 6:
        set_layer_color(6);
        break;
    default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE)
            rgb_matrix_set_color_all(0, 0, 0);
        break;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    // Adding Keycodes for QMK Select Word

    if (!process_select_word(keycode, record)) { return false; }

    switch (keycode)
    {

    case TD(DANCE_0):
        action = &tap_dance_actions[TD_INDEX(keycode)];
        if (!record->event.pressed && action->state.count && !action->state.finished)
        {
            tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
            tap_code16(tap_hold->tap);
        }
        break;
    case RGB_SLD:
        if (record->event.pressed)
        {
            rgblight_mode(1);
        }
        return false;
    }
    return true;
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data)
{
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed)
    {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        )
        {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        }
        else
        {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data)
{
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held)
    {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold)                                 \
    {                                                                        \
        .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, \
        .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}),        \
    }

tap_dance_action_t tap_dance_actions[] = {
    [DANCE_0] = ACTION_TAP_DANCE_TAP_HOLD(LALT(KC_BSPC), KC_LEFT_GUI),
};




// QMK Config

#ifdef CHORDAL_HOLD
// Handedness for Chordal Hold.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_voyager(
        '*', '*', '*', '*', '*', '*',
        '*', 'L', 'L', 'L', 'L', 'L',
        '*', 'L', 'L', 'L', 'L', 'L',
        '*', 'L', 'L', 'L', 'L', 'L',
        '*', '*',

        '*', '*', '*', '*', '*', '*',
        'R', 'R', 'R', 'R', 'R', '*',
        'R', 'R', 'R', 'R', 'R', '*',
        'R', 'R', 'R', 'R', 'R', '*',
        '*', '*');
#endif // CHORDAL_HOLD