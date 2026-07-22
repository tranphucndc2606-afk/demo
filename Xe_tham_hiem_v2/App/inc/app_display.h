/**
 * @file app_display.h
 * @brief Header quan ly giao dien hien thi OLED (Tang App)
 * @author Tran Van Phuong
 */

#ifndef APP_DISPLAY_H
#define APP_DISPLAY_H

#include <stdint.h>

/**
 * @brief Khoi tao man hinh OLED va xoa man hinh ban dau
 */
void App_Display_Init(void);

/**
 * @brief Cap nhat toan bo thong tin len man hinh OLED
 * @param wifi_online Trang thai ket noi Wi-Fi (1: Online, 0: Offline)
 * @param dist_cm Khoang cach tu cảm bien sieu am (cm)
 * @param temp_c Nhiet do tu DS18B20 (do C)
 * @param warn_code Ma canh bao (0: Safe, 1: Stop vat can, 2: Alarm chay)
 */
void App_Display_Update(uint8_t wifi_online, uint32_t dist_cm, int16_t temp_c, uint8_t warn_code);

#endif /* APP_DISPLAY_H */
