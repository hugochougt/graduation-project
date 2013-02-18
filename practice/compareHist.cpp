#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat src_base, src_test1, src_test2;
    Mat hsv_base, hsv_test1, hsv_test2;
    Mat hsv_half_down;

    if(argc < 4)
    {
        cout << "** Error. Usage: ./compareHist.o <img1> <img2> <img3>" << endl;
        return -1;
    }

    src_base = imread(argv[1], 1);
    src_test1 = imread(argv[2], 1);
    src_test2 = imread(argv[3], 1);

    cvtColor(src_base, hsv_base, CV_BGR2HSV);
    cvtColor(src_test1, hsv_test1, CV_BGR2HSV);
    cvtColor(src_base, hsv_test2, CV_BGR2HSV);

    hsv_half_down = hsv_base(Range(hsv_base.rows / 2, hsv_base.rows - 1), Range(0, hsv_base.cols - 1));

    int h_bins = 50, s_bins = 60;
    int histSize[] = {h_bins, s_bins};

    float h_ranges[] = {0, 256};
    float s_range[] = {0, 180};

    const float* ranges[] = {h_ranges, s_range};

    int channels[] = {0, 1};

    MatND hist_base, hist_half_down, hist_test1, hist_test2;

    calcHist(&hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false);
    normalize(hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false);
    normalize(hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
    normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false);
    normalize(hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat());

    int compare_method;
    for(int i = 0; i < 4; i++)
    {
       compare_method = i;
       double base_base = compareHist(hist_base, hist_base, compare_method);
       double base_half = compareHist(hist_base, hist_half_down, compare_method);
       double base_test1 = compareHist(hist_base, hist_test1, compare_method);
       double base_test2 = compareHist(hist_base, hist_test2, compare_method);
       cout << "Method [" << i << "] Perfect, Base-Base, Base-Half, Base-Test(1), Base-Test(2) : " << base_base << ", " << base_half << ", " << base_test1 << ", " << base_test2 << endl;
    }

    cout << "Done" << endl;

    return 0;
}
