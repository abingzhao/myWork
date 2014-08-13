/*
 * mod_demod.cpp
 *
 *  Created on: 2013-10-19
 *      Author: abing
 */
#include"mod_demod.hpp"
//#include"typedefs.h"
#include<complex>
#include<cmath>
#include<math.h>
#include<iostream>
using namespace std;

void mod_mapper(unsigned int sps,unsigned int *in,complex<float> *out,unsigned int noutput_items)
{
        float  one_over_sqrt_2  = 1/sqrt(2);
        float  one_over_sqrt_10 = 1/sqrt(10);
        float  one_over_sqrt_42 = 1/sqrt(42);

        cout<<"  1/sqrt(10)="<<one_over_sqrt_10<<endl;
        cout<<"3*1/sqrt(10)="<<3*one_over_sqrt_10<<endl;
        //cout<<"  1/sqrt(42)="<<one_over_sqrt_42<<endl;
        //cout<<"3*1/sqrt(42)="<<3*one_over_sqrt_42<<endl;
        //cout<<"5*1/sqrt(42)="<<5*one_over_sqrt_42<<endl;
        //cout<<"7*1/sqrt(42)="<<7*one_over_sqrt_42<<endl;
        for (unsigned int i=0;i<noutput_items;i++)
                {
                    float d_re=0,d_im=0;
                    switch (sps)
                    {
                        case 1 :// 3GPP TS 36.211 Table 7.1.1-1: BPSK modulation mapping.
                            {
                                if ( 0 == (unsigned int)in[i] )
                                {
                                    d_re = +one_over_sqrt_2;
                                    d_im = +one_over_sqrt_2;
                                }
                                else
                                {
                                    d_re = -one_over_sqrt_2;
                                    d_im = -one_over_sqrt_2;
                                }
                                break;
                            }//end case MOD_TYPE_BPSK
                        case 2 :// 3GPP TS 36.211 Table 7.1.2-1: QPSK modulation mapping.
                            {
                                switch ((unsigned int) (in[i*2+1]|(in[2*i]<<1)))
                                {
                                    case 0:
                                        d_re = +one_over_sqrt_2;
                                        d_im = +one_over_sqrt_2;
                                        break;
                                    case 1:
                                        d_re = +one_over_sqrt_2;
                                        d_im = -one_over_sqrt_2;
                                        break;
                                    case 2:
                                        d_re = -one_over_sqrt_2;
                                        d_im = +one_over_sqrt_2;
                                        break;
                                    case 3:
                                        d_re = -one_over_sqrt_2;
                                        d_im = -one_over_sqrt_2;
                                        break;
                                }
                                break;
                            }//end case MOD_TYPE_QPSK
                        case 4:// 3GPP TS 36.211 Table Table 7.1.3-1: 16QAM modulation mapping.
                            {
                                switch ( (unsigned int ) ( in[4*i+3]|(in[4*i+2]<<1)|(in[4*i+1]<<2)|(in[4*i+0]<<3) ) )
                                {
                                    case 0:
                                        d_re = +1*one_over_sqrt_10;
                                        d_im = +1*one_over_sqrt_10;
                                        break;
                                    case 1:
                                        d_re = +1*one_over_sqrt_10;
                                        d_im = +3*one_over_sqrt_10;
                                        break;
                                    case 2:
                                        d_re = +3*one_over_sqrt_10;
                                        d_im = +1*one_over_sqrt_10;
                                        break;
                                    case 3:
                                        d_re = +3*one_over_sqrt_10;
                                        d_im = +3*one_over_sqrt_10;
                                        break;
                                    case 4:
                                        d_re = +1*one_over_sqrt_10;
                                        d_im = -1*one_over_sqrt_10;
                                        break;
                                    case 5:
                                        d_re = +1*one_over_sqrt_10;
                                        d_im = -3*one_over_sqrt_10;
                                        break;
                                    case 6:
                                        d_re = +3*one_over_sqrt_10;
                                        d_im = -1*one_over_sqrt_10;
                                        break;
                                    case 7:
                                        d_re = +3*one_over_sqrt_10;
                                        d_im = -3*one_over_sqrt_10;
                                        break;
                                    case 8:
                                        d_re = -1*one_over_sqrt_10;
                                        d_im = +1*one_over_sqrt_10;
                                        break;
                                    case 9:
                                        d_re = -1*one_over_sqrt_10;
                                        d_im = +3*one_over_sqrt_10;
                                        break;
                                    case 10:
                                        d_re = -3*one_over_sqrt_10;
                                        d_im = +1*one_over_sqrt_10;
                                        break;
                                    case 11:
                                        d_re = -3*one_over_sqrt_10;
                                        d_im = +3*one_over_sqrt_10;
                                        break;
                                    case 12:
                                        d_re = -1*one_over_sqrt_10;
                                        d_im = -1*one_over_sqrt_10;
                                        break;
                                    case 13:
                                        d_re = -1*one_over_sqrt_10;
                                        d_im = -3*one_over_sqrt_10;
                                        break;
                                    case 14:
                                        d_re = -3*one_over_sqrt_10;
                                        d_im = -1*one_over_sqrt_10;
                                        break;
                                    case 15:
                                        d_re = -3*one_over_sqrt_10;
                                        d_im = -3*one_over_sqrt_10;
                                        break;
                                }
                                break;
                            }//end case MOD_TYPE_16QAM
                        case 6:// 3GPP TS 36.211 Table 7.1.2-1: QPSK modulation mapping.
                            {
                                switch ( (unsigned int ) (     in[6*i+5]
                                                                                    |(in[6*i+4]<<1)
                                                                                    |(in[6*i+3]<<2)
                                                                                    |(in[6*i+2]<<3)
                                                                                    |(in[6*i+1]<<4)
                                                                                    |(in[6*i+0]<<5) ) )
                                                        {
                                                            case 0:
                                                                d_re = +3*one_over_sqrt_42;
                                                                d_im = +3*one_over_sqrt_42;
                                                                break;
                                                            case 1:
                                                                d_re = +3*one_over_sqrt_42;
                                                                d_im = +1*one_over_sqrt_42;
                                                                break;
                                                            case 2:
                                                                d_re = +1*one_over_sqrt_42;
                                                                d_im = +3*one_over_sqrt_42;
                                                                break;
                                                            case 3:
                                                                d_re = +1*one_over_sqrt_42;
                                                                d_im = +1*one_over_sqrt_42;
                                                                break;
                                                            case 4:
                                                                d_re = +3*one_over_sqrt_42;
                                                                d_im = +5*one_over_sqrt_42;
                                                                break;
                                                            case 5:
                                                                d_re = +3*one_over_sqrt_42;
                                                                d_im = +7*one_over_sqrt_42;
                                                                break;
                                                            case 6:
                                                                d_re = +1*one_over_sqrt_42;
                                                                d_im = +5*one_over_sqrt_42;
                                                                break;
                                                            case 7:
                                                                d_re = +1*one_over_sqrt_42;
                                                                d_im = +7*one_over_sqrt_42;
                                                                break;
                                                            case 8:
                                                                d_re = +5*one_over_sqrt_42;
                                                                d_im = +3*one_over_sqrt_42;
                                                                break;
                                                            case 9:
                                                                d_re = +5*one_over_sqrt_42;
                                                                d_im = +1*one_over_sqrt_42;
                                                                break;
                                                            case 10:
                                                                d_re = +7*one_over_sqrt_42;
                                                                d_im = +3*one_over_sqrt_42;
                                                                break;
                                                            case 11:
                                                                d_re = +7*one_over_sqrt_42;
                                                                d_im = +1*one_over_sqrt_42;
                                                                break;
                                                            case 12:
                                                                d_re = +5*one_over_sqrt_42;
                                                                d_im = +5*one_over_sqrt_42;
                                                                break;
                                                            case 13:
                                                                d_re = +5*one_over_sqrt_42;
                                                                d_im = +7*one_over_sqrt_42;
                                                                break;
                                                            case 14:
                                                                d_re = +7*one_over_sqrt_42;
                                                                d_im = +5*one_over_sqrt_42;
                                                                break;
                                                            case 15:
                                                                d_re = +7*one_over_sqrt_42;
                                                                d_im = +7*one_over_sqrt_42;
                                                                break;
                                                            case 16:
                                                                d_re = +3*one_over_sqrt_42;
                                                                d_im = -3*one_over_sqrt_42;
                                                                break;
                                                            case 17:
                                                                d_re = +3*one_over_sqrt_42;
                                                                d_im = -1*one_over_sqrt_42;
                                                                break;
                                                            case 18:
                                                                d_re = +1*one_over_sqrt_42;
                                                                d_im = -3*one_over_sqrt_42;
                                                                break;
                                                            case 19:
                                                                d_re = +1*one_over_sqrt_42;
                                                                d_im = -1*one_over_sqrt_42;
                                                                break;
                                                            case 20:
                                                                d_re = +3*one_over_sqrt_42;
                                                                d_im = -5*one_over_sqrt_42;
                                                                break;
                                                            case 21:
                                                                d_re = +3*one_over_sqrt_42;
                                                                d_im = -7*one_over_sqrt_42;
                                                                break;
                                                            case 22:
                                                                d_re = +1*one_over_sqrt_42;
                                                                d_im = -5*one_over_sqrt_42;
                                                                break;
                                                            case 23:
                                                                d_re = +1*one_over_sqrt_42;
                                                                d_im = -7*one_over_sqrt_42;
                                                                break;
                                                            case 24:
                                                                d_re = +5*one_over_sqrt_42;
                                                                d_im = -3*one_over_sqrt_42;
                                                                break;
                                                            case 25:
                                                                d_re = +5*one_over_sqrt_42;
                                                                d_im = -1*one_over_sqrt_42;
                                                                break;
                                                            case 26:
                                                                d_re = +7*one_over_sqrt_42;
                                                                d_im = -3*one_over_sqrt_42;
                                                                break;
                                                            case 27:
                                                                d_re = +7*one_over_sqrt_42;
                                                                d_im = -1*one_over_sqrt_42;
                                                                break;
                                                            case 28:
                                                                d_re = +5*one_over_sqrt_42;
                                                                d_im = -5*one_over_sqrt_42;
                                                                break;
                                                            case 29:
                                                                d_re = +5*one_over_sqrt_42;
                                                                d_im = -7*one_over_sqrt_42;
                                                                break;
                                                            case 30:
                                                                d_re = +7*one_over_sqrt_42;
                                                                d_im = -5*one_over_sqrt_42;
                                                                break;
                                                            case 31:
                                                                d_re = +7*one_over_sqrt_42;
                                                                d_im = -7*one_over_sqrt_42;
                                                                break;
                                                            case 32:
                                                                d_re = -3*one_over_sqrt_42;
                                                                d_im = +3*one_over_sqrt_42;
                                                                break;
                                                            case 33:
                                                                d_re = -3*one_over_sqrt_42;
                                                                d_im = +1*one_over_sqrt_42;
                                                                break;
                                                            case 34:
                                                                d_re = -1*one_over_sqrt_42;
                                                                d_im = +3*one_over_sqrt_42;
                                                                break;
                                                            case 35:
                                                                d_re = -1*one_over_sqrt_42;
                                                                d_im = +1*one_over_sqrt_42;
                                                                break;
                                                            case 36:
                                                                d_re = -3*one_over_sqrt_42;
                                                                d_im = +5*one_over_sqrt_42;
                                                                break;
                                                            case 37:
                                                                d_re = -3*one_over_sqrt_42;
                                                                d_im = +7*one_over_sqrt_42;
                                                                break;
                                                            case 38:
                                                                d_re = -1*one_over_sqrt_42;
                                                                d_im = +5*one_over_sqrt_42;
                                                                break;
                                                            case 39:
                                                                d_re = -1*one_over_sqrt_42;
                                                                d_im = +7*one_over_sqrt_42;
                                                                break;
                                                            case 40:
                                                                d_re = -5*one_over_sqrt_42;
                                                                d_im = +3*one_over_sqrt_42;
                                                                break;
                                                            case 41:
                                                                d_re = -5*one_over_sqrt_42;
                                                                d_im = +1*one_over_sqrt_42;
                                                                break;
                                                            case 42:
                                                                d_re = -7*one_over_sqrt_42;
                                                                d_im = +3*one_over_sqrt_42;
                                                                break;
                                                            case 43:
                                                                d_re = -7*one_over_sqrt_42;
                                                                d_im = +1*one_over_sqrt_42;
                                                                break;
                                                            case 44:
                                                                d_re = -5*one_over_sqrt_42;
                                                                d_im = +5*one_over_sqrt_42;
                                                                break;
                                                            case 45:
                                                                d_re = -5*one_over_sqrt_42;
                                                                d_im = +7*one_over_sqrt_42;
                                                                break;
                                                            case 46:
                                                                d_re = -7*one_over_sqrt_42;
                                                                d_im = +5*one_over_sqrt_42;
                                                                break;
                                                            case 47:
                                                                d_re = -7*one_over_sqrt_42;
                                                                d_im = +7*one_over_sqrt_42;
                                                                break;
                                                            case 48:
                                                                d_re = -3*one_over_sqrt_42;
                                                                d_im = -3*one_over_sqrt_42;
                                                                break;
                                                            case 49:
                                                                d_re = -3*one_over_sqrt_42;
                                                                d_im = -1*one_over_sqrt_42;
                                                                break;
                                                            case 50:
                                                                d_re = -1*one_over_sqrt_42;
                                                                d_im = -3*one_over_sqrt_42;
                                                                break;
                                                            case 51:
                                                                d_re = -1*one_over_sqrt_42;
                                                                d_im = -1*one_over_sqrt_42;
                                                                break;
                                                            case 52:
                                                                d_re = -3*one_over_sqrt_42;
                                                                d_im = -5*one_over_sqrt_42;
                                                                break;
                                                            case 53:
                                                                d_re = -3*one_over_sqrt_42;
                                                                d_im = -7*one_over_sqrt_42;
                                                                break;
                                                            case 54:
                                                                d_re = -1*one_over_sqrt_42;
                                                                d_im = -5*one_over_sqrt_42;
                                                                break;
                                                            case 55:
                                                                d_re = -1*one_over_sqrt_42;
                                                                d_im = -7*one_over_sqrt_42;
                                                                break;
                                                            case 56:
                                                                d_re = -5*one_over_sqrt_42;
                                                                d_im = -3*one_over_sqrt_42;
                                                                break;
                                                            case 57:
                                                                d_re = -5*one_over_sqrt_42;
                                                                d_im = -1*one_over_sqrt_42;
                                                                break;
                                                            case 58:
                                                                d_re = -7*one_over_sqrt_42;
                                                                d_im = -3*one_over_sqrt_42;
                                                                break;
                                                            case 59:
                                                                d_re = -7*one_over_sqrt_42;
                                                                d_im = -1*one_over_sqrt_42;
                                                                break;
                                                            case 60:
                                                                d_re = -5*one_over_sqrt_42;
                                                                d_im = -5*one_over_sqrt_42;
                                                                break;
                                                            case 61:
                                                                d_re = -5*one_over_sqrt_42;
                                                                d_im = -7*one_over_sqrt_42;
                                                                break;
                                                            case 62:
                                                                d_re = -7*one_over_sqrt_42;
                                                                d_im = -5*one_over_sqrt_42;
                                                                break;
                                                            case 63:
                                                                d_re = -7*one_over_sqrt_42;
                                                                d_im = -7*one_over_sqrt_42;
                                                                break;
                                                        }

                                break;
                            }//end case MOD_TYPE_64QAM
                        //default :throw std::invalid_argument("invalid MODULATION_TYPE type");
                    }//end switch
                    out[i]=complex<float>(d_re,d_im);
                }//end for

}

