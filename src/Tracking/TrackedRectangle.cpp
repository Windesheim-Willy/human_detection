#include <cmath>

#include "TrackedRectangle.hpp"
#include "opencv2/video/tracking.hpp"

using namespace cv;

TrackedRectangle::TrackedRectangle(Point tl, Point br) 
{
    this->tl = tl;
    this->br = br;
    
    this->lastSeenTick = 0;
    this->seenTicks = 0;
}

void TrackedRectangle::registerTick(int tick)
{
    this->seenTicks++;
    this->lastSeenTick = tick;
}

bool TrackedRectangle::withinOffset(Point tl, Point br)
{
    // Check if its an exact match
    if (this->tl == tl && this->br == br) 
    {
        return true;
    }

    int diffInX = abs(this->tl.x - tl.x);
    int diffInY = abs(this->tl.y - tl.y);

    

    return false;
}