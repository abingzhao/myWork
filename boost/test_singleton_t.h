#ifndef TEST_SINGLETON_T_H
#define TEST_SINGLETON_T_H
#include <iostream>
#include <boost/noncopyable.hpp>

class test_singleton_t : public boost::noncopyable 
{
public:
    static test_singleton_t* instance()
    {
        // if (NULL == p_singleton)
        //      p_singleton = new test_singleton_t();
        static test_singleton_t singleton_t;
        return &singleton_t;
    }
    void printf_num(void);
    // {
    //     std::cout<<"subf_num="<<subf_num<<";frame_num="<<frame_num<<"\n";
    // }

private:
    test_singleton_t(){subf_num = 0;frame_num = 0;std::cout<<__func__<<"\n";}
    ~test_singleton_t(){std::cout<<__func__<<"\n";}
    // static test_singleton_t* p_singleton;
    int subf_num;
    int frame_num;
    void set_subf(int subf_num){this->subf_num=subf_num;}
    void set_fr_num(int frame_num){this->frame_num=frame_num;}
    friend class tx;
};

void
test_singleton_t::printf_num(void)
{
    std::cout<<"subf_num="<<subf_num<<";frame_num="<<frame_num<<"\n";
}
class tx
{
public:
    // singleton_t = test_singleton_t::instance();
    tx(int subf_num =0 ,int frame_num = 0){
        this->subf_num=subf_num;
        this->frame_num=frame_num;
    }
    ~tx(){}
    void set_param(int subf=0,int fr=0){
        
        if(subf==0)
            test_singleton_t::instance()->set_subf(subf_num);
        if(fr==0)
            test_singleton_t::instance()->set_fr_num(frame_num);
        else
        {
            test_singleton_t::instance()->set_subf(subf);
            test_singleton_t::instance()->set_fr_num(fr);
        }
        
    }
    void printf_num(){
        std::cout<<__func__<<":subf_num="<<subf_num<<";frame_num="<<frame_num<<"\n";

    }
private:
    int subf_num;
    int frame_num;
    // test_singleton_t *singleton_t
};

#endif