#include "opencv2.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture capture;
    if(argc != 3)
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

    VideoWriter outputVideo;
    outputVideo.open(argv[2], static_cast<int>(capture.get(CV_CAP_PROP_FOURCC)), capture.get(CV_CAP_PROP_FPS), Size(capture.get(CV_CAP_PROP_FRAME_WIDTH), capture.get(CV_CAP_PROP_FRAME_HEIGHT)), true);

    if(!outputVideo.isOpened())
    {
        cout << "can not open output video." << endl;
        return -1;
    }

    while(!stop)
    {
        capture >> frame;
        if(frame.empty())
            break;

        if(fgImage.empty())
            fgImage.create(frame.size(), frame.type());

        //GaussianBlur(frame, frame, Size(3, 3), 0, 0);

        bgSubtractor(frame, fgMask, -1);

        // 去掉前景mask的噪音。
        medianBlur(fgMask, fgMask, 5);

        fgImage = Scalar::all(0);
        frame.copyTo(fgImage, fgMask);

        outputVideo << fgImage;

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

    cout << "Finished writing." << endl;

    return 0;
}

