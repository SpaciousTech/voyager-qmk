#include QMK_KEYBOARD_H
#include "features/select_word.h"
#include "layout.h"
#include "version.h"
#include "i18n.h"

#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

// Function prototype for process_tap_dance_with_mods
void process_tap_dance_with_mods(tap_dance_state_t *state, uint16_t keycode);

enum layers
{
    BASE,
    NAV,
    APPS,
    SYM,
    FUN,
    WIN,
    MEHF,
};

enum custom_keycodes
{
    RGB_SLD = ML_SAFE_RANGE,
    // Adding Keycodes for QMK Select Word
    SELWORD, // Select forward word
    SELBWD,  // Select backward word
    SELLINE, // Select line
    NEXTSEN, // Go to next sentence
    // Adding custom brace keycodes
    BRACES,   // General bracket key with modifier detection
    SBRACKET, // Square brackets []
    CBRACE,   // Curly braces {}
    ABRACKET, // Angle brackets <>
    PAREN,    // Parentheses ()
};

// Adding Keycodes for QMK Select Word
uint16_t SELECT_WORD_KEYCODE = SELWORD;

// Selection mode variables
static bool selection_mode_active = false;
static bool selection_active = false;
static uint16_t selection_mode_timer = 0;
#define SELECTION_MODE_TIMEOUT 5000 // 5 seconds timeout

