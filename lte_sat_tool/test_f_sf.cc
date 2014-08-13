#include <iostream>
#include <cstdio>
#include <boost/operators.hpp>
struct FRAME_NUM : boost::less_than_comparable<FRAME_NUM ,
                   boost::equality_comparable<FRAME_NUM> >
{
    int frame_num;
    int subframe_num;

    FRAME_NUM(int f1,int sf1):frame_num(f1),subframe_num(sf1){ }
    void operator++()
    {
        if((++subframe_num) == 10)
        {
            subframe_num = 0;
            frame_num++;
        }
    }

    void operator++(int)
    {
        if((++subframe_num) == 10)
        {
            subframe_num = 0;
            frame_num++;
        }
    }

    friend bool operator== (const FRAME_NUM& lhs,const FRAME_NUM& rhs)
    {
        return ( (lhs.frame_num & 1024) == (rhs.frame_num & 1024) && 
                 lhs.subframe_num       == rhs.subframe_num );
    }
    friend bool operator< (const FRAME_NUM& lhs,const FRAME_NUM& rhs)
    {
        return ( (lhs.frame_num & 1024) < (rhs.frame_num & 1024) && 
                 lhs.subframe_num       < rhs.subframe_num );
    }
    void reset_fsf(int f,int sf)
    {
        frame_num  = f;
        subframe_num = sf%10;
        if(sf>10) 
            printf("@subframe_num  Wrong! Must less than 10\n");
    }

};

int main(int argc, char const *argv[])
{
    FRAME_NUM fsf1(0,8);
    FRAME_NUM fsf2(0,0);
    ++fsf1;
    fsf2.reset_fsf(1,2);

    if(fsf1==fsf2) printf("frame/subframe equal!!\n");
    else printf("frame/subframe different!!\n");

    if(fsf1>fsf2) printf("fsf1>fsf2\n");
    else printf("fsf1<=fsf2\n");

    if(fsf1<fsf2) printf("fsf1<fsf2\n");
    else printf("fsf1>=fsf2\n");
    fsf1++;

    printf("%d,%d\n",fsf1.frame_num,fsf2.subframe_num);

    return 0;
    return 0;
}