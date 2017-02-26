#ifndef _LOGINOBJ_DEFINE_H_
#define _LOGINOBJ_DEFINE_H_
#if 0
/******************************************************************************
   ��Ȩ���� (C ), 2008-2018, �������ߣ��������Ƽ����޹�˾

******************************************************************************
  �ļ���          : sceneobj_define.h
  �汾��          : 1.0
  ����            : ZHL
  ��������        : 2008-06-26
  ����޸�        : 
  ��������        : ���峡��������������Ϸ����Ԥ��������
  �����б�        : 
  �޸���ʷ        : 
  1 ����          : 2008-06-26
    ����          : ZHL
    �޸�����      : ����
*******************************************************************************/
#endif

// ���涨�����������
#ifdef _DEBUG_
	#define PLAYER_AT_LOGIN_CAP		10000		//  ��������������
	#define AGIPSESSION_CAP			100000		//  ����ͬʱ��֤������������ 
	#define SERVERSESSION_CAP		100000		//  ����ͬʱ��֤������������ 
	#define IBPAYAUDIT_CAP			(PLAYER_AT_LOGIN_CAP)		//  ����ͬʱ��֤������������ 
#else
	#define PLAYER_AT_LOGIN_CAP		20000		// ��������������
	#define AGIPSESSION_CAP			20000		// ����ͬʱ��֤������������ 
	#define SERVERSESSION_CAP		20000		// ����ͬʱ��֤������������ 
	#define IBPAYAUDIT_CAP			(PLAYER_AT_LOGIN_CAP)		//  ����ͬʱ��֤������������ 
#endif // ! _DEBUG_

// ȫ�ֶ�������
enum EGlobalObjType
{
	OBJTYPE_START = 0x01,		// start 
	OBJTYPE_PLAYER_AT_LOGIN,	// CLoginPlayer
	OBJTYPE_AGIPSESSION, 		// CAGIPSession
	OBJTYPE_SERVERSESSION, 		// CServerSession
	OBJTYPE_IBPAYAUDIT,			// CIbPayAudit
	OBJTYPE_END					// end
};

#endif
