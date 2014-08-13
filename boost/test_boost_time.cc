#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <ctime>
using namespace std;
timespec diff(timespec start, timespec end);


int main() 
{
    namespace pt = boost::posix_time;
    pt::ptime time_now = pt::microsec_clock::universal_time();
    int i=0;
    for (int i = 0; i < 100000; ++i)
    {
        std::cout<< ' ';
    }
    pt::ptime time_end = pt::microsec_clock::universal_time();

    pt::time_duration time_dur = time_end - time_now;


    std::cout<<"time_dur.total_seconds()="<<time_dur.total_seconds()<<"\n";
    std::cout<<"time_dur.fractional_seconds()="<<time_dur.fractional_seconds()<<"\n";
    std::cout<<"pt::time_duration::ticks_per_second()="<<pt::time_duration::ticks_per_second()<<"\n";
    std::cout<<"Total time is :"<<time_dur.total_seconds()+(double)time_dur.fractional_seconds()/pt::time_duration::ticks_per_second()<<"s.\n";
    std::cout<<"\ntime.h\n";
    




    timespec ts1={0},ts2={0}; 
    clock_gettime(CLOCK_MONOTONIC, &ts1);
    for (int i = 0; i < 100000; ++i)
    {
        int a=0;
    }
    clock_gettime(CLOCK_MONOTONIC, &ts2);

    cout<<diff(ts1,ts2).tv_sec<<":"<<diff(ts1,ts2).tv_nsec<<endl;



    std::cout<<"\n\nHave Done!\n";
    return 0;
}

timespec diff(timespec start, timespec end)
{
    timespec temp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}