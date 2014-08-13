#include <iostream>
#include <vector>
#include <string>
#include <boost/foreach.hpp>

int main(int argc, char const *argv[])
{
    std::vector<int> v(5,0);
    int j=1;
    BOOST_FOREACH(int &i,v)
    {

        i=j*j*j;
        j++;
    }
    BOOST_FOREACH(const int &i,v)
    {
        std::cout<<i<<"\t";
    }
    std::cout<<"\n";
    std::string str("Hello World!");
    BOOST_FOREACH(const char i,str)
    {
        std::cout<<i;
    }
    std::cout<<"\nHave Done!\n";
    return 0;
}