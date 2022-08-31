# MM32F3277G8P-Intelligent-Vehicle-Control-Board

#17届智能车竞赛真的让人学到很多<br>
##&nbsp;&nbsp;&nbsp;&nbsp;前有中南大学王击教授带领学生舌战群友，顺利让获得华南赛区三等奖的多车组入围国赛，并且在后来的线下赛中取得未完赛的成绩，可天无绝人之路，举办学校提名一部分多车组未完赛的队伍获得国二，至此，省三的中南多车喜提国二。
##&nbsp;&nbsp;&nbsp;&nbsp;后又有山大威海无线充电组使用一百多克的逐飞2S 2200mAh电池跑出35.5S的好成绩，荣获国一桂冠。

## 已添加[Sbus解析例程](https://github.com/zenchrer/MM32-Sbus-Demo.git)<br>

&nbsp;&nbsp;&nbsp;&nbsp;本项目是2022年全国大学生智能车竞赛平衡信标组桂林信息科技学院Tornado(队)的硬件开源;
在一块PCB上集成了电机驱动以及其它外设接口,基本满足平衡信标组的功能需求,引脚大部分兼容某飞科技的开源程序,某飞的代码虽然有些BUG,但是大体方便可靠(个人认为比隔壁lq的好);电源部分设计参考了2021年立创开源广场moximoxi大佬的开源硬件:[传送门](https://oshwhub.com/moximoxi/shuang-jum3_mini)<br>

***
### 主要特点
+ 主控采用了灵动微电子MM32F3277G8P作为MCU;<br>
+ 电机驱动使用之前开源的EG3013栅极驱动以及N-Channel Mosfet;<br>
+ 预留S-bus接口,方便老车退役改成遥控车;(bushi)<br>
+ 预留并口屏,理论上相比SPI屏幕刷新更快,节约CPU时间;
+ 使用开源EDA软件Kicad6.0.2绘制;
***
### 开发者
组织：桂林信息科技学院 通信创新实践基地<br>
作者：zenchrer [邮箱](zenchrer@qq.com)
***

### 外观
![PCB正面](/images/00.jpg)

![安装图](/images/01.jpg)

![安装图](/images/02.jpg)
***