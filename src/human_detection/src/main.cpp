#include <ros/ros.h>
#include <std_msgs/UInt32.h>
#include "OpenCVTracking.hpp"
#include "human_detection/Person.h"
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "human_dect");
    ros::NodeHandle n;
    ros::Publisher detectionTopic = n.advertise<human_detection::Person>("human_dect", 1);

    OpenCVTracking tracker("test-2-pers.mp4");

    cout << "starting \r\n";

    human_detection::Person tracked; 

    while(tracker.isValid() && ros::ok()) 
    {
        tracker.process();   

        vector<Rectangle*> rects = tracker.getTracker().getTrackedRectangles();

        for (vector<Rectangle*>::iterator it = rects.begin(); it != rects.end();) {
            Rectangle *rect = (*it);

            tracked.id = (uint32_t) rect->getId();
            tracked.distance = (uint32_t) rect->getDistance();
            tracked.accuracy = (uint32_t) rect->accuracy();

            detectionTopic.publish(tracked);

            it++;
        }

        ros::spinOnce();       
    }
}
