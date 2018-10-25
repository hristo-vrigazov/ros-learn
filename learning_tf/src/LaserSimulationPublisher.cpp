//
// Created by dandree2 on 19.10.18.
//

#include "LaserSimulationPublisher.h"

void LaserSimulationPublisher::start() {

}

LaserSimulationPublisher::LaserSimulationPublisher(ros::NodeHandle &nodeHandle, std::string turtleId, std::string laserId)
        :
        turtleId(turtleId),
        laserId(laserId),
        nodeHandle(nodeHandle),
        poseSubscriber(nodeHandle.subscribe("/turtle" + turtleId + "/pose", 100, & LaserSimulationPublisher::poseCallback, this)),
        obstaclesSubscriber(nodeHandle.subscribe("/obstacles", 100, &LaserSimulationPublisher::obstaclesCallback, this)),
        laserScansPublisher(nodeHandle.advertise<sensor_msgs::LaserScan>("/laser_scans" + turtleId + laserId, 100)),
        angleMin(nodeHandle.param<float>("angle_min", -M_PI / 3)),
        angleMax(nodeHandle.param<float>("angle_max", M_PI / 3)),
        rangeMin(nodeHandle.param<float>("range_min", 0.01)),
        rangeMax(nodeHandle.param<float>("range_max", 6.0)), // half the field
        laserBeamCounts(640),
        angleIncrement(nodeHandle.param<float>("angle_increment", (angleMax - angleMin) / laserBeamCounts))
        {

}

void LaserSimulationPublisher::poseCallback(const turtlesim::PoseConstPtr &poseConstPtr) {
    this->pose = *poseConstPtr;
}

void LaserSimulationPublisher::obstaclesCallback(const sensor_msgs::PointCloudConstPtr &pointCloudConstPtr) {
    // probably better to hold it as field and just change the relevant stuff
    sensor_msgs::LaserScan laserScan;
    laserScan.angle_min = angleMin;
    laserScan.angle_max = angleMax;
    laserScan.range_min = rangeMin;
    laserScan.range_max = rangeMax;
    laserScan.angle_increment = angleIncrement;

    laserScan.header.frame_id = "/base_link" + turtleId + "_laser_" + laserId;
    laserScan.header.stamp = pointCloudConstPtr->header.stamp;

    sensor_msgs::PointCloud turtlePointCloud;
    try {
        tfTransformListener.waitForTransform("world", laserScan.header.frame_id, pointCloudConstPtr->header.stamp, ros::Duration(0.01));
        tfTransformListener.transformPointCloud(laserScan.header.frame_id, *pointCloudConstPtr, turtlePointCloud);
    } catch (tf::TransformException &ex) {
        ROS_WARN("Exception: %s", ex.what());
    }

    std::vector<geometry_msgs::Pose2D> polar2D = convertToPolar(turtlePointCloud);
    laserScan.ranges.resize(laserBeamCounts);
    laserScan.intensities.resize(laserBeamCounts);

    for (unsigned int i = 0; i < laserBeamCounts; i++) {
        if (i >= 0 && i < polar2D.size()) {
            geometry_msgs::Pose2D pose2D = polar2D.at(i);
            bool goesOutOfRange = pose2D.theta > angleMax || pose2D.theta < angleMin || pose2D.x > rangeMax || pose2D.x < rangeMin;
            bool goesOutOfWorld = pose2D.x > AXIS_END_VALUE || pose2D.x < 0;
            auto index = static_cast<unsigned int>((polar2D[i].theta - laserScan.angle_min) * (1/laserScan.angle_increment)) % laserBeamCounts;

            if (!goesOutOfRange && !goesOutOfWorld) {
                laserScan.ranges[index] = polar2D[i].x;
                laserScan.intensities[index] = polar2D[i].x;
            }
        }

    }

    this->laserScansPublisher.publish(laserScan);
}

LaserSimulationPublisher::~LaserSimulationPublisher() {

}


std::vector<geometry_msgs::Pose2D> convertToPolar(const sensor_msgs::PointCloud &pointCloudConstPtr) {
    std::vector<geometry_msgs::Pose2D> result;
    for (auto cloudPoint : pointCloudConstPtr.points) {
        geometry_msgs::Pose2D pose2D;
        pose2D.x = sqrt(cloudPoint.x * cloudPoint.x + cloudPoint.y * cloudPoint.y);
        pose2D.y = 0.;
        pose2D.theta = atan2(cloudPoint.y, cloudPoint.x);
        result.push_back(pose2D);
    }

    return result;
}
