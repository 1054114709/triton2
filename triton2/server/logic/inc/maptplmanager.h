#pragma once
// ********************************************************************** //
// CGridBlock
// ********************************************************************** //
#include "property.h"
#include "errcode.h"
#include "base_define.h"
#include "sceneobj_define.h"

// �赲����
// �����˿���ͨ��
#define FLAG_ALLCANPASS			0xFFFFFFFF
// NPC����ͨ��
#define FLAG_NPCCANNOTPASS		0x00000001
// ���԰�ȫ
#define FLAG_ABSOLUTESAFE		0x00000002
// ��԰�ȫ
#define FLAG_CONTRARYSAFE		0x00000004
// ��̬�赲
#define FLAG_STATICBLOCK		0x00000008
// ����ʹ�ô��͵���
#define FLAG_USETELEITEM		0x00000010
// ��̯��ȫ��
#define FLAG_STALLAREA			0x00000020
// PK��
#define FLAG_PKAREA				0x00000040
// �߼��赲��
#define FLAG_SUPERBLOCK			0x00000080

enum MAP_TYPE
{
	COMM_MAP		= 0,
	GROUND_MAP		= 1,
	FB_MAP			= 2,
	BATTLE_MAP		= 3,
	SCHOOL_MAP		= 4,
};


class CMapObject;
class TiXmlElement;
class  CSharedMem;

// ��ͼ��̬�赲��Ϣ
class CGridBlock
{
	public:
		int		mBlockInfo[ 1 ];

	public:
		CGridBlock( )
		{
		}

	public:
		int Initial( )
		{
			mBlockInfo[ 0 ] = 0;
			return SUCCESS;
		}

		// ����Ƿ����ͨ��
		bool CanPlayerPass( )	{ return ( ( mBlockInfo[ 0 ] & FLAG_ALLCANPASS ) == FLAG_ALLCANPASS ); }

		// NPC�Ƿ����ͨ��
		bool CanNpcPass( )		{ return ( ( mBlockInfo[ 0 ] & FLAG_NPCCANNOTPASS ) != FLAG_NPCCANNOTPASS ); }

		// �����Ƿ��Ǿ��԰�ȫ����
		bool IsAbsSafeRegion( )		{ return ( ( mBlockInfo[ 0 ] & FLAG_ABSOLUTESAFE ) == FLAG_ABSOLUTESAFE ); }

		// �����Ƿ�����԰�ȫ����
		bool IsCtrSafeRegion( )	{ return ( ( mBlockInfo[ 0 ] & FLAG_CONTRARYSAFE ) == FLAG_CONTRARYSAFE ); }

		// �Ƿ��Ǿ�̬�赲
		bool IsStaticBlock( )	{ return ( ( mBlockInfo[ 0 ] & FLAG_STATICBLOCK ) == FLAG_STATICBLOCK ); }

		// �Ƿ��ǰ�̯��ȫ��
		bool IsStallSafty( ) { return ( ( mBlockInfo[ 0 ] & FLAG_STALLAREA ) == FLAG_STALLAREA ); }

		// �Ƿ��Ǹ߼��赲
		bool IsSuperBlock( )	{ return ( ( mBlockInfo[ 0 ] & FLAG_SUPERBLOCK ) == FLAG_SUPERBLOCK ); }

};

// ********************************************************************** //
// CMapTpl
// ********************************************************************** //

class CMapTpl
{
private:
	typedef lk::vector< int, 2000 > CREATOR_LIST_TYPE;
public:
	char					mMapName[ NAME_LENGTH ];
	int						mMapID;
	int						mWidth;
	int						mHeight;
	CREATOR_LIST_TYPE	mCreators;	
	int						mPlayerCountMax;
	MAP_TYPE				mMapType;

	// �����ĵ�ͼ����
	bool				mPKPunish;			// PK�ͷ�
	bool				mBasRide;			// ����ͼ�����
	bool				mAdvRide;			// ����߼�����
	bool				mTeleItem;			// ����ʹ�ô�����Ʒ
	bool				mNoNation;			// �Ƿ�û�й�������
	bool				mAbsSafe;			// �Ƿ���԰�ȫ
	bool				mConSafe;			// �Ƿ���԰�ȫ
	bool				mFlyRide;
	short				mMaxLevelLmt;	// ��ߵȼ�����
	short				mMinLevelLmt;	// ��͵ȼ�����
	short				mProtectLevel;
	EPKMode				mPKMode;			// PKģʽ
	CGridBlock			mGrids[ MAX_MAP_CELL ];

public:
	CMapTpl( )
	{
	}

public:
	~CMapTpl( )
	{
		Final( );
	}

	CGridBlock* GetGridBlock( unsigned int vWidth, unsigned int vHeight );

	CMapObject* CreateMapObject( );

	// ��͸�
	inline unsigned short GetWidth( ) { return mWidth; }
	inline unsigned short GetHeight( ) {return mHeight; }

	short GetMinLevelLmt( ) { return mMinLevelLmt; }
	void SetMinLevelLmt( int nMinLevel ) { mMinLevelLmt = nMinLevel; }

	short GetMaxLevellmt( ) { return mMaxLevelLmt; }
	void SetMaxLevelLmt( int nMaxLevel ) { mMaxLevelLmt = nMaxLevel; }

	int LoadMap( TiXmlElement* vpElement, FILE* vpBlock, const char* pTplName, unsigned short vLineID, 
			unsigned short vMapID );
	int Final( );
	int Initial( )
	{
		memset( mMapName, 0, sizeof( mMapName ) );
		mMapID = INVALID_MAP_ID;
		mWidth = 0;
		mHeight = 0;
		mCreators.initailize( );
		mPlayerCountMax = 0;
		mPKPunish = true;
		mBasRide = true;
		mAbsSafe = true;
		mTeleItem = true;
		mNoNation = true;
		mAbsSafe = true;
		mConSafe = true;
		mPKMode = PKMODE_TRAINING;
		mFlyRide = true;

		unsigned int i = 0;
		for( i = 0; i < ARRAY_CNT( mGrids ); i++ )
		{
			mGrids[ i ].Initial( );
		}

		mMinLevelLmt = 0;
		mMaxLevelLmt = 0;
		mProtectLevel = 0;

		return SUCCESS;
	}

	bool IsUnLoad( ) { return ( mWidth == 0 ) || ( mHeight == 0 ); }
	bool IsCreatorIn( int vCreatorIndex );
};

// ********************************************************************** //
// CMapTplManager
// ********************************************************************** //

class CMapTplManager : public CSingleton< CMapTplManager >
{

public:
	CMapTpl mMapTpls[ SERVER_CAP_MAP_TPL ];
	unsigned int mMapTplCount;
public:
	CMapTplManager();
	~CMapTplManager( );

	void* operator new( size_t tSize );
	void operator delete( void* pointer );

	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* pointer, const char* file, int line);

	static unsigned int CountSize( ){ return sizeof( CMapTplManager ); }
	static CSharedMem* mShmPtr;

public:
	// ͨ����ͼID�õ���ͼģ��
	CMapTpl* GetMapTplByID( unsigned short vMapID );
	CMapTpl* CreateMapTpl( const char* pTplName, unsigned short vMapID, unsigned short vLineID, bool bReload = false );
};



