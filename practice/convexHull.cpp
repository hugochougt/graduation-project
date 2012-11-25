#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat src, srcGray;
int thresh = 100;
int maxThresh = 255;
RNG rng(12345);

void threshCallback(int, void*);

int main(int argc, char** argv)
{
    src = imread(argv[1]);

    string srcWindow = "Source";
    namedWindow(srcWindow, CV_WINDOW_AUTOSIZE);
    imshow(srcWindow, src);

    createTrackbar("Threshold:", "Source", &thresh, maxThresh, threshCallback);
    threshCallback(0, 0);

    waitKey(0);
    return 0;
}

void threshCallback(int, void*)
{
    Mat srcCopy = src.clone();
    Mat thresholdOutput;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    cvtColor(srcCopy, thresholdOutput, CV_BGR2GRAY);

    // Detect edges using threshold()
    // threshold(srcGray, thresholdOutput, thresh, 255, THRESH_BINARY);

    // Find contours
    findContours(thresholdOutput, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    // Find the convex hull object for each contour
    vector<vector<Point> > hull(contours.size());
    for(int i = 0; i < contours.size(); i++)
        convexHull(Mat(contours[i]), hull[i], false);

    // Draw contours + hull results
    Mat drawing = Mat::zeros(thresholdOutput.size(), CV_8UC3);
    for(int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        drawContours(drawing, contours, i , color, 1, 8, vector<Vec4i>(), 0, Point());
        drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
    }

    // Show in a window
    namedWindow("Hull demo", CV_WINDOW_AUTOSIZE);
    imshow("Hull demo", drawing);
}
