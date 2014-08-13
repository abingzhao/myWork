#include <iostream>
#include <cstring>

typedef struct string
{
    char ss[100];
    int  len; 
} string;
void get_next(string *str, int *next)
{
    int i = 1;
    int j = 0;
    while(i < str->len)
    {
        if(j ==0 || str->ss[j]==str->ss[i])
        {
            ++i;++j;next[i] = j;
        }
        else
            j=next[j];
    }
}