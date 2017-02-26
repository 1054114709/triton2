#pragma once

#include "clienthandle.h"
#include "westserver.h"
#include "protype.h"
#include "entity.h"
#include "tcp_conn.h"
#include "sceneobj_define.h"
#include "dbinterface.h"
#include "scenecfg_manager.h"
#include "event.h"
#include "ahthunk.h"
#include "lk_hashmap.h"
#include "logmodule.h"

namespace SceneServer
{

// ********************************************************************** //
// CSceneServer
// ********************************************************************** //
//class CClientHandle;
class CSceneLogic;
class CModuleManager;

class CSceneServer : public CSingleton< CSceneServer >
{
public:

	CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH> mProxyClient;

	CClientHandle*	mClientHandle;

	unsigned int	mLastTickCount;
	CSceneLogic*	tpSceneLogic;	
	CModuleManager*	tpModuleManager;

	int				mRunFlag;
	int				mPingCheck;
	bool			mbGateIsRegisted;					// �ж��Ƿ������ط�����ע��ɹ�

	lk::string<64> mProxyServerAddr;	// ���ط�������ַ
	lk::string<64> mSceneserverWanAddr;	// ������������������ַ
	lk::string<64> mSceneName;			// ��������������
	lk::string<64> mSceneServerLanAddr; // ������������������ַ
	unsigned char mThisServerID;	// ����������ID

	lk::string<64> mSavePath;			// dberr, save path
	lk::string<64> mBakPath;			// dberr, bak path

	CountryArrary mCountryArrary[ _COUNTRY_COUNT_MAX_ ];

	CWTimer mTimerOfKeepAlive;
	time_t	mLastPorxyKeepAliveTime;
	time_t	mLastGateKeepAliveTime;
	time_t  mLastLogStatInfoTime;

	int				mLaunchStatus;
	int				mCreateMapStatus;

	lk::vector<int, 20> mDeleteList;

	// ���¼��ص������ù������
	typedef void(*TmLoadConfigCallback)(const char*);
	typedef lk::hash_map<lk::string<256>, TmLoadConfigCallback, 1000> LoadConfigFunclist;
	LoadConfigFunclist m_LoadConfigFuncList;
	
public:
	CSceneServer( );
	~CSceneServer( );

	void* operator new( size_t size );
	void  operator delete( void* pointer );
	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* pointer, const char* file, int line);


public:

	enum ERunFlag
	{
		EFLG_CTRL_NO				= 0,
		EFLG_CTRL_QUIT				= 1,
		EFLG_CTRL_RELOAD			= 2,
		EFLG_CTRL_COREDUMP			= 3,
	};


	//// �رշ�����
	//void ShutDownServer( ); 

	void SendKeepAliveToGate();
	int SendKeepAliveToProxy();

	unsigned int GetLastTickCount( ) { return mLastTickCount; }

	const char* GetCountryName( unsigned short mLindID );

	static CSharedMem* mShmPtr;
	static unsigned int CountSize();
	
	int SendMsg(CEntityPlayer* pPlayer, CMessage* pMsg);
	int SendMsg(int vCommNum, CEntityPlayer** pPlayer, CMessage* pMsg );

	int Initailize( int vInitFlag );
	void CheckTimer();
	int PrepareToRun();
	void Run();
	void CheckRunFlags();
	int CheckLaunchServer();

	void SetRunFlag( int vFlag );
	void ClearRunFlag( );
	bool IsRunFlagSet( int vFlag );

	// �����ⲿ��Ϣ
	int RecvServerMsg(int vMsgCount);
	int RecvClientMsg(int vMsgCount);

	// ������Ϣ
	int ProcessDataMsg( CMessage* vMsg );
	int ProcessRouterMsg( CMessage* vMsg );
	int ProcessClientMsg( CMessage* vMsg );
	int ProcessTimeOutMsg( CMessage* vMsg );
	int ProcessDunserverMsg( CMessage* vMsg );

	//SaveAllPlayer
	int SaveAllPlayer( int vSaveCode );

