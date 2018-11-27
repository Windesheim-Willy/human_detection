#include <cmath>
#include <iostream>
#include <stdio.h>

#include "Rectangle.hpp"
#include "opencv2/video/tracking.hpp"

using namespace cv;

Rectangle::Rectangle(const Rect &rect, int id)
{
    this->tl = rect.tl();
    this->br = rect.br();
    this->id = id;
}

void Rectangle::registerTick(int tick, bool seen)
{
    this->lastTick = tick;

    if (firstTick == 0) {
        firstTick = tick;
    }

    if (seen) {
        this->seenTicks++;
    } else {
        this->missedTicks++;
    }
}

int Rectangle::accuracy()
{
    int x= (int) this->missedTicks / this->seenTicks;

    std::cout << this->id << this->seenTicks << "|" << this->missedTicks << "=" << x << "\r\n";
    return x; 
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
        && 
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
    return this->lastTick;
}

int Rectangle::getId()
{
    return this->id;
}