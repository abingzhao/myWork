/*******************************************************************************
    File        : AVLTree.cc
    Description : Practice basic operation on AVL Tree 
    Author      : abing0513

    Revision                   Change Log
    ----------    ---------    --------------------------------------------
    2014-09-09    abing0513    New Add File;
                               Complete LeftRotate RightRatate LeftBalance 
                               RightBalance and AVLInsert AVLSearch

*******************************************************************************/

/*******************************************************************************
    include 
*******************************************************************************/
#ifndef INCLUDE_AVLTREE_H
#define INCLUDE_AVLTREE_H
#include <iostream>

/*******************************************************************************
    Tree Node Define 
*******************************************************************************/
typedef enum {
    LEFT_HIGHER = 0,
    BALANCED,
    RIGHT_HIGHER,
} BalanceFactor;

template <typename T>
struct AVLTreeNode
{
    T value;
    BalanceFactor bFactor;// 
    AVLTreeNode<T> * pLeftChild, *pRightChild;
    AVLTreeNode(T _val = 0)
    : value(_val),
      bFactor(BALANCED),
      pLeftChild(NULL),
      pRightChild(NULL)
    {}
};

/*******************************************************************************
    Left/Right Rotate :The Root Node is *Tree
*******************************************************************************/
template <typename T>
void RightRotate(AVLTreeNode<T> **Tree)
{
    AVLTreeNode<T> *L  = (*Tree)->pLeftChild;
    (*Tree)->pLeftChild = L->pRightChild;
    L->pRightChild = (*Tree);
    *Tree = L; 
}

template <typename T>
void LeftRotate(AVLTreeNode<T> **Tree)
{
    AVLTreeNode<T> *R  = (*Tree)->pRightChild;
    (*Tree)->pRightChild = R->pLeftChild;
    R->pLeftChild   = (*Tree);
    *Tree = R;
}


/*******************************************************************************
    LeftBalance/RightBalance : 
*******************************************************************************/
template <typename T>
void LeftBalance(AVLTreeNode<T> **Tree)
{
    AVLTreeNode<T> *L = (*Tree)->pLeftChild;
    switch(L->bFactor)
    {
        case LEFT_HIGHER:
        {
            // LL 
            (*Tree)->bFactor = BALANCED;
            L->bFactor       = BALANCED;
            RightRotate(Tree);
            break;
        }
        case RIGHT_HIGHER:
        {
            // LR ,first Left_rotate,then Right_rotate
            AVLTreeNode<T> *Lr = L->pRightChild;
            switch(Lr->bFactor)
            {
                case LEFT_HIGHER:
                {
                    (*Tree)->bFactor = RIGHT_HIGHER;
                    L->bFactor       = BALANCED;
                    break;
                }
                case BALANCED:
                {
                    (*Tree)->bFactor = BALANCED;
                    break;
                }
                case RIGHT_HIGHER:
                {
                    (*Tree)->bFactor = BALANCED;
                    L->bFactor       = LEFT_HIGHER;
                    break;
                }
            }
            Lr->bFactor = BALANCED;
            LeftRotate(&(*Tree)->pLeftChild);
            RightRotate(Tree);
        }
        default :
        {
            std::cout << "BALANCED!" << std::endl;
            break;
        }
    }
}
template <typename T>
void RightBalance(AVLTreeNode<T> **Tree)
{
    AVLTreeNode<T> *R = (*Tree)->pRightChild;
    switch(R->bFactor)
    {
        case RIGHT_HIGHER:
        {
            (*Tree)->bFactor = BALANCED;
            R->bFactor       = BALANCED;
            LeftRotate(Tree);
            break;
        }
        case LEFT_HIGHER:
        {
            AVLTreeNode<T> *Rl = R->pLeftChild;
            switch(Rl->bFactor)
            {
                case LEFT_HIGHER:
                {
                    (*Tree)->bFactor = LEFT_HIGHER;
                    R->bFactor       = BALANCED;
                    break;
                }
                case BALANCED:
                {
                    (*Tree)->bFactor = BALANCED;
                    break;
                }
                case RIGHT_HIGHER:
                {
                    (*Tree)->bFactor = BALANCED;
                    R->bFactor       = RIGHT_HIGHER;
                    break;
                }
                RightRotate(&(*Tree)->pRightChild);
                LeftRotate(Tree);
            }
        }
        // default:
        // {
        //     std::cout << "BALANCED!" << std::endl;
        //     break;
        // }
    }

}
/*******************************************************************************
    Tree Insert
*******************************************************************************/
template <typename T>
bool AVLInsert(AVLTreeNode<T> **Tree, const T ele, bool &taller)
{
    //若在平衡二叉树中不存在结点值和num一样大小的结点  
    //则插入值为num的新结点，并返回true  
    //若因为插入而使得二叉排序树失去平衡，则做平衡旋转处理  
    //taller反映树是否长高 
    if(!*Tree)
    {
        (*Tree) = new AVLTreeNode<T>(ele);
        taller = true;
    }
    else
    {
        if(ele == (*Tree)->value)
        {
            taller = false;
            return false;
        }
        if(ele < (*Tree)->value)
        {
            if(!AVLInsert(&(*Tree)->pLeftChild, ele, taller))
                return false;
            if(taller)
            {
                switch((*Tree)->bFactor)
                {
                    case LEFT_HIGHER:
                    {
                        /*————————————————————— 
                        / 插入前左子树高于右子树，需要进行做平衡处理 
                        / 不管是单向左旋处理，还是先左后右平衡处理 
                        / 处理结果都是使得插入新结点后，树的高度不变 
                        /—————————————————————*/ 
                        LeftBalance(Tree);
                        taller = false;
                        break;
                    }
                    case BALANCED:
                    {
                        (*Tree)->bFactor = LEFT_HIGHER;
                        taller = true;
                        break;
                    }
                    case RIGHT_HIGHER:
                    {
                        (*Tree)->bFactor = BALANCED;
                        taller = false;
                        break;
                    }
                }
            }
        }
        else
        {
            if(!AVLInsert(&(*Tree)->pRightChild, ele, taller))
                return false;
            if(taller)
            {
                switch((*Tree)->bFactor)
                {
                    case LEFT_HIGHER:
                    {
                        (*Tree)->bFactor = BALANCED;
                        taller = false;
                        break;
                    }
                    case BALANCED:
                    {
                        (*Tree)->bFactor = RIGHT_HIGHER;
                        taller = true;
                        break;
                    }
                    case RIGHT_HIGHER:
                    {
                        RightBalance(Tree);
                        taller = false;
                        break;
                    }
                }
            }
        }
    }
    return true;
}
/*******************************************************************************
    Tree Search
*******************************************************************************/
template <typename T>
bool AVLSearch( AVLTreeNode<T> *rootNode, const T ele, 
                AVLTreeNode<T> **targetNode, AVLTreeNode<T> **pNode)
{
    *pNode      = NULL;
    *targetNode = rootNode;
    while(*targetNode)
    {
        if((*targetNode)->value == ele)
            return true;

        (*pNode) = (*targetNode);
        if(ele < (*targetNode)->value)
        {
            *targetNode = (*targetNode)->pLeftChild;
        }
        else
        {
            *targetNode = (*targetNode)->pRightChild;
        }
    }
}


#endif /*INCLUDE_AVLTREE_H*/