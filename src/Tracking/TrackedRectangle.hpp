#ifndef HUMAN_DETECT_TRACKED_RECTANGLE
#define HUMAN_DETECT_TRACKED_RECTANGLE

#include "opencv2/video/tracking.hpp"

class TrackedRectangle
{
    public:
        TrackedRectangle(Point tl, Point br);


        bool withinOffset(Point tl, Point br);
        void registerTick(int tick);

        Point tl;
        Point br;

    private:
        int lastSeenTick;
        int seenTicks;
};

#endif