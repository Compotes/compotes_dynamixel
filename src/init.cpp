#include <iostream>

#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

#include "dynamixel_msgs/MotorState.h"
#include "dynamixel_msgs/JointState.h"

#include "servo/Servo.h"

ros::Publisher servo1;
ros::Publisher servo2;
ros::Subscriber sub;

int main(int argc, char **argv) {
    ros::init(argc, argv, "init");
    ros::NodeHandle n;

    Servo s1 = Servo(1, &n);
    Servo s2 = Servo(2, &n);


    ros::Rate loop_rate(50);

    //std_msgs::Float64 msg;
   // msg.data += 1;
    //cout << s.publisherTopic() << "\n" << s.subscriberTopic() << "\n";
    s1.setPosition(-3.14);
    s2.setPosition(-3.14);
    float angle = 5;
    while (ros::ok()) {        

        if (angle > -1) angle = -3.14;
        else angle = 0;
        
        s1.setPosition(angle);
        s2.setPosition(angle);
        
        ros::Duration(1).sleep();

        ros::spinOnce();
        loop_rate.sleep();
    }
}