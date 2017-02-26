#pragma  once
#include "family.h"
#include "familytype.h"
#include "shm.h"
#include "lk_hashmap.h"
#include "gateobj_define.h"
#include "corpsinfo_pb.hxx.pb.h"  
#include "countrymessage_pb.hxx.pb.h"
#include "entity.h"
#include "module_manager.h"
#include "protype.h"
#include "template.h"
#include "servermessage_pb.hxx.pb.h"
#include "weakprotecter.h"
#include "corps.h"
#include "corpsmanager.h"

#define KING_POWER_INIVALUE1	2000		// ���ӳ�ʼ����
#define KING_POWER_INIVALUE2	50			// ������ʼ����
#define WORLD_SAVE_TIME			300000		// �������ʱ��5����
#define WAR_CHECK_TIME			50000		// 50����һ��ս��״̬��������Ӫ����״̬
#define WAR_SEED_TIME			10000		// ��սˢ��ʱ��
#define ACCUSE_PRENOTICE_TIME	600000		// ����Ԥ��ʾʱ��
#define ACCUSE_NOTICE_TIME		1800000		// ����ʵ����ʾʱ��
#define ACCUSE_PREPARE_TIME		3600000		// ������ǰʱ��
#define ACCUSE_CHECK_TIME		30000		// �������ʱ��
#define ACCUSE_SYNC_TIME		180000		// ����ͬ������ʱ��
#define ACCUSE_FORBID_TIME		604800		// ������ֹ�ٴξ���ʱ��
#define GTLW_CHECK_TIME			5000		// ����ս����״̬ʱ��

#define MAX_LINEID_NUM			20			// ���LineID����
#define MAX_MAPID_NUM			200			// ���MapID����
#define MAX_WAR_WINNER			3			// ����ʤ����
#define MAX_WAR_CANUM			4			// ���Ӫ����

#define	MAIN_WIN_POINT			3			// ��ս������
#define OTHER_WIN_POINT			2			// ����ս������
#define	AWARD_PARAM				20			// ��������
#define WIN_PERCENT				4000		// �����ٷֱ�
#define FIRST_PERCENT			500			// ��һ���ٷֱ�
#define SECOND_PERCENT			300			// �ڶ����ٷֱ�
#define THIRD_PERCENT			200			// �������ٷֱ�
#define BEST_PARAM				24			// ����������

#define MAX_SETTAX_TIMES		3			// ���ô���

enum GMWorldState
{
	STATE_DISABLE	= 0,					// ֹͣGM����	
	STATE_CONTROL	= 1,					// ���ƹ�ս
	STATE_SERIAL	= 2,					// �޸Ĺ�ս���
	STATE_NOSUBMIT	= 3,					// ���ñ�������
	STATE_FORCEACCUSE	= 4,				// ǿ�Ƶ���
	STATE_FORCEEND		= 5,				// ǿ�Ƶ�������
};

enum AccuseState
{
	STATE_NOACCUSE	= 0,					// �޵���״̬
	STATE_TOBE		= 1,					// ȷ��������
	STATE_PREPARE	= 2,					// Ԥ������
	STATE_ACCUSING	= 3,					// ����������
	STATE_ACCUSED	= 4,					// ���ܵ�����
};

using namespace GateServer;

class OfficialFunction
{
public:
	int		mOfficialID;										// ��ְ��CharID
	char	mOfficialName[ NAME_LENGTH ];						// ��Ա����
	int		mUsetimes[ OFFICIAL_FUNCTION_NUM ][ MAX_POWER ];		// ʹ�ô���
};

class CCountry
{
private:
	// ��������
	int	mKingPower;		

	// �Ż�ֵ
	int mWizard[ WIZARD_NUM ];

	// ����ֵ
	int mConstructValue[ OFFICAL_NUM ];

	// �Ż�����ֵ
	int mConstructWizard[ OFFICAL_NUM ];

	// ����ȼ�
	int mConstructLevel[ OFFICAL_NUM ];

	// ��������
	int mPeopleNum;

	// ��ͼID
	int mMapID;

	// ռ�����ID
	int mCorpsID;

