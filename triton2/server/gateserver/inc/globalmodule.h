#pragma once


#include "module_manager.h"
#include "entity.h"
#include "lk_hashmap.h"
#include "lk_string.h"
#include "lk_set.h"
using namespace GateServer;	

class CGlobalModule :public CDataModule, public CSingleton< CGlobalModule >
{
public:
	CGlobalModule(){}
	~CGlobalModule(){ }
public:
	// ����������
	virtual void OnLaunchServer( ){}

	// �˳�������
	virtual void OnExitServer( ) {}

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset ) { }

	// �ͻ��˷�����Ϣ
	virtual void OnMessage( int nServerID, CMessage* pMessage );

	// ���¼��������ļ�
	virtual void ReloadCfg() { }

	// �����Ƿ����
	virtual bool IsLaunched() { return true; }

	// ��һ�쵽��
	virtual void OnNewDayCome() { }

	// ��һ�ܵ���
	virtual void OnNewWeekCome() { }

	// ��������������
	virtual void OnLaunchComplete() { }	
	
	// 
	static unsigned int CountSize();
public:
	
	// �����������鵽��������
	void OnMessageRoleGlobalTele( int nServerID, CMessage *pMessage );
	void SendRoleGlobalTeleResponse( int nErrcode, int nRoleID, int nWorldID, int nServerKey, int nServerID, const char *pAddr, int nLoginToken );

	// ȫ�ָ���������������������Ϣ����
	void OnMessageCreateRepetion( int nServerID, CMessage *pMessage );

	// ȫ�ָ���������������������Ϣ��Ӧ
	void SendResponseCreateRepetion( int nErrcode, int nRegKey, KEY_TYPE nKey );

	// ��ҽ��븱������Ϣ֪ͨ
	void OnMessageWarEnableNotify( int nServerID, CMessage *pMessage );

	// �ߵ���ҵ�֪ͨ
	void OnMessageKickPlayer( int nServerID, CMessage *pMessage );

	// �߳���ҵ���Ϣ֪ͨ
	void OnMessageKickGlobalPlayerACK( int nServerID, CMessage *pMessage );

	// �����������֪ͨ(���Գ���)
	void OnMessagePlayerGlobalTele( int nServerID, CMessage *pMessage );

	// ����������Ļ�Ӧ��Ϣ
	void OnMessageGlobalTeleResponse( int nServerID, CMessage *pMessage );
};