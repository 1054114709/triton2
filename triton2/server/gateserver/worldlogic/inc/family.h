#ifndef _FAMILY_H_
#define _FAMILY_H_
#include "base_define.h"
#include "base.h"
#include "lk_hashmap.h"
#include "object.h"	 
#include "familytype.h"
#include "familydbinfo_pb.hxx.pb.h"
#include "lk_vector.h"
#include "corpstype.h"
#include "activitytype.h"
#include "servertool.h"
#include "template.h"

// Ϊ�˱��������������ת�ã� �����ɢ�����彨����Ȩ��δ����	  


#define roleid_t  int  
#define labelid_t char 

//class CGoodSInfo;
//class CLeagueShopInfo;
//class CLeagueShopsManager;
//
class CLabel
{
private:
	int	 mRights;				// Ȩ����ϸ
	// char mName[NAME_LENGTH];	// ��ν����
	// labelid_t mID; 				// ��νID
public:

	// ����Ȩ��
	void SetRight(EmRight emRight)
	{
		mRights |= emRight;
	}

	// �ж��Ƿ�ӵ��Ȩ��
	bool HasRight(EmRight emRight) 
	{
		return (emRight & mRights) == emRight;
	}

	// ���Ȩ��
	void ClearRight(EmRight emRight)
	{
		mRights &= (~emRight) ;
	}
	
	// ȡ��ְλmID
	// labelid_t GetID() { return mID; }	
	   
	//����ְλmID
	// void SetID(labelid_t nID) { mID = nID; } 

	//ȡ��ְλ����
	// const char* GetName() const { return mName; }  

	//����ְλ����
	// void SetName(const char* szName) { strncpy(mName, szName, sizeof(mName)); mName[sizeof(mName)-1] = 0; } 
}; 

/*
 * ���������Ա�ڼ����е���Ϣ, Ŀǰֻ�йٽ���Ϣ
 *
 */
typedef struct family_info_t
{
	// labelid_t mLabelID;				// ��Ա�ڼ����еĹ���
	int		 mFamilyContribue;		// ���幱�׶�
	int		 mCorpsContribue;		// ���Ź��׶�
	int		 mExp;					// ���˾���
	int		 mAP;					// ����APֵ
	char	 mName[NAME_LENGTH];	// ����ƺ�		
	labelid_t mFamilyPost;			// ����ְλ
	labelid_t mCorpsPost;			// ����ְλ
	int		 mOnLineTime;			// ����ʱ��(Сʱ)
	family_info_t( )
	{
		if ( CObj::msCreateMode )
		{				
			memset( mName, 0, sizeof( mName ) );
			mFamilyContribue = 0;
			mCorpsContribue	 = 0;
			mExp = 0;
			mAP = 0;
			mFamilyPost = FAMILY_POST_MEMEBER;
			mCorpsPost = CORPS_POST_MEMBER; 
			mOnLineTime = 0;
		}
		else
		{
			
		}
	}
}family_info_t;

/*
 * ÿ�������йٽ׵���֯�ṹ����Ŀǰʹ����򵥵����ṹ, ��ʹ����, �������������ݽṹ
 *
 */
typedef struct organization
{
	CLabel	mLabel;		// �ڵ�����
	char	mLBrother;	// ���ֵ�
	char	mRChild; 	// �Һ���
}organization_t;


// ������ŵ���Ʒ��Ϣ
class CGoodSInfo
{
public:
	int mItemID;		// ��ƷID
	int mItemNum;		// ��Ʒ���ѹ�������
	int	mComposeID;		// �һ��̵�Ļ�����ʾ���Ӻϳɵ�ID
	int mPurcharseTime;	// ���һ�ι����ʱ��
public:
	CGoodSInfo()
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
		mItemNum = 0;
		mComposeID = 0;	
		mItemID = 0;
		mPurcharseTime = 0;		
		return 0;
	}
	int Resume()
	{
		return 0;
	}
	~CGoodSInfo(){}
};

// ������ŵ��̵���Ϣ
class CLeagueShopInfo:public CObj
{
public:	
	typedef lk::hash_map< int, CGoodSInfo, MAXGOODSINSHOP > GoodsList;
	enum 
	{
		SHOPTYPE_WARNPC		= 1,		//	ս���̵�
		SHOPTYPE_EXCHANGE	= 2,		//	�һ��̵�
	};
	
	enum ERefreshResult
	{
		REFRESH_ITEMNOCHANGE = 0,
		REFRESH_ITEMCHANGED	 = 1,
	};

