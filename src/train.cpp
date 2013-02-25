#include <sstream>
#include "fish.h"

void help()
{
    cout << "Usage:" << endl;
    cout << "\ttrain <fishname> <image> [images..]" << endl;
}


int main(int argc, char** argv)
{
    if(argc < 3)
    {
        cout << "Too less argument!" << endl;
        help();
        return -1;
    }

    string fishName;
    fishName = argv[1];

    string outputFile = fishName + ".xml";

    FileStorage fs(outputFile, FileStorage::WRITE);
    int size = argc - 2;

    stringstream itoa;
    string ID;

    fs << "fishName" << fishName;
    fs << "size" << size;

    for(int i = 1; i <= size; i++)
    {
        string imgFile = argv[i + 1];
        Mat img = imread(imgFile, CV_LOAD_IMAGE_COLOR);
        if(!img.data)
        {
            cout << "Can't open image " << imgFile << endl;
            continue;
        }
        itoa << "No" << i;
        itoa >> ID;
        Fish fish(img);
        fish.featureDetect();
        fs << ID << fish;
        itoa.clear();
    }

    fs.release();

    cout << "Finished training." << endl;
    return 0;
}

