#include <utility>

//
// Created by dandree2 on 10.10.18.
//

// fix walls
// add laser on the turtle
// publish static transform for the laser

#include "TurtleMover.h"

void TurtleMover::move(double distance) {
    std::cout << "Moving distance " << distance << std::endl;

    // TODO: play with this value for smoother/faster drawing
    geometry_msgs::Twist twist;
    twist.linear.x = distance;
    twist.angular.z = sin(degrees * M_PI / 180.);
    publisher.publish(twist);
    degrees += (updateDegrees);
    ROS_INFO("Iteration");
}

void TurtleMover::timerCallback(const ros::TimerEvent & timerEvent) {
    move(distance);
}

TurtleMover::TurtleMover(ros::NodeHandle & nodeHandle, std::string turtleName, std::string baseLinkPostfix) :
    nodeHandle(nodeHandle),
    period(nodeHandle.param<double>("period", 1.)),
    distance(nodeHandle.param<double>("distance", 1.3)),
    publisher(nodeHandle.advertise<geometry_msgs::Twist>(turtleName + "/cmd_vel", 1000)),
    timer(nodeHandle.createTimer(ros::Duration(2 * M_PI / 10), &TurtleMover::timerCallback, this)),
    turtleName(turtleName),
    baseLinkPostfix(baseLinkPostfix),
    subscriber(nodeHandle.subscribe(turtleName + "/pose", 1000, &TurtleMover::tfPoseCallback, this)) {
    ROS_INFO("Distance: %f",distance);
    ROS_INFO("Period: %f", period);
}

void TurtleMover::tfPoseCallback(const turtlesim::PoseConstPtr &pose) {
    ROS_INFO("Pose callback");
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(pose->x, pose->y, 0.0) );
    tf::Quaternion q;
    q.setRPY(0, 0, pose->theta);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "base_link" + baseLinkPostfix));
}