	enum EShopError
	{
		SHOPERROR_BUYGOODS_WRONGTEMP				= 1,		// �����npc����ս��npc
		SHOPERROR_BUYGOODS_ITEMNOTENOUGH			= 2,		// ��Ʒ��������
		SHOPERROR_EXCHANGEGOODS_WRONGTEMP			= 3,		// �һ�npc����ȷ
		SHOPERROR_EXCHANGEGOODS_NPCHASNOCOMPOSEID	= 4,		// �һ�npcû�и��䷽
		SHOPEEROR_EXCHANGEGOODS_NPCHASNOITEM		= 5,		// ���ܶһ�����Ʒ
	};
public:	
	CLeagueShopInfo()
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
	~CLeagueShopInfo(){ }	
public:
	int Initialize()
	{ 
		mShopType = 0;		
		mGoodsList.initailize();
		return 0;
	}
	int Resume(){ return 0; }
public:
	int mShopType;			// �̵�����(�һ�����ռ���̵�)
	int	mShopID;			// �̵��ID��ս���̵�Ϊ���۱�ID���һ��̵�Ϊ�һ���ID
	GoodsList mGoodsList;	// ��Ʒ�б�
public:
	// ����&��ȡ�̵�����
	void SetShopType( int nShopType ){ mShopType = nShopType; }
	int	 GetShopType(){ return mShopType; }

	// ����&��ȡ�̵�npc��ID
	void SetShopID( int nSellTableID ){ mShopID = nSellTableID; }
	int	 GetShopID( ){ return mShopID; }		
	

	// ����һ����Ʒ��Ϣ
	int InsertGoodInfo( int nItemID, CGoodSInfo &rGoodInfo );

	// ɾ��һ����Ʒ��Ϣ
	int DeleteGoodInfo( int nItemID );

	// ��ȡĳ����Ʒ����Ϣ
	CGoodSInfo *GetGoodInfo( int nItemID );

	// ��ȡ��Ʒ���б�
	int GetGoodsList( PBLeagueShopInfo &rLeagueShop ); 

	// ������Ʒ�б�
	int SetGoodsList( PBLeagueShopInfo &rLeagueShop ); 		

	// ˢ����Ʒ��Ϣ(ֻ����ս���̵�)
	int RefreshShopGoodsInfo( );
};

// ������ŵ������̵���Ϣ
class CLeagueShopsManager
{
public:
	typedef lk::hash_map< int, int, MAXLEAGUESHOPSNUM > LeagueShopsList;	
public:
	CLeagueShopsManager()
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
	~CLeagueShopsManager(){ }
public:
	int Initialize()
	{
		mLeagueShopsList.initailize();
		mSaveStatus = false;
		return 0;

	}
	int Resume()
	{
		return 0;
	}
public:
	LeagueShopsList mLeagueShopsList;
	bool			mSaveStatus;	
public:

	// ����ĳ����Ʒ
	int BuyItem( int nSellTableID, int nItemID, int nNum );

	// �һ�ĳ����Ʒ
	int ExchangeItem( int nExchangeID, int nItemID, int nNum, int nComposeID );	

	// ��ȡ�̵��б�
	int GetShopListInfo( PBLeagueShopsListInfo &rShopList );

	// �����̵��б�
	int SetShopListInfo( PBLeagueShopsListInfo &rShopList );

	// ��ȡĳ��ս���̵���Ʒ����Ϣ
	int GetItemInfoInSellTable( int nSellTableID,  int nItemID, CGoodSInfo &rGoodInfo, int &rGoldPrice );	 		

	// ��ȡ�һ��̵���Ʒ����Ϣ
	int GetExchangeShopItemInfo( int nExchangeID, int nItemID, CGoodSInfo &rGoodInfo );

	//	��ȡ&���ñ���״̬
	void SetSaveStatus( bool bSaveStatus ){ mSaveStatus = bSaveStatus; }
	bool GetSaveStatus(  ){ return mSaveStatus; }	

	// ����һ���ɶһ�����Ʒ
	int InsertExchangeItem( int nExchangeID, int nItemID, int nItemNum );						 

	// ��ȡĳ���̵����Ϣ
	int GetShopInfo( int nShopID, PBLeagueShopInfo &tShopInfo ); 

	// ��ȡĳ���̵����Ϣ
	CLeagueShopInfo *GetLeagueShopInfo( int nShopID ); 

	// ��ȡս���̵���ĳ����Ʒ��������Ϣ
	int GetWarShopItemInfo( int nSellTableID, int nItemID, CGoodSInfo &rGoodInfo, int &rGoldPrice );	
};

/*
 * ������������ݽṹ
 *
 */

