/*******************************************************************************
    File: sList.h

    Description: Implement unique single list in template and its relative 
                 operation. 

    Revision History
    ----------    ---------    --------------------------------------------
    2014-08-08    abing0513    Add The delear of sListNode and class sList.
                               Implement Followed Function:
                                    ListEmpty() 
                                    ListLength()
                                    PushBack()
                                    PushFront()
                                    PopBack()
                                    PopFront()
                                    DestroyList()
                                    PrintAllEle()
    2014-08-09    abing0513    Add The Explanation of Node Counter and Node 
                               Position. Implement Followed Function:
                                    InsertAfter()
                                    InsertBefore()
                                    RemoveAt()
                                    RemoveHead()
                                    RemoveTail()
                                    GetHead()
                                    GetEleAt()
*******************************************************************************/


#ifndef INCLUDE_SLIST_HPP
#define INCLUDE_SLIST_HPP
/*******************************************************************************
    INLCUDES
*******************************************************************************/
#include <iostream>
#include <stdexcept>

/*******************************************************************************
    DEFINES
*******************************************************************************/
// Invalid position of the existed list
const size_t INVALID_POS = static_cast<size_t>(-1);

/*******************************************************************************
    LIST NODE AND CLASS DECLEAR
*******************************************************************************/
template<typename T>
struct sListNode
{
    T data;
    sListNode<T> *next;
    sListNode(const T _data = 0,sListNode* sln = NULL)
    : data(_data),next(sln)
    {}
    T& operator ()(void)
    {
        return data;
    }
};
/**
 * @brief List Implemention
 */
template<typename T>
class sList
{
private:

    //! NOTE: The pHead is The Real first Node of the list, Not Empty Node
    sListNode<T> *pHead;

    //! Counter The Node ,make it efficient to return the size of he list;
    size_t        NodeCounter;
public:
    sList();
    sList(const T& _data);
    ~sList();

    /**
     * @brief Return The Length of List
     */
    size_t ListLength(void) const;

    /**
     * @brief Return True if List is Empty,otherwise return false
     */
    bool   ListEmpty(void) const;

    /**
     * @brief Insert Ele at the Back of the List; (Append Tail)
     */
    void   PushBack(const T&  _data);

    /**
     * @brief Insert Ele at The beginning of the List
     */
    void   PushFront(const T&  _data); 

    /**
     * @brief Return ele in Head, And delete Head
     */
    T      PopFront();

    /**
     * @brief Return ele in Tail, And delete Tail
     */
    T      PopBack();

    /**
     * @brief Insert @param _data After The position @param pos.
     *        return true is Sucessful, otherwise return false
     */
    bool   InsertAfter(const size_t pos, const T _data);

    /**
     * @brief Insert @param _data Before The position @param pos.
     *        return true is Sucessful, otherwise return false
     */
    bool   InsertBefore(const size_t pos, const T _data);

    /**
     * @brief Remove the Node at @param pos in the List
     */
    void   RemoveAt(const size_t pos);

    /**
     * @brief Remove The Head Node of the List
     */
    void   RemoveHead();

    /**
     * @brief Remove The Tail Node of the List
     */
    void   RemoveTail();

    void   ListClear()
    {
        DestroyList();
    }
    T&     GetHead();
    T      GetHead()const;
    T&     GetEleAt(const size_t pos);      
    T      GetEleAt(const size_t pos)const;
    const T& operator[](size_t pos)
    {
        return GetEleAt(pos);
    }
    /**
     * @brief Change The ele in @param pos Node to _data
     */
    void   SetEleAt(const size_t pos, const T &_data);

    /**
     * @brief Return The first position _data  in List,
     *        If Not Found return INVALID_POS (i.e. -1)
     */
    size_t FindEle(const T &_data) const;
    void   PrintAllEle() const;

private:
    /**
     * @brief Destroy The List
     */
    void   DestroyList();
};


/*******************************************************************************
    LIST POSITION AND COUNTER EXPLANATION
    
    Node Counter:    1            2            3            4
    Node pos :       0            1            2            3
                  --------     --------     --------     --------
                 |data|*p-|-->|data|*p-|-->|data|*p-|-->|data|*p-|-->
                  --------     --------     --------     --------
                   pHead
                 Head Node
*******************************************************************************/



