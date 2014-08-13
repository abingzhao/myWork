/*
 * pss_main.cpp
 *
 *  Created on: 2013-10-22
 *      Author: abing
 */
#include <iostream>
#include <cmath>
#include "complex"
#include "pss_gen.hpp"

int main()
{
	std::complex<float> pss_out[62];
	unsigned int N_id_2 = 0;
	pss_gen(N_id_2,pss_out);
	for (int i=0;i<62;i++)
	{
		std::cout<<i<<"th:"<<pss_out[i]<<std::endl;

	}
	return 0;
}