class CFamily : public CObj
{

public:
	enum E_SAVESTATUS
	{
		FAMILY_INFONOCHANGE = 0 ,			// ������Ϣû�иı�
		FAMILY_PROPERYCHANGED,				// ���Ըı�
		FAMILY_MEMBERCHANGED,				// ��Ա��Ϣ�ı�
		FAMILY_ALLINFOCHANGED,				// ������Ϣ���ı�
	};
	enum
	{
		em_family_label_null = -1,
		em_family_officer_limit = 10,
		em_family_member_limit = 15,
	};
	enum
	{
		EM_FAMILYACTION =	1,					// ������صĲ���	
		EM_CORPSACTION  =	2,	  				// ������صĲ���
	};
	enum
	{
		EM_FAMILY_STATUS_ALIVE		= 0,	// ������״̬
		EM_FAMILY_STATUS_DISBAND	,		// ��ɢ״̬
	};
	
	enum									  // ���������һЩ������
	{
		EM_MONEYNOTENOUGH =	1,				// ��Ǯ����
	};
	
	// ��ȡ��ɫ�б�ʱ�ķ��ؽ��
	enum
	{
		EM_MEMBERINFO_SUCCESS = 0,
		EM_MEMBERINFO_NEEDDISBAD = 1
	};
	typedef lk::hash_map<roleid_t, family_info_t, MAX_FAMILYMEMBER_NUM > members_t;
	typedef members_t::const_iterator const_iterator;
	typedef members_t::iterator iterator; 
	typedef lk::vector< roleid_t, MAX_APPLYLIST_APPLIESNUM > FamilyApplyList;
	typedef lk::vector< roleid_t, MAX_CORPSINVITE_NUM >	CorpsInviteList;
private:
	unsigned int m_nFamilyID;												// ����ID
	char 		 m_sFamilyName[MAX_FAMILYNAME_LENGTH*MAX_UTF8_BYTES];		// ��������
	roleid_t	 m_nRooter;													// ���Ȩ����ɫ
	char		 m_sRooterName[NAME_LENGTH];								// �峤�Ľ�ɫ����
	members_t	 m_tMembers;												// ��Ա�ڼ����е����Ա�
	char		 m_szBulletin[MAX_FAMILYNOTICE_LENGTH*MAX_UTF8_BYTES];		// ����
	unsigned int m_nCountryID;												// ����Ĺ���ID
	organization_t 	m_tOfficers[em_family_officer_limit];					// ��ְ��ϵ
	int			 m_nFamilyDBID;												// ���ݿ��еļ���ID	
	FamilyApplyList	m_tApplyList;											// �����б�
	int			m_nCorpsID;													// ����������ľ���ID
	int			m_nSaveStatus;												// �洢״̬
	CorpsInviteList	m_tInviteList;											// ���ŵ�������Ϣ
	int			m_nFamilyStatus;											// �����״̬����״̬�����߽�ɢ״̬
	int			m_nDisbandTime;												// �峤��ɢ�����ʱ��
	int			m_nLastTimeApplyCorps;										// ���������ųɹ������һ��ʱ��
	int			m_nLastTimeLeaveCorps;										// �����뿪���ŵ����ʱ��
	int			m_nNpcID;													// ����ռ��/���۵�NPCID
	int			m_nBidMoney;												// ���徺�۵�Ǯ��
	int			m_nBidTime;													// ���徺�۵�ʱ��
	bool		m_bJoinBattle;												// �Ƿ��в�ս�ʸ�
	int			m_nBattleState;												// ����ս״̬
	int			m_nWarRank;													// �ۺ�����
	char		m_sPVPName[NAME_LENGTH];									// ��ս��������
	int			m_nFamilyActivityStatus;									// �����״̬
	unsigned short m_nBossChallengeTimes;									// ÿ����boss����ս����	
	
	// ����������ʱ����
	int m_nStar;			// �Ǽ�
	int m_nLevel;			// �ȼ�
	int m_nGlory;			// ��ҫ
	int m_nMoney;			// ���
	int m_nFreezeMoney;		// ����Ǯ
	int m_nContribution;	// ����
	int m_nHot;				// ����
	int m_nProd; 			// ������
	int m_nFun;  			// ���ֶ�
	int m_nTech;			// �Ƽ���
	int m_nCul;				// �Ļ���
	
	
	int m_nPVPWinNum;		// pvpʤ���ĳ���
	int m_nPVPFailedNum;	// pvpʧ�ܵĳ���
	int	m_nPVPScore;		// pvp����
	int	m_nPVPStarLevel;	// pvp�Ǽ� 	
	
	int		m_nChallengeStatus;										// ��ս�����״��
	int		m_nChallengeMoney;										// ��ս���
	char	m_sChallengeStarted[NAME_LENGTH];						// �������ս
	char	m_sChallengeReceived[NAME_LENGTH];						// �յ�����ս
	
	int		m_nFamilyNpcMoney;										// ����npc��������ȡ�Ľ�Ǯ
	int		m_nFamilyNpcGlory;										// ����npc��������ȡ����ҫ
	int		m_nNpcWelfareGetTime;									// ����npc����ȡ������ʱ��
	
