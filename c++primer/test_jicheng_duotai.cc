
#include <iostream>
#include <vector>
#include <boost/foreach.hpp>
using namespace std;

class base
{
public:
    base(){cout<<"Here IN base class,FUNC: "<<__func__<<"\n";}
    virtual ~base(){cout<<__func__<<"\n";}
    void print_m0() {cout<<__func__<<";Line "<<__LINE__<<"\n";}
    virtual void print_m(int default_v = 10) {
        cout<<__func__<<";Line "<<__LINE__<<";default_v="<<default_v<<"\n";
    }
protected:
    static const int a=10;
};
//=======================================================================
class son1 : public base
{
public:
    son1(int member)
    {
        this->member = member;
        cout<<"Here IN class son1,FUNC: "<<__func__<<"\n";
    }
    ~son1()
    {cout<<__func__<<"\n";}
    void print_m0() { member = 0;cout<<__func__<<";Line "<<__LINE__<<"\n";}
    void print_m(int default_v) {
        cout<<"Here IN class son1,FUNC: "<<__func__<<" and its member="<<member
            <<";default_v="<<default_v<<"\n";
    }
private:
    int member;
};
//=======================================================================
class son2 : public base
{
public:
    son2(int member)
    {
        this->member = member;
        cout<<"Here IN class son2,FUNC: "<<__func__<<"\n";
    }
    ~son2()
    {cout<<__func__<<"\n";}
    void print_m(int default_v) {
        cout<<"Here IN class son2,FUNC: "<<__func__<<" and its member="<<member
            <<";default_v="<<default_v<<"\n";
    }
private:
    int member;
};
//=======================================================================
class son3 : public base
{
public:
    son3(int member)
    {
        this->member = member;
        cout<<"Here IN class son3,FUNC: "<<__func__<<"\n";
    }
    ~son3()
    {cout<<__func__<<"\n";}
    void print_m(int default_v =5) {
        cout<<"Here IN class son3,FUNC: "<<__func__<<" and its member="<<member
            <<";default_v="<<default_v<<"\n";
    }
private:
    int member;
};
//=======================================================================

base * get_base_ptr(int i, int mem=6)
{
    switch (i)
    {
        case 1  : return new son1(mem);
        case 2  : return new son2(mem);
        default : return new son3(mem);
    }
}

int main()
{
    std::vector<base*> v;
    for (int i = 1; i <= 3; ++i)
    {
        v.push_back(get_base_ptr(i,i*i*i));
    }
    
    BOOST_FOREACH(base * &b,v)
    {
        // b->print_m0();
        b->print_m();
        if(b!=NULL)
            delete b;
    }
    // son3 s3(5);
    // s3.print_m();
    return 0;
}