	int LoadPlayerFromDB( unsigned int nAccountID, unsigned int vCharID, int nDesGameID = 0 );
	int LoadPlayerItemInfoFromDB( int nAccountID, int nCharID, int* panPkgIdx, int nNumber, int nDesGameID = 0 );
	int OnRouterMessageByModule(CMessage* pMessage);
	
	// ��Ϣ������
	int OnGlobalGateMessage( CMessage* pMsg );
	int OnGlobalClientMessge ( CEntityPlayer* pPlayer, CMessage* pMsg );
	int OnMessageLeaveGameRequestEvent( CMessage* pMsg, CEntityPlayer* pPlayer );
	int OnMessageRedirectSceneRequestEvent( CMessage* pMsg, CEntityPlayer* pPlayer ); 
	int OnMessageLoginSceneRequestEvent( CMessage* pMsg, CEntityPlayer* pPlayer );
	int OnMessageReturn2GateRequestEvent( CMessage* pMsg, CEntityPlayer* pPlayer );
	int OnMessageSceneNotOpenNoticeEvent( CMessage* pMsg ); 
	int OnMessagePlayerRedirectResponseEvent( CMessage* vpMsg );
	int OnMessageCreateMapNoticeEvent( CMessage* pMsg );
	int OnMessagePlayerEnterMapNoticeEvent( CMessage* pMsg );
	int OnMessagePlayerReturn2GateReponseEvent( CMessage* pMsg );
	int OnMessagePlayerRedirectMapNotice( CMessage* pMsg );
	int OnMessagePlayerPingRequest( CMessage* pMsg, CEntityPlayer* pPlayer);
	int OnMessagePlayerRedirectErrEvent( CMessage* vpMessage ); 
	int OnMessageKickOffPlayerRequest( CMessage* vpMessage ); 
	int OnMessageClientInfoRequest( CMessage* vpMessage, CEntityPlayer* pPlayer );
	int OnMessageTracePlayerNotify( CMessage* vpMessage );
	int OnMessageCreateRepetion( CMessage* vpMessage );
	int OnMessageServerInfoResponse(CMessage* vpMessage);
	int OnMessageSceneGMMove( CMessage* vpMsg );	  	
	int OnMessageRoleMove( CMessage* vpMsg );
														 
	// ������Ұ�ȫ�������Ϣ
	void OnMessageResetPlayerPassword( CMessage* vpMsg );

	// ����ͻ��˷��������
	int OnMessageClientAntiBotDataNotify( CMessage* pMsg, CEntityPlayer* pPlayer );

	// ����ͻ��˷����ģ���������
	int OnMessageClientAntiBotStartRetNotify(  CMessage* pMsg, CEntityPlayer* pPlayer );

	int OnMessageGetCountryInfo( CMessage* pMsg );
	
	int SendRedirectErrCode( int vCharID, unsigned short vLineID, unsigned short vMapID, REDIRECT_ERR vCode );
	
	// ֪ͨ���ط���ȫ�ر�
	int SendShutdownAck( );

	// ��������֪ͨ�رշ�����
	int OnMessageShutdownNotify( CMessage* pMsg );

	// ������
	int ReadConfig( );
	
	// ��������������
	int ReadServerConfig( );

	int ConnectToServer( );

	bool Connect2Proxy();
	bool Regist2ProxyServer();
	bool Regist2GateServer();

	static void OnMessage( int vCommHandle, CMessage* pMessage );
	static void OnClose( int vCommHandle );
	static void OnAccept( int vCommHandle );
	static void OnTimer( unsigned int vTickCount );

	///////////////////////////////////
	// ��Ϣ��ת��Ӫ��ת������Ϣ
	// author�� qiufufu
	// date : 10-08-23
	//////////////////////////////////////
	//���� �ͻ�������ת��Ӫ
	void OnMessageInviteCamp( CEntityPlayer* pPlayer,CMessage* pMessage);
	//���� �ͻ���ת��Ӫ��Ϣ
	void OnMessageChangeSingleCamp(CEntityPlayer* pPlayer,CMessage* pMessage);
	//���� gateserver �ظ���ת��Ӫ��Ϣ
	void OnMessageChangCampResponse( CMessage* pMessage);
	//����ͻ��� ���Ͳ�ѯת����Ӫ����
	void OnMessageChangeCampConditionRequst(CEntityPlayer *pPlayer, CMessage* pMessage);
	//����ת��Ӫ�ɹ� �㲥��Ϣ
	void OnMessageChangeCampSuccesBroadCast(CEntityPlayer *pPlayer, CMessage* pMessage);

