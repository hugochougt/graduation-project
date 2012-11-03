#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    double alpha;
    int beta;

    if(argc != 2)
    {
        cout << "Arguement error." << endl;
        return -1;
    }

    Mat image = imread(argv[1]);
    Mat newImage = Mat::zeros(image.size(), image.type());
    int channel = image.channels();

    cout << "Basic linear transforms" << endl;
    cout << "-----------------------" << endl;
    cout << "* Enter alpha value [1.0 - 3.0]: ";
    cin >> alpha;
    cout << "* Enter beta value [0 - 100]: ";
    cin >> beta;

    // The three for statements below is equals to image.convertTo(newImage, -1, alpha, beta),
    // which would effectively perform newImage = alpha * image + beta .
    for(int y = 0; y < image.rows; y++)
    {
        for(int x = 0; x < image.cols; ++x)
        {
            for(int c = 0; c < channel; c++)
            {
                newImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(alpha * image.at<Vec3b>(y, x)[c] + beta);
            }
        }
    }

    imshow("Original image", image);
    imshow("New image", newImage);

    waitKey(0);
    return 0;
}
