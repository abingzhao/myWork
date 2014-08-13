/*******************************************************************************
 * Author : abingzhao
 * Date   : 2014-08-13
 * 
 *  Sort algorithm implement ---- MergeSort
 ******************************************************************************/
#include "Sort.hpp"

using namespace std;

template <typename T>
void MergeSeq(T* inPtr,int startIdx,int midIdx, int endIdx, T* tmpPtr)
{
    int k =0;
    // int m = std::max(midIdx - startIdx + 1, endIdx - midIdx);
    // int n = std::min(midIdx - startIdx + 1, endIdx - midIdx);

    int i = startIdx;
    int j = midIdx+1;
    while(i <= midIdx && j <= endIdx)
    {
        if(inPtr[i] < inPtr[j])
            tmpPtr[k++] = inPtr[i++];
        else
            tmpPtr[k++] = inPtr[j++];
    }
    while(i <= midIdx)
    {
        tmpPtr[k++] = inPtr[i++];
    }
    while(j <= endIdx)
    {
        tmpPtr[k++] = inPtr[j++];
    }
    while(--k >= 0)
    {
        inPtr[startIdx + k] = tmpPtr[k];
    }
}
template <typename T>
void MergeSort(T* inPtr,int startIdx, int endIdx, T* tmpPtr)
{
    if(startIdx < endIdx)
    {
        int midIdx = (startIdx + endIdx) / 2;
        MergeSort(inPtr, startIdx, midIdx, tmpPtr);
        MergeSort(inPtr, midIdx+1, endIdx, tmpPtr);
        MergeSeq(inPtr, startIdx, midIdx, endIdx, tmpPtr);
    }
}
template <typename T>
void MergeSort(T* inPtr, int seqLen)
{
    int *tmpPtr = (int*)malloc(sizeof(int)*seqLen);
    MergeSort(inPtr,0,seqLen-1,tmpPtr);
    free(tmpPtr);
}

int main(int argc, char const *argv[])
{
    const int seqLen = 100000;
    int seq[seqLen] = {0};
    RandSeqGenerator(seq, seqLen, 0, seqLen);
    // PrintSeq(seq, seqLen);
    CodeTiming ct;
    ct.Start();
    MergeSort(seq, seqLen);
    ct.EndAndPrint("MergeSort");
    assert(IsUpOrdered(seq,seqLen));
    // PrintSeq(seq, seqLen);
    cout<<"\nMain Done"<<endl;
    return 0;
}


