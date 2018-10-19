//
// Created by dandree2 on 18.10.18.
//

#include "WallPointCloudGenerator.h"

WallPointCloudGenerator::WallPointCloudGenerator(ros::NodeHandle &nodeHandle) :
    nodeHandle(nodeHandle),
    publisher(nodeHandle.advertise<sensor_msgs::PointCloud>("/obstacles", 1)),
    timer(nodeHandle.createTimer(ros::Duration(1), &WallPointCloudGenerator::timerCallback, this)) {

    pointCloud.header.frame_id = "world";

    //TODO: generate boundaries
    createPoints(-AXIS_END_VALUE, true);
    createPoints(AXIS_END_VALUE, true);
    createPoints(-AXIS_END_VALUE, false);
    createPoints(AXIS_END_VALUE, false);

}

void WallPointCloudGenerator::createPoints(int i, bool x) {
    for (float j = -AXIS_END_VALUE; j <= AXIS_END_VALUE; j += 0.1) {
        geometry_msgs::Point32 point;
        point.x = x ? i : j;
        point.y = x ? j : i;
        point.z = 0;
        pointCloud.points.push_back(point);
    }
}


void WallPointCloudGenerator::publishObstacles() {
    publisher.publish(pointCloud);
}

void WallPointCloudGenerator::timerCallback(const ros::TimerEvent &timerEvent) {
    publishObstacles();
}
