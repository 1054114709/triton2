#pragma  once
#include "corpstype.h"
#include "object.h"
#include "family.h"
#include "lk_hashmap.h"
#include "servertool.h"
#include  "corpsinfo_pb.hxx.pb.h"
#include "coretype.h"
#include "gateobj_define.h"
#include "protype.h"
#include "taskmodule.h"


struct NpcStatus;

enum EChallegeEvent
{
	EVENT_ADD = 0,
	EVENT_DEL,
	EVENT_CLEAR,
};

enum EChallegeType
{
	TYPE_SEND = 0,
	TYPE_REC,
};

struct CCorpsFamiyInfo
{ 
	int mContribute;
};

enum ECorpsStateTag
{
	ST_Occupy	= 0x01,	//ռ���˳ǳ�
	ST_InBid	= 0x02,	//�����˾���
	ST_WaitBtl	= 0x04,	//�ȴ���ս
	ST_InBtl	= 0x08,	//ս����
	ST_Single	= 0x10, //�����ľ���
	ST_Union	= 0x20, //��������
	ST_CityMap	= 0x40,	//���ǵ�ͼ, ��ָ����ʾȫ��
	ST_AllState	= 0xFF, //����״̬
};
class CCorpsRepetion
{
private:
	int mCorpsBossID;
	int mStartTime;
	bool mIsOpen;
	KEY_TYPE mKey;

public:
	CCorpsRepetion()
	{
		mCorpsBossID = 0;
		mStartTime = 0;
		mIsOpen = false;
		mKey = INVITED_KEY_VALUE;
	}
public:
	void SetCorpsBossID( int nBossID)
	{
		mCorpsBossID = nBossID;
	}
	int GetCorpsBossID(){ return mCorpsBossID ;}

	void SetStartTime()
	{
		mStartTime = time(NULL);
	}

	int GetStartTime(){ return mStartTime;}

	void SetCorpsIsOpen( bool nIsOpen)
	{
		mIsOpen = nIsOpen;		
	}
	bool IsOpen(){ return mIsOpen;}
	void SetRepetionKey( KEY_TYPE vKey) { mKey  = vKey;}
	KEY_TYPE GetRepetionKey() { return mKey; }
};

class CCorps:public CObj
{
public:
	enum ECORPS_SAVESTATUS
	{
		CORPS_INFONOCHANGE = 0 ,			// ������Ϣû�иı�		
		CORPS_ALLINFOCHANGED,				// ������Ϣ���ı�
	};
		
	// ���Ų�����һЩ������
	enum
	{
		EM_MONEYNOTENOUGH	=	1,			// ��Ǯ����
	};
public:
	CCorps( )
	{
		if ( msCreateMode )
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}
	~CCorps( ){ }
	virtual int Initialize();
	virtual int Resume(){ return 0; } 
public:
	typedef lk::hash_map< int, CCorpsFamiyInfo, MAX_CORPS_FAMILYNUM >  FamilyList;
	typedef lk::hash_map< int, int, MAX_CORPSAPPLY_NUM >			   ApplyList;
	typedef lk::hash_map< int, int, MAX_CORPS_BOSS_NUM >			   CorpsBossList;

	// ��ս��Ա
	typedef lk::vector< int, CORPS_BATTLE_NUM > BattleList;
	// ��ս�б�
	typedef lk::vector< int, SERVER_CAP_CORPS > ChallegeList;

	
	enum EFamilyList
	{
		FAMILYLISTFULL	 = 1,
		FAMILYHASEXIST	 = 2,
	};	
	enum ECorpsApplyList
	{
		APPLYLISTFULL	 = 1,	
	};	
	enum
	{
		EM_CORPS_STATUS_ALIVE	= 0,	///< ����״̬����
		EM_CORPS_STATUS_DISBAND	= 1,	///< ���Ŵ��ڽ�ɢ״̬
	};
	
public:
	FamilyList		m_tFamilyList;										// �����еļ����б�
	ApplyList		m_tApplyList;										// �����е������б���Ϣ
	int				m_nRooterID;										// �󽫾���ɫID
	char			m_sRooterName[NAME_LENGTH];							// �󽫾�����
	int				m_nCorpsID;											// ����ID
	char			m_sCorpsName[MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES];	// ��������
	organization_t 	m_tOfficers[MAX_OFFICER_NUM];						// ְλ��ϵ	
	int				m_nCountryID;										// ����ID
	char			m_sBulletin[CORPS_BULLETIN_LENGTH*MAX_UTF8_BYTES];	// ����
	int				m_nCorpsMoney;										// ���Ž�Ǯ
	int				m_nCorpsStatus;										// ����״̬
	int				m_nCorpsDisbandTime;								// ���Ž�ɢʱ��
	int				m_nSaveStatus;
	
