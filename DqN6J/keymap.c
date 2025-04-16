#include QMK_KEYBOARD_H
#include "features/select_word.h"
#include "layout.h"
#include "version.h"
#include "i18n.h"
#include "rgb_colors.h" // Include the new RGB configuration

#define MOON_LED_LEVEL LED_LEVEL
#define ML_SAFE_RANGE SAFE_RANGE

// Function prototype for process_tap_dance_with_mods
void process_tap_dance_with_mods(tap_dance_state_t *state, uint16_t keycode);

// Define the layers used in the keymap
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

// Define custom keycodes
enum custom_keycodes
{
    RGB_SLD = ML_SAFE_RANGE, // Example: Use the defined starting point

    // Keycodes for QMK Select Word
    SELWORD, // Select forward word
    SELBWD,  // Select backward word
    SELLINE, // Select line

    // Custom brace keycodes
    BRACES,   // General bracket key with modifier detection
    SBRACKET, // Square brackets []
    CBRACE,   // Curly braces {}
    ABRACKET, // Angle brackets <>
    PAREN,    // Parentheses ()

    // Vim motion macros
    VIM_EOL, // Vim End of Line (Esc followed by A)
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
// #define HRM_J RCTL_T(KC_J)
#define HRM_K ROPT_T(KC_K)
#define HRM_L RSFT_T(KC_L)
// #define HRM_SCLN RGUI_T(KC_SCLN)
#define LCG_EQUAL MT(MOD_LCTL | MOD_LGUI, KC_EQUAL)
// #define RCALT_BSLS MT(MOD_RCTL | MOD_RALT, KC_BSLS)
#define LT_REP LT(SYM, KC_0) // Layer-Tap Repeat
#define KC_EURO LSA(KC_2)    // Euro symbol
#define KC_GBP LALT(KC_3)    // British Pound symbol
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
        LCG_EQUAL, KC_1, KC_2, KC_3, KC_4, KC_5,              // Top Row
        LCA_T(KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T,          // Second Row
        LT(SYM, KC_ESCAPE), HRM_A, HRM_S, HRM_D, HRM_F, KC_G, // Third Row
        TT(NAV), ALL_T(KC_Z), KC_X, KC_C, KC_V, KC_B,         // Fourth Row
        LT(NAV, KC_BSPC), TD(DANCE_0),                        // Thumbs Row

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,                          // Top Row
        KC_Y, KC_U, KC_I, KC_O, KC_P, LT(MEHF, KC_BSLS),                 // Second Row
        KC_H, KC_J, HRM_K, HRM_L, KC_SCLN, LT(APPS, KC_QUOTE),           // Third Row
        KC_N, KC_M, KC_COMMA, KC_DOT, MEH_T(KC_SLASH), RCTL_T(KC_ENTER), // Fourth Row
        RSFT_T(KC_SPACE), LT_REP),                                       // Thumbs Row

    [NAV] = LAYOUT_LR(
        _______, KC_1, KC_2, KC_3, KC_4, KC_5,                              // Top Row
        _______, TO(SYM), CW_TOGG, SELLINE, SELBWD, SELWORD,                // Second Row
        _______, KC_LGUI, KC_LSFT, KC_LALT, KC_LCTL, LGUI(KC_A),            // Third Row
        _______, LGUI(KC_Z), LGUI(KC_X), LGUI(KC_C), LGUI(KC_V), LSG(KC_Z), // Fourth Row
        _______, _______,                                                   // Thumbs Row

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,                            // Top Row
        LALT(KC_LEFT), KC_WH_D, KC_WH_U, LALT(KC_RIGHT), XXXXXXX, _______, // Second Row
        KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, VIM_EOL, _______,               // Third Row
        XXXXXXX, XXXXXXX, _______, _______, _______, _______,              // Fourth Row
        _______, _______),                                                 // Thumbs Row

