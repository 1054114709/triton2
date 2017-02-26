#pragma once
class CMapObject;
class CObj;
class CEntity;
// ********************************************************************** //
// CMapEntity
// ********************************************************************** //

#include "lk_sharedvector.h"
#include "sceneobj_define.h"
#include "lk_vector.h"


class CMapEntity : public CObj 
{
public:

	typedef lk::fixed_size_memory_pool< int, SERVER_CAP_DATA_MAPENTIY, 2> SharedSeenEntityPool;	
	typedef lk::fixed_size_memory_pool< int, SERVER_CAP_DATA_MAPPEDAL, 2> SharedSeenPedalPool;	
	typedef lk::shared_vector< int, SERVER_CAP_DATA_MAPENTIY > SeenEntityVector;
	typedef lk::shared_vector< int, SERVER_CAP_DATA_MAPPEDAL > SeenPedalVector;


	//TODO
	int							mEntityID;	// �Լ���ʵ��
	SeenEntityVector			mSeenEntitys;// ������ʵ��
	SeenPedalVector				mSeenPedals; // ������̤��

	// ��̬��������
	static SharedSeenEntityPool*	msSharedSeenEntityPoolPtr;
	static SharedSeenPedalPool*		msSharedSeenPedalPoolPtr;
public:
	
	CMapEntity( CEntity* pEntity )	{	}
	
public:
	//TODO
	CMapEntity( );
	
	virtual ~CMapEntity( );

	virtual int Initialize();
	virtual int Resume();

public:
	inline int GetSelfEntityID( ) {return mEntityID;}

	CEntity* GetSelfEntity( ); 

	// ��ӿ�����ʵ��
	void AddViewEntity( CMapEntity* pEntity );

	// ɾ��������ʵ��
	void DeleteViewEntity( int nMapEntityObjID );

	// ���͵�Ŀ�곡��
//	void Teleport( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const CWTPoint& rDesPos );
	//void Teleport( int vLineID, int vMapID, const CWTPoint& rDesPos );


	// ������Ϣ�������Լ���ʵ�� 
	int SendMessageToSeenEntitys( CMessage* tpMessage );

	// �õ���Ұ���NPC ʵ��ID  ����ģ�����
	int GetSeenNpcs( vector<int>& vNpcs );

};

// ********************************************************************** //
// CMapEntity
// ********************************************************************** //

class CMapNpc : public CMapEntity
{
public:
	
	CMapNpc( ) {}
	CMapNpc( CEntity* pEntity ) : CMapEntity( pEntity )	{	}

public:

	int GetNpcID();

};

// ********************************************************************** //
// CMapPedal
// ********************************************************************** //

class CMapPedal : public CMapNpc
{
public:

	//TODO: ��Щ����Ҫ�ˣ�������CEntityPedal

	//int				mPedalType;			// ̤������
	//CWTRect			mSrcRect;			// ̤��Ĵ���Դ����
	//CWTPoint		mDesPos;			// ����Ǵ���̤�壬��ô���͵�Ŀ������
	//unsigned short	mLineID;			// ����Ǵ���̤�壬��ô���͵�Ŀ����ID
	//unsigned short	mMapID;				// ����Ǵ���̤�壬��ô���͵�Ŀ���ͼID
	//int				mSrcEntityID;		// ���������̤�壬�ͷ�����ID
	//int				mPresistTime;		// ���������̤�壬����ʱ��
	//unsigned short	mSkillID;			// ���������̤�壬��Ӧ����ID
	//unsigned short	mSkillLevel;		// ���������̤�壬��Ӧ���ܵȼ�
	//unsigned int	mMinLevel;			// ���ƴ��͵ĵȼ�
	//unsigned int	mNation;			// �������ƵĹ���

public:
	//TODO
	CMapPedal( ) {}
	virtual ~CMapPedal( ) {}

public:
	//bool OnTouch( CMapObject* pMap, CMapEntity* pEntity, bool& rErase );		// ̤�崥���߼�
};
