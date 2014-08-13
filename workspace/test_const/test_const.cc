/*
 * test_const.cc
 *
 *  Created on: 2014-3-9
 *      Author: abing
 *  为了验证类之间的成员函数调用时候对与const 引用的一些操作
 */
#include "class_a.h"
#include <iostream>
#include <cstring>

int main(void)
{
	int len=10;
	class_a aa(len);
	std::vector<gr_complex> bb(len+2);
	for(int i=0;i<(int)bb.size();i++)
		bb[i]=gr_complex(i+1,-(i+1));
	aa.print_vec(bb);
	const std::vector<gr_complex> cbb = aa.get_seq();
	std::vector<gr_complex> lbb(len);
	memcpy(&lbb[0],&cbb[0],sizeof(gr_complex)*len);
	for(int i=0;i<(int)lbb.size();i++)
		std::cout<<lbb[i]<<std::endl;
	std::cout<<"Have Done!"<<std::endl;
	return 0;
}



