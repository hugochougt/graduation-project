#include "fish.h"

int main(int argc, char** argv)
{
    string filename = argv[1];

    FileStorage fs;
    fs.open(filename, FileStorage::READ);

    if(!fs.isOpened())
    {
        cout << "error" << endl;
        return -1;
    }

    int size = (int) fs["size"];
    cout << "Size: " << size << endl;

    Fish f;
    fs["No2"] >> f;
    cout << f.getArea() << endl;

    cout << f.getHistogram() << endl;
}