	//���� ת��Ӫ���� ��Ϣ
	void  SendChangeCampErrorResponse(CEntityPlayer *pPlayer,ChangeCamp errorCode);

	//gm ǿ��ת����Ӫ
	void OnGMMessageChangeCamp(const char*  role_name,int campid);

	// ���¼���ָ������
	int ReLoadAppointedConfig();

	// ���¼��ص�������
	int ReLoadOneConfig(const char* pcConfigFilePath);

	// ע�����ü��صĻص�����
	// ���ַ�ʽע�᣺
	// 1 �������ļ���·��ע�� 
	// 2 ���ļ��С��ļ���չ��(��.lua,.txt)ע��
	int RegisterLoadConfigCallback(const char* pcConfigPath, TmLoadConfigCallback pFuncCallback);
	int RegisterLoadConfigCallback(const char* pcDirPath, const char* pcExtName, TmLoadConfigCallback pFuncCallback);

	static void LoadDirtyWordCallback(const char* pcConfigPath);
	static void LoadTemplateCallback(const char* pcConfigPath);
	static void LoadSceneConfigCallback(const char* pcConfigPath);
};

// ********************************************************************** //
// CSceneLogic
// ********************************************************************** //

enum emServerStauts
{
	EM_SERVERSTATUS_LOADING	= 0,	// ������������������
	EM_SERVERSTATUS_RUN,			// ������������
	EM_SERVERSTATUS_SHUDOWNING,		// �������ر���
	EM_SERVERSTATUS_EXIT,			// �������˳��ر�
};

class CSceneLogic : public CDBReceiver, public CSingleton< CSceneLogic >
{

	friend class CSceneServer;

public:
	typedef lk::hash_map< int, int, SERVER_CAP_PLAYER >							PLAYERID_MAP;	// Playerʵ������
	typedef lk::hash_map< int, int, SERVER_CAP_NPC >							NPCID_MAP;		// NPCʵ������
	typedef lk::hash_map< lk::string<NAME_LENGTH>, int, SERVER_CAP_PLAYER >		PLAYERNAME_MAP;	// �����������
	typedef lk::vector< int, SERVER_CAP_PLAYER >								PLAYERID_VEC;	// �������

	typedef lk::vector< unsigned int, DELETE_LIST_SIZE >						DELETE_LIST_TYPE;		// �ӳ�ɾ���б�


	PLAYERID_MAP								mPlayerCommIndex;	// �ڳ����е����,CommHandle��Ϊ����
	
	static CSharedMem*	mShmPtr; // �����ڴ�ָ��

	unsigned int								mCurrentDay;		// ������ˢ�µ�����
	CEvent										mEvent;

	//CStatInfo 									mStatInfo;			// ��������ͳ����Ϣ

protected:
	PLAYERID_MAP								mPlayerInWait;		// �ȴ����ӵ����,CharID��Ϊ����
	PLAYERID_VEC								mPlayerInLost;

	// �������
	PLAYERNAME_MAP								mPlayerNameIndex;	// �ڳ����е����,��ɫ������Ϊ����
	PLAYERID_MAP								mPlayerContainer;	// �ڳ����е����,CharID��Ϊ����
	NPCID_MAP									mNpcContainer;		// �ڳ����е�NPC(����������ˣ��������ˣ����䣬�����е�̤��ȵ�,���仰˵����һ�з����), EntityID��Ϊ����

	// 

	// �����

	//CSessionDispatch							mSessionDispatch;

	enum 
	{
		KICK_CHECK_GAP = 60000, // �߲���Ծ��Ҽ��ʱ����,��λ:����
	};

