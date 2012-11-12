/*
 * smoothing.cpp
 *
 *  Created on: 12 Nov, 2012
 *      Author: hugo
 */

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

Mat src, dst;
string windowName = "Filter Demo";

int displayCaption(char* caption);
int displayDst(int delay);

int main(int argc, char** argv) {
	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	src = imread(argv[1]);

	if (displayCaption("Original image") != 0)
		return 0;

	dst = src.clone();
	if (displayDst(DELAY_CAPTION) != 0)
		return 0;

	if (displayCaption("Homogeneous Blur") != 0)
		return 0;

	for (int i = 1; i < MAX_KERNEL_LENGTH; i += 2) {
		blur(src, dst, Size(i, i), Point(-1, -1));
		if (displayDst(DELAY_CAPTION) != 0)
			return 0;
	}

	dst = src.clone();
	if (displayCaption("Gaussian Blur") != 0)
		return 0;

	for (int i = 1; i < MAX_KERNEL_LENGTH; i += 2) {
		GaussianBlur(src, dst, Size(i, i), 0, 0);
		if (displayDst(DELAY_CAPTION) != 0)
			return 0;

	}

	dst = src.clone();
	if (displayCaption("Median Blur") != 0)
		return 0;

	for (int i = 1; i < MAX_KERNEL_LENGTH; i += 2) {
		medianBlur(src, dst, i);
		if (displayDst(DELAY_CAPTION) != 0)
			return 0;
	}

	dst = src.clone();
	if (displayCaption("Bilateral Blur") != 0)
		return 0;

	for (int i = 1; i < MAX_KERNEL_LENGTH; i += 2) {
		bilateralFilter(src, dst, i, i * 2, i / 2);
		if (displayDst(DELAY_CAPTION) != 0)
			return 0;
	}

	return 0;
}

int displayCaption(char* caption) {
	dst = Mat::zeros(src.size(), src.type());
	putText(dst, caption, Point(src.cols / 4, src.rows / 2),
			CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
	imshow(caption, dst);

	int c = waitKey(DELAY_CAPTION);
	if (c >= 0)
		return -1;
	return 0;
}

int displayDst(int delay) {
	imshow(windowName, dst);
	int c = waitKey(DELAY_CAPTION);
	if (c >= 0)
		return -1;
	return 0;
}
