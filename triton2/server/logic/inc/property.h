#ifndef _PROPERTY_H_
#define _PROPERTY_H_

#include <coretype.h>
#include "proclient_svr.h"
#include "protype.h"
#include "judgetype.h"
#include "lk_set.h"
#include "lk_vector.h"


class CProperty;
class CPropertyCharacter;
class CPropertyPedal;
class CPropertyDrop;
class CPropertyMoney;
class CPropertyItem;
class CPropertyPlayer;
class CPropertyPet;
class CPropertyNPC;

class CEntity;
class CEntityMoney;
class CEntityDrop;
class CEntityItem;
class CEntityPedal;
class CEntityPet;
class CEntityNpc;
class CEntityFuncNpc;
class CEntityPlayer;
class CEntityCharacter;
class CEntityResultList;
class CMessage;

// �콱��������
enum EM_AwardLimitType
{	
	EALT_Daily = 0,		// ��������
	EALT_Weekly = 1,	// ��������
	EALT_Max,
};

class CYuanBao
{
	private:
		enum
		{
			em_ibtrans_per_player = 8,
			em_max_yaunbao_amount = 100000000,
		};

		int m_nValue;

		typedef lk::vector<int, em_ibtrans_per_player> LOCKEDYB;
		LOCKEDYB m_lstLocked;

	public:
		enum 
		{
			em_bind_money = BIND_MONEY,
			em_unbind_money = UNBIND_MONEY,
			em_linekong_money = LINEKONG_MONEY,
			em_silver_yuanbao = SILVER_YUANBAO,
			em_golden_yuanbao = GOLDEN_YUANBAO,
			em_combat_fame = COMBAT_FAME,
			em_repe_fame = REPE_FAME,
			em_common_fame = COMMON_FAME,
		};

		CYuanBao(int value = 0){}
		~CYuanBao(){}

		void initialize()
		{
			m_nValue = 0;
			m_lstLocked.initailize();
		}

		void set( int nValue) 
		{
			m_nValue = nValue; 
		}

		// ����nValue
		inline bool lock(int nValue)
		{
			if ( m_nValue >= nValue )
			{
				if ( m_lstLocked.size() >= em_ibtrans_per_player) return false;

				m_lstLocked.push_back(nValue);
				m_nValue = m_nValue - nValue;

				return true;
			}

			return false;
		}

		// ȷ��nValue
		inline bool commit(int nValue)
		{
			LOCKEDYB :: iterator iter = m_lstLocked.begin();
			for ( ;iter != m_lstLocked.end(); ++iter)
			{
				if ( *iter == nValue)
				{
					m_lstLocked.erase(iter);
					return true;
				}
			}
			
			return false;
		}

		// �ع� nValue 
		inline bool rollback(int nValue)
		{
			if ( commit(nValue) )
			{
				m_nValue += nValue;
				return true;
			}

			return false;
		}

		// ���������Ľ��
		inline int locken()
		{
			int nlocked = 0;
			LOCKEDYB::iterator iter = m_lstLocked.begin();

			for ( ;iter != m_lstLocked.end(); ++iter) nlocked += *iter;


			return nlocked;
		}

		// ���ص�ǰʣ��Ľ��
		inline int remain()
		{
			return m_nValue;
		}

		// ��ֵ
		inline bool add( int nValue)
		{
			if ( nValue < 0) return false;

			int n  = m_nValue + nValue;

			if ( n > em_max_yaunbao_amount )
			{
				return false;
			}

			m_nValue = n;
			return true;
		}
};

/************************************************************************/
/* Property ����������ʵ��Ļ���                                        */
/************************************************************************/
class CProperty
{
private:
	unsigned int		mEntityID;		// ʵ��ID
	EEntityType			mEntityType;	// ����
	unsigned int		mTempID;		// ʵ��ģ��ID	

protected:
	// ������ʧ��ʱ
	unsigned int		mDisappearTimer;	
	unsigned int		mDisappearTime;
	unsigned int		mLevel;

public:

	CProperty( )
	{ 
		if( CObj::msCreateMode )
		{
			Initialize( );
		}
		else
		{
			Resume( );
		}
	}
	
	virtual ~CProperty( ){ }

	int Initialize( )
	{
		mEntityType = ENTITYTYPE_NONE;
		mEntityID = 0;
		mTempID = 0;
		mDisappearTime = 0;
		mDisappearTime = 0;
		mLevel = 0;

//		Initial( );
		
		return SUCCESS;
	}

	virtual int Resume( )
	{
		return SUCCESS;
	}

	virtual int Initial() = 0;

	virtual int Final()
	{
		mEntityType = ENTITYTYPE_NONE;
		mEntityID = 0;
		mTempID = 0;
		mDisappearTime = 0;
		mDisappearTime = 0;
		mLevel = 0;
		return SUCCESS;	
	}

public:	

	// ��������Ķ�ʱ��������ʵ��մ���ʱ����
	virtual void StartSavedTimer() { }
	// ˢ�����ԣ�������ʾ�Ƿ��ʼˢ��
	virtual void Refresh( bool vRefresh = false ){ }

	// ��������Ӧ��ʵ��
	CEntity* GetSelfEntity( );

	// ͨ��ʵ��ID����Property
	static CProperty* SearchProByEntityID( unsigned int vEntityID );

public:

	// Get & Set EntityID
	inline unsigned int GetEntityID( )	{ return mEntityID; }
	int SetEntityID( unsigned int vEntityID );

	// Get & Set EntityType
	inline EEntityType GetEntityType( ) { return mEntityType; }
	int SetEntityType( EEntityType vType );	

	// Get & Set TempID
	inline unsigned int GetPropertyTempID( ) { return mTempID; }
	//  ( ������ˣ�����ְҵID�� �����NPC, ��ģ��ID )
	void SetPropertyTempID( unsigned int vTempID );	

	// Get & Set DisappearTimer
	inline unsigned int GetDisapperaTimer( ){ return mDisappearTimer; }
	inline void SetDisappearTimer( unsigned int vDisappearTimer ){ mDisappearTimer = vDisappearTimer; }

	// Get & Set DisappearTime
	inline unsigned int GetDisapperaTime( ){ return mDisappearTime; }
	inline void SetDisappearTime( unsigned int vDisappearTime ){ mDisappearTime = vDisappearTime; }

	inline int SetLevel( unsigned int vLevel ) { mLevel = vLevel; return SUCCESS; }
	inline unsigned int GetLevel( ) { return mLevel; }

	virtual void IsDisappear( CEntity* pEntity, int vTickOffset, std::vector< unsigned int >& vDeleteList );
};



/************************************************************************/
/*  ���ʵ�����Ի���                                                    */
/************************************************************************/
class CPropertyCharacter : public CProperty
{
public:

	CPropertyCharacter( ){ }
	virtual ~CPropertyCharacter( ){ }

	// ����ṹ�洢���������Գ��õ����ݣ��ڻ�װ����ɾBUFF����������¼���
	// ��Щ���ݶ�������ʹ�õ�ʱ����㣬����������������Ч��
	// ���һ���޸�ȥ��������ֿ��ͷ����ֿ�����Ϊ����
	struct Information
	{
		CPropertyValue					mStr;
		CPropertyValue					mWis;
		CPropertyValue					mSpr;
		CPropertyValue					mCon;
		CPropertyValue					mSta;

		CPropertyValue					mMaxHP;
		CPropertyValue					mMaxMP;
		CPropertyValue					mMaxAP;

		CPropertyValue					mPAttackMax;
		CPropertyValue					mPAttackMin;

		CPropertyValue					mMAttackMax;
		CPropertyValue					mMAttackMin;

		CPropertyValue					mDeathRate;
		CPropertyValue					mDeathValue;
		CPropertyValue					mDeathDefense;

		CPropertyValue					mNormalDuck;
		CPropertyValue					mSkillDuck;
		CPropertyValue					mIgnoreDuck;

		CPropertyValue					mSpeed;

		CPropertyValue					mPDefence;
		CPropertyValue					mMDefence;		

		int								mAddFixDamage;
		int								mAddPerDamage;

		int								mDecFixPDamage;
		int								mDecFixMDamage;
		int								mDecPerMDamage;
		int								mDecPerPDamage;

		int								mStealHP;
		int								mStealMP;

		int								mNormalHitRate;
		int								mSkillHitRate;

		ATTACK_TYPE						mAttackType;

		int								mResDef[ RES_NUM ];
		int								mResAtt[ RES_NUM ];	
		int								mEquipWizard[ WIZARD_NUM ];
	};


protected:
	Information 		mInformation;
	unsigned int		mCurHP;			// ��ǰHP
	unsigned int		mCurMP;			// ��ǰMP
	unsigned int		mCurAP;			// ��ǰAP
	unsigned int		mCurSpeed;		// ��ǰ�ٶ�	
	int					mBattleTimer;	// ս����ʱ��
	int					mRefreshTimer;	// �ָ���ʱ��
	StateParam      	mStateParam[ STATE_COUNT_MAX ];// propety��״̬
	CBuffList			mBuffList;					   // Buff�б�
	CDamageList			mDamageList;		// �˺��б�
	unsigned int		mFirstEntityID;		// ��һ������ʵ��
	unsigned int		mMaxDamager;		// ����˺�ʵ��	
	float				mLastHPPer;			// ������ս��ʱ�������ٷֱ�
	unsigned int		mPetID;				// Я�������ID 
   	unsigned int		mTotalTripIndex;	// ��ǰ����ĸ���
	TripEntityInfo  	mTripEntityIDList[ MAX_TRIP_ENTITY ]; // �����б�	
	
public:
	virtual int Initial() = 0;
	virtual int Final() = 0;

	// ��ʼ��CPropertyCharater������
	void CharacterInitial( );

	// ����CPropertyCharacter������
	void CharacterFinal( );

	// �Ƴ�Character״̬
	void DetachState( EState vState, int vIndex, STATE_FROM vFrom, int vParames1 = 0, int vParames2 = 0 );

	// ����Character״̬
	void AttachState( EState vState, int vParames1, int vParames2, int vIndex, STATE_FROM vFrom );
	public:
	// ���˺��б��м����˺�
	void InsertDamage( const CDamage& rDamage );

	// ���ָ��ID��ʵ����˺��ٷֱ�
	float	GetDamagePer( unsigned int vEntityID );

	// �Ƿ�����Լ�����
	bool Controlable( );

	// �Ƿ�����ƶ�
	bool Moveable( );

	// �Ƿ���Թ���
	bool Attackable();

	// ��õ�ǰHP�ٷֱ�
	float GetHPPercent( );

	// ��õ�ǰMP�ٷֱ�
	float GetMPPercent( );

	// ˢ������
	virtual void Refresh( bool vRefresh = false );

	// �����ٻ���ʵ��
	void DestroyPetEntity( );

	// �����ٻ���ʵ��,����ʵ������ʱ
	void DestroyPetByOwnerDestroy( );

	// ��������ʵ��
	bool NoteAddTripEntityID( int vTripEntityID );

	// ȥ������ʵ��
	bool ClearAddTripEntityID( int vTripEntityID );

	// ȥ����������ʵ��
	void ClearAllTripEntity(  );

	// ����DelayAction�¼�
	int DelayActionEvent( CEntityCharacter* pEntity, unsigned int vTickOffSet );

	// ����⻷�¼�
	int AureoleTimeEvent( CEntityCharacter* pEntity, unsigned int vTickOffSet );

	// ����Buff�¼�
	//int BuffTimeEvent( CEntityCharacter* pEntity, CTemplateBuff* tpBuffTpl, CBuffObject* tpBuff );

	// ��������ȴ�¼�
	int SkillCoolingEvent( CEntityCharacter* pEntity, unsigned int vTickOffSet );

	// ����ս����ʱ�¼�
	int BattleTimeEvent( CEntityCharacter* pEntity, unsigned int vTickOffSet ); 

	// �����Ѫ�¼�
	int RecTimeEvent( CEntityCharacter* pEntity, unsigned int vTickOffSet );

	// �����ٶȸı�֪ͨ��Ϣ
	bool CreateMessageNotifySpeedChanged( CMessage* pTotalMessage, CMessageSpeedChangedNotify* pMessage, unsigned int vEntityID, int vSpeed	);

	// ��BuffList��PB�ṹ����Buff�б�
	void CreateBuffListFromTlv2( PBBuffList* pBuffer );

	// ��Buff�б�����ݴ洢��PB�ṹ
	void GetBuffListTlvBuffer2( PBBuffList* pBuffer );



	// �������ɵ�NPC (��������)
	//int OnKillEntityWithHideTimeout( CEntity* pEntity );


	// ���Ԥ�洢��Character����
	inline CPropertyValue GetStr( ) { return mInformation.mStr; }
	inline CPropertyValue GetWis( ) { return mInformation.mWis; }
	inline CPropertyValue GetSpr( ) { return mInformation.mSpr; }
	inline CPropertyValue GetCon( ) { return mInformation.mCon; }
	inline CPropertyValue GetSta( ) { return mInformation.mSta; }
	inline CPropertyValue GetMaxHP( ) { return mInformation.mMaxHP; }
	inline CPropertyValue GetMaxMP( ) { return mInformation.mMaxMP; }
	inline CPropertyValue GetMaxAP( ) { return mInformation.mMaxAP; }
	inline CPropertyValue GetPAttackMax( ) { return mInformation.mPAttackMax; }
	inline CPropertyValue GetPAttackMin( ) { return mInformation.mPAttackMin; }
	inline CPropertyValue GetMAttackMax( ) { return mInformation.mMAttackMax; }
	inline CPropertyValue GetMAttackMin( ) { return mInformation.mMAttackMin; }
	inline CPropertyValue GetDeathRate( ) { return mInformation.mDeathRate; }
	inline CPropertyValue GetDeathValue( ) { return mInformation.mDeathValue; }
	inline CPropertyValue GetDeathDefense( ) { return mInformation.mDeathDefense; }
	inline CPropertyValue GetNormalDuck( ) { return mInformation.mNormalDuck; }
	inline CPropertyValue GetSkillDuck( ) { return mInformation.mSkillDuck; }
	inline CPropertyValue GetIgnoreDuck( ) { return mInformation.mIgnoreDuck; }
	inline CPropertyValue GetSpeed( ) { return mInformation.mSpeed; }
	inline CPropertyValue GetPDefence( ) { return mInformation.mPDefence; }
	inline CPropertyValue GetMDefence( ) { return mInformation.mMDefence; }
	inline int GetAddFixDamage( ) { return mInformation.mAddFixDamage; }
	inline int GetAddPerDamage( ) { return mInformation.mAddPerDamage; }
	inline int GetDecFixPDamage( ) { return mInformation.mDecFixPDamage; }
	inline int GetDecFixMDamage( ) { return mInformation.mDecFixMDamage; }
	inline int GetDecPerPDamage( ) { return mInformation.mDecPerPDamage; }
	inline int GetDecPerMDamage( ) { return mInformation.mDecPerMDamage; }
	inline int	GetStealHP( ) { return mInformation.mStealHP; }
	inline int GetStealMP( ) { return mInformation.mStealMP; }
	inline ATTACK_TYPE GetAttackType( ) { return mInformation.mAttackType; }
	inline int GetNormalHitRate( ) { return mInformation.mNormalHitRate; }
	inline int GetSkillHitRate( ) { return mInformation.mSkillHitRate; }
	inline int GetResDef( int i ) { if ( i <= RES_NONE || i >= RES_NUM ) return 0; return mInformation.mResDef[ i ]; }
	inline int GetResAtt( int i ) { if ( i <= RES_NONE || i >= RES_NUM ) return 0; return mInformation.mResAtt[ i ]; }
	inline int GetEquipWizard( int i ) { if ( i < 0 || i >= WIZARD_NUM ) return 0; return mInformation.mEquipWizard[ i ]; }

	
	// �޸�Ԥ�洢��Character���ԣ����Ͳ�ͬ���޸ĵķ�ʽҲ��ͬ
	virtual CPropertyValue RefreshStr( ) = 0;
	virtual CPropertyValue RefreshWis( ) = 0;
	virtual CPropertyValue RefreshMaxHP( ) = 0;
	virtual CPropertyValue RefreshSpr( ) = 0;
	virtual CPropertyValue RefreshSta( ) = 0;	
	virtual CPropertyValue RefreshCon( ) = 0;	
	virtual CPropertyValue RefreshMaxMP( ) = 0;
	virtual ATTACK_TYPE	RefreshAttackType( ) = 0;
	virtual CPropertyValue RefreshPAttackMax( ) = 0;
	virtual CPropertyValue RefreshPAttackMin( ) = 0;
	virtual CPropertyValue RefreshMAttackMax( ) = 0;
	virtual CPropertyValue RefreshMAttackMin( ) = 0;
	virtual CPropertyValue RefreshDeathRate( ) = 0;
	virtual CPropertyValue RefreshDeathValue( ) = 0;
	virtual CPropertyValue RefreshDeathDefense( ) = 0;
	virtual CPropertyValue RefreshNormalDuck( ) = 0;
	virtual CPropertyValue RefreshSkillDuck( ) = 0;
	virtual CPropertyValue RefreshIgnoreDuck( ) = 0;
	virtual CPropertyValue RefreshPDefence( ) = 0;
	virtual CPropertyValue RefreshMDefence( ) = 0;
	virtual int RefreshAddFixDamage( ) = 0;
	virtual int	RefreshAddPerDamage( );
	virtual int RefreshDecFixPDamage( ) = 0;
	virtual int RefreshDecFixMDamage( ) = 0;
	virtual int RefreshDecPerPDamage( ) = 0;
	virtual int RefreshDecPerMDamage( ) = 0;
	virtual int RefreshStealHP( );
	virtual int RefreshStealMP( );
	virtual int RefreshNormalHitRate( ) = 0;
	virtual int RefreshSkillHitRate( ) = 0;
	virtual int RefreshResDef( int *vDef ) = 0;
	virtual int RefreshResAtt( int *vAtt ) = 0;
	virtual int RefreshEquipWizard( int *vWizard );
	virtual	int GetDuckRate( ) = 0;

public:

	// Get & Set CurHP
	inline unsigned int GetCurHP( ){ return mCurHP; }
	inline void SetCurHP( unsigned int vCurHP ){ mCurHP = vCurHP; }

	// Get & Set CurMP
	inline unsigned int GetCurMP( ){ return mCurMP; }
	inline void SetCurMP( unsigned int vCurMP ){ mCurMP = vCurMP; }

	// Get & Set CurAP
	inline unsigned int GetCurAP( ){ return mCurAP; }
	inline void SetCurAP( unsigned int vCurAP ){ mCurAP = vCurAP; }

	// Get & Set CurSpeed
	inline unsigned int GetCurSpeed( ){ return mCurSpeed; }
	inline void SetCurSpeed( unsigned int vCurSpeed ){ mCurSpeed = vCurSpeed; }

	// Get & Set BattleTimer
	inline int GetBattleTimer( ){ return mBattleTimer; }
	inline void SetBattleTimer( int vBattleTimer ){ mBattleTimer = vBattleTimer; }

	// Get & Set RefreshTimer
	inline int GetRefreshTimer( ){ return mRefreshTimer; }
	inline void SetRefreshTimer( int vRefreshTimer ){ mRefreshTimer = vRefreshTimer; }

	// Get & Set StateParam
	inline StateParam GetStateParam( int i ){ return mStateParam[ i ]; }
	inline void SetStateParam( int i, StateParam vStateParam ){ mStateParam[ i ] = vStateParam; }
	inline void CleanStateParam( ){ memset( mStateParam, 0, sizeof( mStateParam ) ); }

	// Get & Set BuffList
	inline CBuffList *GetBuffList( ){ return &mBuffList; }

	// Get & Set SkillList
	virtual CSkillList& GetSkillList( ) = 0;

	// Get & Set DamageList
	inline CDamageList *GetDamageList( ){ return &mDamageList; }

	// Get & Set FirstEntityID
	inline unsigned int GetFirstEntityID( ){ return mFirstEntityID; }
	inline void SetFirstEntityID( unsigned int vFirstEntityID ){ mFirstEntityID = vFirstEntityID; }

	// Get & Set MaxDamager
	inline unsigned int GetMaxDamager( ){ return mMaxDamager; }
	inline void SetMaxDamager( unsigned int vMaxDamager ){ mMaxDamager = vMaxDamager; }

	// Get & Set LastHPPer
	inline float GetLastHPPer( ){ return mLastHPPer; }
	inline void SetLastHPPer( float vLastHPPer ){ mLastHPPer = vLastHPPer; }

	// Get & Set PetID
	inline unsigned int GetPetID( ){ return mPetID; }
	inline void SetPetID( unsigned int vPetID ){ mPetID = vPetID; }

	// Get & Set TotalTripIndex
	inline unsigned int GetTotalTripIndex( ){ return mTotalTripIndex; }
	inline void SetTotalTripIndex( unsigned int vTotalTripIndex ){ mTotalTripIndex = vTotalTripIndex; }

	// Get & Set TripEntityIDList
	inline TripEntityInfo GetTripEntityIDList( int i ){ return mTripEntityIDList[ i ]; }
	inline void SetTripEntityIDList( int i, TripEntityInfo vTripEntityIDList ){ mTripEntityIDList[ i ] = vTripEntityIDList; }
	inline void CleanTripEntityIDList( ){ memset( mTripEntityIDList, 0, sizeof( mTripEntityIDList ) ); }
	inline int GetTripEntityIDListSize( ){ return ARRAY_CNT( mTripEntityIDList ); }
	
	

	// ������������ƥ��
	virtual bool SkillWeaponValid( CTemplateSkill* pSkill ) { return true; }

	// װ���Ƿ���� ( �;ö��Ƿ�Ϊ0 )
	virtual bool EquipmentAvailable( EEquipPart emPart ) { return true; }

	// Get CommonCD
	virtual int GetCommonCD( ){ return 0; }

	// �����Ƿ��ڹ�����ȴ��
	virtual bool IsCommonCoolingDown( CTemplateSkill* pSkill ) { return false; }


	int AttachBuffState( int vSrcEntityID, CTemplateBuff::CBuffFunc* vpBuffFunc, int vIndex );

	// ��PB�ṹ����State�б�
	void CreateStateListFromTlv2( PBStateList* pBuffer );

	// ��PB�ṹ���State�б�
	void GetStateListTlvBuffer2( PBStateList* pBuffer );


	virtual void SetTranChangeLevel( int vLevel ) {  }
	virtual int GetTranChangeLevel( ) { return 0; }
};

// ��¼ɱ���ߵ�ID�����ʱ��
struct KillData
{
	int mKillID;
	int mKillTime;
};

// ���۸�NPC����
struct SaleItem
{
	unsigned int mItemID;	// CItemObject ����id(Ψһ��ʾ)
	unsigned int mNumber;
	unsigned int mPrice;

	SaleItem() 
	{
		if ( CObj::msCreateMode )
		{
			mItemID = 0;
			mNumber = 0;
			mPrice = 0;
		}		
	}
	SaleItem( unsigned int vItemID, unsigned int vNumber, unsigned int vPrice ) : 
	mItemID( vItemID ), mNumber( vNumber ), mPrice( vPrice ) { } 
};

// ̯λ����
struct STALL
{
	unsigned int obj_id;
	unsigned int Price;
	unsigned int Number;
	unsigned int Index;// stall index
	unsigned int PriceType;

	STALL() 
	{
		if ( CObj::msCreateMode )
		{
			obj_id = 0;
			Price = 0;
			Number = 0;
			Index = 0;
			PriceType = 0;
		}		
	}
	STALL( unsigned int vid, unsigned int vPrice, unsigned int vNum, unsigned int vIndex, unsigned int vPriceType ) : 
	obj_id( vid ), Price( vPrice ), Number( vNum ), Index( vIndex ), PriceType(vPriceType) { }
};

class CStallRecord : public CObj
{
public:
	lk::string<NAME_LENGTH> mBuyerName;
	int		mItemID;
	int		mNumber;
	int		mPrice;
	int		mTimeStamp;
	int		mAction;
	int		mTax;
	int		mPriceType;//�۸�����
	int		mFee;//������
	int64	mItemGuid;
	int		mItemIndex;
	int		mStallIndex; // ̯λ�е�����

public:
	CStallRecord(){ Initialize(); }
	~CStallRecord(){ ; }

	int Initialize() 
	{
		mItemID = 0; 
		mNumber = 0;
		mPrice = 0;
		mTimeStamp = 0;
		mAction = 0; 
		mTax = 0;
		mPriceType = 0; 
		mFee = 0;
		mItemGuid = 0; 
		mItemIndex = 0; 
		mStallIndex=0; 
		return 0 ;
	}
	int Resume() { return  0; } 
};

class CStallInfo
{
private:
	lk::string<NAME_LENGTH>		mName;			// ̯λ����
	lk::string<NAME_LENGTH * 2>	mAd;			// �����Ϣ
	bool bSaved;// ��̯�Ƿ񱣴�
	int mStallType;
public:

	typedef lk::vector< STALL, MAX_STALL_INDEX > StallList;
	StallList	mStall;

	typedef lk::vector< CStallRecord, MAXPLAYERNUM > RecordList;
	RecordList mRecordList;

	CStallInfo() { bSaved = false; mStallType = 0; mStall.initailize(); mRecordList.initailize(); }
	~CStallInfo() { mStall.clear(); mRecordList.clear(); }

	inline void SetFlag( bool bFlag ) { bSaved = bFlag; }
	inline bool IsSaved() { return bSaved; }
	inline void SetName( const char* pName ) { mName = lk::string<NAME_LENGTH>( pName ); }
	inline void SetAd( const char* pAd ) { mAd = lk::string<NAME_LENGTH*2>( pAd ); }
	inline const char* GetName() { return mName.c_str(); }
	inline const char* GetAd() { return mAd.c_str(); }
	inline void PushObj( unsigned int vid, unsigned int vStallIndex, unsigned int vNum, unsigned int vPrice, int vPriceType )
	{
		STALL tStall( vid, vPrice, vNum, vStallIndex,vPriceType );
		mStall.push_back( tStall );
	}
	inline void PushRecord( CStallRecord* vpRecord )
	{
		if ( vpRecord == NULL )
			return ;
		if ( mRecordList.size() == MAXPLAYERNUM )
		{
			RecordList::iterator it = mRecordList.begin();
			mRecordList.erase( it );
		}
		mRecordList.push_back( *vpRecord );
	}
	inline void CleanStall() { bSaved = false; mStall.clear(); mRecordList.clear(); }
	inline void CleanRecord(){ mRecordList.clear(); }
	inline void SetStallType(const int vStallType){ mStallType = vStallType;} 
	inline int GetStallType() { return mStallType;}


};

// �����

// ��ҵ������
struct ComposeInfo 
{
	int mTempID;
	int mUsedTimes;			
};

class CLifeSkill
{
public:
	typedef lk::vector< ComposeInfo, MAX_LIFESKILL_COMPOSENUM > MultiComposeIDList;
	enum EDegreeAddType
	{
		DEGREEADDTYPE_USECOMPOSE = 1,	// ͨ��ʹ���䷽�ķ�ʽ����������
		DEGREEADDTYPE_BYLEVELUP	 = 2,	// ͨ�����ܽ��׵ķ�ʽ����������
		DEGREEADDTYPE_BYITEM	 = 3,	// ͨ��ʹ����Ʒ�ķ�ʽ����������
		DEGREEADDTYPE_BYSTUDY	 = 4,	// ͨ���о����䷽����������		
	};
private:
	int		mLifeSkillType;				// ���������
	int		mLifeSkillLevel;			// ����ܵȼ�
	int		mSpecializedDegree;			// �����������
	// short	mLifeSkillStatus;			// �����״̬
	short	mLifeSkillKind;				// �������࣬�����ܻ��Ǹ��޼���	
	MultiComposeIDList mMultiComposeIDList;
public:
	CLifeSkill()
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
	~CLifeSkill( ){ }
public:
	int Initialize( );
	int Resume(){ return 0; }
public:
	// ��ȡ&�������������
	int		GetLifeSkillType(){  return mLifeSkillType; }
	void	SetLifeSkillType( int nLifeSkillType ){ mLifeSkillType = nLifeSkillType; } 

	// ����&��ȡ����ܵȼ�
	int		GetLifeSkillLevel(  ){  return mLifeSkillLevel; }
	void	SetLifeSkillLevel( int nLifeSkillLevel ){ mLifeSkillLevel = nLifeSkillLevel; }

	// ����&��ȡ����������	
	int		GetSpecializedDegree(){ return mSpecializedDegree; }
	void	SetSpecializedDegree(  int nSpecializedDegree ){ mSpecializedDegree = nSpecializedDegree;  }	

	// ����&��ȡ���������
	void	SetLifeSkillKind( int nLifeSkillKind ){ mLifeSkillKind = nLifeSkillKind; }
	int		GetLifeSkillKind(  ){ return mLifeSkillKind; }

public:	
	// ѧϰһ�����䷽
	int StudyCompose( int nComposeID, int nGetWay, int &rPlayerAp, unsigned int &rPlayerMoney );

	// ɾ��һ���䷽
	int DeleteCompose( int nComposeID );

	// ����Ƿ���ĳ���䷽
	bool CheckCompose( int nComposeID );

	// ����������
	void AddSpecializedDegree( int nDegree, int nAddType );		

	// ���ܽ���
	int LevelUpLifeSkill( int nPlayerLevel, int &nPlayerBindMoney, int &nPlayerMoney );	

	// ���������
	int ForgetLifeSkill( );

	// ��ȡ���ȼ�������������
	int GetCurrentDegreeLimit();

	// ʹ���䷽
	int UseCompose( int nComposeID, int &rDegreeValue, bool bAddNow = true );

	// ����������Ƿ��Ѿ�������ǰ���ܵȼ�������
	bool CheckDegree( int nDegree );

	// ���������
	int InitialLifeSkill( int nLifeSkillType, int nSkillKind );

	// ���������
	int CreatCompose( int nValue, int *pMaterialIDList, int nLenth, int &rComposeID, int nSkillKind );

	// ����Ƿ��������
	int CanLifeSkillLevelUp( CTemplateLifeSkill *pLifeSkill  );
	
	// �ɼ�
	int Collect( int &rPlayerAP, CTemplateCollect *pCollectNpc, int &rDegreeValue, int nLevel, bool bAddNow = false );	

	// ��ȡ���ڵĳƺ�ID
	int GetCurrentTitleID();
public:
	// ��pb�ṹ���������б�
	void SetFromPB( PBLifeSkill &pbLifeSkill );	   

	// ���������б��pb�ṹ
	void CreatTlvPB( PBLifeSkill &pbLifeSkill );  	
	
};

class CPlayerLifeSkill
{
private:
	CLifeSkill mMainLifeSkill;
	CLifeSkill mSubLifeSkill;
	int mMaterialIndex[MATERIALINDEXNUM];
	int mMaterialID[MATERIALINDEXNUM];
public:
	CPlayerLifeSkill()
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