	// �ϴη��͵�����
	int	mLastPower;

public:
	// ��ְ��Ϣ
	OfficialFunction mOfficialData[ OFFICIAL_LEVEL_NUM ][ MAX_OFFICAL_NUM ];
public:
	CCountry( )
	{
		if ( CObj::msCreateMode )
		{	
			Initialize();
		}
		else
		{			

		}	
	}
	~CCountry(){ }
public:
	int Initialize( )
	{
		mKingPower = 0;
		memset( mWizard, 0 ,sizeof(mWizard) );
		memset( mConstructValue, 0 ,sizeof(mConstructValue) );
		memset( mConstructLevel, 0 ,sizeof(mConstructLevel) );
		mPeopleNum = 0;
		mMapID = 0;
		mCorpsID = 0;
		memset( mOfficialData, 0 ,sizeof(mOfficialData) );
		mLastPower = 0;
		return 0;
	}	
	int Resume( ){ return 0; }
public:

	void SetKingPower( int vPower ) { mKingPower = std::max( vPower, 0 ); }
	int  GetKingPower(){ return mKingPower; } 

	void SetWizard( int vValue, int vIndex )
	{
		if ( vIndex < 0 || vIndex > (int) ARRAY_CNT(mWizard) )
			return;
		mWizard[ vIndex ] = vValue > 0 ? vValue : 0;
	}
	int  GetWizard( int vIndex )
	{ 
		if ( vIndex < 0 || vIndex > (int) ARRAY_CNT(mWizard) )
			return 0;
		return mWizard[ vIndex ];
	}

	void SetPeopleNum( int vNum ) { mPeopleNum = std::max( vNum, 0 ); }
	int  GetPeopleNum( ){ return mPeopleNum; }
	void AddPeopleNum( ){ ++mPeopleNum; mPeopleNum = std::max( mPeopleNum, 0 ); }
	void DelPeopleNum( ){ --mPeopleNum; mPeopleNum = std::max( mPeopleNum, 0 ); }

	void SetMapID( int vID ) { mMapID = vID; }
	int  GetMapID(){ return mMapID; }

	void SetConstructValue( int vValue, int vIndex )
	{
		if ( vIndex < 0 || vIndex > (int) ARRAY_CNT(mConstructValue) )
			return;
		mConstructValue[ vIndex ] = vValue > 0 ? vValue: 0;
	}
	int  GetConstructValue( int vIndex )
	{ 
		if ( vIndex < 0 || vIndex > (int) ARRAY_CNT(mConstructValue) )
			return 0;
		return mConstructValue[ vIndex ];
	}

	void SetConstructWizard( int vValue, int vIndex )
	{
		if ( vIndex < 0 || vIndex > (int) ARRAY_CNT(mConstructWizard) )
			return;
		mConstructWizard[ vIndex ] = vValue > 0 ? vValue: 0;
	}
	int  GetConstructWizard( int vIndex )
	{ 
		if ( vIndex < 0 || vIndex > (int) ARRAY_CNT(mConstructWizard) )
			return 0;
		return mConstructWizard[ vIndex ];
	}

	int  GetConstructTotal( int vIndex )
	{ 
		if ( vIndex < 0 || vIndex > (int) ARRAY_CNT(mConstructValue) )
			return 0;
		return mConstructWizard[ vIndex ] + mConstructValue[ vIndex ];
	}

	void SetConstructLevel( int vValue, int vIndex )
	{
		if ( vIndex < 0 || vIndex > (int) ARRAY_CNT(mConstructLevel) )
			return;
		mConstructLevel[ vIndex ] = vValue;
	}
	int  GetConstructLevel( int vIndex )
	{ 
		if ( vIndex < 0 || vIndex > (int) ARRAY_CNT(mConstructLevel) )
			return 0;
		CTemplateConstructExp *tpExp = (CTemplateConstructExp*)CDataStatic::GetTemp( TEMP_CONSTRUCTEXP );
		if ( tpExp == NULL )
			return 0;
		int i = 1;
		CTemplateMapTable *tpTable = (CTemplateMapTable*)CDataStatic::GetTemp( TEMP_MAPTABLE );
		if ( tpTable == NULL )
			return 0;
		for (; i < (int) ARRAY_CNT(tpExp->mExp); i++ )
		{
			// ����������Ƶȼ�����������
			if ( i >= tpTable->mLevel[ mMapID ] )
			{
				break;
			}
			if ( GetConstructTotal( vIndex ) <= tpExp->mExp[ i ] )
			{
				break;
			}
		}
		return i;
	}

