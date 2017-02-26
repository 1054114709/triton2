#ifndef _GATE_LOGIC_H_
#define _GATE_LOGIC_H_

#include "entity.h"
#include "message_pb.hxx.pb.h"
#include "coremessage_pb.hxx.pb.h"
#include "servermessage_pb.hxx.pb.h"
#include "db_msg_pb.hxx.pb.h"
#include "tcp_conn.h"
#include "clienthandle.h"
#include "message_queue.h"
#include "message_dispatcher.h"
#include "gateobj_define.h"
#include "westserver.h"

#ifdef USING_ERATING
#include "Macro.h"
#include "SysProtocol.h"
#include "AGIP.h"
#endif
#define PERF_TIMER	60000		// һ���Ӵ�ӡһ��ͳ����Ϣ  �Ժ�������

class SysProtocol;
class CAGIPSession;

namespace GateServer
{

// ********************************************************************** //
// CGateServer
// ********************************************************************** //
class CGateLogic;
class CModuleManager;

// ���б�־
enum ERunFlag
{
	EFLG_CTRL_NO        = 0,
	EFLG_CTRL_QUIT      = 1,
	EFLG_CTRL_RELOAD    = 2,
	EFLG_CTRL_COREDUMP	= 3,
	EFLG_CTRL_REFRESHRANK = 4, // ˢ���а�
	EFLG_CTRL_PROCESSEXPIREDMAIL = 5,	// ������ڵ��ʼ�
	EFLG_CTRL_SAFESHUTDOWN	= 6,	// ��ȫ�رշ�������
};

// ***************************************************************
//  Class:	CConfigure
//  Responsibility:
//  		1. gateserver.xml ����������
//  Restirct:
//  		1. ֻ�洢���õ�����
//	Others:	 		
//  Date:	2009-07-08
//
// ***************************************************************
class CConfigure
{
	public:
		// ��erating��session����ʱʱ��
		int nEratingSessionTimeout;		

		// �����ݿ��session����ʱʱ��
		int nServerSessionTimeout;		

		// GateServer��ʱ������
		int nGateTimerInterval;			

		// TODO: ����sleep��!!
		// ����ղ����ͻ��˵���Ϣ, Gate Sleep��ʱ����. 
		int nClientHandleIdleSleep;		

		// ��ProxyServer������ͬ������
		int nPingProxyInterval;

		// ��Erating����״̬������
		int nReport2ERatingInterval;

		// ����Ϸ��������Game������ͬ������
		int nGameHeartBeatTimeout;

		// ���״̬�������
		int nPlayerStateCheckInterval;

		// �ȴ��������GateServer�ĳ�ʱʱ��
		int nPlayerWaitConnectTimeout;

		// �����Gate��δ���κβ����ĳ�ʱʱ��
		int nPlayerIdleIngateTimeout;

		// ֪ͨ��������,�ȴ�������Ӧ��ʱʱ��
		int nPlayerWaitKickoffTimeout;

		// �ȴ���ҿ糡����Ӧ�ĳ�ʱʱ��
		int nPlayerWaitRedirectTimerout;

		// �ȴ���ҵ�¼��Ϸ��������Ӧ�ĳ�ʱʱ��
		int nPlayerOnGameStateTimeout;

		// ÿ����������������
		int nPlayerCountPerScene;

		// �����ҷ����Ե�����
		int nPlayerFangChenMiInterval;

		// ���������ͻ���ͬ������
		int nTeamProSynTimeout;

		// �����ݿ��¼ÿ������������ҵ�����
		int nOnLineNOTimeout;

		// ��¼���������ʣ�ÿʱ������
		int nLoginCountOnceTimer;

		// ���Ĭ�ϵ�¼�Ĺ���, ��ͼID
		int nCampID;
		int nLineID;
		int nMapID;

		// ��Ϸ��ΨһID��������54�� ��ʽ��4
		int nGameID;

		// �ϱ�����ϷIDLIST
		int mGameList[32];

