#include "sort_algorithm.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <limits.h>
#include <cstring>
#define len 200000
int main()
{
	//------------------------------------------------------------------------------------------------------------------------------	
	int *origin=(int *) malloc (sizeof(int)*len);
	int *seq=(int *) malloc (sizeof(int)*len);
	srand((unsigned)time(NULL));
	for (int i=0;i<len;i++)
	{
		origin[i]=(int)rand()%(len);
		seq[i]=origin[i];
	}
	//------------------------------------------------------------------------------------------------------------------------------	
	clock_t start, finish; 
	//=========
	 start=clock();
	 bubble_sort(seq,len);
	 finish=clock();
	 std::cout<<"冒泡法排序"<<len<<"个数据共用"<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	 free(seq);
	 //=========
	 int *seq1=(int *) malloc (sizeof(int)*len);
	 memcpy(seq1,origin,sizeof(int)*len);
	 
	 start=clock();
	 insertion_sort(seq1,len);
	 finish=clock();
	 std::cout<<"插入法排序"<<len<<"个数据共用"<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	 free(seq1);
	  //========
	 int *seq2=(int *) malloc (sizeof(int)*len);
	 memcpy(seq2,origin,sizeof(int)*len);
	 
	 start=clock();
	 merge_sort(seq2,0,len-1);
	 finish=clock();
	 std::cout<<"分治法排序"<<len<<"个数据共用"<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	 free(seq2);
	  //=========
	 int *seq3=(int *) malloc (sizeof(int)*len);
	 
	 memcpy(seq3,origin,sizeof(int)*len);
	 start=clock();
	 heap_sort(seq3,len);
	 finish=clock();
	 std::cout<<"对排序法排序"<<len<<"个数据共用"<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	 free(seq3);
	  //=========
	 int *seq4=(int *) malloc (sizeof(int)*len);
	 memcpy(seq4,origin,sizeof(int)*len);
	 
	 start=clock();
	 quick_sort(seq4,0,len-1);
	 finish=clock();
	 std::cout<<"快速排序法排序"<<len<<"个数据共用"<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	 free(seq4);
	  //=========
	 /*
	 start=clock();
	 stooge_sort(f,0,len-1);
	  finish=clock();
	 std::cout<<"stooge法排序"<<len<<"个数据共用"<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	 */
	  //=========
	 int *seq5=(int *) malloc (sizeof(int)*len);
	 memcpy(seq5,origin,sizeof(int)*len);
	 
	 start=clock();
	 counting_sort(seq5,len,len-1);
	 finish=clock();
	 std::cout<<"计数法排序"<<len<<"个数据共用"<<((float)(finish - start)/CLOCKS_PER_SEC)<<"秒"<<std::endl;
	 free(seq5);
	 //------------------------------------------------------------------------------------------------------------------------------	
	 //for (int i=0;i<len;i++)
		//std::cout<<origin[i]<<"	"<<f[i]<<std::endl;


	 
	 
	 
	 free(origin);
	 //------------------------------------------------------------------------------------------------------------------------------	
	return 0;
}