// Short aliases for Home row mods and other tap-hold keys
#define HRM_A LGUI_T(KC_A)
#define HRM_S LSFT_T(KC_S)
#define HRM_D LOPT_T(KC_D)
#define HRM_F LCTL_T(KC_F)
#define HRM_J RCTL_T(KC_J)
#define HRM_K ROPT_T(KC_K)
#define HRM_L RSFT_T(KC_L)
#define HRM_SCLN RGUI_T(KC_SCLN)
#define LCG_EQUAL MT(MOD_LCTL | MOD_LGUI, KC_EQUAL)
#define RCALT_BSLS MT(MOD_RCTL | MOD_RALT, KC_BSLS)

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
    [BASE] = LAYOUT_LR(
        LCG_EQUAL, KC_1, KC_2, KC_3, KC_4, KC_5,
        LCA_T(KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T,
        LT(2, KC_ESCAPE), HRM_A, HRM_S, HRM_D, HRM_F, KC_G,
        TT(1), MEH_T(KC_Z), KC_X, KC_C, KC_V, KC_B,
        LT(3, KC_BSPC), TD(DANCE_0),

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,
        KC_Y, KC_U, KC_I, KC_O, KC_P, RCALT_BSLS,
        KC_H, HRM_J, HRM_K, HRM_L, HRM_SCLN, LT(6, KC_QUOTE),
        KC_N, KC_M, KC_COMMA, KC_DOT, ALL_T(KC_SLASH), RCTL_T(KC_ENTER),
        RSFT_T(KC_SPACE), LT(1, KC_TAB)),

    [NAV] = LAYOUT_LR(
        _______, KC_1, KC_2, KC_3, KC_4, KC_5,
        _______, TO(3), CW_TOGG, NEXTSEN, XXXXXXX, XXXXXXX,
        _______, KC_LGUI, KC_LSFT, KC_LALT, KC_LCTL, LGUI(KC_A),
        _______, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), SGUI_T(KC_Z),
        _______, _______,

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,
        SELLINE, SELBWD, KC_UP, SELWORD, XXXXXXX, _______,
        LALT(KC_LEFT), KC_LEFT, KC_DOWN, KC_RIGHT, LALT(KC_RIGHT), _______,
        XXXXXXX, XXXXXXX, _______, _______, _______, _______,
        _______, _______),

    [APPS] = LAYOUT_LR(
        QK_LLCK, KC_1, KC_2, KC_3, KC_4, KC_5,
        _______, _______, HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T),
        _______, _______, HYPR(KC_S), HYPR(KC_D), LGUI(KC_SPACE), HYPR(KC_G),
        TO(0), _______, _______, HYPR(KC_C), HYPR(KC_V), _______,
        _______, _______,

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,
        HYPR(KC_Y), HYPR(KC_U), HYPR(KC_I), HYPR(KC_O), HYPR(KC_P), _______,
        HYPR(KC_H), HYPR(KC_J), HYPR(KC_K), HYPR(KC_L), _______, _______,
        HYPR(KC_N), HYPR(KC_M), _______, _______, _______, _______,
        _______, _______),

    [SYM] = LAYOUT_LR(
        QK_LLCK, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,
        _______, TO(1), CW_TOGG, BRACES, PAREN, CBRACE,
        _______, KC_PIPE, KC_TILD, KC_GRAVE, KC_CIRC, KC_ASTR,
        TO(0), XXXXXXX, XXXXXXX, KC_DQUO, XXXXXXX, XXXXXXX,
        _______, _______,

        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINUS,
        KC_EXLM, KC_UNDS, KC_MINUS, KC_EQUAL, KC_PLUS, _______,
        KC_HASH, KC_DLR, LALT(LSFT(KC_2)), LALT(KC_3), KC_COLN, _______,
        KC_PERC, KC_AMPR, KC_LABK, KC_RABK, KC_QUES, _______,
        _______, _______),

    [FUN] = LAYOUT_LR(
        XXXXXXX, XXXXXXX, XXXXXXX, QK_DYNAMIC_TAPPING_TERM_DOWN, QK_DYNAMIC_TAPPING_TERM_UP, QK_DYNAMIC_TAPPING_TERM_PRINT,
        RGB_VAI, RGB_TOG, RGB_SLD, RGB_MODE_FORWARD, RGB_SPD, RGB_SPI,
        RGB_VAD, TOGGLE_LAYER_COLOR, RGB_SAD, RGB_SAI, RGB_HUD, RGB_HUI,
        TO(0), XXXXXXX, XXXXXXX, XXXXXXX, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP,
        _______, _______,

        KC_AUDIO_VOL_UP, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, XXXXXXX, TO(0),
        KC_AUDIO_VOL_DOWN, XXXXXXX, KC_UP, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_AUDIO_MUTE, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, LGUI(KC_COMMA), XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______),

    [WIN] = LAYOUT_LR(
        XXXXXXX, XXXXXXX, LALT(LCTL(KC_LBRC)), XXXXXXX, LALT(LCTL(KC_RBRC)), XXXXXXX,
        XXXXXXX, XXXXXXX, LALT(LCTL(KC_KP_7)), LALT(LCTL(KC_KP_8)), LALT(LCTL(KC_KP_9)), XXXXXXX,
        _______, XXXXXXX, LALT(LCTL(KC_4)), LALT(LCTL(KC_KP_5)), LALT(LCTL(KC_6)), XXXXXXX,
        TO(0), XXXXXXX, LALT(LCTL(KC_KP_1)), LALT(LCTL(KC_KP_2)), LALT(LCTL(KC_KP_3)), XXXXXXX,
        LALT(LCTL(KC_DOWN)), LALT(LCTL(US_UNDS)),

        XXXXXXX, LALT(LCTL(KC_LBRC)), XXXXXXX, LALT(LCTL(KC_RBRC)), XXXXXXX, TO(0),
        XXXXXXX, LALT(LCTL(KC_KP_7)), LALT(LCTL(KC_KP_8)), LALT(LCTL(KC_KP_9)), XXXXXXX, XXXXXXX,
        XXXXXXX, LALT(LCTL(KC_4)), LALT(LCTL(KC_KP_5)), LALT(LCTL(KC_6)), XXXXXXX, XXXXXXX,
        XXXXXXX, LALT(LCTL(KC_KP_1)), LALT(LCTL(KC_KP_2)), LALT(LCTL(KC_KP_3)), XXXXXXX, LALT(LCTL(KC_ENTER)),
        LALT(LCTL(US_PLUS)), _______),

    [MEHF] = LAYOUT_LR(
        QK_LLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, MEH(KC_Q), MEH(KC_W), LGUI(LCTL(KC_SPACE)), MEH(KC_R), SGUI_T(KC_T),
        _______, MEH(KC_A), MEH(KC_S), MEH(KC_D), LGUI(KC_SPACE), MEH(KC_G),
        _______, XXXXXXX, XXXXXXX, LALT(LCTL(KC_C)), XXXXXXX, XXXXXXX,
        _______, _______,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), MEH(KC_BSLS),
        MEH(KC_H), MEH(KC_J), MEH(KC_K), MEH(KC_L), MEH(KC_SCLN), _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______),
};

