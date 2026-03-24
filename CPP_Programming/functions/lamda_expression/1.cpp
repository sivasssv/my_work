#include<iostream>
#include <vector>
using namespace std;


void print(vector<int> v)
{

    for(int x: v)
        cout << x << " ";
}

int main()
{
    vector<int> v1, v2;

    auto ByRef = [&](int m){
    
        v1.push_back(m);
        v2.push_back(m);
    };

    auto ByVal = [=](int m){
    
        vector<int> l_v1 = v1; 
        vector<int> l_v2 = v2; 
        l_v1.push_back(m);
        l_v2.push_back(m);
        cout << "Inside by val : ";
        print(l_v1);
        print(l_v2);
    };

    auto Mixed = [&v1, v2](int m){
     
        vector<int> l_v2 = v2; 
        v1.push_back(m);
        l_v2.push_back(m);
        cout << "Inside mixed : ";
        print(l_v2);
    };

    cout << "Initial vectors : " << endl;
    print(v1);
    print(v2);

    ByRef(20);
    ByVal(234);
    Mixed(10);


    cout << "After lamdas" << endl;
    cout << "v1:" ; print(v1);
    cout << "v2:" ; print(v2);

}
