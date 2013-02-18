class VideoProcessor
{
    private:
        VideoCapture caputre;
        void (*process) (Mat&, Mat&);
        bool callIt;
        string windowNameInput;
        string windowNameOutput;
        int delay;
        long fnumber;
        long frameToStop;
        bool stop;
        vector<string> images;
        vector<string>::const_iterator itImg;

        bool readNextFrame(Mat& frame)
        {
            return capture.read(frame);
        }

        bool readNextFrame(Mat& frame)
        {
            if(images.size() == 0)
            {
                return capture.read(frame);
            }
            else
            {
                if(itImg != images.end())
                {
                    frame = imread(*itImg);
                    itImg++;
                    return frame.data != 0;
                }
                else
                {
                    return false;
                }
            }
        }

    public:
        VidewProcessor() : callIt(true), delay(0),
                fnumber(0), stop(false), frameToStop(-1) {}
        
        void setFrameProcessor(void (*frameProcessingCallback) (Mat&, Mat&))
        {
            process = frameProcessingCallback;
        }

        bool setInput(string filename)
        {
            fnumber = 0;
            capture.release();
            images.clear();

            return capture.open(filename);
        }

        void displayInput(string wn)
        {
            windowNameInput = wn;
            namedWindow(windowNameInput);
        }

        void displayOutput(string wn)
        {
            windowNameOutput = wn;
            namedWindow(windowNameOutput);
        }

        void dontDisplay()
        {
            destroyWindow(windowNameInput);
            destroyWindow(windowNameOutput);
            windowNameInput.clear();
            windowNameOutput.clear();
        }

        void run()
        {
            Mat frame;
            Mat output;

            if(!isOpened())
                return;

            stop = false;
            while(!isStopped())
            {
                if(!readNextFrame(frame))
                    break;
                if(windowNameInput.length() != 0)
                    imshow(windowNameInput, frame);
                if(callIt)
                {
                    process(frame, output);
                    fnumber++;
                }
                else
                {
                    output = frame;
                }
                if(windowNameOutput.length() != 0)
                    imshow(windowNameOutput, output);

                if(delay >= 0 && waitKey(delay) >= 0)
                    stopIt();
                if(frameToStop >= 0 && getFrameNumber() == frameToStop)
                    stopIt();
            }
        }

        void stopIp()
        {
            stop = true;
        }

        bool isStopped()
        {
            return stop;
        }

        bool isOpened()
        {
            capture.isOpened() || !images.empty();
        }

        void setDelay(int d)
        {
            delay = d;
        }

        void callProcess()
        {
            callIt = true;
        }

        void dontCallProcess()
        {
            callIt = false;
        }

        void stopAtFrameNo(long frame)
        {
            frameToStop = frame;
        }

        long getFrameNumber()
        {
            long fnumber = static_cast<long>(capture.get(CV_CAP_PROP_POS_FRAMES));
            return fnumber;
        }

        bool setInput(const vector<string>& imgs)
        {
            fnumber = 0;
            capture.release();
            images = imgs;
            itImg = images.begin();
            return true;
        }
}

