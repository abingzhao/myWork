#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <string>
static void out_to_screen(int &ele)
{
    std::cout<<ele<<",";
}
static bool sort_by_aa(int a,int b)
{
    return a<b;
}
typedef struct stundent_score
{
    std::string name;
    unsigned int score;
} stundent_score;
bool sort_by_score_up(const stundent_score &a, const stundent_score &b)
{
    return a.score<b.score;
}

bool sort_by_score_down(const stundent_score &a, const stundent_score &b)
{
    return a.score>b.score;
}
void print_std(const stundent_score &ss)
{
    std::cout<<"\tName  : "<<ss.name
             <<"\tScore : "<<ss.score<<std::endl;
}
int main(void)
{
    srand(time(0));
    std::vector<stundent_score> v;
    for (int i = 0; i < 5; ++i)
    {
        int a = rand()%100;
        stundent_score ss;
        ss.name = "zhangsan"; 
        ss.score = a;
        v.push_back(ss);
    }
    for_each(v.begin(),v.end(),print_std);
    std::cout<<std::endl;
    sort(v.begin(),v.end(),sort_by_score_up);
    for_each(v.begin(),v.end(),print_std);
    std::cout<<std::endl;
    sort(v.begin(),v.end(),sort_by_score_down);
    std::cout<<std::endl;
    for_each(v.begin(),v.end(),print_std);
    std::cout<<"\nHave Done!"<<std::endl;
    return 0;
}