#pragma once

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "lua_tinker.h"
#include "sceneobj_define.h"
#include "chatmanager.h"
#include "proclient_svr.h"
#include "chat.h"
#include "servertool.h"
#include "servercore.h"
#include "globalmodule.h"
#define REPETION_LOG "rep"

#define IS_EFFECTIVE_VALUE( vValue ) ( ( vValue ) != 0 )

#define TIME_COUNT		( 30 )


#define REPE_ASSERT( a, fail_handle )	LK_ASSERT_LOG( REPETION_LOG, a, fail_handle )
#define REPE_ASSERT_STR( a, fail_handle, str, ... ) LK_ASSERT_LOG_STR( REPETION_LOG, a, fail_handle, str, \
																		##__VA_ARGS__ )

#define CHECK_TIME_KEY			( 1 << 0 )
#define CHECK_COUNT_KEY		( 1 << 1 )
#define CHECK_NUMBER_KEY		( 1 << 2 )

#define CHECK_FLAG( flag, key )		( ( key >= CHECK_ALL_FLAG ) ? ( flag == key ) : ( ( flag ) & ( key ) ) != 0 )

#define CHECK_ALL_FLAG		( CHECK_TIME_KEY + CHECK_COUNT_KEY + CHECK_NUMBER_KEY )
#define CHECK_REAL_GET( flag, un_check_flag )	( ( ~( CHECK_ALL_FLAG ) ^ ~( un_check_flag ) ) & flag )
#define GET_CHECK_FLAG( un_check_flag ) ( CHECK_ALL_FLAG - ( un_check_flag ) )
#define GET_UNCHECK_FLAG( flag )    ( CHECK_ALL_FLAG - ( flag ) )

#define UN_CHECK_FLAG_ADD( un_flag, un_flag_add ) ( ( un_flag_add ) | ( un_flag ) )		  

int GetRepetionCheck( );


enum REPE_JOIN_SPCE_TYPE
{
	REPE_JOIN_COUNT	 =	( 1 << 0 ),		// ������������
	REPE_JOIN_TIME	 =	( 1 << 1 ),		// �����������	
	REPE_JOIN_DATE	 =	( 1 << 2 )		// ��������ʱ��
};

enum RTIME_TYPE
{
	UN_BEGIN			= 0,		// begin time type, unbegin
	START_BEGIN 		= 1,		// begin time type, repetion start begin
	COMPLETE_TASK_BEGIN	= 2,		// begin time type, complate task begin
	EVENT_BEGIN			= 3,
};
enum RTIME_RESULT
{
	NOTHING			= 0,			// time event, nothing result
	CLOSE			= 1,			// time event, repetion close
};
enum RTIME_SYNC
{
	SYNC_NONE			= 0,			// no sync with player
	SYNC_ALL				= 1,			// sync with all player
	SYNC_CAMP			= 2,			// sync with camp player
};

struct RTimeEvent
{
	RTIME_TYPE		mType;
	RTIME_RESULT 	mResult;
	int				mInitTime;
	unsigned int	mLoopCountMax;
	bool			mIsCallFunc;
	int				mCamp;
	RTIME_SYNC		mSync;
	int				mSyncKey;
	//RTimeEvent( ): mType( UN_BEGIN ), mResult( NOTHING ), mInitTime( 0 ), mLoopCountMax( 0 ), mIsCallFunc( false ) { }
};


union UData
{
	int				mIValue;
};

struct CData
{
	int 			mKey;
//	DataKind		mDataKind;
	UData			mUData;

	int Init( int vKey/*, DataKind vDataKind*/) { mKey = vKey;/*mDataKind = vDataKind;*/ ClearData( ); return SUCCESS; }
	int ClearData( ) { memset( &mUData, 0, sizeof( mUData ) ); return SUCCESS; }
};

enum RepetionEvent
{
	REPETION_CREATE_PLAYER_EVENT	= 0,
	REPETION_CREATE_OGRE_EVENT		= 1,
	REPETION_TASK_END				= 2,
	REPETION_OGRE_DIE				= 3,
	REPETION_BOX_MACHINERY_SPRING_EVENT = 4,
	REPETION_TIMEASSIGNMENT			= 5,
	REPETION_ENTITY_MOVE_STOP		= 6,
	REPETION_CLOSE_EVENT			= 7,
	REPETION_EVENT_BEGIN			= 8,
	REPETION_EACH_OTHER				= 9,
	REPETION_LEAVE_EVENT			= 10,
	REPETION_CALL_FUN				= 11,
	EEPETION_RELIVE					= 12,
    REPETION_DEBUG_COMMAND			= 13,		
	REPETION_CHECK_AWARD			= 14,

	REPETION_EVENT_END,
	
};

enum RepetionSepecialCheck
{
	REPETION_SHITUCHECK = ( 1 << 0),  //�����飬�ӳ���Ҫ��ʦ������Աȫ������ͽ��
};

struct BattleCamp
{
	int			mCampID;
	int			mPosX;
	int			mPosY;
	
	BattleCamp( )
	{
		if( CObj::msCreateMode )
		{
			mCampID = 0;
			mPosX = 0;
			mPosY = 0;
		}
	}
};

struct RepetionInsertItem
{
	int			mItemID;
	int			mCount;
	int			mReason;

	RepetionInsertItem( )
	{
		if( CObj::msCreateMode ) 
		{
			mItemID = INVALID_OBJ_ID;
			mCount = 0;
			mReason = 0;
		}
	}
};

struct WaitList
{
	unsigned int			mLevelMin;
	unsigned int			mLevelMax;

	WaitList( )
	{
		if( CObj::msCreateMode )
		{
			mLevelMax = mLevelMin = 0;
		}
	}
};

struct JoinSpecCheck
{
	unsigned int			mLevelMin;
	unsigned int			mLevelMax;
	unsigned int			mKey;

	JoinSpecCheck( )
	{
		mLevelMax = mLevelMin = mKey = 0;
	}
};

struct SpecialItem
{
	int mItemID;
	int mFlag;

	SpecialItem( )
	{
		mItemID = 0;
		mFlag = 0;
	}
};

class CRepetionInfo
{
private:
	typedef lk::vector< DateSpace, 10 >	DATA_SPACE_LIST;
	typedef lk::vector< JoinSpecCheck, 5 > JOIN_SPEC_CHECK_LIST;
	typedef lk::vector< DateSpace, 10 >	SIGN_UP_LIST;
private:
	bool 			mUnRelive;			// ������ͨ����
	bool			mTeam;				// Is Redirect Team
   // unsigned short	mMapID;
	unsigned short	mTaskID;			// Into Repetin Need TaskID
	unsigned short  mPosX;
	unsigned short	mPosY;
	unsigned short  mPlayerPerNumber;	// EveryPlayer Into Repetion Everyday Max Number 
	unsigned short	mPlayerWeekPerNumber;
	unsigned short  mPlayerCount;		// Team Into Repetion, playcount less	
	unsigned short  mMinLevel;			// Into Repetion, Player Level less	
	unsigned short  mMaxLevel;			// Into Repetion, Player Level max	

	//TODO:
	unsigned short  mBackMapID;
	unsigned short  mBackPosX;
	unsigned short  mBackPosY;
	int				mRepetionIndex;		// repetion only key
        unsigned int	mPlayerCountMax;	// Player In Repetin Count Max

	//����Կ��
	SpecialItem		mSpecialItem[ 5 ];

	//������Ʒ
	int				mNecessity;

	// Repetion Common Event Arrary
	bool			mRepetionEvent[ REPETION_EVENT_END ];

	// Reption Time Event Arrary	
	RTimeEvent		mTimeEvent[ TIME_COUNT ];

	//����ʱ��
	DATA_SPACE_LIST	mDateSpace;
	DATA_SPACE_LIST mBattleOpenSpace;

        SIGN_UP_LIST    mSignUpList;
	JOIN_SPEC_CHECK_LIST mCheckList;

	BattleCamp		mCamp[ 3 ];

	WaitList		mWaitLevel[ WAIT_LIST_MAX ];

	int				mCommTakeMap[ 5 ];

	int				mMinTimer;					// ������̴���ʱ��

	int	mMapIDList[ REPE_MAP_COUNT_MAX ];
	uint64_t		mLastClearTime;
	int				mMinCheckTime;
	REPE_LEVEL		mTeamLevelFlag;
	int				mQuestionCheck;
	bool			mIsOnTimeOpen;
	bool			mNotLimitTime;				//�����Ƴ���ʱ��
	int				mSpecialCheck;
	int				mPlayerDataToClientIndex;	//���͸��ͻ�����������
	int				mRelogin;					// �Ƿ�����븱��
	int				mCloseTime;					// ����û���˺��ùر�
	int				m_nConsumeTimes;           // ���ĵĴ�����Ĭ��Ϊ1

	int				m_nDelaytime;				//������Ҫ�ӳ�ʱ��رյ�ʱ�䳤��  ΢��
public:
    CRepetionInfo( )
	{
		Clear( );
	}

