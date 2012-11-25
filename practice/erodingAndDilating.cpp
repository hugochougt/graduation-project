#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, erosionDst, dilationDst;

int erosionElem = 0;
int erosionSize = 0;
int dilationElem = 0;
int dilationSize = 0;
int const maxElem = 2;
int const maxKernelSize = 21;

string erosionDemo = "Erosion Demo";
string dilationDemo = "Dilation Demo";

// Function Headers
void Erosion(int, void*);
void Dilation(int, void*);

int main(int argc, char** argv)
{
    src = imread(argv[1]);
    if(!src.data)
        return -1;


    namedWindow(erosionDemo, CV_WINDOW_AUTOSIZE);
    namedWindow(dilationDemo, CV_WINDOW_AUTOSIZE);

    // Create erosion trackbar
    createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", erosionDemo, &erosionElem, maxElem, Erosion);

    createTrackbar("Kernel size:\n 2n+1", erosionDemo, &erosionSize, maxKernelSize, Erosion);

    // Creatttte dilation trackbar
    createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", dilationDemo, &dilationElem, maxElem, Dilation);

    createTrackbar("Kernel size:\n 2n+1", dilationDemo, &dilationSize, maxKernelSize, Dilation);

    // Default start
    Erosion(0, 0);
    Dilation(0, 0);

    waitKey(0);
    return 0;
}

void Erosion(int, void*)
{
    int erosionType;
    if(erosionElem == 0)
        erosionType = MORPH_RECT;
    else if(erosionElem == 1)
        erosionType = MORPH_CROSS;
    else if(erosionElem == 2)
        erosionType = MORPH_ELLIPSE;

    Mat element = getStructuringElement(erosionType, Size(2 * erosionSize + 1, 2 * erosionSize + 1), Point(erosionSize, erosionSize));

    // Apply the erosion operation
    erode(src, erosionDst, element);
    imshow(erosionDemo, erosionDst);
}

void Dilation(int, void*)
{
    int dilationType;
    if(dilationElem == 0)
        dilationType = MORPH_RECT;
    else if(dilationElem == 1)
        dilationElem = MORPH_CROSS;
    else if(dilationElem == 2)
        dilationType = MORPH_ELLIPSE;

    Mat element = getStructuringElement(dilationType, Size(2 * dilationSize + 1, 2 * dilationSize + 1), Point(dilationSize, dilationSize));

    // Apply the dilation operation
    dilate(src, dilationDst, element);
    imshow(dilationDemo, dilationDst);
}
