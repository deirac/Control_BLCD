#pragma once
#include <Arduino.h>


extern TaskHandle_t pwmTaskHandle;
extern TaskHandle_t openLoopTaskHandle;

void pwmInit(uint8_t core);
void openLoopInit(uint8_t core);
void pwmTask(void* pvParameters);
void openLoopTask(void* pvParameters);
