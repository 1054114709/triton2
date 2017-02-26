#pragma  once
#include "corpstype.h"
#include "corps.h"
#include "family.h"
#include "familytype.h"
#include "shm.h"
#include "lk_hashmap.h"
#include "gateobj_define.h"
#include "corpsinfo_pb.hxx.pb.h"   
#include "entity.h"



#include "union.h"



//#include "gatelogic.h"	
//
//using namespace GateServer;	

// ����������Ϣ
struct CCorpsConfigInfo 
{
	int mLevel;					// �ȼ�
	int mFamilyNumLimit;		// ÿһ���ȼ��¼����������
	int mGloryLimit;			// ��ҫ����
	int	mGeneralNumLimit;		// ��ǰ�ȼ���ǰ�潫����������
	int mCounSellorNumLimit;	// ��ǰ�ȼ��¾�ʦ����������
	int	mPvPStarScore;			// ��������һ�Ǽ���Ҫ��pvp����	
	int	mGloryLevelupNeeded;	// ������������һ����Ҫ����ҫ
	int mMoneyLevelupNeeded;	// ������������һ����Ҫ�ļ����Ǯ	
	int mBossRefineValueLimit;	// boss����ֵ���� 
	int	mBossCDLimit;			// ����boss��cd
};  

// �������Ե�������Ϣ
struct CCorpsPropertyConfigInfo 
{
	int mContributePerGold;
	int mScorePerFight;			// pvpÿʤһ���Ļ���
	int mGloryPerFight;			// ÿʤ��һ����ȡ����ҫֵ
	int mExpPerGlory;			// ÿ����ҫֵ��Ҫ�ľ���ֵ
	int mExploitPerGlory;		// ÿ����ҫֵ��Ҫ�Ĺ�ѫֵ
	int mNpcGlory;				// ռ��npc��ÿ�������ȡ����ҫ
	int mNpcMoney;				// ռ��npc��ÿ�������ȡ�Ľ�Ǯ
	int mChallangeMoney;		// ��ս������
	int mChallangeTimesOfDay;	// ÿ�����ս���� 
};


class CCorpsConfig
{
public:
	typedef lk::hash_map< int, CCorpsConfigInfo, CORPS_LEVEL_LIMIT > CorpsConfig;
private:
	CorpsConfig mConfigList;
	CCorpsPropertyConfigInfo mPropertyConfig;
public:
	CCorpsConfig( )
	{
		if ( CObj::msCreateMode )
		{	
			Initialize();
		}
		else
		{			

		}	
	}
	~CCorpsConfig(){ }
public:
	int Initialize( )
	{
		mConfigList.initailize();
		memset( &mPropertyConfig, 0, sizeof( mPropertyConfig ) );
		return 0;
	}	
	int Resume( ){ return 0; }
public:
	// ����һ������������Ϣ
	int InsertCorpsConfig( CCorpsConfigInfo& rCorpsConfig );
	
	// ���ü���Ļ�����������
	int SetCorpsPropertyConfig( CCorpsPropertyConfigInfo &rPropertyConfig );

	// ��ȡĳ���ȼ��ľ��ŵ�������Ϣ
	int GetCorpsConfigByLevel( int nLevel, CCorpsConfigInfo& rCorpsConfig );
	
	// ��ȡĳ���ȼ��¾��ŵļ�����������
	int GetFamilyNumLimitByLevel( int nLevel, int &rFamilyNum );
	
	// ��ȡĳ���ȼ��¾��ŵ���ҫ����
	int GetCorpsGloryLimitByLevel( int nLevel, int &rGlory );
	
	// ��ȡĳ���ȼ�����ǰ�潫������������
	int GetGeneralNumLimitByLevel( int nLevel, int &rGeneralNum );
	
	// ��ȡĳ���ȼ��¾��ŵľ�ʦ��������
	int GetCounSellorNumLimitByLevel( int nLevel, int &rCounSellorNum );
	
	// ��ȡĳ�Ǽ�����������һ�Ǽ�����Ҫ��pvp����
	int GetPvPStarScore( int nLevel, int &rPvPScore );
	
	int GetCorpsRefineValueLimitByLevel( int nLevel, int &rRefineValue); 

	// ���ĳ���ȼ��µ�baoss   cd
	int GetCorpsBossCDLimit( int nLevel, int &rBossCD );

	// ��ȡĳ���ȼ�����һ�ȼ�����Ҫ����ҫ����
	int GetGloryLevelupNeeded( int nLevel, int &rGlory );
	
	// ��ȡ����һ�𶧵Ĺ��׶�
	int GetContributePerGold();
	
	// ��ȡÿʤ��һ���Ļ���
	int GetScorePerFight();
	
	// ��ȡÿʤ��һ����ȡ����ҫֵ
	int GetGloryPerFight(){ return mPropertyConfig.mGloryPerFight; }
	
	// ��ȡĳ���ȼ�����һ�ȼ���Ҫ�Ľ�Ǯ
	int GetMoneyLevelUpNeeded( int nLevel, int &rMoney );
	
