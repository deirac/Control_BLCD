#pragma once
#include <Arduino.h>

/**
 * @brief Inicializa la tarea que convierte target_speed (%)
 *        en tiempo de conmutación (ms) para el motor BLDC.
 */
void speedControllerTaskInit(uint8_t core);

/**
 * @brief Tarea RTOS que ajusta MotorState.comm_delay_ms
 *        según MotorState.target_speed.
 */
void speedControllerTask(void* pvParameters);
