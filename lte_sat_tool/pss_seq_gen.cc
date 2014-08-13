#include <iostream>
#include <cmath>
#include <cstdlib>
#include <complex>
#include <vector>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <fftw3.h>
#define PSS_SEQ_LEN 62
using namespace std;
typedef std::complex<float> gr_complex;
// Define imaginary constant
// 

void fd_pss_generator(int idx,std::vector<gr_complex> &v)
{
    float root_index=0;
    float real_part,imag_part;
    switch(idx)
    {
        case  0:root_index = 25.0;break;
        case  1:root_index = 29.0;break;
        case  2:root_index = 34.0;break;
        default:throw std::runtime_error("产生本地频域PS时候root index出现错误！");
    }

    for (int i=0;i<62;i++)
    {
        if ( i < (62/2) )
        {
            real_part = cos(-M_PI*root_index*i*(i+1)/63);
            imag_part = sin(-M_PI*root_index*i*(i+1)/63);
        }
        else
        {
            real_part = cos(-M_PI*root_index*(i+1)*(i+2)/63);
            imag_part = sin(-M_PI*root_index*(i+1)*(i+2)/63);
        }
        v.push_back(gr_complex(real_part,imag_part));
    }
}
void fft_cc(gr_complex *in,gr_complex *out,int len)
{
    gr_complex* d_in  = (gr_complex*) fftwf_malloc(sizeof(gr_complex)*len);
    gr_complex* d_out = (gr_complex*) fftwf_malloc(sizeof(gr_complex)*len);
    fftwf_plan d_plan_r = fftwf_plan_dft_1d(len, reinterpret_cast<fftwf_complex*>(d_in), reinterpret_cast<fftwf_complex*>(d_out), FFTW_BACKWARD, FFTW_MEASURE);
    
    memcpy(d_in,in,sizeof(gr_complex)*len);
    fftwf_execute(d_plan_r);
    memcpy(out,d_out,sizeof(gr_complex)*len);
    fftwf_destroy_plan(d_plan_r);  
    fftwf_free(d_in);
    fftwf_free(d_out);
}

void pss_gen(std::vector< std::vector<gr_complex> > &d_pss_local)
    {    
        
        float root_index=0;
        float real_part,imag_part;
        for (int idx = 0; idx < 3; ++idx)
        {
            std::vector<gr_complex> v;
            switch(idx)
            {
                case  0:root_index = 25.0;break;
                case  1:root_index = 29.0;break;
                case  2:root_index = 34.0;break;
                default:throw std::runtime_error("产生本地频域PS时候root index出现错误！");
            }
            for (int i=0;i<62;i++)
            {
                if ( i < (62/2) )
                {
                    real_part = cos(-M_PI*root_index*i*(i+1)/63);
                    imag_part = sin(-M_PI*root_index*i*(i+1)/63);
                }
                else
                {
                    real_part = cos(-M_PI*root_index*(i+1)*(i+2)/63);
                    imag_part = sin(-M_PI*root_index*(i+1)*(i+2)/63);
                }
                v.push_back(gr_complex(real_part,imag_part));
            }
            d_pss_local.push_back(v);
        }
        for (int i = 0; i < 3; ++i)
        {
            std::vector<gr_complex> in(128,0);
            std::vector<gr_complex> out(128,0);
            memcpy(&in[33],&d_pss_local[i][0],sizeof(gr_complex)*31);
            memcpy(&in[65],&d_pss_local[i][31],sizeof(gr_complex)*31);
            fft_cc(&in[0],&out[0],128);
            d_pss_local.push_back(out);
            in.clear();
            out.clear();
        }
        for (int i = 0; i < 3; ++i)
        {
            std::vector<gr_complex> in(256,0);
            std::vector<gr_complex> out(256,0);
            memcpy(&in[97],&d_pss_local[i][0],sizeof(gr_complex)*31);
            memcpy(&in[129],&d_pss_local[i][31],sizeof(gr_complex)*31);
            fft_cc(&in[0],&out[0],256);
            d_pss_local.push_back(out);
            in.clear();
            out.clear();
        }
    }