		char m_szMysqlInfo[256];

		bool bFcmServiceOn; 
		bool bFcmIsFake; 
		int  nFcmWarningTimer;

		int nPlayerActiveTimeout;
		
		// ɾ����ɫ�ı���ʱ��
		int nDeleteProtectTime;
		
		// ��ɫɾ������ɾ��ʱ��
		int nDeleteAllowedTime;
		
		// ��ɫɾ����ȴʱ��
		int nDeleteCoolTime;

		// ִ��ɾ��������ʱ���(Сʱ)
		int nMailDeleteHour;
		
		// ִ��ɾ��������ʱ���(����)
		int nMailDeleteMinute;
		
		// ִ�����Ų�����ʱ���(Сʱ)
		int nMailBackHour[MAXSERVERNUM];
		
		// ִ�����Ų�����ʱ���(����)
		int nMailBackMinute[MAXSERVERNUM];
		
		// �ʼ���ID
		int nMailTableID[MAXSERVERNUM];
		
		// ��ȫ����ʱ�����͵ȼ�
		int mProtectLevel;
		
		// Ĭ�ϰ�ȫ����ʱ��
		int mDefaultProtectTime;
		
		// 100304 MAOCY ADD-BEGIN
      // ��ɫ��֤�����־
      int roleValidQuestionFlag;
      // ��ɫ��֤���ⷶΧ
      int roleValidQuestionRange;
      // ��ɫ��֤��������
      int roleValidQuestionRetry;
      // ��ɫ��֤��������
      int roleValidQuestionCount;

		// ����ս��˫������
		int mCorpsCampCount;
		int mBourseUse;
		// ��ɫ��֤����
		SRoleValidQuestion roleValidQuestions[ROLE_VALID_QUESTION_COUNT];
		// ��ɫ��֤ѡ��
		SRoleValidQuestionGroup roleValidQuestionGroups[ROLE_VALID_QUESTION_GROUP_COUNT];
		// 100304 MAOCY ADD-END
		
		int mInternalIPList[MAX_EXCEPTIP_NUM];

		typedef lk::hash_map<unsigned int, int, MAX_MULTI_CLIENT_EXCEPT> MULTICLIENT;
		MULTICLIENT mMultiClientIP;

		// ��鵥IP�������Ŀ���
		int mIsCheckMultiClient;

		// ��鵥IP��������ʱ����
		int mCheckMultiClientInterval;

		// ��IP����������� 
		int mDefaultClientPerIP;
		
		// ����ֱ��ɾ������͵�
		int mDeleteLevel;

		// ͬip��ÿ��mac��ַ�µ�������
		int mDefaultClientOnIPPerMac;

		CConfigure();
};



// ***************************************************************
//  Class:	CGateServer
//  Responsibility:
//  		1. ά����proxyserver, clienthandle������
//  		2. ά����sceneserver������
//  Restirct:
//  		1. ����ģ��
//	Others:	 		
//  Date:	2009-07-08
//
// ***************************************************************
class CGateServer: public CSingleton< CGateServer >
{
	public:
		typedef std::pair< int, int >	MAPTYPE;	
		typedef lk::hash_map< int, int , MAP_AT_GATE_CAP>::iterator	MAPITER;
		typedef lk::hash_map< int, int , MAP_AT_GATE_CAP> MAPCONTAINER;

		struct CountryArrary
		{
			char	mName[ _COUNTRY_NAME_LEN_ + 1 ];
		};

	private:
		// ���е�ͼ�б�
		MAPCONTAINER mMaps;

		// ��������, �洢����pHost�����ID; λ��0 �洢����Ŀǰ����ServerID, ����λ�ð���serverID�洢pHost�Ķ���
		int mSceneHosts[SCENE_AT_GATE_CAP+1];

		// Gateͳһ��ģ��汾��
		int mHostTemplateVer;

		// ��������
		CountryArrary mCountryArrary[ _COUNTRY_COUNT_MAX_ ];

