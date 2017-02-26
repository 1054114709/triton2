/******************************************************************************
	��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

******************************************************************************
	�ļ���		: sceneobj_manager_imp.h
	�汾��		: 1.0
	����			: ZHL
	��������		: 2008-07-09
	����޸�		: 
	��������		: ��������������Ϸ����,�����ڹ����ڴ��� 
	�����б�		: 
	�޸���ʷ		: 
		1 ����	: 2008-07-09
		����		: ZHL
		�޸�����	: ����
*******************************************************************************/
#ifndef _LOGINOBJ_MANAGER_IMP_H_
#define _LOGINOBJ_MANAGER_IMP_H_

#include "object.h"
#include "loginobj_define.h"
#include "objmanager.h"
#include "entity.h"
#include "shm.h"
#include "loginlogic.h"

#define OBJ_ID_START(obj_type)	(((obj_type) << OBJ_ID_BITS) + 1)
#define OBJ_ID_END(obj_type)	((((obj_type) + 1) << OBJ_ID_BITS) - 10)
#define OBJ_ID_COUNT(obj_type, count) OBJ_ID_START(obj_type), count, OBJ_ID_END(obj_type)

class CSharedMem;


class CLoginObjManagerImp 
{
public:
	// ��Ϸ����
	typedef ObjManager< CLoginPlayer, OBJ_ID_COUNT( OBJTYPE_PLAYER_AT_LOGIN, PLAYER_AT_LOGIN_CAP) > ObjMng_PlayerAtLogin;
	typedef ObjManager< CServerSession, OBJ_ID_COUNT( OBJTYPE_SERVERSESSION, SERVERSESSION_CAP) >  ObjMng_ServerSession;
#ifdef USING_ERATING
	typedef ObjManager< CAGIPSession, OBJ_ID_COUNT( OBJTYPE_AGIPSESSION, AGIPSESSION_CAP) >  ObjMng_AGIPSession;
	typedef ObjManager< CIbPayAudit,  OBJ_ID_COUNT( OBJTYPE_IBPAYAUDIT,  IBPAYAUDIT_CAP) >  ObjMng_IbPayAudit;
#endif
public:

	CLoginObjManagerImp();
	~CLoginObjManagerImp();

	void* operator new( size_t size );
	void  operator delete( void* pointer );

	int Initailize();
	int Resume();

	static unsigned int CountSize();

public:

	static CSharedMem* mShmPtr; // �����ڴ�ָ��

	// ��Ϸ����
	ObjMng_PlayerAtLogin mPlayerAtLoginPool;

#ifdef USING_ERATING
	ObjMng_AGIPSession mAGIPSessionPool;
	ObjMng_IbPayAudit  mIbPayAuditPool;
#endif
	ObjMng_ServerSession mServerSessionPool;
};

#endif
