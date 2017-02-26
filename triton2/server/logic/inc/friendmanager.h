#pragma once

#include "friendtype.h"
#include "westserver.h"
#include "property_pb.hxx.pb.h"
#include "servercore.h"
#include "teamtype.h"
struct st_settings
{
	unsigned char nIsRefuseAllAddInf;  // �Ƿ��Զ��ܾ����е���Ӻ�����Ϣ
	EPlayerShow   euMyStatus;		   // �ҵ�״̬
	char          szGroupName[PLAYER_GROUP_COUNT + 1][GROUP_NAME_LENGTH];	   // 4������ �±���ʣ���
	bool		  bIstoSave;			// �з����ı䣬Ҫ���������
	unsigned int  nLastRefrershTime;	// �ϴ�ˢ�º���ʱ��
};

struct st_friend
{
	//char		  szName[ NAME_LENGTH ]; // ���֣���ʱ��
	int			  nCharID;
	unsigned char nGroupId;   // �������ID (0=Ĭ�Ϸ���)
	EPlayerShow   enStatus;   // ״̬�������Ƿ�����
	EPlayerRels   enRel2Me;   // ���ҵĹ�ϵ
	int			  nIntimacyDegree; // �������ܶ�	
	int			  nLastTimeAllOnline; // ���һ��ͬʱ���ߵ�ʱ���
	int			  nDailyIntimacy;	// ������ӻ�ȡ�����ܶ�
	int			  nLastUpdateTime;	// ���һ�θ��µ�ʱ��
	st_friend( )
	{
		if (CObj::msCreateMode)
		{ enStatus = AT_OFFLINE ; }
		nIntimacyDegree = 0;
		nLastTimeAllOnline=0;
	}
	st_friend( unsigned int vPlayerId )
		: nCharID( vPlayerId ) , enStatus(AT_OFFLINE)
	{}

	bool operator < ( const struct st_friend& other )  const
	{
		return nCharID < other.nCharID;
	}
	
	int AddIntimacy( int nIntimacy, int nMaxIntimacy )
	{
		if ( IsANewDay( nLastUpdateTime, time(NULL) ) == true )
		{
			nDailyIntimacy = 0;
		}		
		if ( nDailyIntimacy + nIntimacy > nMaxIntimacy )
		{
			nIntimacy = nMaxIntimacy - nDailyIntimacy;			
		}	
		if ( nIntimacy > 0 )
		{
			nIntimacyDegree += nIntimacy;
			nDailyIntimacy += nIntimacy;
		}			
		nLastUpdateTime = time( NULL );
		return nIntimacy;
	}
};

struct st_enemy
{
	unsigned int   nPlayerId;
	unsigned int   nKilled;
	unsigned int   nBeKilled;
	unsigned char  nIsLocked;
	unsigned char  nState;	// ����״̬ ֻ�����ߺͲ�����
	unsigned long  nKillTime;  // ʱ���

	st_enemy()
	{	
		if (CObj::msCreateMode)
		{ nPlayerId = 0; nKilled = 0; nBeKilled = 0; nIsLocked =  0 ; nState = 0; nKillTime = 0; }
	}
	st_enemy(unsigned int vPlayerId, unsigned short vKilled = 0,  unsigned short vBeKilled = 0, unsigned char vIsLocked = 0
		, unsigned char vState = 0, unsigned long vKillTime = 0 )
		: nPlayerId(vPlayerId), nKilled(vKilled), nBeKilled(vBeKilled), nIsLocked( vIsLocked ), nState(vState), nKillTime(vKillTime) {}
	bool operator < ( const struct st_enemy& other )  const
	{
		return nPlayerId < other.nPlayerId;
	}
};

// Ϊ�˿����ҵ��ĸ���иøɵ��� ��ʱ����������
struct st_enemy_map
{
	unsigned long  nKillTime;			// ʱ���
	int			   nCharID;				// ���ID

	st_enemy_map()
	{
		if (CObj::msCreateMode)
		{ nCharID = 0; nKillTime = 0; }
	}

	st_enemy_map( unsigned long vKillTime, int vCharID )
		: nKillTime(vKillTime), nCharID(vCharID)
	{	}

	bool operator < ( const struct st_enemy_map& other )  const
	{
		return (nKillTime == other.nKillTime)?(nCharID < other.nCharID):(nKillTime < other.nKillTime);
	}
};


