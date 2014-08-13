/*
 * crs_gen_main.cc
 *
 *  Created on: 2013-10-23
 *      Author: abing
 */

#include "crs_gen.h"
#include <complex>
#include <iostream>
#include <fstream>
using namespace std;
int main ()
{
	unsigned int N_subframe=20;//the Number of slot ,20 in one frame
	unsigned int L=2; // For single antenna ,normal CP,there is only 2 value of L:0 and 4
	unsigned int N_id_cell=10;
	const unsigned int CRS_LEN = 2*110;
	complex<float> crs_seq[N_subframe][L][CRS_LEN];



	ofstream file("crs_seq.txt");
	fstream file0("dd0.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	for (unsigned int i=0;i<N_subframe;i++)
	{
		file<<"The CRS seq in the "<<i<<"th slot:"<<endl;
		for (unsigned int j=0;j<L;j++)
		{
			generate_crs(i,j*4,N_id_cell,crs_seq[i][j]);
			for (unsigned int k=0;k<CRS_LEN;k++)
				file<<"	"<<crs_seq[i][j][k];
			file<<endl;
		}
	}

	file.close();
	int total_length = sizeof(crs_seq)/sizeof(complex<float>);
	cout<<total_length<<endl;
	complex <float> result[total_length];
	ofstream file1("result.txt");
	for(int i=0;i<total_length;i++)
	{
		result[i] = crs_seq[(i/440)%20][(i/220)%2][i%220];
		file1<<result[i]<< endl;
	}
	unsigned int j=0;
	for(;!file0.eof();j++)
	{
		complex<float> temp;
		file0.read((char *)(&temp),sizeof(temp));
		temp -=result[j%total_length];
		if (complex<float>(0,0) != temp)
			cout<<"ERROR at the "<<j+1<<"th CRS"<<endl;
	}
	file1.close();
	file0.close();
	cout<<"Done!"<<endl;
	return 0;
}



