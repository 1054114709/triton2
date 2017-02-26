#pragma once

#include "sceneobj_define.h"
#include "servercore.h"
#include "lk_vector.h"
#include "lk_hashmap.h"

class CNpcPolicy;

// ���������
#define TACTICSNUM	140
// ��ʱ�������
#define NPCTIMERNUM 100
// ����б�����
#define NPCENMITY	50
// Ѳ���б�����
#define PATROLNUM	20

class CObj;
class CEntity;
class CEntityNpc;
class CEntityOgre;
class CEntityPet;
class CEntityCharacter;
class TiXmlElement;


// ********************************************************************** //
// CNpcPolicy
// ********************************************************************** //

class CNpcEnmity
{
public:
	int		mEnmity;		// ���ֵ
	int		mEntityID;		// ��ָ��ʵ��ĳ��
	//CNpcEnmity *mpPrev;
	//CNpcEnmity *mpNext;
	// ��ָ��ĳ������±꣬-1��ʾ��Ч
	int		mpPrev;
	int		mpNext;
public:
	//CNpcEnmity( int vEnmity = 0, int vEntityID = 0 ) : mEnmity( vEnmity ), mEntityID( vEntityID )
	//{
	//}

	CNpcEnmity( )
	{
		if ( CObj::msCreateMode )
		{
			mEnmity = -1;
			mEntityID = -1;
			//mpPrev = NULL;
			//mpNext = NULL;
			mpPrev = -1;
			mpNext = -1;
		} 
		else
		{
			;
		}
	}
};


// ********************************************************************** //
// CNpcTimer
// ********************************************************************** //

class CNpcTimer
{
public:
	int mID;
	int mInterval;
	int mTimer;
	int mNum;
	bool mEnabled;
};

// ********************************************************************** //
// CNpcSkill
// ********************************************************************** //

class CNpcSkill
{
public:
	int mSkillID;
	int mSkillLevel;
	int mSkillTarID;
public:
	CNpcSkill( ) : mSkillID( 0 ), mSkillLevel( 0 ), mSkillTarID( 0 )
	{

	}
	CNpcSkill( int vSkillID, int vSkillLevel, int vSkillTarID ) : mSkillID( vSkillID ), mSkillLevel( vSkillLevel ), mSkillTarID( vSkillTarID )
	{

	}
};

// ********************************************************************** //
// CNpcPolicy
// ********************************************************************** //

// ����NPC���� 
class CNpcPolicy : public CObj
{
public:
	enum
	{
		STATE_PEACE,			// ��ƽ״̬
		STATE_BATTLE,			// ս��״̬
	};

	enum
	{
		STEPTIMER		= 300,
	};

	enum
	{
		CLOSE,					// ����
		DISTANT,				// Զ��
	};
public:
	typedef lk::vector< CWTPoint, 4 >	PathList;
	typedef lk::vector< CWTPoint, 4 >	PreList;
	typedef lk::vector< CNpcSkill, 5 >	SkillList;

	typedef lk::hash_map< int, int, NPCENMITY > 	ENMITY;

	int					mNpcID;
	int					mNpcType;
	int					mRunSpeed;			// �ƶ����ٶȣ���ģ���
	int					mMoveTimer;			// �ƶ���ʱ��
	int					mStepTimer;			// �߲���ʱ��
	int					mStandTimer;		// ��վ��ʱ��
	int					mSneerTimer;		// �����ʱ��
	int					mTempTimer;			// ��ʱ��ʱ��
	int					mAttackTimer;		// ������ʱ��
	int					mAttackMode;		// ������ʽ
	CWTPoint			mTargetPos;			// Ԥ��Ŀ���
	CWTPoint			mPathPos;			// ��ǰĿ���
	CWTPoint			mPrevPos;			// ֮ǰĿ���
	PathList			mPathList;			// NPC�ƻ�����·��
	PreList				mPreList;			// NPC�ƻ�����·��
	bool				mIsReturn;			// �Ƿ��ڷ���״̬
	int					mNpcState;			// NPCAI״̬
	int					mTargetEntityID;	// Ŀ��ʵ��
	int					mSneerID;			// �����ʵ��
	int					mMaxTempID;			// ��ʱ����ʵ��
	int					mMinTempID;
	int 				mLastAlive;			// �ϴ�����״̬
	int					mLastState;			// �ϴ�NPC����״̬
	int					mLastTick;
	CEntityNpc*			mpEntity;
	int					mEntityID;			//TODO
	bool				mPath;
	bool				mIsAttacking;
	
