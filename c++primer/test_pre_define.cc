#include "test_pre_define.h"
#include <iostream>

int main()
{
    char str[] = "Programming Language";
    std::cout<<"sizeof(str)="<<sizeof(str)<<";length(str)="<<sizeof(str)/sizeof(char)<<"\n";
    char c = ' ';
    for (int i=0; str[i] != '\0'; ++i)
    {
        c = str[i];
#ifndef UPPER_LETTER
        if(c >= 'A' && c <= 'Z')
            c += 32;
#else
        if(c >= 'a' && c <= 'z')
            c -= 32;
#endif
        std::cout<<c;
    }
    std::cout<<"\nHave Done!\n";
    return 0;
}