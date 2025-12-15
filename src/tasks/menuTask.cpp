#include "tasks/menuTask.h"
#include "motor_state.h"

TaskHandle_t menuTaskHandle = NULL;

void menuInit(uint8_t core){
    xTaskCreatePinnedToCore(
        menuTask,
        "MenuTask",
        4096,
        NULL,
        1,
        &menuTaskHandle,
        core
    );
}

void menuTask(void* pvParameters){
    char c = 'o';
    Serial.println("Menu iniciado. Escriba 'o' para OpenLoop o 'p' para PID.");

    while (1)
    {
        if(Serial.available() > 0){
            c = Serial.read();

            switch (c)
            {
            case 'o':
                Serial.println("Modo cambiado a OPEN LOOP");
                openLoopInit(1);
                break;

            case 'p':
                hallTaskInit(0);              // Lectura del sensor Hall en core 0.
                speedControllerTaskInit(0);   // Control de velocidad (Setpoint).
                commutationTaskInit(1);       // Conmuta usando las tablas.
                pwmInit(1); 
                Serial.println("Modo cambiado a PID");
                break;

            default:
                break;
            }

            serialTaskInit(0);   // Funciones del puerto serial en core 0.
            stopMenuTask();      // Termina el menú después de seleccionar
        }

        vTaskDelay(pdMS_TO_TICKS(50)); // Evita bloquear el watchdog
    }
}


void stopMenuTask(){
    if(menuTaskHandle != NULL){
        vTaskDelete(menuTaskHandle);
        menuTaskHandle = NULL; 
    }
}

  
  
  