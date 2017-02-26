#pragma once

#include "servertool.h"
#include "coretype.h"
#include "protype.h"
#include "share_define.h"
#include "creator.h"
#include "container.h"
#include "base.h"
#include "timerinterface.h"
#include "familytype.h"
#include "corpstype.h"
#include "observer.h"
#include "property.h"
#include "speedup_checker.h"
#include "playerinfo_yqs.h"

class CEntity;
class CEntityMoney;
class CEntityDrop;
class CEntityItem;
class CEntityPedal;
class CEntityPet;
class CEntityNpc;
class CEntityFuncNpc;
class CEntityPlayer;
class CEntityCharacter;
class CMapObject;
class CEntityCollect;
class CEntityBox;
class CProperty;
class CPropertyCharacter;
class CPropertyNpc;


/*
enum EFcmStatus
{
	em_none_rate = 0,
	em_half_rate = 1,
	em_normal_rate = 2,
};
*/

enum EUnHandle
{
	UN_HANDLE_DROP_FOE_DIE		=	( 1 << 0 ),
	UN_HANDLE_PROCESS_FOE_DIE	=	( 1 << 1 ),
	UN_HANDLE_PROCESS_FOR_ATTACK=	( 1 << 2 ),
	UN_HANDLE_HONOR				=	( 1 << 3 ),
	UN_HANDLE_DURA				=	( 1 << 4 )
};


// ********************************************************************** //
// CEntity
// ********************************************************************** //
class CEntity : public CObj
{
public:
	bool				mHasCreated;	// �Ƿ��Ѵ���
	CWTPoint			mPos;			// ʵ������
	EDirType			mDirection;		// ��ҷ���
protected:	
	char				mAttCount;	// ��������
	unsigned short		mLineID;
	unsigned short		mMapID;
	unsigned short		mIndex;
	unsigned int		mCreatorID;		// ������������������ID��0��ʾ�ǹ���
	EEntityType			mEntityType;	// ʵ������
	EmEntityVisiblitiy	mVisibility;	// ��˭�ɼ�( �����ˣ��Լ��� ���� )
	EAliveType			mAliveState;	// ����״̬
	int					mMapObjectID;	// ��ͼ����ID
	unsigned int		mEntityID;	
	CSeenPlayerContainer	mSeenPlayerContainer;	// �ɼ����
	unsigned int		mCreateTime;// ʵ�崴��ʱ�����ʱ���(ms)
	static unsigned int	mListID;	// ����listid, �������ӷ��˴�ͷ����
public:
	
	CEntity( EEntityType vEntityType ) : mEntityType( vEntityType )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	}

	virtual ~CEntity( )
	{
	}

	virtual int Initialize( )
	{
		// -1, -1 �ǷǷ���
		mPos.mX = -1; 
		mPos.mY = -1;
		mLineID = INVALID_LINE_ID;
		mMapID = INVALID_MAP_ID;
		mIndex = INVALID_MAP_INDEX;
		mDirection = DIR_DOWN;
		mAliveState = ALIVE_NORMAL;
		mVisibility = VISIBLITY_ALL;
		mAttCount = 0;
		mCreateTime = 0;
		mMapObjectID = 0;
		mEntityID = 0;
		mCreateTime = 0;
		mAttCount = 0;
		mHasCreated = true;

		return 0;
	}

	virtual int Resume()
	{
		return 0;
	}

public:
	inline int SetVisibility( EmEntityVisiblitiy vIsVisibility ) { mVisibility = vIsVisibility; return SUCCESS; } 

	// ���״̬
	inline EAliveType GetAliveStatus( ) { return mAliveState; }
	inline void SetAliveStatus( EAliveType enAlive ) { mAliveState = enAlive; }
	bool IsAlive( ) const			{ return mAliveState == ALIVE_BATTLE || mAliveState == ALIVE_NORMAL; }

	// �Ƿ������
	inline bool IsPlayer( )		{ return GetEntityType() == ENTITYTYPE_PLAYER; }
	static inline bool IsValidPlayerID( int nEntityID ) { return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_PLAYER; }

	// �Ƿ��ǹ���
	inline bool IsOgre( )		{ return GetEntityType() == ENTITYTYPE_OGRE; }
	static inline bool IsValidOgreID( int nEntityID ) { return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_OGRE; }

	// �Ƿ��ǹ���NPC
	inline bool IsFunNpc( )		{ return GetEntityType() == ENTITYTYPE_FUNCNPC; }
	static inline bool IsValidFunNpcID( int nEntityID ) { return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_FUNCNPC; }

	// �Ƿ������塢������
	inline bool IsPedal( )		{ return GetEntityType() == ENTITYTYPE_PEDAL; }
	static inline bool IsValidPedalID( int nEntityID ) {  return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_PEDAL; }

	// �Ƿ��ǵ���
	inline bool IsItem( )		{ return GetEntityType() == ENTITYTYPE_ITEM; }
	static inline bool IsValidItemID( int nEntityID ) { return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_ITEM; }

	// �Ƿ��ǽ�Ǯ
	inline bool IsMoney( )		{ return GetEntityType() == ENTITYTYPE_MONEY; }
	static inline bool IsValidMoneyID( int nEntityID ) { return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_MONEY; }

	// �Ƿ��ǳ���
	inline bool IsPet( )		{ return GetEntityType() == ENTITYTYPE_PET; }
	static inline bool IsValidPetID( int nEntityID ) { return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_PET; }

	// �Ƿ��ǲɼ�NPC
	inline bool IsCollect( )	{ return GetEntityType() == ENTITYTYPE_COLLECT; }
	static inline bool IsValidCollectID( int nEntityID ) { return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_COLLECT; }

	// �Ƿ��Ǳ���
	inline bool IsBox( )		{ return GetEntityType( ) == ENTITYTYPE_BOX; }
	static inline bool IsValidBoxID( int nEntityID ) { return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_STOREBOX; }
	
	// �Ƿ��Ƕ�̬�赲NPC
	inline bool IsBlock( )		{ return GetEntityType( ) == ENTITYTYPE_BLOCK; }
	static inline bool IsValidBlockID( int nEntityID ) { return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_BLOCK; }

	// �Ƿ����ڵ�
	inline bool IsRedStone()  { return  GetEntityType() == ENTITYTYPE_REDSTONE; }
	static inline bool IsValidRedStoneID( int nEntityID ) { return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_EXPREDSTONE; }

	// �Ƿ���ͨ��NPC����
	inline bool IsNpc( )		{ return IsOgre() || IsFunNpc() || IsCollect() || IsPet() || IsBox() || IsBlock(); }
	static inline bool IsValidNpcID( int nEntityID ) { return IsValidOgreID( nEntityID) || IsValidFunNpcID( nEntityID) || IsValidBoxID( nEntityID) || IsValidBlockID( nEntityID); }
	
	// �Ƿ���character
	inline bool IsCharacter( )	{ return IsPlayer() || IsNpc() || IsPet() ;}
	static inline bool IsValidCharacterID( int nEntityID ) { return IsValidPlayerID( nEntityID ) || IsValidPetID( nEntityID ) || IsValidNpcID( nEntityID ) ;}

	// �Ƿ���ghost
	inline bool IsGhost()		{ return GetEntityType( ) == ENTITYTYPE_GHOST; }
	static inline bool IsValidGhostID( int nEntityID ) { return CObj::ID2TYPE( nEntityID ) == OBJTYPE_ENTITY_GHOST; }
	// �Ƿ��ǵ�������
	inline bool IsDrop( )		{ return IsItem() ; }

	// �Ƿ�����NPC
	virtual bool IsTaskNpc()  { return false;};
	
	// �õ�����ʱ��
	inline unsigned int GetCreateTime( ) { return mCreateTime; }
	inline void SetCreateTime( unsigned int unCreatTime ) { mCreateTime = unCreatTime; }

	// ��Ŀ������Ƿ�ɼ�
	virtual bool IsVisibleFor( CEntity* pTarget )  { return true; }

	// ʵ��ID
	inline unsigned int GetEntityID( ) const		{ return mEntityID; }
	int SetEntityID( unsigned int vEntityID ) { mEntityID = vEntityID; return 0; }
	
	// ����ʵ������
	inline EEntityType GetEntityType( ) const		{ return mEntityType; }

	// ����
	void SetEntityType( EEntityType type )	{ mEntityType = type; GetProperty()->SetEntityType( type ); }
	
	// ����ID ( Ĭ�Ϸ����Լ�)
	virtual unsigned int GetOwnerID() { return mEntityID; }

	// ����
	CEntity* GetOwner();
	
	// ��ID
	virtual unsigned short GetLineID( ) { return mLineID ; }
	virtual void SetLineID( unsigned short usLineID ) { mLineID = usLineID; }
	
	// ��ͼID
	virtual unsigned short GetMapID( )	 {return mMapID;}
	virtual unsigned short GetMapIndex( ) { return mIndex; }
	virtual void SetMapID( unsigned short usMapID )  { mMapID = usMapID; }
	virtual void SetIndex( unsigned short usMapIndex ) { mIndex = usMapIndex; }

	// ����
	virtual CProperty* GetProperty( ) = 0;
	
	// ����ID
	virtual unsigned short GetNationality( ) = 0;

	// �Ƿ�ж�
	virtual bool IsHostileTo( CEntity* pEntity ) = 0;
	
	// �Ƿ��Ѻ�
	virtual bool IsFriendlyTo( CEntity* pEntity ) = 0;
	// �Ƿ��Ƕ���
	virtual bool IsTeamTo( CEntity* pEntity ) = 0;
	
	// �Ƿ���ͬһ�����Ա
	virtual bool IsFamilyTo( CEntity *pEntity ) = 0;
	
	// �Ƿ���ͬһ�����Ա
	virtual bool IsCorpsTo( CEntity *pEntity ) = 0;

	// �Ƿ�����ʵ���Ѻ�
	virtual bool IsHostileToPlayers() = 0;

	// �ô�����Ϊʵ�帳ֵ
	virtual bool Setup( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator, CWTPoint* pPos = NULL, bool bInit = false, int vNpcID = 0 ) { return true; }

	// ����ɼ���
	virtual bool AddViewEntity( CEntity* pTarget );

	// �ӿɼ���ɾ��
	virtual bool DeleteViewEntity( CEntity* pTarget );

	// �õ���ʱ���������
	virtual ITimerReceiver* GetTimerReciver() = 0;

	virtual unsigned int GetNpcID( ) { return 0; }
	virtual void SetNpcID( unsigned int vNpcID ) { ; }

public:
	inline CWTPoint& GetPos() { return mPos; }
	inline int GetPosX() {return mPos.mX;}
	inline int GetPosY() {return mPos.mY;}
	inline void SetPosX(int x) 
	{ 
		if( x == -1 )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ] Set PosX Error %d, FUCK -1, FUCK Writer", __LK_FILE__, __LINE__,
				__FUNCTION__, x );
#ifdef _DEBUG_
			print_trace_fd( "default" );
#endif
		}
		mPos.mX = x; 
	}
	inline void SetPosY(int y) 
	{
		if( y == -1 )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ] Set PosX Error %d, FUCK -1, FUCK Writer", __LK_FILE__, __LINE__,
				__FUNCTION__, y );
#ifdef _DEBUG_
			print_trace_fd( "default" );