		// �����������IP��˿�
		lk::CString32 mProxyServerAddr;

		// GateServer�ṩ���ͻ��˵ķ��ʵ�IP��˿�
		lk::CString32 mGateServerAddr;
		lk::CString32 mGateServerLanAddr; // ������IP
		int mGateServerID;

		// GateWorld������
		lk::CString32 mWorldName;

		// Erating�����GateCode, Passwd �� Mac��ַ
		lk::CString32 mGateCode;
		lk::CString64 mGatePasswd;
		lk::CString32 mGateMac;

		// Erating �������������ID; ����Erating bind�ɹ���ʱ��erating�����;
		// TODO: ���eratingδ���ӳɹ�����ô��?
		unsigned int mRegistID;


		// �������������ӵĿͻ���
		CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH> mProxyClient;

		// TODO: ָ�� ?
		// ����Ϸ�ͻ�����Ϣ����ͨ�ŵĶ���
		CClientHandle*  mClientHandle;	

		// ���õ�����ID; ERating �涨������ '1xx', 
		int  mWorldID; 

		// Erating�Ƿ�������
		bool mERatingIsLaunched;

		// �ϴ���Proxyͬ����ʱ��
		time_t mLastPorxyKeepAliveTime;

		// ���¼��ص������ù������
		typedef void(*TmLoadConfigCallback)(const char*);
		typedef lk::hash_map<lk::string<256>, TmLoadConfigCallback, 1000> LoadConfigFunclist;
		LoadConfigFunclist m_LoadConfigFuncList;

	public: 
		CGateServer();

		~CGateServer(){}

		static CSharedMem* mShmPtr;

		static unsigned int CountSize();

		void* operator new( size_t size );

		void  operator delete( void* pointer );

		int Initialize( int vInitFlag );
	
		int Resume();

	public:	//-- method
		// ����������������Ϣ
		void RecvServerMsg(int vMsgCount);

		// ������Ϸ�ͻ�����Ϣ
		void RecvClientMsg(int vMsgCount);

		// ���Ӵ��������
		bool Connect2ProxyServer();

		// ֪ͨ��¼���������翪����
		void Regist2LoginServer();

		// ֪ͨ��������������ر�
		void UnRegist2LoginServer();

		// ֪ͨ��¼���������绹����
		void SendHeartBeat2Login();

		// ��erating�����������Ϣ
		void SendGWDataReportProto2ERating();

		// ����������������֤��Ϣ
		void Regist2ProxyServer();

		// ֪ͨ���������,���ط���������
		int SendkeepAliveToProxy();

		// ��proxy��������
		void KeepAlive2Proxy();

		// ��Proxy���ͳ���ΪvMsgLen��pMessage
		int Send2ProxyImp(BYTE* pMessage, int vMsgLen);

		// ��tpPlayer������ϢpMsg
		int Send2Player(CGatePlayer* tpPlayer, CMessage* pMsg);
        int Send2Player(std::vector<CGatePlayer*>& vPlayerList, CMessage* pMsg);

		// ������Ϣ����¼������
		void Send2Login( CMessage* pMessage );

		// ������Ϣ����־������
		void Send2Log( CMessage* pMessage, int nSplitor);

		// ���ճ���������ID������Ϣ
		void Send2Scene( int nServerID, CMessage* pMessage );		

		// ���շ�������������Ϣ
		void Send2Scene( CSceneServer* pHost, CMessage* pMessage );	

		// ����������ڳ���������Ϣ
		void Send2Scene( CGatePlayer* pPlayer, CMessage* pMessage );

		// ������Ϣ�����ݷ�����
		void Send2Data( int nAccountID, CMessage* pMessage, int nSrcGameID = 0, int nDesGameID = 0 );
		void SendMsg2Data( google::protobuf::Message* vpMsgFact, int vMsgID, int uID );

		// ��ȫ�ָ���������������Ϣ
		void Send2GlobalDunserver( CMessage* pMessage );	

