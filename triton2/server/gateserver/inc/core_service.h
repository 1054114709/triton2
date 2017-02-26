#ifndef _GATECORE_SERVICE_H_
#define _GATECORE_SERVICE_H_

#include "module_manager.h"	  

// ***************************************************************
//  Class:	CPlayerManager
//  Responsibility:
//  		1. ��֯CGatePlayer����, 
//  		2. �ṩ�����ʺ�,����ɾ����ɫ, ����, ��������, ������Ϸ���߼�
//  Restirct:
//  		1. ����Ӧ�������Ϣ
//	Others:	 		
//  Date:	2009-07-08
//
// ***************************************************************
enum EAfterSendGateError
{
	em_keep_connect,
	em_need_disconnect
};

class CBlackList
{
	public:
		typedef lk::hash_map< int, lk::CString128,  MAXPLAYERNUM > BLACKLIST;

		bool Load();
		bool Append(int nServer, int nRoleID, const char* szName);
		bool Find(int nRoleID);
		const char* GetStr(int nRoleID);
		bool Remove(int nRoleID);
		int	 Size();

		CBlackList()
		{
			if ( CObj::msCreateMode )
			{
				Initialize();
				Load();
			}else
			{
				Resume();
			}
		}

		~CBlackList()
		{

		}

		int Initialize()
		{			
			mList.initailize();
			return 0;
		}

		int Resume()
		{
			return 0;
		}

	private:
		BLACKLIST mList;
};
struct CGlobalData
{
public:
	enum Status
	{
		EGLOBAL_STATUS_PREPARETELE	 = 0,	// ׼�����
		EGLOBAL_STATUS_INGLOBALSCENE = 1,	// ��ȫ�ֳ�����
	};
public:
	int mRoleID;				// ����Ľ�ɫID
	int mGlobalWorldID;			// Ŀ�곡��������ID
	int mStatus;				// ״̬
	int mTeleTime;				// ��ʼ���͵�ʱ��
public:
	CGlobalData()
	{
		mRoleID = 0;
		mGlobalWorldID = 0;
		mStatus = EGLOBAL_STATUS_PREPARETELE;
		mTeleTime = time(NULL);
	}
};
class CPlayerManager : public CSingleton< CPlayerManager >
{
	private:
		typedef std::pair< int, int > PLAYERTYPE;
		typedef lk::hash_map< int, int , PLAYER_AT_GATE_CAP> PLAYERCONTAINER;
		typedef lk::hash_map< int, int , PLAYER_AT_GATE_CAP>::iterator	PLAYERITER;
		typedef lk::hash_map< lk::string<NAME_LENGTH>, int, PLAYER_AT_GATE_CAP > PLAYERNAME_MAP;
		typedef lk::hash_map< int, CGlobalData, PLAYER_AT_GATE_CAP > GLOBALSCENEPLAYERMAP;
		//typedef lk::vector<int ,6> MACACCOUNTVECTOR;
		//typedef lk::hash_map< lk::string<16>, MACACCOUNTVECTOR, 200 > MACPLAYERNUM;
		//typedef lk::hash_map< int ,MACPLAYERNUM,PLAYER_AT_GATE_CAP > IPMAC_MAP;

		// �ڳ����е����, �ý�ɫID��Ϊ����
		PLAYERCONTAINER	mPlayerInSceneByChar;

		// �ڳ����е����, �ý�ɫName��Ϊ����
		PLAYERNAME_MAP	mPlayerInSceneByName;

		// ����������� account ����
		PLAYERCONTAINER	mGatePlayerByAcct;

		// Ŀǰ��Gate�������ӵ��������  �˿ں�����
		PLAYERCONTAINER	mPlayersConnected;

		// ��Login push������,�ȴ���¼����� account ����
		PLAYERCONTAINER	mPlayerInWait;		

		GLOBALSCENEPLAYERMAP mGlobalScenePlayerMap;

		
	public:
		// ���õ�¼�Ľ�ɫ����
		CBlackList mBlackList;

