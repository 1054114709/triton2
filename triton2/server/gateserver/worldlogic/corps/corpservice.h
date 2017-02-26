#pragma once
#include "corpstype.h"
#include "familytype.h"
#include "module_manager.h"
#include "entity.h"
#include "familydbinfo_pb.hxx.pb.h"
#include "corpsinfo_pb.hxx.pb.h"
//#include "gatelogic.h"
#include "family.h"
#include "union.h"
#include "corps.h"

using namespace GateServer;
class SysProtocol;

enum EM_DB_TABLE_TYPE
{
	TAB_BID = 1,
	TAB_NPC = 2,
	TAB_BATTLE = 3,
	TAB_CORPS = 4,
	TAB_UNOIN = 5
};
enum EM_CORPSBOSS_TYPE
{
	CORPS_BOSS_TYPE_ERROR	= 0,
	CORPS_COMMON_BOSS_TYPE	= 1,
	CORPS_HARD_BOSS_TYPE	= 2,
};


class CCorpservice : public CDataModule, public CSingleton< CCorpservice > 
{	
public:
	void OnLaunchServer();
	void OnExitServer();
	void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );
	void OnMessage( int nServerID, CMessage* pMessage );
	void OnSeverMessage(int nServerID, CMessage* pMessage );
	CCorpservice();
	virtual ~CCorpservice(){ };
	int Initialize();
	int Resume(); 
	virtual void OnNewDayCome(); 
	virtual void OnNewWeekCome();
	static unsigned int CountSize();  	

	virtual bool IsLaunched() { return mIsLaunched; }
	
