//
// Created by dandree2 on 18.10.18.
//

#ifndef LEARNING_TF_WALLPOINTCLOUDGENERATOR_H
#define LEARNING_TF_WALLPOINTCLOUDGENERATOR_H

#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>


class WallPointCloudGenerator {
private:
    ros::Timer timer;
    ros::Publisher publisher;
    ros::NodeHandle nodeHandle;

    sensor_msgs::PointCloud pointCloud;

    static const int AXIS_END_VALUE = 12;

public:
    // delete unneeded constructors and operators
    WallPointCloudGenerator() = delete;
    WallPointCloudGenerator(const WallPointCloudGenerator &) = delete;
    WallPointCloudGenerator(const WallPointCloudGenerator &&) = delete;
    WallPointCloudGenerator& operator=(WallPointCloudGenerator&& other) = delete;
    WallPointCloudGenerator& operator=(WallPointCloudGenerator& other) = delete;

    WallPointCloudGenerator(ros::NodeHandle & nodeHandle);

    void publishObstacles();

    void timerCallback(const ros::TimerEvent& timerEvent);

    // if x is true, then the x coordinate is fixed with value equal to i
    void createPoints(float fixedValue, bool x);
};


#endif //LEARNING_TF_WALLPOINTCLOUDGENERATOR_H
