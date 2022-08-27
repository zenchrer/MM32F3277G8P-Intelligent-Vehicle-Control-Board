/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,逐飞科技
 * All rights reserved.
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file             main
 * @company          成都逐飞科技有限公司
 * @author           逐飞科技(QQ3184284598)
 * @version          查看doc内version文件 版本说明
 * @Software         IAR 8.32.4 or MDK 5.28
 * @Target core      MM32F327X_G8P
 * @Taobao           https://seekfree.taobao.com/
 * @date             2022-04-11
 ********************************************************************************************************************/

#include "zf_common_headfile.h"

// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完

// **************************** 代码区域 ****************************
int main(void)
{
    clock_init(SYSTEM_CLOCK_120M); // 初始化芯片时钟 工作频率为 120MHz
    debug_init();                  // 初始化默认 Debug UART
    // 此处编写用户代码 例如外设初始化代码等
    rc_init();
    // 此处编写用户代码 例如外设初始化代码等

    while (1)
    {
        // 此处编写需要循环执行的代码

        // 此处编写需要循环执行的代码
    }
}
// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
// 问题1：屏幕不显示
//      如果使用主板测试，主板必须要用电池供电 检查屏幕供电引脚电压
//      检查屏幕是不是插错位置了 检查引脚对应关系
//      如果对应引脚都正确 检查一下是否有引脚波形不对 需要有示波器
//      无法完成波形测试则复制一个GPIO例程将屏幕所有IO初始化为GPIO翻转电平 看看是否受控
