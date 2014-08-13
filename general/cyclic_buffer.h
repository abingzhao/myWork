/**
 * Author : abing0513
 * data   : 2014-8-8
 */


#ifndef INCLUDED_CYCLIC_BUFFER_H
#define INCLUDED_CYCLIC_BUFFER_H

#include <cstdlib>
#include <cstring>
#include <sstream>
#include <boost/format.hpp>

namespace cyclicbuffer 
{
    template <typename T>
    class cyclic_buffer
    {
    public:
        cyclic_buffer(size_t buffer_size = 1024);
        ~cyclic_buffer();
        
        /**
         * @brief 返回当前缓存中的可读取空间大小
         */
        size_t read_space(void) const;
        /**
         * @brief 返回当前缓存中的可写入空间大小
         */
        size_t write_space(void) const;
        /**
         * @brief 向缓存中写入数据
         * 
         * @param data 要写入的数据指针
         * @param length 要写入的数据长度
         * */        
        void write_to_buffer(const T * const data,size_t length);


        /**
         * @brief 由缓存的读取数据
         * 
         * @param data 输出数据指针
         * @param length 读取的数据长度
         */
        void read_from_buffer(T * const data,size_t length) const;

        /**
         * @brief 单个数据的写
         */
        void push_back(const T& data);

        /**
         * @brief 单个数据的读
         */
        T pop_front();

        /**
         * @brief 调整写指针
         * @param size 调整长度
         */
        void update_r_ptr(signed long size);
        /**
         * @brief 调整读指针
         * @param size 调整长度
         */
        void update_w_ptr(size_t size);
        /**
         * @brief 重载操作符[]，使其下表与缓存中的读指针与缓存大小联合起来
         * @param pos 外部传入的相对于读指针的偏移，需加上读指针后对缓存长度取模
         */
        T &operator[](size_t pos) const { 
            if(pos > read_space())
                throw std::runtime_error("Out of the data length in buffer!");
            return d_buffer[(d_r_ptr+pos)%d_buffer_size];
        }
        /**
         * @brief 返回读指针当前位置（相对于缓存起始的偏移）
         */
        size_t r_ptr() const {return d_r_ptr;}
        /**
         * @brief 返回写指针当前位置（相对于缓存起始的偏移）
         */
        size_t w_ptr() const {return d_w_ptr;}
        /**
         * @brief 清楚当前缓存数据，即读写指针置0
         */
        void clear();
        /**
         * @brief 调整缓存空间的大小
         */
        void resize(size_t new_length);
    private:
        size_t d_buffer_size;
        size_t d_r_ptr;
        size_t d_w_ptr;
        T* d_buffer;
    };
    //==========================================================================
    template <typename T>
    cyclic_buffer<T>::cyclic_buffer(size_t buffer_size)
    :  d_buffer_size(buffer_size)
     , d_r_ptr(0)
     , d_w_ptr(2)
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
    cyclic_buffer<T>::write_to_buffer(const T *data,size_t write_len)
    {
        if(write_len > write_space())
        {
            boost::format fmt("%s:%d:%s:写入缓存空间错误,写入长度不应该大于可写空间大小！");
            std::stringstream ss;
            ss << fmt % __FILE__ % __LINE__ % __func__;
            write_len = write_space();
        }
        if (d_w_ptr + write_len <= d_buffer_size )
        {
            memcpy(d_buffer+d_w_ptr,data,sizeof(T)*write_len);
            d_w_ptr = (d_w_ptr + write_len) % d_buffer_size;
        }
        else
        {
            size_t len = d_buffer_size - d_w_ptr;
            memcpy(d_buffer+d_w_ptr,data,sizeof(T)*len);
            d_w_ptr = (d_w_ptr + len) % d_buffer_size;
            memcpy(d_buffer+d_w_ptr,data+len,sizeof(T)*(write_len-len));
            d_w_ptr = (d_w_ptr + write_len-len) % d_buffer_size;
        }
    }
    //==========================================================================
    template <typename T>
    void cyclic_buffer<T>::read_from_buffer(T *out,size_t read_len) const
    {
        if(read_len > read_space())
        {
            boost::format fmt("%s:%d:%s:读取缓存空间错误,读取长度不应该大于可读空间大小！");
            std::stringstream ss;
            ss << fmt % __FILE__ % __LINE__ % __func__;
            read_len = read_space();
        }
        //读取缓存过程
        if (d_r_ptr + read_len  <= d_buffer_size )
        {
            //当前读指针位置到缓存结束位置的可读空间大于等于本次需要读取的长度，可以一次读取
            memcpy(out,d_buffer+d_r_ptr,sizeof(T)*(read_len));
        }
        else 
        {
            //当前读指针位置到缓存结束位置的可读空间小于于本次需要读取的长度，需要分为两次进行读取
            size_t len = d_buffer_size - d_r_ptr;
            memcpy(out,d_buffer+d_r_ptr,sizeof(T)*len);
            memcpy(out+len,d_buffer,sizeof(T)*(read_len-len));
        }
        d_r_ptr = (d_r_ptr + read_len) % d_buffer_size;
    }
    //==========================================================================
    template <typename T>
    void cyclic_buffer<T>::push_back(const T& data)
    {
        if(write_space() == 0)
            throw std::runtime_error("NO space for new data!");
        d_buffer[d_w_ptr ++ ] = data;
    }
    //==========================================================================
    template <typename T>
    T cyclic_buffer<T>::pop_front()
    {
        if(write_space() == 0)
            throw std::runtime_error("NO data in Buffer!");
        return d_buffer[d_r_ptr--];
    }
    //==========================================================================
    template <typename T>
    void  cyclic_buffer<T>::update_r_ptr( signed long len)
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
} // namespace cyclicbuffer

#endif /* INCLUDED_LTE_SAT_CYCLIC_BUFFER_IMPL_H */