	int Initialize( )
	{
		for ( int i = 0; i < MATERIALINDEXNUM; ++i )
		{											
			mMaterialIndex[i] = -1;
		}	
		memset( mMaterialID, 0, sizeof( mMaterialID ) );
		return 0;		
	}
	int Resume(){ return 0; }
public:

	// ��ȡ�������
	CLifeSkill *GetMainLifeSkill(){ return &mMainLifeSkill; }

	// ��ȡ���������
	CLifeSkill *GetSubLifeSkill(){ return &mMainLifeSkill; }  

	// ��ȡ��ǰ��ѧ�ļ�������
	int	GetCurrentSkillKind( );								  

	// ����ĳ�������
	int ForgetLifeSKill( int nLifeSkillKind );

	// ������������ͻ�ȡ�����
	CLifeSkill *GetLifeSkillByType( int nLifeSkillType );

	// ������������������ȡ�����
	CLifeSkill *GetLifeSkillByKind( int nLifeSkillKind );

	// ���ò���
	int AddMaterial( int nBagIndex, int nPosIndex, int nItemID, int &rPreMaterialIndex );

	// ȡ�²���
	int TakeMaterial( int nPosIndex, int &rBagIndex );

	// �����䷽
	int CreatComPose( int nLifeSkillType,  int nValue, int &rComposeID, int nSkillKind );
	
	// ѧϰ�䷽
	int StudyCompose( int nComposeID );
	
	// ��ȡ�䷽���ϵ��б�
	int GetMaterialList( int *pIDList, int &rNum );
	
	// ���������Ϣ
	int ClearMaterial();  	
public:
	void SetFromPB( PBLifeSkillBox & pbLifeSkillBox );
	void CreatTlvPB( PBLifeSkillBox & pbLifeSkillBox );
};

// ���뱣�����

class CRolePassword
{
public:
	char mPassword[MAX_PASSWORD_LENGTH];	// ����
	int  mStatus;							// ��ǰ����״̬
	int	 mProtectTime;						// ��ȫ����ʱ��
	int	 mProtectTimeLength;				// ��ȫ����ʱ�䳤,�ͻ�������
	int  mEntityID;							// ��Ҷ���ID
public:
	CRolePassword()
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
		memset( mPassword, 0, sizeof( mPassword ) );
		mStatus = EM_PASSWORD_NOTSET;
		mProtectTime = 0;
		mProtectTimeLength = 0; 
		mEntityID = 0;
		return SUCCESS;
	}
	
	int Resume( ){ return SUCCESS; }
	
public:
	// ����&��ȡ����
	int SetPassword( const char *pPassword );
	
	const char *GetPassword(){ return mPassword; }		
	
	// ����&��ȡ����״̬
	void SetStatus( int nStatus ){ mStatus = nStatus; }
	int GetStatus();
	
	// ����&��ȡ��ȫ����ʱ��
	void SetProtectTime( int nProtectTime ){ mProtectTime = nProtectTime; }
	int GetProtectTime(  ){ return mProtectTime; }
	
	// ����&��ȡ��ȫ����ʱ��
	void SetProtectTimeLength( int nProTimeLength ){ mProtectTimeLength = nProTimeLength; }
	int	GetProtectTimeLength( ){ return mProtectTimeLength; }

	// �������ָ��
	void SetEntityID(int nEntityID) { mEntityID = nEntityID; }
	int GetEntityID() { return mEntityID; }
public:	
	
	// ��ʼ������״̬
	int InitialPass( const char *pPassword, int nProtectTime, int nProtectTimeLength, int nPwdStatus );	
	
	// ����Ƿ��Ѿ����˰�ȫ����ʱ��
	bool CheckProtectTime();
	
	// ����Ƿ�������ز���
	int CheckActionAllowed( EPassWordAction emAction );
	
	// ������
	bool CheckPassword( const char *pPassword );
	
	// �������
	void ClearPassword( );
};

// ʱ����Ϣ
class CExpTimeInfo
{
public:
	CExpTimeInfo()
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
	~CExpTimeInfo(){}
	
	int Resume()
	{
		return 0;
	}
	
	int Initialize()
	{
		mOffLineTimeLength = 0;
		mLastTimeLeaveGame = 0;
		mEffectiveOffTimeLength = 0;
		mLastEffectiveTimeLength = 0;
		mLastCalculateTime = 0;
		mBlakcPillID = 0;
		mBlackPillsTime = 0;	
		mExpFromOffLine = 0;
		return 0;
	}
public:
	// ����&��ȡ����ʱ��
	void SetOffLineTimeLength( int nTimeLength ){ mOffLineTimeLength = nTimeLength; }
	int GetOffLineTimeLength(){ return mOffLineTimeLength; }
	
	// ����&��ȡ���һ���뿪��Ϸ��ʱ��
	void SetLastTimeLeaveGame( int nTime ){ mLastTimeLeaveGame = nTime; }
	int GetLastTimeLeaveGame(){ return mLastTimeLeaveGame; }
	
	// ����&��ȡ��Ч����ʱ��
	void SetEffectiveOffTimeLength( int nTimeLength ){ mEffectiveOffTimeLength = nTimeLength; }
	int GetEffectiveOffTimeLength(){ return mEffectiveOffTimeLength; }
	
	// ����&��ȡ���һ�������Чʱ��ʱ��ʱ�䳤��
	void SetLastEffectiveTime( int nTimeLength ){ mLastEffectiveTimeLength = nTimeLength; } 
	int GetLastEffectiveTime(){ return mLastEffectiveTimeLength; }	
	
	// ����&��ȡ��һ�μ�����Ч����ʱ���ʱ��
	void SetLastCalculateTime( int nTime ){ mLastCalculateTime = nTime; }
	int GetLastCalculateTime(){ return mLastCalculateTime; }
	
	// ����&��ȡ�ڹ����ʱ��
	void SetBlackPillTime( int nBlackPillTime ){ mBlackPillsTime = nBlackPillTime; }
	int GetBlackPillTime(){ return mBlackPillsTime; }
	
	// ����&��ȡ�ڹ����ID
	void SetBlackPillID( int nID ){ mBlakcPillID = nID; }
	int GetBlackPillID(  ){ return mBlakcPillID; }

	// ����&��ȡ�����߻�õľ���
	void SetExpFromOffLine( int nID ){ mExpFromOffLine = nID; }
	int GetExpFromOffLine(  ){ return mExpFromOffLine; }
public:
	// ������Ч����ʱ��
	int AddEffectiveOffTimeLength( int nLoginTime, bool bVip = false );
	
	// �һ���Ч����ʱ��
	int ExchangeEffectiveOffLineTime( int nTime );

	// ������ʱ���þ���
	int GetExpFromOffLine( int nLevel );

	// �ɱ��ʻ�����߾���
	int GetExpByRate( int nExp );
	
	// �ڹ���ʱ��һ��ɾ���
	int ExchangeOffLineTimeToExp( int nLevel, int &rExp, int &rOffLineTimeConsumed, int nBlackPillsID = 0 );	
	
	void SetFromPB( PBExpTimeInfo &rPBInfo );
	void CreatTlvPB( PBExpTimeInfo &rPBInfo );
		
private:
	int mOffLineTimeLength;				// ʵ������ʱ��
	int mLastTimeLeaveGame;				// ���һ���뿪��Ϸ��ʱ��						
	int mEffectiveOffTimeLength;		// ��Ч����ʱ��	
	int mLastEffectiveTimeLength;		// ��������Ч����ʱ��ʱ�����ڵ��ۼӳ���		
	int mLastCalculateTime;				// ��һ�μ�����Ч����ʱ���ʱ��
	int mBlackPillsTime;				// �ڹ����ʱ��
	int mBlakcPillID;					// �ڹ����ģ��ID
	int mExpFromOffLine;				// ����ʱ���ۺϵľ���
};

/************************************************************************/
/* �������                                                             */
/************************************************************************/

// cd��
class CGroupCD
{
public:
	CGroupCD()
	{
		if( CObj::msCreateMode )
		{
			Initialize();
		}
	}

	void Initialize() 
	{
		mGroupIdx = 0;
		mCDTime = 0;
		mTimerID = INVALID_OBJ_ID;
	}

	// cd����
	inline int GetCDGroupIdx( ) { return mGroupIdx; }
	inline void SetCDGroupIdx( int nIdx ) { mGroupIdx = nIdx; }

	// ȡ�ú�����ָ��cd�鶨ʱ��id
	inline int GetTimerID(  ) { return mTimerID; }
	inline void SetTimerID( int nTimerID ) { mTimerID =nTimerID; }

	// ȡ�ú����ö�ʱ��ʣ��cdʱ��
	inline int GetCDTime( ) { return mCDTime; }
	inline void SetCDTime( int nCDTime ) { mCDTime = nCDTime; }


private:
	int mGroupIdx;	// ������
	int mCDTime;	// cooldownʱ��
	int mTimerID;	// ��ʱ��ID

};


// cd�������
class CGroupCDList
{
private:
	CGroupCD	mGroupCD[CDGROUP];

public:
	
	void Initialize() 
	{
		for( unsigned int i = 0; i < ARRAY_CNT(mGroupCD); i++ )
		{
			mGroupCD[i].Initialize();
			mGroupCD[i].SetCDGroupIdx( i );
		}
	}

	int GetMaxGroupIdx( ) { return ARRAY_CNT(mGroupCD); }

	CGroupCD& GetGroupCD( int nIdx ) { return mGroupCD[nIdx]; }


	// ˢ��CD��ʱ��
	void RefreshCDTime();


};

class CWizard
{
public:
	int		mWizardPoint[ WIZARD_NUM ];				// �Ż�����
	int		mWizardValue[ WIZARD_NUM ];				// �Ż�ֵ
	int		mWizardSubmit[ WIZARD_NUM ];			// �Ż��ύ��
	int		mWizardIncrease[ WIZARD_NUM ];			// �Ż��ӵ�ֵ
	int		mTrend;									// �ɳ�����

	int		mCombatFame;							// ��������
	int		mRepeFame;								// ��������
	int		mCommonFame;							// ��������
	int		mCombatToday;							// ��������
	int		mRepeToday;								// ��������
	int		mCommonToday;							// ��������
	int		mCombatAll;								// �����ܻ��
	int		mRepeAll;								// �����ܻ��
	int		mCommonAll;								// �����ܻ��

public:
	void Initial( );

	void CreateFromTlv( PBWizard *pWizard );

	void GetTlvBuffer( PBWizard *pWizard );

	// �Ż���������
	int AddPoint( int vType );

	// �Ż�ֵ����,
	void AddValue( int vType, int vValue );

	int Submit( );

	void Clear( );

	inline int GetWizardPoint( int vType )
	{ 
		if ( vType < 0 || vType > WIZARD_NUM )
		{
			return 0;
		}
		return mWizardPoint[ vType ];
	}
	inline int GetWizardValue( int vType )
	{ 
		if ( vType < 0 || vType > WIZARD_NUM )
		{
			return 0;
		}
		return mWizardValue[ vType ];
	}
	inline int GetWizardSubmit( int vType )
	{ 
		if ( vType < 0 || vType > WIZARD_NUM )
		{
			return 0;
		}
		return mWizardSubmit[ vType ];
	}
	inline int GetWizardIncrease( int vType )
	{ 
		if ( vType < 0 || vType > WIZARD_NUM )
		{
			return 0;
		}
		return mWizardIncrease[ vType ];
	}
	inline void SetWizardSubmit( int vType, int vValue )
	{
		if ( vType < 0 || vType > WIZARD_NUM )
		{
			return;
		}
		mWizardSubmit[ vType ] = vValue;
	}
	inline int GetTrend( ){ return mTrend; }
	inline void SetTrend( int vTrend ){ mTrend = vTrend; }

	inline int GetCombatFame( ){ return mCombatFame; }
	inline void SetCombatFame( int vCombatFame ){ mCombatFame = std::min( vCombatFame, FAME_TOTAL_LIMIT ); }
	inline int GetRepeFame( ){ return mRepeFame; }
	inline void SetRepeFame( int vRepeFame ){ mRepeFame = std::min( vRepeFame, FAME_TOTAL_LIMIT ); }
	inline int GetCommonFame( ){ return mCommonFame; }
	inline void SetCommonFame( int vCommonFame ){ mCommonFame = std::min( vCommonFame, FAME_TOTAL_LIMIT ); }

	inline int GetCombatToday( ){ return mCombatToday; }
	inline void SetCombatToday( int vCombatToday ){ mCombatToday = vCombatToday; }
	inline int GetRepeToday( ){ return mRepeToday; }
	inline void SetRepeToday( int vRepeToday ){ mRepeToday = vRepeToday; }
	inline int GetCommonToday( ){ return mCommonToday; }
	inline void SetCommonToday( int vCommonToday ){ mCommonToday = vCommonToday; }

	inline int GetCombatAll( ){ return mCombatAll; }
	inline void SetCombatAll( int vCombatAll ){ mCombatAll = vCombatAll; }
	inline int GetRepeAll( ){ return mRepeAll; }
	inline void SetRepeAll( int vRepeAll ){ mRepeAll = vRepeAll; }
	inline int GetCommonAll( ){ return mCommonAll; }
	inline void SetCommonAll( int vCommonAll ){ mCommonAll = vCommonAll; }

	inline int AddCombatFame( int vDeltaFame )
	{
		if ( vDeltaFame < 0 )
			return 0;
		if ( mCombatToday >= CDataStatic::GetFameLimit( FAME_TYPE_COMBAT ) )
			return 0;
		if ( mCombatFame >= FAME_TOTAL_LIMIT )
			return 0;
		int tOldFame = mCombatFame;
		int tOldToday = mCombatToday;
		int tCombatTemp = std::min( mCombatFame + vDeltaFame, FAME_TOTAL_LIMIT );
		int tDeltaAll = tCombatTemp - tOldFame;
		mCombatToday += tDeltaAll;
		mCombatToday = std::min( mCombatToday, CDataStatic::GetFameLimit( FAME_TYPE_COMBAT ) );
		int tDeltaToday = mCombatToday - tOldToday;		
		mCombatFame += std::min( tDeltaToday, tDeltaAll );
		mCombatAll += std::min( tDeltaToday, tDeltaAll );
		return mCombatFame - tOldFame;
	}

	inline int DelCombatFame( int vDeltaFame )
	{
		if ( vDeltaFame < 0 )
			return 0;
		int tOldFame = mCombatFame;
		mCombatFame -= vDeltaFame;
		mCombatFame = std::max( 0, mCombatFame );
		return mCombatFame - tOldFame;
	}

	inline int AddRepeFame( int vDeltaFame )
	{
		if ( vDeltaFame < 0 )
			return 0;
		if ( mRepeToday >= CDataStatic::GetFameLimit( FAME_TYPE_REPE ) )
			return 0;
		if ( mRepeFame >= FAME_TOTAL_LIMIT )
			return 0;
		int tOldFame = mRepeFame;
		int tOldToday = mRepeToday;
		int tRepeTemp = std::min( mRepeFame + vDeltaFame, FAME_TOTAL_LIMIT );
		int tDeltaAll = tRepeTemp - tOldFame;
		mRepeToday += tDeltaAll;
		mRepeToday = std::min( mRepeToday, CDataStatic::GetFameLimit( FAME_TYPE_REPE ) );
		int tDeltaToday = mRepeToday - tOldToday;		
		mRepeFame += std::min( tDeltaToday, tDeltaAll );
		mRepeAll += std::min( tDeltaToday, tDeltaAll );
		return mRepeFame - tOldFame;
	}