const uint16_t PROGMEM combo0[] = {KC_MINUS, KC_0, COMBO_END};
const uint16_t PROGMEM combo1[] = {KC_BSPC, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM combo2[] = {LCG_EQUAL, KC_2, COMBO_END};
const uint16_t PROGMEM combo3[] = {LCG_EQUAL, KC_3, COMBO_END};
const uint16_t PROGMEM combo4[] = {LCG_EQUAL, KC_4, COMBO_END};
const uint16_t PROGMEM combo5[] = {LCG_EQUAL, KC_5, COMBO_END};

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
    case LCG_EQUAL:
        return g_tapping_term - 50;
    case LCA_T(KC_TAB):
        return g_tapping_term - 50;
    case LT(2, KC_ESCAPE):
        return g_tapping_term - 50;
    case LT(3, KC_BSPC):
        return g_tapping_term - 25;
    case TD(DANCE_0):
        return g_tapping_term - 50;
    case RCALT_BSLS:
        return g_tapping_term - 50;
    case LT(6, KC_QUOTE):
        return g_tapping_term - 50;
    case ALL_T(KC_SLASH):
        return g_tapping_term - 25;
    case RCTL_T(KC_ENTER):
        return g_tapping_term - 50;
    case RSFT_T(KC_SPACE):
        return g_tapping_term - 50;
    case LT(1, KC_TAB):
        return g_tapping_term - 50;
    default:
        return g_tapping_term;
    }
}

