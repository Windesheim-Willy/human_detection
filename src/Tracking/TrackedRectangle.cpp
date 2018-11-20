#include "TrackedRectangle.hpp"

TrackedRectangle::TrackedRectangle(int x, int y, int width, int height) 
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    this->lastSeenTick = 0;
    this->seenTicks = 0;
}

void TrackedRectangle::RegisterTick(int tick)
{
    this->seenTicks++;
    this->lastSeenTick = tick;
}