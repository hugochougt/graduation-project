#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    uchar n;
    n = saturate_cast<uchar>(-23);
    cout << "saturate cast -23 is " << (int)n << endl;
    n = saturate_cast<uchar>(0);
    cout << "saturate cast 0 is " << (int)n << endl;
    n = saturate_cast<uchar>(75);
    cout << "saturate cast 75 is " << (int)n << endl;
    n = saturate_cast<uchar>(255);
    cout << "saturate cast 255 is " << (int)n << endl;
    n = saturate_cast<uchar>(999);
    cout << "saturate cast 999 is " << (int)n << endl;
    n = saturate_cast<uchar>(123456);
    cout << "saturate cast 123456 is " << (int)n << endl;

    return 0;
}
