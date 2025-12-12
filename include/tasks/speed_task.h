#pragma once
#include <Arduino.h>


void speedControllerTaskInit(uint8_t core);
void speedControllerTask(void* pvParameters);
