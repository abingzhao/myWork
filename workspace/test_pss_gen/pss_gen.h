#ifndef INCLUDED_LTE_SAT_PSS_GEN_H
#define INCLUDED_LTE_SAT_PSS_GEN_H

#include <gnuradio/gr_complex.h>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <boost/foreach.hpp>
#include <boost/thread/condition_variable.hpp>
#include <vector>
#include <cmath>
#include <fftw3.h>

//typedef
    class pss_gen
    {
        
    public:
        typedef boost::shared_ptr<pss_gen> sptr;//定义该类的智能指针
        static sptr make();
        pss_gen(void);
        ~pss_gen();
        const std::vector<std::vector<gr_complex> >& get_td_pss();
        const std::vector<std::vector<gr_complex> >& get_fd_pss(); 
    private:
        std::vector<std::vector<gr_complex> > local_fd_pss;
        std::vector<std::vector<gr_complex> > local_td_pss;
        gr_complex *d_in1;
        gr_complex *d_out1;
        fftwf_plan d_plan_b1;
        gr_complex *d_in2;
        gr_complex *d_out2;
        fftwf_plan d_plan_b2;
        void excute(void);
    };

#endif /* INCLUDED_LTE_SAT_PSS_GEN_H */
