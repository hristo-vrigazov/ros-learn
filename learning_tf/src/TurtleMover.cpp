//
// Created by dandree2 on 10.10.18.
//

//ros launch
//+ c++ default, delete operators and constructors
//+ use initializer lists,
//+ use member var or reference to nodehandle
//show two turtles
// move in an eight

#include <iostream>
#include <ros/ros.h>
#include "TurtleMover.h"
#include "geometry_msgs/Twist.h"



void TurtleMover::move(double distance) {
    std::cout << "Moving distance " << distance << std::endl;
    geometry_msgs::Twist twist;
    twist.linear.x = distance;
    twist.angular.z = -0.6;
    publisher.publish(twist);
}

void TurtleMover::timerCallback(const ros::TimerEvent & timerEvent) {
    move(distance);
}

TurtleMover::TurtleMover(ros::NodeHandle nodeHandle, int period, double distance) :
    distance(distance),
    nodeHandle(nodeHandle),
    publisher(nodeHandle.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1)),
    timer(nodeHandle.createTimer(ros::Duration(period), &TurtleMover::timerCallback, this)) {
}