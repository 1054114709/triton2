#pragma once

#include "servercore.h"
#include "servertool.h"
#include "shm.h"
#include "scenelogic.h"
#include "lk_hashmap.h"

// ********************************************************************** //
// CMapModule
// ********************************************************************** //

// �궨�岿��
#define MAP_PBDATA_LEN	128 // ��ͼģ���������л������󳤶�

class CEntityCharacter;
class CEntity;
class CEntityNpc;
class CSharedMem;
class CMessage;


// �첽����
class CAsynTeleport
{
public:
	CAsynTeleport();
	~CAsynTeleport();
	
	int Initialize();


	int mTokenID;	// ����ID
	int mCharID;	 // ������
	char mCharName[ NAME_LENGTH ];	// �����˽�ɫ����
	int mTimeout;	 // ��ʱʱ�䣬��
	int mLevelLmt;	 // �ȼ�����

	struct DstChar
	{
		int mNationID;		// ��ӪID
		int mCountryID;		// ����ID
		int mCorpsID;		// ����ID
		int mFamilyID;		// ����ID
		int mCharID;		// ��ɫID 
		int mKing;			// �Ƿ����
	};	// ��������

	DstChar	mDstChar;
	ComplexPos mDestination; // Ŀ�ĵ�
};



// ��ͼģ��
class CMapModule : public CLogicModule, public CSingleton< CMapModule >
{
public:
	static char	sModuleName[ NAME_LENGTH ];
	CWTimer		mTimer;	
	int			mMoveCheck;

	typedef lk::hash_map< int, CAsynTeleport, 300 >  AsynTeleport;
	AsynTeleport	mAsynTeleportList;

public:
	CMapModule( ) : CLogicModule( sModuleName ), mTimer( CWTimer( 1000 ) )
	{
		if ( mShmPtr->GetInitMode() == SHM_INIT )
		{
			mMoveCheck = 0;
			mAsynTeleportList.initailize( );
		} 
		else
		{
			;
		}
	}
		
	~CMapModule() {}

	static unsigned int CountSize();

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
	virtual void OnLoadConfig( );

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }
private:

	// �������Ѱ·��Ϣ
	int OnMessagePlayerPathRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �������ֹͣ�ƶ���Ϣ
	int OnMessagePlayerStopRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����PetѰ·��Ϣ
	int OnMessagePetPathRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����Petֹͣ�ƶ���Ϣ
	int OnMessagePetStopRequest( CEntityPlayer* pPlayer, CMessage* pMessage );


