#pragma once
#include "dungeontype.h"
#include "servertool.h"
#include "modulemanager.h"
#include "dungeontype.h"
#include "lk_string.h"
#include "lk_hashmap.h"
#include "sceneobj_manager.h"
#include "coretype.h"
using namespace SceneServer;
#define GLOBALWAR_TIMELIMIT_BUFF 77176
struct CGlobalTeleInfo   
{
public:
	lk::CString64 mAddr;	
	int mLoginToken;	
	int mLineID;
	int mMapID;
	int mPosX;
	int mPosY;
	int mTeleType;
	int mSceneType;
	int mSceneWorldID;	// Ŀ�곡��������ID
public:
	CGlobalTeleInfo()
	{
		mAddr.clear();	
		mLoginToken = 0;
		mMapID = 0;
		mLineID = 0;
		mPosX = 0;
		mPosY = 0;
		mTeleType = 0;
		mSceneType = 0;
	}
};

struct CGlobalWarInfo
{
public:
	int mLevel; // �ȼ���
	int mStatus;// ״̬
public:
	CGlobalWarInfo()
	{
		mLevel = 0;
		mStatus = 0;
	}
};
struct CGlobalMapData
{
public:
	int mMapID;
	int mPosX;
	int mPosY;
	int mLineID;
public:
	CGlobalMapData()
	{
		mMapID = 0;
		mPosX = 0;
		mPosY = 0;
		mLineID =0;
	}
};
class CGlobalModule : public CLogicModule, public CSingleton< CGlobalModule >
{
public:
	CGlobalModule():CLogicModule( "globalmodule" )
	{
		if ( CObj::msCreateMode )
		{
			Initialize();
		}
	}
	~CGlobalModule(){ }
public:
	static unsigned int CountSize();
	int Initialize();
public:
	typedef lk::hash_map< int, CGlobalTeleInfo, MAX_GLOBALTELEINFO_NUM > GlobalTeleInfoList;
	CWTimer mOutTimer;
	CWTimer mSyncTimer;
public:
	void OnServerMessgage( CMessage *pMsg );
	
	// �������͵Ļ�Ӧ��Ϣ
	void OnMsgGlobalTeleResponse( CMessage *pMsg );

	// ���Խ��븱����֪ͨ
	void OnMessageWarEnableNotify( CMessage *pMsg );
	
	// ��ұ�������Ϣ��Ӧ
	void OnMessageApplyWarResponse( CMessage *pMsg );

	// ���ս������
	int PlayerApplyWar( CEntityPlayer *pPlayer, int nRepetionIndex = _REPE_GLOBALWAR_INDEX_ );
	
	// ��������
	int GlobalTelePort( CEntityPlayer *pPlayer, EGlobalTeleType eTeleType , EServerType nServerType = ESERVERTYPE_DUNGEON, CGlobalMapData *pMapData = NULL );

	// �߳����
	void OnMessageKickPlayer( CMessage *pMsg );
public:
	// ����������
	virtual void OnLaunchServer( ){}

	// �˳�������
	virtual void OnExitServer( ){}

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffsekt );

	// ��������
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName ){ return 0; }

	// ·����Ϣ
	virtual void OnRouterMessage( CMessage* pMessage ){}

	// �ͻ��˷�����Ϣ
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage ){}

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst );

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );

	// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );

	// ��������
	virtual void OnLoadConfig( ) {}

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }
public:
	// ����һ��ȫ�ִ�����Ϣ
	int InsertGlobalTeleInfo( int nRoleID, CGlobalTeleInfo &rInfo );

	// ��ȡһ��ȫ�ִ�����Ϣ
	CGlobalTeleInfo *GetGlobalTeleInfo( int nRoleID );

	// ɾ��һ��ȫ�ִ�����Ϣ
	int DeleteGlobalTeleInfo( int nRoleID );

	// �뿪ս��
	void PlayerLeaveGlobalWar( int nRoleID, int nReason = EREASON_LEAVEWAR_RETURNBACK );

	// ����ս��
	void EndGlobalWar( int nReason, int nRegKey );

	// ��ȡ��������
	int GetGlobalteleType( int nCharID );

	// ͬ�����ƶ��е����
	int SyncGlobalPlayer();
private:
	GlobalTeleInfoList mGlobalTeleInfo;
};
