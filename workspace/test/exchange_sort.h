/*
 * bubble_sort.h
 *
 *  Created on: 2013-11-19
 *      Author: abing
 */

#ifndef BUBBLE_SORT_H_
#define BUBBLE_SORT_H_

#include "basic_func.h"
#include <iostream>
#include <cmath>
/*!
 * simple bubble sort method,也就是最基本的冒泡排序法，改算法是稳定的
 * */
void simple_bubble_sort(int *seq,int len)
{
	for (int i=0;i<len;i++)
	{
		for(int j=len-1;j>i;j--)
		{
			if(seq[j]<seq[j-1])
				exchange_element(seq,j,j-1);
		}
	}
}
/*！
 * improved bubble sort method,改进的冒泡法
 * 即设置一个交换的标置，当某次i的循环不再进行交换的时候说明已经正确排序，即可以推出循环，并且该算法仍属于bubble算法
 * 所以，是稳定的
 * */
void improved_bubble_sort(int *seq,int len)
{
	for (int i=0;i<len;i++)
	{
		bool exchanged_flag=false;
		for (int j=len-1;j>i;j--)
		{
			if(seq[j]<seq[j-1])
			{
				exchange_element(seq,j,j-1);
				exchanged_flag=true;
			}
		}
		if(!exchanged_flag)
			return;
	}
}
/*!
 * best bubble sort method,改进的bubble算法即improved_bubble_sort人然可以继续优化，每一步之后都把一个数移到
 * 其正确的位置，那就意味着接下来的冒泡算法将会跳过这些点，如果这个点是序列中的第一个，那么算法完成。对于序列后部分正确
 * 排列的待排序序列来说这种算法性能更好，仍属于冒泡算法，是稳定的
 * */
void best_bubble_sort(int *seq,int len)
{
	int i=len-1;
	do
	{
		int k=0;
		for(int j=0;j<i;j++)
		{
			if(seq[j+1]<seq[j])
			{
				exchange_element(seq,j,j+1);
				k=j;
			}
		}
		i=k;
	}while(i>0);
}


/*!
 * cocktail_sort method,鸡尾酒排序法，是冒泡法的变形，它是以双向在序列中进行排序，最大值向右进行升序冒泡，小值向
 * 左进行降序冒泡，直至不再进行交换为止。算法是稳定的。又称做Shaker Sort，Bidirectional Bubble sort等
 * */
void cocktail_sort(int *seq,int len)
{
	int j,l=1,r=len-1,k=r;
	do
	{
		for(j=r;j>0;j--)
		{
			if(seq[j]<seq[j-1])
			{
				exchange_element(seq,j,j-1);
				k=j;
			}
		}
		l=k+1;
		for(j=1;j<=r;j++)
		{
			if(seq[j]<seq[j-1])
			{
				exchange_element(seq,j,j-1);
				k=j;
			}
		}
		r=k-1;
	}while(l<=r);
}

/*!
 * Several-Unique Sort,是冒泡算法一种很有趣的变形，比冒泡算法稍有点慢，并且算法不稳定
 * */
void several_unique_sort(int *seq,int len)
{
	int high_value,new_value;
	int swap_index,position;
	int end_index=len-1;
	if(len>0)
	{
		do
		{
			swap_index=0;
			position=-1;
			high_value=seq[swap_index];
			while(position<end_index)
			{
				position+=1;
				new_value=seq[position];
				if(new_value<high_value)
				{
					seq[swap_index++] = new_value;
					seq[position] = high_value;
				}
				if(high_value<new_value)
				{
					swap_index = position;
					high_value = seq[position];
				}
			}
			end_index = swap_index - 1;
		}while (position >= swap_index);
	}
}

/*!
 * Comb Sort,梳状排序是改良自冒泡算法和快速排序法在泡沫排序中，只比较阵列中相邻的二项，即比较的二项的间距(Gap)是1，
 * 梳排序提出此间距其实可大于1，改自插入排序的希尔排序同样提出相同观点。梳排序中，开始时的间距设定为阵列长度，并在循
 * 环中以固定比率递减，通常递减率设定为1.3。在一次循环中，梳排序如同泡沫排序一样把阵列从首到尾扫描一次，比较及交换两项，
 * 不同的是两项的间距不固定于1。如果间距递减至1，梳排序假定输入阵列大致排序好，并以泡沫排序作最后检查及修正。
 * 该算法不稳定
 * */
void comb_sort11(int*seq,int len)
{
	bool swapped;
	int gap=len;
	do {
		 gap = (gap*10)/13;
		 switch (gap)
		 {
		 	 case 0 : gap = 1;  break;
		 	 case 9 :
		     case 10: gap = 11; break; // this is what makes this Combsort11
		     default:           break;
		 }
		 swapped = false;
		 for(int i = gap; i < len; i++)
		 {
			 const int j = i - gap;
			 if (seq[i] < seq[j])
			 {
				 exchange_element(seq,j,i);
				 swapped = true;
			 }
		 }
	}while (swapped | (gap > 1));
}
/*!
 * Gnome sort :地精排序，或者傻瓜排序，类似与插入排序，但将元素转移到合适位置是通过一系列的元素交换来完成的
 * 算法稳定，复杂度O(n^2)
 * */
void gnome_sort(int *seq,int len)
{
	int position=1;
	while(position<len)
	{
		if(seq[position]>=seq[position-1])
			position =position+1;
		else
		{
			exchange_element(seq,position,position-1);
			if(position>1)
				position =position-1;
		}
	}
}

/*!
 * shell sort 算法中改进*内插法的方法可以应用于bubble算法，
 * 但是这种改进算法使得算法不再稳定
 * */
void shell_bubble_sort(int *seq,int len)
{
	for (int m = len; m > 0; m = static_cast<int>(floor(m * (1.0/1.33))))
	{
		for (int i = 0; i < m; ++i)
		{
			int l = i+((len-i-1)/m)*m;
			do
			{
				int k = 0;
				for (int j = i; j < l; j+=m)
				{
					if (seq[j + m] < seq[j])
					{
						exchange_element(seq,j, j + m);
						k = j;
					}
				}
				l = k;
			} while (m == 1 && l > i);
		}
	}
}




#endif /* BUBBLE_SORT_H_ */
