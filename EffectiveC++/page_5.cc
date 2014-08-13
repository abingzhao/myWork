#include <iostream>
class A
{
public:
    A();
    ~A();
};
class B
{
public:
    explicit B(int x=0,bool b = true);
    ~B(){}
//private:
    int x;
    bool b;
};
B::B(int x,bool b)
{
    this->x = x;
    this->b = b;
}
class C
{
public:
    explicit C(int x){ this->x=x;}
    ~C(){}
    
//private:
    int x;
    static const int LEN = 5;
    int score[LEN];
    void print_f(void)
    {
        std::cout<<"LEN = "<<LEN<<"\n";
    }
};
//const int C::LEN = 5;
void do_somthing(B b_obj)
{
    std::cout<<"B.x="<<b_obj.x<<";B.b="<<b_obj.b<<std::endl;
}
int main()
{
    B b_obj1;
    do_somthing(b_obj1);
    C c_obj1(0);
    c_obj1.print_f();
    std::cout<<"sizeof(c_obj1.score[])="<<sizeof(sizeof(c_obj1.score))<<"\n";
    std::cout<<bool(5!=0)<<"\n";
    std::cout<<"Have Done!\n";
    return 0;
}