#pragma once		
#include "familytype.h"	 
#include "servercore.h"
#include "servertool.h"
#include "lk_vector.h"
#include "lk_hashmap.h"
#include "corpstype.h"

#define   SenMsgToGate( MsgHead, FamilyMsg, EntityPlayer  )	 \
FamilyMsg->clear_headmsg();										\
FamilyMsg->mutable_headmsg()->set_roleid( EntityPlayer->GetCharID() );	\
FamilyMsg->mutable_headmsg()->set_entityid( EntityPlayer->GetEntityID() ); \
CSceneLogic::GetSingleton().Send2Gate( MsgHead ) ;

class CMemberInfo
{
public:
	bool	mIfHasFamilyApplies;	// �Ƿ���������Ϣ
	bool	mIfHasCorpsApply;		// �Ƿ��о���������Ϣ
	int		mFamilyContribute;
	int		mFamilyPost;
	int		mCorpsContribute;
	int		mCorpsPost;	 
	int		mExpGloryNeeded;		// �һ�������ҫ�ľ���
	int		mApGloryNeeded;			// �һ����徭��Ĺ�ѫ	
	int		mFamilyHeaderID;		// ��������ID	
	int		mCorpsHeaderID;			// ��������ID	
	int		mFamilyMoney;			// �����Ǯ
	int		mCorpsMoney;			// ���Ž�Ǯ
	int		mEntityID;				// ��ҵ�ʵ��ID	
public:	
	CMemberInfo()
	{
		if ( CObj::msCreateMode )
		{
			Initailize( );
		}
		else
		{
			Resume();	
		}
	}
	~CMemberInfo(){ }
	
	int Initailize()
	{
		mFamilyContribute = 0;
		mCorpsPost = 0;
		mCorpsContribute = 0;
		mFamilyPost = 0;
		
		mCorpsPost =  CORPS_POST_MEMBER;	 
		mIfHasFamilyApplies = false;	
		mExpGloryNeeded = 0;
		mApGloryNeeded = 0;
		mFamilyHeaderID = 0;
		mCorpsHeaderID = 0;
		mIfHasCorpsApply = false;
		mFamilyMoney = 0;
		mCorpsMoney = 0;
		mEntityID = 0;
		return  SUCCESS;			
	}
	
	int Resume()
	{
		return SUCCESS;
	}
};

struct CFamilyTaskInfo 
{
	int mValue;
};

class  CFamilyInfo : public CObj
{
public:
	typedef lk::hash_map< int, CMemberInfo, MAX_FAMILYMEMBER_NUM > FamilyMemberList;		
public:
	FamilyMemberList	mMemberList;
	char				mFamilyName[MAX_FAMILYNAME_LENGTH*MAX_UTF8_BYTES];	
	int					mCorpsID;
	char				mCorpsName[MAX_FAMILYNAME_LENGTH*MAX_UTF8_BYTES];	 	
public:	
	CFamilyInfo()														    
	{	
		if ( CObj::msCreateMode )
		{
			Initialize();
		}
		else
		{
			Resume();	
		}	
	}	
	int Initialize();
	int Resume(){ return 0; }

	~CFamilyInfo(){ }
public:
	
	// �������Ա���볡��ʱ,�����б�
	int InsertMember( int nRoleID, CMemberInfo &rMemberInfo );
	
	// �������ʱɾ�������Ϣ
	int DeleteMember( int nRoleID );
	
	// �жϳ�Ա�б����Ƿ���ĳ�����
	bool HasMember( int nRoleID );
	
	// �ı��Ա����Ϣ
	int ChangeMemberInfo( int nRoleID, CMemberInfo &rMemberInfo );
	
	// ��ȡ��Ա��Ϣ
	CMemberInfo *GetMemberInfo( int nRoleID );	
	
	// ��ȡ�����������б�
	int GetMemberList( int *pIDList, int &rNum ); 
	
	// ���þ���ID
	void SetCorpsID( int nCorpsID ){ mCorpsID = nCorpsID;  }
	
	// ��ȡ����ID
	int GetCorpsID(  ){ return mCorpsID; }	
	
	// ���ü�������
	void SetFamilyName( const char *pName, bool bRefresh = false );
	
	// ���þ�������
	void SetCorpsName( const char *pName, bool bRefresh = false );
	
