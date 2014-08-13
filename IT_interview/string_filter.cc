#include <iostream>
#include <vector>
#include <cstring>
void string_filter(const char *in_ptr, char *out_ptr)
{
    if(NULL == in_ptr || NULL == out_ptr)
        return;
    int len = strlen(in_ptr);
    std::vector<int> pos_flag(26,0);
    int pos = 0;
    int out_idx = 0;
    for (int i = 0; i < len; ++i)
    {
        pos = in_ptr[i] - 'a';
        if(in_ptr[i] == ' ')
        {
            memset(&pos_flag[0],0,sizeof(pos_flag[0])*pos_flag.size());
            out_ptr[out_idx++] = ' ';
            continue;
        }
        if(pos_flag[pos] == 0)
        {
            ++pos_flag[pos];
            out_ptr[out_idx++] = in_ptr[i];
        }
    }
}

int main(int argc, char const *argv[])
{
    char str[256];
    char out[256];
    std::cin.getline (str,256);
    string_filter(str,out);
    std::cout<<out<<std::endl;
    // std::cout<<str.size()<<"\t"<<sizeof(str)<<std::endl;
    std::cout<<"Have Done!"<<std::endl;
    return 0;
}
