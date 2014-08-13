#include<iostream>
#include<fstream>
#include<complex>
#include<vector>
#include<cmath>
using namespace std;
int main()
{
	vector<complex<float> > origin;
	fstream file("../grc_work/H.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	//fstream file("../source/source_b.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream examplefileC ("../octave/H.txt");
	//ofstream examplefileC1 ("../octave/real_a.txt");
	//ofstream examplefileC2 ("../octave/imag_a.txt");

	file.seekg(0,ios_base::beg);
	int i=0;
	float aa=1.0/128;
	//for(;!file.eof()&&i<20160;i++)
	//for(;!file.eof()&&i<38400;i++)
	for(;!file.eof();i++)
	{
		complex<float> temp;
		file.read((char *)(&temp),sizeof(temp));
		origin.push_back(temp);
		//examplefileC.write((char*)(&temp),sizeof(temp));
		examplefileC<<real(temp)<<endl;
		//examplefileC1<<real(temp)<<endl;
		//examplefileC2<<imag(temp)<<endl;
	}
	examplefileC.close();
	//examplefileC1.close();
	//examplefileC2.close();
	file.close();
	cout<<"Have done!"<<endl;
	return 0;
}
