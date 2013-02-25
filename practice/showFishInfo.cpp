#include "fish.h"

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout << "Argument error." << endl;
        return -1;
    }

    Mat src1 = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat src2 = imread(argv[2], CV_LOAD_IMAGE_COLOR);

    if(!src1.data || !src2.data)
    {
        cout << "can not open image." << endl;
        return -1;
    }

    Fish fish1(src1);
    Fish fish2(src2);

    fish1.featureDetect();
    fish2.featureDetect();

    if(fish1.match(fish2))
        cout << "Yes" << endl;
    else
        cout << "No" << endl;

    //cout << "Area: " << fish.getArea() << endl;
    //cout << "Ratio: " << fish.getRatio() << endl;

    //namedWindow("Histogram", CV_WINDOW_AUTOSIZE);
    //imshow("Histogram", fish.getHistogram());


    cout << "Done" << endl;
    return 0;
}
