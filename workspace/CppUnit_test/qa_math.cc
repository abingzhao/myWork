/*
 * qa_math.cc
 *
 *  Created on: 2013-11-7
 *      Author: abing
 */

#include "qa_math.h"
#include "t_math.h"
#include <cmath>
#include <cppunit/TestAssert.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>

int   bit_d_exp[]={0,1,1,0,1,0,0,1};
float mod_d_exp[]={1/sqrt(2),-1/sqrt(2),-1/sqrt(2),1/sqrt(2),
		                 -1/sqrt(2),1/sqrt(2),1/sqrt(2),-1/sqrt(2)};

void qa_math::testmod()
{
	t_math m;
	float out[8];
	m.mod_mapper(bit_d_exp,out,8);
	CPPUNIT_ASSERT_EQUAL(sizeof(mod_d_exp), sizeof(out));
	for(unsigned int i = 0; i < 8; i++)
		CPPUNIT_ASSERT_DOUBLES_EQUAL(mod_d_exp[i], out[i], 1e-9);
}
void qa_math::testdemod()
{
	t_math m;
	int out[8];
	m.mod_demapper(mod_d_exp,out,8);
	CPPUNIT_ASSERT_EQUAL(sizeof(bit_d_exp), sizeof(out));
	for(unsigned int i = 0; i < 8; i++)
		CPPUNIT_ASSERT_DOUBLES_EQUAL(bit_d_exp[i], out[i], 1e-9);
}
