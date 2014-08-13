#include "Sort.hpp"


using namespace std;

template <typename T>
void SelectSort(T* inPtr, int seqLen)
{
    int tmpIdx = 0;
    for (int i = seqLen-1; i > 0; --i)
    {
        tmpIdx = i;
        for (int j = 0; j < i; ++j)
        {
            if(inPtr[j] > inPtr[tmpIdx])
            {
                tmpIdx = j;
            }
        }
        if(tmpIdx != i)
            Swap(inPtr[i],inPtr[tmpIdx]);
    }
}


/**
 * 堆排序（Heapsort）是指利用堆這種資料結構所設計的一種排序算法。堆積是一個近似完全二叉樹的結構，
 * 並同時滿足堆積的性質：即子結點的键值或索引總是小於（或者大於）它的父節點
 */
/**
 * 基于以上堆相关的操作，我们可以很容易的定义堆排序。例如，假设我们已经读入
 * 一系列数据并创建了一个堆，一个最直观的算法就是反复的调用del_max()函数，
 * 因为该函数总是能够返回堆中最大的值，然后把它从堆中删除，从而对这一系列
 * 返回值的输出就得到了该序列的降序排列。真正的原地堆排序使用了另外一个小技巧。
 * 堆排序的过程是：
 *    1> 建立一个堆H[0..n-1]
 *    2> 把堆首（最大值）和堆尾互换
 *    3> 把堆的尺寸缩小1，并调用shift_down(0),目的是把新的数组顶端数据调整到相应位置
 *    4> 重复步骤2，直到堆的尺寸为1
 */
int ParentNode(int i)
{
    return (i-1)/2;
}
int LeftNode(int i )
{
    return 2 * i + 1;
}
int RightNode(int i)
{
    return 2 * (i + 1);
}
template <typename T>
void MaxHeapify(T* inPtr, int pIdx, int seqLen)
{
    int lChildIdx = LeftNode(pIdx);
    int rChildIdx = RightNode(pIdx);
    int tmpIdx    = pIdx;
    if(lChildIdx < seqLen && inPtr[lChildIdx] > inPtr[tmpIdx])
        tmpIdx = lChildIdx;
    if(rChildIdx < seqLen && inPtr[rChildIdx] > inPtr[tmpIdx])
        tmpIdx = rChildIdx;
    if(tmpIdx != pIdx)
    {
        Swap(inPtr[tmpIdx], inPtr[pIdx]);
        MaxHeapify(inPtr, tmpIdx, seqLen);
    }
}
template <typename T>
void BuildMaxHeap(T *inPtr, int seqLen)
{
    for (int i = seqLen / 2 - 1; i >= 0; --i)
    {
        MaxHeapify(inPtr, i, seqLen);
    }
}
template <typename T>
void HeapSort(T* inPtr, int seqLen)
{
    BuildMaxHeap(inPtr,seqLen);
    for (int i = seqLen - 1; i >= 0; --i)
    {
        Swap(inPtr[0],inPtr[i]);
        MaxHeapify(inPtr,0,i);
    }
}




int main(int argc, char const *argv[])
{
    const int seqLen = 100000;
    int seq[seqLen] = {0};
    int seq2[seqLen] = {0};
    RandSeqGenerator(seq, seqLen, 0, seqLen * 2);
    memcpy(seq2, seq, sizeof(int)*seqLen);
    // PrintSeq(seq, seqLen);
    CodeTiming ct;
    ct.Start();
    SelectSort(seq, seqLen);
    ct.EndAndPrint("SelectSort");
    assert(IsUpOrdered(seq,seqLen));
    // PrintSeq(seq, seqLen);
    ct.Start();
    HeapSort(seq2, seqLen);
    ct.EndAndPrint("HeapSort");
    assert(IsUpOrdered(seq2,seqLen));
    // PrintSeq(seq2, seqLen);
    cout<<"\nMain Done!"<<endl;
    return 0;
}