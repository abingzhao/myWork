#include <iostream>


int main(int argc, char const *argv[])
{
    for(;;)
    {
        for (int i = 0; i < 9600000*5; ++i)
            ;
        sleep(10);
    }
    std::cout << "\nMain Finished" << std::endl;
    return 0;
}