	inline int DelRepeFame( int vDeltaFame )
	{
		if ( vDeltaFame < 0 )
			return 0;
		int tOldFame = mRepeFame;
		mRepeFame -= vDeltaFame;
		mRepeFame = std::max( 0, mRepeFame );
		return mRepeFame - tOldFame  ;
	}

	inline int AddCommonFame( int vDeltaFame )
	{
		if ( vDeltaFame < 0 )
			return 0;
		if ( mCommonToday >= CDataStatic::GetFameLimit( FAME_TYPE_COMMON ) )
			return 0;
		if ( mCommonFame >= FAME_TOTAL_LIMIT )
			return 0;
		int tOldFame = mCommonFame;
		int tOldToday = mCommonToday;
		int tCommonTemp = std::min( mCommonFame + vDeltaFame, FAME_TOTAL_LIMIT );
		int tDeltaAll = tCommonTemp - tOldFame;
		mCommonToday += tDeltaAll;
		mCommonToday = std::min( mCommonToday, CDataStatic::GetFameLimit( FAME_TYPE_COMMON ) );
		int tDeltaToday = mCommonToday - tOldToday;		
		mCommonFame += std::min( tDeltaToday, tDeltaAll );
		mCommonAll += std::min( tDeltaToday, tDeltaAll );
		return mCommonFame - tOldFame;
	}

	inline int DelCommonFame( int vDeltaFame )
	{
		if ( vDeltaFame < 0 )
			return 0;
		int tOldFame = mCommonFame;
		mCommonFame -= vDeltaFame;
		mCommonFame = std::max( 0, mCommonFame );
		return mCommonFame - tOldFame;
	}
};

// ���Ҫ�Ľ���ָ������
class CTodayGuideData
{
public:
	int		mLevelBak;	// ���յȼ�����
	unsigned long long		mExpBak  ;	// ���վ�������
	int		mHonorBak;	// ���չ�ѫ����
	int		mAchiveBak;	// ���ճɾ͵�������
	int		mKillBak ;	// ����������ɱ����
	CTodayGuideData()
	{
		if ( CObj::msCreateMode )
		{
			mLevelBak = 0;
			mExpBak   = 0;
			mHonorBak = 0;
			mAchiveBak= 0;
			mKillBak  = 0;
		}
	}
	void GetPB( PBGuideData* pData )
	{
		if ( pData != NULL )
		{
			pData->set_achivebak(mAchiveBak);
			pData->set_expbak(mExpBak);
			pData->set_honorbak(mHonorBak);
			pData->set_killbak(mKillBak);
			pData->set_levelbak(mLevelBak);
		}
	}

	void CreateFromPB( PBGuideData* pData )
	{
		if ( pData != NULL )
		{
			mAchiveBak = pData->achivebak();
			mExpBak = pData->expbak();
			mHonorBak = pData->honorbak();
			mKillBak = pData->killbak();
			mLevelBak = pData->levelbak();
		}
	}
};

// ���˴��������� ������Ը��˵�XX����
typedef lk::hash_map<unsigned int, int, MAX_TIMER_MGR_LINE> PERSONAL_TIMES_MGR_TYPE;
class CPersonalTimesMgr
{
private:
	PERSONAL_TIMES_MGR_TYPE mPersonalData;
public:
	CPersonalTimesMgr()
	{
		if(CObj::msCreateMode)
		{
			mPersonalData.initailize();
		}
	}

	// ����0 �ɹ�
	int Tick(unsigned int vKey)
	{
		PERSONAL_TIMES_MGR_TYPE::iterator it = mPersonalData.find(vKey);
		if ( it == mPersonalData.end() )
		{
			std::pair<PERSONAL_TIMES_MGR_TYPE::iterator, bool> ret = 
				mPersonalData.insert( std::pair<unsigned int, int>(vKey, 1) );
			if (!ret.second)
				return -1;
		}
		else
		{
			++ it->second;
		}
		return 0;
	}

	int GetTimes(unsigned int vKey)
	{
		PERSONAL_TIMES_MGR_TYPE::iterator it = mPersonalData.find(vKey);
		if ( it == mPersonalData.end() )
			return 0;
		return it->second;
	}

	void SetTimes(unsigned int vKey, int nVal)
	{
		PERSONAL_TIMES_MGR_TYPE::iterator it = mPersonalData.find(vKey);
		if ( it == mPersonalData.end() )
		{
			mPersonalData.insert(std::pair<unsigned int, int>(vKey, nVal) );
		}
		else
		{
			it->second = nVal;
		}
	}

	void GetPB( PBTimes* pPB )
	{
		if ( pPB == NULL )
			return;

		for ( PERSONAL_TIMES_MGR_TYPE::iterator it = mPersonalData.begin(); it != mPersonalData.end(); ++it )
		{
			PBSingleTimes* tpPB = pPB->add_timesinfo();
			tpPB->set_key(it->first);
			tpPB->set_value(it->second);

			LOG_DEBUG("pro", "SAVE TIMES key=0x%x val=%d", it->first, it->second );
		}
	}

	void CreateFromPB( PBTimes* pPB )
	{
		if ( pPB == NULL )
			return;
		for ( int i = 0; i < pPB->timesinfo_size(); ++i )
		{
			PBSingleTimes tpPB = pPB->timesinfo(i);
			mPersonalData.insert(std::pair<unsigned int, int>(tpPB.key(), tpPB.value()) );

			LOG_DEBUG("pro", "LOAD TIMES key=0x%x val=%d", tpPB.key(), tpPB.value() );
		}
	}

	static unsigned int MakeKey( unsigned int vType, int nParam )
	{
		unsigned int tRet = vType;
		tRet = tRet << 24;
		tRet |= nParam;
		return tRet;
	}
};

// ÿ����ҵĻ����
class  SinglePlayerActivityInfo
{
public:
	int nState;
	int nParam1;
	int nParam2; 
	int nParam3; // �ͺ���2�� ��ʾ�Ƿ��Ѿ���ȡ
	int nRealLastedTime; // ��ʵ�ĳ���ʱ��  ��������ڷǴ��̵ĵط���ֻ����
	int nLastedSavedTime; // ���ε�¼��ǰ��ʱ�� ��load���ݵ�ʱ���޸� ������
	bool bIsChanged ; // �Ƿ��ڱ�������֮ǰ�Ĺ�״̬
	time_t chg_tm; // ʱ���
	SinglePlayerActivityInfo()
	{
		nState=0;
		nParam1=0;
		nParam2=0; 
		nParam3=0; 
		nRealLastedTime=0; 
		nLastedSavedTime=0;
		chg_tm=time(0);
		bIsChanged=false;
	}
	int GetDuringTime(CEntityPlayer* pPlayer); // �õ��ӻ��ʼ�������߹���ʱ��

};

typedef lk::hash_map<int, SinglePlayerActivityInfo, HELPID_SIZE> ACTIVITYINFO_TYPE;

class CPlayerActivityInfo
{
public: 
	// first:�ID
	ACTIVITYINFO_TYPE mStates;
	time_t			  mLastSave;
	CPlayerActivityInfo()
	{
		mStates.initailize();
		mLastSave=time(0);
	}

	SinglePlayerActivityInfo* GetActivityInfo( int nActivityID )
	{
		ACTIVITYINFO_TYPE::iterator it = mStates.find(nActivityID);
		if ( it == mStates.end() )
		{
			return NULL;
		}
		else
		{
			return &(it->second);
		}
	}

	void UpdateActivityInfo( int nActivityID, SinglePlayerActivityInfo& rInfo )
	{
		ACTIVITYINFO_TYPE::iterator it = mStates.find(nActivityID);
		if ( it == mStates.end() )
		{
			//rInfo.nParam3=0;
			mStates.insert(std::pair<int, SinglePlayerActivityInfo>(nActivityID, rInfo) );
		}
		else
		{
			// ���״̬û�� �����3�����ϵ� ��ôд���ð�������
			if (rInfo.nState == it->second.nState)
				rInfo.nParam3=it->second.nParam3;
			it->second = rInfo;
		}
	}
};

// �۱���Ķһ���Ϣ
class  CTreasureBowlInfo
{
public:
	typedef lk::hash_map< int, int, TREASUREBOWL_DAILYEXCHANGENUM > CTreasureBowlList;	// �۱���۱���Ʒ
public:
	enum
	{
		CTREASUREBOWL_TIMELIMIT			= 1,	// ʹ����Ʒ�۱�ʱ����Ʒ�Ѿ��ﵽ��Ȼ������
		CTREASUREBOWL_TOTALTIMELIMIT	= 2,	// ʹ����Ʒ�۱�ʱ�Ѿ��ﵽ���۱�����
	};
public:
	CTreasureBowlInfo()
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
	int  Initialize();
	int	 Resume(){ return 0; }
public:
	// ��ȡ&�������һ�ξ۱���ʱ��
	int GetExchangeTime(){ return mExchangeTime; }
	void SetExchangeTime( int nTime ) { mExchangeTime = nTime; }
	
	// ��ȡ&���õ���۱��Ĵ���
	int GetTotalNum(){ return mTotalNum; }
	void SetTotalNum( int nNum ){ mTotalNum = nNum; }
public:
	// ˢ�¾۱��һ���ʱ��
	int RefreshExchangeTime();
	
	// ���ĳ����Ʒ�Ƿ�����پ۱�
	int CheckExchangeItem( int nTotalMaxTimes, int nMaxTimes, int nItemID ); 	
	
	// �������ھ۱���ĳ����Ʒ��Ϣ
	int SetExchangeItem( int nItemID );
	
	// �����ҵľ۱���Ϣ
	int ClearTreasureBowlList();	
	
	// ��ȡĳ����Ʒ�۱���Ϣ
	int GetExchangeItem( int nItemID, int &rUsedTimes );
public:
	
	void SetFromPB( PBTreasureBowl &rTreasureBowl );	
	void CreateTlvPB( PBTreasureBowl &rTreasureBowl );	
private:
	int mTotalNum;
	int mExchangeTime;
	CTreasureBowlList mTreasurebowlList;		    
};

//�����ϵ����Ϣ
class CSpiritTypeInfo
{
private:
	int	m_anSlotOpenStatus[MAX_CASTINGSPIRIT_SLOT];
	int	m_anCastingItemID[MAX_CASTINGSPIRIT_SLOT];
	int	m_anBindStatus[MAX_CASTINGSPIRIT_SLOT];

public:
	CSpiritTypeInfo();
	// ��ȡ�����ÿ���״̬
	int GetSlotOpenStatus(int nSlotIndex);
	void SetSlotOpenStatus(int nSlotIndex, int nStatus);

	// ��ȡ�����������õĵ���id
	int GetCastingItemID(int nSlotIndex);
	void SetCastingItemID(int nSlotIndex, int nItemID);	

	// ��ȡ������������ߵİ�״̬
	int GetBindStatus(int nSlotIndex);
	void SetBindStatus(int nSlotIndex, int nBindStatus);
};

// ����Ĳ�λ��Ϣ
class CSpiritPositionInfo
{
private:
	CSpiritTypeInfo m_SpiritTypeInfo[MAX_CASTINGSPIRIT_TYPE];

public:
	CSpiritPositionInfo();
	// ��ȡ�����ÿ���״̬
	int GetSlotOpenStatus(int nTypeIndex, int nSlotIndex);
	void SetSlotOpenStatus(int nTypeIndex, int nSlotIndex, int nStatus);

	// ��ȡ�����������õĵ���id
	int GetCastingItemID(int nTypeIndex, int nSlotIndex);
	void SetCastingItemID(int nTypeIndex, int nSlotIndex, int nItemID);

	// ��ȡ������������ߵİ�״̬
	int GetBindStatus(int nTypeIndex, int nSlotIndex);
	void SetBindStatus(int nTypeIndex, int nSlotIndex, int nBindStatus);
};

class CSpiritInfo
{
private:
	CSpiritPositionInfo m_PositionInfo[MAX_CASTINGSPIRIT_POSITION];

public:
	// ��ȡ�����ÿ���״̬
	int GetSlotOpenStatus(int nPositionIndex, int nTypeIndex, int nSlotIndex);
	void SetSlotOpenStatus(int nPositionIndex, int nTypeIndex, int nSlotIndex, int nStatus);

	// ��ȡ�����������õĵ���id
	int GetCastingItemID(int nPositionIndex, int nTypeIndex, int nSlotIndex);
	void SetCastingItemID(int nPositionIndex, int nTypeIndex, int nSlotIndex, int nItemID);
	
	// PB���ڴ�����ת��
	void SetFromPB(PBSpiritInfo& rPBSpiritInfo);	
	void CreateTlvPB(PBSpiritInfo& rPBSpiritInfo);

	// �õ���ϵ������Ӱ��ֵ
	int GetEffectValue(int nSpiritType);

	// ��ȡ������������ߵİ�״̬
	int GetBindStatus(int nPositionIndex, int nTypeIndex, int nSlotIndex);
	void SetBindStatus(int nPositionIndex, int nTypeIndex, int nSlotIndex, int nBindStatus);

	// �õ�������
	int GetScore();

	// �õ���������������׵�����
	int GetSlotInfo(int& rnOpenedSlotCount, int& rnCastedSlotCount);
};

class CPropertyPlayer : public CPropertyCharacter
{
public:
	typedef lk::vector< unsigned int , ITEM_FREE_COUNT > ItemForFreeMap;

	// ���۸�NPC�����б�
	typedef lk::vector< SaleItem, ITEM_BUYBACK_MAX > SaleItemList;

	typedef lk::set< int, (CARDBOOK_TYPE * CARDBOOK_NUM) > CardList;

	struct ST_TITLE
	{
		int mTitleID;
		int mTime;
		ST_TITLE(){ mTitleID = 0; mTime = 0; }
	};

	typedef lk::vector< ST_TITLE, TITLEMAX_SELF > TitleList;
	typedef lk::vector<ComplexPos, TELE_LIST_SIZE> TELE_LIST_TYPE;

	struct ST_AWARD
	{
		int mAwardID;
		int mTimes;
		ST_AWARD(){ mAwardID = 0; mTimes = 0; }
		ST_AWARD( int vAwardID, int vTimes ){ mAwardID = vAwardID; mTimes = vTimes; }
	};
	typedef lk::vector< ST_AWARD, MAX_AWARD_NUM > AwardList;

