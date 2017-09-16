#include "ros/ros.h"
#include "zaryabot_srv/working_state.h"

bool update(zaryabot_srv::working_state::Request &req,
         zaryabot_srv::working_state::Response &res)
{
  res.working = (req.enable == true)?true:false;
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "master_service");
  ros::NodeHandle nh;

  ros::ServiceServer service = nh.advertiseService("/working_state", update);
  ROS_INFO("Ready to add two ints.");
  ros::spin();

  return 0;
}
