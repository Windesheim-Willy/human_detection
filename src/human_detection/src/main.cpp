#include "main.h"
#include <ros/ros.h>
#include <iostream>
#include <std_msgs/String.h>
#include "OpenCVTracking.hpp"

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "human_dect");
    ros::NodeHandle n;
    ros::Publisher detectionTopic = n.advertise<std_msgs::String>("human_dect", 1);

    OpenCVTracking tracker("/dev/video1");
    std_msgs::String tracked;

    if (!tracker.isValid()) {
        cout << "could not read capture device, does /dev/video1 exist and is it readable?" << endl;
    }

    if (!ros::ok()) {
        cout << "ros is not ok, did you start the roscore?" << endl;
    }

    while(tracker.isValid() && ros::ok()) 
    {
        tracker.process();   

        vector<Rectangle*> rects = tracker.getTracker().getTrackedRectangles();

        for (vector<Rectangle*>::iterator it = rects.begin(); it != rects.end();) {
            Rectangle *rect = (*it);

            std::stringstream concatString;
            concatString << rect->getId() << "," << rect->accuracy() << "," << rect->getDistance();
            tracked.data = concatString.str();

            detectionTopic.publish(tracked);

            it++;
        }

        ros::spinOnce();       
    }
}
