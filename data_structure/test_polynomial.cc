#include "polynomial.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main(int argc, char const *argv[])
{
    int times = 10000;
    srand(time(NULL));
    for (int j = 0; j < times; ++j)
    {
        int maxOrder1 = 5;
        int maxOrder2 = 5;
        int maxCoef  =  10; 
        std::vector<int> v1;
        std::vector<int> v2;
        for (int i = 0; i <= maxOrder1; ++i)
            v1.push_back(static_cast<int>(rand()%maxCoef));
        for (int i = 0; i <= maxOrder2; ++i)
            v2.push_back(static_cast<int>(rand()%maxCoef));
        
        typename polynomial<std::vector<int> >::sptr poly2;
        typename polynomial<std::vector<int> >::sptr poly1;
        
        poly1 = polynomial<std::vector<int> >::make(v1,maxOrder1);
        poly2 = polynomial<std::vector<int> >::make(v2,maxOrder2);
        
        typename polynomial<std::vector<int> >::sptr polyr;
        polyr = PolySubtract<std::vector<int> >(poly1,poly2);

        cout<<"\n\n****************************************The "<<j
            <<"th Test*******************************************"<<endl;
        cout<<"THe first  Poly : ";
        poly1->PrintPolynomial();
        cout<<"THe second Poly : ";
        poly2->PrintPolynomial();
        cout<<"THe result Poly : ";
        polyr->PrintPolynomial();
    }    
    cout<<"\nMain Finished!"<<endl;
    return 0;
}
