// Copyright 2021-2025 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file cover_selection.c
 * @brief Cover selection with brackets implementation
 */

#include "cover_selection.h"

// Internal selection state
static bool selection_active = false;

// Check if selection is active
bool is_selection_active(void)
{
    return selection_active;
}

// Set selection active state
void set_selection_active(bool active)
{
    selection_active = active;
}

// Mark selection as active
void cover_selection_keypress(void)
{
    selection_active = true;
}

#ifdef SELECT_WORD_OS_MAC
bool is_mac_os(void)
{
    return true;
}
#else
bool is_mac_os(void)
{
    return false;
}
#endif

void cover_selection_with(const char *opening, const char *closing)
{
    // Save modifiers
    const uint8_t mods = get_mods();
    clear_oneshot_mods();
    unregister_mods(MOD_MASK_CSAG);

    if (is_mac_os())
    {
        // On Mac: Move to start of selection
        SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_LEFT))));
        // Type opening bracket
        send_string(opening);
        // Move to end of selection
        SEND_STRING(SS_LGUI(SS_LSFT(SS_TAP(X_RIGHT))));
        // Type closing bracket
        send_string(closing);
    }
    else
    {
        // On Windows/Linux: Move to start of selection
        SEND_STRING(SS_TAP(X_HOME));
        // Type opening bracket
        send_string(opening);
        // Move to end of selection
        SEND_STRING(SS_LSFT(SS_TAP(X_END)));
        // Type closing bracket
        send_string(closing);
    }

    // Restore modifiers
    register_mods(mods);
}

bool process_cover_key(uint16_t keycode, keyrecord_t *record, const char *opening, const char *closing)
{
    if (record->event.pressed && is_selection_active())
    {
        // We have an active selection, surround it
        cover_selection_with(opening, closing);
        selection_active = false; // Reset selection state
        return false;             // Skip regular key processing
    }
    return true; // Continue with regular key processing
}