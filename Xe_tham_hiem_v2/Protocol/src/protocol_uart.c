#include "protocol_uart.h"
#include <stdio.h>

void Protocol_UART_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // UART1 PA9 (TX), PA10 (RX) Alternate Function 7
    GPIOA->MODER |= (2 << (9 * 2)) | (2 << (10 * 2));
    GPIOA->AFR[1] |= (7 << (1 * 4)) | (7 << (2 * 4));

    USART1->BRR = 0x0682; // 9600 Baudrate với APB2 = 16MHz
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void Protocol_Send_Telemetry(int16_t raw_t, uint32_t dist_cm, int warn) {
    char tx_buffer[40];
    int16_t temp_c = (raw_t == -9999) ? -99 : (raw_t / 16);
    uint32_t d_send = (dist_cm == 999) ? 0 : dist_cm;
    int len = sprintf(tx_buffer, "T%d;D%lu;W%d\n", temp_c, d_send, warn);

    for (int i = 0; i < len; i++) {
        while (!(USART1->SR & USART_SR_TXE));
        USART1->DR = tx_buffer[i];
    }
}
