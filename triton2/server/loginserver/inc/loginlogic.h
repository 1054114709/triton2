#ifndef _LOGIN_LOGIC_H_
#define _LOGIN_LOGIC_H_

#include "tcp_conn.h"
#include "entity.h"
#include "message_pb.hxx.pb.h"

#include "clienthandle.h"
#include "loginobj_define.h"
#include "message_queue.h"
#include "message_dispatcher.h"
#include "coremessage_pb.hxx.pb.h"
#include "db_msg_pb.hxx.pb.h"

#ifdef USING_ERATING
#include "Macro.h"
#include "SysProtocol.h"
#include "AGIP.h"
#include "SysAlgorithmMD5.h"
#include <list>

#define const_md5code_length 32 
#define const_md5list_limit 16

#define const_whitelist_limit 256

#define CONFIG_STR_LEN 1024

enum eBindStatus
{
	em_binded_ok = 1, 		// bind ok
	em_binded_failure = 2, 	// bind failure, rebind until ok.
	em_binded_invalid = 3, 	// bind invalid, rebind and using local auth.
};

#endif

// ********************************************************************** //
// CLoginServer
// ********************************************************************** //

class CLoginServerConfigure
{
public:
	int nLoginTimerInterval;
	int nPingProxyInterval;
	int nERatingHandsetInterval;
	int nEratingSessionTimeout;
	int nServerSessionTimeout;
	int nMaxLoginPlayerOnceTimer;
	int nMaxWorldPlayerNum; // ��Ϸ����������
	bool bVerifyByLocalForce; // ǿ�Ʊ�����֤
	int nClientHandleIdleSleep;
	char szEChargeCode[32+1];
	char szEChargePasswd[64+1];
	int nEChargeID;
	int nRatingID;
	int nConnectEratingTimeout;

	int nIbPayRetryFirstInterval;
	int nIbPayRetryFirstTimes;
	int nIbPayRetrySecondInterval;
	int nIbPayRetrySecondTimes;

	int nIbUsedRetryFirstInterval;
	int nIbUsedRetryFirstTimes;
	int nIbUsedRetrySecondInterval;
	int nIbUsedRetrySecondTimes;
	int nValidateConnetSecOutTime;
	int nValidateConnetUSecOutTime;

	unsigned int  nClientVersion;
	bool bLoginServiced;
	bool bVerifyClientMd5Code;
	unsigned int nBlackIPList[64];

	//char sbClientMD5List[const_md5list_limit][const_md5code_length];

	typedef lk::hash_map< int, lk::string<const_md5code_length>, const_md5list_limit > MD5LIST;

	MD5LIST	mClientMD5List;

	char szWhiteNameList[const_whitelist_limit][CLoginPlayer::USER_NAME_LEN+1];
	
	CLoginServerConfigure();
};

class CLoginServer : public CSingleton< CLoginServer >
{
protected:
	CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH> 	 mERatingClient;
	CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH> 	 mProxyClient;
	CTCPConn<RECVBUFLENGTH, POSTBUFLENGTH> 	 mValidateClient;	

	CClientHandle*  mClientHandle;

	int mRunFlag;
	unsigned int mLastTickCount;

	lk::string<32> mERatingServerAddr;
	lk::string<32> mProxyServerAddr;

	lk::string<32> mGmCmdServerPort;
	lk::string<32> mChargeServerPort;
	int mLoginServerID;  // ��½��������server id

	time_t mLastPorxyKeepAliveTime;

	CWTimer mTimerOfKeepAlive;

#ifdef USING_ERATING
	// ���ERATING�Ͽ����ӣ���ERATING�����������������ʱ����
	CWTimer mTimerOfReConn2ERating;
	// ��fd����Eraing��������Ϣ��ע����new������
	SysProtocol* CreateERatingMessage(unsigned char* message_buffer, short message_length);

	// ����Erating
	bool Connect2ERating(eLinkMode emBlock = em_block_mode);
#endif

public:
	CLoginServer() {}
	~CLoginServer(){}

	enum ERunFlag
	{
		EFLG_CTRL_NO        = 0,
		EFLG_CTRL_QUIT      = 1,
		EFLG_CTRL_RELOAD    = 2
	};
	
