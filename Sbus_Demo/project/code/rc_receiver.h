/**
 * @file rc_receiver.h
 * @author zenchrer (zenchrer@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef RC_RECEIVER_H
#define RC_RECEIVER_H

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_fifo.h"

#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"

#define RC_UART_INDEX       (UART_3)       // Sbus串口对应使用的串口号
#define RC_UART_BUAD_RATE   (100000)       // Sbus串口对应使用的串口波特率
#define RC_UART_RX_PIN      (UART3_RX_B11) // Sbus串口对应模块的 RX 要接到单片机的 TX

#define RC_RX_LEN           25 // 25

#define StartByte           0x0f
#define EndByte             0x00

extern uint8_t First_Byte_flag_RC; //首字节标志
extern uint8_t RC_RX_Finish;
extern uint8_t RC_RXIndex;             //当前接收字节数
extern uint8_t RC_RXBuffer[RC_RX_LEN]; //接收缓冲

uint8_t rc_update(uint8_t *buf);
typedef struct
{
    uint16_t CH1;         // 1通道
    uint16_t CH2;         // 2通道
    uint16_t CH3;         // 3通道
    uint16_t CH4;         // 4通道
    uint16_t CH5;         // 5通道
    uint16_t CH6;         // 6通道
    uint16_t CH7;         // 7通道
    uint16_t CH8;         // 8通道
    uint16_t CH9;         // 9通道
    uint16_t CH10;        // 10通道
    uint16_t CH11;        // 11通道
    uint16_t CH12;        // 12通道
    uint16_t CH13;        // 13通道
    uint16_t CH14;        // 14通道
    uint16_t CH15;        // 15通道
    uint16_t CH16;        // 16通道
    uint8_t ConnectState; //有新数据的标志
} RC_CH_Struct;
extern RC_CH_Struct RC_CH;
void rc_init(void);

void rc_uart_callback(void);

#endif // RC_RECEIVER_H