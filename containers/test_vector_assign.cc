#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/foreach.hpp>
#include <iostream>
using namespace std;
int main()
{
    int len = 50;
    namespace pt = boost::posix_time;
    pt::ptime time_now = pt::microsec_clock::universal_time();
    for (int i = 0; i < len; ++i)
    {
        std::vector<std::vector<std::vector<int> > > v;
        v.assign(len,std::vector<std::vector<int> > (len,std::vector<int> (len,0)));
        BOOST_FOREACH(vector<std::vector<int> > &v1,v)
        {
            BOOST_FOREACH(std::vector<int>  &a,v1)
            {
                BOOST_FOREACH(int &b,a)
                    b=10;
            }
        }
        
    }
    pt::ptime time_end = pt::microsec_clock::universal_time();
    pt::time_duration time_dur = time_end - time_now;
    std::cout<<"Total time is :"<<time_dur.total_seconds()+(double)time_dur.fractional_seconds()/pt::time_duration::ticks_per_second()<<"s.\n";
    int a;
    cin>>a;
    std::vector<std::vector<std::vector<int> > > v0;
    v0.assign(len,std::vector<std::vector<int> > (len,std::vector<int> (len,0)));
    pt::ptime time_now0 = pt::microsec_clock::universal_time();
    for (int i = 0; i < len; ++i)
    {
        len = 10;
        v0.assign(len,std::vector<std::vector<int> > (len,std::vector<int> (len,0)));
        BOOST_FOREACH(std::vector<std::vector<int> > &c,v0)
        {
            BOOST_FOREACH(vector<int> &v1,c)
            {
                BOOST_FOREACH(int &a,v1)
                {
                    a = 10;
                }
            }
        }
        
    }
    pt::ptime time_end0 = pt::microsec_clock::universal_time();
    pt::time_duration time_dur0 = time_end0 - time_now0;
    std::cout<<"Total time is :"<<time_dur0.total_seconds()+(double)time_dur0.fractional_seconds()/pt::time_duration::ticks_per_second()<<"s.\n";

    std::cout<<"Have Done \n";
    return 0;
}