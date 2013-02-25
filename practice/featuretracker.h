
using namespace std;
using namespace cv;

class FeatureTracker : public FrameProcessor
{
    Mat gray;
    Mat gray_prev;

    vector<Point2f> points[2];
    vector<Point2f> initial;
    vector<Point2f> features;

    int max_count;
    double qlevel;
    double minDist;
    
    vector<uchar> status;
    vector<float> err;

public:
    FeatureTracker() : max_count(500), qlevel(0.01), minDist(10.0) {}

    void process(Mat &frame, Mat &output)
    {
        cvtColor(frame, gray, CV_BGR2GRAY);
        frame.copyTo(output);

        // 1. If new feature points must be added
        if(addNewPoints())
        {
            detectFeaturePoints();
            points[0].insert(points[0].end(), features.begin(), features.end());
            initial.insert(initial.end(), features.begin(), features.end());
        }
        // for first image of the sequence
        if(gray_prev.empty())
        {
            gray.copyTo(gray_prev);
        }

        // 2. track features
        calcOpticalFlowPyrLK(gray_prev, gray, points[0], points[1], status, err);

        // loop over the tracked points to reject some
        int k = 0;
        for(int i = 0; i < points[1].size(); i++)
        {
            // do we keep this point?
            if(acceptTrackedPoint(i))
            {
                initial[k] = initial[i];
                points[1][k++] = points[1][i];
            }
        }

        // eliminate unsuccessful points
        points[1].resize(k);
        initial.resize(k);

        // 3. Handle the accepted tracked points
        handleTrackedPoints(frame, output);

        // 4. current points and image become previous ones
        std::swap(points[1], points[0]);
        cv::swap(grap_prev, gray);
    }

    void detectFeaturePoints()
    {
        goodFeaturesToTrack(gray, features, max_count, qlevel, minDist);
    }

    bool addNewPoints()
    {
        return points[0].size() <= 10;
    }

    bool acceptTrackedPoint(int i)
    {
        return status[i] && (abd(points[0][i].x - points[1][i].x) + (abs(points[0][i].y - points[1][i].y)) > 2);
    }

    void handleTrackedPoints(Mat &frame, Mat &output)
    {
        for(int i = 0; i < points[1].size(); i++)
        {
            line(output, initial[i], points[1][i], Scalar(255, 255, 255));
            circle(output, points[1][i], 3, Scalar(255, 255, 255), -1);
        }
    }
}