    [APPS] = LAYOUT_LR(
        QK_LLCK, KC_1, KC_2, KC_3, KC_4, KC_5,                                // Top Row
        _______, _______, HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T),     // Second Row
        _______, _______, HYPR(KC_S), HYPR(KC_D), LGUI(KC_SPACE), HYPR(KC_G), // Third Row
        TO(BASE), _______, _______, HYPR(KC_C), HYPR(KC_V), _______,          // Fourth Row
        _______, _______,                                                     // Thumbs Row

        KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS,                              // Top Row
        HYPR(KC_Y), HYPR(KC_U), HYPR(KC_I), HYPR(KC_O), HYPR(KC_P), _______, // Second Row
        HYPR(KC_H), HYPR(KC_J), HYPR(KC_K), HYPR(KC_L), _______, _______,    // Third Row
        HYPR(KC_N), HYPR(KC_M), _______, _______, _______, _______,          // Fourth Row
        _______, _______),                                                   // Thumbs Row

    [SYM] = LAYOUT_LR(
        QK_LLCK, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC,     // Top Row
        _______, TO(NAV), CW_TOGG, BRACES, PAREN, CBRACE,      // Second Row
        _______, KC_AMPR, KC_TILD, KC_GRAVE, KC_PERC, KC_ASTR, // Third Row
        TO(BASE), XXXXXXX, KC_AT, KC_DLR, KC_EURO, KC_GBP,     // Fourth Row
        _______, _______,                                      // Thumbs Row

        KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINUS,           // Top Row
        KC_EQUAL, KC_UNDS, KC_LBRC, KC_RBRC, KC_PLUS, LT(MEHF, KC_PIPE), // Second Row
        KC_HASH, KC_CIRC, KC_LCBR, KC_RCBR, KC_COLN, LT(APPS, KC_DQUO),  // Third Row
        KC_EXLM, KC_MINUS, KC_LABK, KC_RABK, KC_QUES, _______,           // Fourth Row
        _______, _______),                                               // Thumbs Row

    [FUN] = LAYOUT_LR(
        KC_ACL0, KC_ACL1, KC_ACL2, DT_DOWN, DT_UP, DT_PRNT,              // Top Row
        RGB_VAI, RGB_TOG, RGB_SLD, RGB_MODE_FORWARD, RGB_SPD, RGB_SPI,   // Second Row
        RGB_VAD, TOGGLE_LAYER_COLOR, RGB_SAD, RGB_SAI, RGB_HUD, RGB_HUI, // Third Row
        TO(BASE), XXXXXXX, XXXXXXX, XXXXXXX, KC_BRID, KC_BRIU,           // Fourth Row
        _______, _______,                                                // Thumbs Row

        XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, TO(BASE),       // Top Row
        XXXXXXX, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX,        // Second Row
        KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, XXXXXXX, XXXXXXX,         // Third Row
        XXXXXXX, XXXXXXX, LGUI(KC_COMMA), XXXXXXX, XXXXXXX, XXXXXXX, // Fourth Row
        _______, _______),                                           // Thumbs Row

    [WIN] = LAYOUT_LR(
        XXXXXXX, XXXXXXX, LCA(KC_LBRC), XXXXXXX, LCA(KC_RBRC), XXXXXXX, // Top Row
        XXXXXXX, XXXXXXX, LCA(KC_7), LCA(KC_8), LCA(KC_9), XXXXXXX,     // Second Row
        _______, XXXXXXX, LCA(KC_4), LCA(KC_5), LCA(KC_6), XXXXXXX,     // Third Row
        TO(BASE), XXXXXXX, LCA(KC_1), LCA(KC_2), LCA(KC_3), XXXXXXX,    // Fourth Row
        LCA(KC_DOWN), LCA(KC_UNDS),                                     // Thumbs Row

        XXXXXXX, LCA(KC_LBRC), XXXXXXX, LCA(KC_RBRC), XXXXXXX, TO(BASE),  // Top Row
        XXXXXXX, LCA(KC_7), LCA(KC_8), LCA(KC_9), XXXXXXX, XXXXXXX,       // Second Row
        XXXXXXX, LCA(KC_4), LCA(KC_5), LCA(KC_6), XXXXXXX, XXXXXXX,       // Third Row
        XXXXXXX, LCA(KC_1), LCA(KC_2), LCA(KC_3), XXXXXXX, LCA(KC_ENTER), // Fourth Row
        LCA(KC_PLUS), _______),                                           // Thumbs Row

    [MEHF] = LAYOUT_LR(
        QK_LLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         // Top Row
        XXXXXXX, MEH(KC_Q), MEH(KC_W), LGUI(LCTL(KC_SPACE)), MEH(KC_R), SGUI_T(KC_T), // Second Row
        _______, MEH(KC_A), MEH(KC_S), MEH(KC_D), LGUI(KC_SPACE), MEH(KC_G),          // Third Row
        _______, XXXXXXX, XXXXXXX, LCA(KC_C), XXXXXXX, XXXXXXX,                       // Fourth Row
        _______, _______,                                                             // Thumbs Row

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              // Top Row
        MEH(KC_Y), MEH(KC_U), MEH(KC_I), MEH(KC_O), MEH(KC_P), _______,    // Second Row
        MEH(KC_H), MEH(KC_J), MEH(KC_K), MEH(KC_L), MEH(KC_SCLN), _______, // Third Row
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,              // Fourth Row
        _______, _______),                                                 // Thumbs Row
};

