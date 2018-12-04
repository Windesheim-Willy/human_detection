#include <ros/ros.h>
#include <std_msgs/String.h>
#include "OpenCVTracking.hpp"
#include "human_detection/Person.h"

using namespace human_detection;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "human_dect");
    ros::NodeHandle n;

    ros::Publisher chatter_pub = n.advertise<Person>("chatter", 1000);

    OpenCVTracking tracker("test-2-pers.mp4");

    while(tracker.isValid() && ros::ok()) 
    {
        tracker.process();   

        std_msgs::String msg;

        msg.data = "hoi";
        chatter_pub.publish(msg);

        ros::spinOnce();       
    }
}
