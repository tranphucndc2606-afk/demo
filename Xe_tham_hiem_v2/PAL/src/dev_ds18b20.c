#include "dev_ds18b20.h"
#include "bsp_pinout.h"

extern void Delay_us(uint32_t us);

void Dev_DS18B20_Init(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    DS18B20_PORT->MODER |= (1 << (DS18B20_PIN * 2));
    DS18B20_PORT->OTYPER |= (1 << DS18B20_PIN);
    DS18B20_PORT->PUPDR |= (1 << (DS18B20_PIN * 2));
}

static uint8_t DS18B20_Reset(void) {
    DS18B20_PORT->BSRR = (1 << (DS18B20_PIN + 16)); Delay_us(480);
    DS18B20_PORT->BSRR = (1 << DS18B20_PIN); Delay_us(80);
    uint8_t presence = (DS18B20_PORT->IDR & (1 << DS18B20_PIN)) ? 0 : 1;
    Delay_us(400);
    return presence;
}

static void DS18B20_WriteBit(uint8_t bit) {
    if (bit) { DS18B20_PORT->BSRR = (1 << (DS18B20_PIN + 16)); Delay_us(10); DS18B20_PORT->BSRR = (1 << DS18B20_PIN); Delay_us(55); }
    else { DS18B20_PORT->BSRR = (1 << (DS18B20_PIN + 16)); Delay_us(65); DS18B20_PORT->BSRR = (1 << DS18B20_PIN); Delay_us(5); }
}

static void DS18B20_WriteByte(uint8_t data) {
    for (int i = 0; i < 8; i++) DS18B20_WriteBit(data & (1 << i));
}

static uint8_t DS18B20_ReadBit(void) {
    uint8_t bit = 0; DS18B20_PORT->BSRR = (1 << (DS18B20_PIN + 16)); Delay_us(2);
    DS18B20_PORT->BSRR = (1 << DS18B20_PIN); Delay_us(10);
    if (DS18B20_PORT->IDR & (1 << DS18B20_PIN)) bit = 1;
    Delay_us(50);
    return bit;
}

static uint8_t DS18B20_ReadByte(void) {
    uint8_t data = 0;
    for (int i = 0; i < 8; i++) { if (DS18B20_ReadBit()) data |= (1 << i); }
    return data;
}

void Dev_DS18B20_StartConversion(void) {
    if (DS18B20_Reset()) { DS18B20_WriteByte(0xCC); DS18B20_WriteByte(0x44); }
}

int16_t Dev_DS18B20_ReadRawTemp(void) {
    if (!DS18B20_Reset()) return -9999;
    DS18B20_WriteByte(0xCC); DS18B20_WriteByte(0xBE);
    uint8_t lsb = DS18B20_ReadByte();
    uint8_t msb = DS18B20_ReadByte();
    return (int16_t)((msb << 8) | lsb);
}