public:
	// �������ŵ�����
	void OnMessageCreatCorps( int nServerID, CMessage* pMessage );
	
	// ���������ŵ�������Ϣ
	void OnMessageApplyCorps( int nServerID, CMessage* pMessage );
	
	// �ظ��������������ŵ���Ϣ����
	void OnMessageReplyMemberApply( int nServerID, CMessage* pMessage );	
	
	// ������������ŵ���Ϣ����
	void OnMessageInviteCorpsMember( int nServerID, CMessage* pMessage );
	
	// �𸴾����������Ϣ����
	void OnMessageReplyCorpsInvite( int nServerID, CMessage* pMessage );
	
	// �����뿪���ŵ���Ϣ����	
	void OnMessageLeaveCorps( int nServerID, CMessage* pMessage );
	
	// �Ӿ����߳��������Ϣ����
	void OnMessageKickFamily( int nServerID, CMessage* pMessage );	
	
	// ��ȡ���ż����Ա��Ϣ������
	void OnMessageGetCorpsFamiyInfo( int nServerID, CMessage* pMessage );
	
	// ��ȡ����������Ϣ��������Ϣ
	void OnMessageGetCorpsPropertyInfo( int nServerID, CMessage* pMessage );
	
	// �ı���Ź������Ϣ����
	void OnMessageChangeCorpsBulletin( int nServerID, CMessage* pMessage );
	
	// �ı�����������Ϣ����
	void OnMessageChanggeCorpsHeader( int nServerID, CMessage* pMessage );
	
	// ��ȡ�����б����Ϣ����
	void OnMessageGetCorpsApplyList( int nServerID, CMessage* pMessage );
	
	// ��ɢ���ŵ���Ϣ����
	void OnMessageDisbandCorps( int nServerID, CMessage* pMessage );
	
	// ȡ����ɢ���ŵ���Ϣ����
	void OnMessageCancelCorpsDisband( int nServerID, CMessage* pMessage );
	
	// ������������б����Ϣ
	void OnMessageClearCorpsApply( int nServerID, CMessage* pMessage );	 
	
	// ��ȡ������Ϣ�б����Ϣ
	void OnMessageGetCorpsList( int nServerID, CMessage* pMessage );
		
	// ˢ�¾�����Ϣ����Ϣ����
	void OnMessageRefreshCorpsInfo( int nServerID, CMessage* pMessage );

	//-------------------------------------------------------------------------
	/// ��ѯָ��NPC�ľ����б�
	void OnMessageQueryBidRankRequest( int nServerID, CMessage* pMessage );

	//-------------------------------------------------------------------------
	/// ���ž�������
	void OnMessageCorpsBidRequest( int nServerID, CMessage* pMessage );

	//-------------------------------------------------------------------------
	/// ����ʱ�����֪ͨ
	void OnMessageBidTimeOutRequest( int nServerID, CMessage* pMessage );

	void OnMessageSelectBattleFamily( int nServerID, CMessage* pMessage );

	void OnMessageSelectBattleMember( int nServerID, CMessage* pMessage );

	//-------------------------------------------------------------------
	/// ����/�رշ���
	void OnMessageOperateRoomRequest( int nServerID, CMessage* pMessage );

	/// ����/������ս
	void OnMessageChallegeRequest( int nServerID, CMessage* pMessage );

	/// ������ս
	void OnMessageReplyChallegeRequest( int nServerID, CMessage* pMessage );

	/// ��ȡ��ս�����з����б�
	void OnMessageQueryRoomRequest( int nServerID, CMessage* pMessage );
	
	/// ��ȡ�Լ����������ŷ������ս���б�
	void OnMessageQueryChallegeRequest( int nServerID, CMessage* pMessage );
	
	/// ��ȡ�Ա����ŵ���ս�б�
	void OnMessageQueryRecChallegeRequest( int nServerID, CMessage* pMessage );
	//-------------------------------------------------------------------

	// ������ҹ��׶�
	void OnMessagChangeCorpsContribute( CMessage* pMessage );

	// �ı���Ž�Ǯ
	void OnMessageChangeCorpsMoney( CMessage* pMessage );
	
	// �ı������ҫ
	void OnMessageChangeCorpsGlory( CMessage* pMessage );

	// �ı���Ųɼ���Ծ��
	void OnMessageChangeCorpsCollectActive( int nServerID, CMessage* pMessage );
	
	// ����Ƶ����Ϣ
	void OnChatMsg( int nServerID, CMessage* pMessage );	
	
	// ���þ��ų�Աְλ����Ϣ���� 
	void OnMessageSetCorpsPost( int nServerID, CMessage* pMessage );

	// �������ŵ���Ϣ����
	void OnMessageLevelUPCorps( int nServerID, CMessage* pMessage );

	// ���׾��Ž�Ǯ����Ϣ����
	void OnMessageContributeCorpsMoney( int nServerID, CMessage* pMessage );

	//  ��������Ź��׽�Ǯ����Ϣ����
	void OnMessageFamilyContributeMoney( int nServerID, CMessage* pMessage );

	// ���þ��ų�Ա�ƺŵ���Ϣ����
	void OnMessageSetMemberName( int nServerID, CMessage* pMessage );

	
	//-------------------------------------------------------------------
	// �������ս�����
	void OnMessageBattleResultRequest( int nServerID, CMessage* pMessage );

	/// ������ų��������
	void OnMessageBattleFlagRequest( int nServerID, CMessage* pMessage );

	/// ��ʼս��
	void OnMessageStartBattleRequest( int nServerID, CMessage* pMessage );

	void OnMessageAbortBattleCityRequest( int nServerID, CMessage* pMessage );

	void OnFireCorpsBattleEvent( int nRoleID, int nServerID );

	void OnDoBattleResultEvent( CCorps* npWinCorps, int nNpcID, int nMapID, CCorps* npLosCorps = NULL );
	//-------------------------------------------------------------------

	// ��ѯ����npc��������Ϣ����
	void OnMessageQueryCorpsWelfare( int nServerID, CMessage* pMessage );
	
	// ��ȡ����npc��������Ϣ����
	void OnMessageObtainCorpsWelfare( int nServerID, CMessage* pMessage );
	
	// ��ȡ���Ž�Ǯ����Ϣ����
	void OnMessageGetCorpsMoney( int nServerID, CMessage* pMessage );
	
	// ������ź������Ϣ����
	void OnMessageBuyCorpsItem( int nServerID, CMessage* pMessage );

	// �������������������Ϣ
	void OnMessageApplyUnion( int nServerID, CMessage* pMessage );

	// �ظ��������������������Ϣ����
	void OnMessageReplyUnionApply( int nServerID, CMessage* pMessage );	

	// ������ż�����������Ϣ����
	void OnMessageInviteUnionMember( int nServerID, CMessage* pMessage );

	// �������������Ϣ����
	void OnMessageReplyUnionInvite( int nServerID, CMessage* pMessage );

	// �����뿪��������Ϣ����	
	void OnMessageLeaveUnion( int nServerID, CMessage* pMessage );

	// �������߳����ŵ���Ϣ����
	void OnMessageKickCorps( int nServerID, CMessage* pMessage );	

	// ������������
	void OnMessageCreateUnion( int nServerID, CMessage* pMessage );

	void OnMessageMakeUnion( int nServerID, CMessage* pMessage );

	// ���������Ϣ����
	void OnMessageGetUnionInfo( int nServerID, CMessage* pMessage );

	// ��ɢ��������
	void OnMessageDismissUnion( int nServerID, CMessage* pMessage );

	// ������������б�����
	void OnMessageUnionApplyList( int nServerID, CMessage* pMessage );

	// ������������б�����
	void OnMessageAllUnionList( int nServerID, CMessage* pMessage );

	//void OnMessageGetOtherMemberList( int nServerID, CMessage* pMessage );

	void OnMessageGetAllMapList( int nServerID, CMessage* npMessage );

	// ��ѯ���˲�ս�б� [12/16/2009 Macro]
	void OnMessageGetUnionBattleList( int nServerID, CMessage* npMessage );


	// ����ս��Ǯ�ع� [3/10/2010 Administrator]
	void OnMessageRollCorpsMoney( int nServerID, CMessage* npMessage );

	void OnEventDeleteRoom( int nRoleID, int nServerID );

	// ��������
	void OnEventCityUpgrade( CCorps* npCorps, int nServerID );

	// ���˾��۽�������
	int OnEventUnionBattleTimeOut( int nMapID, CCorps* npCorps );
	
	// ���˿�ս����
	int OnEventGetUnionBattleList( int* npList, int& nNum, CCorps* npCorps, int nMapID );

	//// ����ռ��һ���ǳ� [1/27/2010 Macro]
	//int OnEventAddMapOwn( int nCorpsID, int nNpcID );

	//// �Ƴ�ռ���һ���ǳ� [1/27/2010 Macro]
	//int OnEventDelMapOwn( int nCorpsID, int nNpcID );
	 
	// ������������
	void OnMessageAppointPrince( int nServerID, CMessage* npMessage );

	// Ǩ��
	void OnMessageMoveCapital( int nServerID, CMessage* npMessage );

	// ������ɫ����
	void OnMessageSetCorpsColor( int nServerID, CMessage* npMessage );

	// �������˸���
	void OnMessageChangeUnionName( int nServerID, CMessage* npMessage );
	
	// ��ȡ������Ʒ�б��������Ϣ
	void OnMessageGetCorpsGoodsList( int nServerID, CMessage* pMessage );
	
	// ��ȡ���Ŷһ���Ʒ�б����Ϣ����
	void OnMessageGetCorpsExchangeGoodsList( int nServerID, CMessage* pMessage );
	
	// ���ͻ�ȡ������Ʒ�б����Ϣ��Ӧ
	void SendResponseGetCorpsGoodsList( int nServerID, int nErrcode, int nRoleID, int nEntityID, PBLeagueShopInfo &rLeagueShop, int nNpcTmpID );
	
	// ���ͻ�ȡ���ſɶһ���Ʒ�б����Ϣ����
	void SendResponseGetCorpsExchangeGoodList( int nServerID, int nErrcode, int nRoleID, int nEntityID, PBLeagueShopInfo &pbLeagueShop, int nNpcTmpID );
	
	// ���;�����Ʒ�����仯��֪ͨ
	void SendNotifyChangeCorpsGoodsList( int nCorpsID, int nNpcTmpID, int nItemID, int nItemNum, int nComposeID = 0 );
	
	// ���о��Ŷһ�����Ϣ����
	void OnMessageCorpsExchange( int nServerID, CMessage *pMessage );
	
	// ���;��Ŷһ��Ļ�Ӧ��Ϣ
	void SendResponseCorpsExchange( int nServerID, int nErrcode, int nRoleID, int nComposeID, int nNpcTmpID, int nItemNum );
	
	// ���;��Ŷһ������仯��֪ͨ
	void SendNotifyChangeCorpsExchangeGoodsList( int nCorpsID, CGoodSInfo *pGoodInfo, int nNum );
	
	// ����ʹ�þ����ع���Ʒ��֪ͨ
	void SendNotifyUseCorpsLeagueItem( int nCorpsID, CGoodSInfo *pGoodInfo, int nNum, int nRoleID, const char *pName );
	
	// ���Ӿ��ſɶһ���Ʒ����Ϣ֪ͨ
	void OnMessageAddCorpsExchangeItem( int nServerID, CMessage *pMessage );

	// �������սս������
	void OnMessageLoginBattleRequest( int nServerID, CMessage *npMessage );

	// ����ս��֪ͨ�ͻ���ս����
	void OnMessageSendBattleMapRequest( int nServerID, CMessage* npMessage );

	// ǿ��ս����������
	void OnEventBattleOver( int nWinCamp, KEY_TYPE nKey );
	
	// ����boss��ս�����ı�
	void OnMessageChangeBossTimes( int nServerID, CMessage* npMessage );
	
	// ��������ֵ�ı�
	void OnMessageChangeBossRefineValue( int nServerID, CMessage * npMessage );
	// ����boss��������
	int StartCorpBossRepetion(int  vCorpsID, int vBossID, int vBossType);
