#include <string>

#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

#include "dynamixel_msgs/MotorState.h"
#include "dynamixel_msgs/MotorStateList.h"
#include "dynamixel_msgs/JointState.h"

#define MOTOR_STATES_TOPIC "/motor_states/pan_tilt_port"
#define QUEUE_SIZE 1000

using namespace ros;
using namespace std;
using namespace dynamixel_msgs;

class Servo {
public:
    Servo(int id, NodeHandle *n);
    string publisherTopic() const;
    string subscriberTopic() const;
        
    int getId() const;
    float getGoalPosition() const;
    float getPosition() const;
    float getError() const;
    float getLoad() const;
    bool isMoving() const;
    
    void setPosition(float pos);
    
    //TODO
    float setSpeed() const;
    float setSpeed();
    
private:
    void UpdateState(const dynamixel_msgs::MotorStateList::ConstPtr& msg);
    
    int id;
    NodeHandle *nh;
    Publisher publisher;
    Subscriber subscriber;
    MotorState ms;
};
