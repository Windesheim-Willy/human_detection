#ifndef HUMAN_DETECT_RECTANGLE_TRACKING
#define HUMAN_DETECT_RECTANGLE_TRACKING

#include <vector>
#include <stdio.h>

#include "opencv2/video/tracking.hpp"

using namespace cv;
using namespace std;

class RectangleTracker
{
public:
    RectangleTracker();

    void Tick();
    void Update(vector<Rect> &objects);

private:
    int ticks;
    vector<Rect> objects;
};

#endif