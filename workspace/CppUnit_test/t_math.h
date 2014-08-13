/*
 * T_math.h
 *
 *  Created on: 2013-11-7
 *      Author: abing
 */

#ifndef T_MATH_H_
#define T_MATH_H_



class t_math
{
public :
	t_math(){};
	~t_math(){};
	void mod_mapper(int *bit_d,float *mod_d,int LEN);
	void mod_demapper(float *mod_d,int *bit_d,int LEN);
};



#endif /* T_MATH_H_ */