class CFriendItem
{
private:
	CSearchArray<st_friend , FRIENDS_LIMIT> mFriends;     // �ҵĺ����б�   ��charid
	CSearchArray<int , BLACKLIST_LIMIT>		mBlacks;      // �ҵĺ������б� ��charid
	CSearchArray<st_enemy , ENEMIES_LIMIT>	mEnemys;      // �ҵĳ���б�   ��charid
	CSearchArray<st_enemy_map , ENEMIES_LIMIT>	mEnemyKillTimeMap;      // ��и���ʱ�������б�
	int										mBlessTimes;  // ����ף�������Ĵ���
	st_settings		 mSettings;		// �ҵ�����
	typedef lk::vector<int, LATEST_CONTACT_MAX> LatestContactType;
	LatestContactType m_LatestContactList;  // �����ϵ��

public:
	CFriendItem( )
	{
		if (CObj::msCreateMode)
		{ 
			mSettings.nIsRefuseAllAddInf = 0;
			mSettings.euMyStatus = AT_ONLINE;
			mSettings.bIstoSave  = false;
			mSettings.nLastRefrershTime = 0;
			memset( mSettings.szGroupName, 0, (PLAYER_GROUP_COUNT + 1)*GROUP_NAME_LENGTH );
			mBlessTimes = 0;
		}
		m_LatestContactList.initailize();
	}

public:
	// ���в������ɹ��Ļ�����0����������� ȡֵ����
	int		AddFriend( int nSrcCharID, EPlayerShow enStat = AT_ONLINE, EPlayerRels enRel = YOUR_FRIEND ) ;
	int		AddFriend( int nSrcCharID, EPlayerShow enStat, EPlayerRels enRel, short nGroupID ) ;

	int		DelFriend( int nSrcCharID ) ;
	int		MoveFriend( int nCharID, int nDesGroupID );

	int		AddBlack( int nSrcCharID ) ;
	int		DelBlack( int nSrcCharID ) ;
	bool	IsBlack( int nSrcCharID );

	unsigned char	GetRefuseAll( ) const;
	unsigned int	GetLastRefresh( ) const;
	int		SetLastRefresh( unsigned int vTime );

	int		SetMyStatus( EPlayerShow enStat );
	EPlayerShow  GetMyStatus();

	// �ı����״̬
	int		SetFriendStatus( int nSrcCharID, EPlayerShow enStat ); 

	int		GetFriendCharIDList( std::vector<int>& rList, bool bIsOnlyOnline = false ) const;
	int		GetBlackCharIDList( int* pBlacks, int& nNum ) const ;

	//int		GetAllFriendsInfo( Friend_Map& rList );
	const char*	GetGroupName( unsigned char nGroupID ) const;
	int		GetFriend( int nCharID, st_friend& rFriend );

	// �ǲ��Ǻ���
	bool	IsFriend( int nCharID );
	bool	IsEnemy( int nCharID );

	// ������Ϣ����
	int		GetFriendNum( ); 
	//int		GetBlackNum( );

	//bool	IstoSave();
	//void	SetIstoSave();

	// �����У�������Ѿ����ڵĳ�У�����true
	int		OnBeKilled( int nCharID, int& nBeKilled, int& nKilled, int& nOutDelCharID );

	bool    OnKilled( int nCharID, int& nKillHim, int& nBeKilled );

	void    SetEnemyState( int nCharID, unsigned char nState );
	int		GetEnemyCharIDList( std::vector<int>& rList, bool bIsOnlyOnline = false ) const ;

	// �õ����
	int		GetEnemy( int nCharID, st_enemy& rFriend );
	int		DelEnemy( int nSrcCharID );

	void	GetTlvBuffer2( PBFriend* pBuffer );
	void	CreateFromTlv2( PBFriend* pBuffer );

	int		LockEnemy( int nDesCharID, int nLockType );
	int		SetGroupName( unsigned char nGroupID, const char* szGroupName );
	void	SetBlessTimes( int nTimes ){ mBlessTimes = nTimes; }
	int		GetBlessTimes() { return mBlessTimes; }	
	st_friend *GetFriendByRoleID( int nRoleID );
	// ���������ϵ��
	int		AddLatestContacter(int nCharID);
	int		GetContacterCount();
	int		GetContacter(int nIndex);
	
