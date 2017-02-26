//=========================================================================
// union.h
//=========================================================================
#pragma once

#include "entity.h"
#include "corpstype.h"
#include "corpsinfo_pb.hxx.pb.h"   


	
//-------------------------------------------------------------------------
class MsgList
{
public:
	typedef lk::vector< int, MAX_CORPSAPPLY_NUM > ApplyVector;

public:
	ApplyVector mList;

public:
	void Initialize( ){ mList.initailize(); }

	inline bool IsFull( ){ return mList.size() == mList.max_size(); }

	inline bool InList( int vID )
	{ 
		for ( ApplyVector::iterator it = mList.begin(); it != mList.end(); ++it )
		{
			if ( *it == vID )
			{
				return true;
			}
		}
		return false;
	}

	inline void Insert( int vID ){ mList.push_back( vID ); }

	inline void Remove( int vID )
	{
		for ( ApplyVector::iterator it = mList.begin(); it != mList.end(); ++it )
		{
			if ( *it == vID )
			{
				mList.erase( it );
				return;
			}
		}
	}
}; 

/**
** ����
** �������Ӿ��Ÿ���һ����9�������������������ܹ���10�����ŵ�����
** ��Ϊ������ܶ�ط������õ������б���߾��˲�ս�б��Ұ�MAX_CORPS_UNION��ʱ�ŵ�10����
** ��ζ�������о��Ŷ����б���������������Ӿ��š�
** ���Ǿ��˼Ӿ��ŵ�ʱ��Ҫע�����֣�ʵ����ֻ�ܽ���9�����š�
**
*/
class CUnion : public CObj
{
public:
	typedef lk::vector< int, MAX_CORPS_UNION-1 > CorpsVector;	
	enum ECorpsList
	{
		CORPSLISTFULL	 = 1,
		CORPSHASEXIST	 = 2,
	};

	typedef lk::vector< int, MAX_BATTLESIZE > UnionBattleList;

public:
	int		mUnionID;												// ����ID
	char	mUnionName[MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES];		// ��������
	char	mHeadName[NAME_LENGTH];									// �ų�����
	char	mCoreName[MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES];			// ����������
	int		mCoreID;												// ������ID
	int		mCorpNum;												// ��������
	int		mCity;													// ���ǵ�ͼ
	int		mMapNum;												// ��ͼ����
	char	mBulletin[CORPS_BULLETIN_LENGTH*MAX_UTF8_BYTES];		// ����
	int		mMemberNum;												// �˿�����

	CorpsVector mCorpsList;
	MsgList mApplyList;
	MsgList mInviteList;

	UnionBattleList mUnionBattleList;
public:
	CUnion()
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

	~CUnion() {}

	int Initialize()
	{
		mUnionID = 0;
		mCoreID = 0;
		mCorpNum = 0;
		mCity = 0;
		mMapNum = 0;
		mMemberNum = 0;
		memset( mUnionName, 0, ARRAY_CNT(mUnionName) );
		memset( mHeadName, 0, ARRAY_CNT(mHeadName) );
		memset( mCoreName, 0, ARRAY_CNT(mCoreName) );
		memset( mBulletin, 0, ARRAY_CNT(mBulletin) );
		mCorpsList.initailize();
		mApplyList.Initialize();
		mInviteList.Initialize();
		mUnionBattleList.initailize();
		return 0;
	}

	int Resume() {return 0;}

	void SetUnionID( const int vID )
	{ 
		mUnionID = vID;
	}
	int GetUnionID(){ return mUnionID; }

	void SetUnionName( const char* vpName )
	{ 
		if ( vpName == NULL ) return ;
		strncpy( mUnionName, vpName, sizeof( mUnionName ) - 1 );
	}
	char* GetUnionName(){ return mUnionName; }

	void SetHeadName( const char* vpName )
	{ 
		if ( vpName == NULL ) return ;
		strncpy( mHeadName, vpName, sizeof( mHeadName ) - 1 );
	}
	char* GetHeadName(){ return mHeadName; }

	void SetCoreName( const char* vpName )
	{ 
		if ( vpName == NULL ) return ;
		strncpy( mCoreName, vpName, sizeof( mCoreName ) - 1 );
	}
	char* GetCoreName(){ return mCoreName; }

	// ������
	void SetCoreID( const int vID )
	{ 
		mCoreID = vID;
	}
	int GetCoreID(){ return mCoreID; }

	void SetCorpNum( const int vNum )
	{ 
		mCorpNum = vNum;
	}
	int GetCorpNum(){ return mCorpNum; }

	void SetCity( const int vCity )
	{ 
		mCity = vCity;
	}
	int GetCity(){ return mCity; }

	void SetMapNum( const int vNum )
	{ 
		mMapNum = vNum;
	}
	int GetMapNum(){ return mMapNum; }

	void SetBulletin( const char* vpBulletin )
	{ 
		if ( vpBulletin == NULL ) return ;
		strncpy( mBulletin, vpBulletin, sizeof( mBulletin ) - 1 );
	}
	char* GetBulletin(){ return mBulletin; }

	void SetMemberNum( const int vNum )
	{ 
		mMemberNum = vNum;
	}
	int GetMemberNum(){ return mMemberNum; }

	int InsertCorps( int vCorpsID )
	{
		if ( mCorpsList.size() == mCorpsList.max_size() )
			return CORPSLISTFULL;
		for ( CorpsVector::iterator it = mCorpsList.begin(); it != mCorpsList.end(); ++it )
		{
			if ( *it == vCorpsID )
				return CORPSHASEXIST;
		}
		mCorpsList.push_back( vCorpsID );
		return 0;
	}

	void RemoveCorps( int vCorpsID )
	{
		for ( CorpsVector::iterator it = mCorpsList.begin(); it != mCorpsList.end(); ++it )
		{
			if ( *it == vCorpsID )
			{
				// ��ս�б���
				this->DeleteBattleMemberByCorpsID( vCorpsID );

				mCorpsList.erase( it );
				return;
			}
		}
	}

	bool HasCorps( int vCorpsID )
	{
		// ������Ҳ������ڵľ���
		if( vCorpsID == mCoreID )
			return true;

		for ( CorpsVector::iterator it = mCorpsList.begin(); it != mCorpsList.end(); ++it )
		{
			if ( *it == vCorpsID )
				return true;
		}
		return false;
	}

	void GetCorpsList( int *vCorpsID, int &vNumber )
	{
		int tNumber = 1;
		vCorpsID[ 0 ] = mCoreID;
		for ( CorpsVector::iterator it = mCorpsList.begin(); it != mCorpsList.end(); ++it )
		{
			if ( tNumber >= vNumber )
				break;
			vCorpsID[ tNumber++ ] = *it;
		}
		vNumber = tNumber;
	}

	void GetUnionBasicInfo( PBUnionBasicInfo *vInfo );	

	int InsertBattleMember( int nRoleID );
	int ClearBattleList();
	int GetBattleMemberList( int* vpList, int& nSize );
	bool IsInBattleList( int nRoleID );

	// ɾ����ս��Ա [2010-03-14 GaoHong]
	int DeleteBattleMemberByCorpsID( int nCorpsID );
	int DeleteBattleMemberByRoleID( int nRoleID );

	// ��������ֵ
	int GetUnionPower();


};
