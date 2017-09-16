#include "robottrancmd.h"

RobotTranCMD::RobotWheelGeoDef::RobotWheelGeoDef(double center2lr, double center2fb, double wheelRadius)
  : a(center2lr),
    b(center2fb),
    radius(wheelRadius)
{}

RobotTranCMD::RobotTranCMD(ros::NodeHandle& pNode,
                           std::string pub_topic,
                           std::string sub_topic,
                           RobotWheelGeoDef& rbDef)
  : masterNH(&pNode), rbGeo(rbDef), fgMotorEN(false),fgMotorBreak(false) {
  // initialize command message
  for(int i=0; i< JOINT_COUNT; i++) {
    command.jointid.push_back(static_cast<uint8_t>(i));
    command.mode.push_back(zaryabot_msgs::WheelCMD::MODE_STOP);
    command.position.push_back(0.0);
    command.velocity.push_back(0.0);
  }

  // Create publisher
  jointCmdPub = masterNH->advertise<zaryabot_msgs::WheelCMD>(pub_topic,10);
  rbMoveCmdSub = masterNH->subscribe(sub_topic, 10, &RobotTranCMD::updateMoveCMD,this);
}

void RobotTranCMD::enableMotor(bool isEnable) {
  fgMotorEN = isEnable;
}

void RobotTranCMD::breakMotor(bool isBreak) {
  fgMotorBreak = isBreak;
}

void RobotTranCMD::publishJointCMD() {
  if(command.velocity[0] == 0 && command.velocity[1] == 0 && command.velocity[2] == 0 && command.velocity[3]== 0){
    RobotTranCMD::breakMotor(true);

  }else{

    RobotTranCMD::breakMotor(false);
  }

  if(fgMotorEN) {
    // TODO set command.mode[0 ~ 3] to cw or ccw
    for(int i=0; i<JOINT_COUNT; i++ ){
      command.mode[i] = zaryabot_msgs::WheelCMD::MODE_EN;
    }
  }
  else {
    for(int i=0; i<JOINT_COUNT; i++) {
      command.mode[i] = zaryabot_msgs::WheelCMD::MODE_STOP;
    }
  }

  if(fgMotorBreak) {
    for(int i=0; i<JOINT_COUNT; i++) {
      command.mode[i] = zaryabot_msgs::WheelCMD::MODE_BRAKE;
    }
  }
//
  ROS_INFO("Velocity : LF %10.5f , RF %10.5f , LB %10.5f , RB %10.5f",command.velocity[0],command.velocity[1],command.velocity[2],command.velocity[3]);
  ROS_INFO("Mode     : %d , %d , %d , %d",command.mode[0],command.mode[1],command.mode[2],command.mode[3]);
  jointCmdPub.publish(command);
}

void RobotTranCMD::updateMoveCMD(const geometry_msgs::TwistConstPtr& msg) {
  double v_x = msg->linear.x;
  double v_y = msg->linear.y;
  double v_yaw = msg->angular.z;

  double v1 = v_x + v_y - v_yaw*(rbGeo.a + rbGeo.b);
  double v2 = v_x - v_y + v_yaw*(rbGeo.a + rbGeo.b);
  double v3 = v_x - v_y - v_yaw*(rbGeo.a + rbGeo.b);
  double v4 = v_x + v_y + v_yaw*(rbGeo.a + rbGeo.b);

  //for(int i=0;i<JOINT_COUNT;i++){
    command.velocity[0] = v1;
    command.velocity[1] = v2;
    command.velocity[2] = v3;
    command.velocity[3] = v4;



  // TODO translate v1 ~ v4 into Joint velocity(rad/sec)
}
