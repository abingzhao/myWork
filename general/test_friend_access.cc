#include <iostream>

class A
{
private:
    int mi_A;
public:
    A(int a):mi_A(a){}
    friend class B;    
};

class B
{
private:
    A cl_a;
public:
    B(int aa):cl_a(A(aa)){}
    void print_a()
    {
        std::cout<<cl_a.mi_A<<std::endl;
    }    
};

int main(int argc, char const *argv[])
{
    B b(10);
    b.print_a();
    return 0;
}