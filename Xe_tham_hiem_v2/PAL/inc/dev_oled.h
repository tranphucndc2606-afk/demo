#ifndef DEV_OLED_H
#define DEV_OLED_H

#include "stm32f4xx.h"
#include <stdint.h>

void Dev_OLED_Init(void);
void Dev_OLED_Clear(void);
void Dev_OLED_PrintString(uint8_t page, uint8_t col, const char* str);

#endif
