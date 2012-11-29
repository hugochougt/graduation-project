/*
 * featureMatching.cpp
 *
 *  Created on: 29 Nov, 2012
 *      Author: hugo
 */

#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/nonfree/features2d.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	if (argc != 3)
		return -1;

	Mat img1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	Mat img2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);

	if (!img1.data || !img2.data) {
		cout << "--(!) Error reading images." << endl;
		return -1;
	}

	// Step 1: Detect the keypoints using SURF detector
	int minHessian = 400;
	SurfFeatureDetector detector(minHessian);
	vector<KeyPoint> keypoints1, keypoints2;

	detector.detect(img1, keypoints1);
	detector.detect(img2, keypoints2);

	// Step 2: Calculate descriptor (feature vectors)
	SurfDescriptorExtractor extractor;
	Mat descriptor1, descriptor2;

	extractor.compute(img1, keypoints1, descriptor1);
	extractor.compute(img2, keypoints2, descriptor2);

	// Step 3: Matching descriptor keypoints using FLANN matcher
	FlannBasedMatcher matcher;
	vector<DMatch> matches;
	matcher.match(descriptor1, descriptor2, matches);

	double maxDist = 0;
	double minDist = 100;
	double dist;

	// Quick calculation of max and min distance between keypoints
	for (int i = 0; i < descriptor1.rows; i++) {
		dist = matches[i].distance;
		if (dist < minDist)
			minDist = dist;
		if (dist > maxDist)
			maxDist = dist;
	}

	cout << "-- Max dist: " << maxDist << endl;
	cout << "-- Min dist: " << minDist << endl;

	// Draw only "good" matches (i.e. whose distance is less than 2 * minDist
	// PS. radius Match can also be used here
	vector<DMatch> goodMatches;
	for (int i = 0; i < descriptor1.rows; i++) {
		if (matches[i].distance < 2 * minDist)
			goodMatches.push_back(matches[i]);
	}

	// Draw only "good" matches
	Mat imgMatches;
	drawMatches(img1, keypoints1, img2, keypoints2, goodMatches, imgMatches,
			Scalar::all(-1), Scalar::all(-1), vector<char>(),
			DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	// Show detected matches
	imshow("Good Matches", imgMatches);
	for(int i = 0; i < imgMatches.rows; i++)
		cout << "Good Match [" << i << "] keypoint 1: " << goodMatches[i].queryIdx << "-- keypoint 2: " << goodMatches[i].trainIdx << endl;

	waitKey(0);
	return 0;
}
