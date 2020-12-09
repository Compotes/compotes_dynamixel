#include <iostream>
#include <thread>
#include <unistd.h>


#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

#include "dynamixel_msgs/MotorState.h"
#include "dynamixel_msgs/JointState.h"

#include "servo/Servo.h"
#include "joint/Joint.h"


ros::Publisher servo1;
ros::Publisher servo2;
ros::Publisher servo3;
ros::Subscriber sub;

void print_status(Servo* s) {
    while(1) {
        cout << s->getPosition() << endl;
        //cout << s->to_string();
        usleep(100000);
    }
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "init");
    ros::NodeHandle n;

    Servo s1 = Servo(1, &n);
    Servo s2 = Servo(2, &n);
    Servo s3 = Servo(3, &n);



    ros::Rate loop_rate(50);
    //std::thread t1(print_status, &s1);

    //std_msgs::Float64 msg;
   // msg.data += 1;
    //cout << s.publisherTopic() << "\n" << s.subscriberTopic() << "\n";
    s1.setSpeed(0.5);
    s2.setSpeed(1);
    s3.setSpeed(2);
    s1.setPosition(-3.14);
    s2.setPosition(-3.14);
    s3.setPosition(-3.14);
    float angle = 5;
    while (ros::ok()) {        

        if (angle > -1) angle = -3.14;
        else angle = 3.14;
//        cout << s1.to_string();
      
        s1.setPosition(angle);
        s2.setPosition(angle);
        s3.setPosition(angle);
        
        ros::Duration(1).sleep();
        ros::spinOnce();
        loop_rate.sleep();
    }
}
