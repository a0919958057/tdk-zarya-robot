#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <modbus/modbus-rtu.h>
#include <zaryabot_msgs/modbus_test.h>

#define MOTOR_REG_ADDR_VELOCITY (100)
#define MODBUS_SLAVE_ID (10)

// Setup modbus
modbus_t *ctx;


//void wheelcmdcallback(const zaryabot_msgs::WheelCMDConstPtr& msg);
void vel_command_callback(const zaryabot_msgs::modbus_testConstPtr& msg);

int main(int argc, char **argv)
{
  /*************** Set up ROS. *****************/
  ros::init(argc, argv, "modbus_exampe_node");
  ros::NodeHandle nh;


  /*********************************************/



  /*************** Setup modbus ****************/


  ctx = modbus_new_rtu("/dev/ttyUSB0", 9600, 'N', 8, 1);


  modbus_set_debug(ctx, true);


  if (ctx == NULL) {
      ROS_ERROR("Can't create MODBUS context");
      return -1;
  }


  modbus_set_slave(ctx, MODBUS_SLAVE_ID);


  modbus_connect(ctx);
  /*********************************************/


  ROS_INFO("Hello world!");
  //const uint16_t value[2] = {10,4};
  modbus_write_register(ctx,MOTOR_REG_ADDR_VELOCITY,1);
  ros::Subscriber sub = nh.subscribe("/vel_cmd", 10, vel_command_callback);
  ros::spin();
  modbus_free(ctx);

  return 0;
}

void vel_command_callback(const zaryabot_msgs::modbus_testConstPtr& msg) {
  ROS_INFO("set slaveID to %d", msg->slaveID);
  modbus_set_slave(ctx, msg->slaveID);
  ROS_INFO("write value to %d", msg->value);
  modbus_write_register(ctx, MOTOR_REG_ADDR_VELOCITY, msg->value);
}
/*void wheelcmd_callback(const zaryabot_msgs::WheelCMDConstPtr& msg) {
  int dot_theta = static_cast<int>(msg->position[0]);

  //modbus_write_registers(ctx, MOTOR_REG_ADDR_VELOCITY, dot_theta);
}*/
