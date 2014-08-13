#include <iostream>
#include "cyclic_buffer.h"

int main(int argc, char const *argv[])
{
    cyclicbuffer::cyclic_buffer<int> aa(cyclicbuffer::cyclic_buffer<int>(1024));
    // cyclic_buffer<int> *aa = new cyclic_buffer<int>(1024);
    std::cout<<aa.write_space()<<std::endl;

    return 0;
}