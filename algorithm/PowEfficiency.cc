#include <iostream>
#include "../CodeTiming.h"
using namespace std;

/* Return m^n*/
long PowCyclic(long m,long n)
{
    if(n==0)
        return 1;
    long result = m;
    for (long i= 1; i < n; ++i)
    {
        result *= static_cast<long>(m);
    }
    return result;
}
long PowRecursion(long m, long n)
{
    if(n==0)
        return 1;
    if(n == 1)
        return m;
    if((n & 0x1) == 0)
        return PowRecursion(m*m, n/2);
    else
        return PowRecursion(m*m, n/2) * m;
}

int main(int argc, char const *argv[])
{
    cout<<PowCyclic(2,12)<<endl;
    cout<<PowRecursion(2,12)<<endl;
    cout<<"Main Done!"<<endl;
    return 0;
}