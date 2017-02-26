#pragma once			 

#include "servercore.h"
#include "servertool.h"
#include "property.h"
#include "familytype.h"
#include "corpstype.h"
#include "servermessage_pb.hxx.pb.h"

#define   SendCorpsMsgToGate( MsgHead, CorpsMsg, EntityPlayer  )	\
	CorpsMsg->clear_corphead();										\
	CorpsMsg->mutable_corphead()->set_roleid( EntityPlayer->GetCharID() );	\
	CorpsMsg->mutable_corphead()->set_entityid( EntityPlayer->GetEntityID() ); \
	CSceneLogic::GetSingleton().Send2Gate( MsgHead ) ;				   \

struct CorpsNpcInfo
{
	int mCorpsID;
	char mCorpsName[ MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES ];
};

class CCorpsModule : public CLogicModule, public CSingleton< CCorpsModule >
{	 
public:
	static char	sModuleName[ NAME_LENGTH ];

	typedef lk::hash_map< int , CorpsNpcInfo, MAX_CORPSNUM > CorpsNpcList;
	CorpsNpcList	mNpcList;

	bool			mNpcDataFlag;	// npc�����Ƿ�������ͬ��
public:
	CCorpsModule( ):CLogicModule( sModuleName )
	{ 
		mNpcList.initailize();
		mNpcDataFlag = false;
	}	
	~CCorpsModule( ){   } 
	static unsigned int CountSize(  );
public:		
	// ������Ϣ
	void OnGateMessage( CMessage *pMsg );
	