		// ע���ɫID��GatePlayer��������ϵ
		void RegistRoleIDIndex( CGatePlayer* tpPlayer);

		// ע���˺�IDԽGatePlayer�Ĺ�ϵ
		bool RegistAccountIndex( CGatePlayer* tpPlayer );

		// �����ɫID��GatePlayer��������ϵ
		void RemoveRoleIDIndex( CGatePlayer* tpPlayer);

		// ����ʺ�ID��GatePlayer��������ϵ
		void RemoveAccountIDIndex(CGatePlayer* tpPlayer);

		// ע���ɫName��GatePlayer��������ϵ
		void RegistRoleNameIndex(CGatePlayer* tpPlayer);

		// �����ɫName��GatePlayer��������ϵ
		void RemoveRoleNameIndex(CGatePlayer* tpPlayer);

		// ע����Ҷ˿ڵĹ�ϵ
		void UnRegistPlayerComm(CGatePlayer* tpPlayer);

		// ��������˿ڵĹ�ϵ
		void RegistPlayerComm(CGatePlayer* tpPlayer);

		// ��鳡�����ҳ�ʱ
		void CheckPlayerActiveTimeout();

		// �������ÿ��mac��ַ������
	//	void UpdatePlayerNumPerMac(CGatePlayer* tpPlayer);
	public:	//-- ����

		// ����������ݣ��������ٶ���
		void ClearScenePlayer( CGatePlayer* tpPlayer);

		// ����������Ҷ���
		void DestroyGatePlayer( CGatePlayer* tpPlayer, int nLeaveReason = 0xFF);

		// ���糡������ʱ�����Ϳ糡����������vCharID
		int SendRedirErrCode( int vCharID, int vErrorCode, int vLineID, int vMapID );

		// �������ش�����Ϣ
		void SendGateErrorNotice(CGatePlayer* tpPlayer, int nErrCode, 
				EAfterSendGateError after, const char* pszErrString = NULL);

		// �����Ͽ���������ͻ��˵����ӣ��ͻ��˲�����Ӧ 
		void OnlyDisconnectClient(CGatePlayer* tpPlayer);

		// ���׼������Gate
		void EnterGate(int nCommHandle, int nAccountID, int nLoginToken, int nAdultFlag, int nUserStatus, int nGameID, unsigned int nCpuID, unsigned int nDiskID);

		// ɾ��pHost�ϵ��������
		void RemovePlayerInScene(CSceneServer* pHost);

		// �ߵ��������
		void KickOffGatePlayer(CGatePlayer*, unsigned int nAnotherIP);
		// �߳������
		void KickOffScenePlayer(CGatePlayer*, unsigned int nAnotherIP);


		// ��ҽ�����Ϸ
		void PlayerEnterGameWrapper(int nAccountID, int nRoleID, const char* szMac);
		// ��erating ���������Ϸ����
		void SendEnterGameProto2ERating(CGatePlayer* tpPlayer, int nServerID);
		// ��GameServer���������Ϸ����
		void PlayerEnterGame(CGatePlayer* tpPlayer );


		// ��ȡ��ɫ
		void ObtainCharsWrapper(int vCommHandle);
		// erating �����ý�ɫ�б���Ϣ
		void SendObtainCharsProto2ERating(CGatePlayer* tpPlayer);
		// �����ݿⷢ��ȡ�ý�ɫ�б���Ϣ
		void SendObtainChars2DB(CGatePlayer* tpPlayer);


		// ������ɫ
		void CreateCharWrapper(int vCommHandle, const char* szCharName, int nSexID, int nFaceType);
		// �����ݿⷢ�ʹ�����ɫ����
		void SendCreateChar2DB(CGatePlayer* tpPlayer, int nRoleID);
		// erating ������ɫ
		void SendCreateCharProto2ERating(CGatePlayer* tpPlayer);


