#pragma once

#include "sceneobj_define.h"
#include "maptplmanager.h"
#include "mapmessage_pb.hxx.pb.h"
#include "repetionmodule.h"
#include "lk_queue.h"
#include "property.h"
#include "entity_searcher.h"

#define BLOCK_MAX ( ( MAX_MAP_CELL >> 5 ) + 1 )
#define BLOCK_INDEX( tCell )		( tCell >> 5 )
#define BLOCK_CELL_INDEX( tCell )	( tCell % 32 )

// ��̬����NPC������
#define CREATENPC_RANGE_WIDE 20
#define CREATENPC_RANGE_HEIGHT 20

#define VIPCOOLTIME		300

// 
/** @��ͼ��Ԫ��
** ��װ�˱�������( ����ֱ����begin,end���� )
** ��Ҫ�����Զ���ĺ���������ڲ��������б���
*/
class CMapCell
{
protected:
	typedef lk::fixed_size_memory_pool< int, SERVER_CAP_SHARE_CELLENTITY, 2> SharedCellsEntity;	
	typedef lk::shared_vector< int, SERVER_CAP_SHARE_CELLENTITY > CellsEntity;

	//ע�⣺��ͼ�༭��������ĵ�ͼʵ������width+1,height+1. 
	CellsEntity mCells;

public:
	
	CMapCell( );
	~CMapCell( );

	// ��ʵ����뵽cell
	bool AddEntityToCell( CEntity* pEntity )
	{
		mCells.push_back( pEntity->GetEntityID() );	
		return true;
	}

	// ��ʵ���cell���Ƴ�
	bool RemoveEntityFromCell( CEntity* pEntity )
	{
		for ( CellsEntity::iterator tBegin = mCells.begin(); tBegin != mCells.end(); ++tBegin )
		{
			// ����ҵ����Լ�
			if ( *tBegin == (int)pEntity->GetEntityID() )
			{
				mCells.erase( tBegin );
				return true;
			}
		}

		return false;
	}

	// ����
	template<class Visitor>
	void Tick( Visitor& rVst )
	{
		for ( CellsEntity::iterator tBegin = mCells.begin(); tBegin != mCells.end(); )
		{
			// �������󷵻�ֵΪfalseʱ��
			if( rVst( *tBegin ) == false )
			{
				//��ʾѭ��������ǰ��ֹ 
				if( rVst.GetResult() == EM_OBJFUN_ENTITY_TERMINATE )
				{
					return;
				}
				else if( rVst.GetResult() == EM_OBJFUN_ENTITY_NOTEXIST )
				{
					mCells.erase( tBegin++ );
				}
				else
				{
					++tBegin ;
				}
				
			}
			else
			{
				++tBegin ;
			}
		}
	}
};



// ********************************************************************** //
// CMapObject
// ********************************************************************** //
class CMapObject : public CObj
{
	friend class CMapTplManager;
public:

	typedef lk::fixed_size_memory_pool< int, SERVER_CAP_SHARE_CELLENTITY, 2> SharedCellsEntity;	
	typedef lk::shared_vector< int, SERVER_CAP_SHARE_CELLENTITY > CellsEntity;
	typedef lk::vector< int, MAX_MAP_PLAYER_PER > PLAYER_VECTOR;

protected:
	unsigned short				mWidth;				// ��ͼ��
	unsigned short				mHeight;			// ��ͼ��
	unsigned short				mLineID;           
	unsigned short				mMapID; 
	unsigned short				mIndex;
	lk::string<	NAME_LENGTH >	mMapName; 			// ��ͼ����
	KEY_TYPE					mKey;


	static SharedCellsEntity* msMapEntityIDSharedPoolPtr; // ��ͼ���еĶ���

public:
	//ע�⣺��ͼ�༭��������ĵ�ͼʵ������width+1,height+1. 
	PLAYER_VECTOR mPlayers;
	int			mBlock[ ( MAX_MAP_CELL >> 5 ) + 1 ];
	int mPlayerWaitInCount;

#ifdef _FB_
	typedef lk::vector< int, 700 > ENTITY_VECTOR;
	ENTITY_VECTOR	mEntity;
	unsigned int	mRepetionID;

	int			mData[ 10 ];
	
	int				mVirtualMapID;
#endif
	
public:
	CMapObject( unsigned short vLineID, unsigned short vMapID );
	CMapObject( ) ;
	~CMapObject( );

public:
	virtual int Initialize();
	virtual int Resume();

	bool IsCommMap( );
	bool IsBattleMap( );
	bool IsFBMap( );
	bool IsGroundMap( );
	bool IsSchoolMap( );
	
	MAP_TYPE GetMapType( );

	inline void SetMapID( unsigned short vMapID ){ mMapID = vMapID; }
	inline unsigned short GetMapID( ){ return mMapID; }

	inline unsigned short GetMapIndex( ) { return mIndex; }
	inline void SetMapIndex( unsigned short vIndex ) { mIndex = vIndex; }

