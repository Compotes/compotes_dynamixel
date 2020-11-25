#include "Servo.h"
#include<iostream>


Servo::Servo(int id, NodeHandle *n) {
    this->id = id;
    this->nh = n;
    this->client = n->serviceClient<dynamixel_controllers::SetSpeed>(clientService());
    this->publisher = n->advertise<std_msgs::Float64>(publisherTopic(), QUEUE_SIZE);
    this->subscriber = n->subscribe(subscriberTopic(), QUEUE_SIZE, &Servo::UpdateState, this);
}

string Servo::subscriberTopic() const {
    return MOTOR_STATES_TOPIC;
}

string Servo::publisherTopic() const {
    return "/joint" + std::to_string(id) + "_controller/command";
}

string Servo::clientService() const {
    return "/joint" + std::to_string(id) + "_controller/set_speed";
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

void Servo::setSpeed(float speed) {
    dynamixel_controllers::SetSpeed data;
    data.request.speed = speed;
    client.call(data);
}

string Servo::to_string() const {
    string s = "[";
    s += " id : " + std::to_string(id);
    s += "; goal : " + std::to_string(ms.goal);
    s += "; pos : " + std::to_string(ms.position);
    s += "; speed : " + std::to_string(ms.speed);
    s += "]\n";
    return s;
}