	void SetCorpsID( int vID ) { mCorpsID = vID; }
	int  GetCorpsID(){ return mCorpsID; }

	void LoadCorps( );
	void LoadOfficial( PBOfficialList vList );
	void SaveOfficial( PBOfficialList &vList );

	void LoadOfficial( PBOfficialList vList, int vOfficial );
	void SaveOfficial( PBOfficialList &vList, int vOfficial );

	CCorps *GetCorps( ){ return CCorpsManager::GetSingleton().GetCorpsByID( mCorpsID ); }
	inline int GetKingID( )
	{
		CCorps *tpCorps = GetCorps( );
		if ( tpCorps != NULL )
		{
			return tpCorps->GetRooterID( );
		}
		return 0;
	}
	inline const char *GetKingName( )
	{
		CCorps *tpCorps = GetCorps( );
		if ( tpCorps != NULL )
		{
			return tpCorps->GetRooterName( );
		}
		return "";
	}
	inline int GetOfficialID( int vCharID )
	{
		for ( int i = 0; i < OFFICIAL_LEVEL_NUM; i++ )
		{
			for ( int j = 0; j < MAX_OFFICAL_NUM; j++ )
			{
				if ( mOfficialData[ i ][ j ].mOfficialID == vCharID )
				{					
					CTemplateOfficialTable *tpOfficialTable = (CTemplateOfficialTable*)CDataStatic::GetTemp( TEMP_OFFICALLIST );
					if ( tpOfficialTable != NULL )
					{
						int tOfficialID = tpOfficialTable->mOfficial[ i ][ j ];
						CTemplateOfficial *tpOfficial = (CTemplateOfficial *)CDataStatic::SearchTpl( tOfficialID );
						if ( tpOfficial == NULL )
						{
							return -1;
						}
						return tpOfficial->mTempID;
					}
				}
			}
		}
		return 0;
	}
	inline void ClearOfficialID( int vCharID, int &vLevel, int vOrder )
	{
		for ( int i = 0; i < OFFICIAL_LEVEL_NUM; i++ )
		{
			for ( int j = 0; j < MAX_OFFICAL_NUM; j++ )
			{
				if ( mOfficialData[ i ][ j ].mOfficialID == vCharID )
				{
					vLevel = i;
					vOrder = j;
					mOfficialData[ i ][ j ].mOfficialID = 0;
					memset( mOfficialData[ i ][ j ].mOfficialName, 0, sizeof( mOfficialData[ i ][ j ].mOfficialName ) );
					return;
				}
			}
		}
	}
	inline int IsHighOfficial( int vCharID )
	{
		for ( int i = OFFICIAL_LEVEL_TWO; i < OFFICIAL_LEVEL_KING; i++ )
		{
			for ( int j = 0; j < MAX_OFFICAL_NUM; j++ )
			{
				if ( mOfficialData[ i ][ j ].mOfficialID == vCharID )
				{
					CTemplateOfficialTable *tpOfficialTable = (CTemplateOfficialTable*)CDataStatic::GetTemp( TEMP_OFFICALLIST );
					if ( tpOfficialTable != NULL )
					{
						return tpOfficialTable->mOfficial[ i ][ j ];
					}
				}
			}
		}
		return 0;
	}
	inline void ChangeConstructByWizard( int vIndex, int vValue )
	{
		if ( vIndex == WIZARD_ARTS )
		{
			mConstructWizard[ OFFICAL_LIBIN ] += vValue;
			mConstructWizard[ OFFICAL_LIBIN ] = std::max( mConstructWizard[ OFFICAL_LIBIN ], 0 );
		}
		else if ( vIndex == WIZARD_TACTICS )
		{
			mConstructWizard[ OFFICAL_GUOFANG ] += vValue;
			mConstructWizard[ OFFICAL_GUOFANG ] = std::max( mConstructWizard[ OFFICAL_GUOFANG ], 0 );
		}	
		else if ( vIndex == WIZARD_POWER )
		{
			mConstructWizard[ OFFICAL_FAYUAN ] += vValue;
			mConstructWizard[ OFFICAL_FAYUAN ] = std::max( mConstructWizard[ OFFICAL_FAYUAN ], 0 );
		}
		else if ( vIndex == WIZARD_WISDOM )
		{
			mConstructWizard[ OFFICAL_GONGCHENG ] += vValue;
			mConstructWizard[ OFFICAL_GONGCHENG ] = std::max( mConstructWizard[ OFFICAL_GONGCHENG ], 0 );
		}
		else if ( vIndex == WIZARD_POLITICS )
		{
			mConstructWizard[ OFFICAL_RENSHI ] += vValue;
			mConstructWizard[ OFFICAL_RENSHI ] = std::max( mConstructWizard[ OFFICAL_RENSHI ], 0 );
		}
		else if ( vIndex == WIZARD_EDUCATE )
		{
			mConstructWizard[ OFFICAL_HUKOU ] += vValue;
			mConstructWizard[ OFFICAL_HUKOU ] = std::max( mConstructWizard[ OFFICAL_HUKOU ], 0 );
		}
	}

