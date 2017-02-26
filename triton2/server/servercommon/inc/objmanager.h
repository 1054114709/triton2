/******************************************************************************
   ��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

*******************************************************************************
  �ļ���          : objmanager.h
  �汾��          : 1.0
  ����            : ZHL
  ��������        : 2008-06-05
  ����޸�        : 
  ��������        : ���������(����,ɾ��,����),Ч��O(1),��֤����id������
  �����б�        : 
  �޸���ʷ        : 
  1 ����          : 2008-06-05
    ����          : ZHL
    �޸�����      : ����
*******************************************************************************/
#pragma once

#include "array_list.h"
#include "clock.h"
#include "lk_assert.h"
#include "log.h"

/**
* ����ʹ�ö���id
* ����ʹ����������������֤�����ID�ǲ��ϵ����ģ�
* ����ͨ��ID���ʶ�����ٶȺܿ�
* 1. ������fixed_size_memory_pool�ͷŶ������뵽���е�β��
* 2. ���ñ���last_used_id����֤id��������
*/
typedef int id_type;
template <id_type id_start, int count, id_type id_end>
struct incremental_obj_id_policy
{
	incremental_obj_id_policy()
		//: last_used_id(0)
	{
	}

	/**
	* ��ȡһ����Ч�Ķ���id
	* 
	* @param offset �����������е�����(ƫ����)
	* 
	* @return ��Ч�Ķ���ID
	*/
	id_type get_valid_id(int offset)
	{
		id_type tmp_id = id_start + offset;
		if (tmp_id <= last_used_id)
		{
			id_type real_id = tmp_id 
				+ ((last_used_id - tmp_id) / count + 1) * count;
			if (real_id < id_end )
			{
				tmp_id = real_id;
			}
		}
		last_used_id = tmp_id;
		return tmp_id;
	}

	/**
	* ��ȡһ����Ч�Ķ���ƫ����
	* 
	* @param id     ��Ч�Ķ���ID
	* 
	* @return �����������е�����(ƫ����)
	*         ʧ�ܷ���-1
	*/
	int get_offset_value(id_type id)
	{
		if (id < id_start || id > id_end)
		{
			LK_ASSERT(false, return -1);
		}
		return (id - id_start) % count;
	}

	int last_used_id;
};

template <class obj_name, id_type id_start, int count, id_type id_end>
class ObjManager : public lk::fixed_size_memory_pool<obj_name, count>
{
public:
	typedef incremental_obj_id_policy<id_start, count, id_end> id_policy;
	typedef lk::fixed_size_memory_pool<obj_name, count> super;
	typedef typename super::pointer pointer;
	typedef typename super::reference reference;
	typedef typename super::iterator iterator;
	typedef typename super::offset_type offset_type;
	typedef typename super::node_type node_type;

	ObjManager()
		: last_tick_obj_(0)
	{
		//TODO:
		//super::initailize_pool();
		last_tick_obj_ = super::begin( );
	}

	void initailize()
	{
		policy_.last_used_id = 0;
		super::initailize_pool();
		LOG_NOTICE("default", "init addr %6x", this);
	}

	void resume()
	{
		super::resume_pool();
		LOG_NOTICE("default", "resume addr %6x", this);
	}

	/**
	* ����һ������
	* 
	* @return ����ɹ�������ָ������ָ��
	*         ���ʧ�ܣ�����0
	*/
	pointer create()
	{
		pointer p = super::allocate();
		//p = check_valid_id(p);	
		if( p )
		{
			p->set_id( get_valid_id(p) );
		}	
		return p;
	}

	/**
	* ʹ��other��Ϊ����Ĺ��캯������������
	* Ŀǰֻ֧�ֹ��캯��ֻ��һ������
	* 
	* @param other
	* @param v      ���κ�������Ϣ�Ķ���
	*               ��obj_name���캯���Ĳ���
	* 
	* @return ����ɹ�������ָ������ָ��
	*         ���ʧ�ܣ�����0
	*/
	template <typename other>
	pointer create(other& v)
	{
		pointer p = super::allocate(v);
		//p = check_valid_id(p);
		if( p )
		{
			p->set_id( get_valid_id(p) );
		}
		return p;
	}

	/**
	* �ͷŴ����Ķ���
	* 
	* @param p
	*/
	void remove(pointer p)
	{
		if ( p == NULL )
		{
			return;
		}

		if (super::end() != last_tick_obj_ && (&(*last_tick_obj_) == p))
		{
			++last_tick_obj_;
		}

		super::deallocate(p);
	}

	// ������Щ�Ǵ�object�̳еĶ������еĹ���
	/**
	* �ͷŴ����Ķ���
	* ����Ķ������̳���object���ܵ��ô˺���
	* 
	* @param id     �����ID
	*/
	void remove(id_type id)
	{
		pointer p = find_by_id(id);

		//TODO: Ϊ�˷������⣬�������ӡ��־
		if ( p == NULL )
		{
			LOG_ERROR( "default", "object id = %d not found", id );
			return;
		}
		remove( p );
	}

	/**
	* ����ID�����Ҷ���
	* ����Ķ������̳���object���ܵ��ô˺���
	* 
	* @param id     �����id
	* 
	* @return ����ɹ�������ָ������ָ��
	*         ���ʧ�ܣ�����0
	*/
	pointer find_by_id(id_type id)
	{
		int offset = policy_.get_offset_value(id);
		if (offset >= 0)
		{
			pointer p = super::operator [](offset);
			if (p && p->get_id() == id)
			{
				return p;
			}
		}
		return 0;
	}

	// ע�⣺�����캯����һ��������ô˺��������ڻ����ȷ��ID,������
	// ���ڹ��캯��������Ҫ�����ID,���ַ�ʽ�ܳ�ª������ʱֻ����˴���
	id_type get_valid_id(pointer p)
	{
		return policy_.get_valid_id(super::node_offset(p));
	}

	template <typename time_type>
	int tick(time_type curTime, int max_num)
	{
		int count = 0;
		for (; last_tick_obj_ != super::end() && count <= max_num;
			++last_tick_obj_, ++count)
		{
			last_tick_obj_->tick(curTime);
		}

		if (last_tick_obj_ ==  super::end())
		{
			last_tick_obj_ = super::begin();
		}

		return count;
	}

	/**
	* ���ض���������е���ʼ���������
	* 
	* @param 
	* 
	* @return ����ָ�����ĵ�����
	*         
	*/
	iterator begin()
	{
		return super::begin();
	}

	/**
	* ���ض���������еĽ������������
	* 
	* @param 
	* 
	* @return ����ָ�����ĵ�����
	*         
	*/
	iterator end()
	{
		return super::end();
	}

private:

	pointer check_valid_id(pointer p)
	{
		if (p)
		{
			if (!p->valid())
			{
				remove(p);
				p = 0;
			}
		}
		return  p;
	}

	id_policy policy_;
	iterator last_tick_obj_; // ���һ��tick�Ķ���
};


