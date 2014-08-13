/*
 * cppmain.cc
 *
 *  Created on: 2013-11-7
 *      Author: abing
 */
#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/ui/text/TestRunner.h"
int main()
{
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry("alltest");
	runner.addTest( registry.makeTest() );
	runner.run();
	return 0;
}