	int				m_nCorpsLevel;										// ���ŵȼ�	
	int				m_nCorpsGlory;										// ������ҫ	
			
	int				m_nPVPWinNum;										// pvpʤ���ĳ���
	int				m_nPVPFailedNum;									// pvpʧ�ܵĳ���
	int				m_nPVPScore;										// pvp����
	int				m_nPVPStarLevel;									// pvp�Ǽ�	
	int				m_nBidNpcID;										// ���۱�����NPCID
	int				m_nBidMoney;										// ���뾺�����ĵĽ�Ǯ
	int				m_nVictoryTimes;									// սʤ����
	int				m_nLoserTimes;										// ս�ܶ��Ǵ���
	bool			m_bCanBattle;										// �Ƿ���ս���ʸ�
	int				m_nCampID;											// ��ӪID
	int				m_nBattleCity;										// �ǳ�ID
	KEY_TYPE		m_BattleKey;										// ս��key

	int				m_WarRank;
	int				m_WarStatus;
	int				m_EnemyCorpsID;										// ��ս����
	BattleList		m_BattleList;										// ��ս��Ա�б�
	int				m_UnionID;											// ����ID
	int				m_BOSSRefineValue;									// ����boss����ֵ
//	int				m_RefineValueLimit;									// ����ֵ����
	int				m_nCorpsBossScore;								//  ����boss����
	int				m_nCorpsCollectActive;								// ���Ųɼ���Ծ��
	

	// ��ս������
	char			m_RoomName[ NAME_LENGTH ];
	int				m_RoomMoney;
	ChallegeList	m_ChallegeList;
	ChallegeList	m_SendChallegeList;
	int				m_RoomState;
	
	int				m_nCorpsWelfareGetTime;

	char			m_sTmpUnionName[MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES];	// ��������
	char			m_sTmpUnionNotice[CORPS_BULLETIN_LENGTH*MAX_UTF8_BYTES];	// ����
	int				m_OtherCorpsID[ MAX_OTHER_UNION ];
	bool			m_InviteIdle;
	int				m_Color;											// ������ɫ	
	int				m_nForbidTime;										// ��ֹ����������ʱ��
	
	CLeagueShopsManager	m_tCorpsLeagueShop;								// ���ŵ��̵���Ϣ

	CorpsBossList	m_CorpsBossList;									// ����boss���
	CCorpsRepetion  m_CorpsRepetion;									// ���Ÿ���


	CGroupPublishInfo mCorpsPublishTask;								// ���ŷ���
public:

	void OnNewDayCome()
	{
		mCorpsPublishTask.OnNewDayCome();
	}

	void OnNewWeekCome()
	{
		mCorpsPublishTask.OnNewWeekCome();
	}

	// set & get
	inline void SetColor( int nColor ) 
	{ 
		m_Color = nColor; 
		SetSaveStatus( CORPS_ALLINFOCHANGED ); 
	}
	inline int  GetColor() { return m_Color; }

	void SetRoomName( const char* vpName )
	{ 
		if ( vpName == NULL ) return ;
		strncpy( m_RoomName, vpName, sizeof( m_RoomName ) - 1 );
	}
	char* GetRoomName(){ return m_RoomName; }

