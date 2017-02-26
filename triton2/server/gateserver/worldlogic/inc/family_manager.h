#ifndef _FAMILY_MANAGER_H_
#define _FAMILY_MANAGER_H_

#include "family.h"
#include "familytype.h"	
#include "familydbinfo_pb.hxx.pb.h"
#include "familymessage_pb.hxx.pb.h"
#include "servertool.h"
#include "shm.h"
#include "gateobj_define.h"
#include "entity.h"
#include "mailtype.h"
enum EFamilyErrorCode
{
	EFAMILY_CREATE_DUPNAME,
	EFAMILY_ROLE_HAS_FAMILY,
	EFAMILY_MEMBER_IS_FULL,
	EFAMILY_ROLE_ISIN_FAMILY,
	EFAMILY_ROLE_NOAGREERIGHT,
	EFAMILY_ROLE_HAVE_INTHISFAMILY,
	EFAMILY_ROLE_HAVE_INOTHERFAMILY, 
};	

// ����������Ϣ
struct CFamilyConfigInfo 
{
	int mLevel;					// �ȼ�
	int mMemberNumLimit;		// ��Ա��������
	int mGloryLimit;			// ��ҫ����
	int	mPresbyterNumLimit;		// ������������
	int	mPVPScoreLimit;			// ��ǰpvp�Ǽ�����
	int mGloryLevelUPNeeded;	// ��������һ�ȼ���Ҫ����ҫֵ
	int mMoneyLevelUPNeeded;	// ��������һ����Ҫ�Ľ�Ǯ	
	int mInitialStability;		// ÿһ����ʼ��������
	int mReduceStability;		// ÿһ��ÿ��Ӧ�ü��ٵİ�����
};  

// ����������Ե�����
struct CFamilyPropertyConfigInfo
{
	int mContributePerGold;		// ����һ�����ӵĹ��׶�	
	int	mScorePerFight;			// ÿʤ��һ����ȡ�Ļ���
	int	mHour;					// ˢ�¼���״̬��Сʱֵ
	int mMinute;				// ˢ�¼���״̬�ķ���ֵ
	int mGloryPerFight;			// ʤ��һ����ȡ����ҫֵ
	int	mNpcGlory;				// npc��ÿ�������ȡ����ҫ
	int mNpcMoney;				// npc��ÿ�������ȡ�Ľ�Ǯ
	int mExpPerGlory;			// ÿ����ҫֵ��Ҫ�ľ���ֵ
	int mExploitPerGlory;		// ÿ����ҫֵ��Ҫ�Ĺ�ѫֵ
	int	mRepetionMoney;			// �������帱����Ҫ���ĵļ����Ǯ
	int	mRepetionGlory;			// �������帱����Ҫ���ĵļ�����ҫ
	int	mShopRefreshTimeLength;	// ս���̵��ˢ��ʱ��(Сʱ)
	int mRefreshBasicTime;		// ˢ�µĻ�����λ(��)
	int mWarNpcSellTableID;		// ս��npc���̵�ID
	int mChallangeMoney;		// ��ս����
	int mChallangeTimesOfDay;	// ÿ����ս������
	int mRepetionStability;		// ÿ��Ʒ���ҽ����İ�����
};

// �����ȵĵȼ�����
class CStability
{
public:
	int mLevel;								 // �ȼ�
	int	mTimeValue[MAX_STABILITY_TIME_NUM];	 // ����ʱ�䳤��
	int mStability[MAX_STABILITY_TIME_NUM];	 // ÿһʱ�䳤��Ӧ�û�ȡ�İ�����ֵ
public:
	CStability()
	{
		mLevel = 0;
		memset( mTimeValue, 0, sizeof( mTimeValue ) );
		memset( mStability, 0, sizeof( mStability ) );
	}
public:
	int InsertStablity( int nTimeValue, int nStability );	// ����һ�������ȵ�����
	int GetStablity( int nTimeValue, int &rOnLineTime );						// ��ȡ������
};

