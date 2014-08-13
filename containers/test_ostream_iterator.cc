#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
    int dim [] = {1,2,3,4,5,6,7,8,9};
    std::vector<int > v1;
    ostream_iterator<int> iter(cout,"\n");
    ostream_iterator<string> siter(cout,"\n");

    *iter = 22;
    *iter = 23;

    std::vector<string> v;
    v.push_back("Hello ");
    v.push_back("World! ");
    *siter = v[0];
    *siter = v[1];
    return 0;
}