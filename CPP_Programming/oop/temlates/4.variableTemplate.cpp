#include <iostream>
using namespace std;

template <typename T> T pi = T(3.14159);

int main()
{
    cout<<"PI as int:"<< pi<int> <<endl;
    cout<<"pi as double:"<< pi<double> <<endl;
    cout<<"pi as float:"<< pi<float> <<endl;
    return 0;
}
