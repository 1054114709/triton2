#pragma once

#include "object.h"
#include "coretype.h"
#include "lk_vector.h"
#include "servertool.h"

class TiXmlElement;
class CSharedMem;


// ********************************************************************** //
// CCreator
// ********************************************************************** //

class CCreator : public CObj
{
protected:
	int	mCreatorType;		// ������NPC����
	unsigned int mIndex;
	bool mShow;
public:
	int				mHasOgre;			// ��¼��ǰ�Ƿ��й�/npc
	int				mActivity;			// ��¼�Ƿ��л
	unsigned short mMapIndex;

public:
	CCreator() 
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
	CCreator( int vType ) : mCreatorType( vType )	{ Initialize(); }
	
	inline void SetIndex( unsigned int vIndex ){ mIndex = vIndex; }
	inline unsigned int GetIndex() {return mIndex;}

	inline void SetShow( unsigned short vShow ){ mShow = vShow; }
	inline unsigned short GetShow() {return mShow;}

	inline int GetAttachedEntityID( ) { return mHasOgre; }
	inline void SetAttachedEntityID( int nID ) { mHasOgre = nID; }

	virtual int GetCreatorType( ) = 0;
	virtual ~CCreator() {}

	virtual int Initialize() {mShow = true; mHasOgre = 0; mActivity = 0; mMapIndex = 0; mIndex = 0; return 0;}

	// �ָ�
	virtual int Resume() { return 0;} 

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock) = 0;
};

// ********************************************************************** //
// COgreCreator
// ********************************************************************** //

struct DeadRefresh
{
	int		mOgreID;			// �����ģ��ID
	short	mOgreRand;			// ��������ĸ���
};

struct OccurRefresh
{
	int		mOldID;				// ���Ĺ���ID
	int		mTime;				// ����ʱ��
	int		mNewID;				// ˢ�µ�
};

struct CommonRefresh
{
	int		mIndex;				// ����������
	short	mOgreRand;			// �����ĸ���
};

struct RefreshDate
{
	int		mYear;
	char	mMonth;
	char	mDate;
	char	mHour;
	char	mMinute;
	char	mWeek;
	char	mDay;


	// ˫�������õĺ������ֶ�������һ��
	time_t  timet()
	{
		struct tm tm;
		tm.tm_sec = 0;
		tm.tm_min = mMinute;
		tm.tm_hour = mHour;
		tm.tm_mday = mDate;
		tm.tm_mon  = mMonth - 1;
		tm.tm_year = mYear - 1900;

		tm.tm_isdst = 0;

		return mktime(&tm);
	}
};

class COgreCreator : public CCreator
{
public:
	short			mRCount1;
	short			mRCount2;
	short			mRCount3;
	short			mRCount4;
	short			mRCount5;
	short			mRefreshRate;		// ����������ˢ�µĸ���
	short			mRCount6;
	short			mPCount;

	// �������¼�����������LineID��MapID
	unsigned short	mLineID;
	unsigned short	mMapID;
	short			mRCount7;		
	short			mRCount8;				
	int				mInit;				// ��ʼ�Ƿ�ˢ��
	DeadRefresh		mRefresh1[ 20 ];	// ����ˢ��
	OccurRefresh	mRefresh2[ 10 ];	// ����ˢ��
	int				mRefresh3[ 25 ];	// ����ˢ��
	int				mRefresh4[ 10 ];	// ����ˢ��
	CommonRefresh	mRefresh5[ 10 ];	// ����ˢ��
	int				mCommonID;			// ��������������ID
	int				mDisappear;			// NPC��ʧʱ��
	EDirType		mDirection;			// ��ʼ����
	int				mRelife;			// NPC����ʱ��
	CWTPoint		mPosition;			// NPC����
	int				mCountNum;			// ɱ������
	int				mCountDelay;		// ɱ����������ʱ
	int				mCurrentCount;		// ��ǰɱ���ļ���
	RefreshDate		mRefreshTime[ 100 ];		// ָ����ˢ��ʱ��
	//int				mHasOgre;			// ��¼��ǰ�Ƿ��й�
	int				mPathListX[ 20 ];
	int				mPathListY[ 20 ];
	int				mInitBuffID;
	int				mTimeBuffID;
	int				mFuncNpc;
//	int				mActivity;


	// ��NPC Creater��
	int				mOwnerCharID; // ������ID
	int				mIsSendNpc;	  // �Ƿ���NPC
	int				mIsShowOwner;  // �Ƿ��ڿͻ�����ʾ����������

