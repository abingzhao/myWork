#include <iostream>
#include <cstring>
#include "string_related.h"
int main(int argc, char const *argv[])
{
    string *str = new string();
    str->ss[0]='a';
    str->len ++;

    str->ss[1]='a';
    str->len ++;
    str->ss[2]='b';
    str->len ++;
    str->ss[3]='a';
    str->len ++;
    str->ss[4]='a';
    str->len ++;
    str->ss[5]='b';
    str->len ++;
    str->ss[6]='c';
    str->len ++;
    str->ss[7]='a';
    str->len ++;
    str->ss[8]='c';
    str->len ++;
    int nex[10];
    get_next(str,nex);
    std::cout<<(str->ss)<<std::endl;
    for (int i = 0; i < str->len; ++i)
    {
        std::cout<<nex[i]<<"\t";
    }
    std::cout<<std::endl;
    std::cout<<"Have Done!"<<std::endl;
    delete str;
    return 0;
}