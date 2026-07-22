/**
 * @file dev_motor.c
 * @brief Driver dieu khien dong co va huong di chuyen (Tang PAL)
 * @author Tran Minh Phuc
 */

#include "dev_motor.h"
#include "bsp_pinout.h"

/* Toc do mac dinh cua 2 banh (Gia tri PWM tu 0 den 1000) */
uint16_t speed_fwd_left = 550;
uint16_t speed_fwd_right = 550;
uint16_t speed_bwd_left = 550;
uint16_t speed_bwd_right = 550;

/**
 * @brief Khoi tao ngoai vi: Cap clock GPIO/Timer3, cau hinh chan Output va PWM
 */
void Dev_Motor_Init(void) {
    // Cap clock cho Port A, Port B va Timer3
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    // Cua hinh 4 chan huong o che do Output
    MOTOR_R_IN1_PORT->MODER |= (1 << (MOTOR_R_IN1_PIN * 2));
    MOTOR_R_IN2_PORT->MODER |= (1 << (MOTOR_R_IN2_PIN * 2));
    MOTOR_L_IN3_PORT->MODER |= (1 << (MOTOR_L_IN3_PIN * 2));
    MOTOR_L_IN4_PORT->MODER |= (1 << (MOTOR_L_IN4_PIN * 2));

    // Cau hinh 2 chan PWM (PA6, PA7) sang che do Alternate Function (AF2)
    MOTOR_PWM_PORT->MODER |= (2 << (MOTOR_RIGHT_PWM_PIN * 2)) | (2 << (MOTOR_LEFT_PWM_PIN * 2));
    MOTOR_PWM_PORT->AFR[0] |= (2 << (MOTOR_RIGHT_PWM_PIN * 4)) | (2 << (MOTOR_LEFT_PWM_PIN * 4));

    // Cau hinh Timer 3 cho ra PWM tan so 1kHz (Prescaler=16, ARR=1000)
    TIM3->PSC = 16 - 1;
    TIM3->ARR = 1000 - 1;
    TIM3->CCMR1 |= (6 << 4) | (6 << 12); // Mode PWM 1 cho CH1 va CH2
    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E; // Bat Output
    TIM3->CR1 |= TIM_CR1_CEN; // Cho Timer3 chay
}

/**
 * @brief Dat toc do va chieu quay dong co ben phai
 */
void Dev_Motor_Right_SetSpeed(int16_t speed) {
    if (speed > 0) {
        // Quay tien: IN1 = High, IN2 = Low
        MOTOR_R_IN1_PORT->BSRR = (1 << MOTOR_R_IN1_PIN);
        MOTOR_R_IN2_PORT->BSRR = (1 << (MOTOR_R_IN2_PIN + 16));
        TIM3->CCR1 = speed;
    } else if (speed < 0) {
        // Quay lui: IN1 = Low, IN2 = High
        MOTOR_R_IN1_PORT->BSRR = (1 << (MOTOR_R_IN1_PIN + 16));
        MOTOR_R_IN2_PORT->BSRR = (1 << MOTOR_R_IN2_PIN);
        TIM3->CCR1 = -speed;
    } else {
        // Dung dong co: IN1 = Low, IN2 = Low
        MOTOR_R_IN1_PORT->BSRR = (1 << (MOTOR_R_IN1_PIN + 16));
        MOTOR_R_IN2_PORT->BSRR = (1 << (MOTOR_R_IN2_PIN + 16));
        TIM3->CCR1 = 0;
    }
}

/**
 * @brief Dat toc do va chieu quay dong co ben trai
 */
void Dev_Motor_Left_SetSpeed(int16_t speed) {
    if (speed > 0) {
        // Quay tien: IN3 = High, IN4 = Low
        MOTOR_L_IN3_PORT->BSRR = (1 << MOTOR_L_IN3_PIN);
        MOTOR_L_IN4_PORT->BSRR = (1 << (MOTOR_L_IN4_PIN + 16));
        TIM3->CCR2 = speed;
    } else if (speed < 0) {
        // Quay lui: IN3 = Low, IN4 = High
        MOTOR_L_IN3_PORT->BSRR = (1 << (MOTOR_L_IN3_PIN + 16));
        MOTOR_L_IN4_PORT->BSRR = (1 << MOTOR_L_IN4_PIN);
        TIM3->CCR2 = -speed;
    } else {
        // Dung dong co: IN3 = Low, IN4 = Low
        MOTOR_L_IN3_PORT->BSRR = (1 << (MOTOR_L_IN3_PIN + 16));
        MOTOR_L_IN4_PORT->BSRR = (1 << (MOTOR_L_IN4_PIN + 16));
        TIM3->CCR2 = 0;
    }
}

/**
 * @brief Cho xe di tien
 */
void Dev_Car_Forward_Normal(void) {
    Dev_Motor_Left_SetSpeed(speed_fwd_left);
    Dev_Motor_Right_SetSpeed(speed_fwd_right);
}

/**
 * @brief Cho xe di lui
 */
void Dev_Car_Backward(void) {
    Dev_Motor_Left_SetSpeed(-speed_bwd_left);
    Dev_Motor_Right_SetSpeed(-speed_bwd_right);
}

/**
 * @brief Re trai tai cho (Tank Turn)
 */
void Dev_Car_TurnLeft(void) {
    Dev_Motor_Left_SetSpeed(-500);
    Dev_Motor_Right_SetSpeed(500);
}

/**
 * @brief Re phai tai cho (Tank Turn)
 */
void Dev_Car_TurnRight(void) {
    Dev_Motor_Left_SetSpeed(500);
    Dev_Motor_Right_SetSpeed(-500);
}

/**
 * @brief Dung xe hoan toan
 */
void Dev_Car_Stop(void) {
    Dev_Motor_Left_SetSpeed(0);
    Dev_Motor_Right_SetSpeed(0);
}
