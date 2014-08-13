#include "../test_boost.h"
#include <boost/utility/result_of.hpp>
#include <boost/typeof/typeof.hpp>
#include <iostream>
#include <cmath>

using namespace boost;

double add_10(double a)
{
    return a+static_cast<double>(10);
}

template<typename T, typename T1>
typename result_of<T(T1)>::type call_func(T t,T1 t1)
{
    return t(t1);
}

int main(int argc, char const *argv[])
{
    typedef double (*Func)(double d);
    Func func = add_10;
    boost::result_of<Func(double)>::type x = func(9);
    std::cout << GetClearName(typeid(x).name()) << std::endl;

    BOOST_AUTO( y, call_func(func, 9));
    std::cout << GetClearName(typeid(y).name()) << std::endl;

    std::cout<<"\nHave Done!"<<std::endl;
    return 0;
}