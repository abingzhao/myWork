/*
 * crs_gen.cc
 *
 *  Created on: 2013-10-23
 *      Author: abing
 */

#include "crs_gen.h"
#include <complex>


/*********************************************************************
 *   Description       	: Generates LTE cell specific reference signals
 *   Document Reference	: 3GPP TS 36.211  section 6.10.1.1
 *   Inputs				: N_s       - Slot number withing a radio frame
 *            	  	  	  L         - OFDM symbol number within the slot
 *            	 	 	  N_id_cell - Physical layer cell identity
 *	 Outputs				: crs_out   - Reference signal for this cell
 ************************************************************** ******/
void generate_prs(	unsigned int  c_init,
					unsigned int  len,
					unsigned int *prs_out)
{
	unsigned int x1,x2;
	unsigned char bit1,bit2;
	//Initialize x1 and x2
	x1=1;
	x2=c_init;
	// Advance the 2nd m-sequence
	for(unsigned int i=0; i<(1600-31); i++)
	{
		bit1 = ((x1 >> 3) ^ x1) & 0x1;
		x1   = (x1 >> 1) | (bit1 << 30);
		bit2 = ((x2 >> 3) ^ (x2 >> 2) ^ (x2 >> 1) ^ x2) & 0x1;
        x2   = (x2 >> 1) | (bit2 << 30);
    }
	// Generate prs_out
	for (unsigned int i=0; i<len; i++)
	{
		bit1 = ((x1 >> 3) ^ x1) & 0x1;
		bit2 = ((x2 >> 3) ^ (x2 >> 2) ^ (x2 >> 1) ^ x2) & 0x1;

		x1 = (x1 >> 1) | (bit1 << 30);
		x2 = (x2 >> 1) | (bit2 << 30);

		prs_out[i] = bit1 ^ bit2;
	}
}
/********************************************************************************
    Description       	: Generates LTE cell specific reference signals
    Document Reference	: 3GPP TS 36.211  section 6.10.1.1
	Inputs				: N_s       - Slot number withing a radio frame (1-20)
             	  	  	  L         - OFDM symbol number within the slot
             	  	  	  	  	  	  (0 or 4 :single antena only)
             	 	 	  N_id_cell - Physical layer cell identity    (0-503)
	Outputs				: crs_out   - Reference signal for this cell
*********************************************************************************/
void generate_crs(	unsigned int  N_s,
					unsigned int  L,
					unsigned int  N_id_cell,
					std::complex<float> *crs_out )
{
	// Constant declaration
	const unsigned int CRS_LEN = 2*110;
	const float  one_over_sqrt_2 = 1/sqrt(2);
	// Variable declaration
	unsigned int N_cp;
	unsigned int c_init;
	unsigned int prs_out[2*CRS_LEN];
	// Variable initialization
	N_cp=1;//normal CP only
	c_init = 1024 * (7 * (N_s+1) + L + 1) * (2 * N_id_cell + 1) + 2*N_id_cell + N_cp;
	// Generate the psuedo random sequence c
	generate_prs(c_init, 2*CRS_LEN, prs_out);
	// Construct the reference signals
	float crs_re,crs_im;
	for(unsigned int i=0; i<CRS_LEN; i++)
	{
		crs_re = one_over_sqrt_2*(1 - 2*(float)prs_out[2*i]);
	    crs_im = one_over_sqrt_2*(1 - 2*(float)prs_out[2*i+1]);
	    crs_out[i] = std::complex<float>(crs_re,crs_im);
	}
}

