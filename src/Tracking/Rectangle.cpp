#include <cmath>
#include <iostream>
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
}

void Rectangle::registerTick(int tick, bool seen)
{
    if (seen) {
        this->seenTicks++;
        this->lastSeenTick = tick;
    } else {
        this->missedTicks++;
    }
}

int Rectangle::accuracy()
{
    // std::cout << this->id << ": " << this->missedTicks << "-" << this->seenTicks << "\r\n";
    if (this->missedTicks < 2 && this->seenTicks < 2) {
        return 100;
    }

    if (this->missedTicks > this->seenTicks) {        
        return -1;
    }

    return (int) ((float) this->missedTicks / (float) this->seenTicks * 100);
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

int Rectangle::getLastSeenTick()
{
    return this->lastSeenTick;
}

int Rectangle::getId()
{
    return this->id;
}