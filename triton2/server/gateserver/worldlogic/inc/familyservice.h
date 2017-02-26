#pragma once

// #ifndef _FCM_SERVICE_H_
// #define _FCM_SERVICE_H_

#include "module_manager.h"
#include "entity.h"
#include "lk_hashmap.h"
#include "lk_string.h"
#include "gateobj_define.h"
#include "lk_set.h"
#include "familydbinfo_pb.hxx.pb.h"
#include "familymessage_pb.hxx.pb.h"
#include "family.h"

using namespace GateServer;	

class CServiceFamily :public CDataModule, public CSingleton< CServiceFamily >
{
public:
	void OnLaunchServer();
	void OnExitServer();
	void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );
	void OnMessage(int nServerID, CMessage* pMessage );
	void OnSeverMessage(int nServerID, CMessage* pMessage );
	CServiceFamily();
	~CServiceFamily();
	int Initialize();
	int Resume();
	static unsigned int CountSize();
	void* operator new( size_t nsize );
	void  operator delete( void* pointer );	

	virtual bool IsLaunched() { return mIsLaunched; }	
	
	void OnLaunchComplete();
public:
	void LoadFamilyFromDB( int nStart, int nTotalCount );
	void OnSessionLoadFamilyFromDB( CMessage* pMessage, int nStart, int nTotalCount );
	void OnMessageFangChenMiRequest( int nServerID, CMessage* pMessage );
	
	void GetFamilyCountFromDB();
	
	void OnSessionGetFamilyCountFromDB( CMessage* pMessage, int nParam1, int nParam2 );
