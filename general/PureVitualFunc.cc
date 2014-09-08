#include <iostream>
using namespace std;

class AAA{};

class voidA
{
    void f(){}
};
class voidB : public voidA
{
    void f(){}
};

class A
{
    virtual void fA(){}
};
class B: public A
{
    // int a;
    // int a2;
    // int a3;
    // int a4;
    // int a5;
    virtual void fB(){}
    void fb(){}
};

class vA
{
    virtual void fA() = 0;
};
class vB:virtual public vA
{
    virtual void fB(){}
};
int main(int argc, char const *argv[])
{
    cout << sizeof(AAA) << endl;
    cout << sizeof(voidA) << " " << sizeof(voidB) << endl;
    voidA va;voidB vb;
    cout << sizeof(va) << " " << sizeof(vb) << endl;
    cout << sizeof(A) << " " << sizeof(B) << endl;
    cout << sizeof(vA) << " " << sizeof(vB) << endl;
    int *a;
    cout << sizeof(a) << endl;
    return 0;
}

