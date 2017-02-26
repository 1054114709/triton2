#pragma once

#include "stall.h"
#include "servercore.h"
#include "servertool.h"

class CStallModule : public CLogicModule, public CSingleton< CStallModule > 
{
public:
	static char	sModuleName[ NAME_LENGTH ];
	
	// module config data handle
	STALL_CFG* tpCfg;

public:
	CStallModule( ) : CLogicModule( sModuleName )
	{
		tpCfg = CSceneCfgManager::GetSingleton().GetStall_cfg();
	}

	static unsigned int CountSize();

public:
	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );

	// ��������
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName );

	// ·����Ϣ
	virtual void OnRouterMessage( CMessage* pMessage );

	// �ͻ��˷�����Ϣ
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst );

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );

	// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );

	// ��������
	virtual void OnLoadConfig( ) {};

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }

public:
	// to begin process client message

	// ��̯λ
	void OnMessageOpenStall( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ���ȶ�ȡ
	void OnMessageReadProcessRtn( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ̯λ��Ʒ���£��ϼܡ��¼�
	void OnMessageUpdateGoods( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Ʒ�۸�
	void OnMessageUpdatePrice( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ��ҵ��̯λ
	void OnMessageClickStall( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ��ҹ�����Ʒ
	void OnMessageBuyGoods( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ��̯
	void OnMessageCloseStall( CEntityPlayer* pPlayer, CMessage* pMessage );
	// �ر�̯λ����
	void OnMessageCloseStallDlg( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ����̯���͹������
	void OnMessageUpdateText( CEntityPlayer* pPlayer, CMessage* pMessage );

	void OnMessageGetStallRecord( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnMessageClearStallRecord( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �Խ���ɼ���Χ����ҷ���̯λ��Ϣ
	void TouchStallPedal( CEntityPlayer* pPlayer, PBStallInfo* pStallInfo );

	// send message to client

	void SendErrorNotice( CEntityPlayer* pPlayer, int vCode );

	// ���Ϳ�ʼ��̯ʱ�������Ϣ����̯��
	void SendOpenStallError( CEntityPlayer* pPlayer, int nErrCode );

	// print trade logs
	void PrintTradeLog( 
		const char* pMaster, 
		int nMasterID,
		const char* pBuyer,
		int nBuyerID,
		unsigned int vItemID, 
		unsigned int vNumber,
		unsigned int vPrice,
		const int vPriceType);

	// save
	void SaveStallData( CEntityPlayer* pPlayer );
	int GetStallData( CEntityPlayer* pPlayer, CMessageStartStallNotify* pMessage );

	//send message to db
	//����Ԫ����̯�Ľ�����Ϣ��DB
	void SendExchageRequest(CEntityPlayer* pBuyer,CEntityPlayer* pSeller, const CStallRecord* tpRecord, const int nIBFeeID );


	// ����Ԫ���������ݿⳬʱδ����
	void OnSessionTimeoutYbStallExchange( CSession* pSession );

	// ����Ԫ���������ݿⷵ��
	void OnSessionYbStallExchangeResponse( CMessage* pMsg, int nParam1, int nParam2 );
};


