#include <iostream>

//==============================================================================
class profession
{
public:
    virtual void show_job()    = 0;
    virtual void show_salary() = 0;
};
//------------------------------------------------
class sex
{
public:
    virtual void show_sex() = 0;
};
//==============================================================================
class teachers :public profession
{
public:
    void show_job()
    {
        std::cout<<"I'm a teachers! ";
    }
    void show_salary()
    {
        std::cout<<" and my salary is high!\n";
    }
};
//------------------------------------------------
class cleaners :public profession
{
public:
    void show_job()
    {
        std::cout<<"I'm a cleaners! ";
    }
    void show_salary()
    {
        std::cout<<" and my salary is low!\n";
    }
};
//------------------------------------------------
class unemployeds :public profession
{
public:
    void show_job()
    {
        std::cout<<"I have no jod now! ";
    }
    void show_salary()
    {
        std::cout<<" so no salary!\n";
    }
};
//==============================================================================
class male :public sex
{
public:
    void show_sex ()
    {
        std::cout<<"I'm a man! ";
    }
};
//------------------------------------------------
class female :public sex
{
public:
    void show_sex ()
    {
        std::cout<<"I'm a woman! ";
    }
};
//==============================================================================
class person
{
private:
    profession* _pro;
    sex*        _sex;
public:
    person(profession* pro,sex* se)
    {
        _pro = pro;
        _sex = se;
    }
    ~person(){}
    void person_info()
    {
        _sex->show_sex();
        _pro->show_job();
        _pro->show_salary();
    }
};
//==============================================================================
int main(int argc, char const *argv[])
{
    teachers teacher;
    cleaners cleaner;
    unemployeds unemployed;
    male m;
    female w;
    person p1(&teacher,&m);
    person p2(&cleaner,&w);
    person p3(&unemployed,&w);
    p1.person_info();
    p2.person_info();
    p3.person_info();
    return 0;
}