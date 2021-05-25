#include "timer.hpp"
#include "Vector.hpp"

#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    Vector<int> a = { 0, 1, 2 };
    Vector<int> b = { 0, 1, 2 };
    Vector<int> c = { 1, 2 };

    cout<<"a == b: "<<(a==b)<<endl;
    cout<<"a == c: "<<(a==c)<<endl;
    cout<<"a != b: "<<(a!=b)<<endl;
    cout<<"a != c: "<<(a!=c)<<endl;
    cout<<"a < b: "<<(a<b)<<endl;
    cout<<"a < c: "<<(a<c)<<endl;
    cout<<"a <= b: "<<(a<=b)<<endl;
    cout<<"a <= c: "<<(a<=c)<<endl;
    cout<<"a > b: "<<(a>b)<<endl;
    cout<<"a > c: "<<(a>c)<<endl;
    cout<<"a >= b: "<<(a>=b)<<endl;
    cout<<"a >= c: "<<(a>=c)<<endl;

    cout<<"0 elementas: "<<a.at(0)<<endl;
    cout<<"1 elementas: "<<a.at(1)<<endl;
    cout<<"2 elementas: "<<a.at(2)<<endl;

    cout<<"a size: "<<a.size()<<endl;

    cout<<"a.begin() ir elementai po to: "<<*(a.begin())<<*(a.begin()+1)<<*(a.begin()+2)<<endl;

    a.push_back(4);
    a.push_back(6);
    for (int i = 0; i<a.size(); i++)
    {
        cout<<"a "<<i<<" elementas: "<<a[i]<<endl;
    }
}