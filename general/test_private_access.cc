/**
 * 访问控制符 public, protected, private 只在编译阶段访问控制。
 * 也就是说运行时刻可访问 private 成员,用函数指针。
 */

#include <iostream>

class FFF;
typedef void ( FFF::*pFunc)();
pFunc func;
class FFF
{
public:
    FFF()
    {
        func = &FFF::print;
    }
private:
    void print()
    {
        std::cout<<"Here IN Private Member Function"<<std::endl;
    }
};

int main(int argc, char const *argv[])
{
    FFF f;
    (f.*func)();
    return 0;
}