		// ���������ط���Ϣ
		void Send2OtherGate( CMessage* pMessage, int nWorldID );	

		// ע�᳡��������
		void RegistSceneServer(int nServerID, CSceneServer* tpServer);

		// ɾ��ָ�����Ӷ˿ڵ�����
		void DeleteHost(CSceneServer* pHost);

		// ����ĳ���ҵ�ĳ��ͼ���ڵĳ���������
		CSceneServer* GetServerByLineMap( int vLineID, int vMapID );

		// �õ�ָ�����������еĹ������ͼ�б�
		int GetServerMap( const char* pServerName, unsigned int vServerID, std::vector< std::pair< int, std::string > >& rMapList );

		// ͨ�����������Ƶõ�������
		CSceneServer* GetServerByName( const char* pServerName );

		// ͨ��ͨѶ�˿ڵõ�������
		CSceneServer* GetServerByID( int vServerID );

		// ͨ����ID�õ���ͼ��Ϣ
		CSceneMap* GetMapByLineMap( int vLineID, int vMapID );		

		// ȡ�õ�ͼ����е�LINEID
		int  GetMostIdleLineID(int vMapID);

		// ֹͣ
		void ExitServer();

		// ��������
		void OnReloadCfg();

		// ����
		void OnLaunch();

		// ���³����ϱ����������
		void UpdateSceneRptPlayerNumber(int nServerID, int nRptNumber);

		// ��¼�������ı��������ݿ�
		void SaveSceneReport2DB();

		// ��erating���泡������
		void ReportData2Erating();

		// ע�ḱ����Ϣ
		bool RegistRepetionInfo( CMessageRegistRepetionInfo* );

		// ע�᳡������װ�صĵ�ͼ�Ķ�Ӧ��ϵ
		bool RegistSceneMap(int nServerID, int nLineID, int nMapID);

		// ���ע���nServerID�ĳ���������
		int CheckSceneVersion(int nServerID, int nVersion, int nTplVersion);

		// ע���ʼ�������ĳ���
		int RegistSceneByInitial(int nServerID, const char* szSceneName,  const char* szSceneIP,
									int nTplVersion, int nCodeVersion, int nTaskVersion, int nSceneCap );

		// ע��ָ������ĳ���
		int RegistSceneByRecovery(int nServerID, const char* szSceneName,  const char* szSceneIP,
									int nTplVersion, int nCodeVersion, int nTaskVersion, int nSceneCap );

		// ��鳡��������������ʱ
		void CheckGameServerTimeout();

		// ����ProxyActiveTmStmpΪ��ǰʱ��
		void UpdProxyActiveTmStmp() { mLastPorxyKeepAliveTime = time(0); }

		// ȡ��Proxy�����ActiveTimeStamp
		time_t GetProxyActiveTmStmp() { return mLastPorxyKeepAliveTime; }
		
		// ɾ�������ʼ�
		void DeleteExpiredMail( );
		
		// �˻ص����ʼ�
		void BackExpiredMail( int nMailTableID );	
		
		// ��鲢ִ��ϵͳ�ʼ���صĲ���
		void CheckMailSysActionTime();
		
		// ִ��ϵͳɾ�������Ų���
		void ExcuteMailSysAction();	



	public:
		// mGateCode
		void SetGateCode(const char* szCode) { mGateCode = (szCode ? szCode : ""); }
		const char* GetGateCode() const { return mGateCode.c_str(); }

		// mGatePasswd
		void SetGatePasswd(const char* szPasswd) { mGatePasswd = (szPasswd ? szPasswd : ""); }
		const char* GetGatePasswd() const { return mGatePasswd.c_str(); }

		// mGateMac
		void SetGateMac(const char* szMac) { mGateMac = (szMac ? szMac : "") ; }
		const char* GetGateMac() const { return mGateMac.c_str(); }

