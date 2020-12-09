#include "Joint.h"

#include <iostream>


Joint::Joint(const vector<int> &ids) {
    n = NodeHandle();

    for(int i : ids) {
        servos.insert(make_pair(i, Servo(i, &n)));
    }
    
}

