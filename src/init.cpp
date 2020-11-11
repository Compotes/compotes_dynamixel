
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <iostream>


ros::Publisher servo1;
ros::Publisher servo2;


int main(int argc, char **argv) {
    ros::init(argc, argv, "init");
    ros::NodeHandle n;
    servo1 = n.advertise<std_msgs::Float64>("/joint1_controller/command", 1000);
    servo2 = n.advertise<std_msgs::Float64>("/joint2_controller/command", 1000);

    ros::Rate loop_rate(50);

    ros::Time time = ros::Time::now();
    
    std_msgs::Float64 msg;
    msg.data = 0.5;
    
    while (ros::ok()) {
        time = ros::Time::now();
        
        msg.data *= -1;
        servo1.publish(msg);
        servo2.publish(msg);
        ROS_INFO("%d, %lf", 2, msg.data);
        ROS_INFO("%d, %lf", 1, msg.data);

        ros::Duration(1).sleep();

        ros::spinOnce();
        loop_rate.sleep();
    }
}