/*******************************************************************************
    CLASS AND FUNCTION DEFINES
*******************************************************************************/

//------------------------------------------------------------------------------
template<typename T>
sList<T>::sList()
:  pHead(NULL)
 , NodeCounter(0)
{}
//------------------------------------------------------------------------------
template<typename T>
sList<T>::sList(const T& _data)
:  pHead(NULL)
 , NodeCounter(0)
{
    pHead = new sListNode<T>(_data);
    ++NodeCounter;
}
//------------------------------------------------------------------------------
template<typename T>
sList<T>::~sList()
{
    if(NULL != pHead)
        DestroyList();
}
//------------------------------------------------------------------------------
template<typename T>
size_t sList<T>::ListLength() const
{
    return NodeCounter;
}
//------------------------------------------------------------------------------
template<typename T>
bool sList<T>::ListEmpty() const
{
    return 0 == NodeCounter;
}
//------------------------------------------------------------------------------
template<typename T>
void sList<T>::PushBack(const T& _data)
{
    if( NULL == pHead)
    {
        pHead = new sListNode<T>(_data);
        ++NodeCounter;
        return ;
    }
    else
    {
        sListNode<T> *p = pHead;
        while(NULL != p->next)
        {
            p = p->next;
        } 
        sListNode<T> *q = new sListNode<T>(_data);
        p->next = q;
        ++NodeCounter;
        return ;
    }
}
//------------------------------------------------------------------------------
template<typename T>
void sList<T>::PushFront(const T& _data)
{
    sListNode<T> *p = new sListNode<T>(_data);
    p->next = pHead;
    pHead = p;
    ++NodeCounter;
}
//------------------------------------------------------------------------------
template<typename T>
T sList<T>::PopFront()
{
    if (NULL == pHead)
    {
        throw std::runtime_error("The List Is EMPTY!!");
    }
    sListNode<T> *p = pHead;
    pHead = pHead->next;
    --NodeCounter;
    T _data = p->data;
    delete p;
    return _data;
}
//------------------------------------------------------------------------------
template<typename T>
T sList<T>::PopBack()
{
    if (NULL == pHead)
    {
        throw std::runtime_error("The List Is EMPTY!!");
    }
    else if (NULL == pHead)
    {
        return PopFront();
    }
    else
    {
        sListNode<T> *p = pHead;
        while(NULL != p->next->next)
        {
            p = p->next;
        }
        sListNode<T> *q = p->next;
        p->next = NULL;
        --NodeCounter;
        T _data = q->data;
        delete q;
        return _data;
    }
}
//------------------------------------------------------------------------------
template<typename T>
bool sList<T>::InsertAfter(const size_t pos, const T _data)
{
    if(pos >= NodeCounter)
        throw std::runtime_error("The Pos In InsertAfter is Out of Range!");

    sListNode<T> *pTmpNode = pHead;
    size_t position = pos;
    while(position--)
        pTmpNode = pTmpNode->next;
    sListNode<T> *pNewNode = new sListNode<T>(_data);
    pNewNode->next = pTmpNode->next;
    pTmpNode->next = pNewNode;
    ++NodeCounter; 
    return true;
}
//------------------------------------------------------------------------------
template<typename T>
bool sList<T>::InsertBefore(const size_t pos, const T _data)
{
    if(pos > NodeCounter)
        throw std::runtime_error("The Pos In InsertBefore is Out of Range!");

    if(0 == pos)
    {
        PushFront(_data);
        return true;
    }
    if(pos == NodeCounter)
    {
        PushBack(_data);
        return true;
    }
    InsertAfter(pos-1,_data);
}
//------------------------------------------------------------------------------
template<typename T>
void sList<T>::RemoveAt(const size_t pos)
{
    // Out of Range (see LIST POSITION AND COUNTER EXPLANATION)
    if( pos >= NodeCounter || pos < 0 )
        throw std::runtime_error("When RemoveAt(pos), The pos is out of range!");
    if(0 == pos)
    {
        RemoveHead();
        return ;
    }
    if(pos == NodeCounter-1)
    {
        RemoveTail();
        return ;
    }
    sListNode<T> *pTmpNode = pHead;
    size_t position = pos;
    while(--position)
    {
        pTmpNode = pTmpNode->next;
    }
    sListNode<T> *qTmpNode = pTmpNode->next;
    pTmpNode->next = qTmpNode->next;
    --NodeCounter;
    delete qTmpNode;
}
//------------------------------------------------------------------------------
template<typename T>
void sList<T>::RemoveHead()
{
    if(NULL == pHead)
        throw std::runtime_error("When RemoveHead, The List Is Empty");
    sListNode<T> *pTmpNode = pHead;
    pHead = pHead->next;
    --NodeCounter;    
    delete pTmpNode;
}
//------------------------------------------------------------------------------
template<typename T>
void sList<T>::RemoveTail()
{
    if(NULL == pHead)
        throw std::runtime_error("When RemoveTail, The List Is Empty");
    if(1 == NodeCounter)
        RemoveHead();
    
    sListNode<T> *pTmpNode1 = pHead;
    sListNode<T> *pTmpNode2 = pHead;
    while(NULL != pTmpNode1->next)
    {
        pTmpNode2 = pTmpNode1;
        pTmpNode1 = pTmpNode1->next;
    }    
    pTmpNode2->next = NULL;
    --NodeCounter;    
    delete pTmpNode1;
}
//------------------------------------------------------------------------------
template<typename T>
void sList<T>::DestroyList()
{
    while(NULL != pHead)
    {
        sListNode<T> * p = pHead->next;
        delete  pHead;
        pHead = p;
    } 
    NodeCounter = 0;
}
//------------------------------------------------------------------------------
template<typename T>
T& sList<T>::GetHead()
{  
    if(NULL != pHead)
        return pHead->data;
    throw std::runtime_error("GetHead On an EMPTY List!");
}
//------------------------------------------------------------------------------
template<typename T>
T sList<T>::GetHead() const
{  
    if(NULL != pHead)
        return pHead->data;
    throw std::runtime_error("GetHead On an EMPTY List!");
}
//------------------------------------------------------------------------------
template<typename T>
T& sList<T>::GetEleAt(const size_t pos)
{
    if( pos >= NodeCounter || pos < 0 )
        throw std::runtime_error("When GetEleAt(pos), The pos is out of range!");
    if(pos == 0)
        return GetHead();
    size_t position = pos;
    sListNode<T> *pTmpNode = pHead;
    while(position--) 
        pTmpNode = pTmpNode->next;
    return pTmpNode->data;
}
//------------------------------------------------------------------------------
template<typename T>
T sList<T>::GetEleAt(const size_t pos) const
{
    if( pos >= NodeCounter || pos < 0 )
        throw std::runtime_error("When GetEleAt(pos), The pos is out of range!");
    if(pos == 0)
        return GetHead();
    size_t position = pos;
    sListNode<T> *pTmpNode = pHead;
    while(position--) 
        pTmpNode = pTmpNode->next;
    return pTmpNode->data;
}
//------------------------------------------------------------------------------
template<typename T>
void sList<T>::SetEleAt(const size_t pos, const T &_data)
{
    if( pos >= NodeCounter || pos < 0 )
        throw std::runtime_error("When SetEleAt(pos), The pos is out of range!");
    sListNode<T> *pTmpNode = pHead;
    size_t position = pos;
    while(position--)
    {
        pTmpNode = pTmpNode->next;
    }
    pTmpNode->data = _data;
}
//------------------------------------------------------------------------------
template<typename T>
size_t sList<T>::FindEle(const T &_data) const
{
    sListNode<T> *pTmpNode = pHead;
    size_t position = 0;
    while(pTmpNode)
    {
        if(_data == pTmpNode->data)
            return position;
        pTmpNode = pTmpNode->next;
        ++position;
    }
    return INVALID_POS;
}
//------------------------------------------------------------------------------
template<typename T>
void sList<T>::PrintAllEle() const
{
    sListNode<T> *p = pHead;
    size_t i =0;
    while(NULL != p)
    {
        std::cout<< "The " <<i<< "th Ele :"<<p->data<<std::endl;
        ++i;
        p = p->next;
    }
}
//
#endif /*INCLUDE_SLIST_HPP*/