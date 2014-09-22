#include <iostream>
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
bool IsPOwerOfFour(int inPut)
{
    while(inPut)
    {
        if(inPut == 1)
            return true;
        else
            inPut = inPut>>2;
    }
    return false;
}
int main(int argc, char const *argv[])
{
    cout << IsPOwerOfFour(16) << endl;
    // cout<<PowCyclic(2,12)<<endl;
    // cout<<PowRecursion(2,12)<<endl;
    int  a[] = {1,2,3,4,5,6};
    int *p = a;
    int **q = &p;
    cout << (*(p++)) << endl;
    cout << **q << endl;

    cout<<"Main Done!"<<endl;
    return 0;
}