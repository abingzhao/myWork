/*******************************************************************************
    File        : hanoi.cc
    Description : Implement Hanoi Porblem With Divide and Conquer Category
    Author      : abing0513

    Revision                   History
    ----------    ---------    --------------------------------------------
    2014-08-29    abing0513    

*******************************************************************************/

/*******************************************************************************
    INCLUDE
*******************************************************************************/
#include <iostream>

/*******************************************************************************
    namespace
*******************************************************************************/
using namespace std;

/*******************************************************************************
    Function MoveOne
*******************************************************************************/
void MoveOne(int idx, char origin, char desti)
{
    cout << "Move NO." << idx << " From " << origin << " to " << desti << endl;
}
/*******************************************************************************
    FUNCTION Hanoi
*******************************************************************************/
void Hanoi(int num, char origin, char desti, char temp)
{
    if(num == 1)
        MoveOne(1, origin, desti);
    else
    {
        Hanoi(num - 1, origin, temp, desti);
        MoveOne(num, origin, desti);
        Hanoi(num - 1, temp, origin, desti);
    }
}

int main(int argc, char const *argv[])
{
    Hanoi(3, 'A', 'B', 'C');
    std::cout << "\nMain Finished" << std::endl;
    return 0;
}