	void SetRoomMoney( int nMoney ) 
	{
		 m_RoomMoney = nMoney;
		 SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	int  GetRoomMoney(){ return m_RoomMoney; }

	void SetRoomState( int nState ) { m_RoomState = nState; }
	int  GetRoomState(){ return m_RoomState; }

	void SetEnemyCorpsID( int nCorpsID ) { m_EnemyCorpsID = nCorpsID; }
	int  GetEnemyCorpsID(){ return m_EnemyCorpsID; }

	void SetWarRank( int nRank ) { m_WarRank = nRank; }
	int  GetWarRank(){ return m_WarRank; }

	void SetWarStatus( int nStatus ) { m_WarStatus = nStatus; }
	int  GetWarStatus(){ return m_WarStatus; }

	// ���úͻ�ȡ����ID
	void SetCorpsID( int nCorpsID ){ m_nCorpsID = nCorpsID; }
	int	 GetCorpsID(){ return m_nCorpsID; }	 

	void SetCorpsCamp( int nCampID ) 
	{	
		m_nCampID = nCampID; 
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	int  GetCorpsCamp() { return m_nCampID; }

	void SetBattleCity( int nCity );

	int  GetBattleCity() { return m_nBattleCity; }

	void SetBattleKey( KEY_TYPE nKey )
	{
		 m_BattleKey = nKey;
	}
	KEY_TYPE GetBattleKey(){ return m_BattleKey; }
	
	// ����&��ȡ���Ÿ�������ȡʱ��
	void SetCorpsWelfareGetTime( int nTime ){ m_nCorpsWelfareGetTime = nTime; }
	int	 GetCorpsWelfareGetTime(){ return m_nCorpsWelfareGetTime; }
	
	// ��ȡ���ŵ�npc��Ǯ
	int GetCorpsWelfare( int nNpcID, int &rNpcMoney, int &rNpcGlory, bool bRefresh = true );	
	
	// ���úͻ�ȡ��������
	void SetCorpsName( const char  *pName )
	{ 
		strncpy( m_sCorpsName, pName, MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES -1 );
		m_sCorpsName[MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES -1] = '\0';		
	}
	
	// ���&��ȡ������ҫ
	void SetCorpsGlory( int nGlory )
	{ 
		m_nCorpsGlory = nGlory; 
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	int GetCorpsGlory(){ return m_nCorpsGlory; }	  
	
	// ����&��ȡpvp����
	void SetPVPScore( int nScore )
	{
		 m_nPVPScore = nScore;
		 SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	int	 GetPVPScore(){ return m_nPVPScore; }
	
	// ����&��ȡpvp�Ǽ�
	void SetPVPStarLevel( int nLevel )
	{
		m_nPVPStarLevel = nLevel;
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	int	 GetPVPStarLevel( ){ return m_nPVPStarLevel; }	
	
	const char *GetCorpsName( ){ return m_sCorpsName; }
	
	const char *GetCorpsNameShow()
	{
		// �ַ���������ʾ
#ifdef CHARSET_SHOW_GBK
		static char tCorpsName[ MAX_CORPSNAME_LENGTH ] = {0};
		int nNameLen = sizeof(tCorpsName)-1;
		charset_convert( "utf8", "gbk", (char*)m_sCorpsName, strlen( m_sCorpsName ),
			tCorpsName, (size_t*)&nNameLen );
		return tCorpsName;
#else
		return m_sCorpsName;
#endif		
	}
	
	// ��ȡ���ŵ��̵���Ϣ
	CLeagueShopsManager *GetCorpsShop(){ return &m_tCorpsLeagueShop; }
	
	void SetBidNpcID(int nNpcID)
	{
		 m_nBidNpcID = nNpcID;
		 SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	int GetBidNpcID(){ return m_nBidNpcID; }

	void SetBidMoney(int nMoney)
	{
		m_nBidMoney = nMoney;
	}
	int GetBidMoney(){ return m_nBidMoney; }

	// ����&��ȡ����ʤ���ĳ���
	void SetVictoryNum( int nNum )
	{
		m_nVictoryTimes = nNum;
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}	
	void IncVictoryTimes()
	{
		m_nVictoryTimes += 1;
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	
	void IncLoserTimes()
	{
		m_nLoserTimes += 1;
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	void SetLoserTimes( int nTimes )
	{
		m_nLoserTimes = nTimes;
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	
	int GetVictoryTimes(){ return m_nVictoryTimes; }
	int GetLoserTimers(){ return m_nLoserTimes; }

	bool GetCanBattle(){ return m_bCanBattle; }
	void SetCanBattle( bool bFlag )
	{
		m_bCanBattle = bFlag;
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	
	// ���úͻ�ȡ�󽫾�ID
	void SetRooterID( int nRooterID ){ m_nRooterID = nRooterID; SetSaveStatus( CORPS_ALLINFOCHANGED ); }
	int	 GetRooterID( ){ return m_nRooterID; }
	
	// ���úͻ�ȡ�󽫾�����
	void SetRooterName( const char *pName )
	{ 
		strncpy( m_sRooterName, pName, NAME_LENGTH -1 );
		m_sRooterName[ NAME_LENGTH -1] = '\0'; 
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	const char *GetRooterName( ){ return m_sRooterName; }	 	
	
	// ���úͻ�ȡ����ID
	void SetCorpsCountryID( int nCountryID ){ m_nCountryID = nCountryID;  }
	int	 GetCorpsCountryID( ){ return m_nCountryID; }
	
	// ���úͻ�ȡ����ȼ�
	void SetCorpsLevel( int nCorpsLevel ){ m_nCorpsLevel = nCorpsLevel; SetSaveStatus( CORPS_ALLINFOCHANGED ); }
	int	 GetCorpsLevel(){ return m_nCorpsLevel; }
	
	// ���úͻ�ȡ���Ž�Ǯ
	void SetCorpsMoney( int nMoney )
	{			
		m_nCorpsMoney = nMoney;
		if ( m_nCorpsMoney > MAX_FAMILYCORPS_MONEY || m_nCorpsMoney < 0 )
		{
			m_nCorpsMoney = nMoney;
		}
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	
	int	 GetCorpsMoney( ){ return m_nCorpsMoney; }
	
	// ���úͻ�ȡ����״̬
	void SetCorpsStatus( int nStatus ){ m_nCorpsStatus = nStatus; SetSaveStatus( CORPS_ALLINFOCHANGED ); }
	int	 GetCorpsStatus(){  return m_nCorpsStatus; }
	
	// ���úͻ�ȡ���Ž�ɢʱ��
	void SetCorpsDisbandTime( int nDisbandTime ){ m_nCorpsDisbandTime = nDisbandTime; SetSaveStatus( CORPS_ALLINFOCHANGED ); }
	int	 GetCorpsDisbandTime( ){ return m_nCorpsDisbandTime; } 
	
	// ���úͻ�ȡ����
	void SetBulletin( const char *pBulletin )
	{ 
		strncpy( m_sBulletin, pBulletin, CORPS_BULLETIN_LENGTH*MAX_UTF8_BYTES-1 );
		m_sBulletin[CORPS_BULLETIN_LENGTH*MAX_UTF8_BYTES-1] = '\0';
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	const char *GetBulletin(){ return m_sBulletin; }
	
	// ����&��ȡ���ŵĴ洢״̬
	int		GetSaveStatus(){ return m_nSaveStatus; }
	void	SetSaveStatus( int nStatus ){ m_nSaveStatus = nStatus; }


	// ��ȡ&���þ��ŵ�pvp�Ǽ�
	int		GetCorpsPvPStarLevel( ){ return m_nPVPStarLevel; }
	void	SetCorpsPvPSetrLevel( int nLevel ){ m_nPVPStarLevel = nLevel; }

	void SetUnionID( int nUnionID ) { m_UnionID = nUnionID; }
	int  GetUnionID(){ return m_UnionID; }

	void SetBossRefineValue(int nValue)
	{
		if (nValue < 0 )
		{
			m_BOSSRefineValue = 0;
		}else if( nValue > GetCorpsBossRefineValueLimit() )
		{
			m_BOSSRefineValue = GetCorpsBossRefineValueLimit();
		}else{
			m_BOSSRefineValue = nValue;
		}
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}
	int GetBossRefineValue(){ return m_BOSSRefineValue; }

	int GetBossCDCoolTime();

	int GetCorpsBossScore() { return m_nCorpsBossScore; }
	void SetCorpsBossScore( int nScore )
	{
		if ( nScore <= 0 )
		{
			m_nCorpsBossScore = 0;
		}
		else
		{
			m_nCorpsBossScore = nScore;
		}
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}

	int GetCorpsCollectActive() { return m_nCorpsCollectActive; }
	void SetCorpsCollectActive( int nActiveValue )
	{
		if ( nActiveValue <= 0 )
		{
			m_nCorpsCollectActive = 0;
		}
		else
		{
			m_nCorpsCollectActive = nActiveValue;
		}
		SetSaveStatus( CORPS_ALLINFOCHANGED );
	}

	void SetTmpUnionName( const char *pName )
	{ 
		if ( pName == NULL )
			return;
		strncpy( m_sTmpUnionName, pName, MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES -1 );
		m_sTmpUnionName[ MAX_CORPSNAME_LENGTH*MAX_UTF8_BYTES -1 ] = '\0'; 
	}
	const char *GetTmpUnionName( ){ return m_sTmpUnionName; }	

	void SetTmpUnionNotice( const char *pNotice )
	{ 
		if ( pNotice == NULL )
			return;
		strncpy( m_sTmpUnionNotice, pNotice, CORPS_BULLETIN_LENGTH*MAX_UTF8_BYTES -1 );
		m_sTmpUnionNotice[ CORPS_BULLETIN_LENGTH*MAX_UTF8_BYTES -1] = '\0'; 
	}
	const char *GetTmpUnionNotice( ){ return m_sTmpUnionNotice; }

	void AddTmpCorpsID( int vID )
	{
		for ( size_t i = 0; i < ARRAY_CNT(m_OtherCorpsID); i++ )
		{
			if ( m_OtherCorpsID[ i ] == vID )
				return;
			if ( m_OtherCorpsID[ i ] == 0 )
			{
				m_OtherCorpsID[ i ] = vID;
				return;
			}
		}
	}

	void ClearTempUnion(  )
	{
		memset( m_sTmpUnionName, 0, sizeof(m_sTmpUnionName) );
		memset( m_sTmpUnionNotice, 0, sizeof(m_sTmpUnionNotice) );
		memset( m_OtherCorpsID, 0, sizeof(m_OtherCorpsID) );
	}

	void SetInviteIdle( int bInvite ) { m_InviteIdle = bInvite; }
	bool  GetInviteIdle(){ return m_InviteIdle; }

	void SetForbidTime( int nForbidTime ){ m_nForbidTime = nForbidTime;  }
	int	 GetForbidTime( ){ return m_nForbidTime; }
	
	// �������в���һ������
	int InsertFamily( int nFamilyID, CCorpsFamiyInfo &sFamilyInfo );
	
	// ɾ�������е�һ������
	int DeletFamily( int nFamilyID );
	
	// ��ȡ�����еļ������
	int GetFamilyNum(){ return m_tFamilyList.size(); }
	
	// �����ŵļ�������Ƿ��Ѿ�����
	bool CheckMemberFull(){ return m_tFamilyList.size() >= MAX_CORPS_FAMILYNUM;  }
	
	// ��ȡ���ż����б�
	FamilyList & GetFamilyList(){ return m_tFamilyList; }
	
	// ����б����Ƿ���ĳ������
	bool CheckHasFamily( int nFamilyID );
	
	// ��������б����Ƿ���ĳ������
	bool ChekcFamilyApply( int nFamilyID );
	
	// ����һ�������������Ϣ
	int InsertFamilyApply( int nFamilyID, int nApplyingID );
	
	// ɾ��һ�������������Ϣ
	int DeletFamilyApply( int nFammilyID );
	
	// �ж������б��Ƿ��Ѿ�����
	bool CheckApplyListIfFull(){ return m_tApplyList.size() >= MAX_CORPSAPPLY_NUM; }	
	
	// ��þ��ŵ�����
	int GetCorpsMemberNum();
	
	// ��ȡ���ŵĳ�Ա��Ϣ�б�
	void GetCorpsMemberList( PBCorpsMemberList &pbCorpsMember );
	
	// ��ȡ���ŵ�������Ϣ
	void GetCorpsBasicInfo( PBCorpsBasicInfo &pbBasicInfo );
	
	// ��ȡ�����������
	int GetApplyingRoleID( int nFamilyID );
	
	// ��þ��ŵ������б�
	int GetApplyList( PBCorpsApplyList &pbCorpsApply );
	
	// ���þ��ų�Ա��Ϣ��PB�ṹ
	int CreatCorpsFamilyPBInfo( PBCorpsFamilyInfoList &pbCorpsFamilyInfo );
	
	// ��PB�ṹ�������ŵļ����Ա��Ϣ
	int GetCorpsFamilyInfoFromPB( PBCorpsFamilyInfoList &pbCorpsFamilyInfo );

	// ��PB���ݴ������ŵķ�����Ϣ
	int GetCorpsPublishInfoFromPB( PBCorpsPublishInfo &pbPublishInfo );

	// �������ŷ�����Ϣ��PB��Ϣ
	int CreateCorpsPublishDB(PBCorpsPublishInfo &pbPublishInfo);
	
	// ��ȡ���������
	int GetApplyNum( ){ return m_tApplyList.size(); }
	
	// �������ľ�����Ϣ
	int ClearCorpsInfoOfFamily( );
	
	// �����Ž�ɢʱ���Ƿ��ѵ�
	bool CheckCorpsDisbandTime( );
	
	// ��վ��������б�
	int ClearCorpsApplyList(){ m_tApplyList.clear(); return 0; }
	
	// ��ȡ��ҵľ���ְλ
	int GetMemberPost( int nMemberID, int &rPost );

	int MakeCorpsPbPropert( CorpsProperty* vpProperty );

	int InsertBattleMember( int nRoleID );
	int ClearBattleList();
	int GetBattleListSize();
	int GetBattleMemberList( int* vpList, int& nSize );
	bool IsInBattleList( int nRoleID );
	int DelBattleRole( int nRoleID );

	int HasOwnThisMap( int nMapID );

	// ���npc��������ȡʱ�� 
	int GetNpcWelfareTime( int nNpcID, int &rTime );
	
	// ����npc��������ȡʱ��
	int SetNpcWelfareTime( int nNpcID, int nTime );

	int ClearNpcBattleInfo( int nNpcID );

	// ���ؾ����Ƿ���ս���У�nStateType��ʾ��ѯ����
	bool IsInBattle(int nBattleType, int nStateType);

	int GetPBBuffer( PBCorpsBattleList* npList, bool bAll = true );
	int SetFromPB( PBCorpsBattleList* npList );

	inline NpcStatus* GetNpcState(int _NpcID);
	
	int GetMapList( int* npMapList, int& nNum );
	int GetMap( int nNpcID );
	

	//���ñ�����ս���б���ʧЧfrom 2010.6.13
	int SetNpcBattleStatus( int nNpcID, int nNpcStat, int nWarStat ) {return 0;};

	// �����Ƿ��������
	bool CanCorpsLevelUP( );
	
	// ��ȡ������Ҫ�Ľ�Ǯ����ҫ
	int GetLevelCondition( int &rMoney, int &rGlory );

	// �Ƿ��Ǵ���
	inline bool IsCoreOwner( ) { return m_nBattleCity == COUNTRY_MAP_CHANGAN; }

	// �Ƿ���һ��ռ��
	inline bool IsNormalOwner( )
	{ 
		return ( m_nBattleCity == COUNTRY_MAP_WUJI || m_nBattleCity == COUNTRY_MAP_CHECHI 
			|| m_nBattleCity == COUNTRY_MAP_BAOXIANG || m_nBattleCity == COUNTRY_MAP_NVER ) ;
	}

	// �Ƿ���ִ������
	inline bool IsOwner( ) { return IsCoreOwner( ) || IsNormalOwner( ); }	

	// �Ƿ���Ծ��� [12/12/2009 Macro]
	bool CanBidThisMap( int nMapID );
	
public:	
	// ��������
	int	LevelUPCorps( int &rLevel, int &rMoney );
	
	// ְλ����
	int SetMemberPost( int nRoleID, int nPost, int &rOldPost );
	
	// ���Ӿ�����ҫ
	int AddCorpsGlory( int nValue, int nType = 0 );
	
	// ���پ�����ҫ
	bool ReduceCorpsGlory( int nValue, int nType = 0 ); 
	
	// ���׾��Ž�Ǯ
	int ContributeCorpsMoney( int nMoney, int nType = 0 );
	
	// ����pvp����
	bool AddPvPScore( int nValue, int nFailedCorpsLevel );
	
	// ����pvp����
	bool ReducePvPScore( int nValue, int nWinCorpsLevel );
	
	// �ж�ĳ������Ƿ���Ȩ��
	bool HasPost( int nRoleID, int nCorpsPost );
	
	// ��ȡĳ��ְλ��Ա�б�
	int GetMemberListOfPost( int *pList, int& rNum, int nPost, int nType );
	
	// ���ľ��Ž�Ǯ
	int ConsumeCorpsMoney( int nMoney, int nType = 0 );
	
	// ��ȡĳ��ְλ�ĸ���
	int GetPostNum( int nPost );
	
	// ��ȡĳ��ְλ����������
	int GetPostLimitNum( int nPost );
	
	// ���Ӿ��ų�Ա�Ĺ��׶�
	int AddCorpsMemberContribute( int nMemberID, int nContribute );
	
	// ���Ӿ��ų�Ա�Ĺ��׶�
	int SetCorpsMemberName( int nMemberID, const char *pName );
	
	// ������ҵĹ��׶�
	int SetCorpsContribute( int nMemberID, int nContribute );

	// ��ս�б���
	
	// ����Ƿ���ĳ����Ա
	bool HasMember( int nRoleID );
	
	// ��ȡ���˵ľ��Ź��׶�
	int GetMemberContribute( int nRoleID );
	
	// ����&��ȡ�����Ա�ľ���
	int	GetMemberExp( int nRoleID );

	// ���ӳ�Ա�ľ��� 
	void AddMemberExp( int nRoleID, int nExp ); 

	// ���ó�Ա����
	void SetMemberExp( int nRoleID, int nExp ); 

	// ��ȡ��ԱAPֵ
	int GetMemberAP( int nRoleID );

	// ���ó�ԱAPֵ
	void SetMemberAP( int nRoleID, int nAP );

	// ���ӳ�ԱAP
	void AddMemberAP( int nRoleID, int nAP );
	
	// ĳ��ְλ�Ƿ���ĳ��Ȩ��
	bool PostHasRight( int nPost, int nRight );
	
	// ��Ա�Ƿ���ĳ��Ȩ��
	bool MemberHasRight( int nRoleID, int nRight );
	
	// �г���ĳ��Ȩ������б�
	int ListMemberOfRight( int *pIDList, int *pPostList, int *pContributeList, int &rNum, int nRight );
	
	// ��ȡ��ҵļ���
	CFamily *GetMemberFamily( int nMemberID );

	// ��ȡ���ŷ�����Ϣ

	CGroupPublishInfo *GetCorpsPublishInfo(){ return &mCorpsPublishTask;}
	
	// ��ʼ�������б�
	int InitialOrgnization(  );
	
	// ����Ǯ�Ƿ��㹻
	bool CheckMoneyEnough( int nMoney );
	
	// �������Ƿ��ܹ�ʹ��ĳ���̵�
	int CheckCorpsCanUseShop( int nNpcTmpID, int nWarCityMap );
	
	// ��ȡʹ���̵������
	int GetCorpsShopErrcode( int nErrcode, int &rShopsErrcode );

	// ������ƺŴ���
	int UpdateNationTitle( int nMapID, bool bIsAdd );

	// �õ���������ֵ
	int GetPower();
	

	//�ṹ���洢NPC������Ϣ��DB��DLC@2010-06-07
	//int SaveBattleBidListToDB();
	//int LoadBattleBidListFromDB();


	int CheckIfHasBidRight(int _RoleID, int _MapID);

	//���bosstimes
	void ChangeCorpsBossTimes(int nBossID, int nTimes );

	//
	int GetCorpsBossTimes( int nBossID );

	//
	int GetCorpsBossRefineValueLimit( );

public:
	template< typename TYPE_T >
	void AddChallege( TYPE_T& nList, int nCorpsID )
	{
		nList.push_back( nCorpsID );
	}

	template< typename TYPE_T >
	void ClearChallege( TYPE_T& nList )
	{
		nList.clear();
	}

	template< typename TYPE_T >
	int GetChallegeList( TYPE_T& nList,  int* vpList, int& nSize )
	{
		if ( vpList == NULL )
		{
			return -1;
		}

		int tSize = nSize;
		nSize = 0;

		ChallegeList::iterator it = nList.begin();
		for ( ; it != nList.end() && nSize < tSize; ++ it )
		{
			vpList[ nSize ++ ] = *it;
		}
		return 0;
	}

	template< typename TYPE_T >
	void DelChallege( TYPE_T& nList, int nCorpsID )
	{
		ChallegeList::iterator it = nList.begin();
		for ( ; it != nList.end(); ++ it )
		{
			if ( *it == nCorpsID )
			{
				nList.erase( it );
				break;
			}
		}
		return ;
	}

	template< typename TYPE_T >
	bool InChallege( TYPE_T& nList, int nCorpsID )
	{
		ChallegeList::iterator it = nList.begin();
		for ( ; it != nList.end(); ++ it )
		{
			if ( *it == nCorpsID )
			{
				return true;
			}
		}
		return false;
	}
};



