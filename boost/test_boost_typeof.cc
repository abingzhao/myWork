#include "test_boost.h"
#include <boost/make_shared.hpp>
#include <boost/typeof/typeof.hpp>
#include BOOST_TYPEOF_INCREMENT_REGISTRATION_GROUP()
#include <iostream>
#include <utility>
#include <memory>
namespace t{
    struct test_boost_typeof
    {
        int a;
        int b;
    };
}
BOOST_TYPEOF_REGISTER_TYPE(t::test_boost_typeof)

int main(int argc, char const *argv[])
{
    BOOST_AUTO(x, std::make_pair("test",t::test_boost_typeof()));
    std::cout << GetClearName(typeid(x).name()) << std::endl;
    x.second.a = 10;
    x.second.b = 10;
    std::cout << x.second.a << std::endl; 
    
    std::cout<<std::endl;
    BOOST_AUTO(p, boost::make_shared<int>(5));
    std::cout << GetClearName(typeid(p).name()) << std::endl;


    return 0;
}