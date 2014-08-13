/*
 * pss_gen.cc
 *
 *  Created on: 2013-10-22
 *      Author: abing
 */

/* Function:    pss_gen
 * Description: Generates an LTE primary synchronization signal
 * Inputs:      N_id_2  - Physical layer identity (value:0-2)
 * Outputs:     pss_d_u - The sequence d(n) used for the primary
 *                        synchronization signal, generated from
 *                        a frequency domain Zadoff-Chu sequence.
 * Spec:        3GPP TS 36.211 section 6.11.1.1 v10.1.0
 */


#include <cmath>
#include <complex>
#include "pss_gen.h"

void pss_gen(unsigned int N_id_2,std::complex <float> *pss_out)
{
	const unsigned int LEN = 62;
	float root_index;
	float real_part,imag_part;
	//confirm the root_index by N_id_2
	if(N_id_2 == 0)
	{
		root_index = 25;
	}
	else if(N_id_2 == 1)
	{
		root_index = 29;
	}
	else
	{
	    root_index = 34;
	}

	for (unsigned int i=0;i<LEN;i++)
	{
		if (i<31)
		{
			real_part = cos(-M_PI*root_index*i*(i+1)/63);
			imag_part = sin(-M_PI*root_index*i*(i+1)/63);
		}
		else
		{
			real_part = cos(-M_PI*root_index*(i+1)*(i+2)/63);
			imag_part = sin(-M_PI*root_index*(i+1)*(i+2)/63);
		}
		pss_out[i] = std::complex <float> (real_part,imag_part);
	}
}


