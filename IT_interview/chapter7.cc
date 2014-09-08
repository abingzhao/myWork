#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    /****************page 81,example 4*************************/
    char *a[] ={"hello","the","world"};
    cout << a[0] << a[1] << a[2] << endl;
    char **pa = a;
    // pa++;
    cout << *pa++ << endl;
    cout << *pa++ << endl;
    cout << *pa << endl;
    /**/
    enum aa { 
    bbb= 0, 
    ccc=4,
    };
    cout << static_cast<int>(bbb) << endl;
    cout << static_cast<int>(ccc) << endl;
    cout << "Main Finished\n" << endl;
    return 0;
}