#include <iostream>

std::size_t num_digits(int);//声明式

int main()
{
    int x=1500;
    std::cout<<num_digits(x)<<"\n";
    std::cout<<sizeof(std::size_t)<<"\n";
    return 0;
}
std::size_t num_digits(int number)//定义式
{
    std::size_t digits_sofar = 1;
    while((number /= 10) != 0)
        ++digits_sofar;
    return digits_sofar;
}
