#ifndef _FRIEND_MODULE_H_
#define _FRIEND_MODULE_H_

#include "lk_hashmap.h"
#include "friendtype.h"
#include "friendmanager.h"
#include "protype.h"
#include "proclient_svr.h"
#include "coretype.h"
#include "friendmessage_pb.hxx.pb.h"
#include "property_pb.hxx.pb.h"
#include "servercore.h"
#include "servertool.h"
#include "dbinterface.h"
#include "teammodule.h"


class CEntityPlayer;

// ********************************************************************** //
// CFriendModule
// ********************************************************************** //

class MasterInfo
{
public:
	int	mMasterID;
	int mSlaveID;
	int mTime;
public:
	MasterInfo(){ }
	MasterInfo( int vMasterID, int vSlaveID ){ mMasterID = vMasterID; mSlaveID = vSlaveID; mTime = time(NULL); }
};

typedef lk::hash_map<int, CFriendItem, SERVER_CAP_PLAYER> FriendType ;
typedef lk::vector< MasterInfo, 1000 > MasterList;
#define MAX_LEVELUP_FRIEND_NUM  40 
#define MAX_LEVELUP_PLAYER_NUM  1000
#define MAX_SWORNTEAM_NUM		2000
struct CFriendBlessData
{
public:
	int mRoleID;
	int mLevel;
public:
	CFriendBlessData()
	{
		mRoleID = 0;
		mLevel = 0;
	}
};
class LevelUpFriendList : public lk::vector< CFriendBlessData, MAX_LEVELUP_FRIEND_NUM > 
{
public:
	LevelUpFriendList()
	{
		initailize();
	}
public:
	bool HasFriend( int nRoleID )
	{
		for ( iterator it = begin(); it != end(); ++it )
		{
			if ( (*it).mRoleID == nRoleID )
			{
				return true;
			}			
		}	
		return false;
	}
	void DeleteFriend( int nRoleID )
	{
		for ( iterator it = begin(); it != end(); ++it )
		{
			if ( (*it).mRoleID == nRoleID )
			{
				erase( it );
				break;
			}			
		}		
	}
	CFriendBlessData *GetData( int nRoleID )
	{
		for ( iterator it = begin(); it != end(); ++it )
		{
			if ( (*it).mRoleID == nRoleID )
			{
				return it;			
			}			
		}		
		return NULL;
	}
};

typedef lk::hash_map< int, LevelUpFriendList, MAX_LEVELUP_PLAYER_NUM > LevelUpPlayerList;
typedef lk::hash_map< int, CSwornTeam, MAX_SWORNTEAM_NUM > SwornTeamList;
class CFriendModule : public CLogicModule, public CDBReceiver, public CSingleton< CFriendModule >
{
	private:
		FriendType mRels;
		MasterList mMasterList;
		CWTimer	   mClearTimer;
		LevelUpPlayerList mLevelUpPlayerList;
		SwornTeamList mSwornTeamList;
		//typedef lk::hash_map<int, CPlayerRels, SERVER_CAP_PLAYER>::iterator iterator;
		//typedef lk::hash_map<int, CPlayerRels, SERVER_CAP_PLAYER>::const_iterator const_iterator;

