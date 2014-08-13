#include"complex"
#include"mod_demod.hpp"
#include"typedefs.h"
#include<iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;




int main ()
{
    unsigned int LEN=16;
    unsigned int mod_type=4
    complex<float> d_out[LEN];
    unsigned int bps=mod_type;
    unsigned int d_in[LEN*bps];
    for(unsigned int i=0;i<LEN;i++)
    {
        for (unsigned int j=0;j<bps;j++)
        {
            d_in[i*bps+j]=((i>>j)&(0x01));
        }
        cout<<endl;
    }
    mod_mapper(mod_type,d_in,d_out,LEN);
/*
    srand((unsigned)time(NULL));
    float a[LEN*2];
    for (unsigned int i=0;i<LEN*2;i++)
    	a[i]=((float)(rand()%100)/50-1)/10;

    for (unsigned int i=0;i<LEN;i++)
    {
    	d_out[i] +=complex<float>(a[2*i],a[2*i+1]);
    }
*/
    int8 out_in[LEN*bps];
    //unsigned int out_in[LEN*bps];
    soft_mod_demapper(mod_type,d_out,out_in,LEN*bps);

    for (unsigned int i=0;i<LEN;i++)
    {
        for (unsigned int j=0;j<bps;j++)
        {
            d_in[i*bps+j]=((i>>j)&(0x01));
            cout<<d_in[i*bps+j]<<" ";
        }
        cout<<"maps to :"<<d_out[i];
        for (unsigned int j=0;j<bps;j++)
            cout<<(int)out_in[i*bps+j]<<" ";
        cout<<endl;
    }
    return 0;
}
