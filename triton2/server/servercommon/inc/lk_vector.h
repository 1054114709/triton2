

/******************************************************************************
   ��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

******************************************************************************
  �ļ���          : lk_vector.h
  �汾��          : 1.0
  ����            : ZHL
  ��������        : 2008-06-04
  ����޸�        : 
  ��������        : ��װ��һ���̶���󳤶ȵ�����(�����ڹ����ڴ���ʹ��)
  �����б�        : 
  �޸���ʷ        : 
  1 ����          : 2008-06-04
    ����          : ZHL
    �޸�����      : ����
*******************************************************************************/


#pragma  once

#include <cstddef>
#include <string>
#include "lk_assert.h"

namespace lk
{


template < typename T, std::size_t count >
class vector
{
public:
    // type definitions
    typedef T value_type;
    typedef T * iterator;
    typedef T * const const_iterator;
    typedef T & reference;
    typedef const T &  const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    // iterator support
    iterator begin()
    {
        return elems_;
    }

    const_iterator begin() const
    {
        return elems_;
    }

    iterator end()
    {
        return elems_ + size_;
    }

    const_iterator end() const
    {
        return elems_ + size_;
    }

    // reverse iterator support
    typedef std::reverse_iterator < iterator > reverse_iterator;
    typedef std::reverse_iterator < const_iterator > const_reverse_iterator;

    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }

    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

    // operator[]
    reference operator[] (size_type i)
    {
        LK_ASSERT(i < size_ && "operator[] out of range", ;);
        return elems_[i];
    }

    const_reference operator[] (size_type i) const
    {
        LK_ASSERT(i < size_ && "operator[] out of range", ;);
        return elems_[i];
    }

    // front() and back()
    reference front()
    {
        return elems_[0];
    }

    const_reference front() const
    {
        return elems_[0];
    }

    reference back()
    {
        return elems_[size_ - 1];
    }

    const_reference back() const
    {
        return elems_[size_ - 1];
    }

    size_type size() const
    {
        return size_;
    }

    bool empty() const
    {
        return 0 == size_;
    }

    static size_type max_size()
    {
        return count;
    }

    // �������һ��
    iterator push_back(const T & t)
    {
        //LK_ASSERT(size_ < capacity() && "array<> push_back size_ > capacity()", return elems_ + size_);
		if( size_ >= capacity() )
		{
			LOG_ERROR( "default", "array<> push_back size_ > capacity()");
			print_trace_fd( "default" );
			return elems_ + size_;
		}
		elems_[size_++] = t;
        return elems_ + size_;
    }

	//��ͷ������һ��Ԫ��
	iterator push_front(const T & t)
    {
        LK_ASSERT(size_ < capacity() && "array<> push_front size_ > capacity()", return &elems_[0]);
		for(int i = size_; i > 0; i--)
		{
			elems_[i] = elems_[i-1];
		}
        elems_[0] = t;
		size_++;
        return &elems_[0];
    }

    // erase a element and move the back elemts to front
    iterator erase(iterator pos)
    {
        iterator endPos = end();
        if (pos != endPos)
        {
            iterator nextPos = pos + 1;
            if (nextPos != endPos)
            {
                std::copy(nextPos, endPos, pos);
            }
            --size_;
        }
        return pos;
    }

    void erase(size_type pos)
    {
        LK_ASSERT(pos < size_ && "erase out of range", return);
        size_type next = pos + 1;
        if (next < size_)
        {
            std::copy(elems_ + next, elems_ + size_, elems_ + pos);
        }
        --size_;
    }

    iterator erase(iterator first, iterator last)
    {
        iterator __i(std::copy(last, end(), first));
        size_ -= (last - first);
        return first;
    }

	void pop_back() 
	{
		size_ -- ;
	}

    size_t capacity()
    {
        return count;
    }

    void clear()
    {
        size_ = 0;
    }

	void initailize()
	{
		clear();
	}

private:
    T elems_[count];
    size_t size_;
};



};                   
                         