	int LoadTpl( CMapTpl* pMapTpl );
	int CreateAllEntity( );	

	unsigned short GetLineID( ) { return mLineID; }
	void SetLineID( unsigned short usLineID ) { mLineID = usLineID; }

	int SetKey( KEY_TYPE vKey ) { mKey = vKey; return SUCCESS; }
	KEY_TYPE GetKey( ) { return mKey; }

	short GetMinLevelLmt( ) ;
	short GetMaxLevellmt( ) ;

	CGridBlock* GetGridBlock( unsigned int vWidth, unsigned int vHeight );

	// ��ͼ��
	inline unsigned short GetWidth( ) { return mWidth; }

	// ��ͼ��
	inline unsigned short GetHight( ) { return mHeight; }

	// ����NPC
	int CreateNpc( CCreator* pNpcTpl, bool vInit = false, int vNpcID = 0, CWTPoint vPoint = CWTPoint( 0, 0 ), bool vDelay = false );

	// �õ���ͼ��
	virtual CMapCell* GetCell( const CWTPoint& rPoint ) = 0;

	// ����Ƿ����ͨ��
	bool CanPlayerPass( const CWTPoint& rPoint );

	// NPC�Ƿ����ͨ��
	bool CanNpcPass( const CWTPoint& rPoint );

	// �Ƿ�����Ч����
	inline bool IsValidPos( const CWTPoint& rPoint ) { return rPoint.mX <= GetWidth() && rPoint.mY <= GetHight(); }
	
	// �Ƿ�����԰�ȫ����(����������ɱ)
	bool IsCtrSafeRegion( const CWTPoint& rPoint );

	// �Ƿ��Ǿ��԰�ȫ����(�й�������ɱ)
	bool IsAbsSafeRegion( const CWTPoint& rPoint );

	// �Ƿ�̬�赲
	bool IsStaticBlock( const CWTPoint& rPoint );

	// �Ƿ��ǰ�̯��ȫ��
	bool IsStallSaftyArea( const CWTPoint& rPoint );

	// �����Ƿ�������ڰ�̯
	bool HasInStall( const CWTPoint& rPoint );

	// �Ƿ��ƶ�����
	unsigned int IsLocked( const CWTPoint& rPoint );

	// �Ƿ�߼��赲
	bool IsSuperBlock( const CWTPoint& rPoint );

	// �ƶ�ʵ��
	void MoveEntity( CEntityCharacter* pEntity, const CWTPoint& rPoint );

	// �ƶ�ʵ��
	void PathEntity( CEntityCharacter* pEntity, const CWTPoint& rSrcPos, const CWTPoint& rDesPos, int vDirection );

	// ����·��
	void FindPath( const CWTPoint& rSrcPos, const CWTPoint& rDesPos, std::vector< CWTPoint >& rPathList );

	// ����ʵ��
	int CreateEntity( CEntity* pSrcEntity, CCreator* pCreator ,bool vFirst = false);


	// ���ʹ���npc��Ϣ���������
	int SendCreateNpc2Player( CEntityPlayer* pReceiver, std::vector<CEntity*> *pNpcVec, int nListID = 0 );

	// ���ʹ�������npc��Ϣ��������
	int SendCreateNpc2Players( std::vector<CEntityPlayer*>* pReceiver, CEntity* pSingleNpc, int nListID = 0 );

	// ���ʹ��������Ϣ���������
	int SendCreatePlayer2Player( CEntityPlayer* pReceiver, std::vector<CEntityPlayer*> *pPlayerVec );

	// ���ʹ������������Ϣ��������
	int SendCreatePlayer2Players( std::vector<CEntityPlayer*>* pReceiver, CEntityPlayer* pSinglePlayer );

	// �������ٶ��entity��Ϣ���������
	int SendDestroyEntity2Player( CEntityPlayer* pReceiver, std::vector<CEntityPlayer*>* pPlayerToBeDestroy, std::vector<CEntity*>* pNpcToBeDestroy );
	
	// �������ٵ���entity��Ϣ��������
	int SendDestroyEntity2Players( std::vector<CEntityPlayer*>* pReceiver, CEntity* pEntityToBeDestroy );

	// ɾ��ʵ��
	void DestroyEntity( CEntity* pEntity );

	// ��ʱ��
	void OnTimer( unsigned int vTickOffset );

	void OnEntityMove( CEntityCharacter* pEntity, const CWTPoint& rPos, EDirType vDirection );

	// ��ʵ����뵽cell
	bool AddEntityToCell( CEntity* pEntity );

	// ��ʵ���cell���Ƴ�
	bool RemoveEntityFromCell( CEntity* pEntity );

	// �õ������
	bool GetDropPos( CWTPoint &vOrginPos );

	// �õ�NPC������
	bool GetNpcCreatePos( CWTPoint &vOrginPos, EEntityType nType );

	bool IsFull( );

