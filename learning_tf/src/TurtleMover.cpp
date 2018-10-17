//
// Created by dandree2 on 10.10.18.
//

// publish pose from current turtle to another topic
// publish point cloud
// investigate why topics are not shown in RVIZ
// + fix the eight

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

TurtleMover::TurtleMover(ros::NodeHandle & nodeHandle, std::string turtleName) :
    nodeHandle(nodeHandle),
    period(nodeHandle.param<double>("period", 1.)),
    distance(nodeHandle.param<double>("distance", 1.3)),
    publisher(nodeHandle.advertise<geometry_msgs::Twist>(turtleName + "/cmd_vel", 1000)),
    timer(nodeHandle.createTimer(ros::Duration(2 * M_PI / 10), &TurtleMover::timerCallback, this)),
    turtleName(turtleName),
    subscriber(nodeHandle.subscribe(turtleName + "/pose", 1000, &TurtleMover::poseCallback, this)) {
    ROS_INFO("Distance: %f",distance);
    ROS_INFO("Period: %f", period);
}

void TurtleMover::poseCallback(const turtlesim::PoseConstPtr &pose) {
    ROS_INFO("Pose callback");
    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin(tf::Vector3(pose->x, pose->y, 0.0) );
    tf::Quaternion q;
    q.setRPY(0, 0, pose->theta);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "base_link"));
}

