CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
ORYX_ENABLE = yes
RGB_MATRIX_CUSTOM_KB = yes
TAP_DANCE_ENABLE = yes
SPACE_CADET_ENABLE = no
CAPS_WORD_ENABLE = yes
COMBO_ENABLE = yes
DYNAMIC_TAPPING_TERM_ENABLE = yes
LAYER_LOCK_ENABLE = yes




# Custom QMK here
SRC += features/select_word.c
KEY_OVERRIDE_ENABLE = yes
REPEAT_KEY_ENABLE = yes 