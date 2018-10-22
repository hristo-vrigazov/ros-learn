//
// Created by dandree2 on 19.10.18.
//

#include "LaserSimulationPublisher.h"

void LaserSimulationPublisher::start() {

}

LaserSimulationPublisher::LaserSimulationPublisher(ros::NodeHandle &nodeHandle, std::string turtleId)
        :
        nodeHandle(nodeHandle),
        poseSubscriber(nodeHandle.subscribe("/turtle" + turtleId + "/pose", 100, & LaserSimulationPublisher::poseCallback, this)),
        obstaclesSubscriber(nodeHandle.subscribe("/obstacles", 100, &LaserSimulationPublisher::obstaclesCallback, this)),
        laserScansPublisher(nodeHandle.advertise<sensor_msgs::LaserScan>("/laser_scans", 100)),
        angleMin(nodeHandle.param<float>("angle_min", -M_PI/2)),
        angleMax(nodeHandle.param<float>("angle_max", M_PI/2)),
        rangeMin(nodeHandle.param<float>("range_min", 0.5)),
        rangeMax(nodeHandle.param<float>("range_max", 6.0)), // half the field
        angleIncrement(nodeHandle.param<float>("angle_increment", M_PI/64)),
        scanTime(nodeHandle.param<float>("scan_time", 0.5)),
        laserBeamCounts((unsigned int)((angleMax - angleMin) / angleIncrement))
        {
    ROS_ERROR(("/turtle" + turtleId + "/pose").c_str());
}

void LaserSimulationPublisher::poseCallback(const turtlesim::PoseConstPtr &poseConstPtr) {
    ROS_ERROR("Pose callback");
    this->pose = *poseConstPtr;
}

void LaserSimulationPublisher::obstaclesCallback(const sensor_msgs::PointCloudConstPtr &pointCloudConstPtr) {
    ROS_ERROR("Obstacles callback");

    std::vector<geometry_msgs::Pose2D> points2d = convertToPolar(pointCloudConstPtr);

    // probably better to hold it as field and just change the relevant stuff
    sensor_msgs::LaserScan laserScan;
    laserScan.angle_min = angleMin;
    laserScan.angle_max = angleMax;
    laserScan.range_min = rangeMin;
    laserScan.range_max = rangeMax;
    laserScan.angle_increment = angleIncrement;
    laserScan.scan_time = scanTime;

    laserScan.header.frame_id = "/base_link1_laser";
    laserScan.header.stamp = pointCloudConstPtr->header.stamp;

    for (unsigned int i = 0; i < laserBeamCounts; i++) {
        geometry_msgs::Pose2D pose2D = points2d.at(i);
//        bool goesOutOfRange = pose2D.theta > angleMax || pose2D.theta < angleMin || pose2D.x > rangeMax || pose2D.x < rangeMin;
//        if (!goesOutOfRange) {
//
//        }

        laserScan.ranges.push_back(points2d.at(i).x);
        laserScan.intensities.push_back(points2d.at(i).x);

    }

    this->laserScansPublisher.publish(laserScan);
}

LaserSimulationPublisher::~LaserSimulationPublisher() {

}


std::vector<geometry_msgs::Pose2D> convertToPolar(const sensor_msgs::PointCloudConstPtr &pointCloudConstPtr) {
    std::vector<geometry_msgs::Pose2D> result;
    for (auto cloudPoint : pointCloudConstPtr->points) {
        geometry_msgs::Pose2D pose2D;
        pose2D.x = sqrt(cloudPoint.x * cloudPoint.x + cloudPoint.y * cloudPoint.y);
        pose2D.y = 0;
        pose2D.theta = atan2(cloudPoint.y, cloudPoint.x);
        result.push_back(pose2D);
    }

    return result;
}
