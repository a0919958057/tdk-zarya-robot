#include <ros/ros.h>

#include <geometry_msgs/Twist.h>

#include <modbus/modbus-rtu.h>
#include "zaryabot_msgs/NumPunchState.h"

#define MOTOR_REG_ADDR_VELOCITY (100)
#define MODBUS_SLAVE_ID (11)

// Setup modbus
modbus_t *ctx;
modbus_t *ctx1;

//void wheelcmdcallback(const zaryabot_msgs::WheelCMDConstPtr& msg);
void vel_command_callback(const geometry_msgs::TwistConstPtr& msg);

int main(int argc, char **argv)
{
  /*************** Set up ROS. *****************/
  ros::init(argc, argv, "modbus_exampe_node");
  ros::NodeHandle nh;


  /*********************************************/



  /*************** Setup modbus ****************/


  ctx = modbus_new_rtu("/dev/ttyACM1", 9600, 'N', 8, 1);
  ctx1= modbus_new_rtu("/dev/ttyUSB0", 9600, 'N', 8, 1);

  modbus_set_debug(ctx, true);
  modbus_set_debug(ctx1, true);

  if (ctx == NULL) {
      ROS_ERROR("Can't create MODBUS context");
      return -1;
  }
  if (ctx1 == NULL) {
      ROS_ERROR("Can't create MODBUS context");
      return -1;
  }

  modbus_set_slave(ctx, MODBUS_SLAVE_ID);
  modbus_set_slave(ctx,10);

  modbus_connect(ctx);
  modbus_connect(ctx1);




  /*********************************************/


  ROS_INFO("Hello world!");
  const uint16_t value[2] = {10,4};
  const uint16_t mega[2] = {200,100};

  modbus_write_registers(ctx,MOTOR_REG_ADDR_VELOCITY,2,value);
  modbus_write_registers(ctx1,MOTOR_REG_ADDR_VELOCITY,2,mega);

  //ros::Subscriber sub = nh.subscribe("/vel_cmd", 100, vel_command_callback);

  ros::spin();



  modbus_free(ctx);
  modbus_free(ctx1);

  return 0;
}

/*void vel_command_callback(const geometry_msgs::TwistConstPtr& msg) {
  int dot_theta = static_cast<int>(msg->angular.z);

  modbus_write_register(ctx, MOTOR_REG_ADDR_VELOCITY, dot_theta);
}*/
/*void wheelcmd_callback(const zaryabot_msgs::WheelCMDConstPtr& msg) {
  int dot_theta = static_cast<int>(msg->position[0]);

  //modbus_write_registers(ctx, MOTOR_REG_ADDR_VELOCITY, dot_theta);
}*/
