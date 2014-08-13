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




int main(int argc, char const *argv[])
{
    const int seqLen = 10000;
    int seq[seqLen] = {0};
    RandSeqGenerator(seq, seqLen, 0, seqLen * 2);
    // PrintSeq(seq, seqLen);
    CodeTiming ct;
    ct.Start();
    SelectSort(seq, seqLen);
    ct.EndAndPrint("SelectSort");
    // PrintSeq(seq, seqLen);
    cout<<"\nMain Done!"<<endl;
    return 0;
}