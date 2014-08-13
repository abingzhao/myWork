#ifndef HAVE_SORT_HPP
#define HAVE_SORT_HPP

#include <iostream>
#include <algorithm>
#include <iterator>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cassert>

template <typename T>
void Swap(T& lhs,T& rhs)
{
    T tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

template <typename T>
bool IsUpOrdered(T* seqPtr, int seqLen)
{
    for (int i = 1; i < seqLen; ++i)
    {
        if(seqPtr[i-1] > seqPtr[i])
            return false;
    }
    return true;
}

void RandSeqGenerator(int * seqPtr,const int seqLen, 
                        const int minVal, const int maxVal)
{
    srand(time(NULL));
    const int stepVal = maxVal - minVal;
    for (int i = 0; i < seqLen; ++i)
    {
        seqPtr[i] = rand()%stepVal + minVal;
    }

}


#endif/*HAVE_SORT_HPP*/