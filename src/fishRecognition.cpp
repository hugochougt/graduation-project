#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
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

    BackgroundSubtractorMOG2 bgModel;	// (100, 3, 0.3, 5);

    Mat frame, fgMask, fgImage;
    bool updateModel = true;

    while(true)
    {
        capture >> frame;
        if(frame.empty())
        	break;

        // The usage of GaussianBulr() function reduce the performance of this program.
        GaussianBlur(frame, frame, Size(3, 3), 0, 0);

        if(fgImage.empty())
        	fgImage.create(frame.size(), frame.type());

        bgModel(frame, fgMask, updateModel ? -1 : 0);

        fgImage = Scalar::all(0);
        frame.copyTo(fgImage, fgMask);

        Mat bgImage;
        bgModel.getBackgroundImage(bgImage);

        imshow("frame", frame);
        imshow("foreground mask", fgMask);
        imshow(windowName, fgImage);
        if(!bgImage.empty())
        	imshow("mean background image", bgImage);

        char k = waitKey(30);
        if(k == 27)
        	break;
        if(k == ' ')
        {
        	updateModel = !updateModel;
        	if(updateModel)
        		cout << "Background update is on" << endl;
        	else
        		cout << "Background update is off" << endl;
        }

        //imshow(windowName, frame);
        //if(waitKey(30) >= 0)
        //    break;
    }

    return 0;
}