	KEY_TYPE m_nFamilyBossKey;										// ���帱��key
	int		m_nFamilyRepetionLevel;									// ���帱���ȼ�
	int		m_nReptionScore;
	int		m_nRepetionDate;										// ���帱�����ϴν���ʱ��(��)
	int		m_nRepetionOpenTimes;									// ������帱�������Ĵ���
	int		m_nWeekNum;												// ���帱�����ܽ������
	CLeagueShopsManager m_tFamilyShop;								// �����̵���Ϣ
	int		m_nStabilityDegree;										// ���尲����	
public:
	CFamily();
	virtual int Initialize();
	virtual int Resume() ;
	~CFamily(){}
public:
	void SetID(int nFamilyID) { m_nFamilyID = nFamilyID; }
	int  GetID() { return m_nFamilyID; }

	void SetRooter(roleid_t nRoleID) 
	{
		m_nRooter = nRoleID;
		SetSaveStatus( FAMILY_PROPERYCHANGED );	
	}
	roleid_t GetRooter() { return m_nRooter; }
	
	void SetName(const char* szName) { strncpy(m_sFamilyName, szName, sizeof(m_sFamilyName)); m_sFamilyName[sizeof(m_sFamilyName)-1] = 0; }
	const char* GetName() { return m_sFamilyName; }
	const char *GetFamilyNameShow()
	{			
		// �ַ���������ʾ
#ifdef CHARSET_SHOW_GBK
		static char tFamilyName[ MAX_FAMILYNAME_LENGTH ] = {0};
		int nNameLen = sizeof(tFamilyName)-1;
		charset_convert( "utf8", "gbk", (char*)m_sFamilyName, strlen( m_sFamilyName ),
			tFamilyName, (size_t*)&nNameLen );
		return tFamilyName;
#else
		return m_sFamilyName;
#endif			
	} 
	void SetBulletin(const char* szBulletin) 
	{ 
		SetSaveStatus( FAMILY_PROPERYCHANGED );	
		strncpy(m_szBulletin, szBulletin, sizeof(m_szBulletin)); 
		m_szBulletin[sizeof(m_szBulletin)-1] = 0; 
	}

	const char* GetBulletin() { return m_szBulletin; }

	// set labelid's id, name, mRights, and his lbrother, rchild.
	void SetOrgan(labelid_t nLableID, organization_t organ)
	{
		SetSaveStatus( FAMILY_MEMBERCHANGED );	
		if (nLableID >= em_family_officer_limit || nLableID < 0) return;
		m_tOfficers[(int)nLableID] = organ;
	}

	void SetCanJoinBattle( bool bFlag ){ m_bJoinBattle = bFlag; }
	bool GetCanJoinBattle(){ return m_bJoinBattle; }

	// ȡ�ó�Ա�б�
	members_t& GetMembers( ) { return m_tMembers; }
	
	// ��ȡ�����Ա����
	int GetMemberNum(){ return m_tMembers.size(); }
	
	// ��ȡ��ְ���
	organization_t *GetOfficers() { return m_tOfficers; }

	// ������ʱ�ò���
	void SetStar(int nStar) { m_nStar = nStar; }
	const int  GetStar() const { return m_nStar; }

	void SetLevel(int nLevel) { m_nLevel = nLevel; }
	int GetLevel() { return m_nLevel; }

	void SetGlory(int nGlory) { m_nGlory = nGlory; }
	int GetGlory() { return m_nGlory; }

	void SetMoney(int nMoney) { m_nMoney = nMoney; }
	int GetMoney() { return m_nMoney; }
	void SetFreezeMoney(int nMoney) { m_nFreezeMoney = nMoney; }
	int GetFreezeMoney() { return m_nFreezeMoney; }

	int GetFamilyMoney() { return m_nMoney - m_nFreezeMoney; }
	void RemoveFreezeMoney(){ m_nMoney -= m_nFreezeMoney; m_nFreezeMoney = 0; }

	void SetContribution(int nContribution) { m_nContribution = nContribution; }
	int GetContribution() { return m_nContribution; }

	void SetHot(int nHot) { m_nHot = nHot; }
	int  GetHot() { return m_nHot; }

	void SetProd(int nProd) { m_nProd = nProd; }
	int GetProd() { return m_nProd; }

	void SetFun(int nFun) { m_nFun = nFun; }
	int GetFun() { return m_nFun; }

	void SetTech(int nTech) { m_nTech = nTech; }
	int GetTech() { return m_nTech; }

	void SetCul(int nCul) { m_nCul = nCul; }
	int GetCul() { return m_nCul; }
	
	void SetCountryID( int nCountryID ){ m_nCountryID = nCountryID; }
	int  GetCountryID( ){ return m_nCountryID; }
	