	void SetLastPower( int vPower ) { mLastPower = std::max( vPower, 0 ); }
	int  GetLastPower(){ return mLastPower; } 
	inline void AddAllCount( int nFunctionType, int nFunctionOrder )
	{
		for ( int i = OFFICIAL_LEVEL_NUM - 1; i >= 0; i-- )
		{
			for ( int j = 0; j < MAX_OFFICAL_NUM; j++ )
			{
				mOfficialData[ i ][ j ].mUsetimes[ nFunctionType ][ nFunctionOrder ]++;
			}
		}
	}
};

class MetierRank
{
public:
	int		mCharID;
	int		mHonor;
	int		mKill;
};

class CWorld
{
public:
	// ���ҽṹ
	CCountry mCountry[ COUNTRY_NUM ];

	// �Ѻöȹ�ϵ
	int	mFriendStatus[ WORLD_NUM ];

	// �⽻��ϵ
	int mNationStatus[ WORLD_NUM ];

	// �����б�
	int	mOperationList[ WORLD_NUM ];

	// ��������
	int mOpNumber;

	// ����������ܵȼ�
	int mTotalLevel;

	// ���������
	int mTotalNum;

	// ����Ӫ�ڸ�����������ͼ�������
	int mPlayerNum[ MAX_LINEID_NUM ][ MAX_MAPID_NUM ];

	// ��Ӫ���ID
	int mCampID;

	// ս������ֵ
	int mSource[ MAX_WAR_CAMP ];

	// ս��������ֵ
	int mSeed[ MAX_WAR_CAMP ];

	// ���۽��
	int mBidMoney;

	// ���۵����ID
	int mBidCampID;

	// ��ʤ��
	MetierRank mWinChar[ METIER_NOVICE ][ MAX_WAR_WINNER ];

	// ս��ʤ���������
	int mBasicAward;

	// ����ʤ���������
	int mBestAward;

	// �����ܽ��
	int	mSubmitMoney;

	// ռ��ݵ���
	int mSeedNum[ MAX_WAR_CAMP ];

	// ��ɱ����
	int mKill[ MAX_WAR_CAMP ];

	//����ͳ��������Ӫ�ĵ��ܸ��������ۼ�ֵ
	int m_nHonerInc;
	
	//�ϴ�ͳ�Ƶĵȼ�����
	int m_nCampLevelScore;

	//�ϴ�ͳ�Ƶĸ��������ۼ�ֵ
	int m_nCampHonerScore;

	//�ϴ�ͳ�Ƶ��ܷ֣����������ݿ⣬���һ��ͳ�Ƶõ�
	int m_nCampTotalScore;

	//���Ƽ��𣬲��������ݿ⣬����ʱ���ݻ��ּ��㣬�Ա�֤�޸����ݿ����ݺ󲻳�ͻ
	int m_nWeekLevel;

	// ����״̬
	int mAccuseState;

	// �����޳�Ʊ
	int mAccuseYes;

	// ��������Ʊ
	int mAccuseNo;

	// ������ȨƱ
	int mAccuseAbort;

	// ���ż���
	int mGateTimes;

	// �������
	int mFlagTimes;

	// ������ʱ
	CWTimer mAccusePreNoticeTimer;
	CWTimer mAccuseNoticeTimer;
	CWTimer mAccusePrepareTimer;
	CWTimer mAccuseSyncTimer;

