#include <iostream>

using namespace std;

class ABC{
    public:
        ABC()
        {
            cout << "abc()" << endl;
        }

        ABC(int x)
        {
            cout << "abc(int " << x << ")" << endl;
        }
};

int main()
{
    ABC aaa;
    ABC xxx(1111);
}