	int AddPlayerIntoMap( CEntityPlayer* vpPlayer ,bool vFirst);
	int RemovePlayerFromMap( CEntityPlayer* vpPlayer );
	int GetPlayerCount( );

	int AddPlayerWaitInCount( );
	int DelPlayerWaitInCount( );
	int GetPlayerWaitInCount( );
	
	int GetPlayerCountMax( );

	// �����Ƿ��赲NPCռ��
	bool IsOccupiedByBlock( CWTPoint& rPos );

	// ����ʹ�õͼ�����
	bool CanRideBaseHorse( CWTPoint& rPos ) { return true; }

	// ����ʹ�ø߼�����
	bool CanRideAdvanceHorse( CWTPoint& rPos ) { return true; }

	// �õ���ͼ��
	const char* GetMapName( ) { return mMapName.c_str(); }

	// ����Message����ͼ������player
	void SendMsg2Player( CMessage* vpMsg );

	// �Ƿ��Ǿ��԰�ȫ��
	bool IsAbsSafe( );

	// Point Is Block
	bool IsBlock( int mX, int mY );

	// Set Block
	int AddBlock( int mX, int mY );

	// Remove Block
	int RemoveBlock( int mX, int mY );

	// �ô��ɼ���Χ
	int GetViewRect( CEntity* pEntity, CWTPoint& rLeftTop, CWTPoint& rRightBottom );
	
	bool IsCreatorIn( int vCreatorIndex );

#ifdef _FB_
	int SetRepetionID( unsigned int vObjID ) { mRepetionID = vObjID; return SUCCESS; }
	CRepetion* GetRepetion( ) { return ( CRepetion* )CSceneObjManager::GetSingletonPtr( )->GetObject( mRepetionID ); }
	int GetRepetionID( ) { return mRepetionID; }
	int DestroyAliveTempOgreEntity( unsigned int vTemplateID, unsigned int vCount );

	int SetVirtualMapID( unsigned int vMapID );
	int GetVirtualMapID( );

	int SetMapData( int vIndex, int vData );
	int GetMapData( int vIndex );
#endif

};


// ���͵�ͼ
class CMapObjectL : public CMapObject
{
public:
#ifndef _FB_
	static const int msWidth = 600 ;	
	static const int msHeight = 800 ; 
#else
	static const int msWidth = 300 ;
	static const int msHeight = 320;
#endif
	virtual CMapCell* GetCell( const CWTPoint& rPoint );

private:
	CMapCell mCells[msWidth*msHeight];

};

// ���͵�ͼ
class CMapObjectM : public CMapObject
{
public:
#ifndef _FB_
	static const int msWidth = 240 ;
	static const int msHeight = 320 ;
#else
	static const int msWidth = 200;
	static const int msHeight = 350;
#endif
	virtual CMapCell* GetCell( const CWTPoint& rPoint );

private:
	CMapCell mCells[msWidth*msHeight];
};

// С�͵�ͼ
class CMapObjectS : public CMapObject
{
public:
#ifndef _FB_
	static const int msWidth = 188 ;
	static const int msHeight = 172 ;
#else
	static const int msWidth = 90;
	static const int msHeight = 95;
#endif
	virtual CMapCell* GetCell( const CWTPoint& rPoint );

private:
	CMapCell mCells[msWidth*msHeight];
};

// ********************************************************************** //
// CMapObjManager
// ********************************************************************** //

class CMapObjManager : public CSingleton< CMapObjManager >
{
public:
	typedef lk::hash_map< int, int, SERVER_CAP_L_MAP_OBJECT+SERVER_CAP_M_MAP_OBJECT+SERVER_CAP_S_MAP_OBJECT > 	MapObjMap;
	
	static CSharedMem* mShmPtr; // �����ڴ��ַ

#ifdef _FB_
	typedef lk::queue< int, SERVER_CAP_REPETION_OBJECT >	FreeMapObjQueue;
	int mMapObjID[ SERVER_CAP_REPETION_OBJECT ];
	FreeMapObjQueue mFreeMapObjQueue;
#else
	MapObjMap mMapObjects;
#endif	
	typedef lk::vector< int, 200 >		DENY_LIST_TYPE;
	DENY_LIST_TYPE	mDenyList;

public:
	CMapObjManager();
	~CMapObjManager( );

	void* operator new( size_t size );
	void  operator delete( void* pointer );

	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* pointer, const char* file, int line);

	static unsigned int CountSize();

public:
	// ������ͼ
	CMapObject* CreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName,
		KEY_TYPE vKey = 0 );

	// �õ���ͼ����
	CMapObject* GetMapObject( unsigned short vLineID, unsigned short vMapID, unsigned short vMapIndex, 
		KEY_TYPE vKey = INVITED_KEY_VALUE  );

	CMapObject* GetMapObject( unsigned int vObjID );

	int DestroyMapObject( CMapObject* vpMapObj );

	int ReloadDeny( );
	bool IsDeny( int vTempID );

public:
	static int MakeKey( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex = 0 );
};



