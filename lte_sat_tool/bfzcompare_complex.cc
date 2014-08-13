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
	fstream file("../grc_work/fd_re_grid.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	// ofstream examplefileC ("out1.txt");
	file.seekg(0,ios_base::beg);

	for(int i=0;!file.eof();i++)
	{
		complex<float> temp;
		file.read((char *)(&temp),sizeof(temp));
		origin.push_back(temp);
		//if((i>=9600)&(i<19200))
			// examplefileC<<temp<<endl;
	}
	// examplefileC.close();
	file.close();
	fstream file1("../grc_work/tx_fd.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
	// ofstream example ("out2.txt");
	for (int i=0;!file1.eof();i++)
	{
		complex<float> temp;
		file1.read((char*)(&temp),sizeof(temp));
		newly_delt.push_back(temp);
		//if (i<10000)
			// example<<temp<<endl;
	}
	// example.close();
	file1.close();
	int d=min(origin.size(),newly_delt.size());
	int n=0;
	for(int i=0;i<d-1;i++)
	{
		if((i%100)==0)
			cout<<i<<": origin[i]="<<origin[i]<<"	newly_delt[i]="<<newly_delt[i]<<endl;
		if (  (abs(origin[i].real()-newly_delt[i].real())>0.000001)
			| (abs(origin[i].imag()-newly_delt[i].imag())>0.000001) )
		{
			
			n++;
			cout<<i<<": origin[i]="<<origin[i]<<"	newly_delt[i]="<<newly_delt[i]<<endl;
			break;
		}
	}
	cout<<"比较的总数木为："<<d<<endl;
	if(n==0)
		cout<<"No error!"<<endl;
	else
		cout<<"错误的个数为"<<n<<endl;

	cout<<"Have done!"<<endl;
	return 0;
}