#endif
		} 
		mPos.mY = y; 
	}

	// ����
	inline EDirType GetDirection( ) { return mDirection; }
	inline void SetDirection( EDirType enDir ) { mDirection = enDir; }

	virtual int GetTeamFlag( ) = 0;
	
	// creator id
	inline unsigned int GetCreatorID( ) { return mCreatorID; }
	void SetCreatorID( unsigned int vCreatorID ) { mCreatorID = vCreatorID; }

	// �ɼ��������
	inline CSeenPlayerContainer& GetSeenPlayersContainer() { return mSeenPlayerContainer;}


	// �õ���ͼ����
	CMapObject* GetMapObject( );

	// �õ���ͼ����ID
	inline unsigned int GetMapObjectID() { return mMapObjectID; }

	// ���õ�ͼ����
	inline void SetMapObjectID( int nMapObjectID ) { mMapObjectID = nMapObjectID; }

	// ��ӵ������б���
	bool AddFunResult( unsigned int unSrcEntityID, unsigned short usFunc, unsigned short usResult, bool bBroadCast = true, unsigned int unValue1 = 0, unsigned int unValue2 = 0, unsigned int unValue3 = 0, unsigned int unValue4 = 0, unsigned int unValue5 = 0 );

	// ��ʼ�������б�
	void InitFunResult( int nListID = 0 );

	// Ŀ���Ƿ��ھ��뷶Χ��
	bool IsWithinDistance( CEntity* pTarget, unsigned int unDistance );

	// �Ƿ��ڿɼ���Χ��
	bool IsWithinViewDistance( CEntity* pTarget );

public:
	// ����ʹ�ü��ܻ�ִ��Ϣ
	virtual void SendUseSkillErrorNotice( int nType ) = 0;

	inline void AddAttackCount()
	{
		if ( ++mAttCount > 15 )
		{
			mAttCount = 1;
		}
	}

	inline int GetAttListID()
	{
		return ( ( 0xF0000000 | mEntityID ) & ( mAttCount << 28 | 0xFFFFFFF ) );
	}
};


class CEntityCharacter : public CEntity, public CCharacterObservable
{
protected:
	bool			mHasTarget;
	unsigned short	mMotionState;	// �ƶ�״̬
	CWTPoint		mTargetPos;
	double			mMoveLastTime;	// �������ƶ�ʱ��
	CEntityCharacter*	mEntityAureoList[ TEAMNUM ];	// �⻷����ʵ���б� ( �⻷ֻ��С������ )

public:
	CEntityCharacter( EEntityType vEntityType ) : CEntity( vEntityType )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}

	}

	virtual ~CEntityCharacter( )
	{
	}

	virtual int Initialize( )
	{
		mMotionState = MOTION_IDLE;
		mHasTarget = false;
		memset( mEntityAureoList, 0, sizeof( mEntityAureoList ) );
		return 0;
	}

	virtual int Resume()
	{
		return 0;
	}

public:
	inline CWTPoint GetTargetPos( ) { return mTargetPos; }
	void SetTargetPos( const CWTPoint& rPoint )
	{
		mTargetPos = rPoint;
		mHasTarget = true;
	}
	
	virtual ITimerReceiver* GetTimerReciver() = 0;

	int AddAureoEntityList( CEntityCharacter* pEntity );
	void ClearAureoEntityList( );
	void RemoveAureoEntityList( CEntityCharacter* pEntity );
	void CheckAureoEntityList( CEntityCharacter** pEntityList, int vEntityCount, CEntityCharacter** pAddEntityList, int& vAddEntityCount, CEntityCharacter** pRemoveEntityList, int & vRemoveEntityCount );

	inline CEntityCharacter* GetAureoEntity(unsigned int vIndex )
	{
		if ( vIndex >= 0 && vIndex < ARRAY_CNT( mEntityAureoList ) )
			return mEntityAureoList[ vIndex ];
		return NULL;
	}

	// �����жϻ
	void InterruptActivity();

public:
	inline bool GetContorlable( )	{ return ((CPropertyCharacter*)GetProperty())->Controlable( );  }

	// �ƶ���
	inline bool GetMoveable( )	{ return  ((CPropertyCharacter*)GetProperty())->Moveable( ) && IsAlive(); } // ��֪����û����ȷ����״̬������ֱ�ӵ��Ƚϱ���

	// �Ƿ���Թ���
	inline bool GetAttackable( ) { return ((CPropertyCharacter*)GetProperty())->Attackable( ); }

	inline unsigned short GetMotionState( ) { return mMotionState; }
	inline void SetMotionState( unsigned short vMotionState ) { mMotionState = vMotionState; }

	inline double GetMoveLastTime( ) { return mMoveLastTime; }
	inline void SetMoveLastTime( double vMoveLastTime ) { mMoveLastTime = vMoveLastTime; }

	virtual void SetIndex( unsigned short usMapIndex ) { mIndex = usMapIndex; }

	inline bool GetHasTarget( ) { return mHasTarget; }
	inline void SetHasTarget( bool vHasTarget ) { mHasTarget = vHasTarget; }

public:
	// ����ʹ�ü��ܻ�ִ��Ϣ
	virtual void SendUseSkillErrorNotice( int nType ) = 0;

	// ���BUFF״̬
	virtual void RemoveBuffState( CTemplateBuff* pBuffTpl, int& nSrcEntityID, int& nBackDamage );

	// ���BUFF״̬
	virtual void InsertBuffState( CEntityCharacter* pSrcEntity, CTemplateBuff* pBuffTpl, CBuffObject* vpBuffObj/*CBuffList* pBuffList*/, int nSkillType, int vDamage );
		
	// �ָ�HP
	virtual int CureHP( int vCureHP, unsigned int nSrcEntityID = 0, EResultType emType = RESULT_NORMAL, bool bAddFunc = true );

	// �ָ�MP
	virtual int CureMP( int vCureMP, unsigned int nSrcEntityID = 0, EResultType emType = RESULT_NORMAL, bool bAddFunc = true );

	// �ָ�AP
	virtual int CureAP( int vCureAP, unsigned int nSrcEntityID = 0, EResultType emType = RESULT_NORMAL, bool bAddFunc = true );

	// ����HP
	virtual int ExpendHP( int vCureHP, unsigned int nSrcEntityID = 0, EResultType emType = RESULT_NORMAL, bool bAddFunc = true );
	
	// ����MP
	virtual int ExpendMP( int vExpendMP, unsigned int nSrcEntityID = 0, EResultType emType = RESULT_NORMAL, bool bAddFunc = true );

	// ͵ȡHP
	virtual int StealHP( int nDamage );

	// ͵ȡMP
	virtual int StealMP( int nDamage );

	// ˲��ı�λ��
	virtual void ChangePos( CWTPoint vPos, EResultType emType, unsigned int nSrcEntityID = 0 );

	// ʵ������ʱ,���BUFF
	virtual void RemoveBuffEntityDie();

	// ʵ�����BUFF
	virtual int EntityInsertBuff( CEntityCharacter* pSrcEntity, CTemplateBuff* pBuffTpl, int nSkillType = 0, int nDamage = 0 , int nBuffTime = 0 );

	// ʵ��ɾ��BUFF
	virtual int EntityRemoveBuff( int vBuffID, int vListID = 0 );
		
	// ʵ�������Ƿ���ĳBUFF
	virtual bool EntityHasBuff( int nBuffID );

	// �ֶ�ɾ��BUFF
	virtual bool ActiveRemoveBuff( int nBuffID );

	// ʵ������
	virtual void EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf = false, bool vIsAward = true );
	
	// ����Ϊ����ʵ����������ؽӿ� ( ����,��Ҫ��Ϊ���Ժ�NPC���������ϲ���,����ΪPLAYER��װ����׼�� )
	// ��������,��һ�þ��� ( ��ʱֻ��OGRE�� )
	virtual void ExpForDie( CEntityCharacter* pSrcEntity ) {};
	// ��������,������Ʒ ( ��ʱֻ��OGRE�� )
	virtual void DropForDie( CEntityCharacter* pSrcEntity, int vMaxTeam ) {};
	// ����������� ( ��ʱֻ��OGRE,FUNCNPC,PET�� )
	virtual void TimeForDie( ) {};
	// ֪ͨ�������� ( CHARACTERʹ�� )
	virtual void NotifyDeath( CEntityCharacter* pSrcEntity );
	// ����ɱ��ȡѪ ( CHARACTERʹ�� )
	virtual void KillerRenew( CEntityCharacter* pSrcEntity );
	// �����ٻ����߼� ( ��ʱֻ��PLAYER,PETʹ�� )
	virtual void PetLogicForDie( ) {};
	// ��ù�ѫ ( ��ʱֻ��PLAYERʹ�� )
	virtual void HonorForDie( CEntityCharacter* pSrcEntity ) {};
	// PK���� ( ��ʱֻ��PLAYERʹ�� )
	virtual void PKRuleForDie( CEntityCharacter* pSrcEntity ) {};

	// ֪ͨ���Ըı�
	virtual void NotifyPropertyRefresh( ) = 0;

	// �Ƿ����ͨ��
	virtual bool CanPass( unsigned int nPosX, unsigned int nPosY );

	// ��ȡ����
	virtual const char* GetName() { return ""; };

	bool CheckBuffCondition( CTemplateBuff* vpBuff, CMapObject* vpMap );



	virtual int GetCampID( ) { return 0; }
	virtual int SetCampID( int vCampID );// { return SUCCESS; }

	// ʵ���Ƿ���buff
	bool HasBuff( int nBuffID ) ;

	// buff����
	void BuffTimeEvent( CTemplateBuff* tpBuffTpl, CBuffObject* tpBuff );

	// �Ƿ���Է���
	bool CanFly( );

	// �Ƿ���Ա�����
	bool CanBeTransformed( );

    //����ˢ�¼������buff
    void OnBuffRefreshCD( CEntityPlayer* tpPlayer, CTemplateBuff::CBuffFunc & buffFunc);

	// �õ���ɫ��ʵ��ȼ�
	int GetLevel();
};


// ********************************************************************** //
// CEntityPlayer
// ********************************************************************** //
class CEntityPlayer : public CEntityCharacter
{
public:
	enum COMM_STATE
	{
		STATE_INWAIT,					// �ȴ���ҽ��볡��
		STATE_INMAP,					// ������
		STATE_RETURNTOGATE,				// ����������
		STATE_LEAVEGAME,				// �뿪��Ϸ��
		STATE_REDIRECT,					// �糡����
		STATE_KICKOUT,					// ����������
		STATE_FORCEEXIT,				// ǿ���˳���
		STATE_REDIRECT_INWAIT,			// �ȴ������������ҽ��볡��,�б���STATE_INWAIT		
	};

	enum emSaveStatus
	{
		em_start_save = 1 ,
		em_finish_save = 2
	}; 

protected:
	bool			mIsExchange;			
	bool 			mIsRedirect;			// �Ƿ��ǿ糡����¼
	bool			mIfTracedPlayer;			// ������־: ����Ƿ�����Ҫ׷�ٵ����
	bool			mProtectStatus;
	CPropertyPlayer mProperty;
	CClientInfo		mClientInfo;
	CCharProfile	mCharProfile;	// ��ɫ��Ҫ
	unsigned int	mLoginToken;	// ��½����
	COMM_STATE		mCommState;		// ����״̬
	int				mCommHandle;	// ͨѶ�˿�
	CWTimer			mWaitTimer;		// �ȴ����ӵļ�ʱ��
	CWTimer			mLeaveTimer;	// ���߼�ʱ��
	time_t			mLastSaveTimeStamp; 
	time_t			mRedirectTimeStamp;	// ���״̬ΪSTATE_REDIRECT��ʱ���

