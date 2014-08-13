#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
using namespace std;
int main()
{
	vector<char > origin;
	fstream file("screamble.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream examplefileC ("screamble.txt");
	file.seekg(0,ios_base::beg);
	int i=0;
	for(;!file.eof();i++)
	{
		char temp;
		file.read((char *)(&temp),sizeof(temp));
		origin.push_back(temp);
		if(i<20000)
			examplefileC<<(int)temp<<endl;
	}
	examplefileC.close();
	file.close();
	cout<<"Have done!"<<endl;
	return 0;
}
