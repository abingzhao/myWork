/*
 * class_a.h
 *
 *  Created on: 2014-3-9
 *      Author: abing
 */

#ifndef CLASS_A_H_
#define CLASS_A_H_
#include <vector>
#include <complex>
#include <iostream>
typedef std::complex<float> gr_complex;
class class_a
{
public:
	class_a(int len){
		d_len = len;
		bb = std::vector<gr_complex>(d_len);
	}
	//~class_a();

	void print_vec(const std::vector<gr_complex>& vec)
	{
		for(int i=0;i<d_len;i++)
		{
			std::cout<<vec[i]<<std::endl;
			//vec[5]=0;
		}

	}
	const std::vector<gr_complex>& get_seq()
	{

		for(int i=0;i<(int)bb.size();i++)
			bb[i]=gr_complex((i+1)*2,-(i+1)*2);
		return bb;
	}

private:
	int d_len;
	std::vector<gr_complex> bb;
};



#endif /* CLASS_A_H_ */