class CStabilityConfig
{
private:
	int	mTaskStability;									// �������ܹ���ȡ�ļ��尲����
	int	mMoneyStablity;									// ÿ����һ�ǰ󶨽��ܹ���ȡ�İ�����ֵ
	int mDisbandMailID;									// �����ɢʱ���������Ա���ʼ�ID
	int mHeaderMailID;									// �����ɢ�Ƿ����峤���ʼ�ID
	int mUseStability;									// �Ƿ�ʹ�ü��尲�����趨(0Ϊ��ʹ�ã�����Ϊʹ��),���ʹ�ð����Ƚ�Ϊ0ʱ�����ɢ
	CStability mLevelStablity[MAX_STABILITY_LEVEL_NUM];	// �������ʱ���ۻ������ȵĵȼ��������
public:
	// Set & Get TaskStability
	void SetTaskStablity( int nStability ) { mTaskStability = nStability; }
	int GetTaskStability(){ return mTaskStability; }
	
	// Set & Get MoneyStablity
	void SetMoneyStability( int nStablity ) { mMoneyStablity = nStablity; }
	int GetMoneyStability(){ return mMoneyStablity;  }
	
	// Set & Get DisbandMailID
	void SetDisbandMailID( int nID ){ mDisbandMailID = nID; }
	int GetDisbandMailID(){ return mDisbandMailID; }
	
	// Set & Get HeaderMailID 
	void SetHeaderMailID( int nMailID ){ mHeaderMailID = nMailID; }
	int GetHeaderMailID(){ return mHeaderMailID; }
	
	// ����һ���ȼ���ص�����
	void InsertLevelInfo( CStability &rStabiliy );
	
	// ��ȡĳ���ȼ�����ʱ������Ӧ�İ�����
	int GetStabilityValue( int nLevel, int nTime, int &rOnLineTime );
	
	// Set & Get UseStability
	int GetUseStability(){ return mUseStability; }
	void SetUseStability( int nStability ){ mUseStability = nStability; }
public:
	int Initialize();
	int Resume(){ return 0; }		
	CStabilityConfig()
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
	~CStabilityConfig()
	{
		
	}
};

// ÿһ�ȼ�����������Ӧ���ڵ���Ϣ
class CStabilityRedstone
{
public:
	int mStability[MAX_STABILITY_REDSTONE_NUM];
	int mRedstoneID[MAX_STABILITY_REDSTONE_NUM];
	int mEtraExp[MAX_STABILITY_REDSTONE_NUM];
public:
	CStabilityRedstone()
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
	int Initialize()
	{
		memset( mStability, 0, sizeof( mStability ) );
		memset( mRedstoneID, 0, sizeof( mRedstoneID ) );
		memset( mEtraExp, 0, sizeof( mEtraExp ) );
		return 0;
	}
	int Resume(){ return 0; }
public:
	int GetRedStoneID( int nStablity, int &rExtraExp );
	int InsertStabilityRedstone( int nStability, int nRedstone, int nExtraExp );
};

// �����ڵ���������Ϣ
class CFamilyRedstoneConfig
{
public:
	CFamilyRedstoneConfig()
	{
		if ( CObj::msCreateMode )
		{
			Initiallize();
		}
		else
		{
			Resume();
		}
	}
public:
	int Initiallize()
	{
		memset( mStablityRedstone, 0, sizeof( mStablityRedstone ) );
		return 0;
	}
	
	int Resume()
	{
		return 0;
	}
public:
	int GetFamilyRedstone( int nLevel, int nStablity, int &rExtraExp );
	int InsertFamilyRedstone( int nLevel, int nRedstoneID, int nStablity, int nExtraExp );
private:
	CStabilityRedstone mStablityRedstone[FAMILY_LEVEL_LIMIT];
};


// �ʼ���Ϣ
struct CSysMailInfo
{
public:
	int mItemID[MAIL_ITEM_COUNT_MAX];
	int mItemNum[MAIL_ITEM_COUNT_MAX];	
public:
	CSysMailInfo()
	{		
		memset( mItemID, 0, sizeof( mItemID ) );
		memset( mItemNum, 0, sizeof( mItemNum ) );
	}
};

class CMailConfig 
{
public:
	typedef lk::hash_map< int, CSysMailInfo, MAX_MAILINFO_NUM > MailInfoList;
public:
	
	// ����һ���ʼ���Ϣ
	int InsertMailInfo( int nSysID, CSysMailInfo &rMailInfo );
		
