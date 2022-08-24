# MM32F3277G8P-Intelligent-Vehicle-Control-Board
本项目是2022年全国大学生智能车竞赛平衡信标组桂林信息科技学院Tornado的硬件开源;<br>
硬件非常普通,引脚大部分兼容某飞科技的开源程序,某飞的代码虽然有些BUG,但是大体方便可靠;<br>
电源设计参考了2021年立创开源广场moximoxi大佬的开源硬件:[传送门](https://oshwhub.com/moximoxi/shuang-jum3_mini)
***
### 主要特点
+ 主控采用了灵动微电子MM32F3277G8P作为MCU;<br>
+ 使用Kicad6.0.2绘制;
+ 电机驱动使用之前开源的EG3013栅极驱动以及N-Channel Mosfet;<br>
+ 预留S-bus接口,方便老车退役改成遥控车;(bushi)<br>
+ 预留并口屏,理论上相比SPI屏幕刷新更快,节约CPU时间;
***

### 外观
![PCB正面](/images/00.jpg)

![安装图](/images/01.jpg)

![安装图](/images/02.jpg)
***