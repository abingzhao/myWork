#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "BinaryTree.h"
using namespace std;



int main(int argc, char const *argv[])
{
    int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    AVLTreeNode<int> *rootNode = new AVLTreeNode<int>(a[0]);
    bool taller = false;
    for(int i = 1; i <= 14; ++i)
    {
        // cout << i << endl;
        AVLInsert(&rootNode, a[i], taller);
    }
    // AVLTreeNode<int> *pp;
    // AVLTreeNode<int> *ff;
    // for (int i = 0; i < 15; ++i)
    // {
    //     pp = NULL;
    //     ff = NULL;
    //     if(AVLSearch(rootNode, a[i], &pp, &ff))
    //     {
    //         cout << "Find :" << (pp->key) ;
    //         if(ff)
    //             cout << "; And his parent Node is :" << (ff->key) ;
    //         else 
    //             cout << "; And his is The RootNODE!";
    //         cout << endl;
    //     }
    // }
    int maxL;
    int maxR;
    cout << GetNodeNum(rootNode) << endl;
    cout << GetDepth(rootNode) << endl;
    LevelTraverse(rootNode);
    cout << "\n NUM of Leaf Node " << TreeLeafNodeNum(rootNode) << endl; 
    cout << GetMaxDistance(rootNode, maxL, maxR) << endl;

    cout << "\nPre Order : " << "\t";
    PreOrderTraverse(rootNode);
    cout << "\nPre Order  : " << "\t";
    PreOrderNonrecursive(rootNode);
    cout << endl;
    cout << endl;
    cout << "\nIn Order  : " << "\t";
    InOrderTraverse(rootNode);
    cout << "\nIn Order  : " << "\t";
    InOrderNonrecursive(rootNode);
    cout << endl;
    cout << "\nPost Order: " << "\t";
    PostOrderTraverse(rootNode);
    cout << "\nPost Order: " << "\t";
    PostOrderNonrecursive(rootNode);
    cout << endl;
    treeNode<int> *rootNode1 = CreateTree(a, sizeof(a)/sizeof(a[0]));
    // treeNode<int> *pp  = TreeMaximum(rootNode1);
    
    // if(pp)
    //     cout << pp->key << endl;
    // pp = TreeMinimum(rootNode1);
    
    // if(pp)
    //     cout << pp->key << endl;

    // InorderTreeWalk(rootNode1);
    // while(rootNode1)
    // {
    //     cout << "\norigin :"; 
    //     InorderTreeWalk(rootNode1);
    //     rootNode1 = TreeDelete(rootNode1,rootNode1);
    //     // TreeDelete(rootNode1,rootNode1);
    //     cout << "\nafter  :"; 
    //     InorderTreeWalk(rootNode1);
    // }
    cout << GetNodeNum(rootNode1) << endl;
    cout << GetDepth(rootNode1) << endl;

    std::cout << "\nMain Finished" << std::endl;
    return 0;
}
