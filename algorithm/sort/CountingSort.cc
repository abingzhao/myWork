
#include "Sort.hpp"
#include "../../CodeTiming.h"
using namespace std;

void CountingSort(int * const seqPtr, const int seqLen,
                 const int minVal, const int maxVal)
{
    const int countingLen = maxVal - minVal + 1;
    int *countingSeq = (int*)malloc(sizeof(int)*countingLen);
    memset(countingSeq,0,sizeof(int)*countingLen);
    for (int i = 0; i < seqLen; ++i)
    {
        countingSeq[seqPtr[i] - minVal]++; 
    }
    int outPtr = 0;
    for (int i = 0; i < countingLen; ++i)
    {
        while(countingSeq[i]-- != 0)
            seqPtr[outPtr++] = i + minVal;
    }
    free(countingSeq);
}

int main(int argc, char const *argv[])
{
    const int seqLen = 0x7FFF;//FFFFFF;
    int minVal = 0;
    int maxVal = 5;
    // int seq[seqLen] = {0}; 
    int *seq = (int*)malloc(sizeof(int)*seqLen);
    memset(seq,0,sizeof(int)*seqLen);
    CodeTiming ct;
    ct.Start();
    RandSeqGenerator(seq, seqLen, minVal, maxVal);
    ct.EndAndPrint("RandSeqGenerator");
    // cout<<"Origin Seq:\n\t";
    // copy(seq, seq+seqLen, ostream_iterator<int>(cout,", "));
    // cout<<endl<<"Sorted Seq:\n\t";
    ct.Start();
    CountingSort(seq, seqLen, minVal, maxVal);
    ct.EndAndPrint("RandSeqGenerator");
    // copy(seq, seq+seqLen, ostream_iterator<int>(cout,", "));
    assert(IsUpOrdered(seq,seqLen));
    free(seq);
    cout<<"\nMain Done!"<<endl;
    return 0;
} 