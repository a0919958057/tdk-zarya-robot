#include <ros/ros.h>
#include "robottrancmd.h"
#include "modbus/modbus-rtu.h"
#include "zaryabot_srv/working_state.h"

#define MODBUS_SLAVE_ID (9)
#define WHEEL_COMMAND   (100)

bool iscommunicate(false);

// Setup modbus
modbus_t *ctx;
bool update(zaryabot_srv::working_state::Request  &req,
            zaryabot_srv::working_state::Response &res);
void WheelCMDCallback(const zaryabot_msgs::WheelCMDConstPtr& msg);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "wheel_command2arduino");
  ros::NodeHandle nh;

  /*************** Setup modbus ****************/
  ctx = modbus_new_rtu("/dev/ttyUSB0", 115200, 'N', 8, 1);

  modbus_set_debug(ctx, true);

  if (ctx == NULL) {
      ROS_ERROR("Can't create MODBUS context");
      return -1;
  }

  modbus_set_slave(ctx, MODBUS_SLAVE_ID);

  modbus_connect(ctx);

  /*********************************************/
  ros::ServiceServer service = nh.advertiseService("/connect2chassis", update);
  ros::Subscriber sub = nh.subscribe("output",10,WheelCMDCallback);

  ROS_INFO("Hello world!");
  ros::spin();
  //ros::Rate r(10);

  modbus_free(ctx);

   // ros::spinOnce();
   //r.sleep();

return 0;
}
void WheelCMDCallback(const zaryabot_msgs::WheelCMDConstPtr& msg)

{
  if(iscommunicate){
    ROS_INFO("Velocity : %10.5f , %10.5f , %10.5f , %10.5f",msg ->velocity[0],msg ->velocity[1],msg ->velocity[2],msg ->velocity[3] );
    ROS_INFO("Mode     : %d , %d , %d , %d", msg ->mode[0], msg ->mode[1], msg ->mode[2], msg ->mode[3]);
    int v1 = static_cast <int>(msg ->velocity[0]);
    int v2 = static_cast <int>(msg ->velocity[1]);
    int v3 = static_cast <int>(msg ->velocity[2]);
    int v4 = static_cast <int>(msg ->velocity[3]);
    int m1 = static_cast <int>(msg ->mode[0]);
    int m2 = static_cast <int>(msg ->mode[1]);
    int m3 = static_cast <int>(msg ->mode[2]);
    int m4 = static_cast <int>(msg ->mode[3]);
    const uint16_t value[8] = {v1,v2,v3,v4,m1,m2,m3,m4};
    modbus_write_registers(ctx, WHEEL_COMMAND ,8, value);
  }
}
bool update(zaryabot_srv::working_state::Request  &req,
            zaryabot_srv::working_state::Response &res){
  iscommunicate = req.enable;
  if(iscommunicate)
    ROS_INFO("working");
  else
    ROS_INFO("power off");
  res.working = iscommunicate;
  return true;
}
