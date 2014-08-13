/*
 * sss_gen.cc
 *
 *  Created on: 2013-10-22
 *      Author: abing
 */

/* Function:    sss_gen
 * Description: Generates LTE secondary synchronization signals
 * Inputs:      N_id_1    - Physical layer cell identity group (value:0-167)
 *              N_id_2    - Physical layer identity  (value:0-2)
 * Outputs:     sss_d_u_0 - The sequence d(n) used for the secondary
 *                         synchronization signal, an interleaved
 *                          concatenation of two length-31 binary
 *                         sequences for subframe 0
 * Outputs:     sss_d_u_5 - The sequence d(n) used for the secondary
 *                         synchronization signal, an interleaved
 *                         concatenation of two length-31 binary
 *                         sequences for subframe 5
 * Spec:        3GPP TS 36.211 section 6.11.2.1 v10.1.0
 */

#include <complex>
#include <iostream>
#include <cstring>
#include "sss_gen.h"


void sss_gen(	unsigned int          N_id_1,
				unsigned int          N_id_2,
				std::complex<float>   *sss_0_out,
				std::complex<float>   *sss_5_out)
{
	const unsigned int LEN = 62;
	//float sss_0_real,sss_0_imag,sss_5_real,sss_5_imag;

	unsigned int m0,m1;
	unsigned int m_prime,q_prime,q;
	//Generate m0 and m1
	q_prime = N_id_1/30;
	q       = (N_id_1 + q_prime*((q_prime + 1)/2))/30;
	m_prime = N_id_1 + (q*(q + 1)/2);
	m0      = m_prime % 31;
	m1      = (m0 + (m_prime/31) + 1) % 31;
	//std::cout<<"m0=:"<<m0<<"    m1="<<m1<<std::endl;
	//Generate s_x_tilde and s_tilde
	unsigned char s_x_tilde[31];
	char s_tilde[31];
	memset(s_x_tilde,0,sizeof(unsigned char)*31);
	s_x_tilde[4] = 1;
	for (int i=0;i<26;i++)
	{
		s_x_tilde[i+5] = (s_x_tilde[i+2] + s_x_tilde[i]) % 2;
	}
	//std::cout<<"s_tilde:"<<std::endl;
	for (int i=0;i<31;i++)
	{
		s_tilde[i] = 1 - 2 * s_x_tilde[i];
		//std::cout<<"	"<<(int)s_tilde[i]<<std::endl;
	}
	//Generate c_x_tilde and c_tilde
	unsigned char c_x_tilde[31];
	char c_tilde[31];
	memset(c_x_tilde,0,sizeof(unsigned char)*31);
	c_x_tilde[4] = 1;
	for (int i=0;i<26;i++)
	{
		c_x_tilde[i+5] = (c_x_tilde[i+3] + c_x_tilde[i]) % 2;
	}
	//std::cout<<"c_tilde:"<<std::endl;
	for (int i=0;i<31;i++)
	{
		c_tilde[i] = 1 - 2 * c_x_tilde[i];
		//std::cout<<"	"<<(int)c_tilde[i]<<std::endl;
	}
	//Generate z_x_tilde and z_tilde
	unsigned char z_x_tilde[31];
	char z_tilde[31];
	memset(z_x_tilde,0,sizeof(unsigned char)*31);
	z_x_tilde[4] = 1;
	for (int i=0;i<26;i++)
	{
		z_x_tilde[i+5] = (z_x_tilde[i+4] + z_x_tilde[i+2] + z_x_tilde[i+1] + z_x_tilde[i]) % 2;
	}
	///std::cout<<"z_tilde:"<<std::endl;
	for (int i=0;i<31;i++)
	{
		z_tilde[i] = 1 - 2 * z_x_tilde[i];
		//std::cout<<"	"<<(float)z_tilde[i]<<std::endl;
	}
	//Generate s_0_m0[31],s_1_m1[31],c_0[31],c_1[31],z_0_m0[31],z_1_m1[31]
	float s_0_m0[31],s_1_m1[31],c_0[31],c_1[31],z_1_m0[31],z_1_m1[31];
	std::cout<<"s_0_m0 s_1_m1  c_0     c_1    z_1_m0 z_1_m1"<<std::endl;
	for (int i=0;i<31;i++)
	{
		s_0_m0[i] = (float) s_tilde[(i + m0) % 31];
		s_1_m1[i] = (float) s_tilde[(i + m1) % 31];
		c_0[i]    = (float) c_tilde[(i + N_id_2) % 31];
		c_1[i]    = (float) c_tilde[(i + N_id_2 + 3) % 31];
		z_1_m0[i] = (float) z_tilde[(i + (m0 % 8)) % 31];
		z_1_m1[i] = (float) z_tilde[(i + (m1 % 8)) % 31];
		std::cout<<s_0_m0[i]<<"	"<<s_1_m1[i]<<"	"
				 <<c_0[i]   <<"	"<<c_1[i]   <<"	"
				 <<z_1_m0[i]<<"	"<<z_1_m1[i]<<"	"<<std::endl;

	}
	//Generate SSS
	for (unsigned int i=0;i<LEN/2;i++)
	{
		/*
			sss_0_real  = (float) s_0_m0[i]*c_0[i];
			sss_0_imag   = 0;
			sss_5_real   = (float) s_1_m1[i]*c_0[i];
			sss_5_imag  = 0;

			sss_0_real = (float) s_1_m1[i]*c_1[i]*z_1_m0[i];
			sss_0_imag = 0;
			sss_5_real = (float) s_0_m0[i]*c_1[i]*z_1_m1[i];
			sss_5_imag = 0;
		*/
		sss_0_out[2*i]   = std::complex<float>(s_0_m0[i]*c_0[i] , 0);
		sss_5_out[2*i]   = std::complex<float>(s_1_m1[i]*c_0[i] , 0);

		sss_0_out[2*i+1] = std::complex<float>(s_1_m1[i]*c_1[i]*z_1_m0[i],0);
		sss_5_out[2*i+1] = std::complex<float>(s_0_m0[i]*c_1[i]*z_1_m1[i],0);
	}

}