	int		UpdateLastTimeAllOnLine( int nRoleID, int nTime );	// �������к��ѵ����һ��ͬʱ����ʱ��
	int		UpdateIntimacyDegree( int nRoleID, int nValue ); // ����ĳ�����ѵ����ܶ�
	int		GetFriendIntimacyDegree( int nRoleID );	// ��ȡĳ�����ѵ����ܶ�
	int		GetLastTimeAllOnLine( int nRoleID );	// ��ȡ��ĳ�����ѵ����һ�ι�ͬ����ʱ��
private:
	int		SetRefuseAll( unsigned char nFlag ) ;
	int		GetEarlyestEnemyNoLocked();			
};

// ��������ף��������Ϣ
struct CBlessExpInfo
{
public:
	int mTimes;			// ���ٴ�������
	int mOgreNum;		// ��������İٷֱ�
public:
	CBlessExpInfo( )
	{
		mTimes = 0;
		mOgreNum = 0;
	}
};
struct CMarriageIntimacy
{
public:
	int mIntimacy;	// �����ٵ���������Ҫ�����ܶ�
	int mItemReduced;// ��Ϊ���ܵĿ��Լ��ٵĵ�������
public:
	CMarriageIntimacy()
	{
		mIntimacy = 0;
		mItemReduced = 0;
	}	
};

#define MAX_MARRIAGEINTIMACY_NUM 20
struct CIntimacyConfig
{
public:
	int mOffLineDays;
	int mDayReduced;
	int mKillReduced;
	int mDisbandReduced; // ��ɢ��ݼ��ٵ����ܶ�
	int mLeaveReduced;	 // �뿪��ݼ��ٵ����ܶ�
	int	mKickReduced;
	int mSwornIntimacy;	// �����Ҫ�����ܶ�	
	int	mTeamIntimacyTime; // ÿ�������������ҵ����ܶ�����һ��
	int mMaxIntimacy;	// ���ܶ�����	
	int mDivorceReduced;// ��Ϊ�����������ܶ�	
	int mSwornTitleID;	// �ƺ�ID
	int mItemCreateSworn;	// ���������Ҫ�ľ���
	int mItemDisbandSworn; // ��ɢ��Ҫ�ľ���
	int mItemKickMember;  // ������Ҫ�ľ���
	int mItemChangeName;  // ��������
	int mMaxDailyDegree;  // ÿ���ȡ���ܶȵ�����
	int mRebuildItemID;	  // �����ݵĵ���ID
	CMarriageIntimacy mMarriageIntimacy[MAX_MARRIAGEINTIMACY_NUM];
public:
	CIntimacyConfig()
	{
		mOffLineDays = 3;
		mDisbandReduced = 20;
		mKickReduced = 10;
		mDisbandReduced = 20; // �ٷֱ�
		mLeaveReduced = 20;	 
		mKickReduced =10;
		mSwornIntimacy=100;
		mTeamIntimacyTime = 30;
		mDayReduced = 4;
		mMaxIntimacy = 5000;
		mKillReduced = 30;		
		mDivorceReduced = 200;
		mSwornTitleID = 0;
		mItemCreateSworn = 0;
		mItemDisbandSworn = 0;
		mItemKickMember = 0;
		mItemChangeName = 0;
		mMaxDailyDegree = 30;
		mRebuildItemID = 0;
	}
public:
	int InsertMarriageIntimacy( int nIntimacy, int nItemNum )
	{
		for ( int i = 0; i < ARRAY_CNT( mMarriageIntimacy ); ++i )
		{
			if ( mMarriageIntimacy[i].mIntimacy == 0 )
			{
				mMarriageIntimacy[i].mIntimacy = nIntimacy;
				mMarriageIntimacy[i].mItemReduced = nItemNum;
				break;
			}													
		}
		return SUCCESS;
	}
	int GetReducedNumOfMarriageItem( int nIntimacy )
	{
		int tNum = 0;
		for ( int i = 0; i < ARRAY_CNT( mMarriageIntimacy ); ++i )
		{
			if ( nIntimacy >= mMarriageIntimacy[i].mIntimacy && mMarriageIntimacy[i].mItemReduced > tNum )
			{
				tNum = mMarriageIntimacy[i].mItemReduced;
			}													
		}
		return tNum;
	}		  
	int InitializeMarriageIntimacy()
	{
		memset( mMarriageIntimacy, 0, sizeof( mMarriageIntimacy ) );
		mItemCreateSworn = 0;
		mItemDisbandSworn = 0;
		mItemKickMember = 0;
		mItemChangeName = 0;
		return 0;
	}
};
class CFriendBlessConfig
{
public:
	int mLevelInterval;		// û���ټ������ѷ�һ��ף��
	int mOgreNum;			// �����Ѷ���ֻͬ�ȼ��ֵľ���
	int mOgreExpTableID;	// ����ȼ������ģ��ID			
	CBlessExpInfo mBlessExpInfoList[MAX_FRIENDBLESS_NUM];
	int mLevel;				// ���ټ�������ף��
	CIntimacyConfig mIntimacyConfig;
public:
	void SetLevelInterval( int nLevelInterval ){ mLevelInterval = nLevelInterval; }
	int GetLevelInterval(){ return mLevelInterval; }

