/*
 * selection_sort.h
 *
 *  Created on: 2013-11-19
 *      Author: abing
 */

#ifndef SELECTION_SORT_H_
#define SELECTION_SORT_H_
#include "basic_func.h"

/*!
 * selection sort ;选择排序发，是一种简单直观的排序算法。首先在未排序序列中找到最小（大）元素，
 * 存放到排序序列的起始位置，然后，再从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。
 * 以此类推，直到所有元素均排序完毕。   算法不稳定
 * http://zh.wikipedia.org/wiki/%E9%80%89%E6%8B%A9%E6%8E%92%E5%BA%8F
 * */
void selection_sort(int *seq,int len)
{
    int i_min;
    for (int j = 0; j < len-1; j++)
    {
        i_min = j;
        for(int i=j+1;i<len;i++)
        {
            if(seq[i]<seq[i_min])
                i_min=i;
        }
        if(i_min!=j)
            exchange_element(seq,j,i_min);
    }
}

/*！
 * dual selection sort :双向选择排序，同时去寻找序列中的最大值个最小值，然后放到合适的位置，
 * 不稳定
 * */
void dual_selection_sort(int* seq,int len)
{
    int start_index=0,end_index=len-1;
    int min_index,max_index;
    for(;start_index<end_index;start_index++,end_index--)
    {
        min_index=start_index;
        max_index=start_index;
        for(int i=start_index+1;i<=end_index;i++)
        {
            if (seq[i]<seq[min_index])
                min_index=i;
            if (seq[i]>seq[max_index])
                max_index=i;
        }
        exchange_element(seq,min_index,start_index);
        if (max_index==start_index)
            exchange_element(seq,min_index,end_index);
        else
            exchange_element(seq,max_index,end_index);
    }
}
/*!
 * bingo sort method:将several unique sort 的思想应用到选择排序当中，即每次找到最大值后，
 * 同时也将其他等于该值的item也一起变换到最佳位置，这样就比selection sort 移动的次数较少
 */
void bingo_sort(int *seq,int len)
{
	for(int end_index=len-1;end_index>0;)
	{
		int max_index=0;
		//寻找最大值
		for (int j=end_index;j>0;j--)
			if(seq[j]>seq[max_index])
				max_index=j;
		exchange_element(seq,max_index,end_index);
		max_index=end_index;
		end_index--;
		for(int j=end_index;j>0;j--)
			if(seq[j]==seq[max_index])
			{
				exchange_element(seq,end_index,j);
				end_index--;
			}
	}
}

/*!
 * Exact Sort:对于选择排序法来说，通常情况下，在找到第n个最小的元素之后，会把它与第n个元素交换位置，那这样的情况下，
 * 原来位于第n个位置的会被转移到新的位置，新的位置可能并不是他的最佳位置，这样的话，须要对他继续进行交换，一般情况下，
 * 每个元素平均会被转移两次采纳呢个到正确位置。
 * 这种改进的selection sort，将每个元素一部直接送到正确位置。即对于第n个元素在转移到位置n之前，原来位于n位置的元素
 * 要先找到他的正确位置n‘并转移到n’，在转移之前，原位于n'的元素要先找到并转移到他的正确位置n''……依次类推。
 * */
int real_index(const int *sorted_flag, int f, int len)
{
    int fc = -1;
    for (int i = 0; i<len; ++i)
    {
        if (!sorted_flag[i])
        	++fc;
        if (fc == f)
        	return i;
    }
    return -1;
}
void exact_sort(int * seq,int len)
{
	//用于指示对应位置的元素是否已经是最佳位置，不是则该位置为flase；初始时候都是false
	int *const sorted_flag= new int[len];
	for (int i=0;i<len;i++)
		sorted_flag[i]=false;
	//设置开始元素的位置，可以手动设置
	int start_point=real_index(sorted_flag,0,len);//给出第一个未排序元素位置
	int current_index=start_point;//当前元素位置
	int current_value=seq[current_index];//当前元素位置的元素值
	//循环就是整个序列的长度，也可以不仅行任何控制，使用  for(;;)
	for(int i=0;i<len;i++)
	{
		//每一次循环都是为了找到当前元素值的正确位置
		int counter=0;//计数器，用于记录未正确排序的且比给定当前元素值要小的元素的个数
		for (int j=len-1;j >=0;j--)
			if((!sorted_flag[j])&&(j!=start_point)&&(seq[j]<current_value))
				counter++;
		int destination_index=real_index(sorted_flag,counter,len);
		if (destination_index==-1)
			break;//-1表明已经没有有未排序的元素，循环退出
		sorted_flag[destination_index]=true;
		//如果找到的目的位置与起始位置相同，就要重新找到一个起始位置
		if(destination_index==start_point)
		{
			if(destination_index != current_index)//目的位置没在当前位置
				seq[destination_index]=current_value;//把当前元素值放入其目的位置
			start_point=real_index(sorted_flag,0,len);//重新给出第一个未排序元素位置
			if(start_point ==-1)
				break;//-1表明已经没有有未排序的元素，循环退出
			//取出新的起始位置元素给当前元素位置、当前元素值
			current_value=seq[start_point];//当前元素位置的元素值
			current_index=start_point;//当前元素位置
			
		}
		else
		{
			exchange_element(seq[destination_index],current_value);
			current_index=destination_index;
		}
	}
	delete []sorted_flag;
}






#endif /* SELECTION_SORT_H_ */