		// ɾ����ɫ
		void DeleteCharWrapper(int vCommHandle, int nCharID, const char* szPasswd, int nPasswdType);
		// �����ݿⷢ��ɾ���������
		void SendDeleteChar2DB(CGatePlayer* tpPlayer, int nCharID );
		// �����ݿⷢ��ɾ����ɫ������������
		void SendDelRoleRelationData2DB( int nAccountID, int nRoleID );
		// ��erating ����ɾ�����ʱ��������֤
		//void SendPasswdVerifyProto2ERating(CGatePlayer* tpPlayer, int nCharID,  const char* szPasswd, uint32_t nPasswdType);
		// eratingɾ����ɫ
		void SendDeleteRoleProto2ERating(CGatePlayer* pPlayer, int nRoleID);

		// ����ɾ����ɫ�Ļ�Ӧ��Ϣ
		void SendResponseDelteRole( CGatePlayer *tpPlayer, int nErrcode, int nRoleID, int nRoleDeleteStatus, int nDelteStatusLeftTime );
		
		// ������ҵ���Ϣ
		void UpDatePlayerInfo( CGatePlayer *tpPlayer, int nRoleID, int nParam1, int nParam2 );

		// ��ERATING ���͵ǳ���Ϣ
		// nFlag = 3, �쳣�˳�  nFlag = 1, �����˳�   nFlag = 2, ������֪ͨ
		void SendUserLogoutProto2ERating(CGatePlayer* tpPlayer, CMessagePlayerLeaveMapNotice* tpPlayerLeave, int nFlag = 1);
		
		// ������ҵ��ʺ���Ϣ
		void UpDatePlayerAccountInfo( CGatePlayer *tpPlayer, int nParam1, int nParam2 );


		// ����Ŷ�
		void QueuePlayer(CGatePlayer* tpPlayer, CSceneServer* tpHost);
		// ���ŶӶ������Ƴ����
		void RemovePlayerFromQueue(CGatePlayer* tpPlayer);
		
		// ��ĳ�����ҵ���ҷ�����Ϣ
		void SendCountryMessage( CMessage *pMessage, int nCountryID );

		// ��gate��ֱ�Ӹ�ĳ�����ҵ���ҷ�����Ϣ
		void SendCountryMessageFromGate( CMessage *pMessage, int nCountryID );
		
		// ��gate��ֱ�Ӹ��������ҷ�����Ϣ
		void SendWorldMessageFromGate( CMessage *pMessage, int vMapID = 0 );
		
		// ������ҲƲ�����
		int ResetRolePassword( int nRoleID );
		
		// ������ҵ�����
		void UpDateRolePassword( int nAccountID, int nRoleID, const char *pPassword, int nParam1, int nParam2 );

		// ����һ����ҵ�ȫ�ֳ����б���
		void InsertPlayerToGlobalSceneMap( int nAccountID, CGlobalData &rGlobalData );

		void DeletePlayerFromGlobalSceneMap( int nAccountID );

		// �߳������������������
		void KickPlayerInGlobalScene( int nAccountID = 0 );

		// �ж�����Ƿ���������Ӫ
		bool IsPlayerInGlobalScene( int nAccountID );

		// �����߳�ȫ�ֳ�����ҵĽ��֪ͨ��Ϣ
		void SendKickGlbalPlayerACK( int nAcccountID, int nRoleID, int nRoleWorlID );

		// �߳���ҳ�ʱ
		void OnTimeOutKickGlobalPlayer( int nAccountID, int nRoleID );

		// ��ȡȫ����Ϣ
		CGlobalData * GetGlobalData( int nAccountID );

	public: //-- �ӿ�

		unsigned short GetPlayerCountryLineID( CGatePlayer* vpPlayer );

		// �õ������е����,ͨ��ͨѶ�˿�ID
		CGatePlayer* GatePlayer( int vCommHandle );

		// �����ʺ�ȡ�����
		CGatePlayer*  GetPlayerByAcct(int nAccountID);

