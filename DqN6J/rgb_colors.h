// rgb_config.h
#pragma once
#include QMK_KEYBOARD_H  // Include base QMK stuff, likely includes quantum.h, etc.


// Define some common colors using HSV format {Hue, Saturation, Value}
// Standard Colors
#define C_RED {0, 255, 255}        // Red
#define C_BROWN {0, 218, 204}      // Red-Brownish
#define C_ORANGE {21, 255, 255}    // Orange
#define C_YELLOW {36, 255, 255}    // Yellow
#define C_GREEN {78, 255, 255}     // Green
#define C_LTGREEN {103, 255, 255}  // Light Green
#define C_TEAL {115, 255, 204}     // Teal
#define C_CYAN {117, 255, 255}     // Cyan
#define C_LTBLUE {138, 255, 255}   // Light Blue
#define C_BLUE {153, 255, 255}     // Blue
#define C_DKBLUE {170, 255, 255}   // Dark Blue
#define C_PURPLE {196, 255, 255}   // Purple
#define C_MAGENTA {209, 255, 255}  // Magenta
#define C_PINK {236, 255, 255}     // Pink
#define C_WHITE {0, 0, 255}        // White
#define C_OFF {0, 0, 0}            // LED Off (Black)

#define C_MODS {0, 255, 255}      // Red used for Home Row Mods
#define C_LAYER {87, 255, 255}    // Green used for layer keys
#define C_ARROW {89, 255, 255}    // Green for arrow keys
#define C_THUMBS {115, 255, 204}  // Teal used for small thumbs keys
#define C_FUNC {13, 255, 255}     // Dark Orange used for function Layer

#define C_MACRO {115, 255, 204}    // Teal for Macros keys (Select, Hyper, MEH)
#define C_CMDPLUS {170, 255, 255}  // Dark Blue for CMD + keys
#define C_SHIFTED {40, 255, 255}   // Yellow for Shifted keys (!@#$%^&*)

