#include <iostream>
#include <vector>
#include <cstdlib>
#include <boost/shared_ptr.hpp>
class test
{
public:
    typedef boost::shared_ptr<test> sptr; 
    static sptr make(int len) {return  test::sptr(new test(len));}
    test(int len){ length = len;std::cout<<"test Constructor!length="<<length<<"\n";}
    ~test(){ std::cout<<"test Deconstructor!length="<<length<<"\n";}
    void print_len(void){std::cout<<"len = "<<length<<"\n";}
private:
    int length;
};
class test2
{
public:
    test2(int len)
    {
        length = len;
        t1=test::make(len);
    }
    ~test2(){}
    void update_len(int len){
        length = len;
        std::cout<<__func__<<"line:"<<__LINE__<<":addr="<<t1<<"\n";
        t1=test::make(len);
        std::cout<<__func__<<"line:"<<__LINE__<<":addr="<<t1<<"\n";
    }
    void print_len()
    {
        t1->print_len();
    }
private:
    int length;
    test::sptr t1;
};
int main(int argc, char const *argv[])
{
    test::sptr t1;
    t1 = test::make(55);
    std::cout<<__func__<<"line:"<<__LINE__<<";t1.use_count()="<<t1.use_count()<<"\n";
    test2 t2(5);
    std::cout<<__func__<<"line:"<<__LINE__<<";t1.use_count()="<<t1.use_count()<<"\n";
    t2.update_len(6);
    std::cout<<__func__<<"line:"<<__LINE__<<";t1.use_count()="<<t1.use_count()<<"\n";
    t2.print_len();
    std::cout<<"\n\nHave Done!\n";
    return 0;
}