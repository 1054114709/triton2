#pragma  once

#include "servertool.h"
#include "modulemanager.h"
#include "dungeonmanager.h"
#include "shm.h"
#include "message_pb.hxx.pb.h"
using namespace DungeonServer;
struct CGlobalTeleData  
{
public:
	int	mLineID;			// ��ID	(��Ŀ�곡���ڱ���ʱ��Ҫ��Щ��Ϣ)
	int mMapID;			// ��ͼID
	int	mPosX;			// ������
	int	mPosY;			// ������		
	int mTeamFlag;		// �����־
	int mLoginToken;	// ��¼����
	KEY_TYPE mRepetionKey;// ������key
	int	mRepetionIndex;	// ��������
	int mSceneWorldID;		// Ŀ�곡��������ID
public:
	CGlobalTeleData()
	{
		mLineID = 0;
		mMapID = 0;
		mPosX = 0;
		mPosY = 0;		
		mTeamFlag = 0;
		mLoginToken = 0;
		mRepetionKey = 0;
		mRepetionIndex = 0;
		mSceneWorldID = 0;
	}
};
class CDungeonConfig  
{
public:
	int mMaxWarAliveTime;	// ����ս�����ʱ��(��)
	int mWarTimeInterval;	// ս���Ŀ���ʱ����(��)	
	int mTimeInterval;		// ���ִ��һ�μ��(����)	
	int mWarProctectTime;	// ��������ʱ��
	int mActivityTime;		// �����ʱ��
	int mMaxOffLineTime;	// ������߲�ɾ��ʱ��
	int mMaxWaitTime;		// ���ȴ�ʱ��
public:
	CDungeonConfig()
	{
		mMaxWarAliveTime = 1200;
		mWarTimeInterval = 30;	
		mTimeInterval = 300;
		mWarProctectTime = 180;
		mActivityTime = 7200;
		mMaxOffLineTime = 60;
		mMaxWaitTime = 30;
	}
};

// ȫ�������Ϣ
class CGlobalPlayer
{
public:
	enum 
	{
		EROLE_STATUS_NULL			= 0,		// ��ʼ״̬
		EROLE_STATUS_APPLY			= 1,		// ����״̬	
		EROLE_STATUS_INWAR			= 2,		// ��ս����
		EROLE_STATUS_INGLOBALSCENE	= 3,		// ��ȫ�ַ�������(�������µ�)
	};
public:	
	int mWorldID;			// ��ұ��������ID	
	int mWarRegKey;			// ս����ϢID
	int mStatus;			// ״̬
	int mServerKey;			// ������ڳ�����������ID				
	int mRepetionIndex;		// ȫ�ָ�������			
public:
	CGlobalPlayer()
	{
		mWorldID = 0;		
		mWarRegKey = 0;
		mStatus = 0;
		mServerKey = 0;	
		mRepetionIndex = 0;		
	}
};

class CDungeonModule : public CLogicModule
{
public:
	typedef lk::hash_map< int, CGlobalPlayer, MAX_GLOBALPLAYER_NUM > GlobalPlayerList;
public:
	CDungeonModule(): CLogicModule("CDungeonModule")
	{			
		mTimer = CWTimer(1000);		
	}
	~CDungeonModule(){}
public:
	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );													

	// ��������
	virtual void OnLoadConfig( );

	// ��һ�쵽��
	virtual void OnNewDayCome(  ) { }

	// ��һ�ܵ���
	virtual void OnNewWeekCome(  ) { }

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; } 

	// �����������ɹ�
	virtual void OnLaunchComplete( ){ }

	// ���շ�������Ϣ
	virtual void OnServerMessage( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID );

