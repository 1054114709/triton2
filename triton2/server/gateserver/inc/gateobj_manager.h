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

#ifndef _GATEOBJ_MANAGER_H_
#define _GATEOBJ_MANAGER_H_

#include "entity.h"
#include "gateobj_define.h"
#include "servertool.h"
#include "array_list.h"
#include "shm.h"

class CObj;
class CGateObjManagerImp;
class CSharedMem;


class CGateObjManager : public CSingleton< CGateObjManager > 
{
public:
	CGateObjManager();
	~CGateObjManager();

	void* operator new(size_t size);
	void  operator delete(void* pointer);

	int Initialize();
	int Resume();
	unsigned short GetGUID( );

	CObj*	CreateObject( EGlobalObjType vObjType );
	int		DestroyObject( int vObjID );
	CObj*	GetObject( int vObjID ); 

	void Dump( char* pBuffer, unsigned int& unLen );
	static unsigned int CountSize( );

public:
	
	static CSharedMem* mShmPtr; // �����ڴ�ָ��


	// ��Ϸ����
	CGateObjManagerImp* mGateObjManagerImp;

	unsigned short mIncreasingCount;		// װ�������ļ��� 

};

#endif