	typedef lk::vector< int, MAX_MATRIX_MENBER > MatrixList;
protected:
	unsigned long long				mExp;				// ����
	unsigned short					mSex;				// �Ա�
	unsigned short					mRemainPoint;		// ʣ�����Ե�
	unsigned short					mSkillPoint;		// ʣ�༼�ܵ�
	unsigned short					mCurStr;			// ����
	unsigned short					mCurWis;			// ����
	unsigned short					mCurSta;			// ����
	unsigned short					mCurCon;			// ����
	unsigned short					mCurSpr;			// ����
	int								mMoney;				// ���
	int								mBindMoney;			// �������X
	int								mStorageMoney;		// �ֿ�洢��Ǯ
	int								mStorageBindMoney;	// �ֿ�洢�󶨽�Ǯ
	unsigned int					mTalkNpcEntityID;	// ��ҵ�ǰ�Ի�NPCID
	EService						mServiceStatus;		// ��ҷ���״̬
	CProduce						mProduce;			// �������״̬
	CGroupCDList					mCDGroup;			// CD��
	int             				mCommonCD;			// ������ȴʱ��
	CEquipment						mEquipment;			// װ��
	CBaggage						mBaggage;			// ����
	CItemBox						mTaskBaggage;		// ������߰���
	CStorage						mStorage;			// �ֿ�
	CSkillListInstance<11>			mEquipSkill;		// װ�������б�
	CShortcutList					mShortcut;			// ��ҿ����
	unsigned int					mProLevel;			// �����ȼ�
	unsigned int					mProExp;			// ��������
	ComplexPos						mTownPos;			// �سǵ�����		
	TELE_LIST_TYPE					mTeleList;	// ���͵��ߴ��͵��б�		
	ItemForFreeMap                  mItemForFreeList;	// ��Ŵ��ڰ󶨽��״̬����Ʒ��ָ��
	int								mStorageStatus;		// �ֿ�״̬
	int								mHonor;				// ��ѫ
	int								mTodayHonor;		// ���չ�ѫ
	int								mInHonPerDay;		// �����õĹ�ѫֵ
	int								mOutHonPerDay;		// ÿ���ṩ�Ĺ�ѫ��
	int								mLastObjID;			// ��һ�β������Ʒ
	int								mSaveDate;			// ��¼��һ��ˢ�µ�����
	KillData						mKill[ 30 ];		// ��ɱ��Ϣ
	int								mDiploidTime;		// ��ȡ��˫������ʱ��ɱ������ʷ��¼
	CPlayerRepetion					mRepetion;
	int								mValidDiploid;		// ��Ч��˫��ʱ��
	int								mDailyWelfareStatus;// �ǲ����Ѿ���ȡ��ÿ�ո�����״̬��־		
	int								mHasRedStoneStatus;	// �Ƿ�����ڵ�״̬�ı�־
	unsigned int					mRedStoneID;		// ���ʹ���ڵ����Ҵ��ڶ���״̬ʱΪ�ڵ�ID������Ϊ0
	int								mAnswerStatusObjID;	// 	
	int								mKillNumOut;		// ɱ����(�ڹ���)
	int								mKillNumIn;			// ɱ����(�ڹ���)
	int								mLastRefreshTime;	// �ϴ�ˢ˫ʱ��	
	int								mCompletedTasks;	// ������������
	int								mDieNum	;			// ��������
	CPlayerLifeSkill				mPlayerLifeSkill;	// ��������	
	CSkillListInstance<250>			mSkill;				// �����б�		Ϊ��ħ־���ӵ�250
	CTreasureBowlInfo				mTreasureBowlInfo;	// �۱�����Ϣ
	CSpiritInfo						m_SpiritInfo;		// ������Ϣ
public:																
	bool							mYellowStatus;			// �Ƿ����
	// �ڹ�ʱ��Ҫ�����ҩƷģ��ID
	bool							mInAutoPlay;			// �Ƿ��Զ��һ�
	int								mDiploidState[ MAX_DIPLOIDSTATE ];	// 0:�Ƿ���˫״̬;1:�Ƿ񶳽�;2:��ʱ��ID;
																		// 3:��ʱ��ֹͣʱ��(����);4:��ȡ��ʣ��˫��ʱ�� 
	SaleItemList					mSaleItem;				// �۳���NPC�ĵ���
	CStallInfo						mStallInfo[3];				// ��̯��¼

	int								mResetPPNum;			// ��ǰ�������Ե����
	int								mResetSPNum;			// ��ǰ���ü��ܵ����
	int								mLastResetPPIndex;		// ���һ���������Ե���INDEX
	int								mLastResetSPIndex;		// ���һ�����ü��ܵ���INDEX
	int								mReduceLevel;			// ����װ������ȼ�
	StateList						mAttackList;			// ���е�����״̬
	StateList						mDefenceList;			// �����е�����״̬
	StateList						mDeathList;				// ����������״̬
	StateList						mReduceHPList;			// ��Ѫ������״̬
	int								mAttackStateTime;		// ��������Ч������ȴʱ��
	int								mDefenceStateTime;		// ����������Ч������ȴʱ��
	int								mDeathStateTime;		// ��������Ч������ȴʱ��
	int								mReduceHPStateTime;		// ��Ѫ����Ч������ȴʱ��
			
	int								mLastFamilyApplyTime;	// ��������������ʱ��
	int		 						mLastTimeLeaveFamily;	// ���һ���뿪�����ʱ��	

	int								mPKValue;				// PK ֵ
	EPKStatus						mPKStatus;				// PK״̬(�ף������ƣ���)
	int								mYellowTimer;			// ��������ʱ
	CardList						mActiveCardList;		// �Ѽ���Ŀ�Ƭ�б�	
	CardList						mOwnCardList;			// ���ռ��Ŀ�Ƭ�б�
	int								mPrisonTime;			// �ڼ���������Ϸʱ��
	int								mPrisonTotalTime;		// ������������
	unsigned int					mLastWeeklyDisposTime;	// �ϴδ���ÿ���¼�ʱ��
	unsigned int					mLastDaylyDisposTime;	// �ϴδ���ÿ���¼�ʱ��

	// �������
	unsigned char					mAssignExpScl;			// ��־����������� �ٷֱ�

	int								mTalentExp;				// ��Ϊֵ
	int								mTalentPoint;			// �컯��
	CSkillListInstance<100>			mTalentSkill;			// �컯����
	int								mTalentStep;			// ��ǰ�컯С��
	int								mTalentStudy;			// ��ǰС����Ͷ����컯��
	int								mTalentLevel;			// ���컯�ȼ�

	int								mCurrentTitle;			// ��ǰ�ƺ�
	TitleList						mTitleList;// �ƺ��б�
	CSkillListInstance<6>			mTitleSkill;			// �ƺż���
	int								mLastRefreshApTime;		// ��һ��ˢ��AP��ʱ��

	CYuanBao						mGoldenYB;				// ��Ԫ��
	CYuanBao						mSilverYB;				// ��Ԫ��


	// ���а�Ҫͳ�Ƶ���Ŀ��
	int								mOriginReliveTimes;		// ԭ�ظ������
	int								mKillSameNationNum;		// ɱ����Ӫ����
	int								mKillOgreNum;			// ɱ����
	int								mUpFailNum;				// ����ʧ�ܴ���
	int								mTodayKillEnemyNumIn;		// �����ڹ���ɱ�е�����(����)
	int								mTodayKillEnemyNumOut;		// �����ڹ���ɱ�е�����(����)
	
	int								mDecompoundEquipIndex;		// ���ֽ��װ������

	// �Ż�ϵͳ������
	CWizard							mWizard;

	int								mLastJudgeTime;			// �ϴ�����ʱ��

	int								mVipFlag;				// ��Ա��ʾ����ͨ��Ա���м���Ա���߼���Ա
	int								mVipEndDate;			// ��Ա��������
	AwardList						mAwardList[EALT_Max];	// �����б�
	MatrixList						mMatrixList;			// ������
	int								mMasterID[ MAX_MASTER_NUM ];  // ǰ��ID
	int								mSlaveValue[ MAX_MATRIX_LEVEL ];// ��Ե��ֵ
	int								mSlavePoint;			// ��Ե����
	int								mMasterPoint;			// ʦ�»���
	int								mSlaveNum;				// ��ʦ����
	int								mSlaveTotal;			// ��Ե�ܼ�
	int								mMasterTotal;			// ʦ���ܼ�
	int								mMasterPercent[ MAX_MASTER_NUM ];	// �ж�����
	int								mBeginnerNum;			// ���ֵ�������
	int								mFormalNum;				// ��ʽ��������
	int								mMasterTimes;			// ��ʦ����
	int								mMasterGive;			// �ܼƸ���ʦ��
	CRolePassword					mRolePassword;			// ��ɫ����
	int								mCharmValue;			// ����ֵ
	int								mWeekIncCharm;			// �����ۼƻ������ֵ
	int								mLastWeekIncCharm;		// �����ۼƻ������ֵ
	CTodayGuideData					mGuideData;				// ����ָ������
	CPersonalTimesMgr				mTimesMgr;			// ���˴���������
	
	int								mProgressFunc;		// �������ڶ���Ĺ���ģ��
	uint64_t						mProgressStartTime;	// ���뿪ʼ�ĵ�ʱ��
	int								mInvestStatus;		// �����ʾ�״̬
	int								mTotalWar;			// ��ս�ۼ�ս��
	int								mTodayWar;			// ���ι�սս��
	int								mTodayOther;		// ��������ս��
	int								mFreeWar;			// �ۼƿ�֧��ս��
	int								mWarKill;			// ��ս������ɱ
	int								mWarSerial;			// ��ǰ��ս�ƴ�
	int								mExpHonor;			// �����Ѷһ���������
	int								mItemHonor;			// �����Ѷһ���Ʒ����
	int								mHasVoted;			// ������ͶƱ����

	CPlayerExchange				mExange;
	CExpTimeInfo				mExpTimeInfo;			// ���߾�����Ϣ
	CPlayerActivityInfo			mActivityInfo;			// ���Ϣ

    int                         miIsShowFashion;        // �Ƿ���ʾʱװ
    int                         miIsShowEquip;          // �Ƿ�ɲ�ѯװ����Ϣ

public:
    inline void SetIsShowFashion( int nIsShowFashion ){ miIsShowFashion = nIsShowFashion; }
    inline int  GetIsShowFashion(  ) { return miIsShowFashion; }
    inline void SetIsShowEquip( int nIsShowEquip ){ miIsShowEquip = nIsShowEquip; }
    inline int  GetIsShowEquip(  ) { return miIsShowEquip; };

	CPlayerExchange* GetPlayerExchange( ){ return &mExange; }

	inline void SetTotalPrisonTime( int nTime ) { mPrisonTotalTime = nTime; }
	inline int  GetTotalPrisonTime() { return mPrisonTotalTime; }

	inline void SetLastJudgeTime( int nTime ){ mLastJudgeTime = nTime; }
	inline int  GetLastJudgeTime(){ return mLastJudgeTime; }

	inline void SetResetPPNum( int nNum ) { mResetPPNum = nNum; }
	inline void SetResetSPNum( int nNum ) { mResetSPNum = nNum; }
	inline void SetLastResetSPIndex( int nIdx ) { mLastResetSPIndex = nIdx; }
	inline void SetLastResetPPIndex( int nIdx ) { mLastResetPPIndex = nIdx; }

	inline int GetResetPPNum() { return mResetPPNum; }
	inline int GetResetSPNum() { return mResetSPNum; }
	inline int GetLastResetSPIndex() { return mLastResetSPIndex; }
	inline int GetLastResetPPIndex() { return mLastResetPPIndex; }
	CPlayerLifeSkill *GetPlayerLifeSkill(){ return &mPlayerLifeSkill; }

	inline void SetAutoPlayFlag( bool nFlag ){ mInAutoPlay = nFlag; }
	inline bool GetAutoPlayFlag() { return mInAutoPlay; }

	inline int GetOriginReliveTimes() { return mOriginReliveTimes;}
	inline void SetOriginReliveTimes( int nValue) { mOriginReliveTimes = nValue;}

	inline int GetKillSameNationNum() { return mKillSameNationNum;}
	inline void SetKillSameNationNum( int nValue) { mKillSameNationNum = nValue;}

	inline int GetKillOgreNum() { return mKillOgreNum;}
	inline void SetKillOgreNum( int nValue) { mKillOgreNum = nValue;}

	inline int GetUpFailNum() { return mUpFailNum;}
	inline void SetUpFailNum( int nValue) { mUpFailNum = nValue;}

	inline int GetTodayKillEnemyNumIn() { return mTodayKillEnemyNumIn; }
	inline int GetTodayKillEnemyNumOut() { return mTodayKillEnemyNumOut; }
	inline void SetTodayKillEnemyNumIn(int nValue) { mTodayKillEnemyNumIn = nValue; }
	inline void SetTodayKillEnemyNumOut(int nValue) { mTodayKillEnemyNumOut = nValue; }

	inline int GetCharmValue() { return mCharmValue; }
	inline void SetCharmValue( int nVal ) { mCharmValue = nVal; }

	inline int GetWeekIncCharm() { return mWeekIncCharm; }
	inline void SetWeekIncCharm( int nVal ) { mWeekIncCharm = nVal; }

	// ������ܵ�����
	inline int GetLastWeekIncCharm() { return mLastWeekIncCharm; }
	inline void SetLastWeekIncCharm( int nVal ) { mLastWeekIncCharm = nVal; }
	
	// ����&��ȡ���ڶ���Ĺ���ģ��
	void SetProgressFunc( int nProgressFunc ){ mProgressFunc = nProgressFunc; }
	int	GetProgressFunc(  ){ return mProgressFunc; } 

	// ����&��ȡ����Ŀ�ʼʱ��
	void SetProgressStartTime( uint64_t rTime ){ mProgressStartTime = rTime; }
	uint64_t GetProgressStartTime(){ return mProgressStartTime; }
	void ClearPropTelet(){ mTeleList.clear();}
	
	// �������Ƿ���ȷ
	bool CheckProgressTime( int nFuncType, int nNetSpeed, bool bUseConfigTime = true, int nProgressTime = 0 );

	inline CTodayGuideData* GetGuideData() { return &mGuideData; }
	inline CPersonalTimesMgr* GetTimesMgr() { return &mTimesMgr; }
	// �������ݿ�ṹ����


	// ������Ϣblob
	char* GetRoleBasicBlobStr( );
	void CreateBasicInfoFromTlv( PBPlayerBasicInfo* pBasicInfo );
	void GetBasicInfoTlvBuffer( PBPlayerBasicInfo* pBasicInfo );

	// �洢����ϵͳ�������
	void CreateCharmInfoFromTlv( PBCharm* pInfo );
	void GetCharmInfoTlvBuffer( PBCharm* pInfo );
	void CreateTimesInfoFromTlv( PBTimes* pInfo );
	void GetTimesInfoTlvBuffer( PBTimes* pInfo );

	// ����blob
	char* GetRoleSkillBlobStr(	);

	// Buff blob
	char* GetRoleBuffBlobStr( );

	// ���� blob
	char* GetRolePackageBlobStr( );

	// װ��blob
	char* GetRoleEquipBlobStr( );

	// �ֿ�blob
	char* GetRoleStorageBlobStr( );

	// ����blob
	char* GetRoleTaskPackageBlobStr( );

	// CD��blob
	char* GetRoleCDGroupBlobStr( );
	void CreateCDGroupFromTlv( PBPlayerCDGroupInfo* pCDGroup );
	void GetCDGroupTlvBuffer( PBPlayerCDGroupInfo* pCDGroup );

	// ������Ϣblob
	char* GetRoleTelePosBlobStr( );
	void CreateTelePosFromTlv( PBTelePosInfo* pTelePos );
	void GetTelePosTlvBuffer( PBTelePosInfo* pTelePos );

	// PVP blob
	char* GetRolePvPBlobStr( );
	void CreatePvPBlobInfoFromTlv( PBPlayerPVPInfo* pPvPInfo );
	void GetPvPBlobInfoTlvBuffer( PBPlayerPVPInfo* pPvPInfo );

	// Title blob
	char* GetRoleTitleBlobStr( );
	void CreateTitleInfoFromTlv( PBPlayerTitleInfo* pTitleInfo );
	void GetTitleInfoTlvBuffer( PBPlayerTitleInfo* pTitleInfo ); 

	// Activity blob
	char* GetRoleActivityBlobStr( );
	void CreateActivityInfoFromTlv( PBPlayerActivityInfo* pActivityInfo );
	void GetActivityInfoTlvBuffer( PBPlayerActivityInfo* pActivityInfo, bool bRealSave=false );

	SinglePlayerActivityInfo* GetActivityInfo( int nActivityID )
	{
		return mActivityInfo.GetActivityInfo( nActivityID );
	}

	void UpdateActivityInfo( int nActivityID, SinglePlayerActivityInfo& rInfo )
	{
		mActivityInfo.UpdateActivityInfo( nActivityID, rInfo );
	}

