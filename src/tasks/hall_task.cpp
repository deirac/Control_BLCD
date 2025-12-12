#include "tasks/hall_task.h"
#include "motor_state.h"

TaskHandle_t hallTaskHandle = NULL;
uint8_t HALL_BUFER[6] = {0,0,0,0,0,0};
uint8_t HALL[3] = {0,0,0};

// ====================================================
// ============== FUNCIONES AUXILIARES ================
// ====================================================
/**
 * @brief Función auxiliar para leer la posición Hall.
 * @param void
 * @return void
 */
static inline void readHallState(){
    HALL[0] = digitalRead(PIN_HALL_U); // medir HU
    HALL[1] = digitalRead(PIN_HALL_V); // medir HU
    HALL[2] = digitalRead(PIN_HALL_W); // medir HU
}

/**
 * @brief Buscar estado Hall en la tabla HALL_ORDER.
 * @param void
 * @return void
 */

static int findHallIndex(){
    for (int i = 0; i < 6; i++){
        if (HALL[0] == HALL_ORDER[i][0] &&
            HALL[1] == HALL_ORDER[i][1] &&
            HALL[2] == HALL_ORDER[i][2]) 
        {
            return i;
        }
    }
    return -1;  // error / ruido / transición inválida
}

// ===================================================
// ============= FUNCIONES DE LA TAREA ===============
// ===================================================

/**
 * @brief Función de sensado 
 * @param pvParameters
 */
void hallTask(void* pvParameters){
    (void)pvParameters;
    uint8_t phase = -1; 

    while(1){
        readHallState();
        phase = findHallIndex();

        if (phase != -1){
            MotorState.phase = phase;    
        }
        else {
            Serial.println("[HALL]: Err, noise or invalid secuence sensors.");
        }
        vTaskDelay(1);  // 1 ms
    }
}


/**
 * @brief Tarea de sensado
 * @param core
 */
void hallTaskInit(uint8_t core){
    pinMode(PIN_HALL_U, INPUT);
    pinMode(PIN_HALL_V, INPUT);
    pinMode(PIN_HALL_W, INPUT);

    xTaskCreatePinnedToCore(
        hallTask,
        "HallTask",
        4096,
        nullptr,
        2,
        &hallTaskHandle,
        core
    );
}