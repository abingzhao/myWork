#include <iostream>
#include <fstream>
#include <vector>
#include <complex>
#include <algorithm>
#include <fftw3.h>
using namespace std;
typedef complex<float> gr_complex;

void conv(gr_complex *result,const gr_complex *in,const float *coef,int len);

int main ()
{
    std::fstream file1,file2,file3;
    file1.open("../source/one_pulse.dat",ios_base::in|ios_base::binary);
    file2.open("../source/coef_67_128.dat",ios_base::binary|ios_base::in);
    file3.open("../source/conv_result.dat",ios_base::out|ios_base::binary);
    std::vector<float> coef(66);
    file2.read((char*)(&coef[0]),sizeof(float)*66);
    std::reverse(coef.begin(),coef.end());
    std::vector<gr_complex> data(9600);
    file1.read((char*)(&data[0]),sizeof(gr_complex)*9600);
    data.resize(19200,0);
    //data[0]=gr_complex(1,0);
    // data[1000]=gr_complex(1,0);
    std::vector<gr_complex> conv_result(9600);
    for (int i = 0; i < 9600; ++i)
    {
        //if(i<coef.size())
            //conv(&conv_result[i],&data[i],&coef[coef.size()-i],coef.size()-i);
        //else
            conv(&conv_result[i],&data[i],&coef[0],coef.size());
    }

    file3.write((char*)(&conv_result[0]),sizeof(gr_complex)*(conv_result.size()));

    file3.close();
    file2.close();
    file1.close();
    cout<<"Have Done!\n";
    return 0;
}
void conv(gr_complex *result,const gr_complex *in,const float *coef,int len)
{
    float res[2];
    float *realpt = &res[0], *imagpt = &res[1];
    const float *aPtr = (float*)in;
    const float *bPtr = (float*)coef;
    int number = 0;
    *realpt = 0;
    *imagpt = 0;
    for (number = 0; number < len; ++number)
    {
        *realpt += ((*aPtr++) * (*bPtr));
        *imagpt += ((*aPtr++) * (*bPtr++));
    }
    *result = *(gr_complex *)(&res[0]);
}