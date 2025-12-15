#pragma once
#include <Arduino.h>


// -------------------------------------------------
// -------------- PWM CONFIG -----------------------
// -------------------------------------------------
#define PWM_FREQ        20e3                            // Frecuencia en kHz
#define PWM_RESOLUTION  8                               // Resolución en bits 
#define PWM_MAX_DUTY    ((1 << PWM_RESOLUTION) - 1)     // Duty maximo de 255
#define DEADTIME_US     4                               // Dead time en micro segundos 

// ------------------------------------------------
// ---------- Pines sensores HALL -----------------
// ------------------------------------------------
#define PIN_HALL_U 34                                   
#define PIN_HALL_V 35
#define PIN_HALL_W 32

// ------------------------------------------------
// ------ Pines PWM para IR2110 (High side) -------
// ------------------------------------------------
#define PIN_HS_U 18
#define PIN_HS_V 19
#define PIN_HS_W 21

// ------------------------------------------------
// ------ Pines PWM para IR2110 (Low side) --------
// ------------------------------------------------
#define PIN_LS_U 5
#define PIN_LS_V 4
#define PIN_LS_W 2
