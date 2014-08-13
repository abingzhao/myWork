#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <cmath>
typedef std::complex<float> gr_complex;
using namespace std;
int main()
{
	vector< gr_complex > origin(4000,1);
	// fstream file("../source/data.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream examplefileC ("../source/source.dat",ios::binary);
	// file.seekg(0,ios_base::beg);
	int i=0;
	// for(;!file.eof()&&i<38400;i++)
	// {
	// 	complex<float> temp;
	// 	file.read((char *)(&temp),sizeof(temp));
	// 	origin.push_back(temp);
	// 	examplefileC.write((char*)(&temp),sizeof(temp));
	// }
	origin.resize(8000,0);
	examplefileC.write((char*)(&origin[0]),sizeof(origin[0])*8000);
	examplefileC.close();
	// file.close();
	cout<<"Have done!"<<endl;
	return 0;
}
