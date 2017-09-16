#ifndef ROBOTTRANCMD_H
#define ROBOTTRANCMD_H

#include <ros/ros.h>

#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h>
#include <std_msgs/UInt8.h>
#include <zaryabot_msgs/WheelCMD.h>

// Look this : http://www.gmii.tw/makeblock/4

#define JOINT_COUNT (4)

class RobotTranCMD {
public:
  // Nested Class
  class RobotWheelGeoDef {
    public:
    RobotWheelGeoDef(double center2lr, double center2fb, double wheelRadius);

    double a;
    double b;
    double radius;
  };

public:
  RobotTranCMD(ros::NodeHandle& pNode, std::string pub_topic, std::string sub_topic, RobotWheelGeoDef& rbDef);

  void enableMotor(bool isEnable);

  void breakMotor(bool isBreak);

  void publishJointCMD();
private:
  void updateMoveCMD(const geometry_msgs::TwistConstPtr& msg);

private:
  ros::NodeHandle* masterNH;
  zaryabot_msgs::WheelCMD command;
  ros::Publisher jointCmdPub;
  ros::Subscriber rbMoveCmdSub;
  RobotWheelGeoDef rbGeo;
  bool fgMotorEN;
  bool fgMotorBreak;

};

#endif // ROBOTTRANCMD_H
