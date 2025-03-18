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
 * @file cover_selection.h
 * @brief Cover selection with brackets
 *
 * This feature allows covering selected text with various types of brackets.
 * It works in conjunction with the select_word feature to detect active selections.
 */

#pragma once

#include "quantum.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Feature configuration
#ifndef COVER_SELECTION_ENABLE
#define COVER_SELECTION_ENABLE true
#endif

    // Selection state tracking
    bool is_selection_active(void);
    void set_selection_active(bool active);

    /**
     * @brief Cover selected text with opening and closing characters.
     *
     * @param opening  Opening bracket/character
     * @param closing  Closing bracket/character
     */
    void cover_selection_with(const char *opening, const char *closing);

    /**
     * @brief Process a key event for covering selection with brackets.
     *
     * @param keycode  Keycode being processed
     * @param record   Key record
     * @param opening  Opening bracket/character
     * @param closing  Closing bracket/character
     * @return bool    True if the key should be processed normally, false if handled
     */
    bool process_cover_key(uint16_t keycode, keyrecord_t *record, const char *opening, const char *closing);

    /**
     * @brief Check if system is Mac OS.
     *
     * @return bool  True if system is Mac OS
     */
    bool is_mac_os(void);

#ifdef __cplusplus
}
#endif