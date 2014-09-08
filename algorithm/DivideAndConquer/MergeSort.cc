/*******************************************************************************
    File        : MergeSort.cc
    Description : Implement Merge Sort
    Author      : abing0513

    Revision     History
    ----------    ---------    --------------------------------------------
    2014-08-29    abing0513

*******************************************************************************/

/*******************************************************************************
    INCLUDE
*******************************************************************************/
#include <iostream>
#include <cstdlib>
#include "../sort/Sort.hpp"
/*******************************************************************************
    namespace
*******************************************************************************/
using namespace std;

/*******************************************************************************
    UpOrder
*******************************************************************************/
bool UpOrder(int lhs, int rhs)
{
    return lhs > rhs;
}
/*******************************************************************************
    DownOrder
*******************************************************************************/
bool DownOrder(int lhs, int rhs)
{
    return lhs < rhs;
}

/*******************************************************************************
    MergeSeq
*******************************************************************************/
template <typename T, typename Compare>
void MergeSeq(T* inPtr, int startIdx, int midIdx, int endIdx, T* tmpPtr, Compare pCmp)
{
    int k = 0;
    int i = startIdx;
    int j = midIdx + 1;
    while(i <= midIdx && j <= endIdx)
    {
        if(pCmp(inPtr[i], inPtr[j]))
            tmpPtr[k++] = inPtr[j++];
        else
            tmpPtr[k++] = inPtr[i++];
    }
    while(i <= midIdx)
        tmpPtr[k++] = inPtr[i++];
    while(j <= endIdx)
        tmpPtr[k++] = inPtr[j++];
    while(--k >= 0)
        inPtr[startIdx + k] = tmpPtr[k];
}

/*******************************************************************************
    MergeSort
*******************************************************************************/
template <typename T, typename Compare>
void MergeSort(T* inPtr, int startIdx, int endIdx, T* tmpPtr, Compare pCmp)
{
    if(startIdx < endIdx)
    {
        int midIdx = startIdx + (endIdx - startIdx) / 2;
        MergeSort(inPtr, startIdx, midIdx, tmpPtr, pCmp);
        MergeSort(inPtr, midIdx + 1, endIdx, tmpPtr, pCmp);
        MergeSeq(inPtr, startIdx, midIdx, endIdx, tmpPtr, pCmp);
    }
}
template <typename T, typename Compare>
void MergeSort(T* inPtr, int len, Compare pCmp)
{
    T* tmpPtr = (T*)malloc(sizeof(T)*len);
    MergeSort(inPtr, 0, len-1, tmpPtr, pCmp);
    free(tmpPtr);
}

/*******************************************************************************
    main
*******************************************************************************/
int main(int argc, char const *argv[])
{
    const int seqLen = 10;
    int seq[seqLen] = {0};
    RandSeqGenerator(seq, seqLen, 0, seqLen);
    PrintSeq(seq, seqLen);
    CodeTiming ct;
    ct.Start();
    MergeSort(seq, seqLen, DownOrder);
    ct.EndAndPrint("MergeSort");
    // assert(IsUpOrdered(seq,seqLen));
    PrintSeq(seq, seqLen);

    std::cout << "\nMain Finished" << std::endl;
    return 0;
}