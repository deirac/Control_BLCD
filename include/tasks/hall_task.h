#pragma once
#include <Arduino.h>
#include "commutation_table.h"
#include "config.h"

extern TaskHandle_t hallTaskHandle;     // Sensor HALL task handler 
extern uint8_t HALL_BUFER[6];           // Bufer para comprobar estados
extern uint8_t HALL[3];                 // Receptor de sensores 


void hallTaskInit(uint8_t core);
void hallTask(void* pvParameters);