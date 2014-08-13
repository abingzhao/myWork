#include <iostream>
#include <vector>
 
using namespace std;
 
vector <string> v;
char ch;
 
int main ()
{
 
    for(int i=0; i<100000000; i++)
        v.push_back("abcdefghijklmn");
    cin >> ch;
    // 此时检查内存情况 占用54M
 
    v.clear();
    cin >> ch;
    // 此时再次检查， 仍然占用54M
 
    cout << "Vector 的 容量为" << v.capacity() << endl;
    // 此时容量为 1048576
 
    vector<string>(v).swap(v);
 
    cout << "Vector 的 容量为" << v.capacity() << endl;
    // 此时容量为0
    cin >> ch;
    // 检查内存，释放了 10M+ 即为数据内存
    return 0;
}