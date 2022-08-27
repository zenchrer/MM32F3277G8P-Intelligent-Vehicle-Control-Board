#include "rc_receiver.h"

static uint8 rc_uart_data;

uint8_t First_Byte_flag_RC     = 1; //���ֽڱ�־
uint8_t RC_RX_Finish           = 0;
uint8_t RC_RXIndex             = 0;   //��ǰ�����ֽ���
uint8_t RC_RXBuffer[RC_RX_LEN] = {0}; //���ջ���
RC_CH_Struct RC_CH;

void rc_init(void)
{
    afio_init((gpio_pin_enum)(RC_UART_RX_PIN & 0xFF), GPI, (gpio_af_enum)((RC_UART_RX_PIN & 0xF00) >> 8), GPI_FLOATING_IN); // ��ȡ��ӦIO���� AF���ܱ���

    RCC->APB1ENR |= ((uint32)0x00000001 << 18);   // ʹ�� UART3 ʱ��
    RCC->APB1RSTR |= ((uint32)0x00000001 << 18);  // ��λ UART3
    RCC->APB1RSTR &= ~((uint32)0x00000001 << 18); // ��ɸ�λ UART3

    UART3->GCR |= UART_GCR_UARTEN(1);
    UART3->CCR |= UART_CCR_CHAR(3); // 8bits ����λ
    UART3->CCR |= UART_CCR_SPB0(1); // 2ֹͣλ
    UART3->CCR |= UART_CCR_SPB1(0);
    UART3->CCR |= UART_CCR_PSEL(1); // żУ��
    UART3->CCR |= UART_CCR_PEN(1);  // żУ��

    UART3->BRR = (system_clock / RC_UART_BUAD_RATE) / 16; // ���ò�����
    UART3->FRA = (system_clock / RC_UART_BUAD_RATE) % 16; // ���ò�����

    UART3->CCR |= UART_CCR_CHAR(3); // 8bits ����λ
    UART3->GCR |= UART_GCR_RXEN(1); // ʹ�� TX RX UART

    uart_rx_irq(RC_UART_INDEX, 1);
}

void rc_uart_callback(void)
{
    uart_query_byte(RC_UART_INDEX, &rc_uart_data);
    if ((rc_uart_data == 0x0f) || (First_Byte_flag_RC == 0))
    {
        First_Byte_flag_RC = 0; //���ֽ���ʶ��
        if (RC_RXIndex < (RC_RX_LEN - 2))
        {
            RC_RXBuffer[RC_RXIndex] = rc_uart_data;
            RC_RXIndex++;
        }
        else if (RC_RXIndex < (RC_RX_LEN - 1))
        {
            RC_RXBuffer[RC_RX_LEN - 1] = rc_uart_data;
            First_Byte_flag_RC         = 1; //׼���ٴ�ʶ�����ֽ�
            RC_RXIndex                 = 0; //���һ֡��25�ֽڣ����ݽ��գ�׼����һ�ν���
            if ((RC_RXBuffer[0] == StartByte) && (RC_RXBuffer[24] == EndByte))
            {
                RC_RX_Finish = 1; //���ճɹ�
                rc_update(RC_RXBuffer);
            }
            else
            {
                RC_RX_Finish       = 0; //����ʧ��
                First_Byte_flag_RC = 1; //׼���ٴ�ʶ�����ֽ�
                RC_RXIndex         = 0; //����ʧ�ܣ�׼����һ�ν���
            }
        }
    }
}

uint8_t rc_update(uint8_t *buf)
{
    int i;
    if (buf[23] == 0)
    {
        RC_CH.ConnectState = 1;
        RC_CH.CH1          = ((int16_t)buf[1] >> 0 | ((int16_t)buf[2] << 8)) & 0x07FF;
        RC_CH.CH2          = ((int16_t)buf[2] >> 3 | ((int16_t)buf[3] << 5)) & 0x07FF;
        RC_CH.CH3          = ((int16_t)buf[3] >> 6 | ((int16_t)buf[4] << 2) | (int16_t)buf[5] << 10) & 0x07FF;
        RC_CH.CH4          = ((int16_t)buf[5] >> 1 | ((int16_t)buf[6] << 7)) & 0x07FF;
        RC_CH.CH5          = ((int16_t)buf[6] >> 4 | ((int16_t)buf[7] << 4)) & 0x07FF;
        RC_CH.CH6          = ((int16_t)buf[7] >> 7 | ((int16_t)buf[8] << 1) | (int16_t)buf[9] << 9) & 0x07FF;
        RC_CH.CH7          = ((int16_t)buf[9] >> 2 | ((int16_t)buf[10] << 6)) & 0x07FF;
        RC_CH.CH8          = ((int16_t)buf[10] >> 5 | ((int16_t)buf[11] << 3)) & 0x07FF;
        RC_CH.CH9          = ((int16_t)buf[12] << 0 | ((int16_t)buf[13] << 8)) & 0x07FF;
        RC_CH.CH10         = ((int16_t)buf[13] >> 3 | ((int16_t)buf[14] << 5)) & 0x07FF;
        RC_CH.CH11         = ((int16_t)buf[14] >> 6 | ((int16_t)buf[15] << 2) | (int16_t)buf[16] << 10) & 0x07FF;
        RC_CH.CH12         = ((int16_t)buf[16] >> 1 | ((int16_t)buf[17] << 7)) & 0x07FF;
        RC_CH.CH13         = ((int16_t)buf[17] >> 4 | ((int16_t)buf[18] << 4)) & 0x07FF;
        RC_CH.CH14         = ((int16_t)buf[18] >> 7 | ((int16_t)buf[19] << 1) | (int16_t)buf[20] << 9) & 0x07FF;
        RC_CH.CH15         = ((int16_t)buf[20] >> 2 | ((int16_t)buf[21] << 6)) & 0x07FF;
        RC_CH.CH16         = ((int16_t)buf[21] >> 5 | ((int16_t)buf[22] << 3)) & 0x07FF;
        return 1;
    }
    else
    {
        RC_CH.ConnectState = 0;
        return 0;
    }
}
