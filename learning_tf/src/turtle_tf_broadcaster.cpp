#include <ros/ros.h>
#include "TurtleMover.h"


int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_mover");
    if (argc != 2) {
        ROS_ERROR("need turtle name as argument");
        return -1;
    }

    std::string turtle_name;
    turtle_name = argv[1];
    std::cout << "Creating turtle mover" << std::endl;
    ros::NodeHandle nodeHandle("~");
    TurtleMover turtleMover(nodeHandle, turtle_name);
    std::cout << "Running turtle mover" << std::endl;
    ros::spin();
    return 0;

};


