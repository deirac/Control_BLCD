#include "tasks/commutation_task.h"
#include "motor_state.h"

TaskHandle_t commutationTaskHandle = NULL;

void commutationTaskInit(uint8_t core){
    xTaskCreatePinnedToCore(
        commutationTask,
        "CommutationTask",
        2048,
        nullptr,
        2,
        &commutationTaskHandle,
        core
    );
}

void commutationTask(void* pvParameters){
    (void)pvParameters;

    while(1){
        // Avanza la fase
        xSemaphoreTake(motorStateMutex, portMAX_DELAY);
        MotorState.phase++;
        if (MotorState.phase >= 6) MotorState.phase = 0;
        uint16_t delay = MotorState.comm_delay_ms;
        xSemaphoreGive(motorStateMutex);
        // Tiempo entre conmutaciones →
        // ajustado por el controlador de velocidad
        vTaskDelay(pdMS_TO_TICKS(delay));
        
    }
}