public:	
	// �������ŵĻ�Ӧ��Ϣ		
	void SendResponseCreatCorps( int nServerID, int nRoleID, int nRet, int nCorpsID, const char *pCorpsName, int nEntityID, int nCorpsColor );
	
	// ���������ŵĻ�Ӧ��Ϣ
	void SendResponseApplyCorps( int nServerID, int nRoleID, int nRet, int nCorpsID, const char *pCorpsName, int nEntityID = 0  );
	
	// �м������������ŵ���Ϣ֪ͨ	
	void SendNotifyCorpsMemberApply( CGatePlayer *pPlayer, int nRoleID, FamilyData &pbFamilyData );
	
	// �ظ��������������ŵ���Ϣ��Ӧ
	void SendResponseReplyCorpsMemberApply( int nServerID, int nRoleID, int nRet, int nResult, int nFamilyID, int nEntityID = 0 );
	
	// ���������ŵĽ��֪ͨ 
	void SendNotifyApplyCorpsResult( CGatePlayer *pPlayer, int nRoleID, int nRet, int nCorpsID, const char *pCorpsName, int nUnionID = 0, const char *pUnionName = NULL );
	
	// ������������ŵ���Ϣ��Ӧ	
	void SendResponseInviteCorpsMember( int nServerID, int nRoleID, int nRet, const char *pFamilyName, int nEntityID );
	
	// ���������ŵ���Ϣ֪ͨ	 	
	void SendNotifyCorpsInvite( CGatePlayer *pPlayer, int nRoleID, PBCorpsBasicInfo &pbCorpsInfo, int nInvitingID, const char * pInvitingName );
	
	// �𸴾����������Ϣ�ظ�
	void SendResponseReplyCorpsInvite( int nServerID, int nRoleID, int nRet, int nResult, int nCorpsID, const char *pCorpsName, int nEntityID, int nUnionID = 0, const char *pUnionName = NULL );
	
	// ������������ŵĽ��֪ͨ
	void SendNotifyCorpsInviteResult( CGatePlayer *pPlayer, int nRoleID, int nResult, const char *pFamilyName );
	
	// �м��������ŵ���Ϣ֪ͨ	 	
	void SendNotifyFamilyJoinCorps( PBCorpsMember &pbCorpsMember, int *pRoleIDList, int vRoleNum );
		
	// �����뿪���ŵ���Ϣ��Ӧ	 
	void SendResponseLeaveCorps( int nServerID, int nRoleID, int nRet, int nEntityID );
	
	// �����뿪���ŵ���Ϣ֪ͨ	
	void SendNotifyFamilyLeaved( int nFamilyID, const char *pFamilyName, int *pRoleIDList, int nRoleNum );
	
	// �Ӿ����߳��������Ϣ��Ӧ
	void SendResponseKickFamily( int nServerID, int nRoleID, int nRet, int nFamilyID, const char *pFamilyName, int nEntityID );
	
	// ����Ӿ������汻�ߵ���֪ͨ		
	void SendNotifyFamilyKicked( int nFamilyID, const char * pFamilyName, int *pRoleIDList, int tNum );
	
	// ��ȡ���ż����Ա��Ϣ�Ļ�Ӧ��Ϣ  	
	void SendResponseGetCorpsFamilyInfo( int nServerID, int nRoleID, PBCorpsMemberList &pbCorpsMemberList, int nEntityID );
	
	// ��ȡ����������Ϣ�Ļ�Ӧ��Ϣ	
	void SendResponseGetCorpsPropertyInfo( int nServerID, int nRoleID, CorpsProperty &pbCorpsProperty, int nEntityID );
	
	// �ı���Ź������Ϣ�ظ�
	void SendResponseChangeCorpsBulletin( int nServerID, int nRoleID, int nRet, const char *pBulletin, int nEntityID );
	
	// �ı���Ź������Ϣ֪ͨ
	void SendNotifyChangeCorpsBulletin( const char *pBulletin, int *pRoleIDlist, int tNum );
			
	// �ı�����������Ϣ�ظ�
	void SendResponseChangeCorpsHeader( int nServerID, int nRoleID, int nRet, int nMemberID, const char *pMemberName, int nEntityID );

	// �ı�����������Ϣ֪ͨ
	void SendNotifyChangeCorpsHeader( int nHeaderID, const char *pHeaderName, int nMemberID, const char *pMemberName, int *pRoleIDList, int nNum );

	// ��ȡ�����б����Ϣ��Ӧ 	
	void SendResponseGetCorpsApplyList( int nServerID, int nRoleID, int nRet, PBCorpsApplyList &pbApplyList, int nEntityID );

	// ��ɢ���ŵ���Ϣ��Ӧ
	void SendResponseDisbandCorps( int nServerID, int nRoleID, int nRet, int nEntityID );
	
	// ��ɢ���ŵ���Ϣ֪ͨ
	void SendNotifyDisbandCorps( int *pRoleIDList, int tNum );
	
	// ȡ����ɢ���ŵ���Ϣ����
	void SendResponseCancelCorpsDisband( int nServerID, int nRoleID, int nRet, int nEntityID = 0 );
	
	// ���;��ŵ���Ϣ֪ͨ
	void SendCorpsNotifyMsg( CMessage *pMessage, int *pRoleIDList, int vRoleNum );
	
	// ����������������б����Ϣ��Ӧ
	void SendResponseClearCorpsApply( int nServerID, int nRet, int nRoleID, int nEntityID );
	
	// ����ˢ�¾�����Ϣ�Ļ�Ӧ��Ϣ
	void SendResponseRefreshCorpsInfo( int nServerID, int nRoleID, int nEntityID, PBCorpsMemberList &pbCorpsMemberList );
	
	// ���ͻ�ȡ������Ϣ�Ļ�Ӧ��Ϣ
	void SendResponseGetCorpsList( int nServerID, int nRoleID, int nEntityID, CorpsInfoList &pbCorpsList, int nCurPage, int nTotalPage );
	
	
	// ���þ��ų�Աְλ����Ϣ��Ӧ	
	void SendResponseSetCorpMemberPost( int nServerID, int nRoleID, int nErrcode, int nMemberID, int nPost, int nEntityID = 0 );  

	// �������ŵ���Ϣ��Ӧ
	void SendResponseLevelUPCorps( int nServerID, int nErrcode, int nLevel, int nRoleID, int nEntityID = 0 );  

	// ���׾��Ž�Ǯ����Ϣ��Ӧ
	void SendResponseContributeCorpsMoney( int nServerID, int nErrcode, int nMoney, int nRoleID, int nEntityID = 0 );  

	// ��������Ź��׽�Ǯ����Ϣ��Ӧ
	void SendResponseFamilyContributeMoney( int nServerID, int nErrcode, int nMoney, int nRoleID, int nEntityID = 0 );  

	// ���þ��ų�Ա�ƺŵ���Ϣ��Ӧ
	void SendResponseSetMemberName( int nServerID, int nMemberID, const char *pName, int nRoleID, int nEntityID, int nErrcode );  

	// ���þ���ְλ��֪ͨ
	void SendNotifySetCorpsPost( int *pIDList, int nNum, int nManagerID, const char *pManagerName, int nMemberID, const char *pMemberName, int nOriginalPost, int nNewPost );

	// ����������֪ͨ
	void SendNotifyCorpsLevelUP( int *pIDList, int nNum, int nLevel, int nMoney, int nGlory, int nMaxFamilyNum, int nMaxGeneralNum, int nCounsellor, int nLevelMoney, int nLevelGlory );  
	
	// ���;��Ž�Ǯ�ı����Ϣ֪ͨ
	void SendNotifyCorpsMoneyChanged( int nCorpsID, int nCorpsMoney, int nRoleID, int nValue, int nReason = REASON_CONTRIBUTE, const char *pName = NULL );
																		  
	// ���;�����ҫ�ı����Ϣ֪ͨ
	void SendNotifyCorpsGlroyChangedNotify( int nCorpsID, int nCorpsGlroy, int nRoleID, int nValue, int nReason = REASON_NPCWELFARE, const char *pName = NULL );
	
	// ���;��ŵĸ��˹��׶ȸı����Ϣ֪ͨ
	void SendNotifyCorpsContributeChangedNotify( int nCorpsID, int nMemberContribute, int nRoleID, int nValue );

	// ���;��Ųɼ���Ծ�ȸı����Ϣ֪ͨ
	void SendNotifyCorpsCollectActiveChange( int nCorpsID, int nRoleID, int nActiveValue, int nValue=0, int nChangeType=0 );

	// ����pvp�ȼ�������֪ͨ	
	void SendNotifyCorpsPVPStarLevelUP( int nServerID );
	
	// ���;��ſ�����������Ϣ֪ͨ
	void SendNotifyCorpsCanLevelUP( int nCorpsID );

	// ���ŷ���������Ϣ֪ͨ
	void SendNotifyCorpsPublishTask( int nCorpsID );
	
	// ���ľ��Ž�Ǯ
	int ConsumeCorpsMoney( int nRoleID, int nMoney, int nReason = REASON_ACTIVIYCONSUME );
		
	// �����ų�Ա������Ϣ
	void SendCorpsMsg( int nRoleID, CMessage *pMessage );
	
	// �����ų�Ա������Ϣ
	void SendCorpsMsgByID( int nCorpsID, CMessage *pMessage );

	// ���;�������
	void SendCorpsProperty( int nCorpsID );
	
	// ���ͳƺű��ı��֪ͨ
	void SendNotifyCorpsTitleChanged( CGatePlayer *pPlayer, int nManagerID, const char *pManagerName, const char *pCorpsTitle );
	
	// ���͹�����ź������Ϣ��Ӧ
	void SendResponseBuyCorpsItem( CGatePlayer *pPlayer, int nErrcode, int nRedPaperID, int nRedPaperNum, int nEntityID = 0 );
	
	// ��ʼ��������Ϣ�б�
	int InitializeCorpsConfig();

	virtual void ReloadCfg( );

	// ���ʹ���������Ӧ
	void SendCreateUnionResponse( CGatePlayer *pPlayer, int vRoleID, int vResult, int vUnionID );

	// ���ʹ�������֪ͨ
	void SendCreateUnionNotify( int vServerID, int vRoleID, CUnion *pUnion );

	// ���ʹ���������Ӧ
	void SendMakeUnionResponse( CGatePlayer *pPlayer, int vRoleID, int vResult, int vOpType );

	// ���ʹ�������֪ͨ
	void SendMakeUnionNotify( CGatePlayer *pPlayer, int vRoleID, int vOpType, CCorps *pCorps );

	// ������������Ļ�Ӧ��Ϣ
	void SendResponseApplyUnion( int nServerID, int nRoleID, int nRet, int nUnionID, const char *pUnionName, int nEntityID = 0  );

	// ������������Ļ�Ӧ��Ϣ
	void SendResponseReplyApplyUnion( int nServerID, int nRoleID, int nRet, int nResult, int nCorpsID );

	// �о������������������Ϣ֪ͨ	
	void SendNotifyUnionMemberApply( CGatePlayer *pPlayer, int nRoleID, PBCorpsBasicInfo vInfo );	

	// ������ż�����������Ϣ��Ӧ	
	void SendResponseInviteUnionMember( int nServerID, int nRoleID, int nRet, const char *pCorpsName, int nEntityID );

	// ���������������Ϣ֪ͨ	 	
	void SendNotifyUnionInvite( CGatePlayer *pPlayer, int nRoleID, PBUnionBasicInfo &pbCorpsInfo, int nInvitingID, const char * pInvitingName );

	// �������������Ϣ�ظ�
	void SendResponseReplyUnionInvite( int nServerID, int nRoleID, int nRet, int nResult, int nUnionID, const char *pUnionName, int nEntityID );

	// ������ż��������Ľ��֪ͨ
	void SendNotifyUnionInviteResult( CGatePlayer *pPlayer, int nRoleID, int nResult, const char *pCorpsName );

	// �о��ż�����������Ϣ֪ͨ	 	
	void SendNotifyCorpsJoinUnion( PBCorpsBasicInfo CorpsInfo, int vUnionID, char *vUnionName, int *pRoleIDList, int vRoleNum );

	// �����뿪��������Ϣ��Ӧ	 
	void SendResponseLeaveUnion( int nServerID, int nRoleID, int nRet, int nEntityID );

	// �����뿪��������Ϣ֪ͨ	
	void SendNotifyCorpsLeaved( int nCorpsID, const char *pCorpsName, int *pRoleIDList, int nRoleNum );

	// �������߳����ŵ���Ϣ��Ӧ
	void SendResponseKickCorps( int nServerID, int nRoleID, int nRet, int nCorpsID, const char *pCorpsName, int nEntityID );

	// ���Ŵ��������汻�ߵ���֪ͨ		
	void SendNotifyCorpsKicked( int nCorpsID, const char * pCorpsName, int *pRoleIDList, int tNum );

	// ���ͻ��������Ӧ
	void SendGetUnionInfoResponse( CGatePlayer *pPlayer, int vRoleID, int vResult, CUnion *pUnion );

	// ���ͽ�ɢ������Ӧ
	void SendDismissUnionResponse( CGatePlayer *pPlayer, int vRoleID, int vResult );

	// ���ͽ�ɢ����֪ͨ
	void SendDismissUnionNotify( int nServerID, int vRoleID, int *vCorpsID, int vNum );

	// ���ͻ�����������б��Ӧ
	void SendUnionApplyListResponse( CGatePlayer *pPlayer, int vRoleID, CUnion *pUnion );

	// ��������������֪ͨ
	void SendNotifyUnionInviteResult( int nRoleID, int nResult, const char * pInvitedName );

	// �ı���ų�Ա����
	void ChangeCorpsCountry( int vMapID, int vCorpsID );

	// ����������֪ͨ
	void SendNotifyApplyUnion( int nServerID, int nRoleID, int nRet, int nUnionID, const char *pUnionName );

	void SendChangeUnionNameResponse( int nRoleID, int nRet );
	void SendChangeUnionNameNotify( int nRoleID, const char *pUnionName, const char *pUnionNotice );

	void SendBattleJoinNotice( int nServerID, int nNpcID, const char* npCorpsName, int nCharID, int nType );
	//�ı����boss��ս����
	void SendNotifyBossTimesChanged(int nCorpsID, int nBossID, int nTimes,int nValue, int nRoleId, int nReason, const char * pName  );

	//�ı���ŵ�����ֵ
	void SendNotifyBossRefineValueChanged( int nCorpsID, int nRefineValue, int nValue, int nRoleID, int nReason , const char *pName  );
	
	//���;���boss����������֪ͨ
	void SendNotifyCorpsBossRepetionOpen( int nCorpsID, int nBossId, int nRoleId , const char *pName );
	//�ж�corpsboss�� ����
	int  GetCorpsBossType(int nBossID );
	// ��ҽ������boss�Ļ�Ӧ
	void SendIntoCorpsBossRepetionResponse( int nRoleID, int nRet);

	void SendSummonCorpsBossRespones( int nRoleID, int nRet );
	void OnMessageSummonCorpsBoss( int nServerID, CMessage * npMessage );
	// ���;��Ÿ�������֪ͨ
	void SendNotifyCorpsBossRepetionEnd(int nCorpsID );
