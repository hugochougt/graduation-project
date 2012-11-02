#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    void Sharpen(const Mat&, Mat&);
    Mat M(4, 6, CV_8UC1);
    randu(M, Scalar::all(0), Scalar::all(255));
    cout << "M = " << endl << M << endl;

    Mat R;
    Sharpen(M, R);
    cout << "R = " << endl << R << endl;

    Mat kern = (Mat_<char>(3, 3) << 0, -1, 0,
                                    0, 5, 0,
                                    0, -1, 0);
    Mat K;
    filter2D(M, K, M.depth(), kern);
    cout << "K = " << endl << K << endl;

    return 0;
}

void Sharpen(const Mat& image, Mat& result)
{
    CV_Assert(image.depth() == CV_8U);

    result.create(image.size(), image.type());
    const int nChannels = image.channels();

    for(int j = 1; j < image.rows - 1; ++j)
    {
       const uchar* previous = image.ptr<uchar>(j - 1);
       const uchar* current = image.ptr<uchar>(j); 
       const uchar* next = image.ptr<uchar>(j + 1); 

       uchar* output = result.ptr<uchar>(j);

       for(int i = nChannels; i < nChannels * (image.cols - 1); ++i)
       {
           *output++ = saturate_cast<uchar>(5 * current[i] - current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
       }
    }

    result.row(0).setTo(Scalar(0));
    result.row(result.rows - 1).setTo(Scalar(0));
    result.col(0).setTo(Scalar(0));
    result.col(result.rows - 1).setTo(Scalar(0));
}
