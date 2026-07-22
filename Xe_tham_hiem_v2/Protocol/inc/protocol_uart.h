#ifndef PROTOCOL_UART_H
#define PROTOCOL_UART_H

#include "stm32f4xx.h"
#include <stdint.h>

void Protocol_UART_Init(void);
void Protocol_Send_Telemetry(int16_t raw_t, uint32_t dist_cm, int warn);

#endif
