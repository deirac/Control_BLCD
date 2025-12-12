#pragma once
#include <Arduino.h> 

extern TaskHandle_t serialTaskHandle;   // Serial task handler

void serialTaskInit(uint8_t core);
void serialTask(void* pvParameters);
void processSerialCommand(const String& input);



