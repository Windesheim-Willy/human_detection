#include <unistd.h>
#include "OpenCVTracking.hpp"

int main(int argc, const char** argv)
{
    OpenCVTracking tracker("test-2-pers.mp4");

    while(tracker.isValid()) 
    {
        tracker.process();      

        usleep(5000);
        
    }
}