	// ��ȡ��������
	const char *GetFamilyName(){ return mFamilyName; }
	
	// ��ȡ��������
	const char *GetCorpsName( ){ return mCorpsName; }
	
	// ��ȡ��������
	const char *GetFamilyNameShow(); 
	
	// ��ȡ��������
	const char *GetCorpsNameShow();
	
	// ��ȡ��Ա����
	int GetMemberNum(){ return mMemberList.size(); }
};


class CFamilyModule : public CLogicModule, public CSingleton< CFamilyModule >
{
public:
	typedef lk::hash_map< int, lk::string<MAX_FAMILYNAME_LENGTH*MAX_UTF8_BYTES>, MAX_FAMILY_NUM > IDNameList;
	typedef lk::hash_map< int, int, 1000 > NPCList;
	typedef lk::hash_map< int, int, MAX_FAMILY_NUM > FamilyList;
	typedef lk::hash_map< int, CFamilyTaskInfo, MAX_FAMILYTASK_NUM > FamilyTaskList;
	static char	sModuleName[ NAME_LENGTH ];

	IDNameList	mNameList;
	NPCList		mNpcList;
	FamilyList	mFamilyList;
	FamilyTaskList mFamilyTask;
public:
	CFamilyModule():CLogicModule( sModuleName ){  }
	~CFamilyModule(){  }
	static unsigned int CountSize( );
public:	
	// ������Ϣ  CMessageCreatFamilyRequest
	void OnMessageCreatFamily( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������Ϣ  CMessageInviteMemberRequest
	void OnMessageInviteMember( CEntityPlayer *pPlayer, CMessage *pMessage );	  
	
	// ������Ϣ CMessageReplyFamilyInviteRequest
	void OnMessageReplyFamilyInvite( CEntityPlayer *pPlayer, CMessage *pMessage );	  
	
	// ������Ϣ CMessageApplyFamilyRequest
	void OnMessageApplyFamily( CEntityPlayer *pPlayer, CMessage *pMessage );	  	
	
	// ������ϢCMessageReplyMemberApplyRequest   
	void OnMessageReplyMemberApply( CEntityPlayer *pPlayer, CMessage *pMessage );	
		
	// ������Ϣ CMessagePostAppointRequest   
	void OnMessagePostAppoint( CEntityPlayer *pPlayer, CMessage *pMessage );	  	
	
	// ������Ϣ CMessageLeaveFamilyRequest
	void OnMessageLeaveFamily( CEntityPlayer *pPlayer, CMessage *pMessage );	  	
	
	// ������Ϣ CMessageGetFamilyMemberInfoRequest		 
	void OnMessageGetFamilyMemberInfo( CEntityPlayer *pPlayer, CMessage *pMessage );	  	
	
	// ������Ϣ CMessageGetFamilyPropertyRequest
	void OnMessageGetFamilyPropetyInfo( CEntityPlayer *pPlayer, CMessage *pMessage );	  	
	
	// ������Ϣ CMessageGetAllFamilyInfoResponse
	void OnMessageGetAllFamilyInfo( CEntityPlayer *pPlayer, CMessage *pMessage );	  	
	
	// ������Ϣ CMessageGetApplyListRequest
	void OnMessageGetApplyList( CEntityPlayer *pPlayer, CMessage *pMessage );	  	
	
	// ������Ϣ	CMessageKickPlayerRequest
	void OnMessageKickPlayer( CEntityPlayer *pPlayer, CMessage *pMessage );	  	
	
	// ������Ϣ CMessageDisbandFamilyRequest
	void OnMessageDisbandFamily( CEntityPlayer *pPlayer, CMessage *pMessage );	  	
	
	// ������Ϣ CMessageAppointHeaderRequest
	void OnMessageAppointHeader( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������Ϣ CMessageChangeFamilyNoticeRequest
	void OnMessageChangeFamilyNotice( CEntityPlayer *pPlayer, CMessage *pMessage );	
		
	// ������Ϣ CMessageClearFamilyApplyRequest
	void OnMessageClearFamilyApply( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������Ϣ CMessageCancelFamilyDisbandRequest
	void OnMessageCancelDisbandFamily( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������Ϣ CMessageRefreshFamilyInfoRequest
	void OnMessageRefreshFamilyInfo( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��������NPC������Ϣ
	void OnMessageBidNpc( CEntityPlayer *pPlayer, CMessage *pMessage );

	// �����峤����������Ϣ
	void OnMessageMemberSubmit( CEntityPlayer *pPlayer, CMessage *pMessage );

	// �����ѯNPC����
	void OnMessageBidInfo( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ����NPC������Ϣ
	void OnMessageAbortNpc( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��������ID��Ϣ
	void OnMessageIDNameNotify( CMessage *pMessage );

	// ����NPCռ����Ϣ
	void OnMessageNpcListNotify( CMessage *pMessage );	

	// �������¾���֪ͨ
	void OnMessageBidRestartNotify( CMessage *pMessage );

	// �����跿����Ϣ
	void OnMessageMakeRoom( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ������ս������Ϣ
	void OnMessageChaRoom( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ����ͬ����ս��Ϣ
	void OnMessageAgreeBattle( CEntityPlayer *pPlayer, CMessage *pMessage );

	// �����ѯ�����б���Ϣ
	void OnMessageQueryAllRoom( CEntityPlayer *pPlayer, CMessage *pMessage );

	// �����ѯ�Լ��ķ�����Ϣ
	void OnMessageQueryMyRoom( CEntityPlayer *pPlayer, CMessage *pMessage );

	// �����ѯ�Լ�����ս��Ϣ
	void OnMessageQueryMyCha( CEntityPlayer *pPlayer, CMessage *pMessage );

	// �������������Ϣ
	void OnMessageAbortRoom( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ���������ս��Ϣ
	void OnMessageAbortCha( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ͨ��ID�������
	char* GetFamilyName( int vFamilyID );

	// ���ռ��NPC�ļ���ID
	int GetFamilyIDByNpcID( int vNpcID );
	
	
	// ���ü����Աְλ����Ϣ����
	void OnMessageSetFamilyMemberPost( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// �������������
	void OnMessageLevelUPFamily( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// ���׼����Ǯ����Ϣ����
	void OnMessageContributeFamilyMoney( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��������boss��֪ͨ
	void OnMessageStartFamilyBoss( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ��ȡ���徭�����Ƶ���Ϣ����
	void OnMessageGetFamilyExpCard( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ��ҽ�����帱������Ϣ����
	void OnMessageEnterFamilyRepetion( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ��ȡ��������б����Ϣ����
	void OnMessageGetFamilyGoodsList( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ��ȡ����һ���Ʒ�б����Ϣ����
	void OnMessageGetFamilyExchangeGoodsList( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ��ȡ��������б�����ط�����Ϣ
	void OnGateMsgGetFamilyGoodsListResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ��ȡ����һ���Ʒ�б�����ط�����Ϣ
	void OnGateMsgGetFamilyExchangeGoodsListResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// ����һ�
	void FamilyExchange( CEntityPlayer *pPlayer, int nComposeID, int nEntityID, int nItemNum );
	
	// ����һ��Ļ�Ӧ��Ϣ
	void OnGateResponseFamilyExchange( CMessage *pMessage );
	
	// ���Ӽ���һ���Ʒ�Ľӿ�
	int AddFamilyExchangeItem( CEntityPlayer *pPlayer, CTplLeagueBag *tpTplLeagueBag );
		
	public:
	// ��������
	void CreatFamily(  CEntityPlayer *pPlayer, const char *pFamilyName );	  	
	// �����Ա
	void InviteFamilyMember( CEntityPlayer *pPlayer, int vEntityID, const char *pName = NULL );
	// ������
	void ReplyFamilyInvite( CEntityPlayer *pPlayer, int Result, int FamilyID );
	// ����������
	void ApplyFamily( CEntityPlayer *pPlayer, int vEntityID, int FamilyID = 0 );
	// �ظ��������
	void ReplyMemberApply( CEntityPlayer *pPlayer, int Result, int PlayerCharID );
	// ְλ����
	void AppiontPost(  CEntityPlayer *pPlayer, int PlayerCharID, int ActionKind );
	// �뿪����
	void LeaveFamily( CEntityPlayer *pPlayer );
	// ��ȡ���������б�
	CMemberInfo* GetFamilyMemberInfo( CEntityPlayer *pPlayer );	
	// ��ȡ����������Ϣ
	void GetFamilyPropertyInfo( CEntityPlayer *pPlayer );	
	// ��ȡ���м���Ļ�����Ϣ
	void GetAllFamilyInfo( CEntityPlayer *pPlayer ); 
	// ��ȡ����������б�
	void GetApplyList( CEntityPlayer *pPlayer );
	// �߳������Ա
	void KickFamilyMember( CEntityPlayer *pPlayer, int PlayerCharID );
	// ��ɢ����
	void DisbandFamily( CEntityPlayer *pPlayer );
	// ת������ְλ
	void AppointHeader( CEntityPlayer *pPlayer, int PlayerCharID );
	// �ı���幫��
	void ChangeFamilyNotice( CEntityPlayer *pPlayer, const char *pNotice );
	// ���npc�Ƿ��м������ط���
	bool CheckNpcFamilyService( CEntityPlayer *pPlayer, int nNpcEntityID, int eService );
public:

	// ID_S2C_RESPONSE_CREATFAMILY ��������Ļ�Ӧ 
	void OnGSCreatFamilyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_RESPONSE_INVITEMEMBER	 �������Ļ�Ӧ
	void OnGSIviteMemberResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_NOTIY_FAMILYINVITED	 �����������֪ͨ	 	
	void OnGSFamilyInvitedNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_RESPONSE_REPLYFAMILYINVITE	�𸴼�������Ļظ� 
	void OnGSReplyFamilyInviteResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
		
	// ID_S2C_RESPONSE_FAMILYAPPLY	 ����������Ļ�Ӧ	
	void OnGSFamilyApplyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_NOTIFY_MEMBERAPPLY	���������������������������֪ͨ	
	void OnGSMemberApplyNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_RESPONSE_REPLYMEMBERAPPLY �ظ��������������Ļ�Ӧ
	void OnOnGSReplyMemberApplyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );					
	
	// ID_S2C_NOTIFY_FAMILYAPPLYSUCESS	 ֪ͨ�������������ɹ�
	void OnGSFamilyApplySucessNotify( CEntityPlayer *pPlayer, CMessage *pMessage );					
	
	// ID_S2C_NOTIFY_FAMILYMEMBERADDED		֪ͨ�����Ա���³�Ա���루���������ͨ�ã�	
	void OnGSFamilyMemberAddedNotify( CEntityPlayer *pPlayer, CMessage *pMessage );			
	
	// ID_S2C_RESPONSE_POSTAPPOINT		 ���������ְλ����Ļ�Ӧ
	void OnGSPostAppointResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_NOTIFY_POSTAPPOINT	 �������������ְλ��֪ͨ
	void OnGSPostAppointNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_RESPONSE_LEAVEFAMILY	�����Ա�뿪����Ļ�Ӧ
	void OnGSLeaveFamilyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );		
	
	// ID_S2C_NOTIFY_MEMBERLEAVEFAMILY	�����Ա�뿪�����֪ͨ	 
	void OnGSMemberLeaveFamilyNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
		
	// ID_S2C_RESPONSE_GETFAMILYMEMBERINFO ��ȡ�����Ա��Ϣ�Ļ�Ӧ	
	void OnGSGetFamilyMemberInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage );			
	
	// ID_S2C_RESPONSE_FAMILYPROPERTY	 ��ȡ������Ϣ�Ļ�Ӧ������������Ϣ
	void OnGSFamilyPropertyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
											 				
	// ID_S2C_RESPONSE_GETALLFAMILYINFO	 ��ȡ���м��������Ϣ�Ļظ���Ϣ  
	void OnGSGetAllFamilyInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
		
	// ID_S2C_RESPONSE_GETAPPLYLIST	���������б�	
	void OnGSGetApplyListResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_RESPONSE_KICKMEMBER	 �������˵Ļ�Ӧ
	void OnGSKickMemberResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_NOTIFY_KICKPLAYER	 �������˵�֪ͨ
	void OnGSKickPlayerNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_RESPONSE_DISBANDFAMILY	��ɢ����Ļ�Ӧ
	void OnGSDisbandFamilyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
		
	// ID_S2C_NOTIFY_DISBANDFAMILY  ��ɢ�����֪ͨ
	void OnGSDisbandFamilyNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
		
	// ID_S2C_RESPONSE_CHANGENOTICE	�ı���幫��Ļ�Ӧ	
	void OnGSChangeNoticeResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_RESPONSE_APPOINTHEADER	 ����ת��ְλ�Ļ�Ӧ��Ϣ
	void OnGSAppointHeaderResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_NOTIFY_CHANGERHEADER	����ת��ְλ��֪ͨ	
	void OnGSChangeHeaderNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_NOTIFY_FAMILYPEROPERTY	����������Ϣ֪ͨ
	void OnGSFamilyPropertyNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ID_S2C_NOTIFY_INVITERESULT ����Ľ�����ܾ���������ԭ��
	void OnGSInviteMemberResultNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	//	ȡ����ɢ�������Ϣ��Ӧ
	void OnGSCancelDisbandCorpsResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������������б����Ϣ��Ӧ
	void OnGSClearFamilyApplyListResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// �ı���幫���֪ͨ
	void OnGSChangeFamilyNoticeNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ˢ�¼����Ա����Ϣ��Ӧ
	void OnGSRefreshFamilyInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ���������ŵ�֪ͨ
	void OnGSJoinCorpsNotify( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��������NPC��Ӧ
	void OnGSBidNpcResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��������NPC֪ͨ
	void OnGSMemberSubmitNotify( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��������NPC��Ӧ
	void OnGSMemberSubmitResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ����NPC��Ӧ
	void OnGSAbortNpcResponse( CEntityPlayer *pPlayer, CMessage *pMessage ); 	


	// �����ط���ս������֪ͨ
	void SendBattleEndNotify( KEY_TYPE vKey, int vWinSide );

	// ��ѯNPC�����Ӧ
	void OnGSBidInfoResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	

	// ���跿���Ӧ
	void OnGSMakeRoomResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��ս�����Ӧ
	void OnGSChaRoomResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ͬ����ս��Ӧ
	void OnGSAgreeBattleResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��ѯ�����б��Ӧ
	void OnGSQueryAllRoomResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��ѯ�Լ��ķ����Ӧ
	void OnGSQueryMyRoomResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��ѯ�Լ�����ս��Ӧ
	void OnGSQueryMyChaResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ���������Ӧ
	void OnGSAbortRoomResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ������ս��Ӧ
	void OnGSAbortChaResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// �յ���ս֪ͨ
	void OnGSFamilyChaNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ȡ��ȡ�����ڵ��Ļ�Ӧ��Ϣ
	void OnGateMsgGetExpCard( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ҹ��׶ȸı����Ϣ
	void OnGateNotifyFamilyContributeChanged( CEntityPlayer *pPlayer, CMessage *pMessage );
			
	// �����������ص���Ϣ
	void OnGateMsg( CMessage *pMessage );
	
	// �����ط��ͼ�����Ϣ
	void SendToGate( void *pMsg, int MsgID, CEntityPlayer *pPlayer );
	
	// ���ͻ��˷��ͻ�Ӧ��Ϣ
	void SendToClient( CEntityPlayer *pPlayer, void *pMsg, int MsgID );	
	

	// ���ü����Աְλ����Ϣ��Ϣ��Ӧ
	void OnGateMsgSetFamilyMemberPostResponse( CEntityPlayer *pPlayer, CMessage *pMessage );	
		
	// ��������Ļ�Ӧ
	void OnGateMsgLevelUPFamilyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ���׼����Ǯ����Ϣ��Ӧ
	void OnGateMsgContributeFamilyMoneyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ռ��npc����ȡ�����Ǯ����Ϣ��Ӧ
	void OnGateMsgObtainFamilyMoneyResponse( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ���ü���ְλ��֪ͨ
	void OnGateMsgSetFamilyPostNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ����������֪ͨ	
	void OnGateMsgLevelUPFamilyNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// pvp�Ǽ�������֪ͨ
	void OnGateMsgPVPStarLevelUPNotify( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��������boss��Ļ�Ӧ��Ϣ
	void OnGateMsgStartFamilyBossResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ѯ����npc����
	void OnGateMsgQueryNpcWelfareResponse( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ��ȡ�����Ǯ
	void OnGateMsgGetFamilyMoney( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������ҵĹ��׶�
	void AddPlayerFamilyContribute( int nRoleID, int nContribute, int nAddType = 0 );
	
	// �ı�����Ǯ
	void ChangeFamilyMoney( CEntityPlayer *pPlayer, int nMoney, bool bPayOut = false, int nReason = REASON_TASK );
	
	// �ı������ҫֵ
	void ChangeFamilyGlory( CEntityPlayer *pPlayer, int nValue, int bReduced = false, int nReason = REASON_TASK );
	
	// �ı���尲����
	void ChangeFamilyStability( CEntityPlayer *pPlayer, int nValue, int nReason = REASON_TASK, int nParam1 = 0, int nParam2 = 0 );
	
	// ��ѯ���帣��
	void OnMessageQueryFamilyWelfare( CEntityPlayer *pPlayer, CMessage *pMessage );		

	// ��ռ��npc����ȡ�����Ǯ����Ϣ����
	void OnMessageObtainFamilyMoney( CEntityPlayer *pPlayer, CMessage *pMessage );		
	
	// ��ȡ�����Ǯ������
	void OnMessageGetFamilyMoney( CEntityPlayer *pPlayer, CMessage *pMessage );	
	
	// �������������Ϣ��Ӧ
	void OnGateResponseBuyFamilyItem( CMessage *pMessage );	
	
	// ���������Ʒ�Ľӿ�
	void BuyFamilyItem( CEntityPlayer *pPlayer, int nItemID, int nItemNum, int nNpcTmpID );	
	
	// ������帱�������ػ�Ӧ
	void OnGateMsgEnterFamilyRepetion( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������帱����Ϣ
	void ClearFamilyRepetionInfo( int nFamilyID, int nRepetionLevel, int nOgreNum, int nTimeLength , int nBigWaveNum, int nSamllWaveNum, int nMaxHitNum, int nScore );
	
	// ��ȡ����ļ��尲���Ƚ���
	void OnTaksChangeStability( int nTaskID, CEntityPlayer *pPlayer );
public:
	// ����һ����ҵ���Ϣ
	int InsertFamilyMember( int nCorpsID, int nFamilyID, int nRoleID, CMemberInfo &rMemberInfo,  const char *pFamilyName = NULL, const char *pCorpsName = NULL );
	
	// ɾ��һ����ҵ���Ϣ
	int DeleteFamilyMember( int nFamilyID, int nRoleID );
	
	// ��ȡĳ������������Ϣ�б�
	int GetFamilyMemberList( int nFamilyID, int *pIDList, int &rNum );
	
	// ɾ��������Ϣ( ��ɢ�����ʱ�� )
	int DeleteFamilyInfo( int nFamilyID );
	
	// ��ȡ��������������ĳ�����ŵĳ�Ա�б�
	int GetCorpsMemberList( int nCorpsID, int *pIDList, int &rNum );
	
	// ��ȡ�����ڵ�ǰ������������������ҵ�ƽ���ȼ�
	int GetFamilyAverageLevel( int nFamilyID, int &rLevel );
	
	// ��ȡ��������,�����м����Ա�ڱ�����ʱ����Ч
	const char *GetFamilyNameByID( int nFamilyID );
	
	// ��ȡ��������,�����о��ų�Ա�ڱ�����ʱ����Ч
	const char *GetCorspNameByID( int nFamilyID, int nCorpsID );
	
	// ��ȡ�����Ա�ĸ�����Ϣ
	CMemberInfo *GetFamilyMemberInfo( int nFamilyID, int nRoleID );
	
	// ��ȡ������Ϣ
	CFamilyInfo *GetFamilyInfo( int nFamilyID );
	
	// �ж�����Ƿ��Ǽ�������
	bool HasFamilyRight( CEntityPlayer *pPlayer, int nRight );
	
	// �ж��Ƿ��Ǿ�������
	bool HasCorpsRight( CEntityPlayer *pPlayer, int nRight );
	
	// ��ʼ����������
	int InitialFamilyConfig();
	
	// �ж��Ƿ���ĳ������
	bool IsFamilyTask( int nTaskID );

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
	virtual bool OnCheckLaunch( ) { return true; }

	// ���ؼ������õĻص�����
	static void LoadFamilyConfigCallback(const char* pcConfigPath);

};
