/*
 * mod_demod.cpp
 *
 *  Created on: 2013-10-19
 *      Author: abing
 */
#include"mod_demod.h"
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

		//cout<<"  1/sqrt(10)="<<one_over_sqrt_10<<endl;
		//cout<<"3*1/sqrt(10)="<<3*one_over_sqrt_10<<endl;
		//cout<<"  1/sqrt(42)="<<one_over_sqrt_42<<endl;
		//cout<<"3*1/sqrt(42)="<<3*one_over_sqrt_42<<endl;
		//cout<<"5*1/sqrt(42)="<<5*one_over_sqrt_42<<endl;
		//cout<<"7*1/sqrt(42)="<<7*one_over_sqrt_42<<endl;
		for (unsigned int i=0;i<noutput_items;i++)
				{
					float real_part=0,imag_part=0;
					switch (sps)
					{
						case 1 :// 3GPP TS 36.211 Table 7.1.1-1: BPSK modulation mapping.
							{
								if ( 0 == (unsigned int)in[i] )
								{
									real_part = +one_over_sqrt_2;
									imag_part = +one_over_sqrt_2;
								}
								else
								{
									real_part = -one_over_sqrt_2;
									imag_part = -one_over_sqrt_2;
								}
								break;
							}//end case MOD_TYPE_BPSK
						case 2 :// 3GPP TS 36.211 Table 7.1.2-1: QPSK modulation mapping.
							{
								switch ((unsigned int) (in[i*2+1]|(in[2*i]<<1)))
								{
									case 0:
										real_part = +one_over_sqrt_2;
										imag_part = +one_over_sqrt_2;
										break;
									case 1:
										real_part = +one_over_sqrt_2;
										imag_part = -one_over_sqrt_2;
										break;
									case 2:
										real_part = -one_over_sqrt_2;
										imag_part = +one_over_sqrt_2;
										break;
									case 3:
										real_part = -one_over_sqrt_2;
										imag_part = -one_over_sqrt_2;
										break;
								}
								break;
							}//end case MOD_TYPE_QPSK
						case 4:// 3GPP TS 36.211 Table Table 7.1.3-1: 16QAM modulation mapping.
							{
								switch ( (unsigned int ) ( in[4*i]|(in[4*i+1]<<1)|(in[4*i+2]<<2)|(in[4*i+3]<<3) ) )
								{
									case 0:
										real_part = +1*one_over_sqrt_10;
										imag_part = +1*one_over_sqrt_10;
										break;
									case 1:
										real_part = +1*one_over_sqrt_10;
										imag_part = +3*one_over_sqrt_10;
										break;
									case 2:
										real_part = +3*one_over_sqrt_10;
										imag_part = +1*one_over_sqrt_10;
										break;
									case 3:
										real_part = +3*one_over_sqrt_10;
										imag_part = +3*one_over_sqrt_10;
										break;
									case 4:
										real_part = +1*one_over_sqrt_10;
										imag_part = -1*one_over_sqrt_10;
										break;
									case 5:
										real_part = +1*one_over_sqrt_10;
										imag_part = -3*one_over_sqrt_10;
										break;
									case 6:
										real_part = +3*one_over_sqrt_10;
										imag_part = -1*one_over_sqrt_10;
										break;
									case 7:
										real_part = +3*one_over_sqrt_10;
										imag_part = -3*one_over_sqrt_10;
										break;
									case 8:
										real_part = -1*one_over_sqrt_10;
										imag_part = +1*one_over_sqrt_10;
										break;
									case 9:
										real_part = -1*one_over_sqrt_10;
										imag_part = +3*one_over_sqrt_10;
										break;
									case 10:
										real_part = -3*one_over_sqrt_10;
										imag_part = +1*one_over_sqrt_10;
										break;
									case 11:
										real_part = -3*one_over_sqrt_10;
										imag_part = +3*one_over_sqrt_10;
										break;
									case 12:
										real_part = -1*one_over_sqrt_10;
										imag_part = -1*one_over_sqrt_10;
										break;
									case 13:
										real_part = -1*one_over_sqrt_10;
										imag_part = -3*one_over_sqrt_10;
										break;
									case 14:
										real_part = -3*one_over_sqrt_10;
										imag_part = -1*one_over_sqrt_10;
										break;
									case 15:
										real_part = -3*one_over_sqrt_10;
										imag_part = -3*one_over_sqrt_10;
										break;
								}
								break;
							}//end case MOD_TYPE_16QAM
						case 6:// 3GPP TS 36.211 Table 7.1.2-1: QPSK modulation mapping.
							{
								switch ( (unsigned int ) ( 	in[6*i]
																					|(in[6*i+1]<<1)
																					|(in[6*i+2]<<2)
																					|(in[6*i+3]<<3)
																					|(in[6*i+4]<<4)
																					|(in[6*i+5]<<5) ) )
														{
															case 0:
																real_part = +3*one_over_sqrt_42;
																imag_part = +3*one_over_sqrt_42;
																break;
															case 1:
																real_part = +3*one_over_sqrt_42;
																imag_part = +1*one_over_sqrt_42;
																break;
															case 2:
																real_part = +1*one_over_sqrt_42;
																imag_part = +3*one_over_sqrt_42;
																break;
															case 3:
																real_part = +1*one_over_sqrt_42;
																imag_part = +1*one_over_sqrt_42;
																break;
															case 4:
																real_part = +3*one_over_sqrt_42;
																imag_part = +5*one_over_sqrt_42;
																break;
															case 5:
																real_part = +3*one_over_sqrt_42;
																imag_part = +7*one_over_sqrt_42;
																break;
															case 6:
																real_part = +1*one_over_sqrt_42;
																imag_part = +5*one_over_sqrt_42;
																break;
															case 7:
																real_part = +1*one_over_sqrt_42;
																imag_part = +7*one_over_sqrt_42;
																break;
															case 8:
																real_part = +5*one_over_sqrt_42;
																imag_part = +3*one_over_sqrt_42;
																break;
															case 9:
																real_part = +5*one_over_sqrt_42;
																imag_part = +1*one_over_sqrt_42;
																break;
															case 10:
																real_part = +7*one_over_sqrt_42;
																imag_part = +3*one_over_sqrt_42;
																break;
															case 11:
																real_part = +7*one_over_sqrt_42;
																imag_part = +1*one_over_sqrt_42;
																break;
															case 12:
																real_part = +5*one_over_sqrt_42;
																imag_part = +5*one_over_sqrt_42;
																break;
															case 13:
																real_part = +5*one_over_sqrt_42;
																imag_part = +7*one_over_sqrt_42;
																break;
															case 14:
																real_part = +7*one_over_sqrt_42;
																imag_part = +5*one_over_sqrt_42;
																break;
															case 15:
																real_part = +7*one_over_sqrt_42;
																imag_part = +7*one_over_sqrt_42;
																break;
															case 16:
																real_part = +3*one_over_sqrt_42;
																imag_part = -3*one_over_sqrt_42;
																break;
															case 17:
																real_part = +3*one_over_sqrt_42;
																imag_part = -1*one_over_sqrt_42;
																break;
															case 18:
																real_part = +1*one_over_sqrt_42;
																imag_part = -3*one_over_sqrt_42;
																break;
															case 19:
																real_part = +1*one_over_sqrt_42;
																imag_part = -1*one_over_sqrt_42;
																break;
															case 20:
																real_part = +3*one_over_sqrt_42;
																imag_part = -5*one_over_sqrt_42;
																break;
															case 21:
																real_part = +3*one_over_sqrt_42;
																imag_part = -7*one_over_sqrt_42;
																break;
															case 22:
																real_part = +1*one_over_sqrt_42;
																imag_part = -5*one_over_sqrt_42;
																break;
															case 23:
																real_part = +1*one_over_sqrt_42;
																imag_part = -7*one_over_sqrt_42;
																break;
															case 24:
																real_part = +5*one_over_sqrt_42;
																imag_part = -3*one_over_sqrt_42;
																break;
															case 25:
																real_part = +5*one_over_sqrt_42;
																imag_part = -1*one_over_sqrt_42;
																break;
															case 26:
																real_part = +7*one_over_sqrt_42;
																imag_part = -3*one_over_sqrt_42;
																break;
															case 27:
																real_part = +7*one_over_sqrt_42;
																imag_part = -1*one_over_sqrt_42;
																break;
															case 28:
																real_part = +5*one_over_sqrt_42;
																imag_part = -5*one_over_sqrt_42;
																break;
															case 29:
																real_part = +5*one_over_sqrt_42;
																imag_part = -7*one_over_sqrt_42;
																break;
															case 30:
																real_part = +7*one_over_sqrt_42;
																imag_part = -5*one_over_sqrt_42;
																break;
															case 31:
																real_part = +7*one_over_sqrt_42;
																imag_part = -7*one_over_sqrt_42;
																break;
															case 32:
																real_part = -3*one_over_sqrt_42;
																imag_part = +3*one_over_sqrt_42;
																break;
															case 33:
																real_part = -3*one_over_sqrt_42;
																imag_part = +1*one_over_sqrt_42;
																break;
															case 34:
																real_part = -1*one_over_sqrt_42;
																imag_part = +3*one_over_sqrt_42;
																break;
															case 35:
																real_part = -1*one_over_sqrt_42;
																imag_part = +1*one_over_sqrt_42;
																break;
															case 36:
																real_part = -3*one_over_sqrt_42;
																imag_part = +5*one_over_sqrt_42;
																break;
															case 37:
																real_part = -3*one_over_sqrt_42;
																imag_part = +7*one_over_sqrt_42;
																break;
															case 38:
																real_part = -1*one_over_sqrt_42;
																imag_part = +5*one_over_sqrt_42;
																break;
															case 39:
																real_part = -1*one_over_sqrt_42;
																imag_part = +7*one_over_sqrt_42;
																break;
															case 40:
																real_part = -5*one_over_sqrt_42;
																imag_part = +3*one_over_sqrt_42;
																break;
															case 41:
																real_part = -5*one_over_sqrt_42;
																imag_part = +1*one_over_sqrt_42;
																break;
															case 42:
																real_part = -7*one_over_sqrt_42;
																imag_part = +3*one_over_sqrt_42;
																break;
															case 43:
																real_part = -7*one_over_sqrt_42;
																imag_part = +1*one_over_sqrt_42;
																break;
															case 44:
																real_part = -5*one_over_sqrt_42;
																imag_part = +5*one_over_sqrt_42;
																break;
															case 45:
																real_part = -5*one_over_sqrt_42;
																imag_part = +7*one_over_sqrt_42;
																break;
															case 46:
																real_part = -7*one_over_sqrt_42;
																imag_part = +5*one_over_sqrt_42;
																break;
															case 47:
																real_part = -7*one_over_sqrt_42;
																imag_part = +7*one_over_sqrt_42;
																break;
															case 48:
																real_part = -3*one_over_sqrt_42;
																imag_part = -3*one_over_sqrt_42;
																break;
															case 49:
																real_part = -3*one_over_sqrt_42;
																imag_part = -1*one_over_sqrt_42;
																break;
															case 50:
																real_part = -1*one_over_sqrt_42;
																imag_part = -3*one_over_sqrt_42;
																break;
															case 51:
																real_part = -1*one_over_sqrt_42;
																imag_part = -1*one_over_sqrt_42;
																break;
															case 52:
																real_part = -3*one_over_sqrt_42;
																imag_part = -5*one_over_sqrt_42;
																break;
															case 53:
																real_part = -3*one_over_sqrt_42;
																imag_part = -7*one_over_sqrt_42;
																break;
															case 54:
																real_part = -1*one_over_sqrt_42;
																imag_part = -5*one_over_sqrt_42;
																break;
															case 55:
																real_part = -1*one_over_sqrt_42;
																imag_part = -7*one_over_sqrt_42;
																break;
															case 56:
																real_part = -5*one_over_sqrt_42;
																imag_part = -3*one_over_sqrt_42;
																break;
															case 57:
																real_part = -5*one_over_sqrt_42;
																imag_part = -1*one_over_sqrt_42;
																break;
															case 58:
																real_part = -7*one_over_sqrt_42;
																imag_part = -3*one_over_sqrt_42;
																break;
															case 59:
																real_part = -7*one_over_sqrt_42;
																imag_part = -1*one_over_sqrt_42;
																break;
															case 60:
																real_part = -5*one_over_sqrt_42;
																imag_part = -5*one_over_sqrt_42;
																break;
															case 61:
																real_part = -5*one_over_sqrt_42;
																imag_part = -7*one_over_sqrt_42;
																break;
															case 62:
																real_part = -7*one_over_sqrt_42;
																imag_part = -5*one_over_sqrt_42;
																break;
															case 63:
																real_part = -7*one_over_sqrt_42;
																imag_part = -7*one_over_sqrt_42;
																break;
														}

								break;
							}//end case MOD_TYPE_64QAM
		    			//default :throw std::invalid_argument("invalid MODULATION_TYPE type");
					}//end switch
					out[i]=complex<float>(real_part,imag_part);
				}//end for

}

