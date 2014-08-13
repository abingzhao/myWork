#include "test_list.h"
#include <stdexcept>
#include <iostream>
#include <cstring>
/*============================================================================*/
linear_list::sptr linear_list::make(unsigned max_len)
{
    return linear_list::sptr(new linear_list(max_len));
}
//----------------------------------------------------
linear_list::linear_list(unsigned max_length)
: max_len(max_length)
{
    m_ll = new l_list();
    m_ll->element = (int*)malloc(sizeof(int)*max_len);
    memset(m_ll->element,0,sizeof(int)*max_len);
    m_ll->list_size = 0;
}
//----------------------------------------------------
linear_list::~linear_list()
{
    std::cout<<__func__<<std::endl;
    if(NULL != m_ll->element)
        free(m_ll->element);
    if(NULL != m_ll)
        delete m_ll;
}
//----------------------------------------------------
bool linear_list::list_empty()
{
    if(0 == m_ll->list_size && NULL != m_ll->element)
        return true;
    else if(0 < m_ll->list_size && NULL != m_ll->element)
        return false;
    else
        throw std::runtime_error("Linear list is invalid! Please Checkout!");
}
//----------------------------------------------------
void linear_list::list_clear()
{
    if(0 == m_ll->list_size || NULL == m_ll->element)
        throw std::runtime_error("Linear list is invalid! Please Checkout!");
    else
        m_ll->list_size = 0;
}
//----------------------------------------------------
bool linear_list::get_element(unsigned idx, int &ele)
{
    if( NULL == m_ll->element )
        throw std::runtime_error("Linear list is invalid! Please Checkout!");
    if( 0 == m_ll->list_size )
        throw std::range_error("Linear list is empty!");
    if( idx >= m_ll->list_size )
        return false;
    ele = m_ll->element[idx];
    return true;
}
//----------------------------------------------------
bool linear_list::insert_element(unsigned idx, int ele)
{
    if( NULL == m_ll->element )
        throw std::runtime_error("Linear list is invalid! Please Checkout!");
    if(max_len == m_ll->list_size)
    {
        std::cout<<"The list is FULL,cannot insert!"<<std::endl;//log
        return false;
    }
    if (idx > m_ll->list_size)
    {
        std::cout<<"The request insert location is outof the current list size"<<std::endl;
        return false;
    }
    unsigned i = m_ll->list_size;
    while(i>idx && i>0)
    {
        m_ll->element[i] = m_ll->element[i-1];
        i--;
    }
    m_ll->element[i] = ele;
    m_ll->list_size++;
    return true; 

}
//----------------------------------------------------
bool linear_list::delete_element(unsigned idx)
{
    if( NULL == m_ll->element )
        throw std::runtime_error("Linear list is invalid! Please Checkout!");
    if(0 == m_ll->list_size)
    {
        std::cout<<"The list is EMPTY,cannot insert!"<<std::endl;//log
        return false;
    }
    if (idx >= m_ll->list_size)
    {
        std::cout<<"The request delete location is outof the current list size"<<std::endl;
        return false;
    }
    while(idx < m_ll->list_size-1)
    {
        m_ll->element[idx] = m_ll->element[idx+1];
        idx++;
    }
    m_ll->list_size--;
    return true;
}
//----------------------------------------------------
unsigned linear_list::find_element(int ele)
{
    if( NULL == m_ll->element )
        throw std::runtime_error("Linear list is invalid! Please Checkout!");
    if(0 == m_ll->list_size)
    {
        std::cout<<"The list is EMPTY,cannot find!"<<std::endl;//log
        return -1;//MAX_UNSIGNED_INT 
    }
    unsigned len = m_ll->list_size;
    for (unsigned i = 0; i < len; ++i)
    {
        if(m_ll->element[i] == ele)
            return i;
    }
}
//----------------------------------------------------
void linear_list::show_list_ele()
{
    if( NULL == m_ll->element )
        throw std::runtime_error("Linear list is invalid! Please Checkout!");
    if(0 == m_ll->list_size)
    {
        std::cout<<"The list is empty!"<<std::endl;
        return;
    }
    unsigned len = m_ll->list_size;
    std::cout<<"There is "<<len<<" elements:\n";
    for (unsigned i = 0; i < len; ++i)
    {
        std::cout<<"\t"<<(m_ll->element[i]);
        if(i%10 == 9)
            std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
/*============================================================================*/
single_list::sptr single_list::make()
{
    return sptr(new single_list());
}
//----------------------------------------------------
single_list::single_list():m_header(NULL){}
//----------------------------------------------------
single_list::~single_list()
{
    if(NULL != m_header)
    {
        if(NULL != m_header->next)
            list_clear();
        if(NULL != m_header)
            delete m_header;
    }
    std::cout<<"In "<<__func__<<" ,completely destruct!"<<std::endl;
}
//----------------------------------------------------
void single_list::list_init()
{
    if(NULL == m_header)
    {
        m_header = new sl_node();
        m_header->next    = NULL;
        m_header->element = 0;//Header Node ,no data
    }
    else if(NULL != m_header->next)
        list_clear();
    else
        return;
}
//----------------------------------------------------
void single_list::list_clear()
{
    if(NULL == m_header)
        return;
    else if(NULL == m_header->next)
        return;
    else
    {
        while(NULL != m_header->next)
        {
            sl_node * s = m_header->next;
            delete m_header;
            m_header = s;
        }
    }
}
//----------------------------------------------------
bool single_list::list_empty()
{
    if(NULL == m_header)
        throw std::runtime_error("Invalid List! Please Checkout!");
    if(NULL == m_header->next)
        return true;
    else
        return false;
}
//----------------------------------------------------
void single_list::destroy_list()
{
    if(NULL == m_header)
        return;
    else
    {
        list_clear();
        delete m_header;
        m_header = NULL;
    }
}
//----------------------------------------------------
bool single_list::get_element(int loc, int &ele)
{
    if(NULL == m_header)
        throw std::runtime_error("Invalid List! Please Checkout!");
    if(NULL == m_header->next)
        throw std::range_error("Read on an empty list!");
    sl_node* p = m_header;
    int j = 1;
    while(j<loc && NULL!=p)
    {
        p = p->next;
        ++j;
    }
    if(j==loc)
        ele = p->element;
    else
        std::cerr<<"Read index is beyond list!"<<std::endl;
}
//----------------------------------------------------
bool single_list::insert_element(int loc, int ele)
{
    if(NULL == m_header)
        throw std::runtime_error("Invalid List! Please Checkout!");
    sl_node* p = m_header;
    int j = 1;
    while( p && j<loc)
    {
        p = p->next;
        ++j;
    }
    if(!p || j>loc)
        return false;
    sl_node * s = new sl_node();
    s->element = ele;
    s->next = p->next;
    p->next = s;
    return true;
}
//----------------------------------------------------
bool single_list::delete_element(int loc)
{
    if(NULL == m_header)
        throw std::runtime_error("Invalid List! Please Checkout!");
    sl_node* p = m_header;
    int j = 1;
    while(NULL!=p->next && j<loc)
    {
        ++j;
        p = p->next;
    }
    if(NULL==p->next || j>loc)
        return false;
    sl_node* s = p->next;
    p->next = s->next;
    delete s;
    return true;
}
//----------------------------------------------------
unsigned single_list::find_element(int ele)
{
    if(NULL == m_header)
        throw std::runtime_error("Invalid List! Please Checkout!");
    sl_node* p = m_header->next;
    unsigned j = 0;
    while(p != NULL)
    {
        if(ele == p->element)
            return j;
        ++j;
        p = p->next;
    }
    std::cerr<<"Connot Fine "<<ele<<" in List"<<std::endl;
}
//----------------------------------------------------
unsigned single_list::length()
{
    if(NULL == m_header)
        throw std::runtime_error("Invalid List! Please Checkout!");
    if(NULL == m_header->next)
        std::cout<<"The List is EMPTY!"<<std::endl;
    sl_node* p = m_header;
    unsigned j = 0;
    while(p != NULL)
    {
        ++j;
        p = p->next;
    }
    return j;
}
//----------------------------------------------------
void single_list::show_list_ele()
{
    if(NULL == m_header)
        throw std::runtime_error("Invalid List! Please Checkout!");
    if(NULL == m_header->next)
        std::cout<<"The List is EMPTY!"<<std::endl;
    sl_node* p = m_header->next;
    int j =0;
    while(p != NULL)
    {
        std::cout<<"\t"<<(p->element);
        p=p->next;
        ++j;
        if(j%10 == 9)
            std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
//----------------------------------------------------
void single_list::create_list(int len)
{
    srand(time(NULL));
    list_init();
    if(m_header == NULL )
        throw std::runtime_error("Invalid List! Please Checkout!");
    sl_node * p = m_header;
    for (int i = 1; i < len; ++i)
    {
        sl_node *s = new sl_node();
        s->element = i + 1;
        s->next = p->next;
        p->next = s;
    }
}
//----------------------------------------------------
void single_list::create_list_tail(int len)
{
    srand(time(NULL));
    list_init();
    if(m_header == NULL )
        throw std::runtime_error("Invalid List! Please Checkout!");
    sl_node * p = m_header;
    for (int i = 1; i < len; ++i)
    {
        sl_node *s = new sl_node();
        s->element = i + 1;
        p->next = s;
        p = s;
    }
}
/*============================================================================*/

circular_list::circular_list():m_header(NULL){}
//----------------------------------------------------
circular_list::~circular_list()
{

}
//----------------------------------------------------
void circular_list::list_init()
{
    if(NULL == m_header)
    {
        m_header = new cl_node();
        m_header->element = 0;
        m_header->next    = m_header;
    }
    else
        list_clear();
}
//----------------------------------------------------
void circular_list::list_clear()
{
    if(NULL == m_header)
    {
        std::stringstream ss;
        ss<<"In "<<__func__<<" Line:"<<__LINE__
            <<" Invalid list, header node is NULL\n";
        throw std::runtime_error(ss.str());
    }
    cl_node * p = m_header;
    while(p->next != m_header)
    {
        cl_node * s = p->next;
        p->next = s->next;
        delete s;
    }
}
//----------------------------------------------------
bool circular_list::list_empty()
{
    if(NULL == m_header)
    {
        std::stringstream ss;
        ss<<"In "<<__func__<<" Line:"<<__LINE__
            <<" Invalid list, header node is NULL\n";
        throw std::runtime_error(ss.str());
    }
    return (m_header->next == m_header);
}
//----------------------------------------------------
bool circular_list::get_element(int loc, int &ele)
{
    if(NULL == m_header)
        throw std::runtime_error("Invalid List! Please Checkout!");
    if(m_header == m_header->next)
        throw std::range_error("Read on an empty list!");
    cl_node* p = m_header;
    int j = 1;
    while(j<loc && m_header!=p)
    {
        p = p->next;
        ++j;
    }
    if(j==loc)
        ele = p->element;
    else
        std::cerr<<"Read index is beyond list!"<<std::endl;
}
//----------------------------------------------------
bool circular_list::insert_element(int loc, int ele)
{
    if(NULL == m_header)
        throw std::runtime_error("Invalid List! Please Checkout!");
    // if(m_header == m_header->next)
    //     throw std::range_error("Insert on an empty list!");
    cl_node* p = m_header;
    int j =1;
    while(j<loc && p->next != m_header)
    {
        p = p->next;
        ++j;
    }
    if(j==loc)
    {
        cl_node* s = new cl_node();
        s->element = ele;
        s->next = p->next;
        p->next = s;
        return true;
    }
    else
    {
        std::cerr<<"Insert index is beyond list!"<<std::endl;
    }
    return false;
}
//----------------------------------------------------
bool circular_list::delete_element(int loc)
{
    if(NULL == m_header)
        throw std::runtime_error("Invalid List! Please Checkout!");
    if(m_header == m_header->next)
        throw std::range_error("Delete on an empty list!");
    cl_node* p = m_header;
    int j = 1;
    while(j<loc && p->next!=m_header)
    {
        p = p->next;
        ++j;
    }
    if(j==loc)
    {
        sl_node* s = p->next;
        p->next = s->next;
        delete s;
        return true;
    }
    else
    {
        std::cerr<<"Delete index is beyond list!"<<std::endl;
    }
    return false;
}
//----------------------------------------------------
void circular_list::show_list_ele()
{
    if(NULL == m_header)
        throw std::runtime_error("Invalid List! Please Checkout!");
    if(m_header == m_header->next)
        throw std::range_error("Empty List!");
    cl_node* p = m_header->next;
    int j = 0;
    while(p != m_header)
    {
        std::cout<<"\t"<<p->element;
        p = p->next;
        ++j;
        if(j%10 == 9)
            std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
/*============================================================================*/
int main()
{
    // unsigned max_len = 100;
    // linear_list::sptr ll = linear_list::make(max_len);
    // for (int i = 0; i < 5; ++i)
    // {
    //     ll->insert_element(i,i+1);
    // }
    // ll->show_list_ele();
    // ll->delete_element(unsigned(2));
    // ll->show_list_ele();
    // std::cout<<(ll->find_element(5) ? "Find 5":"Not find 5")<<std::endl;
    // ll->list_clear();
    // ll->show_list_ele();
    // for (unsigned i = 0; i < 3; ++i)
    // {
    //     ll->insert_element((ll->get_l_list())->list_size,ll->get_l_list()->list_size);
    //     ll->show_list_ele();
        
    // }
    //---------------------------
    // single_list::sptr sl = single_list::make();
    
    // try
    // {
    //     sl->list_init();
    //     for (int i = 1; i < 10; ++i)
    //     {
    //         sl->insert_element(i,i+1);
    //     }
    //     std::cout<<"There is "<<(sl->length())<<" elements in list:"<<std::endl;
    //     sl->show_list_ele();
    //     sl->delete_element(5);
    //     sl->delete_element(4);
    //     sl->delete_element(3);
    //     std::cout<<"There is "<<(sl->length())<<" elements in list:"<<std::endl;
    //     sl->show_list_ele();
    //     sl->list_clear();
    //     std::cout<<"There is "<<(sl->length())<<" elements in list:"<<std::endl;
    //     sl->show_list_ele();
    //     // sl->destroy_list();
    //     // std::cout<<"There is "<<(sl->length())<<" elements in list:"<<std::endl;
    //     // sl->show_list_ele();

    //     sl->create_list(10);
    //     std::cout<<"There is "<<(sl->length())<<" elements in list:"<<std::endl;
    //     sl->show_list_ele();

    //     sl->create_list_tail(10);
    //     std::cout<<"There is "<<(sl->length())<<" elements in list:"<<std::endl;
    //     sl->show_list_ele();
    //     int a =0;
    //     sl->get_element(1,a);
    //     std::cout<<(a)<<std::endl;
    // }
    // catch(std::runtime_error &re)
    // {
    //     std::cout<<re.what()<<std::endl;
    // }
    
    circular_list::sptr cl = circular_list::make();
    cl->list_init();
    try
    {
        cl->insert_element(1,5);
        cl->show_list_ele();
        for (int i = 0; i < 5; ++i)
        {
            cl->insert_element(i+1,i);
        }
        cl->show_list_ele();
        cl->delete_element(3);
        cl->delete_element(3);
        cl->show_list_ele();
    }
    catch(std::runtime_error &re)
    {
        std::cout<<re.what()<<std::endl;
    }
    std::cout<<"Have Done!"<<std::endl;
    return 0;
}