	enum EValidateStatus
	{
		EFLG_VALIDATE_NOCHECK = 0,	// û����֤
		EFLG_VALIDATE_CHECKED = 1,	// ͨ����֤
	};

	static CSharedMem* mShmPtr;

	// ����LoginServer ռ�õĹ����ڴ�Ĵ�С, ��ʵ������Ҫռ���κι����ڴ�, loginlogic��Ҫռ��, 
	// ��Ϊmain����ֻ�ܿ���LoginServer, ��˽����ļ������������
	static unsigned int CountSize(); 

	// ��ʼ��
	int Initialize( int vInitFlag );

	// ������ͣ�ı�־
	void CheckRunFlags();
	void SetRunFlag( int vFlag );
	void ClearRunFlag();
	bool IsRunFlagSet( int vFlag );

	// ���ܴӷ�������������Ϣ�� ����ERating, ����GateServer, �Լ�����GateServer������ 
	void RecvServerMsg(int vMsgCount);

	// �ӹ����ڴ��ȡ�ͻ��˹�������Ϣ
	void RecvClientMsg(int vMsgCount);
	
	// ������֤����������Ϣ
	int RecvValidateMsg( int nSec, int nUsec );

	// ����������
	void Launch();

	// ���з����� 
	void Run(const int nDaemon );
	
	// ���ʱ��
	void CheckTimer();
	
	// ��PROXY����������ע����Ϣ
	void Regist2ProxyServer(); 	
	// ��PROXY����������ͬ����Ϣ
	void SendKeepAliveToProxy();
	
	// ����PROXY������������
	bool Connect2Proxy();
	
	// ������֤������������
	bool Connect2Validate();
	
	// ����֤����������ע��
	bool Regist2ValidateServer( );

	struct CLoginServerConfigure mConfig;

	// �������ļ�loginserver.xml ��ȡ���õ�vConfig
	int ReadCfg(CLoginServerConfigure& vConfig);
	// �õ�gameid����� login����
	int ReadCfgByGameId(CLoginServerConfigure &config);
	
public:

	// ����ҷ�����Ϣ�ӿ�
	void Send2PlayerImp( CLoginPlayer* tpPlayer, CMessage* pMessage );

	// ��ERating������Ϣ�ӿ�
	bool Send2ERating( BYTE* pMessage, int vMsgLen );

	// ��Gate������Ϣ�ӿ�
	int Send2ProxyImp( BYTE* pMessage, int vMsgLen );
	
	// ����֤������������Ϣ�ӿ�
	void Send2Validate( CMessage *tpMsg ); 	

	// �Ƿ��Ǻ�����IP��ַ
	bool IsBlackIP(unsigned int nAddr);

#ifdef USING_ERATING
	// ERATING �Ƿ�����
	bool IsConnected2ERating();

	// Close ERating
	void CloseERating() { mERatingClient.GetSocket()->Close(); }

	// �������erating����ʱ��
	time_t mTmSend2Erating;	

	// ������յ�erating����ʱ��
	time_t mTmRecv4Erating;
#endif
};

// ********************************************************************** //
// CLoginServer
// ��¼����������ͬ�������в�ͬ�İ汾
// ********************************************************************** //

class CLoginLogic;

class CLoginLogic : public CSingleton< CLoginLogic >
{
public:
	// �������
	typedef lk::hash_map<int, int,  PLAYER_AT_LOGIN_CAP>	PLAYERCONTAINER;
	typedef std::list< int > QUEUEPLAYERCONTAINER;

public:
	// �����ʼ����ַ
	static CSharedMem*  mShmPtr;

	// ���캯��
	CLoginLogic();

	// ��������
	~CLoginLogic();

	// ������new �� delete 
	void* operator new( size_t size );
	void  operator delete( void* pointer );

	// ����ռ���ڴ��С
	static unsigned int CountSize();

	// ��ʼ��
	void Initialize();

	// �ָ�����
	void Resume();

	// ��½������ʱ��
	void OnTimer( unsigned int vTickCount );

public:
	// ��Ӧ��֤����������Ϣ
	void OnValidateMessage( CMessage *pMessage );
	