	int SetLastClearTime( uint64_t vTime ) 
	{ 
		LOG_NOTICE( REPETION_LOG, "[ %s : %d ][ %s ] Repetion %d Set LastClearTime %lld", __LK_FILE__, __LINE__,
			__FUNCTION__, GetRepetionIndex( ), vTime );
		mLastClearTime = vTime; 
		return SUCCESS; 
	}
	uint64_t GetLastClearTime( ) { return mLastClearTime; }

	int SetMinCheckTime( int vMinCheckTime ) { mMinCheckTime = vMinCheckTime; return SUCCESS; }
	int GetMinCheckTime( ) { return mMinCheckTime; }

	int Clear( )
	{
		unsigned int i = 0;

		mPlayerCountMax = 0;
//		mMapID = INVALID_MAP_ID;
		mPosX = 0;
		mPosY = 0;
		mTaskID = 0;
		mTeam = false;
		mMinTimer = 5 * 60 * 1000;				// Ĭ��5����
		mRepetionIndex = INVALID_REPETION_INDEX;
		mUnRelive = false;
		mTeamLevelFlag = REPE_LEVEL_AVER;

		SetLastClearTime( 0 );

		for( i = 0; i < sizeof( mRepetionEvent ) / sizeof( mRepetionEvent[ 0 ] ); i++ )
		{
			mRepetionEvent[ i ] = false;
		}

		for( i = 0; i < sizeof( mTimeEvent ) / sizeof( mTimeEvent[ 0 ] ); i++ )
		{
			mTimeEvent[ i ].mType = UN_BEGIN;
			mTimeEvent[ i ].mResult = NOTHING;
			mTimeEvent[ i ].mInitTime = 0;
			mTimeEvent[ i ].mLoopCountMax = 0;
			mTimeEvent[ i ].mIsCallFunc = false;
			mTimeEvent[ i ].mCamp = 0;
			mTimeEvent[ i ].mSyncKey = 0;
			mTimeEvent[ i ].mSync = SYNC_NONE;
		}
		for( i = 0; i < sizeof( mCommTakeMap ) / sizeof( mCommTakeMap[ 0 ] ); i++ )
		{
			mCommTakeMap[ i ] = 0;
		}
		for( i = 0; i < sizeof( mCamp ) / sizeof( mCamp[ 0 ] ); i++ )
		{
			mCamp[ i ].mCampID = 0;
			mCamp[ i ].mPosX = 0;
			mCamp[ i ].mPosY = 0;
		}

		for( i = 0; i < sizeof( mWaitLevel ) / sizeof( mWaitLevel[ 0 ] ); i++ )
		{
			mWaitLevel[ i ].mLevelMin = 0;
			mWaitLevel[ i ].mLevelMax = 0;
		}
		mDateSpace.initailize( );
		mBattleOpenSpace.initailize( );
		mCheckList.initailize( );	

		mPlayerWeekPerNumber = 0;
		mPlayerPerNumber = 0;
		mPlayerCount = 0;
		mMinLevel = 0;
		mMaxLevel = 100;
		mBackMapID = 0;
		mBackPosX = 0;
		mBackPosY = 0;

		memset( mMapIDList, INVALID_MAP_ID, sizeof( mMapIDList ) ); 
		mQuestionCheck = 0;
		mIsOnTimeOpen = false;
		mNotLimitTime = false;
		mNecessity = 0;
		mSpecialCheck = 0;
		mPlayerDataToClientIndex = -1;
		m_nConsumeTimes = 1;
		m_nDelaytime = 500;
		return SUCCESS;
	}

	int SetUnRelive( int vRelive )
	{
		if( vRelive != 0 )
		{
			mUnRelive = true;
		}

		return 0;
	}

	bool IsUnRelive( ) { return mUnRelive; }

	int GetRepetionIndex( ) { return mRepetionIndex; }
	int SetRepetionIndex( int vRepetionIndex ) { mRepetionIndex = vRepetionIndex; return SUCCESS; }
	int SetJoinSpecCheck( unsigned int vLevelMin, unsigned int vLevelMax, int vKey )
	{
		JoinSpecCheck tCheck;

		tCheck.mLevelMax = vLevelMax;
		tCheck.mLevelMin = vLevelMin;
		tCheck.mKey = vKey;

		mCheckList.push_back( tCheck );

		return SUCCESS;	
	}

	int SetSpecialItem( int vItemID, int vFlag )
	{
		for( unsigned int i = 0; i < ARRAY_CNT( mSpecialItem ); i++ )
		{
			if( mSpecialItem[ i ].mItemID == 0 || mSpecialItem[ i ].mItemID == vItemID )
			{
				mSpecialItem[ i ].mItemID = vItemID;
				mSpecialItem[ i ].mFlag = vFlag;
				break;
			}
		}
		return SUCCESS;
	}

	const SpecialItem* GetSpecialItem( int vFlag, unsigned int* vIndex )
	{
		for( unsigned int i = *vIndex; i < ARRAY_CNT( mSpecialItem ); i++ )
		{
			if( CHECK_FLAG( mSpecialItem[ i ].mFlag, vFlag ) == true )
			{
				*vIndex = i;
				return &mSpecialItem[ i ];
			}
		}
		
		return NULL;	
	}