	// ��ȡĳ���ʼ���Ϣ
	CSysMailInfo * GetMailInfoByID( int nSysID );
	
	int Initialize()
	{
		mMailInfoList.initailize();
		return 0;
	}
	int Resume()
	{
		return 0;
	}
public:
	CMailConfig()
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
	~CMailConfig(){}
private:
	MailInfoList mMailInfoList;
};

// ncp����������
struct CNpcWelfare
{
	int mNpcMoney;				// npc��Ǯ
	int mNpcGlory;				// npc��ҫ	
};

// ����Ʒ���ҵ�ʱ������
struct CRepetionTimeInfo
{
public:
	int mBeginTime;
	int mEndTime;
	int mWeekDay;
	int mOpenTimes;
public:
	CRepetionTimeInfo()
	{
		mBeginTime = 0;
		mEndTime = 0;
		mWeekDay = 0;
		mOpenTimes= 0;
	}		
};
class CFamilyConfig
{
public:
	typedef lk::hash_map< int, CFamilyConfigInfo, FAMILY_LEVEL_LIMIT > FamilyConfig;
	typedef lk::hash_map< int, CNpcWelfare,	MAX_NPCNUMOFWELFARE >  NpcWelfareList;
	typedef lk::vector< CRepetionTimeInfo, MAX_REPETIONTIMEINFO_NUM > RepetionTimeInfoList;
private:
	FamilyConfig mConfigList;
	CFamilyPropertyConfigInfo mPropertyConfig;
	NpcWelfareList			  mNpcWelfare;
	RepetionTimeInfoList	  mRepetionTimeInfoList;
	CStabilityConfig		  mStabilityConfig;
	CMailConfig				  mMailConfig;
	CFamilyRedstoneConfig	  mFamilyRedstoneConfig;	
	int						  mReptionWeekNum;
public:
	CFamilyConfig( )
	{
		if ( CObj::msCreateMode )
		{	
			Initialize();
		}
		else
		{			
				
		}	
	}
	~CFamilyConfig(){ }
public:
	int Initialize( )
	{
		mConfigList.initailize();
		memset( &mPropertyConfig, 0, sizeof( mPropertyConfig ) );
		mNpcWelfare.initailize();
		mRepetionTimeInfoList.initailize();
		mStabilityConfig.Initialize();
		mMailConfig.Initialize();
		mFamilyRedstoneConfig.Initiallize();
		mReptionWeekNum = 0;
		return 0;
	}	
	int Resume( ){ return 0;  }
public:
	// ����һ������������Ϣ
	int InsertFamilyConfig( CFamilyConfigInfo& rFamilyConfig );
	
	// ���ü���Ļ�����������
	int SetFamilyPropertyConfig( CFamilyPropertyConfigInfo &rFamilyPropertyConfig );
	
	// ����һ��npc�ĸ�����Ϣ
	int InsertNpcWelfare( int nNpcID, CNpcWelfare &rNpcWelfare );
	
	// ��ȡnpc�ĸ�����Ϣ
	int GetNpcWelfare( int nNpcID, CNpcWelfare &rNpcWelfare );
	
	// ��ȡĳ���ȼ��ļ����������Ϣ
	int GetFamilyConfigByLevel( int nLevel, CFamilyConfigInfo& rFamilyConfig );	
	
	// ��ȡ����ĳһ�ȼ��µ���������
	int GetMemberNumLimitByLevel( int nLevel, int &rMemberNum );
	
	// ��ȡ����ĳһ�ȼ��µ���ҫ����
	int GetGloryLimitByLevel( int nLevel, int &rGlory );
	
	// ��ȡ���ϵ���������
	int GetPresbyterNumLimit( int nLevel, int &rNumber );
	
	// ��ȡĳһpvp�Ǽ�����������һpvp�Ǽ���pvp����
	int GetPVPScoreLimit( int nLevel, int &rPvPScoreLimit );
	
	// ��ȡĳһ�ȼ�����������һ�ȼ���Ҫ����ҫֵ
	int GetGloryLevelUPNeeded( int nLevel, int &rGlory );
	
