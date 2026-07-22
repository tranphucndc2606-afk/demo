#ifndef BSP_PINOUT_H
#define BSP_PINOUT_H

#include "stm32f4xx.h"

// ==============================================================================
// 1. CẤU HÌNH ĐỘNG CƠ & CẦU H (TB6612 / L298N)
// ==============================================================================
// PWM PA6 (TIM3_CH1) - Bánh Phải, PA7 (TIM3_CH2) - Bánh Trái
#define MOTOR_PWM_PORT          GPIOA
#define MOTOR_RIGHT_PWM_PIN     6
#define MOTOR_LEFT_PWM_PIN      7

// Chân hướng Bánh Phải: PB10 (IN1), PB8 (IN2)
#define MOTOR_R_IN1_PORT        GPIOB
#define MOTOR_R_IN1_PIN         10
#define MOTOR_R_IN2_PORT        GPIOB
#define MOTOR_R_IN2_PIN         8

// Chân hướng Bánh Trái: PB14 (IN3), PB15 (IN4)
#define MOTOR_L_IN3_PORT        GPIOB
#define MOTOR_L_IN3_PIN         14
#define MOTOR_L_IN4_PORT        GPIOB
#define MOTOR_L_IN4_PIN         15

// ==============================================================================
// 2. CẤU HÌNH CẢM BIẾN SIÊU ÂM (HC-SR05)
// ==============================================================================
#define SONAR_TRIG_PORT         GPIOA
#define SONAR_TRIG_PIN          0

#define SONAR_ECHO_PORT         GPIOA
#define SONAR_ECHO_PIN          1

// ==============================================================================
// 3. CẤU HÌNH CẢM BIẾN NHIỆT ĐỘ (DS18B20)
// ==============================================================================
#define DS18B20_PORT            GPIOA
#define DS18B20_PIN             4

// ==============================================================================
// 4. CẤU HÌNH CÒI CẢNH BÁO (BUZZER)
// ==============================================================================
#define BUZZER_PORT             GPIOA
#define BUZZER_PIN              5

// ==============================================================================
// 5. CẤU HÌNH MÀN HÌNH OLED (I2C1)
// ==============================================================================
// PB6: SCL, PB7: SDA
#define OLED_I2C_PORT           GPIOB
#define OLED_SCL_PIN            6
#define OLED_SDA_PIN            7

// ==============================================================================
// 6. CẤU HÌNH MẠNG ESP32 (USART1)
// ==============================================================================
// PA9: TX, PA10: RX
#define UART_ESP_PORT           GPIOA
#define UART_TX_PIN             9
#define UART_RX_PIN             10

#endif
