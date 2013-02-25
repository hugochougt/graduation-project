
using namespace cv;
using namespace std;

class BGFGSegmentor : public FrameProcessor 
{
    Mat gray;
    Mat background;
    Mat backImage;
    Mat foreground;

    double learningRate;
    int threshold;

public:
    BGFGSegmentor() : threshold(10), learningRate(0.01) { }

    void processing(Mat &frame, Mat &output)
    {
        cvtColor(frame, gray, CV_BGR2GRAY);

        if(background.empty())
        {
            gray.convertTo(background, CV_32F);
        }

        background.converTo(backImage, CV_8U);

        absdiff(backImage, gray, foreground);

        threshold(foreground, output, threshold, 255, THRESH_BINARY_INV);

        accumulateWeighted(gray, background, learningRate, output);
    }
}