	int				mLoadState;		// ��ȡ״̬
	int				mSaveState;		// �洢״̬
	int				mTLineID;		// ���ڿ������Ŀ�곡����Ϣ
	int				mTMapID;		// ���ڿ������Ŀ�곡����Ϣ
	int				mTX;			// ���ڿ������Ŀ�곡����Ϣ
	int				mTY;			// ���ڿ������Ŀ�곡����Ϣ
	int 			m_nProfileCheckSum;
	int 			m_nDetailCheckSum;
	unsigned int	mServerMoveTime;	// move time check
	long long		mClientMoveTime;	// move time check
	EPKMode			mPKMode;			// PKģʽ
	CPlayerTimerReceiver		mTimerReciver; // ��ʱ������
	int				mCreatMethod;		// ���������Ұ�Ĵ�����ʽ
	int				mRoleStatus;	// ���״̬����14λĿǰ��������״̬λ
	int				mRoleStatusParam; // ״̬�������磺����ʱ�䣬��ֹ��½ʱ��(�룩 )
	EFcmStatus 		mFcmStatus;		// ����������0.5�ı���
	int				mMoveDistance; // �ƶ���֤�ж� : ����
	unsigned int	mSpeedCheckTime; //�ƶ���֤�ж� : �ٶȼ��ʱ��
	CWTPoint		mLastCheckPoint; // �ϴμ�������
	int				mMsgCount;		 // ��Ϣ��֤�� ��Ϣ����
	int				mFirstMsgTime;	 // ��Ϣ��֤�� ��ʼͳ�ƺ��һ����Ϣ��ʱ��	 
	int				mHandle;					// ������ pk, ���� �Ƿ��������߼�( ����, PKֵ�仯 )
	int				mKickReason;	// ���������ߵĻ�������ԭ��
	int				mKickCode;		// ��ұ���ʱ���������ţ���Ҫ���ڷ����)
	unsigned int 	m_nGmStatus; 		// GM Ȩ��״̬
	int				mCallNpcEntityID; //  �ٻ�������NPC��ʵ��ID  ����Ҫ�ɵ� ʵʱ���� ������
	int 			m_nValidSeconds;	// ��Ч��ʱ��
	unsigned int	mCurRequestMsgSeq;	// �ͻ���������Ϣ��ǰ���кţ�����)
	int				mUnionID;			// ����ID
	int				mCountryID;
	emSaveStatus	mSaveProgress;
	int				mChatObjID;		// �������ID
	int				mMailObjID;	    // �ʼ�����ID
	int				mTeamFlag;		// ��ӱ�־��Ϊ�ӳ�charid
	unsigned int	mTeamID;		// ��TeamID
	int				mStallID;		// �󶨰�̯����
	int				mTaskToken;	    // ����������
	int				mFamilyID;		// ����ID
	int				mCorpsID;		// ����ID
	int				mHeadCorpsID;
	int				mOfficialID;
	int				mKingID;

	unsigned int	mPingTime;		// ��¼�ϴ��յ�PING��ʱ��

	int 			mGameID;						// �����Դ
	int				mMarriageID;	// ����ID
	int				mHydrangeaStatus;
	int				mPetCreatorID;			// �ٻ���creator id 
	char			mKey[ KEYLEN ];	// �����Կ
	char			mLogName[LOGNAMELENGTH];	// ������־: ׷����־��
	char			mUnionName[MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES];
	char			mRoleCreateTime[20];			// ��ɫ����ʱ��
	char 			mUserName[NAME_LENGTH+1];		// �ʺ�����
	int				mChangeCampTime;//ת��Ӫcd

	PBBourseDetailList mBourseBuyLog;
	PBBourseDetailList mBourseSellLog;
	bool			mBourseLogIsNeedLoad;

	int 			m_nAfterFcmKilled;			//������֮��ɱ�����������
	int				mFriendID;					// ����ף��ʱ�������ѵĽ�ɫID 

	int				mRoleWorldID;				// ��ɫ���������ID(����ID)	
	int				mSwornID;					// ���ID
public:
    CPlayerInfoForYaoQianShu moYaoQianShu;  // ҡǮ�����Ϣ

public:
    CSpeedChecker mSpeedChecker;

public:
	CEntityPlayer();

	virtual ~CEntityPlayer(); 

	virtual int Initialize()
	{
		CEntity::Initialize( );
		GetProperty()->Initial( );
		GetProperty()->SetEntityType( mEntityType );
		GetProperty()->SetEntityID( get_id() );
		ResetSpeedCheck( );

		mCommHandle =  0;
		mCommState = STATE_INWAIT; // ��ʼ���ɵȴ����볡��
		mWaitTimer =  1000 * 240;
		mLeaveTimer = 1000 * 240;
		mLastSaveTimeStamp = time(0);
		mTaskToken = -1;
		mIndex = 0;
        mTLineID = 0;
        mTMapID  = 0;
        mTX      = 0;
        mTY      = 0;
		mTeamFlag	= 0;
		mTeamID		= 0;
		mStallID	= 0;
		mClientMoveTime	= 0;
		mServerMoveTime = 0;
		mPKMode = PKMODE_TRAINING;
		memset( mKey, 0, sizeof( mKey ) );
		mLoadState = LSSTATE_NONE;
		mSaveState = LSSTATE_NONE;
		mFcmStatus = em_normal_rate;
		mChatObjID = 0;
		mMailObjID = 0;	
		mFamilyID = 0;
		// memset( mFamilyName, 0, sizeof( mFamilyName ) );
		// mIsFamilyHeader = false;
		// mIfHasFamilyApplies = false;
		mCorpsID = 0;		
		// memset( mCorpsName, 0, sizeof( mCorpsName ) );
		// mIsCorpsHeader = false;
		// mIfHasCorpsApply = false;	  	
		mCreatMethod = PLAYERCREAT_TELEPORT;
		mMsgCount = 0;
	    mFirstMsgTime = 0;	   	   
		mIfTracedPlayer = false;
		memset( mLogName, 0, sizeof(mLogName));
		mHandle = 0;
		m_nProfileCheckSum = 0;
		m_nDetailCheckSum = 0;
		mKickReason = 0;
		mKickCode = 0;
		// mExpGloryNeeded = 0;
		// mApGloryNeeded = 0;
		// mCorpsHeaderID = 0;
		// mFamilyHeaderID = 0;
		m_nGmStatus = 0;
		mCallNpcEntityID = 0;
		mSaveProgress = em_finish_save;
		mRoleStatus = 0;
		mRoleStatusParam = 0;
		m_nValidSeconds = -1;		// -1 �������
		// mFamilyPost = -1;
		// mCorpsPost = -1;
		mCurRequestMsgSeq = 0; 
		// mFamilyContribute = 0;
		// mCorpsContribute = 0;
		// mFamilyMoney = 0;
		// mCorpsMoney = 0;
		mUnionID = 0;
		memset( mUnionName, 0, sizeof( mUnionName ) );
		mHeadCorpsID = 0;
		mCountryID = 0;
		mOfficialID = 0;
		mKingID	= 0;
		mProtectStatus = true;

		mUserName[0] = 0;
		mMarriageID = 0;
		
		mRoleCreateTime[0] = 0;
		mHydrangeaStatus = 0;
		mPetCreatorID = INVALID_OBJ_ID;

		mGameID = 4;
		mIsExchange = false;
		mIsRedirect = false;
		mChangeCampTime = 0 ;
		mBourseLogIsNeedLoad = true;
		
		m_nAfterFcmKilled = 0;
		mRoleWorldID = 0;
		mSwornID = 0;
		return 0;
	}

	virtual int Resume()
	{
		ResetSpeedCheck( );
		mBourseLogIsNeedLoad = true;
		return 0;
	}

public:
	int SetHandle( EUnHandle vUnHandle ) { mHandle ^= vUnHandle; return SUCCESS; }
	int SetUnHandle( EUnHandle vUnHandle ) { mHandle |= vUnHandle; return SUCCESS; }
	bool IsHandle( EUnHandle vUnHandle ) { return ( mHandle & vUnHandle ) == 0; }

	bool GetBourseLogIsNeedLoad( ) { return mBourseLogIsNeedLoad; }
	int SetBourseLogIsNeedLoad( bool vIsLoad ) { return mBourseLogIsNeedLoad = vIsLoad; return SUCCESS; }
	int SetBourseLog( const PBBourseDetailList& vpBuyList, const PBBourseDetailList& vpSellList );
	int BourseLogSend( );

	virtual unsigned int GetLoginTime( ){ return mClientInfo.mSockTime; }
	inline virtual CProperty* GetProperty( ) { return &mProperty; }

	int	SetClientMoveTime( long long vClientMoveTime ) { mClientMoveTime = vClientMoveTime; return SUCCESS; }
	long long GetClientMoveTime( ) { return mClientMoveTime; }

	int SetServerMoveTime( unsigned int vServerMoveTime ) { mServerMoveTime = vServerMoveTime; return SUCCESS; }
	unsigned int GetServerMoveTime( ) { return mServerMoveTime; };

	// ��ð�������Ʒ
	CItemObject* GetItemObject( int vIndex )
	{ 
		return ( ( CPropertyPlayer* )GetProperty( ) )->GetBaggage()->GetItemObjPtr( vIndex );
	}
	// ����ID
	virtual unsigned int GetOwnerID();

	// �Ƿ�ж�
	virtual bool IsHostileTo( CEntity* pEntity );

	// �Ƿ��Ѻ�
	virtual bool IsFriendlyTo( CEntity* pEntity );

	// �Ƿ��Ƕ���
	virtual bool IsTeamTo( CEntity* pEntity );	
	
	// �Ƿ���ͬһ�����Ա
	virtual bool IsFamilyTo( CEntity *pEntity );
	
	// �Ƿ���ͬһ���ų�Ա
	virtual bool IsCorpsTo( CEntity *pEntity );

	// �Ƿ�����ʵ���Ѻ�
	virtual bool IsHostileToPlayers();

	// �������Ƿ������ֱ������򱣻�
	virtual bool IsBeginnerProtect();

	// �������Ƿ��ܵ��糡���������򱣻�
	virtual bool IsTransProtect();

	// �����Ƿ����
	virtual bool PKIsYellow( CEntity* pDesEntity );

	// ɱ���Ƿ����
	virtual bool PKIsRed( CEntity* pDesEntity );

	// ��Ŀ������Ƿ�ɼ�
	virtual bool IsVisibleFor( CEntity* pTarget );

	// ����CharID
	inline unsigned int	GetCharID( )	{return mCharProfile.mCharID; }
	inline void	SetCharID( unsigned int nCharID ) { mCharProfile.mCharID = nCharID; }

	// �������
	const char*	GetCharName( ) { return mCharProfile.mCharName; }
	inline void	SetCharName( const char* pszCharName ) 
	{
		if( pszCharName != NULL )
		{
			strncpy(mCharProfile.mCharName, pszCharName, sizeof( mCharProfile.mCharName )-1);
		}
	}
	
	// ����&��ȡ��������ID
	// void SetFamilyHeaderID( int nFamilyHeaderID ){ mFamilyHeaderID = nFamilyHeaderID; }
	// int	 GetFamilyHeaderID( ){ return mFamilyHeaderID; }
	
	// ����&��ȡ��������ID
	// void SetCorpsHeaderID( int nCorpsHeaderID ){ mCorpsHeaderID = nCorpsHeaderID; }
	// int	 GetCorpsHeaderID(){ return mCorpsHeaderID; }
	
	// ����&��ȡ��Ҹ���״̬
	void SetIfTarcePlayer( bool bValue ){ mIfTracedPlayer = bValue; }
	bool GetIfTracePlayer(  ){ return mIfTracedPlayer; }

	void SetUnionID( int nUnionID ){ mUnionID = nUnionID; }
	int	 GetUnionID( ){ return mUnionID; }

	void SetUnionName( const char *pUnionName )
	{
		strncpy( mUnionName, pUnionName, MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES -1 );
		mUnionName[MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES-1] = '\0';
	}
	const char *GetUnionName(){ return mUnionName; }

	const char *GetUnionNameShow()
	{
		// �ַ���������ʾ
#ifdef CHARSET_SHOW_GBK
		static char tUnionName[ MAX_CORPSNAME_LENGTH ] = {0};
		int nNameLen = sizeof(tUnionName)-1;
		charset_convert( "utf8", "gbk", (char*)mUnionName, strlen( mUnionName ),
			tUnionName, (size_t*)&nNameLen );
		return tUnionName;
#else
		return mUnionName;
#endif	
	}