	void SetRooterName( const char *pName )
	{ 
		strncpy( m_sRooterName, pName, sizeof( m_sRooterName ) - 1 ); 
		m_sRooterName[NAME_LENGTH -1]='\0';
		SetSaveStatus( FAMILY_PROPERYCHANGED ); 
	}	
	const char *GetRooterName(  ){ return m_sRooterName; }
	
	void SetFamilyDBID( int vDbID ){ m_nFamilyDBID = vDbID;  }
	int  GetFamilyDBID( ){ return m_nFamilyDBID; }
	
	void SetCorpsID( int nCorpsID )
	{
		 m_nCorpsID = nCorpsID;
		 SetSaveStatus( FAMILY_PROPERYCHANGED );	
	}
	int	 GetCorpsID( ){ return m_nCorpsID; }
	
	void SetSaveStatus( int vSaveStatus );
	int  GetSaveStatus( ){ return m_nSaveStatus; };
	void ClearSaveStatus( ) { m_nSaveStatus = FAMILY_INFONOCHANGE; }
	
	// ����&��ȡ����״̬
	void SetFamilyStatus( int nSaveSatus )
	{
		m_nFamilyStatus = nSaveSatus; 
		SetSaveStatus( FAMILY_PROPERYCHANGED );	
	}
	int GetFamilyStatus( ){ return m_nFamilyStatus; }
	
	// ����&��ȡ�����ɢʱ��
	void SetFamilyDisbandTime( int nDisbandTime ){ m_nDisbandTime = nDisbandTime;  }
	int	 GetFamilyDisbandTime(){ return m_nDisbandTime; } 
	
	// ����npc����ȡ������ʱ��
	int GetNpcWelfareGetTime( ){ return m_nNpcWelfareGetTime; }
	void  SetNpcWelfareGetTime( int nTime )
	{ 
		SetSaveStatus( FAMILY_PROPERYCHANGED );	
		m_nNpcWelfareGetTime = nTime;
	}
	
	
	// ���úͻ�ȡ���������ųɹ������ʱ��
	void SetLastTimeApplyCorps( int nLastTime ){ m_nLastTimeApplyCorps = nLastTime; }
	int	 GetLastTimeApplyCorps(){ return m_nLastTimeApplyCorps ; }
	
	// ���úͻ�ȡ�뿪���ŵ����ʱ��
	void SetLastTimeLeaveCorps( int nLastTime ){  m_nLastTimeLeaveCorps = nLastTime; }
	int	 GetLastTimeLeaveCorps( ){ return m_nLastTimeLeaveCorps; }	 
	
	// ����&��ȡ��ս�����״̬
	void SetChallengeStatus( int nStatus ){ m_nChallengeStatus = nStatus; }
	int	 GetChallengeStatus( ){ return m_nChallengeStatus; }
	
	// ����&��ȡ��ս���
	void SetChallengeMoney( int nMoney ){ m_nChallengeMoney = nMoney; }
	int	 GetChallengeMoney( ){ return m_nChallengeMoney; }
	
	// ����&��ȡ����������ս
	void SetChallengeStarted( const char *pChallenge )
	{
		strncpy( m_sChallengeStarted, pChallenge, NAME_LENGTH - 1 );
		m_sChallengeStarted[NAME_LENGTH-1]='\0';
	}
	const char *GetChallengeStarted(){ return m_sChallengeStarted; }
	
	// ����&��ȡ����յ�����ս
	void SetChallengeReceived( const char *pChallenge )
	{
		strncpy( m_sChallengeReceived, pChallenge, NAME_LENGTH - 1 );
		m_sChallengeReceived[NAME_LENGTH-1] = '\0';
	}
	
	const char *GetChallengeReceived(){ return m_sChallengeReceived; }	
	
	// ����&��ȡ��������
	void SetRepetionScore( int nScore )
	{
		 m_nReptionScore = nScore; 
		 SetSaveStatus( FAMILY_PROPERYCHANGED );
	}
	int	 GetRepetionScore( ){ return m_nReptionScore; }	
	

	void SetNpcID( int nNpcID ){  m_nNpcID = nNpcID; SetSaveStatus( FAMILY_PROPERYCHANGED );  }
	int	 GetNpcID( ){ return m_nNpcID; }
	void SetBidMoney( int nBidMoney ){  m_nBidMoney = nBidMoney;  SetSaveStatus( FAMILY_PROPERYCHANGED );  }
	int	 GetBidMoney( ){ return m_nBidMoney; }
	void SetBidTime( int nBidTime ){  m_nBidTime = nBidTime;  SetSaveStatus( FAMILY_PROPERYCHANGED );  }
	int	 GetBidTime( ){ return m_nBidTime; }
	void SetBattleState( int vState ){ m_nBattleState = vState; SetSaveStatus( FAMILY_PROPERYCHANGED );  }
	int	 GetBattleState( ){ return m_nBattleState; }

