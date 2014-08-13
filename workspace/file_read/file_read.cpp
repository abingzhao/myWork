#include<iostream>
#include<fstream>
#include<complex>
#include<vector>
#include<cmath>
using namespace std;
int main()
{
	vector<complex<float> > origin;
	vector<complex<float> > newly_delt;
	//vector<char > origin;
	//vector<char > newly_delt;
	fstream file("000.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream examplefileC ("000.txt");
	file.seekg(0,ios_base::beg);
	int i=0;
	for(;!file.eof();i++)
	{
		//char temp;
		complex<float> temp;
		file.read((char *)(&temp),sizeof(temp));
		origin.push_back(temp);
		if(i<20000)
			examplefileC<<temp<<endl;
	}
	examplefileC.close();
	file.close();
	/*
	fstream file1("demap_out.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream example ("unpacked_out.txt");
	for (;!file1.eof();)
	{
		//char temp;
		complex<float> temp;
		file1.read((char*)(&temp),sizeof(temp));
		newly_delt.push_back(temp);
		example<<temp<<endl;
	}
	example.close();
	file1.close();
	int d=min(origin.size(),newly_delt.size());
	d=d-d%9312;
	cout<<"比较的总数木为："<<d<<endl;
	int n=0;
	for(int i=0;i<d;i++)
	{
		if ( (abs(abs(origin[i])-abs(newly_delt[i])) > 0.001)
				|(abs(arg(origin[i])-arg(newly_delt[i]))>0.001) )
		//if (origin[i]!=newly_delt[i])
		{
			n++;
			cout<<i<<endl;
		}
	}
	if(n==0)
		cout<<"No error!"<<endl;
	else
		cout<<"错误的个数为"<<n<<endl;
	*/
	cout<<"Have done!"<<endl;
	return 0;
}