	// �컯blob
	char* GetRoleTalentBlobStr( );
	void CreateTalentInfoFromTlv( PBPlayerTalentInfo* pTalentInfo );
	void GetTalentInfoTlvBuffer( PBPlayerTalentInfo* pTalentInfo );

	// mw blob
	char* GetRoleMWBlobStr( );
	void CreateMWInfoFromTlv( PBPlayerMWInfo* pMWInfo );
	void GetMWInfoTlvBuffer( PBPlayerMWInfo* pMWInfo );

	// �����blob
	char* GetRoleLifeSkillBlobStr( );


	// ��ħ־blob
	char* GetRoleMonsterBlobStr( );
	void CreateMonsterInfoFromTlv( PBMonsterRecordInfo* pMonster);
	void GetMonsterRecordInfoTlvBuffer( PBMonsterRecordInfo* pMonster );

	// ͳ����Ϣblob
	char* GetRoleStatisticBlobStr( );
	void CreateStatisticFromTlv( PBPlayerStatisticInfo* pStatistic );
	void GetStatisticTlvBuffer( PBPlayerStatisticInfo* pStatistic  );

	// �Ż� blob
	char* GetRoleWizardBlobStr( );

	// �ͻ���blob��Ϣ
	char* GetRoleClientInfoBlobStr( );
	void CreateRoleClientInfoFromTlv( PBPlayerClientInfo* pClientInfo );
	void GetRoleClientInfoTlvBuffer( PBPlayerClientInfo* pClientInfo );
	
	// ��ȡ��ȫ������ص���Ϣ
	CRolePassword *GetRolePassword(){ return &mRolePassword; }

	void CreateMatrixInfoFromTlv( PBMatrixInfo* pMatrix);
	void GetMatrixRecordInfoTlvBuffer( PBMatrixInfo* pMatrix );	

	// ��ȡ���߾������
	CExpTimeInfo *GetExpTimeInfo(  ){ return &mExpTimeInfo; }
public:

	CPropertyPlayer( ){ }
	virtual ~CPropertyPlayer( ){ }

	int Initial( );
	int Final( ); 
	// ���CD��
	//int CheckCDGroup( int *vCDGroup, int vNum );

	// ����CD��
	//int RefreshCDGroup( int *vCDGroup, int vNum );
	
	// ������
	bool CheckPassWord( const char *pPassWord );	

	// ����
	int RideHorse( unsigned int vHorseTempID );

	// ���� (��Ҫ�ṩ�󶨵�BUFF ID)
	int OffHorse(int nHorseBuffID);

	// ���װ�����ӵļ��ܵȼ�
	unsigned short GetIncSkillLevel( unsigned short vSkillID );

	// �������Ƿ����㹻�ռ�
	bool TestBaggageSpace( int* pItemID, int* pNumber, int vNumber );

	// �������Ƿ���ָ��������ĳ����Ʒ
	bool BaggageHasItem( unsigned int vItemID, unsigned int vNumber );

	// ��ð�����ָ��������Ʒ�ĸ���
	int BaggageHasItem( unsigned int vItemID );

	// ���ݼ���ID��ü���
	CSkillObject* GetSkillObjectByID( unsigned int vSkillID );

	// ���ݼ���index��ü���
	CSkillObject* GetSkillObjectByIndex( unsigned int unSkillIndex );
	CSkillObject* GetSkillObjectBySkillIDInMagicWeapon( int vSkillID );

	// �ƶ���Ʒ
	int MoveItem( unsigned int vSrcIndex, unsigned int vSrcSlot, unsigned int vDesIndex, unsigned int vDesSlot, unsigned int vNumber, int &rNum );

	// �����������Ʒ
	int InsertBaggageItem( CItemObject* pItem, int &vPos, int *vIndex, int *vNumber, int &vLen );

	// �Ӱ����Ƴ�ָ��λ�õ���Ʒ
	int RemoveBaggageItem( unsigned int vIndex, unsigned int vNumber = 0 );

	// �Ӳֿ��Ƴ�ָ��λ�õ���Ʒ
	int RemoveStorageItem( unsigned int vIndex, unsigned int vNumber = 0 );

	// ����װ��
	int Equip( unsigned int vSrcIndex, unsigned int &vDesIndex );

	// ж��װ��
	int UnEquip( unsigned short vPart, unsigned int vIndex = ~0 );

	// ��PB�ṹ����
	void CreateFromTlv2( PBProperty* pBuffer );

	// ��䲿��PB�ṹ���������������ֿ�
	void GetTlvBuffer2( PBProperty* pBuffer );

	// ���ݷ��ʹ������PB�ṹ 
	void GetTotalBufferForClient( PBProperty* pBuffer, int nFillOder );

	// �����������Ե�
	int ResetAllPP( );

	// �������м��ܵ�
	int ResetAllSP( );

	// ���������컯��
	int ResetAllTalent( int vStep );

	// ���õ������ܵ�
	int ResetSingleSP( unsigned short vGenerID, unsigned char vCol, unsigned char vRow );

	// ����ְҵ
	int ResetMetier( );

	// �ı�ְҵ
	void ChangeMetier( int vMetierID );

	// ��ҵ����Ե�
	int ClickPropertyPoint( EPropertyType vPropertyType );

	// ��ҵ㼼�ܵ�
	int ClickSkillPoint( unsigned short vGenerID, unsigned char vCol, unsigned char vRow, unsigned int& vSkillID, int& vIndex, int& vMoney, int& vBindState );

	// �Ƿ�����������Ե�
	bool IsSPResetable( unsigned short vGenerID, unsigned char vCol, unsigned char vRow );

	// ���ܵ��Ƿ��ǳ�ʼֵ
	bool IsSPInit();

	// ���Ե��Ƿ��ǳ�ʼֵ
	bool IsPPInit();

	// ���������Ĭ����1��
	void LevelUp( int vLevel = 1 );

	// ������ȴ���¼�
	//int CDGroupCoolingEvent( CEntity* pEntity, unsigned int vTickOffSet );

	// ���������¼�
	int PKTimeEvent( CEntity* pEntity, unsigned int vTickOffSet );	

	// ���������������¼�
	int LogicTimeEvent(	CEntity* pEntity, unsigned int vTickOffSet );


	
	// ��ȡ���ڽ����״̬����Ʒ
	void GetItemForFree( );
	
	// ��ȡ���ڽ����״̬����Ʒ
	void GetItemForFreeFromItemBox( CItemBox &vItemBox );
	
	// ��ȡ���ڽ����״̬����Ʒ
	void GetItemForFreeFromEquipmet();

	// ���Ӵ��ڰ󶨽��״̬����Ʒ
	void InsertItemForFreeIntoList( CItemObject *tpItemObj );

	// �ж��Ƿ�Ӧ�ý����
	void CheckItemList( int ItemNow );

	//// ���ͻ��˷��Ͳֿ���Ϣ
	//void SendStorageInfo( CEntityPlayer *tpPlayer );

	// ������Ե�
	int AddPropertyPoint( int vSTR, int vCON, int vSTA, int vWIS, int vSPR );

	// ������ü�����ؼӳ�
	unsigned int MWGetFixNumber( CTemplateSkill::PASSINC_TYPE vType );
	int MWGetPerNumber( CTemplateSkill::PASSINC_TYPE vType );

	// �õ��Ż���Ϣ
	CWizard& GetWizard( ) { return mWizard; }

	// ˢ��Ԥ�洢������
	virtual CPropertyValue RefreshMaxHP( );
	virtual CPropertyValue RefreshStr( );
	virtual CPropertyValue RefreshWis( );
	virtual CPropertyValue RefreshSpr( );
	virtual CPropertyValue RefreshSta( );
	virtual CPropertyValue RefreshCon( );
	virtual CPropertyValue RefreshMaxMP( );
	virtual CPropertyValue RefreshMaxAP( );
	virtual ATTACK_TYPE RefreshAttackType( );

	virtual CPropertyValue RefreshPAttackMax( );
	virtual CPropertyValue RefreshPAttackMin( );
	virtual CPropertyValue RefreshMAttackMax( );
	virtual CPropertyValue RefreshMAttackMin( );

	virtual CPropertyValue RefreshDeathRate( ); // ����

	virtual CPropertyValue RefreshDeathValue( );
	virtual CPropertyValue RefreshDeathDefense( );
	virtual CPropertyValue RefreshNormalDuck( );
	virtual CPropertyValue RefreshSkillDuck( );
	virtual CPropertyValue RefreshIgnoreDuck( );

	virtual CPropertyValue RefreshPDefence( );
	virtual CPropertyValue RefreshMDefence( );

	virtual int RefreshAddFixDamage( );
	virtual int RefreshDecFixPDamage(  );
	virtual int RefreshDecFixMDamage( );
	virtual int RefreshDecPerPDamage( );
	virtual int RefreshDecPerMDamage( );
	virtual int RefreshStealHP( );
	virtual int RefreshStealMP( );
	virtual int RefreshNormalHitRate( );
	virtual int RefreshSkillHitRate( );
	virtual int RefreshResDef( int *vDef );
	virtual int RefreshResAtt( int *vAtt );
	virtual int RefreshEquipWizard( int *vWizard );
	void RefreshSkillList( );
	void RefreshSkillListAction( CSkillList* pSkillList );
	void RefreshStateList( );
	virtual int	GetDuckRate( );

	// ��ʱ����� ����������������ID 
	bool OnSkillCooldownTimeOut( CEntityPlayer* pEntity, int nSkillID, int nSkillLevel, int nSkillCD = 0, int nMWObjID = 0  );

	// ������Ұ󶨵Ķ�ʱ��
	virtual void StartSavedTimer( ) ;

    //����cd ˢ��  add by ycx  20100630
    bool OnSkillCDRefresh( CSkillObject* pSkillObj, CEntityPlayer* pDesEntity);
    //cd�� ˢ��   add by ycx  20100630
    bool OnGroupCDRefresh(CGroupCD& rGroupCD, CEntityPlayer* pDesEntity);

public:

	inline int GetLastRefreshAPTime(){ return mLastRefreshApTime; }
	inline void SetLastRefreshAPTime( int nTime ) { mLastRefreshApTime = nTime; }
	
	// Get & Set Exp
	inline unsigned long long GetExp( ){ return mExp; }
	inline void SetExp( unsigned long long vExp ){ mExp = vExp; }

	// Get & Set Sex
	inline unsigned int GetSex( ){ return mSex; }
	inline void SetSex( unsigned int vSex ){ mSex = vSex; }

	// Get & Set RemainPoint
	inline short GetRemainPoint( ){ return mRemainPoint; }
	inline void SetRemainPoint( short vRemainPoint ){ mRemainPoint = vRemainPoint; }

	// Get & Set SkillPoint
	inline short GetSkillPoint( ){ return mSkillPoint; }
	inline void SetSkillPoint( short vSkillPoint ){ mSkillPoint = vSkillPoint; }

	// Get & Set CurStr
	inline short GetCurStr( ){ return mCurStr; }
	inline void SetCurStr( short vCurStr ){ mCurStr = vCurStr; }

	// Get & Set CurWis
	inline short GetCurWis( ){ return mCurWis; }
	inline void SetCurWis( short vCurWis ){ mCurWis = vCurWis; }

	// Get & Set CurSta
	inline short GetCurSta( ){ return mCurSta; }
	inline void SetCurSta( short vCurSta ){ mCurSta = vCurSta; }

	// Get & Set CurCon
	inline short GetCurCon( ){ return mCurCon; }
	inline void SetCurCon( short vCurCon ){ mCurCon = vCurCon; }

	// Get & Set CurSpr
	inline short GetCurSpr( ){ return mCurSpr; }
	inline void SetCurSpr( short vCurSpr ){ mCurSpr = vCurSpr; }

	// Get & Set Money
	inline int GetMoney( ){ return mMoney; }
	inline void SetMoney( int vMoney ){ mMoney = vMoney; }

	// Get & Set StorageMoney
	inline int GetStorageMoney( ) { return mStorageMoney; }
	inline void SetStorageMoney( int nMoney ) { mStorageMoney = nMoney; }

	// Get & Set TalkNpcEntityID
	inline unsigned int GetTalkNpcEntityID( ){ return mTalkNpcEntityID; }
	inline void SetTalkNpcEntityID( unsigned int vTalkNpcEntityID ){ mTalkNpcEntityID = vTalkNpcEntityID; }

	// Get & Set ServiceStatus
	inline EService GetServiceStatus( ){ return mServiceStatus; }
	inline void SetServiceStatus( EService vServiceStatus ){ mServiceStatus = vServiceStatus; }
	
	// Get & Set Produce
	inline CProduce *GetProduce( ){ return &mProduce; }

	// Get & Set CDGroup
	inline CGroupCDList& GetCDGroupList( ){ return mCDGroup; }
	//inline void SetCDGroup( int i, int vCDGroup ){ mCDGroup[ i ] = vCDGroup; }
	//inline void CleanCDGroup( ){ memset( mCDGroup, 0, sizeof( mCDGroup ) ); }

	// Get & Set CommonCD
	inline int GetCommonCD( ){ return mCommonCD; }
	inline void SetCommonCD( int vCommonCD ){ mCommonCD = vCommonCD; }

	// Get & Set BindMoney
	inline int GetBindMoney() { return mBindMoney; }
	inline void SetBindMoney( int vMoney ) { mBindMoney = vMoney; }

	// Get & Set StorageBindMoney
	inline int GetStorageBindMoney() { return mStorageBindMoney; }
	inline void SetStorageBindMoney( int nMoney ) { mStorageBindMoney = nMoney; }

	inline unsigned int GetLastWeeklyDisposTime() {return mLastWeeklyDisposTime;}
	inline void SetLastWeeklyDisposTime( unsigned int nTime ) { mLastWeeklyDisposTime = nTime; }

	inline unsigned int GetLastDaylyDisposTime() {return mLastDaylyDisposTime;}
	inline void SetLastDaylyDisposTime( unsigned int nTime ) { mLastDaylyDisposTime = nTime; }

	// Get & Set Equipment
	inline CEquipment *GetEquipment( ){ return &mEquipment; }

	// Get & Set Baggage
	inline CBaggage *GetBaggage( ){ return &mBaggage; }

	// Get & Set TaskBaggage
	inline CItemBox *GetTaskBaggage( ){ return &mTaskBaggage; }

	// Get & Set Storage
	inline CStorage *GetStorage( ){ return &mStorage; }	

	// Get & Set EquipSkill
	inline CSkillList *GetEquipSkill( ){ return &mEquipSkill; }

	// Get & Set TallentSkill
	inline CSkillList *GetTallentSkill( ){ return &mTalentSkill; }


	// Get & Set Shortcut
	inline CShortcutList *GetShortcut( ){ return &mShortcut; }

	// Get & Set ProLevel
	inline unsigned int GetProLevel() { return mProLevel; }
	inline void SetProLevel( unsigned int vProLevel ) { mProLevel = vProLevel; }

	// Get & Set ProExp
	inline unsigned int GetProExp() { return mProExp; }
	inline void SetProExp( unsigned int vProExp ) { mProExp = vProExp; }

	// Get & Set HorseState
	inline int GetHorseState( ){ return mStateParam[ STATE_RIDE_HORSE ].mInState; }
	//inline void SetHorseState( int vHorseState ){ mHorseState = vHorseState; }

	// Get & Set HorseSpeedPer
	//unsigned int GetHorseSpeedPer( ) { return mHorseSpeedPer; }
	//void InitHorseSpeedPer( );
	//void SetHorseSpeedPer( unsigned int vHorseSpeedPer ) { mHorseSpeedPer = vHorseSpeedPer; }