	void SetPVPName( const char *pName )
	{ 
		strncpy( m_sPVPName, pName, sizeof( m_sPVPName ) - 1 ); 
		m_sPVPName[NAME_LENGTH -1]='\0';
	}	
	const char *GetPVPName(  ){ return m_sPVPName; }

	// ����&��ȡpvp�ɹ��ĳ���
	void SetPVPWinNum( int nPVPWinNum ){ m_nPVPWinNum = nPVPWinNum; SetSaveStatus( FAMILY_PROPERYCHANGED );  }
	int	 GetPVPWinNum( ){ return m_nPVPWinNum; }
	
	// ����&��ȡpvpʧ�ܵĳ���
	void SetPVPFaildNum( int nPVPFailedNum ){ m_nPVPFailedNum = nPVPFailedNum; SetSaveStatus( FAMILY_PROPERYCHANGED );  }
	int	 GetPVPFailedNum( ){ return m_nPVPFailedNum; }	 	

	
	// ����&��ȡ�����pvp����
	void SetPVPScore( int nPVPScore ){ m_nPVPScore = nPVPScore; SetSaveStatus( FAMILY_PROPERYCHANGED );  }
	int	 GetPVPScore( ){ return m_nPVPScore; } 
	
	// ����&��ȡ�����pvp�Ǽ�
	void SetPVPStarLevel( int nPVPLevel ){ m_nPVPStarLevel = nPVPLevel; SetSaveStatus( FAMILY_PROPERYCHANGED ); }
	int	 GetPVPStarLevel( ){ return m_nPVPStarLevel; }
	
	// ����&��ȡ�ۺ�����
	void SetWarRank( int nWarRank ){ m_nWarRank = nWarRank; SetSaveStatus( FAMILY_PROPERYCHANGED );  }
	int	 GetWarRank( ){ return m_nWarRank; }
	
	// ����&��ȡ����״̬
	void SetFamilyActivityStatus( int nStatus ){ m_nFamilyActivityStatus = nStatus; }
	int	 GetFamilyActivityStatus(){ return m_nFamilyActivityStatus; }
	
	// ����&��ȡ���帱��key
	void SetFamilyBossKey( KEY_TYPE nKey ){ m_nFamilyBossKey = nKey; }
	KEY_TYPE  GetFamilyBossKey(){ return m_nFamilyBossKey; }
	
	// ���ü��帱���ȼ�
	void SetFamilyRepetionLevel( int nLevel ){ m_nFamilyRepetionLevel = nLevel; }
	int	 GetFamilyRepetionLevel( ){ return m_nFamilyRepetionLevel; }
	
	// ����&��ȡnpc������Ľ�Ǯ
	void SetFamilyNpcMoney( int nMoney )
	{ 
		m_nFamilyNpcMoney = nMoney;
		SetSaveStatus( FAMILY_PROPERYCHANGED ); 
	}
	int	 GetFamilyNpcMoney( bool bRefresh = true );
	
	// ����&��ȡnpc������ȡ����ҫֵ
	void SetFamilyNpcGlory( int nGlory )
	{
		m_nFamilyNpcGlory = nGlory;
		SetSaveStatus( FAMILY_PROPERYCHANGED );
	}
	int	 GetFamilyNpcGlory( bool bRefresh = true );
	
	// ��ȡ����npc����
	int GetFamilyWelfare( int nNpcTmpID, int &rGlory, int &rMoney, bool bRefresh = true );
		
	// ��ѯ������ȴʱ���Ƿ����
	bool CheckLastTimeApplyCorps( );
	
	// ����뿪�������ȴʱ���Ƿ��Ѿ�����
	bool CheckLastTimeLeaveCorps( );
	
	// ��ȡ����Ļ�������(�����Ա�ɼ�)
	int  GetFamilyProperty( PBFamilyPropery &rPBProperty, bool bIfIncludeBasicInfo = true );
	
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
	
	// ����&��ȡ���帱���Ľ�������
	void SetRepetionDate( int nDate )
	{ 
		m_nRepetionDate = nDate;
		SetSaveStatus( FAMILY_PROPERYCHANGED );
	}
	int	 GetRepetionDate(){ return m_nRepetionDate; }
	
	// ����&��ȡ���帱������Ŀ�������
	void SetRepetionOpenTimes( int nTimes )
	{ 
		m_nRepetionOpenTimes = nTimes;
		SetSaveStatus( FAMILY_PROPERYCHANGED );
	}
	int	 GetRepetionOpenTimes(){ return m_nRepetionOpenTimes; }
	
	// ��鸱������ʱ��
	bool CheckRepetionDate( int nDate, int nMaxTimes, int nMaxWeekNum );
	
