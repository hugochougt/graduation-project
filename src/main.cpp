#include <sstream>
#include <opencv2/video/video.hpp>
#include "fish.h"


void help()
{
    cout << "Usage:" << endl;
    cout << "\trecognition <videoFile> <fishName>" << endl;
}

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout << "**** Argument error. ****" << endl;
        help();
        return -1;
    }

    string videoFile = argv[1];
    string fishName = argv[2];
    string featureData = fishName + ".xml";

    string mainWindow = "Main Window";

    // Load the feature datas.
    FileStorage fs;
    fs.open(featureData, FileStorage::READ);

    if(!fs.isOpened())
    {
        cout << "**** Failed to open " << featureData << " ****" << endl;
        return -1;
    }

    int size = (int)fs["size"];
    vector<Fish> fishVec;
    stringstream itoa;
    string ID;

    //cout << "train size: " << size << endl;

    for(int i = 1; i <= size; i++)
    {
        itoa << "No" << i;
        itoa >> ID;
        Fish f;
        fs[ID] >> f;
        fishVec.push_back(f);
        itoa.clear();
    }

    //cout << "vector size: " << fishVec.size() << endl;

//        if(fishVec[3].match(fishVec[1]))
//            cout << "Yes" << endl;
//        else
//            cout << "No" << endl;

//    return 0;

    /*
    for(int i = 0; i < fishVec.size(); i++)
    {
        cout << fishVec[i].getArea() << endl;
    }
    */

    // Load the video file.
    VideoCapture capture;
    capture.open(videoFile);

    if(!capture.isOpened())
    {
        cout << "Failed to open " << videoFile << endl;
        return -1;
    }

    double rate = capture.get(CV_CAP_PROP_FPS);
    int delay = 1000 / rate;

    Mat frame, fgMask, fgImage;
    BackgroundSubtractorMOG2 bgSubtractor;
    bool stop(false);
    bool found(false);
    int discard = 30; 
    Scalar color = Scalar(0, 0, 0);

    namedWindow(mainWindow, CV_WINDOW_AUTOSIZE);

    while(!stop)
    {
        capture >> frame;
        if(frame.empty())
            break;

        if(fgImage.empty())
            fgImage.create(frame.size(), frame.type());

        bgSubtractor(frame, fgMask, -1);

        // Foreground image mask denoising.
        medianBlur(fgMask, fgMask, 5);

        fgImage = Scalar::all(0);
        frame.copyTo(fgImage, fgMask);

        // Discard the first 30 frame.
        if(discard-- > 0)
            continue;

        //namedWindow("bgSubtrac", CV_WINDOW_AUTOSIZE);
        //imshow("bgSubtrac", fgImage);

        Mat grayImage, threshImage;
        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        cvtColor(fgImage, grayImage, CV_BGR2GRAY);

        threshold(grayImage, threshImage, 100, 255, THRESH_BINARY);

        findContours(threshImage, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        //cout << "Size of contours" << contours.size() << endl;

        vector<RotatedRect> minEllipse(contours.size());
        vector<RotatedRect> minRect(contours.size());

        for(int i = 0; i < contours.size(); i++)
        {
            if(contours[i].size() < 24)
                continue;

            RotatedRect rect = minAreaRect(Mat(contours[i]));
            //if(contours[i].size() > 10)
            //   minEllipse[i] = fitEllipse(Mat(contours[i]));

            Mat tempImage, rotatedImage, croppedImage;

            float angle = rect.angle;
            Size rectSize = rect.size;

            if(rect.angle < -45)
            {   
                angle += 90.0;
                std::swap(rectSize.width, rectSize.height);
            }   

            tempImage = getRotationMatrix2D(rect.center, angle, 1.0);
            warpAffine(fgImage, rotatedImage, tempImage, fgImage.size(), INTER_CUBIC);
            getRectSubPix(rotatedImage, rectSize, rect.center, croppedImage);

            /*
            namedWindow("cropped", CV_WINDOW_AUTOSIZE);
            imshow("cropped", croppedImage);
            if(waitKey(0) == 'q')
                return 0;
            */

            Fish fish(croppedImage);
            if(fish.featureDetect() == false)
                break;

            for(int j = 0; j < fishVec.size(); j++)
            {
                if(fish.match(fishVec[j]))
                {
                    RotatedRect ellp = fitEllipse(Mat(contours[i]));
                    ellipse(frame, ellp, color, 2, 8);
                    cout << "founded" << endl;
                    namedWindow("result", CV_WINDOW_AUTOSIZE);
                    imshow("result", frame);

                    waitKey(0);
                    break;
                }
            }
        }

        imshow(mainWindow, frame);

        if(waitKey(delay) >= 0)
            stop = true;
    }

    return 0;
}
