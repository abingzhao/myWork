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

/*******************************************************************************
 * QuickSort:
 * --主要思想：
 *          快速排序是C.R.A.Hoare于1962年提出的一种划分交换排序。它采用了一种分治的策略，
 *          通常称其为分治法(Divide-and-ConquerMethod)。
 * --分治：
 *          在R[low..high]中任选一个记录作为基准(Pivot)，以此基准将当前无序区划分为左、
 *          右两个较小的子区间R[low..pivotpos-1)和R[pivotpos+1..high]，并使左边子
 *          区间中所有记录的关键字均小于等于基准记录(不妨记为pivot)的关键字pivot.key，
 *          右边的子区间中所有记录的关键字均大于等于pivot.key，而基准记录pivot则位于正
 *          确的位置(pivotpos)上，它无须参加后续的排序。
 *          注意：
 *  　           划分的关键是要求出基准记录所在的位置pivotpos。划分的结果可以简单地表示为
 *          (注意pivot=R[pivotpos])：
 *          R[low..pivotpos-1].keys≤R[pivotpos].key≤R[pivotpos+1..high].keys
 *          其中low≤pivotpos≤high。
 * --求解：
 *          通过递归调用快速排序对左、右子区间R[low..pivotpos-1]和R[pivotpos+1..high]
 *          快速排序。
 * --组合：
 *          因为当"求解"步骤中的两个递归调用结束时，其左、右两个子区间已有序。对快速排序而言，
 *          "组合"步骤无须做什么，可看作是空操作。
 ******************************************************************************/
template <typename T>
int Partion(T* inPtr, int lowIdx, int highIdx)
{
    int tmpIdx = lowIdx;
    
}

int main(int argc, char const *argv[])
{
    const int seqLen = 10;
    int seq[seqLen] = {0};
    int seqb[seqLen] = {0};
    RandSeqGenerator(seq,seqLen,0,seqLen);
    // memcpy(seqb,seq,sizeof(int)*seqLen);
    copy(seq, seq + seqLen, ostream_iterator<int>(cout,", ")); cout<<endl;
    // BubbleSortWithFlag2(seq,seqLen);
    // cout<<swapCounter<<endl;
    // assert(IsUpOrdered(seq,seqLen));
    // swapCounter = 0;
    // BubbleSort(seqb,seqLen);
    // cout<<swapCounter<<endl;
    // assert(IsUpOrdered(seqb,seqLen));
    // copy(seq, seq + seqLen, ostream_iterator<int>(cout,", ")); cout<<endl;
    cout<<"\nMain Finished"<<endl;
    return 0;
}