/**
 * @file app_control.c
 * @brief Bo nao dieu khien trung tam cua xe (Tang App)
 * @author Tran Van Phuong
 */

#include "app_control.h"
#include "dev_motor.h"
#include "dev_sonar.h"
#include "dev_ds18b20.h"
#include "protocol_uart.h"
#include "app_safety.h"
#include "app_display.h" // Dung module display thay vi goi OLED tho

static Kalman1D_t kf_temp;
static uint32_t distance_cm = 999;
static int16_t raw_temp = -9999;
static int16_t temp_c = 0;

static uint32_t auto_stop_timer = 0;
static uint32_t fast_task_counter = 0;
static uint32_t slow_task_counter = 0;
static uint8_t wifi_status_online = 0;
static uint8_t wifi_timeout = 0;

static int warn_code = 0;
static char cmd = 'S';

void App_Control_Init(void) {
    Dev_Motor_Init();
    Dev_Sonar_Init();
    App_Display_Init(); // Khoi tao giao dien hien thi
    Dev_DS18B20_Init();
    Protocol_UART_Init();
    App_Safety_Buzzer_Init();

    Kalman1D_Init(&kf_temp, 0.01f, 2.0f, 1.0f, 25.0f);
    Dev_DS18B20_StartConversion();
}

void App_Control_Execute(void) {
    // Đọc UART1 bằng thanh ghi
    if (USART1->SR & USART_SR_ORE) (void)USART1->DR;
    if (USART1->SR & USART_SR_RXNE) {
        char rx_cmd = USART1->DR;
        if (rx_cmd == 'O') {
            wifi_status_online = 1;
            wifi_timeout = 0;
        }
        else if (rx_cmd == 'o') {
            wifi_status_online = 0;
        }
        else {
            cmd = rx_cmd;
            wifi_status_online = 1;
            wifi_timeout = 0;
            if (cmd != 'S') auto_stop_timer = 20;
        }
    }

    // =========================================================
    // LUỒNG SIÊU TỐC (Mỗi 40ms): QUÉT SIÊU ÂM BẢO VỆ XE KHẨN CẤP
    // =========================================================
    fast_task_counter++;
    if (fast_task_counter >= 2) {
        distance_cm = Dev_Sonar_MeasureDistance();

        if (distance_cm > 0 && distance_cm <= 10) {
            warn_code = 1;
            App_Safety_Buzzer_On();
            if (cmd == 'F') { Dev_Car_Stop(); cmd = 'S'; }
        } else {
            if (temp_c <= 45 && cmd != 'H') {
                warn_code = 0;
                App_Safety_Buzzer_Off();
            }
        }
        fast_task_counter = 0;
    }

    // =========================================================
    // LUỒNG CHẬM (Mỗi 300ms): NHIỆT ĐỘ, OLED VÀ WEB
    // =========================================================
    slow_task_counter++;
    if (slow_task_counter >= 15) {
        raw_temp = Dev_DS18B20_ReadRawTemp();
        Dev_DS18B20_StartConversion();

        if (raw_temp != -9999) {
            float current_temp_f = (float)raw_temp / 16.0f;
            temp_c = (int16_t)Kalman1D_Update(&kf_temp, current_temp_f);
        } else {
            temp_c = 0;
        }

        if (temp_c > 45) { warn_code = 2; App_Safety_Buzzer_On(); }
        else if (cmd == 'H') App_Safety_Buzzer_On();

        Protocol_Send_Telemetry(raw_temp, distance_cm, warn_code);
        if (++wifi_timeout > 5) wifi_status_online = 0;

        // --- CỰC KỲ GỌN GÀNG: Đẩy dữ liệu sang tầng Display xử lý ---
        App_Display_Update(wifi_status_online, distance_cm, temp_c, warn_code);

        slow_task_counter = 0;
    }

    // --- HỆ THỐNG XUẤT LỆNH ĐỘNG CƠ (PHANH TUYẾN TÍNH V1) ---
    if (cmd == 'F') {
        if (distance_cm > 0 && distance_cm <= 10) {
            Dev_Car_Stop();
        } else if (distance_cm > 10 && distance_cm <= 50) {
            float ti_le = (float)(distance_cm - 10) / 40.0f;
            int left_pwm = 200 + (int)(ti_le * (speed_fwd_left - 200));
            int right_pwm = 200 + (int)(ti_le * (speed_fwd_right - 200));
            Dev_Motor_Left_SetSpeed(left_pwm);
            Dev_Motor_Right_SetSpeed(right_pwm);
        } else {
            Dev_Car_Forward_Normal();
        }
    }
    else if (cmd == 'B') { Dev_Car_Backward(); }
    else if (cmd == 'L') { Dev_Car_TurnLeft(); }
    else if (cmd == 'R') { Dev_Car_TurnRight(); }
    else if (cmd == 'S') { Dev_Car_Stop(); }

    // WATCHDOG AN TOÀN KHI MẤT KẾT NỐI
    if (auto_stop_timer > 0) {
        auto_stop_timer--;
        if (auto_stop_timer == 0) {
            Dev_Car_Stop();
            if (cmd != 'H') cmd = 'S';
        }
    }
}
