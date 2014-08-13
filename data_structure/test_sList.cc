#include "sList.hpp"
#include <list>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(int argc, char const *argv[])
{
    cout.width(4);
    // sListNode<int> * sln = new sListNode<int>(5); 
    // cout<< (*sln)()<<endl;
    // delete sln;
    size_t len = 0;
    srand(time(0));
    sList<int> slist;
    for (int i = 0; i < 5; ++i)
    {
        slist.PushFront(1);
        slist.PushBack(2);
    }
    len =  slist.ListLength();
    for (size_t i = 0; i < len; ++i)
    {
        cout<<"\t"<<slist.GetEleAt(i);
        if(i%10 == 9)
            cout<<endl;
    }cout<<"After push_front and PushBack,List size :"<<slist.ListLength()<<endl;
    for (int i = 0; i < 10; ++i)
    {
        size_t len = slist.ListLength();
        size_t pos = rand()%len;
        int    _data = rand()%1000;
        slist.InsertAfter(pos,5);
        slist.InsertBefore(pos,10);
    }
    cout<<"After InsertAfter and InsertAfter,List size :"<<slist.ListLength()<<endl;
     len = slist.ListLength();
    for (size_t i = 0; i < len; ++i)
    {
        cout<<"\t"<<slist.GetEleAt(i);
        if(i%10 == 9)
            cout<<endl;
    }

    sList<char> ss;
    cout<<ss.ListLength()<<endl; 
    cout<<"\nSuccessful Finished Main!"<<endl;
    return 0;
}