#pragma once 
#include <Arduino.h>

/**
 * @brief Secuencia para MOSFET de canal N, esta secuencia
 * se debe invertir para MOSFET de canal P.
 */
static const uint8_t HIGH_TABLE[6][3] = {
    {1,0,0},
    {1,0,0},
    {0,1,0},
    {0,1,0},
    {0,0,1},
    {0,0,1}
};

/**
 * @brief Secuencia para MOSFET de canal N, esta secuencia
 * se debe invertir para MOSFET de canal P.
 */
static const uint8_t LOW_TABLE[6][3] = {
    {0,1,0},
    {0,0,1},
    {0,0,1},
    {1,0,0},
    {1,0,0},
    {0,1,0}
};


/**
 * @brief Secuencia que deebe recibirse de los sensores a 120°.
 */
static const uint8_t HALL_ORDER[6] = {
    0b001, 0b101, 0b100, 0b110, 0b010, 0b011
};
