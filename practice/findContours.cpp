#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

string srcWindow = "Source Window";
string grayWindow = "Gray Window";
string threshWindow = "Thresh Window";
string arrayWindow[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21"};
int thresh = 64;

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        cout << "Arguments error!" << endl;
        return -1;
    }

    Mat srcImg = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat grayImg, threshImg;

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    cvtColor(srcImg, grayImg, CV_BGR2GRAY);

    threshold(grayImg, threshImg, thresh, 255, THRESH_BINARY);

    findContours(threshImg, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    cout << "Size of contours: " << contours.size() << endl;

    double area;
    for(int i = 0; i < contours.size(); i++)
    {
        cout << "Size of contours " << i << " : " << contours[i].size() << endl;
        area = contourArea(contours[i]);
        cout << "Area: " << area << endl;

        {
            RotatedRect rect = minAreaRect(Mat(contours[i]));
            Mat m, rotated, cropped;

            float angle = rect.angle;
            Size rect_size = rect.size;

            if(rect.angle < -45)
            {
                angle += 90.0;
                std::swap(rect_size.width, rect_size.height);
            }

            m = getRotationMatrix2D(rect.center, angle, 1.0);
            warpAffine(srcImg, rotated, m, srcImg.size(), INTER_CUBIC);
            getRectSubPix(rotated, rect_size, rect.center, cropped);

            imshow("cropped", cropped);
            waitKey(0);
        }
    }

    //namedWindow(srcWindow, CV_WINDOW_AUTOSIZE);
    //namedWindow(grayWindow, CV_WINDOW_AUTOSIZE);
    //namedWindow(threshWindow, CV_WINDOW_AUTOSIZE);

    //imshow(srcWindow, srcImg);
    //imshow(grayWindow, grayImg);
    //imshow(threshWindow, threshImg);

    waitKey(0);
    return 0;
}
