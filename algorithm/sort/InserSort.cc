#include "Sort.hpp"
using namespace std;

template <typename T>
void InsertSort(T *inPtr, int seqLen)
{
    T eleTmp = inPtr[0];
    for (int i = 1; i < seqLen; ++i)
    {
        eleTmp = inPtr[i];
        int tmpIdx = i;
        while(--tmpIdx >= 0)
        {
            if(inPtr[tmpIdx] > eleTmp)
                inPtr[tmpIdx+1] = inPtr[tmpIdx];
            else
                break;
        }
        if(i != tmpIdx +1 )
            inPtr[tmpIdx + 1] = eleTmp;
    }
}

template <typename T>
void ShellSort(T* inPtr, int seqLen)
{
    T eleTmp = inPtr[0];
    int stepLen = seqLen;
    for (; stepLen > 0; stepLen /= 2)
    {
        for (int i = 0; i < seqLen; i += stepLen)
        {
            eleTmp = inPtr[i];
            int tmpIdx = i - stepLen;
            while( tmpIdx >= 0)
            {
                if(inPtr[tmpIdx] > eleTmp)
                    inPtr[tmpIdx + stepLen] = inPtr[tmpIdx];
                else 
                    break;
            }
            if( i != tmpIdx + stepLen)
                inPtr[tmpIdx + stepLen] = eleTmp;
        }
    }    
}

int main(int argc, char const *argv[])
{
    const int seqLen = 100000;
    int seq[seqLen] = {0};
    RandSeqGenerator(seq, seqLen, 0, seqLen*2);
    // PrintSeq(seq,seqLen);
    CodeTiming ct;
    ct.Start();
    InsertSort(seq,seqLen);
    ct.EndAndPrint("InsertSort");
    assert(IsUpOrdered(seq, seqLen));
    ct.Start();
    ShellSort(seq,seqLen);
    // PrintSeq(seq,seqLen);
    ct.EndAndPrint("ShellSort");
    assert(IsUpOrdered(seq, seqLen));
    cout<<"\nMain Done!"<<endl;
    return 0;
}
