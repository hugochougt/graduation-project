#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class Fish{
public:
    Fish(Mat img)
    {
        srcImage.create(img.size(), img.type());
        img.copyTo(srcImage);

        area = 0.0;
        ratio = 0.0;
        thresh = 64;
        succeeded = false;
    }

    Fish()
    {
        area = 0.0;
        ratio = 0.0;
        thresh = 64;
        succeeded = false;
    }

    /*
    Fish(const Fish& f)
    {
        area = f.getArea();
        ratio = f.getRatio();
        histogram = f.getHistogram();
    }
    */

    bool featureDetect()
    {
        Mat grayImg, threshImg;

        vector<vector<Point> > contours;
        vector<Vec4i> hierarchy;

        cvtColor(srcImage, grayImg, CV_BGR2GRAY);
        
        threshold(grayImg, threshImg, thresh, 255, THRESH_BINARY);

        findContours(threshImg, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

        if(contours.size() != 1)
        {
            cout << "**** Detecting features failed ****" << endl;
            succeeded = false;
            return succeeded;
        }

        // get the ROI
        Mat tempImg, rotatedImg;
        RotatedRect rect = minAreaRect(contours[0]);

        float angle = rect.angle;
        Size rectSize = rect.size;

        if(angle < -45)
        {
            angle += 90.0;
            std::swap(rectSize.width, rectSize.height);
        }

        tempImg = getRotationMatrix2D(rect.center, angle, 1.0);
        warpAffine(srcImage, rotatedImg, tempImg, srcImage.size(), INTER_CUBIC);
        getRectSubPix(rotatedImg, rectSize, rect.center, croppedImage);

        // 1. Calculates the area
        area = contourArea(contours[0]);

        // 2. Calculates the ratio
        ratio = (double) croppedImage.cols / croppedImage.rows;

        // 3. Calculates the histogram
        int hBins = 50, sBins = 60;
        int histSize[] = {hBins, sBins};

        float hRanges[] = {1, 256};
        float sRanges[] = {0, 180};

        const float* ranges[] = {hRanges, sRanges};

        int channels[] = {0, 1};

        Mat hsvImg;

        cvtColor(srcImage, hsvImg, CV_BGR2HSV);
        calcHist(&hsvImg, 1, channels, Mat(), histogram, 2, histSize, ranges, true, false);
        normalize(histogram, histogram, 0, 1, NORM_MINMAX, -1, Mat());

        succeeded = true;
        return succeeded;
    }

    bool match(Fish &f)
    {
        //f.featureDetect(); 

        double fArea = f.getArea();
        double fRatio = f.getRatio();
        MatND fROI = f.getHistogram();

        if(matchHistogram(fROI) && (matchArea(fArea) || matchRatio(fRatio)))
            return true;
        else
            return false;
    }

    bool matchArea(double x)
    {
        if(x > area * 0.8 && x < area * 1.2)
        {
            cout << "Area match" << endl;
            return true;
        }
        else
        {
            cout << "Area not match" << endl;
            return false;
        }
    }

    bool matchRatio(double x)
    {
        if(x > ratio * 0.9 && x < ratio * 1.1)
        {
            cout << "Ratio match" << endl;
            return true;
        }
        else
        {
            cout << "ratio not match" << endl;
            return false;
        }
    }

    bool matchHistogram(MatND m)
    {
        double dd = compareHist(histogram, m, CV_COMP_CORREL); 
        cout << "compareHist " << dd << endl;
        if(dd > 0.4)
            return true;
        else
            return false;
    }

    void write(FileStorage& fs) const
    {
        fs << "{" << "area" << area << "ratio" << ratio << "histogram" << histogram << "}";
    }

    void read(const FileNode& node)
    {
        area = (double) node["area"];
        ratio = (double) node["ratio"];
        node["histogram"] >> histogram;
    }

    double getArea()
    {
        return area;
    }

    double getRatio()
    {
        return ratio;
    }

    MatND getHistogram()
    {
        return histogram;
    }

    Mat getROIImage()
    {
        return croppedImage;
    }

    void setThresh(int t)
    {
        thresh = t;
    }

private:
    string name;

    Mat srcImage;

    Mat croppedImage;

    double area;

    double ratio;

    MatND histogram;

    int thresh;

    bool succeeded;
};

void write(FileStorage& fs, const string&, const Fish& f)
{
    f.write(fs);
}

void read(const FileNode& node, Fish& f, const Fish& defaultValue = Fish())
{
    if(node.empty())
        f = defaultValue;
    else
        f.read(node);
}