	// ��Ӧ�Ӹ���������ع�������Ϣ
	void OnProxyMessage(CMessage* pMessage);

	// ��Ӧ�ͻ��˹�������Ϣ
	void OnClientMessage(CMessage* pMessage);

	// ��Ӧ���¶���loginserver.xml
	void OnReloadConfig();

	// ��Ӧ�˳���Ϣ
	void OnExit();

	// ��Gate������Ϣ
	void Send2Gate(CMessage* pMessage);

	// ��Ŀǰ���еĳ�������Ϣ
	void Send2AllScene(CMessage* pMessage);

	// ����erating�İ�״̬
	void UpdateERatingBindStatus(bool is_binded);

	// ��Ϸ�����Ƿ���
	bool IsWorldOpened() { return mServiceTurnedOn; }

	// ����commע�����, 
	void RegistPlayerComm(int nCommHandle, CLoginPlayer* tpPlayer);

	// ����ͨѶ�˿ڲ������
	CLoginPlayer* GetPlayerByComm( int nCommHandle );

	// ����뿪��½������, �������״̬���ٶ��� 
	void PlayerLeaveFromLogin( CLoginPlayer* tpPlayer);

	// ����SQL ����
	CServerSession* ExecuteSql( int vSessionType, int vParam1, int vParam2,
							int nFixID, int vCallBack, SQLTYPE vSqlType, const char * pSQL, ... );

	// TODO: ȡ��Charge��Ҫ��RatingID
	uint32_t GetRatingID( );

	uint32_t GetWorldID( ) { return mSingleWorld.mWorldID; }

	int GetGameID() { return mSingleWorld.mGameID; }

	#ifdef USING_ERATING
	// ��Ӧ��ERating��������Ϣ
	void OnERatingMessage(SysProtocol* pProto);

	// ��ERATINGע��
	void SendBindProto2ERating(em_connect_erating_flag emConnect);

	// ����AGIPSession����
	CAGIPSession* CreateSession4Proto(SysProtocol* pproto);
	#endif

	// ERating�Ƿ�󶨳ɹ�
	bool IsERatingBinded() { return mERatingIsBinded; }

	//��ȡ config �����ļ���Ŀ¼
	void GetConfigDataFileNamePath(int nGameID, char *filename, char *input, int len);


private:

	// ��ҵ�¼��� 
	void OnMessageLoginCompleteNotice(CMessage* pMessage);	

	// ��Ӧ���ط����������İ汾ע����Ϣ
	void OnMessageUpdateVersionNotice(CMessage* pMessage);

	// ��������ֹͣ��Ϣ��Ӧ 
	void OnMessageGateInfoNotice(CMessage* pMessage);
	void OnMessageGateShutDownNotice(CMessage* tpMessage);

	// ����������Ϣ
	void OnMessageGateHeartBeatNotice( CMessage* tpMessage );

	// ��Ӧ����뿪�����֪ͨ
	void OnMessagePlayerLeaveGateNotice(CMessage* tpMessage);

	// ��Ӧ��ҽ�������Ļ�Ӧ, ��ҽ����¼��Ϸ���� 
	void OnMessagePlayerEnterGateResponse(CMessage* tpMessage);

	// ��Ӧ��ҵ�¼����Ϸ����, ��ҽ�����Ϸ������
	void OnMessagePlayerLoginCompleteNotice(CMessage* tpMessage);

	// ��Ӧ���ݿ�ִ�н����Ϣ
	void OnMessageExecuteSqlResponse(CMessage* tpMessage);

	// ��֤����ʺ�
	void OnSessionVerifyAcctByMySql(CMessage* tpMessage, int vParamater1, int vParamater2 );

	// ��ҵ�½������
	void OnMessageLoginServerRequest( int vCommHandle, CMessage* pMessage);

	// ���յ��˳��Ŷ���Ϣ
	void OnMessagePlayerCancelLoginQueue( int vCommHandle, CMessage* tpMessage);

	// ע��comm, 
	void UnRegistPlayerComm(int nCommHandle);

	// ��ҵ�¼
	void PlayerLogin(CLoginPlayer* tpPlayer);


