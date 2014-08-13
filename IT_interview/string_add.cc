#include <iostream>
#include <cstring>
#include <cstdio>

bool valid_string(const char *in,int len)
{
    if(in[0]!= '-' && !((in[0]>='0')  &&  (in[0]<='9')))
    {
        return false;
    }
    for (int i = 0; i < len; ++i)
    {
        if(!(  (in[i]>='0')  &&  (in[i]<='9') ))
            return false;
    }
    return true;
}
void reverse_string(const char *in,char* reverse_out)
{
    int len  =strlen(in);
    reverse_out[len] = '\0';
    for (int i = len-1; i >= 0; --i)
    {
        reverse_out[len-1-i] = in[i];    
    }
}
void string_add(const char *in1, const char *in2, char *result)
{
    int len1 = strlen(in1); 
    int len2 = strlen(in2);
    char reverse_in1[len1];
    char reverse_in2[len2];
    int max_len = std::max(len1,len2);
    char out[max_len+1];
    reverse_string(in1,reverse_in1);
    reverse_string(in2,reverse_in2);
    std::cout<<reverse_in1<<std::endl;
    std::cout<<reverse_in2<<std::endl;
    const char zero = '0';
    const char nine = '9';
    char temp;
    char flag = 0;
    for (int i = 0; i < max_len; ++i)
    {
        if(i<len1 && i<len2)
        {
            temp = reverse_in1[i]+reverse_in2[i] + flag - zero;
            if(temp > nine)
            {
                out[i] = temp-1 - nine + zero;
                flag = 1;
            }
            else
            {
                out[i] = temp;
                flag = 0; 
            }
        }
        else if(i>=len1 && i<len2)
        {
            temp = reverse_in2[i] + flag;
            if(temp > nine)
            {
                out[i] = temp-1 - nine + zero;
                flag = 1;
            }
            else
            {
                out[i] = temp;
                flag = 0; 
            }
        }
        else if(i<len1 && i>=len2)
        {
            temp = reverse_in1[i] + flag;
            if(temp > nine)
            {
                out[i] = temp-1 - nine + zero;
                flag = 1;
            }
            else
            {
                out[i] = temp;
                flag = 0; 
            }
        }
    }
    std::cout<<strlen(out)<<std::endl;
    reverse_string(out,result);
}

int main(int argc, char const *argv[])
{
    char in1[] = "12254";
    char in2[] = "56852";
    char result[10];
    std::cout<<in1<<std::endl;
    std::cout<<in2<<std::endl;
    // reverse_string(in1,result);
    string_add(in1,in2,result);
    // std::cout<<strlen(result)<<std::endl;
    std::cout<<result<<std::endl;
    std::cout<<"Have Done!"<<std::endl;
    return 0;
}
