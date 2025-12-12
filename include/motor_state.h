#pragma once
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

typedef struct {
    volatile uint8_t phase;           // 0–5
    volatile uint16_t duty;           // 0–4095
    volatile uint8_t direction;       // 0=fwd, 1=rev
    volatile uint16_t speed_target;   // 0–100 %
    volatile uint16_t comm_delay_ms;  // tiempo entre fases
} motor_state_t;

extern motor_state_t MotorState;
extern SemaphoreHandle_t motorStateMutex;