#include <ros/ros.h>
#include "TurtleMover.h"


int main(int argc, char **argv) {
    ros::init(argc, argv, "turtle_mover");
    std::cout << "Creating turtle mover" << std::endl;
    TurtleMover turtleMover;
    std::cout << "Running turtle mover" << std::endl;
    turtleMover.run();
    return 0;

};