public:	
	// ������Ϣ  CMessageCreatFamilyRequest
	void OnMessageCreatFamily( int nServerID, CMessage *pMessage );

	// ������Ϣ  CMessageInviteMemberRequest
	void OnMessageInviteMember( int nServerID, CMessage *pMessage );	  

	// ������Ϣ CMessageReplyFamilyInviteRequest
	void OnMessageReplyFamilyInvite( int nServerID, CMessage *pMessage );	  

	// ������Ϣ CMessageApplyFamilyRequest
	void OnMessageApplyFamily( int nServerID, CMessage *pMessage );	  	

	// ������ϢCMessageReplyMemberApplyRequest   
	void OnMessageReplyMemberApply( int nServerID, CMessage *pMessage );	

	// ������Ϣ CMessagePostAppointRequest   
	void OnMessagePostAppoint( int nServerID, CMessage *pMessage );	  	

	// ������Ϣ CMessageLeaveFamilyRequest
	void OnMessageLeaveFamily( int nServerID, CMessage *pMessage );	  	

	// ������Ϣ CMessageGetFamilyMemberInfoRequest		 
	void OnMessageGetFamilyMemberInfo( int nServerID, CMessage *pMessage );	  	

	// ������Ϣ CMessageGetFamilyPropertyRequest
	void OnMessageGetFamilyPropetyInfo( int nServerID, CMessage *pMessage );	  	

	// ������Ϣ CMessageGetAllFamilyInfoResponse
	void OnMessageGetAllFamilyInfo( int nServerID, CMessage *pMessage );	  	

	// ������Ϣ CMessageGetApplyListRequest
	void OnMessageGetApplyList( int nServerID, CMessage *pMessage );	  	

	// ������Ϣ	CMessageKickPlayerRequest
	void OnMessageKickPlayer( int nServerID, CMessage *pMessage );	  	

	// ������Ϣ CMessageDisbandFamilyRequest
	void OnMessageDisbandFamily( int nServerID, CMessage *pMessage );	  	

	// ������Ϣ CMessageAppointHeaderRequest
	void OnMessageAppointHeader( int nServerID, CMessage *pMessage );

	// ������Ϣ CMessageChangeFamilyNoticeRequest
	void OnMessageChangeFamilyNotice( int nServerID, CMessage *pMessage );		

	// ������Ϣ	CMessageClearFamilyApplyRequest
	void OnMessageClearFamilyApply( int nServerID, CMessage *pMessage );
	
	// ������Ϣ CMessageCancelFamilyDisbandRequest
	void OnMessageCancelFamilyDisband( int nServerID, CMessage *pMessage );
	
	// ������Ϣ CMessageRefreshFamilyInfoRequest
	void OnMessageRefreshFamilyInfo( int nServerID, CMessage *pMessage );
	

	// ���ü����Աְλ����Ϣ����
	void OnMessageSetFamilyMemberPost( int nServerID, CMessage *pMessage );

	// �������������
	void OnMessageLevelUPFamily( int nServerID, CMessage *pMessage );

	// ���׼����Ǯ����Ϣ����
	void OnMessageContributeFamilyMoney( int nServerID, CMessage *pMessage );	

	// ��������NPC������Ϣ
	void OnMessageBidNpc( int nServerID, CMessage *pMessage );

	// ����NPC���ᵽʱ��Ϣ
	void OnMessageBidTimeOut( int nServerID, CMessage *pMessage );

	// �����峤������Ա��Ϣ
	void OnMessageMemberSubmit( int nServerID, CMessage *pMessage );

	// �������ս����Ϣ
	void OnMessageBattleStart( int nServerID, CMessage *pMessage );

	// ����ս��������Ϣ
	void OnMessageBattleEnd( int nServerID, CMessage *pMessage );

	// ����NPC��ѯ����
	void OnMessageNpcInfo( int nServerID, CMessage *pMessage );

	// �������NPC����
	void OnMessageAbortNpc( int nServerID, CMessage *pMessage );

	// ���跿������
	void OnMessageMakeRoom( int nServerID, CMessage *pMessage );

	// ��ս��������
	void OnMessageChaRoom( int nServerID, CMessage *pMessage );

	// ͬ����ս����
	void OnMessageAgreeBattle( int nServerID, CMessage *pMessage );

	// ��ѯ�����б�����
	void OnMessageQueryAllRoom( int nServerID, CMessage *pMessage );

	// ��ѯ�Լ��ķ�������
	void OnMessageQueryMyRoom( int nServerID, CMessage *pMessage );

	// ��ѯ�Լ�����ս����
	void OnMessageQueryMyCha( int nServerID, CMessage *pMessage );

	// ������������
	void OnMessageAbortRoom( int nServerID, CMessage *pMessage );

	// ������ս����
	void OnMessageAbortCha( int nServerID, CMessage *pMessage );	
	
	// �ı�����Ǯ
	void OnMessageChangeFamilyMoney( CMessage *pMessage );
	
	// �ı������ҫֵ
	void OnMessageChangeFamilyGlory( CMessage *pMessage );
	
	// ���ӳ�Ա����
	void OnMessageChangeFamilyContribute( CMessage *pMessage );
	
	// ��������boss����������
	void OnMessageStartFamilyBoss( int nServerID, CMessage *pMessage );
	
	// ��ѯ����Npc����
	void OnMessageQueryFamilyNpcWelfare( int nServerID, CMessage *pMessage );
	
	// ��ȡ�����Ǯ( �Ѽ����Ǯ���ɸ��˽�Ǯ )
	void OnMessageGetFamilyMoney( int nServerID, CMessage *pMessage );
		
	// ��ռ��npc����ȡ�����Ǯ( ����ҫ )����Ϣ����
	void OnMessageObtainFamilyMoney( int nServerID, CMessage *pMessage );
	
	// ��ȡ�����ڵ�����Ϣ
	void OnMessageGetExpCard( int nServerID, CMessage *pMessage );
	
	// �������������Ϣ����
	void OnMessageBuyFamilyItem( int nServerID, CMessage *pMessage );
	
	// ������帱������Ϣ����
	void OnMessageEnterFamilyRepetion( int nServerID, CMessage *pMessage );
	
	// ������帱����Ϣ
	void OnMessageClearFamilyRepetionInfo( CMessage *pMessage );
	
	// ��ȡ������Ʒ�б����Ϣ����
	void OnMessageGetFamilyGoodsList( int nServerID, CMessage *pMessage );
	
	// ��ȡ����һ���Ʒ�б����Ϣ����
	void OnMessageGetFamilyExchangeGoodsList( int nServerID, CMessage *pMessage );
	
	// ���ͻ�ȡ������Ʒ�б����Ϣ��Ӧ
	void SendResponseGetFamilyGoodsList( int nServerID, int nErrcode, int nRoleID, int nEntityID, PBLeagueShopInfo &rLeagueShop, int nNpcTmpID );
		
	// ���ͻ�ȡ����һ���Ʒ�б����Ϣ��Ӧ
	void SendResponseGetFamilyExchangeGoodsList( int nServerID, int nErrcode, int nRoleID, int nEntityID, PBLeagueShopInfo &rLeagueShop, int nNpcTmpID );
	
	// ���ͼ�����Ʒ�б����仯��֪ͨ
	void SendNotifyChangeFamilyShopItem( int nFamilyID,  int nNpcTmpID, int nItemID, int nItemNum, int nComposeID = 0 );
	
	// ���ͼ���һ���Ʒ�б����仰��֪ͨ
	void SendNotifyChangeExchangeShopItem( int nFamilyID,  CGoodSInfo *pGoodInfo, int nGoodNum );

	// ����ʹ�ü����ع���Ʒ��֪ͨ
	void SendNotifyUseFamilyLeagueItem( int nFamilyID,  CGoodSInfo *pGoodInfo, int nGoodNum, int nRoleID, const char *pName );
	
	// ���м���һ�����Ϣ����
	void OnMessageFamilyExchange( int nServerID, CMessage *pMessage );
	
	// ���ͼ���һ�����Ϣ��Ӧ
	void SendResponseFamilyExchange( int nServerID, int nErrcode, int nRoleID, int nComposeID, int nNpcTmpID, int nItemNum );
	
	// ���Ӽ���һ�����Ϣ֪ͨ
	void OnMessageAddFamilyExchangeItem( int nServerID, CMessage *pMessage );