	bool IsSpecialCheck( CEntityPlayer* vpPlayer, REPE_JOIN_SPCE_TYPE tCheckKey )
	{
		REPE_ASSERT( vpPlayer != NULL, return true );

		JOIN_SPEC_CHECK_LIST::iterator it;
		for( it = mCheckList.begin( ); it != mCheckList.end( ); it++ )
		{
			JoinSpecCheck tCheck = *it;	
			if( vpPlayer->GetLevel( ) >= tCheck.mLevelMin && vpPlayer->GetLevel( ) < tCheck.mLevelMax )
			{
				if( ( tCheck.mKey & tCheckKey ) != 0 )
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}	

		return true;	
	}

    inline int GetPlayerCountMax( ){ return mPlayerCountMax; }
	inline int ClearDateSpace( ) { mDateSpace.initailize( ); return SUCCESS; }
	inline int ClearSignUp( ) { mSignUpList.initailize( ); return SUCCESS; }
	inline int ClearBattleOpenSpace( ) { mBattleOpenSpace.initailize( ); return SUCCESS; }
    inline  int GetMapID( int vMapIDListIndex ) 
	{
		REPE_ASSERT_STR( vMapIDListIndex >= 0, return INVALID_MAP_ID, "vMapIDListID %d", vMapIDListIndex );
		REPE_ASSERT_STR( vMapIDListIndex < ( int )ARRAY_CNT( mMapIDList ), return INVALID_MAP_ID, "vMapIDListID %d,"
			" ARRAY_CNT( mMapIDList ) %d", vMapIDListIndex, ARRAY_CNT( mMapIDList ) );
		return mMapIDList[ vMapIDListIndex ]; 
	}
	inline int GetBeginMapID( ) { return GetMapID( 0 ); }
    inline  int SetPlayerCountMax( unsigned int vPlayerCountMax ){ mPlayerCountMax = vPlayerCountMax; return 0; }
    int SetMapID( int vMapID ) 
	{ 
		unsigned int i = 0;
		for( i = 0; i < ARRAY_CNT( mMapIDList ); i++ )
		{
			if( mMapIDList[ i ] == INVALID_MAP_ID )
			{
				mMapIDList[ i ] = vMapID;
				return SUCCESS;
			}
			else if( mMapIDList[ i ] == vMapID )
			{
				LOG_ERROR( REPETION_LOG, "[ %s : %d ][ %s ] MapID %d Is Registe In RepetionIndex %d", __LK_FILE__,
					__LINE__, __FUNCTION__, vMapID, GetRepetionIndex( ) );
				return ERR_EXIST;
			}
		}

		return ERR_FULL;
	}
	inline REPE_LEVEL GetTeamLevelFlag( ) { return mTeamLevelFlag; }
	inline int SetTeamLevelFlag( REPE_LEVEL vLevelFlag ) { mTeamLevelFlag = vLevelFlag; return SUCCESS; }
	int GetMapSizeMax( ) { return ( int )ARRAY_CNT( mMapIDList ); };
//	inline  bool IsRepetionMap( ) { return mMapID != INVALID_MAP_ID; }
	bool MapIsInRepetion( int vMapID )
	{
        unsigned int i = 0;
        for( i = 0; i < ARRAY_CNT( mMapIDList ); i++ )
        {
            if( mMapIDList[ i ] == vMapID )
            {
				return true;
            }
        }

        return false;		
	}

	inline  unsigned short GetTaskID( ) { return mTaskID; }
	inline  int SetTaskID( unsigned short vTaskID ) { mTaskID = vTaskID; return SUCCESS; }
	inline  int SetPos( unsigned short vPosX, unsigned short vPosY ) { mPosX = vPosX; mPosY = vPosY; return SUCCESS; };
	inline  unsigned int GetPosX( ) { return mPosX; }
	inline unsigned int GetPosY( ) { return mPosY; }
	inline int SetTeamIn( ) { mTeam = true; return SUCCESS; }
	inline bool IsTeamIn( ) { return mTeam; }
	inline int SetPlayerPerNumber( unsigned short vPlayerPerNumber ) { mPlayerPerNumber = vPlayerPerNumber; return SUCCESS; }
	inline int  SetPlayerWeekPerNumber( unsigned short vPlayerWeekPerNumber )
	{
		mPlayerWeekPerNumber = vPlayerWeekPerNumber;
		return SUCCESS;
	}
	inline int SetPlayerCount( unsigned short vCount ) { mPlayerCount = vCount; return SUCCESS; }
	inline int SetMinLevel( unsigned short vMinLevel ) { mMinLevel = vMinLevel; return SUCCESS; }
	inline int SetMaxLevel( unsigned short vMaxLevel ) { mMaxLevel = vMaxLevel; return SUCCESS; }
	inline int GetMinTimer( ) { return mMinTimer; }
	inline int SetMinTimer( int vTimer )
	{
		if( vTimer > mMinTimer )
		{
			mMinTimer = vTimer;
		}
		return mMinTimer;
	}
	inline int RegisteEvent( RepetionEvent vEventType ) 
	{ 
		REPE_ASSERT( ( unsigned int )vEventType <= ARRAY_CNT( mRepetionEvent ), return ERR_INVALID_PARAMETER );
		mRepetionEvent[ vEventType ] = true;
		return SUCCESS;
	}

	inline bool GetEvent( RepetionEvent vEventType )
	{
		REPE_ASSERT( ( unsigned int )vEventType <= ARRAY_CNT( mRepetionEvent ), return false );
		return mRepetionEvent[ vEventType ];
	}

	const BattleCamp* GetBattleCamp( unsigned int vCampID )
	{
		if( vCampID <= sizeof( mCamp ) / sizeof( mCamp[ 0 ] )/* && vCampID != 0*/ )
		{
			return &mCamp[ vCampID ];
		}

		return NULL;
	}

	int SetWaitListLevel( unsigned int vLevelMin, unsigned int vLevelMax );
	WaitList* GetWaitListLevel( unsigned int vIndex )
	{
		if( vIndex >= sizeof( mWaitLevel ) / sizeof( mWaitLevel[ 0 ] ) )
		{
			return NULL;
		}

		if( mWaitLevel[ vIndex ].mLevelMin == 0 )
		{
			return NULL;
		}

		return &mWaitLevel[ vIndex ];
	}	

	int SetBattleCamp( lua_tinker::table vTable );

	int SetTimeEvent(	unsigned int vIndex, 
						RTIME_TYPE vType, 
						RTIME_RESULT vResult, 
						unsigned int vTime, 
						int vLoopCount,  
						bool vIsCallFunc,
						lua_tinker::table vSync
					);

	const RTimeEvent* GetTimeEvent( unsigned int vIndex )
	{
		REPE_ASSERT( vIndex < ARRAY_CNT( mTimeEvent ), return NULL );

		return &mTimeEvent[ vIndex ];
	}

	int SetOpenDate( DateSpace* vSpace );
	int SetBattleOpenSpace( DateSpace* vSpace );
	const DateSpace* GetBattleOpenSpace( int vIndex );

	bool IsInOpenTime( );

	inline  int SetBackMapID( unsigned short vMapID ) { mBackMapID = vMapID; return SUCCESS; }
	inline  int SetBackPos( unsigned short vPosX, unsigned short vPosY ) 
		{ mBackPosX = vPosX, mBackPosY = vPosY; return SUCCESS; }
	inline  unsigned short GetBackMapID( ) { return mBackMapID; }
	inline  unsigned short GetBackPosX( ) { return mBackPosX; }
	inline  unsigned short GetBackPosY( ) { return mBackPosY; }
	inline  unsigned short GetPlayerPerNumber( ) { return mPlayerPerNumber; }
	inline	unsigned short GetPlayerWeekPerNumber( ) { return mPlayerWeekPerNumber; }
	inline  unsigned short GetPlayerCount( ) { return mPlayerCount; }
	inline  unsigned short GetMinLevel( ) { return mMinLevel; }
	inline  unsigned short GetMaxLevel( ) { return mMaxLevel; }

	int	SetCommTakeMap( int vMapID )
	{
		unsigned int i = 0;
		for( i = 0; i < sizeof( mCommTakeMap ) / sizeof( mCommTakeMap[ 0 ] ); i++ )
		{
			if( mCommTakeMap[ i ] == INVALID_MAP_ID )
			{
				mCommTakeMap[ i ] = vMapID;
				break;
			}
		}
		return SUCCESS;
	}

	int GetPlayerAllTakeCount( CPropertyPlayer* vpPlayer );
	int GetWeekPlayerAllTakeCount( CPropertyPlayer* vpPro, unsigned int &WeekCount );

	inline bool IsBattle( )
	{
		return ( mWaitLevel[ 0 ].mLevelMin == 0 ) ? false : true;
	}
        int SetSignUpDate( DateSpace* vpSpace );
        bool IsInSignUpTime( );
	

	//  Set & Get QuestionCheck
	void SetQuestionCheck( int nCheck ) { mQuestionCheck = nCheck; }
	int GetQuestionCheck(){ return mQuestionCheck; }
	bool IsInNowSignUpTime( int vTime );
	void SetIsOnTimeOpen( int OnTimeOpen)
	{ 
		if( OnTimeOpen != 0)
		{
			mIsOnTimeOpen = true;
		}
	}
	bool  IsOnTimeOpen(){ return mIsOnTimeOpen; }
	bool IsInNowOpenTime( int vTime );

	void SetNotLimitTime( int vNotlimitTime)
	{
		if( vNotlimitTime != 0)
		{
			mNotLimitTime = true;
		}
	}

	bool NotLimitTime(){ return mNotLimitTime; }

	int SetNecessity( int vNecessityID )
	{

		mNecessity = vNecessityID;
		return mNecessity;
	}

	int  GetNecessity(  )
	{
		
		return mNecessity ;
	}

	
	bool NeedNecessity()
	{
		if(mNecessity != 0)
		{
			return true;
		}
		return false;
	}

	inline int GetSpecialCheck( ){ return mSpecialCheck; }
	inline int SetSpecialCheck( int vCheckFlag ){ return mSpecialCheck = vCheckFlag ;}
	bool NeedSpecialCheck()
	{
		if( mSpecialCheck != 0)
		{
			return true;
		}
		return false;
	}
	inline int GetPlayerDataToClientIndex( ){ return mPlayerDataToClientIndex; }
	inline int SetPlayerDataToClientIndex( int vIndex){ return mPlayerDataToClientIndex = vIndex ;}
	void SetRelogin( int nRelogin ) { mRelogin = nRelogin; }
	int GetRelogin(){ return mRelogin; } 
	void SetCloseTime( int nTime ) { mCloseTime = nTime; }
	int GetCloseTime(){ return mCloseTime; }
	void SetConsumeTimes(int nConsumeTims) { m_nConsumeTimes = nConsumeTims; }
	int GetConsumeTimes(){ return m_nConsumeTimes; }
	int SetDelayTime( int vTime ) {  m_nDelaytime =  vTime > m_nDelaytime ? vTime: m_nDelaytime ;}
	
	int GetDelayTime( ){  return  m_nDelaytime; }
	
};


// Every Repetion Instance
class CRepetion : public CCharacterObserver//public CObj
{
private:
	typedef bool (*Fun_EntityLoop)( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vParame1, int vParame2 );
	#define CREATE_ENTITY_ARRARY_MAX	( 250 )
	struct CreatorEntityID
	{
		unsigned short	mCreateIndex;
		unsigned int	mEntityID;

		CreatorEntityID( )
		{
			if( CObj::msCreateMode )
			{
				mCreateIndex = 0;
				mEntityID = INVALID_OBJ_ID;
			}
		}
	};

	struct RTimeAffair
	{
		RTimeEvent  	mEvent;
		int				mTime;
		bool			mIsBegin;
		unsigned int	mLoopCount;
		int				mTimeID;

		RTimeAffair( )
		{
			if( CObj::msCreateMode )
			{
				mTime = 0;
				mIsBegin = false;
				mLoopCount = 0;
				mTimeID = INVALID_OBJ_ID;
			}
		}
		
		int SetTimer( int vRepetionID, int vIndex, int vTime = 0 )
		{
			int             tOtherInfo[MAX_TIMER_PARA_NUM] = { 0 };
			tOtherInfo[ 0 ] = MESSAGE_REPETION;
			tOtherInfo[ 1 ] = vIndex;
			mTimeID = CTimerMng::GetSingletonPtr( )->SetTimer( vRepetionID, TIMER_REPETION, 
				( vTime == 0 ) ? mEvent.mInitTime : vTime, 2, tOtherInfo, 5 );
			LOG_INFO( REPETION_LOG, "[ %s : %d ][ %s ] Repetion( %d ) SetTime %d", __LK_FILE__, __LINE__, __FUNCTION__,
				vRepetionID, mTimeID );
			return SUCCESS;
		}

