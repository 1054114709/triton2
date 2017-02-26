#pragma once 
#if 0
/******************************************************************************
   ��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

******************************************************************************
  �ļ���          : lk_assert.h
  �汾��          : 1.0
  ����            : �ź���
  ��������        : 2008-06-04
  ����޸�        : 
  ��������        :  ��װassert, relaseģʽ��Ҳ����
  �����б�        : 
  �޸���ʷ        : 
  1 ����          : 2008-06-04
    ����          : �ź���
    �޸�����      : ����
*******************************************************************************/
#endif

#if 0
/*
#ifdef use_lk_assert  
#include "log.h"
#define lk_assert(a, fail_handle)  \
	do \
	{   \
	if (!(a))   \
		{         \
		log_error("default","assert:%s.[%s,%s,%d]",#a,__file__,__function__, __line__);  \
		fail_handle; \
		}  \
	} while(0);
#else
#include <assert.h>
#define lk_assert(a, fail_handle) \
	do   \
	{    \
		assert(a);   \
	} while(0);
#endif 
*/

#endif

#include <assert.h>
#include "base.h"

#ifdef USE_LK_ASSERT  
#include "log.h"
#define LK_ASSERT(a, fail_handle)  \
	if (!(a))   \
		{         \
		LOG_ERROR("default","ASSERT:%s.[%s,%s,%d]",#a,__FILE__,__FUNCTION__, __LINE__);  \
		fail_handle; \
		}
	
#define LK_ASSERT_STR( a, fail_handle, str, ... )									\
	if( ( a ) == false )															\
	{																				\
		char log_str[ 1024 ];														\
		sprintf( log_str, str, ##__VA_ARGS__ );										\
		LOG_ERROR( "default", "[ %s : %d ][ %s ][ ASSERT: ( %s ) == false ], %s",	\
			__FILE__, __LINE__, __FUNCTION__, #a, log_str );						\
		fail_handle;																\
	}

#define LK_ASSERT_LOG( log, a, fail_handle ) 										\
	if( ( a ) == false )															\
	{																				\
		LOG_ERROR( "default", "[ %s : %d ][ %s ] ASSERT:%s", __LK_FILE__, __LINE__,	\
			__FUNCTION__, #a );														\
		LOG_ERROR( log, "[ %s : %d ][ %s ] ASSERT:%s", __LK_FILE__, __LINE__,		\
			__FUNCTION__, #a ); 													\
		fail_handle;																\
	}

#define LK_ASSERT_LOG_STR( log, a, fail_handle, str, ... )							\
	if( ( a ) == false )                                                            \
	{                                                                               \
		char log_str[ 1024 ];                                                       \
		sprintf( log_str, str, ##__VA_ARGS__ );                                     \
		LOG_ERROR( "default", "[ %s : %d ][ %s ][ ASSERT: ( %s ) == false ], %s",   \
			__LK_FILE__, __LINE__, __FUNCTION__, #a, log_str );                     \
		LOG_ERROR( log, "[ %s : %d ][ %s ][ ASSERT: ( %s ) == false ], %s",   		\
			__LK_FILE__, __LINE__, __FUNCTION__, #a, log_str );						\
		fail_handle;                                                                \
	}
#else
#define LK_ASSERT(a, fail_handle) \
	do   \
	{    \
	assert(a);   \
	} while(0);

#define LK_ASSERT_STR( a, fail_handle, str, ... )	LK_ASSERT( a, fail_handle )

#define LK_ASSERT_LOG( log, a, fail_handle ) 	LK_ASSERT( a, fail_handle )
#define LK_ASSERT_LOG_STR( log, a, fail_handle, str, ... ) 	LK_ASSERT( a, fail_handle )

#endif    

   


      
  