public:
	// ����������˳ɹ�����֪ͨ
	void SendNotifyInviteResult( CGatePlayer *pPlayer, int nRoleID, int nResult, const char *pName );
	
	// ID_S2C_RESPONSE_CREATFAMILY ��������Ļ�Ӧ 
	void SendResponseCreatFamily( int nServerID, int nRoleID, int nRet, int FamilyID, const char *pFamilyName,  int EntityID = 0 );

	// ID_S2C_RESPONSE_INVITEMEMBER	 �������Ļ�Ӧ
	void SendResponseIviteMember( int vServerID, int RoleID, const char *pName, int tRet, int EntityID = 0  );

	// ID_S2C_NOTIY_FAMILYINVITED	 �����������֪ͨ	 	
	void SendNotityFamilyInvited( CGatePlayer *pPlayer, int RoleID, int InviteID, const char *InviteName, int InviteFamilyID, const char *InviteFamilyName, int nMemberNum, int nGlory, int nPvpStar, int nNpcID, const char *pRooterName, int nFamilyLevel = 1, const char *pCorpsName = NULL, int nUionID = 0, const char *pUnionName = NULL );

	// ID_S2C_RESPONSE_REPLYFAMILYINVITE	�𸴼�������Ļظ� 
	void SendResponseReplyFamilyInvite( int vServerID, int RoleID, int nRet, int nResult, const char *pInvitingRoleName, int nFamilyID, const char *pFamilyName, int EntityID = 0 , int nCorpsID = 0, const char *pCorpsName = NULL, int nFamilyHeader = 0, int nCorpsHeader = 0, int nUnionID = 0, const char *pUnionName = NULL );

	// ID_S2C_RESPONSE_FAMILYAPPLY	 ����������Ļ�Ӧ	
	void SendResponseFamilyApply( int vServerID, int RoleID, int Result, int FamilyID, const char * FamilyName, int EntityID = 0 );					

	// ID_S2C_NOTIFY_MEMBERAPPLY	���������������������������֪ͨ	
	void SendNotifyMemberApply( CGatePlayer *pPlayer, int RoleID, int ApplyID, int Level, int Metier, const char *pName, int nFaceType, int nSex, int MapID, int LineID );		

	// ID_S2C_RESPONSE_REPLYMEMBERAPPLY �ظ��������������Ļ�Ӧ
	void SendResponseReplyMemberApply( int vServerID, int RoleID, int Errcode, int nResult, int nCharID, const char *pApplyName, int EntityID = 0 );						

	// ID_S2C_NOTIFY_FAMILYAPPLYSUCESS	 ֪ͨ�������������ɹ�
	void SendNotifyFamilyApplySucess( CGatePlayer *pPlayer, int RoleID, int Result, int FamilyID, const char *pFamilyName, int nCorpsID = 0, const char *pCorpsName = NULL, int nFamilyHeader = 0, int nCorpsHeader = 0, int nUnionID = 0, const char *pUnionName = NULL );					

	// ID_S2C_NOTIFY_FAMILYMEMBERADDED		֪ͨ�����Ա���³�Ա���루���������ͨ�ã�	
	void SendNotifyFamilyMemberAdded( int MemberRoleID, int nLevel, int nSex, int nFaceID, int nMetierID, const char *pName, const char *pManagerName, int *pRoleIDList, int RoleNum, int OnLine,  int nMapID = 0, int nLineID = 0 );

	// ID_S2C_RESPONSE_POSTAPPOINT		 ���������ְλ����Ļ�Ӧ
	void SendResponsePostAppoint( int vServerID, int RoldID, int Errcode, int MemberID, int Post,int EntityID = 0 );

	// ID_S2C_NOTIFY_POSTAPPOINT	 �������������ְλ��֪ͨ
	void SendNotifyPostAppoint( int ActionKind, int RoleID, const char *pManagerName, int *RoleIDList, int RoleNum, const char *pRoleName );

	// ID_S2C_RESPONSE_LEAVEFAMILY	�����Ա�뿪����Ļ�Ӧ
	void SendResponseLeaveFamily( int vServerID, int RoleID, int Errcode, int EntityID = 0 );				

	// ID_S2C_NOTIFY_MEMBERLEAVEFAMILY	�����Ա�뿪�����֪ͨ	 
	void SendNotifyMemberLeaveFamily( int vLeaverID, const char *pLeaverName, int *pRoleIDList, int RoleNum );

	// ID_S2C_RESPONSE_GETFAMILYMEMBERINFO ��ȡ�����Ա��Ϣ�Ļ�Ӧ	
	void SendResponseGetFamilyMemberInfo( int vServerID, int RoleID, int *PFamilyList, int nFamilyNum, int EntityID = 0 );				

	// ID_S2C_RESPONSE_FAMILYPROPERTY	 ��ȡ������Ϣ�Ļ�Ӧ������������Ϣ
	void SendResponseFamilyProperty( int vServerID, int RoleID, PBFamilyPropery &pbFamilData, int EntityID = 0 );

	// ID_S2C_RESPONSE_GETALLFAMILYINFO	 ��ȡ���м��������Ϣ�Ļظ���Ϣ  
	void SendResponseGetAllFamilyInfo( int vServerID, int RoleID, CMessageGetAllFamilyInfoResponse &pbFamilyInfo, int nCurPage, int nTotalPage, int EntityID = 0 );

	// ID_S2C_RESPONSE_GETAPPLYLIST	���������б�	
	void SendResponseGetApplyList( int vServerID, int RoleID,  CMessageGetApplyListResponse &pbApplyList, int EntityID = 0 );

	// ID_S2C_RESPONSE_KICKMEMBER	 �������˵Ļ�Ӧ
	void SendResponseKickMember( int vServerID, int RoleID, int KickedPlayerID, const char *pKickedName, int Errcode, int EntityID = 0 );

	// ID_S2C_NOTIFY_KICKPLAYER	 �������˵�֪ͨ
	void SendNotifyKickPlayer( const char *pName, int RoleID, int *pRoleIDList, int RoleNum, const char * pKickedName, int nKickedRoleID, const char *pManageName, int nManageID );

	// ID_S2C_RESPONSE_DISBANDFAMILY	��ɢ����Ļ�Ӧ
	void SendResponseDisbandFamily( int vServerID, int RoleID, int Errcode, int EntityID = 0 );

	// ID_S2C_NOTIFY_DISBANDFAMILY  ��ɢ�����֪ͨ
	void SendNotifyDisbandFamily( int FamilyID, int *pRoleIDList, int RoleNum );

	// ID_S2C_RESPONSE_CHANGENOTICE	�ı���幫��Ļ�Ӧ	
	void SendResponseChangeNotice( int vServerID, int RoleID, int Errcode, const char *pNotice, int EntityID = 0 );

	// ID_S2C_RESPONSE_APPOINTHEADER	 ����ת��ְλ�Ļ�Ӧ��Ϣ
	void SendResponseAppointHeader( int vServerID, int RoleID, int MemberID, const char *pRoleName, int Errcode, int EntityID = 0 );

	// ID_S2C_NOTIFY_CHANGERHEADER	����ת��ְλ��֪ͨ	
	void SendNotifyChangeHeader( int ManagerID, const char *pNanagerName, int MemberID, const char *pMemberName, int *pRoleIDList, int RoleNum );

	// ID_S2C_NOTIFY_FAMILYPEROPERTY	����������Ϣ֪ͨ
	void SendNotifyFamilyProperty( int nFamilyID );
	
	// ����������������б�Ļ�Ӧ��Ϣ
	void SendResponseClearFamilyApply( int nServerID, int nErrcode, int nRoleID, int nEntityID = 0 );
	
	// ���ͼ��������ŵ���Ϣ֪ͨ
	void SendNotifyJoinCorps( int nCorpsID, const char *pCorpsName, int *pRoleIDList, int nNum, int nJoinMethod = JOINCORPS_OTHERFAMILYCORPS, int nUnionID = 0, const char *pUnionName = NULL );
	
	// ����ȡ�����Ž�ɢ����Ϣ�ظ�
	void SendResponseCancelFamilyDisband( int nServerID, int tErrcode, int nRoleID, int nEntityID = 0 );
	
	// ���ͼ���ͨ��ı��֪ͨ
	void SendNotifyChangeFamilyNotice( const char *pNotice, int *pRoleIDList, int nRoleNum );
	
	// ����ˢ�¼�����Ϣ�Ļظ�
	void SendResponseRefreshFamilyInfo( int nServerID, int nRoleID, int nEntityID, PBFamilyMemberList &pbMemList );

	// ��������NPC������Ӧ
	void SendBidNpcResponse( int vServerID, int vResult, int vNpcID, int vMoney, int vRoleID, int vEntityID = 0 );

	// ���峤���ͱ���֪ͨ
	void SendMemberSubmitNotify( int vServerID, int vNpcID, const char *vFamilyName, int vFirst, int vRoleID, int vEntityID = 0 );

	// ��������NPC��ʱ��Ӧ
	void SendBidTimeOutResponse( int vServerID, int vNpcID, int *vFamilyID, int *vMoney, int vAttID, int vDefID, int Num );

	// �����峤������Ӧ
	void SendMemberSubmitResponse( int vServerID, int vResult, int vNpcID, int vRoleID, int vEntityID = 0 );

	// ����ս����ʼ��Ӧ
	void SendBattleStartResponse( int vServerID, int vNpcID, int *vFamilyID, int *vMoney, int vAttID, int vDefID, int Num );

	// ���Ͳ�ѯ�����Ӧ
	void SendNpcInfoResponse( int vServerID, int vNpcID, int vCountryID, int vRoleID, int vEntityID = 0 );

	// ���ͷ���NPC��Ӧ
	void SendAbortNpcResponse( int vServerID, int vResult, int vNpcID, int vRoleID, int vEntityID );

	// ���ͷ���NPC֪ͨ
	void SendAbortNpcNotify( int vServerID, int vNpcID, char *vName, int vRoleID, int vEntityID );

	// �������¾�����Ϣ
	void SendBidRestartNotify( int vServerID, int vNpcID );

	// ����ս�������Ϣ
	void SendBattleResultNotify( int vServerID, int vNpcID, int vAttFamilyID, int vDefFamilyID, int vWinSide );		

	// ����ս��������ս��Ϣ
	void SendPreBattleNotify( int vServerID, int vNpcID, int vAttFamilyID, int vDefFamilyID, int vMoney );	

	// ���Ϳ��跿���Ӧ
	void SendMakeRoomResponse( int vServerID, int vResult, int vMoney, char *vName, int vRoleID, int vEntityID );

	// ������ս�����Ӧ
	void SendChaRoomResponse( int vServerID, int vResult, int vFamilyID, int vRoleID, int vEntityID );

	// ����ͬ����ս��Ӧ
	void SendAgreeBattleResponse( int vServerID, int vResult, int vFamilyID, int vRoleID, int vEntityID );

	// ���ͷ��������Ӧ
	void SendAbortRoomResponse( int vServerID, int vResult, int vRoleID, int vEntityID );

	// ���ͷ�����ս��Ӧ
	void SendAbortChaResponse( int vServerID, int vResult, int vFamilyID, int vRoleID, int vEntityID );	

	// ���Ϳ��跿��֪ͨ
	void SendMakeRoomNotify( int vServerID, int vFamilyID );

	// ����ȡ������֪ͨ
	void SendAbortRoomNotify( int vServerID, int vFamilyID );

	// ������ս����֪ͨ
	void SendChaRoomNotify( int vServerID, int vSrcFamilyID, int vDesFamilyID );

	// ����ȡ������֪ͨ
	void SendAbortChaNotify( int vServerID, int vSrcFamilyID, int vDesFamilyID );
	
	
	// ���ü����Աְλ����Ϣ��Ϣ��Ӧ
	void SendResponseSetFamilyMemberPost( int nServerID, int nErrcode, int nMemberID, int nPost, int nRoleID, int nEntityID = 0 );

	// ��������Ļ�Ӧ
	void SendResponseLevelUPFamily( int nServerID, int nErrcode, int nLevel, int nRoleID, int nEntityID = 0 );

	// ���׼����Ǯ����Ϣ��Ӧ
	void SendResponseContributeFamilyMoney( int nServerID, int nErrcode, int nMoney, int nRoleID, int nEntityID = 0 );	

	// ��ռ��npc����ȡ�����Ǯ����Ϣ��Ӧ
	void SendResponseObtainFamilyMoney( int nServerID );	

	// ���ü���ְλ��֪ͨ
	void SendNotifySetFamilyPost( int *pIDList, int nNum, int nManagerID, const char *pManagerName, int nMemberID, const char *pMemberName, int nOldPost, int nNewPost );	

	// ����������֪ͨ	
	void SendNotifyLevelUPFamily( int *pIDList, int nNum, int nLevel, int nMoney, int nGlory, int nMaxMemberNum, int nMaxPresterNum, int nLevelMoney, int nLevelGlory, int nStability, int nReduceStability );

	// pvp�Ǽ�������֪ͨ
	void SendNotifyPVPStarLevelUP( int *pIDList, int nNum, int nPvPLevel );	
	
	// �������Ա������Ϣ
	void SendFamilyMsg( int nRoleID, CMessage *pMessage );
	
	// �������Ա������Ϣ
	void SendFamilyMsgByID( int nFamilyID, CMessage *pMessage );
	
	// ���ͼ���֪ͨ
	void SendFamilyNotify( CMessage *pMessage, int *pRoleIDList, int vRoleNum );
	
	// ���ͼ����Ǯ�ı��֪ͨ 
	void SendNotifyFamilyMoneyChanged( int nMoney, int nRoleID, int nFamilyID, int nReason, int tValue, const char *pName = NULL );	
	
	// ���ͼ�����ҫ�ı��֪ͨ
	void SendNotifyFamilyGloryChanged( int nGlory, int nRoleID, int nFamilyID, int nReason, int tValue, const char *pName = NULL );
	
	// ���ͼ����Ա���׶ȸı��֪ͨ	
	void SendNotifyFamilyContributeChanged( int nContribute, int nRoleID, int nFamilyID, int tValues );
	
	// ���ͼ������������֪ͨ
	void SendNotifyFamilyCanLevelUP( int nFamilyID );
	
	// ���͹������������Ϣ����
	void SendResponseBuyFamilyItem( int nServerID, int nRoleID, int nErrcode, int nRedPaperID, int nRedPaperNum, int nEntityID = 0  );
	
	// �����Ϣ
	void MakeMessage( CMessage &MsgHead, int RoleID, void *pMsg, int MsgID, int EntityID = 0 );	
	
	// ���ͽ�����帱������Ϣ��Ӧ
	void SendResponseEnterFamilyRepetion( CGatePlayer *pPlayer, int nErrcode, int nEntityID );	
		
	// ˢ�¼���״̬
	void ReFreshFamilyStatus();

	// �ı�������
	void ChangeFamilyCountry( int *pRoleIDList, int vRoleNum, int vCountryID );
	
	// ���ͼ��尲���ȸı��֪ͨ
	void SendNotifyFamilyStabilityChanged( int nStablity, int nRoleID, int nFamilyID, int nReason, int tValue, const char *pName = NULL, int nOnLineTime = 0 );
	
	// �ı���尲���ȵ���Ϣ֪ͨ
	void OnMessageChangeFamilyStability( CMessage *pMessage );	
	
	// �жϼ��尲�����Ƿ����
	void JudgeFamilyStability( CFamily *pFamily, CGatePlayer *pPlayer );
	
