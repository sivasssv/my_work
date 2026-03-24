#include <iostream>
using namespace std;


class A
{
    private:
         int count;
    public:
         A(int _x){count = _x;}
        int get()
        {
            return count;
        }
};

class B
{
    static A a;
    public:
    int get()
    {
        return a.get();
    }
};

A B::a(0);

int main()
{
    B b;
    cout << b.get();

    return 0;
}
