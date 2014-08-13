#include <vector>
// #include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/foreach.hpp>
#include <iostream>
using namespace std;
#include <cstdlib>
#include <complex>
#include <cassert>
#include <cstring>
typedef std::complex<float> gr_complex;

const int count = 500;



class sincos_table {
    std::vector<float> d_cos;
    size_t d_sz;
    float d_scale;
  public:
    sincos_table(size_t tbl_size) :
        d_cos(tbl_size,1),
        d_sz(tbl_size),
        d_scale(tbl_size/(M_PI*2))
        {
        for(size_t i=0; i<tbl_size; i++){
            d_cos[i] = ::cos(2*M_PI*i/tbl_size);
            }
        }
    // ~sincos_table(){}
    const float sin(float x){
        int idx = (((int)(x*d_scale)) + d_sz - d_sz/4 )% d_sz;
        return d_cos[idx];
        }
    const float cos(float x){
        int idx = (((int)(x*d_scale)) + d_sz) % d_sz;
        return d_cos[idx];
        }
    const float sinc(float x){
        return x==0?1:sin(x)/x;
        }
};
timespec diff(timespec start, timespec end);
void direct_complex_multiply(std::vector<gr_complex> &v);
void table_lookup(std::vector<gr_complex> &v, sincos_table d_table);
// void table_lookup_float_muliply(std::vector<gr_complex> &v, std::vector<gr_complex> v1, sincos_table d_table);
void table_lookup_float_muliply(std::vector<gr_complex> &v,sincos_table d_table);

int main(int argc, char const *argv[])
{
    // using namespace boost::posix_time;
    // namespace pt = boost::posix_time;
    sincos_table d_table(1024*10);
    std::vector<gr_complex> v(1920,0);
    std::vector<gr_complex> v1(1920,0);
    std::vector<gr_complex> v2(1920,0);
    std::vector<gr_complex> v3(1920,0);
    srand (time(NULL));

    BOOST_FOREACH(gr_complex &v_ele,v)
    {
        float i_e=(float)( rand() % 200+400 ) / 600.0;
        float q_e=(float)( rand() % 200+400 ) / 600.0;
        v_ele = gr_complex(i_e,q_e);
    }
    memcpy(&v3[0],&v[0],sizeof(gr_complex)*1920);
    memcpy(&v2[0],&v[0],sizeof(gr_complex)*1920);
    memcpy(&v1[0],&v[0],sizeof(gr_complex)*1920);


    // for (int i = 0; i < 1920; ++i)
    // {
    //     assert((v2[i].real()-v1[i].real())<0.002);
    //     assert((v2[i].imag()-v1[i].imag())<0.002);
    //     assert((v2[i].real()-v3[i].real())<0.002);
    //     assert((v2[i].imag()-v3[i].imag())<0.002);
    //     if(i<10)
    //         std::cout<<"v1="<<v1[i]<<"\tv2="<<v2[i]<<"\tv3="<<v3[i]<<"\n";
    // }





    timespec ts1={0},ts2={0}; 
    clock_gettime(CLOCK_MONOTONIC, &ts1);
    direct_complex_multiply(v1);
    clock_gettime(CLOCK_MONOTONIC, &ts2);

    cout<<diff(ts1,ts2).tv_sec+diff(ts1,ts2).tv_nsec/1e9<<endl;

    timespec ts3={0},ts4={0}; 
    clock_gettime(CLOCK_MONOTONIC, &ts3);
    table_lookup(v2,d_table);
    clock_gettime(CLOCK_MONOTONIC, &ts4);

    cout<<diff(ts3,ts4).tv_sec+diff(ts3,ts4).tv_nsec/1e9<<endl;
    

    timespec ts5={0},ts6={0}; 
    clock_gettime(CLOCK_MONOTONIC, &ts5);
    table_lookup_float_muliply(v3,d_table);
    clock_gettime(CLOCK_MONOTONIC, &ts6);

    cout<<diff(ts5,ts6).tv_sec+diff(ts5,ts6).tv_nsec/1e9<<endl;
    for (int i = 0; i < 1920; ++i)
    {
        // assert((v2[i].real()-v1[i].real())<0.002);
        // assert((v2[i].imag()-v1[i].imag())<0.002);
        // assert((v2[i].real()-v3[i].real())<0.002);
        // assert((v2[i].imag()-v3[i].imag())<0.002);
        if(i<10)
            std::cout<<"v1="<<v1[i]<<"\tv2="<<v2[i]<<"\tv3="<<v3[i]<<"\n";
    }
    std::cout<<"Have Done\n";
    return 0;
}