void mod_demapper(unsigned int sps,std::complex<float> *in,signed int *out,unsigned int noutput_items)
{
    //float  one_over_sqrt_2  = 1/sqrt(2);
    float  one_over_sqrt_10 = 1/sqrt(10);
    float  one_over_sqrt_42 = 1/sqrt(42);

    for (unsigned int i=0;i<noutput_items;i++)
    {
                float d_re=real(in[i]),d_im=imag(in[i]);
                float ang = atan2(imag(in[i]), real(in[i]));

                switch (sps)
                {
                    case 1 :// 3GPP TS 36.211 Table 7.1.1-1: BPSK modulation mapping.
                    {
                        if((ang > -M_PI/4) && (ang < 3*M_PI/4))
                            out[i]=0x0;
                        else
                            out[i]=0x1;
                        break;
                    }
                    case 2 :// 3GPP TS 36.211 Table 7.1.2-1: QPSK modulation mapping.
                    {
                        if((ang >= 0) && (ang < M_PI/2))
                        {
                            out[2*i]   = 0x0;
                            out[2*i+1] = 0x0;
                        }
                        else if((ang >= -M_PI/2) && (ang < 0))
                        {
                            out[2*i]   = 0x0;
                            out[2*i+1] = 0x1;
                        }
                        else if((ang >= M_PI/2) && (ang < M_PI))
                        {
                            out[2*i]   = 0x1;
                            out[2*i+1] = 0x0;
                        }
                        else
                        {
                            out[2*i]   = 0x1;
                            out[2*i+1] = 0x1;
                        }
                        break;
                    }//end case 2
                    case 4:// 3GPP TS 36.211  Table 7.1.3-1: 16QAM modulation mapping.
                    {
                        if (d_re >= 2*one_over_sqrt_10)
                        {
                            if (d_im >= 2*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x1; out[4*i+1] = 0x1;
                                out[4*i+2] = 0x0; out[4*i+3] = 0x0;
                            }
                            else if (d_im >= 0*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x0; out[4*i+1] = 0x1;
                                out[4*i+2] = 0x0; out[4*i+3] = 0x0;
                            }
                            else if (d_im >= -2*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x0; out[4*i+1] = 0x1;
                                out[4*i+2] = 0x1; out[4*i+3] = 0x0;
                            }
                            else
                            {
                                out[4*i]   = 0x1; out[4*i+1] = 0x1;
                                out[4*i+2] = 0x1; out[4*i+3] = 0x0;
                            }
                        }
                        else if (d_re >= 0*one_over_sqrt_10)
                        {
                            if (d_im >= 2*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x1; out[4*i+1] = 0x0;
                                out[4*i+2] = 0x0; out[4*i+3] = 0x0;
                            }
                            else if (d_im >= 0*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x0; out[4*i+1] = 0x0;
                                out[4*i+2] = 0x0; out[4*i+3] = 0x0;
                            }
                            else if (d_im >= -2*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x0; out[4*i+1] = 0x0;
                                out[4*i+2] = 0x1; out[4*i+3] = 0x0;
                            }
                            else
                            {
                                out[4*i]   = 0x1; out[4*i+1] = 0x0;
                                out[4*i+2] = 0x1; out[4*i+3] = 0x0;
                            }
                        }
                        else if (d_re >= -2*one_over_sqrt_10)
                        {
                            if (d_im >= 2*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x1; out[4*i+1] = 0x0;
                                out[4*i+2] = 0x0; out[4*i+3] = 0x1;
                            }
                            else if (d_im >= 0*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x0; out[4*i+1] = 0x0;
                                out[4*i+2] = 0x0; out[4*i+3] = 0x1;
                            }
                            else if (d_im >= -2*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x0; out[4*i+1] = 0x0;
                                out[4*i+2] = 0x1; out[4*i+3] = 0x1;
                            }
                            else
                            {
                                out[4*i]   = 0x1; out[4*i+1] = 0x0;
                                out[4*i+2] = 0x1; out[4*i+3] = 0x1;
                            }
                        }
                        else
                        {
                            if (d_im >= 2*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x1; out[4*i+1] = 0x1;
                                out[4*i+2] = 0x0; out[4*i+3] = 0x1;
                            }
                            else if (d_im >= 0*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x0; out[4*i+1] = 0x1;
                                out[4*i+2] = 0x0; out[4*i+3] = 0x1;
                            }
                            else if (d_im >= -2*one_over_sqrt_10)
                            {
                                out[4*i]   = 0x0; out[4*i+1] = 0x1;
                                out[4*i+2] = 0x1; out[4*i+3] = 0x1;
                            }
                            else
                            {
                                out[4*i]   = 0x1; out[4*i+1] = 0x1;
                                out[4*i+2] = 0x1; out[4*i+3] = 0x1;
                            }
                        }
                        break;
                    }//end case 4
                    case 6:// 3GPP TS 36.211 Table 7.1.4-1: 64QAM modulation mapping.
                    {
                        if     (d_re >=  6*one_over_sqrt_42)
                        {
                            if     (d_im >=  6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >=  4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >=  2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >=  0*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                        }
                        else if(d_re >=  4*one_over_sqrt_42)
                        {
                            if     (d_im >=  6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >=  4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >=  2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >=  0*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                        }
                        else if(d_re >=  2*one_over_sqrt_42)
                        {
                            if     (d_im >=  6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >=  4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }


                            else if(d_im >=  2*one_over_sqrt_42)

                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >=  0*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                        }
                        else if(d_re >=  0*one_over_sqrt_42)
                        {
                            if     (d_im >=  6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >=  4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >=  2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >=  0*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else if(d_im >= -6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                            else
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
                            }
                        }
                        else if(d_re >= -2*one_over_sqrt_42)
                        {
                            if     (d_im >=  6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  0*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                        }
                        else if(d_re >= -4*one_over_sqrt_42)
                        {
                            if     (d_im >=  6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  0*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                        }
                        else if(d_re >= -6*one_over_sqrt_42)
                        {
                            if     (d_im >=  6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  0*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                        }
                        else
                        {
                            if     (d_im >=  6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >=  0*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -2*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -4*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else if(d_im >= -6*one_over_sqrt_42)
                            {
                                out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                            else
                            {
                                out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
                                out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
                            }
                        }
                        break;
            }//end case 6
        }//end switch (N_bits_per_mod_symbol)
    }
}


void hard_mod_demapper( unsigned int sps,
						std::complex<float> *in,
						unsigned int *out,
						unsigned int noutput_items)
{
    for (unsigned int i=0;i<noutput_items;i++)
    {
        //char x = hard_decision(in[(int)ceil(i/sps)],sps);
        //out[i] = (unsigned int)(x>>(i%sps))&0x1;
        unsigned char demap_temp = hard_decision(in[(int)ceil(i/sps)],sps);
        unsigned char x = (demap_temp<<(i%sps+(8-sps)))&0x80;
        out[i] = (x>>7);
    }
}
void  soft_mod_demapper(unsigned int sps,
                        std::complex<float> *in,
                        int8 *out,
                        unsigned int noutput_items)
{
    float  ang;
    float  sd;
    float  act_re;
    float  act_im;
    float  act_dist;
    float  one_over_sqrt_2  = 1/sqrt(2);
    float  one_over_sqrt_10 = 1/sqrt(10);
    float  one_over_sqrt_42 = 1/sqrt(42);


    if (1==sps)
    {
    	act_dist = sqrt(one_over_sqrt_2 *one_over_sqrt_2 + one_over_sqrt_2 *one_over_sqrt_2 );
        for (unsigned int i=0;i<noutput_items;i++)
        {
            ang = atan2(imag(in[i]), real(in[i]));
            if((ang > -M_PI/4) && (ang < 3*M_PI/4))
            {
                act_re = +one_over_sqrt_2;
                act_im = +one_over_sqrt_2;
                sd     = get_soft_decision(real(in[i]), imag(in[i]), act_re, act_im, act_dist);
                out[i] = +(int8)(127*sd);
            }
            else
            {
                act_re = -one_over_sqrt_2;
                act_im = -one_over_sqrt_2;
                sd     = get_soft_decision(real(in[i]), imag(in[i]), act_re, act_im, act_dist);
                out[i] = -(int8)(127*sd);
            }
        }
    }
    else if(2==sps)
    {
    	act_dist = sqrt(one_over_sqrt_2 *one_over_sqrt_2 + one_over_sqrt_2 *one_over_sqrt_2 );
        for(unsigned int i=0; i<noutput_items/2; i++)
        {
            ang = atan2(imag(in[i]), real(in[i]));
            if((ang >= 0) && (ang < M_PI/2))
            {
                act_re     = +one_over_sqrt_2;
                act_im     = +one_over_sqrt_2;
                sd         = get_soft_decision(real(in[i]), imag(in[i]), act_re, act_im, act_dist);
                out[i*2+0] = +(int8)(127*sd);
                out[i*2+1] = +(int8)(127*sd);
            }
            else if((ang >= -M_PI/2) && (ang < 0))
            {
                act_re     = +one_over_sqrt_2;
                act_im     = -one_over_sqrt_2;
                sd         = get_soft_decision(real(in[i]), imag(in[i]), act_re, act_im, act_dist);
                out[i*2+0] = +(int8)(127*sd);
                out[i*2+1] = -(int8)(127*sd);
            }
            else if((ang >= M_PI/2) && (ang < M_PI))
            {
                act_re     = -one_over_sqrt_2;
                act_im     = +one_over_sqrt_2;
                sd         = get_soft_decision(real(in[i]), imag(in[i]), act_re, act_im, act_dist);
                out[i*2+0] = -(int8)(127*sd);
                out[i*2+1] = +(int8)(127*sd);
            }
            else
            {
                act_re     = -one_over_sqrt_2;
                act_im     = -one_over_sqrt_2;
                sd         = get_soft_decision(real(in[i]), imag(in[i]), act_re, act_im, act_dist);
                out[i*2+0] = -(int8)(127*sd);
                out[i*2+1] = -(int8)(127*sd);
            }
        }
    }
    else if (4 == sps)
    {
    	act_dist   = sqrt(one_over_sqrt_10*one_over_sqrt_10+one_over_sqrt_10*one_over_sqrt_10);
        for(unsigned int i=0; i<noutput_items/4; i++)
        {
            float d_re=real(in[i]),d_im=imag(in[i]);
            if ( d_re>= 2*one_over_sqrt_10)
            {
                if(d_im >= 2*one_over_sqrt_10)
                {
                    act_re     = +3*one_over_sqrt_10;
                    act_im     = +3*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = +(int8)(127*sd);
                    out[i*4+1] = +(int8)(127*sd);
                    out[i*4+2] = -(int8)(127*sd);
                    out[i*4+3] = -(int8)(127*sd);
                }
                else if (d_im >= 0*one_over_sqrt_10)
                {
                    act_re     = +3*one_over_sqrt_10;
                    act_im     = +1*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = +(int8)(127*sd);
                    out[i*4+1] = +(int8)(127*sd);
                    out[i*4+2] = -(int8)(127*sd);
                    out[i*4+3] = +(int8)(127*sd);
                }
                else if (d_im >= -2*one_over_sqrt_10)
                {
                    act_re     = +3*one_over_sqrt_10;
                    act_im     = -1*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = +(int8)(127*sd);
                    out[i*4+1] = -(int8)(127*sd);
                    out[i*4+2] = -(int8)(127*sd);
                    out[i*4+3] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = +3*one_over_sqrt_10;
                    act_im     = -3*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = +(int8)(127*sd);
                    out[i*4+1] = -(int8)(127*sd);
                    out[i*4+2] = -(int8)(127*sd);
                    out[i*4+3] = -(int8)(127*sd);
                }
            }
            else if (d_re >= 0*one_over_sqrt_10)
            {
                if      (d_im >= 2*one_over_sqrt_10)
                {
                    act_re     = +1*one_over_sqrt_10;
                    act_im     = +3*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = +(int8)(127*sd);
                    out[i*4+1] = +(int8)(127*sd);
                    out[i*4+2] = +(int8)(127*sd);
                    out[i*4+3] = -(int8)(127*sd);
                }
                else if (d_im >= 0*one_over_sqrt_10)
                {
                    act_re     = +1*one_over_sqrt_10;
                    act_im     = +1*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = +(int8)(127*sd);
                    out[i*4+1] = +(int8)(127*sd);
                    out[i*4+2] = +(int8)(127*sd);
                    out[i*4+3] = +(int8)(127*sd);
                }
                else if (d_im >= -2*one_over_sqrt_10)
                {
                    act_re     = +1*one_over_sqrt_10;
                    act_im     = -1*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = +(int8)(127*sd);
                    out[i*4+1] = -(int8)(127*sd);
                    out[i*4+2] = +(int8)(127*sd);
                    out[i*4+3] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = +1*one_over_sqrt_10;
                    act_im     = -3*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = +(int8)(127*sd);
                    out[i*4+1] = -(int8)(127*sd);
                    out[i*4+2] = +(int8)(127*sd);
                    out[i*4+3] = -(int8)(127*sd);
                }
            }
            else if (d_re >= -2*one_over_sqrt_10)
            {
                if      (d_im >= 2*one_over_sqrt_10)
                {
                    act_re     = -1*one_over_sqrt_10;
                    act_im     = +3*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = -(int8)(127*sd);
                    out[i*4+1] = +(int8)(127*sd);
                    out[i*4+2] = +(int8)(127*sd);
                    out[i*4+3] = -(int8)(127*sd);
                }
                else if (d_im >= 0*one_over_sqrt_10)
                {
                    act_re     = -1*one_over_sqrt_10;
                    act_im     = +1*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = -(int8)(127*sd);
                    out[i*4+1] = +(int8)(127*sd);
                    out[i*4+2] = +(int8)(127*sd);
                    out[i*4+3] = +(int8)(127*sd);
                }
                else if (d_im >= -2*one_over_sqrt_10)
                {
                    act_re     = -1*one_over_sqrt_10;
                    act_im     = -1*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = -(int8)(127*sd);
                    out[i*4+1] = -(int8)(127*sd);
                    out[i*4+2] = +(int8)(127*sd);
                    out[i*4+3] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = -1*one_over_sqrt_10;
                    act_im     = -3*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = -(int8)(127*sd);
                    out[i*4+1] = -(int8)(127*sd);
                    out[i*4+2] = +(int8)(127*sd);
                    out[i*4+3] = -(int8)(127*sd);
                }
            }
            else
            {
                if         (d_im >= 2*one_over_sqrt_10)
                {
                    act_re     = -3*one_over_sqrt_10;
                    act_im     = +3*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = -(int8)(127*sd);
                    out[i*4+1] = +(int8)(127*sd);
                    out[i*4+2] = -(int8)(127*sd);
                    out[i*4+3] = -(int8)(127*sd);
                }
                else if (d_im >= 0*one_over_sqrt_10)
                {
                    act_re     = -3*one_over_sqrt_10;
                    act_im     = +1*one_over_sqrt_10;

                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = -(int8)(127*sd);
                    out[i*4+1] = +(int8)(127*sd);
                    out[i*4+2] = -(int8)(127*sd);
                    out[i*4+3] = +(int8)(127*sd);
                }
                else if (d_im >= -2*one_over_sqrt_10)
                {
                    act_re     = -3*one_over_sqrt_10;
                    act_im     = -1*one_over_sqrt_10;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = -(int8)(127*sd);
                    out[i*4+1] = -(int8)(127*sd);
                    out[i*4+2] = -(int8)(127*sd);
                    out[i*4+3] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = -3*one_over_sqrt_10;
                    act_im     = -3*one_over_sqrt_10;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*4+0] = -(int8)(127*sd);
                    out[i*4+1] = -(int8)(127*sd);
                    out[i*4+2] = -(int8)(127*sd);
                    out[i*4+3] = -(int8)(127*sd);
                }
            }
        }
    }
    else if (6 == sps)
    {
    	act_dist = sqrt(one_over_sqrt_42 *one_over_sqrt_42 + one_over_sqrt_42 *one_over_sqrt_42 );
    	for (unsigned int i=0;i<noutput_items/6;i++)
    	{
    		float d_re=real(in[i]),d_im=imag(in[i]);
            if     (d_re >=  6*one_over_sqrt_42)
            {
                if     (d_im >=  6*one_over_sqrt_42)
                {
                    act_re     = +7*one_over_sqrt_42;
                    act_im     = +7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >=  4*one_over_sqrt_42)
                {
                    act_re     = +7*one_over_sqrt_42;
                    act_im     = +5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  2*one_over_sqrt_42)
                {
                    act_re     = +7*one_over_sqrt_42;
                    act_im     = +3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  0*one_over_sqrt_42)
                {
                    act_re     = +7*one_over_sqrt_42;
                    act_im     = +1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -2*one_over_sqrt_42)
                {
                    act_re     = +7*one_over_sqrt_42;
                    act_im     = -1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -4*one_over_sqrt_42)
                {
                    act_re     = +7*one_over_sqrt_42;
                    act_im     = -3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >= -6*one_over_sqrt_42)
                {
                    act_re     = +7*one_over_sqrt_42;
                    act_im     = -5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = +7*one_over_sqrt_42;
                    act_im     = -7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
            }
            else if(d_re >=  4*one_over_sqrt_42)
            {
                if     (d_im >=  6*one_over_sqrt_42)
                {
                    act_re     = +5*one_over_sqrt_42;
                    act_im     = +7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >=  4*one_over_sqrt_42)
                {
                    act_re     = +5*one_over_sqrt_42;
                    act_im     = +5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  2*one_over_sqrt_42)
                {
                    act_re     = +5*one_over_sqrt_42;
                    act_im     = +3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  0*one_over_sqrt_42)
                {
                    act_re     = +5*one_over_sqrt_42;
                    act_im     = +1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -2*one_over_sqrt_42)
                {
                    act_re     = +5*one_over_sqrt_42;
                    act_im     = -1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -4*one_over_sqrt_42)
                {
                    act_re     = +5*one_over_sqrt_42;
                    act_im     = -3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >= -6*one_over_sqrt_42)
                {
                    act_re     = +5*one_over_sqrt_42;
                    act_im     = -5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = +5*one_over_sqrt_42;
                    act_im     = -7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
            }
            else if(d_re >=  2*one_over_sqrt_42)
            {
                if     (d_im >=  6*one_over_sqrt_42)
                {
                    act_re     = +3*one_over_sqrt_42;
                    act_im     = +7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >=  4*one_over_sqrt_42)
                {
                    act_re     = +3*one_over_sqrt_42;
                    act_im     = +5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  2*one_over_sqrt_42)
                {
                    act_re     = +3*one_over_sqrt_42;
                    act_im     = +3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  0*one_over_sqrt_42)
                {
                    act_re     = +3*one_over_sqrt_42;
                    act_im     = +1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -2*one_over_sqrt_42)
                {
                    act_re     = +3*one_over_sqrt_42;
                    act_im     = -1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -4*one_over_sqrt_42)
                {
                    act_re     = +3*one_over_sqrt_42;
                    act_im     = -3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >= -6*one_over_sqrt_42)
                {
                    act_re     = +3*one_over_sqrt_42;
                    act_im     = -5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = +3*one_over_sqrt_42;
                    act_im     = -7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
            }
            else if(d_re >=  0*one_over_sqrt_42)
            {
                if     (d_im >=  6*one_over_sqrt_42)
                {
                    act_re     = +1*one_over_sqrt_42;
                    act_im     = +7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >=  4*one_over_sqrt_42)
                {
                    act_re     = +1*one_over_sqrt_42;
                    act_im     = +5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  2*one_over_sqrt_42)
                {
                    act_re     = +1*one_over_sqrt_42;
                    act_im     = +3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  0*one_over_sqrt_42)
                {
                    act_re     = +1*one_over_sqrt_42;
                    act_im     = +1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -2*one_over_sqrt_42)
                {
                    act_re     = +1*one_over_sqrt_42;
                    act_im     = -1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -4*one_over_sqrt_42)
                {
                    act_re     = +1*one_over_sqrt_42;
                    act_im     = -3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >= -6*one_over_sqrt_42)
                {
                    act_re     = +1*one_over_sqrt_42;
                    act_im     = -5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = +1*one_over_sqrt_42;
                    act_im     = -7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = +(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
            }
            else if(d_re >= -2*one_over_sqrt_42)
            {
                if     (d_im >=  6*one_over_sqrt_42)
                {
                    act_re     = -1*one_over_sqrt_42;
                    act_im     = +7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >=  4*one_over_sqrt_42)
                {
                    act_re     = -1*one_over_sqrt_42;
                    act_im     = +5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  2*one_over_sqrt_42)
                {
                    act_re     = -1*one_over_sqrt_42;
                    act_im     = +3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  0*one_over_sqrt_42)
                {
                    act_re     = -1*one_over_sqrt_42;
                    act_im     = +1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -2*one_over_sqrt_42)
                {
                    act_re     = -1*one_over_sqrt_42;
                    act_im     = -1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -4*one_over_sqrt_42)
                {
                    act_re     = -1*one_over_sqrt_42;
                    act_im     = -3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >= -6*one_over_sqrt_42)
                {
                    act_re     = -1*one_over_sqrt_42;
                    act_im     = -5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = -1*one_over_sqrt_42;
                    act_im     = -7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
            }
            else if(d_re >= -4*one_over_sqrt_42)
            {
                if     (d_im >=  6*one_over_sqrt_42)
                {
                    act_re     = -3*one_over_sqrt_42;
                    act_im     = +7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >=  4*one_over_sqrt_42)
                {
                    act_re     = -3*one_over_sqrt_42;
                    act_im     = +5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  2*one_over_sqrt_42)
                {
                    act_re     = -3*one_over_sqrt_42;
                    act_im     = +3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  0*one_over_sqrt_42)
                {
                    act_re     = -3*one_over_sqrt_42;
                    act_im     = +1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -2*one_over_sqrt_42)
                {
                    act_re     = -3*one_over_sqrt_42;
                    act_im     = -1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -4*one_over_sqrt_42)
                {
                    act_re     = -3*one_over_sqrt_42;
                    act_im     = -3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >= -6*one_over_sqrt_42)
                {
                    act_re     = -3*one_over_sqrt_42;
                    act_im     = -5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = -3*one_over_sqrt_42;
                    act_im     = -7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = +(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
            }
            else if(d_re >= -6*one_over_sqrt_42)
            {
                if     (d_im >=  6*one_over_sqrt_42)
                {
                    act_re     = -5*one_over_sqrt_42;
                    act_im     = +7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >=  4*one_over_sqrt_42)
                {
                    act_re     = -5*one_over_sqrt_42;
                    act_im     = +5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  2*one_over_sqrt_42)
                {
                    act_re     = -5*one_over_sqrt_42;
                    act_im     = +3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  0*one_over_sqrt_42)
                {
                    act_re     = -5*one_over_sqrt_42;
                    act_im     = +1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -2*one_over_sqrt_42)
                {
                    act_re     = -5*one_over_sqrt_42;
                    act_im     = -1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -4*one_over_sqrt_42)
                {
                    act_re     = -5*one_over_sqrt_42;
                    act_im     = -3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >= -6*one_over_sqrt_42)
                {
                    act_re     = -5*one_over_sqrt_42;
                    act_im     = -5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = -5*one_over_sqrt_42;
                    act_im     = -7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = +(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
            }
            else
            {
                if     (d_im >=  6*one_over_sqrt_42)
                {
                    act_re     = -7*one_over_sqrt_42;
                    act_im     = +7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >=  4*one_over_sqrt_42)
                {
                    act_re     = -7*one_over_sqrt_42;
                    act_im     = +5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  2*one_over_sqrt_42)
                {
                    act_re     = -7*one_over_sqrt_42;
                    act_im     = +3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >=  0*one_over_sqrt_42)
                {
                    act_re     = -7*one_over_sqrt_42;
                    act_im     = +1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = +(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -2*one_over_sqrt_42)
                {
                    act_re     = -7*one_over_sqrt_42;
                    act_im     = -1*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
                else if(d_im >= -4*one_over_sqrt_42)
                {
                    act_re     = -7*one_over_sqrt_42;
                    act_im     = -3*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = +(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else if(d_im >= -6*one_over_sqrt_42)
                {
                    act_re     = -7*one_over_sqrt_42;
                    act_im     = -5*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = +(int8)(127*sd);
                }
                else
                {
                    act_re     = -7*one_over_sqrt_42;
                    act_im     = -7*one_over_sqrt_42;
                    sd         = get_soft_decision(d_re, d_im, act_re, act_im, act_dist);
                    out[i*6+0] = -(int8)(127*sd);
                    out[i*6+1] = -(int8)(127*sd);
                    out[i*6+2] = -(int8)(127*sd);
                    out[i*6+3] = -(int8)(127*sd);
                    out[i*6+4] = -(int8)(127*sd);
                    out[i*6+5] = -(int8)(127*sd);
                }
            }
    	}
    }
    else
        std::cout<<"Wrong modulation type"<<std::endl;
}


char hard_decision(std::complex<float> mod_symbol,int bps)
    {

        float  one_over_sqrt_10 = 1/sqrt(10);
        float  one_over_sqrt_42 = 1/sqrt(42);

        float d_re=real(mod_symbol),d_im=imag(mod_symbol);
        float ang = atan2(imag(mod_symbol), real(mod_symbol));

        switch (bps)
            {
                case 1 :// 3GPP TS 36.211 Table 7.1.1-1: BPSK modulation mapping.
                {
                    if((ang > -M_PI/4) && (ang < 3*M_PI/4))  return 0x0;//0
                    else                                     return 0x1;//1
                    break;
                }
                case 2 :// 3GPP TS 36.211 Table 7.1.2-1: QPSK modulation mapping.
                {
                    if     ((ang >= 0) && (ang < M_PI/2))    return 0x0;//00
                    else if((ang >= -M_PI/2) && (ang < 0))   return 0x1;//01
                    else if((ang >= M_PI/2) && (ang < M_PI)) return 0x2;//10
                    else                                     return 0x3;//11
                    break;
                }//end case 2
                case 4:// 3GPP TS 36.211  Table 7.1.3-1: 16QAM modulation mapping.
                {
                    if (d_re >= 2*one_over_sqrt_10)
                    {
                        if      (d_im >= 2*one_over_sqrt_10)  return 0x3;//0011
                        else if (d_im >= 0*one_over_sqrt_10)  return 0x2;//0010
                        else if (d_im >= -2*one_over_sqrt_10) return 0x6;//0110
                        else                                        return 0x7;//0111
                    }
                    else if (d_re >= 0*one_over_sqrt_10)
                    {
                        if      (d_im >= 2*one_over_sqrt_10)  return 0x1;//0001
                        else if (d_im >= 0*one_over_sqrt_10)  return 0x0;//0000
                        else if (d_im >= -2*one_over_sqrt_10) return 0x4;//0100
                        else                                       return 0x5;//0101
                    }
                    else if (d_re >= -2*one_over_sqrt_10)
                    {
                        if      (d_im >= 2*one_over_sqrt_10)  return 0x9;//1001
                        else if (d_im >= 0*one_over_sqrt_10)  return 0x8;//1000
                        else if (d_im >= -2*one_over_sqrt_10) return 0xc;//1100
                        else                                       return 0xd;//1101
                    }
                    else
                    {
                        if         (d_im >= 2*one_over_sqrt_10)  return 0xb;//1011
                        else if (d_im >= 0*one_over_sqrt_10)  return 0xa;//1010
                        else if (d_im >= -2*one_over_sqrt_10) return 0xe;//1110
                        else                                        return 0xf;//1111
                    }
                    break;
                }//end case 4
                case 6:// 3GPP TS 36.211 Table 7.1.4-1: 64QAM modulation mapping.
                {
                    if     (d_re >=  6*one_over_sqrt_42)
                    {
                        if     (d_im >=  6*one_over_sqrt_42) return 0x0f;//001111
                        else if(d_im >=  4*one_over_sqrt_42) return 0x0d;//001110
                        else if(d_im >=  2*one_over_sqrt_42) return 0x0a;//001010
                        else if(d_im >=  0*one_over_sqrt_42) return 0x0b;//001011
                        else if(d_im >= -2*one_over_sqrt_42) return 0x1b;//011011
                        else if(d_im >= -4*one_over_sqrt_42) return 0x1a;//011010
                        else if(d_im >= -6*one_over_sqrt_42) return 0x1d;//011110
                        else                                      return 0x1f;//011111
                    }
                    else if(d_re >=  4*one_over_sqrt_42)
                    {
                        if     (d_im >=  6*one_over_sqrt_42) return 0x0d;//001101
                        else if(d_im >=  4*one_over_sqrt_42) return 0x0c;//001100
                        else if(d_im >=  2*one_over_sqrt_42) return 0x08;//001000
                        else if(d_im >=  0*one_over_sqrt_42) return 0x09;//001001
                        else if(d_im >= -2*one_over_sqrt_42) return 0x19;//011001
                        else if(d_im >= -4*one_over_sqrt_42) return 0x18;//011000
                        else if(d_im >= -6*one_over_sqrt_42) return 0x1c;//011100
                        else                                      return 0x1d;//011101
                    }
                    else if(d_re >=  2*one_over_sqrt_42)
                    {
                        if     (d_im >=  6*one_over_sqrt_42) return 0x05;//000101
                        else if(d_im >=  4*one_over_sqrt_42) return 0x04;//000100
                        else if(d_im >=  2*one_over_sqrt_42) return 0x00;//000000
                        else if(d_im >=  0*one_over_sqrt_42) return 0x01;//000001
                        else if(d_im >= -2*one_over_sqrt_42) return 0x11;//010001
                        else if(d_im >= -4*one_over_sqrt_42) return 0x10;//010000
                        else if(d_im >= -6*one_over_sqrt_42) return 0x14;//010100
                        else                                      return 0x15;//010101
                    }
                    else if(d_re >=  0*one_over_sqrt_42)
                    {
                        if     (d_im >=  6*one_over_sqrt_42) return 0x07;//000111
                        else if(d_im >=  4*one_over_sqrt_42) return 0x06;//000110
                        else if(d_im >=  2*one_over_sqrt_42) return 0x02;//000010
                        else if(d_im >=  0*one_over_sqrt_42) return 0x03;//000011
                        else if(d_im >= -2*one_over_sqrt_42) return 0x13;//010011
                        else if(d_im >= -4*one_over_sqrt_42) return 0x12;//010010
                        else if(d_im >= -6*one_over_sqrt_42) return 0x16;//010110
                        else                                      return 0x17;//010111
                    }
                    else if(d_re >= -2*one_over_sqrt_42)
                    {
                        if     (d_im >=  6*one_over_sqrt_42) return 0x27;//100111
                        else if(d_im >=  4*one_over_sqrt_42) return 0x26;//100110
                        else if(d_im >=  2*one_over_sqrt_42) return 0x22;//100010
                        else if(d_im >=  0*one_over_sqrt_42) return 0x23;//100011
                        else if(d_im >= -2*one_over_sqrt_42) return 0x33;//110011
                        else if(d_im >= -4*one_over_sqrt_42) return 0x32;//110010
                        else if(d_im >= -6*one_over_sqrt_42) return 0x36;//110110
                        else                                      return 0x37;//110111
                    }
                    else if(d_re >= -4*one_over_sqrt_42)
                    {
                        if     (d_im >=  6*one_over_sqrt_42) return 0x25;//100101
                        else if(d_im >=  4*one_over_sqrt_42) return 0x24;//100100
                        else if(d_im >=  2*one_over_sqrt_42) return 0x20;//100000
                        else if(d_im >=  0*one_over_sqrt_42) return 0x21;//100001
                        else if(d_im >= -2*one_over_sqrt_42) return 0x31;//110001
                        else if(d_im >= -4*one_over_sqrt_42) return 0x30;//110000
                        else if(d_im >= -6*one_over_sqrt_42) return 0x34;//110100
                        else                                      return 0x35;//110101
                    }
                    else if(d_re >= -6*one_over_sqrt_42)
                    {
                        if     (d_im >=  6*one_over_sqrt_42) return 0x2d;//101101
                        else if(d_im >=  4*one_over_sqrt_42) return 0x2c;//101100
                        else if(d_im >=  2*one_over_sqrt_42) return 0x28;//101000
                        else if(d_im >=  0*one_over_sqrt_42) return 0x29;//101001
                        else if(d_im >= -2*one_over_sqrt_42) return 0x39;//111001
                        else if(d_im >= -4*one_over_sqrt_42) return 0x38;//111000
                        else if(d_im >= -6*one_over_sqrt_42) return 0x3c;//111100
                        else                                      return 0x3d;//111101
                    }
                    else
                    {
                        if     (d_im >=  6*one_over_sqrt_42) return 0x2f;//101111
                        else if(d_im >=  4*one_over_sqrt_42) return 0x2e;//101110
                        else if(d_im >=  2*one_over_sqrt_42) return 0x2a;//101010
                        else if(d_im >=  0*one_over_sqrt_42) return 0x2b;//101011
                        else if(d_im >= -2*one_over_sqrt_42) return 0x3b;//111011
                        else if(d_im >= -4*one_over_sqrt_42) return 0x3a;//111010
                        else if(d_im >= -6*one_over_sqrt_42) return 0x3e;//111110
                        else                                      return 0x3f;//111111
                    }
                    break;
                }//end case 6
                default: return 0;
            }//end switch (N_bits_per_mod_symbol)

    }

float get_soft_decision(float rx_re, float rx_im, float exp_re, float exp_im, float max_dist)
{
    float diff_re;
    float diff_im;
    float dist;

    diff_re = rx_re - exp_re;
    diff_im = rx_im - exp_im;
    dist    = sqrt(diff_re*diff_re + diff_im*diff_im);

    if(dist >= max_dist)
    {
        dist = max_dist - (max_dist/120);
    }

    return(1 - dist/max_dist);
}

