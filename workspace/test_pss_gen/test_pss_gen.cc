#include "pss_gen.h"
#include <iostream>
#include <vector>
using namespace std;
int main()
{
	pss_gen aa;

	const vector<vector<gr_complex> > a=aa.get_fd_pss();
    //for (int i = 0; i < 62; ++i)
    
        //cout<<abs(a[0][i])<<endl;
    
    //cout<<a.size()<<endl;
    cout<<"Have Done!"<<endl;
    //aa.~pss_gen();
	return 0;
}