	// ��ȡĳһ�ȼ�����������һ�ȼ���Ҫ�Ľ�Ǯ
	int GetMoneyLevelUPNeeded( int nLevel, int &rMoney );
	
	// ��ȡĳһ�ȼ��ĳ�ʼ������
	int GetInitialStability( int nLevel, int &rStability );
	
	// ��ȡĳһ���ȼ�ÿ��Ӧ�ü��ٵļ��尲����
	int GetReduceStability( int nLevel, int &rStability );
	
	// ��ȡһ�����ӵĹ��׶�
	int GetContributePerGold(  );
	
	// ��ȡ ÿʤ��һ����ȡ�Ļ���
	int GetScorePerFight(  );
	
	// ��ȡÿ��ˢ�µ�ʱ��ֵ
	int GetRefreshHour( ) { return mPropertyConfig.mHour; }	
	
	// ��ȡÿ��ˢ�µķ���ֵ
	int GetRefreshMinute( ){ return mPropertyConfig.mMinute; }
	
	// ��ȡʤ��һ������ҫֵ
	int GetGloryPerFight() { return mPropertyConfig.mGloryPerFight; }
	
	// ��ȡnpc��ÿ�������ȡ�Ľ�Ǯ
	int	GetNpcMoney(){ return mPropertyConfig.mNpcMoney; }
	
	// ��ȡnpc��ý�������ȡ����ҫ
	int GetNpcGlory(){ return mPropertyConfig.mNpcGlory; }
	
	// ��ȡһ����ҫֵ����Ҫ�ľ���ֵ
	int GetExpPerGlory(){ return mPropertyConfig.mExpPerGlory; }
	
	// ��ȡһ����ҫֵ����Ҫ�Ĺ�ѫֵ
	int GetExploitPerGlory(){ return mPropertyConfig.mExploitPerGlory; }
	
	// ��ȡ������帱����Ҫ���ĵļ����Ǯ
	int GetRepetionMoney( ){ return mPropertyConfig.mRepetionMoney; }
	
	// ��ȡ������帱����Ҫ���ĵļ��徭��
	int	GetRepetionGlory( ){ return mPropertyConfig.mRepetionGlory; }	
	
	// ��ȡ�̵��ˢ��ʱ��
	int GetShopRefreshTime(){ return mPropertyConfig.mShopRefreshTimeLength*mPropertyConfig.mRefreshBasicTime; }
	
	// ��ȡ����ս��npc�ĳ��۱�ID
	int GetWarNpcSellTableID(){ return mPropertyConfig.mWarNpcSellTableID; }

	// ��ȡ������ս����Ǯ����
	int GetChallangeMoney() { return mPropertyConfig.mChallangeMoney;}

	// ��ȡ������ս��ÿ�մ���
	int GetChallangeTimesOfDay() { return mPropertyConfig.mChallangeTimesOfDay; }
	
	// ����һ��������ʱ��������Ϣ
	int InsertRepetionTimeInfo( CRepetionTimeInfo &rRepetionTimeInfo );	
		
	// ����Ƿ���Խ�����帱��
	int CheckRepetionOpenTime(  );
	
	// ��ȡ����ĸ���ʱ����Ϣ	
	CRepetionTimeInfo *GetCurrentReptionTimeInfo();
	
	// ��ȡ����������
	CStabilityConfig *GetStabilityConfig(){ return &mStabilityConfig; }
	
	// ��ȡ�ʼ�����
	CMailConfig *GetMailConfig(){ return &mMailConfig; }

	// ��ȡ�����ڵ�����
	CFamilyRedstoneConfig *GetFamilyRedstoneConfig() { return &mFamilyRedstoneConfig; }

	// ��ȡƷ���ҵİ�����
	int GetRepetionStability(){ return mPropertyConfig.mRepetionStability; }

	// ���ø����ܴ���
	void SetRepetionWeekNum( int nNum ){ mReptionWeekNum = nNum; }
	// ��ȡ�����ܴ���
	int GetRepetionWeekNum(){ return mReptionWeekNum; }
};						    

// ���߼����, ����յ���Ϣ�޹�; �����Է���Ϣ
class CFamilyManager : public CSingleton< CFamilyManager >
{
public:
	enum 
	{
		// �ǳ�Ա�¼�
		em_event_family_establish,		// ���彨��
		em_event_clear_apply_by_timer,	// ���붨�����

