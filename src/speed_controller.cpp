#include "speed_controller.h"
#include "motor_state.h"

TaskHandle_t speedControllerTaskHandle = NULL;

/**
 * @brief Inicialización de la tarea.
 */
void speedControllerTaskInit(uint8_t core){
    xTaskCreatePinnedToCore(
        speedControllerTask,
        "SpeedControllerTask",
        2048,
        nullptr,
        2,
        &speedControllerTaskHandle,
        core
    );
}

/**
 * @brief Controlador de velocidad muy simple basado en
 *        frecuencia de conmutación (ms entre pasos).
 *
 *        target_speed (0–100%) → comm_delay_ms (40 → 2 ms)
 */
void speedControllerTask(void* pvParameters){
    (void)pvParameters;

    while(1){
        int spd = MotorState.speed_target;

        // Limitar a rango válido
        if (spd < 0) spd = 0;
        if (spd > 100) spd = 100;

        // Traducir velocidad a delay
        // 0%  = 40 ms  (muy lento)
        // 100% = 2 ms  (rápido)
        uint16_t delay_ms = map(spd, 0, 100, 40, 2);

        MotorState.comm_delay_ms = delay_ms;

        // Actualizar el control a 20 Hz
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