const uint16_t PROGMEM combo0[] = {KC_MINUS, KC_0, COMBO_END};
const uint16_t PROGMEM combo1[] = {KC_BSPC, KC_RIGHT, COMBO_END};
const uint16_t PROGMEM combo2[] = {LCG_EQUAL, KC_2, COMBO_END};
const uint16_t PROGMEM combo3[] = {LCG_EQUAL, KC_3, COMBO_END};
const uint16_t PROGMEM combo4[] = {LCG_EQUAL, KC_4, COMBO_END};
const uint16_t PROGMEM combo5[] = {LCG_EQUAL, KC_5, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    COMBO(combo0, TO(BASE)),
    COMBO(combo1, TO(BASE)),
    COMBO(combo2, TO(APPS)),
    COMBO(combo3, TO(SYM)),
    COMBO(combo4, TO(FUN)),
    COMBO(combo5, TO(WIN)),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode)
    {
    case LCG_EQUAL:
        return g_tapping_term - 125;
    case LCA_T(KC_TAB):
        return g_tapping_term - 125;
    case LT(SYM, KC_ESCAPE):
        return g_tapping_term - 125;
    case LT(NAV, KC_BSPC):
        return g_tapping_term - 100;
    case TD(DANCE_0):
        return g_tapping_term - 125;
    // case RCALT_BSLS:
    //     return g_tapping_term - 125;
    case LT(MEHF, KC_BSLS):
        return g_tapping_term - 125;
    case LT(APPS, KC_QUOTE):
        return g_tapping_term - 125;
    case ALL_T(KC_Z):
        return g_tapping_term - 100;
    case RCTL_T(KC_ENTER):
        return g_tapping_term - 125;
    case RSFT_T(KC_SPACE):
        return g_tapping_term - 125;
    case LT_REP:
        return g_tapping_term - 100; // Add faster tapping term for SYM_REP key
    case TT(NAV):                    // Tap-Tap Navigation Layer
        return g_tapping_term - 150;
    default:
        return g_tapping_term;
    }
}

// Define the Shift+Backspace -> Delete key override
// Disabled in favor of direct handling in process_record_user
// const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, LT(SYM, KC_BSPC), KC_DEL);
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

// --- Color Definitions Start ---
// Define some common colors using HSV format {Hue, Saturation, Value}
// Standard Colors
#define C_RED {0, 255, 255}       // Red
#define C_BROWN {0, 218, 204}     // Red-Brownish
#define C_ORANGE {21, 255, 255}   // Orange
#define C_YELLOW {36, 255, 255}   // Yellow
#define C_GREEN {78, 255, 255}    // Green
#define C_LTGREEN {103, 255, 255} // Light Green
#define C_TEAL {115, 255, 204}    // Teal
#define C_CYAN {117, 255, 255}    // Cyan
#define C_LTBLUE {138, 255, 255}  // Light Blue
#define C_BLUE {153, 255, 255}    // Blue
#define C_DKBLUE {170, 255, 255}  // Dark Blue
#define C_PURPLE {196, 255, 255}  // Purple
#define C_MAGENTA {209, 255, 255} // Magenta
#define C_PINK {236, 255, 255}    // Pink
#define C_WHITE {0, 0, 255}       // White
#define C_OFF {0, 0, 0}           // LED Off (Black)

