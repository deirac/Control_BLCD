#include <Arduino.h>
#include "config.h"
#include "motor_state.h"

// ===== TAREAS =====
#include "tasks/serial_task.h"
#include "tasks/hall_task.h"
#include "tasks/commutation_task.h"
#include "tasks/speed_task.h"
#include "tasks/pwm_task.h"

void setup() {
  serialTaskInit(0);            // Funciones del puerto serial en core 0.
  hallTaskInit(0);              // Lectura del sensor Hall en core 0.
  speedControllerTaskInit(0);   // Control de velocidad (Setpoint).
  commutationTaskInit(1);       // Conmuta usando las tablas.
  pwmInit(1);                   // Genera el PWM.
}

void loop() {
  // no hace nada. 
}

