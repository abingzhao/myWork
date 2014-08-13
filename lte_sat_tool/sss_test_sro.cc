#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;
int main()
{
	complex<float> *sss=(complex<float>*)malloc(sizeof(complex<float>)*72);
	vector<complex<float> > fft;

	fstream file1("fft_out.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream ofile1 ("fft.txt");
	fstream file2("sss.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream ofile2 ("sss.txt");
	//file.seekg(0,ios_base::beg);
	complex<float> sum1,sum2,sum3;
	
	int N = 5;
	for(int i=0;!file1.eof()&(i<16*N);i++)
	{	
		complex<float> temp1;
		file1.read((char*)(&temp1),sizeof(temp1));
		if(i>=16*(N-3))
		{
			fft.push_back(temp1);
			ofile1<<temp1<<endl;
		}
	}

	float pha_err = 0.0;
	int sum = 0;
	float delta=0.0;
	int m=0;
	for(;!file2.eof()&(m<5000);m++)
	{
		
		//complex<float> temp1;
		file2.read((char*)(&sss[0]),sizeof(complex<float>)*72);
		for(int i=0;i<72&m==6;i++)
		{
		//	sss.push_back(temp1);
			ofile2<<sss[(m-1)*72+i]<<endl;
		}
		for (int i = 0; i < 30; ++i)
		{
			if(i<31)
			{
				//pha_err1 += sss[i+5 + 1] * sss[i+5];
				pha_err += abs(arg(sss[i+5])) * (i+5+92);
				sum +=(i+5+92) * (i+5+92);
			}
			else	
			{
				//pha_err2 += sss[i+5+31 +1] * sss[i+5+31];
				pha_err += abs(arg(sss[i+5-35]) )* (i+5-35);

				sum +=(i+5-35) * (i+5-35);
			}
		}
		delta += pha_err / float(sum);
		//std::cout<<m<<":error:"<<delta/float(m+1)<<std::endl;
	}
	ofile1.close();
	ofile2.close();
	file1.close();
	file2.close();
/////////////////////////////////////////

	//complex<float> pha_err1 = 0.0;
	//complex<float> pha_err2 = 0.0;
	/*
	float pha_err = 0.0;
	int sum = 0;
	for (int i = 0; i < 30; ++i)
	{
		if(i<31)
		{
			//pha_err1 += sss[i+5 + 1] * sss[i+5];
			pha_err += abs(arg(sss[i+5])) * (i+5+92);
			sum +=(i+5+92) * (i+5+92);
		}
		else	
		{
			//pha_err2 += sss[i+5+31 +1] * sss[i+5+31];
			pha_err += abs(arg(sss[i+5-35]) )* (i+5-35);

			sum +=(i+5-35) * (i+5-35);
		}
	}*/
	//float delta=arg(pha_err2 + pha_err1);
	//float delta=pha_err / float(sum);
	std::cout<<delta/float(m)<<std::endl;
	std::cout<<"2*pi*delt/N="<<(2.0*M_PI*0.5/16.0)<<std::endl;
	
	for (int i = 0; i < 16; ++i)
	{
		std::cout<<i<<"th:"<<"fft="<<fft[i]<<"\tcompentioned="
			<<fft[i]*exp(complex<float>(0,((2.0*M_PI*0.5/16.0))*(-1)*((i+0)%16)))<<std::endl;
		//std::cout<<complex<float>(1,0)*exp(complex<float>(0,(2.0*M_PI*0.5/128.0)*(1)*i))<<std::endl;
	}
	


	free(sss);
	cout<<"Have done!"<<endl;
	return 0;
}
