//
// Created by dandree2 on 10.10.18.
//

#ifndef LEARNING_TF_TURTLEMOVER_H
#define LEARNING_TF_TURTLEMOVER_H


#include <ros/timer.h>
#include <ros/publisher.h>
#include <iostream>
#include <ros/ros.h>
#include "geometry_msgs/Twist.h"
#include "turtlesim/Spawn.h"
#include "math.h"

class TurtleMover {
private:
    ros::Timer timer;
    ros::Publisher publisher;
    double distance;
    double period;

    ros::NodeHandle nodeHandle;

public:
	TurtleMover() = delete;
	TurtleMover(const TurtleMover &) = delete;
	TurtleMover(const TurtleMover &&) = delete;
	TurtleMover& operator=(TurtleMover&& other) = delete;
    TurtleMover& operator=(TurtleMover& other) = delete;

    TurtleMover(ros::NodeHandle nodeHandle);

    void move(double distance);

    void timerCallback(const ros::TimerEvent& timerEvent);

};


#endif //LEARNING_TF_TURTLEMOVER_H
