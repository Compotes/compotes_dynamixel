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
    servo1 = n.advertise<std_msgs::Float64>("/joint1_controller/command", 1000);
    servo2 = n.advertise<std_msgs::Float64>("/joint2_controller/command", 1000);

    Servo s = Servo(1, &n, "/joint2_controller");


    ros::Rate loop_rate(50);

    ros::Time time = ros::Time::now();
    std_msgs::Float64 msg;
    msg.data = 1;
    
    while (ros::ok()) {
        time = ros::Time::now();
        
        msg.data *= -1;
        servo1.publish(msg);
        servo2.publish(msg);
        
        cout << s.GetCurrentPosition() << "\n";
        
        ros::Duration(1).sleep();

        ros::spinOnce();
        loop_rate.sleep();
    }
}