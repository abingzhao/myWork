#ifndef INCLUDE_BINARY_TREE_H
#define INCLUDE_BINARY_TREE_H

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

/*******************************************************************************
    total node number of Tree
*******************************************************************************/
template <typename T>
int GetNodeNum(T pRoot)  
{  
    if(pRoot == NULL) // 递归出口  
        return 0;  
    return GetNodeNum(pRoot->pLeftChild) + GetNodeNum(pRoot->pRightChild) + 1;  
}

/*******************************************************************************
    Depth
*******************************************************************************/
template <typename T>
int GetDepth(T pRoot)  
{  
    if(pRoot == NULL) // 递归出口  
        return 0;  
    int depthLeft = GetDepth(pRoot->pLeftChild);  
    int depthRight = GetDepth(pRoot->pRightChild);  
    return depthLeft > depthRight ? (depthLeft + 1) : (depthRight + 1);   
}

/*******************************************************************************
    Preorder inorder and post order, recursively implementation
*******************************************************************************/
template <typename T> 
void PreOrderTraverse(T pRoot)  
{  
    if(pRoot == NULL)  
        return;  
    cout << (pRoot->key) << ", ";
    PreOrderTraverse(pRoot->pLeftChild); // 前序遍历左子树  
    PreOrderTraverse(pRoot->pRightChild); // 前序遍历右子树  
} 
template <typename T> 
void InOrderTraverse(T pRoot)  
{  
    if(pRoot == NULL)  
        return;  
    InOrderTraverse(pRoot->pLeftChild); // 前序遍历左子树  
    cout << (pRoot->key) << ", ";
    InOrderTraverse(pRoot->pRightChild); // 前序遍历右子树  
} 
template <typename T> 
void PostOrderTraverse(T pRoot)  
{  
    if(pRoot == NULL)  
        return;  
    PostOrderTraverse(pRoot->pLeftChild); // 前序遍历左子树  
    PostOrderTraverse(pRoot->pRightChild); // 前序遍历右子树  
    cout << (pRoot->key) << ", ";
} 


/*******************************************************************************
    二叉树的非递归前序遍历，前序遍历思想：先让根进栈，只要栈不为空，就可以做弹出操作，
    每次弹出一个结点，记得把它的左右结点都进栈，记得右子树先进栈，这样可以保证右子树在
    栈中总处于左子树的下面。

*******************************************************************************/
template <typename T>
void PreOrderNonrecursive(T rootNode)     //先序遍历的非递归  
{
    if(!rootNode)  
        return ;  
 
    stack<T> s;
    s.push(rootNode);
    while(!s.empty())
    {
        T temp = s.top();
        cout << (temp->key) << ", ";
        s.pop();
        if(temp->pRightChild)
            s.push(temp->pRightChild);
        if(temp->pLeftChild)
            s.push(temp->pLeftChild);
    }
}
template <typename T>
void InOrderNonrecursive(T rootNode)     //先序遍历的非递归  
{  
    if (NULL == rootNode)  
        return;  
  
    stack<T> S;  
    T pS = rootNode;  
  
    while ((pS != NULL) || !S.empty())  
    {  
        while (pS)  
        {  
            S.push(pS);  
            pS = pS->pLeftChild;  
        }  
  
        pS = S.top();  
        cout << pS->key << ", ";  
  
        if (!S.empty())  
        {  
            S.pop();  
            pS = pS->pRightChild;  
        }  
    }  
}  
template <typename T>
void PostOrderNonrecursive(T rootNode)     //先序遍历的非递归  
{
    if(!rootNode)  
        return ;  
 
    stack<T> s;
    s.push(rootNode);
    while(!s.empty())
    {
        T temp = s.top();
        s.pop();
        if(temp->pRightChild)
            s.push(temp->pRightChild);
        if(temp->pLeftChild)
            s.push(temp->pLeftChild);
        cout << (temp->key) << ", ";
    }
}
/*******************************************************************************
    二叉树的广度遍历／层序遍历
*******************************************************************************/
template <typename T>
void LevelTraverse(T pRoot)  
{  
    if(pRoot == NULL)  
        return;  
    queue<T> q;  
    q.push(pRoot);  
    while(!q.empty())  
    {  
        T pNode = q.front();  
        q.pop();  
        cout << (pNode->key) << ", ";
        // Visit(pNode); // 访问节点  
        if(pNode->pLeftChild != NULL)  
            q.push(pNode->pLeftChild);  
        if(pNode->pRightChild != NULL)  
            q.push(pNode->pRightChild);  
    }  
    return;  
}  


/*******************************************************************************
    leaf number of Binary Tree
*******************************************************************************/
template <typename T>
int TreeLeafNodeNum(T rootNode)
{
    if(rootNode == NULL)
        return 0;
    if(rootNode->pLeftChild == NULL &&rootNode->pRightChild == NULL)
        return 1;
    return TreeLeafNodeNum(rootNode->pLeftChild) + TreeLeafNodeNum(rootNode->pRightChild);
}

/*******************************************************************************
    Max Distance between Nodes of Tree
*******************************************************************************/
template <typename T>
int GetMaxDistance(T pRoot, int & maxLeft, int & maxRight)  
{  
    // maxLeft, 左子树中的节点距离根节点的最远距离  
    // maxRight, 右子树中的节点距离根节点的最远距离  
    if(pRoot == NULL)  
    {  
        maxLeft = 0;  
        maxRight = 0;  
        return 0;  
    }  
    int maxLL, maxLR, maxRL, maxRR;  
    int maxDistLeft, maxDistRight;  
    if(pRoot->pLeftChild != NULL)  
    {  
        maxDistLeft = GetMaxDistance(pRoot->pLeftChild, maxLL, maxLR);  
        maxLeft = max(maxLL, maxLR) + 1;  
    }  
    else  
    {  
        maxDistLeft = 0;  
        maxLeft = 0;  
    }  
    if(pRoot->pRightChild != NULL)  
    {  
        maxDistRight = GetMaxDistance(pRoot->pRightChild, maxRL, maxRR);  
        maxRight = max(maxRL, maxRR) + 1;  
    }  
    else  
    {  
        maxDistRight = 0;  
        maxRight = 0;  
    }  
    return max(max(maxDistLeft, maxDistRight), maxLeft+maxRight);  
}  





#endif /*INCLUDE_BINARY_TREE_H*/