#ifndef JOINT_H
#define JOINT_H

#include "../servo/Servo.h"

#include <vector>
#include <map>

using namespace std;

class Joint {
public:
    Joint(const vector<int>&ids);
    bool inPosition();
            
    
private:
    NodeHandle n;
    map<int, Servo> servos;
    map<int, float> goal_positions;
    int id;
};

#endif