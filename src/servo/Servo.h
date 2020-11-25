#include <string>

#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

#include "dynamixel_msgs/MotorState.h"
#include "dynamixel_msgs/MotorStateList.h"
#include "dynamixel_msgs/JointState.h"

#include "dynamixel_controllers/SetSpeed.h"

#define MOTOR_STATES_TOPIC "/motor_states/pan_tilt_port"
#define QUEUE_SIZE 1000

using namespace ros;
using namespace std;
using namespace dynamixel_msgs;

class Servo {
public:
    Servo(int id, NodeHandle *n);
    
    bool isMoving() const;    
    int getId() const;
    float getGoalPosition() const;
    float getPosition() const;
    float getError() const;
    float getLoad() const;
    float getSpeed() const;
    string to_string() const;

    void setSpeed(float speed);
    void setPosition(float pos);

private:
    void UpdateState(const dynamixel_msgs::MotorStateList::ConstPtr& msg);
    string publisherTopic() const;
    string subscriberTopic() const;
    string clientService() const;
    
    int id;
    NodeHandle *nh;
    ServiceClient client;
    Publisher publisher;
    Subscriber subscriber;
    MotorState ms;
};
