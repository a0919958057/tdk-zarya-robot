#include "ros/ros.h"
#include "std_msgs/String.h"
#include "remote_control/RemoteCMD.h"
#include "geometry_msgs/Twist.h"
#include "zaryabot_msgs/GripperCMD.h"
#include "sensor_msgs/Imu.h"
#include "tf/tf.h"
#include "zaryabot_srv/working_state.h"

#define forward        (1)
#define backward       (2)
#define turnleft       (3)
#define turnright      (4)
#define forward_left   (5)
#define forward_right  (6)
#define backward_left  (7)
#define backward_right (8)

int HandwheelStatus = 0;
int WriteStatus = 0;
int CarStatus = 0;
int ButtomStatus[11] ={0};


int last = 0;
int now  = 0;
double turndeg = 90;
double goaldeg,startdeg;
double nowdeg;
int rightcount=0,leftcount=0;
enum State{STOP,TURN_RIGHT,TURN_LEFT};
State turnstate = STOP;
enum Mode{NINE,HIT,SPEED,SET};
Mode buttommode;
enum num{one,two,three,four,zero};
num column = one;
num hitnum = one;
int speed;
void imuupdate(const sensor_msgs::ImuConstPtr& msg)
{
  tf::Matrix3x3 m(tf::Quaternion(msg->orientation.x,msg->orientation.y,msg->orientation.z,msg->orientation.w));
  double roll,pitch,yaw;
  m.getRPY(roll,pitch,yaw);
  //m_roll = (roll);
  nowdeg = yaw * 180 /M_PI;

  //ROS_INFO("I heard: [%f]", degree);
  //ROS_INFO("Imu Orientation x:[%f], y:[%f], z:[%f]", roll, pitch, yaw);

}
void remoteCMDupdate(const remote_control::RemoteCMDConstPtr& msg)
{
  //update
  HandwheelStatus = static_cast <int>(msg ->handwheel);
  WriteStatus     = static_cast <int>(msg ->write);
  CarStatus       = static_cast <int>(msg ->car);
  for(int i=0;i<11;i++){
    ButtomStatus[i] = static_cast <int>(msg ->buttom[i]);
  }
  //ROS_INFO("Car:  %d",CarStatus);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "wheel_command_pub2");
  ros::NodeHandle nh;
  geometry_msgs::Twist twist;
  zaryabot_msgs::GripperCMD gripper;
  zaryabot_srv::working_state working;

  ros::Publisher TwistPub = nh.advertise<geometry_msgs::Twist>("/input",10);
  ros::Publisher GripperPub = nh.advertise<zaryabot_msgs::GripperCMD>("/gripper/command",10);
  ros::Subscriber RemoteSub = nh.subscribe("/remote/command", 1000, remoteCMDupdate);
  ros::Subscriber sub = nh.subscribe("/imu/data", 50, imuupdate);
  ros::ServiceClient gripper_client = nh.serviceClient<zaryabot_srv::working_state>("/connect2gripper");
  ros::ServiceClient chassis_client = nh.serviceClient<zaryabot_srv::working_state>("/connect2chassis");

  ros::Rate r(10);
  while(ros::ok()){
    //update remoteCMD to twist

    //buttom to gripper
    //
    if(ButtomStatus[0]==0 && ButtomStatus[1] == 0){
      buttommode = SPEED;
      working.request.enable = true;
      if(chassis_client.call(working))
        ROS_INFO("run chassis ");
      else
        ROS_ERROR("can't run chassis");
      working.request.enable = false;
      if(gripper_client.call(working))
        ROS_INFO("stop gripper");
      else
        ROS_ERROR("can't stop gripper");
    }
    if(ButtomStatus[0]==1 && ButtomStatus[1] == 1){
      buttommode = SET;
      working.request.enable = false;
      if(chassis_client.call(working))
        ROS_INFO("stop chassis ");
      else
        ROS_ERROR("can't stop chassis");
      if(gripper_client.call(working))
        ROS_INFO("stop gripper");
      else
        ROS_ERROR("can't stop gripper");
    }
    if(ButtomStatus[0]==1 && ButtomStatus[1] == 0){
      buttommode = HIT;
      working.request.enable = false;
      if(chassis_client.call(working))
        ROS_INFO("stop chassis ");
      else
        ROS_ERROR("can't stop chassis");
      working.request.enable = true;
      if(gripper_client.call(working))
        ROS_INFO("run gripper");
      else
        ROS_ERROR("can't run gripper");
    }
    if(ButtomStatus[1]==1 && ButtomStatus[0] == 0){
      buttommode = NINE;
      working.request.enable = false;
      if(chassis_client.call(working))
        ROS_INFO("stop chassis ");
      else
        ROS_ERROR("can't stop chassis");
      working.request.enable = true;
      if(gripper_client.call(working))
        ROS_INFO("run gripper");
      else
        ROS_ERROR("can't run gripper");
    }
    switch (buttommode) {
    case NINE:
      switch (column) {
      case one:
        gripper.ninegripper[0] = 0;
        if(ButtomStatus[5]==1 || ButtomStatus[6]==1 || ButtomStatus[7]==1)
          column = zero;
        break;
      case two:
        gripper.ninegripper[0] = 1;
        if(ButtomStatus[5]==1 || ButtomStatus[6]==1 || ButtomStatus[7]==1)
          column = zero;
        break;
      case three:
        gripper.ninegripper[0] = 2;
        if(ButtomStatus[5]==1 || ButtomStatus[6]==1 || ButtomStatus[7]==1)
          column = zero;
        break;
      case zero:
        if(ButtomStatus[5]==1)
          column = one;
        if(ButtomStatus[6]==1)
          column = two;
        if(ButtomStatus[7]==1)
          column = three;
        break;
      }
      gripper.ninegripper[1] = (ButtomStatus[3] ==0)?0:1;
      gripper.ninegripper[2] = (ButtomStatus[4] ==0)?0:1;
      gripper.ninegripper[3] = (ButtomStatus[10]==0)?0:1;
      gripper.ninegripper[4] = (ButtomStatus[9] ==0)?0:1;
      break;
    case HIT:
      switch (hitnum) {
      case one:
        gripper.hitgripper[0] = 0;
        gripper.hitgripper[1] = 0;
        if(ButtomStatus[5]==1 || ButtomStatus[6]==1 || ButtomStatus[7]==1 || ButtomStatus[10]==1)
          hitnum = zero;
        break;
      case two:
        gripper.hitgripper[0] = 0;
        gripper.hitgripper[1] = 1;
        if(ButtomStatus[5]==1 || ButtomStatus[6]==1 || ButtomStatus[7]==1 || ButtomStatus[10]==1)
          hitnum = zero;
        break;
      case three:
        gripper.hitgripper[0] = 1;
        gripper.hitgripper[1] = 0;
        if(ButtomStatus[5]==1 || ButtomStatus[6]==1 || ButtomStatus[7]==1 || ButtomStatus[10]==1)
          hitnum = zero;
        break;
      case four:
        gripper.hitgripper[0] = 1;
        gripper.hitgripper[1] = 1;
        if(ButtomStatus[5]==1 || ButtomStatus[6]==1 || ButtomStatus[7]==1 || ButtomStatus[10]==1)
          hitnum = zero;
        break;
      case zero:
        if(ButtomStatus[5]==1)
          hitnum = one;
        if(ButtomStatus[6]==1)
          hitnum = two;
        if(ButtomStatus[7]==1)
          hitnum = three;
        if(ButtomStatus[10]==1)
          hitnum = four;
        break;
      }
      gripper.hitgripper[2] = (ButtomStatus[4]==0)?0:1;
      gripper.hitgripper[3] = (ButtomStatus[3]==0)?0:1;
      gripper.hitgripper[4] = (ButtomStatus[2]==0)?0:1;
      break;
    case SPEED:
      switch (CarStatus) {
      case forward:
        twist.linear.x  = speed;
        twist.linear.y  = 0;
        twist.angular.z = 0;
        break;
      case backward:
        twist.linear.x  = -speed;
        twist.linear.y  = 0;
        twist.angular.z = 0;
        break;
      case turnleft:
        twist.linear.x  = 0;
        twist.linear.y  = -speed;
        twist.angular.z = 0;
        break;
      case turnright:
        twist.linear.x  = 0;
        twist.linear.y  = speed;
        twist.angular.z = 0;
        break;
      case forward_left:
        twist.linear.x  = speed/2;
        twist.linear.y  = -speed/2;
        twist.angular.z = 0;
        break;
      case forward_right:
        twist.linear.x  = speed/2;
        twist.linear.y  = speed/2;
        twist.angular.z = 0;
        break;
      case backward_left:
        twist.linear.x  = -speed/2;
        twist.linear.y  = -speed/2;
        twist.angular.z = 0;
        break;
      case backward_right:
        twist.linear.x  = -speed/2;
        twist.linear.y  = speed/2;
        twist.angular.z = 0;
        break;
      default:
        twist.linear.x  = 0;
        twist.linear.y  = 0;
        twist.angular.z = 0;
        break;
      }
      //handwheel

        if(HandwheelStatus>50000)
          now = (HandwheelStatus-65536) / 200;
        else
          now = HandwheelStatus / 200;
        if(now - last < 0){
        rightcount++;
        ROS_INFO("r %d",rightcount);
        }
        else if(now - last > 0){
        leftcount++;
        ROS_INFO("l %d",leftcount);
        }
        switch (turnstate) {
        case STOP:
          ROS_INFO("s");
          startdeg = nowdeg;
          if(rightcount != 0){
            goaldeg = atan2(sin(( -turndeg +startdeg )*M_PI/180),cos(( -turndeg +startdeg )*M_PI/180)) * 180/M_PI;
            turnstate = TURN_RIGHT;
          }else if(leftcount != 0){
            goaldeg = atan2(sin(( turndeg +startdeg )*M_PI/180),cos(( turndeg +startdeg )*M_PI/180)) * 180/M_PI;
            turnstate = TURN_LEFT;
          }

          break;
        case TURN_RIGHT:
          ROS_INFO("R");
          twist.linear.x  = 0;
          twist.linear.y  = 0;
          twist.angular.z = 100;
          if(abs(goaldeg - nowdeg)<=1){
            turnstate = STOP;
            rightcount--;
          }
          break;
        case TURN_LEFT:
          ROS_INFO("L");
          twist.linear.x  = 0;
          twist.linear.y  = 0;
          twist.angular.z = -100;
          if(abs(goaldeg - nowdeg)<=1){
            turnstate = STOP;
            leftcount--;
          }
          break;
        }
        last = now;
        ROS_INFO("I heard: [%f]", nowdeg);
      break;
    case SET:
      if(HandwheelStatus>255 && HandwheelStatus < 50000)
        speed = 255;
      else if(HandwheelStatus > 50000)
        speed = 0;
      else
        speed = HandwheelStatus;
      ROS_INFO("I heard: [%d]", speed);
      break;
    }



    //
    TwistPub.publish(twist);
    GripperPub.publish(gripper);
    ros::spinOnce();
    r.sleep();
  }
  return 0;
}
