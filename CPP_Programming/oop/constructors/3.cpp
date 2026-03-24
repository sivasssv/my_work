#include <iostream>
using namespace std;


class Point
{
    private:
         int &t;
    public:
        Point(int &x): t(x){}
        int getT() {return t;}
};


int main()
{
    int x = 20;
    Point t1(x);
    cout <<t1.getT()<< "\n";
    x = 30;
    cout <<t1.getT()<< "\n";

    return 0;
}
