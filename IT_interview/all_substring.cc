#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

 /*!
  * 蛮力求解法
  * @param str  [description]
  * @param high [description]
  */
void all_substring1(const char *str,int high)
{
    int i, j, k;
    if(!str)
        return;

    for(i=0;i<=high;i++)
    {
        for(j=i; j<=high;j++)
        {
            for(k = i; k<=j; k++)
                cout<<str[k];
            cout<<"\t";
        } 
        cout<<"\n";
    }
}

int main()
{
    int len = 10;
    char * str = (char*)malloc(sizeof(char)*3);
    
    all_substring1(str,2);
    return 0;
}