/*
 * CppUnit_T_math.h
 *
 *  Created on: 2013-11-7
 *      Author: abing
 */

#ifndef CPPUNIT_T_MATH_H_
#define CPPUNIT_T_MATH_H_

#include <cppunit/TestCase.h>
#include "cppunit/extensions/HelperMacros.h"

class qa_math : public CppUnit::TestCase
{
	CPPUNIT_TEST_SUITE(qa_math); //声明一个TestSuite
	CPPUNIT_TEST(testmod); //添加TestCase到TestSuite
	CPPUNIT_TEST(testdemod);
	CPPUNIT_TEST_SUITE_END();
private:
	void testmod();
	void testdemod();
};




#endif /* CPPUNIT_T_MATH_H_ */
