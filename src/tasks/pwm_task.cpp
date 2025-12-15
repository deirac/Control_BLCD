#include "tasks/pwm_task.h"
#include "config.h"
#include "motor_state.h"
#include "commutation_table.h"

TaskHandle_t pwmTaskHandle = NULL;
TaskHandle_t openLoopTaskHandle = NULL;

void pwmInit(uint8_t core){
    xTaskCreatePinnedToCore(
        pwmTask,
        "PWMTask",
        4096,
        nullptr,
        3,
        &pwmTaskHandle,
        core
    );
}

void openLoopInit(uint8_t core){
    xTaskCreatePinnedToCore(
        openLoopTask,
        "OpenLoopTask",
        4096,
        nullptr,
        3,
        &openLoopTaskHandle,
        core
    );
}


void initPINs(){
        // 3 canales PWM solo para HIGH SIDE
    ledcSetup(0, PWM_FREQ, PWM_RESOLUTION); 
    ledcSetup(1, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(2, PWM_FREQ, PWM_RESOLUTION);

    ledcAttachPin(PIN_HS_U, 0);
    ledcAttachPin(PIN_HS_V, 1);
    ledcAttachPin(PIN_HS_W, 2);

    // LOW SIDE como GPIO
    pinMode(PIN_LS_U, OUTPUT);
    pinMode(PIN_LS_V, OUTPUT);
    pinMode(PIN_LS_W, OUTPUT);
}

void pwmTask(void* pvParameters){
    (void)pvParameters;

    initPINs();
    bool dir = 0; 

    while(1){
        xSemaphoreTake(motorStateMutex, portMAX_DELAY);
        uint8_t ph = MotorState.phase;
        uint16_t duty = MotorState.duty;
        uint16_t delay = MotorState.comm_delay_ms;
        dir = MotorState.direction;
        xSemaphoreGive(motorStateMutex);

        const uint8_t (*HT)[3];
        const uint8_t (*LT)[3];
        
        if(dir == 0){ // ORIENTACIÓN NORMAL 
            HT = HIGH_TABLE;
            LT = LOW_TABLE;
        } else {      // ORIENTACIÓN INVERTIDA
            HT = LOW_TABLE;
            LT = HIGH_TABLE;
        }

        // HIGH SIDE con PWM
        ledcWrite(0, HT[ph][0] ? duty : 0);
        ledcWrite(1, HT[ph][1] ? duty : 0);
        ledcWrite(2, HT[ph][2] ? duty : 0);

        // LOW SIDE con nivel lógico fijo
        digitalWrite(PIN_LS_U, LT[ph][0] ? HIGH : LOW);
        digitalWrite(PIN_LS_V, LT[ph][1] ? HIGH : LOW);
        digitalWrite(PIN_LS_W, LT[ph][2] ? HIGH : LOW);

        vTaskDelay(pdMS_TO_TICKS(delay));
    }
}

void openLoopTask(void* pvParameters){
    (void)pvParameters;

    initPINs();
    uint8_t phase = 0;                // fase inicial

    xSemaphoreTake(motorStateMutex, portMAX_DELAY);
    uint16_t duty = MotorState.duty;                 // ciclo de trabajo (ejemplo 50%)
    uint16_t delay = MotorState.comm_delay_ms;       // tiempo de conmutación en ms
    xSemaphoreGive(motorStateMutex);

    bool dir = 0;                                    // 0 = normal, 1 = invertido

    const uint8_t (*HT)[3];
    const uint8_t (*LT)[3];

    while(1){
        // Selección de tablas según dirección
        if(dir == 0){
            HT = HIGH_TABLE;
            LT = LOW_TABLE;
        } else {
            HT = LOW_TABLE;
            LT = HIGH_TABLE;
        }

        // HIGH SIDE con PWM
        ledcWrite(0, HT[phase][0] ? duty : 0);
        ledcWrite(1, HT[phase][1] ? duty : 0);
        ledcWrite(2, HT[phase][2] ? duty : 0);

        // LOW SIDE con nivel lógico
        digitalWrite(PIN_LS_U, LT[phase][0] ? HIGH : LOW);
        digitalWrite(PIN_LS_V, LT[phase][1] ? HIGH : LOW);
        digitalWrite(PIN_LS_W, LT[phase][2] ? HIGH : LOW);

        // Avanzar fase
        phase++;
        if(phase >= 6) phase = 0;   // volver al inicio

        // Esperar antes de la siguiente conmutación
        vTaskDelay(pdMS_TO_TICKS(delay));
    }
}
