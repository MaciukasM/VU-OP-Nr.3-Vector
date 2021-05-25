#include "timer.hpp"
#include "Vector.hpp"

#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    int n = 100000000; //testo dydis
    Timer t;

    Vector<int> v1; //mano Vector()
    int perkelimai1 = 0; //mano Vector()

    vector<int> v2; //iprastam vector()
    int perkelimai2 = 0; //iprastam vector()

    t.reset();
    for(int i = 0; i<n; i++)
    {
        if (v1.capacity() == v1.size()) perkelimai1++;
        v1.push_back(i);
    }
    cout<<"Mano vektoriaus laikas(su "<<n<<" elementu): "<<t.elapsed()<<endl;
    
    t.reset();
    for(int i = 0; i<n; i++)
    {
        if (v2.capacity() == v2.size()) perkelimai2++;
        v2.push_back(i);
    }
    cout<<"Iprasto vektoriaus laikas(su "<<n<<" elementu): "<<t.elapsed()<<endl;

    cout<<"\nMano vektoriaus atminties perkelimu skaicius: "<<perkelimai1<<endl;
    cout<<"Iprasto vektoriaus atminties perkelimu skaicius: "<<perkelimai2<<endl;
}