// Define the Shift+Backspace -> Delete key override
// Disabled in favor of direct handling in process_record_user
// const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, LT(3, KC_BSPC), KC_DEL);
// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    // &delete_key_override,  // Disabled - now handled in process_record_user
    NULL // Null terminate the array
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void)
{
    rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [0] = {{156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {87, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {87, 255, 255}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {34, 255, 255}, {87, 255, 255}, {0, 255, 219}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {118, 255, 255}, {0, 255, 219}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {87, 255, 255}, {34, 255, 255}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {87, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {34, 255, 255}, {0, 255, 219}, {87, 255, 255}, {0, 255, 219}, {118, 255, 255}},

    [1] = {{161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {87, 255, 255}, {87, 255, 255}, {242, 255, 255}, {34, 255, 255}, {0, 0, 0}, {0, 0, 0}, {87, 255, 255}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {0, 255, 219}, {203, 255, 255}, {87, 255, 255}, {203, 255, 255}, {203, 255, 255}, {203, 255, 255}, {203, 255, 255}, {203, 255, 255}, {118, 255, 255}, {0, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {161, 255, 255}, {34, 255, 255}, {34, 255, 255}, {89, 255, 255}, {34, 255, 255}, {0, 0, 0}, {87, 255, 255}, {146, 255, 255}, {89, 255, 255}, {89, 255, 255}, {89, 255, 255}, {146, 255, 255}, {87, 255, 255}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {87, 255, 255}, {0, 255, 255}, {118, 255, 255}},

    [2] = {{0, 255, 219}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {87, 255, 255}, {0, 0, 0}, {121, 211, 222}, {121, 211, 222}, {121, 211, 222}, {41, 245, 224}, {87, 255, 255}, {0, 0, 0}, {121, 211, 222}, {188, 186, 204}, {108, 255, 255}, {156, 217, 143}, {87, 255, 255}, {236, 255, 255}, {0, 0, 0}, {23, 171, 255}, {9, 255, 199}, {0, 0, 0}, {114, 255, 182}, {0, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {156, 255, 255}, {121, 211, 222}, {121, 211, 222}, {121, 211, 222}, {184, 255, 255}, {121, 211, 222}, {87, 255, 255}, {121, 211, 222}, {121, 211, 222}, {121, 211, 222}, {121, 211, 222}, {0, 0, 0}, {87, 255, 255}, {45, 255, 255}, {162, 227, 246}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {87, 255, 255}, {0, 255, 255}, {114, 255, 182}},

    [3] = {{0, 255, 219}, {40, 255, 255}, {40, 255, 255}, {40, 255, 255}, {40, 255, 255}, {40, 255, 255}, {87, 255, 255}, {87, 255, 255}, {0, 246, 255}, {132, 255, 252}, {132, 255, 252}, {132, 255, 252}, {87, 255, 255}, {197, 214, 255}, {197, 214, 255}, {197, 214, 255}, {197, 214, 255}, {197, 214, 255}, {87, 255, 255}, {0, 0, 0}, {0, 0, 0}, {197, 214, 255}, {0, 0, 0}, {0, 0, 0}, {118, 255, 255}, {0, 255, 255}, {40, 255, 255}, {39, 255, 255}, {39, 255, 255}, {39, 255, 255}, {39, 255, 255}, {39, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {87, 255, 255}, {175, 255, 255}, {175, 255, 255}, {147, 255, 255}, {175, 255, 255}, {175, 255, 255}, {87, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {175, 255, 255}, {87, 255, 255}, {0, 255, 255}, {118, 255, 255}},

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
    // Process selection word functionality
    if (!process_select_word(keycode, record))
    {
        return false;
    }

    // Handle Shift+Backspace to output Delete
    if (keycode == LT(3, KC_BSPC) && record->event.pressed)
    {
        const uint8_t mods = get_mods();

        // Check for Shift+Opt+Backspace to send Opt+Delete
        if ((mods & MOD_MASK_SHIFT) && (mods & MOD_MASK_ALT))
        {
            // Send Opt+Delete
            uint8_t alt_mods = mods & MOD_MASK_ALT; // Preserve just the Option mods
            clear_mods();
            register_mods(alt_mods);
            tap_code(KC_DEL);
            clear_mods();
            register_mods(mods);
            return false;
        }
        // Regular Shift+Backspace to send Delete
        else if (mods & MOD_MASK_SHIFT)
        {
            // If shift is held, send Delete instead
            clear_mods();
            tap_code(KC_DEL);
            register_mods(mods);
            return false;
        }
    }

    // Handle Shift+ Opt+Backspace to output Opt+Delete

    switch (keycode)
    {
    // Word selection keycodes
    case SELWORD:
        if (record->event.pressed)
        {
            select_word_register('W'); // Forward selection
            // Start selection mode
            selection_mode_active = true;
            selection_mode_timer = timer_read();
            selection_active = true; // Mark selection as active
        }
        else
        {
            select_word_unregister();
        }
        return false;

    case SELBWD:
        if (record->event.pressed)
        {
            select_word_register('B'); // Backward selection
            selection_active = true;   // Mark selection as active
        }
        else
        {
            select_word_unregister();
        }
        return false;

    case SELLINE:
        if (record->event.pressed)
        {
            select_word_register('L'); // Line selection
            selection_active = true;   // Mark selection as active
        }
        else
        {
            select_word_unregister();
        }
        return false;

    case BRACES: // Types [], {}, or <> and puts cursor between braces.
    {
        const uint8_t mods = get_mods();
        const uint8_t oneshot_mods = get_oneshot_mods();

        // Check if selection is active and handle accordingly
        if (record->event.pressed)
        {
            clear_oneshot_mods(); // Temporarily disable mods.
            unregister_mods(MOD_MASK_CSAG);
            if ((mods | oneshot_mods) & MOD_MASK_SHIFT)
            {
                SEND_STRING("{}");
            }
            else if ((mods | oneshot_mods) & MOD_MASK_CTRL)
            {
                SEND_STRING("<>");
            }
            else if ((mods | oneshot_mods) & MOD_MASK_ALT)
            {
                SEND_STRING("()");
            }
            else
            {
                SEND_STRING("[]");
            }
            tap_code(KC_LEFT);   // Move cursor between braces.
            register_mods(mods); // Restore mods.
        }
    }
        return false;

    case SBRACKET: // Square brackets []
        if (record->event.pressed)
        {
            const uint8_t mods = get_mods();
            clear_oneshot_mods();
            unregister_mods(MOD_MASK_CSAG);
            SEND_STRING("[]");
            tap_code(KC_LEFT);
            register_mods(mods);
        }
        return false;

    case CBRACE: // Curly braces {}
        if (record->event.pressed)
        {
            const uint8_t mods = get_mods();
            clear_oneshot_mods();
            unregister_mods(MOD_MASK_CSAG);
            SEND_STRING("{}");
            tap_code(KC_LEFT);
            register_mods(mods);
        }
        return false;

    case ABRACKET: // Angle brackets <>
        if (record->event.pressed)
        {
            const uint8_t mods = get_mods();
            clear_oneshot_mods();
            unregister_mods(MOD_MASK_CSAG);
            SEND_STRING("<>");
            tap_code(KC_LEFT);
            register_mods(mods);
        }
        return false;

    case PAREN: // Parentheses ()
        if (record->event.pressed)
        {
            const uint8_t mods = get_mods();
            clear_oneshot_mods();
            unregister_mods(MOD_MASK_CSAG);
            SEND_STRING("()");
            tap_code(KC_LEFT);
            register_mods(mods);
        }
        return false;

    case NEXTSEN: // Next sentence macro.
        if (record->event.pressed)
        {
            SEND_STRING(". ");
            add_oneshot_mods(MOD_BIT(KC_LSFT)); // Set one-shot mod for shift.
        }
        return false;

    case TD(DANCE_0):
        action = &tap_dance_actions[TD_INDEX(keycode)];
        if (!record->event.pressed && action->state.count && !action->state.finished)
        {
            tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;

            // Use our custom function instead of directly tapping
            process_tap_dance_with_mods(&action->state, tap_hold->tap);
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

void process_tap_dance_with_mods(tap_dance_state_t *state, uint16_t keycode)
{
    const uint8_t mods = get_mods();

    // If shift is pressed with Alt+Backspace, send Option+Delete
    if ((mods & MOD_MASK_SHIFT) && keycode == LALT(KC_BSPC))
    {
        clear_mods();             // Clear all mods
        register_code(KC_LALT);   // Press Option
        tap_code(KC_DEL);         // Tap Delete
        unregister_code(KC_LALT); // Release Option
        register_mods(mods);      // Restore mods
        return;
    }
    // Otherwise fall back to normal behavior
    tap_code16(keycode);
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
    LAYOUT_LR(
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

// Add a housekeeping task to check for selection mode timeouts
void housekeeping_task_user(void)
{
    // Call the select_word task for its own timeout handling
    select_word_task();

    // Handle our selection mode timeout
    if (selection_mode_active && timer_elapsed(selection_mode_timer) > SELECTION_MODE_TIMEOUT)
    {
        selection_mode_active = false;
        selection_active = false; // Also reset the selection state
    }
}
