#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
    vector<string> algorithms;
    Algorithm::getList(algorithms);
    cout << "Algorithms: " << algorithms.size() << endl;
    for(int i = 0; i < algorithms.size(); i++)
        cout << algorithms[i] << endl;

    return 0;
}
