#include <string>

#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/String.h"

#include "dynamixel_msgs/MotorState.h"
#include "dynamixel_msgs/JointState.h"


using namespace ros;
using namespace std;


class Servo {
public:
    Servo(int id, NodeHandle *n, string topicName, int queueSize=1000);
    
    float GetGoalPosition();
    float GetCurrentPosition();
    float GetError();
    float GetLoad();
    bool IsMoving();
    
    //TODO
    float GetSpeed();
    float SetSpeed();
private:
    void UpdateState(const dynamixel_msgs::JointState::ConstPtr& msg);
    
    NodeHandle *nh;
    Publisher publisher;
    Subscriber subscriber;
    int id;
    
    float goal_position;
    float current_position;
    float error;
    float load;
    bool moving;
};