	// GM����
	int	mGMAccuse;

	// ��̽��Ӫ
	int	mGTWorld;

	// ��̽����ʱ��
	int	mGTEndTime;

	// ������Ӫ
	int mLWWorld;

	// �������ʱ��
	int mLWEndTime;
	
public:
	CWorld( )
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
	~CWorld(){ }
public:
	int Initialize( )
	{
		memset( mCountry, 0, sizeof(mCountry) );
		memset( mFriendStatus, 0, sizeof(mFriendStatus) );
		memset( mNationStatus, 0, sizeof(mNationStatus) );
		memset( mOperationList, 0, sizeof(mOperationList) );
		mCountry[ COUNTRY_CHANGAN ].SetMapID( COUNTRY_MAP_CHANGAN );
		mCountry[ COUNTRY_WUJI ].SetMapID( COUNTRY_MAP_WUJI );
		mCountry[ COUNTRY_CHECHI ].SetMapID( COUNTRY_MAP_CHECHI );
		mCountry[ COUNTRY_BAOXIANG ].SetMapID( COUNTRY_MAP_BAOXIANG );
		mCountry[ COUNTRY_NVER ].SetMapID( COUNTRY_MAP_NVER );
		mOpNumber = 0;
		
		// ����������������
		memset( mPlayerNum, 0, sizeof(mPlayerNum) );
		// ����ս����������� 
		mTotalLevel = 0;
		mTotalNum = 0;		
		mCampID = -1;
		memset( mSource, 0, sizeof(mSource) );		// ��������ʼʱ����һ��
		memset( mSeed, 0, sizeof(mSeed) );
		mBidMoney = 0;
		mBidCampID = -1;
		mSubmitMoney = 0;
		memset( mSeedNum, 0, sizeof(mSeedNum) );		// ��������ʼʱ����һ��
		memset( mKill, 0, sizeof(mKill) );
		// ����ս����ʼʱ���
		memset( mWinChar, 0, sizeof(mWinChar) );
		mBasicAward = 0;
		mBestAward = 0;

		mAccuseState = 0;
		mAccuseYes = 0;
		mAccuseNo = 0;
		mAccuseAbort = 0;
		mGateTimes = 0;
		mFlagTimes = 0;
		mAccusePreNoticeTimer = CWTimer( ACCUSE_PRENOTICE_TIME );
		mAccusePrepareTimer = CWTimer( ACCUSE_PREPARE_TIME );
		mAccuseNoticeTimer = CWTimer( ACCUSE_NOTICE_TIME );
		mAccuseSyncTimer = CWTimer( ACCUSE_SYNC_TIME );
		mGMAccuse = 0;

		// ��ʼ�����������������
		m_nHonerInc = 0;
		m_nCampLevelScore = 0;
		m_nCampHonerScore = 0;
		m_nCampTotalScore = 0;
		m_nWeekLevel = 0;

		mGTWorld = 0;
		mGTEndTime = 0;
		mLWWorld = 0;
		mLWEndTime = 0;

		return 0;
	}	
	int Resume( ){ return 0; }
public:	
};

class CWorldManager : public CSingleton< CWorldManager >
{
public:
	CWorld	mWorld[ WORLD_NUM ];
	int		mWarSerial;
	int		mWinWorld;
	int		mTitleTime;
	int		mSetRate;			// Ԥ��˰��
	int		mTaxRate;			// ˰��
	int		mTaxMoney;			// ˰��
	int		mCorpsMoney;		// ˰���ۺϽ�
	int		mSetTimes;			// ���ô���
public:
	static CSharedMem* mShmPtr; 
	void * operator new( size_t tsize );
	void   operator delete( void *pPointer );			    
	static unsigned int CountSize();
	CWorldManager();
	~CWorldManager(){}
	int Initailize( );
	int Resume( );	
public:
	int UpdateWorldDBInfo( int vWorldID, int vCountryID );
	int UpdateWorldStatusDBInfo( int vWorldID );
	void LoadCorpsFromMap( int vWorldID, int vMapID, int vCorpsID );
	void SyncNation( int vServerID );
	void DailyRefresh( );
	int GetCountryIDByMap( int vMapID );
	void ClearOfficialID( CGatePlayer *pPlayer );
	void ChangePeopleNum( int vWorldID, int vCountryID, int vChangeType );
	int UpdateOfficialDBInfo( int vWorldID, int vCountryID );
	CCountry* GetCountryByPlayer( CGatePlayer *pPlayer );
	void CheckAccuseTimer( int vWorldID, int vOffset );
	void SysForceAccuse( int vWorldID, int vMapID );
	void ResetAccuseState( int vWorldID );

