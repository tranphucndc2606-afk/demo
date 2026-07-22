#include "stm32f4xx.h"
#include "app_control.h"

void Delay_us(uint32_t us) {
    uint32_t start = TIM2->CNT;
    while ((TIM2->CNT - start) < us);
}

void Delay_ms(uint32_t ms) {
    for (volatile uint32_t i = 0; i < ms * 4000; i++) __NOP();
}

void Timer2_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = 16 - 1; // 1us tick
    TIM2->ARR = 0xFFFFFFFF;
    TIM2->EGR |= TIM_EGR_UG;
    TIM2->CR1 |= TIM_CR1_CEN;
}

int main(void) {
    Timer2_Init();

    // Khởi tạo toàn bộ ứng dụng
    App_Control_Init();

    // Vòng lặp chính thực thi định thời 20ms
    while (1) {
        App_Control_Execute();
        Delay_ms(20);
    }
}
