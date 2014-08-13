#include <iostream>
#include <boost/typeof/typeof.hpp>
#include <boost/assign.hpp>
#include <iterator>
#include <algorithm>
int main(int argc, char const *argv[])
{
    using namespace boost::assign;
    std::vector<int> v;
    BOOST_AUTO(vc, v.capacity());
    v += 1,2,3,4,5,6,7,9,0;
    vc = v.capacity();
    std::cout<<vc<<std::endl;
    

    copy(v.begin(),v.end(),std::ostream_iterator<int>(std::cout,", "));
    std::cout<<std::endl;

    std::list<std::string> l;
    push_front(l)("CPP")("CXX")("JAVA")("Python");
    copy(l.begin(),l.end(),std::ostream_iterator<std::string>(std::cout,"  "));
    std::cout<<std::endl;
    std::map<int ,std::string> m ;
    insert(m)(0,"Zero")(1,"One")(2,"Two");
    // copy(m.begin().first,m.end().first,std::ostream_iterator<int>(std::cout,"  "));
    std::cout<<std::endl;
    
    return 0;
}