		// �����¼�
		em_event_alienate_by_rooter, 	// ����ת��ְλ
		em_event_dismiss_by_rooter,		// �����ɢ

		//��Ҫ���Ƴ�ԱȨ�޵��¼�
		em_event_post_appoint_by_player,	// ְ������
		em_event_change_notice_by_player,// �ı���幫��
		em_event_fired_by_player,	// ������Ա
		em_event_list_apply_by_player, 	// �鿴��������
		em_event_agree_apply_by_player,	// ��׼����������� 
		em_event_invite_by_player,		// ������Ҽ���

		// ���Ƴ�ԱȨ�޹������¼�
		em_event_oprate_officer, 		// ��Ա������ְ, �޸Ĺ�ְ��ɾ����ְ
		em_event_oprate_rights,  		// ��ԱΪ��ְ����Ȩ��/����

		// ��ͨ��Աӵ�е�Ȩ��
		em_event_family_outline_watch,	// �����Ҫ��Ϣ�鿴
		em_event_family_detail_watch,	// ������ϸ��Ϣ�鿴
		em_event_retire_by_norooter,	// ��������Ա�˳�����
		em_event_refused_inviting,		// ��Ҿܾ�����
		em_event_agreed_inviting,		// ���ͬ������
		em_event_listfamily_by_player,	// ��һ�ȡ�������м����
		em_event_applyto_by_player,		// �������������
	};

	enum EFamilyInfo
	{
		em_apply_limit = 5,
		em_family_num  = FAMILY_CAP,
		em_npc_num = 100,
	};	
public:

	typedef lk::hash_map< int, int, em_family_num > TFamilies;
	typedef lk::hash_map< roleid_t, int, em_apply_limit> TApplyList;

	class BidInfo
	{
	public:
		int mBidMoney;		// ���۽��
		int mBidTime;		// ����ʱ��

	public:
		BidInfo( ){ mBidMoney = 0; mBidTime = 0; }
		~BidInfo( ){ }
	};

	typedef lk::hash_map< int, BidInfo, em_family_num > BidList;

	class NPCInfo
	{
	public:
		int		mOwnFamily;		// ��������
		BidList mBidList;		// �����б�
		int		mMaxMoney;		// ��߾���
		int		mDefID;			// ���ط�ID
		int		mAttID;			// ������ID
	public:
		NPCInfo( ){ }
		NPCInfo( const NPCInfo& vInfo ){ }
		~NPCInfo( ){ }
	};
	
	typedef lk::hash_map< int, NPCInfo, em_npc_num > NPCList;
	typedef lk::vector< int, SUBMIT_LIMIT > MemberList;
	typedef lk::hash_map< int, MemberList, em_family_num > SubmitList; 

	class BattleInfo
	{
	public:
		KEY_TYPE	mKey;				// ����key
		int			mAttFamilyID;		// ������ID
		int			mDefFamilyID;		// ���ط�ID
		int			mType;				// ��������

	public:
		BattleInfo( ){ mKey = INVITED_KEY_VALUE; mAttFamilyID = 0; mDefFamilyID = 0; mType = TYPE_BATTLE_NPC; }
		BattleInfo( KEY_TYPE vKey, int vAttFamilyID, int vDefFamilyID, int vType ) : mKey( vKey ), mAttFamilyID( vAttFamilyID ), mDefFamilyID( vDefFamilyID ), mType( vType ){ }
		~BattleInfo( ){ }
	};
	typedef lk::vector< BattleInfo, em_family_num > BattleList;

	typedef lk::vector< int, em_family_num > ChaList;
	class RoomInfo
	{
	public:
		char	mName[ NAME_LENGTH ];	// ������
		int		mMoney;					// ����۸�
		ChaList	mChList;				// ��ս�б�
		int		mState;					// ����״̬
		bool	mLock;					// ����״̬
	public:
		RoomInfo( ){ mMoney = 0; mState = STATE_IDLE; mLock = false; }
		RoomInfo( int vMoney, int vState ) : mMoney( vMoney ), mState( vState ){ }
		~RoomInfo( ){ }
	};
	typedef lk::hash_map< int, RoomInfo, em_family_num > RoomList;
	
