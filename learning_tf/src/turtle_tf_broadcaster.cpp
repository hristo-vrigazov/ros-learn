#include <ros/ros.h>
#include "TurtleMover.h"


int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_mover");
    std::cout << "Creating turtle mover" << std::endl;
    ros::NodeHandle nodeHandle;
    TurtleMover turtleMover(nodeHandle, 1, 1.3);
    std::cout << "Running turtle mover" << std::endl;
    //turtleMover.run();
    ros::spin();
    return 0;

};


