#include "Sort.hpp"
using namespace std;
/**
 * 计数排序(Counting sort)是一种稳定的排序算法。计数排序使用一个额外的数组C，
 * 其中第i个元素是待排序数组A中值等于i的元素的个数。然后根据数组C来将A中的元素排到正确的位置。
 * 
 * 算法的步骤如下： 
 *      找出待排序的数组中最大和最小的元素 
 *      统计数组中每个值为i的元素出现的次数，存入数组C的第i项 
 *      对所有的计数累加（从C中的第一个元素开始，每一项和前一项相加） 
 *      反向填充目标数组：将每个元素i放在新数组的第C(i)项，每放一个元素就将C(i)减去1 
 */
void CountingSort(int *inPtr, int seqLen, int minVal, int maxVal)
{
    int tmpSeqLen = maxVal - minVal + 1;
    cout<<tmpSeqLen<<endl;
    int *tmpSeq = (int*)malloc(sizeof(int)*tmpSeqLen);
    memset(tmpSeq,0,sizeof(int)*tmpSeqLen);
    for (int i = 0; i < seqLen; ++i)
    {
        ++tmpSeq[inPtr[i] - minVal];
    }
    PrintSeq(tmpSeq, tmpSeqLen);
    int *outPtr = inPtr;
    for (int i = 0; i < tmpSeqLen; ++i)
    {
        while(--tmpSeq[i] >= 0)
        {
            *outPtr++ = i + minVal;
        }
    }
    free(tmpSeq);
}

void RadixSort()
{
    
}

int main(int argc, char const *argv[])
{
    const int seqLen = 10;
    int seq[seqLen] = {0};
    RandSeqGenerator(seq, seqLen, 0, 5); 
    PrintSeq(seq, seqLen);
    CountingSort(seq, seqLen, 0, 5);
    PrintSeq(seq, seqLen);
    cout<<"\nMain Finished!"<<endl;
    return 0;
}