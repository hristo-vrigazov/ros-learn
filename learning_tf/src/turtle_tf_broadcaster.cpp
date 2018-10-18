#include <ros/ros.h>
#include "TurtleMover.h"


int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_mover");
    if (argc != 3) {
        ROS_ERROR("Need turtle name as argument and ");
        return -1;
    }

    std::string turtle_name;
    turtle_name = argv[1];
    std::cout << "Creating turtle mover" << std::endl;

    std::string base_link_postfix = argv[2];

    ros::NodeHandle nodeHandle("~");
    TurtleMover turtleMover(nodeHandle, turtle_name, base_link_postfix);
    std::cout << "Running turtle mover" << std::endl;
    ros::spin();
    return 0;

};


