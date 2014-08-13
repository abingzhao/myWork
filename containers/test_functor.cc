/**
 * test The usage of functor
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
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

template <typename T>
void fill_vec_with_rand(T& v, int first_pos, int end_pos)
{
    srand(time(0));
    assert(first_pos <= end_pos);
    for (int i = first_pos; i <= end_pos; ++i)
    {
        v.push_back(rand()%100);
        boost::this_thread::sleep(boost::posix_time::microseconds(100));
    }
}

void print_vec(const int& ele)
{
    cout.width(4);
    cout<<""<<ele;
}

template<typename T>
class sum
{
private:
    long _sum;
    long _num_count;
public:
    sum():_sum(0),_num_count(0)
    {}
    
    void operator () (T& ele)
    {
        _sum += static_cast<long>(ele);
        ++ _num_count;
    }
    operator double ()
    {
        return static_cast<double>(static_cast<double>(_sum) / static_cast<double>(_num_count));
    }
};
bool is_even(const int &ele)
{
    return ele%2 == 0;
}

int main(int argc, char const *argv[])
{
    // std::vector<int> v;
    list<int> v;
    fill_vec(v, 1 , 10);
    for_each(v.begin(),v.end(),print_vec);

    double sum_d = for_each(v.begin(),v.end(),sum<int>());

    cout<<"\nThe sum is: "<<sum_d<<endl;
    v.clear();
    fill_vec_with_rand(v,1,10);
    for_each(v.begin(),v.end(),print_vec);
    int num_of_even_ele = count_if(v.begin(),v.end(),is_even);
    cout<<"\nThe even num is: "<<num_of_even_ele<<endl;
    cout<<"\nDone! Normally exit."<<std::endl;
    return 0;
}