void mod_demapper(unsigned int sps,std::complex<float> *in,signed int *out,unsigned int noutput_items)
{
	//float  one_over_sqrt_2  = 1/sqrt(2);
	float  one_over_sqrt_10 = 1/sqrt(10);
	float  one_over_sqrt_42 = 1/sqrt(42);

	for (unsigned int i=0;i<noutput_items;i++)
	{
	    		float real_part=real(in[i]),imag_part=imag(in[i]);
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
	    				if (real_part >= 2*one_over_sqrt_10)
	    				{
	    					if (imag_part >= 2*one_over_sqrt_10)
	    					{
	    						out[4*i]   = 0x1; out[4*i+1] = 0x1;
	    						out[4*i+2] = 0x0; out[4*i+3] = 0x0;
	    					}
	    					else if (imag_part >= 0*one_over_sqrt_10)
	    					{
	    						out[4*i]   = 0x0; out[4*i+1] = 0x1;
	    						out[4*i+2] = 0x0; out[4*i+3] = 0x0;
	    					}
	    					else if (imag_part >= -2*one_over_sqrt_10)
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
	    				else if (real_part >= 0*one_over_sqrt_10)
	    				{
	    					if (imag_part >= 2*one_over_sqrt_10)
	    					{
	    						out[4*i]   = 0x1; out[4*i+1] = 0x0;
	    						out[4*i+2] = 0x0; out[4*i+3] = 0x0;
	    					}
	    					else if (imag_part >= 0*one_over_sqrt_10)
	    					{
	    						out[4*i]   = 0x0; out[4*i+1] = 0x0;
	    						out[4*i+2] = 0x0; out[4*i+3] = 0x0;
	    					}
	    					else if (imag_part >= -2*one_over_sqrt_10)
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
	    				else if (real_part >= -2*one_over_sqrt_10)
	    				{
	    					if (imag_part >= 2*one_over_sqrt_10)
	    					{
	    						out[4*i]   = 0x1; out[4*i+1] = 0x0;
	    						out[4*i+2] = 0x0; out[4*i+3] = 0x1;
	    					}
	    					else if (imag_part >= 0*one_over_sqrt_10)
	    					{
	    						out[4*i]   = 0x0; out[4*i+1] = 0x0;
	    						out[4*i+2] = 0x0; out[4*i+3] = 0x1;
	    					}
	    					else if (imag_part >= -2*one_over_sqrt_10)
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
	    					if (imag_part >= 2*one_over_sqrt_10)
	    					{
	    						out[4*i]   = 0x1; out[4*i+1] = 0x1;
	    						out[4*i+2] = 0x0; out[4*i+3] = 0x1;
	    					}
	    					else if (imag_part >= 0*one_over_sqrt_10)
	    					{
	    						out[4*i]   = 0x0; out[4*i+1] = 0x1;
	    						out[4*i+2] = 0x0; out[4*i+3] = 0x1;
	    					}
	    					else if (imag_part >= -2*one_over_sqrt_10)
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
	    				if     (real_part >=  6*one_over_sqrt_42)
	    				{
	    					if     (imag_part >=  6*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >=  4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >=  2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >=  0*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -6*one_over_sqrt_42)
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
	    				else if(real_part >=  4*one_over_sqrt_42)
	    				{
	    					if     (imag_part >=  6*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >=  4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >=  2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >=  0*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -6*one_over_sqrt_42)
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
	    				else if(real_part >=  2*one_over_sqrt_42)
	    				{
	    					if     (imag_part >=  6*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >=  4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}


	    					else if(imag_part >=  2*one_over_sqrt_42)

	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >=  0*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -6*one_over_sqrt_42)
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
	    				else if(real_part >=  0*one_over_sqrt_42)
	    				{
	    					if     (imag_part >=  6*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >=  4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >=  2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >=  0*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x0;
	    					}
	    					else if(imag_part >= -6*one_over_sqrt_42)
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
	    				else if(real_part >= -2*one_over_sqrt_42)
	    				{
	    					if     (imag_part >=  6*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  0*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -6*one_over_sqrt_42)
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
	    				else if(real_part >= -4*one_over_sqrt_42)
	    				{
	    					if     (imag_part >=  6*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  0*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x0; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -6*one_over_sqrt_42)
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
	    				else if(real_part >= -6*one_over_sqrt_42)
	    				{
	    					if     (imag_part >=  6*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  0*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x0; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -6*one_over_sqrt_42)
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
	    					if     (imag_part >=  6*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x1;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >=  0*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x0; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -2*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x1; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -4*one_over_sqrt_42)
	    					{
	    						out[6*i]   = 0x0; out[6*i+1] = 0x1; out[6*i+2] = 0x0;
	    						out[6*i+3] = 0x1; out[6*i+4] = 0x1; out[6*i+5] = 0x1;
	    					}
	    					else if(imag_part >= -6*one_over_sqrt_42)
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


void hard_mod_demapper(unsigned int sps,std::complex<float> *in,unsigned int *out,unsigned int noutput_items)
{
	for (unsigned int i=0;i<noutput_items;i++)
	{
	    char x = hard_decision(in[(int)ceil(i/sps)],sps);
	    out[i] = (unsigned int)(x>>(i%sps))&0x1;


	}
}
char hard_decision(std::complex<float> mod_symbol,int bps)
    {

    	float  one_over_sqrt_10 = 1/sqrt(10);
    	float  one_over_sqrt_42 = 1/sqrt(42);

    	float real_part=real(mod_symbol),imag_part=imag(mod_symbol);
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
    				if (real_part >= 2*one_over_sqrt_10)
    				{
    					if      (imag_part >= 2*one_over_sqrt_10)  return 0x3;//0011
    					else if (imag_part >= 0*one_over_sqrt_10)  return 0x2;//0010
    					else if (imag_part >= -2*one_over_sqrt_10) return 0x6;//0110
    					else 									   return 0x7;//0111
    				}
    				else if (real_part >= 0*one_over_sqrt_10)
    				{
    					if      (imag_part >= 2*one_over_sqrt_10)  return 0x1;//0001
    					else if (imag_part >= 0*one_over_sqrt_10)  return 0x0;//0000
    					else if (imag_part >= -2*one_over_sqrt_10) return 0x4;//0100
    					else                                       return 0x5;//0101
    				}
    				else if (real_part >= -2*one_over_sqrt_10)
    				{
    					if      (imag_part >= 2*one_over_sqrt_10)  return 0x9;//1001
    					else if (imag_part >= 0*one_over_sqrt_10)  return 0x8;//1000
    					else if (imag_part >= -2*one_over_sqrt_10) return 0xc;//1100
    					else                                       return 0xd;//1101
    				}
    				else
    				{
    					if 		(imag_part >= 2*one_over_sqrt_10)  return 0xb;//1011
    					else if (imag_part >= 0*one_over_sqrt_10)  return 0xa;//1010
    					else if (imag_part >= -2*one_over_sqrt_10) return 0xe;//1110
    					else 									   return 0xf;//1111
    				}
    				break;
    			}//end case 4
    			case 6:// 3GPP TS 36.211 Table 7.1.4-1: 64QAM modulation mapping.
    			{
    				if     (real_part >=  6*one_over_sqrt_42)
    				{
    					if     (imag_part >=  6*one_over_sqrt_42) return 0x0f;//001111
    					else if(imag_part >=  4*one_over_sqrt_42) return 0x0d;//001110
    					else if(imag_part >=  2*one_over_sqrt_42) return 0x0a;//001010
    					else if(imag_part >=  0*one_over_sqrt_42) return 0x0b;//001011
    					else if(imag_part >= -2*one_over_sqrt_42) return 0x1b;//011011
    					else if(imag_part >= -4*one_over_sqrt_42) return 0x1a;//011010
    					else if(imag_part >= -6*one_over_sqrt_42) return 0x1d;//011110
    					else                                      return 0x1f;//011111
    				}
    				else if(real_part >=  4*one_over_sqrt_42)
    				{
    					if     (imag_part >=  6*one_over_sqrt_42) return 0x0d;//001101
    					else if(imag_part >=  4*one_over_sqrt_42) return 0x0c;//001100
    					else if(imag_part >=  2*one_over_sqrt_42) return 0x08;//001000
    					else if(imag_part >=  0*one_over_sqrt_42) return 0x09;//001001
    					else if(imag_part >= -2*one_over_sqrt_42) return 0x19;//011001
    					else if(imag_part >= -4*one_over_sqrt_42) return 0x18;//011000
    					else if(imag_part >= -6*one_over_sqrt_42) return 0x1c;//011100
    					else                                      return 0x1d;//011101
    				}
    				else if(real_part >=  2*one_over_sqrt_42)
    				{
    					if     (imag_part >=  6*one_over_sqrt_42) return 0x05;//000101
    					else if(imag_part >=  4*one_over_sqrt_42) return 0x04;//000100
    					else if(imag_part >=  2*one_over_sqrt_42) return 0x00;//000000
    					else if(imag_part >=  0*one_over_sqrt_42) return 0x01;//000001
    					else if(imag_part >= -2*one_over_sqrt_42) return 0x11;//010001
    					else if(imag_part >= -4*one_over_sqrt_42) return 0x10;//010000
    					else if(imag_part >= -6*one_over_sqrt_42) return 0x14;//010100
    					else                                      return 0x15;//010101
    				}
    				else if(real_part >=  0*one_over_sqrt_42)
    				{
    					if     (imag_part >=  6*one_over_sqrt_42) return 0x07;//000111
    					else if(imag_part >=  4*one_over_sqrt_42) return 0x06;//000110
    					else if(imag_part >=  2*one_over_sqrt_42) return 0x02;//000010
    					else if(imag_part >=  0*one_over_sqrt_42) return 0x03;//000011
    					else if(imag_part >= -2*one_over_sqrt_42) return 0x13;//010011
    					else if(imag_part >= -4*one_over_sqrt_42) return 0x12;//010010
    					else if(imag_part >= -6*one_over_sqrt_42) return 0x16;//010110
    					else                                      return 0x17;//010111
    				}
    				else if(real_part >= -2*one_over_sqrt_42)
    				{
    					if     (imag_part >=  6*one_over_sqrt_42) return 0x27;//100111
    					else if(imag_part >=  4*one_over_sqrt_42) return 0x26;//100110
    					else if(imag_part >=  2*one_over_sqrt_42) return 0x22;//100010
    					else if(imag_part >=  0*one_over_sqrt_42) return 0x23;//100011
    					else if(imag_part >= -2*one_over_sqrt_42) return 0x33;//110011
    					else if(imag_part >= -4*one_over_sqrt_42) return 0x32;//110010
    					else if(imag_part >= -6*one_over_sqrt_42) return 0x36;//110110
    					else                                      return 0x37;//110111
    				}
    				else if(real_part >= -4*one_over_sqrt_42)
    				{
    					if     (imag_part >=  6*one_over_sqrt_42) return 0x25;//100101
    					else if(imag_part >=  4*one_over_sqrt_42) return 0x24;//100100
    					else if(imag_part >=  2*one_over_sqrt_42) return 0x20;//100000
    					else if(imag_part >=  0*one_over_sqrt_42) return 0x21;//100001
    					else if(imag_part >= -2*one_over_sqrt_42) return 0x31;//110001
    					else if(imag_part >= -4*one_over_sqrt_42) return 0x30;//110000
    					else if(imag_part >= -6*one_over_sqrt_42) return 0x34;//110100
    					else                                      return 0x35;//110101
    				}
    				else if(real_part >= -6*one_over_sqrt_42)
    				{
    					if     (imag_part >=  6*one_over_sqrt_42) return 0x2d;//101101
    					else if(imag_part >=  4*one_over_sqrt_42) return 0x2c;//101100
    					else if(imag_part >=  2*one_over_sqrt_42) return 0x28;//101000
    					else if(imag_part >=  0*one_over_sqrt_42) return 0x29;//101001
    					else if(imag_part >= -2*one_over_sqrt_42) return 0x39;//111001
    					else if(imag_part >= -4*one_over_sqrt_42) return 0x38;//111000
    					else if(imag_part >= -6*one_over_sqrt_42) return 0x3c;//111100
    					else                                      return 0x3d;//111101
    				}
    				else
    				{
    					if     (imag_part >=  6*one_over_sqrt_42) return 0x2f;//101111
    					else if(imag_part >=  4*one_over_sqrt_42) return 0x2e;//101110
    					else if(imag_part >=  2*one_over_sqrt_42) return 0x2a;//101010
    					else if(imag_part >=  0*one_over_sqrt_42) return 0x2b;//101011
    					else if(imag_part >= -2*one_over_sqrt_42) return 0x3b;//111011
    					else if(imag_part >= -4*one_over_sqrt_42) return 0x3a;//111010
    					else if(imag_part >= -6*one_over_sqrt_42) return 0x3e;//111110
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

    return(max_dist - dist);
}

