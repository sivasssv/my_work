#include <iostream>
using namespace std;

template <typename T> class Number
{
    public:
        T x;
        T y;

        Number(T v1, T v2): x(v1), y(v2){}

        void getValues()
        {
            cout << x << " " << y;
        }
};

int main()
{
    Number<int> intNum(4, 6);
    Number<double> doubleNum(5.5, 7.8);

    intNum.getValues();
    cout<<endl;
    doubleNum.getValues();
    return 0;
}
