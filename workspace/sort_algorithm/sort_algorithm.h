/*
 * banquansuoyou  abing
 */

/*！
 * 插入排序法实现方案
 */
#include <limits.h>
#include <cstdlib>
void insertion_sort(int *seq,int length)
{
    int temp;
    for (int j=1;j<length;j++)
    {
        temp=seq[j];
        int i=0;
        for (i=j-1;;i--)
        {
            if((seq[i]>temp)&(i>=0))
            {
                seq[i+1]=seq[i];
                continue;
            }
                
            else
            {
                seq[i+1]=temp;
                break;
            }
                
        }
        seq[i+1]=temp;
    }
}

/*!
 * 分治法排序实现方案
 */
void merge(int *seq,int p,int q,int r)
{
    int n1=q-p+1;
    int n2=r-q;
    int *L=new int[n1+1];
    int *R=new int[n2+1];
    for (int i=1;i<=n1;i++)
    {
        L[i-1]=seq[p+i-1];
    }
    for (int j=1;j<=n2;j++)
    {
        R[j-1]=seq[q+j];
    }
    L[n1]=INT_MAX;
    R[n2]=INT_MAX;
    int i=0,j=0;
    for (int k=p;k<=r;k++)
    {
        if(L[i]<R[j])
        {
            seq[k]=L[i];
            i++;
        }
        else
        {
            seq[k]=R[j];
            j++;
        }
    }
}
void merge_sort(int *seq,int p,int r)
{
    int q;
    if(p<r)
    {
        q=(p+r)/2;
        merge_sort(seq,p,q);
        merge_sort(seq,q+1,r);
        merge(seq,p,q,r);
    }
}
/*！
 * 冒泡法排序实现方案
 */
void bubble_sort(int *seq,int len)
{
    for (int i=0;i<len;i++)
    {
        bool exchange_flag=false;
        for (int j=len-1;j>i;j--)
        {
            if (seq[j]<seq[j-1])
            {
                int temp=seq[j];
                seq[j]=seq[j-1];
                seq[j-1]=temp;
                exchange_flag=true;
            }
        }
        if (!exchange_flag)
            return;
    }
}



/*！
 * 堆排序法实现方案
 */
int parent(int i)
{
    return ((i-1)/2);
}
int left(int i)
{
    return (2*i+1);
}
int right(int i)
{
    return (2*(i+1));
}
void max_heapify(int *seq,int i,int heap_size)
{
    int l=left(i);
    int r=right(i);
    int largest;
    if ((l<heap_size)&(seq[l]>seq[i]))
        largest=l;
    else
        largest=i;
    if((r<heap_size)&(seq[r]>seq[largest]))
        largest=r;
    if(largest!=i)
    {
        int temp=seq[i];
        seq[i]=seq[largest];
        seq[largest]=temp;
        max_heapify(seq,largest,heap_size);
    }
}
void build_max_heap(int *seq,int len)
{
    int heap_size=len;
    for(int i=(len-1)/2;i>=0;i--)
        max_heapify(seq,i,heap_size);
}
void heap_sort(int*seq,int len)
{
    int heap_size=len;
    build_max_heap(seq,len);
    for (int i=len-1;i>0;i--)
    {
        int temp=seq[i];
        seq[i]=seq[0];
        seq[0]=temp;
        heap_size=heap_size-1;
        max_heapify(seq,0,heap_size);
    }
}

/*!
 *QUICK_SORT-METHOD
 */
int partition(int*seq,int p,int r)
{
    int x=seq[r];
    int i=p-1;
    for (int j=p;j<=r-1;j++)
    {
        if (seq[j]<=x)
        {
            i=i+1;
            int temp=seq[i];
            seq[i]=seq[j];
            seq[j]=temp;
        }
    }
    int temp=seq[r];
    seq[r]=seq[i+1];
    seq[i+1]=temp;
    return i+1;
}
void quick_sort(int *seq,int p,int r)
{
    if(p<r)
    {
        int q=partition(seq,p,r);
        quick_sort(seq,p,q-1);
        quick_sort(seq,q+1,r);
    }
}
/*!
 * Stooge_sort-method
 */
void stooge_sort(int *seq,int i,int j)
{
    if (seq[i]>seq[j])
    {
        int temp=seq[i];
        seq[i]=seq[j];
        seq[j]=temp;
    }
    if(i+1>=j)
        return;
    int k=(j-i+1)/3;
    stooge_sort(seq,i,j-k);
    stooge_sort(seq,i+k,j);
    stooge_sort(seq,i,j-k);
}
/*!
 * Counting_sort-method
 */
void counting_sort(int *seq,int len,int max_element)
{
    int *seq_b=(int*)malloc(sizeof(int)*len);
    int *seq_c=(int*)malloc(sizeof(int)*(max_element+1));
    for(int i=0;i<=max_element;i++)
        seq_c[i]=0;
    for(int j=0;j<len;j++)
        seq_c[seq[j]]=seq_c[seq[j]]+1;
    for(int i=1;i<=max_element;i++)
        seq_c[i]=seq_c[i]+seq_c[i-1];
    for(int j=len-1;j>=0;j--)
    {
        seq_b[seq_c[seq[j]]-1]=seq[j];
        seq_c[seq[j]] -=1;
    }
    for(int i=0;i<len;i++)
        seq[i]=seq_b[i];
    free(seq_b);
    free(seq_c);
}