#pragma once
#include <Arduino.h>


// -------------------------------------------------
// -------------- PWM CONFIG -----------------------
// -------------------------------------------------
#define PWM_FREQ        20e3                            // Frecuencia en kHz
#define PWM_RESOLUTION  12                              // Resolución en bits 
#define PWM_MAX_DUTY    ((1 << PWM_RESOLUTION) - 1)     // Duty maximo de 4095
#define DEADTIME_US     4                               // Dead time en micro segundos 

// ------------------------------------------------
// ---------- Pines sensores HALL -----------------
// ------------------------------------------------
#define PIN_HALL_A 34                                   
#define PIN_HALL_B 35
#define PIN_HALL_C 32

// ------------------------------------------------
// ------ Pines PWM para IR2110 (High side) -------
// ------------------------------------------------
#define HS_A_PIN 18
#define HS_B_PIN 19
#define HS_C_PIN 21

// ------------------------------------------------
// ------ Pines PWM para IR2110 (Low side) --------
// ------------------------------------------------
#define LS_A_PIN 5
#define LS_B_PIN 4
#define LS_C_PIN 2
