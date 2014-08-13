#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <complex>
#include <cstring>
#include <fftw3.h>
using namespace std;
typedef complex<float> gr_complex;

class buffer
{
public:
    buffer(size_t length = 128);
    ~buffer(){free(d_buffer);}
    size_t read_space(void);
    size_t write_space(void);
    void write_to_buffer(const gr_complex *data,const size_t length);
    void read_from_buffer(gr_complex *data,const size_t length);
    void update_r_ptr(size_t size);
    gr_complex &operator[](size_t position){return d_buffer[(d_r_ptr+position)%d_buffer_size];}
// private:
    size_t d_buffer_size;
    size_t d_r_ptr;
    size_t d_w_ptr;
    gr_complex *d_buffer;
};
buffer::buffer(size_t length)
{
    d_buffer_size = length;
    d_r_ptr  = 0;
    d_w_ptr  = 0;
    d_buffer = (gr_complex*)malloc(sizeof(gr_complex)*d_buffer_size);
}
size_t buffer::read_space(void)
{
    if((d_r_ptr < d_w_ptr) && (d_w_ptr - d_r_ptr > 2))
    {
        return d_w_ptr - d_r_ptr - 2;
    }
    if((d_r_ptr > d_w_ptr) && (d_buffer_size + d_w_ptr - d_r_ptr > 2) )
    {
        return d_buffer_size + d_w_ptr - d_r_ptr - 2;
    }
    return 0;
}
//==========================================================================
size_t buffer::write_space(void)
{
    if( (d_r_ptr <= d_w_ptr) && (d_buffer_size + d_r_ptr -d_w_ptr > 2))
        return d_buffer_size + d_r_ptr -d_w_ptr - 2;
    if((d_r_ptr > d_w_ptr) && (d_r_ptr - d_w_ptr > 2))
        return d_r_ptr - d_w_ptr - 2;
    return 0;
}

void 
buffer::write_to_buffer(const gr_complex *in,const size_t length)
{
    if (d_w_ptr + length <= d_buffer_size )
    {
        memcpy(d_buffer+d_w_ptr,in,sizeof(gr_complex)*length);
        d_w_ptr = (d_w_ptr + length) % d_buffer_size;
    }
    else
    {
        size_t len = d_buffer_size - d_w_ptr;
        memcpy(d_buffer+d_w_ptr,in,sizeof(gr_complex)*len);
        d_w_ptr = (d_w_ptr + len) % d_buffer_size;
        memcpy(d_buffer+d_w_ptr,in+len,sizeof(gr_complex)*(length-len));
        d_w_ptr = (d_w_ptr + length-len) % d_buffer_size;
    }
}
void 
buffer::read_from_buffer(gr_complex *out,const size_t length)
{
    //读取缓存过程
    if (d_r_ptr + length  <= d_buffer_size )
    {
        //当前读指针位置到缓存结束位置的可读空间大于等于本次需要读取的长度，可以一次读取
        memcpy(out,d_buffer+d_r_ptr,sizeof(gr_complex)*(length));
    }
    else 
    {
        //当前读指针位置到缓存结束位置的可读空间小于于本次需要读取的长度，需要分为两次进行读取
        int len = d_buffer_size - d_r_ptr;
        memcpy(out,d_buffer+d_r_ptr,sizeof(gr_complex)*len);
        memcpy(out+len,d_buffer,sizeof(gr_complex)*(length-len));
    }
}
void 
buffer::update_r_ptr(size_t len)
{
    d_r_ptr = (d_r_ptr + len) % d_buffer_size;
}


int main()
{
    buffer* d_buf = new buffer(10);
    cout<<"write_space()="<<d_buf->write_space()<<";;read_space()="<<d_buf->read_space()<<";d_w_ptr="<<d_buf->d_w_ptr<<";d_r_ptr="<<d_buf->d_r_ptr<<"\n";
    std::vector<gr_complex> v(8,0);
    for (int i = 0; i < v.size(); ++i)
        v[i]=i+1;
    d_buf->write_to_buffer(&v[0],v.size());
    cout<<"After write 8 elements,write_space()="<<d_buf->write_space()<<";;read_space()="<<d_buf->read_space()<<";d_w_ptr="<<d_buf->d_w_ptr<<";d_r_ptr="<<d_buf->d_r_ptr<<"\n";
    // cout<<(*d_buf)[5]<<"\n";
    std::vector<gr_complex> v1(6,0);
    d_buf->read_from_buffer(&v1[0],v1.size());
    cout<<"After read 6 elements,write_space()="<<d_buf->write_space()<<";;read_space()="<<d_buf->read_space()<<";d_w_ptr="<<d_buf->d_w_ptr<<";d_r_ptr="<<d_buf->d_r_ptr<<"\n";
    d_buf->update_r_ptr(v1.size());
    cout<<"After update_r_ptr(6),write_space()="<<d_buf->write_space()<<";;read_space()="<<d_buf->read_space()<<";d_w_ptr="<<d_buf->d_w_ptr<<";d_r_ptr="<<d_buf->d_r_ptr<<"\n";
    std::vector<gr_complex> v2(4,0);
    for (int i = 0; i < v2.size(); ++i)
        v2[i]=gr_complex(0,i+1);
    d_buf->write_to_buffer(&v2[0],v2.size());
    cout<<"After write 4 elements,write_space()="<<d_buf->write_space()<<";;read_space()="<<d_buf->read_space()<<";d_w_ptr="<<d_buf->d_w_ptr<<";d_r_ptr="<<d_buf->d_r_ptr<<"\n";
    (*d_buf)[4]=gr_complex(1,0);
    cout<<(*d_buf)[4]<<"\n";
    delete d_buf;
    cout<<"Have Done!\n";
    return 0;
}