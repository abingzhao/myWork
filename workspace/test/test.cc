#include "radix_sort.h"
#include "basic_func.h"
#include "exchange_sort.h"
#include "sort_algorithm.h"
#include "selection_sort.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#define len 100000
int main()
{
	clock_t start, finish;
	int *seq = (int*)malloc(sizeof(int)*len);
	int *seq1 = (int*)malloc(sizeof(int)*len);
	int *seq2 = (int*)malloc(sizeof(int)*len);
	int *seq3 = (int*)malloc(sizeof(int)*len);
	//int *seq4 = (int*)malloc(sizeof(int)*len);
	//int *seq5 = (int*)malloc(sizeof(int)*len);
	//int *seq6 = (int*)malloc(sizeof(int)*len);
	//int *seq7 = (int*)malloc(sizeof(int)*len);
	srand((unsigned)time(NULL));
	for (int i=0;i<len;i++)
	{
		seq[i]=(int)(rand()%100);
		seq1[i]=seq[i];
		seq2[i]=seq[i];
		seq3[i]=seq[i];
		//seq4[i]=seq[i];
		//seq5[i]=seq[i];
		//seq6[i]=seq[i];
		//seq7[i]=seq[i];
	}
	//============================================================================
	start=clock();
	selection_sort(seq,len);
	finish=clock();
	std::cout<<"selection_sort法排序"<<len<<"个数据共用";
	std::cout<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	if(!is_sorted(seq,len))
		std::cout<<"selection_sort法未正确完成排序"<<std::endl;
	//============================================================================
	start=clock();
	dual_selection_sort(seq1,len);
	finish=clock();
	std::cout<<"dual_selection_sort法排序"<<len<<"个数据共用";
	std::cout<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	if(!is_sorted(seq1,len))
		std::cout<<"dual_selection_sort法未正确完成排序"<<std::endl;
	//============================================================================
	start=clock();
	bingo_sort(seq2,len);
	finish=clock();
	std::cout<<"bingo_sort法排序"<<len<<"个数据共用";
	std::cout<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	if(!is_sorted(seq2,len))
		std::cout<<"bingo_sort法未正确完成排序"<<std::endl;
	//seq_print(seq2,len);
	//============================================================================
	start=clock();
	exact_sort(seq3,len);
	finish=clock();
	std::cout<<"exact_sort法排序"<<len<<"个数据共用";
	std::cout<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	if(!is_sorted(seq3,len))
		std::cout<<"exact_sort法未正确完成排序"<<std::endl;
	//seq_print(seq3,len);
	//============================================================================
	/*start=clock();
	several_unique_sort(seq4,len);
	finish=clock();
	std::cout<<"several_unique_sort法排序"<<len<<"个数据共用";
	std::cout<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	if(!is_sorted(seq4,len))
		std::cout<<"several_unique_sort法未正确完成排序"<<std::endl;
	//============================================================================
	start=clock();
	comb_sort11(seq5,len);
	finish=clock();
	std::cout<<"comb_sort11法排序"<<len<<"个数据共用";
	std::cout<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	if(!is_sorted(seq5,len))
		std::cout<<"comb_sort11法未正确完成排序"<<std::endl;
	//============================================================================
	start=clock();
	gnome_sort(seq6,len);
	finish=clock();
	std::cout<<"gnome_sort法排序"<<len<<"个数据共用";
	std::cout<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	if(!is_sorted(seq6,len))
		std::cout<<"gnome_sort法未正确完成排序"<<std::endl;
	//============================================================================
	start=clock();
	shell_bubble_sort(seq7,len);
	finish=clock();
	std::cout<<"shell_bubble_sort法排序"<<len<<"个数据共用";
	std::cout<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	if(!is_sorted(seq7,len))
		std::cout<<"shell_bubble_sort法未正确完成排序"<<std::endl;
	//============================================================================
	 */

	//free(seq7);
	//free(seq6);
	//free(seq5);
	//free(seq4);
	free(seq3);
	free(seq2);
	free(seq1);
	free(seq);
	std::cout<<"程序完成,正常退出!"<<std::endl;
	return 0;
}
