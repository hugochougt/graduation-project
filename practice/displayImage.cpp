#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		cout << "Usage: displayImage <ImageName>" << endl;
		return -1;
	}

	Mat image;
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);	// Read the file

	if(!image.data)									// Check for invalid input
	{
		cout << "Could not open or find the image" << argv[1] << endl;
		return -1;
	}

	namedWindow("Display window", CV_WINDOW_AUTOSIZE);	// Create a window for display
	imshow("Display window", image);					// Show image inside it

	waitKey(0);
	return 0;
}
