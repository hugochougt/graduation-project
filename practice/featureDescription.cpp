/*
 * featureDescription.cpp
 *
 *  Created on: 25 Nov, 2012
 *      Author: hugo
 */

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/nonfree/features2d.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << " Usage: ./SURF_descriptor <img1> <img2>" << endl;
		return -1;
	}

	Mat img1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);

	if (!img1.data || !img2.data)
		return -1;

	// Step 1: Detect the keypoints using SURF Detector
	int minHessian = 400;
	SurfFeatureDetector detector(minHessian);

	vector<KeyPoint> keyPoints1, keyPoints2;

	detector.detect(img1, keyPoints1);
	detector.detect(img2, keyPoints2);

	// Step 2: Calculate descriptors (feature vectors)
	SurfDescriptorExtractor extractor;

	Mat descriptors1, descriptors2;
	extractor.compute(img1, keyPoints1, descriptors1);
	extractor.compute(img2, keyPoints2, descriptors2);

	// Step 3: Matching descriptor vectors with a brute force matcher
	BFMatcher matcher(NORM_L2);
	vector<DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);

	// Draw matches
	Mat imgMatches;
	drawMatches(img1, keyPoints1, img2, keyPoints2, matches, imgMatches);

	// Show detected matches
	imshow("Matches", imgMatches);

	waitKey(0);
	return 0;
}
