/*
 * radix_sort.h
 *
 *  Created on: 2013-11-18
 *      Author: abing
 */

#ifndef RADIX_SORT_H_
#define RADIX_SORT_H_
#include <vector>
#include <cstring>
#include <iostream>


/*!
 * bucket排序  结合插入法
 * */
void insertion_sort(double *seq,int length)
{
	double temp;
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
void bucket_sort(double *seq,int len)
{
	std::vector< std::vector<double> > temp(len);
	for (int i=0;i<len;i++)
		temp[(int)len*seq[i]].push_back(seq[i]);
	int n_len=0;
	for (int i=0;i<len;i++)
	{
		if(!temp[i].empty())
		{
			insertion_sort(&temp[i][0],(int)temp[i].size());
			for(int j=0;j<(int)temp[i].size();j++)
				seq[n_len+j]=temp[i][j];
			n_len = n_len + (int)temp[i].size();
		}
	}
}

/*!
 * 基数发排序
 * */




#endif /* RADIX_SORT_H_ */
