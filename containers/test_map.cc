#include <boost/foreach.hpp>
#include <iostream>
#include <map>
#include <algorithm>
typedef std::pair<const int, int>  i_2_i;

void print_map(const i_2_i& v)
{
    std::cout<<v.second<<std::endl;
}

int main(int argc, char const *argv[])
{
    std::map<int, int> square;
    for (int i = 0; i < 5; ++i)
    {
        square[i] = i*i;
    }   
    for_each(square.begin(),square.end(),print_map);
    
    BOOST_FOREACH(i_2_i &v,square)
    {
        int k = v.first;
        std::cout<<square[k]<<std::endl;
    } 
    std::cout<<"Have Done!"<<std::endl;
    return 0;
}
