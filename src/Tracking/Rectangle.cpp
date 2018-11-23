#include <cmath>

#include "Rectangle.hpp"
#include "opencv2/video/tracking.hpp"

using namespace cv;

Rectangle::Rectangle(const Rect &rect)
{
    this->tl = rect.tl();
    this->br = rect.br();
}

void Rectangle::registerTick(int tick)
{
    this->seenTicks++;
    this->lastTick = tick;

    if (firstTick == 0) {
        firstTick = tick;
    }
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
    // this->tl.y = this->tl.y + ((this->tl.y - rect.tl().y) / 2);
    // this->tl.x = this->tl.x + ((this->tl.x - rect.tl().x) / 2);
    // this->br.x = this->br.x + ((this->br.x - rect.br().x) / 2);
    // this->br.y = this->br.y + ((this->br.y - rect.br().y) / 2); 

    this->tl.y = rect.tl().y;
    this->tl.x = rect.tl().x;
    this->br.x = rect.br().x;
    this->br.y = rect.br().y; 
}

int Rectangle::getLastSeenTick()
{
    return this->lastTick;
}