		// mGateServerAddr
		void SetGateServerIP(const char* szAddr) { mGateServerAddr = (szAddr ? szAddr : ""); }
		const char* GetGateServerIP() const { return mGateServerAddr.c_str(); }

		void SetGateServerLanIP( const char* szAddr ) { mGateServerLanAddr = (szAddr ? szAddr : ""); }
		const char* GetGateServerLanIP() const { return mGateServerLanAddr.c_str(); }

		void SetGateServerID( int nID ) { mGateServerID = nID; }
		int GetGateServerID( ) { return mGateServerID; }

		// mProxyServerAddr
		void SetProxyServerIP(const char* szAddr) { mProxyServerAddr = (szAddr ? szAddr : ""); }
		const char* GetProxyServerIP() const { return mProxyServerAddr.c_str(); }

		// mRegistID
		void SetRegistID(unsigned int nRegistID ) { mRegistID = nRegistID; }
		unsigned int GetRegistID() { return mRegistID; }

		// mERatingIsLaunched
		void SetERatingIsLaunched(bool bLaunched) { mERatingIsLaunched = bLaunched; }
		bool IsERatingLaunched() { return mERatingIsLaunched; }

		// mWorldID
		void SetWorldID(unsigned int nWorldID ) { mWorldID = nWorldID; }
		int GetWorldID() { return mWorldID; }

		// mWorldName
		void SetWorldName(const char* szName) { mWorldName = (szName ? szName : ""); }
		const char* GetWorldName() const { return mWorldName.c_str(); }

		// mSceneHosts[0]
		void SetMaxSceneServerID(int nMax) { mSceneHosts[0] = nMax; }
		int  GetMaxSceneServerID() { return mSceneHosts[0]; }

		// mSceneHosts[i] i > 0
		void SetServerObjID(int nServerID, int nObjID) { mSceneHosts[nServerID] = nObjID; }
		int  GetServerObjID(int nServerID) { return mSceneHosts[nServerID]; }

		// reset mSceneHosts[0]
		void ResetMaxSceneServerID() 
		{ 
			int i = GetMaxSceneServerID(); 
			for (;	i > 0; --i)
			{
				if ( GetServerObjID( i) != INVALID_OBJ_ID) break;
			}

			SetMaxSceneServerID( i ); // ��С��0
		}

		// calu valid mSceneHosts[i, GetMaxSceneServerID()]
		int GetSceneServerNumber()
		{
			int nRet = 0;
			for (int i = 1; i <= GetMaxSceneServerID(); ++i)
			{
				if ( GetServerObjID(i) !=  INVALID_OBJ_ID ) nRet++;
			}

			return nRet;
		}

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

		// �������õĻص�����
		static void LoadIPConfigCallback(const char* pcConfigPath);
		static void LoadGateserverConfigCallback(const char* pcConfigPath);
		static void LoadDirtyWordConfigCallback(const char* pcConfigPath);
		static void LoadRoleValidConfigCallback(const char* pcConfigPath);
		static void LoadTracelistCallback(const char* pcConfigPath);
		static void LoadTemplateCallback(const char* pcConfigPath);