	typedef lk::hash_map< int, KEY_TYPE, em_family_num > FamilyRepitonKeyList;
private:		
	// ����
	TFamilies		m_tFamilies; 
	// �����
	TApplyList		m_tApplies;
	// ������Ϣ��
	CFamilyConfig	m_tFamilyConfig;
	// �����NPC�б�
	NPCList		mNpcList;
	// ����ս�����б�
	SubmitList  mNPCSubmitList;
	// ս���б�
	BattleList	mBattleList;
	// �����б�
	RoomList	mRoomList;
	
	// ���帱����key�б�
	FamilyRepitonKeyList mFamilyReptionKeyList;
public:
	TFamilies		*GetFamilyList() { return &m_tFamilies; }
	CFamilyConfig	*GetFamilyConfig(){ return &m_tFamilyConfig; }
public:
	static CSharedMem* mShmPtr; // �����ڴ��ַ
	void * operator new( size_t tsize );
	void   operator delete( void *pPointer ); 
	static unsigned int CountSize();
	CFamilyManager() ;
	~CFamilyManager(){}
	int Initailize( );
	int Resume();
public:
	/* ͨ�ò������� */
	// ͨ���������ƻ�ȡ����
	CFamily * GetFamilyByName( const char* szFamilyName );
	
	// ͨ������ID��ȡ����
	CFamily* GetFamilyByID( int nFamilyID );	
	
	// ��ȡ��Ҽ���
	CFamily * GetFamilyOfPlayer( roleid_t nRoleID );
	
	// ����ҵ�������������б�
	int	Insert2ApplyList( int nRoleID, int nFamilyID );
	
	// ��ȡĳ������������б�
	int GetApplyList( int nFamilyID, PBApplyList & pbApplyList ); 
	 
	// ͨ��ID��ȡĳ�����������
	const char * GetFamilyNameByID( int nRoleID );	
	
	// �Ѽ�����뵽�б�����
	int InsertFamily( CFamily *pFamily );
	
	// ��ȡ���������Ա������
	int GetFamilyApplyNum( int vFamilyID );	

public:		
	/* �ͻ���������غ��� */
	
	// ��������		
	int  OnEventEstablishFamily( roleid_t nRoleID, const char* szFamilyName, int &FamilyID );
	
	// ������Ҽ������
	int	 OnEventInvite2Family( roleid_t nInvitingRoleID, roleid_t nInvitedRoleID );

	// ���뱻�˾ܾ�
	int OnEventRefusedByPlayer( roleid_t nInvitingRoleID, roleid_t nInvitedRoleID, int nFamilyID ); 

	// ���뱻��ͬ��
	int OnEventAgreeedByPlayer( roleid_t nInvitingRoleID, roleid_t nInvitedRoleID, int nFamilyID ); 
		
	// ��ȡ�����Ա�б�
	int OnEventListFamilies( roleid_t nRoleID, int* pMember, int &nNum, int ExceptRoleID = 0 );
	int OnEventListFamilies( CFamily *pFamily, int* pMember, int &nNum, int ExceptRoleID = 0 );  
	
	// ����������	
	int OnEventSubmitApply( roleid_t nApplyingRoleID, CFamily *pFamily );
	
	// ͨ��������������������
	int OnEventApplyByName( roleid_t nApplyingRoleID, const char *pFamilyName );		
	
	// ͨ������ID����������
	int OnEventApplyByID( roleid_t nApplyingRoleID, int nFamilyID );
	
	// ��ȡ���е������б�
	int OnEventListAllApplies( roleid_t nRoleID, PBApplyList &pbApply );

	// ͬ������
	int OnEventReplayApply( roleid_t nApprovalRoleID, int nApplyingRoleID, int tRet );  	
	
	//	�����ҵ�����
	bool OnEventRemoveApply( roleid_t nRoleID );	
		
	// ������е�����
	bool OnEventClearAllApply( );  
	
	// ����ת��ְλ���������
	int OnEventARoleAlienate( roleid_t nARoleID, roleid_t nDestRoleID ); 
	
	// �������
	int OnEventFirePlayer( roleid_t nABCRoleID, roleid_t nDestRoleID );	
	
