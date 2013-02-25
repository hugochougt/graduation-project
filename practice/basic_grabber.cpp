#include <opencv2/core/core.hhp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int main(int argc, char** argv)
{
    if(argc != 2)
        return -1; 

    string videoName = argv[1];
    VideoCapture capture(videoName);
    
    if(!capture.isOpened())
        return -1;

    Mat frame;
    while(true)
    {
        capture >> frame;
    }

    return 0;