	public:
		static char sModuleName[ NAME_LENGTH ];
		CFriendModule():CLogicModule(sModuleName)
		{
			if( mShmPtr->GetInitMode() == SHM_INIT ) 
			{
				mLevelUpPlayerList.initailize();
				mRels.initailize();
				mSwornTeamList.initailize();
			}
		}
	public:
		CFriendBlessConfig mFriendBlessConfig;
	public:	
		CFriendBlessConfig *GetFriendBlessConfig(){ return &mFriendBlessConfig; }
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
		virtual void OnCreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst );
		// ����ʵ��
		virtual void OnDestroyEntity( CEntity* pEntity, int vCode );
		// �洢����
		virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );

		// ��������
		virtual void OnLoadConfig( ) ;

		// ����������ϼ��
		virtual bool OnCheckLaunch( ) { return true; }

		static unsigned int CountSize();

		void OnGateMessage( CMessage* pMessage );
		void SendRouterMsg2Client( CMessage* pMessage );


		CFriendItem* GetPlayerFriendItem(int nRoleID);

	//private:

		// ****�������ܲ���****
		void PlayerAddFriendByName ( CEntityPlayer* pPlayer, const  char* strDesName ); // �Ӻ��Ѻ���
		void PlayerAddFriendByID ( CEntityPlayer* pPlayer, int nDesCharID ); // �Ӻ��Ѻ���
		void PlayerReplyAddFriend( int nSrcPlayerID, int nReplyCharID,  const char* szReplyName, int nHead
			, int nReplySex, int nApplyCode, unsigned char nIsFullList , unsigned char nIsReqInReplyLst, int nReplyNationID ); // ��������ظ�
		void SendErrorCode ( int nCharID, EFriendModuleErrorCode ecode );
		void AskGateFriendInfo( int nRequesterID, const CFriendItem& rItem, bool bIsRefresh = false );
		void SendMyStatus2Friends( int nMyCharID, const std::vector<int>& rList, unsigned char nStat, int nRels );
		void SendMyStatus2Gate( int nMyCharID, unsigned char nStat );

		void InsertFriendData( int nCharID, const CFriendItem& rItem );
		void DelMember( CEntityPlayer* pPlayer, int nDesCharID, int oprType );

		// ****�����ݿ�ͨ�Ų���****

		// ȥ���ݿ�����ֻص�
		void AddBlackCallBack( CMessage* pMsg, int vparam1, int vparam2 );
		void OnPlayerAddFriendCallBack( CMessage* pMsg, int vparam1, int vparam2 );

		void CommonSqlCallBack( CMessage* pMsg, int vparam1, int vparam2 );

		// on message
		void OnMessageAddFriendOffLine( int nRequesterID, const char* szDesName );
		void OnPlayerReplyAddFriend( CEntityPlayer* pPlayer, int nSrcPlayerID, int nArgCode ); // �Ƿ�ͬ��
		void OnMessagePlayerChangeStatus( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessageRecvOnlineFriends( CMessage* pMsg );
		void OnPlayerSendMessageRet( CMessage* pMsg );
		void OnReplayerAddRequesterInServer( CMessage* pMsg );
		void OnMessageAddFriendInDesServer( CMessage* pMessage );
		void OnMessagePlayerDelFriends( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessagePlayerChangeGroupName( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessagePlayerChangeFriendGroup( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessagePlayerSendMsg( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessagePlayerMoveBlack( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessagePlayerAddBlack( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessagePlayerLockEnemy( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessagePlayerRereshFriendState( CEntityPlayer* pPlayer, CMessage* pMsg );

		void OnMessageGetCharIDFromGate( CMessage* pMessage );
		void OnMessageAddFriend( CMessage* pMessage );
		void DisposeAddFriend( CEntityPlayer* pPlayer, int nDesID );
		void OnPlayerBeKilled( CEntityPlayer* pSrcPlayer, CEntityPlayer* pDesPlayer );

		void OnMessageChangeMasterRequest( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessageGetSlaveRequest( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessageQueryPlayerRequest( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessageRemoveSlaveRequest( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessageRemoveMasterRequest( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessageAlterMasterPercentRequest( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessageGetLowPlayerRequest( CEntityPlayer* pPlayer, CMessage* pMsg );
		void OnMessageAnswerChangeRequest( CEntityPlayer* pPlayer, CMessage* pMsg );

		void OnMessageChangeMasterResponse( CMessage* pMsg );
		void OnMessageChangeMasterNotify( CMessage* pMsg );
		void OnMessageGetSlaveResponse( CMessage* pMsg );
		void OnMessageSlaveLevelUpNotify( CMessage* pMsg );
		void OnMessageSlaveOnOffNotify( CMessage* pMsg );		
		void OnMessageQueryPlayerResponse( CMessage* pMsg );
		void OnMessageRemoveSlaveResponse( CMessage* pMsg );
		void OnMessageRemoveSlaveNotify( CMessage* pMsg );
		void SendSlaveOnOffNotify( CEntityPlayer *pSrcPlayer, int vOnline );
		void SendSlaveValueNotify( CEntityPlayer *pSrcPlayer );
		void OnMessageRemoveMasterResponse( CMessage* pMsg );
		void OnMessageRemoveMasterNotify( CMessage* pMsg );
		void SendAddMasterPointRequest( CEntityPlayer *pPlayer, int vRawPoint );
		void OnMessageAddMasterPointNotify( CMessage* pMsg );
		void OnMessageAnswerChangeNotify( CMessage* pMsg );
		
		// �ı�״̬֪ͨ
		void OnMessageFriendChangeStatusNotice( CMessage* pMsg );

		// ��ϵ��״̬�ı�֪ͨ
		void OnMessageContacterStatusNotice( CMessage* pMsg );

		// ���ⲿ�ӿ�
		EPlayerRels GetRel2Me( int nCallerCharID, int nFriendID );

		// ���ú��ѹ�ϵ
		int SetRel2Me( CEntityPlayer *pPlayer, int nFriendID, EPlayerRels eRels, EOprFriendCode eOprCode );
		
		bool IsInBlack( int nAcharid, int nBcharid ); // �������

public:
		void SendAllFriendNotice( CEntityPlayer* npPlayer );

		// ***********************************************************
		//  Function:		MakeRouterMessageByID	
		//  Description:	�����շ����ID����һ��·����Ϣ
		//  Input:			ԴID��Ŀ��ID���Ƿ����ң� ��ϢID����Ϣ��
		//  OutPut:			CMessage
		//  Return:			�ɹ�=0
		//  Others:
		//  Date:			2008.11.4
		// **********************************************************
		template< typename MSG_T >
		int MakeRouterMessageByID( unsigned int nSrcID, unsigned int nDesID, unsigned char nIstoPlayer
			, unsigned int nMessageID, MSG_T& rMsgpare,  CMessage* pMessage )
		{
			rMsgpare.mutable_router()->set_srccharid( nSrcID );
			rMsgpare.mutable_router()->set_descharid( nDesID );
			rMsgpare.mutable_router()->set_send2player( 0 );
			rMsgpare.mutable_router()->set_routertype( CMessageRouter::ROUTER_CHAR );
			pMessage->set_msgpara((uint32_t) &rMsgpare);
			pMessage->mutable_msghead()->set_messageid( nMessageID );
			return 0;
		}

		// ***********************************************************
		//  Function:		MakeRouterMessageByName	
		//  Description:	�����շ������������һ��·����Ϣ
		//  Input:			ԴID��Ŀ��ID���Ƿ����ң� ��ϢID����Ϣ��
		//  OutPut:			CMessage
		//  Return:			�ɹ�=0
		//  Others:
		//  Date:			2008.11.4
		// **********************************************************
		template< typename MSG_T >
		int MakeRouterMessageByName( const char* szSrcName, const char* szDesName, unsigned char nIstoPlayer
			, unsigned int nMessageID, MSG_T& rMsgpare, CMessage* pMessage )
		{
			rMsgpare.mutable_router()->set_srcname( szSrcName );
			rMsgpare.mutable_router()->set_desname( szDesName );
			rMsgpare.mutable_router()->set_send2player( 0 );
			rMsgpare.mutable_router()->set_routertype( CMessageRouter::ROUTER_NAME );
			pMessage->set_msgpara((uint32_t) &rMsgpare);
			pMessage->mutable_msghead()->set_messageid( nMessageID );
			return 0;
		}
public:
	void LoadFriendBlessConfig();
	void FriendLevelUp( CEntityPlayer *pPlayer, int nUpLevel );	
	void SendFriendLevelUpNotify( CEntityPlayer *pPlayer, int pDesCharID, CEntityPlayer *pDesPlayer = NULL );
	void OnMessageFriendBlessRequest( CEntityPlayer *pPlayer, CMessage *pMsg );
	void OnRouterMsgFriendLevelUpNotify( CMessage *pMsg );
	void SendFriendBlessResponse( CEntityPlayer *pPlayer, int nErrcode );
	void SendNotifyFriendBless( CEntityPlayer *pPlayer, int nRoleID, const char *pFriendName, int nExp );
	void OnRouterFriendBlessNotify( CMessage *pMsg );
	void SetLevelUpFriendID( int nRoleID, CFriendBlessData &rData );
	void DeleteLevelUpFriendID( int nRoleID, int nFriendRoleID );
	bool HasLevelUpFriendID( int nRoleID, int nFriendRoleID );
	void DeleteLevelUpFriendList( int nRoleID );
	CFriendBlessData *GetFriendBlessData( int nRoleID, int nFriendRoleID );

	// ���غ���ף�����õĻص�����
	static void LoadFriendBlessConfigCallback(const char* pcConfigPath);

	// ���������ϵ��
	int UpdateLatestContact(int nCharID, int nContacterID);
	int NotifyLastContacterToClient(int nCharID, int nContacterID);
	int NotifyLastContacterToGate(int nSenderID, int nReceiverID);
	int UploadContacterListToGate(int nCharID);
	void GetContacterListInfo( int nRequesterID, CFriendItem& rItem);
	void OnRouterMsgLastContacter(CMessage* pMessage);

	// �ж��б���������֮������ܶ��Ƿ񳬹�ĳ��ֵ
	bool JudgeIntimacyDegree( int *pRoleIDList, int nNum, int nDegree );

	// ���������ʱ����ĳ����ҵ����ܶ�
	void UpdateIntimacyDegree( CEntityPlayer *pPlayer );

	int GetIntimacyDegree( int nRole1, int nRoleID2, int &rIntimacyDegree );
	// �ı�һ������໥֮������ܶ�
	void ChangeGroupIntimacyDegree( int *pRoleIDList, int nNum, EM_EntimacyChangeType nType, int nValue = 0 );

	// �����޸����ܶȵ�֪ͨ
	void SendModifyIntimacyNotify( int nRoleID, int nChangedValue, int nIntimacy, EM_EntimacyChangeType nType, int nFriendID, int nUpdateTime = 0, int nDailyIntimacy = 0 );

	// ���͸���ͬʱ����ʱ���֪ͨ
	void SendModifyLastTimeAllOnLineNotify( CEntityPlayer *pPlayer, int nRoleID, int nTime );

	// ������ߵ�ʱ��ͬ�����ͬʱ����ʱ��
	void UpdateLastTimeAllOnLine( CEntityPlayer *pPlayer );

	// ����������ҵ����ܶ�
	void ChangeIntimacy( int nRoleID1, int nRoleID2, EM_EntimacyChangeType eType, int nValue = 0 );
	
	// ����������֮������ܶ�
	void UpDateTeamIntimacy( CTeam* tpTeam );

	// ������ݵ���Ϣ����
	void OnMessageCreateSwornTeam( CEntityPlayer *pPlayer, CMessage *pMsg );
	// ������ݵĻ�Ӧ��Ϣ
	void SendResponseCreateSwornTeam( CEntityPlayer *pPlayer, int nErrcode );
	// ������ݵ�֪ͨ
	void SendNotifyCreateSwornTeam(  CEntityPlayer **pPlayer, int nTeamCount, CSwornTeam *pSwornTeam );	
	// �뿪������������
	void OnMessageLeaveSwornTeam( CEntityPlayer *pPlayer, CMessage *pMsg );
	// �뿪����������Ϣ��Ӧ
	void SendResponseLeaveSwornTeam( CEntityPlayer *pPlayer, int nErrcode );
	// �뿪����������Ϣ֪ͨ
	void SendNotifyLeaveSwornTeam( CEntityPlayer *pPlayer, CSwornTeam *pSwornTeam );
	// ��������
	void OnMessageKickSwornMember( CEntityPlayer *pPlayer, CMessage *pMsg );
	// ���˻�Ӧ
	void SendResponseKickSwornMember( CEntityPlayer *pPlayer, int nErrcode );
	// ����֪ͨ
	void SendNotifyKickSwornMember( CEntityPlayer *pPlayer, CSwornTeam *pSwornTeam, int nRoleID );
	// ��ɢ�������
	void OnMessageDisbandSwornTeam( CEntityPlayer *pPlayer, CMessage *pMsg );
	// ��ɢ�������Ļ�Ӧ
	void SendResponseDisbandSwornTeam( CEntityPlayer *pPlayer, int nErrcode );
	// ��ɢ��������֪ͨ
	void SendNotifyDisbandSwornTeam( CSwornTeam *pSwornTeam );	
	// ���ͽ���������Ϣ
	void SendNotifySwornInfo( CEntityPlayer *pPlayer, CSwornTeam *pSwornTeam );		
	// �ı����������Ƶ�����
	void OnMessageChangeSwornName( CEntityPlayer *pPlayer, CMessage *pMsg );
	// �ı����������ƵĻ�Ӧ
	void SendResponseChangeSwornName( CEntityPlayer *pPlayer, int nErrcode );
	// �ı����������Ƶ�֪ͨ
	void SendNotifyChangeSwornName( CSwornTeam *pSwornTeam );
	// �ؽ���ݵ���Ϣ����
	void OnMessageRebuildSworn( CEntityPlayer *pPlayer, CMessage *pMsg );
	// ���ʹ�����ݵ���Ϣ��Ӧ
	void SendResponseRebuildSworn( CEntityPlayer *pPlayer, int nErrcode );
	// �������½�ݵ���Ϣ֪ͨ
	void SendNotifyRebuildSworn( CEntityPlayer **pPlayer, int nTeamCount, CEntityPlayer **pNewMember, int nNewMemberNum, CSwornTeam *pSwornTeam );

	// ����һ�����������Ϣ
	int InsertSwornTeam( int nSwornID, CSwornTeam &rSwornTeam );
	// ��ȡһ�����������Ϣ
	CSwornTeam *GetSwornTeam( int nSwornID );
	// ɾ��һ�����������Ϣ
	int DeleteSwornTeam( int nSwornID );
	// ������ݵ�DB��Ϣ
	int CreateSwornDBInfo( CSwornTeam &rSwornTeam );
	// ɾ����ݵ�DB��Ϣ
	int DeleteSwornDBInfo( int nSwornID );
	// ��ȡĳ�˵Ľ����Ϣ
	int GetSwornDBInfo( CEntityPlayer *pPlayer );
	// ���½����Ϣ
	int UpdateSwornDBInfo( int nSwornID, CSwornTeam &rSwornTeam );
	// ������ҽ��ID
	int UpDateRoleSwornID( int nRoleID, int nSwornID );
	// ��ȡ�����Ϣ
	int OnSessionGetSwornDBInfo( CMessage *pMsg, int nParam1, int nParam2 );
	// ��ȡ�����Ϣ��ʱ
	int OnTimeOutGetSwornDBInfo( int nParam1, int nParam2 );
	// ���ط��صĽ����Ϣ
	void OnRouterMsgSwornInfo( CMessage *pMsg );
	// ���ط��ص��뿪��ݵ���Ϣ
	void OnRouterMsgLeaveSwornTeamNotify( CMessage *pMsg );
	// �����������ܶȵ���Ϣ
	void OnRouterMsgModifyIntimacy( CMessage *pMsg );
	// ����֪ͨ
	void OnRouterMsgKickSwornMember( CMessage *pMsg );
	// ��ɢ��ݵ���Ϣ֪ͨ
	void OnRouterMsgDisbandSwornTeam( CMessage *pMsg );
	// ��ݸ�����֪ͨ��Ϣ
	void OnRouterMsgChangeSwornName( CMessage *pMsg );
	// ��������ͬʱ��¼ʱ��
	void OnRouterMsgModifyLastTimeAllOnLine( CMessage *pMsg );
	// �����Ϊ���ܶȽ����Լ��ٵ�ʯͷ����
	int CheckItemNumAffectedByIntimacy( int nSrcCharID, int nDesCharID, int &rNum );	
	// �������н�ݳ�Ա�Ľ�����ܶ�
	int CheckTeamSwornIntimacy( CEntityPlayer *pPlayer, int nValue );
};

#endif
