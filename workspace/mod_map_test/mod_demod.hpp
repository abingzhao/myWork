#include"typedefs.h"
#include <complex>

void  mod_mapper(unsigned int sps,
        unsigned int *in,
        std::complex<float>  *out,
        unsigned int noutput_items);
void  mod_demapper(unsigned int sps,
        std::complex<float> *in,
        signed int *out,
        unsigned int noutput_items);
float get_soft_decision(float rx_re,
        float rx_im, float exp_re,
        float exp_im,
        float max_dist);
void  hard_mod_demapper(unsigned int sps,
        std::complex<float> *in,
        unsigned int *out,
        unsigned int noutput_items);
char  hard_decision(std::complex<float> mod_symbol,int bps);
void  soft_mod_demapper(unsigned int sps,
        std::complex<float> *in,
        int8 *out,
        unsigned int noutput_items);
