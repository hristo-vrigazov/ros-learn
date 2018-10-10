//
// Created by dandree2 on 10.10.18.
//

#ifndef LEARNING_TF_TURTLEMOVER_H
#define LEARNING_TF_TURTLEMOVER_H


#include <ros/timer.h>

class TurtleMover {
private:
    ros::Timer timer;


public:
    TurtleMover();

    void run();

    void move(double distance);

    void timerCallback(const ros::TimerEvent&);
};


#endif //LEARNING_TF_TURTLEMOVER_H
