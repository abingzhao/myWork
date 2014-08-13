// constructing bitsets
#include <iostream>       // std::cout
#include <cstring>         // std::string

int main ()
{
    char a[] = "C++";
    std::cout<<"sizeof(a)="<<sizeof(a)<<"\tstrlen(a)="<<strlen(a)<<"\ta="<<a<<std::endl;    
    char b[] = {'C','+','+'};
    std::cout<<"sizeof(b)="<<sizeof(b)<<"\tstrlen(b)="<<strlen(b)<<"\tb="<<b[0]<<b[1]<<b[2]<<std::endl;    

    return 0;
}