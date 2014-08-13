#include "test_container.h"
#include <deque>
template<typename T>
class multi_ply
{
private:
    T __param;
public:
    multi_ply(T _val):__param(_val){}
    T operator () (T & ele) const 
    {
        return __param * ele;
    }  
};

template<typename T>
class multiply
{
private:
    T __param;
public:
    multiply(T _val):__param(_val){}
    T operator()(T& ele1, T& ele2) const 
    {
        return (ele1 + ele2) * __param;
    }    
};

int main(int argc, char const *argv[])
{
    std::vector<double> v;
    list<double>  l;
    fill_vec_with_rand<std::vector<double> ,double>(v,1,10);
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    fill_vec_with_rand<std::list<double> ,double>(l,1,10);
    cout<<"Origin          v:\t";
    for_each(v.begin(),v.end(),print_vec<double>);
    cout<<endl;
    cout<<"Origin          l:\t";
    for_each(l.begin(),l.end(),print_vec<double>);
    cout<<endl;
    transform(v.begin(),v.end(),v.begin(),multi_ply<double>(0.5));
    cout<<"After multi_ply v:\t";
    for_each(v.begin(),v.end(),print_vec<double>);
    cout<<endl;

    deque <double> q;
    transform(v.begin(),v.end(),l.begin(),back_inserter(q),multiply<double>(2));
    cout<<"After multiply  q:\t";
    for_each(q.begin(),q.end(),print_vec<double>);
    cout<<endl;
    cout<<"\n\nHave Done!"<<endl;
    return 0;
}