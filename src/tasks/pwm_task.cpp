#include "tasks/pwm_task.h"
#include "config.h"
#include "motor_state.h"
#include "commutation_table.h"

TaskHandle_t pwmTaskHandle = NULL;

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

void pwmTask(void* pvParameters){
    (void)pvParameters;

    // 6 canales PWM
    ledcSetup(0, PWM_FREQ, PWM_RESOLUTION); 
    ledcSetup(1, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(2, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(3, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(4, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(5, PWM_FREQ, PWM_RESOLUTION);

    ledcAttachPin(PIN_HS_U, 0);
    ledcAttachPin(PIN_HS_V, 1);
    ledcAttachPin(PIN_HS_W, 2);

    ledcAttachPin(PIN_LS_U, 3);
    ledcAttachPin(PIN_LS_V, 4);
    ledcAttachPin(PIN_LS_W, 5);

    while(1){
        uint8_t ph = MotorState.phase;
        uint16_t duty = MotorState.duty;

        const uint8_t (*HT)[3];
        const uint8_t (*LT)[3];

        if(MotorState.direction == 0){// ORIENCIÓN NORMAL 
            HT = HIGH_TABLE;
            LT = LOW_TABLE;
        } else {                      // ORIENTACIÓN INVERTIDA
            HT = LOW_TABLE;
            LT = HIGH_TABLE;
        }

        // HIGH SIDE
        ledcWrite(0, HT[ph][0] ? duty : 0);
        ledcWrite(1, HT[ph][1] ? duty : 0);
        ledcWrite(2, HT[ph][2] ? duty : 0);

        // LOW SIDE
        ledcWrite(3, LT[ph][0] ? duty : 0);
        ledcWrite(4, LT[ph][1] ? duty : 0);
        ledcWrite(5, LT[ph][2] ? duty : 0);

        vTaskDelay(1);
    }
}
