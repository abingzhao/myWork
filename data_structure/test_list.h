#include <cstdlib>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <ctime>
#include <sstream>
/******************************************************************************/
typedef struct 
{
    int *element;
    unsigned list_size;
} l_list;
class linear_list
{
public:
    typedef boost::shared_ptr<linear_list> sptr;
    static sptr make(unsigned max_len) ;
    linear_list(unsigned max_len = 10);
    ~linear_list();
    
    l_list* get_l_list() const{return m_ll;}
    bool list_empty();
    void list_clear();
    bool get_element(unsigned idx, int &ele);
    bool insert_element(unsigned idx, int ele);
    bool delete_element(unsigned idx);
    unsigned find_element(int ele);
    unsigned length(){return m_ll->list_size;}
    void show_list_ele();
private:
    l_list* m_ll;
    unsigned max_len;
};
/******************************************************************************/
typedef struct node
{
    int element;
    struct node *next;
}node;
typedef struct node sl_node;
class single_list
{
public:
    typedef boost::shared_ptr<single_list> sptr;
    static sptr make();
    single_list();
    ~single_list();
    
    sl_node* get_header(){ return m_header;}
    void list_init();
    void list_clear();
    bool list_empty();
    void destroy_list();
    bool get_element(int loc, int &ele);
    bool insert_element(int loc, int ele);
    bool delete_element(int loc);
    unsigned find_element(int ele);
    unsigned length();
    void show_list_ele();
    void create_list(int len);
    void create_list_tail(int len);

private:
    sl_node *m_header;
};
/******************************************************************************/
typedef struct node cl_node;
class circular_list
{
public:
    typedef boost::shared_ptr<circular_list> sptr;
    static sptr make(){ return sptr(new circular_list());}
    circular_list();
    ~circular_list();
    void list_init();
    void list_clear();
    bool list_empty();
    bool get_element(int loc, int &ele);
    bool insert_element(int loc, int ele);
    bool delete_element(int loc);
    void show_list_ele();

private:
    cl_node *m_header;
};
/******************************************************************************/
/******************************************************************************/