public:
	// ���������
	void OnMessageGlobalTeleportRequest( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID );

	// ���Ϳ������Ϣ
	void SendResponseGlobalTeleport( int nErrcode, int nRoleID, int nGameID, int nServerID,  const char  *pGateAddr, CGlobalTeleData &rTeleData );

	// ���ط��ؿ��֪ͨ
	void OnMessageRoleGlobalTeleResponse( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID );
	
	// ��������
	int CreateReption( CWarRegInfo *pWarRegInfo, int nServerListID = 0, int nRepetionIndex = 0 );

	// ���������Ļ�Ӧ��Ϣ
	void OnMessageCreateRepetionResponse( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID );

	// ��ұ���
	void OnMessagePlayerApplyWarRequest( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID );	
	
	// ���ͱ����Ļ�Ӧ��Ϣ
	void SendApplyWarResponse( int nGameID, int nServerID, int nErrcode, int nRegKey, int nRoleID, int nCanStart, int nMinLevel, int nMaxLevel, int nTeamFlag );

	// ���Ϳ��Խ�������֪ͨ
	void NotifyWarEnable( CWarRegInfo *pWarRegInfo );

	// �����֪ͨ���Խ���ս��
	void NotifyPlayerWarEnable( int nGameID, int nRoleID, int nWarRegKey, int nTeamFlag );

	// ����뿪ս������Ϣ֪ͨ
	void OnMessagePlayerLeaveWarNotify( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID );	

	// ս��������֪ͨ
	void OnMessageWarEndNotify( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID );	

	// �������˵���Ϣ����
	void OnMessageKickPlayer( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID );	

	// �������˵�֪ͨ
	void OnMessageKickGlobalPlayerACK( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID );	

	// ͬ�����ƶ����
	void OnMessageSyncGlobalPlayer( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID );	
public:
	// �ӵȴ��б�����ӳ�Ա��ս����
	void AddWarMemberFromWaitList();

	// ����Ƿ��п��Կ�����ս����Ϣ
	void CheckWarRegInfo();
	
	// ɾ������ʱ����������
	void RemoveTimeOutRole();

	// ɾ����Ч��ս����Ϣ
	void DeleteValidWarRegInfo();
public:
	// ��ȡȫ�ַ�������������Ϣ
	int ReadServerConfig( const char *pFile );

	// ��ȡ�ȼ�����
	int ReadLevelConfig( const char *pFile );

	// ��һ������
	int ReadDungeonConfig( const char *pFile );	

	// ��ȡ��Ϸ����
	int ReadGameConfig( const char *pFile );	
public:

	// ��ȫ�ַ��������������Ϣ
	CGlobalPlayer* RegPlayerToServer( int nRoleID, int nWorldID, int nRepetionIndex = 0 );

	// ���͵�ȫ�ַ�����
	void OnEventTeleToGlobalSceneServer();

	// ���ص�ԭʼ������
	void OnEventReturnToOriginalScene();

	// ��������
	void OnEventCreateRepetion();

	// ���ٸ���		
	void OnEventDestroyRepetion();
public:
	int InsertGlobalPlayer( int nCharID, CGlobalPlayer &rPlayer );
	CGlobalPlayer *GetGlobalPlayer( int nCharID );
	int DeleteGlobalPlayer( int nCharID );
public:
	// ����һ������������
	CWarRegInfoManager *CreateWarManager( int nServerListID, int nRepetionIndex );
	// ��ȡһ����������������Ϣ
	CWarRegInfoManager *GetWarManager( int nServerListID, int nRepetionIndex );
	// ��ȡһ������������
	CWarRegInfoManager *GetWarManagerByWorldID( int nWorldID, int nRepetionIndex );	
	// ɾ������������
	int DeleteWarManager( int nServerListID, int nRepetionIndex );
	// ɾ��ս����Ϣ
	void DeleteWarRegInfo( CWarRegInfo *pWarRegInfo );	
	// ����ս����������
	void SetWarStartNum( int nServerListID, int nWarStartNum );
public:	
	CWarRegInfoManager mWarRegInfoManager[MAX_GLOBAL_REPETION_NUM];
	CGlobalServerConfig mGlobalServerConfig;
	CServerManager mServerManager;
	CLevelConfig mLevelConfig;
	CDungeonConfig mDungeonConfig;
	CWTimer mTimer;
	GlobalPlayerList mGlobalPlayerList;
};