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

#include "sensor_msgs/PointCloud.h"

class TurtleMover {
private:
    ros::Timer timer;
    ros::Publisher publisher;
    double distance;
    double period;

    ros::NodeHandle nodeHandle;
    ros::Subscriber subscriber;

    ros::Subscriber poseSubscriber;
    ros::Publisher posePublisher;

    ros::Publisher pointCloudPublisher;

    std::string turtleName;
	std::string baseLinkPostfix;

    int updateDegrees = 15;
    double degrees = 0;

    tf::TransformBroadcaster br;

public:
	TurtleMover() = delete;
	TurtleMover(const TurtleMover &) = delete;
	TurtleMover(const TurtleMover &&) = delete;
	TurtleMover& operator=(TurtleMover&& other) = delete;
    TurtleMover& operator=(TurtleMover& other) = delete;

    TurtleMover(ros::NodeHandle & nodeHandle, std::string turtleName, std::string baseLinkPostfix);

    void move(double distance);

    void timerCallback(const ros::TimerEvent& timerEvent);

    void tfPoseCallback(const turtlesim::PoseConstPtr &pose);

    void poseCallback(const turtlesim::PoseConstPtr &pose);

};


#endif //LEARNING_TF_TURTLEMOVER_H
