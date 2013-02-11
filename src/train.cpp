#include "opencv2.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture capture;
    if(argc != 2)
    {
        cout << "Argument error!" << endl;
        return -1;
    }

    capture.open(argv[1]);
    if(!capture.isOpened())
    {
        cout << "Can't open video." << endl;
        return -1;
    }

    Mat frame, fgMask, fgImage;
    bool stop(false);
    BackgroundSubtractorMOG2 bgSubtractor;
    bool updateModel = false;

    string winMainWindow = "Main Window";
    string winForeground = "Foreground Window";

    char key = '\0';

    namedWindow(winMainWindow);
    namedWindow(winForeground);

    while(!stop)
    {
        capture >> frame;
        if(frame.empty())
            break;

        if(fgImage.empty())
            fgImage.create(frame.size(), frame.type());

        GaussianBlur(frame, frame, Size(3, 3), 0, 0);

        bgSubtractor(frame, fgMask, -1);

        medianBlur(fgMask, fgMask, 5);

        fgImage = Scalar::all(0);
        frame.copyTo(fgImage, fgMask);

        imshow(winMainWindow, frame);
        imshow(winForeground, fgImage);
        
        key = waitKey(30);
        if(key == 'q')
        {
            cout << "exit" << endl;
            stop = true;
        }
        if(key == ' ')
        {
            updateModel = !updateModel;
            cout << "updateModel = " << updateModel << endl;
        }
    }

    return 0;
}

