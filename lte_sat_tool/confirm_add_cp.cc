#include<iostream>
#include<fstream>
#include<complex>
#include<vector>
#include<cmath>
#include <cstring>
using namespace std;
int main()
{
    vector<complex<float> > origin;
    fstream file("out1.dat",ios_base::in|ios_base::out|ios_base::app|ios::binary);
    ofstream examplefileC ("out1.txt");
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
    int d_slotl=7*128+10+9*6;
    int sum=0;
    for (int i = 0; i < origin.size()/d_slotl; ++i)
    {
        std::vector<complex <float> > v(d_slotl);
        memcpy(&v[0],&origin[0+i*d_slotl],sizeof(complex<float>)*d_slotl);
        for (int j = 0; j < 7; ++j)
        {
            if(j==0)
                for (int ii = 0; ii < 10; ++ii)
                {
                    if (v[ii]!=v[ii+128])
                        sum++;
                }
            else
                for (int ii = 0; ii < 9; ++ii)
                {
                    if(v[138 + (j-1)*137 +ii]!=v[138 + (j-1)*137 +ii+128])
                        sum++;
                }
        }

    }
    cout<<"比较的总数木为："<<(origin.size()/d_slotl)*origin.size()<<endl;
    cout<<"错误的个数为"<<sum<<endl;
    return 0;
}