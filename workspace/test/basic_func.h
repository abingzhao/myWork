/*
 * basic_func.h
 *
 *  Created on: 2013-11-19
 *      Author: abing
 */

#ifndef BASIC_FUNC_H_
#define BASIC_FUNC_H_
#include <iostream>
/*!
 * 判断是否已经正确排序
 * */
bool is_sorted(double *seq,int len)
{
	bool sorted=true;
	for(int i=0;i<len-1;i++)
	{
		if (seq[i]>seq[i+1])
			sorted=false;
	}
	return sorted;
}
bool is_sorted(int *seq,int len)
{
	bool sorted=true;
	for(int i=0;i<len-1;i++)
	{
		if (seq[i]>seq[i+1])
			sorted=false;
	}
	return sorted;
}

/*！
 * 交换序列seq中的下标为p、q的两元素值
 * */
void exchange_element(int *seq,int p,int q)
{
	int temp=seq[p];
	seq[p]=seq[q];
	seq[q]=temp;
}
void exchange_element(double *seq,int p,int q)
{
	double temp=seq[p];
	seq[p]=seq[q];
	seq[q]=temp;
}
void exchange_element(int &p,int &q)
{
	int temp=p;
	p=q;
	q=temp;
}
/*!
 * 将数据输出
 * */
void seq_print(int *seq,int len)
{
	for (int i=0;i<len;i++)
		std::cout<<seq[i]<<std::endl;
}


#endif /* BASIC_FUNC_H_ */
