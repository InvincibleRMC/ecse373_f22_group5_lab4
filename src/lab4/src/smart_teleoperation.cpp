#include <sensor_msgs/LaserScan.h>
#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"


geometry_msgs::Twist output_msg;
geometry_msgs::Twist input_msg;
sensor_msgs::LaserScan lidar_msg;

ros::Publisher cmd_vel;
int enteredLidar=0;

void lidarCallback(const sensor_msgs::LaserScan msg){
    enteredLidar = 1;
    lidar_msg=msg;
}

void velocityCallback(const geometry_msgs::Twist msg){
    
    if(enteredLidar==1){
    ROS_INFO("velocityCallback");
    float x = msg.linear.x;

    if(x>0){
        
        int i = lidar_msg.ranges.size()/2;
        float distance_ahead = lidar_msg.ranges[i];
        ROS_INFO("%f",distance_ahead);
        if(distance_ahead > 1){
            cmd_vel.publish(msg);
        }
        else{
            ROS_INFO("Wall Detected!!");
            output_msg = msg;
            output_msg.linear.x=0;
            cmd_vel.publish(output_msg);
        }
    }
    else{
    cmd_vel.publish(msg);
    }
   
    }
}


int main(int argc, char* argv[]) {
    ROS_INFO("Starting up NODE!!");
    ros::init(argc, argv, "lab4"); 
    ros::NodeHandle nh;
    
    cmd_vel = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    
    ros::Subscriber des_vel = nh.subscribe<geometry_msgs::Twist>("des_vel", 1000,velocityCallback);
    ros::Subscriber lidar_1 = nh.subscribe<sensor_msgs::LaserScan>("laser_1", 1000,lidarCallback);
    
    ros::spin();
}