	void AddPlayerNum( int vWorldID, int vLineID, int vMapID );
	void DelPlayerNum( int vWorldID, int vLineID, int vMapID );
	int GetPlayerTotal( int vLineID, int vMapID );
	int GetPlayerNum( int vWorldID, int vLineID, int vMapID );
	int GetLineID( int vLineID );
	void OnSubmit( int vWorldID, int vLevel, int vMoney );
	void EndClearWar( );
	void StartClearWar( );
	void SetCampID( int vWorldID, int vCampID );
	int GetCampID( int vWorldID );
	void AddSource( int vWorldID, int vCampID, int vValue );
	void DelSource(	int vWorldID, int vCampID, int vValue );	
	void AddSeed( int vWorldID, int vCampID, int vValue );
	void DelSeed( int vWorldID, int vCampID, int vValue );	
	int GetSource( int vWorldID, int vCampID );
	int GetSeed( int vWorldID, int vCampID );
	int GetSeedNum( int vWorldID, int vCampID );
	void ClearSource( );
	void SetBidMoney( int vWorldID, int vMoney );
	int GetBidMoney( int vWorldID );
	void SetBidCampID( int vWorldID, int vCampID );
	int GetBidCampID( int vWorldID );
	void SetSubmitMoney( int vWorldID, int vMoney );
	int GetSubmitMoney( int vWorldID );
	int GetWinWorld( );
	void CheckBidWorld( );
	void AddWinner( int vWorldID, int vCharID, int vHonor, int vKill, int vMetierID );
	int UpdateWorldWarDBInfo( int vWorldID );
	int UpdateWorldGlobalDBInfo( );
	int	CheckAward( );	
	int GetBasicAward( int vWorldID );
	int GetBestAward( int vWorldID );
	int GetRank( int vWorldID, int vCharID, int vMetierID );	
	void SwapWinner( int vWorldID, int vMetierID, int vSrcIndex, int vDesIndex );
	void ReorderWinner( int vWorldID, int vMetierID, int vFirst );
	int UpdateWorldWarCharDBInfo( int vWorldID );
	void GetAwardBySingle( int vWorldID, int vLevel, int vCharID, int vMetierID, int &vBasicAward, int &vBestAward );
	void AddKill( int vWorldID, int vCampID );
	int GetKill( int vWorldID, int vCampID );

	int GetGTTarget( int nWorldID );
	int GetGTEndTime( int nWorldID );
	int GetLWTarget( int nWorldID );
	int GetLWEndTime( int nWorldID );
	int SetGT( int nSrcWorld, int nDesWorld, int nTime );
	int SetLW( int nSrcWorld, int nDesWorld, int nTime );
	int CheckGTAndLW( );
	int SendGTAndLWToScene( int nServerID );
public:
	bool IsWinner(int nWorldID);
	CWorld* GetWorldByID(int nWorldID);
};

class CWorldModule: public CDataModule, public CSingleton< CWorldModule >
{
public:
	CWTimer mTimer;
	int		mTokenID;
	int		mWorldLaunched;
	int		mOfficialLaunched;
	int		mStatusLaunched;
	CWTimer mWarTimer;
	int		mWarStatus;
	CWTimer mSeedTimer;	
	CWTimer	mAccuseTimer;
	CWTimer mGTLWTimer;

	int		mWarLaunched;
	int		mCharLaunched;
	int		mGlobalLaunched;

