#include <vector>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <ctime>

#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/video/tracking.hpp"

#include "Tracking/RectangleTracker.hpp"

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
        // prepare video input
        VideoCapture cap("test-3-pers.mp4");

        CascadeClassifier detectBody;
        string cascade = "opencv/haar-upper-body.xml";

        // Load cascade into CascadeClassifier
        bool cascadeLoaded = detectBody.load(cascade);

        if (cascadeLoaded == false) {
                cout << "failed to load body detection";
                return -1;
        }

        // vars used in for
        char buffer[126];
        RectangleTracker tracker;
        vector<Rect> humans;

        // Basic video input loop
        for (;;)
        {
                bool Is = cap.grab();
                if (Is == false) 
                {
                        cout << "Video Capture Fail" << endl;
                        break;
                } else {
                        // Just for measure time
                        const clock_t begin_time = clock();

                        // prepare 2 Mat container
                        Mat img;
                        Mat original;

                        // capture frame from video stream
                        cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);
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
                                Size(70, 70),    // min
                                Size(640, 480)  // max
                        );

                        tracker.update(humans);
                       
                        for (int f = 0; f < tracker.getTrackedRectangles().size(); f++) {
                                Rectangle *rect = tracker.getTrackedRectangles().at(f);

                                rectangle(
                                        original, 
                                        rect->tl, 
                                        rect->br, 
                                        Scalar(0,0,255), 
                                        2, 8, 0
                                );

                                sprintf(buffer, "id: %d", rect->getId());
                                putText(original, buffer, Point(rect->tl.x, rect->tl.y + 20), 1, 2, Scalar(85, 150, 85), 2, 2, 0);

                                sprintf(
                                        buffer,
                                        "h:%d w:%d",
                                        rect->br.y - rect->tl.y,
                                        rect->br.x - rect->tl.x
                                );
                                putText(original, buffer, Point(rect->tl.x, rect->tl.y + 50), 1, 2, Scalar(85, 150, 85), 2, 2, 0);

                                sprintf(buffer, "%i", rect->accuracy());
                                putText(original, buffer, Point(rect->tl.x, rect->tl.y + 80), 1, 2, Scalar(85, 150, 85), 2, 2, 0);
                        }

                        // measure time as current - begin_time
                        clock_t diff = clock() - begin_time;

                        // convert time into string
                        sprintf(buffer, "time 0.%ds", (int) diff);
                        putText(original, buffer, Point(400, 25), 1, 2, Scalar(255, 255, 255), 2, 8, 0);

                        sprintf(buffer, "Humans: %d (%d)", tracker.getTrackedRectangles().size(), tracker.getDetectedCount());
                        putText(original, buffer, Point(10, 25), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
                        
                        // draw results
                        namedWindow("prev", WINDOW_AUTOSIZE);
                        imshow("prev", original);

                        int key1 = waitKey(10);
                }
        }
}