	void SetHeadCorpsID( int nHeadCorpsID ){ mHeadCorpsID = nHeadCorpsID; }
	int	 GetHeadCorpsID( ){ return mHeadCorpsID; }

	// ����&��ȡ����
	void SetCountryID( int nCountryID ){ mCountryID = nCountryID; }
	int	 GetCountryID( ){ return mCountryID; }

	void SetOfficialID( int nOfficialID ){ mOfficialID = nOfficialID; }
	int	 GetOfficialID( ){ return mOfficialID; }

	void SetKingID( int nKingID ){ mKingID = nKingID; }
	int	 GetKingID( ){ return mKingID; }
	
	// ����&��ȡ��־����
	void SetLogName( const char *pLogName )
	{ 
		strncpy( mLogName, pLogName, LOGNAMELENGTH -1 );
		mLogName[ LOGNAMELENGTH -1 ] = '\0';
	}
	const char *GetLogName( ){ return mLogName; }
	
	// ��ʼ��������־
	int InitializeLog( );
	
	// �رո�����־
	int CloseLog( );
	
	// д��Ϣ��������־
	int WriteMsgInfo( CMessage *pMessage, int nMsgType = 1 );
	

	// �õ�GBK������û���
	const char* GetCharNameShow( )
	{
		// �ַ���������ʾ
#ifdef CHARSET_SHOW_GBK
		static char cCharName[ NAME_LENGTH ] = {0};
		int nNameLen = sizeof(cCharName)-1;
		charset_convert( "utf8", "gbk", (char*)mCharProfile.mCharName, strlen( mCharProfile.mCharName ),
			cCharName, (size_t*)&nNameLen );
		return cCharName;
#else
		return mCharProfile.mCharName;
#endif
	}
	
	// ��ҹ���
	inline unsigned short GetNationality( )	{ return mCharProfile.mNationality; }
	inline void SetNationality( unsigned short ucNation )	{ mCharProfile.mNationality = ucNation; }

	// �õ����һ�ε�½ʱ��
	inline unsigned int GetLastLoginTime( ) { return mCharProfile.mLastLogin; }
	inline void SetLastLoginTime( unsigned int unTime ) { mCharProfile.mLastLogin = unTime; }

	// �õ�����ʱ��
	inline unsigned int GetOnlineTime( ) { return mCharProfile.mOnlineTime; }
	inline void SetOnlineTime( unsigned int unTime ) { mCharProfile.mOnlineTime = unTime; }

	// �����־
	inline virtual int GetTeamFlag( ) { return mTeamFlag; }
	inline void SetTeamFlag(int nFlag) { mTeamFlag = nFlag;}

	inline unsigned int GetTeamID( ) { return mTeamID; }
	inline void SetTeamID( int nTeamID ) { mTeamID = nTeamID; }

	// ��̯
	inline void SetStallID( int nStallID ) { mStallID = nStallID; }
	inline int GetStallID( ) { return mStallID; }
	inline bool HasStall( ) { return ( ( mStallID > 0 ) ? true : false ); }

	// ְҵ
	inline unsigned char GetMetier( ) { return mCharProfile.mMetier; }
	inline void SetMetier( unsigned char ucMetier ) { mCharProfile.mMetier = ucMetier; }

	// PKģʽ
	inline EPKMode GetPKMode() { return mPKMode; }
	inline void SetPKMode( EPKMode vPKMode ) { mPKMode = vPKMode; }

	// �Ա�
	inline unsigned char GetSex( ) { return mProperty.GetSex(); }
	inline void SetSex( unsigned char ucSex ) { mProperty.SetSex( ucSex ); }

	// �ȼ�
	inline unsigned char GetLevel( ) { return mProperty.GetLevel(); }
	inline void SetLevel( unsigned char ucLevel ) { mProperty.SetLevel( ucLevel ); }
	
	// ����
	inline unsigned long long GetExp( ) { return mProperty.GetExp(); }
	inline void SetExp( unsigned long long nExp ) { mProperty.SetExp( nExp ); }

	// ��Ǯ & �󶨽�Ǯ
	inline int GetMoney() { return mProperty.GetMoney(); }
	inline int GetBindMoney() { return mProperty.GetBindMoney(); }

	inline int GetGoldenYB( ) { return mProperty.GoldenYB( ).remain( ); }
	inline CYuanBao& GetGolden( ) { return mProperty.GoldenYB( ); }
	int DecGoldenYB( int vYb ) 
	{ 
		LK_ASSERT( vYb > 0, return ERR_INVALID_PARAMETER );

		if ( mProperty.GoldenYB( ).lock( vYb ) == true )
		{
			if( mProperty.GoldenYB( ).commit( vYb ) == true )
			{
		//		GoldenNotice( );
				return SUCCESS;
			}
		}

		return ERR_NO_ENOUGH_MEMORY;
	}
	int IncGoldenYB( int vYb )
	{
		LK_ASSERT( vYb > 0 , return ERR_INVALID_PARAMETER );

		int rtn = ( mProperty.GoldenYB( ).add( vYb ) == true ) ? SUCCESS : ERR_UNKNOWN;

		if( rtn == SUCCESS )
		{
	//		GoldenNotice( );	
		}	
		
	}

	int GoldenNotice( );

	// ����
	inline unsigned short GetFaceType( ) { return mCharProfile.mFaceType; }
	inline void SetFaceType( unsigned short usFace ) { mCharProfile.mFaceType = usFace; } 

	// team leave
	unsigned short GetTeamLevel( );
	unsigned short GetTeamMaxLevel( );
	unsigned short GetTeamMinLevel( );

	// �ı�PKģʽ
	int ChangePKMode( unsigned int vPKMode );

	// �õ��ʺ�ID
	inline unsigned int GetAccountID( ) { return mCharProfile.mAccountID; }
	inline void SetAccountID( unsigned int unAccountID ) { mCharProfile.mAccountID = unAccountID; }

	// �������״̬
	inline COMM_STATE GetCommState( ) { return mCommState; }
	inline void SetCommState( COMM_STATE emCommState ) {mCommState = emCommState; }

	inline int GetCommHandle() { return mCommHandle; }
	inline void SetCommHandle( int vCommHandle ) { mCommHandle = vCommHandle; }

	// ��ҷ���״̬
	inline void SetServiceStatus( EService emStatus ) { mProperty.SetServiceStatus( emStatus ); }
	inline EService GetServiceStatus( ) { return mProperty.GetServiceStatus(); }

	// �õ���ʱ����ӿ�
	virtual ITimerReceiver* GetTimerReciver() { return &mTimerReciver; }
	
	// ����ģʽ
	int		GetCreatMethod(){ return mCreatMethod; }
	void	SetCreatMethod( int nCreatMethod ){ mCreatMethod = nCreatMethod; }

	inline int GetRoleStatus( void ){ return mRoleStatus; } 
	inline void SetRoleStatus( int vRoleStatus ){ mRoleStatus = vRoleStatus; }

	inline int GetRoleStatusParam( ) { return mRoleStatusParam; }
	inline void SetRoleStatusParam( int nRoleStatusParam ) { mRoleStatusParam = nRoleStatusParam; }

	inline EFcmStatus GetFcmStatus ()  { return mFcmStatus; }
	void SetFcmStatus (EFcmStatus emStatus) ; 

	inline CClientInfo* GetClientInfo( ) { return &mClientInfo; }

	inline unsigned int GetLoginToken( ) { return mLoginToken; }
	inline void SetLoginToken( unsigned int vLoginToken ) { mLoginToken = vLoginToken; }

	inline CWTimer* GetWaitTimer( ) { return &mWaitTimer; }
	inline void SetWaitTimer( int vWaitTimer ){ mWaitTimer = vWaitTimer; }

	inline CWTimer* GetLeaveTimer( ) { return &mLeaveTimer; }
	inline void SetLeaveTimer( int vLeaveTimer ){ mLeaveTimer = vLeaveTimer; }

	inline time_t GetLastSaveTimeStamp( ){ return mLastSaveTimeStamp; } 
	inline void SetLastSaveTimeStamp( time_t vLastSaveTimeStamp ){ mLastSaveTimeStamp = vLastSaveTimeStamp; }

	inline time_t GetRedirectTimeStamp( ){ return mRedirectTimeStamp; } 
	inline void SetRedirectTimeStamp( time_t vRedirectTimeStamp ){ mRedirectTimeStamp = vRedirectTimeStamp; }

	inline int GetTaskToken( ) { return mTaskToken; }
	inline void SetTaskToken( int vTaskToken ) { mTaskToken = vTaskToken; }

	inline char* GetKey( ) { return &mKey[ 0 ]; }
	void SetKey( const char* sKey) { memcpy(mKey, sKey, KEYLEN); }


	inline int GetLoadState( ) { return mLoadState; }
	inline void SetLoadState( int vLoadState ) { mLoadState = vLoadState; }

	inline int GetSaveState( ) { return mSaveState; }
	inline void SetSaveState( int vSaveState ) { mSaveState = vSaveState; }

	inline int GetTLineID( ) { return mTLineID; }
	inline void SetTLineID( int vTLineID ) { mTLineID = vTLineID; }

	inline int GetTMapID( ) { return mTMapID; }
	inline void SetTMapID( int vTMapID ) { mTMapID = vTMapID; }

	inline int GetTX( ) { return mTX; }
	inline void SetTX( int vTX ) { mTX = vTX; }

	inline int GetTY( ) { return mTY; }
	inline void SetTY( int vTY ) { mTY = vTY; }

	int CalProfileCheckSum();
	int CalDetailCheckSum(const char* from, size_t nsize);
	inline void ResetCheckSum(){ m_nProfileCheckSum = 0; m_nDetailCheckSum = 0; }

	inline int GetCallNpcEntityID() { return mCallNpcEntityID;}
	inline void SetCallNpcEntityID( int nValue) { mCallNpcEntityID = nValue;}
	
	// ��ù�ѫ
	inline int GetHonor( ) { return mProperty.GetHonor(); }

	// ��ȡ/�����������ID
	int  GetChatObjID(){  return mChatObjID; }
	void SetChatObjID( int vChatObjID ){ mChatObjID = vChatObjID; }
	
	// ��ȡ�����ʼ�����ID
	int  GetMailObjID() { return mMailObjID; }
	void SetMailObjID( int vMailObjID ){ mMailObjID = vMailObjID; }
	
	// ��ȡ���ü���ID
	void SetFamilyID( int vFamilyID ){ mFamilyID = vFamilyID; }
	int  GetFamilyID(  ){ return mFamilyID; }	


	// ����&��ȡ����ID
	void SetCorpsID( int nCorpsID ){ mCorpsID = nCorpsID; }
	int	 GetCorpsID( ){ return mCorpsID; }	
	
	// ����&��ȡ��ҷ��͵���Ϣ����
	void SetMsgCount( int nMsgCount ){ mMsgCount = nMsgCount; }
	int	 GetMsgCount(  ){ return mMsgCount; }
	
	// ����&��ȡͳ����Ϣ����ʱ��һ����Ϣ��ʱ��
	void SetFirstMsgTime( int nTime ){ mFirstMsgTime = nTime; }
	int	 GetFirstMsgTime( ){ return mFirstMsgTime; }  

	inline void SetRoleCreateTime( const char* pSrc ) { strncpy( mRoleCreateTime, pSrc, 19 ); }
	inline char* GetRoleCreateTime() { return mRoleCreateTime; }
	
	// ����&��ȡ����ID
	void SetMarriageID( int nMarriageID ){ mMarriageID = nMarriageID; }
	int GetMarriageID( ){ return mMarriageID; }	
	//����ת��Ӫcd
	void SetChangeCampTime(int nchangeCamptime){mChangeCampTime = nchangeCamptime;}
	int GetChangeCampTime(){return mChangeCampTime;}

