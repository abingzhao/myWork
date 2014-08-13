#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <cmath>
using namespace std;
int main()
{
	//vector<float > origin;
	fstream file("../grc_work/i_buffer.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream examplefileC ("../octave/i_buffer.txt");

	file.seekg(0,ios_base::beg);
	int i=0;
	for(;!file.eof();i++)
	{
		//complex<float> temp;
		float temp;
		file.read((char *)(&temp),sizeof(temp));
		//origin.push_back(temp);
		//if(i<19200)
		//if(abs(temp)==inf)
			//break;
			examplefileC<<(temp)<<endl;
	}
	examplefileC.close();
	file.close();
	cout<<"Have done!"<<endl;
	return 0;
}
