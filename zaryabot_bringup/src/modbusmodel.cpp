#include "modbusmodel.h"

ModbusModel::ModbusModel(char* _name,size_t _lengh):
modbus_ctx(NULL),modbus_slaveID(0)
{
  if(sizeof(modbus_drive_name) < _lengh){
    ROS_INFO("failed to set modbus drive name");
  }else{
    for(int i=0;i<_lengh;i++){
      modbus_drive_name[i] = _name[i];
    }
  }


}

uint8_t ModbusModel::getSlaveID(){
  return modbus_slaveID;
}
bool ModbusModel::registerModbusInterface(modbus_t* _ctx) {

    if(_ctx == NULL) return false;

    // Register the modbus interface to this class
    modbus_ctx = _ctx;
    return true;
}
