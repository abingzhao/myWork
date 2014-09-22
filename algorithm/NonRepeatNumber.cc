/*******************************************************************************
    File        : NonRepeatNumber.cc
    Description : Description
    Author      : abing0513

    Revision                   Change Log
    ----------    ---------    --------------------------------------------
    2014-09-11    abing0513    Change Log

*******************************************************************************/
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

/*******************************************************************************
    给定N是一个正整数，求比N大的最小“不重复数”，这里的不重复是指没有两个相等的相邻位，
    如1102中的11是相等的两个相邻位故不是不重复数，而12301是不重复数。
*******************************************************************************/
int MinBiggerNonRepeatNum(int num)
{
    while(true)
    {
        int a[20] = {0};
        int b = 0;
        int idx = 0;
        bool flag = false;
        bool no_change = false;
        while(num)
        {
            a[idx++] = num%10;
            num = num / 10;        
        }
        for (int i = idx-1; i >= 0; --i)
        {
            if(a[i] == a[i-1] && !flag)
            {
                ++a[i-1];
                flag = true;
            }
            else if(flag)
            {
                a[i-1] = b;
                b = (b==0) ? 1:0; 
            }
            else
                no_change = true;
        }
        num = 0;
        for (int i = idx-1; i >= 0; --i)
        {
            num = num * 10 + a[i];
        }
        if(no_change)
            return num;
    }
}


void ConvertLongToHexString(long inPut, char *outPut)
{
    if(!outPut)
        return ;
    const char table[] = "0123456789ABCDEF";
    long tmp = inPut;
    int idx = -1;
    while(tmp)
    {
        outPut[++idx] = table[tmp&0xF];
        tmp = tmp>>4;
    }
    int i = 0;
    while(i < idx)
    {
        char tmpChar  = outPut[idx];
        outPut[idx--] = outPut[i]; 
        outPut[i++]   = tmpChar;
    }
}


int main(int argc, char const *argv[])
{
    // int a = 0 ;
    // while(true)
    // {
    //     cout << "Input a Number (exit with -1):";
    //     cin >> a ;
    //     if(a == -1)
    //         break;
    //     cout << "The Min Bigger NonRepeatNumber of " << a << " is :" 
    //          << MinBiggerNonRepeatNum(a) << endl;
    // }
    char a[100] ="";
    long num = 0x1a2b3c4d;
    ConvertLongToHexString(num,a);
    cout << "Hex(" << num << ") = 0x" << a << endl;
    std::cout << "\nMain Finished" << std::endl;
    return 0;
}

