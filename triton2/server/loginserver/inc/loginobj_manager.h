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

#ifndef _LOGINOBJ_MANAGER_H_
#define _LOGINOBJ_MANAGER_H_

#include "entity.h"
#include "loginobj_define.h"
#include "servertool.h"
#include "array_list.h"
#include "shm.h"

class CObj;
class CLoginObjManagerImp;
class CSharedMem;


class CLoginObjManager : public CSingleton< CLoginObjManager > 
{
public:
	CLoginObjManager();
	~CLoginObjManager();

	void* operator new(size_t size);
	void  operator delete(void* pointer);

	int Initailize();
	int Resume();
	unsigned short GetGUID( );

	CObj*	CreateObject( EGlobalObjType vObjType );
	int		DestroyObject( int vObjID );
	CObj*	GetObject( int vObjID ); 

	static unsigned int CountSize( );

public:
	
	static CSharedMem* mShmPtr; // �����ڴ�ָ��


	// ��Ϸ����
	CLoginObjManagerImp* mLoginObjManagerImp;

	unsigned short mIncreasingCount;		// װ�������ļ��� 
};

#endif