public:	  
	
	// ����pvp���ֵ���Ϣ
	void AddPvPScore( int nFamily, int nScore );
	
	// ���ļ����Ǯ, Freeze��ʾ��ʵ�����Ļ��Ƕ�������
	int ConsumeFamilyMoney( int nRoleID, int nMoney, bool bFreeze = false, int nReason = REASON_CHALLENGEWAR );
	
	// ���ļ����Ǯ
	int AddFamilyMoney( int nRoleID, int nMoney, const char *pName, bool bFreeze = false, int nReason = REASON_WARWIN );
	
public:						   	
	// �����������ݿ���Ϣ�Ļ�Ӧ��Ϣ
	int OnCreatFamilyDBInfo( CMessage* tpMessage, int FamilyObjID, int Para );
	
	// �յ����ƻ�Ӧ
	void OnAGIPSessionCreateGroup( SysProtocol* pproto, int nParam1, int nParam2);
	void OnAGIPTimeoutCreateGroup(int nParam1, int nParam2);
public:	
	// ��ʼ������������Ϣ
	int InitializeFamilyconfig(  );

	virtual void ReloadCfg( );

	// �������õĻص�����
	static void LoadFamilyConfigCallback(const char* pcConfigPath);
	
private:
	CWTimer mUpdateTimer;	// ��������µ�ʱ����
	CWTimer mDisbandTimer;	// �������ɢ��ʱ����
	bool	mIsLaunched;
	//CWTimer m

};

// #endif

