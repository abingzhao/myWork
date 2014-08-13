/*
 * test.cc
 *
 *  Created on: 2013-11-19
 *      Author: abing
 */

#include <iostream>
#include <cmath>
#include <complex>
using namespace std;
bool is_prime(int num)
{

	int   m=sqrt(num);
	for(int   i=2;i<=m;i++)
	{
		if(num%i==0)   return   false;
	}
	return   true;
}

int max_prime(int num)
{
	for (int m=num-1;m>0;m--)
	{
		if(is_prime(m))
		{
			return m;
			break;
		}
	}
	return 1;
}




int main()
{
	int a=71;
	cout<<max_prime(a)<<endl;

	complex<float> aa(cos(M_PI/4),sin(M_PI/4));
	cout<<aa<<endl;
	complex<float> bb;
	bb=aa*aa;
	cout<<bb<<endl;
	cout<<abs(aa)<<"	"<<abs(bb)<<endl;
	cout<<arg(aa)<<"	"<<arg(bb)<<endl;
	return 0;
}


