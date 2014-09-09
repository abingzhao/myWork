#include "BinarySearchTree.h"


using namespace std;

// int main(int argc, char const *argv[])
// {
//     int a[] = {3,2,1,4,5,6,7,10,9,8};
//     AVLTreeNode<int> *rootNode = new AVLTreeNode<int>(a[0]);
//     bool taller = false;
//     for(int i = 1; i <= 9; ++i)
//     {
//         // cout << i << endl;
//         AVLInsert(&rootNode, a[i], taller);
//     }
//     AVLTreeNode<int> *pp;
//     AVLTreeNode<int> *ff;
//     for (int i = 0; i < 10; ++i)
//     {
//         pp = NULL;
//         ff = NULL;
//         if(AVLSearch(rootNode, a[i], &pp, &ff))
//         {
//             cout << "Find :" << (pp->value) ;
//             if(ff)
//                 cout << "; And his parent Node is :" << (ff->value) ;
//             else 
//                 cout << "; And his is The RootNODE!";
//             cout << endl;
//         }
//     }
//     std::cout << "\nMain Finished" << std::endl;
//     return 0;
// }




int main(int argc, char const *argv[])
{
    int a[] = {1,15,5,16,9,18,30,2};
    treeNode<int> *rootNode = CreateTree(a, sizeof(a)/sizeof(a[0]));
    


    // treeNode<int> *pp  = TreeMaximum(rootNode);
    
    // if(pp)
    //     cout << pp->key << endl;
    // pp = TreeMinimum(rootNode);
    
    // if(pp)
    //     cout << pp->key << endl;

    InorderTreeWalk(rootNode);
    while(rootNode)
    {
        cout << "\norigin :"; 
        InorderTreeWalk(rootNode);
        rootNode = TreeDelete(rootNode,rootNode);
        // TreeDelete(rootNode,rootNode);
        cout << "\nafter  :"; 
        InorderTreeWalk(rootNode);
    }
    std::cout << "\nMain Finished" << std::endl;
    return 0;
}