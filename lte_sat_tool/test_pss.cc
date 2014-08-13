#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef std::complex<float> gr_complex;
#define PSS_SEQ_LEN 62 
void zc(gr_complex *zc, int cell_id)
    {
        float root_index;
        float real_part,imag_part;
        switch (cell_id)
        {
            case 0: root_index=25.0; break;
            case 1: root_index=29.0; break;
            case 2: root_index=34.0; break;
        }
        for (int i=0;i<PSS_SEQ_LEN;i++)
        {
            if ( i < (PSS_SEQ_LEN/2) )
            {
                real_part = cos(-M_PI*root_index*i*(i+1)/63);
                imag_part = sin(-M_PI*root_index*i*(i+1)/63);
                zc[i] = gr_complex(real_part,imag_part);
            }
            else
            {
                real_part = cos(-M_PI*root_index*(i+1)*(i+2)/63);
                imag_part = sin(-M_PI*root_index*(i+1)*(i+2)/63);
                zc[i+1] = gr_complex(real_part,imag_part);
            }
        }
        zc[31]=gr_complex(0.0);
    }

    void extract_pss(gr_complex *chu, const gr_complex *in)
    {
        memcpy(chu   , in+5   , sizeof(gr_complex)*31 );
        memcpy(chu+32, in+5+31, sizeof(gr_complex)*31 );
    }

    gr_complex 
    corr(gr_complex *in_seq1,gr_complex *in_seq2, int len)
    {
        gr_complex sum=0;
        for (int i = 0; i < len; ++i)
        {
            sum += in_seq2[i] * conj(in_seq1[i]);
        }
        return sum;
    }
int main()
{
	gr_complex *pss=(gr_complex*)malloc(sizeof(gr_complex)*72*5000000);
	fstream file("../grc_work/in_pss_seq.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream outfile0 ("../../octave/pss.txt");
    ofstream outfilepha("../../octave/pss_pha.txt");

	ofstream outfile1 ("../../octave/corr_val_pss.txt");
	//ofstream outfile2 ("corr_val_1.txt");
	//ofstream outfile3 ("corr_val_2.txt");
	file.seekg(0,ios_base::beg);
	int m;
    float argl;
	for(int i=0;!file.eof()&(i<72*500000);i++)
	{
		gr_complex temp;
		file.read((char *)(&temp),sizeof(temp));
		outfile0<<abs(temp)<<std::endl;
        if(i%72==0)
        {
            argl = arg(temp);
            outfilepha<<(argl)<<std::endl;
        }
        else
        {
            argl +=arg(temp);
            outfilepha<<(argl)<<std::endl;

        }
		pss[i]=(temp);
		m=i/72;
	}
	gr_complex d_chu0[63];
    gr_complex d_chu1[63];
    gr_complex d_chu2[63];
    zc(d_chu0,0);
    zc(d_chu1,1);
    zc(d_chu2,2);
    for (int i = 0; i < m; ++i)
    {
    	gr_complex chuX[63];
    	extract_pss(chuX,pss+72*i);
    	outfile1<<(abs(corr(chuX,d_chu0,63))*abs(corr(chuX,d_chu0,63)) / ( abs(corr(chuX,chuX,63)) * abs(corr(d_chu0,d_chu0,63))))<<endl;
    		//<<(abs(corr(chuX,d_chu1,63))*abs(corr(chuX,d_chu1,63)) / ( abs(corr(chuX,chuX,63)) * abs(corr(d_chu1,d_chu1,63))))<<endl
    		//<<(abs(corr(chuX,d_chu2,63))*abs(corr(chuX,d_chu2,63)) / ( abs(corr(chuX,chuX,63)) * abs(corr(d_chu2,d_chu2,63))))<<endl;
    }


    free(pss);
	outfile0.close();
    outfilepha.close();
	outfile1.close();
	file.close();
	cout<<"Have done!"<<endl;
	return 0;
}