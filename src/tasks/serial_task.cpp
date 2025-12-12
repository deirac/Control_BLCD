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


void serialTask(void* pvParameters) {
    (void)pvParameters;

    Serial.begin(115200);
    String buffer = "";

    Serial.print(">>> "); // prompt inicial

    while (1) {
        // Esperar hasta que llegue un comando completo terminado en '\n'
        if (Serial.available()) {
            char c = Serial.read();

            if (c == '\r') continue; // ignorar retorno de carro

            if (c == '\n') {
                // Hacer echo del comando completo
                Serial.println(buffer);

                // Procesar el comando
                processSerialCommand(buffer);

                // Limpiar buffer y mostrar prompt
                buffer = "";
                Serial.print(">>> ");
            } else {
                // Acumular caracteres en el buffer
                buffer += c;
            }
        }

        // Pequeña pausa para no consumir 100% CPU
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}


void processSerialCommand(const String& input){
    if (input.startsWith("spd")){
        xSemaphoreTake(motorStateMutex, portMAX_DELAY);
        MotorState.speed_target= input.substring(3).toInt();
        Serial.print("vel: ");
        Serial.println(MotorState.speed_target);
        xSemaphoreGive(motorStateMutex);
    }
    else if (input.startsWith("duty")){
        xSemaphoreTake(motorStateMutex, portMAX_DELAY);
        MotorState.duty = input.substring(4).toInt();
        Serial.print("duty: ");
        Serial.println(MotorState.duty);
        xSemaphoreGive(motorStateMutex);
    }
    else if (input.startsWith("dir")){
        xSemaphoreTake(motorStateMutex, portMAX_DELAY);
        MotorState.direction = input.substring(3).toInt();
        Serial.print("dir: ");
        if(MotorState.direction==0) Serial.println("forward");
        else Serial.println("reverse");
        xSemaphoreGive(motorStateMutex);
    }
}