/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_LTE_SAT_H
#define INCLUDED_LTE_SAT_H

#include <complex>
/*********************************************************************
 * This header file defines some constants used in our lte_sat project
 *********************************************************************/


#define PSS_SEQ_LEN 62  //Length of PSS
#define SSS_SEQ_LEN 62  //Length of SSS

#define N_PRB_DL_MAX   110 //Largest downlink bandwidth configuration:110 PRBs
#define N_SLOT_FRAME   20  //Total number of slot in one frame
#define N_SC_PRB_DL    12  //Number of subcarriers per PRB in one OFDM symbol
#define N_SYNMBL_SLOT  7   //Number of OFDM symbols per slot
#define N_CRS_SUBFRAME 8   //Number of CRS in one PRB per slot

#define N_SUBF_FRAME   10  //Number of subframe in one frame
#define N_CRS_SYMBOL_SLOT  2           //Number of OFDM symbol used to map the CRS per slot
#define BASIC_SEQ_LEN      2*N_PRB_DL_MAX  //Maximum CRS length used for oe OFDM symbol in time domain

typedef std::complex<float>			gr_complex;

#endif
