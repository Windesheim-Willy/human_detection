#include "RectangleTracker.hpp"

RectangleTracker::RectangleTracker()
{
    this->ticks = 0;
}

void RectangleTracker::tick()
{
    this->ticks++;

    this->trackedRectangles = new vector<TrackedRectangle>();
}

void RectangleTracker::update(vector<Rect> &foundRectangles)
{
    for (int f = 0; f < foundRectangles.size(); f++) {


        

    }
}

vector<TrackedRectangle>* RectangleTracker::getTrackedRectangles()
{
    return this->trackedRectangles;
}