/*
 * demapper.cc
 *
 *  Created on: 2013-10-26
 *      Author: abing
 */

//Basic header file
#include "pss_gen.h"
#include "sss_gen.h"
#include "crs_gen.h"
#include "mod_demod.h"
#include "lte_sat_define.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
//#include <cstdlib>
#include <assert.h>
using namespace std;

int main()
{
	//Basic variable configuration
	unsigned int N_id_cell=7;
	unsigned int N_id_1=2;
	unsigned int N_id_2=1;
	unsigned int N_rb_dl=6;
	//unsigned int mod_type=2;//QPSK
	//unsigned int mapped_data_length=4;//when input is 0x61(01100001),the output length
	//Generate the PSSs SSSs and CRSs
	gr_complex pss_sequence[PSS_SEQ_LEN];
	gr_complex sss_0_sequence[SSS_SEQ_LEN];
	gr_complex sss_5_sequence[SSS_SEQ_LEN];
	gr_complex crs_sequence[N_SLOT_FRAME][N_CRS_SYMBOL_SLOT][N_PRB_DL_MAX*2];
	pss_gen(N_id_2,pss_sequence);
	sss_gen(N_id_1,N_id_2,sss_0_sequence,sss_5_sequence);
	for (unsigned int i=0;i<N_SLOT_FRAME;i++)
	{
		for (unsigned int j=0;j<N_CRS_SYMBOL_SLOT;j++)
		{
			generate_crs(i,j*4,N_id_cell,crs_sequence[i][j]);
		}
	}
	//Generate the complex-valued modulation symbol

	gr_complex data_required_per_frame[N_rb_dl*12*140-288-N_rb_dl*8*10];
	/*
	gr_complex mapped_data[mapped_data_length];
	unsigned int map_data[8]={1,0,0,1,0,0,1,0};
	mod_mapper(mod_type,map_data,mapped_data,mapped_data_length);
	for (unsigned int i=0;i<mapped_data_length;i++)
	{
		cout<<mapped_data[i]<<endl;
	}
	for(unsigned int i=0;i< N_rb_dl*12*140-288-N_rb_dl*8*10;i++)
	{
		data_required_per_frame[i]=mapped_data[i%mapped_data_length];
	}
	*/
	fstream file_d("out4.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream file1("out2.txt");
	file_d.seekg(0,ios_base::beg);
	for (unsigned int i=0;(i<N_rb_dl*12*140-288-N_rb_dl*8*10)&(!file_d.eof());i++)
	{
		gr_complex temp;
		file_d.read((char*)(&temp),sizeof(temp));
		data_required_per_frame[i] = temp;
		file1<<temp<<endl;
	}
	file1.close();
	file_d.close();
	//Get the GNURadio simulation data in one frame
	gr_complex frame_array[N_rb_dl*12][140];
	fstream file("out3.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream file_to("out1.txt");
	file.seekg(0,ios_base::beg);
	for(unsigned int i=0;(i<N_rb_dl*12*140)&!file.eof();i++)
	{
		gr_complex temp;
		file.read((char *)(&temp),sizeof(temp));
		frame_array[i%(N_rb_dl*12)][i/(N_rb_dl*12)]=temp;
		file_to<<temp<<endl;
	}
	file_to.close();
	file.close();
	//From the GNUradio simulation data get the PSSs SSSs and CRSs
	gr_complex pss_0_sequence_sim[PSS_SEQ_LEN];
	gr_complex pss_5_sequence_sim[PSS_SEQ_LEN];
	gr_complex sss_0_sequence_sim[SSS_SEQ_LEN];
	gr_complex sss_5_sequence_sim[SSS_SEQ_LEN];
	gr_complex crs_sequence_sim[N_SLOT_FRAME][N_CRS_SYMBOL_SLOT][N_PRB_DL_MAX*2];
	gr_complex mod_data_sim[N_rb_dl*12*140-288-N_rb_dl*8*10];
	unsigned int pss_0_index=0;
	unsigned int pss_5_index=0;
	unsigned int sss_0_index=0;
	unsigned int sss_5_index=0;
	unsigned int data_index=0;
	for (unsigned int l=0;l<140;l++)
	{

		for (unsigned int k=0;k<N_rb_dl*12;k++)
		{
			if (((l % N_SYNMBL_SLOT) == 0)|((l % N_SYNMBL_SLOT) == 4))//CRS
			{
				unsigned int v = 3 *((l % N_SYNMBL_SLOT) != 0);
				unsigned int v_shift = N_id_cell;
				int prb_index = k * 2 / N_SC_PRB_DL;
				int m_prime   = prb_index + N_PRB_DL_MAX - N_rb_dl;
				if (k  == (prb_index * 6 + (v + v_shift) % 6))
				{
					crs_sequence_sim[l / 7][1 *((l % N_SYNMBL_SLOT) != 0)][m_prime] = frame_array[k][l];
				}
				else
				{
					mod_data_sim[data_index] = frame_array[k][l];
					data_index++;
				}
			}
			else if ((l % N_SYNMBL_SLOT) == 5)//SSS
			{
				if (  ((l / 7) == 0)  //Ensure this is the 0# slot
				   	 &(k >= N_rb_dl*N_SC_PRB_DL/2 - 36)
				     &(k <= N_rb_dl*N_SC_PRB_DL/2 - 36 + 71))
				{
					if ( (k >= N_rb_dl*N_SC_PRB_DL/2 - 31)
				    	&(k <= N_rb_dl*N_SC_PRB_DL/2 - 31 + 61))
				    {
						sss_0_sequence_sim[sss_0_index] = frame_array[k][l];
						sss_0_index++;
				    }
				    else
				    {
				    	assert(frame_array[k][l] == gr_complex(0,0));
				    }
				}
				else if (  ((l / 7) == 10)  //Ensure this is the 10# slot
					 &(k >= N_rb_dl*N_SC_PRB_DL/2 - 36)
					 &(k <= N_rb_dl*N_SC_PRB_DL/2 - 36 + 71))
				{

					if ( (k >= N_rb_dl*N_SC_PRB_DL/2 - 31)
						&(k <= N_rb_dl*N_SC_PRB_DL/2 - 31 + 61))
					{
						sss_5_sequence_sim[sss_5_index] = frame_array[k][l];
						sss_5_index++;
					}
				    else
					{
						assert(frame_array[k][l] == gr_complex(0,0));
					}
				}
				else
				{
					mod_data_sim[data_index] = frame_array[k][l];
					data_index++;
				}
			}
			else if ((l % N_SYNMBL_SLOT) == 6)//PSS
			{

				if (  ((l / 7) == 0)  //Ensure this is the 0# slot
				   	 &(k >= N_rb_dl*N_SC_PRB_DL/2 - 36)
				     &(k <= N_rb_dl*N_SC_PRB_DL/2 - 36 + 71))
				{
					if ( (k >= N_rb_dl*N_SC_PRB_DL/2 - 31)
				    	&(k <= N_rb_dl*N_SC_PRB_DL/2 - 31 + 61))
				    {
						pss_0_sequence_sim[pss_0_index] = frame_array[k][l];
						pss_0_index++;
				    }
				    else
				    {
				    	assert(frame_array[k][l] == gr_complex(0,0));
				    }
				}
				else if (  ((l / 7) == 10)  //Ensure this is the 10# slot
					 &(k >= N_rb_dl*N_SC_PRB_DL/2 - 36)
					 &(k <= N_rb_dl*N_SC_PRB_DL/2 - 36 + 71))
				{

					if ( (k >= N_rb_dl*N_SC_PRB_DL/2 - 31)
						&(k <= N_rb_dl*N_SC_PRB_DL/2 - 31 + 61))
					{
						pss_5_sequence_sim[pss_5_index] = frame_array[k][l];
						pss_5_index++;
					}
				    else
					{
						assert(frame_array[k][l] == gr_complex(0,0));
					}
				}
				else
				{
					mod_data_sim[data_index] = frame_array[k][l];
					data_index++;
				}
			}
			else
			{
				mod_data_sim[data_index] = frame_array[k][l];
				data_index++;
			}

		}//end for (k^)
	}//end for (l^)
	ofstream file11("c.txt");
	for (unsigned int i=0;i<N_rb_dl*12*140-288-N_rb_dl*8*10;i++)
	{
		file11<<mod_data_sim[i]<<endl;
	}
	for (unsigned int i=0;i<PSS_SEQ_LEN;i++)
	{
		if(abs(pss_sequence[i]-pss_0_sequence_sim[i])>0.0001)
		{
			cout<<"ERROR OCCURED AT "<<i<<"th pss_0_sequence";
			cout<<"	"<<pss_sequence[i]<<"	"<<pss_0_sequence_sim[i]<<endl;//31th:(0.456211,0.889872)
		}
	}
	for (unsigned int i=0;i<PSS_SEQ_LEN;i++)
	{
		if  (abs(pss_sequence[i]-pss_5_sequence_sim[i])>1e-5)
		{
			cout<<"ERROR OCCURED AT "<<i<<"th pss_5_sequence";
			cout<<"	"<<pss_sequence[i]<<"	"<<pss_5_sequence_sim[i]<<endl;
		}

	}
	for (unsigned int i=0;i<SSS_SEQ_LEN;i++)
	{
		if(abs(sss_0_sequence[i]-sss_0_sequence_sim[i])>0.0001)
			cout<<"ERROR OCCURED AT "<<i<<"th sss_0_sequence"<<endl;
	}
	for (unsigned int i=0;i<SSS_SEQ_LEN;i++)
	{
		if(abs(sss_5_sequence[i]-sss_5_sequence_sim[i])>0.0001)
		{
			cout<<"ERROR OCCURED AT "<<i<<"th sss_5_sequence";
			cout<<"	"<<sss_5_sequence[i]<<"	"<<sss_5_sequence_sim[i]<<endl;
		}

	}
	int count=0;
	for (unsigned int i=0;i<N_rb_dl*12*140-288-N_rb_dl*8*10;i++)
	{
		if(abs(mod_data_sim[i]-data_required_per_frame[i])>0.0001)
		{
			count++;
			cout<<"ERROR OCCURED AT "<<i<<"th data_required_per_frame	";
			cout<<mod_data_sim[i]<<"	"<<data_required_per_frame[i]<<endl;
		}
	}
	cout<<"total error is "<<count<<endl;
	return 0;
}



