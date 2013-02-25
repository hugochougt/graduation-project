#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/video/tracking.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    if(argc != 2)
        return -1;

    VideoCapture capture(argv[1]);
    if(!capture.isOpened())
        return -1;

    double rate = capture.get(CV_CAP_PROP_FPS);

    bool stop(false);
    Mat frame;
    namedWindow("Extracted Frame");

    int delay = 1000 / rate;

    cout << "rate" << rate << "delay" << delay << endl;
    /*
    Mat gray, gray_prev;
    vector<Point2f> points[2];
    vector<Point2f> features;
    const int MAX_COUNT = 500;
    Size winSize(10, 10);
    TermCriteria termcrit(CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03);
    bool firstFrame = true;

    while(!stop)
    {
        if(!capture.read(frame))
            break;

        cvtColor(frame, gray, CV_BGR2GRAY);
        if(firstFrame)
        {
            goodFeaturesToTrack(gray, features, MAX_COUNT, 0.01, 10, Mat(), 3, 0, 0.04);
            cornerSubPix(gray, features, winSize, Size(-1, -1), termcrit);
            points[0].insert(points[0].end(), features.begin(), features.end());
            firstFrame = false;
        }

        vector<uchar> status;
        vector<float> err;
        if(gray_prev.empty())
            gray.copyTo(gray_prev);
        calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err, winSize, 3, termcrit, 0);
        size_t i, k;
        for(i = k = 0; i < points[1].size(); i++)
        {
            if(!status[i])
                continue;
            if((abs(points[0][i].x - points[1][i].x) + (abs(points[0][i].y - points[1][i].y)) < 2))
                continue;
            line(frame, points[0][i], points[1][i], Scalar(0, 255, 0));
            points[1][k++] = points[1][i];
            circle(frame, points[1][i], 3, Scalar(0, 255, 0), -1, 8);
        }
        points[1].resize(k);
        if(points[1].size() <= 10)
            firstFrame = true;

        std::swap(points[1], points[0]);
        cv::swap(gray_prev, gray);

        imshow("Extracted Frame", frame);

        if(waitKey(delay) >= 0)
            stop = true;
    }
    */
    capture.release();
    return 0;
}