		int ClearTimer( )
		{
			if( mTimeID == INVALID_OBJ_ID )
			{
				return SUCCESS;
			}

			LOG_INFO( REPETION_LOG, "[ %s : %d ][ %s ] ClearTime( %d )", __LK_FILE__, __LINE__, __FUNCTION__, mTimeID );
			CTimerMng::GetSingletonPtr( )->ClearTimer( mTimeID, false );
			mTimeID = INVALID_OBJ_ID;
			
			return SUCCESS;
		}

		bool IsActivityTimer( CTimerItem* vpTimer )
		{
			REPE_ASSERT( vpTimer != NULL, return false );
			if( vpTimer->get_id( ) != mTimeID )
			{
				return false;
			}

			return true;
		}
	};

	struct ENTITY_TARGET_POS
	{
		int				mEntityID;
		int				mPosX;
		int				mPosY;

		ENTITY_TARGET_POS( )
		{
			if( CObj::msCreateMode )
			{
				mEntityID = INVALID_OBJ_ID;
				mPosX = 0;
				mPosY = 0;
			}
		}
	};

	struct REPETION_MAPOBJ
	{
		int				mMapID;
		int				mMapObjID;

		REPETION_MAPOBJ( )
		{
			if( CObj::msCreateMode )
            {
				mMapObjID = INVALID_OBJ_ID;
				mMapID = 0;
            }
		}
	};

	typedef lk::vector< ENTITY_TARGET_POS, 100 > MoveEntityList;

private:
	bool			mSysClose;			// �ж��Ƿ���Ҫϵͳǿ�йر�
	RTimeAffair		mTimer[ TIME_COUNT ];
	unsigned int	mTimeCount;
	bool			mEventOpen[ REPETION_EVENT_END ];

	CData			mData[ 25 ];

	int				mBeginTime;
	int				mParame[ 2 ];      //����ɱ�õ������������� 0����͵ȼ���1��ߵȼ�

	MoveEntityList		mList;

	int				mMinTimer;

	REPETION_MAPOBJ	mMapObjIDList[ REPE_MAP_COUNT_MAX ];
	KEY_TYPE		mKey;
	int				mRepetionIndex;
	int				mClearTimeID;

	int				mCreator;
	int				mRemoveItem;
	int				mMinCheckTime;

	int				mPlayerJoinTimes;
	int				mEmptyTime;		// ��������Ϊ0��ʱ��
public:
	CRepetion( )
	{
        if( CObj::msCreateMode )
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}

	virtual int Initialize() 
	{ 
		unsigned int i = 0;

		mTimeCount = 0;
		mMinTimer = 0;
		mRepetionIndex = INVALID_REPETION_INDEX;
		mClearTimeID = INVALID_OBJ_ID;
		mBeginTime = 0;
		mKey = INVITED_KEY_VALUE;

		mList.initailize( );
		
		mCreator = 0;
		mRemoveItem = 0;

		mSysClose = false;

		for( i = 0; i < sizeof( mTimer ) / sizeof( mTimer[ 0 ] ); i++ )
		{
			mTimer[ i ].mTime = 0;
			mTimer[ i ].mIsBegin = false;
			mTimer[ i ].mLoopCount = 0;
			mTimer[ i ].mTimeID = INVALID_OBJ_ID;
		}

		for( i = 0; i < sizeof( mData ) / sizeof( mData[ 0 ] ); i++ )
		{
			mData[ i ].Init( 0 );
		}

		memset( mMapObjIDList, 0, sizeof( mMapObjIDList ) );
		memset( mParame, 0, sizeof( mParame ) );
		mMinCheckTime = 0;
		mPlayerJoinTimes = 0;
		mEmptyTime = 0;
		return 0;
	}

	int SetSysClose( ) { mSysClose = true; return SUCCESS; }
	bool IsSysClose( ) { return mSysClose; }

	int AddPlayerJoinTimes( ) { mPlayerJoinTimes++; return mPlayerJoinTimes; }
	int GetPlayerJoinTimes( ) { return mPlayerJoinTimes; }

	int SetMinCheckTime( int vMinCheckTime ) { mMinCheckTime = vMinCheckTime; return SUCCESS; }
	int GetMinCheckTime( ) { return mMinCheckTime; }
	int SetCreator( int vCreator ) { mCreator = vCreator; return SUCCESS; }
	int GetCreator( ) { return mCreator; }

	int SetRemoveItem( int vRemoveItem ) { mRemoveItem = vRemoveItem; return SUCCESS; }
	int GetRemoveItem( ) { return mRemoveItem; }

	int SetClear( );
	int ClearTimeout( );
	bool IsInClear( ) { return mClearTimeID != INVALID_OBJ_ID; }

	virtual int Resume() {return 0;}

	int SetBeginTime( int tTime ) { mBeginTime = tTime; return mBeginTime; }
	int GetBeginTime( ) { return mBeginTime; }

	int SetKey( KEY_TYPE vKey ) { mKey = vKey; return SUCCESS; }
	KEY_TYPE GetKey( ) { return mKey ; }

	int SetRepetionIndex( int vRepetionIndex ) { mRepetionIndex = vRepetionIndex; return SUCCESS; }
	int GetRepetionIndex( ) { return mRepetionIndex; }

	int RemoveSpecialItem( CEntityPlayer* vpPlayer );


	int SetMapObjID( int vMapID, int vMapObjID )
	{
		REPE_ASSERT_STR( vMapObjID != INVALID_OBJ_ID, return ERR_INVALID_PARAMETER, "vMapObjID %d", vMapObjID );
		REPE_ASSERT_STR( vMapID != INVALID_MAP_ID, return ERR_INVALID_PARAMETER, "vMapID %d", vMapID );

		for( unsigned int i = 0; i < ( int )ARRAY_CNT( mMapObjIDList ); i++ )
		{
			if( mMapObjIDList[ i ].mMapObjID == INVALID_OBJ_ID && mMapObjIDList[ i ].mMapID == INVALID_MAP_ID )
			{
				mMapObjIDList[ i ].mMapObjID = vMapObjID;
				mMapObjIDList[ i ].mMapID = vMapID;
				return SUCCESS;
			}
			
		}

		return ERR_FULL;
	}

	CMapObject* GetMapObject( int vIndex );
	CMapObject* GetMapObjectByMapID( int vMapID );
	CMapObject* GetBeginMapObject( ) { return GetMapObject( 0 ); }
	int GetMapObjSizeMax( ) { return ( int )ARRAY_CNT( mMapObjIDList ); }

	bool IsOverMinTime( ) { return ( mMinTimer == 0 ) ? true : false; }

	inline int PushMoveEntity( int vEntityID, int vPosX, int vPosY ) 
	{
		ENTITY_TARGET_POS tTarget;
			
		tTarget.mEntityID = vEntityID;
		tTarget.mPosX = vPosX;
		tTarget.mPosY = vPosY;

		MoveEntityList::iterator it;
		for( it = mList.begin( ); it != mList.end( ); it++ )
		{
			if( ( *it ).mEntityID == vEntityID )
			{
				mList.erase( it );
				break;
			}
		}

		mList.push_back( tTarget );

		return SUCCESS;			
	} 



//	int SetMapObjID( unsigned int vMapObjID ) { mMapObjID = vMapObjID; return SUCCESS; }
	CRepetionInfo* GetRepetionInfo( );
	CMapObject* GetMapObject( );  //{ return CMapObjManager::GetSingletonPtr( )->GetMapObject( mMapObjID ); }
	KEY_TYPE GetMapKey( );

	void OnTimer( unsigned int vTickCount, std::vector< int >* vpDelete );
	void OnTimeout( CTimerItem* vpTimer );
	void ClearAllTimer( );

	// Load Config 
	int Load( CRepetionInfo* vpRepetionInfo  ); 
	// Every Repetion Data
	int SetData( int vKey, int vData );
	int GetData( int vKey );

	// Time
	int ChangeTimeSpace( unsigned int vTimeIndex, unsigned int vTimeSpace );
	void ChangeTime( unsigned int vTimeIndex, int vTime );
	int GetTime( unsigned int vTimeIndex );
	// Time Begin
	int TimeBegin( RTIME_TYPE vType );
	int TimeBeginByIndex( unsigned int vIndex );
	int TimeRestartByIndex( unsigned int vIndex );
	//Time End
	int TimeEnd( RTIME_TYPE vType );
	int TimeEndByIndex( unsigned int vIndex );
	int TimePauseByIndex( unsigned int vIndex );

	// Call Lua Common Event
//	int DoEvent( CRepetionInfo* vpRepetionInfo, RepetionEvent vEventType, int vParame1 = 0, int vParame2 = 0 );
	int DoEvent( CRepetionInfo* vpRepetionInfo, RepetionEvent vEventType, lua_tinker::table *vParame );
	int EventClose( RepetionEvent vEventType );

