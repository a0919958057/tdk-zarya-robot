
#include "ros/ros.h"
#include "zaryabot_srv/working_state.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "master_client");

  ros::NodeHandle nh;
  ros::ServiceClient client = nh.serviceClient<zaryabot_srv::working_state>("/connect2gripper");
  zaryabot_srv::working_state srv;
  //srv.request.enable = true;

  if (client.call(srv))
  {
    ROS_INFO("WORKING~~~~~~~~  %d",srv.response.working);
  }
  else
  {
    ROS_INFO("Failed to call service add_two_ints");
  }
  ros::spin();

  return 0;

}

