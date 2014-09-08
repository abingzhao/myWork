/**
 * 问题描述：
 * n个人围成一个环，然后给从某个人开始顺时针从1开始报数，每报到m时，将此人出环杀死(当然不杀死
 * 也可以啊)，然后从下一个人继续从1报数，直到最后只剩下一个人，求这个唯一剩下的存活的人是谁？
 *
 *
 * 解法一(模拟游戏过程)：
 *     思想：建立一个有N个元素的循环链表，然后从链表头开始遍历并记数，如果计数i==m(i初始为1)
 *     踢出元素，继续循环，当当前元素与下一元素相同时退出循环。
 */

#include <iostream>

namespace josephus_pro{
    typedef struct ring_node
    {
        int pos;
        ring_node* next;
    }ring_node;

    void destroy_josephus_ring(ring_node* header)
    {
        while (NULL != header)
        {
            ring_node* p=header;
            header = header->next;
            delete p; 
        }
        header = NULL;
    }

    ring_node* create_josephus_ring(int n)
    {
        ring_node* header = NULL;
        ring_node* p_cur  = NULL;
        ring_node* p_prev = NULL;
        
        header = new ring_node();
        header->pos  = 0;
        header->next = header;
        p_prev       = header;
        int i = 1;
        while(i<n)
        {
            p_cur = new ring_node();
            p_cur->pos = i;
            p_prev->next = p_cur;
            p_cur->next  = header;
            p_prev = p_cur;
            ++i;
        }
        std::cout<<std::endl;
        return header;
    }
    void print_josephus_ring(ring_node* header)
    {
        if(NULL == header)
        {
            std::cout<<"Epmty Ring\n"<<std::endl;
            return ;
        }
        std::cout<<"\t"<<(header->pos);
        ring_node* p_cur = header->next;
        while(p_cur != header)
        {
            std::cout<<"\t"<<(p_cur->pos);
            p_cur = p_cur->next;
        }
        std::cout<<std::endl;
    }
    void kick_out_ele(ring_node* header, int m)
    {
        ring_node* p_prev = header;
        ring_node* p_cur  = header;
        int i = 1;
        while(p_cur != NULL)
        {
            if( i == m)
            {
                std::cout<<"chuju:"<<(p_cur->pos)<<std::endl;
                p_prev->next = p_cur->next;
                delete p_cur;
                p_cur = p_prev->next;
                i = 1;
            }
            p_prev = p_cur;
            p_cur = p_prev->next;
            if(p_prev==p_cur)
            {
                std::cout<<"WINNER:"<<(p_cur->pos)<<std::endl;
                delete p_cur;
                return;
            }
            ++i;
        }
    }
}//end josephus_pro

int main(int argc, char const *argv[])
{
    int n = 80;
    int m = 55;
    josephus_pro::ring_node* header=
        josephus_pro::create_josephus_ring(n);
    josephus_pro::print_josephus_ring(header);
    josephus_pro::kick_out_ele(header,m);

    int s = 0;
    for (int i = 1; i <= n; i++)
    {
        s = (s + m) % i;
    }
    std::cout<<(s)<<std::endl;
    std::cout<<"Have Done!"<<std::endl;
    return 0;
}