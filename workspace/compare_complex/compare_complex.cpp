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
	fstream file("000.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream examplefileC ("demap_out.txt");
	file.seekg(0,ios_base::beg);

	for(int i=0;!file.eof();i++)
	{
		complex<float> temp;
		file.read((char *)(&temp),sizeof(temp));
		origin.push_back(temp);
		if(i<10000)
			examplefileC<<temp<<endl;
	}
	examplefileC.close();
	file.close();
	fstream file1("111.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream example ("map_in.txt");
	for (int i=0;!file1.eof();i++)
	{
		complex<float> temp;
		file1.read((char*)(&temp),sizeof(temp));
		newly_delt.push_back(temp);
		if (i<10000)
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
		if ( (abs(origin[i]-newly_delt[i]) > 0.01)
				|(abs(abs(arg(origin[i]))-abs(arg(newly_delt[i])))>0.01) )
		{
			n++;
			cout<<i<<": origin[i]="<<origin[i]<<"	newly_delt[i]="<<newly_delt[i]<<endl;
		}
	}
	if(n==0)
		cout<<"No error!"<<endl;
	else
		cout<<"错误的个数为"<<n<<endl;

	cout<<"Have done!"<<endl;
	return 0;
}