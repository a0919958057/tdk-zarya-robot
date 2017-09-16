#ifndef MODBUSMODEL_H
#define MODBUSMODEL_H

#include<ros/ros.h>
#include"modbus/modbus-rtu.h"
#include"zaryabot_msgs/WheelCMD.h"

#define MODBUS_BAUD (9600)
// "N" for none "E" for even "O" for odd
#define MODBUS_PARITY "N"
#define MODBUS_DATA_BITS (8)
#define MODBUS_STOP_BITS (1)

class ModbusModel {
public:
  ModbusModel(char* _name,size_t _lengh);
  uint8_t getSlaveID();
  bool registerModbusInterface(modbus_t* _ctx);
  bool write();
  bool read();

private:
  //
private:

  modbus_t *modbus_ctx;
  uint8_t modbus_slaveID;
  char modbus_drive_name[20];
  //size_t lengh;
};



#endif // MODBUSMODEL_H