public:
	void LoadCorpsFromDB( int nStart, int nTotalCount );
	void OnSessionLoadCorps( CMessage* pMessage, int nStart, int nTotalCount );
	void OnSessionLoadCorpsBid( CMessage* pMessage, int nStart, int nTotalCount );
	void OnSessionLoadCorpsBattle( CMessage* pMessage, int nStart, int nTotalCount );
	void OnSessionLoadNpcStatus( CMessage* pMessage, int nStart, int nTotalCount );

	int OnSessionCreatCorpsDBInfo( CMessage* pMessage, int nCorpsObjID, int nRooterID );
	int OnSessionCreateUnionDBInfo( CMessage* pMessage, int nHeadID, int nUnionID );
	void LoadUnionFromDB( int nStart, int nCount );
	void OnSessionLoadUnion( CMessage* pMessage, int nStart, int nCount );
	void OnAGIPSessionCreateUnion(SysProtocol* pSysProto, int nObjectID, int nGroupType);
	void OnAGIPSessionCreateCorps(SysProtocol* pSysProto, int nObjectID, int nGroupType);

	void OnAGIPTimeoutCreateUnion(int nObjectID, int nGroupType);
	void OnAGIPTimeoutCreateCorps(int nObjectID, int nGroupType);
	
	void StartLoadAllFromDB(int _Type);
	void OnSessionGetDataNumFromDB( CMessage *pMessage, int nParam1, int nParam2, int nTableType );

	// �������õĻص�����
	static void LoadCorpConfigCallback(const char* pcConfigPath);

private: 
	CWTimer mUpdateTimer;		// ���������ݸ��µļ�ʱ��
	CWTimer mDisbandTimer;		// �����Ž�ɢʱ��ļ�ʱ��
	CWTimer mBattleNoticeTimer;	// ��ս֪ͨ��ʱ��
	CWTimer m_CheckNpcStateTimer; // ����սNPC״̬��鶨ʱ��
	bool	mIsLaunched;

	bool m_bMigratieMode;	//�ж��Ƿ�Ǩ������
};