timespec diff(timespec start, timespec end)
{
    timespec tmp;
    if ((end.tv_nsec-start.tv_nsec)<0) {
        tmp.tv_sec = end.tv_sec-start.tv_sec-1;
        tmp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    } else {
        tmp.tv_sec = end.tv_sec-start.tv_sec;
        tmp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return tmp;
}


void direct_complex_multiply(std::vector<gr_complex> &v)
{
    int   d_fftl     = 128;
    int   d_cpl0     = 10;
    int   d_cpl      = 9;
    float cfo_total  = 0.6;
    int   d_td_subfl = 1920;
    int   subf_idx   = 0;
    for ( subf_idx = 0; subf_idx < count; ++subf_idx)
    {
        int start = 0;
        for (int symb = 0; symb < 14; ++symb)
        {
            if(symb == 0)
            {
                start = 0;
                for (int i = 0; i < d_fftl+d_cpl0; ++i)
                {
                    if(i < d_cpl0)
                        v[ start + i ] = v[ start + i ] * 
                            exp(gr_complex(0,2*M_PI*(i+d_fftl-d_cpl0)*cfo_total/d_fftl));
                    else
                        v[ start + i ] = v[ start + i ] * 
                            exp(gr_complex(0,2*M_PI*(i-d_cpl0)*cfo_total/d_fftl));
                }
            }
            else if((symb > 0)&&(symb < 7))
            {
                start = symb*d_fftl+d_cpl0+(symb-1)*d_cpl;
                for (int i = 0; i < d_fftl+d_cpl; ++i)
                {
                    if(i<d_cpl)
                        v[ start + i ] = v[ start + i ] * 
                            exp(gr_complex(0,2*M_PI*(i+d_fftl-d_cpl)*cfo_total/d_fftl));
                    else
                        v[ start + i ] = v[ start + i ] * 
                            exp(gr_complex(0,2*M_PI*(i-d_cpl)*cfo_total/d_fftl));
                }
            }
            else if(symb == 7)
            {
                start = d_td_subfl / 2;
                for (int i = 0; i < d_fftl+d_cpl0; ++i)
                {
                    if(i<d_cpl0)
                        v[ start + i ] = v[ start + i ] * 
                            exp(gr_complex(0,2*M_PI*(i+d_fftl-d_cpl0)*cfo_total/d_fftl));
                    else
                        v[ start + i ] = v[ start + i ] * 
                            exp(gr_complex(0,2*M_PI*(i-d_cpl0)*cfo_total/d_fftl));
                }
            }
            else
            {
                start =  d_td_subfl/2 + d_cpl0 + (symb-7)*d_fftl+(symb-7-1)*d_cpl;
                for (int i = 0; i < d_fftl+d_cpl; ++i)
                {
                    if(i<d_cpl)
                        v[ start + i ] = v[ start + i ] * 
                            exp(gr_complex(0,2*M_PI*(i+d_fftl-d_cpl)*cfo_total/d_fftl));
                    else
                        v[ start + i ] = v[ start + i ] * 
                            exp(gr_complex(0,2*M_PI*(i-d_cpl)*cfo_total/d_fftl));
                }
            }
        }
    }
}

void table_lookup(std::vector<gr_complex> &v, sincos_table d_table)
{
    int   d_fftl     = 128;
    int   d_cpl0     = 10;
    int   d_cpl      = 9;
    float cfo_total  = 0.6;
    int   d_td_subfl = 1920;
    int   subf_idx   = 0;
    const float temp = 2*M_PI*cfo_total/d_fftl; 
    for ( subf_idx = 0; subf_idx < count; ++subf_idx)
    {
        float d_angle =0;
        int start = 0;
        for (int symb = 0; symb < 14; ++symb)
        {
            if(symb == 0)
            {
                start = 0;
                for (int i = 0; i < d_fftl+d_cpl0; ++i)
                {
                    if(i < d_cpl0)
                    {
                        d_angle = (i+d_fftl-d_cpl0)*temp;
                    }
                    else
                    {
                        d_angle = (i-d_cpl0)*temp;
                    }
                        v[start+i] = v[start+i] * gr_complex(d_table.cos(d_angle),d_table.sin(d_angle));

                }
            }
            if((symb > 0)&&(symb < 7))
            {
                start = symb*d_fftl+d_cpl0+(symb-1)*d_cpl;
                for (int i = 0; i < d_fftl+d_cpl; ++i)
                {
                    if(i < d_cpl)
                    {
                        d_angle = (i+d_fftl-d_cpl)*temp;
                    }
                    else
                    {
                        d_angle = (i-d_cpl)*temp;
                    }
                        v[start+i] = v[start+i] * gr_complex(d_table.cos(d_angle),d_table.sin(d_angle));

                }
            }
            if(symb == 7)
            {
                start = d_td_subfl / 2;
                for (int i = 0; i < d_fftl+d_cpl0; ++i)
                {
                    if(i < d_cpl0)
                    {
                        d_angle = (i+d_fftl-d_cpl0)*temp;
                    }
                    else
                    {
                        d_angle = (i-d_cpl0)*temp;
                    }
                        v[start+i] = v[start+i] * gr_complex(d_table.cos(d_angle),d_table.sin(d_angle));

                }
            }
            if(symb>7)
            {
                start =  d_td_subfl/2 + d_cpl0 + (symb-7)*d_fftl+(symb-7-1)*d_cpl;
                for (int i = 0; i < d_fftl+d_cpl; ++i)
                {
                    if(i < d_cpl)
                    {
                        d_angle = (i+d_fftl-d_cpl)*temp;
                    }
                    else
                    {
                        d_angle = (i-d_cpl)*temp;
                    }
                        v[start+i] = v[start+i] * gr_complex(d_table.cos(d_angle),d_table.sin(d_angle));

                }
            }
        }
    }
}

// void table_lookup_float_muliply(std::vector<gr_complex> &v,std::vector<gr_complex> v1,sincos_table d_table)
void table_lookup_float_muliply(std::vector<gr_complex> &v, sincos_table d_table)
{
    int   d_fftl     = 128;
    int   d_cpl0     = 10;
    int   d_cpl      = 9;
    float cfo_total  = 0.6;
    int   d_td_subfl = 1920;
    int   subf_idx   = 0;
    const float temp = 2*M_PI*M_PI*cfo_total/180.0/d_fftl;
    for ( subf_idx = 0; subf_idx < count; ++subf_idx)
    {
        float d_angle =0;
        int start = 0;
        for (int symb = 0; symb < 14; ++symb)
        {
            if(symb == 0)
            {
                start = 0;
                for (int i = 0; i < d_fftl+d_cpl0; ++i)
                {
                    if(i < d_cpl0)
                    {
                        d_angle = (i+d_fftl-d_cpl0)*temp;
                    }
                    else
                    {
                        d_angle = (i-d_cpl0)*temp;
                    }
                        v[start+i] *=  gr_complex(std::cos(d_angle),std::sin(d_angle));

                }
            }
            if((symb > 0)&&(symb < 7))
            {
                start = symb*d_fftl+d_cpl0+(symb-1)*d_cpl;
                for (int i = 0; i < d_fftl+d_cpl; ++i)
                {
                    if(i < d_cpl)
                    {
                        d_angle = (i+d_fftl-d_cpl)*temp;
                    }
                    else
                    {
                        d_angle = (i-d_cpl)*temp;
                    }
                        v[start+i] *=  gr_complex(std::cos(d_angle),std::sin(d_angle));

                }
            }
            if(symb == 7)
            {
                start = d_td_subfl / 2;
                for (int i = 0; i < d_fftl+d_cpl0; ++i)
                {
                    if(i < d_cpl0)
                    {
                        d_angle = (i+d_fftl-d_cpl0)*temp;
                    }
                    else
                    {
                        d_angle = (i-d_cpl0)*temp;
                    }
                        v[start+i] *=  gr_complex(std::cos(d_angle),std::sin(d_angle));

                }
            }
            if(symb>7)
            {
                start =  d_td_subfl/2 + d_cpl0 + (symb-7)*d_fftl+(symb-7-1)*d_cpl;
                for (int i = 0; i < d_fftl+d_cpl; ++i)
                {
                    if(i < d_cpl)
                    {
                        d_angle = (i+d_fftl-d_cpl)*temp;
                    }
                    else
                    {
                        d_angle = (i-d_cpl)*temp;
                    }
                        v[start+i] *=  gr_complex(std::cos(d_angle),std::sin(d_angle));

                }
            }
        }
    }
}