	// ��ȡÿ����ҫֵ��Ҫ�ľ���ֵ
	int GetExpPerGlory(){ return mPropertyConfig.mExpPerGlory; }
	
	// ��ȡÿ����ҫֵ��Ҫ�Ĺ�ѫֵ
	int GetExploitPerGlory(){ return mPropertyConfig.mExploitPerGlory; } 
	
	// ��ȡnpc��ÿ�������ȡ�Ľ�Ǯ
	int GetNpcMoney(){ return mPropertyConfig.mNpcMoney; }
	
	// ��ȡnpc��ÿ�������ȡ����ҫ
	int GetNpcGlory( ){ return mPropertyConfig.mNpcGlory; }

	// ��ȡ��ս����
	int GetChallangeMoney() { return mPropertyConfig.mChallangeMoney; }

	// ��ȡ��ս��ÿ�մ���
	int GetChallangeTimesOfDay() { return mPropertyConfig.mChallangeTimesOfDay; }

	//

};	


class CCorpsManager : public CSingleton< CCorpsManager >
{
public:													     
	typedef lk::hash_map< int, int, SERVER_CAP_CORPS > CorpsList;		/// List of all corps
	typedef lk::vector< int, SERVER_CAP_CORPS > RoomList;				// �����б�
	typedef lk::hash_map< int, int, MAX_UNION_NUM > UnionList;
	
public:
	CCorpsConfig mCorpsConfig;

	CorpsList m_tCorpsList;
	RoomList m_tRoomList;
	UnionList m_UnionList;

public:
	static CSharedMem* mShmPtr; 
	void * operator new( size_t tsize );
	void   operator delete( void *pPointer );			    
	static unsigned int CountSize();
	CCorpsManager();
	~CCorpsManager(){}
	int Initailize( );
	int Resume( );	
public:
	CCorps *GetCorpsByID( int nCorpsID );
	/// ��ȡ�����������
	CCorps *GetCorpsOfPlayer( int nRoleID );
	CCorps *GetCorpsByName( const char *pCorpsName );

	CUnion *GetUnionByID( int nUnionID );
	CUnion *GetUnionOfPlayer( int nRoleID );
	CUnion *GetUnionByName( const char *pUnionName );
	int InsertCoprsInfo( CCorps *pCorps );
	int DeleteCorpsInfo( CCorps *pCorps ); 
	
	CCorpsConfig *GetCorpsConfig(){ return &mCorpsConfig; } 
		
	// ��ȡ���ŵĳ�Ա�б�
	void GetCorpsMemberList( CCorps *tpCorps, int *pMemberList, int &nNum, int nExceptFamiyID = 0, int nExceptRoleID = 0 );
	
	// ͨ������ID��ȡ���ŵĳ�Ա�б�
	void GetCorpsMemberListByFamilyID( CCorps *tpCorps );
	
public:
	// ��������
	int OnEventCreatCorps( int nRoleID, const char *pCorpsName, int nCorpsID, int nCorpsColor );
	
	// ����������
	int OnEventApplyCorps( int nApplyingID, CCorps *pCorps, FamilyData &pbFamilyData );
	
	// ������
	int OnEventReplyApply( int nReplyingID, int nFamilyID, int nResult, int &nApplyingID );
	
	// �������������
	int OnEventInviteFamily( int nCorpsRooterID, CFamily *pFamily );
	
	// �𸴾�������
	int OnEventReplyCorpsInvite( int nInvitedID, CCorps *pCorps, int nResult );
	
	// ��ɢ����
	int OnEventDisbandCorps( int nRooterID, int *pMemberList, int &nMemberNum );
	
	// ��ȡ���ŵ�������Ϣ
	int OnEventGetCorpsProperty( int nRooterID, CorpsProperty &pbCorpsInfo );
		
	// ��ȡĳ������ĵ���Ϣ
	int OnEventGetCorpsMemberInfo( int nRoleID, PBCorpsMemberList &pbCorpsMemberList );
	
	// �ı�Ҿ��ŵĹ�����Ϣ
	int OnEventChangeCoprsNotice( int nRoleID, const char *pNotice );	
	
	// ת�ô󽫾�ְλ
	int OnEventAppointCorpsHeader( int nHeaderID, int nMemberID );
	
	// �߳�����
	int OnEventKickFamilyOfCorps( int nRooterID, int nFamilyID );
	
	// �뿪����
	int OnEventLeaveCorps( int nRoleID );
	
	// ��ȡ�����б���Ϣ
	int OnEventListCorps( int nRoleID, int nCountryID, CorpsInfoList &pbCorpsList, int nCurPage, int &rTotalPage );	
	
	// ��ȡ���ŵ�����	
	int OnEventListCorpsApply( int nRoleID, PBCorpsApplyList &pbCorpsApply );
	
	// ������ŵ���Ϣ
	int OnEventClearCorpsInfo( CCorps *pCorps );
	
