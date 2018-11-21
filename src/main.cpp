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
        VideoCapture cap("/dev/video0");

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
        RectangleTracker* tracker = new RectangleTracker();
        vector<TrackedRectangle>* trackedRectangle = tracker->getTrackedRectangles();

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

                        // Store results in these 2 vectors
                        vector<Rect> humans;

                        // prepare 2 Mat container
                        Mat img;
                        Mat original;

                        // capture frame from video file
                        cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);

                        // Resize image if you want with same size as your VideoWriter
                        resize(img, img, Size(640, 480));

                        // Store original colored image
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

                        tracker->update(humans);


                        for (int f = 0; f < trackedRectangle->size(); f++) {
                                rectangle(original, trackedRectangle[f].tl(), trackedRectangle[f].br(), Scalar(0,0,255), 2, 8, 0);
                        }
                        // Draw results from detectorBody into original colored image
                        // if (humans.size() > 0) {
                        //         for (int gg = 0; gg < humans.size(); gg++) {
                        //                 rectangle(original, humans[gg].tl(), humans[gg].br(), Scalar(0,0,255), 2, 8, 0);

                        //                 sprintf(buffer, "h:%d, w:%d", humans[gg].height, humans[gg].width);
                        //                 putText(original, buffer, Point(400, 30 * (gg+1)), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
                        //         }
                        // }

                        // measure time as current - begin_time
                        clock_t diff = clock() - begin_time;

                        // convert time into string
                        sprintf(buffer, "0.%d", (int) diff);

                        // display TIME ms on original image
                        putText(original, buffer, Point(100, 20), 1, 2, Scalar(255, 255, 255), 2, 8, 0);
                        
                        // draw results
                        namedWindow("prew", WINDOW_AUTOSIZE);
                        imshow("prew", original);

                        int key1 = waitKey(10);
                }
        }
}
