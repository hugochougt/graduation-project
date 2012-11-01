#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat& ScanImageAndReduceC(Mat& I, const uchar* const table);
Mat& ScanImageAndReduceIterator(Mat& I, const Vec3b* const table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table);
void LUTFunction(Mat& I, Mat& J, const uchar* const table);

int main(int argc, char** argv) {
	if (argc < 3) {
		cout << "Usage: scamImage <ImageName> <intValueToReduce> [G]" << endl;
		return -1;
	}

	int divideWith;
	stringstream s;
	s << argv[2];
	if (!s) {
		cout << "Invalid number entered for dividing." << endl;
	}
	s >> divideWith;

	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = divideWith * (i / divideWith);

	double t;

	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
	imshow("Original", image);

	Mat tmp1 = image.clone();
	t = (double) getTickCount();
	Mat reduce1 = ScanImageAndReduceC(tmp1, table);
	t = ((double) getTickCount() - t) / getTickFrequency();
	cout << "The efficient way: " << t << endl;
	imshow("ScanImageAndReduceC", reduce1);

	Mat tmp2 = image.clone();
	t = (double) getTickCount();
	Mat reduce2 = ScanImageAndReduceRandomAccess(tmp2, table);
	t = ((double) getTickCount() - t) / getTickFrequency();
	cout << "On-The-Fly RA: " << t << endl;
	imshow("ScanImageAndReduceIterator", reduce2);

	Mat tmp3 = image.clone();
	Mat reduce3;
	t = (double) getTickCount();
	LUTFunction(tmp3, reduce3, table);
	t = ((double) getTickCount() - t) / getTickFrequency();
	cout << "LUT function: " << t << endl;
	imshow("LUTFunction", reduce3);

//	There is a compile error with the ScanImageAndReduceIterator() function
//	Mat tmp4 = image.clone();
//	Mat reduce4 = ScanImageAndReduceIterator(tmp4, table);
//	imshow("ScanImageAndReduceIterator", reduce4);

	waitKey(0);
	return 0;
}

// The efficient way
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table) {
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(uchar));

	int channels = I.channels();

	int nRows = I.rows * channels;
	int nCols = I.cols;

	if (I.isContinuous()) {
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar *p;
	for (i = 0; i < nRows; ++i) {
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
			p[j] = table[p[j]];
	}

	return I;
}

// The iterator (safer) method
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table) {
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(Vec3b));

	const int channels = I.channels();
	switch (channels) {
	case 1: {
		MatIterator_<uchar> it, end;
		for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
			*it = table[*it];
		break;
	}
	case 3: {
		MatIterator_<Vec3b> it, end;
		for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it) {
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];
		}
		break;
	}
	}

	return I;
}

// On-the-fly address calculation with reference returning
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table) {
	// accept only char type matrices
	CV_Assert(I.depth() != sizeof(Vec3b));

	const int channels = I.channels();
	switch (channels) {
	case 1: {
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
		break;
	}
	case 3: {
		Mat_<Vec3b> _I = I;

		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j) {
				_I(i, j)[0] = table[_I(i, j)[0]];
				_I(i, j)[1] = table[_I(i, j)[1]];
				_I(i, j)[2] = table[_I(i, j)[2]];
			}
		I = _I;
		break;
	}
	}

	return I;
}

// The LUT() function of the core module
void LUTFunction(Mat& I, Mat& J, const uchar* const table) {
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.data;
	for (int i = 0; i < 256; ++i)
		p[i] = table[i];

	LUT(I, lookUpTable, J); // I is input image and J is output one
}
