#include <iostream>
#include <cstring>
// #include <vector>
// #include <utility>

void string_filter(const char *in, char *out,int length)
{
    // char *buffer = (char*)malloc(sizeof(char)*length);
    out [0]=in[0];
    int out_len = 1;
    for (int i = 1; i < length; ++i)
    {
        bool is_in_v = false;
        for (int j =0; j<out_len;++j)
        {
            if(in[i] == out[j])
            {
                is_in_v = true;
                break;
            }
        }
        if(!is_in_v)
        {
            out[out_len] = in[i];
            ++out_len;
        }
    }
}

int main(int argc, char const *argv[])
{
    char a[]="aahelbloeo";
    std::cout<<a<<std::endl;
    char out[sizeof(a)];
    string_filter(a,out,sizeof(a));
    // std::cout<<out<<std::endl;
    // std::cout<<strlen(a)<<sizeof(out)<<std::endl;
    for (int i = 0; i < strlen(out); ++i)
    {
        if(out[i] != '\0')
            std::cout<<out[i];
        else
            break;
    }
    std::cout<<"\nHave Done\n";
    return 0;
}