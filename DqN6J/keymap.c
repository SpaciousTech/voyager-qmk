#include QMK_KEYBOARD_H
#include "version.h"
#include "features/achordion.h"
#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

enum custom_keycodes
{
    RGB_SLD = ML_SAFE_RANGE,
};

// QMK Achordion
void housekeeping_task_user(void)
{
    achordion_task();
}

enum tap_dance_codes
{
    DANCE_0,
    DANCE_1,
    DANCE_2,
    DANCE_3,
    DANCE_4,
    DANCE_5,
    DANCE_6,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_voyager(
        TD(DANCE_0), KC_1, KC_2, KC_3, KC_4, KC_5, TO(3), KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, TD(DANCE_2),
        KC_LEFT_GUI, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, MT(MOD_LGUI, KC_BSLS),
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, TD(DANCE_3), MT(MOD_RSFT, KC_QUOTE),
        KC_LEFT_CTRL, ALL_T(KC_Z), KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, TD(DANCE_4), KC_DOT, MT(MOD_RALT, KC_SLASH), MT(MOD_RCTL, KC_ENTER),
        LT(1, KC_BSPC), TD(DANCE_1), MT(MOD_LALT, KC_SPACE), TT(2)),
    [1] = LAYOUT_voyager(
        KC_ESCAPE, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_BSPC,
        KC_TRANSPARENT, LCTL(KC_LEFT_SHIFT), LSFT(KC_LEFT_ALT), KC_GRAVE, KC_LCBR, KC_RCBR, KC_KP_7, KC_KP_8, KC_KP_9, KC_SLASH, KC_MINUS, KC_TRANSPARENT,
        KC_TRANSPARENT, RGUI(RCTL(KC_RIGHT_SHIFT)), LCTL(KC_RIGHT_GUI), KC_CIRC, KC_LPRN, KC_RPRN, KC_KP_4, TD(DANCE_5), KC_KP_6, KC_ASTR, KC_PLUS, KC_RIGHT_SHIFT,
        KC_TRANSPARENT, KC_TRANSPARENT, LCTL(LSFT(KC_LEFT_GUI)), KC_AMPR, KC_LBRC, KC_RBRC, KC_KP_1, KC_KP_2, KC_KP_3, KC_DOT, KC_EQUAL, KC_ENTER,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TD(DANCE_6)),
    [2] = LAYOUT_voyager(
        KC_TRANSPARENT, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRANSPARENT,
        KC_TRANSPARENT, LGUI(KC_Q), LGUI(KC_W), TO(3), RGB_VAD, RGB_VAI, LGUI(KC_X), LGUI(KC_C), KC_UP, LGUI(KC_V), KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, LGUI(KC_A), KC_TRANSPARENT, KC_BSPC, KC_LEFT_GUI, KC_LEFT_ALT, LGUI(KC_Z), KC_LEFT, KC_DOWN, KC_RIGHT, LGUI(LSFT(KC_Z)), KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, LCTL(LSFT(KC_TAB)), LCTL(KC_TAB), KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
    [3] = LAYOUT_voyager(
        KC_TRANSPARENT, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, LGUI(LCTL(KC_SPACE)), KC_TRANSPARENT, KC_TRANSPARENT, QK_DYNAMIC_TAPPING_TERM_PRINT, QK_DYNAMIC_TAPPING_TERM_DOWN, QK_DYNAMIC_TAPPING_TERM_UP, RALT(RGUI(RCTL(RSFT(KC_W)))), KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, RALT(RGUI(RCTL(RSFT(KC_S)))), RALT(RGUI(RCTL(RSFT(KC_D)))), KC_TRANSPARENT, RALT(RGUI(RCTL(RSFT(KC_G)))), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RALT(RGUI(RCTL(RSFT(KC_C)))), RALT(RGUI(RCTL(RSFT(KC_Q)))), KC_TRANSPARENT, RALT(RGUI(RCTL(RSFT(KC_N)))), KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, TO(0)),
    [4] = LAYOUT_voyager(
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT),
};

const uint16_t PROGMEM combo0[] = {KC_H, ALL_T(KC_Z), KC_X, COMBO_END};
const uint16_t PROGMEM combo1[] = {KC_1, KC_3, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, TO(3)),
    COMBO(combo1, TO(4)),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case MT(MOD_LGUI, KC_BSLS):
        return g_tapping_term + 50;
    case TD(DANCE_4):
        return g_tapping_term + 50;
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
    [0] = {{0, 255, 219}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {18, 222, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {18, 222, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {18, 222, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {186, 255, 255}, {0, 255, 219}, {29, 255, 255}, {190, 221, 255}, {190, 221, 255}, {190, 221, 255}, {190, 221, 255}, {0, 255, 219}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {18, 222, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {39, 255, 255}, {18, 222, 255}, {123, 244, 255}, {114, 255, 255}, {39, 255, 255}, {39, 255, 255}, {18, 222, 255}, {18, 222, 255}, {0, 255, 219}, {186, 255, 255}},

    [1] = {{0, 255, 219}, {40, 255, 255}, {40, 255, 255}, {40, 255, 255}, {40, 255, 255}, {40, 255, 255}, {18, 222, 255}, {0, 0, 0}, {0, 0, 0}, {40, 255, 255}, {225, 223, 255}, {225, 223, 255}, {18, 222, 255}, {0, 0, 0}, {0, 0, 0}, {40, 255, 255}, {225, 223, 255}, {225, 223, 255}, {18, 222, 255}, {18, 222, 255}, {0, 0, 0}, {40, 255, 255}, {225, 223, 255}, {225, 223, 255}, {186, 255, 255}, {0, 255, 255}, {29, 255, 255}, {190, 221, 255}, {190, 221, 255}, {190, 221, 255}, {190, 221, 255}, {0, 255, 219}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {40, 255, 255}, {39, 255, 255}, {18, 222, 255}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {39, 255, 255}, {39, 255, 255}, {18, 222, 255}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {39, 255, 255}, {39, 255, 255}, {18, 222, 255}, {0, 255, 255}, {186, 255, 255}},

    [2] = {{0, 255, 219}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {18, 222, 255}, {187, 255, 255}, {187, 255, 255}, {18, 222, 255}, {215, 255, 255}, {215, 255, 255}, {18, 222, 255}, {187, 255, 255}, {0, 0, 0}, {0, 255, 255}, {18, 222, 255}, {18, 222, 255}, {18, 222, 255}, {18, 222, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {186, 255, 255}, {0, 255, 255}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {147, 255, 255}, {0, 255, 219}, {203, 255, 255}, {203, 255, 255}, {0, 185, 255}, {203, 255, 255}, {0, 0, 0}, {18, 222, 255}, {203, 255, 255}, {0, 255, 255}, {0, 185, 255}, {0, 255, 255}, {203, 255, 255}, {18, 222, 255}, {85, 255, 255}, {85, 255, 255}, {187, 255, 255}, {187, 255, 255}, {18, 222, 255}, {18, 222, 255}, {0, 255, 255}, {186, 255, 255}},

    [3] = {{0, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {18, 222, 255}, {0, 0, 0}, {0, 0, 0}, {34, 214, 242}, {0, 0, 0}, {0, 0, 0}, {18, 222, 255}, {0, 0, 0}, {29, 255, 255}, {29, 255, 255}, {0, 0, 0}, {29, 255, 255}, {18, 222, 255}, {18, 222, 255}, {0, 0, 0}, {29, 255, 255}, {29, 255, 255}, {0, 0, 0}, {186, 255, 255}, {0, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {114, 255, 255}, {0, 255, 255}, {241, 163, 246}, {241, 163, 246}, {241, 163, 246}, {184, 255, 255}, {0, 0, 0}, {18, 222, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {18, 222, 255}, {45, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {18, 222, 255}, {0, 255, 255}, {186, 255, 255}},

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
    default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE)
            rgb_matrix_set_color_all(0, 0, 0);
        break;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (!process_achordion(keycode, record))
    {
        return false;
    } // QMK Achordion
    switch (keycode)
    {

    case RGB_SLD:
        if (record->event.pressed)
        {
            rgblight_mode(1);
        }
        return false;
    }
    return true;
}

typedef struct
{
    bool is_press_action;
    uint8_t step;
} tap;

enum
{
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[7];

uint8_t dance_step(tap_dance_state_t *state);

uint8_t dance_step(tap_dance_state_t *state)
{
    if (state->count == 1)
    {
        if (state->interrupted || !state->pressed)
            return SINGLE_TAP;
        else
            return SINGLE_HOLD;
    }
    else if (state->count == 2)
    {
        if (state->interrupted)
            return DOUBLE_SINGLE_TAP;
        else if (state->pressed)
            return DOUBLE_HOLD;
        else
            return DOUBLE_TAP;
    }
    return MORE_TAPS;
}

void on_dance_0(tap_dance_state_t *state, void *user_data);
void dance_0_finished(tap_dance_state_t *state, void *user_data);
void dance_0_reset(tap_dance_state_t *state, void *user_data);

void on_dance_0(tap_dance_state_t *state, void *user_data)
{
    if (state->count == 3)
    {
        tap_code16(KC_EQUAL);
        tap_code16(KC_EQUAL);
        tap_code16(KC_EQUAL);
    }
    if (state->count > 3)
    {
        tap_code16(KC_EQUAL);
    }
}

void dance_0_finished(tap_dance_state_t *state, void *user_data)
{
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step)
    {
    case SINGLE_TAP:
        register_code16(KC_EQUAL);
        break;
    case SINGLE_HOLD:
        register_code16(KC_ESCAPE);
        break;
    case DOUBLE_TAP:
        register_code16(KC_ESCAPE);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code16(KC_EQUAL);
        register_code16(KC_EQUAL);
    }
}

void dance_0_reset(tap_dance_state_t *state, void *user_data)
{
    wait_ms(10);
    switch (dance_state[0].step)
    {
    case SINGLE_TAP:
        unregister_code16(KC_EQUAL);
        break;
    case SINGLE_HOLD:
        unregister_code16(KC_ESCAPE);
        break;
    case DOUBLE_TAP:
        unregister_code16(KC_ESCAPE);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code16(KC_EQUAL);
        break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(tap_dance_state_t *state, void *user_data);
void dance_1_finished(tap_dance_state_t *state, void *user_data);
void dance_1_reset(tap_dance_state_t *state, void *user_data);

void on_dance_1(tap_dance_state_t *state, void *user_data)
{
    if (state->count == 3)
    {
        tap_code16(LALT(KC_BSPC));
        tap_code16(LALT(KC_BSPC));
        tap_code16(LALT(KC_BSPC));
    }
    if (state->count > 3)
    {
        tap_code16(LALT(KC_BSPC));
    }
}

void dance_1_finished(tap_dance_state_t *state, void *user_data)
{
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step)
    {
    case SINGLE_TAP:
        register_code16(LALT(KC_BSPC));
        break;
    case SINGLE_HOLD:
        register_code16(KC_LEFT_SHIFT);
        break;
    case DOUBLE_TAP:
        register_code16(LALT(KC_BSPC));
        register_code16(LALT(KC_BSPC));
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code16(LALT(KC_BSPC));
        register_code16(LALT(KC_BSPC));
    }
}

void dance_1_reset(tap_dance_state_t *state, void *user_data)
{
    wait_ms(10);
    switch (dance_state[1].step)
    {
    case SINGLE_TAP:
        unregister_code16(LALT(KC_BSPC));
        break;
    case SINGLE_HOLD:
        unregister_code16(KC_LEFT_SHIFT);
        break;
    case DOUBLE_TAP:
        unregister_code16(LALT(KC_BSPC));
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code16(LALT(KC_BSPC));
        break;
    }
    dance_state[1].step = 0;
}
void on_dance_2(tap_dance_state_t *state, void *user_data);
void dance_2_finished(tap_dance_state_t *state, void *user_data);
void dance_2_reset(tap_dance_state_t *state, void *user_data);

void on_dance_2(tap_dance_state_t *state, void *user_data)
{
    if (state->count == 3)
    {
        tap_code16(KC_MINUS);
        tap_code16(KC_MINUS);
        tap_code16(KC_MINUS);
    }
    if (state->count > 3)
    {
        tap_code16(KC_MINUS);
    }
}

void dance_2_finished(tap_dance_state_t *state, void *user_data)
{
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step)
    {
    case SINGLE_TAP:
        register_code16(KC_MINUS);
        break;
    case DOUBLE_TAP:
        register_code16(KC_DELETE);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code16(KC_MINUS);
        register_code16(KC_MINUS);
    }
}

void dance_2_reset(tap_dance_state_t *state, void *user_data)
{
    wait_ms(10);
    switch (dance_state[2].step)
    {
    case SINGLE_TAP:
        unregister_code16(KC_MINUS);
        break;
    case DOUBLE_TAP:
        unregister_code16(KC_DELETE);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code16(KC_MINUS);
        break;
    }
    dance_state[2].step = 0;
}
void on_dance_3(tap_dance_state_t *state, void *user_data);
void dance_3_finished(tap_dance_state_t *state, void *user_data);
void dance_3_reset(tap_dance_state_t *state, void *user_data);

void on_dance_3(tap_dance_state_t *state, void *user_data)
{
    if (state->count == 3)
    {
        tap_code16(KC_SCLN);
        tap_code16(KC_SCLN);
        tap_code16(KC_SCLN);
    }
    if (state->count > 3)
    {
        tap_code16(KC_SCLN);
    }
}

void dance_3_finished(tap_dance_state_t *state, void *user_data)
{
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step)
    {
    case SINGLE_TAP:
        register_code16(KC_SCLN);
        break;
    case DOUBLE_TAP:
        register_code16(KC_BSPC);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code16(KC_SCLN);
        register_code16(KC_SCLN);
    }
}

void dance_3_reset(tap_dance_state_t *state, void *user_data)
{
    wait_ms(10);
    switch (dance_state[3].step)
    {
    case SINGLE_TAP:
        unregister_code16(KC_SCLN);
        break;
    case DOUBLE_TAP:
        unregister_code16(KC_BSPC);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code16(KC_SCLN);
        break;
    }
    dance_state[3].step = 0;
}
void on_dance_4(tap_dance_state_t *state, void *user_data);
void dance_4_finished(tap_dance_state_t *state, void *user_data);
void dance_4_reset(tap_dance_state_t *state, void *user_data);

void on_dance_4(tap_dance_state_t *state, void *user_data)
{
    if (state->count == 3)
    {
        tap_code16(KC_COMMA);
        tap_code16(KC_COMMA);
        tap_code16(KC_COMMA);
    }
    if (state->count > 3)
    {
        tap_code16(KC_COMMA);
    }
}

void dance_4_finished(tap_dance_state_t *state, void *user_data)
{
    dance_state[4].step = dance_step(state);
    switch (dance_state[4].step)
    {
    case SINGLE_TAP:
        register_code16(KC_COMMA);
        break;
    case DOUBLE_TAP:
        register_code16(LGUI(KC_COMMA));
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code16(KC_COMMA);
        register_code16(KC_COMMA);
    }
}

void dance_4_reset(tap_dance_state_t *state, void *user_data)
{
    wait_ms(10);
    switch (dance_state[4].step)
    {
    case SINGLE_TAP:
        unregister_code16(KC_COMMA);
        break;
    case DOUBLE_TAP:
        unregister_code16(LGUI(KC_COMMA));
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code16(KC_COMMA);
        break;
    }
    dance_state[4].step = 0;
}
void on_dance_5(tap_dance_state_t *state, void *user_data);
void dance_5_finished(tap_dance_state_t *state, void *user_data);
void dance_5_reset(tap_dance_state_t *state, void *user_data);

void on_dance_5(tap_dance_state_t *state, void *user_data)
{
    if (state->count == 3)
    {
        tap_code16(KC_KP_5);
        tap_code16(KC_KP_5);
        tap_code16(KC_KP_5);
    }
    if (state->count > 3)
    {
        tap_code16(KC_KP_5);
    }
}

void dance_5_finished(tap_dance_state_t *state, void *user_data)
{
    dance_state[5].step = dance_step(state);
    switch (dance_state[5].step)
    {
    case SINGLE_TAP:
        register_code16(KC_KP_5);
        break;
    case SINGLE_HOLD:
        register_code16(KC_KP_0);
        break;
    case DOUBLE_TAP:
        register_code16(KC_KP_5);
        register_code16(KC_KP_5);
        break;
    case DOUBLE_SINGLE_TAP:
        tap_code16(KC_KP_5);
        register_code16(KC_KP_5);
    }
}

void dance_5_reset(tap_dance_state_t *state, void *user_data)
{
    wait_ms(10);
    switch (dance_state[5].step)
    {
    case SINGLE_TAP:
        unregister_code16(KC_KP_5);
        break;
    case SINGLE_HOLD:
        unregister_code16(KC_KP_0);
        break;
    case DOUBLE_TAP:
        unregister_code16(KC_KP_5);
        break;
    case DOUBLE_SINGLE_TAP:
        unregister_code16(KC_KP_5);
        break;
    }
    dance_state[5].step = 0;
}
void dance_6_finished(tap_dance_state_t *state, void *user_data);
void dance_6_reset(tap_dance_state_t *state, void *user_data);

void dance_6_finished(tap_dance_state_t *state, void *user_data)
{
    dance_state[6].step = dance_step(state);
    switch (dance_state[6].step)
    {
    case DOUBLE_TAP:
        layer_move(0);
        break;
    }
}

void dance_6_reset(tap_dance_state_t *state, void *user_data)
{
    wait_ms(10);
    switch (dance_state[6].step)
    {
    }
    dance_state[6].step = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
    [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
    [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
    [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
    [DANCE_4] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_4, dance_4_finished, dance_4_reset),
    [DANCE_5] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_5, dance_5_finished, dance_5_reset),
    [DANCE_6] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_6_finished, dance_6_reset),
};

// Custom QMK here
const key_override_t delete_key_override =
    ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL); // This is a custom key override that will replace the default behavior of the shift+BSPC key with the DEL key.

const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL};