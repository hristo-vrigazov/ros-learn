//
// Created by dandree2 on 19.10.18.
//

#ifndef LEARNING_TF_LASERSIMULATIONPUBLISHER_H
#define LEARNING_TF_LASERSIMULATIONPUBLISHER_H

#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include "geometry_msgs/Pose2D.h"
#include <sensor_msgs/PointCloud.h>
#include "sensor_msgs/LaserScan.h"
#include "math.h"
#include "tf/transform_listener.h"

// + separate laser scans
// + multiple laser scans for a turtle - behind one (set yaw e.g.)


std::vector<geometry_msgs::Pose2D> convertToPolar(const sensor_msgs::PointCloud &pointCloudConstPtr);

class LaserSimulationPublisher {
private:
    std::string turtleId;
    std::string laserId;

    ros::NodeHandle nodeHandle;
    ros::Subscriber poseSubscriber;
    ros::Subscriber obstaclesSubscriber;
    ros::Publisher laserScansPublisher;

    unsigned int laserBeamCounts;

    float angleMin;
    float angleMax;
    float rangeMin;
    float rangeMax;
    float angleIncrement;

    float scanTime;

    turtlesim::Pose pose;
    tf::TransformListener tfTransformListener;

    static const int AXIS_END_VALUE = 12;

public:
    LaserSimulationPublisher() = delete;
    LaserSimulationPublisher(const LaserSimulationPublisher &) = delete;
    LaserSimulationPublisher(const LaserSimulationPublisher &&) = delete;
    LaserSimulationPublisher& operator=(LaserSimulationPublisher&& other) = delete;
    LaserSimulationPublisher& operator=(LaserSimulationPublisher& other) = delete;

    LaserSimulationPublisher(ros::NodeHandle &nodeHandle, std::string turtleId, std::string laserId);

    void start();

    void poseCallback(const turtlesim::PoseConstPtr &poseConstPtr);

    void obstaclesCallback(const sensor_msgs::PointCloudConstPtr &pointCloudConstPtr);

    ~LaserSimulationPublisher();
};



#endif //LEARNING_TF_LASERSIMULATIONPUBLISHER_H