	// Call Lua Time Event
	int TimeEvent( unsigned int vTimeIndex ); 
	unsigned int GetLoopCount( unsigned int vTimeIndex );

	// ��õ�ǰ����������
	int GetPlayerCount( );		

	// �Ƿ��������
	bool CanRelogin();
	
	// �Ƿ������������
	bool RepetionRemainAlive();
	
	//
	void SetEmptyTime( int nTime ) { mEmptyTime = nTime; }
	int GetEmptyTime(){ return mEmptyTime; }

//	int InsertEntity( CEntity* tpEntity, CCreator* tpCreator );
	int NpcEntityLoop( unsigned int vTemplateID, Fun_EntityLoop vFun, int vParame1, int vParame2 ); 
	int NpcEntityLoopByMap( unsigned int vTemplateID, Fun_EntityLoop vFun, int vMapID, int vParame1, int vParame2 );
	int PlayerEntityLoop( Fun_EntityLoop vFun, int vParame1, int vParame2 ); 
	int PlayerEntityLoopByMap( Fun_EntityLoop vFun, int vMapID, int vParame1, int vParame2 );
	int PlayerCheckAward( int vWinCamp );

	// NPCʵ��ѭ���� �߼�������lua�м�
	int NpcEntityLoopInLuaByMapID( unsigned int vTempID, int vMapID, lua_tinker::table* vParame );
	// player ѭ���� �߼�������lua�м�
	int PlayerLoopInLua( int vMapID, lua_tinker::table* vParame );
//	int DestroyEntity( CEntity* vpEntity );

	// Repetion Begin & End
	int Begin( );
	int End( );


	// Read And Write Parame1 or Parame2
	int SetParame( unsigned int vIndex, int vParame ) 
	{ 
		REPE_ASSERT_STR( vIndex < ARRAY_CNT( mParame ), return ERR_INVALID_PARAMETER, "Index %d, Max Index %d",
			vIndex, ARRAY_CNT( mParame ) );
		mParame[ vIndex ] = vParame; 
		return SUCCESS; 
	}

	int GetParame( unsigned int vIndex ) 
	{ 
		REPE_ASSERT_STR( vIndex < ARRAY_CNT( mParame ), return ERR_INVALID_PARAMETER, "Index %d, Max Index %d",
			vIndex, ARRAY_CNT( mParame ) );
		return mParame[ vIndex ]; 
	}

	int PlayerJoinRepetion( CEntityPlayer* vpPlayer ,bool vFirst);	
	// ��������뿪����, ����������뿪��رո���
	int AllPlayerLeave( bool vDecCount = false );
	int PlayerJumpTowerFloor( CEntityPlayer* tpPlayer,int tstep,int tfloor);

	// Observer
	virtual int CharacterDeath( CEntityCharacter* vKilled, CEntityCharacter* vKiller );
	virtual int MachinerySpring( CEntityBox* vpMachinery, CEntity* vpSpringed );
	virtual int TimeAssignment( CEntityCharacter* vpCharacter, int vTimerID, int vOtherInfoLength, 
		int* vpOtherInfo );
	virtual int MoveStop( CEntity* tpEntity );

	// Creator Entity Loop Event
	static bool UseSkill( CRepetion* vpRepetion, CEntityCharacter* vpDesEntity, int vSrcEntityID, int vSkillTempID );
	static bool AddEnmity( CRepetion* vpRepetion, CEntityCharacter* vpDesEntity, int vSrcEntityID, int vEnmityValue );
	static bool SetIntData( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vIndex, int vIntData );
	static bool SetIntDataMax( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vIndex, int vIntData );
	static bool AddIntData( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vIndex, int vIntData );
	static bool SetCampID( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vCampID, int vValue );
	static bool PlayerRelive( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vCampID, int vPosPoint );
	static bool PlayerReliveByMapID( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vMapID, int vPosPoint );
	static bool PlayerReliveSys( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vParame1, int vParame2 );
	static bool NoticeEventByCamp( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vCampID, int vMsg );
	static bool AllPlayerRelive( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vParame1, int vParame2 );
	static bool InsertItemByCamp( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vCampID, int vInsertItemPtr );
	static bool InsertItemAll( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vParame1, int vInsertItemPtr );
	static bool InsertMoneyAll( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vMoney, int vBind );
	static bool RemoveBuff( CRepetion* vpRepetion, CEntityCharacter* vpDesEntity, int vBuffTempID, int vParame2 );
	static bool InsertBuff( CRepetion* vpRepetion, CEntityCharacter* vpDesEntity, int vBuffTempID, int vParame2 );
	static bool AllTeleport( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vMapID, int vParame2 );
	static bool AllPlayerInSpecLevel( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vParame1,int vParame2 );
	static bool AddTitle( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vTitleID, int vEntityID );
	static bool GetIntData( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vIndex, int * pIntData );
	static bool RefreshNpcView( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vParame1, int vParame2 );
	static bool LeaveRepetion( CRepetion* vpRepetion, CEntityCharacter* vpDesEntity, int vParame1, int vParame2);
	static bool AddIntDataByCamp( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vCampID, int vParam );
	static bool GetCampPlayerCount( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vCampID, int vParam );
	static bool AwardFameByIndex( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vIndex, int vPercent );
	static bool AwardFameCamp1( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vIndex, int vPercent );
	static bool AwardFameCamp2( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vIndex, int vPercent );
public:
	struct CCampMsgData
	{
	public:
		CMessage *mpMsgParam;
		int *mExceptRoleID;
		int mExceptRoleNum;
	public:
		CCampMsgData()
		{
			mpMsgParam = NULL;
			mExceptRoleNum = 0;
			mExceptRoleID = NULL;
		}
		bool IsExceptRole( int nRoleID )
		{
			for ( int i = 0; i < mExceptRoleNum; ++i )
			{
				if ( nRoleID == mExceptRoleID[i] )
				{
					return true;
				}				
			}	
			return false;
		}
	};
	// ����vParam��CCampMsgData����
	static bool SendMsgByCamp( CRepetion* vpRepetion, CEntityCharacter* vpEntity, int vCampID, int vParam );
};

// ս�����˵�ͶƱ��Ϣ
#define  MAX_VOTE_ROLENUM 30
struct CCampKickVote
{
public:
	struct VoteData
	{
	public:
		int mRoleID;
		int mResult;
	public:
		VoteData()
		{
			mRoleID = 0;
			mResult = 0;
		}
	};
public:
	typedef lk::vector< VoteData, MAX_VOTE_ROLENUM > VotePlayerList;
public:
	int mSponsorRoleID;	// �����˵�ID
	int mKickedRoleID;	// �����˵�ID	
	int mCampRoleNum;	// ����ʱ������Ӫ������	
	int mCampID;		// ��ӪID	
	VotePlayerList mVotePlayerList;
public:
	CCampKickVote()
	{
		mSponsorRoleID = 0;
		mKickedRoleID = 0;
		mVotePlayerList.initailize();
		mCampRoleNum = 0;
		mCampID = 0;		
	}
public:
	bool CheckVoteValid( int nRoleID )
	{
		VotePlayerList::iterator it = mVotePlayerList.begin();
		for ( ; it != mVotePlayerList.end(); ++it )
		{
			if ( it->mRoleID == nRoleID )
			{
				return false;
			}			
		}		
		return true;
	}
	int InsertRoleVoteResult( int nRoleID, int nResult )
	{
		VoteData tData;
		tData.mRoleID = nRoleID;
		tData.mResult = nResult;
		mVotePlayerList.push_back( tData );
		return SUCCESS;
	}

	// ��ȡͬ�����˵�����
	int GetAgreeNum()	
	{
		int tNum = 0;
		VotePlayerList::iterator it = mVotePlayerList.begin();
		for ( ; it != mVotePlayerList.end(); ++it )
		{
			if ( it->mResult == 1 )
			{
				++tNum;
			}			
		}
		return tNum;
	}
	// ��ȡͶƱ������
	int GetVotedNum()
	{
		return mVotePlayerList.size();
	}
};

#define MAX_REPETION_CAMPKICKVOTE_NUM 300

// ********************************************************************** //
// CRepetionModule
// ********************************************************************** //
class CRepetionModule : public CLogicModule, public CSingleton< CRepetionModule >
{
private:
	struct WaitRedirectRepetion
	{
		unsigned short mMapID;
	};

public:
	static char	sModuleName[ NAME_LENGTH ];
	
public:
	CRepetionModule( ) : CLogicModule( sModuleName ), mLua( NULL ), mRepetionTime( CWTimer( 500 ) )	
	{		
		if ( CObj::msCreateMode )
		{
			mCampKickVoteList.initailize();
		}
		m_bReloadFlag = false;
	}	

	static unsigned int CountSize( );
public:
	CRepetionInfo       mRepetionInfo[ MAP_INDEX_MAX ];
	lua_State* 			mLua;
	CWTimer				mRepetionTime;
	bool				m_bReloadFlag; // ���¼��صı�־

private:
	bool NotInWaitRedirMap( CEntityPlayer* vpPlayer );

public:
	CRepetionInfo* GetRepetionInfoByMapID( int vMapID, int vIndex = 0 );
	CRepetionInfo* GetRepetionInfo( int vRepetionIndex );

