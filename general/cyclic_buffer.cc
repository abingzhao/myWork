#include "cyclic_buffer.h"
// namespace cyclicbuffer
// {
    //==========================================================================
    template <typename T>
    cyclic_buffer<T>::cyclic_buffer(size_t buffer_size)
    :  d_buffer_size(buffer_size)
     , d_r_ptr(0)
     , d_w_ptr(0)
    {
        if(d_buffer_size < 0)
        {
            boost::format fmt("%s:%d:%s:缓存空间大小设置错误,自动设为默认值应为76800！");
            std::stringstream ss;
            ss << fmt % __FILE__ % __LINE__ % __func__;
            d_buffer_size = 76800;
        }
        d_buffer = (T*)malloc(sizeof(T)*d_buffer_size);
        memset(d_buffer,0,sizeof(T)*d_buffer_size);
    }
    //==========================================================================
    template <typename T>
    cyclic_buffer<T>::~cyclic_buffer()
    {
        if(NULL != d_buffer)
            free(d_buffer);
    }
    //==========================================================================
    template <typename T>
    size_t cyclic_buffer<T>::read_space(void) const
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
    template <typename T>
    size_t cyclic_buffer<T>::write_space(void) const
    {
        if( (d_r_ptr <= d_w_ptr) && (d_buffer_size + d_r_ptr -d_w_ptr > 2))
            return d_buffer_size + d_r_ptr -d_w_ptr - 2;
        if((d_r_ptr > d_w_ptr) && (d_r_ptr - d_w_ptr > 2))
            return d_r_ptr - d_w_ptr - 2;
        return 0;
    }
    //==========================================================================
    template <typename T>
    void 
    cyclic_buffer<T>::write_to_buffer(const T *data,size_t length)
    {
        if(length > write_space())
        {
            boost::format fmt("%s:%d:%s:写入缓存空间错误,写入长度不应该大于可写空间大小！");
            std::stringstream ss;
            ss << fmt % __FILE__ % __LINE__ % __func__;
            length = write_space();
        }
        if (d_w_ptr + length <= d_buffer_size )
        {
            memcpy(d_buffer+d_w_ptr,data,sizeof(T)*length);
            d_w_ptr = (d_w_ptr + length) % d_buffer_size;
        }
        else
        {
            size_t len = d_buffer_size - d_w_ptr;
            memcpy(d_buffer+d_w_ptr,data,sizeof(T)*len);
            d_w_ptr = (d_w_ptr + len) % d_buffer_size;
            memcpy(d_buffer+d_w_ptr,data+len,sizeof(T)*(length-len));
            d_w_ptr = (d_w_ptr + length-len) % d_buffer_size;
        }
    }
    //==========================================================================
    template <typename T>
    void 
    cyclic_buffer<T>::read_from_buffer(T *out,size_t length) const
    {
        if(length > read_space())
        {
            boost::format fmt("%s:%d:%s:读取缓存空间错误,读取长度不应该大于可读空间大小！");
            std::stringstream ss;
            ss << fmt % __FILE__ % __LINE__ % __func__;
            length = read_space();
        }
        //读取缓存过程
        if (d_r_ptr + length  <= d_buffer_size )
        {
            //当前读指针位置到缓存结束位置的可读空间大于等于本次需要读取的长度，可以一次读取
            memcpy(out,d_buffer+d_r_ptr,sizeof(T)*(length));
        }
        else 
        {
            //当前读指针位置到缓存结束位置的可读空间小于于本次需要读取的长度，需要分为两次进行读取
            size_t len = d_buffer_size - d_r_ptr;
            memcpy(out,d_buffer+d_r_ptr,sizeof(T)*len);
            memcpy(out+len,d_buffer,sizeof(T)*(length-len));
        }

    }
    //==========================================================================
    template <typename T>
    void 
    cyclic_buffer<T>::update_r_ptr( signed long len)
    {
        d_r_ptr = (d_r_ptr + len) % d_buffer_size;
    }
    //==========================================================================
    template <typename T>
    void 
    cyclic_buffer<T>::update_w_ptr(size_t len)
    {
        d_w_ptr = (d_w_ptr + len) % d_buffer_size;
    }
    //==========================================================================
    template <typename T>
    void 
    cyclic_buffer<T>::clear(void )
    {
        d_r_ptr = 0;
        d_w_ptr = 0;
    }
    //==========================================================================
    template <typename T>
    void 
    cyclic_buffer<T>::resize(size_t new_length)
    {
        d_buffer = (T*)realloc(d_buffer,sizeof(T)*new_length);
        d_buffer_size = new_length;
    }
// }// namespace cyclicbuffer
