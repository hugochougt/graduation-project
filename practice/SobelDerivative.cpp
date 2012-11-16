/*
 * SobelDerivative.cpp
 *
 *  Created on: 16 Nov, 2012
 *      Author: hugo
 */

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src, srcGray;
	Mat grad;

	string windowName = "Sobel Demo - Simple Edge Detector";
	int scale = 1;
	int delta = 0;
	int dDepth = CV_16S;

	src = imread(argv[1]);
	if(!src.data)
		return -1;

	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	cvtColor(src, srcGray, CV_RGB2GRAY);

	namedWindow(windowName, CV_WINDOW_AUTOSIZE);

	Mat gradX, gradY;
	Mat absGradX, absGradY;

	// Gradient X
	// Scharr(srcGray, gradX, dDepth, 1, 0, scale, delta, BORDER_DEFAULT);
	Sobel(srcGray, gradX, dDepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(gradX, absGradX);

	// Gradient Y
	// Scharr(srcGray, gradY, dDepth, 1, 0, scale, delta, BORDER_DEFAULT);
	Sobel(srcGray, gradY, dDepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
	convertScaleAbs(gradY, absGradY);

	// Total gradient (approximate)
	addWeighted(absGradX, 0.5, absGradY, 0.5, 0, grad);

	imshow(windowName, grad);

	waitKey(0);
	return 0;
}