		// �³�������ü���
		int LoadIPConfig(const char* pcConfigPath, CConfigure& vConfigure);
		int LoadGateserverConfig(const char* pcConfigPath, CConfigure& vConfigure);
};

// ��Ҫ��־׷�ٵ��ʺŵĽ�ɫ��Ϣ
class CTraceCharInfo
{
public:
	typedef lk::vector< int, PLAYERNUM > RoleList;
	RoleList mRoleList;
public:
	CTraceCharInfo()
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
	~CTraceCharInfo()
	{
		
	}
public:
	int Initialize()
	{			
		mRoleList.initailize();
		return 0;
	}
	int Resume()
	{
		 return 0;
	}
};

// ��Ҫ��־׷�ٵ��ʺŵĽ�ɫ��Ϣ������
class CTracePlayerManager
{
public:
	typedef lk::hash_map< int, CTraceCharInfo,  MAXPLAYERNUM > PlayerList;
	PlayerList mPlayerList;
public:
	CTracePlayerManager()
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
public:
	int		InsertPlayerInfo( int nAccountID, int *pRoleIDList, int nRoleIDNum );
	int		DeletePlayerInfo( int nAccountID );
	bool    CheckIfRoleIDNeedTrace( int nAccoutID, int nRoleID );
	int		InitializeList(  );
public:
	int Initialize()
	{
		mPlayerList.initailize();
		return 0;
	}
	int Resume()
	{
		return 0;
	}
};


// ***************************************************************
//  Class:	CGateLogic
//  Responsibility:
//  		1. ������Ӧ��Ϣ,�ַ���Ϣ
//  		2. ����Timer
//  		3. �������������أ�ֹͣӦ��
//  Restirct:
//  		1. �߼�ģ��
//	Others:	 		
//  Date:	2009-07-08
//
// ***************************************************************
class CGateLogic : public CSingleton< CGateLogic >
{
	public:
		CGateLogic();

		~CGateLogic();

		static CSharedMem*  mShmPtr;

		void* operator new( size_t size );

		void  operator delete( void* pointer );

		// ����
		int Initialize( int vInitFlag );

		// �ָ�
		int Resume();

		// ����
		void Launch();

		// ����
		void Run(const int nDaemon );

		// ������б�־
		void CheckRunFlags();

		// ���� mRunFlag �Ľӿ�
		void SetRunFlag( int vFlag );

		void ClearRunFlag( );

		bool IsRunFlagSet( int vFlag );

		// ���ö�ʱ��
		void CheckTimer();

		// 100304 MAOCY ADD-BEGIN
		// ���ؽ�ɫ��֤��Ϣ
		void ReadRoleValidQuestionConfig(CConfigure& vConfigure);
		// 100304 MAOCY ADD-END

		// ��ȡ���õ�vConfig��
		int ReadCfg(CConfigure& vConfig);

		// �������Ĵ�С
		static unsigned int CountSize();
	public: //--method
		// ִ��SQl
		bool ExecuteSql( int vSessionType, int vParam1, int vParam2, 
				int nAccountID, int vCallBack, SQLTYPE vSqlType, const char* pSQL, ... );

		// �������������ļ���ʱ��, Logic��Щ����������
		void OnReloadConfig();

		// ����session
		void FireServerSession(int nSessionClass, CMessage* tpMessage, int nParam1, int nParam2);
		// ����eraing��session
		void FireAGIPSession(int nSessionClass, SysProtocol* pproto, 
				int nParam1, int nParam2, int nParam3, int nParam4, const char* szParam5);

		// ����erating��Ϣ
		SysProtocol* CreateERatingMessage(unsigned char* message_buffer, short message_length);
		// ��Ӧerating��Ϣ
		void OnERatingMessage(SysProtocol* proto);
		// ����erating session
		CAGIPSession* CreateSession4Proto(SysProtocol* pproto);
		
		// ��ȡ׷����ҹ�����
		CTracePlayerManager &GetTracePlayerManager(){ return mTracePlayerManager; }
		
	public: //--timer
		// ���ض�ʱ��
		void OnTimer(unsigned int vTickCount, unsigned int vTickOffset );

		// ���erating session�ĳ�ʱ
		void CheckAGIPSessionTimeout();

		// ����erating session ��ʱ
		void OnAGIPSessionTimeout(int nSessionClass, int nParam1, int nParam2);

		// ������ݿ��Ӧ��ʱ
		void CheckDBSessionTimeout();

		// ����db session �ĳ�ʱ
		void OnServerSessionTimeout(int nSessionClass, int nParam1, int nParam2);

		//��ȡ config �����ļ���Ŀ¼
		const char* GetConfigDataFileNamePath(int nGameID, const char * filename);

	public:	//--message
		// ����Ӵ����������������Ϣͳһ���
		void OnProxyMessage(CMessage* vMsg );

