/*******************************************************************************
    File        : BinarySearchTree.cc
    Description : Learn Binary Search Tree related
    Author      : abing0513

    Revision                   Change Log
    ----------    ---------    --------------------------------------------
    2014-09-04    abing0513    New File, Define The node,

*******************************************************************************/





/*******************************************************************************
    Inlcude 
*******************************************************************************/
#ifndef INCLUDE_BINARY_SEARCH_TREE_H
#define INCLUDE_BINARY_SEARCH_TREE_H
#include <iostream>

/*******************************************************************************
    namespace
*******************************************************************************/
using namespace std;

/*******************************************************************************
    DEFINES: The tree node, And some basic opreation
*******************************************************************************/
#define ENABLE_RECURSION 1

template <typename T>
struct treeNode
{
    T key;
    treeNode<T> *pParent;
    treeNode<T> *pLeftChild;
    treeNode<T> *pRightChild;
    treeNode(T val):key(val),
    pParent(NULL),
    pLeftChild(NULL),
    pRightChild(NULL)
    {}
};
template <typename T>
T Key(treeNode<T> *pNode)
{
    return pNode->key;
}
template <typename T>
treeNode<T> * LeftChild(treeNode<T>* pNode)
{
    if(!pNode)
        return pNode->pLeftChild;
    return NULL;
}
template <typename T>
treeNode<T> * RightChild(treeNode<T>* pNode)
{
    if(!pNode)
        return pNode->pRightChild;
    return NULL;
}
template <typename T>
treeNode<T> * Parent(treeNode<T>* pNode)
{
    if(!pNode)
        return pNode->pParent;
    return NULL;
}
/*******************************************************************************
    Binary Search, Inlcude Maximum Value Search and Minimum value search
    reference : Introduce to Algorithm Page 152-158
*******************************************************************************/
template <typename T>
treeNode<T>* TreeSearch(treeNode<T> *rootNode, T val)
{
#if ENABLE_RECURSION // Recursively 递归方式
    if(NULL == rootNode || rootNode->key == val)
        return rootNode;
    else if(rootNode->key > val)
        return TreeSearch(rootNode->pLeftChild, val);
    else
        return TreeSearch(rootNode->pRightChild, val);
#else // Non-recursively 非递归方式
    treeNode<T> *pTmp = rootNode;
    while(pTmp!=NULL)
    {
        if(pTmp->key == val)
            return pTmp;
        else if(pTmp->key > val)
            pTmp = pTmp->pLeftChild;
        else
            pTmp = pTmp->pRightChild;
    }
    return pTmp;
#endif
}

template <typename T>
treeNode<T>* TreeMaximum(treeNode<T> *rootNode)
{
    if(rootNode)
    {
        int i = 1;
        treeNode<T> *pTmp = rootNode;
        while(pTmp->pRightChild)
        {
            pTmp = pTmp->pRightChild;
            ++i;
        }
        cout << "Right H = " << i << endl;
        return pTmp;
    }
    else
        return NULL;
}

template <typename T>
treeNode<T>* TreeMinimum(treeNode<T> *rootNode)
{

    if(rootNode)
    {
        int i = 1;
        treeNode<T> *pTmp = rootNode;
        while(pTmp->pLeftChild)
        {
            pTmp = pTmp->pLeftChild;
            ++i;
        }
        // cout << "Left H = " << i << endl;
        return pTmp;
    }
    else
        return NULL;
}


/*******************************************************************************
    Inorder Print Binary Search Tree, 
    reference : Introduce to Algorithm Page 152-158

*******************************************************************************/
template <typename T>
void InorderTreeWalk(treeNode<T> *rootNode)
{
    if(rootNode)
    {
        InorderTreeWalk(rootNode->pLeftChild);
        cout << rootNode->key << ", ";
        InorderTreeWalk(rootNode->pRightChild);
    }
}

/*******************************************************************************
    Insert Node and The Create of Binary Search Tree from array or vector
*******************************************************************************/
template <typename T>
void TreeInsert(treeNode<T> *rootNode, treeNode<T> *node)
{
    treeNode<T> *y = NULL;
    treeNode<T> *x = rootNode;
    while(x)
    {
        y = x;
        if(node->key < x->key)
        {
            x = x->pLeftChild;
        }
        else
            x = x->pRightChild;
    }
    if(!y)
        rootNode = node;
    else if(node->key < y->key)
    {
        y->pLeftChild = node;
        node->pParent = y;
    }
    else
    {
        y->pRightChild = node;
        node->pParent = y;
    }
}
template <typename T>
treeNode<T>* CreateTree(T* pEle,  int eleLen)
{
    if(pEle && eleLen != 0) 
    {
        int  i = 0;
        treeNode<T> *rootNode = new treeNode<T>(pEle[i]);
        while(++i < eleLen)
        {
            treeNode<T> *node = new treeNode<T>(pEle[i]);
            TreeInsert(rootNode,node);
        }
        return rootNode;
    }
    else
        return NULL;
}
/*******************************************************************************
    Delete ,Include Presuccessor and Successor
*******************************************************************************/
template <typename T>
treeNode<T> *TreeSuccessor(treeNode<T> *node)
{
    if(node)
    {
        if(node->pRightChild)
            return TreeMinimum(node->pRightChild);
        treeNode<T> *y = node->pParent;
        while(y && node == y->pRightChild)
        {
            node = y;
            y = node->pParent;
        }
        return y;
    }
    else 
        return NULL;
}
template <typename T>
treeNode<T> *TreePreSuccessor(treeNode<T> *node)
{
    if(node)
    {
        if(node->pLeftChild)
            return TreeMaximum(node->pLeftChild);
        treeNode<T> *y = node->pParent;
        while(y && node == y->pLeftChild)
        {
            node = y;
            y = node->pParent;
        }
        return y;
    }
    else 
        return NULL;
}
template <typename T>
treeNode<T> *TreeDelete(treeNode<T> *rootNode, treeNode<T>* node)
// void TreeDelete(treeNode<T> *rootNode, treeNode<T>* node)
{
    treeNode<T>* y = NULL;
    treeNode<T>* x = NULL;
    if(node->pLeftChild == NULL || node->pRightChild == NULL)
        y = node;
    else
        y = TreeSuccessor(node);
    // cout << y->pLeftChild << endl;
    if(y->pLeftChild)
        x = y->pLeftChild;
    else
        x = y->pRightChild;

    if(x)
        x->pParent = y->pParent;
    
    if(y->pParent == NULL)
    {
        rootNode = x;
        // cout << y->pParent << "    :" << x <<endl;
    }
    else if(y == y->pParent->pLeftChild)
    {
        y->pParent->pLeftChild  = x;
    }
    else
        y->pParent->pRightChild = x;

    // cout << "Delete " << node->key << endl;
    if(node!=y)
        node->key = y->key;

    delete y;
    y = NULL ;
    return rootNode;
}

#endif /*INCLUDE_BINARY_SEARCH_TREE_H*/