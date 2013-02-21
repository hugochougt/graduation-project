#include <iostream>

using namespace std;

class abc{
    public:
        abc()
        {
            cout << "abc()" << endl;
        }

        abc(int x)
        {
            cout << "abc(int " << x << ")" << endl;
        }
};
