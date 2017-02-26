#pragma once

#include "tradetype.h"
#include "trade.h"
#include "trademanager.h"
#include "trademessage_pb.hxx.pb.h"
#include "sceneobj_define.h"
#include "sceneobj_manager.h"
#include "propertymodule.h"
#include "servercore.h"
#include "servertool.h"

// ********************************************************************** //

// CTradeModule

// ********************************************************************** //


class CTradeModule : public CLogicModule, public CSingleton< CTradeModule >
{
public:
	static char	sModuleName[ NAME_LENGTH ];
	
public:
	int mTimePile;
	
public:
	CTradeModule() : CLogicModule( sModuleName )
	{
		if ( mShmPtr->GetInitMode() == SHM_INIT )
		{
			mTimePile = 1000;	
		}	
	}

	static unsigned int CountSize();
	
public:
	virtual void OnLaunchServer( );
	virtual void OnExitServer();
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName );
	virtual void OnRouterMessage( CMessage* pMessage );
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );
	virtual void OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst );
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );

	// ��������
	virtual void OnLoadConfig( ) ;

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }

	// ��������
	void OnMessageTradeInvite( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ���봦��
	void OnMessageTradeInviteProc( CEntityPlayer* pPlayer, CMessage* pMessage );	
	
	// ���½�����Ʒ�б�: ��ӡ��Ƴ�
	void OnMessageUpdateTradeGoods( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ���ͽ��׽��
	void OnMessageSendTradeMoney( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ����������Ϣ
	void OnMessageLockTrade( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ȷ�Ͻ��״���
	void OnMessageSubmitTrade( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// �رս���
	void OnMessageCloseTrade( CEntityPlayer* pPlayer, CMessage* pMessage );
		
	// ����������Ϣת�����ͻ���
	void OnSendTradeInviteCallBack(CEntityPlayer* pPlayer, unsigned int vEntityID );	

	// ֪ͨ�ͻ��˿�ʼ����
	void OnSendTradeBeginCallBack( CEntityPlayer* pPlayer, unsigned int vEntityID );	

	// ȡ������
	void OnCancelTrade( int vEntityID );

	// check player service status
	int CheckPlayerService( CEntityPlayer* pSrcPlayer, CEntityPlayer* pDesPlayer ); 

	void SendErrorNotice( CEntityPlayer* pPlayer, int vCode );
};


