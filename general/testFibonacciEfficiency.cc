#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <cassert>
using namespace std;

long FibonacciRecursion(int n)
{
    assert(n>=0);
    if(n <= 1)
        return static_cast<long>(n);
    else
        return FibonacciRecursion(n-1) + FibonacciRecursion(n-2);
}
long FibonacciForCyc(int n)
{
    if(n <= 1)
        return static_cast<long>(n);
    long curFibonacci    = 0;
    long preFibonacci    = 1;
    long prePreFibonacci = 0;
    for (int i = 2; i <= n; ++i)
    {
        curFibonacci    = preFibonacci + prePreFibonacci;
        prePreFibonacci = preFibonacci;
        preFibonacci    = curFibonacci;
    }
    return curFibonacci;
}

int main(int argc, char const *argv[])
{
    int  n = 40;
    namespace pt = boost::posix_time;
    pt::ptime start = pt::microsec_clock::universal_time();
    long res1 = FibonacciRecursion(n);
    pt::time_duration dd = pt::microsec_clock::universal_time() - start;
    cout<<" Cost " <<dd.total_seconds()+(double)dd.fractional_seconds()/pt::time_duration::ticks_per_second()<<endl;

    /*pt::ptime */start = pt::microsec_clock::universal_time();
    long res2 = FibonacciForCyc(n);
    /*pt::time_duration */dd = pt::microsec_clock::universal_time() - start;
    cout<<" Cost " <<dd.total_seconds()+(double)dd.fractional_seconds()/pt::time_duration::ticks_per_second()<<endl;
    assert(res1 == res2);
    cout<<"Main Finished!"<<endl;
    return 0;
}