	void SetOgreNum( int nNum ){ mOgreNum = nNum; }
	int GetOgreNum(){ return mOgreNum; }
	
	void SetOgreExpTableID( int nID ) { mOgreExpTableID = nID; }
	int GetOgreExpTableID(){ return mOgreExpTableID; }

	void SetLevel( int nLevel ){ mLevel = nLevel; }
	int GetLevel(){ return mLevel; }
public:
	int Initialize()
	{
		mLevelInterval = 0;
		mOgreNum = 0;
		mOgreExpTableID = 0;
		memset( mBlessExpInfoList, 0, sizeof( mBlessExpInfoList ) );
		return 0;
	}	
	int Resume(){ return 0; }
	CFriendBlessConfig()
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
public:
	int InsertBlessExpInfo( int nTimes, int nOgreNum );
	int GetBlessExpInfo( int nTimes );
	CIntimacyConfig *GetIntimacyConfig(){ return &mIntimacyConfig; }
};

// ���
struct CSwornMember 
{
public:
	int mRoleID;		//	��ɫID
	int mTeamPos;		//	���������
	int mRoleStatus;
public:
	CSwornMember()
	{
		mRoleStatus = 0;
		mRoleID = 0;
		mTeamPos = 0;
	}
};

// �������
class CSwornTeam
{
public:
	enum
	{
		EROLE_STATUS_OFFLINE = 0,
		EROLE_STATUS_ONLINE = 1,
	};
public:
	typedef lk::vector< CSwornMember, TEAM_NUMBER > SwornMemberList;
public:
	CSwornTeam()
	{
		if ( CObj::msCreateMode )
		{
			Initialize();	
		}			
	}
	~CSwornTeam(){}
public:
	int GetSwornID(){ return mSwornID; }
	void SetSwornID( int nSwornID ){ mSwornID = nSwornID; }
	const char * GetSwornName(){ return mSwornName; }
	void SetSwornName( const char *pName )
	{
		if ( pName != NULL )
		{
			memset( mSwornName, 0, sizeof( mSwornName ) );
			strncpy( mSwornName, pName, sizeof(mSwornName) - 1 );
		}		
	}
	int InsertMember( CSwornMember &rMember )
	{
		mSwornMemberList.push_back( rMember );
		return 0;
	}
	int GetCampID(){ return mCampID; }
	void SetCampID( int nCampID ){ mCampID = nCampID; }
	int Initialize();
	int KickMember( int nRoleID, int nKickedRoleID );
	int LeaveSwornTeam( int nRoleID );
	int DisbandSwornTeam( int nRoleID );
	bool HasMember( int nRoleID );
	int DeleteMember( int nRoleID );	
	int FindFirstPos();	// ������ѡ���ϴ�
	int GetTeamPos( int nRoleID );
	int ChangeRoleStatus( int nRoleID, int nStatus );
	int GetOnLineNum( );
	int SetFromPB( PBSwornTeam &rSwornTeam );
	int CreateTlvPB( PBSwornTeam &rSwornTeam );
	int GetRoleIDList( int *pRoleIDList, int &rNum );
	int GetNumber(){ return mSwornMemberList.size(); }
	SwornMemberList *GetSwornMember(){ return &mSwornMemberList; }
	int GetMaxPos();	// ��ȡ���һλ���λ��
	int ChangePos( );// ��Ϊ�뿪���ı���λ
public:
	char mSwornName[NAME_LENGTH];		// �����������
	SwornMemberList mSwornMemberList;	// ��ݳ�Ա�б�
	int	mSwornID;						// �������ID(�����ɫID)
	int mCampID;					// ��Ӫ
};