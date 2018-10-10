//
// Created by dandree2 on 10.10.18.
//

#include <iostream>
#include <ros/ros.h>
#include "TurtleMover.h"
#include "geometry_msgs/Twist.h"

void TurtleMover::run() {
    ros::spin();
}

TurtleMover::TurtleMover(int period, double distance) : distance(distance) {
    ros::NodeHandle nodeHandle("turtle_mover");
    this->publisher = nodeHandle.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);
    this->timer = nodeHandle.createTimer(ros::Duration(period), & TurtleMover::timerCallback, this);
}

void TurtleMover::move(double distance) {
    std::cout << "Moving distance " << distance << std::endl;
    geometry_msgs::Twist twist;
    twist.linear.x = distance;
    twist.angular.z = -3.14;
    publisher.publish(twist);
}

void TurtleMover::timerCallback(const ros::TimerEvent & timerEvent) {
    move(distance);
}
