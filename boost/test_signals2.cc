#include <boost/signals.hpp>
#include <boost/random.hpp>
#include <boost/bind.hpp>
#include <iostream>
using namespace boost;
using namespace boost::signals;
class ring
{
public:
    typedef signal<void()> signal_t;
    typedef signal_t::slot_type slot_t;

    connection connect(const slot_t &s)
    {
        return alarm.connect(s);
    }

    void press()
    {
        std::cout<< "Ring alarm..."<<std::endl;
        alarm();
    }
private:
    signal_t alarm;
};
 
typedef variate_generator<rand48, uniform_smallint<> > bool_rand;
bool_rand g_rand(rand48(time(0)), uniform_smallint<>(0,100));

extern char const nurse1[] = "Mary";
extern char const nurse2[] = "Kate";

template<char const *name>
class nurse
{
private:
    bool_rand &rand;
public:
    nurse():rand(g_rand){}

    void action()
    {
        std::cout << name;
        if(rand() > 30)
            std::cout<<" wakeup and open door."<<std::endl;
        else
            std::cout<<" is sleeping..."<<std::endl;
    }
};

extern char const baby1[] = "Tom";
extern char const baby2[] = "Jerry";

template<char const *name>
class baby
{
private:
    bool_rand &rand;
public:
    baby():rand(g_rand){}

    void action()
    {
        std::cout << "Baby " << name;
        if(rand() > 50)
            std::cout<<" wakeup and crying loudly..."<<std::endl;
        else
            std::cout<<" is sleeping sweetly..."<<std::endl;
    }
};

class guest
{
public:
    void press(ring &r)
    {
        std::cout << "A guest press the ring." <<std::endl;
        r.press();
    }
};

int main(int argc, char* argv[])
{
    ring r;
    nurse<nurse1> n1;
    nurse<nurse2> n2;
    baby<baby1> b1;
    baby<baby2> b2;
    guest g;

    r.connect(bind(&nurse<nurse1>::action,n1));
    r.connect(bind(&nurse<nurse2>::action,n2));
    r.connect(bind(&baby<baby1>::action,b1));
    r.connect(bind(&baby<baby2>::action,b2));

    g.press(r);
    return 0;
}