	// ��ȡ�����̵���Ϣ
	CLeagueShopsManager *GetFamilyShop( ){ return &m_tFamilyShop; } 		
	
	// ��ȡ�����̵��pb��Ϣ
	int GetFamilyShopPBInfo( PBLeagueShopsListInfo &rPbInfo );
	
	// ͨ�������̵��pb�ṹ��Ϣ���ü����̵�
	int SetFamilyShopFromPBInfo( PBLeagueShopsListInfo &rPbInfo );
	
	// set & get 
	void SetStabilityDegree( int nStability )
	{
		m_nStabilityDegree = nStability;
		SetSaveStatus( FAMILY_PROPERYCHANGED );
	}
	int GetStabilityDegree(){ return m_nStabilityDegree; }
	
public:
	// ȡ�ù���
	CLabel* GetLabel(labelid_t nLabelID); 

	// ȡ�õ�ǰ��Ա����
	int GetMemberCount();		

	// �жϼ�ͥ��Ա�Ƿ��Ѵ�����
	bool IsFull();

	// ����³�Ա
	bool Ins2Member( roleid_t nRoleID, family_info_t &stFamilyInfo );

	// ɾ����Ա
	bool Del4Member( roleid_t nRoleID );
	
	// ȡ�ó�Ա�ڼ����е���Ϣ
	family_info_t* GetMemberFamilyInfo( roleid_t nRoleID );

	// �жϼ����Ա�Ƿ�ӵ��Ȩ��emright
	bool MemberHasRight( roleid_t nRoleID, EmRight emright );	
	
	// �ж����Ƿ����ĳ����Ա
	bool HasMember( roleid_t nRoleID ){ return m_tMembers.find( nRoleID )!= m_tMembers.end(); }
	
	// ��ȡ��Ա��Ϣ�б�
	void GetMemberInfoList( PBFamilyMemberInfoList *pbMembList  );
	
	// ͨ��PBFamilyMemberInfoList������Ա��Ϣ
	void CreatMemberInfo( PBFamilyMemberInfoList *pbMembList );
	
	// ����һ����ҵ�����
	int	InsertApply( int nApplyingID );
	
	// ɾ��һ����ҵ�����
	int DeletApply( int nApplyingID );
	
	// �����ҵ�������Ϣ�Ƿ����
	bool CheckApply( int nApplyingID );
	
	// ����Ƿ����������б�����
	bool CheckIfApplyListFull(){ return m_tApplyList.size() >= MAX_APPLYLIST_APPLIESNUM; }
	
	// ��������б�
	void ClearApplyList(){ m_tApplyList.clear(); }	
	
	// ��ȡ�����б����Ϣ
	int GetApplyList( PBApplyList &pbApply );
	
	// ��ȡ�����б����Ҹ���
	int GetAppplyNum( ){ return m_tApplyList.size(); }
	
	// ��ȡ����ĳ�Ա��Ϣ�б�
	int GetFamilyMemberInfoList( PBFamilyMemberList &pbFamilyMemberList, bool bCorpsInfo = false );
	
	// ��ȡ����Ļ���������Ϣ( ��ȡ�����б��� )
	int	GetFamilyBasicInfo( FamilyData &pbFamilyData );	
	
	// ��ȡ����ĳ�ԱID�б�
	int GetFamilyMemberIDList( int *pMemberList, int &nNum, int nExceptRoleID = 0 );
	
	// �������Ƿ���ĳ�����ŵ�������Ϣ
	bool CheckCorpsInvite( int nCorpsID );
	
	// ����һ�����ŵ�������Ϣ
	int InsertCorpsInvite( int nCorpsID );
	
	// ɾ��һ�����ŵ�������Ϣ
	int DeleteCorpsInvite( int nCorpsID );
	
	// ������������Ϣ�Ƿ��Ѿ�����
	bool CheckInviteListIfFull(  ){ return m_tInviteList.size() >=  MAX_CORPSINVITE_NUM; }
	
	// ����Ƿ�Ӧ�ý�ɢ����
	bool CheckDisbandTime( );
	
	// ������ҵ�ְλ
	void SetPost( int nRoleID, labelid_t nPost, int &rOldPost, int nPostKind = EM_FAMILYACTION );
	
	// ��ȡ��ҵ�ְλ
	int GetPost( int nRoleID, int nType, int &rPost );
public:
	// ��ȡ���嵱ǰ�ȼ��µĳ�Ա��������
	int GetMemberLimitNum( );
	
	// ��ȡ���嵱ǰ�ȼ��µ���ҫֵ����
	int GetGloryLimit( );
	
	// ���ü����Ա��ְλ
	int SetFamilyPost( int nCharID, int nPost, int &rOldPost );
	
	// ���þ��ų�Ա��ְλ
	int SetCorpsPost( int nCharID, int nPost, int &rOldPost );
	
