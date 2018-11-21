#ifndef HUMAN_DETECT_RECTANGLE_TRACKING
#define HUMAN_DETECT_RECTANGLE_TRACKING

#include <vector>
#include <stdio.h>

#include "opencv2/video/tracking.hpp"
#include "TrackedRectangle.hpp"

using namespace cv;
using namespace std;

class RectangleTracker
{
public:
    RectangleTracker();

    void tick();
    void update(vector<Rect> &foundRectangles);

    vector<TrackedRectangle> *getTrackedRectangles();

private:
    int ticks;
    vector<TrackedRectangle> *trackedRectangles;
};

#endif