	// ��ͻ��˷�����Ϣ
	void Send2Client(CLoginPlayer* tpPlayer, CMessage* tpMessge);

	// �����ݿ������������Ϣ
	void Send2Data(int nFixID, CMessage* pMessage );

	// ����־������������Ϣ
	void Send2Log(int nFixID, CMessage* pMessage );

	// ���������ĳ�����������
	void Push2Gate( CLoginPlayer* pPlayer);

	void SendLoginErrorNotice(CLoginPlayer* tpPlayer, int nErrCode);

	void FireServerSession(int nSessionClass, CMessage* tpMessage, int nParam1, int nParam2);

	void OnServerSessionTimeout(int nSessionClass, int nParam1, int nParam2);

	// ������֤�ʺ�
	int VerifyAcctByLocal( CLoginPlayer* tpPlayer);

	// �����ʺŲ������
	CLoginPlayer* GetPlayerByAcct( int vAccountID );

	void LoginToLower( char * pszSrc, size_t len);

	// ���͵�ǰ���Ŷ�����
	void SendQueuePostion(CLoginPlayer* tpPlayer, size_t nPos);
	
	// ��֤��Ӧ��Ϣ
	void OnMessageValidateServerResponse( CMessage* pMessage );	

	// �õ��������������
	int GetWorldOnlinePlayerNum( ) { return mCurrentPlayerNumber; }
	void SetWorldOnlinePlayerNum( int nNum ) { mCurrentPlayerNumber = nNum; }

	#ifdef USING_ERATING
	// ע�ᵽErating
	void OnAGIPMsgBindResponse(SysProtocol* pSysProto, int nParam1, int nParam2);

	// ERating ��Ϣ������֤�ʺ�
	void SendUserLoginProto2ERating( CLoginPlayer* tpPlayer);
	void OnAGIPMsgUserLoginResponse(SysProtocol* pProto, int nParam1, int nParam2);

	// Unbind ����
	void SendUnbindProto2ERating();
	void OnAGIPMsgUnbindResponse(SysProtocol* pSysProto, int nParam1, int nParam2);

	// Handset ����
	void SendHandsetProto2ERating();
	void OnAGIPMsgHandsetResponse(SysProtocol* pSysProto, int nParam1, int nParam2);

	// ����IDȡ��CAGIPSession
	CAGIPSession* GetAGIPSession(int nSessionID);

	// ��Ӧ�����ع�����ERATING��Ϣ,protobuf��ʽ
	void OnMessageERatingProtoStream(CMessage* tpMessage);

	// ��Ӧ��Ϸ�����ERating��Ӧ����Ϣ
	void FireAGIPSession(int nSessionClass, SysProtocol* pproto, int nParam1, int nParam2);

	// ��Ϸ�����session��ʱ����
	void OnAGIPSessionTimeout(int nSessionClass, int nParam1, int nParam2);
	#endif

	bool IsJoinAuth(CLoginPlayer* tpPlayer);

private:
	// ��Ϸ����������(�������ض�ʱ֪ͨ)
	int	 mCurrentPlayerNumber;		

	// ������ͬʱ�����½����
	int	 mOnceLoginNumber;		

	// �������뿪������������
	int  mOnceLeaveNumber;

	CWTimer mWaitTimer;

	#ifdef USING_ERATING
	// �̳ǽ����ط�ʱ����
	CWTimer mTimerOfIbPay;

	// ERATING ������Ӧ����ʱʱ����, ͬʱҲ��������ʱ����
	CWTimer mERatingHandsetTimer;
	#endif

	// �Ƿ�ʹ��ERating����
	bool mERatingIsBinded;

	// TODO: GATE�Ƿ���
	bool mServiceTurnedOn;

	// Ψһ����
	CWorldServer mSingleWorld;

	// ��¼�����������, �����ʺ�����
	PLAYERCONTAINER mPlayerContainer;	

	// ���ӵ�LoginServer�����, fd ����
	PLAYERCONTAINER mPlayerConnected;	

	// ��¼�����Ŷӿ��ƶ���, ����������ݿ�������Ч��
	QUEUEPLAYERCONTAINER mLoginQueue;
};

#endif
