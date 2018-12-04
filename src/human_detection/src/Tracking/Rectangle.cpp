#include <cmath>
#include <stdio.h>

#include "Rectangle.hpp"
#include "opencv2/video/tracking.hpp"

using namespace cv;

Rectangle::Rectangle(const Rect &rect, int id, int tick)
{
    this->tl = rect.tl();
    this->br = rect.br();
    this->id = id;

    this->seenTicks = 0;
    this->missedTicks = 0;
    this->lastSeenTick = tick;
    this->lastTick = tick;
}

void Rectangle::registerTick(int tick, bool seen)
{
    if (seen) {
        this->seenTicks++;
        this->lastSeenTick = tick;
    } else {
        this->missedTicks++;
    }

    this->lastTick = tick;
}

int Rectangle::accuracy()
{
    if (this->missedTicks < 5 && this->seenTicks < 5) {
        return 100;
    }

    return (int) ((float) (seenTicks - missedTicks) / (float) seenTicks * 100); 
}

int Rectangle::getDistance()
{
    return (300 - (this->br.y - this->tl.y)) * 2;
}

bool Rectangle::withinOffset(const Rect &rect)
{
    // Check if its an exact match
    if (this->tl == rect.tl() && this->br == rect.br()) 
    {
        return true;
    }

    int tlDiffInX = abs(this->tl.x - rect.tl().x);
    int tlDiffInY = abs(this->tl.y - rect.tl().y);

    int brDiffInX = abs(this->br.x - rect.br().x);
    int brDiffInY = abs(this->br.y - rect.br().y);

    if (
        tlDiffInX < ALLOWED_OFFSET && tlDiffInY < ALLOWED_OFFSET
        ||
        brDiffInX < ALLOWED_OFFSET && brDiffInY < ALLOWED_OFFSET    
    ) {
        return true;
    }
    
    return false;
}

void Rectangle::adjustPosition(const Rect &rect)
{
    this->tl.y = rect.tl().y;
    this->tl.x = rect.tl().x;
    this->br.x = rect.br().x;
    this->br.y = rect.br().y; 
}

int Rectangle::getLastTick()
{
    return this->lastTick;
}

int Rectangle::getId()
{
    return this->id;
}