
#include <iostream>
#include <algorithm>
#include <cassert>
#include <time.h>
#include <boost/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

template <typename T>
void fill_vec(T& v, int first_pos, int end_pos)
{
    assert(first_pos <= end_pos);
    for (int i = first_pos; i <= end_pos; ++i)
    {
        v.insert(v.end(),i*i);
    }
}

template <typename T,typename T1>
void fill_vec_with_rand(T& v, int first_pos, int end_pos)
{
    srand(time(0));
    assert(first_pos <= end_pos);
    for (int i = first_pos; i <= end_pos; ++i)
    {
        // srand(i);
        v.push_back(static_cast<T1>(rand()%10));
        boost::this_thread::sleep(boost::posix_time::microseconds(500));
    }
}

template<typename T>
void print_vec(const T& ele)
{
    // cout.width(4);
    cout<<ele<<", ";
}