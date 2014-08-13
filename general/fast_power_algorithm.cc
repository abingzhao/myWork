#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cmath>
using namespace std;

// return x^n
template <typename T>
T  fast_power(T x, T n)
{
    T y = 1;
    while (1)
    {
        T t = n % 2;
        n = n / 2;
        if(t == 1)
            y *= x;
        if(n == 0)
            break;
        x *= x;
    }
    return y;
}

int main(int argc, char const *argv[])
{
    double  times = 10000;
    double x = 0;
    double y = 0;
    namespace pt = boost::posix_time;
    pt::ptime time_now = pt::microsec_clock::universal_time();
    for (int i = 0; i < times; ++i)
    {
        x = fast_power(99,10);
    }
    pt::time_duration time_dur = pt::microsec_clock::universal_time() - time_now;


    std::cout<<"Total time is :"<<time_dur.total_seconds()+(double)time_dur.fractional_seconds()/pt::time_duration::ticks_per_second()<<"s.\n";
    pt::ptime time_now1 = pt::microsec_clock::universal_time();
    for (int i = 0; i < times; ++i)
    {
        y = pow(99,10);
    }
    pt::time_duration time_dur1 = pt::microsec_clock::universal_time() - time_now1;
    std::cout<<"Total time is :"<<time_dur1.total_seconds()+(double)time_dur1.fractional_seconds()/pt::time_duration::ticks_per_second()<<"s.\n";
    

    cout<<"Main Done!"<<endl;
    return 0;
}