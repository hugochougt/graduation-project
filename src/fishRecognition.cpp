#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        cout << "Usage: fishRecognition.o <videoname>" << endl;
        return -1;
    }

    string windowName = "Fish Recognition";
    string videoName = argv[1];
    
    VideoCapture capture(videoName);
    if(!capture.isOpened())
    {
        cout << "Fail to open the video" << endl;
        return -1;
    }

    namedWindow(windowName, CV_WINDOW_AUTOSIZE);

    while(true)
    {
        Mat frame;
        capture >> frame;
        imshow(windowName, frame);
        if(waitKey(30) >= 0)
            break;
    }

    return 0;
}
