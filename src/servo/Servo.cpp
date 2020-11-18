#include "Servo.h"

Servo::Servo(int id, NodeHandle *n, string topicName, int queueSize) {
    this->id = id;
    publisher = n->advertise<std_msgs::Float64>("/" +  topicName + "/command", queueSize);
    subscriber = n->subscribe("/" +  topicName + "/state", queueSize, &Servo::UpdateState, this);
    nh = n;
}

void Servo::UpdateState(const dynamixel_msgs::JointState::ConstPtr& msg)
{
     goal_position = msg->goal_pos;
     current_position = msg->current_pos;
     error = msg->error;
     load = msg->load;
     moving = msg->is_moving;
}

float Servo::GetGoalPosition() {
    return goal_position;
}

float Servo::GetCurrentPosition() {
    return current_position;
}

float Servo::GetError() {
    return error;
}

float Servo::GetLoad() {
    return load;
}

bool Servo::IsMoving() {
    return moving;
}
