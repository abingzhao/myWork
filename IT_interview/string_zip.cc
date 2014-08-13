#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
const int LEN = 256;

void string_zip(const char *in_ptr, char *out_ptr)
{
    if(NULL == in_ptr || NULL == out_ptr)
        return ;
    int length = strlen(in_ptr);
    if(length<1)
        return ;
    int same_count = 1;
    int out_count = 0;
    char first = in_ptr[0];
    for (int i = 1; i <= length; ++i)
    {
        if(in_ptr[i] == first)
            ++same_count;
        else if(in_ptr[i] != first)
        {
            out_ptr[out_count++] = first;
            sprintf(&out_ptr[out_count++],"%d",same_count);
            same_count = 1;
            first = in_ptr[i];
        }
        if(in_ptr[i] == ' ')
        {
            while(in_ptr[i]==' '){++i;}
            first = in_ptr[i];
            same_count = 1;
            out_ptr[out_count++] = ' ';
        }
    }
}

int main(int argc, char const *argv[])
{
    char in[LEN];
    char out[LEN];
    std::cin.getline(in,LEN);
    string_zip(in,out);
    std::cout<<out<<std::endl;
    std::cout<<"Have Done!"<<std::endl;
    return 0;
}