	// �������ŵ�����
	void OnMessageCreatCorps( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ���������ŵ�������Ϣ
	void OnMessageApplyCorps( CEntityPlayer *pPlayer, CMessage *pMessage );		
	
	// �ظ��������������ŵ���Ϣ����
	void OnMessageReplyCorpsMemberApply( CEntityPlayer *pPlayer, CMessage *pMessage );		

	// ������������ŵ���Ϣ����
	void OnMessageInviteCorpsMember( CEntityPlayer *pPlayer, CMessage *pMessage );			
	
	// �𸴾����������Ϣ����
	void OnMessageReplyCorpsInvite( CEntityPlayer *pPlayer, CMessage *pMessage );					

	// �����뿪���ŵ���Ϣ����
	void OnMessageFamilyLeaveCorps( CEntityPlayer *pPlayer, CMessage *pMessage );						
	
	// �Ӿ����߳��������Ϣ����
	void OnMessageKickFamily( CEntityPlayer *pPlayer, CMessage *pMessage );							

	// ��ȡ���ż����Ա��Ϣ������
	void OnMessageGetCorpsFamilyInfo( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��ȡ����������Ϣ��������Ϣ
	void OnMessageGetCorpsPropertyInfo( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// ��ȡ������ĳ������ĳ�Ա��Ϣ����Ϣ����
	void OnMessageGetCorpsFamilyMember( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// �ı���Ź������Ϣ����
	void OnMessageChangeCorpsBulletin( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// �ı�����������Ϣ����
	void OnMessageChangeCorpsHeader( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ȡ���ŵ������б�
	void OnMessageCorpsApplyList( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ɢ�������Ϣ����
	void OnMessageDisbandCorps( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ȡ�������ɢ����Ϣ
	void OnMessageCancelDisbandCorps( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������������б����Ϣ
	void OnMessageClearCorpsApply( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ˢ�¾�����Ϣ����Ϣ
	void OnMessageRefreshCorpsInfo( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ȡ������Ϣ�б�
	void OnMessageGetCorpsList( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��������������
	void OnMessageCreateUnion( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// �������������������Ϣ
	void OnMessageApplyUnion( CEntityPlayer *pPlayer, CMessage *pMessage );		

	// �ظ��������������������Ϣ����
	void OnMessageReplyUnionMemberApply( CEntityPlayer *pPlayer, CMessage *pMessage );		

	// ������ż�����������Ϣ����
	void OnMessageInviteUnionMember( CEntityPlayer *pPlayer, CMessage *pMessage );			

	// �������������Ϣ����
	void OnMessageReplyUnionInvite( CEntityPlayer *pPlayer, CMessage *pMessage );					

	// �����뿪��������Ϣ����
	void OnMessageCorpsLeaveUnion( CEntityPlayer *pPlayer, CMessage *pMessage );						

	// �������߳����ŵ���Ϣ����
	void OnMessageKickCorps( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// ��������������
	void OnMessageMakeUnion( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ����б������
	void OnMessageGetUnionInfo( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// ��ɢ����������
	void OnMessageDismissUnion( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ������������б������
	void OnMessageUnionApplyList( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��������б������
	void OnMessageAllUnionList( CEntityPlayer *pPlayer, CMessage *pMessage );

	// �������˸���
	void OnMessageChangeUnionName( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	
	// ���þ��ų�Աְλ����Ϣ���� 
	void OnMessageSetCorpsPost( CEntityPlayer *pPlayer, CMessage *pMessage );

	// �������ŵ���Ϣ����
	void OnMessageLevelUPCorps( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ���׾��Ž�Ǯ����Ϣ����
	void OnMessageContributeCorpsMoney( CEntityPlayer *pPlayer, CMessage *pMessage );

	//  ��������Ź��׽�Ǯ����Ϣ����
	void OnMessageFamilyContributeMoney( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// ���þ��ų�Ա�ƺŵ���Ϣ����
	void OnMessageSetMemberName( CEntityPlayer *pPlayer, CMessage *pMessage );		

	// ��ȡ����ս�������а���Ϣ
	void OnMessageGetCorpsBattleBidRank( CEntityPlayer *pPlayer, CMessage* pMessage );

	// ���۱���
	void OnMessageCorpsBattleBidRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ѡ���ս����
	void OnMessageSelectBattleFamilyRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ѡ���ս����
	void OnMessageSelectBattleMemberRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ʥ��̨
	void OnMessageMendShengHuoTaiRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ��ս��������Ϣ
	void OnMessageCorpsChallegeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ��������
	void OnMessageOperateRoomRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ��ս����
	void OnMessageChallegeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ��Ӧ��ս����
	void OnMessageReplyChallegeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ��ѯ�����б�����
	void OnMessageQueryRoomListRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ��ѯ��ս�б�����
	void OnMessageQueryChallegeListRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ��ѯ����npc��������Ϣ����
	void OnMessageQueryNpcWelfareRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ��ȡ����npc��������Ϣ����
	void OnMessageObtainNpcWelfareRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ��ȡ���Ž�Ǯ����Ϣ����
	void OnMessageGetCorpsMoneyRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ��ȡ������Ʒ�б����Ϣ����
	void OnMessageGetCorpsGoodsList( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ��ȡ���Ŷһ���Ʒ�б����Ϣ����
	void OnMessageGetCorpsExchangeGoodsList( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ��ȡ������Ʒ�б����Ϣ����
	void OnGateMessageGetCorpsGoodsList( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ��ȡ���Ŷһ���Ʒ�б����Ϣ����
	void OnGateMessageGetCorpsExchangeGoodsList( CEntityPlayer* pPlayer, CMessage* pMessage );	
	
	// ���Ŷһ�
	void CorpsExchange( CEntityPlayer *pPlayer, int nComposeID, int nEntityID, int nItemNum );
	
	// ���Ŷһ��Ļ�Ӧ��Ϣ
	void OnGateResponseCorpsExchange( CMessage *pMsg );
	
	// ���Ӿ��Ŷһ���Ʒ
	int AddCorpsExchangeItem( CEntityPlayer *pPlayer, CTplLeagueBag *tpTplLeagueBag );
	
public:	
	// �������ŵĻ�Ӧ��Ϣ
	void OnGSCreatCorpsResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ���������ŵĻ�Ӧ��Ϣ
	void OnGSApplyCorpsResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// �м������������ŵ���Ϣ֪ͨ
	void OnGSCorpsMemberApplyNotify( CEntityPlayer *pPlayer, CMessage *pMessage );		
	
	// �ظ��������������ŵ���Ϣ��Ӧ
	void OnGSReplyMemberApplyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ���������ŵĽ��֪ͨ
	void OnGSApplyCorpsResultNotify( CEntityPlayer *pPlayer, CMessage *pMessage );	
		
	// ������������ŵ���Ϣ��Ӧ
	void OnGSInviteCorpsMemberResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	 
		
	// ���������ŵ���Ϣ֪ͨ
	void OnGSCorpsInviteNotify( CEntityPlayer *pPlayer, CMessage *pMessage );	
		
	// �𸴾����������Ϣ�ظ�
	void OnGSReplyCorpsInviteResponse( CEntityPlayer *pPlayer, CMessage *pMessage );		
		
	// ������������ŵĽ��֪ͨ
	void OnGSCorpsInviteResultNotify( CEntityPlayer *pPlayer, CMessage *pMessage );		
		
	// �м��������ŵ���Ϣ֪ͨ
	void OnGSFamilyJoinCorpsNotify( CEntityPlayer *pPlayer, CMessage *pMessage );			
		
	// �����뿪���ŵ���Ϣ��Ӧ
	void OnGSFamilyLeaveCorpsResponse( CEntityPlayer *pPlayer, CMessage *pMessage );			

	// �����뿪���ŵ���Ϣ֪ͨ
	void OnGSFamilyLeaveCorpsNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
		
	// �Ӿ����߳��������Ϣ��Ӧ
	void OnGSKickFamilyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );		
	
	// ����Ӿ������汻�ߵ���֪ͨ	
	void OnGSFamilyKickedNotify( CEntityPlayer *pPlayer, CMessage *pMessage );		
		
	// ��ȡ���ż����Ա��Ϣ�Ļ�Ӧ��Ϣ
	void OnGSGetCorpsFamilyInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage );		
		
	// ��ȡ����������Ϣ�Ļ�Ӧ��Ϣ
	void OnGSGetCorpsPropertyInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	
			
	// ��ȡ������ĳ������ĳ�Ա��Ϣ����Ϣ��Ӧ
	void OnGSGetCorpsFamilyMemberResponse( CEntityPlayer *pPlayer, CMessage *pMessage );		
		
	// �ı���Ź������Ϣ�ظ�
	void OnGSChangeCorpsBulletinResponse( CEntityPlayer *pPlayer, CMessage *pMessage );			

	// �ı���Ź������Ϣ֪ͨ
	void OnGSChangeCorpsBulletinNotify( CEntityPlayer *pPlayer, CMessage *pMessage );		
																								
	// �ı�����������Ϣ�ظ�
	void OnGSChangeCorpsHeaderResponse( CEntityPlayer *pPlayer, CMessage *pMessage );		
	
	// �ı�����������Ϣ֪ͨ							
	void OnGSChangeCorpsHeaderNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ȡ���ŵ������б����Ϣ��Ӧ
	void OnGSGetCorpsApplyListResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ɢ�������Ϣ��Ӧ
	void OnGSDisbandCorpsResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ɢ�������Ϣ֪ͨ
	void OnGSDisbandCorpsNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ȡ����ɢ�������Ϣ��Ӧ
	void OnGSCancelDisbandCorpsResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ˢ�¾�����Ϣ����Ϣ��Ӧ
	void OnGSRefreshCorpsInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������������б����Ϣ����
	void OnGSClearCorpsApplyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ȡ������Ϣ�б����Ϣ����
	void OnGSGetCorpsListResponse( CEntityPlayer *pPlayer, CMessage *pMessage );  

	// �������˸���
	void OnGSChangeUnionNameResponse( CEntityPlayer *pPlayer, CMessage *pMessage ); 
	void OnGSChangeUnionNameNotify( CEntityPlayer *pPlayer, CMessage *pMessage ); 
	void OnGateMessageSummonCorpsBossResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	
	
	// ���þ��ų�Աְλ����Ϣ��Ӧ	
	void OnGSSetCorpMemberPostResponse( CEntityPlayer *pPlayer, CMessage *pMessage );  
	
	// �������ŵ���Ϣ��Ӧ
	void OnGSLevelUPCorpsResponse( CEntityPlayer *pPlayer, CMessage *pMessage );  
	
	// ���׾��Ž�Ǯ����Ϣ��Ӧ
	void OnGSContributeCorpsMoneyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );   
		
	// ��������Ź��׽�Ǯ����Ϣ��Ӧ
	void OnGSFamilyContributeMoneyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );  
	
	// ���þ��ų�Ա�ƺŵ���Ϣ��Ӧ
	void OnGSSetMemberNameResponse( CEntityPlayer *pPlayer, CMessage *pMessage );  

	// ���þ���ְλ��֪ͨ
	void OnGSSetCorpsPostNotify( CEntityPlayer *pPlayer, CMessage *pMessage );  

	// ����������֪ͨ
	void OnGSCorpsLevelUPNotify( CEntityPlayer *pPlayer, CMessage *pMessage );  

	// ����pvp�ȼ�������֪ͨ	
	void OnGSCorpsPVPStarLevelUPNotify( CEntityPlayer *pPlayer, CMessage *pMessage );  
	
	// ��ѯ����npc��������Ϣ��Ӧ
	void OnGateMsgQueryNpcWelfareResponse( CEntityPlayer *pPlayer, CMessage *pMessage );  
	
	// ��ȡ����npc��������Ϣ��Ӧ
	void OnGateMsgObtainNpcWelfareResponse( CEntityPlayer *pPlayer, CMessage *pMessage );  
	
	// ��ȡ���Ž�Ǯ����Ϣ��Ӧ
	void OnGateMsgGetCorpsMoneyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );  

	void OnGSQueryBidRankResponse( CEntityPlayer* pPlayer, CMessage* pMessage );

	void OnGSCorpsBidResponse( CEntityPlayer* pPlayer, CMessage* pMessage );

	void OnGSCorpsJoinBattleNotice( CMessage* pMessage );

	void OnGSSelectBattleFamilyResponse( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnGSSelectBattleMemberResponse( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnGSCorpsBattleRightsNotify( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnGSFamilyBattleRightsNotify( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnGSMemberBattleRightsNotify( CEntityPlayer* pPlayer, CMessage* pMessage );

	void OnGSSendBattleFlagOwnerNoitce( CMessage* pMessage );

	void OnGSCorpsChallgeReponse( CEntityPlayer* pPlayer, CMessage* pMessage );

	void OnGSCorpsBattleResultNotice( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// �ı���ų�Ա���׶ȵ�֪ͨ
	void OnGateNotifyChangeCorpsContribute( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �ı���Ųɼ���Ծ�ȵ�֪ͨ
	void OnGateNotifyChangeCorpsCollectActive( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������ź������Ϣ��Ӧ
	void OnGateResponseBuyCorpsItem( CMessage* pMessage );
	
	// ���ųƺŸı����Ϣ֪ͨ
	void OnGateMsgCorpsTitleChangedNotify( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ���������Ļ�Ӧ��Ϣ
	void OnGSCreateUnionResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// ���������Ļ�Ӧ֪ͨ
	void OnGSCreateUnionNotify( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// ������������Ļ�Ӧ��Ϣ
	void OnGSApplyUnionResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// �о������������������Ϣ֪ͨ
	void OnGSUnionApplyNotify( CEntityPlayer *pPlayer, CMessage *pMessage );		

	// �ظ��������������������Ϣ��Ӧ
	void OnGSReplyUnionApplyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// ������������Ľ��֪ͨ
	void OnGSApplyUnionResultNotify( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// ������ż�����������Ϣ��Ӧ
	void OnGSInviteUnionMemberResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	 

	// ���������������Ϣ֪ͨ
	void OnGSUnionInviteNotify( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// �������������Ϣ�ظ�
	void OnGSReplyUnionInviteResponse( CEntityPlayer *pPlayer, CMessage *pMessage );		

	// ������ż��������Ľ��֪ͨ
	void OnGSUnionInviteResultNotify( CEntityPlayer *pPlayer, CMessage *pMessage );		

	// �о��ż�����������Ϣ֪ͨ
	void OnGSCorpsJoinUnionNotify( CEntityPlayer *pPlayer, CMessage *pMessage );			

	// �����뿪��������Ϣ��Ӧ
	void OnGSCorpsLeaveUnionResponse( CEntityPlayer *pPlayer, CMessage *pMessage );			

	// �����뿪��������Ϣ֪ͨ
	void OnGSCorpsLeaveUnionNotify( CEntityPlayer *pPlayer, CMessage *pMessage );

	// �������߳����ŵ���Ϣ��Ӧ
	void OnGSKickCorpsResponse( CEntityPlayer *pPlayer, CMessage *pMessage );		

	// ���Ŵ��������汻�ߵ���֪ͨ	
	void OnGSCorpsKickedNotify( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ���������Ļ�Ӧ��Ϣ
	void OnGSMakeUnionResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// ���������Ϣ�Ļ�Ӧ
	void OnGSGetUnionInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��ɢ��������Ϣ��Ӧ
	void OnGSDismissUnionResponse( CEntityPlayer *pPlayer, CMessage *pMessage );		

	// ��ɢ������֪ͨ	
	void OnGSDismissUnionNotify( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ������������б����Ϣ��Ӧ
	void OnGSUnionApplyListResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��������б����Ϣ��Ӧ
	void OnGSAllUnionListResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

public:

	// ���npc�Ƿ��о�����صķ��񣬲��Ҿ����Ƿ�Ϸ�
	bool CheckNpcCorpsService( CEntityPlayer *pPlayer, int nNpcEntityID, int eService );

	// ����Ƿ��ھ���ս���ۿ���ʱ��
	bool CheckInBidOpenTime( int nNpcID );
	
	// ������ҵĹ��׶�
	void AddPlayerCorpsContribute( int nRoleID, int nContribute, int nAddType = 0 );

	// �ı���ҵľ��Ųɼ���Ծ��
	void ChangeCorpsCollectActive( int nRoleID, int nChangeValue, int nChangeType = 0 );

	// �ı�����Ǯ
	void ChangeCorpsMoney( CEntityPlayer *pPlayer, int nMoney, bool bPayOut = false, int nReason = REASON_TASK ); 

	// �ı������ҫֵ
	void ChangeCorpsGlory( CEntityPlayer *pPlayer, int nValue, int bReduced = false, int nReason = REASON_TASK );			

	int OnStartFireBattleTimer( int nEntityID );

	void InsertNpcList( CMessageNpcListNotify* vpNotify );

	const char* GetCorpsNameByNpcID( int nNpcID );
	
	int	GetCorpsIDByNpcID( int nNpcID );
	
	// ���������Ʒ�Ľӿ�
	void BuyCorpsItem( CEntityPlayer *pPlayer, int nItemID, int nItemNum, int nNpcTmpID, int nCityMapID );	

	// �Ƿ��о������˷���
	bool HasUnionService( CEntityPlayer *pPlayer, int vNpcEntityID );
	// ��Ӿ���boss��ս����
	void ChangeCorpsBossTimes( CEntityPlayer *pPlayer, int nBossId ,int nTimes , int nReason );

	// ���Ӿ���boss����ֵ
	void ChangeCorpsBOSSRefineValue( CEntityPlayer * pPlayer, int nValue , int nReason );

	//�ٻ�����boss����
	void OnMessageSummonCorpsBossRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

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

	// �ڲ���ʱ��Ϣ
	virtual void OnTimeoutMessage( CMessage* pMessage );

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst );

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );

	// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );

	// ��������
	virtual void OnLoadConfig( );

	// ����������ϼ��
	virtual bool OnCheckLaunch( );
};
