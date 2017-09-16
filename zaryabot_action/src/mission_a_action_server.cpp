#include <ros/ros.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mission_a_action_server");
  ros::NodeHandle nh;

  ROS_INFO("Hello world!");
}
