#pragma once 
#include <Arduino.h>

  // ===== TAREAS =====
#include "tasks/serial_task.h"
#include "tasks/hall_task.h"
#include "tasks/commutation_task.h"
#include "tasks/speed_task.h"
#include "tasks/pwm_task.h"



extern TaskHandle_t menuTaskHandle;

void menuInit(uint8_t core);
void menuTask(void* pvParameters);
void stopMenuTask();