		// ͨ����ɫID, �õ������е����
		CGatePlayer* ScenePlayer( int vCharID );

		// ͨ����ɫ����, �õ������е����
		CGatePlayer* ScenePlayer( const char* pName );

		// �õ�������gate�ϵ��˺Ÿ���
		unsigned int GetWorldPlayerNumber( ) { return mGatePlayerByAcct.size(); }

	public:
		static CSharedMem* mShmPtr;

		void * operator new( size_t tsize );
		void   operator delete( void *pPointer );

		static unsigned int CountSize();

		CPlayerManager();
		~CPlayerManager();

		int Initialize();
		int Resume();
};

// ***************************************************************
//  Class:	CCoreService
//  Responsibility:
//  		1. ������Ӧ��Ϣ
//  		2. ���𴥷�OnTimer�¼�
//  Restirct:
//  		1. ��CPlayerManager����
//	Others:	 		
//  Date:	2009-07-08
//
// ***************************************************************

class CCoreService: public GateServer::CDataModule, public CSingleton<CCoreService>
{
	public:	 //-- �����Ϣ	
		
		virtual bool IsLaunched() { return true; }

		// ��������ɫ�б�
		void OnMessagePlayerObtainCharsRequest(int vCommHandle, CMessage* tpMessage);
		// ��ӦErating���صĽ�ɫ�б���Ϣ
		void OnAGIPMsgRoleListResponse(SysProtocol* pSysProto, int nParam1, int nParam2);
		// ��������ݿⷵ�صĽ�ɫ�б���Ϣ
		void OnSessionObtainChars( CMessage* tpMessage, int vParamater1, int vParamater2 );
		// �����erating���ؽ�ɫ�б�ʱ		
		void OnAGIPMsgRoleListTimeOut(int nParam1, int nParam2);
		// �����dbserver���ؽ�ɫ�б�ʱ		
		void OnTimeOUtObtainChars(int nParam1, int nParam2);
		
		// ���ʱ��ȡ����
		void SendGetGlobalRoleData2DB( CGatePlayer *pPlayer );
		// ���ʱ�����ݴ���
		void OnSessionGetGlobalRoleData( CMessage* tpMessage, int vParamater1, int vParamater2 );
		// ���ʱ�����ݻ�ȡ��ʱ
		void OnTimeOutGetGlobalRoleData(int nParam1, int nParam2);

		// ��Ҵӳ����뿪
		void OnMessagePlayerLeaveMapNotice( int vCommHandle, CMessage* tpMessage);
		// ��Ӧerating���ص��뿪��Ϸ��Ϣ
		void OnAGIPMsgUserLogoutResponse(SysProtocol* pSysProto, int nParam1, int nParam2);	
		// ����erating��������뿪��ʱ
		void OnAGIPMsgUserLogoutTimeOut(int nParam1, int nParam2);


		// �������ɾ����ɫ
		void OnMessagePlayerDeleteCharRequest( int vCommHandle, CMessage* tpMessage);
		// ɾ����ɫʱ���2������
		void OnMessageCheckRolePwd( int vCommHandle, CMessage *pMessage  );
		// ��Ӧerating���ص�ɾ����ɫ��Ϣ
		void OnAGIPMsgDeleteRoleResponse(SysProtocol* pSysProto, int nParam1, int nParam2);
		// ��Ӧerating���صİ�ȫ����֤��Ϣ
		//void OnAGIPMsgPasswdVerifyResponse(SysProtocol* pSysProto, int nParam1, int nParam2);
		// ��������ݿⷵ�ص�ɾ����ɫ��Ϣ
		void OnSessionDeleteChar( CMessage* tpMessage, int vParamater1, int vParamater2 );
		// ����Eratingɾ����ɫ��ʱ
		void OnAGIPMsgDeleteRoleTimeOut(int nParam1, int nParam2);
		// �������ݿ�ɾ����ɫ��ʱ
		void OnTimeOutDeleteChar(int nParam1, int nParam2);
		// ����ɾ����ɫ��ʱ��������֤��ʱ
		//void OnAGIPMsgPasswdVerifyTimeOut(int nParam1, int nParam2);
		