	int RedirectRepetionMap(	CEntityPlayer* vpPlayer, 
								unsigned short vMapID, 
								unsigned short vPosX = 0, 
								unsigned short vPosY = 0, 
								CEntityNpc* vpNpc = NULL,
								int vCheckFlag = CHECK_ALL_FLAG,
								int vRemoveItem = 0,
								bool vCheckedNecessity = false
							);
	int RegisterLua( const char* vpLuaDir );
	int DestroyRepetion( CRepetion* vpRepetion );
	int OnDestroyEntity( CEntity* vpEntity );

	// �ṩ��GMʹ��
	int PlayerSingleIntoRepe( CEntityPlayer* vpPlayer, int vRepeIndex, int vPosX, int vPosY );
	int PlayerJumpTower( CEntityPlayer* tpPlayer,int vstep,int vfloor);
	

	int SendErrCode(	CEntityPlayer* vpPlayer, 
						int vRepetionErr, 
						unsigned short vMapID, 
						int vParame1 = 0, 
						int vParame2 = 0 
					);
	int SendErrCode( 	int* vpPlayerListID, 
						int vPlayerCount, 
						int vErrCode, 
						int vPlayerCharID,
						unsigned short vMapID, 
						int vParame1 = 0, 
						int vParame2 = 0
					);
	int SendTeamErrCode(	CEntityPlayer* vpPlayer, 
							ERepetion vRepetionErr, 
							unsigned short vMapID,
							int vParame1 = 0, 
							int vParame2 = 0 
						); 
	int EndTask( CEntityPlayer* vpPlayer, unsigned int vTaskID, bool vIsComplate );
	CRepetion* GetRepetion( CEntityCharacter* vpPlayer );
	int PlayerIntoRepetionCheck( CEntityPlayer* vpPlayer, CRepetionInfo* vpInfo, int vCheckFlag );
	bool IntoRepetionTimeCheck( CRepetionInfo* vpInfo );
	CPlayerRepetion* GetPlayerRepetion( CEntityPlayer* vpPlayer )
	{
		REPE_ASSERT( vpPlayer != NULL, return NULL );
		return  ( ( CPropertyPlayer* )vpPlayer->GetProperty( ) )->GetRepetion( );
	}
	int CleanRepetion( CPropertyPlayer* vpPlayer );
	bool RedirectRepetionCheck(	CEntityPlayer* vpPlayer, int* vpPlayerListID, int vPlayerCount, CRepetionInfo* vpInfo, 
		CEntityNpc* vpNpc = NULL, int tCheckFlag = CHECK_ALL_FLAG, const SpecialItem** vpSpecialItem = NULL ,int flag = 0,
		int *vNeedItem = NULL ,bool *vIsCheckedNecessity = false );
	int PlayerIntoRepetion( CEntityPlayer* vpPlayer, int vMapID, int vPosX, int vPosY, KEY_TYPE vKey = 0, bool bIntoLastRepetion = false );

	// Create Battle
	int CreateBattle( int vBattleID, int vLevel );
	int PlayerIntoBattleByKey(
		CEntityPlayer* tpPlayer, 
		int vBattleID, 
		int vCampID,
		KEY_TYPE vKey,  
		CEntityNpc* vpNpc = NULL);

	// С�ӽ���ս���ȴ�����
	int TeamWaitBattle( CEntityPlayer* tpPlayer, int vBattleID, CEntityNpc* vpNpc = NULL );
	
	// �Ƿ�Ϊս����ͼ
	bool IsBattleMap( int vMapID );
	bool IsRepetionMap( int vMapID );

	int RelivePlayer( CEntityPlayer* vpPlayer, CRepetion* vpRepetion, int vPosX, int vPosY, int vMapID = 0 );

	// �õ�lua������ڴ�ʹ��kb
	int GetLuaVMUsedMem( ) { return lua_getgccount( mLua );}

	// ��������( ������������ȫ����ͼ )
	CRepetion* CreateRepetion( int vRepetionIndex, int vLineID, KEY_TYPE vKey, int vCreator, int vRemoveItem, int vParam1 = 0, int vParma2 = 0 );

	// 
	int GetJoinRepetionCountMax( int vMapID );

	int GetPlayerJoinRepetionCount( int vMapID, CEntityPlayer* vpPlayer );
	int GetPlayerJoinRepetionTakeCount( int vMapID, CEntityPlayer* vpPlayer );

	bool IsUnRelive( int vMapID );			// �ж��Ƿ��ܹ���ͨ����

	int EachOther( CEntityPlayer* vpPlayer, int vKey, int vParame1 = 0, int vParame2 = 0 );

	// ����Ƿ��ܹ����븱��
	// ����SUCCESS�ǿ��Խ���
	int PlayerCanIntoRepetion( CEntityPlayer* vpPlayer, int vRepetionIndex );

	int NotifyRepetionIndex( CEntityPlayer* vpPlayer, int vRepetionIndex );

	const SpecialItem*  GetSpecialUnCheck( CEntityPlayer* vpPlayer, CRepetionInfo* vpInfo, int vCheckFlag, 
		int vUnCheckFlag );

	// ���ָ����������һ��
	int DelteRepetionCount( CEntityPlayer* pPlayer, int nRepetionIdx );

	int OnMessageNpcFunc( CEntityPlayer* pPlayer, CMessage* vpMsg );

	// �����ҵ�ǰ��������
	int GetPlayerRepeFloorNo( CEntityPlayer* pPlayer );

	// С�ӽ��붨ʱ���������ȴ�����
	int TeamFixWaitBattle( CEntityPlayer* tpPlayer, int vBattleID, CEntityNpc* vpNpc = NULL );
	// ���˽��붨ʱ���������ȴ�����
	int SingleFixWaitBattle( CEntityPlayer* tpPlayer, int vBattleID, CEntityNpc* vpNpc = NULL );
        // ����ʱ����
        bool SignUpRepetionTimeCheck( CRepetionInfo* vInfo );
        int  PlayerIntoRepetionRandomPlace( CEntityPlayer* vpPlayer, CRepetionInfo *vpInfo, int vKey = 0 );
	// ����ڸ������Ƿ񿪱��䱻����
	bool PlayerOpenBoxLimited(  CEntityPlayer *pPlayer);
public:
	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickSekt );

	// ��������
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName );
	// ·����Ϣ
	virtual void OnRouterMessage( CMessage* pMessage );

	// �ͻ��˷�����Ϣ
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst );

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );

	// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );

	// ��������
	virtual void OnLoadConfig( );

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }

	virtual void OnTimeoutMessage( CMessage* vMsg );

	virtual void OnPlayerLeave( CEntityPlayer* pPlayer, int nState );

	int PlayerLeaveRepetion( CEntityPlayer* vpPlayer, bool vCanBack = true, bool vDecCount = false );
public:
	// static fun member
	static CRepetion* GetRepetion( unsigned int vObjID );
	static CRepetion* GetRepetion( CEntity* vpEntity );

