#include <sensor_msgs/LaserScan.h>
#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"


geometry_msgs::Twist mgs;


int main(int argc, char* argv[]) {
    mgs.linear.x = 1.0;
    mgs.linear.y = 1.0;
    mgs.linear.z = 1.0;
    mgs.angular.x = 0.0;
    mgs.angular.y = 0.0;
    mgs.angular.z = 0.0;

    ros::init(argc, argv, "lab4"); 
    ros::NodeHandle nh;
    ros::spin();
    ros::Publisher cmd_vlc_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    cmd_vlc_pub.publish(mgs);
}
