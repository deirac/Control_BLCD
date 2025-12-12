#include "tasks/serial_task.h"
#include "motor_state.h"

TaskHandle_t serialTaskHandle = NULL;


/**
 * @brief Iniciación puerto serial y comandos: 
 * -> spdxxx <velocidad> [0...100]
 * -> dutyxx <duty> [0..100]
 * -> dirx <dirección> <0->Forward, 1->Reverse>
 * @param core
 */
void serialTaskInit(uint8_t core){
    xTaskCreatePinnedToCore(
        serialTask,
        "SerialTask",
        4096,
        nullptr,
        1,
        &serialTaskHandle,
        core
    );
}

void serialTask(void* pvParameters){
    (void)pvParameters;

    Serial.begin(115200);
    String input;

    while(1){
        if (Serial.available()) {
            input = Serial.readStringUntil('\n');

            if (input.startsWith("spd")){
                MotorState.speed_target= input.substring(3).toInt();
            }
            else if (input.startsWith("duty")){
                MotorState.duty = input.substring(4).toInt();
            }
            else if (input.startsWith("dir")){
                MotorState.direction = input.substring(3).toInt();
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}