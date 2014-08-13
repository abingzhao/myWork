#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include "test_container.h"



int main(int argc, char const *argv[])
{
    int dim[] = {1,2,3,4,5,6,7,8,9,10};
    vector<int> v1;
    v1.assign(dim,dim+10);
    cout<<"Ele In v1:"<<endl<<"\t";
    for_each(v1.begin(),v1.end(),print_vec<int>);
    cout<<endl;

    list<int> l1,l2,l3;
    copy(v1.begin(),v1.end(),back_inserter(l1));
    cout<<"Ele In l1:"<<endl<<"\t";
    for_each(l1.begin(),l1.end(),print_vec<int>);
    cout<<endl;
    
    copy(v1.begin(),v1.end(),front_inserter(l2));
    cout<<"Ele In l2:"<<endl<<"\t";
    for_each(l2.begin(),l2.end(),print_vec<int>);
    cout<<endl;

    cout<<"Ostream_iterator for l2:"<<endl<<"\t";
    copy(l2.begin(),l2.end(),ostream_iterator<int>(cout,", "));
    cout<<endl;

    cout<<"Modified l3:"<<endl<<"\t";
    copy(l2.begin(),l2.end(),back_inserter(l3));
    copy_backward(v1.begin(),v1.begin()+6,l3.end());
    copy(l3.begin(),l3.end(),ostream_iterator<int>(cout,"\t"));
    cout << endl;

    cout<<"\nHave Done!"<<endl;
    return 0;
}

