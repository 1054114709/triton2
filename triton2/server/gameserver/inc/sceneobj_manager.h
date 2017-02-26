/******************************************************************************
   ��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

******************************************************************************
  �ļ���          : sceneobj_manager.h
  �汾��          : 1.0
  ����            : ZHL
  ��������        : 2008-06-05
  ����޸�        : 
  ��������        : �ṩ��Ϸ���󴴽���ɾ�������ҽӿڡ��ýӿں�ʵ�ַ���ķ�ʽ�������������͡�
  �����б�        : 
  �޸���ʷ        : 
  1 ����          : 2008-06-05
    ����          : ZHL
    �޸�����      : ����
*******************************************************************************/

#pragma once

#include "sceneobj_define.h"
#include "servertool.h"
#include "lk_assert.h"
#include "lk_sharedvector.h"
#include "array_list.h"
#include "objmanager.h"

class CObj;
class CSceneObjManagerImp;
class CSharedMem;


class CSceneObjManager : public CSingleton< CSceneObjManager > 
{
public:
	CSceneObjManager();
	~CSceneObjManager();

	void* operator new(size_t size);
	void  operator delete(void* pointer);
	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* pointer, const char* file, int line);

	int Initailize();
	int Resume();
	unsigned short GetGUID( );

	CObj*	CreateObject( EGlobalObjType vObjType );
	int		DestroyObject( int vObjID );
	CObj*	GetObject( int vObjID ); 

	// �����ʹ��������
	void Dump( char* pBuffer, unsigned int& unLen );

	static unsigned int CountSize( );

public:
	typedef lk::fixed_size_memory_pool< int, SERVER_CAP_SHARE_CELLENTITY, 2> DataMng_SharedCellsEntityID;	


	typedef lk::fixed_size_memory_pool< unsigned int, SERVER_CAP_SHARE_SEEN_PLAYER, 2>	DataMng_SharedSeenPlayers;
	typedef lk::fixed_size_memory_pool< unsigned int, SERVER_CAP_SHARE_SEEN_CHARNPC, 2>	DataMng_SharedSeenCharNpcs;
	typedef lk::fixed_size_memory_pool< unsigned int, SERVER_CAP_SHARE_SEEN_STATICNPC,2>	DataMng_SharedSeenStaticNpcs;

public:
	
	static CSharedMem* mShmPtr; // �����ڴ�ָ��


	// ��Ϸ����
	CSceneObjManagerImp* mSceneObjManagerImp;

	// ��Ϸ���ݣ���Ҫ�Ǹ���ObjectID������
	DataMng_SharedCellsEntityID	mSharedCellsEntityID;

	DataMng_SharedSeenPlayers		mSharedSeenPlayers;
	DataMng_SharedSeenCharNpcs		mSharedSeenCharNpcs;
	DataMng_SharedSeenStaticNpcs	mSharedSeenStaticNpcs;

	unsigned short mIncreasingCount;		// װ�������ļ��� 

};


