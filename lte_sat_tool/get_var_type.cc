#include <iostream>
#include <cstring>
#include <vector>
#include <vector>
#include <list>
#include <cmath>
#include <typeinfo>
#include <boost/foreach.hpp>
using namespace std;
#include <cxxabi.h>
/**
 * g++编译器打印的类型名比较晦涩，vc编译器打印的类型名很清晰，参考这里。
 * 下面给出一个用g++打印清晰类型名的一个示例。
 */
const string GetClearName(const char* name)
{
    int status = -1;
    char* clearName = abi::__cxa_demangle(name, NULL, NULL, &status);
    const char* const demangledName = (status==0) ? clearName : name;
    std::string ret_val(demangledName);
    free(clearName);
    return ret_val;
}
class get_var_type
{
    
};
int main()
{
    // aaaa ua;
    unsigned int a= -10;
    size_t bb=a;
    time_t t;
    get_var_type aa;

    std::cout<<sizeof(long double )<<"\t"<< GetClearName(typeid(long double).name())<<"\n";

    int i;
    int * pi;
    std::cout << "int is: " << GetClearName(typeid(int).name()) << '\n';
    std::cout << "  i is: " << GetClearName(typeid(i).name()) << '\n';
    std::cout << " pi is: " << GetClearName(typeid(pi).name()) << '\n';
    std::cout << "*pi is: " << GetClearName(typeid(*pi).name()) << '\n';
    std::cout << "    is: " << GetClearName(typeid(aa).name()) << '\n';
    std::list<char> v;
    std::cout << "  v is: " << GetClearName(typeid(v).name()) << '\n';

    std::cout<<"Have Done!\n";
    return 0;
}