public:
	// ����Ƿ����ͨ��
	bool CanPlayerPass( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, unsigned int vPosX, unsigned int vPosY, bool vFlyState );

	// NPC�Ƿ����ͨ��
	bool CanNpcPass( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, unsigned int vPosX, unsigned int vPosY, bool vFlyState );
	bool CanNpcPass( CEntityCharacter* tpEntity, unsigned int vPosX, unsigned int vPosY );

	// �Ƿ��ǰ�̯��ȫ����
	bool IsStallSafeArea( unsigned short usLineID, unsigned short usMapID, unsigned short vIndex, unsigned int vPosX, unsigned int vPosY );
	
	// ͨ������õ�ʵ���б�
	void GetRangeEntity(	unsigned short vLineID,
                           	unsigned short vMapID,
							unsigned short vIndex,
                            unsigned short vRangeType,
                            unsigned short vLength,
                            unsigned short vWidth,
                            CEntity* vpSrcEntity,
                            CEntityCharacter** vpEntityList,
							int* vpEntityCount 
						);


	//////////////////////////////////////////////////////////////////////////
	// ģ�����ú���
	//////////////////////////////////////////////////////////////////////////
	
	// �õ���ͼ����
	const char* GetMapName( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex );

	// ����Ƿ����ͨ��
	bool CanPlayerPass( unsigned short vLineID, unsigned short vMapID, unsigned int vPosX, unsigned int vPosY, bool vFlyState );

	// NPC�Ƿ����ͨ��
	bool CanNpcPass( unsigned short vLineID, unsigned short vMapID, unsigned int vPosX, unsigned int vPosY, bool vFlyState );

	//// �Ƿ�ȫ����
	//bool IsSafeRegion( unsigned short usLineID, unsigned short usMapID, unsigned short usIndex, int nPosX, int nPoxY  );

	// ��֤�����Ƿ���Ч
	bool IsCellValid( CEntity* pEntity, int nPosX, int nPoxY );

	// ʵ����·���ƶ�
	bool PathEntity(CEntityCharacter* pEntity, int nSrcPosX, int nSrcPosY, int nDesPosX, int nDesPosY, unsigned short usDir );

	// �ƶ�ʵ��
	bool MoveEntity( CEntityCharacter* pEntity, int nPosX, int nPosY, bool bStop );

	// ����ʵ��
	bool Teleport( unsigned short usLineID, unsigned short usMapID, int nPosX, int nPosY, CEntity* pEntity, unsigned short usMapIndex = 0, KEY_TYPE vKey = INVITED_KEY_VALUE );


	//////////////////////////////////////////////////////////////////////////

	// ����һ��NPC
	bool CreateNpc( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, CCreator* vpCreator, unsigned int& vEntityID, int vNpcID = 0, CWTPoint vPoint = CWTPoint( 0, 0 ), bool vDelay = false );

	// ������Ϣ��ָ����������
	void SendRectMessage(  unsigned short usLineID, unsigned usMapID, unsigned short usMapIndex, const CWTRect* pRect, CMessage* pMessage );

	// ��֤�������Ƿ��Ѿ�������ڰ�̯
	bool HasInStall( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CWTPoint& rPos );

	// ��֤�����Ƿ��Ǿ�̬�赲
	bool IsStaticBlock( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex , CWTPoint& rPos );

	// ��֤�����Ƿ��Ǹ߼��赲
	bool IsSuperBlock( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex , CWTPoint& rPos );

	// �õ����������
	bool GetDropPos( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CWTPoint &vOrginPos );

	// �ж�ָ���������Ƿ�����һ�NPC
	void HasEntity( CEntity* pSrcEntity, int nSrcPosX, int nSrcPosY,  unsigned short usRound, unsigned short usType );

	// ʹ�ü���ʱ,��ǰ��������������겻ͬ,�Լ��ܵ�ǰ����Ϊ��,��������(��ʱֻ��������Ч)
	void OnEntityMove( CEntityCharacter* pEntity, const CWTPoint& vDesPoint );

	//// �������Χ�ɼ���ҹ㲥
	//void MessageBroadCast( CEntityPlayer* pPlayer, CMessage* pMessage, bool bToSelf = false, bool bTeamOnly = false );

	//// NPC����Χ�ɼ���ҹ㲥
	//void MessageBroadCast( CEntityNpc* pNpc, CMessage* pMessage );

	//// ��Ҹ�����(ֻ��pet,pedal,redstone)����Χ�ɼ�������ҹ㲥
	//void MessageBroadCast( CEntity* pPlayerDependency, CMessage* pMessage, bool bTeamOnly  );

	void MessageBroadCast( CEntity* pEntity, CMessage* pMessage, bool bTeamOnly = false, bool bToSelf = false  );

	CWTPoint GetRandomPos( CEntityCharacter* pEntity );
	
	// �����첽����
	int AddAsynTeleport( CAsynTeleport& rAsynTele );

	// ��ѯ�첽����
	CAsynTeleport* GetAsyncTeleport( int nTeleTokenID );

	// ɾ���첽����
	int DeleteAsynTeleport( int nTeleTokenID );

	// ��ҵȼ��Ƿ������ͼ���Ƶȼ�
	bool IsLevelMatched( CEntityPlayer* pPlayer, int nMapID );

	virtual void OnLaunchComplete( );

	// ��������NPC���õĻص�����
	static void LoadDenyTempConfigCallback(const char* pcConfigPath);
};



