#pragma once

// #ifndef _FCM_SERVICE_H_
// #define _FCM_SERVICE_H_

#include "module_manager.h"
#include "entity.h"
#include "lk_hashmap.h"
#include "lk_string.h"
#include "gateobj_define.h"
#include "lk_set.h"

using namespace GateServer;	

class CChatmodule :public CDataModule, public CSingleton< CChatmodule >
{
public:
	void OnLaunchServer();
	void OnExitServer();
	void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );
	void OnMessage(int nServerID, CMessage* pMessage );
	void OnSeverMessage(int nServerID, CMessage* pMessage );
	void OnMessageFangChenMiRequest( int vServerID, CMessage* tpMessage );
	CChatmodule();
	~CChatmodule();
	int Initialize();							    
	int Resume();
	static unsigned int CountSize();
	void* operator new( size_t nsize );
	void  operator delete( void* pointer );	
	virtual bool IsLaunched() { return true; }
public:
	// ����Ƶ��
	void OnWorldChatMsg( CMessage* pMessage );
	
	// ����Ƶ��
	void OnP2PChatMsg( CMessage* pMessage );
	
	// ����Ƶ��
	void OnFamilyChatMsg( CMessage* pMessage );
	
	// ����Ƶ��
	void OnCorpsChatMsg( CMessage* pMessage );

	// ����ϵͳ�㲥
	void SendSysNotice( const char *pMsg, int RepeatedNum );
	
	// ���Ͷ�����Ϣ
	void OnTeamMsg( CMessage* pMessage );

private:
	
	// ���������ݱ��浽��־������
	void SendChatMsg2Log( CMessage* pMessage );
};



