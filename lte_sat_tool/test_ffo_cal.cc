#include <iostream>
#include <fstream>
#include <complex>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <vector>

typedef std::complex<float> gr_complex;

gr_complex corr(gr_complex *in1,gr_complex *in2,int len);

int main()
{
    gr_complex *cped_data = (gr_complex*)malloc(sizeof(gr_complex)*19200);
    std::fstream file("buffer.dat",std::ios_base::in|std::ios_base::app|std::ios::binary);
    file.seekg(std::ios::beg);
    for(int i=0;(!file.eof())&(i<19200+960);i++)
    {
        gr_complex temp;
        file.read((char*)(&temp),sizeof(gr_complex));
        cped_data[i] = temp;
        //std::cout<<temp<<std::endl;
    }
    std::vector<gr_complex> corr_val;
    gr_complex corr_temp;
    //cped_data[0]=0;
    //cped_data[1]=0;
    for (int i = 0; i < 20; ++i)
    {
        corr_temp = corr (cped_data+i*960,cped_data+i*960+128,10);
        corr_val.push_back(corr_temp);
        for (int j = 1; j < 7; ++j)
        {
            corr_temp = corr ( cped_data+i*960+138+(j-1)*(137),cped_data+i*960+138+(j-1)*(137)+128,9);
            corr_val.push_back(corr_temp);
        }
    }
    for (int i = 0; i < 140; ++i)
    {
        std::cout<<i<<"\t\tcorr_val="<<corr_val[i]<<"abs(corr_val)="<<abs(corr_val[i])
            <<";arg(corr_val)="<<arg(corr_val[i])<<std::endl;
    }
    std::cout<<arg(gr_complex(-1,-1))<<"\t\t"<<M_PI*0.75<<std::endl;
    std::cout<<"Done!!"<<std::endl;
    return 0;
}


gr_complex corr(gr_complex *in1,gr_complex *in2, int len)
{
    gr_complex sum=0;
    for (int i = 0; i < len; ++i)
    {
        sum += in1[i]*conj(in2[i]);
    }
    return sum;
}