		// ����ӿͻ��˹�������Ϣͳһ���
		void OnClientMessage(CMessage* vMsg );

		// ����ProxyMessage�е�Server��Ϣ
		void OnServerControlMessage(int nServerID, CMessage* pMsg);

		// ��ӦProxyMessage �е���ת��Ϣ
		void OnRouterMessage(int vCommHandle, CMessage* tpMessage);

		// �����������ݿ����Ϣ
		void OnMessageExecuteSqlResponse(CMessage* tpMessage);

		// �������Գ�����������Ϣ
		void OnMessageGameHeartBeatNotice(int nServerID, CMessage* tpMessage);

		// ������Ϣ������ͼ��Ӧ
		void OnMessageCreateMapResponse(int nServerID, CMessage* pMessage);

		// ����
		void OnMessageRegistRepetionInfo( int nServerID, CMessage* pMessage );

		// ����ɾ��������ͼ��Դ
		void OnMessageDestroyRepetionMap( int vServerID, CMessage* pMessage );

		// �����������������Ϣ
		void OnMessageServerInfoNotice(int nServerID, CMessage* pMessage);

		// ��Ӧerating���ص�DataReport��Ϣ
		void OnAGIPMsgGWDataReportResponse(SysProtocol* pSysProto, int nParam1, int nParam2);

		// ����ERating״̬֪ͨ
		void OnMessageERatingStateNotice(CMessage* tpMessage);

		// ��Ӧerating proto ���
		void OnMessageERatingProtoStream(CMessage* pMessge);
		
		// ��ĳ�����ҵ����г�Ա������Ϣ
		void SendCountryMessage(CMessage *pMessage, int nCountryID);
		
		// ����������������׷�������Ϣ��֪ͨ
		void SendTracePlayerNotice();

		// ��ERating ���ʹ�������
		void SendCreateGroupProto2ERating(int nRoleID, const char* szGroupName, int nGroupType, int nObjectID);

		// �����г������͹ر�֪ͨ
		void SendShutdownNotify();

		// ������Ӧ�ر���Ϣ
		int OnMessageShutdownAck( CMessage* pMessage );
		
		// ����Ƿ���ip�б�����
		bool CheckIfIpInInternalIPList( int nIPAddr );

		// ��鵥IP�µ�������
		void CheckMultiClientPerIP();

		CConfigure mConfig;


		char mConfigtmpbuf[1024];


		enum emLauchFlag
		{
			EM_LAUNCH_LOADING		= 0, // ��������
			EM_LAUNCH_LOACOMPLETE,		 // �������
			EM_LAUNCH_SHUTDOWNING,		 // ���ڹرճ���
			EM_LAUNCH_SHUTDOWNCOMPLETE,	 // �رճ������
			EM_LAUNCH_SELFSHUTDOWNING,	 // ���ڹر�����
			EM_LAUNCH_EXIT				 // �˳�
		};

		// ˢ�¶��������ó���ȡ����timer����
		void RefreshTimerConfig();

	private:
		// ������ƿ���
		int mRunFlag;

		// ����������������ʱ��
		CWTimer mTimerOfKeepAlive;

		// ���¼����������������ʱ��
		CWTimer mTimerOfLoginKeepAlive;

		// ����������ģ��
		CModuleManager* tpModuleManager;// service module

		CWTimer mTimerOfReport2ERating;

		// ��鵥IP�ͻ�����������ʱ��
		CWTimer mTimerOfCheckMultiClientPerIP;

		//  
		CWTimer mWaitTimer;
		CWTimer mStateTimer;
		CWTimer mPerfTimer;
		CWTimer mOnLineNOTimer;
		CWTimer mOnLinePlayerStatPrintTimer;
		CWTimer mLaunchTimer; // �������timer
		int		mLaunchFlag;	// ���������־

		uint64_t mLastTickCount;	// the last timer active time.
		CTracePlayerManager mTracePlayerManager;
};

}

#endif
