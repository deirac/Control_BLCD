#pragma once
#include <Arduino.h> 
#include "types.h"

extern TaskHandle_t serialTaskHandle;   // Serial task handler

void serialTaskInit(uint8_t core);
void serialTask(void* pvParameters);