	// Get & Set HorseTempID
	unsigned int GetHorseTempID( ) { return mStateParam[ STATE_RIDE_HORSE ].mParames1; }
	//void SetHorseTempID( unsigned int vHorseTempID ) { mHorseTempID = vHorseTempID; }

	// Get & Set TownPos
	inline ComplexPos *GetTownPos( ){ return &mTownPos; }

	ComplexPos* GetTelePos( unsigned int nIndex );
	int AddTelePos( const ComplexPos& rPos );
	int DelTelePos( unsigned int nIndex );

	// Get & Set StorageStatus
	inline int GetStorageStatus( ) { return mStorageStatus; }
	inline void SetStorageStatus( int vStorageStatus ){ mStorageStatus = vStorageStatus; }  

	// Get & Set Honor
	inline int GetHonor( ) { return mHonor; }
	inline void SetHonor( int vHonor ){ mHonor = vHonor; } 

	// Get & Set Honor
	inline int GetTodayHonor( ) { return mTodayHonor; }
	inline void SetTodayHonor( int vHonor ){ mTodayHonor = vHonor; } 

	// Get & Set InHonPerDay
	inline int GetInHonPerDay( ) { return mInHonPerDay; }
	inline void SetInHonPerDay( int vInHonPerDay ){ mInHonPerDay = vInHonPerDay; } 

	// Get & Set OutHonPerDay
	inline int GetOutHonPerDay( ) { return mOutHonPerDay; }
	inline void SetOutHonPerDay( int vOutHonPerDay ){ mOutHonPerDay = vOutHonPerDay; } 	

	// Get & Set LastObjID
	inline int GetLastObjID( ) { return mLastObjID; }
	inline void SetLastObjID( int vLastObjID ){ mLastObjID = vLastObjID; } 

	// Get & Set SaveDate
	inline int GetSaveDate( ) { return mSaveDate; }
	inline void SetSaveDate( int vSaveDate ){ mSaveDate = vSaveDate; } 

	// Get & Set Kill
	inline KillData *GetKill( int i ){ return &mKill[ i ]; }
	inline void SetKill( int i, KillData vKill ){ mKill[ i ] = vKill; }
	inline void CleanKill( ){ memset( mKill, 0, sizeof( mKill ) ); }
	inline int GetKillSize( ){ return ARRAY_CNT(mKill); }

	// Get & Set Repetion
	inline CPlayerRepetion *GetRepetion( ){ return &mRepetion; }

	// Get & Set DiploidTime
	inline int GetDiploid( ) { return mDiploidTime; }
	inline void SetDiploid( int vDiploidTime ) { mDiploidTime = vDiploidTime; }
	// ˫����ֵ
	int GetTotalDiploid();
	inline bool IsVip() { return mVipFlag == EM_VIP_NONE ? false : true; }

	inline void SetVipFlag( int nFlag ) { mVipFlag = nFlag; }
	inline int  GetVipFlag() { return mVipFlag; }
	inline void OpenVip( int nTime ) 
	{ 
		mVipFlag = EM_VIP_NORMAL; 
		mVipEndDate = nTime;
	}
	inline void CloseVip() 
	{ 
		mVipFlag = EM_VIP_NONE; 
		mVipEndDate = 0;
	}

	inline void SetVipTime( int nTime ) { mVipEndDate = nTime; }
	inline int  GetVipTime() { return mVipEndDate; }

	// Get & Set ValidDiploid
	int GetValidDiploid();
	inline void SetValidDiploid( int vValidDiploid ) { mDiploidState[ LEFTVALID_STATE ] = vValidDiploid; }
	
	// Get & Set AnswerStatus
	int		GetAnswerStatusObjID(  ){ return mAnswerStatusObjID; }
	void    SetAnswerStatusObjID( int Status ) { mAnswerStatusObjID = Status;  }
	// Get & Set AnswerStatusRedStoneID
	int		GetRedStoneID(){ return mRedStoneID; }
	void	SetRedStoneID( int RedStoneStatus ) {  mRedStoneID = RedStoneStatus; }
	
	// Get & Set WelfareStatus
	int GetWelfareStatus() { return mDailyWelfareStatus;	}
	void SetWelfareStatus( int Status ) { mDailyWelfareStatus = Status; }
	
	// Get & Set HasRedStoneStatus
	int GetHasRestoneStatus() { return mHasRedStoneStatus; }
	void SetHasRestoneStatus( int Status ){ mHasRedStoneStatus = Status; }

	// Get & Set LastRefreshTime
	inline int GetLastRefreshTime() { return mLastRefreshTime; }
	inline void SetLastRefreshTime( int nTime ) { mLastRefreshTime = nTime; }

	// Get & Set KillNumIn
	inline int GetKillNumIn() { return mKillNumIn; }
	inline void SetKillNumIn( int vKillNum ) { mKillNumIn = vKillNum; }

	// Get & Set KillNumOut
	inline int GetKillNumOut() { return mKillNumOut; }
	inline void SetKillNumOut( int vKillNum ) { mKillNumOut = vKillNum; }

	// Get & Set DieNum
	inline int GetDieNum() { return mDieNum; }
	inline void SetDieNum( int vDieNum ) { mDieNum = vDieNum; }

	// Get & Set CompletedTaskNum
	inline int GetCompletedTaskNum() { return mCompletedTasks; }
	inline void SetCompletedTaskNum( int vCompletedTaskNum ) { mCompletedTasks = vCompletedTaskNum; }


	// Get & Set LastFamilyApplyTime
	void SetLastFamilyApplyTime( int vLastTime ){ mLastFamilyApplyTime = vLastTime; }
	int	 GetLastFamilyApplyTime( ){ return mLastFamilyApplyTime; }
	
	// Get & Set LastTimeLeaveFamily
	void SetLastTimeLeaveFamily( int vLastTime ){ mLastTimeLeaveFamily = vLastTime;  }
	unsigned int	 GetLastTimeLeaveFamily( ) { return mLastTimeLeaveFamily; }

	// Get & Set ReduceLevel
	inline int GetReduceLevel() { return mReduceLevel; }
	inline void SetReduceLevel( int vReduceLevel ) { mReduceLevel = vReduceLevel; }

	// Get & Set DiploidState
	inline void SetDiploidState( EDiploidState i, int vParam )
	{ 
		//LK_ASSERT( i < ARRAY_CNT( mDiploidState ), return );
		mDiploidState[ i ] = vParam; 
	}
	inline int GetDiploidState( int i ) { return mDiploidState[ i ]; }
	inline bool IsFreezeDouble()
	{
		return ( mDiploidState[ FREEZE_STATE ] > 0 &&  mDiploidState[ DIPLOID_STATE ] > 0 ? true : false );
	}
	inline bool UnFreezeDouble()
	{
		return ( mDiploidState[ DIPLOID_STATE ] > 0 && mDiploidState[ FREEZE_STATE ] == 0 ? true : false );
	}
	inline bool InDoubleTime()
	{
		return ( mDiploidState[ DIPLOID_STATE ] > 0 ? true : false );
	}
	inline int GetDiploidTimerID()
	{
		return mDiploidState[ TIMEID_STATE ];
	}
	inline void SetDoubleTimerID( int nTimerID )
	{
		mDiploidState[ TIMEID_STATE ] = nTimerID;
	}
	inline bool CanObtainDoubleExp()
	{
		if ( (mDiploidState[ DIPLOID_STATE ] > 0 && mDiploidState[ FREEZE_STATE ] == 0)
			|| mDiploidState[ ACTIVITY_STATE ] > 0) 
			return true;
		return false;
	}
	inline void SetDoubleFreezeState( bool bFreeze )
	{
		if ( bFreeze ) 
			mDiploidState[ FREEZE_STATE ] = 1;
		else
			mDiploidState[ FREEZE_STATE ] = 0;
	}
	inline void SetDoubleTimeState( bool bOpen )
	{
		if ( bOpen )
			mDiploidState[ DIPLOID_STATE ] = 1;
		else
			mDiploidState[ DIPLOID_STATE ] = 0;  
	}

	inline bool IsActivityDouble()
	{
		return ( mDiploidState[ ACTIVITY_STATE ] > 0 ? true : false );
	}

	inline void InitDoubleState()
	{
		for ( int i = 0; i < (int)ARRAY_CNT( mDiploidState ) - 1; i ++ )
			mDiploidState[ i ] = 0;
	}

	inline void SetActivityState( int nRate )
	{
		mDiploidState[ ACTIVITY_STATE ] = nRate;
	}

	inline int GetActivityState()
	{
		return mDiploidState[ ACTIVITY_STATE ];
	}

	inline int GetLastStopTime(){ return mDiploidState[ TIMERSTOP_STATE ]; }
	inline void SetLastStopTime( int nTime ){ mDiploidState[ TIMERSTOP_STATE ] = nTime; }

	void CheckDiploidState();

	// Get & Set SaleItem
	inline SaleItemList *GetSaleItem( ){ return &mSaleItem; }

	// Get & Set StallInfo
	inline CStallInfo *GetStallInfo(const int vStallType ){ return &mStallInfo[vStallType]; }

	// Get & Set AttackList
	inline StateList *GetAttackList( ){ return &mAttackList; }
	// Get & Set DefenceList
	inline StateList *GetDefenceList( ){ return &mDefenceList; }
	// Get & Set DeathList
	inline StateList *GetDeathList( ){ return &mDeathList; }
	// Get & Set AttackStateTime
	inline int GetAttackStateTime() { return mAttackStateTime; }
	inline void SetAttackStateTime( int vAttackStateTime ) { mAttackStateTime = vAttackStateTime; }
	// Get & Set DefenceStateTime
	inline int GetDefenceStateTime() { return mDefenceStateTime; }
	inline void SetDefenceStateTime( int vDefenceStateTime ) { mDefenceStateTime = vDefenceStateTime; }
	// Get & Set DeathStateTime
	inline int GetDeathStateTime() { return mDeathStateTime; }
	inline void SetDeathStateTime( int vDeathStateTime ) { mDeathStateTime = vDeathStateTime; }

	// Get & Set AssignExpScl
	inline unsigned char GetAssignExpScl() { return mAssignExpScl; }
	inline void SetAssignExpScl( unsigned char val ) { mAssignExpScl = val; }
	
	// Get & Set CurrentTitle
	inline int GetCurrentTitle() { return mCurrentTitle; }
	inline void SetCurrentTitle( int vCurrentTitle ) { mCurrentTitle = vCurrentTitle; }

	// �ƺŻ�ȡʱ�� [12/29/2009 Macro]
	int GetTitleTime( int nTitleID )
	{
		TitleList::iterator it = mTitleList.begin();
		for ( ; it != mTitleList.end(); ++ it )
		{
			if ( it->mTitleID == nTitleID )
				return it->mTime;
		}
		return SUCCESS;
	}

	int AddTitle( int vTitleID, unsigned int nInvalidTime = 0 );
	int GetLowLevelTitle( int vTitleID );
	int GetTitleList( int* npList, int& nNum )
	{
		if ( npList == NULL ) return -1;
		int tSize = nNum; nNum = 0;
		TitleList::iterator it = mTitleList.begin();
		for ( ; it != mTitleList.end(); ++ it )
		{
			if ( nNum < tSize )
				npList[ nNum ++ ] = it->mTitleID;
		}
		return SUCCESS;
	}

	inline void RemoveTitle( int vTitleID )
	{
		TitleList::iterator it = mTitleList.begin();
		for ( ; it != mTitleList.end(); ++ it )
		{
			if ( it->mTitleID == vTitleID )
			{
				RemoveTitleSkill( vTitleID );
				mTitleList.erase( it );
				break;
			}
		}
		return ;
	}

	inline bool HasTitle( int vTitleID )
	{
		TitleList::iterator it = mTitleList.begin();
		for ( ; it != mTitleList.end(); ++ it )
		{
			if ( it->mTitleID == vTitleID )
				return true;
		}
		return false;
	}

	inline void RemoveTitleSkill( int vTitleID )
	{
		CTitle* tpTitle = CDataStatic::GetTitle( vTitleID );
		if ( tpTitle == NULL )
			return ;
		CTemplateSkill* tpSkill = ( CTemplateSkill* ) CDataStatic::SearchTpl( tpTitle->mAddProperty );
		if ( tpSkill == NULL )
			return ;
		mTitleSkill.RemoveSkill( tpSkill->mSkillID );
	}

	// Get & Set TalentExp
	inline int GetTalentExp() { return mTalentExp; }
	inline void SetTalentExp( int vTalentExp ) { mTalentExp = vTalentExp; }
	// Get & Set TalentPoint
	inline int GetTalentPoint() { return mTalentPoint; }
	inline void SetTalentPoint( int vTalentPoint ) { mTalentPoint = vTalentPoint; }
	// Get & Set TalentStep
	inline int GetTalentStep() { return mTalentStep; }
	inline void SetTalentStep( int vTalentStep ) { mTalentStep = vTalentStep; }
	// Get & Set TalentStudy
	inline int GetTalentStudy( ) { return mTalentStudy; }
	inline void SetTalentStudy( int vTalentStudy ) { mTalentStudy = vTalentStudy; }
	// Get & Set TalentLevel
	inline int GetTalentLevel( ) { return mTalentLevel; }
	inline void SetTalentLevel( int vTalentLevel ) { mTalentLevel = vTalentLevel; }
	
	// Get & Set DecompoundEquipIndex
	int	 GetDecompoundEquipIndex( ){ return mDecompoundEquipIndex; }
	void SetDecompoundEquipIndex( int nIndex ){ mDecompoundEquipIndex = nIndex; }
	
	// ����̯λ�ı�
	inline void SaveStallText( const char* pName, const char* pAd, const int vStallType )
	{
		LK_ASSERT( pName != NULL && pAd != NULL, return );
		mStallInfo[vStallType].SetName( pName );
		mStallInfo[vStallType].SetAd( pAd );
	}
	

	inline int	GetPKValue() { return mPKValue; }
	inline void SetPKValue( int nValue ) { mPKValue = nValue; }
	void IncreasePKValue( int nValue );

	bool InJudgeCoolTime()
	{
		return ( ( time(NULL) - mLastJudgeTime ) > JUDGE_COOL_TIME ? false : true );
	}
	

	inline EPKStatus GetPKStatus() { return mPKStatus; }
	inline void	SetPKStatus( EPKStatus nPkStatus ) { mPKStatus = nPkStatus; }

	inline bool GetYellowStatus() { return mYellowStatus; }
	inline void	SetYellowStatus( bool bStatus ) { mYellowStatus = bStatus; }

	inline void SetYellowTimer(int nTimer) { mYellowTimer = nTimer; }
	inline int  GetYellowTimer() { return mYellowTimer; }

	inline void SetPrisonTime( int nTime ) { mPrisonTime = nTime; }
	inline void IncPrisonTime( int nTime ) { mPrisonTime += nTime; }
	inline int	GetPrisonTime() { return mPrisonTime; }

	inline int GetMasterID( int i ) 
	{
		if ( i < 0 || i >= MAX_MASTER_NUM )
			return 0;
		return mMasterID[ i ]; 
	}
	inline void	SetMasterID( int nMasterID, int i )
	{
		if ( i < 0 || i >= MAX_MASTER_NUM )
			return;
		mMasterID[ i ] = nMasterID;
	}

	inline void AddSlaveID( int vSlaveID ){ mMatrixList.push_back( vSlaveID ); }
	inline bool IsSlaveFull( )
	{
		if ( mBeginnerNum + mFormalNum >= MAX_MATRIX_MENBER || mBeginnerNum >= MAX_BEGINNER_SLAVE_NUM )
			return true;
		return false;
	}

