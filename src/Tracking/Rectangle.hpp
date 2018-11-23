#ifndef HUMAN_DETECT_RECTANGLE
#define HUMAN_DETECT_RECTANGLE

#define ALLOWED_OFFSET 50

#include "opencv2/video/tracking.hpp"

using namespace cv;

class Rectangle
{
    public:
        Rectangle(const Rect &rect);
        ~Rectangle();

        int getLastSeenTick();

        bool withinOffset(const Rect &rect);
        void adjustPosition(const Rect &rect);

        void registerTick(int tick);

        Point tl;
        Point br;

    private:
        Rect *rect;
        int lastTick, firstTick, seenTicks;
};

#endif