	// ������ȴʱ��
	int				mCoolTime;

	int				mMaxEnmity;			// ���������
	int				mRefresh7[ 10 ];	// ��ˢ��
	
	int				mRefresh8[ 10 ];	// ��ˢ��

	int				mNextRefreshTime;

public:
	COgreCreator( ) : CCreator( ENTITYTYPE_OGRE )	{ Initialize();	}
	COgreCreator( int vType ) : CCreator( vType ) { Initialize(); } 
	virtual int Initialize() ;
	int GetCreatorType( ) { return ENTITYTYPE_OGRE; }	

	virtual ~COgreCreator() {}

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock);

	// ������ˢ��ʱ��
	int GetRightTime( struct tm *now );
};

/************************************************************************/
/* CBoxCreator                                                                     */
/************************************************************************/
class CBoxCreator : public COgreCreator
{
public:
	CBoxCreator( ) : COgreCreator( ENTITYTYPE_BOX ) { }
	int GetCreatorType( ) { return ENTITYTYPE_BOX; }

	virtual ~CBoxCreator( ) { }

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock) ;
};

/************************************************************************/
/* CBlockCreator                                                                     */
/************************************************************************/
class CBlockCreator : public COgreCreator
{
public:
	CBlockCreator( ) : COgreCreator( ENTITYTYPE_BLOCK ) { }
	int GetCreatorType( ) { return ENTITYTYPE_BLOCK; }

	virtual ~CBlockCreator( ) { }

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock) ;
};


// ********************************************************************** //
// CNpcCreator
// ********************************************************************** //

class CNpcCreator : public COgreCreator
{
public:
	int				mNpcID;			// NPC��ģ��ID
	EDirType		mDirection;		// ��ʼ����
	CWTPoint		mPosition;		// NPC����
	//int				mInit;

public:
	CNpcCreator( EEntityType enType = ENTITYTYPE_FUNCNPC ) : COgreCreator( enType ) {Initialize();}
	int GetCreatorType( ) { return mCreatorType; }

	virtual ~CNpcCreator() {}

	virtual int Initialize() ;

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock);
};

// ********************************************************************** //
// CDropCreator
// ********************************************************************** //

class CDropCreator : public CCreator
{
public:
	int				mRange;			// ���䷶Χ
	int				mCenterX;		// ��������X
	int				mCenterY;		// ��������Y
	int				mDropType;		// �������ͣ����Թ��������
public:
	CDropCreator( int vCreatorType ) : CCreator( vCreatorType ) {}
	CDropCreator( int vRange, int vCenterX, int vCenterY, int vDropType )
		: CCreator( ENTITYTYPE_ITEM ), mRange( vRange ), mCenterX( vCenterX ), mCenterY( vCenterY ), mDropType( vDropType )
	{
	}
	virtual ~CDropCreator() {}

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock) { return true;}
};

// ********************************************************************** //
// CRedStoneCreator
// ********************************************************************** //

class  CRedstondeCreator : public CDropCreator
{
public:
	int mItemID;
	int	mOwnerCharID[ TEAMNUM ];			// ��Ʒ������,��Ҫһ��Ψһ�ı�ʾ,���Ը���CHARID
	CRedstondeCreator( ) : CDropCreator(  ENTITYTYPE_REDSTONE )	{ }
	
	CRedstondeCreator(  int vItemID,int vRange, int vCenterX, int vCenterY,int *vOwnerCharID, int vDropType = DROP_OBJECTIVE   )
		:CDropCreator( vRange, vCenterX, vCenterY, vDropType ),mItemID( vItemID  )
		{			
			memcpy( mOwnerCharID, vOwnerCharID, sizeof( mOwnerCharID ) );
		}
public:
	virtual int GetCreatorType( ) { return ENTITYTYPE_REDSTONE; }
	int *GetOwnerID( ){  return mOwnerCharID; }
	virtual ~CRedstondeCreator(){}

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock) { return true;}
};



// ********************************************************************** //
// CItemCreator
// ********************************************************************** //

class CItemCreator : public CDropCreator
{
public:
	int				mItemID;					// ���ɵĵ���ID	
	int				mOwnerCharID[ TEAMNUM ];	// ��Ʒ������,��Ҫһ��Ψһ�ı�ʾ,���Ը���CHARID
	void*			mpItem;						// һ��������ߣ������ֵ����0����ôͨ��mItemID����һ���µ���
	int				mListID;					// ������Ʒʱ�ͻ�����ʾ��
	int				mLevel;						// ����װ��ʱ��ѯ�ȼ�
	bool			mProtect;					// �Ƿ���Ҫ����

public:

