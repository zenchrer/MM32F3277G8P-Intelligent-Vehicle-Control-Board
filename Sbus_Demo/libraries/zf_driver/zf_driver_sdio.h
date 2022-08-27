/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file             zf_driver_sdio
* @company          �ɶ���ɿƼ����޹�˾
* @author           ��ɿƼ�(QQ3184284598)
* @version          �鿴doc��version�ļ� �汾˵��
* @Software         IAR 8.32.4 or MDK 5.28
* @Target core      MM32F327X_G8P
* @Taobao           https://seekfree.taobao.com/
* @date             2022-04-11
********************************************************************************************************************/

#ifndef _zf_driver_sdio_h_
#define _zf_driver_sdio_h_

#include "hal_device_registers.h"
#include "hal_sdio.h"

#include "zf_common_typedef.h"
#include "zf_common_clock.h"

#define SDIO_TIMEOUT_COUNT          (100)

typedef enum                                                                    // ö�� SDIO ����״̬ ��ö�ٶ��岻�����û��޸�
{
    SDIO_ERROR_STATE_NO_ERROR,
    SDIO_ERROR_STATE_TIME_OUT,
}sdio_error_state_enum;

typedef enum                                                                    // ö�� SDIO ��������λ��   ��ö�ٶ��岻�����û��޸�
{
    SDIO_DATA_BUS_1BIT,                                                         // 1bit ��������λ��
    SDIO_DATA_BUS_4BIT,                                                         // 4bit ��������λ��
}sdio_data_bus_width_enum;

typedef enum                                                                    // SD ����Ӧ��Ϣ���� �˽ṹ�嶨�岻�����û��޸�
{
    SDIO_RESP_TYPE_R1,                                                          // 32 bit + 8 bit CRC
    SDIO_RESP_TYPE_R2,                                                          // 128 bit + 8 bit CRC, for CID and CSD
    SDIO_RESP_TYPE_R3,                                                          // 32 bit + 8 bit CRC, for OCR
    SDIO_RESP_TYPE_R6,                                                          // 32 bit + 8 bit CRC, for RCA
    SDIO_RESP_TYPE_R7,                                                          // 32 bit + 8 bit CRC, for card interface condition
}sdio_resp_type_enum;


#define sdio_switch_fifo_dir(x)             ((x) ? (SDIO->BUFCTL |= 0x00000800) : (SDIO->BUFCTL &= 0xFFFFF7FF))
#define sdio_switch_fifo_read_wait(x)       ((x) ? (SDIO->MMCCTRL |= 0x00000400) : (SDIO->MMCCTRL &= 0xFFFFFBFF))
#define sdio_clear_fifo()                   (SDIO->BUFCTL |= 0x00008000)
#define sdio_set_block_count(x)             (SDIO->MMCBLOCKCNT = (x))

#define sdio_set_fifo_data(x)               (SDIO->DATABUF[0] = (x))
#define sdio_get_fifo_data()                (SDIO->DATABUF[0])

uint32                  sdio_get_state              (void);
void                    sdio_clear_state            (uint32 flags);
sdio_error_state_enum   sdio_execute_cmd            (uint8 cmd_index, uint32 param, uint32 flags);
void                    sdio_execute_data           (uint32 data);
sdio_error_state_enum   sdio_request_resp           (sdio_resp_type_enum type, uint32 *resp);

void                    sdio_set_data_bus_width     (sdio_data_bus_width_enum width);
void                    sdio_disable                (void);
void                    sdio_enable                 (void);
void                    sdio_init                   (void);

#endif