public:
	//lua Interface

	static void Debug( const char* vpStr );
	static void Error( const char* vpStr );
	static void Infor( const char* vpStr );
	static void Notice( const char* vpStr );
	static void RegisterRepetion( lua_tinker::table vTable/*CRepetionInfo* vpRepetion*/ );
	static void RegisteOpenTime( int vRepetionID, lua_tinker::table vTable );
	static void RegisteBattleOpenSpace( unsigned int vRepetionIndex, lua_tinker::table vTable );
	static void RegisteEvent( int vRepetionID, RepetionEvent vEventType );

	static void RegisteTimeEvent(	int vRepetionIndex,
									unsigned int vTimeIndex,
									lua_tinker::table vTimeInfo,
									bool vIsCallFunc
								);
	static void RegisterCommTakeMap( int vRepetion, int vCommMapID );

	static void RepetionClose( unsigned int vRepetionID );

	// ע��ս����Ӫ��Ϣ( ����PVP��������Ч )
	static void RegisterBattleCamp( int vRepetionIndex,	lua_tinker::table vTable );
	static void RegisterBattleWaitLevel( int vRepetionIndex, lua_tinker::table vTable );

	//Create Npc From Lua
	static void CreateNpc( 	unsigned int vRepetionID, unsigned int vCreatorIndex );
	static void CreateNpcByBite( unsigned int vRepetionID, int vBite, lua_tinker::table vList );
	static void CreateNpcRealMap( unsigned int vRepetionID, int vRealMapID, int vCreatorIndex );

	static void UseSkill2Template(	unsigned int vRepetionID, 
									unsigned int vSrcEntityID, 
									unsigned int vDesTemplateID, 
									unsigned int vSkillTempID 
								);

	static void UseSkill( unsigned int vSrcEntityID, unsigned int vDesEntityID, unsigned int vSkillTempID );

	static void AddEnmity2Template(	unsigned int vRepetionID, 
									unsigned int vSrcEntityID, 
									unsigned int vDesTemplateID, 
									unsigned int vEnmityValue 
								);
	static void TimeBegin( unsigned int vRepetionID, unsigned int vTimeIndex );
	static void TimeRestart( unsigned int vRepetionID, unsigned int vTimeIndex );
	static void ChangeTimeSpace( unsigned int vRepetionID, unsigned int vTimeIndex, unsigned int vTimeSpace );
	static void EventClose( unsigned int vRepetionID, RepetionEvent vEventType );
	static void TimeEnd( unsigned int vRepetionID, unsigned int vTimeIndex );
	static void TimePause( unsigned int vRepetionID, unsigned int vTimeIndex );
	static void ObserverEntityDeath( unsigned int vRepetionID, unsigned int vEntityID );
	static void ObserverMachinery( unsigned int vRepetionID, unsigned int vEntityID );
	static void ObserverAssignment( unsigned int vRepetionID, unsigned int vEntityID );
	static int SetAssignment( unsigned int vRepetionID, unsigned int vEntityID, int vTime, 
		lua_tinker::table vTable );
	static void ClearAssignment( unsigned int vRepetionID, unsigned int vEntityID, int vTimeID );
	static void ClearAssignmentAll( unsigned int vRepetionID, unsigned int vEntityID, lua_tinker::table vTable );
	static int DestroyAliveTempOgre( unsigned int vRepetionID, unsigned int vTempID, unsigned int tCount );
	static void EventNoticeAll( unsigned int vRepetionID, REPETION_EVENT_NOTICE vEvent, int vParame1, int vParame2 );
	static void EventNoticeByCamp( unsigned int vRepetionID, int vCampID, REPETION_EVENT_NOTICE vEvent, int vParame1, 
		int vParame2, const char *pParam3 = NULL, int vParame4 = 0 );
	void SendBattleMsgByCamp( int nRepetionID, int nCampID, CMessage *pMsg );
	static void EventNoticeSingle(	unsigned int vRepetionID, 
									unsigned int vEntityID, 
									REPETION_EVENT_NOTICE vEvent,
									int vParame1, 
									int vParame2 
								);	
	static void SetIntData(	unsigned int vRepetionID, int vKey, int vData );
	static int  GetIntData( unsigned int vRepetionID, int vKey );
	static void CharacterDie( unsigned int vRepetionID, unsigned int vEntityID, unsigned int vIsAward );
	static void ChangePKType( unsigned int vEntityID, unsigned int vPKType );
	static void AllPlayerAddEnmitiy( unsigned int vRepetionID, unsigned int vEntityID, int vEnmityValue );
	static void ClearEnmity( unsigned int vEntityID );
	static void AddEnmity( unsigned int vSrcEntity, unsigned int vDesEntity, int vEnmityValue );

	//����Ogre����ּ�ʱ��
	static void SetAliveRefresh( unsigned int vRepetionID, unsigned int vEntityID, int vTime, int vIndex );

	//�������
	static void CreateHierogram( unsigned int vRepetionID, unsigned int vTempID, int vPosX, int vPosY );
	static void CreateHierogramByMap( unsigned int vRepetionID, int vMapID, unsigned vTempID, int vPosX, int vPosY );

	//����
	static void Teleport( unsigned int vRepetionID, unsigned int vEntityID, int vPosX, int vPosY );
	static void AllTeleport( unsigned int vRepetionID, int vMapID, int vPosX, int vPosY, int vUnTeleMapID );
	static void TeleportByMap( unsigned int vRepetionID, unsigned int vEntityID, int vMapID, int vPosX, int vPosY );

	// use skill to all player
	static void UseSkill2AllPlayer( unsigned int vRepetionID, unsigned int vSrcEntityID, unsigned int vSkillTempID );

	// set all player repetion data
	static void SetIntData2AllPlayer( unsigned int vRepetionID, unsigned int vIndex, int vIntData );
//	static int GetPlayerIntDataByRepetion( unsigned int vRepetion, unsigned int entityid, unsigned int vIndex );
	static void SetIntData2AllPlayerMax( unsigned int vRepetionID, unsigned int vIndex, int vIntData );

	// all player repetion data add
	static void AddIntData2AllPlayer( unsigned int vRepetionID, unsigned int vIndex, int vIntData );

	// �õ������ȼ�
	static int GetRepeLevel( unsigned int vRepetionID );

	// �õ���ʼʱ��
	static int GetBeginTime( unsigned int vRepetionID );

	// Npc�ƶ�
	static void NpcMove( int vRepetionID, int vEntityID, int vPosX, int vPosY );

	// npc follow
	static void NpcFollow( int vRepetionID, int vEntityID, int vFollowedID, int vOffsetX, int vOffsetY );

	// �õ�ʵ����Χ��ͬ��Ӫʵ�����	
	static lua_tinker::table GetCampCountEncircleEntity( 
		int vRepetionID, 
		int vEntityID, 
		int vDistance, 
		EEntityType vCampEntityType ); 

	// �õ�ʵ������
	static lua_tinker::table GetPos( int vRepetionID, int vEntityID );

	// NpcѲ��·��
	static void NpcPatrol( int vRepetionID, int vEntityID, int vStart, lua_tinker::table vRoute );

	// ����Character CampID
	static void SetCampID( int vRepetionID, int vEntityID, int vCampID );
	static int GetCampID( int vRepetionID, int vEntityID );

	// ����ͬһ����ʵ���CampID
	static void ChangeCampIDByTempID( int vRepetionID, int vDesTemplateID, int vCampID );

	// ˢ��NPC��NPC�ɼ���
	static void NpcRefreshView( int vRepetionID, int vTempID, int vMapID );

	// ����vCampID��player
	static void PlayerRelive( int vRepetionID, int vCampID, int vPosX, int vPosY );
	static void PlayerReliveByMapID( int vRepetionID, int vMapID, int vPosX, int vPosY );
	static void PlayerReliveSys( int vRepetionID );

	static void ChangeTime( int vRepetionID, unsigned int vIndex, int vTime );
	static int GetTime( int vRepetionID, unsigned int vIndex );

    // ����CFamilyModule::SendBattleEndNotify
    static void SendBattleEndNotifyByFamily( int vRepetionID, int vWinSide );

	// �����赲����, EntityĿǰ����ΪBLOCK( 2009��9��31�� )
	static void ChangeMode( int vRepetionID, int vEntityID );

	static void ChangeCampFlagByCorps( int vRepetionID, int vEntityID, int vCampID, int bAll = 0 );
	static void BattleResultNoticeByCorps( int vRepetionID, int vWinCamp );
	static void SendBattleMapNoticeByCorps( int vRepetionID, int vEntityID );

	static int GetParame( int vRepetionID, int vIndex );
	// �����������Ʒ
	static void InsertItem( int vRepetionID, int vEntityID, int vItemID, int vCount, lua_tinker::table vParame ); 
	// ����ӪvCampID�������������Ʒ
	static void InsertItemByCamp( int vRepetionID, int vCampID, int vItemID, int vCount, lua_tinker::table vParame );
	// �������������Ʒ
	static void InsertItemAll( int vRepetionID, int vItemID, int vCount, lua_tinker::table vParame );

	// ��ý�Ǯ
	static void InsertMoneyAll( int vRepetionID, int vMoney, int vBind );

	// ɾ��NPC BUFF
	static void NpcRemoveBuff( int vRepetionID, int vDesTemplateID, int vBuffTempID );
	static void NpcRemoveBuffByMapID( int vRepetionID, int vDesTemplateID, int vBuffTempID, int vMapID );

	static void NpcInsertBuffByMapID( int vRepetionID, int vDesTemplateID, int vBuffTempID, int vMapID );

	// ɾ����� BUFF
	static void PlayerRemoveBuffByMapID( int vRepetionID,  int vBuffTempID, int vMapID );
	
	// ���BUFF
	static void PlayerInsertBuffByMapID( int vRepetionID,  int vBuffTempID, int vMapID );
	
	// �ж�ʵ���Ƿ���buff
	static bool CharacterHasBuf( int vRepetionID, int vEntityID, int vBuffID );

	//�õ���ͼ�ϵ�����
	static int GetPlayerNumByMapID(int vRepetionID, int vMapID );
	
	// �����ڵ�
	static void CreateRedstone( int vRepetionID, int vStoneTempID, int vFamilyID, lua_tinker::table vMapInfo );

	// ��ø���KEY
	static KEY_TYPE GetRepetionKey( int vRepetionID );

	// ���帱�����֪ͨ
	static void FamilyRepetionInfoEnd( int vRepetionID, int vFamilyID, lua_tinker::table vTable );

	// ��÷��ص�ͼID
	static int GetBackMapID( int vRepetionID, int vEntityID );

	static int SetVirtualMap( int vRepetionID, int vRealMapID, int  vVirtualMapID );

	// ���õ�ͼdata
	static int SetMapIntData( int vRepetionID, int vRealMapID, int vKey, int vData );
	static int GetMapIntData( int vRepetionID, int vRealMapID, int vKey );

	// ����NPCת����ȼ���ʵ�ʵȼ�
	static int NpcChangeLevel( int vRepetionID, int vEntityID, int vChangeLevel, int vLevel );

	// ʵ����BUFF
	static int EntityInsertBuff( int vRepetionID, int vEntityID, int vBuffID );
	// ʵ��ɾ��BUFF 
	static int EntityRemoveBuff( int vRepetionID, int vEntityID, int vBuffID );

	// ɾ���������Ǵ�
	static void SetTodayTimesByGroupID( int vRepetionID, int vEntityID, int vTaskGroupID, int vCount );

	//�������ڸ�����������
	static int GetPlayerDieCountInRepetion( unsigned int vRepetionIndex, unsigned int  vEntityID );
	// 
	static int GetMapID( int vRepetionID, int vEntityID );
	static int GetMapObjectID( int vRepetionID, int vEntityID );


	// ȫ��ս������֪ͨ
	static void EndGlobalWar( int vRepetionID, lua_tinker::table vTable );
