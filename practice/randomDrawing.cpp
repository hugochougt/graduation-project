#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

#define DELAY 30
#define LINETYPE 8
#define NUMBER 20

using namespace std;
using namespace cv;

int x_1, x_2, y_1, y_2;

static Scalar randomColor(RNG &rng) {
	int color = (unsigned) rng;
	return Scalar(color & 255, (color >> 8) & 255, (color >> 16) & 255);
}

int main(int argc, char** argv) {
	if (argc < 3) {
		cout << "Usage: randomDrawing <width> <height>" << endl;
		return -1;
	}

	int drawingRandomLines(Mat image, char* windowName, RNG rng);
	int displayRandomText(Mat image, char* windowName, RNG rng);

	char* windowName = "randomDrawing";
	int height = atoi(argv[1]);
	int width = atoi(argv[2]);
	int c;

	x_1 = (int) -width / 2;
	x_2 = (int) width * 3 / 2;
	y_1 = (int) -height / 2;
	y_2 = (int) height * 3 / 2;

	RNG rng(0xFFFFFFFF);
	Mat image = Mat::zeros(height, width, CV_8UC3);
	imshow(windowName, image);
	waitKey(DELAY);

	c = drawingRandomLines(image, windowName, rng);
	if (c != 0)
		return 0;

	c = displayRandomText(image, windowName, rng);
	if(c != 0)
		return 0;

	waitKey(0);
	return 0;
}

int drawingRandomLines(Mat image, char* windowName, RNG rng) {
	Point start, end;
	for (int i = 0; i < NUMBER; i++) {
		start.x = (int) rng.uniform(x_1, x_2);
		start.y = (int) rng.uniform(y_1, y_2);
		end.x = (int) rng.uniform(x_1, x_2);
		end.y = (int) rng.uniform(y_2, y_2);

		line(image, start, end, randomColor(rng), rng.uniform(1, 8), LINETYPE);
		imshow(windowName, image);

		if (waitKey(DELAY) >= 0)
			return -1;
	}

	return 0;
}

int displayRandomText(Mat image, char* windowName, RNG rng) {
	for (int i = 0; i < NUMBER; i++) {
		Point org;
		org.x = rng.uniform(x_1, x_2);
		org.y = rng.uniform(y_1, y_2);

		putText(image, "Testing text rendering", org, rng.uniform(0, 8),
				rng.uniform(1, 100) * 0.05 + 0.1, randomColor(rng),
				rng.uniform(1, 10), LINETYPE);
		imshow(windowName, image);

		if (waitKey(DELAY) >= 0)
			return -1;
	}
	return 0;
}