#define C_MODS {0, 255, 255}     // Red used for Home Row Mods
#define C_LAYER {87, 255, 255}   // Green used for layer keys
#define C_ARROW {89, 255, 255}   // Green for arrow keys
#define C_THUMBS {115, 255, 204} // Teal used for small thumbs keys
#define C_FUNC {13, 255, 255}    // Dark Orange used for function Layer

#define C_MACRO {115, 255, 204}   // Teal for Macros keys (Select, Hyper, MEH)
#define C_CMDPLUS {170, 255, 255} // Dark Blue for CMD + keys
#define C_SHIFTED {40, 255, 255}  // Yellow for Shifted keys (!@#$%^&*)
// --- Color Definitions End ---

const uint8_t PROGMEM ledmap[][RGB_MATRIX_LED_COUNT][3] = {
    [BASE] = {
        // Left Hand Side
        C_LAYER, C_BLUE, C_BLUE, C_BLUE, C_BLUE, C_BLUE,           // Top row
        C_LAYER, C_ORANGE, C_ORANGE, C_ORANGE, C_ORANGE, C_ORANGE, // Second row
        C_LAYER, C_MODS, C_MODS, C_MODS, C_MODS, C_ORANGE,         // Third row (Home Row Mods)
        C_LAYER, C_TEAL, C_ORANGE, C_ORANGE, C_ORANGE, C_ORANGE,   // Fourth row
        C_THUMBS, C_RED,                                           // Thumb cluster

        // Right Hand Side
        C_BLUE, C_BLUE, C_BLUE, C_BLUE, C_BLUE, C_BLUE,            // Top row
        C_ORANGE, C_ORANGE, C_ORANGE, C_ORANGE, C_ORANGE, C_LAYER, // Second row
        C_ORANGE, C_ORANGE, C_MODS, C_MODS, C_ORANGE, C_LAYER,     // Third row (Home Row Mods)
        C_ORANGE, C_ORANGE, C_ORANGE, C_ORANGE, C_TEAL, C_LAYER,   // Fourth row
        C_RED, C_THUMBS                                            // Thumb cluster
    },
    [NAV] = {
        // Left Hand Side
        C_LAYER, C_BLUE, C_BLUE, C_BLUE, C_BLUE, C_BLUE,                // Top row
        C_LAYER, C_LAYER, C_PINK, C_MACRO, C_MACRO, C_MACRO,            // Second row
        C_LAYER, C_MODS, C_MODS, C_MODS, C_MODS, C_CMDPLUS,             // Third row
        C_LAYER, C_CMDPLUS, C_CMDPLUS, C_CMDPLUS, C_CMDPLUS, C_CMDPLUS, // Fourth row
        C_THUMBS, C_RED,                                                // Thumb cluster

        // Right Hand Side
        C_BLUE, C_BLUE, C_BLUE, C_BLUE, C_BLUE, C_BLUE,           // Top row
        C_SHIFTED, C_LTBLUE, C_LTBLUE, C_SHIFTED, C_OFF, C_LAYER, // Second row
        C_ARROW, C_ARROW, C_ARROW, C_ARROW, C_MACRO, C_LAYER,     // Third row
        C_OFF, C_OFF, C_OFF, C_OFF, C_MODS, C_LAYER,              // Fourth row
        C_RED, C_THUMBS                                           // Thumb cluster
    },
    [APPS] = {
        // Left Hand Side
        C_RED, C_BLUE, C_BLUE, C_BLUE, C_BLUE, C_BLUE,           // Top row
        C_LAYER, C_OFF, C_LTBLUE, C_LTBLUE, C_LTBLUE, C_LTGREEN, // Second row
        C_LAYER, C_OFF, C_YELLOW, C_ORANGE, C_BROWN, C_TEAL,     // Third row
        C_LAYER, C_TEAL, C_OFF, C_TEAL, C_RED, C_OFF,            // Fourth row
        C_THUMBS, C_RED,                                         // Left Thumb cluster

        // Right Hand Side
        C_BLUE, C_BLUE, C_BLUE, C_BLUE, C_BLUE, C_BLUE,             // Top row
        C_ORANGE, C_ORANGE, C_ORANGE, C_MAGENTA, C_ORANGE, C_LAYER, // Second row
        C_ORANGE, C_ORANGE, C_ORANGE, C_ORANGE, C_OFF, C_LAYER,     // Third row
        C_RED, C_RED, C_OFF, C_OFF, C_OFF, C_LAYER,                 // Fourth row
        C_RED, C_THUMBS                                             // Right Thumb cluster
    },
    [SYM] = {
        // Left Hand Side
        C_RED, C_SHIFTED, C_SHIFTED, C_SHIFTED, C_SHIFTED, C_SHIFTED, // Top row
        C_LAYER, C_LAYER, C_PINK, C_BROWN, C_BROWN, C_BROWN,          // Second row
        C_LAYER, C_ORANGE, C_ORANGE, C_ORANGE, C_ORANGE, C_ORANGE,    // Third row
        C_LAYER, C_OFF, C_ORANGE, C_BROWN, C_BROWN, C_BROWN,          // Fourth row
        C_THUMBS, C_RED,                                              // Left Thumb cluster

        C_SHIFTED, C_SHIFTED, C_SHIFTED, C_SHIFTED, C_SHIFTED, C_SHIFTED, // Top row
        C_PURPLE, C_PURPLE, C_PINK, C_PINK, C_PURPLE, C_SHIFTED,          // Second row
        C_PURPLE, C_PURPLE, C_PINK, C_PINK, C_SHIFTED, C_SHIFTED,         // Third row
        C_PURPLE, C_PURPLE, C_SHIFTED, C_SHIFTED, C_SHIFTED, C_LAYER,     // Fourth row
        C_RED, C_THUMBS                                                   // Right Thumb cluster
    },
    [FUN] = {
        // Left Hand Side
        C_BROWN, C_BROWN, C_BROWN, C_YELLOW, C_YELLOW, C_YELLOW, // Top row
        C_FUNC, C_FUNC, C_FUNC, C_FUNC, C_FUNC, C_FUNC,          // Second row
        C_FUNC, C_FUNC, C_FUNC, C_FUNC, C_FUNC, C_RED,           // Third row
        C_LAYER, C_OFF, C_OFF, C_OFF, C_MAGENTA, C_MAGENTA,      // Fourth row
        C_THUMBS, C_RED,                                         // Left Thumb cluster

        C_OFF, C_PURPLE, C_PURPLE, C_PURPLE, C_OFF, C_LAYER, // Top row
        C_OFF, C_TEAL, C_TEAL, C_TEAL, C_OFF, C_OFF,         // Second row
        C_ARROW, C_ARROW, C_ARROW, C_ARROW, C_OFF, C_OFF,    // Third row
        C_OFF, C_OFF, C_ORANGE, C_OFF, C_OFF, C_OFF,         // Fourth row
        C_RED, C_THUMBS                                      // Right Thumb cluster
    },
    [WIN] = {
        // Left Hand Side
        C_OFF, C_OFF, C_PURPLE, C_OFF, C_PURPLE, C_OFF,  // Top row
        C_OFF, C_OFF, C_BROWN, C_BLUE, C_BROWN, C_OFF,   // Second row
        C_OFF, C_OFF, C_BLUE, C_TEAL, C_BLUE, C_OFF,     // Third row
        C_LAYER, C_OFF, C_BROWN, C_BLUE, C_BROWN, C_OFF, // Fourth row
        C_BROWN, C_RED,                                  // Left Thumb cluster

        C_OFF, C_PURPLE, C_OFF, C_PURPLE, C_OFF, C_LAYER, // Top row
        C_OFF, C_BROWN, C_BLUE, C_BROWN, C_OFF, C_OFF,    // Second row
        C_OFF, C_BLUE, C_TEAL, C_BLUE, C_OFF, C_OFF,      // Third row
        C_OFF, C_BROWN, C_BLUE, C_BROWN, C_OFF, C_YELLOW, // Fourth row
        C_ARROW, C_THUMBS                                 // Right Thumb cluster
    },
    [MEHF] = {
        // Left Hand Side
        C_RED, C_OFF, C_OFF, C_OFF, C_OFF, C_OFF,                 // Top row
        C_OFF, C_TEAL, C_TEAL, C_PINK, C_SHIFTED, C_ORANGE,       // Second row
        C_LAYER, C_SHIFTED, C_SHIFTED, C_SHIFTED, C_CYAN, C_TEAL, // Third row
        C_LAYER, C_OFF, C_OFF, C_ORANGE, C_OFF, C_OFF,            // Fourth row
        C_THUMBS, C_RED,                                          // Left Thumb cluster

        C_OFF, C_OFF, C_OFF, C_OFF, C_OFF, C_OFF,                        // Top row
        C_SHIFTED, C_SHIFTED, C_SHIFTED, C_SHIFTED, C_SHIFTED, C_ORANGE, // Second row
        C_TEAL, C_SHIFTED, C_SHIFTED, C_SHIFTED, C_SHIFTED, C_LAYER,     // Third row
        C_OFF, C_OFF, C_OFF, C_OFF, C_OFF, C_OFF,                        // Fourth row
        C_RED, C_THUMBS                                                  // Right Thumb cluster
    },
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
    case BASE:
        set_layer_color(BASE);
        break;
    case NAV:
        set_layer_color(NAV);
        break;
    case APPS:
        set_layer_color(APPS);
        break;
    case SYM:
        set_layer_color(SYM);
        break;
    case FUN:
        set_layer_color(FUN);
        break;
    case WIN:
        set_layer_color(WIN);
        break;
    case MEHF:
        set_layer_color(MEHF);
        break;
    default:
        if (rgb_matrix_get_flags() == LED_FLAG_NONE)
            rgb_matrix_set_color_all(0, 0, 0);
        break;
    }
    return true;
}