	inline void AddSlaveValue( int vValue, int vIndex )
	{
		if ( vIndex >=0 && vIndex < (int)ARRAY_CNT(mSlaveValue) )
		{
			mSlaveValue[ vIndex ] += vValue;
		}
	}
	inline int GetSlaveValue( int vIndex )
	{
		if ( vIndex >=0 && vIndex < (int)ARRAY_CNT(mSlaveValue) )
		{
			return mSlaveValue[ vIndex ];
		}
		return 0;
	}

	inline void SetSlavePoint( int vPoint ){ mSlavePoint = vPoint; }
	inline int GetSlavePoint( ){ return mSlavePoint; }

	inline void SetMasterPoint( int vPoint ){ mMasterPoint = vPoint; }
	inline int GetMasterPoint( ){ return mMasterPoint; }

	inline void SetSlaveTotal( int vTotal ){ mSlaveTotal = vTotal; }
	inline int GetSlaveTotal( ){ return mSlaveTotal; }

	inline void SetMasterTotal( int vTotal ){ mMasterTotal = vTotal; }
	inline int GetMasterTotal( ){ return mMasterTotal; }

	inline void SetMasterPercent( int vPercent, int vIndex )
	{
		if ( vIndex >=0 && vIndex < (int)ARRAY_CNT(mMasterPercent) )
		{
			mMasterPercent[ vIndex ] = vPercent;
		}
	}
	inline int GetMasterPercent( int vIndex )
	{
		if ( vIndex >=0 && vIndex < (int)ARRAY_CNT(mMasterPercent) )
		{
			return mMasterPercent[ vIndex ];
		}
		return 0;
	}

	inline void SetMasterTimes( int vTimes ){ mMasterTimes = vTimes; }
	inline int GetMasterTimes( ){ return mMasterTimes; }

	inline void SetMasterGive( int vGive ){ mMasterGive = vGive; }
	inline int GetMasterGive( ){ return mMasterGive; }

	inline void SetBeginnerNum( int vNum ){ mBeginnerNum = vNum; }
	inline int GetBeginnerNum( ){ return mBeginnerNum; }

	inline void SetFormalNum( int vNum ){ mFormalNum = vNum; }
	inline int GetFormalNum( ){ return mFormalNum; }

	inline void SetSlaveNum( int vNum ){ mSlaveNum = vNum; }
	inline int GetSlaveNum( ){ return mSlaveNum; }

	inline CYuanBao& GoldenYB() { return mGoldenYB; }
	inline CYuanBao& SilverYB() { return mSilverYB; }

	EPKStatus GetTplPKState();
	EPKStatus GetMainPKState();

	bool IsRedPKStatus();
	bool IsWhitePKStatus();
	
	// ������������ƥ��
	bool SkillWeaponValid( CTemplateSkill* pSkill );

	// װ���Ƿ���� ( �;ö��Ƿ�Ϊ0 )
	bool EquipmentAvailable( EEquipPart emPart );

	// �����Ƿ��ڹ�����ȴ��
	bool IsCommonCoolingDown() { return ( GetCommonCD() > 0 ) ? true : false; }

	// ����Ƿ��㹻(֧�ְ󶨻�ǰ�)
	bool IsMoneyEnough( bool bBind, int vMoney );

	// ������ʱ���Ƿ��ڱ���״̬��
	bool CanAttacked();

	// �Ƿ���Դ���
	bool CanTeleport();

	// ���ͼ,���ﴦ��
	void ChangeHorseStateTransMap( unsigned short unMapID );

	// ��������״̬buff
	void InsertSelfBuff( CEntityCharacter *pDesEntity, CTemplateProperty::PROPERTY_FUNC vType, int vOldPer = 0, int vNewPer = 0 );

	// Get & Set SkillList
	inline virtual CSkillList& GetSkillList( ) { return mSkill ;}

	inline int GetWizardDiff( int vType )
	{
		if ( vType < 0 || vType > WIZARD_NUM )
		{
			return 0;
		}
		return mWizard.GetWizardPoint( vType ) + mWizard.GetWizardIncrease( vType ) + GetEquipWizard( vType ) - mWizard.GetWizardSubmit( vType );
	}

	inline int AddAwardTimes( int vAwardID, EM_AwardLimitType nType = EALT_Daily )
	{
		for ( AwardList::iterator it = mAwardList[nType].begin(); it != mAwardList[nType].end(); ++it )
		{
			if ( it->mAwardID == vAwardID )
			{
				it->mTimes++;
				return it->mTimes;
			}
		}
		mAwardList[nType].push_back( ST_AWARD( vAwardID, 1 ) );
		return 1;
	}

	inline int GetAwardTimes( int vAwardID, EM_AwardLimitType nType = EALT_Daily )
	{
		for ( AwardList::iterator it = mAwardList[nType].begin(); it != mAwardList[nType].end(); ++it )
		{
			if ( it->mAwardID == vAwardID )
			{
				return it->mTimes;
			}
		}
		return 0;
	}

	inline int InsertAwardTimes( int vAwardID, int vTimes, EM_AwardLimitType nType = EALT_Daily )
	{
		for ( AwardList::iterator it = mAwardList[nType].begin(); it != mAwardList[nType].end(); ++it )
		{
			if ( it->mAwardID == vAwardID )
			{
				return -1;
			}
		}
		mAwardList[nType].push_back( ST_AWARD( vAwardID, vTimes ) );
		return 0;
	}

	inline int ClearAwardTimes( EM_AwardLimitType nType = EALT_Daily )
	{
		mAwardList[nType].clear();
		return 0;
	}

	int GetIndexByID( int vID );

	void DeleteItem( );

	void RemoveBuffOnLogOff( );
	
	// Get&Set InvestStatus
	int GetInvestStatus(){ return mInvestStatus; }
	void SetInvestStatus( int nStatus ){ mInvestStatus = nStatus; }

	int GetTotalWar(){ return mTotalWar; }
	void SetTotalWar( int nTotalWar ){ mTotalWar = nTotalWar; }

	int GetTodayWar(){ return mTodayWar; }
	void SetTodayWar( int nTodayWar ){ mTodayWar = nTodayWar; }

	int GetTodayOther(){ return mTodayOther; }
	void SetTodayOther( int nTodayOther ){ mTodayOther = nTodayOther; }

	int GetFreeWar(){ return mFreeWar; }
	void SetFreeWar( int nFreeWar ){ mFreeWar = nFreeWar; }

	int GetWarKill(){ return mWarKill; }
	void SetWarKill( int nWarKill ){ mWarKill = nWarKill; }

	int GetWarSerial(){ return mWarSerial; }
	void SetWarSerial( int nWarSerial ){ mWarSerial = nWarSerial; }

	int GetExpHonor(){ return mExpHonor; }
	void SetExpHonor( int nExpHonor ){ mExpHonor = nExpHonor; }

	int GetItemHonor(){ return mItemHonor; }
	void SetItemHonor( int nItemHonor ){ mItemHonor = nItemHonor; }

	int GetHasVoted(){ return mHasVoted; }
	void SetHasVoted( int nHasVoted ){ mHasVoted = nHasVoted; }
	
	CTreasureBowlInfo *GetTreasureBowlInfo() { return &mTreasureBowlInfo; }
	//
	void GetRepetDataForClient( PBRepetDataList * pBuffer);

	CSpiritInfo& GetSpiritInfo(){return m_SpiritInfo;}
};


/************************************************************************/
/* NPC���� ���������NPC..... )                                       */
/************************************************************************/
class CPropertyNPC : public CPropertyCharacter
{
protected:
	int				mRelifeTimer;		//�����ʱ��
	int             mRelifeTime;        //�����ʱ��������

	int				mBattleTimer;		// ս����ʱ��ID
	CSkillListInstance<1>	mSkill;		// �����б�

	int				mTranChangeLevel;

public:
	CPropertyNPC( ){ }
	virtual ~CPropertyNPC( ){ }

    int Initial( );
    int Final( );

	virtual CPropertyValue RefreshMaxHP( );
	virtual CPropertyValue RefreshStr( );
	virtual CPropertyValue RefreshWis( );
	virtual CPropertyValue RefreshSpr( );
	virtual CPropertyValue RefreshSta( );
	virtual CPropertyValue RefreshCon( );
	virtual CPropertyValue RefreshMaxMP( );
	virtual ATTACK_TYPE RefreshAttackType( );
	virtual CPropertyValue RefreshPAttackMax( );
	virtual CPropertyValue RefreshPAttackMin( );
	virtual CPropertyValue RefreshMAttackMax( );
	virtual CPropertyValue RefreshMAttackMin( );
	virtual CPropertyValue RefreshDeathRate( );
	virtual CPropertyValue RefreshDeathValue( );
	virtual CPropertyValue RefreshDeathDefense( );
	virtual CPropertyValue RefreshNormalDuck( );
	virtual CPropertyValue RefreshSkillDuck( );
	virtual CPropertyValue RefreshIgnoreDuck( );
	virtual CPropertyValue RefreshPDefence( );
	virtual CPropertyValue RefreshMDefence( );
	virtual int RefreshAddFixDamage( );
	virtual int RefreshDecFixPDamage( );
	virtual int RefreshDecFixMDamage( );
	virtual int RefreshDecPerMDamage( );
	virtual int RefreshDecPerPDamage( );
	virtual int RefreshNormalHitRate( );
	virtual int RefreshSkillHitRate( );
	virtual int RefreshResDef( int *vDef );
	virtual int RefreshResAtt( int *vAtt );
	virtual	int GetDuckRate( );

	// Get & Set RelifeTimer
	inline int GetRelifeTimer( ) { return mRelifeTimer; }
	inline void SetRelifeTimer( int vRelifeTimer ){ mRelifeTimer = vRelifeTimer; } 

	// Get & Set RelifeTime
	inline int GetRelifeTime( ) { return mRelifeTime; }
	inline void SetRelifeTime( int vRelifeTime ){ mRelifeTime = vRelifeTime; } 

	inline int GetBattleTimer() { return mBattleTimer; }
	inline void SetBattleTimer( int nTimer ) { mBattleTimer = nTimer; }

	// Get & Set SkillList
	inline virtual CSkillList& GetSkillList( ) { return mSkill ;}

	// ������ʧTimer��ʱ���¼�
	int OnEntityDisappearTimeout( CEntity* pEntity );

	void SetTranChangeLevel( int vLevel ) { mTranChangeLevel = vLevel; }
	int GetTranChangeLevel( ) { return mTranChangeLevel; }
};

/************************************************************************/
/* ��������                                                             */
/************************************************************************/
class CPropertyPet : public CPropertyCharacter
{
protected:
	//unsigned int			mMonsterID;	// ����ID
	CSkillListInstance<1>	mSkill;		// �����б�

public:
	CPropertyPet( ){ }
	virtual ~CPropertyPet( ){ }

    int Initial( );
    int Final( );

	virtual CPropertyValue RefreshMaxHP( );
	virtual CPropertyValue RefreshStr( );
	virtual CPropertyValue RefreshWis(  );
	virtual CPropertyValue RefreshSpr( );
	virtual CPropertyValue RefreshSta( );
	virtual CPropertyValue RefreshCon( );
	virtual CPropertyValue RefreshMaxMP( );
	virtual ATTACK_TYPE RefreshAttackType( );
	virtual CPropertyValue RefreshPAttackMax( );
	virtual CPropertyValue RefreshPAttackMin( );
	virtual CPropertyValue RefreshMAttackMax( );
	virtual CPropertyValue RefreshMAttackMin( );
	virtual CPropertyValue RefreshDeathRate( );
	virtual CPropertyValue RefreshDeathValue( );
	virtual CPropertyValue RefreshDeathDefense( );
	virtual CPropertyValue RefreshNormalDuck( );
	virtual CPropertyValue RefreshSkillDuck( );
	virtual CPropertyValue RefreshIgnoreDuck( );
	virtual CPropertyValue RefreshPDefence( );
	virtual CPropertyValue RefreshMDefence( );
	virtual int RefreshAddFixDamage( );
	virtual int RefreshDecFixPDamage( );
	virtual int RefreshDecFixMDamage( );
	virtual int RefreshDecPerMDamage( );
	virtual int RefreshDecPerPDamage( );
	virtual int RefreshNormalHitRate( );
	virtual int RefreshSkillHitRate( );
	virtual int RefreshResDef( int *vDef );
	virtual int RefreshResAtt( int *vAtt );
	virtual int GetDuckRate( );

	//// Get & Set MonsterID
	//inline unsigned int GetMonsterID( ) { return mMonsterID; }
	//inline void SetMonsterID( unsigned int vMonsterID ) { mMonsterID = vMonsterID; }

	// Get & Set SkillList
	inline virtual CSkillList& GetSkillList( ) { return mSkill; }
};


/************************************************************************/
/* ����������                                                                     */
/************************************************************************/
class CPropertyDrop : public CProperty
{
protected:
	int				mItemProtect;
	int				mOwnerCharID[ TEAMNUM ];

public:
	bool			HasOwner( );
	bool			IsOwner( int vCharID );

	// Get & Set ItemProtect
	inline int GetItemProtect( ) { return mItemProtect; }
	inline void SetItemProtect( int vItemProtect ){ mItemProtect = vItemProtect; } 

	// Get & Set OwnerCharID
	inline unsigned int GetOwnerCharID( int i ){ return mOwnerCharID[ i ]; }
	inline void SetOwnerCharID( int i, unsigned int vOwnerCharID ){ mOwnerCharID[ i ] = vOwnerCharID; }
	inline void CleanOwnerCharID( ){ memset( mOwnerCharID, 0, sizeof( mOwnerCharID ) ); }
	inline void CloneOwnerCharID( int *vOwnerCharID ){ memcpy( mOwnerCharID, vOwnerCharID, sizeof( mOwnerCharID ) ); }
};


/************************************************************************/
/* ��������                                                                     */
/************************************************************************/
class CPropertyItem : public CPropertyDrop
{
protected:
	unsigned int	mItemID;
public:
    int Initial( );
    int Final( );

	// Get & Set ItemID
	inline unsigned int GetItemID( ) { return mItemID; }
	inline void SetItemID( unsigned int vItemID ){ mItemID = vItemID; } 
};

/************************************************************************/
/* ��Ǯ����                                                             */
/************************************************************************/
class CPropertyMoney : public CPropertyDrop
{
protected:
	int mMoney;
public:
	int Initial( );
	int Final( );

	// Get & Set Money
	inline int GetMoney( ) { return mMoney; }
	inline void SetMoney( int vMoney ){ mMoney = vMoney; } 

};

/************************************************************************/
/* ���͵㣬��������                                                                     */
/************************************************************************/
class CPropertyPedal : public CProperty
{
public:
	int Initial( );
	int Final( );
	void IsDisappear( CEntity* pEntity, int vTickOffset );
	//void PedalIsTouch( CEntity* pEntity, int vTickOffset, vector< CEntity* >& vDeleteList );
};


/************************************************************************/
/* ��������                                                                     */
/************************************************************************/
//class CPropertyBox : public CProperty
//{
//public:
	
//	int Initial( ) { return SUCCESS; }
//	int Final( ) { return SUCCESS; }
//};
/************************************************************************/
/* �ڵ�����                                                                     */
/************************************************************************/
class CPropertyRedStone : public CProperty
{
public:
	int Initial( ) { return SUCCESS; }
	int Final( ) { return SUCCESS; }
};

///************************************************************************/
/* �赲����                                                                     */
/************************************************************************/
//class CPropertyBlock : public CProperty
//{
//public:
	
//	int Initial( ) { return SUCCESS; }
//	int Final( ) { return SUCCESS; }
//};


#endif




