#include <ros/ros.h>
#include "TurtleMover.h"


int main(int argc, char **argv) {

    std::cout << "Running turtle mover" << std::endl;
    TurtleMover turtleMover;
    turtleMover.run();

    return 0;

};