	// ������֮��ɱ����������� 
	void IncAfterFcmKilled(int nCount = 1);
	void ResetAfterFcmKilled() { m_nAfterFcmKilled = 0; }
	int GetAfterFcmKilled(){return m_nAfterFcmKilled;}

	void SetGmStatus(unsigned int nStatus) { m_nGmStatus = nStatus; }
	unsigned int GetGmStatus() { return m_nGmStatus; }		

	// ����Ƿ����Ժ������
	bool FromPartner() { return mUnionName[0] == '$'; }
	int GetGameID() { return mGameID; }
	void SetGameID(int nGameID) { mGameID = nGameID; }

	// �����ϢƵ��
	bool CheckMsgFrequency( int nMsgLimitPerSec, int nCountLimit );
	
	// ˢ��ÿ�ռ���������
	void DailyCountRefresh( unsigned int unDate );

	// �õ����ܹ���CD
	inline int GetCommonCD( ) { return mProperty.GetCommonCD(); }

	// ִ�м�������
	void DoSkillCost( CTemplateSkill* tpSkillTpl, bool bIsMagicWeapon = false );

	// �жϼ��������Ƿ�����
	bool CheckSkillCost( CTemplateSkill* tpSkillTpl, bool bIsMagicWeapon = false );

	// �����Ƿ����ʹ��
	int CanUseSkill( CSkillObject* tpSkillObj, bool bIsMagicWeapon= false );

	// ��鼼������ǰ������
	int CheckSpecialUseCondition(  CTemplateSkill* tpSkillTpl, bool bIsMagicWeapon = false );

	// ������ȴ
	void DoSkillCoolDown( CSkillObject* pSkillObject, bool bIsMagicWeapon = false );

	// �������������
	void InterruptNpcService( );

	// �жϼ��������Ƿ�����
	bool CheckSkillWeapon( CTemplateSkill* tpSkillTpl );	

	// ֪ͨ���Ըı�
	virtual void NotifyPropertyRefresh( );

	// �ı�����ʱ����buff
	void ChangePKBuff( int vOldPKStatus, int vNewPKStatus, int vOldValue, int vNewValue );
	
	// ����&��ȡ��ҵ�����״̬
	void SetHydrangeaStatus( int nStatus ){ mHydrangeaStatus = nStatus; }
	int GetHydrangeaStatus(){ return mHydrangeaStatus; }
	
public:
	// ����ʹ�ü��ܻ�ִ��Ϣ
	void SendUseSkillErrorNotice( int nType );

	// ʵ����������
	virtual void EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf = false, bool vIsAward = true );

	// ʵ������ʱ,���BUFF
	void RemoveBuffEntityDie( );

	// �����ٻ����߼� ( ��ʱֻ��PLAYER,PETʹ�� )
	virtual void PetLogicForDie( );
	// ��ù�ѫ ( ��ʱֻ��PLAYERʹ�� )
	virtual void HonorForDie( CEntityCharacter* pSrcEntity );
	// PK���� ( ��ʱֻ��PLAYERʹ�� )
	virtual void PKRuleForDie( CEntityCharacter* pSrcEntity );

	// �Ƿ����ͨ��
	bool CanPass( unsigned int nPosX, unsigned int nPosY );

	// �Ƿ��ڹ���
	bool IsOverseas(){ return ( GetLineID() != GetNationality() )&&( IS_REPETION_LINE_ID( GetLineID() ) == false )&&(GetNationality() != 0) ;}


	// ����ٶ���֤����
	int SpeedCheckTeleport( );
	int ResetSpeedCheck( );

	int SetMoveDistance( unsigned int vLength )
	{
//		mMoveDistance += vLength;
		mMoveDistance++;

		return SUCCESS;
	}

	unsigned int GetSpeekCheckTime( ) { return mSpeedCheckTime; }
	int GetMoveDistance( ) { return mMoveDistance; }

	int SpeedCheck( bool vIsCoerce = false );

	bool RefrushPingTime( );

	// ��ȡ����
	virtual const char* GetName() { return GetCharName(); };

#ifdef _FB_
	virtual int GetCampID( );
#endif

#ifdef _FB_
	virtual int SetCampID( int vCampID )
	{
		CPlayerRepetion* tpRepetion = ( ( CPropertyPlayer* )GetProperty( ) )->GetRepetion( );
		CEntityCharacter::SetCampID( vCampID );
		return tpRepetion->SetCampID( vCampID );	
	}
#endif
	
	// �����˫��ʱ��, nRate��SERVER_PERCENT_INT(10000)Ϊ��׼
	void OpenActiveDoubleTime( int nRate);

	// �رջ˫��ʱ��
	void CloseActiveDoubleTime( ) ;

	// �õ�����ID
	int GetPetID( ) { return mProperty.GetPetID(); }
	void SetPetID( int nPetID ) { mProperty.SetPetID( nPetID ) ;}

	// �õ�����
	CEntityPet* GetPet( );

	// ������ù��Ķ�ʱ����ʱ���Ա���ʣ��ʱ�����
	//void TimeoutTimerForSaveData(  );

	// ��ȡ��ʱ����ʣ��ʱ��
	void GetLeftTimeofPlayerTimer( ); 

	// �ж��Ƿ����½���ɫ
	bool IsNewCharacter( );

	// ���ñ���ԭ��
	void SetKickoutReason( int nReason ) { mKickReason = nReason; }
	int GetKickoutReason( ) { return mKickReason; }

	void SetKickoutCode( int nCode ) { mKickCode = nCode; }
	int GetKickoutCode( ) { return mKickCode; }

	// ˢ��CD��
	int RefreshCDGroup( int *vCDGroup, int vNum );

	// ���CD��
	int CheckCDGroup( int *vCDGroup, int vNum );

	// ���CD��
	int ClearCDGroup( int *nCDGroup, int nNum );

	// ���ͼʱ���buff
	int CheckBuffOnChangeMap( CMapObject* vpMap );
	
	void StartSave() { mSaveProgress = em_start_save; }
	void FinishSave() { mSaveProgress = em_finish_save; }
	bool IsSaving() { return mSaveProgress == em_start_save; }
	bool HasSaved() { return mSaveProgress == em_finish_save; }

	void SetValidSeconds(int nSeconds) { m_nValidSeconds = nSeconds; }
	int  GetValidSeconds() { return m_nValidSeconds; }

	inline unsigned int GetCurRequestSeq( ) { return mCurRequestMsgSeq; }
	inline void SetCurRequestSeq( unsigned int unSeq ) { mCurRequestMsgSeq = unSeq; }

	inline void SetUserName(const char* szUserName) 
	{
		memcpy(mUserName, szUserName, sizeof(mUserName));
		mUserName[sizeof(mUserName)-1] = 0;

		if ( szUserName[0] == '$')
		{
			char buffer[12] = {0};
			memcpy(buffer, szUserName, 4);
			mGameID = atoi(&buffer[1]);
		}
	}

	inline const char* GetUserName() const { return mUserName; }

	void SetProtectStatus( bool vStatus ){ mProtectStatus = vStatus; }
	int	 GetProtectStatus( ){ return mProtectStatus; } 

	bool CanRemainFly( );

	// ����ٻ���creator id
	inline int GetPetCreatorID() { return mPetCreatorID; }
	inline void SetPetCreatorID( int nPetCreatorID ) { mPetCreatorID = nPetCreatorID; }

	// ע�⣬�������ڼ�¼��Ʒ��ʧ�����ٻ��ǽ���
	bool IsExchange() { return mIsExchange; }
	void SetExchange(bool flag) { mIsExchange = flag; }

	bool IsRedirect() { return mIsRedirect; }
	void SetRedirect(bool flag) { mIsRedirect = flag; }

	// ���������ĺ��ѽ�ɫ�ɣ�
	void SetFriendID( int nFriendID ){ mFriendID = nFriendID; }
	int GetFriendID(){ return mFriendID; }

	void SetRoleWorldID( int nWorldID ) { mRoleWorldID = nWorldID; }
	int GetRoleWorldID() { return mRoleWorldID; }

	void SetSwornID( int nSwornID )	{ mSwornID = nSwornID; }
	int GetSwornID(){ return mSwornID; }
};

// ********************************************************************** //
// CEntityNpc
// ********************************************************************** //
class CEntityNpc : public CEntityCharacter
{
protected:
	bool			mSuperState;	// ����״̬
	unsigned short	mTaskID;		// ������������ ����������� ��0
	unsigned int	mNpcID;			// ���NPC����ΪENTITYTYPE_OGRE,	��ô��ID�������ģ��ID
									// ���NPC����ΪENTITYTYPE_FUNCNPC, ��ô��ID����NPCģ��ID
									// ���NPC����ΪENTITYTYPE_PEDAL,	��ô��ID����0

	CWTPoint		mOrginPos;		// ������
	int				mOrginMapID;	// ������ͼID
	int				mOccurTimer;	// ���ļ�ʱ��
	int				mOccurTime;		// ����ʱ��
	CNpcTimerReceiver mTimerReceiver; // NPC��ʱ����
	int				mPolicyID;		// ����ID
	int				mPKType;		// pk����
	int				mGroupID;
	int				mNpcChangeState;// ����NPC�����״̬ 1������� 0��û��
	int				mOwnerCharID;	// �����߽�ɫID �������ĸ�������������  0��ʾ�޹���
	int				mSendNpcState;	// ����NPC״̬ ���ֵ���ܻᱻ����ģ�嶯̬�޸�  0=���ǻ���NPC 1=�ǻ���NPC
	int				mCallerEntityID;	// �ٻ�NPC���� ��������ٻ���һ��NPC��ʱ�� ��NPCҪ���ɵ�
	unsigned int	mNationality;	// ����NPC�Ĺ��� Ĭ����Line ID ����ǻ���NPC ���������ߵ�nation id
	#ifdef _FB_
	int				mCampID;
	#endif
	int				mIsShowOwner;	// NPCͷ���Ƿ���ʾ������
	int				mOwnCampID;		// ������ӪID

	int				mTranChangeLevel;

	CSeenCharactorNpcContainer mSeenNpcContainer; // �ɼ�npc����(��Ҫ����������������) 
public:

	CEntityNpc( EEntityType vEntityType ) : CEntityCharacter( vEntityType )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	}
	virtual ~CEntityNpc( )
	{}
		
	virtual int Initialize( )
	{
		CEntity::Initialize( );
		mOrginMapID = 0;
		mSuperState = false;
		mCreatorID = 0;
		mOccurTimer = 0;
		mPolicyID = 0;		

		mOccurTime = 0;

		mPKType = 0;
		mGroupID = 0;

		mNpcChangeState = 0;
		mOwnerCharID = 0;
		mTaskID = 0;

		mSendNpcState = 0;
		#ifdef _FB_
		mCampID = 0;
		#endif
		mIsShowOwner = 0;
		mCallerEntityID = 0;
		mNationality = 0;
		mNpcID = 0;
		mOwnCampID = 0;
		return 0;
	}

	virtual int Resume( )
	{
		return 0;
	}

