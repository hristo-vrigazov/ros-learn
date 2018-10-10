//
// Created by dandree2 on 10.10.18.
//

#include <iostream>
#include <ros/ros.h>
#include "TurtleMover.h"
#include "geometry_msgs/Twist.h"

void TurtleMover::run() {
    std::cout << "Hello!" << std::endl;
}

TurtleMover::TurtleMover() {
    ros::NodeHandle nodeHandle;
}
