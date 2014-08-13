#include <iostream>
#include <fstream>
#include <complex>
#include <cstring>
#include <vector>
#include <cmath>
#include <fftw3.h>
#include <volk/volk.h>
using namespace std;
typedef complex<float> gr_complex;

    gr_complex corr(gr_complex *x, gr_complex *y, int len)
    {
        gr_complex sum=0;
        for(int j = 0; j < len; ++j)
        {
            sum = sum + x[j]*std::conj(y[j]);
        }
        return sum;
    }

int main()
{
    vector<gr_complex > received;
    fstream file("../../data_ays/cell_dui_dao_cuo.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
    ofstream examplefileC ("../../octave/data1.txt");
    file.seekg(0,ios_base::beg);
    int i=0;
    for(;!file.eof();i++)
    {
        gr_complex temp;
        file.read((char *)(&temp),sizeof(temp));
        received.push_back(temp);
        if(i<20000)
            examplefileC<<temp<<endl;
    }
    examplefileC.close();
    file.close();

    ///////////////////////////////////////////////////////////////////////////
    //std::vector<gr_complex> produced;
    ofstream file_out("../../octave/data.txt");
    int d_fftl=128;
    int d_cpl0=160*d_fftl/2048;
    int d_cpl =144*d_fftl/2048;
    gr_complex *d_cp0=(gr_complex*)malloc(sizeof(gr_complex)*d_cpl0);
    gr_complex *d_cp1=(gr_complex*)malloc(sizeof(gr_complex)*d_cpl0);
    gr_complex *d_res=(gr_complex*)malloc(sizeof(gr_complex)*d_cpl0);
    for (int i = 0; i < received.size()-(d_fftl+1); ++i)
    {
        memcpy(d_cp0,&received[0]+i       ,sizeof(gr_complex)*d_cpl );
        memcpy(d_cp1,&received[0]+i+d_fftl,sizeof(gr_complex)*d_cpl );
        gr_complex val0 = corr(d_cp0,d_cp1,d_cpl);
        gr_complex val1 = corr(d_cp0,d_cp0,d_cpl);
        gr_complex val2 = corr(d_cp1,d_cp1,d_cpl);
        file_out<<abs(val0)*abs(val0)/((abs(val1))*(abs(val2)))<<endl;
    }


    file_out.close();
    free(d_cp0);
    free(d_cp1);
    free(d_res);
    cout<<"Have done!"<<endl;
    return 0;
}


