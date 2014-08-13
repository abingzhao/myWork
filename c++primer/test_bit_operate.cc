#include <iostream>
#include <climits>
const size_t int_len = sizeof(int)*8;
//===========取最值运算
int max_int_0(){ return (1<<(int_len-1))-1; }
int max_int_1(){ return ~(1<<(int_len-1)); }
int max_int_2(){ return ((unsigned int)-1)>>1;}
int min_int_0(){ return (1<<(int_len-1)); }
//===========乘除2相关运算
int multi_2(int a){ return (a<<1); }
int divid_2(int a){ return (a>>1); }
int multi_2(int a, int n){ return (a<<n); }//multiply by 2^n
int divid_2(int a, int n){ return (a>>n); }//divide by 2^n
//===========判断一个数的奇偶性
bool is_odd(int a){ return (a&1)==1;}
//===========不用临时变量交换两个数（面试常考）
void swap_int(int &a,int &b)
{
    a ^= b;
    b ^= a;
    a ^= b;
}
//===========取绝对值（某些机器上，效率比n>0  ?  n:-n 高）
int abs_int(int n){ return (n^(n>>int_len-1))-(n>>int_len-1); 
/**
 *  n>>31 ---> singned bit 
 */
}

//===========取两个数的最大值（某些机器上，效率比a>b ? a:b高）
int max_one_int_0(int a, int b)
{
    /*如果a>=b,(a-b)>>31为0，否则为-1*/  
    return b & ((a-b) >> 31) | a & (~(a-b) >> 31);
}
int max_one_int_1(int x, int y)
{
    /*如果x<y x<y返回1，否则返回0，与0做与运算结果为0，与-1做与运算结果不变*/ 
    return x^((x ^ y) & -(x < y));
}
//===========取两个数的最小值
int min_one_int_0(int x, int y)
{
    return x^((x ^ y) & -(x > y));
}
int min_one_int_1(int a, int b)
{
    return a & ((a-b) >> 31) | b & (~(a-b) >> 31);
}
//===========判断一个数是不是2的幂
bool is_power_of_2(int n)
{
    /* if n = 2^m ,n=..1000..   n-1= ....0111...   n&(n-1)=0*/
    return n>0 ? (n&(n-1))==0 : false;
}
//===========对2的n次方取余
int mod_powerof2(int a, int b)
{
    /**qu a%b here b must equal to 2^m*/
    return (a & (b-1));
    /*如果是2的幂，n一定是100... n-1就是1111.... 
     所以做与运算结果保留m在n范围的非0的位*/  
}

int main(int argc, char const *argv[])
{
    int a= 5,b = 6;
    std::cout<<"INT_MAX= "<<INT_MAX<<"\tmax_int_2()= "<<max_int_2()<<std::endl;
    std::cout<<"INT_MIN= "<<INT_MIN<<"\tmin_int_0()= "<<min_int_0()<<std::endl;
    std::cout<<"a= "<<5<<"\ta*2= "<<5*2<<"\tmulti_2(a)= "<<multi_2(5)<<std::endl;
    std::cout<<"a= "<<10<<"\ta/2= "<<10/2<<"\tdivid_2(a)= "<<divid_2(10)<<std::endl;
    std::cout<<"a= "<<5<<"\tn= "<<2<<"\tmulti_2(a,n)= "<<multi_2(5,2)<<std::endl;
    std::cout<<"a= "<<20<<"\tn= "<<2<<"\tdivid_2(a,n)= "<<divid_2(20,2)<<std::endl;
    std::cout<<"a= "<<5<<"\ta is an"<<(is_odd(5) ? " odd ":" even ")<<"number!"<<std::endl;
    std::cout<<"a= "<<a<<"\tb= "<<b<<"\tafter swap_int(a,b)";
    swap_int(a,b);
    std::cout<<"\ta= "<<a<<"\tb= "<<b<<std::endl;
    std::cout<<"a= "<<-6<<"\tb= "<<6<<"\tabs_int(a)="<<abs_int(-6)<<"\tabs_int(b)= "<<abs_int(6)<<std::endl;
    std::cout<<"a= "<<a<<"\tb= "<<b<<"\tmax_one_int_0(a,b)= "<<max_one_int_0(a,b)<<std::endl;
    std::cout<<"a= "<<a<<"\tb= "<<b<<"\tmax_one_int_1(a,b)= "<<max_one_int_1(a,b)<<std::endl;
    std::cout<<"a= "<<a<<"\tb= "<<b<<"\tmin_one_int_0(a,b)= "<<min_one_int_0(a,b)<<std::endl;
    std::cout<<"a= "<<a<<"\tb= "<<b<<"\tmin_one_int_1(a,b)= "<<min_one_int_1(a,b)<<std::endl;
    std::cout<<"a= "<<8<<"\tb= "<<5<<"\tis_power_of_2(a)"<<is_power_of_2(8)<<"\tis_power_of_2(b)"<<is_power_of_2(5)<<std::endl;
    std::cout<<"a= "<<15<<"\tb= "<<8<<"\tmod_powerof2(a,b)= "<<mod_powerof2(15,8)<<std::endl;
    std::cout<<"Have Done!"<<std::endl;
    return 0;
}