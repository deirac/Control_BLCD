#pragma once
#include <Arduino.h>

// ------------------------------------------
// ---------- STATE MOTOR -------------------
// ------------------------------------------

/**
 * @brief BLDC motor state data structure 
 */
typedef struct {
    uint8_t phase;
    uint8_t hall_state;         // bits ABC
    uint8_t comm_index;         // 0..5
    int16_t target_speed;       // de Serial
    int16_t current_speed;      // 0...?
    int16_t pwm_duty;
    bool direction;             // 0=CCW, 1=CW
} MotorState_t;

// ------------------------------------------
// ----------- EXTERN VARIABLE --------------
// ------------------------------------------

extern MotorState_t MotorState;         // current BLDC motor status
extern QueueHandle_t serialQueue;       // Serial message queue






