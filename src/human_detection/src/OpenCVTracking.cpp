#include "main.h"
#include "OpenCVTracking.hpp"

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/video/tracking.hpp"

#include "Tracking/Rectangle.hpp"
#include "Tracking/RectangleTracker.hpp"

using namespace cv;
using namespace std;

OpenCVTracking::OpenCVTracking(const string &video, const string &cascade)
{
    this->capture = new VideoCapture(video);
    valid = detectBody.load(cascade);
}

bool OpenCVTracking::isValidCascade()
{
    return this->valid;
}

bool OpenCVTracking::isValidVideo()
{
    return capture->grab();
}

void OpenCVTracking::process()
{
    vector<Rect> humans;

    // matrix containers
    Mat img;
    Mat original;

    // Just for measure time
    const clock_t begin_time = clock();

    valid = capture->grab();

    if (valid)
    {
        // capture frame from video stream
        capture->retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);

        // Resize to gain some performance
        resize(img, img, Size(640, 480));
        img.copyTo(original);

        // color to gray image
        cvtColor(img, img, CV_BGR2GRAY);

        // size (w, h)
        detectBody.detectMultiScale(
            img, 
            humans, 
            1.1, 
            3, 
            CASCADE_DO_CANNY_PRUNING,                       
            // min
            Size(70, 70),    
            // max
            Size(400, 350)
        );

        bodyTracker.update(humans);
        
        for (int f = 0; f < bodyTracker.getTrackedRectangles().size(); f++) {
            Rectangle *rect = bodyTracker.getTrackedRectangles().at(f);

            if (DEBUG) {
                this->drawRectange(original, rect);
            }
        }

        if (DEBUG) {
            this->drawPerformance(original, begin_time);
        }
    }
}

void OpenCVTracking::drawPerformance(Mat &image, float begin_time)
{
    // measure time as current - begin_time
    clock_t diff = clock() - begin_time;

    // convert time into string
    sprintf(buffer, "time %.4fs", ((float) diff) / CLOCKS_PER_SEC);
    putText(image, buffer, Point(400, 25), 1, 2, Scalar(255, 255, 255), 2, 8, 0);

    sprintf(buffer, "Humans: %i (%i)", (int) bodyTracker.getTrackedRectangles().size(), bodyTracker.getDetectedCount());
    putText(image, buffer, Point(10, 25), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
    
    // draw results
    namedWindow("prev", WINDOW_AUTOSIZE);
    imshow("prev", image);

    int key1 = waitKey(1);
}

void OpenCVTracking::drawRectange(Mat &image, Rectangle *rect) 
{
    rectangle(
        image, 
        rect->tl, 
        rect->br, 
        Scalar(0,0,255), 
        2, 8, 0
    );

    // ID
    sprintf(buffer, "id: %i", rect->getId());
    putText(image, buffer, Point(rect->tl.x, rect->tl.y + 20), 1, 2, Scalar(85, 150, 85), 2, 2, 0);

    // Height, width
    sprintf(
        buffer,
        "h:%d w:%d",
        rect->br.y - rect->tl.y,
        rect->br.x - rect->tl.x
    );
    putText(image, buffer, Point(rect->tl.x, rect->tl.y + 50), 1, 2, Scalar(85, 150, 85), 2, 2, 0);

    // Accuracy
    sprintf(buffer, "%i", rect->accuracy());
    putText(image, buffer, Point(rect->tl.x, rect->tl.y + 80), 1, 2, Scalar(85, 150, 85), 2, 2, 0);

    // Distance
    sprintf(buffer, "%i cm", rect->getDistance());
    putText(image, buffer, Point(rect->tl.x, rect->tl.y + 110), 1, 2, Scalar(85, 150, 85), 2, 2, 0);
}

RectangleTracker &OpenCVTracking::getTracker()
{
    return this->bodyTracker;
}