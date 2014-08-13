#include <iostream>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

int main(int argc, char const *argv[])
{
    namespace pt = boost::posix_time;
    std::vector<std::vector<int> > v;
    pt::ptime time_now = pt::microsec_clock::universal_time();
    for (int i = 0; i < 100; ++i)
    {
        v.assign(1000,std::vector<int> (1000,0));
    }

    pt::ptime time_end = pt::microsec_clock::universal_time();
    pt::time_duration time_dur = time_end - time_now;
    std::cout<<"assigned time is :"<<time_dur.total_seconds()
            +(double)time_dur.fractional_seconds()/pt::time_duration::ticks_per_second()<<"s.\n";
    
    std::vector<std::vector<int> > v1;
    pt::ptime time_now1 = pt::microsec_clock::universal_time();
    for (int i = 0; i < 100; ++i)
    {
        v1.resize(1000,std::vector<int> (1000,0));
    }

    pt::ptime time_end1 = pt::microsec_clock::universal_time();
    pt::time_duration time_dur1 = time_end1 - time_now1;
    std::cout<<"resize time is :"<<time_dur1.total_seconds()
            +(double)time_dur1.fractional_seconds()/pt::time_duration::ticks_per_second()<<"s.\n";
    std::cout<<v1[56][77]<<"\n";
    cout<<"Have Done\n";
    return 0;
}