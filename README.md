# tdk-zarya-robot

ROS Stack for Zarya機器人使用
- 應用於TDK比賽
---
## Required Library
###  1. OpenCV 3.2.0
###  2. libModbus
**Install instruction for Ubuntu 16.04**

`
sudo apt-get install libmodbus-* -y
`
---

## Sensor List
- Hokuyo urg-04lx-ug01
- InvenSense MPU-6050 integrated with Arduino
其餘評估中

## Actuator List
- Dynamixel AX-12A
其餘評估中

## CHANGE LOG
### 0.0.1 (2017/03/24)

- 初始化專案
  - 建立 ZaryaBot metapackage
    
      相依zaryabot_bringup, zaryabot_description
  - 建立 zaryabot_bringup
  
      啟動機器人時將使用這個package
  - 建立 zaryabot_description
  
      機器人描述package，建模模擬等等都於此package