	CItemCreator() : CDropCreator( ENTITYTYPE_ITEM ) {}

	CItemCreator( int vItemID, int vRange, int vCenterX, int vCenterY, int *vOwnerCharID, void* pItem, int vListID = 0, int vLevel = 0, int vDropType = DROP_OBJECTIVE, bool vProtect = true ) 
		: CDropCreator( vRange, vCenterX, vCenterY, vDropType ), mItemID( vItemID ), mpItem( pItem ), mListID( mListID ), mLevel( vLevel ), mProtect( vProtect ) 
	{
		memcpy( mOwnerCharID, vOwnerCharID, sizeof( mOwnerCharID ) );
	}
	int GetCreatorType( ) { return ENTITYTYPE_ITEM; }

	virtual ~CItemCreator() {}

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock) { return true;}
};

// ********************************************************************** //
// CMoneyCreator
// ********************************************************************** //

class CMoneyCreator : public CDropCreator
{
public:
	unsigned int	mMoney;			// ���ɵĵ���ID

public:

	CMoneyCreator() : CDropCreator( ENTITYTYPE_MONEY ) {}

	CMoneyCreator( unsigned int vMoney, int vRange, int vCenterX, int vCenterY, int vCreateType, int vDieEntityID, int vDropType = DROP_OBJECTIVE ) 
		: CDropCreator( vRange, vCenterX, vCenterY, vDropType ), mMoney( vMoney )
	{
	}
	
	virtual ~CMoneyCreator() {}
	int GetCreatorType( ) { return ENTITYTYPE_MONEY; }

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock) { return true;}

};

// ********************************************************************** //
// CPedalCreator
// ********************************************************************** //

class CPedalCreator : public CCreator
{
public:
//	enum
//	{
//		PEDAL_TELEPORT,		// ���͵�̤��
//		PEDAL_TRAP,			// ����̤��
//		PEDAL_HIEROGRAM,	// ���̤��
//	};
	struct ActiveData 
	{
		int  mHour;
		int  mRand;
		bool mActive;
	};	

public:
	int				mPedalType;		// �����̤�壬̤������
	CWTRect			mSrcRect;		// ̤���Դ����
	CWTRect			mActRect;		// ��������
	CWTPoint		mDesPos;		// ����Ǵ��͵�̤�壬Ŀ������
	unsigned short	mLineID;		// ����Ǵ��͵�̤�壬Ŀ����ID, �������0��ʾ���ߵ�ͼ
	unsigned short	mMapID;			// ����Ǵ��͵�̤�壬Ŀ���ͼID
	unsigned short	mSkillID;		// ���������̤�壬��Ӧ�ļ���ID
	unsigned short	mSkillLevel;	// ���������̤�壬��Ӧ�ļ��ܵȼ�
	int				mSrcEntityID;	// �ͷ���ʵ��ID
	unsigned int	mTeamID;
	unsigned int	mMinLevel;		// ��͵ȼ�
	unsigned int	mNation;		// ���ƹ���
	int				mTempID;
	int				mInit;
	ActiveData		mRandList[ 24 ];	// ����ʱ���б�
	int				mRandCount;		// �������
	int				mMaxActive;		// ��󼤻�����
	int				mCurrentActive;	// ��ǰ��������
	int				mPedalID;		// ��Ӧ��ʵ��ID
	int				mExistTime;		// ���ʱ��

	int				mDefaultLineID;
	int				mDefaultMapID;
public:

	CPedalCreator( ) : CCreator( ENTITYTYPE_PEDAL )	
	{	
		if( CObj::msCreateMode )
		{
			mPedalType = 0;
			mLineID = 0;
			mMapID = 0;
			mSkillID = 0;
			mSkillLevel = 0;
			mSrcEntityID = 0;
			mTeamID = 0;
			mMinLevel = 0;
			mNation = 0;
			mTempID = 0;
			memset( mRandList, 0, sizeof(mRandList) );
			mRandCount = 0;
			mMaxActive = 0;
			mCurrentActive = 0;
			mPedalID = 0;
			mExistTime = 0;

			mDefaultLineID = 0;
			mDefaultMapID = 0;
		}
	}
	virtual ~CPedalCreator() {}
	int GetCreatorType( ) { return ENTITYTYPE_PEDAL; }

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock) ;

	int RefreshActive( );
};

// ********************************************************************** //
// CPetCreator
// ********************************************************************** //

