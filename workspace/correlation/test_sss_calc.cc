#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <cstring>
#include <cmath>
#include "xcorr.h"

typedef std::complex<float> gr_complex;
using namespace std;


gr_complex corr(gr_complex *x,gr_complex *y, int len)
    {
        gr_complex val = 0;
        for(int i = 0 ; i < len ; i++){
            val += (x[i]*conj(y[i]) );
        }
        return val;
    }

void xcorr(std::vector<gr_complex> &v, gr_complex *x,gr_complex *y, int len)
    {
        int N = len;

        for (int i = 0 ; i < 2 * N - 1 ; i++){
            if(i < N){
                v.push_back( corr(x+(N-1-i),y,i+1) );
            }
            else{
                v.push_back( corr(x,y+(i-N),2*N-1-i) );
            }
        }
    }
int main()
{
    int d_N_id_2=0;
    int d_N_id_1=0;
    int N_id_1 = d_N_id_1;
    int N_id_2 = d_N_id_2;
/////////sss_gen_c中产生的SSS序列
    int m0,m1;
        int m_prime,q_prime,q;
        /*
         * 根据小区物理表示组N_id_1产生用于决定循环移位的次数的m0和m1
         */
        q_prime = floor(N_id_1/30);
        q       = floor( (N_id_1 + (q_prime*(q_prime + 1)/2) )/30 );
        m_prime = N_id_1 + (q*(q + 1)/2);
        m0     = m_prime % 31;
        m1     = (m0 + int(floor((m_prime/31)))  + 1) % 31;
        
        /*
         * 产生序列s_0_m0和s_1_m1和基准序列s_tilde
         */
        unsigned char s_x_tilde[31];
        char s_tilde[31];
        memset(s_x_tilde,0,sizeof(unsigned char)*31);
        s_x_tilde[4] = 1;
        for (int i=0;i<26;i++)
        {
            s_x_tilde[i+5] = (s_x_tilde[i+2] + s_x_tilde[i]) % 2;
        }
        for (int i=0;i<31;i++)
        {
            s_tilde[i] = 1 - 2 * s_x_tilde[i];
        }
        
        /*
         * 产生扰码序列c_0和c_1的基准序列c_tilde
         */
        unsigned char c_x_tilde[31];
        char c_tilde[31];
        memset(c_x_tilde,0,sizeof(unsigned char)*31);
        c_x_tilde[4] = 1;
        for (int i=0;i<26;i++)
        {
            c_x_tilde[i+5] = (c_x_tilde[i+3] + c_x_tilde[i]) % 2;
        }
        for (int i=0;i<31;i++)
        {
            c_tilde[i] = 1 - 2 * c_x_tilde[i];
        }
        
        /*
         * 产生扰码z_1_m0和z_1_m1的基准序列z_tilde
         */
        unsigned char z_x_tilde[31];
        char z_tilde[31];
        memset(z_x_tilde,0,sizeof(unsigned char)*31);
        z_x_tilde[4] = 1;
        for (int i=0;i<26;i++)
        {
            z_x_tilde[i+5] = (z_x_tilde[i+4] + z_x_tilde[i+2] + z_x_tilde[i+1] + z_x_tilde[i]) % 2;
        }
        for (int i=0;i<31;i++)
        {
            z_tilde[i] = 1 - 2 * z_x_tilde[i];
        }
        
        /*
         * 根据m0和m1以及N_id_2，把所有基准序列经特定的移位产生用于计算SSS的序列
         */
        float s_0_m0[31],s_1_m1[31],c_0[31],c_1[31],z_1_m0[31],z_1_m1[31];
        for (int i=0;i<31;i++)
        {
            s_0_m0[i] = (float) s_tilde[(i + m0) % 31];
            s_1_m1[i] = (float) s_tilde[(i + m1) % 31];
            c_0[i]    = (float) c_tilde[(i + N_id_2) % 31];
            c_1[i]    = (float) c_tilde[(i + N_id_2 + 3) % 31];
            z_1_m0[i] = (float) z_tilde[(i + (m0 % 8)) % 31];
            z_1_m1[i] = (float) z_tilde[(i + (m1 % 8)) % 31];
        }
        // 计算 SSS
        gr_complex sss_0_out[62]=0;
        gr_complex sss_10_out[62]=0;

        for (unsigned int i=0;i<62/2;i++)
        {
            sss_0_out[2*i]   = gr_complex (s_0_m0[i]*c_0[i] , 0);
            sss_10_out[2*i]   = gr_complex (s_1_m1[i]*c_0[i] , 0);

            sss_0_out[2*i+1] = gr_complex (s_1_m1[i]*c_1[i]*z_1_m0[i]*128,0);
            sss_10_out[2*i+1] = gr_complex (s_0_m0[i]*c_1[i]*z_1_m1[i]*128,0);
        }
        gr_complex ssss_ref[62];
        for (int i = 0; i < 62; ++i)
        {
            ssss_ref[i]=gr_complex(s_tilde[i%31],0);
        }
    gr_complex even[31];
    gr_complex odd[31];
    for (int i = 0; i < 31; ++i)
    {
        even[i]=sss_0_out[2*i+0];
        odd[i]=sss_0_out[2*i+1];
        //std::cout<<"s_0_m0["<<i<<"]="<<s_0_m0[i]<<";;even["<<i<<"]="<<even[i]/gr_complex(c_0[i])<<std::endl;
        //std::cout<<"s_1_m1["<<i<<"]="<<s_1_m1[i]<<";;odd["<<i<<"]="<<odd[i]/gr_complex(c_1[i]*z_1_m0[i])<<std::endl;
    }
    for (int i = 0; i < 31; ++i)
    {
        even[i]=even[i]/gr_complex(c_0[i]);
    }
    gr_complex reice[62]=0;
    memcpy(reice,even,sizeof(gr_complex)*31);
    gr_complex result[123];
    cross_c(reice,ssss_ref,result,62,62);
    std::ofstream file("data.txt");
    float max_corr=0;
    int max_pos=-1;
    for (int i = 0; i < 123; ++i)
    {
        //std::cout<<abs(result[i])<<std::endl;
        file<<abs(result[i])<<std::endl;
        if((i>=31)&(i<=61))
            if(max_corr<abs(result[i]))
            {
                max_corr=abs(result[i]);
                max_pos=i;
            }
    }
    int m0_ba=abs(max_pos-61);
    std::cout<<"max_pos="<<max_pos<<";m0_ba="<<m0_ba<<";m0="<<m0<<std::endl;
    file.close();

    for (int i = 0; i < 31; ++i)
    {
        z_1_m0[i] = (float) z_tilde[(i + (m0_ba % 8)) % 31];
    }
    for (int i = 0; i < 31; ++i)
    {
        //odd[i]=odd[i]/gr_complex(c_1[i]*z_1_m0[i]);
        odd[i]=gr_complex(s_1_m1[i]);
    }
    gr_complex reice1[62]=0;
    memcpy(reice1,odd,sizeof(gr_complex)*31);
    gr_complex result1[123];
    cross_c(reice1,ssss_ref,result1,62,62);
    std::ofstream file1("data1.txt");
    for (int i = 0; i < 123; ++i)
    {
        //std::cout<<abs(result[i])<<std::endl;
        file1<<abs(result1[i])<<std::endl;
        if((i>=31)&(i<=61))
            if(max_corr<abs(result1[i]))
            {
                max_corr=abs(result1[i]);
                max_pos=i;
            }
    }
    int m1_ba=abs(max_pos-61);
    file1.close();
    std::cout<<"max_pos="<<max_pos<<";m1_ba="<<m1_ba<<";m1="<<m1<<std::endl;


	cout<<"Have done!"<<endl;
	return 0;
}
