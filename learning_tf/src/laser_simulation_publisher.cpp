#include <ros/init.h>
#include "LaserSimulationPublisher.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "laser_simulation_publisher");

    if (argc != 2) {
        ROS_ERROR("Need turtle id as an argument.");
        return -1;
    }
    std::string turtleId = argv[1];
    ros::NodeHandle nodeHandle("~");
    LaserSimulationPublisher laserSimulationPublisher(nodeHandle, turtleId);
    laserSimulationPublisher.start();

    ros::spin();
    return 0;

}