	bool				mBattleStart;
	bool				mBattleEnd;
	bool				mIsDead;			// �Ƿ�����
	bool				mKill;				// �Ƿ�ɱ�����
	short				mCanUseSkill;		// �Ƿ����ʹ�ü���
	SkillList			mSkillList;			// ʩ�ż��ܵ��б�
	CNpcTimer			mTimer[ NPCTIMERNUM ];
	int					mTimerNum;
	bool				mDone[ 45 ][ 5 ];	// �ж϶�Ӧ�Ĳ��������Ƿ��Ѿ�ִ��
	int					mTeleTimer;			// ���ָ��ʱ�����޷��߻أ����ͻس�����

	bool				mSleep;				// �Ƿ�������
	bool				mNoSleep;			// npc���κ�����¶������� 

	ENMITY				mEnmityData;		// �³������
	int					mFollowID;			// �����ʵ��ID
	int					mOffsetX;			// �����ƫ��X
	int					mOffsetY;			// �����ƫ��Y
	CWTPoint			mPatrolList[ PATROLNUM ];		// Ѳ��·���б�
	int					mPatrolIndex;		// Ѳ��·��λ��
	int					mPatrolDirection;	// Ѳ�߷���



public:

	CNpcPolicy( );
	virtual ~CNpcPolicy( );

	virtual int Initialize();
	virtual int Resume();

public:
	// �õ�����״̬
	inline bool IsSleeping( ) { return mSleep; }

	// ��ӳ��
	void InsertEnmity( int vEntityID, int vEnmity = -1 );

	// �õ���޵�Ŀ��
	int GetEnmityEntityID( );

	// ȫ����ճ��Ϊָ����ֵ
	void ClearEnmity( int vEnmity );

	// ���ָ��ʵ��ĳ��
	void ClearEnmity( int vEntityID, int vEnmity );

	// ɾ��ָ��ʵ���һ���ֳ��
	void RemoveEnmity( int vEntityID, int vEnmity );

	// �ƶ���ָ��λ��
	void MoveTo( const CWTPoint& rPoint );

	// ���س�����
	void Return2Orgin( bool vProtected, bool vReturn );

	// ������վ
	void Stand( int vTimer );

	// ����Ŀ��
	void ResetTarget( );

	// ��ͨ����
	void NormalAttack( CEntityCharacter* pTarget );

	// ���ܹ���
	void UseSkill( int vSkillID, CEntity* pTarget );

	// ���й���
	void DoAttack( );

	// �ٻ���˼��
	void OnPet( unsigned int vTickCount );

	// ����NPC˼��
	void OnTask( unsigned int vTickCount );

	// �õ���������
	bool GetAttackPosition( const CWTPoint& rSrcPos, const CWTPoint& rDesPos, int vRange, int vType );

	// �õ��������
	CWTPoint GetRandPos( );	

	// ����߼�����
	void OnTactics( int vTacticsID );

	// ���Ŀ��
	void GetTarget( int vCode, std::vector< int > &vTargetList );

	// ��ƽ״̬�߼�
	void OnPeace( unsigned int vTickCount );

	// ս��״̬�߼�
	void OnBattle( unsigned int vTickCount );

	// ������Ѱ��Ŀ��
	void SearchEnemy( );

	// ������Զ�ʱ
	void OnTacticTimer( unsigned int vTickOffSet );

	// �������߼�
	void OnBackLogic( );