	int		mGMDay;
	int		mGMHour;
	int		mGMMin;
	int		mNoSubmit;
	CWeakProtecter		m_WeakProtecter;	// ������������
public:
	void OnLaunchServer();
	void OnExitServer();
	void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );
	void OnMessage( int nServerID, CMessage* pMessage );
	void OnSeverMessage(int nServerID, CMessage* pMessage );
	CWorldModule();
	~CWorldModule(){ };
	int Initialize();
	int Resume(); 	
	static unsigned int CountSize();

	virtual bool IsLaunched();

	virtual void OnNewDayCome( );

	inline int GetTokenID( ){ return mTokenID; }
	inline void SetTokenID( int vTokenID ){ mTokenID = vTokenID; }

	void LoadWorld( );
	void LoadWorldStatus( );
	void OnSessionLoadWorld( CMessage* pMessage );
	void OnSessionLoadWorldStatus( CMessage* pMessage );
	void AddOperation( int vSrcWorldID, int vDesWorldID, int vOpType );
	void SetOperation( int vSrcWorldID, int vCharID );
	bool HasOperation( int vSrcWorldID, int vDesWorldID, int vOpType );
	void ClearOperation( int vSrcWorldID, int vDesWorldID, int vOpType );
	void LoadOfficial( );
	void LoadOfficial( int vWorldID, int vCountryID );
	void OnSessionLoadOfficial( CMessage* pMessage, int nParam1 );	
	void LoadWorldWar( );
	void OnSessionLoadWorldWar( CMessage* pMessage );
	void LoadWorldGlobal( );
	void OnSessionLoadWorldGlobal( CMessage* pMessage );
	void LoadWorldWarChar( );
	void OnSessionLoadWorldWarChar( CMessage* pMessage );

	void CheckWarTime( );
	void UpdateAllWar( );
	bool OnUseGTFunction( int nSrcWorldID, int nDesWorldID, int nTime, CGatePlayer *pPlayer );
	bool OnUseLWFunction( int nSrcWorldID, int nDesWorldID, int nTime, CGatePlayer *pPlayer );
	
