#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// template<typename Bag>
// typename Bag::value_type min(const Bag & b)
// {
// 	typename Bag::const_iterator it;
// 	typename Bag::value_type m = *b.begin();
// 	for (it = b.begin(); it != b.end(); ++it)
// 	if (*it < m)
// 	m = *it;
// 	return m;
// }

template<typename T>
void pp(const T& t)
{
	//typename T::reference r = *t;
	std::cout<<t<<"\t";
}
template<typename T>
void print_vec(const T& ele)
{
    cout<<" "<<ele;
}

int main()
{
	vector<string> input;
	string temp;
	input.push_back("aaa");
	input.push_back("bbb");
	input.push_back("ccc");
	input.push_back("ddd");

	std::vector<string>::size_type len = input.size();
	std::cout<<"input len = "<<len<<std::endl;
	std::vector<int> v;
	for (int i = 0; i < 10; ++i)
	{
		v.push_back(rand()%10);
		cout<<v[i]<<"\t";
	}
	cout<<endl;
    for_each(v.begin(),v.end(),pp<int>);
	cout<<endl;
    //cout<<endl<<min(v)<<endl;
    // pp("slslslslsl");    
	vector<string>::iterator want = std::find(input.begin(),input.end(), string("ccc"));
	if (want != input.end())
	{
		vector<string>::value_type r = *want;
		std::cout<<r<<std::endl;
        r="abc";
		std::cout<<r<<std::endl;
		std::cout<<input[2]<<std::endl;

		//r = "bogus";
	}

}