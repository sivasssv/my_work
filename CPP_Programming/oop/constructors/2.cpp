#include <iostream>
using namespace std;


class Point
{
    private:
        const int t;
    public:
        Point(int x): t(x){}
        int getT() {return t;}
};


int main()
{
    Point t1(10);
    cout <<t1.getT()<< "\n";
    return 0;
}
