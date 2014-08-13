#include <iostream>
#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/foreach.hpp>
int main()
{
    namespace pt = boost::posix_time;
    pt::ptime time_now = pt::microsec_clock::universal_time();
    pt::ptime time_end = pt::microsec_clock::universal_time();
    pt::time_duration time_dur = time_end - time_now;
    int N = 200*100;
    std::vector<int> v(10);
    time_now = pt::microsec_clock::universal_time();
    for (int i = 0; i < N; ++i)
    {
        int j=0;
        BOOST_FOREACH(int &vi,v)
        {
            vi = j * j++; 
        }
    }
    time_end = pt::microsec_clock::universal_time();
    time_dur = time_end - time_now;
    std::cout<<"BOOST_FOREACH takes "<<time_dur.total_seconds()<<"."<<time_dur.fractional_seconds()<<"s\n";
    
    BOOST_FOREACH(const int &vi,v)
    {
        std::cout<<vi<<"\t"; 
    }
    std::cout<<"\n";

    time_now = pt::microsec_clock::universal_time();
    for (int i = 0; i < N; ++i)
    {
        int j=0;
        for (std::vector<int>::iterator  iter=v.begin(); iter!=v.end(); ++iter)
        {
            *iter = j * j++;
        }
    }
    time_end = pt::microsec_clock::universal_time();
    time_dur = time_end - time_now;
    std::cout<<"vector iterator takes "<<time_dur.total_seconds()<<"."<<time_dur.fractional_seconds()<<"s\n";
    BOOST_FOREACH(const int &vi,v)
    {
        std::cout<<vi<<"\t"; 
    }
    std::cout<<"\n";

    time_now = pt::microsec_clock::universal_time();
    for (int i = 0; i < N; ++i)
    {
        int j=0;
        for (int m = 0; m < v.size(); ++m)
        {
            v[m] = j * j++;
        }
    }
    time_end = pt::microsec_clock::universal_time();
    time_dur = time_end - time_now;
    std::cout<<"for loop takes "<<time_dur.total_seconds()<<"."<<time_dur.fractional_seconds()<<"s\n";
    BOOST_FOREACH(const int &vi,v)
    {
        std::cout<<vi<<"\t"; 
    }
    std::cout<<"\n";


    std::cout<<"\nHave Done!\n";
    return 0;
}