		// ȡ��ɾ����ɫ����Ϣ����
		void OnMessageCancelDeleteRole( int vCommHandle, CMessage *pMessage  );



		// �����������ɫ
		void OnMessagePlayerCreateCharRequest( int vCommHandle, CMessage* tpMessage);
		// ��������ݿⷵ�صĴ�����ɫ��Ϣ
		void OnSessionCreateChar( CMessage* tpMessage, int vParamater1, int vParamater2 );
		// ��ӦErating���صĴ�����ɫ��Ϣ
		void OnAGIPMsgCreateRoleResponse(SysProtocol* pSysProto, int nParam1, int nParam2);
		// ��ӦErating������ɫ��ʱ
		void OnAGIPMsgCreateRoleTimeOut(int nParam1, int nParam2);
		// ��ӦDB������ɫ��ʱ
		void OnTimeOUtCreateChar(int nParam1, int nParam2 );



		// �����¼����������ҽ�Ҫ����������Ϣ
		void OnMessagePlayerEnterGateNotice	( CMessage* pMessage );
		// ����ͻ��˵�½��������
		void OnMessagePlayerLoginGateRequest( int vCommHandle, CMessage* pMessage );
		// ���������˻�Ӧ��Ϣ
		void OnMessageKickOffPlayerResponse(int nServerID, CMessage* pMessage);

		void OnMessageEntityGMMove( int nServerID, CMessage* pMessage );
		void OnMessageRoleMove( int nServerID, CMessage* pMsg );

		// ������ҷ��͵Ľ�����Ϸ��������
		void OnMessagePlayerEnterGameRequest( int vCommHandle, CMessage* pMessage );
		// ��Ӧerating���صĽ�����Ϸ������Ϣ
		void OnAGIPMsgEnterGameResponse(SysProtocol* pSysProto, int nParam1, int nParam2);
		// ������֪ͨ�����Ѿ�׼���ý�����ҽ�����Ϣ
		void OnMessageScenePlayerEnterMapResponse( int nServerID, CMessage* pMessage );
		// ������ҽ��볡��ȷ��
		void OnMessagePlayerEnterConfirm(int nServerID, CMessage* pMessage);
		// ����erating��EnterGame����Ӧ��ʱ
		void OnAGIPMsgEnterGameTimeOut(int nParam1, int nParam2);


		// ��������л�������������Ϣ
		void OnMessagePlayerRedirectScene( int nServerID, CMessage* pMessage );
		// ������֪ͨ���ضԿ糡����ʽ�����ͼ����Ӧ��Ϣ
		void OnMessageRedirectEnterMapResponse( int vCommHandle, CMessage* pMessage );			
		// ������ҿ糡��ʧ����Ϣ
		void OnMessageRedirectSErrorEvent( int vCommHandle, CMessage* pMessage );



		// ������Ҹ�����Ӫ����Ϣ
		void OnMessageRoleChangeCampNotice(int nServerID, CMessage* pMessage);
		// ����������
		// void OnMessageFangChenMiRequest(int nServerID, CMessage* pMessage);
		// �������ȡ���Ŷ���Ϣ
		void OnMessagePlayerCancelLoginQueue( int vCommHandle, CMessage* pMessage );
		// ��ҷ�������֪ͨ
		void OnMessagePlayerReturn2GateNotice( int vServerID, CMessage* pMessage );
		// ������Ҹ�����Ϣ�ı�(�ȼ���ְҵ����ͼ.....)
		void OnMessagePersonalLevelChange( CMessage* pMessage );



		// ������ҶϿ����ص��¼�
		void OnEventPlayerDisconnectGate(int nCommandID);