	CWTimer										mDailyTimer;		// ÿ�ռ�ʱ��
	CWTimer										mTimer;				// �߼������ʱ��
	CWTimer										mStateCheckTimer;	// ��������߼������ʱ��
	int											mTemplateVersion;	// ģ���ļ��汾��
	int											mTaskVersion;		// �����ļ��汾��
	int											mSavePerf;			// ���ϴα���ͳ����Ϣʱ��(����)
	CWTimer										mTimeMemCheck;		// �ڴ�����(����) 
		

	CAHContorlManager							mAHControlMng;		// ����ҹ�����

	char mConfigtmpbuf[1024];
	
	

	int mServerStatus; // ������״̬ emServerStauts
	int mWorldID;	// ������Ψһ����ID. gate_id
	int mLineID;	// �������ڱ�������������line_id
	int mGameID;	// ��ϷID
	DELETE_LIST_TYPE							mDeleteList;		// �ӳ�ɾ���б� ����module������� ����Ϣ���������ontimer��������
	
	CMessagePlayerProperty						mSavePlayerProperty;

public:
	CSceneLogic( );
	~CSceneLogic( );

	void* operator new( size_t size );
	void  operator delete( void* pointer );
	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* pointer, const char* file, int line);

	static unsigned int CountSize( );

	int Initailize( );
	int Resume();

public:

	//// �رշ�����
	//void ShutDownServer( ) { mServerStatus = EM_SERVERSTATUS_SHUDOWN; }

	//// �������Ƿ񿪷�
	//bool IsServerOn( ) { return mServerStatus == EM_SERVERSTATUS_RUN; } 

	//// �Ƿ����˳�����
	//bool CanExitServer( ) { return mServerStatus == EM_SERVERSTATUS_EXIT; }

	int GetServerStatus() { return mServerStatus; }
	void SetServerStatus( int nStat ) { mServerStatus = nStat; }

	// ������
	int ReadConfig();

	// �õ���ǰ����
	unsigned int GetCurrentDay() {return mCurrentDay;}

	// ÿ��ˢ��
	void DailyRefresh();

	// ÿ��ˢ��
	void WeeklyRefresh();

	// �ֲ�����

	void OnSavePlayer( int nSaveCode, int nEntityPlayerID, int nResultCode );
	int SaveErr( CEntityPlayer* vpPlayer );

	// �����ķֲ���ȡ����
	void OnLoadPlayer_CharProfile( CMessage* pMessage, int vParameter1, int vParameter2 );
	void OnLoadPlayer_Property( CMessage* pMessage, int vParameter1, int vParameter2 );
	void OnLoadPlayer_Baggage( CMessage* pMessage, int vParameter1, int vParameter2 );
	void OnLoadPlayer_Storage( CMessage* pMessage, int vParameter1, int vParameter2 );
	void OnLoadPlayer_Task( CMessage* pMessage, int vParameter1, int vParameter2 );
	void OnLoadPlayer_Friend( CMessage* pMessage, int vParameter1, int vParameter2 );
	void OnLoadPlayer_Final( CEntityPlayer* pPlayer, int vCharID, int vCommHandle );
	void OnLoadPlayer_Repetion( CMessage* pMessage, int vParameter1, int vParameter2 );
	void OnLoadPlayer_YuanBao( CMessage* pMessage, int vParameter1, int vParameter2 );

	// on db message 
	int OnMessageLoadPlayerItemInfoFromDB( CMessage* pMsg );
	int OnTimeoutLoadPlayerItemInfoFromDB( unsigned int unCharID, int iPkgIdx  );
	int OnMessageSaveItemInfoToDBResponse( CMessage* pMessage );
	int OnTimeoutSaveItemInfoToDB( int nCharID );
	int OnMessageLoadPlayerProperty( CMessage* pMsg );

	int GetPlayer4KickOut(CMessage*, CEntityPlayer*);