	// ȡ����ɢ���ŵ���Ϣ�ظ�
	int OnEventCancelCorpsDisband( int nRoleID );
	
	// ��������������Ϣ
	int OnEventClearCorpsApply( int nRoleID );

	
	


	//int OnAttachBattleCity( int nMapID, int nCorpsID );
	//int OnDeleteBattleCity( int nMapID );
	//int OnFindBattleCity( int nMapID, int& nCorpsID );
	int OnGetBattleMapList( int* npList, int* npCorpsList, int& nNum, int nServerID );

	void InsertRoom( int nCorpsID ){ m_tRoomList.push_back( nCorpsID ); }
	int OnGetRoomList( int* vpList, int& nSize );
	bool HasRoom( int nCorpsID );
	int OnDelRoom( int nCorpsID );


	//void SendCorpsNpcList( int nServerID );

	void SendCorpsNpcSingle( int nServerID, int nNpcID, int nCorpsID, bool bAdd = true );

	// �������ս��״̬
	int ClearCorpsBattleStatus( int nCorpsID );
	
	// ���þ���ְλ
	int OnEventSetCorpsMemberPost( int nManagerID, int nMemberID, int nPost, int &rOldPost );

	// ���׽�Ǯ
	int OnEventContributeMoney( int nMemberID, int nMoney );

	// ���Ľ�Ǯ
	int OnEventConsumeMoney( int nManagerID, int nMoney );

	// ��������
	int OnEventLevelUPCorps( int nManagerID, int &rLevel, int &rMoney );

	// ���Ӽ�����ҫ
	int OnEventAddCorpsGlory( int nCorpsID, int nGloryValue );

	// ���ټ�����ҫ
	int OnEventReduceCorpsGlory( int nCorpsID, int nGloryValue, bool &rLevelDown );

	// ���Ӽ���pvp���ֵĽӿ�
	int OnEventAddCorpsPVPScore( int nCorpsID, int nScoreValue, bool &rLevelUP );
	
	// ���ó�Ա�ƺ�
	int OnEventSetCorpsMemberName( int nManagerID, int nMemberID, const char *pName );
	
	// ������׽�Ǯ
	int OnEventFamilyContributeMoney( int nMemberID, int nMoney );

	// ���Ž���
	int OnEventCreateUnion( int vHeadID, int *vCorpsID, int vNumber, char *vUnionName, char *vUnionNotice, int vCharID );

	// �����������
	int OnEventApplyUnion( int nApplyingID, CUnion *pUnion, PBCorpsBasicInfo &Info );

	// ������
	int OnEventReplyUnionApply( int nReplyingID, int nCorpsID, int nResult, PBCorpsBasicInfo &vCorpsInfo );

	// ������ż�������
	int OnEventInviteCorps( int nCorpsRooterID, CCorps *pInviteCorps );

	// ����������
	int OnEventReplyUnionInvite( int nInvitedID, CUnion *pUnion, int nResult );

	// ��ɢ����
	int OnEventDisbandUnion( int nRooterID );	

	// �ı������Ĺ�����Ϣ
	int OnEventChangeUnionNotice( int nRoleID, const char *pNotice );	

	// �߳�����
	int OnEventKickCorpsOfUnion( int nRooterID, int nCorpsID );

	// �뿪����
	int OnEventLeaveUnion( int nRoleID );	

public:
	/*********���ݿ���صĲ���***********/
	// �������ŵ����ݿ���Ϣ
	int CreatCorpsDBInfo( CCorps *pCorps );

	// ������������
	int CreatUnionDBInfo(CUnion* pUnion);

	// ���¾��ŵ����ݿ���Ϣ
	int UpDateCorpsDBInfo( CCorps *pCorps );

	// ɾ�����ŵ����ݿ���Ϣ
	int DeletCorpsDBInfo( CCorps *pCorps );

	// �������еľ�����Ϣ
	void UpDateAllCorpsDBInfo( bool bDirectSave = false );
	
	// ɾ����ɢʱ���ѵ��ľ���
	void DeleteCorpsOnDisbandTime();
	
	// ��ȡ������ӵ��ĳ��Ȩ�޵����ߵ�ְλ��ߵĳ�Ա
	CGatePlayer *GetManagerOfRight( CCorps *tpCorps, int nRight );

	// �������������ݿ���Ϣ
	int UpdateUnionDBInfo( CUnion *pUnion );

	// ɾ�����������ݿ���Ϣ
	int DeleteUnionDBInfo( CUnion *pUnion );

	// �������е�������Ϣ
	void UpDateAllUnionDBInfo( );
	
	// ���ݾ���ID��ɢ����
	void DisbandCorps( CCorps *pCorps );
	
	// ���б����Ƴ�����
	int RemoveCorpsFromList( int nCorpsID );
	
	// ɾ�����Ų��ҷ���֪ͨ
	void DeleteCorpsWithNotify( CCorps *pCorps );
	
	// ɾ�����˲��ҷ���֪ͨ
	void DeleteUnionWithNotify( CUnion *pUnion, int nRooterID );
};
