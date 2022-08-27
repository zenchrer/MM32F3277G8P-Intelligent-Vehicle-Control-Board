#ifndef RC_RECEIVER_H
#define RC_RECEIVER_H

#include "zf_common_clock.h"
#include "zf_common_debug.h"
#include "zf_common_fifo.h"

#include "zf_driver_delay.h"
#include "zf_driver_gpio.h"
#include "zf_driver_uart.h"

#define RC_UART_INDEX       (UART_3)       // ���ߴ��ڶ�Ӧʹ�õĴ��ں�
#define RC_UART_BUAD_RATE   (100000)       // ���ߴ��ڶ�Ӧʹ�õĴ��ڲ�����
#define RC_UART_TX_PIN      (UART3_TX_B10) // ���ߴ��ڶ�Ӧģ��� TX Ҫ�ӵ���Ƭ���� RX
#define RC_UART_RX_PIN      (UART3_RX_B11) // ���ߴ��ڶ�Ӧģ��� RX Ҫ�ӵ���Ƭ���� TX
#define RC_UART_BUFFER_SIZE (64)

#define RC_RX_LEN           25 // 25?

#define StartByte           0x0f
#define EndByte             0x00

extern uint8_t First_Byte_flag_RC; //���ֽڱ�־
extern uint8_t RC_RX_Finish;
extern uint8_t RC_RXIndex;             //��ǰ�����ֽ���
extern uint8_t RC_RXBuffer[RC_RX_LEN]; //���ջ���

uint8_t rc_update(uint8_t *buf);
typedef struct
{
    uint16_t CH1;         // 1ͨ��
    uint16_t CH2;         // 2ͨ��
    uint16_t CH3;         // 3ͨ��
    uint16_t CH4;         // 4ͨ��
    uint16_t CH5;         // 5ͨ��
    uint16_t CH6;         // 6ͨ��
    uint16_t CH7;         // 7ͨ��
    uint16_t CH8;         // 8ͨ��
    uint16_t CH9;         // 9ͨ��
    uint16_t CH10;        // 10ͨ��
    uint16_t CH11;        // 11ͨ��
    uint16_t CH12;        // 12ͨ��
    uint16_t CH13;        // 13ͨ��
    uint16_t CH14;        // 14ͨ��
    uint16_t CH15;        // 15ͨ��
    uint16_t CH16;        // 16ͨ��
    uint8_t ConnectState; //�������ݵı�־
} RC_CH_Struct;
extern RC_CH_Struct RC_CH;
void rc_init(void);

void rc_uart_callback(void);

#endif // RC_RECEIVER_H