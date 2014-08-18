#ifndef HAVE_CODETIMING_H
#define HAVE_CODETIMING_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>

namespace pt = boost::posix_time;
class CodeTiming
{
private:
    pt::ptime startTime;
    pt::time_duration timeDur;
public:
    CodeTiming():startTime(pt::microsec_clock::universal_time()){}
    ~CodeTiming(){}
    void Start()
    {
        startTime = pt::microsec_clock::universal_time();
    }
    void EndAndPrint(const char *msg)
    {
        timeDur = pt::microsec_clock::universal_time() - startTime;
        std::cout<<"\n\tRun "<<msg<<" Takes :"
                 <<timeDur.total_seconds()
            +(double)timeDur.fractional_seconds()/pt::time_duration::ticks_per_second()<<"s"<<std::endl;

    }
    
};


#endif/*HAVE_CODETIMING_H*/