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
#include <turtlesim/Pose.h>
#include <tf/transform_broadcaster.h>


class TurtleMover {
private:
    ros::Timer timer;
    ros::Publisher publisher;
    double distance;
    double period;

    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber;

    std::string turtleName;

    int updateDegrees = 15;
    int totalUpdates = 100;
    double degrees = 0;

public:
	TurtleMover() = delete;
	TurtleMover(const TurtleMover &) = delete;
	TurtleMover(const TurtleMover &&) = delete;
	TurtleMover& operator=(TurtleMover&& other) = delete;
    TurtleMover& operator=(TurtleMover& other) = delete;

    TurtleMover(ros::NodeHandle & nodeHandle, std::string turtleName);

    void move(double distance);

    void timerCallback(const ros::TimerEvent& timerEvent);

    void poseCallback(const turtlesim::PoseConstPtr& pose);

};


#endif //LEARNING_TF_TURTLEMOVER_H
