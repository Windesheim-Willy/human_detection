#include "RectangleTracker.hpp"
#include <iostream>

RectangleTracker::RectangleTracker()
{
    this->ticks = 0;
}

void RectangleTracker::update(vector<Rect> &foundRectangles)
{
    this->ticks++;

    // This is easy
    if (foundRectangles.size() == 0 && trackedRectangles.size() == 0) {
        return;
    }

    // Empty set but one rectangle
    if (this->trackedRectangles.size() == 0 && foundRectangles.size() == 1) {
        Rectangle *rect = new Rectangle(foundRectangles[0], ++this->detectedCount);
        this->trackedRectangles.push_back(rect);
        return;
    }

    // Link and update positions
    bool seen;

    for (int f = 0; f < foundRectangles.size(); f++) {

        seen = false;

        for (int t = 0; t < this->trackedRectangles.size(); t++) {

            if (this->trackedRectangles[t]->withinOffset(foundRectangles[f])) {
                this->trackedRectangles[t]->adjustPosition(foundRectangles[f]);
                this->trackedRectangles[t]->registerTick(this->ticks, true);

                seen = true;

                // Stop this loop
                break;
            }
        }

        if (seen == false) {
            Rectangle *rect = new Rectangle(foundRectangles[f], ++this->detectedCount);
            this->trackedRectangles.push_back(rect);
        }
    }

    for (int t = 0; t < this->trackedRectangles.size(); t++) {
        if (this->trackedRectangles[t]->getLastSeenTick() != ticks) {
            this->trackedRectangles[t]->registerTick(ticks, false);
        }
    }

    for (vector<Rectangle*>::iterator it = trackedRectangles.begin(); it != trackedRectangles.end();) {
        if (ticks - (*it)->getLastSeenTick() > 10) {
            Rectangle * toDelete = (*it);
            trackedRectangles.erase(it);

            // Lets save some memory for those in need :-)
            delete toDelete;
        } else {
            ++it;
        }
    }
}

vector<Rectangle*> &RectangleTracker::getTrackedRectangles()
{
    return this->trackedRectangles;
}

int RectangleTracker::getDetectedCount()
{
    return this->detectedCount;
}