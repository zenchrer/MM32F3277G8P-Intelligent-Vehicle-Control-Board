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

#include "zf_driver_gpio.h"
#include "zf_driver_delay.h"
#include "zf_driver_sdio.h"

//-------------------------------------------------------------------------------------------------------------------
// @brief       sdio ��ȡ��ǰ״̬
// @param       cmd_index       ��������
// @param       param           ����
// @param       flags           ��־
// @return      void
// Sample usage:                sdio_get_state();
//-------------------------------------------------------------------------------------------------------------------
uint32 sdio_get_state (void)
{
    uint32 flags = SDIO->CLRMMCINT;

    if (SDIO->BUFCTL & 0x00000001)
        flags |= 0x00000200;
    if (SDIO->BUFCTL & 0x00000002)
        flags |= 0x00000400;

    return flags;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       sdio �����ǰ״̬
// @param       flags           ��Ӧ״̬
// @return      void
// Sample usage:                sdio_clear_state(0x00000009);
//-------------------------------------------------------------------------------------------------------------------
void sdio_clear_state (uint32 flags)
{
    SDIO->CLRMMCINT = (0x000000FF & flags);
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       sdio ִ������
// @param       cmd_index       ��������
// @param       param           ����
// @param       flags           ��־
// @return      void
// Sample usage:                sdio_execute_cmd(0, 0, 0);
//-------------------------------------------------------------------------------------------------------------------
sdio_error_state_enum sdio_execute_cmd (uint8 cmd_index, uint32 param, uint32 flags)
{
    uint32 cmd_io = 0;
    uint32 cmd_io_ext = 0;
    uint32 timeout_count = 0;
    sdio_error_state_enum return_state = SDIO_ERROR_STATE_NO_ERROR;

    do{
        SDIO->CMDBUF[4] = 0x40 | cmd_index;
        SDIO->CMDBUF[3] = ((param & 0xff000000) >> 24);
        SDIO->CMDBUF[2] = ((param & 0xff0000  ) >> 16);
        SDIO->CMDBUF[1] = ((param & 0xff00    ) >> 8);
        SDIO->CMDBUF[0] = ( param & 0xff      );

        cmd_io          = 0x00000004;
        cmd_io_ext      = SDIO->MMCIOMBCTL;
        cmd_io_ext     &= 0xFFFFFFF8;

        if (0u != (flags & 0x00000040))
        {
            cmd_io_ext |= 0x00000002;
            SDIO->MMCIO = 0u;
            SDIO->MMCIOMBCTL = cmd_io_ext | 0x00000001;
        }
        else
        {
            if (0u != (flags & 0x00000001) )
            {
                cmd_io |= 0x00000002;
            }
            if (0u != (flags & 0x00000004) )
            {
                cmd_io |= 0x00000010;
            }
            if (0u != (flags & 0x00000080) )
            {
                cmd_io |= 0x00000001;
            }
            SDIO->MMCIOMBCTL = cmd_io_ext;
            SDIO->MMCIO = cmd_io;
        }

        while (0u == (0x00000001 & sdio_get_state()))
        {
            timeout_count ++;
            if(SDIO_TIMEOUT_COUNT < timeout_count)
            {
                return_state = SDIO_ERROR_STATE_TIME_OUT;
                break;
            }
            system_delay_ms(1);
        }
        if(SDIO_ERROR_STATE_TIME_OUT == return_state)
            break;
        sdio_clear_state(0x00000001);
    }while(0);
    return SDIO_ERROR_STATE_NO_ERROR;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       sdio ��������
// @param       data            ����
// @return      void
// Sample usage:                sdio_execute_data(0x00000001);
//-------------------------------------------------------------------------------------------------------------------
void sdio_execute_data (uint32 data)
{
    uint32 cmd_io = 0u;
    uint32 cmd_io_ext = SDIO->MMCIOMBCTL;

    cmd_io_ext &= 0xFFFFFFF8;

    if (0u != (data & 0x00000002) )
    {
        cmd_io |= 0x00000001;
    }
    if (0u != (data & 0x00000001) )
    {
        cmd_io |= 0x00000003;
    }
    if (0u != (data & 0x00000020) )
    {
        cmd_io_ext |= 0x000000001;
    }
    else if (0u != (data & 0x00000040) )
    {
        cmd_io_ext |= 0x000000003;
    }

    SDIO->MMCIO = cmd_io;
    SDIO->MMCIOMBCTL = cmd_io_ext;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       sdio ������Ӧ
// @param       type            ��Ӧ����
// @param       *resp           ��Ӧ������ ��������Ϊ NULL ��������
// @return      void
// Sample usage:                sdio_request_resp(SDIO_RESP_TYPE_R1, NULL);
//-------------------------------------------------------------------------------------------------------------------
sdio_error_state_enum sdio_request_resp (sdio_resp_type_enum type, uint32 *resp)
{
    uint32 cmd_io = 0x0000000C;
    uint32 timeout_count = 0;
    sdio_error_state_enum return_state = SDIO_ERROR_STATE_NO_ERROR;

    do{ 
        if (type == SDIO_RESP_TYPE_R2)
            cmd_io |= 0x00000010;
        SDIO->MMCIO = cmd_io;

        while (0u == (0x00000001 & sdio_get_state()))
        {
            timeout_count ++;
            if(SDIO_TIMEOUT_COUNT < timeout_count)
            {
                return_state = SDIO_ERROR_STATE_TIME_OUT;
                break;
            }
            system_delay_ms(1);
        }
        if(SDIO_ERROR_STATE_TIME_OUT == return_state)
            break;
        sdio_clear_state(0x00000009);

        uint32 buf[4];
        buf[0] = (SDIO->CMDBUF[3] << 24)
              | (SDIO->CMDBUF[2] << 16)
              | (SDIO->CMDBUF[1] << 8 )
              | (SDIO->CMDBUF[0]);

        if (type == SDIO_RESP_TYPE_R2)
        {
            buf[1] = (SDIO->CMDBUF[7] << 24)
                  | (SDIO->CMDBUF[6] << 16)
                  | (SDIO->CMDBUF[5] << 8 )
                  | (SDIO->CMDBUF[4]);
            buf[2] = (SDIO->CMDBUF[11] << 24)
                  | (SDIO->CMDBUF[10] << 16)
                  | (SDIO->CMDBUF[9 ] << 8 )
                  | (SDIO->CMDBUF[8 ]);
            buf[3] = (SDIO->CMDBUF[15] << 24)
                  | (SDIO->CMDBUF[14] << 16)
                  | (SDIO->CMDBUF[13] << 8 )
                  | (SDIO->CMDBUF[12]);
        }
        if(NULL != resp)
        {
            memcpy(resp, buf, sizeof(buf));
        }
    }while(0);
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       sdio ������������λ��
// @param       width           ��������λ��
// @return      void
// Sample usage:                sdio_set_data_bus_width(SDIO_DATA_BUS_1BIT);
//-------------------------------------------------------------------------------------------------------------------
void sdio_set_data_bus_width (sdio_data_bus_width_enum width)
{
    if(SDIO_DATA_BUS_4BIT == width)
        SDIO->MMCCTRL |= 0x00000080;
    else
        SDIO->MMCCTRL &= 0xFFFFFF7F;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       sdio ʧ��
// @param       void
// @return      void
// Sample usage:                sdio_disable();
//-------------------------------------------------------------------------------------------------------------------
void sdio_disable (void)
{
    SDIO->MMCCARDSEL &= 0xFFFFFF3F;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       sdio ʹ��
// @param       void
// @return      void
// Sample usage:                sdio_enable();
//-------------------------------------------------------------------------------------------------------------------
void sdio_enable (void)
{
    SDIO->MMCCARDSEL |= 0x000000C0;
}

//-------------------------------------------------------------------------------------------------------------------
// @brief       sdio ��ʼ��
// @param       void
// @return      void
// Sample usage:                sdio_init();
//-------------------------------------------------------------------------------------------------------------------
void sdio_init (void)
{
    uint32 register_data = 0;

    afio_init(C8 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO D0  ���ų�ʼ��
    afio_init(C9 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO D1  ���ų�ʼ��
    afio_init(C10, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO D2  ���ų�ʼ��
    afio_init(C11, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO D3  ���ų�ʼ��
    afio_init(C12, GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO CLK ���ų�ʼ��
    afio_init(D2 , GPO, GPIO_AF12, GPO_AF_PUSH_PULL);                           // SDIO CMD ���ų�ʼ��

    system_delay_ms(100);

    RCC->AHB1ENR |= (0x00000400);                                               // ʹ�� SDIO ʱ��
    RCC->AHB1RSTR |= (0x00000400);                                              // ��λ SDIO ����
    RCC->AHB1RSTR &= (0xFFFFFBFF);                                              // ��λ ����

    sdio_enable();

    register_data = SDIO->MMCCTRL;
    register_data |= 0x00000001;                                                // �л� SDIO �ӿڵ� SD/MMC/SDIO ģʽ
    register_data |= 0x00000002;                                                // �л� SDIO �ӿڵ� SD/MMC/SDIO �˿��Զ�����ģʽ
    register_data &= 0xFFFFFFFB;                                                // CMD ����ģʽѡ�� �������
    register_data =  ((register_data & 0xFFFFFFC7) | 0x00000010);               // CLK ʱ������ѡ�� ��׼ʱ������Ƶ
    register_data |= 0x00000040;                                                // SD/MMC/SDIO �˿ڸ��ٴ���ģʽ ��ʱ��ԴΪ AHB ʱ��
    register_data &= 0xFFFFFF7F;                                                // SD/MMC/SDIO �˿� 1bit ���߿��
    register_data &= 0xFFFFF8FF;                                                // SD/MMC ģʽ SDIO �жϽ�ֹ SDIO ���ȴ�����
    SDIO->MMCCTRL = register_data;

    SDIO->MMCCRCCTL = 0x00000000;                                               // ��ֹ���� CRC ����
    SDIO->MMCIOMBCTL = 0x00000000;                                              // �����Զ���鴫��
                                                                                // ���ݷ���д��
                                                                                // ����ȫ�Զ�����Ͷ������
                                                                                // CLK����Ĭ��
                                                                                // ���ó�ʱѡ��
    SDIO->MMCCRCCTL |= 0x000000C0;                                              // ���� CMD �� DAT ��·�� CRC ��·ʹ��
}
