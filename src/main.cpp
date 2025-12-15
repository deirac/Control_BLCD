#include <Arduino.h>
#include "config.h"
#include "motor_state.h"
#include "tasks/menuTask.h"



void setup() {
  Serial.begin(115200);
  menuInit(0);
}

void loop() {
  // no hace nada. 
}