	// ���������߼�
	void OnDieLogic( );

	// ��������߼�
	void OnIdle( );

	// �����߶��߼�
	void OnStep( );

	void FindPath( const CWTPoint& rSrcPos, const CWTPoint& rDesPos );
	void PathNpc( );
	void StepNpc( );

	CWTPoint GetMovePos( );
};


// ********************************************************************** //
// CNpcCondition
// ********************************************************************** //

class CNpcCondition
{
public:
	int mTypeID;
	int mParam1;
	int mParam2;
	int mParam3;
	int mParam4;
};

// ********************************************************************** //
// CNpcAction
// ********************************************************************** //

class CNpcAction
{
public:
	int	mTypeID;		// ����������
	int mParam1;		// �����Ĳ������ɾ������;�������
	int mParam2;
	int mParam3;
	char mSpeak[ 100 ];	// ��˵�Ļ�
	int mTarget;		// �����Ķ���
};

// ********************************************************************** //
// CNpcTrigger
// ********************************************************************** //

class CNpcTrigger
{
public:
	std::vector< CNpcCondition > mCondition;
	std::vector< CNpcAction > mAction;
	bool mActive;
	bool mInbattle;

public:
	void Initialize( )
	{
		mCondition.clear();
		mAction.clear();
		mActive = 0;
		mInbattle = 0;
	}
};

// ********************************************************************** //
// CNpcTactics
// ********************************************************************** //

class CNpcTactics
{
public:
	char	mTacticsName[ 100 ];
	std::vector< CNpcTrigger > mTrigger;

public:
	void Initialize( )
	{
		memset( mTacticsName, 0, sizeof(mTacticsName) );
		
		for( unsigned int i = 0; i < mTrigger.size(); i++ )
			mTrigger[i].Initialize();

		mTrigger.clear();
	}
};

// ********************************************************************** //
// CNpcModule
// ********************************************************************** //

class CNpcModule : public CLogicModule, public CSingleton< CNpcModule >
{
public:
	static char	sModuleName[ NAME_LENGTH ];
	CWTimer		mTimer;
	unsigned int mLastTickTimer; // npcģ������һ��tickʱ��
public:
	CNpcModule( ); 

	static unsigned int CountSize();

public:
	typedef lk::hash_map< int, int, SERVER_CAP_NPCPOLICY > NpcPolicys;

	NpcPolicys	mNpcPolicys;


public:
	static CNpcTactics mTactics[ TACTICSNUM ];

public:


	// NPC������
	void OnAttacked( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, unsigned int vEnmityValue );
	// NPC������
	void OnSneered( unsigned int vSrcEntityID, unsigned int vDesEntityID, unsigned int vSneerValue );
	// �˻���������
	void OnDead( unsigned int vDesEntityID, unsigned short vDead );
	// �ⲿ��������NPC ����NPC�ƶ�
	void OnMoveNpc( unsigned int vEntityID, unsigned int vPosX, unsigned int vPosY );
	// ���ô��ͺ�Ŀ���
	void OnTeleport( unsigned int vEntityID, unsigned int vPosX, unsigned int vPosY );

	// ����NPC�Ƿ�����(���cpp)
	void OnSleep( CEntityNpc* pEntity, bool vFlag, int nAutoSleep = 0 );

	// ���ø���Ŀ��
	void OnFollow( CEntityNpc* pEntity, unsigned int vFollowID, int vOffsetX, int vOffsetY );

	// ���λ������
	CWTPoint GetTargetPos( unsigned int vEntityID );

	// ֹͣ����NPC
	void StopTaskNpc( unsigned int vEntityID );

	// ����Ѳ������
	void SetPatrol( CEntityNpc* pEntity, int *vPosX, int *vPosY, int vLen, int vStart );


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
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode )
	{
		return true;
	}

	// ��������
	virtual void OnLoadConfig( );

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }

	// ���ز������õĻص�����
	static void LoadStrategyConfigCallback(const char* pcConfigPath);
};
