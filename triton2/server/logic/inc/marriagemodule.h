#pragma  once	   
#include "servercore.h"
#include "servertool.h"
#include "marriagemanager.h"
#include "marriagemessage_pb.hxx.pb.h"

class CMarriageModule : public CLogicModule , public CSingleton< CMarriageModule >
{ 
public:
	CMarriageModule():CLogicModule(sModuleName)
	{
		if ( CObj::msCreateMode )
		{						
			Initialize();
		}
		else
		{
			
		}
	}
	 ~CMarriageModule(){ }
public:	
	static unsigned int CountSize();
	static char	sModuleName[ NAME_LENGTH ];	
public:	
	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffsekt );

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
	virtual void OnLoadConfig( );	

	// ��ʱ��Ϣ
	virtual void OnTimeoutMessage( CMessage* pMessage );

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return mCampInfoComplete&&mMarriageComplete; }
public:
	int Initialize();		
		
public:		
	// ���������Ϣ����
	void OnMessageApplyMarryRequest( CEntityPlayer *pPlayer, CMessage* pMessage );
	
	// ���������Ϣ��Ӧ
	void SendApplyMarryResponse( CEntityPlayer *pPlayer, int nErrcode );

	// ���������Ϣ֪ͨ
	void SendMarryRequestNotify( CEntityPlayer *pPlayer, const char *pName, int nRoleID, int nWeddingTime, int nWeddingModule );
	
	// �𸴽�����Ϣ����
	void OnMessageReplyMarryRequest( CEntityPlayer *pPlayer, CMessage* pMessage );
	
	// �𸴽�����Ϣ��Ӧ
	void SendReplyMarryResponse( CEntityPlayer *pPlayer, int nErrcode, const char *pSpouseName = NULL, int nResult = 0, int nMarriageStatus = 0 );
	
	// ��ҽ��ɹ�����Ϣ
	void SendPersonalMarriedNotify( const char *pGroomName, const char *pBrideName, int nServerSequence );

	// ��������
	void SendMarriageTipsNotify( CMarriageInfo *pMarriageInfo, CEntityPlayer *pPlayer = NULL );

	// ��ʼ�������Ϣ����
	void OnMessageBegginWeddingRequest( CEntityPlayer *pPlayer, CMessage* pMessage );
	
	// ��ʼ�������Ϣ��Ӧ
	void SendBeginWeddingResponse( CEntityPlayer *pPlayer, int nErrcode );

	// ��ʼ��������һ������ʼ�����֪ͨ
	void SendMarriageNoticeNotify( CEntityPlayer *pPlayer );		

	// ����ż��ʼ�������Ϣ����
	void OnMessageReplyBeginWeddingRequest( CEntityPlayer *pPlayer, CMessage* pMessage );
	
	// ����ż��ʼ�������Ϣ��Ӧ	
	void SenndReplyBeginWeddingResponse( CEntityPlayer *pPlayer, int nErrcode );

	// ����ʼ��֪ͨ(ȫ��֪ͨ)	
	void SendWeddingNotify( CMarriageInfo *pMarriageInfo );	

	// �������õ�֪ͨ
	void SendEnterMarriageHallNotify( CEntityPlayer *pPlayer );
	
	// �Ƿ�ͬ��������õĴ�����
	void OnMessageReplyEnterMarriageHallRequest( CEntityPlayer *pPlayer, CMessage* pMessage );
	
	// �Ƿ�ͬ��������õĴ𸴻�Ӧ
	void SendReplyEnterMarriageHallResponse( CEntityPlayer *pPlayer, int nErrcode );

	// ��������������õ���Ϣ����
	void OnMessageNewlywedEnterHallRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��������������õ���Ϣ��Ӧ
	void SendNewlywedEnterHallResponse( CEntityPlayer *pPlayer, int nErrcode, int nWeddingModule, int nBaitangEnd );

	// ӵ��������������������õ���Ϣ����
	void OnMessageGuestEnterHallRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ӵ��������������������õ���Ϣ��Ӧ
	void SendGuestEnterHallResponse( CEntityPlayer *pPlayer, int nErrcode );

	// ���˰��õ�����
	void OnMessageBaiTangRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ���˰��õĻ�Ӧ
	void SendBaitangResponse( CEntityPlayer *pPlayer, int nErrcode );

	// ���˰��õ���Ϣ֪ͨ		
	void SendBaitangNotify( CEntityPlayer *pPlayer, const char *pGroomName, const char *pBrideName, int nGroomEntityID, int nBrideEntityID );

	// �����������Ϣ����
	void OnMessagePutKeepsakeRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// �����������Ϣ��Ӧ
	void SendPutKeepsakeResponse( CEntityPlayer *pPlayer, int nErrcode, int nIndex );
	
	// ���ͷ��������֪ͨ
	void SendTimeToPutKeepSakeNotify( CMarriageInfo *pMarriage, CEntityPlayer *pPlayer = NULL );

	// �������������
	void OnMessageExchangeKeepsakeRequest( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ��������Ļ�Ӧ��Ϣ
	void SendExchangeKeepsakeResponse( CEntityPlayer *pPlayer, int nErrcode );

	// ���������֪ͨ
	void SendExchangeKeepsakeNotify( const char *pGroomName, CItemObject *pBrideKeepsake, const char *pBrideName, CItemObject *pGroomKeepsake );

	// ������Ϣ����
	void OnMessageDivorceRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������Ϣ��Ӧ
	void SendVivorceResponse( CEntityPlayer *pPlayer, int nErrcode );

	// ������Ϣ֪ͨ	
	void BroadCastDivorce( CEntityPlayer *pPlayer, const char *pGroomName, const char *pBrideName, int nGroomCharID, int nBrideCharID );
	
	// ������ż�������Ϣ֪ͨ
	void SendDivorceNotify( CEntityPlayer *pPlayer, int nRoleID );

	// �����֪ͨ(�Է��Ƿ�ͬ��)
	void SendMarryResultNotify( CEntityPlayer *pPlayer, int nResult, const char *pSpuseName, int nMarriageStatus );
	
	// ��ʼ����Ľ��֪ͨ(��ż�Ƿ�ͬ��)	
	void SendBeginWeddinResultNotify( CEntityPlayer *pPlayer, int nResult );
	
	// ��ȡ����Ӫ������Ϣ����Ϣ����
	void OnMessageGetCampMarriageInfoRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
			
	// ����Ӫ������Ϣ����Ϣ��Ӧ	
	void SendGetCampMarriageInfoResponse( CEntityPlayer *pPlayer );	
	
	// ���͸��˵Ļ�����Ϣ
	void SendPersonMarriageInfoNotify( CEntityPlayer *pPlayer, CMarriageInfo *pMarriageInfo );
	
	// ��ż����·����Ϣ
	void OnRoterMessageSpouseDivorce( CMessage *pMessage );
	
	// ���npc�ķ���;���
	bool CheckMarriageNpc( CEntityPlayer *pPlayer, int nEntityID );
	
	// ʹ��ϵͳ����������
	void OnMessageUseSysInvitation( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ����ʹ��ϵͳ�����Ļ�Ӧ��Ϣ
	void SendUseSysInvitationResponse( CEntityPlayer *pPlayer, int nErrcode );
	
	// �������˽��ɹ���֪ͨ
	void SendNewlyMarriedNotify( CMarriageInfo *tpMarriage );
	
	// ��ʼ����һ�����Ϣ����
	void OnMessageStartKeepsakeExchangeRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ���Ϳ�ʼ����һ�����Ϣ��Ӧ
	void SendStartKeepsakeExchangeResponse( CEntityPlayer *pPlayer, int nErrcode );
	
	// ��ֹ����һ�����Ϣ����
	void OnMessageStopKeepsakeRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ֹ����һ�����Ϣ��Ӧ
	void SendStopKeepsakeResponse( CEntityPlayer *pPlayer, int nErrcode );
	
	// ������ֹ�������Ϣ֪ͨ
	void SendStopKeepsakeNotify( CEntityPlayer *pPlayer );
	
	// �����һ�������
	void OnMessageInvitationExchange( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ���������һ�����Ϣ��Ӧ
	void SendInvitationExchangeResponse( CEntityPlayer *pPlayer, int nErrcode );
	
	// �������ｻ���Ľ��֪ͨ
	void SendKeepsakeExchangeResultNotify( CMarriageInfo *pMarriage, int nGroomItemID, int nBrideItemID, CEntityPlayer *pPlayer = NULL );
	
	// ���ｻ��
	void InvitationExchange( CEntityPlayer *pPlayer, int nItemIndex );
	
	// �����͵�����npc����Ϣ
	void OnMessageTeletoMarriageNpcRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ���������͵�����npc����Ϣ��Ӧ
	void SendTeletoMarriageNpcResponse( CEntityPlayer *pPlayer, int nErrcode );
	
	// ���²���������Ϣ����
	void OnMessageReviewWeddingRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ���²���������Ϣ��Ӧ
	void SendReviewWeddingResponse( CEntityPlayer *pPlayer, int nErrcode );
	
	// ���²���������Ϣ֪ͨ
	void SendReviewWeddingNotify( CMarriageInfo *pMarriage );
	
	// ������»��߲������
	void PlayerReviewWedding( CEntityPlayer *pPlayer, int nWeddingModule, int nTimeID, int nDayID );			
		
public:
	
	// ���������
	void PlayerMarryApply( CEntityPlayer *pPlayer, int nWeddingTime, int nWeddingTimeLength, int nWeddingModule );
	
	// ��Ҵ𸴽������
	void PlayerReplyMarry( CEntityPlayer *pPlayer, int nResult );
	
	// ��ҿ�ʼ�����������Ϣ
	void PlayerBeginWedding( CEntityPlayer *pPlayer, CEntity *pNpc = NULL );
	
	// ��Ҵ𸴻���ʼ
	void PlayerReplyWeddingBegin( CEntityPlayer *pPlayer, int nResult );
	
	// ��ҿ�ʼ��������
	void PlayerEnterMarriageHall( CEntityPlayer *pPlayer, bool bNewly = true );
	
	// ���������ʱ��
	void OnTimeOutWeddingEnd( CTimerItem* pTimer );
	
	// ��������
	void EndWedding();
	
	// �������ʧЧ
	void OnTimeOutMarryApplyTimeOut( CTimerItem* pTimer );
	
	// ���ͻ���֪ͨ
	void OnTimeWeddingNotify( CTimerItem* pTimer );
	
	// �������н���
	void OnTimeOutWeddingOnStreet( CTimerItem* pTimer );
	
	// ��Ұ���
	void PlayerBaitang( CEntityPlayer *pPlayer, CEntity *pEntity );
	
	// ��һ�ȡ�����Ϣ�б�
	void PlayerGetMarriageInfo( CEntityPlayer *pPlayer );
	
	// ��ҷ������������
	void PlayerPutKeepsake( CEntityPlayer *pPlayer, int nKeepSeekIndex );
	
	// �������������
	void PlayerExchangeKeepsake( CEntityPlayer *pPlayer );
	
	// �����������
	void PlayerDivorce( CEntityPlayer *pPlayer );
	
	// �������ȡ������
	void PlayerCancelWedding( CEntityPlayer *pPlayer );
	
	// ʹ��ϵͳ����
	void UseSysInvitation( CEntityPlayer *pPlayer, int nIndex, const char *pName );
	
	// �����ͨ��ϵͳ�ʼ���������
	void SendInvitationByMail( CEntityPlayer *pPlayer, int nSysInvitationIndex, int nRoleID, const char *pName );
	
	// ��ȡ��ռ�õ�ʱ�����Ϣ
	PBMarriageInfo *GetSysWeddingTimeUsed( CMarriageInfo *tpMarriageInfo, PBMarriageList &rTimeList, time_t nTime );	
	
	// �����ƶ�npc	
	
	// ��ʼ��ϵͳ����ʱ��
	int InitializeSysWeddingInfo( const char *pFileName );		
	
	// ��ʼ��npc���ƶ�·��
	int InitializeWeddingNpcPath( const char *pFileName );	
	
	// �����ҵĻ�����Ϣ
	int ClearWeddingInfo( CMarriageInfo *pMarriage );
	
	// ��������ͼ����ҷ�����Ϣ
	void SendMapMessage( int nMapID, CMessage *pMessage );
	
	// ��ȡnpc��ͷ��Ӧ����ʾ����������
	const char *GetNewlyName( CEntity *tpEntity );
	
public:
	// ������������ݿ���Ϣ
	void CreatMarriageDBInfo( CMarriageInfo *tpMarriageInfo );
	
	// �����������ݿ���Ϣ�ķ�����Ϣ
	void OnSessionCreatMarriageDBInfo( CMessage *pMessage, int nParam1, int nParam2 );	
	
	// ������״̬
	void CheckWeddingStatus();	
	
	// ������npc���ƶ����
	void CheckWeddingNpc();
	
	// ��������������Ϣ
	void CreatWeddingInfo( CMarriageInfo *pMarriageInfo );
	
	// ��ʼ������
	void InitialWeddingHall( CMarriageInfo *tpMarriageInfo );
	
	// ���ͻ��������֪ͨ
	void SendWeddingEndNotify( CMarriageInfo *pMarriageInfo );
	
	// ������״̬
	bool CheckNewlyBaitangStatus( );

public:	
	// ���ػ�����Ļ�����¼����
	void LoadMarriageCountFromDB( int nCampID );
	
	// ���ػ�����Ļ�����¼���������ݿⷵ����Ϣ
	void OnSessionLoadMarriageCountFromDB( CMessage *pMessage, int nParam1, int nParam2 );
	
	// ���ػ��������ݿ���Ϣ
	void LoadMarriageInfoFromDB( int nTotalCount, int nLoadCount );	
	
	// ���ػ������ݿ���Ϣ�ķ�����Ϣ
	void OnSessionLoadMarriageInfoFromDB( CMessage *pMessage, int nParam1, int nParam2 );	
	
	
	// ��ȡ���ݿ�����Ӫ��Ϣ
	void LoadCampInfo( int nCampID );
	
	// ��ȡ���ݿ�����Ӫ��Ϣ�ķ�����Ϣ
	void OnSessionLoadCampInfo( CMessage *pMessage, int nParam1, int nParam2 );
	
	// ������ҵĻ�����Ϣ
	void LoadPlayerMarriageInfo( CEntityPlayer *pPlayer );
	
	// ������ҵĻ�����Ϣ�����ݿⷵ����Ϣ
	void OnsessionLoadPlayerMarriageInfo( CMessage *pMessage, int nRoleID, int nParam2 );
	
	// ������Ӫ��Ϣ��
	void CreatCampDBInfo( int nCampID, int nMarriedNum );
	
	// ������Ӫ��Ϣ��Ļ�Ӧ��Ϣ
	void OnSessionCreatCampDBInfo( CMessage *pMessage, int nCampID, int nParam2 );
	
	// ������ҽ�ɫ��Ϣ�еĻ���ID�ֶ�
	void UpDatePlayerMarriageID( int nRoleID, int nMarriageID );
	
	// ������ҵĻ�����Ϣ���ݿ�
	void UpDateMarriageInfo( CMarriageInfo *tpMarriageInfo );
	
	// �������ݿ����Ӫ��Ϣ
	void UpDateCampDBInfo( CCampInfo *tpCampInfo );
	
	// ɾ�����ݿ����Ӫ��Ϣ
	void DeleteMarriageDBInfo( CMarriageInfo *tpMarriage );
	
	// ��ʼ����
	void StartWedding( CMarriageInfo *pMarriageInfo, EWeddingStartType emType );
	
private:
	bool mMarriageComplete;
	bool mCampInfoComplete;	
	CWTimer mWeddingNpcTimer;
	CWTimer mMarriageStatusTimer;
	CWTimer mBaitangTimer;	
};