public:
	void CheckRepetionQuestionVerify( CRepetionInfo *pRepetion, CEntityPlayer *pPlayer );
	
	void RepetionQuestionVerifyResult( CEntityPlayer *pPlayer, int tCheckResult, int nReason );
        //ע�ᱨ��ʱ��
	static void RegisteSignUpTime( int vRepetionIndex, lua_tinker::table vTable );
	     //����뿪����
	static void PlayerLeave( unsigned int vRepetionID, unsigned int vEntityID );
	static void KickPlayerFromTeam( unsigned int vEntityID);
	static void AttachPlayerState(unsigned int vEntityID, EState vState, int vParames1, int vParames2, int vIndex );
//	static void DetachPlayerState(unsigned int vEntityID, EState vState, int vParames1, int vParames2, int vIndex );
	static void SetIntData2Player( unsigned int vRepetionID,unsigned int vEntityID,  unsigned int vIndex, int vIntData );
	static void AddIntData2Player( unsigned int vRepetionID,unsigned int vEntityID,  unsigned int vIndex, int vIntData );
	static int GetIntData2Player( unsigned int vRepetionID,unsigned int vEntityID,  unsigned int vIndex);
	static void EventNoticeAllInPlayerData(	unsigned int vRepetionID, REPETION_EVENT_NOTICE vEvent, int vParame1, int vIndex );
	static void ObtainRepetionExp(unsigned int vRepetionID, unsigned int vEntityID, unsigned int vExp );
	static void CreateNeedfire( unsigned int vRepetionID, unsigned int vTempID, int vPosX, int vPosY , int vMapID);
	static void SendEventNotify( int vEventID, int vCountryID, lua_tinker::table vTableInt, lua_tinker::table vTableString );
	static void PlayerCreateNpcDynamic(  unsigned int vEntityID , unsigned int vTempID,unsigned int vEntityType , int vPosX,int vPosY );
	static void PlayerReliveBySys( unsigned int vRepetionID, unsigned int vEntityID ,int vHPPer, int vMPPer );
	static void DealBattleWinner( unsigned int vRepetionID,unsigned int vHasWinner, unsigned int vLevel ,unsigned int vEntityID);
	static void SendSysMailForRepetion( unsigned int vRepetionID, lua_tinker::table param );
	static lua_tinker::table GetRepetionPlayerID(  unsigned int vRepetionID );
	static int  SendMessageInLua( int vMessageID,lua_tinker::table vMessage );
	static void AddIntDataByCampID( unsigned int vRepetionID,unsigned int vCampID,  unsigned int vIndex, int vIntData );
	// ��óƺ�
	static int AddTitleAll( int vRepetionID, int vTitleID, int vEntityID );

	// ����������Ϣ
	static int SendEventNotice( int vRepetionID, int vEventID, lua_tinker::table vParame );

	// ͨ��ID �������
	static const char* GetNameByCharID( int vRepetionID, int vCharID );

	// ��������	
	static void AwardFameAll( int vRepetionID, int vIndex, int vPercent );
	static void AwardFameAllCamp1( int vRepetionID, int vIndex, int vPercent );
	static void AwardFameAllCamp2( int vRepetionID, int vIndex, int vPercent );
	static void AwardFameSingle( int vRepetionID, int vEntityID, int vIndex, int vPercent );
	static void CheckAward( int vRepetionID, int vWinCamp );

	// ����lua����
	static int CallFun( int vRepetion, lua_tinker::table vParame );

	//
	static void NpcLoop4TempInLuaByMapID( int vRepetion, int vTempID, int vMapID, lua_tinker::table vParame );

	//
	static void PlayerLoopInLuaByMapID( int vRepetionID, int vMapID, lua_tinker::table vTable );

	static void PlayerLeaveByMapID( int vRepetionID, int vMapID );
    
	static int GetEntityLevel( unsigned int vEntity );
	static bool NeedNecessityCheck( CRepetionInfo *vInfo);
	static bool NeedSpeciaCheck( CRepetionInfo * vInfo );
	static long GetTemplateLevelExp(unsigned int vRepetionID, unsigned int vEntityID, unsigned int vTemplateID );
	static short GetTowerLevel(short vlevel);
	static void CreateNpcDynamic( unsigned int vRepetionID, int vMapID, int  vTempID, lua_tinker::table vParame );
	static void RepeLogScore( unsigned int vRepetionID, unsigned int vEntityID, int vCurrentScore, int vDeltaScore, int vScoreType );

public:
	void OnMessageGetRandomTeleCharge( CEntityPlayer *pPlayer,CMessage * pMessage );
	void OnMessageRandomTele( CEntityPlayer *pPlayer,CMessage * pMessage );
	void OnMessagePlayerApplyWar( CEntityPlayer *pPlayer,CMessage * pMessage );
	void SendResponsePlayerApplyWar( CEntityPlayer *pPlayer, int nErrcode, CGlobalWarInfo &rGlobalWarInfo, int nMinLevel,int nMaxLevel );	
	void OnMessagePlayerEnterGlobalWar( CEntityPlayer *pPlayer,CMessage * pMessage );
	void SendResponsePlayerEnterGlobalWar( CEntityPlayer *pPlayer, int nErrcode );	
	void SendNotifyCanEnterGlobalWar( CEntityPlayer *pPlayer, int nRepetionIndex );	
	void OnMessagePlayerLeaveGlobalWarRequest( CEntityPlayer *pPlayer,CMessage * pMessage );
	void SendResponsePlayerLeaveGlobalWar( CEntityPlayer *pPlayer, int nErrcode );
	void OnMessageKickCampPlayerRequest( CEntityPlayer *pPlayer,CMessage * pMessage );
	void SendResponseKickCampPlayer( CEntityPlayer *pPlayer, int nErrcode );
	void SendNotifyKickCampPlayer( CRepetion *tpRepetion, CEntityPlayer *pSponsorPlayer, CEntityPlayer *pKickedPlayer );
	void OnMessageVoteToKickPlayer( CEntityPlayer *pPlayer,CMessage * pMessage );
	void SendResponseVoteToKickPlayer( CEntityPlayer *pPlayer, int nErrcode );
	void SendKickResultNotify( CRepetion *tpRepetion, int nCampID, int nSponsorRoleID, int nKickedRoleID, const char* pKickedRoleName, int nResult );
	void EndVoteToCampKick( int nRepetionID );
	void OnMessageIntoCorpsBossRepetion( CEntityPlayer *pPlayer, CMessage *pMessage );

public:
	typedef lk::hash_map< int, CCampKickVote, MAX_REPETION_CAMPKICKVOTE_NUM > CampKickVoteList;
	CampKickVoteList mCampKickVoteList;
public:
	int InsertCampKickVote( int nRepeitonID, CCampKickVote &rCampKickVote );
	CCampKickVote *GetCampKickVote( int nRepeitonID );
	int DeleteCampKickVote( int nRepetionID );

	// ����lua�ļ��Ļص�����
	static void LoadLuaFileCallback(const char* pcConfigPath);
};

#define CAMP_MAX_COUNT	( 10 )
class CCampCheck
{
private:
	struct CampCount
	{
		int 	mCampFlag;
		int 	mCampCount;

		CampCount( ) : mCampFlag( 0 ) , mCampCount( 0 ){ }
	};
public:
	CampCount	mCount[ CAMP_MAX_COUNT ];
	EEntityType mEntityType;
	int			mDistance;
	CEntity*	mpSearchEntity;
public:
	CCampCheck( CEntity* vpSearchEntity ) 
		: mEntityType( ENTITYTYPE_NONE ), mDistance( 0 ), mpSearchEntity( vpSearchEntity ) { }
	int SetDistance( int vDistance ) { mDistance = vDistance; return SUCCESS; }
	int SetEntityType( EEntityType vType ) { mEntityType = vType; return SUCCESS; }
	bool operator( )( CEntity* pTarget );
	bool AddCampFlag( int vCamp );
	int GetCampCount( int vCamp );
};



