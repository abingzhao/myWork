#include <fftw3.h>
#include <complex>
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
int main()     
{  
    const int N=128;       
    std::cout<<"hh"<<std::endl;
    std::vector<std::complex<float> > v(N+10);
    std::complex<float> *in, *out;    
    std::fstream file;
    file.open("../source/DATA.dat",std::ios_base::in|std::ios_base::binary);

    // fftwf_plan p;                   
    in = (std::complex<float>*) fftwf_malloc(sizeof(std::complex<float>) * N);          
    out = (std::complex<float>*) fftwf_malloc(sizeof(std::complex<float>)* N); 
    
    file.read((char*)(&v[0]),sizeof(std::complex<float>)*v.size());
    
    // for(int i=0;i<N;i++)
    //     std::cout<<i<<";;;;"<<v[i]<<std::endl;
    memcpy(in,&v[10],sizeof(std::complex<float>)*N);
    // for(int i=0;i<N;i++)
    //     std::cout<<in[i]<<std::endl;
    // p = fftw_plan_dft_1d(N, reinterpret_cast<fftwf_complex*>(in)
    //     , reinterpret_cast<fftwf_complex*>(out), FFTW_FORWARD,FFTW_ESTIMATE);  
    fftwf_plan p = fftwf_plan_dft_1d(N, reinterpret_cast<fftwf_complex*>(in), 
      reinterpret_cast<fftwf_complex*>(out), FFTW_FORWARD, FFTW_ESTIMATE);        
    fftwf_execute(p); // 执行变换   
    // for(int i=0;i<N;i++)
    //     std::cout<<*out++<<std::endl;            
    memcpy(&v[0],out,sizeof(std::complex<float>)*N);         
    for(int i=0;i<N;i++)
        std::cout<<v[i]<<std::endl;
    fftwf_free(out);
    fftwf_destroy_plan(p);          
    fftwf_free(in);
    file.close();
    return 0;    
} 