#include <iostream>
using namespace std;

template <typename T1, typename T2, typename T3> class Number
{
    public:
        T1 x;
        T2 y;
        T3 z;

        Number(T1 v1, T2 v2, T3 v3): x(v1), y(v2), z(v3){}

        void getValues()
        {
            cout << x << " " << y << " "<< z;
        }
};

int main()
{
    Number<int, double, string> idsNum(4, 6.5, "siva");
    Number<char, float, bool> cfbNum('A', 7.86f, true);

    idsNum.getValues();
    cout<<endl;
    cfbNum.getValues();

    return 0;
}
