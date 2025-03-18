// Copyright 2023-2024
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
 * @brief Cover selection with brackets feature
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

    // Track if we have an active selection
    extern bool selection_active;

    /**
     * @brief Detect if the host OS is Mac
     *
     * @return true if Mac OS, false otherwise
     */
    bool is_mac_os(void);

    /**
     * @brief Cover selected text with specified opening and closing brackets
     *
     * @param opening The opening bracket string
     * @param closing The closing bracket string
     */
    void cover_selection_with(const char *opening, const char *closing);

    /**
     * @brief This function should be called from your process_record_user for each selection keycode
     * to set the selection_active flag to true.
     */
    void cover_selection_keypress(void);

    /**
     * @brief Process key events for bracket keys to add cover selection capability
     *
     * @param keycode The keycode being processed
     * @param record Key press/release event information
     * @param opening The opening bracket string
     * @param closing The closing bracket string
     * @return true if the keycode should be processed further, false otherwise
     */
    bool process_cover_key(uint16_t keycode, keyrecord_t *record, const char *opening, const char *closing);

#ifdef __cplusplus
}
#endif