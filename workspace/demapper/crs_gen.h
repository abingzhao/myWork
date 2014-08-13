/*
 * crs_gen.h
 *
 *  Created on: 2013-10-23
 *      Author: abing
 */

#ifndef CRS_GEN_H_
#define CRS_GEN_H_

#include <complex>

/************************************************************************
 *   Description       	: Generates the Pseudo-random sequence
 *   Document Reference	: 3GPP TS 36.211  section 7.2
 *	 Inputs				: c_init    - Initialization value for the sequence
 *	              	  	  seq_len   - Length of the output sequence
 *	 Outputs			: prs_out   - Psuedo random sequence
*************************************************************************/
void generate_prs(	unsigned int  c_init,
					unsigned int  len,
					unsigned int *prs_out);
/********************************************************************************
 *   Description       	: Generates LTE cell specific reference signals
 *   Document Reference	: 3GPP TS 36.211  section 6.10.1.1
 *   Inputs				: N_s       - Slot number withing a radio frame (1-20)
 *            	  	  	  L         - OFDM symbol number within the slot (0 or 4)
 *            	 	 	  N_id_cell - Physical layer cell identity(0-503)
 *	 Outputs			: crs_out   - Reference signal for this cell
 ********************************************************************************/
void generate_crs(	unsigned int  N_s,
					unsigned int  L,
					unsigned int  N_id_cell,
					std::complex<float> *crs_out );


#endif /* CRS_GEN_H_ */
