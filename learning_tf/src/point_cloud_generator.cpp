//
// Created by dandree2 on 18.10.18.
//

#include <ros/init.h>
#include "WallPointCloudGenerator.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "point_cloud_generator");
    ros::NodeHandle nodeHandle("~");

    WallPointCloudGenerator wallPointCloudGenerator(nodeHandle);

    wallPointCloudGenerator.publishObstacles();

    ros::spin();
    return 0;
}
