#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <ctime> 

//============================================================================//
class sort_seq
{
public:
    typedef boost::shared_ptr<sort_seq> sptr;//定义该类的智能指针
    static sptr make(size_t leng){ return sptr(new sort_seq(leng));}
    sort_seq(size_t leng = 10)
     :  len(leng)
       // ,impl(this)
     {
        // std::cout<<__func__<<std::endl;
        seq = (int*)malloc(sizeof(int)*len);
        memset(seq,0,sizeof(int)*len);
    }
    ~sort_seq(){
        // std::cout<<__func__<<std::endl;
        if(NULL!=seq)
            free(seq);
    }
    void swap_class(sort_seq & other)
    {
        using std::swap;
        swap(seq,other.seq);
        swap(len,other.len);
        // swap(impl,other.impl);
    }
    int * get_seq()
    {
        return seq;
    }
    size_t & get_len()
    {
        return len;
    }
    void show_element()
    {
        for (size_t i = 0; i < len; ++i)
        {
            std::cout<<seq[i]<<"\t";
            if(i%10==9)
                std::cout<<std::endl;
                        
        }
    }
private:
    int * seq;
    size_t len;
    // sort_seq *impl;
} ;
//============================================================================//
namespace pt = boost::posix_time;

class run_time
{
public:
    typedef boost::shared_ptr <run_time> sptr;
    static sptr make(size_t leng){return run_time::sptr(new run_time(leng));}
    run_time(size_t leng)
    :  start_time(pt::microsec_clock::universal_time())
     , pro_name(" ")
     , len(leng)
    {
        time_dur = pt::microsec_clock::universal_time() - start_time;
    }
    ~run_time(){}
    void start(){ start_time = pt::microsec_clock::universal_time();}
    void end()  { time_dur   = pt::microsec_clock::universal_time() - start_time;}
    void show_time()
    {
        std::cout<<"Run "<<pro_name<<" to sort "<<len<<" elements need "
            <<time_dur.total_seconds()+(double)time_dur.fractional_seconds()/pt::time_duration::ticks_per_second()
            <<"s!"<<std::endl;
    }
    void set_name(std::string name){ pro_name = name;}
private:
    pt::ptime         start_time;
    pt::time_duration time_dur;
    std::string       pro_name;
    size_t            len;
};
//============================================================================//
typedef enum {
    UP_ORDERED = 0,
    DOWN_ORDERED,
    SAME_SRAND,
    RANDOM,
} seq_type;
void fill_rand_seq(sort_seq::sptr ss, seq_type st)
{
    if(NULL == ss->get_seq() || 0 == ss->get_len())
        throw std::runtime_error("Invalid data length");
    size_t len = ss->get_len();
    int * seq = ss->get_seq();
    switch(st)
    {
        case UP_ORDERED:
        {
            for (size_t i = 0; i < len; ++i)
                seq[i] = i+1;
            break;
        }
        case DOWN_ORDERED:
        {
            for (size_t i = 0; i < len; ++i)
                seq[i] = len - i;
            break;
        }
        case SAME_SRAND:
        {
            srand(0);
            int max_value = 100;
            for (size_t i = 0; i < len; ++i)
            {
                seq[i]= rand() % max_value;
            }
            break;
        }
        case RANDOM:
        {
            srand(time(NULL));
            int max_value = 100;
            for (size_t i = 0; i < len; ++i)
            {
                seq[i]= rand() % max_value;
            }
            break;
        }
        default:
        {
            srand(time(NULL));
            int max_value = 100;
            for (size_t i = 0; i < len; ++i)
            {
                seq[i]= rand() % max_value;
            }
            break;
        }
    }
    
}

