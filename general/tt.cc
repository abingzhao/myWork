#include <iostream>
#include <cstdlib>
#include <cstring>
class tt
{
    int a;
    int b;
    int *p_int;
public:
    tt(int aa,int bb):a(aa),b(bb)
    {
        p_int = (int*)malloc(sizeof(int)*10);
        memset(p_int,0,sizeof(int)*10);
        std::cout<<__func__;
        print_a_b();
    }
    ~tt()
    {
        if(p_int!=NULL)
            free(p_int);
        std::cout<<__func__<<std::endl;
    }

    void print_a_b(void )
    {
        std::cout<<"\ta=\t"<<a<<"\tb=\t"<<b<<std::endl;
    }
    void write_p_int(int d,int idx)
    {
        p_int[idx] = d;
    }
};

int main(int argc, char const *argv[])
{
    tt tttt(5,6);
    tttt = tt(55,66);
    tttt = tt(555,666);
    std::cout<<"\nHave Done!"<<std::endl;
    return 0;
}