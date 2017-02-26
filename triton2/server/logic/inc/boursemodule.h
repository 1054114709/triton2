#ifndef _BOURSE_H_
#define _BOURSE_H_

enum BOURSE_DOC_TYPE
{
	BOURSE_DOC_BUY	= 1,
	BOURSE_DOC_SELL	= 2
};

class CBourseModule :  public CLogicModule, public CSingleton< CBourseModule >
{
private:
	static char sModuleName[ NAME_LENGTH ];

	unsigned int mListID;
	PBBourseDetailList mBuyList;
	PBBourseDetailList mSellList;

	int mMoneyTax;
	int mYbTax;
	int mTaxID;

public:
	CBourseModule( );

	static unsigned int CountSize( );
	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickSekt );

	// ��������
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName ){ return SUCCESS; }
	// ·����Ϣ
	virtual void OnRouterMessage( CMessage* pMessage );

	// �ͻ��˷�����Ϣ
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst );

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode ){ }

	// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode ){ return true; }

	// ��������
	virtual void OnLoadConfig( );

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }

public:
	CPlayerExchange* GetPlayerExchange( CEntityPlayer* vpPlayer );
	int DBSessionTimeOut( CSession* vpSession );
	int DBSessionEnd( CSession* vpSession, int vResultCode );
	
	int IncAccount( CEntityPlayer* vpPlayer, int vMoney, int vYb );
	int DecAccount( CEntityPlayer* vpPlayer, int vMoney, int vYb );

	int AddSellOrder( CEntityPlayer* vpPlayer, int vPrice, int vYbCount );
	int AddBuyOrder( CEntityPlayer* vpPlayer, int vPrice, int vYbCount );

	int RemoveDoc( CEntityPlayer* vpPlayer );

	int GetPlayerSelfDocList( CEntityPlayer* vpPlayer );
	int PlayerSelfDocListNotice( CMessage* vpMsg );
	int NoticePlayerAccount( CEntityPlayer* vpPlayer, int vAcount = BOURSE_ACCOUNT_LOAD, int vParame1 = 0, 
			int vParame2 = 0, int vParame3 = 0 );
	int GetPlayerAccount( CEntityPlayer* vpPlayer );

	int SendEventCode( CEntityPlayer* vpPlayer, int vCode, int vParame1 = 0, int vParame2 = 0 );
	int BourseTradeNotice( int vAccountID, CMessage* vpMsg, int vMsgID );

	void SendEventNotify( int vEventID, int vPrice, int vCount );
public:
	int OnMessageD2SBourseAccountNotice( CMessage* vpMsg );
	void OnMessageS2LBourseLog( CMessage* vpMsg );

	int OnMessageC2SBourseLoadAccount( CEntityPlayer* vpPlayer, CMessage* vpMsg );
	int OnMessageC2SBourseIncAccount( CEntityPlayer* vpPlayer, CMessage* vpMsg );
	int OnMessageC2SBourseDecAccount( CEntityPlayer* vpPlayer, CMessage* vpMsg );
	int OnMessageC2SBourseAddBuy( CEntityPlayer* vpPlayer, CMessage* vpMsg );
	int OnMessageC2SBourseAddSell( CEntityPlayer* vpPlayer, CMessage* vpMsg );
	int OnMessageC2SBourseLoadSelfList( CEntityPlayer* vpPlayer, CMessage* vpMsg );
	int OnMessageC2SBourseLoadList( CEntityPlayer* vpPlayer, CMessage* vpMsg );
	int OnMessageC2SBourseDecBuyDoc( CEntityPlayer* vpPlayer, CMessage* vpMsg );
	int OnMessageC2SBourseDecSellDoc( CEntityPlayer* vpPlayer, CMessage* vpMsg );
	int OnMessageC2SBourseLogQuery( CEntityPlayer* vpPlayer, CMessage* vpMsg );


	int OnMessageG2SBourseListNotice( CMessage* vpMsg );
	int OnMessageG2SBourseTradeBuy( CMessage* vpMsg );
	int OnMessageG2SBourseTradeSell( CMessage* vpMsg );
	int OnMessageD2SBourseLog( CMessage* vpMsg );

	int AddOrder( CEntityPlayer* vpPlayer, PBBourseDetail& vDetail, BOURSE_DOC_TYPE vType, int vCount );


};

#endif


