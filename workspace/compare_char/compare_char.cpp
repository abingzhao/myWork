#include<iostream>
#include<fstream>
#include<complex>
#include<vector>
#include<cmath>
using namespace std;
int main()
{

	vector<char > origin;
	vector<char > newly_delt;
	fstream file("source.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream examplefileC ("after_scatter.txt");
	file.seekg(0,ios_base::beg);

	for(int i=0;!file.eof();i++)
	{
		char temp;
		file.read((char *)(&temp),sizeof(temp));
		origin.push_back(temp);
		if (i<40000)
			examplefileC<<(int)temp<<endl;
	}
	examplefileC.close();
	file.close();
	fstream file1("sink.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	ofstream example ("after_decision.txt");
	for (int i=0;!file1.eof();i++)
	{
		char temp;
		file1.read((char*)(&temp),sizeof(temp));
		newly_delt.push_back(temp);
		if (i<40000)
			example<<(int)temp<<endl;

	}
	example.close();
	file1.close();
	int d=min(origin.size(),newly_delt.size());
	//d=d-d%9312;
	cout<<"比较的总数木为："<<d<<endl;
	int n=0;
	for(int i=0;i<d;i++)
	{
		if (origin[i]!=newly_delt[i])
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
