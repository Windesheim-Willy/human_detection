#include "RectangleTracker.hpp"

RectangleTracker::RectangleTracker()
{
    this->ticks = 0;
}

void RectangleTracker::Tick()
{
    this->ticks++;
}

void RectangleTracker::Update(vector<Rect> &objects)
{
    for (int i = 0; i < objects.size(); i++) {

    }
}