public:
	inline void SetLevel( unsigned char ucLevel ) { GetProperty( )->SetLevel( ucLevel ); }
	inline int GetLevel( ) { return GetProperty( )->GetLevel( ); }

	// ����ɼ���
	virtual bool AddViewEntity( CEntity* pTarget );

	// �ӿɼ���ɾ��
	virtual bool DeleteViewEntity( CEntity* pTarget );

	// �ɼ�npc����
	inline CSeenCharactorNpcContainer& GetSeenNpcsContainer() { return mSeenNpcContainer;}

	virtual unsigned short GetNationality( ) { return mNationality; }
	void SetNationality( unsigned short nVal ) { mNationality = nVal; }
	// �����־
	virtual int GetTeamFlag( );

	// ����ID
	virtual unsigned int GetOwnerID();

	// �Ƿ�ж�
	virtual bool IsHostileTo( CEntity* pEntity );

	// �Ƿ��Ѻ�
	virtual bool IsFriendlyTo( CEntity* pEntity );

	// �Ƿ��Ƕ���
	virtual bool IsTeamTo( CEntity* pEntity );
	
	// �Ƿ���ͬһ�����Ա
	virtual bool IsFamilyTo( CEntity* pEntity );
	
	// �Ƿ���ͬһ���ų�Ա
	virtual bool IsCorpsTo( CEntity *pEntity ){ return false; }

	// �Ƿ�����ʵ���Ѻ�
	virtual bool IsHostileToPlayers();

	// ����Ƿ������ֱ������򱣻�
	virtual bool IsBeginnerProtect() { return false; };

	// ����Ƿ��ܵ��糡���������򱣻�
	virtual bool IsTransProtect()  { return false; };
	
	// �����Ƿ����
	virtual bool PKIsYellow( CEntity* pDesEntity ) { return false; }

	// ɱ���Ƿ����
	virtual bool PKIsRed( CEntity* pDesEntity ) { return false; }

	virtual ITimerReceiver* GetTimerReciver() { return &mTimerReceiver; }

	virtual unsigned int GetNpcID( ) { return mNpcID; }
	virtual void SetNpcID( unsigned int vNpcID ) { mNpcID = vNpcID; }

	inline CWTPoint GetOrginPos( ) { return mOrginPos; }
	inline void SetOrginPos( CWTPoint vOrginPos ) { mOrginPos = vOrginPos; }

	inline int GetOrginMapID( ) { return mOrginMapID; }
	inline void SetOrginMapID( int vMapID ) { mOrginMapID = vMapID; }

	inline bool GetSuperState( ) { return mSuperState; }
	inline void SetSuperState( bool vSuperState ) { mSuperState = vSuperState; }

	inline int GetOccurTime( ) { return mOccurTime; }
	inline void SetOccurTime( int vOccurTime ) { mOccurTime = vOccurTime; }

	inline int GetOccurTimer( ) { return mOccurTimer; }
	inline void SetOccurTimer( int vOccurTimer ) { mOccurTimer = vOccurTimer; }

	inline int GetPolicyID( ) { return mPolicyID; }
	inline void SetPolicyID( int vPolicyID ) { mPolicyID = vPolicyID; }

	inline int GetPKType( ) { return mPKType; }
	inline void SetPKType( int vPKType ) { mPKType = vPKType; }

	inline int GetNpcChangeState( ) { return mNpcChangeState; }
	inline void SetNpcChangeState( int vState ) { mNpcChangeState = vState; }

	inline int GetOwnercharID( ) { return mOwnerCharID; }
	inline void SetOwnerCharID( int vCharID ) { mOwnerCharID = vCharID; }

	inline int GetTaskID( ) { return mTaskID; }
	inline void SetTaskID( int vTaskID ) { mTaskID = vTaskID; }

	inline int GetSendNpcState( ) { return mSendNpcState; }
	inline void SetSendNpcState( int vState ) { mSendNpcState = vState; }

	inline int GetIsShowOwner( ) { return mIsShowOwner; }
	inline void SetIsShowOwner( int vState ) { mIsShowOwner = vState; }

	inline int GetCallerEntityID( ) { return mCallerEntityID; }
	inline void SetCallerEntityID( int vID ) { mCallerEntityID = vID; }

	virtual bool IsTaskNpc() { return mSendNpcState == 1; }

	virtual void EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf = false, bool vIsAward = true );

	virtual int ChangeNpcByLevel( unsigned int vLevel );

	inline int GetGroupID( ) { return mGroupID; }

	inline int GetOwnCampID( ) { return mOwnCampID; }
	inline void SetOwnCampID( int vOwnCampID ) { mOwnCampID = vOwnCampID; }

public:
	// ����ʹ�ü��ܻ�ִ��Ϣ
	virtual void SendUseSkillErrorNotice( int nType ) { };	
	
	// ����������� ( ��ʱֻ��OGRE,FUNCNPC,PET�� )
	virtual void TimeForDie( );

	// ֪ͨ���Ըı�
	virtual void NotifyPropertyRefresh( );
	
	// ��ȡ����
	virtual const char* GetName();

	#ifdef _FB_
	virtual int GetCampID( ) { return mCampID; }
	virtual int SetCampID( int vCampID ) { mCampID = vCampID; CEntityCharacter::SetCampID( vCampID ); return SUCCESS; }
	#endif
};




// ********************************************************************** //
// CEntityOgre
// ********************************************************************** //
class CEntityOgre : public CEntityNpc
{
private:
	CPropertyNPC	mProperty;


public:
	CEntityOgre() : CEntityNpc( ENTITYTYPE_OGRE )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	}

	CEntityOgre( EEntityType vEntityType ) : CEntityNpc( vEntityType )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	}

	virtual ~CEntityOgre()
	{}

	virtual int Initialize()
	{
		GetProperty()->Initial( );
		GetProperty()->SetEntityType( mEntityType );
		GetProperty()->SetEntityID( get_id() );
		return 0;
	}

	virtual int Resume()
	{
		return 0;
	}

public:
	inline virtual CProperty* GetProperty( ) { return &mProperty; }
	// ����ID
	virtual unsigned int GetOwnerID();

	// �Ƿ�ж�
	virtual bool IsHostileTo( CEntity* pEntity );

	// �Ƿ��Ѻ�
	virtual bool IsFriendlyTo( CEntity* pEntity );

	// �Ƿ��Ƕ���
	virtual bool IsTeamTo( CEntity* pEntity );
	
	// �Ƿ���ͬһ�����Ա
	virtual bool IsFamilyTo( CEntity* pEntity );
	
	// �Ƿ���ͬһ���ų�Ա
	virtual bool IsCorpsTo( CEntity *pEntity ){ return false; }

	// �Ƿ�����ʵ���Ѻ�
	virtual bool IsHostileToPlayers();

	// �ô�����Ϊʵ�帳ֵ
	virtual bool Setup( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos = NULL, bool bInit = false, int vNpcID = 0 );	
	
	// ��������,��һ�þ��� ( ��ʱֻ��OGRE�� )
	virtual void ExpForDie( CEntityCharacter* pSrcEntity );
	// ��������,������Ʒ ( ��ʱֻ��OGRE�� )
	virtual void DropForDie( CEntityCharacter* pSrcEntity, int vMaxTeam );
	// ����������� ( ��ʱֻ��OGRE,FUNCNPC,PET�� )
	virtual void TimeForDie( );

	virtual void EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf = false, bool vIsAward = true );
};

class CEntityBox : public CEntityOgre
{
public:
//	CPropertyBox  mBoxProperty;

public:
	CEntityBox( ) : CEntityOgre( ENTITYTYPE_BOX )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}

	}
	
//	virtual int Initialize()
//	{

//		GetProperty()->Initial( );
//		GetProperty()->SetEntityType( mEntityType );
//		GetProperty()->SetEntityID( get_id() );
//		return 0;
//	}

//	virtual int Resume()
//	{
//		return 0;
//	}

//	virtual CProperty* GetProperty( ) { return &mBoxProperty; }
	// ����ID
	virtual unsigned short GetNationality( ) { return GetLineID( ); }

	// �Ƿ�ж�
	virtual bool IsHostileTo( CEntity* pEntity ) { return false; }

	// �Ƿ��Ѻ�
	virtual bool IsFriendlyTo( CEntity* pEntity ) { return false; }

	// �Ƿ��Ƕ���
	virtual bool IsTeamTo( CEntity* pEntity ) { return false; } 
	
	// �Ƿ���ͬһ�����Ա
	virtual bool IsFamilyTo( CEntity* pEntity ){ return false; }
	
	// �Ƿ���ͬһ���ų�Ա
	virtual bool IsCorpsTo( CEntity *pEntity ){ return false; }

	// �Ƿ�����ʵ���Ѻ�
	virtual bool IsHostileToPlayers() { return true; };

//	virtual ITimerReceiver* GetTimerReciver() { return NULL; }

	virtual int GetTeamFlag( ) { return TEAM_NONE; }

	// ����ID
	virtual unsigned int GetOwnerID() { return GetEntityID( ); }

	// ��ȡ����
	virtual const char* GetName() { return ""; };


	virtual void EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf = false, bool vIsAward = true );
};

class CEntityBlock : public CEntityOgre
{
public:
//	CPropertyBlock  mBlockProperty;

public:
	CEntityBlock( ) : CEntityOgre( ENTITYTYPE_BLOCK )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}

	}
	
//	virtual int Initialize()
//	{

//		GetProperty()->Initial( );
//		GetProperty()->SetEntityType( mEntityType );
//		GetProperty()->SetEntityID( get_id() );
//		return 0;
//	}

//	virtual int Resume()
//	{
//		return 0;
//	}

//	virtual CProperty* GetProperty( ) { return &mBlockProperty; }
	// ����ID
	virtual unsigned short GetNationality( ) { return GetLineID( ); }

	// �Ƿ�ж�
	virtual bool IsHostileTo( CEntity* pEntity ) { return false; }

	// �Ƿ��Ѻ�
	virtual bool IsFriendlyTo( CEntity* pEntity ) { return false; }

	// �Ƿ��Ƕ���
	virtual bool IsTeamTo( CEntity* pEntity ) { return false; }
	
	// �Ƿ���ͬһ�����Ա
	virtual bool IsFamilyTo( CEntity* pEntity ){ return false; } 
	
	// �Ƿ���ͬһ���ų�Ա
	virtual bool IsCorpsTo( CEntity *pEntity ){ return false; }

	// �Ƿ�����ʵ���Ѻ�
	virtual bool IsHostileToPlayers() { return true; };

//	virtual ITimerReceiver* GetTimerReciver() { return NULL; }

	virtual int GetTeamFlag( ) { return TEAM_NONE; }

	// ����ID
	virtual unsigned int GetOwnerID() { return GetEntityID( ); }

	// ��ȡ����
	virtual const char* GetName() { return ""; };


	virtual void EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf = false, bool vIsAward = true );

	// �Ƴ��赲npc�Ķ�̬�赲 
	void RemoveBlock( );

	// �����赲�Ŀ���
	int ChangeMode( );

};


// ********************************************************************** //
// CEntityFuncNpc
// ********************************************************************** //
class CEntityFuncNpc : public CEntityNpc
{
private:
	CPropertyNPC	mProperty;

public:
	CEntityFuncNpc( ) : CEntityNpc( ENTITYTYPE_FUNCNPC )
	{
		if( CObj::msCreateMode )
		{
			Initialize( );
		}
		else
		{
			Resume( );
		}
	}
	inline virtual CProperty* GetProperty( ) { return &mProperty; }
	// �ô�����Ϊʵ�帳ֵ

	virtual bool Setup( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos = NULL, bool bInit = false, int vNpcID = 0 );

	virtual int Initialize( )
	{
//		CEntity::Initailize( );
//		mEntityType = ENTITYTYPE_FUNCNPC;

		GetProperty()->Initial( );
		GetProperty()->SetEntityType( mEntityType );
		GetProperty()->SetEntityID( get_id() );
		return 0;
	}

	virtual int Resume( )
	{
		return 0;
	}

	virtual void TimeForDie( );

	virtual void EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf = false, bool vIsAward = true );
	virtual bool IsFriendlyTo( CEntity* pEntity );

};

// ********************************************************************** //
// CEntityPet
// ********************************************************************** //
class CEntityPet : public CEntityNpc
{
protected:
	unsigned int mOwnerID;		// �ٻ��ߵ�ID
	unsigned int mOnlineTime;	// �ٻ��޵�����ʱ��
	int			 mCurTargetID;	// �ٻ��޵�ǰĿ��ID
	int			 mCurLevel;		// �ٻ��޵�ǰ��ʱ�ȼ�
	int			 mCurMode;		// ��ǰģʽ

private:
	CPropertyPet	mProperty;


public:

	CEntityPet() : CEntityNpc( ENTITYTYPE_PET )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	}

	virtual ~CEntityPet( )
	{}
	
	virtual int Initialize( )
	{
//		CEntity::Initailize( );
		mSuperState = false;
		mOwnerID = 0;
		mOnlineTime = 0;
		mCurTargetID = 0;
		mCurLevel = CTemplateSummonBeast::PET_LEVEL_ONE;
		mCurMode = 0;

		GetProperty()->Initial( );
		GetProperty()->SetEntityType( mEntityType );
		GetProperty()->SetEntityID( get_id() );

		return 0;
	}

	virtual int Resume( )
	{
		return 0;
	}

public:
	//virtual unsigned short GetMapID( )	{ return mMapID; }
	//virtual unsigned short GetLineID( ) { return mLineID; }
	inline virtual CProperty* GetProperty( ) { return &mProperty; }

	// ���״̬
	virtual int GetTeamFlag( );

	// ����ID
	virtual unsigned int GetOwnerID();

	// �Ƿ�ж�
	virtual bool IsHostileTo( CEntity* pEntity );

	// �Ƿ��Ѻ�
	virtual bool IsFriendlyTo( CEntity* pEntity );

	// �Ƿ��Ƕ���
	virtual bool IsTeamTo( CEntity* pEntity );
	
	// �Ƿ���ͬһ���ų�Ա
	virtual bool IsCorpsTo( CEntity *pEntity ){ return false; }
	
	// �Ƿ���ͬһ�����Ա
	virtual bool IsFamilyTo( CEntity* pEntity ){ return false; }

	// �Ƿ�����ʵ���Ѻ�
	virtual bool IsHostileToPlayers(); 

	virtual void EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf = false, bool vIsAward = true );

	bool Setup(unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos = NULL, bool bInit  = false, int vNpcID = 0 );

	//inline unsigned int GetOwnerID( ) { return mOwnerID; }
	inline void SetOwnerID( unsigned int vOwnerID ) { mOwnerID = vOwnerID; }

	inline unsigned int GetOnlineTime( ) { return mOnlineTime; }
	inline void SetOnlineTime( unsigned int vOnlineTime ) { mOnlineTime = vOnlineTime; }

	inline int GetCurTargetID( ) { return mCurTargetID; }
	inline void SetCurTargetID( int vCurTargetID ) { mCurTargetID = vCurTargetID; }

	// ��ʱ�ȼ�
	inline int GetCurLevel( ) { return mCurLevel; }
	inline void SetCurLevel( int vCurLevel ) { mCurLevel = vCurLevel; }	

	inline int GetCurMode( ) { return mCurMode; }
	inline void SetCurMode( int vCurMode ) { mCurMode = vCurMode; }	

	// �����ٻ����߼� ( ��ʱֻ��PLAYER,PETʹ�� )
	virtual void PetLogicForDie( );

	// �Ƿ����ͨ��
	bool CanPass( unsigned int nPosX, unsigned int nPosY );

	// ��ȡ����
	virtual const char* GetName() { return ""; };

	virtual unsigned short GetNationality( )
	{
		CEntityPlayer *pOwner = (CEntityPlayer *)CSceneObjManager::GetSingleton().GetObject( mOwnerID );
		if ( pOwner != NULL )
		{
			return pOwner->GetNationality();
		}
		
		return GetLineID( ); 
	}

#ifdef _FB_
	int GetCampID( ) 
	{ 
		CEntity* tpOwner = GetOwner( );
		if( tpOwner != NULL )
		{
			LK_ASSERT_STR( tpOwner->IsCharacter( ) == true, return 0, "EntityType %d", tpOwner->GetEntityType( ) );
			return ( ( CEntityCharacter* )tpOwner )->GetCampID( );
		}

		return 0;
	}
#endif
};


// ********************************************************************** //
// CEntityPedal
// ********************************************************************** //
class CEntityPedal : public CEntity
{
protected:
	unsigned short	mDstLineID;			// ����Ǵ���̤�壬��ô���͵�Ŀ����ID
	unsigned short	mDstMapID;			// ����Ǵ���̤�壬��ô���͵�Ŀ���ͼID
	unsigned short	mDstMapIndex;		// ����Ǵ���̤�壬��ô���͵�Ŀ���ͼindex
	unsigned short	mSkillID;			// ���������̤�壬��Ӧ����ID
	unsigned short	mSkillLevel;		// ���������̤�壬��Ӧ���ܵȼ�
	unsigned int	mNpcID;
	unsigned int	mOwnerID;			// �ͷ���ID
	unsigned int	mTeamID;			// ��������ID
										// TODO ��������Ŷ�,����,����,���ҵ�
	int				mPedalType;			// ̤������
	CWTRect			mSrcRect;			// ̤��Ĵ���Դ����
	CWTRect			mActRect;			// ̤������þ���
	CWTPoint		mDesPos;			// ����Ǵ���̤�壬��ô���͵�Ŀ������
	int				mSrcEntityID;		// ���������̤�壬�ͷ�����ID
	int				mPresistTime;		// ���������̤�壬����ʱ��
	unsigned int	mMinLevel;			// ���ƴ��͵ĵȼ�
	unsigned int	mRestrictNation;	// �������ƵĹ���
	CPropertyPedal  mProperty;
	unsigned int	mDelayTimer;		// ����̤�崥�����ʱ��
	//unsigned short  mLineID;
	//unsigned short 	mMapID;
	//unsigned short	mIndex;
public:

	CEntityPedal() : CEntity( ENTITYTYPE_PEDAL )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	}

	virtual ~CEntityPedal( )
	{
	}

	virtual int Initialize( )
	{
		mOwnerID = 0;
		mSkillID = 0;
		mSkillLevel = 0;
		mTeamID = 0;

		GetProperty()->Initial( );
		GetProperty()->SetEntityType( mEntityType );
		GetProperty()->SetEntityID( get_id() );

		mDelayTimer = 0;
		mVisibility = VISIBLITY_TEAM;
		return 0;
	}

	virtual int Resume( )
	{	
		return 0;
	}

	virtual void EntityDie( CEntityCharacter* pSrcEntity, bool bKillSelf = false, bool vIsAward = true );

	inline void SetOwnerID( unsigned int unOwnerID ) { mOwnerID = unOwnerID; }

	inline unsigned int GetTeamID( ) { return mTeamID; }
	inline void SetTeamID( unsigned int unTeamID ) { mTeamID = unTeamID; }
	
	inline int GetPedalType( ) { return mPedalType; }
	inline void SetPedalType( int nPedal ) { mPedalType = nPedal; }

	inline bool IsTeleport( ) { return mPedalType == PEDAL_TELEPORT; }		// �Ƿ�Ϊ����NPC
	inline bool IsTrap( ) { return mPedalType == PEDAL_TRAP; }				// �Ƿ�Ϊ����
	inline bool IsHierogram( ) { return mPedalType == PEDAL_HIEROGRAM; }	// �Ƿ�Ϊ���
	inline bool IsNeedFire( ) { return  mPedalType == PEDAL_NEEDFIRE; }     //�Ƿ��ǻ���

	inline CWTRect& GetSrcRect( ) { return mSrcRect; }
	inline void SetSrcRect( CWTRect& SrcRect ) { mSrcRect = SrcRect; }

	inline CWTRect& GetActRect( ) { return mActRect; }
	inline void SetActRect( CWTRect& ActRect ) { mActRect = ActRect; }

	inline CWTPoint& GetDesPos( ) { return mDesPos; }
	inline void SetDesPos( CWTPoint& DesPos ) { mDesPos = DesPos; }
	
	inline unsigned short GetDstLineID( ) { return mDstLineID; }
	inline void SetDstLineID( unsigned short usDstLine ) { mDstLineID = usDstLine; }

	inline unsigned short GetDstMapID( ) { return mDstMapID; }
	inline void SetDstMapID( unsigned short usDstLine ) { mDstMapID = usDstLine; }

	inline int GetSrcEntityID( ) { return mSrcEntityID; }
	inline void SetSrcEntityID( int nSrcEntityID ) { mSrcEntityID = nSrcEntityID; }

	inline int GetPresistTime( ) { return mPresistTime; }
	inline void SetPresistTime( int nPresist ) { mPresistTime = nPresist; }

	inline unsigned short GetSkillID( ) { return mSkillID; }
	inline void SetSkillID( unsigned short usSkillID ) { mSkillID = usSkillID; }

	inline unsigned short GetSkillLevel( ) { return mSkillLevel; }
	inline void SetSkillLevel( unsigned short usSkillLevel ) { mSkillLevel = usSkillLevel; }

	inline unsigned int GetMinLevel( ) { return mMinLevel; }
	inline void SetMinLevel( unsigned int unMinLevel ) { mMinLevel = unMinLevel ;}

	inline unsigned int GetmRestrictNation( ) { return mRestrictNation; }
	inline void SetRestrictNation( unsigned int unNation ) { mRestrictNation = unNation; }

	inline unsigned int GetDelayTimer() { return mDelayTimer; }
	inline void SetDelayTimer( unsigned int vDelayTimer ) { mDelayTimer = vDelayTimer; }

public:

	virtual unsigned short GetNationality( ) { return mLineID; }
	inline virtual CProperty* GetProperty( )	{ return &mProperty; }

	virtual unsigned int GetNpcID( ) { return mNpcID; }
	virtual void SetNpcID( unsigned int vNpcID ) { mNpcID = vNpcID; }

	virtual int GetTeamFlag( )
	{
		CEntityPlayer* pOwner = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( mOwnerID );
		return ( pOwner != NULL ) ? pOwner->GetTeamFlag() : TEAM_NONE;
	} 

	// ����ID
	virtual unsigned int GetOwnerID();

	// �Ƿ�ж�
	virtual bool IsHostileTo( CEntity* pEntity );

	// �Ƿ��Ѻ�
	virtual bool IsFriendlyTo( CEntity* pEntity );

	// �Ƿ��Ƕ���
	virtual bool IsTeamTo( CEntity* pEntity );
	
	// �Ƿ���ͬһ�����Ա
	virtual bool IsFamilyTo( CEntity* pEntity ){ return false; }
	
	// �Ƿ���ͬһ���ų�Ա
	virtual bool IsCorpsTo( CEntity *pEntity ){ return false; }
												 
	// �Ƿ�����ʵ���Ѻ�
	virtual bool IsHostileToPlayers();
	
	// ����
	virtual bool Setup(unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos = NULL, bool bInit  = false, int vNpcID = 0 );
	
	// ��Ŀ������Ƿ�ɼ�
	virtual bool IsVisibleFor( CEntity* pTarget );

	virtual ITimerReceiver* GetTimerReciver() { return NULL; };
public:
	// ����ʹ�ü��ܻ�ִ��Ϣ
	virtual void SendUseSkillErrorNotice( int nType ) { };

	// ���崥��
	bool IsTouch( int vTickOffset );

	// ʵ���Ƿ�������/���͵���
	bool IsTouchOn( CEntity* pEntity );

	// ���Ͷ���
	void TeleAction( int vTickOffset );

	// ���嶯��
	bool TrapAction( );

	// �������
	bool HierogramAction( );

	//���涯��
	bool NeedfireAction( );

	// �������
	void OnEntityHierogram( CEntityPlayer* pPlayer );

	// ����BUFF����
	void PedalBuffSkill( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateTrapSkill* pTrapSkill, int vSkillType = 0 );
	
	// ���巢��
	void OnEntityTrap( );

#ifdef _FB_
	int GetCampID( ) 
	{ 
		CEntity* tpOwner = GetOwner( );
		// Player�뿪Sceneʱ��, Owner����Ϊ��
		if( tpOwner != NULL )
		{
			LK_ASSERT_STR( tpOwner->IsCharacter( ) == true, return 0, "EntityType %d", tpOwner->GetEntityType( ) );
			return ( ( CEntityCharacter* )tpOwner )->GetCampID( );
		}

		return 0;
	}