		// ����ʱ
		void OnMessagePlayerPingRequest(int vCommHandle, CMessage* tpMessage);
		
		// ������Ұ�ȫ����״̬�ı����Ϣ
		void OnMessageChangePassWordStatus(int vCommHandle, CMessage* pMessage);

		// �޸�������ҵĻ�Ա��־
		void OnMessageUpdateVipFlag( int nServerID, CMessage* npMessage );

		// ���´��̳ɹ�
		void OnMessageResavePlayerSuccess(int nServerID, CMessage* pMessage);

// 100304 MAOCY ADD-BEGIN
      // ��ɫ��֤ʱ�����������
      void BuildQuestionOptionData(SRoleValidQuestionOption* pInputOption, SRoleValidQuestionOption* pOutputOption);
      // ��ɫ��֤ʱ����������
      void BuildQuestionRequireResponse(CGatePlayer* tpPlayer, CMessageQuestionRequireResponse& response, SRoleValidQuestionOption* pOptions);
		// ��ɫ��֤ʱ����������
		void OnMessageQuestionRequireRequest(int vCommHandle, CMessage* pMessage);
		// ��ɫ��֤ʱ������֤
		void OnMessageQuestionAnswerRequest(int vCommHandle, CMessage* pMessage);
// 100304 MAOCY ADD-END

// 100331 [GS] MAOCY ADD-BEGIN
      // ��¼��������ѯ��ɫ��Ϣ����
      void OnMessageRoleQuery(int nServerID, CMessage* pMessage);
// 100331 [GS] MAOCY ADD-END

	  ///////////////////////////////////
	  // ��Ϣ��ת��Ӫ��ת������Ϣ
	  // author�� qiufufu
	  // date : 10-08-23
	  //////////////////////////////////////
	 //����ǿ���б�
	  void OnMessageCampWeakRequest(CMessage *pMessage);

	 //scenserver��֤ת��Ӫ�����ɹ��� ���͸�gate�� gateserver�Ƿ���֤�ɹ�
	  void OnMessageChangeCampRequest(CMessage *pMessage);
	 //scensever ɾ�����߳ɹ� ��֪ͨgate �޸����а���Ϣ��������Ӫid��
	  void OnMessageChangeCampNotice(CMessage *pMessage);
	 // ���͸��ͻ��� ת��Ӫʧ����Ϣ
	  void SendChangeCampErrorResponse(CGatePlayer* tpPlayer, ChangeCamp errorCode);
		
	 // ����������غ�ֱ�ӽ��볡��
	 void PlayerDirectEnterGame( int nCommHandle, CGatePlayer *pPlayer );
	public: //-- method

		// �����Ҹ���״̬��ʱ
		void CheckPlayerStatusTimeout();


		// ����ŶӶ���
		void DealQueuePlayer(unsigned int nNowTick);

		void OnEventHostDown(CSceneServer* pHost);

		// ��Ӧ��������������Ϣ
		void OnServerMessage(int nServerID, CMessage* tpMessage);

		// ��Ӧ�ͻ�����Ϣ
		void OnClientMessage(CMessage* tpMessage);

		void OnLaunchServer();
		void OnExitServer();
		void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );
		void OnMessage(int nServerID, CMessage* pMessage );
		void OnReloadConfig();

		CCoreService();
		~CCoreService();

		int Initialize();
		int Resume();
		static unsigned int CountSize();
		void* operator new( size_t nsize );
		void  operator delete( void* pointer );

		// ���غ��������õĻص�����
		static void LoadBlackListConfigCallback(const char* pcConfigPath);
		
	private:
		// �ȴ�������ҵļ���ʱ��
		CWTimer	mWaitTimer;			

		// ������״̬��Timer
		CWTimer	mStateTimer;		

		//�������״̬��ӡ��ʱ��
		CWTimer	mOnLinePlayerStatPrintTimer; 

		// ��������д�����ݿ�
		CWTimer	mOnLineNOTimer;		

};

#endif
