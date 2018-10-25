#include <ros/init.h>
#include "LaserSimulationPublisher.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "laser_simulation_publisher");

    if (argc != 3) {
        ROS_ERROR("Need turtle id and laser id as an argument.");
        return -1;
    }
    std::string turtleId = argv[1];
    std::string laserId = argv[2];
    ros::NodeHandle nodeHandle("~");
    LaserSimulationPublisher laserSimulationPublisher(nodeHandle, turtleId, laserId);
    laserSimulationPublisher.start();

    ros::spin();
    return 0;

}