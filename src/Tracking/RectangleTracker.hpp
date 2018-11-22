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

    vector<Rectangle*> &getTrackedRectangles();

private:
    int ticks;
    vector<Rectangle*> trackedRectangles;
};

#endif