#endif

};


// ********************************************************************** //
// CEntityDrop
// ********************************************************************** //
class CEntityDrop : public CEntity
{
protected:
	unsigned int	mNpcID;
	//unsigned short mLineID;
	//unsigned short mMapID;
	//unsigned short mIndex;

	CNpcTimerReceiver mTimerReceiver;		// NPC��ʱ����
public:
	//virtual unsigned short GetMapID( ) { return mMapID; }
	//virtual unsigned short GetLineID( ) { return mLineID; }
	//virtual unsigned short GetMapIndex( ) { return mIndex; }
	//virtual void SetMapID( unsigned short vMapID ) { mMapID = vMapID; }
	//virtual void SetIndex( unsigned short vIndex ) { mIndex = vIndex; }
	//virtual void SetLineID( unsigned short vLineID ) { mLineID = vLineID; }

	virtual unsigned short GetNationality() { return mLineID; }

	virtual unsigned int GetNpcID( ) { return mNpcID; }
	virtual void SetNpcID( unsigned int vNpcID ) { mNpcID = vNpcID; }
	
public:
	CEntityDrop( EEntityType vEntityType ) : CEntity( vEntityType )  
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	}

	virtual ~CEntityDrop()
	{}
	
	virtual int Initialize()
	{
		mNpcID = 0;
		mLineID = 0;
		mMapID = 0;
		mIndex = 0;
		return 0;
	}
	
	virtual int Resume() 
	{
		return 0;
	}

	inline virtual int GetTeamFlag( ) { return TEAM_NONE; }
	// ����ID
	virtual unsigned int GetOwnerID();

	// �Ƿ�ж�
	virtual bool IsHostileTo( CEntity* pEntity );

	// �Ƿ��Ѻ�
	virtual bool IsFriendlyTo( CEntity* pEntity );

	// �Ƿ��Ƕ���
	virtual bool IsTeamTo( CEntity* pEntity );
	
	// �Ƿ���ͬһ���ų�Ա
	virtual bool IsCorpsTo( CEntity *pEntity ){ return false; }
	
	// �Ƿ���ͬһ�����Ա
	virtual bool IsFamilyTo( CEntity* pEntity ){ return false; }

	// �Ƿ�����ʵ��ж�
	virtual bool IsHostileToPlayers();
	virtual ITimerReceiver* GetTimerReciver() { return &mTimerReceiver; }

public:
	// ����ʹ�ü��ܻ�ִ��Ϣ
	virtual void SendUseSkillErrorNotice( int nType ) { };
};

// ********************************************************************** //
// CEntityItem
// ********************************************************************** //
class CEntityItem : public CEntityDrop
{
private:
	CPropertyItem	mProperty;
public:
	CEntityItem() : CEntityDrop( ENTITYTYPE_ITEM )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	}
	virtual ~CEntityItem()	{}

	virtual int Initialize() 
	{
		GetProperty()->Initial( );
		GetProperty()->SetEntityType( mEntityType );
		GetProperty()->SetEntityID( get_id() );
		return 0;
	}

	virtual bool Setup(unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator, CWTPoint* pPos  = NULL , bool bInit  = false, int vNpcID = 0 );
	
	virtual int  Resume( )
	{
		return 0;
	}

	inline virtual CProperty* GetProperty( ) { return &mProperty; }
};

// ********************************************************************** //
// CEntityMoney
// ********************************************************************** //
class CEntityMoney : public CEntityDrop
{
private:
	CPropertyMoney	mProperty;
public:
	CEntityMoney() : CEntityDrop( ENTITYTYPE_MONEY )
	{
		if ( CObj::msCreateMode )
		{
			Initialize( );
		} 
		else
		{
			Resume( );
		}
	}
	virtual ~CEntityMoney() {}

	virtual bool Setup(unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator, CWTPoint* pPos  = NULL , bool bInit  = false, int vNpcID = 0 );

	virtual int Initialize()
	{

		GetProperty()->Initial( );
		GetProperty()->SetEntityType( mEntityType );
		GetProperty()->SetEntityID( get_id() );
		return 0;
	}

	virtual int Resume( )
	{
		return 0;
	}

	inline virtual CProperty* GetProperty( ) { return &mProperty; }
};

//
//// ********************************************************************** //
//// CEntityTaskNpc			�����г���NPC
//// ********************************************************************** //
//class CEntityTaskNpc : public CEntityNpc
//{
//public:
//	CEntityTaskNpc( ) : CEntityNpc( ENTITYTYPE_TASKNPC )
//	{
//		if( CObj::msCreateMode )
//		{
//			Initialize( );
//		}
//		else
//		{
//			Resume( );
//		}
//	}
//
//	//virtual CProperty* GetProperty( ) { return &mProperty; }
//	// �ô�����Ϊʵ�帳ֵ
//
//	//virtual bool Setup( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos = NULL, bool bInit = false );
//
//	virtual int Initialize( )
//	{
//		return 0;
//	}
//
//	virtual int Resume( )
//	{
//		return 0;
//	}
//};


// ********************************************************************** //
// CEntityCollect			�ɼ���NPC
// ********************************************************************** //
class CEntityCollect : public CEntityNpc
{
private:
	CPropertyNPC	mProperty;
protected:	
	int mNumber;	// ���ɵĴ���

public:
	CEntityCollect( ) : CEntityNpc( ENTITYTYPE_COLLECT )
	{
		if( CObj::msCreateMode )
		{
			Initialize( );
		}
		else
		{
			Resume( );
		}
	}

	inline virtual CProperty* GetProperty( ) { return &mProperty; }
	// �ô�����Ϊʵ�帳ֵ

	virtual bool Setup( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos = NULL, bool bInit = false, int vNpcID = 0 );

	virtual int Initialize( )
	{
		mNumber = 0;

		GetProperty()->Initial( );
		GetProperty()->SetEntityType( mEntityType );
		GetProperty()->SetEntityID( get_id() );
		return 0;
	}

	virtual int Resume( )
	{
		return 0;
	}

	inline int GetNumber( ){ return mNumber; }
	inline void SetNumber( int vNumber ){ mNumber = vNumber; }
};

// ********************************************************************** //
// CEntityRedStone
// �ڵ�ֻ���ڵ�����ʹ�ò��ܷ��뵽����
// ********************************************************************** //

class  CEntityRedStone: public CEntity
{	
public:
	CEntityRedStone( EEntityType vEntityType ) : CEntity( vEntityType )  
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
	CEntityRedStone(  ): CEntity( ENTITYTYPE_REDSTONE ) {  } 
	
	virtual int Initialize()
	{
		mPos.mX	= 0;
		mPos.mY	= 0;
		mStatus = 0;
		mTeamID = 0;
		return 0;
	}

	virtual int Resume()
	{
		return 0;
	}

	virtual ~CEntityRedStone(){}
public:
	// ����ID
	virtual unsigned int GetOwnerID( )  {  return mEntityID; };	
	
	// ��������ID
	void SetOwnerID( unsigned int vownerid ) {  }
	
	// 
	virtual int GetTeamFlag( ){ return 0; }
	
	//// ��ID
	//virtual unsigned short GetLineID( ) {  return mLineID; }
	//virtual void SetLineID( unsigned short usLineID ) {  mLineID = usLineID;  }
	//
	//// ��ͼID
	//virtual unsigned short GetMapID( ){  return mMapID; }
	//virtual unsigned short GetMapIndex( ) { return mMapIndex; };
	//virtual void SetMapID( unsigned short usMapID ) {  mMapID = usMapID; }
	//virtual void SetIndex( unsigned short usMapIndex ) {  mMapIndex = usMapIndex;  }
	// ����
	virtual CProperty* GetProperty( ) { return &mRedStoneProperty; }
	
	// ����ID
	virtual unsigned short GetNationality( ) { return ~0; }

	// �Ƿ�ж�
	virtual bool IsHostileTo( CEntity* pEntity ){ return false; }

	// �Ƿ��Ѻ�
	virtual bool IsFriendlyTo( CEntity* pEntity ) { return false; }

	// �Ƿ��Ƕ���
	virtual bool IsTeamTo( CEntity* pEntity ) { return false; }
	
	// �Ƿ���ͬһ�����Ա
	virtual bool IsFamilyTo( CEntity* pEntity ){ return false; }
	
	// �Ƿ���ͬһ���ų�Ա
	virtual bool IsCorpsTo( CEntity *pEntity ){ return false; }

	// �Ƿ�����ʵ���Ѻ�
	virtual bool IsHostileToPlayers( ) { return false; }

	// ��������
	virtual ITimerReceiver* GetTimerReciver( ) { return &mTimerReceiver; }	
	virtual bool Setup( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator, CWTPoint* pPos = NULL, bool bInit = false, int vNpcID = 0 ); 

public:
	void SetPos( int x, int y )
	{  
		if( x == -1 || y == -1 )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ] Set Pos Error %d, %d, FUCK -1, FUCK Writer", __LK_FILE__, __LINE__,
				__FUNCTION__, x, y );
#ifdef _DEBUG_
			print_trace_fd( "default" );
#endif
		}
		mPos.mX = x; 
		mPos.mY = y; 
	}
	int	 GetX(){ return mPos.mX ; }
	int  GetY(){ return mPos.mY ; }
	void SetStatus( int Status ){ mStatus = Status; }
	int  GetStatus( ){ return mStatus; }
	void SetTeamID( int TeamID ){ mTeamID = TeamID;  }
	int  GetTeamID( ) { return mTeamID; } 		
	bool IfInRedStoneBound( int Posx,int Posy );
	void SetTimerID( int vTimerID ){ mTimerID = vTimerID; }
	int	 GetTimerID(  ){ return mTimerID; }
	bool CheckIfOwner( int vCharID );		
	
	// ����&��ȡ������ʱ����ID
	void SetProcessTimerID( int nTimerID ){ mProcessTimerID = nTimerID; }
	int	GetProcessTimerID(){ return mProcessTimerID; }
private:
	CNpcTimerReceiver mTimerReceiver;			// �ڵ���ʱ��
	int			   mStatus;					    // ʹ��״̬
	unsigned int   mTeamID;						// ����ID	
	//unsigned int   mLineID;						// ��ID
	//unsigned int   mMapID;						// ��ͼID
	//unsigned int   mMapIndex;					// 
	unsigned int   mOwnerID[TEAMNUM];			// ������ɫID
	int			   mProcessTimerID;				// ������ʱ����ID
	CPropertyRedStone mRedStoneProperty;		// �ڵ�������
	int	  mTimerID;								// ��ʱ��ID	

public:
	// ����ʹ�ü��ܻ�ִ��Ϣ
	virtual void SendUseSkillErrorNotice( int nType ) { };
};

/* --------------------------------------------------------------------------*/
/* 
* @Synopsis ghost
*ֻ��һ��������  ֵ�𡣡���ֻ��ֻ�����ڸ�������Ϊû�д���ʱ���١�yucx
*/ 
/* ----------------------------------------------------------------------------*/

class CEntityGhost: public CEntityNpc
{
private:
	CPropertyNPC	mProperty;

public:
	CEntityGhost( ) : CEntityNpc( ENTITYTYPE_GHOST )  
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

	virtual bool Setup( unsigned short usLineID, unsigned short usMapID, unsigned short usMapIndex, CCreator* pCreator , CWTPoint* pPos = NULL, bool bInit = false, int vNpcID = 0 );

	virtual int Initialize()
	{
		mPos.mX	= 0;
		mPos.mY	= 0;
		return 0;
	}

	virtual int Resume()
	{
		return 0;
	}

	inline virtual CProperty* GetProperty( ) { return &mProperty; }
private:
	unsigned int	mNpcID;

};