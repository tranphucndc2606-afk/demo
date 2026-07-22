#ifndef DEV_SONAR_H
#define DEV_SONAR_H

#include "stm32f4xx.h"
#include <stdint.h>

void Dev_Sonar_Init(void);
uint32_t Dev_Sonar_MeasureDistance(void);

#endif
