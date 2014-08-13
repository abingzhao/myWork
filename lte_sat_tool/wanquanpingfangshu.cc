/**
 * 时间：2014-6-7
 * 功能：给定整数区间[A,B]问其中有多少个完全平方数。
 *       输入格式：
 *       多组数据，包含两个正整数A,B 1<=A<=B<=2000000000。
 *       输出格式：
 *       每组数据输出一行包含一个整数，表示闭区间[A,B]中包含的完全平方数的个数。
 * 示例：
 *      输入样例
 *       1 1
 *       1 2
 *       3 10
 *       3 3
 *      输出样例：
 *       1
 *       1
 *       2
 *       0
 */

#include <iostream>
#include <cmath>
#include <boost/format.hpp>
#include <vector>
double square_root (double radicand, double precision) ;

int main(int argc, char* argv[])
{
    std::vector<int> v_start;
    std::vector<int> v_end;
    int start = 0, end = 0, sqrt_start = 0, sqrt_end = 0, num = 0;
    while(std::cin>>start>>end)
    {
        v_start.push_back(start);
        v_end.push_back(end);
    }
    assert(v_start.size()==v_end.size());
    for(int i=0;i<(int)v_start.size();++i)
    {
        start = v_start[i];
        end   = v_end[i];
        sqrt_start = (int)std::ceil (square_root((double)start,0.001));
        sqrt_end   = (int)std::floor(square_root((double)end  ,0.001));
        num = (sqrt_end - sqrt_start)+1;
        if( (sqrt_end+1) * (sqrt_end+1) == end)
            ++num;
        if( (sqrt_start-1) * (sqrt_start-1) == start)
            ++num;
        std::cout<<num<<std::endl;
    }
    return 0;
}

double square_root (double radicand, double precision)
{
    if (radicand > 0)
    {
        double square_root = radicand / 10 ;
        while (square_root * square_root > radicand)
            square_root /= 2 ;
        double fakePrecision = 0.1; 
        while (1)
        {
            while ((square_root + fakePrecision) * (square_root + fakePrecision) <= radicand)
            {
                square_root += fakePrecision ;
            }
            if (fakePrecision > precision)
            {
                fakePrecision /= 10 ;
            }
            else
            {
                return square_root ;
            }
        }
    }
    else
    {
        std ::cerr << "Radicand must > 0" << std ::endl ;
        return 0 ;
    }
}