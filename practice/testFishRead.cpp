#include "fish.h"

int main()
{
    string filename = "uary.yml";

    FileStorage fs(filename, FileStorage::READ);

    FileNode node = fs["features"];

    Fish f;

    if(node.type() != FileNode::SEQ)
    {
        return -1;
    }

    FileNodeIterator it = node.begin(), itEnd = node.end();
    for(; it != itEnd; it++)
    {
        (Fish)*it;
    }

    return 0;
}
