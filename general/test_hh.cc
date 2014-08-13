#include <iostream>

int main(int argc, char const *argv[])
{
    char *aa = "hello World!";
    std::cout<<aa<<std::endl;    
    aa[0] = 'H';
    return 0;
}