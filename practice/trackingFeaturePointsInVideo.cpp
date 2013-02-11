#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/video.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture capture;
    if(argc == 2)
        capture.open(argv[1]);
    else
        capture.open("/home/hugo/code/graduation-project/video/v_00003.avi");

    if(!capture.isOpened())
        return -1;

    double rate = capture.get(CV_CAP_PROP_FPS);

    bool stop(false);
    Mat frame;
    namedWindow("Extracted Frame");

    // Delay between each frame in ms corresponds to video frame rate
    int delay = 1000 / rate;

    while(!stop)
    {
        // Read next frame if any
        if(!capture.read(frame))
            break;
        imshow("Extracted Frame", frame);
        
        if(waitKey(delay) >= 0)
            stop = true;
    }

    capture.release();
    return 0;
}
