#include <ros/ros.h>
#include "robottrancmd.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "wheel_command");
  ros::NodeHandle nh;


//32 28 10 cm
  RobotTranCMD::RobotWheelGeoDef geo(0.32,0.28,0.1);
  //RobotTranCMD RbTranCMD(nh,);

  RobotTranCMD pub(nh,"output", "input", geo);
  ROS_INFO("Hello world!");
  ros::Rate r(10);

  pub.enableMotor(true);

  while(ros::ok()) {

    pub.publishJointCMD();

    ros::spinOnce();
    r.sleep();

  }

}
