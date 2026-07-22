#include "dev_sonar.h"
#include "bsp_pinout.h"

extern void Delay_us(uint32_t us);

void Dev_Sonar_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    SONAR_TRIG_PORT->MODER |= (1 << (SONAR_TRIG_PIN * 2)); // Output
    SONAR_ECHO_PORT->PUPDR |= (2 << (SONAR_ECHO_PIN * 2)); // Pull-down Input
}

uint32_t Dev_Sonar_MeasureDistance(void) {
    SONAR_TRIG_PORT->BSRR = (1 << SONAR_TRIG_PIN);
    Delay_us(10);
    SONAR_TRIG_PORT->BSRR = (1 << (SONAR_TRIG_PIN + 16));

    uint32_t timeout = 1000000;
    while (!(SONAR_ECHO_PORT->IDR & (1 << SONAR_ECHO_PIN))) { if (--timeout == 0) return 999; }

    uint32_t start = TIM2->CNT;
    while (SONAR_ECHO_PORT->IDR & (1 << SONAR_ECHO_PIN)) { if ((TIM2->CNT - start) > 25000) break; }
    return (TIM2->CNT - start) / 58;
}
