#include "Servo.h"
#include<iostream>


Servo::Servo(int id, NodeHandle *n) {
    this->id = id;
    this->nh = n;
    this->publisher = n->advertise<std_msgs::Float64>(publisherTopic(), QUEUE_SIZE);
    this->subscriber = n->subscribe(subscriberTopic(), QUEUE_SIZE, &Servo::UpdateState, this);
}

string Servo::subscriberTopic() const {
    return MOTOR_STATES_TOPIC;
}

string Servo::publisherTopic() const {
    return "/joint" + std::to_string(id) + "_controller/command";
}

void Servo::UpdateState(const dynamixel_msgs::MotorStateList::ConstPtr& msg) {
    ms = msg->motor_states[id-1];
}

int Servo::getId() const {
    return ms.id;
}

float Servo::getPosition() const {
    return ms.position;
}

float Servo::getGoalPosition() const {
    return ms.goal;
}

float Servo::getError() const {
    return ms.error;
}

float Servo::getLoad() const {
    return ms.load;
}

bool Servo::isMoving() const {
    return ms.moving;
}

void Servo::setPosition(float pos) { // position in radians
    std_msgs::Float64 msg;
    msg.data = pos;
    this->publisher.publish(msg);
}