// Function to control which keys are remembered for the repeat key
bool remember_last_key_user(uint16_t keycode, keyrecord_t *record, uint8_t *remembered_mods)
{
    // Keys to be ignored by the Repeat Key
    switch (keycode)
    {
    case LT_REP:           // Don't repeat the repeat key itself
    case KC_BSPC:          // Don't repeat backspace
    case TD(DANCE_0):      // Don't repeat the tap dance
    case LT(NAV, KC_BSPC): // Don't repeat the Nav layer backspace
    case VIM_EOL:          // Don't repeat the Vim End of Line key
        return false;      // Ignore these keys
    }
    return true; // Remember all other keys
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    // Process selection word functionality
    if (!process_select_word(keycode, record))
    {
        return false;
    }

    // Handle Shift+Backspace to output Delete
    if (keycode == LT(NAV, KC_BSPC) && record->event.pressed)
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

    switch (keycode)
    {

    // Layer-Tap Repeat keycodes
    case LT_REP: // SYM layer on hold, Repeat Key on tap.
        if (record->tap.count)
        {                                      // on tap.
            repeat_key_invoke(&record->event); // Repeat the last key.
            return false;
        }
        break;

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

    case VIM_EOL: // Vim End of Line - Esc followed by 'A'
        if (record->event.pressed)
        {
            tap_code(KC_ESC);    // Sends Escape
            tap_code16(S(KC_A)); // Sends Shift + a (capital A)
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

    // Ensure we're using these variables to avoid unused variable warnings
    // This is a compiler hint that we intend to use these variables
    (void)selection_mode_active;
    (void)selection_active;
    (void)selection_mode_timer;
}
