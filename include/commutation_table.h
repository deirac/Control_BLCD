#pragma once 
#include <Arduino.h>


/**
 * @brief HIGH TABLE
 * + → HS = 1, LS = 0
 * - → HS = 0, LS = 1
 * OFF → HS = 0, LS = 0
 */
static const uint8_t HIGH_TABLE[6][3] = {
    {1, 0, 0},  // 1: U+,  Voff, W-
    {0, 1, 0},  // 2: Uoff, V+,  W-
    {0, 1, 0},  // 3: U-,  V+,  Woff
    {0, 0, 1},  // 4: U-,  Voff, W+
    {0, 0, 1},  // 5: Uoff, V-,  W+
    {1, 0, 0}   // 6: U+,  V-,  Woff
};

/**
 * @brief LOW TABLE
 * - → LS = 1
 * + y OFF → LS = 0
 */
static const uint8_t LOW_TABLE[6][3] = {
    {0, 0, 1},  // 1: U+,  Voff, W-
    {0, 0, 1},  // 2: Uoff, V+,  W-
    {1, 0, 0},  // 3: U-,  V+,  Woff
    {1, 0, 0},  // 4: U-,  Voff, W+
    {0, 1, 0},  // 5: Uoff, V-,  W+
    {0, 1, 0}   // 6: U+,  V-,  Woff
};

/**
 * @brief Secuencia que debe recibirse de los sensores (120°).
 */
static const uint8_t HALL_ORDER[6][3] = {
    {1, 0, 0},   // 1
    {1, 1, 0},   // 2
    {0, 1, 0},   // 3
    {0, 1, 1},   // 4
    {0, 0, 1},   // 5
    {1, 0, 1}    // 6
};