	// ��ɢ����
	int OnEventDismissFamily( roleid_t nARoleID, int *pMemberList, int &rMemberNum );	

	// �뿪����
	int OnEventLeaveFromFamily( roleid_t nRoleID );
			
	// ���ù�ְ
	int OnEventOperateOfficer(roleid_t nRoleID, int nFamilyID, labelid_t nLabelID, const char* szLabelName);
	
	// Ϊְλ����Ȩ��
	int OnEventOperateRights(roleid_t nRoleID, int nFamilyID, labelid_t nLabelID, int rights);
	
	// �г����м������Ϣ
	int OnEventListFamily( roleid_t nRoleID, int nCountryID, PBFamilyList &pFamilyData, int nCurPage, int &rTotalPage );
	
	// ��ȡ�����б�
	bool OnEventListApply(roleid_t nRoleID, int nFamilyID);	 
	
	// ְλ����
	int  OnEventPostAppoint( roleid_t RooterID, roleid_t MemberID, int LabelID );
			
	// ��������б�
	void OnEventClearApplyByTimer( );
	
	// ͬ���������
	int OnEventAgreeInvite( roleid_t nInvitingRoleID, roleid_t nInvitedRoleID );
	
	// ��ȡ�������Ϣ
	int OnEventGetFamiyProperty( roleid_t nRoleID, PBFamilyPropery &pFamilyData );
	
	// �ı����Ĺ�����Ϣ
	int OnEventChangeFamilyBulletin( roleid_t nRoleID, const char *pBulletion );
	
	// ���ĳ������������б�
	int ClearApplyListOfFamily( int FamilyID );
	
	// ������������б�
	int OnEventClearApplyList( roleid_t nRoleID );	 
	
	// ��ɢ����,���������Ϣ
	int OnEventClearFamilyInfo( CFamily *pFamily ); 
	
	// ȡ�������ɢ
	int OnEventCancelFamilyDisband( int nRoleID );
	
	// ɾ����ҵ�����������Ϣ
	void DeleteAllApplyOfPlayer( int nRoleID );
	
	
	
	// ����ְλ
	int OnEventSetFamilyPost( int nManagerID, int nMemberID, int nPost, int &rOldPost );
	
	// ���׽�Ǯ
	int OnEventContributeMoney( int nMemberID, int nMoney );
	
	// ���Ľ�Ǯ
	int OnEventConsumeMoney( int nManagerID, int nMoney, bool bFreeze );
	
	// ��������
	int OnEventLevelUPFamily( int nManagerID, int &rLevel, int &rMoney, int &rStability );
	
	// ���Ӽ�����ҫ
	int OnEventAddFamilyGlory( int nFamilyID, int nGloryValue );
	
	// ���ټ�����ҫ
	int OnEventReduceFamilyGlory( int nFamilyID, int nGloryValue, bool &rLevelDown );
	
	// ���Ӽ���pvp���ֵĽӿ�
	int OnEventAddFamilyPVPScore( int nFamilyID, int nScoreValue, bool &rLevelUP );		
	
public:
	/*********���ݿ���صĲ���***********/
	// ������������ݿ���Ϣ
	int CreatFamilyDBInfo( CFamily *pFamily );

	// ���¼�������ݿ���Ϣ
	int UpDateFamilyDBInfo( CFamily *pFamily );

	// ɾ����������ݿ���Ϣ
	int DeletFamilyDBInfo( CFamily *pFamliy );
	
	// �����еļ�����Ϣ
	void UpDateAllFamilyDBInfo( );
	
	// ɾ�����д��ڽ�ɢ״̬�����Ѿ����ڵļ���
	void DeleteFamilyOnTimeDisband( );	
	
