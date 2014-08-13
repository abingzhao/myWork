#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "../CodeTiming.h"
using namespace std;

template <typename T>
void GenRandomSeq(T *inPtr, int seqLen, T maxVal, T minVal)
{
    srand(time(0));
    for (int i = 0; i < seqLen; ++i)
    {
        T randVal = static_cast<T>(rand()%static_cast<int>(maxVal - minVal)) + minVal;
        randVal = max(randVal, minVal);
        randVal = min(randVal, maxVal);
        inPtr[i] = randVal;
    }
}
/**
 * @brief Slow Algorithm O(N^2)
 */
template <typename T>
int MaxSubSeqSumDirect(const T* inPtr, int seqLen, T& maxSum)
{
    maxSum = static_cast<T>(0);
    int maxIndex = 0;
    for (int i = 0; i < seqLen; ++i)
    {
        T sumTmp = static_cast<T>(0);
        for (int j = i; j < seqLen; ++j)
        {
            sumTmp += inPtr[j];
            if(maxSum < sumTmp)
            {
                maxSum = sumTmp;
                maxIndex = i;
            }
        }
    }
    return maxIndex;
} 

// O(n)
template <typename T>
void MaxSubSeqSum(T* inPtr, int seqLen, T& maxSum)
{
    maxSum = static_cast<T>(0);
    T sumTmp = static_cast<T>(0);
    for (int i = 0; i < seqLen; ++i)
    {
        if(sumTmp <= static_cast<T>(0))
            sumTmp = inPtr[i];
        else
            sumTmp += inPtr[i];
        if(maxSum < sumTmp)
            maxSum = sumTmp;
    }

}
int main(int argc, char const *argv[])
{
    CodeTiming cc;
    const int seqLen = 10;
    double maxVal = 10;
    double minVal = -8;
    double inSeq[seqLen] = {0};
    double maxSubSeqSum = 0;
    double maxSubSeqSum2 = 0;
    int startIndex = -1;
    GenRandomSeq(inSeq, seqLen, maxVal, minVal);
    copy(inSeq, inSeq+seqLen, ostream_iterator<double>(cout,", "));
    cc.Start();
    startIndex = MaxSubSeqSumDirect(inSeq, seqLen, maxSubSeqSum);
    cc.EndAndPrint("MaxSubSeqSumDirect");

    cc.Start();
    MaxSubSeqSum(inSeq, seqLen, maxSubSeqSum2);
    cc.EndAndPrint("MaxSubSeqSum");
    assert(maxSubSeqSum == maxSubSeqSum2);
    cout<<"Main Done!"<<endl;
    return 0;
}