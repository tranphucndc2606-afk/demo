#ifndef APP_SAFETY_H
#define APP_SAFETY_H

#include "stm32f4xx.h"
#include <stdint.h>

typedef struct {
    float q; float r; float x; float p; float k;
} Kalman1D_t;

void Kalman1D_Init(Kalman1D_t *kf, float q, float r, float p, float initial_value);
float Kalman1D_Update(Kalman1D_t *kf, float measurement);

void App_Safety_Buzzer_Init(void);
void App_Safety_Buzzer_On(void);
void App_Safety_Buzzer_Off(void);

#endif