class CPetCreator : public CCreator
{
public:
	CWTPoint		mPos;			// �ٻ��޴�����λ��
	EDirType		mDirection;		// ��ʼ����
	int				mPetID;			// �ٻ���ģ��ID
	int				mSrcEntityID;	// �ٻ��ߵ�ID
	int				mOnlineTime;	// ����ʱ��
	int				mPetMode;		// pkģʽ
public:

	int Initialize()
	{
		mPos = CWTPoint(0,0);
		mDirection = DIR_DOWN;
		mPetID = 0;
		mSrcEntityID = 0;
		mOnlineTime = 0;
		mPetMode = 0;
		return 0;
	}

	CPetCreator( ) : CCreator( ENTITYTYPE_PET )
	{	
		if( CObj::msCreateMode )
		{
			Initialize();
		}
	}

	int GetCreatorType( ) { return ENTITYTYPE_PET; }
	virtual ~CPetCreator() {}

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock) { return true;}
};



// ********************************************************************** //
// CCollectCreator
// ********************************************************************** //

class CCollectCreator : public CCreator
{
public:
	CWTPoint		mPosition[ 200 ];	// ������λ��
	EDirType		mDirection;		// ��ʼ����
	int				mNpcID;			// ģ��ID
	int				mRelife;		// NPC����ʱ��
	int				mDisappear;		// ��ʧʱ�� 
	int				mPCount;		// λ������
	int				mInit;

public:

	CCollectCreator( ) : CCreator( ENTITYTYPE_COLLECT )	
	{
		if( CObj::msCreateMode )
		{
			memset( mPosition, 0, sizeof( mPosition ) );
			mDirection = DIR_DOWN;
			mNpcID = 0;
			mRelife = 0;
			mDisappear = 0;
			mPCount	= 0;
			mInit = 0;
		}
	}
	int GetCreatorType( ) { return ENTITYTYPE_COLLECT; }
	virtual ~CCollectCreator() {}

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock) ;
};

// ********************************************************************** //
// CGhostCreator
// ********************************************************************** //

class CGhostCreator : public CCreator
{
//public:
//	CWTPoint		mPos;	// ������λ��
//	EDirType		mDirection;		// ��ʼ����
//	int				mNpcID;			// ģ��ID
//public:
//
//	CGhostCreator( ) : CCreator( ENTITYTYPE_GHOST )	{ }
//	virtual int GetCreatorType( ){ return ENTITYTYPE_GHOST; }
//	CGhostCreator( int vType ) : CCreator( vType ) {  } 
//
//	virtual ~CGhostCreator() {}
//
//
//	// �������ļ�����
//	virtual bool LoadFromConfig(TiXmlElement* pElemBlock) { return true;};
//	/////////////////
public:
	CWTPoint		mPos;	// ������λ��
	EDirType		mDirection;		// ��ʼ����
	int				mNpcID;			// ģ��ID

public:
	CGhostCreator( ) : CCreator( ENTITYTYPE_GHOST )	{ Initialize();	}
	CGhostCreator( int vType ) : CCreator( vType ) { Initialize(); } 
	virtual int Initialize() ;
	int GetCreatorType( ) { return ENTITYTYPE_GHOST; }	

	virtual ~CGhostCreator() {}

	// �������ļ�����
	virtual bool LoadFromConfig(TiXmlElement* pElemBlock){ return true;};
	//////////////////
};



/************************************************************************/
/* CCreatorManager                                                                     */
/************************************************************************/
class CCreatorManager : public CSingleton< CCreatorManager >
{
public:
	typedef lk::vector< int, 3000 > TimeRefreshList;
	typedef lk::vector< int, 10 > PedalRefreshList;
	typedef lk::vector< int, 100 > NotifyList;
	int mOgreCreator[ OGREINDEX ];
	TimeRefreshList mRefreshList;
	PedalRefreshList mPedalList;
	NotifyList mNotifyList;

public:

	void* operator new( size_t size );
	void operator delete( void* pointer );

	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* pointer, const char* file, int line);

	int InsertCreatorBase( int vIndex, CCreator* vpCreatorBase );
	CCreator* GetCreator( int vIndex  );
	unsigned int GetCreateIndex( CCreator* vpCreate );
	void RefreshPedals( );
	void RemoveCreator( CCreator *pCreator );

	CCreatorManager( );
	~CCreatorManager( );

	static CSharedMem* mShmPtr;
	static unsigned int CountSize(){ return sizeof( CCreatorManager ); }
};


