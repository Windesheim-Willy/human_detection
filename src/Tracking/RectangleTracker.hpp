#ifndef HUMAN_DETECT_RECTANGLE_TRACKING
#define HUMAN_DETECT_RECTANGLE_TRACKING

#include <vector>
#include <stdio.h>

#include "opencv2/video/tracking.hpp"
#include "Rectangle.hpp"

using namespace cv;
using namespace std;

class RectangleTracker
{
public:
    RectangleTracker();
    
    void update(vector<Rect> &foundRectangles);
    int getDetectedCount();

    vector<Rectangle*> &getTrackedRectangles();

private:
    int ticks;
    int detectedCount;
    vector<Rectangle*> trackedRectangles;
};

#endif