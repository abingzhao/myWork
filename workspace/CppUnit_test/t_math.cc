/*
 * T_math.cc
 *
 *  Created on: 2013-11-7
 *      Author: abing
 */
#include "t_math.h"
#include <cmath>

void t_math::mod_mapper(int *bit_d,float *mod_d,int LEN)
{
	for (int i=0;i<LEN;i++)
		mod_d[i] = (1-(float)bit_d[i]*2)/sqrt(2);
}

void t_math::mod_demapper(float *mod_d,int *bit_d,int LEN)
{
	for(int i=0;i<LEN;i++)
		bit_d[i] = mod_d[i]>0 ? (int)0:(int)1;
}

