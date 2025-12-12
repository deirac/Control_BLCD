#include "tasks/serial_task.h"


TaskHandle_t serialTaskHandle = NULL;


/**
 * @brief 
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
                MotorState.target_speed = input.substring(3).toInt();
            }
            else if (input.startsWith("duty")){
                MotorState.pwm_duty = input.substring(4).toInt();
            }
            else if (input.startsWith("dir")){
                MotorState.direction = input.substring(3).toInt();
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}