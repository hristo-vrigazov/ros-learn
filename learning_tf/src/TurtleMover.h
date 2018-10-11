//
// Created by dandree2 on 10.10.18.
//

#ifndef LEARNING_TF_TURTLEMOVER_H
#define LEARNING_TF_TURTLEMOVER_H


#include <ros/timer.h>
#include <ros/publisher.h>

class TurtleMover {
private:
    ros::Timer timer;
    ros::Publisher publisher;
    double distance;

    ros::NodeHandle nodeHandle;

public:
	TurtleMover() = delete;
	//copy const
	//move const 
	//move operator
	//assignment operator 
    TurtleMover(int period = 1, double distance = 1.3);

    void run();

    void move(double distance);

    void timerCallback(const ros::TimerEvent& timerEvent);
};


#endif //LEARNING_TF_TURTLEMOVER_H
