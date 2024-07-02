# arduino巡线小车程序代码
 ## 前言
 为了参加河北省青少年科技创新大赛，小车完成的功能之中包括了巡线设计，和光敏寻迹等，但由于时间等因素限制，只搞出来了巡线设计
 ## 材料
 ardunio r4 开发板
 TB6612电机驱动模块 
 两个直流电机
 TCRT5000红外模块
 LM2596稳压电源
 ## 接线设计
 ### 连接电机
首先，将电机连接到TB6612驱动模块：
- 左电机：
  - 左电机正极连接到TB6612的A01端口
  - 左电机负极连接到TB6612的A02端口
- 右电机：
  - 右电机正极连接到TB6612的B01端口
  - 右电机负极连接到TB6612的B02端口

### 连接TB6612电机驱动模块到Arduino
- AIN1（TB6612）连接到 Arduino 数字引脚6
- AIN2（TB6612）连接到 Arduino 数字引脚7
- BIN1（TB6612）连接到 Arduino 数字引脚4
- BIN2（TB6612）连接到 Arduino 数字引脚5
- PWMA（TB6612）连接到 Arduino 数字引脚9
- PWMB（TB6612）连接到 Arduino 数字引脚10

### 连接TCRT5000红外传感器到Arduino
- 左侧传感器：
  - VCC连接到Arduino的5V
  - GND连接到Arduino的GND
  - OUT连接到Arduino的数字引脚1
- 中间传感器：
  - VCC连接到Arduino的5V
  - GND连接到Arduino的GND
  - OUT连接到Arduino的数字引脚2
- 右侧传感器：
  - VCC连接到Arduino的5V
  - GND连接到Arduino的GND
  - OUT连接到Arduino的数字引脚3
### 连接电源
确保TB6612的VCC连接到Arduino的5V，GND连接到Arduino的GND，VM连接到电机的电源（比如电池的正极），GND连接到电机电源的负极。

## 图片展示
![image](https://github.com/MCKN007/arduino-tracking-car/blob/main/486663af21e9f1f80060d4c7eb11116.jpg)
![image](https://github.com/MCKN007/arduino-tracking-car/blob/main/86acf9d3f5a3099269393ebcdce4cc1.jpg)
![image](https://github.com/MCKN007/arduino-tracking-car/blob/main/cd20a337345d51993fc23f8cff3637a.jpg)

