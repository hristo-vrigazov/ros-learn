//
// Created by dandree2 on 10.10.18.
//

// transformation for rviz - using tf
// subcribe for pose -> transform

#include "TurtleMover.h"

void TurtleMover::move(double distance) {
    std::cout << "Moving distance " << distance << std::endl;

    // TODO: play with this value for smoother/faster drawing
    int updateDegrees = 15;
    int totalUpdates = 100;
    double degrees = 0;

    for (int i = 0; i < totalUpdates; i++) {
        geometry_msgs::Twist twist;
        twist.linear.x = distance;
        twist.angular.z = sin(degrees * M_PI / 180.);
        publisher.publish(twist);
        degrees += (updateDegrees);
        ros::Duration((M_PI * 2.) / 10.).sleep();
        ROS_INFO("Iteration %d", i);
    }


}

void TurtleMover::timerCallback(const ros::TimerEvent & timerEvent) {
    move(distance);
}

TurtleMover::TurtleMover(ros::NodeHandle nodeHandle) :
    nodeHandle(nodeHandle),
    period(nodeHandle.param<double>("period", 1.)),
    distance(nodeHandle.param<double>("distance", 1.3)),
    publisher(nodeHandle.advertise<geometry_msgs::Twist>("/cmd_vel", 1)),
    timer(nodeHandle.createTimer(ros::Duration(period), &TurtleMover::timerCallback, this)) {
    ros::ServiceClient serviceClient;
    turtlesim::Spawn spawnRequest;
    ROS_INFO("Distance: %f",distance);
    ROS_INFO("Period: %f", period);
    serviceClient.call(spawnRequest);
}