public:
	// �رշ�����
	void Shutdown( );

	// ����������
	void Launch( );

	// ִ�з�����
	void Run(int nDaemon );

	// �õ��������
	int GetPlayerNumber( ) const;

	// ִ��SQL
	int ExecuteSql( int vSessionType, int vParam1, int vParam2, int vPlayerCharID, int vCallBack, SQLTYPE vSqlType, const char* pSQL, ... );

	int GetSaveFilePath( int vPlayerCharID, char* pPath, int vPathLen );
	void Save2File( int vSessionType, int vPlayerCharID, ::google::protobuf::Message* vpMsg, const char* pKey, std::vector<std::string>& rFirlds, unsigned int nAccountID );
	void OnMessageResavePlayer( CMessage* pMsg );
	int  ReSavePlayerFromFile( int vCharID );
	int  ReSavePlayerInfoFromXml( const char* xmlfile, int nCharID, unsigned int nAccountID );
	int  OnResaveSuccess( int nCharID, int nResaveFlag );
	void GetPlayerPosInfoFromXml( int vCharID, int& rLineID, int& rMapID, int& rPosX, int& rPosY );

	bool LoadPlayerInfo( int vAccountID, int vPlayerCharID, int nDesGameID = 0 );
	bool SavePlayerInfo( CEntityPlayer* vPlayer, int vSaveCode, int vCallBack );
	bool LoadPlayerProperty( int nAccountID, int vPlayerCharID, int nDesGameID = 0 );
	bool SavePlayerProperty( CEntityPlayer* vpPlayer, int vSaveCode, int vCallBack );

    // ����ҡǮ�������
	// TODO:��ʱ���޸�(���ս����ȫ������)
    void LoadPlayerYaoQianShuInfoFromDB( int nAccountID, int nCharID );
    void OnLoadPlayer_YaoQianShu( CMessage* pMessage, int nCharID, int nAccoutID );
    void LoadPlayerPickStoreBoxFromDB( int nAccountID, int nCharID );
    void OnLoadPlayer_PickStoreBox( CMessage* pMessage, int nCharID, int nAccoutID );

	bool SendMsg2Data( google::protobuf::Message* vpMsg, int Uid, int tMsgID, int nDesGameID = 0 );

	void ClearSavePlayerPropety( ){ mSavePlayerProperty.Clear( ); }
	CMessagePlayerProperty* GetSavePlayerProperty( ) { return &mSavePlayerProperty; }
	 

	// �õ��ڳ����е�ָ�����( ͨ��accountID���� )
	CEntityPlayer* GetPlayerByAccountID( int nAccountID );	
	
	// �õ��ڳ����е�ָ�����( ͨ��CharID���� )
	CEntityPlayer* GetPlayerByCharID( int vCharID );

	// �õ��ڳ����е�ָ�����( ͨ��ͨѶ�˿����� )
	CEntityPlayer* GetPlayerByComm( int vCommHandle );

	// �õ��ڳ����е�ָ�����( ͨ����ɫ���� )
	CEntityPlayer* GetPlayerByName( const char* pCharName );

	

	// �õ��ȴ������е����
	CEntityPlayer* GetWaitingPlayerByCharID( int vCharID );

	// �������ݵ�����
	bool Send2Gate( CMessage* pMessage );

	void Send2GMServer( CMessage* pMessage );

	// ������Ϣ����־������
	void Send2Log( CMessage* pMessage, int nHandle, int nSplitor, int nDesGameID = 0 );

	// ������Ϣ�����ݷ�����
	int Send2Data( BYTE* pMessage, unsigned short vLength );
	int Send2Data( int nUin, CMessage& rMessage, int nDesGameID = 0 );

	// ��ȫ�ָ���������������Ϣ
	int Send2GlobalDunServer( CMessage* pMessage );

	// ������Ϣ����ǰ��Ϸ������
	void SendSceneMessage( CMessage* pMessage, int CountryID = -1, int MapID = 0 );

	// ������Ϣ��������Ϸ������( ͨ������ת�� )
 	void SendWorldMessage( CMessage* pMessage );
 	
	// ������Ϣ��ĳ������( ͨ������ת�� )
	void SendCountryMessage( CMessage* pMessage, int nCountryID );
	
	// ������Ϣ��ĳ������( ͨ������ת�� )
	void SendFamilyMessage( CMessage* pMessage, int nFamilyID, bool bNeendSendToScene = false );
	
	// ������Ϣ����������( ͨ������ת�� )
	void SendCorpsMessage( CMessage* pMessage, int nCorpsID,  bool bNeendSendToScene = false );
		
	// ͨ��worldid������Ϣ�����շ�ΪĿ�����أ�
	void Send2OtherGate( CMessage *pMessage, int nWorldID );	

	// ������Ϣ��ָ���ͻ���,����ͨ������ת��
	void Send2Player( const char* pName, CMessage* pMessage );

	// ������Ϣ���ͻ���
	void Send2Player( int vCharID, CMessage* pMessage );

	// ������Ϣ���ͻ���
	void Send2Player( CEntity* pPlayer, CMessage* pMessage );

	// ������Ϣ������ͻ���
	void Send2Player(  CEntityPlayer* pPlayer, BYTE* pMessageBuff, int nLen, CMessage* pMessage );

	// ������Ϣ������ͻ���
	void Send2Player( std::vector< CEntityPlayer*>* rEntityVec, CMessage* pMessage );

	// �õ�ָ��ʵ��
	CEntity* GetEntity( int vEntityID );

	// ����ʵ��
	void CreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst = true );

	// ɾ��ʵ��
	void DestroyEntity( CEntity* pEntity, int vSaveCode );

	// ɾ�����ʵ��
	int DestroyPlayerInstance( CEntityPlayer* vpPlayer, EMLeaveReason emLeave, EMSaveResult emSave, int nGlobalSceneWorldID = 0 );

	// ���׼���뿪
	void OnPlayerLeave( CEntityPlayer *pPlayer, int nState );

	// �����������
	int KickPlayer( int vCharID, int nReason = 0, int nfrom = 0);

	// ���ã� ��Ҫ��������ϴ����ݴ��̲���ȷ��Ľ�ֹ��½֪ͨ
	void KickPlayerWithoutSave( CEntityPlayer* pPlayer, EMSaveResult emSave );

	// ���������������
	void KickAllExcept( unsigned int unCharID );

	// �����������
	void SavePlayer( CEntityPlayer* pPlayer, int vSaveCode );

	// ������ҷ�blob��ʽ����
	bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );

	// ����뿪��Ϸ����
	int PlayerLeaveFromGame(CEntityPlayer* tpPlayer);

	// �õ��������������
	int GetPlayersInScene(std::vector<CEntityPlayer*>& rPlayers);
	
	// ����������־Ŀ¼
	int CreatPlayerLog( );

	// ȡ�÷��������ڵ�����ID
	int GetWorldID() { return mWorldID; }
	void SetWorldID (int nWorldID) { mWorldID = nWorldID; }

	// ȡ�÷��������������lineid
	int GetLineID() { return mLineID; }
	int SetLineID( int nLineID ) { mLineID = nLineID; return 0; }

	int GetGameID() { return mGameID; }
	void SetGameID (int nGameID) { mGameID = nGameID; }

	// ��ӵ�ɾ���б�
	void AddDeleteList( unsigned int unEntityID );
	// ���ӳ�ɾ���б���ɵ�
	void DoDeleteList();

	// ��¼������Ʒ
	void LogValuableEquip(int nRoleID, CItemObject* pItem);

	// �����߲������
	int TeleAll( int nMapID, int nPosX, int nPosY );

	// ����ָ����ͼNPC
	int DestroyMapNPC( int nMapID, int nMapIndex = 0);

	//��ȡ config �����ļ���Ŀ¼
	const char* GetConfigDataFileNamePath(int nGameID, const char * filename);

protected:
	// ������ͼ
	int CreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName );

	// ���ٳ���
	void DestroyScene( const char* pName );

	// ���ص�ͼģ��
	int LoadSceneTpl( const char* pFileName );

	// ��ӡ��ǰ�������
	void PrintPlayer( CEntityPlayer* pPlayer );

	// ������ʱ�䴦��
	void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );

	// ��鴦���������
	void OnCheckOnlieStateEvent( unsigned int vTickCount, unsigned int vTickOffset );

	// �������ݿ�ص�
	void OnFireSession( CMessage* pMessage );

	// ����session��ʱ
	void OnSessionTimeOut( int nSessionID );

	// ����������
	void CalcCurrentDay( );
	
	// �����ҵ���ϢƵ��
	bool CheckMsgFrequency( CEntityPlayer *pPlayer );
};


};  
   
#define const_package_size 0x7FFF
