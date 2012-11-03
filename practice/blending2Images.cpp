#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    double alpha = 0.5;
    double beta;
    double input;

    Mat src1, src2, dst;

    if(argc != 3)
    {
        cout << "Arguement error." << endl;
        return -1;
    }

    cout << "Simple Linear blender" << endl;
    cout << "---------------------" << endl;
    cout << "* Enter alpha [0 - 1]: ";
    cin >> input;

    if(input >= 0 && input <= 1)
    {
        alpha = input;
        beta = 1 - alpha;
    }

    // Since we are adding src1 and src2, they both must be the same size(width and height) and type.
    src1 = imread(argv[1]);
    src2 = imread(argv[2]);

    if(!src1.data || !src2.data)
    {
        cout << "Error loading images." << endl;
        return -1;
    }

    namedWindow("Linear blender", CV_WINDOW_AUTOSIZE);
    addWeighted(src1, alpha, src2, beta, 0.0, dst);
    imshow("Linear blender", dst);

    waitKey(0);
    return 0;
}
