#pragma once
#include <Arduino.h>

/**
 * @brief Inicializa la tarea de conmutación del motor.
 * Cambia la fase cada cierto tiempo (MotorState.comm_delay_ms).
 */
void commutationTaskInit(uint8_t core);

/**
 * @brief Función RTOS que ejecuta la conmutación de fases.
 */
void commutationTask(void* pvParameters);
