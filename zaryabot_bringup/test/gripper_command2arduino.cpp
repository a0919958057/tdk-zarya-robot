#include <ros/ros.h>
#include "modbus/modbus-rtu.h"
#include "zaryabot_msgs/GripperCMD.h"
#include "zaryabot_srv/working_state.h"

#define MODBUS_SLAVE_ID (10)
#define NINEGRIPPER_COMMAND   (200)
#define HITGRIPPER_COMMAND    (201)

bool iscommunicate(false);

// Setup modbus
modbus_t *ctx;
bool update(zaryabot_srv::working_state::Request  &req,
            zaryabot_srv::working_state::Response &res);
void GripperCMDCallback(const zaryabot_msgs::GripperCMDConstPtr& msg);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "griper_command2arduino");
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
  ros::ServiceServer service = nh.advertiseService("/connect2gripper", update);
  ros::Subscriber sub = nh.subscribe("/gripper/command",10,GripperCMDCallback);

  ROS_INFO("Hello world!");
  ros::spin();
  //ros::Rate r(10);

  modbus_free(ctx);

   // ros::spinOnce();
   //r.sleep();

return 0;
}
void GripperCMDCallback(const zaryabot_msgs::GripperCMDConstPtr& msg)
{
  if(iscommunicate){
    //ROS_INFO("Velocity : %10.5f , %10.5f , %10.5f , %10.5f",msg ->velocity[0],msg ->velocity[1],msg ->velocity[2],msg ->velocity[3] );
    //ROS_INFO("Mode     : %d , %d , %d , %d", msg ->mode[0], msg ->mode[1], msg ->mode[2], msg ->mode[3]);
    int muti = 1;
    int sum = 0;
    for(int i=4;i>=0;i--){
      if(msg->ninegripper[i]==1){
          sum += muti;
      }
      if(msg->ninegripper[i]==2){
          sum += 2 * muti;
      }
      muti *= 3;
    }
    int hitmuti = 1;
    int hitsum = 0;
    for(int i=4;i>=0;i--){
      if(msg->hitgripper[i]==true){
          hitsum += hitmuti;
      }
      hitmuti *= 2;
    }
    int v1 = sum;
    int v2 = hitsum;
    const uint16_t value[2] = {v1,v2};
    modbus_write_registers(ctx, NINEGRIPPER_COMMAND ,2, value);
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
