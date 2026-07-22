#ifndef DEV_DS18B20_H
#define DEV_DS18B20_H

#include "stm32f4xx.h"
#include <stdint.h>

void Dev_DS18B20_Init(void);
void Dev_DS18B20_StartConversion(void);
int16_t Dev_DS18B20_ReadRawTemp(void);

#endif
