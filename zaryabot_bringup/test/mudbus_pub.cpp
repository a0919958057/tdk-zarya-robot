#include "ros/ros.h"
#include "std_msgs/String.h"
#include "zaryabot_msgs/modbus_test.h"

using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "mudbus_pub");
  ros::NodeHandle nh;

  ros::Publisher chatter_pub = nh.advertise<zaryabot_msgs::modbus_test>("/vel_cmd", 10);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    zaryabot_msgs::modbus_test msg;
    cout<< "slaveID:" <<endl;
    cin >> msg.slaveID;
    cin.get();

    cout<<"value:"<<endl;
    cin>> msg.value;
    cin.get();

    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }

  return 0;
}
