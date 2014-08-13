#include "sort_algorithm.h"

int main(int argc, char const *argv[])
{
    // size_t len = 10;
    size_t len = 200000;

    seq_type st = SAME_SRAND;
    sort_seq::sptr ss = sort_seq::make(len);
    run_time::sptr rt = run_time::make(len);
    // try
    // {
        // fill_rand_seq(ss,st);
    // }
    // catch(std::runtime_error re)
    // {
    //     std::cout<<ss.get_len()<<std::endl;
    //     std::cout<<re.what()<<std::endl;
    //     sort_seq ts(10);
    //     ss.swap_class(ts);
    //     fill_rand_seq(ss,st);
    // }
    // rt->set_name("bubble_classic");    
    // fill_rand_seq(ss,st);
    // bubble_classic(ss,rt);
    // // ss->show_element();

    // rt->set_name("bubble_kindof");    
    // fill_rand_seq(ss,st);
    // bubble_kindof(ss,rt);

    // rt->set_name("bubble_with_flag");    
    // fill_rand_seq(ss,st);
    // bubble_with_flag(ss,rt);

    rt->set_name("select_sort");    
    fill_rand_seq(ss,st);
    select_sort(ss,rt);
    // ss->show_element();

    rt->set_name("insertion_sort");    
    fill_rand_seq(ss,st);
    insertion_sort(ss,rt);
    // ss->show_element();
    
    rt->set_name("quick_sort");    
    fill_rand_seq(ss,st);
    quick_sort(ss,rt);
    // ss->show_element();
    std::cout<<"Have Done!"<<std::endl;
    return 0;
}