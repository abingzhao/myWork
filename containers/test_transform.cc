#include "test_container.h"

template<typename T>
T multi_add( T& ele)
{
    ele *= static_cast<T>(10);
    ele += static_cast<T>(10);
    return ele;
}

int main(int argc, char const *argv[])
{
    float vec[] = {1,3,5,7,9,11,13,15,17,19};
    cout<<"origin ele  :"<<"\t";
    for_each(vec,vec+10,print_vec<float>);
    cout<<endl;

    vector<float> v1;
    v1.assign(vec,vec+10);
    cout<<"Multiple_add:"<<"\t";
    transform(v1.begin(),v1.end(),v1.begin(),multi_add<float>);
    copy(v1.begin(),v1.end(),ostream_iterator<float>(cout,", "));
    cout<<endl;

    list<float> l1,l2;
    transform(vec,vec+10,back_inserter(l1),negate<float>());
    cout<<"Multiple -1 :"<<"\t";
    for_each(l1.begin(),l1.end(),print_vec<float>);
    cout<<endl;

    transform(l1.begin(),l1.end(),l1.begin(),bind2nd(multiplies<float>(),10.0));
    cout<<"Multiple 10 :"<<"\t";
    copy(l1.begin(),l1.end(),ostream_iterator<float>(cout,", "));
    cout<<endl;

    cout<<"Divides  10 :"<<"\t";
    transform(l1.rbegin(),l1.rend(),ostream_iterator<float>(cout,", "),bind2nd(divides<float>(),10.0));
    cout<<endl;
    cout<<endl;
    cout<<"            :"<<"\t";
    copy(l1.begin(),l1.end(),ostream_iterator<float>(cout,", "));
    cout<<endl;

    copy(vec,vec+10,back_inserter(l2));
    transform(vec,vec+10,l2.begin(),l2.begin(),multiplies<float>());
    // transform(vec,vec+10,l2.begin(),back_inserter(l2),multiplies<float>());
    cout<<"Square l2   :"<<"\t";
    // for_each(l2.begin(),l2.end(),print_vec<float>);
    copy(l2.begin(),l2.end(),ostream_iterator<float>(cout,", "));
    cout<<endl;



    transform(vec,vec+10,l2.begin(),l2.begin(),plus<float>()    );
    cout<<"Plus   l2   :"<<"\t";
    copy(l2.begin(),l2.end(),ostream_iterator<float>(cout,", "));
    cout<<endl;

    cout<<"Minus  l2   :"<<"\t";
    transform(l2.begin(),l2.end(),l1.begin(),ostream_iterator<float>(cout,", "),minus<float>());
    cout<<endl;
    cout<<"\n\nHave Done!"<<endl;
    return 0;
}