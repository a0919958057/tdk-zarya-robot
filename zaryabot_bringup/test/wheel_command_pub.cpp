#include "ros/ros.h"
#include "std_msgs/String.h"
#include "zaryabot_msgs/WheelCMD.h"
#include "geometry_msgs/Twist.h"

using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "wheel_command_pub");
  ros::NodeHandle nh;

  ros::Publisher chatter_pub = nh.advertise<geometry_msgs::Twist>("input", 10);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    geometry_msgs::Twist msg;

    cout << "X:" << endl;
    cin >> msg.linear.x;
    cin.get();

    cout << "Y:" << endl;
    cin >> msg.linear.y;
    cin.get();

    cout << "Z:" << endl;
    cin >> msg.angular.z;
    cin.get();



    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
