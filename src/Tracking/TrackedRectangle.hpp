#ifndef HUMAN_DETECT_RECTANGLE_TRACKING
#define HUMAN_DETECT_RECTANGLE_TRACKING

class TrackedRectangle
{
    public:
        TrackedRectangle(int x, int y, int width, int height);

        void RegisterTick();
        bool Valid(int currentTick);

    private:
        int lastSeenTick;
        int seenTicks;

        int x, y, width, height;
};

#endif