	// ��ȡ������߾�����ĳ��ְλ������
	int GetNumOfCertainPost( int nPost, int nType );
	
	// ����Ա�Ƿ���ĳ��ְλ 
	bool HasPost( int nRoleID, int nPost, int nPostKind );
	
	// ĳ�ּ���ְλ��ǰ�ȼ��µ���������
	int GetPostLimitNum( int nPost );
	
	// ���ü����Ա������
	void SetMemberName( int nRoleID, const char *pName );	   
	
	// ������ҵĹ��׶�
	void AddMemberContribute( int nMemberID, int nValue, int nType = EM_FAMILYACTION );	
	
	// ������ҵĹ��׶�
	void ReduceMemberContribute( int nMemberID, int nValue, int nType = EM_FAMILYACTION );	
	
	// ������ҵĹ��׶�
	int GetMemberContribute( int nMemberID, int nType = EM_FAMILYACTION );	
	
	// ������ҵĹ��׶�
	int SetMemberContirubte( int nMemberID, int nContribute, int nType = EM_FAMILYACTION );	
			
public:
	// ��������
	int LevelUPFamily( int &rLevel, int &rMoney, int &rStability );
	
	// �����Ա���׽�Ǯ
	int ContributeMoney( int nMemberID, int nFamilyMoney );
	
	// ������ҫ
	int AddGlory( int nGloryValue, int nGloryType = 0 );
	
	// ������ҫ
	int ReduceGlory( int nGloryValue, int nGloryType = 0 );	
	
	// ��ȡ����Ծ��ŵ��ܹ��׶�
	int GetTotalCorpsContribute();		
	
	// ����pvp����
	bool AddPVPScore( int nValue, int nFailedFamilyLevel, int nType = 0 );
	
	//  ����pvp����
	bool ReducePVPScore( int nValue, int nWinFamilyLevel, int nType = 0 );
	
	// ��ȡĳ��ְλ��Ա�б�
	int GetMemberListOfPost( int *pList, int& rNum, int nPost, int nType );
	
	// ���Ӽ����pvpʤ������
	int AddPVPWinNum( int nNum );	
	
	// ���Ӽ����pvpʧ�ܳ���
	int AddPVPFailedNum( int nNum );
	
	// ���ļ����Ǯ
	int ConsumeFamilyMoney( int nMoney, bool bFreeze = false );
	
	// ���Ӽ����Ǯ
	int AddFamilyMoney( int nMoney, bool bFreeze = false );

	// ����ˢ��һЩ����
	int RefreshStatus();
	
	// �����Ƿ��������
	bool CanFamilyLevelUp();
	
	// ��ȡ������Ҫ�Ľ�Ǯ����ҫ
	int GetLevelCondition( int &rMoney, int &rGlory );
	
	// ��ʼ��ְλϵͳ
	int InitialOrganization();
	
	// �ж�ְλ��Ȩ�޵Ķ�Ӧ��ϵ
	bool PostHasRight( int nPost, int nRight );
	
	// ��ȡ��ĳ��Ȩ�޵�����б�
	int ListMemberOfRight( int *pIDList, int *pPost, int *pContributeList, int &rNum, int nRight ); 
	
	// ���ü��帱����Ϣ
	int SetFamilyRepetionInfo( KEY_TYPE nRepetionKey, int nLevel );
		
	// ��ռ��帱����Ϣ
	int ClearFamilyRepetionInfo(  );		
	
	inline int GetNPCState( )
	{
		if ( m_nNpcID == 0 )
		{
			return STATE_NOBID;
		}
		else
		{
			if ( m_nBidMoney == 0 )
			{
				return STATE_OWN;
			}
			else
			{
				return STATE_CHAZING;
			}
		}
	}
	
	// ��ȡ�����̵�Ĵ�����
	int GetShopErrcode( int nErrcode, int &rShopErrcode );
	
	// �жϼ����Ǯ�Ƿ��㹻
	bool CheckFamilyMoneyEnough( int nMoney );	
	
	// ������ĳ�Ա��Ϣ
	int CheckFamilyRoleInfo();
	
	// ���ټ��尲����
	int ReduceStabilityDegree( int nValue );
	
	// ���Ӽ��尲����
	int AddStabilityDegree( int nValue );

	// ��������ۻ��İ�����
	int AddStabilityByMemberOnTime( int nRoleID, int nLevel, int nTime, int &rOnLineTime, int &rAddStability );

	// ���������ҵ������ۻ�ʱ��
	int ClearMemberOnLineTime();

	// m_nWeekNumber
	void SetWeekNum( int nNum )
	{
		SetSaveStatus( FAMILY_PROPERYCHANGED );
		m_nWeekNum = nNum;
	}
	int GetWeekNum(){ return m_nWeekNum; }
}; 
  
#endif

