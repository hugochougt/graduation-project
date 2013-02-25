#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat src, src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

void thresh_callback(int , void*);

int main(int argc, char** argv)
{
    src = imread(argv[1], 1);
    
    cvtColor(src, src_gray, CV_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));

    string source_window = "Source";
    namedWindow(source_window, CV_WINDOW_AUTOSIZE);
    imshow(source_window, src);

    createTrackbar("Threshold:", source_window, &thresh, max_thresh, thresh_callback);
    thresh_callback(0, 0);

    waitKey(0);

    return 0;
}

void thresh_callback(int , void*)
{
    Mat threshold_output;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    threshold(src_gray, threshold_output, thresh, 255, THRESH_BINARY);

    findContours(threshold_output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    vector<RotatedRect> minRect(contours.size());
    vector<RotatedRect> minEllipse(contours.size());

    for(int i = 0; i < contours.size(); i++)
    {
        minRect[i] = minAreaRect(Mat(contours[i]));
        cout << contours[i].size() << endl;
        if(contours[i].size() > 24)
        {
            minEllipse[i] = fitEllipse(Mat(contours[i]));
        }
    }

    //Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
    for(int i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
        //drawContours(drawing, contours, i , color, 1, 8, vector<Vec4i>(), 0, Point());
        ellipse(src, minEllipse[i], color, 2, 8);
        
        /*
        Point2f rect_points[4];
        minRect[i].points(rect_points);
        for(int j = 0; j < 4; j++)
        {
            line(drawing, rect_points[j], rect_points[(j + 1) % 4], color, 1, 8);
        }
*/
    }

    namedWindow("Contours", CV_WINDOW_AUTOSIZE);
    imshow("Contours", src);
}
