#include <iostream>
#include <cstdlib>
// #include <bo>

using namespace std;
class A;
class construtor_A;
class use_A;

class A
{
public:
    A(){}
    ~A(){cout<<__func__<<": LINE "<<__LINE__<<endl;}
    void print_A()
    {
        cout<<"Here Using One Function IN Class A!"<<endl;
    }
};

class use_A
{
private:
    A* p_A;
public:
    use_A():p_A(NULL){}
    ~use_A(){}
    void set_p_A(A* p_a_in_con_A)
    {
        p_A = p_a_in_con_A;
        cout<<__func__<<":LINE "<<__LINE__<<"\tp_A="<<p_A<<endl;
    }
    void call_print_A_in_use_A()
    {
        if(NULL != p_A)
        {
            p_A->print_A();
        }
        else
            cout<<"Has INVALID Pointor to Class A!"<<endl;
    }
    void free_A()
    {
        if(NULL != p_A)
        {
            delete p_A;
            p_A = NULL;
        }
    }
};
class construtor_A
{
private:
    A     *p_a_in_con_A;
    use_A *p_use_A;
    int   *aaa;
public:
    construtor_A()
    :  p_a_in_con_A(new A())
     , p_use_A(new use_A())
     , aaa(NULL)
    { 
        cout<<__func__<<":LINE "<<__LINE__<<"\tp_a_in_con_A="<<p_a_in_con_A<<endl;
        p_use_A->set_p_A(p_a_in_con_A);
    }
    ~construtor_A()
    {
        if(aaa!=NULL)
            free (aaa);
        cout<<__func__<<": LINE "<<__LINE__<<endl;
    }
    void call_use_A()
    {
        p_use_A->call_print_A_in_use_A();
    }
    void free_A()
    {
        delete p_a_in_con_A;
        p_a_in_con_A = NULL;
    }
    void call_free_A_in_use_A()
    {
        p_use_A->free_A();
    }
    void use_malloc()
    {
        aaa = (int*)malloc(sizeof(int)*100000);
    }
};

int main(int argc, char const *argv[])
{
    construtor_A p_c_A= construtor_A();
    p_c_A.call_use_A();
    p_c_A.free_A();
    construtor_A p_c_A2= construtor_A();
    p_c_A.call_use_A();
    cout<<"Have Done !"<<endl;
    return 0;
}