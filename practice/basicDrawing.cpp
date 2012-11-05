/*
 * basicDrawing.cpp
 *
 *  Created on: 5 Nov, 2012
 *      Author: hugo
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void drawAtom(int width);
void myEllipse(Mat image, int w, double angle);
void myFilledCircle(Mat image, int width, Point center);
void drawRook(int width);
void myPolygon(Mat image, int width);
void myLine(Mat image, Point start, Point end);

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "Usage: basicDrawing <width>" << endl;
		return -1;
	}

	stringstream s;
	s << argv[1];
	if (!s) {
		cout << "Invalid number entered for width." << endl;
		return -1;
	}
	int width;
	s >> width;

	drawAtom(width);

	drawRook(width);

	waitKey(0);
	return 0;
}

void drawAtom(int width) {
	char* atomWindow = "Drawing: Atom";
	Mat atomImage = Mat::zeros(width, width, CV_8UC3);
	myEllipse(atomImage, width, 90);
	myEllipse(atomImage, width, 0);
	myEllipse(atomImage, width, 45);
	myEllipse(atomImage, width, -45);
	myFilledCircle(atomImage, width, Point(width / 2.0, width / 2.0));
	namedWindow(atomWindow, CV_WINDOW_AUTOSIZE);
	imshow(atomWindow, atomImage);
}

void myEllipse(Mat image, int w, double angle) {
	int thickness = 2;
	int lineType = 8;

	ellipse(image, Point(w / 2.0, w / 2.0), Size(w / 4.0, w / 16.0), angle, 0,
			360, Scalar(255, 0, 0), thickness, lineType);
}

void myFilledCircle(Mat image, int width, Point center) {
	int thickness = -1;
	int lineType = 8;

	circle(image, center, width / 32.0, Scalar(0, 0, 255), thickness, lineType);
}

void drawRook(int width) {
	string windowName = "Drawing: rook";
	Mat rookImage = Mat::zeros(width, width, CV_8UC3);

	myPolygon(rookImage, width);
	rectangle(rookImage, Point(0, 7.0 * width / 8), Point(width, width),
			Scalar(0, 255, 255), -1, 8);
	myLine(rookImage, Point(0, 15 * width / 16), Point(width, 15 * width / 16));
	myLine(rookImage, Point(width / 4, 7 * width / 8), Point(width / 4, width));
	myLine(rookImage, Point(width / 2, 7 * width / 8), Point(width / 2, width));
	myLine(rookImage, Point(3 * width / 4, 7 * width / 8), Point(3 * width / 4, width));

	namedWindow(windowName, CV_WINDOW_AUTOSIZE);
	imshow(windowName, rookImage);
}

void myPolygon(Mat image, int w) {
	int lineType = 8;
	/** Create some points */
	Point rookPoints[1][20];
	rookPoints[0][0] = Point(w / 4.0, 7 * w / 8.0);
	rookPoints[0][1] = Point(3 * w / 4.0, 7 * w / 8.0);
	rookPoints[0][2] = Point(3 * w / 4.0, 13 * w / 16.0);
	rookPoints[0][3] = Point(11 * w / 16.0, 13 * w / 16.0);
	rookPoints[0][4] = Point(19 * w / 32.0, 3 * w / 8.0);
	rookPoints[0][5] = Point(3 * w / 4.0, 3 * w / 8.0);
	rookPoints[0][6] = Point(3 * w / 4.0, w / 8.0);
	rookPoints[0][7] = Point(26 * w / 40.0, w / 8.0);
	rookPoints[0][8] = Point(26 * w / 40.0, w / 4.0);
	rookPoints[0][9] = Point(22 * w / 40.0, w / 4.0);
	rookPoints[0][10] = Point(22 * w / 40.0, w / 8.0);
	rookPoints[0][11] = Point(18 * w / 40.0, w / 8.0);
	rookPoints[0][12] = Point(18 * w / 40.0, w / 4.0);
	rookPoints[0][13] = Point(14 * w / 40.0, w / 4.0);
	rookPoints[0][14] = Point(14 * w / 40.0, w / 8.0);
	rookPoints[0][15] = Point(w / 4.0, w / 8.0);
	rookPoints[0][16] = Point(w / 4.0, 3 * w / 8.0);
	rookPoints[0][17] = Point(13 * w / 32.0, 3 * w / 8.0);
	rookPoints[0][18] = Point(5 * w / 16.0, 13 * w / 16.0);
	rookPoints[0][19] = Point(w / 4.0, 13 * w / 16.0);

	const Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };

	fillPoly(image, ppt, npt, 1, Scalar(255, 255, 255), lineType);
}

void myLine(Mat image, Point start, Point end) {
	int thickness = 2;
	int lineType = 8;

	line(image, start, end, Scalar(0, 0, 0), thickness, lineType);
}
