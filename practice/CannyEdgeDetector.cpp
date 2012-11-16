/*
 * CannyEdgeDetector.cpp
 *
 *  Created on: 16 Nov, 2012
 *      Author: hugo
 */

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src, srcGray;
Mat dst, detectedEdges;

int edgeThreshold = 1;
int lowThreshold = 1;
int const maxLowThreshold = 100;
int ratio = 3;
int kernelSize = 3;
string windowName = "Edge Map";

/*
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int , void*)
{
	// Reduce noise with a kernel 3x3
	blur(srcGray, detectedEdges, Size(3, 3));

	// Canny detector
	Canny(detectedEdges, detectedEdges, lowThreshold, lowThreshold * ratio, kernelSize);

	// Using canny's output as a mask
	dst = Scalar::all(0);

	src.copyTo(dst, detectedEdges);
	imshow(windowName, dst);
}

/*
 * @function main
 */
int main(int argc, char** argv)
{
	src = imread(argv[1]);
	if (!src.data)
		return -1;

	// Create a matrix of the same type and size as src (for dst)
	dst.create(src.size(), src.type());

	// Convent the image to grayscale
	cvtColor(src, srcGray, CV_BGR2GRAY);

	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	createTrackbar("Min Threshold", windowName, &lowThreshold, maxLowThreshold, CannyThreshold);

	CannyThreshold(0, 0);

	waitKey(0);
	return 0;
}