gr_complex corr(gr_complex *x,gr_complex *y, int len)
{
    #if 1
        gr_complex val = 0;
        for(int i = 0 ; i < len ; i++)
        {
            val += (x[i]*conj(y[i]) );
        }
        return val;
    #endif
    #if 0
    volk_32fc_conjugate_32fc(d_conj_y , y, len);
    volk_32fc_x2_multiply_32fc(res, x, d_conj_y , len);
    volk_32fc_deinterleave_32f_x2(i_vector, q_vector, res, len);
    float i_result = 0.0f;
    float q_result = 0.0f;
    volk_32f_accumulator_s32f(&i_result, i_vector, len);
    volk_32f_accumulator_s32f(&q_result, q_vector, len);
    
    return val;
    #endif
}
float coarse_fcfo_estimation(   gr_complex*  rx_td_pss
                               ,gr_complex*  local_td_pss
                               ,int d_fftl)
{
    
    gr_complex* d_x      = (gr_complex*)fftwf_malloc(sizeof(gr_complex)*256);
    gr_complex* d_y      = (gr_complex*)fftwf_malloc(sizeof(gr_complex)*256);
    gr_complex temp_var1;
    gr_complex temp_var2;
    memcpy(d_x,&rx_td_pss[0],sizeof(gr_complex) * d_fftl);
    memcpy(d_y,&local_td_pss[0],sizeof(gr_complex) * d_fftl);
    temp_var1 = corr(d_x,d_y,d_fftl/2);
    temp_var2 = corr(d_x + d_fftl / 2,d_y + d_fftl / 2,d_fftl / 2);
    fftwf_free(d_x);
    fftwf_free(d_y);
    return -1 * arg(conj(temp_var1) * temp_var2) / M_PI;
    
}

int main( )
{
    int len = 256;
    gr_complex* d_res    = (gr_complex*)fftwf_malloc(sizeof(gr_complex)*len);
    gr_complex* d_x      = (gr_complex*)fftwf_malloc(sizeof(gr_complex)*len);
    gr_complex* d_y      = (gr_complex*)fftwf_malloc(sizeof(gr_complex)*len);
    gr_complex* d_conj_y = (gr_complex*)fftwf_malloc(sizeof(gr_complex)*len);
    float* i_vector = (float*)fftwf_malloc(sizeof(float)*len);
    float* q_vector = (float*)fftwf_malloc(sizeof(float)*len);
    std::vector<std::vector<gr_complex> > d_pss_local;
    pss_gen(d_pss_local);
    cout<<d_pss_local.size()<<endl;
    
    ofstream examplefileC ("../../octave/LTE_sync_ttials/td_pss_128_in_C.txt",ios::out);
    
    std::vector<gr_complex> v;
    fd_pss_generator(1,v);
    cout<<v.size()<<endl;
    gr_complex* in  =(gr_complex*)fftwf_malloc(sizeof(gr_complex)*len);
    gr_complex* out =(gr_complex*)fftwf_malloc(sizeof(gr_complex)*len);
    memset(in,0,sizeof(gr_complex)*len);
    memcpy(in+33+64,&v[0],sizeof(gr_complex)*31);
    memcpy(in+65+64,&v[31],sizeof(gr_complex)*31);
    fft_cc(in,out,len);
    memcpy(d_res,out,sizeof(gr_complex)*len);

    d_res[0] = 0;
    float epsilon =coarse_fcfo_estimation(out,out,len);
    cout<<epsilon<<endl;
    fftwf_free(in);
    fftwf_free(out);
    examplefileC.close();
    fftwf_free(d_res);
    fftwf_free(d_x);
    fftwf_free(d_y);
    fftwf_free(d_conj_y);
    fftwf_free(i_vector);
    fftwf_free(q_vector);
    //cout<<type(arg(gr_complex(1,0)))<<endl;
    cout<<"Have Done!"<<endl;
    return 0;
}