#include "app_safety.h"
#include "bsp_pinout.h"

void Kalman1D_Init(Kalman1D_t *kf, float q, float r, float p, float initial_value) {
    kf->q = q; kf->r = r; kf->p = p; kf->x = initial_value;
}

float Kalman1D_Update(Kalman1D_t *kf, float measurement) {
    kf->p = kf->p + kf->q;
    kf->k = kf->p / (kf->p + kf->r);
    kf->x = kf->x + kf->k * (measurement - kf->x);
    kf->p = (1.0f - kf->k) * kf->p;
    return kf->x;
}

void App_Safety_Buzzer_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    BUZZER_PORT->MODER |= (1 << (BUZZER_PIN * 2));
}

void App_Safety_Buzzer_On(void)  { BUZZER_PORT->BSRR = (1 << BUZZER_PIN); }
void App_Safety_Buzzer_Off(void) { BUZZER_PORT->BSRR = (1 << (BUZZER_PIN + 16)); }