	// ˢ�����м����״̬
	void RefreshFamilyStatus();
public:
	// �����½�������NPC
	int InsertNPC( int vNpcID, int vCountryID );
	// ����NPC����������
	int GetNpcOwner( int vNpcID, int vCountryID );
	// �޸�NPC����������
	int SetNpcOwner( int vNpcID, int vOwnerFamily, int vCountryID, bool vInit = false );
	// ����NPC����
	int AddBid( int vNpcID, int vBidFamily, int vBidMoney, int vBidTime, int vCountryID, bool vInit = false );
	// ɾ��NPC����
	int DelBid( int vNpcID, int vBidFamily, int vCountryID );
	// ���ĳNPC���о���
	int ClearBid( int vNpcID, int vCountryID );
	// ��þ��۳ɹ��ļ���
	int GetWinner( int vNpcID, int &vAttFamily, int &vDefFamily, int vCountryID );
	// ������о��ۼ���
	int GetAllFamily( int vNpcID, int *FamilyList, int *MoneyList, int &Num, int vCountryID );
	// ����ѯ��Ϣ
	void GetBid( int vNpcID, int vCountryID, CMessageBidInfoResponse &vResponse );

	// ��ӱ���
	void AddSubmit( int vFamilyID, int vCharID );
	// ��ñ���
	int GetSubmit( int vCharID );
	// ��ձ���
	void ClearSubmit( int vFamilyID );
	// ֪ͨ����ս��
	void NotifyBattle( int vAttFamilyID, int vDefFamilyID, int vType, int vNpcID = 0 );
	// ս������
	void EndBattle( KEY_TYPE vKey, int vWinSide );
	// �ж��Ƿ��ڱ����б���
	bool InList( int vFamilyID, int vCharID );
	// ֪ͨ����ս��
	void NotifyEnter( int vFamilyID, int vCharID );

	// ��������
	int AddRoom( int vFamilyID, int vMoney, char *vName );
	// ������ս
	int AddCha( int vRoomFamilyID, int vChaFamilyID );
	// ɾ������
	int	DelRoom( int vFamilyID, int &vMoney );
	// ɾ����ս
	int DelCha( int vFamilyID );
	// �����ս
	int ClearCha( int vFamilyID );
	// ���÷���״̬
	int SetRoom( int vFamilyID, int vState );
	// ���÷�������
	int LockRoom( int vFamilyID, bool vLock );
	// ��ѯ��սƥ��
	int HasCha( int vRoomFamilyID, int vChaFamilyID, int &vMoney );
	// ��ѯȫ��������Ϣ
	int QueryAllRoom( CMessageQueryAllRoomResponse &vResponse );
	// ��ѯ�Լ�������Ϣ
	int QueryMyRoom( int vFamilyID, int &vMoney, CMessageQueryMyRoomResponse &vResponse );
	// ��ѯ�Լ���ս��Ϣ
	int QueryMyCha( int vFamilyID, CMessageQueryMyChaResponse &vResponse );

	// �򳡾������¼���ID����֪ͨ
	void SendFamilyIDName( int vServerID );
	// �򳡾�����NPCռ��֪ͨ
	void SendNpcList( int vServerID );

	void SendSingleIDName( int vServerID, int vFamilyID, char *vFamilyName );
	void SendSingleNpc( int vServerID, int vNpcID, int vFamilyID );
	
	// ��ȡ��������ĳ��Ȩ�޵�ְλ��߲������ߵĳ�Ա��Ϣ
	CGatePlayer *GetManagerOfRight( CFamily *pFamily, int nRight );
	
	// ����һ������Key
	int InsertFamilyReptionKey( int nFamilyID, KEY_TYPE nReptionKey );
	
	// ɾ��һ������Key
	int DeleteFamilyReptionKey( int nFamilyID );
	
	// ʹ�ø���Key��������
	int EndFamilyReptionByKey( KEY_TYPE nReptionKey, bool bNormalEnd );
	
	// ���ݼ���ID��ɢ����
	int DisbandFamily( CFamily *pFamily );
	
	// ��Ϊ��ɫ�����ڵ�ԭ��ɾ��һ�������ڵļ���
	int ClearNoExistFamily( CFamily *pFamily );
	
	// ���б����Ƴ�����
	int RemoveFromList( int nFamilyID );
	
	// �������������ڵ���Ϣ
	int CheckFamily();
	
	// �����尲����
	int CheckFamilyStability();
	
	// ��ɢ������ϲ���֯
	bool DisbandedFamilyOrg( CFamily *pFamily );
	
	// ���ͼ����ɢ��ϵͳ�ʼ�	
	int SendDisbandNoticeByMail( CFamily *pFamily );
	
}; 
#endif