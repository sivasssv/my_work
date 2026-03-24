#include <iostream>
using namespace std;

class math
{
    public:
        void add (int a, int b)
        {
            cout << "Interger sum = " << a+b << endl;
        }

        void add (double a, double b)
        {
            cout << "float sum = " << a+b << endl;
        }
};

int main()
{
    math sum;

    sum.add(5, 6);
    sum.add(5.6, 6.6);

    return 0;
}