public:
	void OnMessageCountryInfo( int nServerID, CMessage *pMessage );
	void OnMessageJoinCountry( int nServerID, CMessage *pMessage );
	void OnMessageLeaveCountry( int nServerID, CMessage *pMessage );

	void OnMessageSetOfficial( int nServerID, CMessage *pMessage );
	void OnMessageUnSetOfficial( int nServerID, CMessage *pMessage );
	void OnMessageUseFunction( int nServerID, CMessage *pMessage );
	void OnMessageOfficialInfo( int nServerID, CMessage *pMessage );
	void OnMessageUseTimes( int nServerID, CMessage *pMessage );

	void OnMessageChangeWizard( int nServerID, CMessage *pMessage );
	void OnMessageChangeConstruct( int nServerID, CMessage *pMessage );
	void OnMessageChangePower( int nServerID, CMessage *pMessage );
	void OnMessageChangeFriend( int nServerID, CMessage *pMessage );
	void OnMessageKillPerson( int nServerID, CMessage *pMessage );

	void OnMessageWorldQuest( int nServerID, CMessage *pMessage );
	void OnMessageWorldAnswer( int nServerID, CMessage *pMessage );
	void OnMessageWorldInfo( int nServerID, CMessage *pMessage );
	void OnMessagePlayerInfo( int nServerID, CMessage *pMessage );
	void OnMessageTrySummon( int nServerID, CMessage *pMessage );
	void OnMessageRealSummon( int nServerID, CMessage *pMessage );
	void OnMessageRefuseSummon( int nServerID, CMessage *pMessage );
	void OnMessageAccuseKing( int nServerID, CMessage *pMessage );
	void OnMessagePowerInfo( int nServerID, CMessage *pMessage );
	void OnMessageSpecialEvent( int nServerID, CMessage *pMessage );

	void SendCountryInfoResponse( int vCharID, int vWorldID, int vCountryID, int vNeedFull );
	void SendJoinCountryResponse( int vCharID, int vResult, int vCountryID );
	void SendLeaveCountryResponse( int vCharID,  int vResult );
	void SendJoinCountryNotify( int vCharID, int vCountryID );
	void SendOfficialChangeNotify( int vCharID, int vOfficialLevel, int vOfficialOrder, int vWorldID, int vCountryID, int vType );

	void SendSetOfficialResponse( int vCharID, int vResult, char *vName, int vLevel, int vOrder, int vNormalSet, int vTargetID );
	void SendUnSetOfficialResponse( int vCharID, int vResult, int vLevel, int vOrder );
	void SendUseFunctionResponse( int vCharID, int vResult, char * vName, int vType, int vOrder );
	void SendOfficialInfoResponse( int vCharID, int vWorldID, int vCountryID );
	void SendUseTimesResponse( int vCharID, int vWorldID, int vCountryID );
	void SendUseFunctionNotify( int vCharID, int vTargetID, int vType, int vOrder, int vWorldID, int vCountryID, char *vSrcName, TeleportData tData );
	void SendKillPersonResponse( int vServerID, int vSrcCharID, int vDesCharID, int vPKValue );

	void SendWorldQuestResponse( int vCharID, int vResult, int vWorldID, int vOpType );
	void SendWorldAnswerResponse( int vCharID, int vResult, int vWorldID, int vOpType, int vAnswer );
	void SendWorldQuestNotify( int vCharID, int vWorldID, int vOpType );
	void SendWorldResultNotify( int vSrcWorldID, int vDesWorldID, int vOpType );
	void SendWorldInfoResponse( int vCharID, int vWorldID );	
	void SendEventNotify( int vEventID, int vWorldID, int vCountryID, int *vIntParam, int vSize, char *vStringParam1, char *vStringParam2, int vCharID = 0 );
	void SendWorldAnswerNotify( int vCharID, int vSrcWorldID, int vDesWorldID, int vOpType, int vAnswer );
	void SendKingChangeNotify( int vWorldID, int vCountryID, int nServerID );
	void SendAllKingNotify( int nServerID );
	void SendWarNotify( int vEventID, int vInt0, int vInt1, int vInt2, char *vName );
	void SendWarSource( int vWorldID, int vMapID, int vSource );
	void SendReliveChange( int nServerID );
	void SendWarSourceToSingle( int vCharID, int vMapID );
	void SendSyncWarStatus( int nServerID );
	void SendWarCamp( );
	void SendCreateWarStoneNotify( int vMapID, int vServerID );
	void SendModifyRateNotify( int vRate, CGatePlayer *pPlayer, int vReal, int vWinWorld );
	void SendAccuseKingNotify( int vWorldID, CGatePlayer *pPlayer );
	void SendAccuseInfoNotify( int vEventID, int vWorldID, int vInt0, int vInt1, int vInt2, int vInt3, const char *vName, int vCharID = 0 );
	void SendAccuseStatusNotify( int vWorldID, CGatePlayer *pPlayer );
	void SendMakeGTNotify( int nSrcWorldID, int nDesWorldID, int nTime, CGatePlayer *pPlayer );
	void SendMakeLWNotify( int nSrcWorldID, int nDesWorldID, int nTime, CGatePlayer *pPlayer );

	void OnMessageSubmitWar( int nServerID, CMessage *pMessage );
	void OnMessageEnterWar( int nServerID, CMessage *pMessage );
	void OnMessageQueryWarCamp( int nServerID, CMessage *pMessage );
	void OnMessageQueryWarNum( int nServerID, CMessage *pMessage );
	void OnMessageQueryWarInfo( int nServerID, CMessage *pMessage );
	void OnMessageQueryWarRank( int nServerID, CMessage *pMessage );
	void OnMessageBidCamp( int nServerID, CMessage *pMessage );
	void OnMessageWarChange( int nServerID, CMessage *pMessage );
	void OnMessageObtainWarHonor( int nServerID, CMessage *pMessage );
	void OnMessageCampBidInfo( int nServerID, CMessage *pMessage );
	void OnMessageCampResInfo( int nServerID, CMessage *pMessage );
	void OnMessageWarControl( int nServerID, CMessage *pMessage );
	void OnMessageGetWarAward( int nServerID, CMessage *pMessage );
	void OnMessageQueryWarAward( int nServerID, CMessage *pMessage );
	void OnMessageWarStoneOver( int nServerID, CMessage *pMessage );
	void OnMessageAddTax( int nServerID, CMessage *pMessage );
	void OnMessageModifyRate( int nServerID, CMessage *pMessage );
	void OnMessageGetTax( int nServerID, CMessage *pMessage );

public:
	void OnEventUpdateNationTitle( int nRoleID, int nMapID, int nAction, bool bAdd );
	void SendNationTitleUpdateNotice( CGatePlayer* npPlayer, int nTitleID, bool bAdd );
	void OnMessageGetNationTitleList( int nServerID, CMessage* npMessage );
};
