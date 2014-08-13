#include "Sort.hpp"

using namespace std;

static int swapCounter = 0;

template <typename T>
void BubbleSort(T * const inPtr,  int seqLen)
{
    for (int i = seqLen-1; i > 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            if(inPtr[j] > inPtr[j+1])
            {
                Swap(inPtr[j],inPtr[j+1]);
                ++swapCounter;
            }
        }
    }
}
template <typename T>
void BubbleSortWithFlag(T * const inPtr,  int seqLen)
{
    bool exchanged = false;
    for (int i = seqLen-1; i > 0; --i)
    {
        exchanged = false;
        for (int j = 0; j < i; ++j)
        {
            if(inPtr[j] > inPtr[j+1])
            {
                Swap(inPtr[j],inPtr[j+1]);
                exchanged = true;
                ++swapCounter;
            }
        }
        if(!exchanged)
            return ;
    }
}
/**
 * @brief 外循环一次，记录本次在执行内循环时候的最后一次交换位置，来更新i的步进值，
 *        扩大一次外循环带来的有序区长度
 */
template <typename T>
void BubbleSortWithFlag2(T * const inPtr,  int seqLen)
{
    int lastSwapPos = 0;
    bool exchanged = false;
    for (int i = seqLen-1; i > 0;/* --i*/)
    {
        exchanged = false;
        lastSwapPos = i;
        for (int j = 0; j < i; ++j)
        {
            if(inPtr[j] > inPtr[j+1])
            {
                Swap(inPtr[j],inPtr[j+1]);
                lastSwapPos = j;
                exchanged = true;
                ++swapCounter;
            }
        }
        if(!exchanged)
            return ;
        i = lastSwapPos;
    }
}

/**
 * @brief 另一种形式的冒泡排序，及每次遍历不再是大就交换，而是记录最大值下标，
 * 在内循环完成之后交换一次
 */
template<typename T>
void SimpleSelect(T* inPtr, int seqLen)
{
    int maxIdex = 0;
    for (int i = seqLen - 1; i > 0; --i)
    {
        maxIdex = i;
        for (int j = 0; j < i; ++j)
        {
            if(inPtr[j] > inPtr[maxIdex])
                maxIdex = j;
        }
        if(i!=maxIdex)
        {
            Swap(inPtr[i],inPtr[maxIdex]);
            ++swapCounter;
        }
    }
}

int main(int argc, char const *argv[])
{
    const int seqLen = 10;
    int seq[seqLen] = {0};
    int seqb[seqLen] = {0};
    RandSeqGenerator(seq,seqLen,0,seqLen);
    memcpy(seqb,seq,sizeof(int)*seqLen);
    copy(seq, seq + seqLen, ostream_iterator<int>(cout,", ")); cout<<endl;
    BubbleSortWithFlag2(seq,seqLen);
    cout<<swapCounter<<endl;
    assert(IsUpOrdered(seq,seqLen));
    swapCounter = 0;
    BubbleSort(seqb,seqLen);
    cout<<swapCounter<<endl;
    assert(IsUpOrdered(seqb,seqLen));
    // copy(seq, seq + seqLen, ostream_iterator<int>(cout,", ")); cout<<endl;
    cout<<"\nMain Finished"<<endl;
    return 0;
}