static long swap_count = 0;
void swap (int &vara, int &varb)
{
    // ++swap_count;
    // vara ^= varb;
    // varb ^= vara;
    // vara ^= varb;
    int temp = vara;
    vara = varb;
    varb = temp;
}
void is_ordered(sort_seq::sptr ss,bool up_order)
{
    if(NULL == ss->get_seq() || 0 == ss->get_len())
        return;
    size_t len = ss->get_len();
    int * seq  = ss->get_seq();
    bool ordered = true;
    if(up_order)
    {
        for (int i = 0; i < len-1; ++i)
        {
            if(seq[i] > seq[i+1])
                ordered = false;
        }
    }
    else
    {
        for (int i = 0; i < len-1; ++i)
        {
            if(seq[i] < seq[i+1])
                ordered = false;
        }
    }
    if(ordered)
        std::cout<<"The seq in SS is ORDERED!"<<std::endl;
    else
        std::cout<<"The seq in SS is NOT ORDERED!"<<std::endl;
}
//============================================================================//
// Bubble Sort
void bubble_classic(sort_seq::sptr ss, run_time::sptr rt)
{
    swap_count = 0;
    if(NULL == ss->get_seq() || 0 == ss->get_len())
        return;
    size_t len = ss->get_len();
    int * seq  = ss->get_seq();
    rt->start();
    for (size_t i = 0; i < len; ++i)
    {
        for (size_t j = len-1; j > i; --j)
        {
            if(seq[j]<seq[j-1])
                swap(seq[j],seq[j-1]);
        }
    }
    rt->end();
    rt->show_time();
    is_ordered(ss,true);
}
void bubble_kindof(sort_seq::sptr ss, run_time::sptr rt)
{
    rt->start();
    swap_count = 0;
    if(NULL == ss->get_seq() || 0 == ss->get_len())
        return;
    size_t len = ss->get_len();
    int * seq  = ss->get_seq();
    for (size_t i = 0; i < len; ++i)
    {
        for(size_t j = i+1; j < len;++j)
        {
            if(seq[i]<seq[j])
                swap(seq[i],seq[j]);
        }
    }
    rt->end();
    rt->show_time();
    is_ordered(ss,true);
}
void bubble_with_flag(sort_seq::sptr ss, run_time::sptr rt)
{
    rt->start();
    swap_count = 0;
    if(NULL == ss->get_seq() || 0 == ss->get_len())
        return;
    size_t len = ss->get_len();
    int * seq  = ss->get_seq();
    bool exchanged =false;
    for (size_t i = 0; i < len; ++i)
    {
        for (size_t j = len-1; j > i; --j)
        {
            if(seq[j]<seq[j-1])
            {
                swap(seq[j],seq[j-1]);
                exchanged = true;
            }
        }
        if(!exchanged)
        {
            rt->end();
            return;
        }
    }
    rt->end();
    rt->show_time();
    is_ordered(ss,true);
}
void bubble_dual_direct(sort_seq::sptr ss, run_time::sptr rt)
{
    rt->start();
    swap_count = 0;
    if(NULL == ss->get_seq() || 0 == ss->get_len())
        return;
    size_t len = ss->get_len();
    int * seq  = ss->get_seq();
    bool exchanged =false;
    for (size_t i = 0; i < len; ++i)
    {
        for(size_t j = len-1; j > i; --j)
        {
            if(seq[j] < seq[j-1])
            {
                exchanged = true;
                swap(seq[j],seq[j-1]);
            }
        }
        for(size_t j = 0; j < i;++j)
        {
            if(seq[j] > seq[j+1])
            {
                exchanged = true;
                swap(seq[j],seq[j+1]);
            }
        }
        if(!exchanged)
        {
            rt->end();
            return;
        }
    }
    rt->end();
    rt->show_time();
    is_ordered(ss,true);
}
//============================================================================//
void select_sort(sort_seq::sptr ss, run_time::sptr rt)
{
    rt->start();
    swap_count = 0;
    if(NULL == ss->get_seq() || 0 == ss->get_len())
        return;
    size_t len = ss->get_len();
    int * seq  = ss->get_seq();
    for (size_t i = 0; i < len; ++i)
    {
        size_t min_idx = i;
        for(size_t j = len-1; j > i; --j)
        {
            if(seq[min_idx] > seq[j])
                min_idx = j;
        }
        if(min_idx != i)
            swap(seq[min_idx],seq[i]);
    }
    rt->end();
    rt->show_time();
    is_ordered(ss,true);
}
//============================================================================//
void insertion_sort(sort_seq::sptr ss, run_time::sptr rt)
{
    rt->start();
    swap_count = 0;
    if(NULL == ss->get_seq() || 0 == ss->get_len())
        return;
    size_t len = ss->get_len();
    int * seq  = ss->get_seq();

    int temp = seq[0];
    for(size_t i = 1; i < len; ++i)
    {
        if(seq[i]<seq[i-1])//如果序列是倒序的，那么有无次条件判断不影响。
                           //但是如果序列本身是正序的，加了此条件后下面语句不在执行
        {
            temp = seq[i];
            for (int j = i-1;  ; --j)
            {
                if(temp < seq[j] && j>=0)
                {
                    seq[j+1] = seq[j];
                    continue;
                }
                else
                {
                    seq[j+1] = temp;
                    break;
                }
            }
        }
    }
    
    rt->end();
    rt->show_time();
    is_ordered(ss,true);
}
//============================================================================//
int partition(int *seq, int low, int high)
{
    int ref_val = seq[low];
    while(low<high)
    {
        while( low<high && seq[high]>=ref_val )
            --high;
        swap(seq[low],seq[high]);
        while( low<high && seq[low]<=ref_val)
            ++low;
        swap(seq[low],seq[high]);
    }
    return low;
}
void quick_sort_impl(int *seq, int low, int high)
{
    if(low < high)
    {
        int q = partition(seq,low,high);
        quick_sort_impl(seq,low,q-1);
        quick_sort_impl(seq,q+1,high);
    }
}
void quick_sort(sort_seq::sptr ss, run_time::sptr rt)
{
    rt->start();
    swap_count = 0;
    if(NULL == ss->get_seq() || 0 == ss->get_len())
        return;
    size_t len = ss->get_len();
    int * seq  = ss->get_seq();

    quick_sort_impl(seq,0,len-1);
    
    rt->end();
    rt->show_time();
    is_ordered(ss,true);
}
//============================================================================//
