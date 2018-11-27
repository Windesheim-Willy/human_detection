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
        VideoCapture cap("test.mov");

        CascadeClassifier detectBody;
        string cascade = "opencv/cascade.xml";

        // Load cascade into CascadeClassifier
        bool cascadeLoaded = detectBody.load(cascade);

        if (cascadeLoaded == false) {
                cout << "failed to load body detection";
                return -1;
        }

        // vars used in for
        char buffer[126];
        RectangleTracker tracker;
        // vector<Rectangle*> trackedRectangle = tracker.getTrackedRectangles();
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
                        resize(img, img, Size(800, 600));
                        img.copyTo(original);

                        // color to gray image
                        cvtColor(img, img, CV_BGR2GRAY);

                        // detect people, more remarks in performace section
                        // size (w, h)
                        detectBody.detectMultiScale(
                                img, 
                                humans, 
                                1.1, 
                                3, 
                                CASCADE_DO_CANNY_PRUNING,                       
                                Size(50,50),    // min
                                Size(555, 555)  // max
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
                        }

                        // measure time as current - begin_time
                        clock_t diff = clock() - begin_time;

                        // convert time into string
                        sprintf(buffer, "time 0.%ds", (int) diff);
                        putText(original, buffer, Point(100, 25), 1, 2, Scalar(255, 255, 255), 2, 8, 0);

                        sprintf(buffer, "Humans: %d", tracker.getTrackedRectangles().size());
                        putText(original, buffer, Point(10, 25), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
                        
                        // draw results
                        namedWindow("prew", WINDOW_AUTOSIZE);
                        imshow("prew", original);

                        // tracker.tick();
                        int key1 = waitKey(10);
                }
        }
}
