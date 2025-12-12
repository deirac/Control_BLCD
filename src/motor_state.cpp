#include "motor_state.h"

motor_state_t MotorState = {
    .phase = 0,
    .duty = 0,
    .direction = 0,
    .speed_target = 25,
    .comm_delay_ms = 10
};

SemaphoreHandle_t motorStateMutex = xSemaphoreCreateMutex();