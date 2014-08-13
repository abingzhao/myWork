#include "pss_gen.h"
#include <fftw3.h>
#include <cmath>


    pss_gen::pss_gen()
    {
        d_in1     = (gr_complex*) fftwf_malloc(sizeof(gr_complex)*128);
        d_out1    = (gr_complex*) fftwf_malloc(sizeof(gr_complex)*128);
        d_plan_b1 = fftwf_plan_dft_1d(128, reinterpret_cast<fftwf_complex*>(d_in1),
            reinterpret_cast<fftwf_complex*>(d_out1), FFTW_BACKWARD, FFTW_MEASURE);
        d_in2     = (gr_complex*) fftwf_malloc(sizeof(gr_complex)*256);
        d_out2    = (gr_complex*) fftwf_malloc(sizeof(gr_complex)*256);
        d_plan_b2 = fftwf_plan_dft_1d(256, reinterpret_cast<fftwf_complex*>(d_in2),
            reinterpret_cast<fftwf_complex*>(d_out2), FFTW_BACKWARD, FFTW_MEASURE);
        std::cout<<"Structor!  1"<<std::endl;

        //--------先产生频域数据----------------
        excute();
        std::cout<<"Structor!  2"<<std::endl;


        
    }
    pss_gen::~pss_gen()
    {
        std::cout<<"Destructor!  1"<<std::endl;
        fftwf_free(d_in1); 
        fftwf_free(d_out1);
        fftwf_destroy_plan(d_plan_b1);
        fftwf_free(d_in2);
        fftwf_free(d_out2);
        fftwf_destroy_plan(d_plan_b2);
    }
    void
    pss_gen::excute(void)
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
            local_fd_pss.push_back(v);
        }
        //std::cout<<local_fd_pss.size()<<std::endl;
        //std::cout<<local_fd_pss[0].size()<<std::endl;
        //std::cout<<local_fd_pss[1].size()<<std::endl;
        //std::cout<<local_fd_pss[2].size()<<std::endl;
        std::cout<<"Excute!  1"<<std::endl;

        //--------将频域数据变换到时域----------------
        for (int i = 0; i < 3; ++i)
        {
            //std::cout<<"FOR!  1"<<std::endl;
            //gr_complex* d_in1    = (gr_complex*) fftwf_malloc(sizeof(gr_complex)*128);
            //gr_complex* d_out1   = (gr_complex*) fftwf_malloc(sizeof(gr_complex)*128);
            //fftwf_plan d_plan_b1 = fftwf_plan_dft_1d(128, reinterpret_cast<fftwf_complex*>(d_in1),
            //    reinterpret_cast<fftwf_complex*>(d_out1), FFTW_BACKWARD, FFTW_MEASURE);
            memset(d_in1, 0, sizeof(gr_complex)*128);
            std::cout<<"FOR!  2"<<std::endl;

            memcpy(d_in1+33,&local_fd_pss[i][0],sizeof(gr_complex)*31);
            std::cout<<"FOR!  3"<<std::endl;

            memcpy(d_in1+65,&local_fd_pss[i][31],sizeof(gr_complex)*31);

            fftwf_execute(d_plan_b1);
            std::vector<gr_complex> v(128,0);
            memcpy(&v[0],d_out1,sizeof(gr_complex)*128);
            local_td_pss.push_back(v);
            //std::cout<<local_td_pss.size()<<"   "<<v.size()<<std::endl;
            //v.clear();
            //fftwf_free(d_in1); 

            //fftwf_free(d_out1);

            //fftwf_destroy_plan(d_plan_b1);
            
        }
        std::cout<<"Excute!  2"<<std::endl;

        for (int i = 0; i < 3; ++i)
        {
            //gr_complex* d_in2    = (gr_complex*) fftwf_malloc(sizeof(gr_complex)*256);
            //gr_complex* d_out2   = (gr_complex*) fftwf_malloc(sizeof(gr_complex)*256);
            //fftwf_plan d_plan_b2 = fftwf_plan_dft_1d(256, reinterpret_cast<fftwf_complex*>(d_in2),
            //    reinterpret_cast<fftwf_complex*>(d_out2), FFTW_BACKWARD, FFTW_MEASURE);
            memset(d_in2, 0, 256*sizeof(gr_complex));
            memcpy(d_in2+97,&local_fd_pss[i][0],sizeof(gr_complex)*31);
            memcpy(d_in2+129,&local_fd_pss[i][31],sizeof(gr_complex)*31);
            fftwf_execute(d_plan_b2);
            std::vector<gr_complex> v(256,0);
            memcpy(&v[0],d_out2,sizeof(gr_complex)*256);
            local_td_pss.push_back(v);
            //std::cout<<local_td_pss.size()<<"   "<<v.size()<<std::endl;
            //v.clear();
            //fftwf_free(d_in2); 
            //fftwf_free(d_out2);
            //fftwf_destroy_plan(d_plan_b2);
        }
    }
    const std::vector<std::vector<gr_complex> >& 
    pss_gen::get_td_pss()
    {
        return local_td_pss;
    }
    const std::vector<std::vector<gr_complex> >& 
    pss_gen::get_fd_pss()
    {
        return local_fd_pss;
    } 

