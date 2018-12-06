#ifndef HUMAN_DETECT_OPENCVTRACKING
#define HUMAN_DETECT_OPENCVTRACKING

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/video/tracking.hpp"

#include "Tracking/Rectangle.hpp"
#include "Tracking/RectangleTracker.hpp"

using namespace cv;
using namespace std;

class OpenCVTracking 
{
    public: 
        OpenCVTracking(const string &filename);

        bool isValid();
        void process();

        RectangleTracker &getTracker();

    protected:
        void drawPerformance(Mat &image, float time);
        void drawRectange(Mat &image, Rectangle *rect);                

    private:
        VideoCapture *capture;
        CascadeClassifier detectBody;

        RectangleTracker bodyTracker;

        bool valid;
        char buffer[126];
};

#endif