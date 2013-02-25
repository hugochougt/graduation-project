#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    Mat src_test1, src_test2;
    Mat hsv_test1, hsv_test2;

    if(argc < 3)
    {
        cout << "** Error. Usage: ./compareHist.o <img1> <img2>" << endl;
        return -1;
    }

    src_test1 = imread(argv[1], 1);
    src_test2 = imread(argv[2], 1);

    cvtColor(src_test1, hsv_test1, CV_BGR2HSV);
    cvtColor(src_test2, hsv_test2, CV_BGR2HSV);

    int h_bins = 50, s_bins = 60;
    int histSize[] = {h_bins, s_bins};

    float h_ranges[] = {1, 256};
    float s_range[] = {0, 180};

    const float* ranges[] = {h_ranges, s_range};

    int channels[] = {0, 1};

    MatND hist_test1, hist_test2;

    calcHist(&hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false);
    normalize(hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat());

    calcHist(&hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false);
    normalize(hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat());

    imshow("1111", hist_test1);

    cout << "histogram:" << endl;
    cout << hist_test1 << endl;

    cout << "CORREL: " << compareHist(hist_test1, hist_test2, CV_COMP_CORREL) << endl;
    cout << "CHISQR: " << compareHist(hist_test1, hist_test2, CV_COMP_CHISQR) << endl;
    cout << "INTERSEC: " << compareHist(hist_test1, hist_test2, CV_COMP_INTERSECT) << endl;
    cout << "BHATTACHARYYA: " << compareHist(hist_test1, hist_test2, CV_COMP_BHATTACHARYYA) << endl;
    cout << "HELLINGER: " << compareHist(hist_test1, hist_test2, CV_COMP_HELLINGER) << endl;
    cout << "Done" << endl;

    waitKey(0);
    return 0;
}
