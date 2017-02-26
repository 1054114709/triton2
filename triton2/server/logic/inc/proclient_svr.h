#pragma once

#include "coretype.h"
#include "protype.h"
#include "sceneobj_manager.h"
#include "promessage_pb.hxx.pb.h"
#include "share_define.h"
#include "property_pb.hxx.pb.h"
#include "lk_vector.h"
#include "lk_hashmap.h"
#include "template.h"
#include "timer_define.h"
#include "skill_list.h"
#include "buffer.h"

class CProperty;
class CPropertyCharacter;
class CPropertyPlayer;
class CPropertyNPC;
class CPropertyPet;
class CEntityCharacter;
class CEntityResultList;
class CEntityPlayer;



enum EquipProType
{
	TYPE_NONE = 0,
	TYPE_PATTACKLOW,
	TYPE_PATTACKHIGH,
	TYPE_MATTACKLOW,
	TYPE_MATTACKHIGH,
	TYPE_DEATHRATE,
	TYPE_DEATHVALUE,
	TYPE_PDEFENCE,
	TYPE_MDEFENCE,
	TYPE_MAXHP,
	TYPE_MAXMP,
};

class CPropertyValue
{
public:
	int			mInitValue;
	int			mDeltaValue;
public:
	CPropertyValue( ) //: mInitValue( 0 ), mDeltaValue( 0 )	
	{
		if( CObj::msCreateMode )
		{
			mInitValue = 0;
			mDeltaValue = 0;
		}
	}
public:
	operator int( )
	{ return mInitValue + mDeltaValue; }
	operator unsigned int( )
	{
		return mInitValue + mDeltaValue;
	}	

	bool operator ==( CPropertyValue& tOther )
	{
		return ( ( mInitValue == tOther.mInitValue ) && ( mDeltaValue == tOther.mDeltaValue ) );
	}
};

// ********************************************************************** //
// CItemObject
// ********************************************************************** //

class CItemObject : public CObj
{
protected:
	unsigned int	mItemID;					// ����ID
private:
	unsigned int	mNumber;					// ��������
	int				mLocked;					// ��������
	int             mBindStatus;                // ��״̬
	int				mUsedTimes;					// ��ʹ�ô���
	uint64_t		mPurchaseID;				// ����Ľ���ID
	OBJGUID			mObjGUID;					// ����ʱ��Ψһ��ʶ 
	time_t			mInvalidTime;				// ����ʱ��
	
	int				mValidTimerID;				// ��Чʱ�䶨ʱ��ID��ʵʱ���ݣ�������
	int				mBindTime;					// ��Ʒ�󶨵�ʱ��
public:
	//TODO
	CItemObject()
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

	CItemObject( unsigned int vItemID , unsigned int vNumber = 0 ) : mItemID( vItemID ), mNumber( vNumber ), mLocked( false ), mPurchaseID( 0)
	{
	}

	virtual int Initialize()
	{
		mItemID = 0;
		mNumber = 0;
		mLocked = 0;
		mBindStatus = 0;
		mUsedTimes  = 0;
		mPurchaseID = 0;
		mObjGUID.a.guid = 0;
		mInvalidTime = 0;
		mValidTimerID = INVALID_OBJ_ID;
		mBindTime = 0;
		return 0;
	}
	
	virtual int Resume()
	{
		return 0;
	}

public:
	
	// ����ID
	inline unsigned int GetItemID()	{ return mItemID; }
	inline void SetItemID( unsigned int unItemID ) { mItemID = unItemID; }

	// ���߸���
	inline unsigned int GetItemNum() { return mNumber; }
	inline void SetItemNum( unsigned int unItemNum ) { mNumber = unItemNum; }

	// ��״̬
	inline int GetBindStatus() { return mBindStatus; }
	inline void SetBindStatus( int BindStatus )
	{				
		mBindStatus = BindStatus;				
	}

	void ChangeBindStatus( int nBindStatus )
	{
		mBindStatus |= nBindStatus;
	}

	// ʹ�ô���
	inline int GetUsedTimes() {return mUsedTimes;}
	inline void SetUsedTimes( int nUsedTimes ) { mUsedTimes = nUsedTimes; }

	// lock status
	inline int GetLockStatus() { return mLocked; }
	inline void SetLockStatus( int nLock ) { mLocked = nLock; }
	
	// ����Ʒ
	int BindItem( int vBindType );

	void SetGUID() ;

	inline uint64_t GetGUID()
	{
		return mObjGUID.value();
	}

	inline OBJGUID GetGUIDObj()
	{
		return mObjGUID;
	}

	inline void SetGUID( uint64_t nGUID ) { mObjGUID.a.guid = nGUID; }
	
	// ����ID
	inline uint64_t GetPurchaseID() { return mPurchaseID ; }
	inline void SetPurchaseID( uint64_t unPurchaseID ) { mPurchaseID = unPurchaseID; }

	// ��Чʱ��
	inline unsigned int GetInvalidTime( ) { return mInvalidTime; }
	inline void SetInvalidTime( int nInvalidTime ) { mInvalidTime = nInvalidTime; }
	
	// ��Чʱ��timer
	inline int GetValidTimerID( ) { return mValidTimerID; }
	inline void SetValidTimerID( int nValidTimerID ) { mValidTimerID = nValidTimerID; }	

	// �Ƿ��ѹ���
	bool IsOvertimed()
	{
		if ( GetInvalidTime() == 0 )
		{
			return false;
		}
		else
		{
			if ( GetInvalidTime() <= (unsigned int)time(0) ) // ������
			{
				return true;
			}
		}
		return false;
	}

public:

	void GetItemBinaryBuffer2( PBItemObject* pBuffer, int vNumber = -1 );
	virtual void GetItemBinary2( PBItemObject*& pGene ) = 0;

	/** �Ƿ���ͬһ�ֵ�����(���Ӱ����ض�������)
	**  ����������Դ�����ҵ��ߺ���Ϸ�������ߣ�����ĳЩ����������Ҫ�ȼۣ�
	**	��������ĸ���
	*/
	bool IsSameItemGroup( unsigned int nItemID, int nType );

	/** �Ƿ��ǵ�ͼ������Ʒ
	**  
	*/
	bool IsMapLimitedItem( int nCurMapID );

	/** �Ƿ��Ǹ���������Ʒ
	**  
	*/
    bool IsRepetionLimitedItem( int nCurRepetionIndex );
};

// ********************************************************************** //
// CItemEquipment
// װ������
// ********************************************************************** //

class CItemEquipment : public CItemObject
{
protected:
	unsigned char	mSlotNumber;					// �򿪵�װ���۸���	
	unsigned char	mNameLength;					// ���������ֳ���
	int				mLevel;							// װ���ȼ�
	unsigned int	mSlotProperty[ JEWELNUM ];		// װ�����Ƿ�򿪣�0δ����1��
	unsigned int	mProperty[ PROPERTYNUM ];		// ��������ID,0��ʾû�и�������
	unsigned int	mSlotValue[ JEWELNUM ];			// װ���۵ı�ʯID
	unsigned int	mValue[ PROPERTYNUM ];			// ����������ֵ
	unsigned int	mSlotSpell;						// ��Ƕ�ķ���

    int              mCurDurability;				// װ���;ö�
	unsigned int     mAbrasionCount;				// ��ĵ�������npc������ļ�100����ҽ�����ļ�1000����10000�����һ���;ö�
   	unsigned int     mBindFreeTime;                 // ���װ���󶨵�ʱ��                

	CPropertyValue	mMaxSlotNumber;					// װ�����ṩ�����۸���
	unsigned int	mJudge[ UPGVALUENUM ];			// �������Եĸ���ֵ
	int				mResDef;						// �������
	int				mResAtt;						// ���Թ������
	int				mDefLevel;						// ���Եȼ�
	int				mAttLevel;						// ���Թ����ȼ�
	int				mMagicStoneID;					// ��ħʯID
	int				mMagicStoneNum;					// ͬ�ָ�ħʯ�ĸ�ħ����
	int				mSpouseID;						// ���õĽ�ɫID
	int				mExtraType;						// ���ӵ�����
	int				mBindTime;						// װ������ͨ�󶨵�ʱ��
	char			mSpouseName[NAME_LENGTH];		// ��ż������
	char			mName[ NAME_LENGTH ];			// ����������O
public:

	CItemEquipment( )
	{
		if ( CObj::msCreateMode )
		{
			Initialize ();
		}
		else
		{
			Resume();
		}
	}

	virtual ~CItemEquipment( ) {}
public:

	// BindFree Time
	inline int GetBindFreeTime()	{	return mBindFreeTime;	}	
	inline void SetBindFreeTime( int FreeTime ){	mBindFreeTime = FreeTime;	}		
	
	// Level
	inline int GetLevel() { return mLevel; }
	inline void SetLevel( int nLevel ) { mLevel = nLevel; }

	// SlotNumber
	inline unsigned char GetSlotNumber( ) { return mSlotNumber; }
	inline void SetSlotNumber( unsigned char ucSlot ) { mSlotNumber = ucSlot; }

	// SlotProperty
	inline unsigned int GetSlotProperty( int nIdx ) { return mSlotProperty[nIdx] ;}
	inline void SetSlotProperty( int nIdx, unsigned int usValue ) { mSlotProperty[nIdx] = usValue; }

	// Property �����������
	inline unsigned int GetProperty( int nIdx ) { return mProperty[nIdx]; }
	inline void SetProperty( int nIdx, unsigned int usValue ) { mProperty[nIdx] = usValue; }

	// SlotValue
	inline unsigned int GetSlotValue( int nIdx ) { return mSlotValue[ nIdx] ; }
	inline void SetSlotValue( int nIdx, unsigned int usValue ) { mSlotValue[nIdx] = usValue; }

	// Value
	inline unsigned int GetValue( int nIdx ) { return mValue[ nIdx ] ; }
	inline void SetValue( int nIdx, unsigned int usValue ) { mValue[nIdx] = usValue; }

	// NameLength
	inline unsigned char GetNameLength() { return mNameLength; }
	inline void SetNameLength( unsigned char ucNameLen ) { mNameLength = ucNameLen; }
	inline unsigned char GetMaxNameLength() { return sizeof(mName)-1; }

	// Name
	inline char* GetName() { return mName; }
	inline void SetName( const char* pName ) { strncpy( mName, pName, sizeof(mName)-1 ); mName[ sizeof(mName)-1] = 0; }
	
	//mSlotSpell
	inline unsigned int GetSlotSpell() { return mSlotSpell; }
	inline void SetSlotSpell( unsigned int usSpell ) { mSlotSpell = usSpell; }

	// mCurDurability
	inline int GetDurability() { return mCurDurability; }
	inline void SetDurability( int nDur ) { mCurDurability = nDur; }

	// mAbrasionCount
	inline int GetAbrasionCount() { return mAbrasionCount; }
	inline void SetAbrasionCount( int nAbr ) { mAbrasionCount = nAbr; }

	// mMaxSlotNumber
	inline CPropertyValue& GetMaxSlotNumber() { return mMaxSlotNumber; }
	inline void SetMaxSlotNumber( CPropertyValue nMaxSlotNumber) { mMaxSlotNumber = nMaxSlotNumber; }

	inline void SetMaxSlotNumberInit( int nInit ) { mMaxSlotNumber.mInitValue = nInit; }
	inline void SetMaxSlotNumberDelta( int nDelat ) { mMaxSlotNumber.mDeltaValue = nDelat; }

	// mJudge
	inline unsigned int GetJuge( int nIdx ) { return mJudge[nIdx]; }
	inline void SetJuge( int nIdx, unsigned int nValue ) { mJudge[nIdx] = nValue; }

	// mResDef
	inline int GetResDef( ) { return mResDef;}
	inline void SetResDef( int nResDef ) { mResDef = nResDef; }

	// mResAtt
	inline int GetResAtt( ) { return mResAtt;}
	inline void SetResAtt( int nResAtt ) { mResAtt= nResAtt; }

	// mDefLevel
	inline int GetDefLevel() { return mDefLevel; }
	inline void SetDefLevel( int nDefVal ) { mDefLevel = nDefVal; }

	// mAttLevel
	inline int GetAttLevel( ) { return mAttLevel; }
	inline void SetAttLevel( int nAttLevel ) { mAttLevel = nAttLevel; }

	// nMagicStoneID
	inline void SetMagicStoneID( int nMagicStoneID ){ mMagicStoneID = nMagicStoneID; }
	inline int  GetMagicStoneID(){ return mMagicStoneID; }

	// mMagicStoneNum
	inline void SetMagicStoneNum( int nMagicStoneNum ){ mMagicStoneNum = nMagicStoneNum; }
	inline int GetMagicStoneNum( ){ return mMagicStoneNum; }

	virtual int Initialize();	

	virtual int Resume( ) 	{	return CItemObject::Resume( );	}	

	int GetPropertyFromTpl( int vItemID, bool vInit = true );
	
	void SetSpouseID( int nSpouseID ){ mSpouseID = nSpouseID;  }
	int	GetSpouseID(  ){ return mSpouseID; }
	
	void SetSpouseName( const char *pSpouseName )
	{
		if ( pSpouseName != NULL )
		{
			strncpy( mSpouseName, pSpouseName, NAME_LENGTH - 1 );
			mSpouseName[NAME_LENGTH -1]='\0';	
		}				 
	}
	const char *GetSpouseName(){ return mSpouseName; }

	inline int GetExtraType( ) { return mExtraType; }
	inline void SetExtraType( int nExtraType ) { mExtraType = nExtraType; }
	
	// ����&��ȡװ���İ�ʱ��
	void SetBindTime( int nBindTime ) { mBindTime = nBindTime; }
	int GetBindTime(){ return mBindTime; }
public:
	// ����װ�����;ö�
	int ReduceDurability(  int NpcType , int PlayerAlive = 1 );

	// ����װ���;ö�Ϊ��ʼֵ
	int ResetDurability( );
	
    int GetLostDurability( );
   
	int GetMendMoney( );
	
public:
	
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
	static void SetValueFromPB( CItemEquipment* tpItem, PBItemObject*& pGene );

	// ����һ��"��"���ߣ�������ɸ�������
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber ) ;
	static void SetValueFromCreator( CItemEquipment* tpEquip, unsigned int vItemID, unsigned int vNumber );

	virtual void GetItemBinary2( PBItemObject*& pGene );
	
	int GetFixNumber( CTemplateProperty::PROPERTY_FUNC vFunc, int vEquipProType = 0, CPropertyPlayer *pProperty = NULL );

	int GetPerNumber( CTemplateProperty::PROPERTY_FUNC vFunc );

	// �õ�װ����ָ�����ܵĵȼ��ӳ�
	unsigned short GetIncSkillLevel( unsigned short vSkillID );
	unsigned short GetValueByID( unsigned short vSkillID, CTemplateProperty::PROPERTY_FUNC vType );
	int	GetStateID( StateList& vBuffList,CTemplateProperty::PROPERTY_FUNC vType );

	void GetSkillList( std::vector< unsigned short >& rSkillList, CTemplateProperty::PROPERTY_FUNC vFunc );
	
	// װ����ħ
	int SetMagicStone( int nMagicStoneID );
	
	// ��ȡ��ħ����
	int GetMagicAttribute(  );	

	// �ж��Ƿ��ǽ������
	bool IsMarriageEquipment();

	// �ж��Ƿ��ǽ������
	bool IsSwornEquipment();
};

// ********************************************************************** //
// CItemMagicWeapon
// ��������
// ********************************************************************** //

class CItemMagicWeapon : public CItemEquipment
{
private:
	// ��������
	int				mMWLevel;	// �����ȼ�
	unsigned long long	mExp;		// ��������
	unsigned int	mMp;		// ����ֵ
	unsigned int	mHp;		// ����ֵ
	
	unsigned int	mCurKeenpoints;		// ��ǰ���� (�������ܵ�Ӱ��)
	unsigned int	mCurCalmpoints;		// ��ǰ���� (�������ܵ�Ӱ��)	
	unsigned int	mCurMagicpoints;	// ��ǰ���� (�������ܵ�Ӱ��)	
	unsigned int	mCurBierpoints;		// ��ǰ���� (�������ܵ�Ӱ��)	
	unsigned int	mCurImmortalpoints;	// ��ǰ���� (�������ܵ�Ӱ��)	

	unsigned int	mExtraKeenpoints;		// �������ӵ����� (�������ܵ�Ӱ��)
	unsigned int	mExtraCalmpoints;		// �������ӵĶ��� (�������ܵ�Ӱ��)
	unsigned int	mExtraMagicpoints;		// �������ӵķ��� (�������ܵ�Ӱ��)
	unsigned int	mExtraBierpoints;		// �������ӵ����� (�������ܵ�Ӱ��)
	unsigned int	mExtraImmortalpoints;	// �������ӵ����� (�������ܵ�Ӱ��)

	unsigned int	mAddKeenpoints;		// ������ӵ�����
	unsigned int	mAddCalmpoints;		// ������ӵĶ���
	unsigned int	mAddMagicpoints;	// ������ӵķ���
	unsigned int	mAddBierpoints;		// ������ӵ�����
	unsigned int	mAddImmortalpoints;	// ������ӵ�����

	unsigned int	mLeftPoints;// ��ǰʣ��Ǳ�ܵ�

	// ϴ����Ҫ�õ������ݣ�

	// ��ұ��������¼� 5�����Ե�ļ�¼ �������
	unsigned int	mPlayerAddPointLastLevel[POINT_TYPE_NUM];	// ��ұ�������ǰ�Լ��ӵĵ�ľ���
	unsigned int	mLeftPointsLastLevel;	// ��������ǰ��ҵ�ʣ��Ǳ�ܵ�
	unsigned int	mNewAddPoints;	// ���������¼ӵ�Ǳ�ܵ�
	unsigned int	mNewAddSkillPoints;	// ���������¼ӵļ��ܵ�
	int				mStepClearState;	// ���Сϴ״̬
	int				mLastAddedSkillBoxIndex;	// �ϴμ��ܼӵ�ļ��ܿ�����

	// ��������
	unsigned int	mProBase;	// ���Ի���ֵ
	unsigned int	mProUp;		// ���Գɳ�ֵ
	unsigned int	mProEff;	// ����Ӱ���
	unsigned int	mProSpir;	// ����

	// ����/���ܿ����
	unsigned int	mProcessVal;		// ��ǰ����ֵ
	unsigned int    mLastLevelProcessVal;	// Сϴ����
	unsigned int	mLeftSkillPoints;	// ��ǰʣ�༼�ܵ�

	// �������
	int				mNextActBoxIndex;	// ��һ����������ļ��ܿ�����
	int				mLastLevelNextActBox;	// ��һ����������ļ��ܿ�����

	unsigned int	mMaxMp;		// ����ֵ����
	unsigned int	mMaxHp;		// ����ֵ����
	int				mIncMp;		// ����ֵÿ�λָ�����
	int				mIncHp;		// ����ֵÿ�λָ�����

	int				mProJudgeFlag;		// �Ƿ���������Լ���

	CSkillListInstance<6>	mMWSkillList; // �������ļ����б� (û�ж�Ӧ��ϵ ���ⲿ�������)
	int				mQilinID; // �Ѻϳɵ�����ID

	// ʵʱ����:����Ҫ���浽���ݿ� ������װ��/ж��/����/���ߵ�ʱ��Ҫ������
	int	mTimerID[MW_TIMER_NUM];
	int mOwnerEntityID;		// ����ߵ�ʵ��ID �������ʱ��ֵ

	bool IsNeedIncMp() { return mMp < mMaxMp; }
	bool IsNeedDecHp() { return mHp > 0; }
	void CheckTimers() ;

	// ���Ӽ��� HP MP�漰�����Ƚ϶� ֱ��set���������ֹ
	void SetMp( unsigned int nValue) { mMp = nValue; }
	void SetHp( unsigned int nValue) { mHp = nValue; }

public:
	unsigned int    mSkills[SKILL_BOX_LMT];  // ÿ�����ܿ���Ѽ������� 0û��
	unsigned int    mSkillActNum[SKILL_BOX_LMT];  // ÿ�����ܿ���Ѽ�������
	unsigned int    mSkillBookID[SKILL_BOX_LMT];  // ÿ�����ܿ����ʹ�õļ�����
	unsigned int    mAddedSkillPoints[SKILL_BOX_LMT];  // ÿ�����ܿ���ļ����Ѽӵļ��ܵ�
	unsigned int    mSkillInitLevel[SKILL_BOX_LMT];  // ÿ�����ܿ���ļ��ܳ�ʼ�ȼ�
	unsigned char   mActiveState[SKILL_BOX_LMT];  // ÿ�����ܿ򼤻���� 0δ����

public:
	CItemMagicWeapon( )
	{
		if ( CObj::msCreateMode )
		{
			Initialize2();
		}
		else
		{
			Resume();
		}
	}
	virtual ~CItemMagicWeapon( ) {}	
	virtual void Initialize2();
	void InitializeMW(); // ��ʼ����������

public:
	// ������ ֻ��һ��һ��������
	void LevelUp( ); 

	// ˢ�¸�������ֵ  �������Ƿ�����ʱ��
	void RefreshPropertys( bool bIsStartTimer = true ); 

	// ��װ�Ϸ���/���볡����ʱ����� ��ʼ����ʱ�� ����������ߵ�ָ��
	void OnStartMagicWeapon( CEntityPlayer* pPlayer, bool bIsStartTimer=true );

	// ��ж�·�����ʱ����� �ɵ���ʱ�� ����������ߵ�ָ�� ���߾Ͳ��õ����� ���������ٵ�
	void OnEndMagicWeapon( CEntityPlayer* pPlayer );

	// ��ʱ�ָ�MP
	int OnTimerIncMp();

	// ��ʱ����HP
	int OnTimerDecHp();

	// ������HP
	int OnDieCutHp();

	// ��������(����)MP�ӿ� ����ʵ������/����ֵ
	int  OnIncMp( int nVal, bool bIsStartTimer = true );

	// ��������(����)HP�ӿ� ����ʵ������/����ֵ
	int  OnIncHp( int nVal );

	// ����ӵ� ����0�ɹ�
	int  OnAddPotential( unsigned int nNewKeenpoints, unsigned int nNewCalmpoints, unsigned int nNewMagicpoints, unsigned int nNewBierpoints, unsigned int nNewImmortalpoints );

	// �¼Ӽ��ܣ�����&������ã� ����0�ɹ�  ����������ID ���ܵȼ� Ŀ�꼼�ܿ�  
	int  OnInsertSkill( int nSkillID, int nSkillLevel, int nBoxIndex, bool bIsStartTimer = true  );

	// �¼������� һ��Ҫ�Ӽ��ܺ������Ӽ�������   ���������ܿ�ID  ���أ�0  �ɹ� ���������
	int  OnJudgeNewSkill( int nBoxIndex, bool& bIsFirst, CMessageInsertSkillNotify* pMsg );

	// ������  ���ʵ������������б� �������� ��������ʱ�����
	int  OnSelfLearnSkill( unsigned char arrIndex[] );

	// �õ��������ܻ���ֵ ��Ҫ���ڷ����ͻ���
	void GetSkillBaseInfo( unsigned char nBoxIndex, int& rSkillID, int& rSkillLevel, int& rActedNum, int& rBookID );

	// �������Լ����¼��ܿ�(�ⲿ �ڷ���������ʱ����� ��Ϊ��ƺͿͻ���ͨ��)
	int  OnActiveNewSkillBox( int& nFirstActBoxIndex );

	// �������ܼӵ�
	int  OnClickSP( int nBoxIndex );

	// �õ�����������
	unsigned int GetAttackValue();

	// �õ������������ȼ�
	unsigned int GetDeathRate();

	// ʹ�ü�����ϳɼ��� ���� ���ܿ����� �������ģ��ID ���� ��ȷ0 ���������
	int  OnUseSkillBook( int nBoxIndex, int nBookID, CMessageInsertSkillNotify* pMsg );

	// ��װ�Ϸ���/���ߵ�ʱ�� Ҫ��������CD
	void OnStartSkillCD( CEntityPlayer* pOwner );

	// ��ж�·���/���ߵ�ʱ�� Ҫֹͣ����CD
	void OnStopSkillCD( CEntityPlayer* pOwner );

	// ϴ��--Сϴ
	int  Return2LastLevel();

	// �������ã���ϴ��
	int ResetMagicWeapon(CEntityPlayer* pPlayer);

	// ��ñ��������¼ӵ�Ǳ�ܵ�
	int	 GetThisLevelGotPoints();

	// ��ñ��������¼ӵļ��ܵ�
	int	 GetThisLevelGotSkillPoints();

	// ��ģ�帳ֵ
	int  SetupFromTemplate( );

	// ��ģ�����ü��� Ҫ����������ָ�� ��ΪҪ���ȼ�����Ϣ
	int  SetupSkillFromTemplate( CEntityPlayer* pOwner );

	// �������Լ��� �ӿ��ڲ��жϵڼ��� �ⲿ�����ж�/�۳���Ʒ
	int  OnJudgeProperty( int nEffTableID, int nSpirTableID );

	// ����ϴ���ܵ�
	int  ClearMWSkillPoint();
	int  GetTotalAddSP();

	// ����������ӡ��
	int  OnPrintQilin( int nQilinID );

private:
	// �õ�ĳ���ܿ�ļ��� �ó�ȡ�ĳ�ȡ ���������ܿ��������Ƿ��һ�� ���أ�����ID
	int GetBoxSkillNewID( int nBoxIndex, bool bIsFirst );

	// ������Ҽӵ�����
	void BackUpData();

public: // �������Ľӿ� ������ҵĽӿ�	
	// ������ҹ�����
	static int GetAttackForPlayer( CPropertyPlayer* pProperty );
	// ������ҷ�����
	static int GetRecoveryForPlayer( CPropertyPlayer* pProperty );
	// �������MP����
	static int GetMaxMpForPlayer( CPropertyPlayer* pProperty );
	// �������HP����
	static int GetMaxHpForPlayer( CPropertyPlayer* pProperty );
	// ������������ȼ�
	static int GetDeadLineForPlayer( CPropertyPlayer* pProperty );

public:
	int GetMWLevel() { return mMWLevel;}
	void SetMWLevel( int nValue) { mMWLevel = nValue;}

	unsigned long long GetExp() { return mExp;}
	void SetExp( unsigned long long nValue) { mExp = nValue;}

	unsigned int GetMp() { return mMp;}

	unsigned int GetHp() { return mHp;}

	unsigned int GetKeenpoints() { return mCurKeenpoints+mExtraKeenpoints;}
	unsigned int GetCalmpoints() { return mCurCalmpoints+mExtraCalmpoints;}
	unsigned int GetMagicpoints() { return mCurMagicpoints+mExtraMagicpoints;}
	unsigned int GetBierpoints() { return mCurBierpoints+mExtraBierpoints;}
	unsigned int GetImmortalpoints() { return mCurImmortalpoints+mExtraImmortalpoints;}

	void SetCurCalmpoints( unsigned int nValue) { mCurCalmpoints = nValue;}
	void SetCurKeenpoints( unsigned int nValue) { mCurKeenpoints = nValue;}
	void SetCurMagicpoints( unsigned int nValue) { mCurMagicpoints = nValue;}
	void SetCurBierpoints( unsigned int nValue) { mCurBierpoints = nValue;}
	void SetCurImmortalpoints( unsigned int nValue) { mCurImmortalpoints = nValue;}

	void SetExtraCalmpoints( unsigned int nValue) { mExtraCalmpoints = nValue;}
	void SetExtraKeenpoints( unsigned int nValue) { mExtraKeenpoints = nValue;}
	void SetExtraMagicpoints( unsigned int nValue) { mExtraMagicpoints = nValue;}
	void SetExtraBierpoints( unsigned int nValue) { mExtraBierpoints = nValue;}
	void SetExtraImmortalpoints( unsigned int nValue) { mExtraImmortalpoints = nValue;}

	unsigned int GetLeftPoints() { return mLeftPoints;}
	void SetLeftPoints( unsigned int nValue) { mLeftPoints = nValue;}

	unsigned int GetProBase() { return mProBase;}
	void SetProBase( unsigned int nValue) { mProBase = nValue;}

	unsigned int GetProUp() { return mProUp;}
	void SetProUp( unsigned int nValue) { mProUp = nValue;}

	unsigned int GetProEff() { return mProEff;}
	void SetProEff( unsigned int nValue) { mProEff = nValue;}

	unsigned int GetProSpir() { return mProSpir;}
	void SetProSpir( unsigned int nValue) { mProSpir = nValue;}

	unsigned int GetProcessVal() { return mProcessVal;}
	void SetProcessVal( unsigned int nValue) { mProcessVal = nValue;}

	unsigned int GetLeftSkillPoints() { return mLeftSkillPoints;}
	void SetLeftSkillPoints( unsigned int     nValue) { mLeftSkillPoints = nValue;}

	unsigned int GetMaxMp() { return mMaxMp;}
	void SetMaxMp( unsigned int nValue) { mMaxMp = nValue; }

	unsigned int GetMaxHp() { return mMaxHp;}
	void SetMaxHp( unsigned int nValue) { mMaxHp = nValue; }

	int GetIncMp() { return mIncMp;}
	void SetIncMp( int nValue) { mIncMp = nValue;}

	int GetIncHp() { return mIncHp;}
	void SetIncHp( int nValue) { mIncHp = nValue;}

	unsigned int GetAddKeenpoints() { return mAddKeenpoints;}
	void SetAddKeenpoints( unsigned int nValue) { mAddKeenpoints = nValue;}

	unsigned int GetAddCalmpoints() { return mAddCalmpoints;}
	void SetAddCalmpoints( unsigned int nValue) { mAddCalmpoints = nValue;}

	unsigned int GetAddMagicpoints() { return mAddMagicpoints;}
	void SetAddMagicpoints( unsigned int nValue) { mAddMagicpoints = nValue;}

	unsigned int GetAddBierpoints() { return mAddBierpoints;}
	void SetAddBierpoints( unsigned int nValue) { mAddBierpoints = nValue;}

	unsigned int GetAddImmortalpoints() { return mAddImmortalpoints;}
	void SetAddImmortalpoints( unsigned int nValue) { mAddImmortalpoints = nValue;}

	int GetProJudgeFlag() { return mProJudgeFlag;}
	void SetProJudgeFlag( unsigned int nValue) { mProJudgeFlag = nValue;}

	int GetLeftPointsLastLevel() { return mLeftPointsLastLevel;}
	void SetLeftPointsLastLevel( int nValue) { mLeftPointsLastLevel = nValue;}

	int GetNewAddPoints() { return mNewAddPoints;}
	void SetNewAddPoints( int nValue) { mNewAddPoints = nValue;}

	int GetNewAddSkillPoints() { return mNewAddSkillPoints;}
	void SetNewAddSkillPoints( int nValue) { mNewAddSkillPoints = nValue;}

	int GetStepClearState() { return mStepClearState;}
	void SetStepClearState( int nValue) { mStepClearState = nValue;}

	int GetLastAddedSkillBoxIndex() { return mLastAddedSkillBoxIndex;}
	void SetLastAddedSkillBoxIndex( int nValue) { mLastAddedSkillBoxIndex = nValue;}

	int GetLastLevelProcessVal() { return mLastLevelProcessVal; }
	void SetLastLevelProcessVal( int nValue ) { mLastLevelProcessVal = nValue; } 

	int GetNextActBoxIndex() { return mNextActBoxIndex;}
	void SetNextActBoxIndex( int nValue) { mNextActBoxIndex = nValue;}

	int GetLastLevelNextActBox() { return mLastLevelNextActBox;}
	void SetLastLevelNextActBox( int nValue) { mLastLevelNextActBox = nValue;}

	int  GetCurQL() { return  mQilinID; }
	void SetCurQL( int nID ) { mQilinID=nID; }

	void SetPlayerAddPointLastLevel( int nVal, int i )
	{
		mPlayerAddPointLastLevel[i] = nVal;
	}

	int GetOwner() { return mOwnerEntityID;}

	// ��ʼ��MP HP
	void InitMpHp( unsigned int nMp, unsigned int nHp ) { mMp = nMp; mHp = nHp; }

	CSkillList* GetMWSkillList() { return &mMWSkillList; }
public:
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber ) ;
	virtual void GetItemBinary2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemBindStone
// ��ʯ
// ********************************************************************** //
class CItemBindStone : public CItemObject
{
public:	
	CItemBindStone()
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
	virtual int Initialize()
	{
		return	CItemObject::Initialize( );
	}
	virtual int Resume() 
	{
		return CItemObject::Resume( );
	}

	virtual ~CItemBindStone(){}
	
	static CItemObject * Creator(unsigned int vItemID , unsigned int vNumber  );

	static CItemObject* BinaryClone2( PBItemObject*& pGene );
	virtual void GetItemBinary2( PBItemObject*& pGene ) { return; }
};
// ********************************************************************** //
// CItemShout
// ��������
// ********************************************************************** //
class CItemShout : public CItemObject
{
public:
	CItemShout()
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

	virtual int Initialize()
	{
		return	CItemObject::Initialize( );
	}
	
	virtual int Resume() 
	{
		return CItemObject::Resume( );
	}

    virtual ~CItemShout(){}
	
	static CItemObject * Creator(unsigned int vItemID , unsigned int vNumber  );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
	virtual void GetItemBinary2( PBItemObject*& pGene ) { return; }
};
// ********************************************************************** //
// CItemAutoShout
// �Զ���������
// ********************************************************************** //
class CItemAutoShout : public CItemObject
{
public:
	CItemAutoShout()
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

	virtual int Initialize()
	{
		return	CItemObject::Initialize( );
	}
	
	virtual int Resume() 
	{
		return CItemObject::Resume( );
	}

	virtual ~CItemAutoShout(){}
	
	static CItemObject * Creator(unsigned int vItemID , unsigned int vNumber  );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
	virtual void GetItemBinary2( PBItemObject*& pGene ) { return; }
};

// ********************************************************************** //
// CItemReturn
// �سǵ���
// ********************************************************************** //

class CItemReturn : public CItemObject
{
public:
	//TODO
	CItemReturn( )
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

	virtual ~CItemReturn( ) {}
	
	virtual int Initailize()
	{
		return	CItemObject::Initialize( );
	}
	
	virtual int Resume() 
	{
		return CItemObject::Resume( );
	}


	
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );
	virtual void GetItemBinary2( PBItemObject*& pGene )	{ return; }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};


// ********************************************************************** //
// CItemSkillBook
// �������������
// ********************************************************************** //
class CItemSkillBook : public CItemObject
{
public:
	//TODO
	CItemSkillBook( )
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

	virtual ~CItemSkillBook( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene )	{	}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};



// ********************************************************************** //
// CItemFuncItem
// ���������
// ********************************************************************** //
class CItemFuncItem : public CItemObject
{
public:
	//TODO
	CItemFuncItem( )
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

	virtual ~CItemFuncItem( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene )	{	}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};


// ********************************************************************** //
// CItemTeleport
// ���ͷ�����
// ********************************************************************** //

class CItemTeleport : public CItemObject
{
private:
	// ��¼�洢��λ��
	unsigned short		mLineID;	
	unsigned short		mMapID;
	int					mPosX;
	int					mPosY;

public:
	//TODO
	CItemTeleport( )
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

	virtual ~CItemTeleport() {}

	virtual int Initialize ();
	

	virtual int Resume(){ return CItemObject::Resume();	}

	inline unsigned short GetLineID() { return mLineID; }
	inline void SetLineID( unsigned short unLineID ) { mLineID = unLineID; }

	inline unsigned short GetMapID() { return mMapID; }
	inline void SetMapID( unsigned short unMapID ) { mMapID = unMapID; }

	inline int GetPosX() { return mPosX; }
	inline void SetPosX( int nPosX ) { mPosX = nPosX; }

	inline int GetPosY() { return mPosY; }
	inline void SetPosY( int nPosY ) { mPosY = nPosY;}

public:
	
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	/*{ return new CItemTeleport; }*/
	virtual void GetItemBinary2( PBItemObject*& pGene );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemQuestPaper
// ���
// ********************************************************************** //
class CItemQuestPaper: public CItemObject
{	
public:
	CItemQuestPaper()
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

	virtual int Initialize()
	{
		return	CItemObject::Initialize( );
	}

	virtual int Resume() 
	{
		return CItemObject::Resume( );
	}

	virtual ~CItemQuestPaper(){}

	static CItemObject * Creator( unsigned int vItemID , unsigned int vNumber  );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
	virtual void GetItemBinary2( PBItemObject*& pGene ) { return; }	
};

// ********************************************************************** //
// CItemEquipUpg
// װ����������
// ********************************************************************** //

class CItemEquipUpg : public CItemObject
{
public:
	//TODO
	CItemEquipUpg( )
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
	virtual ~CItemEquipUpg( ) {}

	virtual int Initialize(){ return CItemObject::Initialize();	}

	virtual int Resume(){ return CItemObject::Resume();	}

	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene )	{ return; }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemRelife
// �������
// ********************************************************************** //

class CItemRelive : public CItemObject
{
private:
	int		mCooldown;	// ��ǰ����ȴʱ��


public:
	//TODO
	CItemRelive( )
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

	virtual ~CItemRelive( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		mCooldown = 0;
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

	inline int GetCooldown( ) { return mCooldown; }
	inline void SetCooldown( int nCD ) { mCooldown = nCD; }

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene )	{	pGene->set_cooldown( mCooldown );	}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemSkill
// ʹ�ü��������
// ********************************************************************** //

class CItemSkill : public CItemObject
{
private:
	int		mCooldown;	// ��ǰ����ȴʱ��

public:

	CItemSkill( ) 
	{
		if ( CObj::msCreateMode )
		{
			Initailize();
		} 
		else
		{
			Resume();
		}
	}

	virtual ~CItemSkill( ) {}

	virtual int Initailize()
	{
		CItemObject::Initialize( );
		mCooldown = 0;
		return 0;
	}

	virtual int Resume()
	{
		return CItemObject::Resume( );
	}

	inline int GetCooldown( ) { return mCooldown; }
	inline void SetCooldown( int nCD ) { mCooldown = nCD; }

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene )	{ pGene->set_cooldown( mCooldown ); }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemBook
// ���������
// ********************************************************************** //

class CItemBook : public CItemObject
{
public:
	//TODO:
	CItemBook( ) 
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
	virtual ~CItemBook( ) {}

	virtual int Initialize() 
	{
		return  CItemObject::Initialize();		
	}
	
	virtual int Resume() 
	{
		return CItemObject::Resume( );
	}

	
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );
	virtual void GetItemBinary2( PBItemObject*& pGene ) { return; }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemNote
// ������
// ********************************************************************** //

class CItemNote : public CItemObject
{
public:

	//TODO
	CItemNote( )
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
	virtual ~CItemNote( ) {}

	virtual int Initialize()
	{
		return CItemObject::Initialize();
	}

	virtual int Resume()
	{
		return CItemObject::Resume();
	}

	
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );
	virtual void GetItemBinary2( PBItemObject*& pGene ) { return; }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemTuff
// ԭ�ϵ���
// ********************************************************************** //

class CItemStuff : public CItemObject
{
public:
	
	CItemStuff( )
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
	virtual ~CItemStuff( ) {}

	virtual int Initialize ()
	{
		return CItemObject::Initialize();
	}

	int Resume()
	{
		return CItemObject::Resume();
	}

	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );
	virtual void GetItemBinary2( PBItemObject*& pGene ) { return; }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemExp
// ����ӱ�����
// ********************************************************************** //

class CItemExp : public CItemObject
{
public:
	
	CItemExp( )
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
	virtual ~CItemExp( ) {}
	
	virtual int Initialize( )
	{
		return CItemObject::Initialize( );
	}

	virtual int Resume( )
	{
		return CItemObject::Resume( );
	}

	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );
	virtual void GetItemBinary2( PBItemObject*& pGene ) { return; }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemPhysic
// ҩƷ�����
// ********************************************************************** //

class CItemPhysic : public CItemObject
{
private:
	unsigned int	mRemainHP;
	unsigned int	mRemainMP;
	unsigned int	mRemainAP;
	int				mCooldown;	// ��ǰ����ȴʱ��

public:

	CItemPhysic( )
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
	virtual ~CItemPhysic( ) {}

	CItemPhysic( int ItemID  ) : CItemObject( ItemID ), mRemainHP( 0 ), mRemainMP( 0 ), mRemainAP( 0 ), mCooldown( 0 )
	{
	}

	virtual int Initialize()
	{
		CItemObject::Initialize( );
		mRemainHP = 0;
		mRemainMP = 0;
		mRemainAP = 0;
		mCooldown = 0;
		return 0;
	}

	virtual int Resume( )
	{
		return CItemObject::Resume( );
	}

	inline unsigned int GetRemainHP() { return mRemainHP; }
	inline void SetRemainHP( unsigned int nRemainHP ) { mRemainHP = nRemainHP; }

	inline unsigned int GetRemainMP() { return mRemainMP; }
	inline void SetRemainMP( unsigned int nRemainMP ) { mRemainMP = nRemainMP; }

	inline  unsigned int GetRemainAP() { return mRemainAP; }
	inline void SetRemainAP( unsigned int nRemainAP ) { mRemainAP = nRemainAP; }

	inline int GetCooldown() { return mCooldown; }
	inline void SetCooldown( int nCD ) { mCooldown = nCD; }

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	/*{ return new CItemPhysic; }*/
	virtual void GetItemBinary2( PBItemObject*& pGene );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemHorse
// ҩƷ�����
// ********************************************************************** //

class CItemHorse : public CItemObject
{
private:
	int				mCooldown;	// ��ǰ����ȴʱ��

public:

	CItemHorse( )
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
	virtual ~CItemHorse( ) {}

	CItemHorse( int ItemID  ) : CItemObject( ItemID ), mCooldown( 0 )
	{
	}

	virtual int Initailize()
	{
		CItemObject::Initialize( );
		mCooldown = 0;
		return 0;
	}

	virtual int Resume( )
	{
		return CItemObject::Resume( );
	}

	inline int GetCooldown( ) { return mCooldown; }
	inline void SetCooldown( int nCD ) { mCooldown = nCD; }

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );
	virtual void GetItemBinary2( PBItemObject*& pGene )
	{
		pGene->set_cooldown( mCooldown );
	}

	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemHorse
// ҩƷ�����
// ********************************************************************** //
class CItemKitBag : public CItemObject
{
public:
	CItemKitBag()
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
	CItemKitBag( int nItemID ):CItemObject( nItemID ){  }
	virtual ~CItemKitBag( ){ }

private:

	//int mIndexNumber;	// ��չ����������

public:
	virtual int Initialize( ){  return 0; }
	virtual int Resume( ){  return 0; }
public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );
	virtual void GetItemBinary2( PBItemObject*& pKitBag ); 
	static CItemObject* BinaryClone2( PBItemObject*& pKitBag );
};

// ********************************************************************** //
// CItemTask
// ���������
// ********************************************************************** //
class CItemTask : public CItemObject
{
private:

	int				mCooldown;	// ��ǰ����ȴʱ��

public:

	CItemTask( ) 
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

	virtual ~CItemTask() {}

	virtual int Initialize()
	{
		CItemObject::Initialize( );
		mCooldown = 0;
		return 0;
	}
	
	virtual int Resume(){ return CItemObject::Resume( ); }

	inline int GetCooldown( ) { return mCooldown; }
	inline void SetCooldown( int nCD ) { mCooldown = nCD; }

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	/*{ return new CItemTask; }*/
	virtual void GetItemBinary2( PBItemObject*& pGene )	{	pGene->set_cooldown( mCooldown ); }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};



// ********************************************************************** //
// CItemSpecialTask
// ����������Ʒ
// ********************************************************************** //
class CItemSpecialTask : public CItemObject
{
private:

	int				mCooldown;	// ��ǰ����ȴʱ��

public:

	CItemSpecialTask( ) 
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

	virtual ~CItemSpecialTask() {}

	virtual int Initialize()
	{
		CItemObject::Initialize( );
		mCooldown = 0;
		return 0;
	}

	virtual int Resume()
	{
		return CItemObject::Resume( );
	}

	inline int GetCooldown( ) { return mCooldown; }
	inline void SetCooldown( int nCD ) { mCooldown = nCD; }

public:
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene ) ;
};




// ********************************************************************** //
// CItemRune
// ���������
// ********************************************************************** //
class CItemRune : public CItemObject
{
public:
	CItemRune( )
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

	virtual ~CItemRune() {}

	virtual int Initialize()
	{
		CItemObject::Initialize( );
		return 0;
	}

	virtual int Resume()
	{
		return CItemObject::Resume( );
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );
	virtual void GetItemBinary2( PBItemObject*& pGene ) { return; }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemJewel
// �鱦�����
// ********************************************************************** //
class CItemJewel : public CItemObject
{
public:
	CItemJewel( )
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

	virtual ~CItemJewel() {}

	virtual int Initialize()
	{
		CItemObject::Initialize( );
		return 0;
	}

	virtual int Resume()
	{
		return CItemObject::Resume( );
	}

public:
	
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );
	virtual void GetItemBinary2( PBItemObject*& pGene ) { return; }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemYuanBug
// Ԫ���������
// ********************************************************************** //
class CItemYuanBug : public CItemObject
{
private:
	// ��ǰ�洢��Ԫ��
	int		mCurrent;
public:
	CItemYuanBug( )
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

	virtual ~CItemYuanBug() {}

	virtual int Initialize()
	{
		CItemObject::Initialize( );
		mCurrent = 0;
		return 0;
	}

	virtual int Resume()
	{
		return CItemObject::Resume( );
	}
	

	inline int GetCurrent( ) { return mCurrent; }
	inline void SetCurrent( int nCur ) { mCurrent = nCur; }

	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );
	virtual void GetItemBinary2( PBItemObject*& pGene )
	{
		pGene->mutable_itemcontent()->set_current( mCurrent );
	}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );



};

// ********************************************************************** //
// CItemYuanEgg
// Ԫ���������
// ********************************************************************** //
class CItemYuanEgg : public CItemObject
{
public:
	CItemYuanEgg( )
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

	virtual ~CItemYuanEgg() {}

	virtual int Initialize()
	{
		CItemObject::Initialize( );
		return 0;
	}

	virtual int Resume()
	{
		return CItemObject::Resume( );
	}

	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );
	virtual void GetItemBinary2( PBItemObject*& pGene ) { return; }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemScroll
// �������
// ********************************************************************** //
class CItemScroll : public CItemObject
{
private:
	int		mActivated;	// �Ƿ񼤻�


public:
	//TODO
	CItemScroll( )
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

	virtual ~CItemScroll( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		mActivated = 0;
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

	inline int GetActivated() { return mActivated; }
	inline void GetActivated( int nActivate ) { mActivated = nActivate; }

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene )	{	pGene->set_cooldown( mActivated );	}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};


// ********************************************************************** //
// CItemCard
// ��Ƭ����
// ********************************************************************** //
class CItemCard : public CItemObject
{

public:
	//TODO
	CItemCard( )
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

	virtual ~CItemCard( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene )	{	}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};



// ********************************************************************** //
// CItemCall
// �ٻ������
// ********************************************************************** //
class CItemCall : public CItemObject
{
public:
	//TODO
	CItemCall( )
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

	virtual ~CItemCall( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene )	{	}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemReturnPaper
// ���ؾ����
// ********************************************************************** //
class CItemReturnPaper : public CItemObject
{

public:
	//TODO
	CItemReturnPaper( )
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

	virtual ~CItemReturnPaper( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene )	{	}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};


// ********************************************************************** //
// CItemGiftBag
// ��������
// ********************************************************************** //
class CItemGiftBag : public CItemObject
{
public:
	//TODO
	CItemGiftBag( )
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

	virtual ~CItemGiftBag( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene )	{	}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemTeleSymbol
// ���ͷ�����
// ********************************************************************** //
class CItemTeleSymbol : public CItemObject
{
public:
	//TODO
	CItemTeleSymbol( )
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

	virtual ~CItemTeleSymbol( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene )	{	}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemStove
// ¯ʯ����
// ********************************************************************** //
class CItemStove : public CItemObject
{
private:
	int		mCoolDown;		// ��ǰʣ����ȴʱ��

public:
	//TODO
	CItemStove( )
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

	virtual ~CItemStove( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		mCoolDown = 0;
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

	inline int GetCooldown( ) { return mCoolDown; }
	inline void SetCooldown( int nCD ) { mCoolDown = nCD; }

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemMineMap
// �ر�ͼ
// ********************************************************************** //
class CItemMineMap : public CItemObject
{
private:
	// ��¼�洢��λ��
	unsigned short		mLineID;	
	unsigned short		mMapID;
	int					mPosX;
	int					mPosY;

public:
	//TODO
	CItemMineMap( )
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

	virtual ~CItemMineMap( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		mLineID = 0;
		mMapID = 0;
		mPosY = 0;
		mPosX = 0;
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

	inline unsigned short GetLineID() { return mLineID; }
	inline void SetLineID( unsigned short unLineID ) { mLineID = unLineID; }

	inline unsigned short GetMapID() { return mMapID; }
	inline void SetMapID( unsigned short unMapID ) { mMapID = unMapID; }

	inline int GetPosX() { return mPosX; }
	inline void SetPosX( int nPosX ) { mPosX = nPosX; }

	inline int GetPosY() { return mPosY; }
	inline void SetPosY( int nPosY ) { mPosY = nPosY;}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemToken
// ����
// ********************************************************************** //
class CItemToken : public CItemObject
{
private:
	// ��¼�洢��λ��
	unsigned short		mLineID;	
	unsigned short		mMapID;
	int					mPosX;
	int					mPosY;
public:
	//TODO
	CItemToken( )
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

	virtual ~CItemToken( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		mLineID = 0;
		mMapID = 0;
		mPosY = 0;
		mPosX = 0;
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

	inline unsigned short GetLineID() { return mLineID; }
	inline void SetLineID( unsigned short unLineID ) { mLineID = unLineID; }

	inline unsigned short GetMapID() { return mMapID; }
	inline void SetMapID( unsigned short unMapID ) { mMapID = unMapID; }

	inline int GetPosX() { return mPosX; }
	inline void SetPosX( int nPosX ) { mPosX = nPosX; }

	inline int GetPosY() { return mPosY; }
	inline void SetPosY( int nPosY ) { mPosY = nPosY;}


public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemMagicStone
// ��ħʯ
// ********************************************************************** //
class  CItemMagicStone : public CItemObject
{
public:
	CItemMagicStone()
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
	~CItemMagicStone( ){ }
	
public:
	int Initialize( ){ return 0; }
	int Resume( ){ return 0; }
	
public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene ){ }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );	
};

// ********************************************************************** //
// CItemLifeSkillScroll
// ����ܾ���
// ********************************************************************** //
class  CItemLifeSkillScroll : public CItemObject
{
public:
	CItemLifeSkillScroll()
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
	~CItemLifeSkillScroll( ){ }

public:
	int Initialize( ){ return 0; }
	int Resume( ){ return 0; }

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene ){ }
	static CItemObject* BinaryClone2( PBItemObject*& pGene );	
};

// ********************************************************************** //
// CItemRemove
// ժ����
// ********************************************************************** //
class CItemRemove : public CItemObject
{		
public:
	//TODO
	CItemRemove( )
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

	virtual ~CItemRemove( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene ){}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemChange
// ת����
// ********************************************************************** //
class CItemChange : public CItemObject
{		
public:
	//TODO
	CItemChange( )
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

	virtual ~CItemChange( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene ){}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemChange
// ת����
// ********************************************************************** //
class CItemRedPaper : public CItemObject
{  
public:
	//TODO
	CItemRedPaper( )
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

	virtual ~CItemRedPaper( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}
	
public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene ){}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};


// ********************************************************************** //
// CItemRunTime
// ********************************************************************** //

class CItemRunTime
{
	//typedef CItemObject* ( *ItemCloneFromBinary )( char*& pGene );
	//typedef CItemObject* ( *ItemCloneFromString )( char* pString );
	typedef CItemObject* ( *ItemCreator )( unsigned int vItemID, unsigned int vNumber );

	typedef CItemObject* ( *ItemCloneFromBinary2 )( PBItemObject*& pGene );

public:
	unsigned short	mItemType;
	//ItemCloneFromBinary		mpItemBinaryClone;		// ͨ�������¡
	//ItemCloneFromString		mpItemStringClone;		// ͨ���ַ�����¡
	ItemCreator				mpItemCreator;			// ����һ���µ���

	ItemCloneFromBinary2	mpItemBinaryClone2;		// ͨ�������¡2

public:
	// ���߿�¡��
	static std::vector< CItemRunTime >* spItemTypes;

	static void RegisterClone( unsigned short vItemType, ItemCloneFromBinary2 pBinaryClone2, ItemCreator pCreator )
		{ spItemTypes->push_back( CItemRunTime( vItemType,  pBinaryClone2, pCreator ) ); }

	static void Initialize( );

	static void Finialize( ){	delete spItemTypes;	}

public:
	CItemRunTime( unsigned short vItemType,  ItemCloneFromBinary2 pBinaryClone2, ItemCreator pCreator ) : 
	  mItemType( vItemType ),  mpItemCreator( pCreator ),mpItemBinaryClone2( pBinaryClone2 )
	{
	}

public:
	static CItemObject* CloneFromBinary2( PBItemObject*& pGene );
	static CItemObject* Clone( unsigned int vItemID, unsigned int vNumber );
	
};	

// ********************************************************************** //
// CItemVip
// ��Ա����
// ********************************************************************** //
class CItemVip : public CItemObject
{  
public:
	//TODO
	CItemVip( )
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

	virtual ~CItemVip( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene ){}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemClean
// ϴ�����
// ********************************************************************** //
class CItemClean : public CItemObject
{  
public:
	//TODO
	CItemClean( )
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

	virtual ~CItemClean( ) {}

	virtual int Initialize()
	{
		CItemObject::Initialize();
		return 0;
	}

	virtual int Resume()
	{
		return 	CItemObject::Resume();
	}

public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene ){}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemLeagueBag
// ��������ع���Ʒ
// ********************************************************************** //
class  CItemLeagueBag : public CItemObject 
{
public:
	CItemLeagueBag()
	{
		if ( CObj::msCreateMode )
		{
			Initailize();	
		}
		else
		{
			Resume();
		}
	}
	
	~CItemLeagueBag( ){ }
	virtual int Initailize()
	{
		return CItemObject::Initialize();		
	}
	
	virtual int Resume( )
	{
		return CItemObject::Resume();
	}
public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene ){}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
};

// ********************************************************************** //
// CItemInvitation
// �������
// ********************************************************************** //
class CItemInvitation : public CItemObject
{
public:
	CItemInvitation()
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
	~CItemInvitation(){ }
	virtual int Initialize()
	{
		memset( mGroomName, 0, sizeof( mGroomName ) );
		memset( mBrideName, 0, sizeof( mBrideName ) );
		mWeddingTime = 0;
		mWeddingLength = 0;
		return CItemObject::Initialize();	
	}
	virtual int Resume()
	{
		return CItemObject::Resume();
	}
public:
	char mGroomName[NAME_LENGTH];	// ��������
	char mBrideName[NAME_LENGTH];	// ��������
	int  mWeddingTime;				// ����
	int  mWeddingLength;			// ����ʱ��
public:
	
	// ����&��ȡ���ɵ�����
	void SetGroomName( const char *pName )
	{
		strncpy( mGroomName, pName, NAME_LENGTH - 1 );				
		mGroomName[NAME_LENGTH-1] = '\0';
	}
	const char * GetGroomName(){ return mGroomName; }
	
	// ����&��ȡ���������
	void SetBrideName( const  char *pName )
	{
		strncpy( mBrideName, pName, NAME_LENGTH - 1 );
		mBrideName[NAME_LENGTH-1] = '\0';
	}	
	const char *GetBrideName(){ return mBrideName; }
	
	// ����&��ȡ����
	void SetWeddingTime( int nTime ){ mWeddingTime = nTime; }
	int	GetWeddingTime( ){ return mWeddingTime; }
	
	// ����&��ȡ����ʱ��
	void SetWeddingTimeLength( int nTimeLength ){ mWeddingLength = nTimeLength; }
	int	GetWeddingTimeLength(){ return mWeddingLength; }
	
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );
	
};


// ********************************************************************** //
// CItemInvitation
// �������
// ********************************************************************** //
class CItemSysInvitation : public CItemObject
{
public:
	CItemSysInvitation()
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
	~CItemSysInvitation(){ }
public:
	virtual int Initialize()
	{
		return 0;
	}
	virtual int Resume()
	{
		return 0;
	}
public:	
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene ){}
	static CItemObject* BinaryClone2( PBItemObject*& pGene );	
};

// ********************************************************************** //
// CItemBlackPills
// �ڹ���
// ********************************************************************** //
class CItemBlackPills : public CItemObject
{
public:
	CItemBlackPills()
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
	~CItemBlackPills(){}
public:	
	virtual int Initialize()
	{
		mLeftTime = 0;
		return 0;
	}
	virtual int Resume()
	{
		return 0;
	} 
public:
	int GetLeftTime(){ return mLeftTime; }
	void SetLeftTime( int nTime ){ mLeftTime = nTime; }
public:
	int mLeftTime;
public:	
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );		 	
};	   

// ********************************************************************** //
// CItemExpContainer
// �������鵤
// ********************************************************************** //
class CItemExpContainer : public CItemObject
{
public:
	CItemExpContainer()
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
	~CItemExpContainer() {}
public:
	virtual int Initialize()
	{
		mExp = 0;
		return 0;				
	}
	
	virtual int Resume()
	{
		return 0;			
	}

public:	   	
	unsigned long long GetExp() { return mExp; }
	void SetExp( unsigned long long nExp ) { mExp = nExp; }
private:
	unsigned long long mExp;
public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );		 
};

// ********************************************************************** //
// CItemExpContainer
// �������鵤
// ********************************************************************** //
class CItemExpPills : public CItemObject
{
public:
	CItemExpPills()
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
	~CItemExpPills(){}
public:	
	virtual int Initialize() 
	{
		return 0;
	}
	virtual int Resume()
	{
		return 0;
	}
public:
	static CItemObject* Creator( unsigned int vItemID, unsigned int vNumber );	
	virtual void GetItemBinary2( PBItemObject*& pGene );
	static CItemObject* BinaryClone2( PBItemObject*& pGene );		 	
};

// ********************************************************************** //
// CItemList
// ********************************************************************** //
template< int NUMBER >
class CItemList 
{
private:

	int mpItems[ NUMBER ];

public:

	virtual int Initialize()
	{
		for( int i = 0; i < NUMBER; i ++ )
		{
			mpItems[ i ] = INVALID_OBJ_ID;
		}
		return 1;
	}

	virtual int Resume(){	return 1;	}

public:

	CItemList( )
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

	virtual ~CItemList( )
	{
	}

public:

	CItemList( const CItemList& rItemList )
	{
		for ( int i = 0; i < NUMBER; i ++ )
		{
			mpItems[ i ] = INVALID_OBJ_ID;
		}
	}
	

	CItemList& operator = ( const CItemList& rItemList )
	{
		if ( this == &rItemList )
			return *this;

		for ( int i = 0; i < NUMBER; i ++ )
		{
			mpItems[ i ] = INVALID_OBJ_ID;
		}

		for ( int i = 0; i < NUMBER; i ++ )
		{
			if ( rItemList.mpItems[ i ] == INVALID_OBJ_ID )
				continue;
		}

		return *this;
	}

public:
	// ��ȫ�����ֻ����ָ��
	int& operator [] ( int vIndex )
	{
		if( vIndex < 0 || vIndex >= NUMBER )
		{
			// ���������������Ƚ�����
			LOG_FATAL( "pro", "[%s:%d] index %d over flow %d", __FUNCTION__, __LINE__, vIndex, NUMBER );
			return mpItems[0];
		}

		return mpItems[ vIndex ];
	}

	CItemObject* GetItemObjPtr( int vIndex )
	{
		if( vIndex < 0 || vIndex >= NUMBER )
		{
			LOG_ERROR( "pro", "[%s:%d] index %d over flow %d", __FUNCTION__, __LINE__, vIndex, NUMBER );
			return NULL ;
		}
		
		if( mpItems[ vIndex ] != INVALID_OBJ_ID )
		{
			return (CItemObject*) CSceneObjManager::GetSingletonPtr()->GetObject ( mpItems[ vIndex ] );	
		}
		else
		{
			return NULL;
		}
	}

	bool  ChangeItemByIndex(int vIndex, int itemid,int isBind)
	{
		if( vIndex < 0 || vIndex >= NUMBER )
		{
			LOG_ERROR( "pro", "[%s:%d] index %d over flow %d", __FUNCTION__, __LINE__, vIndex, NUMBER );
			return  FALSE;
		}

		if( mpItems[ vIndex ] == INVALID_OBJ_ID )
		{
			return FALSE;	
		}
		CItemObject* obj = (CItemObject*) CSceneObjManager::GetSingletonPtr()->GetObject ( mpItems[ vIndex ] );
		if (obj == NULL)
		{
			return FALSE;
		}
		obj->SetItemID(itemid) ;
		if (isBind == ITEM_BINDSTATUS_BINDED)
		{
			obj->SetBindStatus(ITEM_BINDSTATUS_BINDED);
		}
		return  TRUE;
	}

	void Clear( )
	{
		for ( int i = 0; i < NUMBER; i ++ )
		{
			if( mpItems[ i ] == INVALID_OBJ_ID )
			{
				continue;
			}

			CSceneObjManager::GetSingletonPtr( )->DestroyObject( mpItems[ i ] ) ;
			mpItems[ i ] = INVALID_OBJ_ID;
		}
	}

	void GetTlvBuffer2( PBItemBox* pBuffer, int tStart = 0, int tEnd = NUMBER )
	{
		tEnd = std::min( NUMBER, tEnd );
		int tCount = 0;
		for ( int i = tStart; i < tEnd; i++ )
		{
			if ( INVALID_OBJ_ID == mpItems[ i ] )
			{
				continue;
			}
		
			CItemObject* pItemObj = (CItemObject*) CSceneObjManager::GetSingletonPtr()->GetObject( mpItems[ i ] );
			if( pItemObj == NULL)
			{
				LOG_ERROR( "pro", "can't find (id:%d, index:%d) object in itembox ", mpItems[i], i );
				continue;
			}

			::PBItemObject* tpPBItemObject = pBuffer->add_itemobjects();
			tpPBItemObject->set_itemid( pItemObj->GetItemID() );
			tpPBItemObject->set_number( pItemObj->GetItemNum() );
			if( pItemObj->GetBindStatus() != 0 )
				tpPBItemObject->set_bindstatus( pItemObj->GetBindStatus() );
			if( pItemObj->GetUsedTimes() != 0 )
				tpPBItemObject->set_usedtimes( pItemObj->GetUsedTimes() );

			if (pItemObj->GetGUID() != 0)
			{
				tpPBItemObject->set_objguid(pItemObj->GetGUID());
			}

			if (pItemObj->GetPurchaseID() != 0)
			{
				tpPBItemObject->set_purchaseid (pItemObj->GetPurchaseID());	
			}

			if (pItemObj->GetInvalidTime() != 0)
				tpPBItemObject->set_invalidtime(pItemObj->GetInvalidTime());			
	
			tpPBItemObject->set_index( i );
			pItemObj->GetItemBinary2( tpPBItemObject );
			tCount++;
		}
	}
	 

	bool CreateFromTlv2( PBItemBox* pBuffer )
	{
		int tCount = pBuffer->itemobjects_size();
		for ( int i = 0; i < tCount; i++ )
		{
			::PBItemObject* tpPBItemObject = pBuffer->mutable_itemobjects( i );

			CItemObject* tpItem = CItemRunTime::CloneFromBinary2( tpPBItemObject );
			if( tpItem == NULL )
			{
				LOG_ERROR( "pro", "Item Clone fuction didn't register. item id %d", tpPBItemObject->itemid() );
				return false;
			}

			unsigned int tIndex = tpPBItemObject->index( );

			if( tIndex > ARRAY_CNT(mpItems) || tIndex < 0 )
			{
				LOG_ERROR( "pro" ,"In CItemList::CreateFromTlv, invalide index %d", tIndex );
				continue;
			}

			mpItems[ tIndex ] = tpItem->get_id();
		}

		return true;
	}
	// ����ĳһ��Ϊ��
	void SetIndexNull( int index ){	mpItems[ index ] = INVALID_OBJ_ID; }

	// ���ݶ���ID ��������
	int	GetIndexByObjID( int nObjID )
	{
		for ( int i = 0; i < NUMBER; i ++ )
		{
			if( mpItems[ i ] == nObjID )
			{
				return i;
			}
		}
		return -1;
	}

	virtual void DeleteUnusedItem( int vCharID );
};

// ********************************************************************** //
// CItemBox
// ********************************************************************** //




class CItemBox : public CItemList< BOX_LIMIT >
{
public:
	unsigned int mReleaseIndex;			// ��ǰ�ͷŵ��Ǹ����� 
	int mKitbag[ MAX_KITBAG_NUM ];		// ������λ		
	int mKitBagStatus;					// ����״̬
	int	mKitBagIndex;					// ��չ������
	int mKitLocked[ MAX_KITBAG_NUM ];  // ��λ�Ƿ�����
	typedef lk::hash_map< int, int, BOX_LIMIT > ITEMNUMBERPAIR;

	ITEMNUMBERPAIR mItemPair;			// ��ƷID�������Ķ�Ӧ��ϵ
public:
	CItemBox(  )
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

	virtual ~CItemBox( ){}

	virtual int Initialize( );
	
	virtual int Resume( )
	{
		return 0;
	}

public:
	unsigned int Space( );

	bool Lock( int vItemIndex, int vLock );

	bool HasItem( unsigned int vItemID, unsigned int vNumber, int vType = BIND_ALL );

	int HasItem( unsigned int vItemID, int vType = BIND_ALL );

	bool HasItem( unsigned int vIndex, unsigned int vItemID, unsigned int vNumber, int vType = BIND_ALL );

	int GetItemNum( unsigned int vIndex, unsigned int vItemID, int vType = BIND_ALL );

	bool Space( int* pItemID, int* pNumber, int vNumber );

	bool Space( unsigned int vItemID, unsigned int vNumber );	

	//int RemoveItemByID( unsigned int vItemID, unsigned int vNumber = ~0, int vType = BIND_ALL );

	int RemoveItem( unsigned int vIndex, unsigned int vNumber = ~0 );

	int InsertItem( CItemObject* pItem, int *vIndex, int *vNumber, int &vLen );
	
	int InsertItem( CItemObject* pItem, int vIndex );
	// ɾ������
	CItemObject* EraseItem( int vSrcIndex, int vNumber );

	//// �õ�ʹ�ô���
	//int	GetItemUsedTimes( int vItemID );

	int Move( unsigned int vSrcIndex, unsigned int vDesIndex, CItemBox& rDesBox, unsigned int vNumber , int &rMoveNum );
	
	bool CreateFromTlv2( PBItemBox* pBuffer );
	void GetTlvBuffer2( PBItemBox* pBuffer, int tStart = 0, int tEnd = BOX_LIMIT );
	// �Ƿ���ĳ�����͵���Ʒ( ����ǹ�������Ʒ�Ļ���nFuncType���븳ֵ, rIndex ��¼���һ����Ʒ��λ�� )
	int HasItemOfCertainType( int nType, int &rNum, int &rIndex, int nFuncType = 0 );
	
	// ��ȡ��Ʒ������
	int GetItemType( int vSrcInde, int &rType );

	int GetTlvSize2( );

	int	GetKitBagIDByIndex( int nIndex ); 
	int AddKitBag( int nIndex, int nNewKitBagID,  int &rOldKitBagObjID, int nNewKitBagObjID );
	
	// ȡ�±���
	int TakeKitBag( int nKitBagIndex, int &rKitBagObjID ); 

	// Set & Get KitBagStatus
	int		GetKitBagStatus(){ return mKitBagStatus; }
	void 	SetKitBagStatus( int nKitBagStatus ){ mKitBagStatus = nKitBagStatus; }

	// Set & Get ReleaseIndex
	int		GetReleaseIndex(){ return mReleaseIndex; }
	void 	SetReleaseIndex( int nReleaseIndex ){ mReleaseIndex = nReleaseIndex; }

	// Set & Get KitBagIndex
	int		GetKitBagIndex(){ return mKitBagIndex; }
	void 	SetKitBagIndex( int nKitBagIndex ){ mKitBagIndex = nKitBagIndex; }

	void    ResetPair(int nItemID, int nItemNum);
	int 	GetItemTotalCount( int nItemID);
	
	// ��ȡָ��λ�ñ����ĸ�������
	int GetKitBagIndexLimit( int nKitBagIndex, int &rNum );
	
	// ��ȡָ���������ڵİ�������
	int GetBagTypeByIndex( int nIndex, EBagType &rSlotType, int &rBagIndex );
	
	// ���ĳ��λ�õı����Ѿ�����
	bool CheckKitBagExpiredTime( int nKitBagIndex );
	
	// ��ȡָ����λ�ı�����Ʒ
	CItemKitBag *GetKitBagItemByIndex( int nKitBagIndex );
	// ת��ָ����λ������Ʒ
	bool ChangeKitBagItemByIndex(int index, int itemid,int isBind);
	
	// ��������Ƿ���Ч
	bool CheckIndexValid( int nIndex, bool bExceptExpiredKitbag = false );
	
	// ��ȡְλλ�ñ�������ȡʼĩλ��
	int GetKitBagIndexRange(  EBagType emSlotTyp, int nBagIndex, int &rBeginIndex, int &rEndIndex );
	
	// ��ȡָ��λ�ð�������Ʒ��PB����
	int GetItemInBag( EBagType emSlotType, int nBagIndex, PBItemBox &rItemBox );
	
	// ��ȡָ��������Ʒ����
	int GetItemCountInBag( EBagType emSlotType, int nBagIndex, int &rCount );	
	
	// ������������ߣ��������Ʒ����
	void Clear( );	

	virtual void DeleteUnusedItem( int vCharID );
};



// ����������

class CItemBoxToolkit
{
public:
	CItemBox* mItemBox;

public:
	CItemBoxToolkit( CItemBox* pBox ) : mItemBox(pBox) { }
	~CItemBoxToolkit() {}

	// ����ָ�������ϵ��ض�������Ʒ����
	unsigned int ComputeItemNum( int nIdx, unsigned int nItemID, int nType  );

	// ����һ�������ڵ��ض�������Ʒ����
	unsigned int ComputeItemNum( int nBegin, int nEnd, unsigned int nItemID,  int nType );

	// ���������������ض�������Ʒ����
	unsigned int ComputeItemNum( unsigned int nItemID, int nType );

	//// �õ�ָ����������Ʒ��ʹ�ô���
	//int GetItemUsedNum( int nIdx, unsigned int nItemID );

	//// �õ�ָ��һ����������Ʒ��ʹ�ô���
	//int GetItemUsedNum( int nBegin, int nEnd, unsigned int nItemID );

	//// �õ�������ָ����Ʒ��ʹ�ô���
	//int GetItemUsedNum( unsigned int nItemID );

	// ����ָ�������϶�ָ����Ʒ��ʣ��ѵ���
	int GetLeftPileNum( int nIdx, unsigned int nItemID, bool bEmptyCounted = true );

	// ����һ�������ڶ�ָ����Ʒ��ʣ��ѵ���
	int GetLeftPileNum( int nBegin, int nEnd, unsigned int nItemID, bool bEmptyCounted = true );

	// �õ������ڶ�ָ����Ʒ��ʣ��ѵ���
	int GetLeftPileNum( unsigned int nItemID, bool bEmptyCounted = true );

	// �õ�ָ��������ָ�����͵ĵ��߸���
	int GetCertainTypeItemNum( int nIdx, int nType, int nFuncType );

	// ɾ��ָ��������ָ�������ĵ���
	int RemoveItem( int nIdx, unsigned int nItemID, unsigned int nNumber, int nType );

	// ��ָ����������ָ����������
	int InsertItem( int nIdx, CItemObject* pItem, CTplItem *pTplItem );

	/**
	** ������ �ж�ָ��������װ�����Ƿ�󶨵���
	** ���أ� INVALID_OBJ_ID����װ��������װ������δ�󶨻���װ�����Ѿ����
	*/
	int CheckEquipBindTime( int nIdx );

	/* �������õ�ָ��������װ����������
	** ���أ�<0 ����װ��������װ��������Ҫ����; 0����ʧ�;õ�װ������������Ϊ0; >0����ʧ�;õ�װ���������������0
	**/
	int GetEquipMendMoney( int nIdx );
};




// �½��ֿ��࣬�̳�CItemBox����¼�ֿⱳ������ȹ���
class CStorage : public CItemBox
{
public:			
	int		mBindMoney;						// �ֿ�洢�İ󶨽�Ǯ
	int		mMoney;							// �ֿ�洢�ķǰ󶨽�Ǯ
	bool	mChanged;						// �Ƿ�ı��
public:
	CStorage( )
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
	virtual ~CStorage(){}
public:
	virtual int Initialize( );	
	virtual int Resume( )
	{
		return 0;
	}
public:
	// ��ȡ&���ð󶨽�Ǯ
	//void SetBindMoney( int nBindMoney ){ mBindMoney = nBindMoney; }
	//int	 GetBindMoney( ){ return mBindMoney; }
	//
	//// ��ȡ&���ý�Ǯ
	//void SetMoney( int nMoney ){ mMoney = nMoney; }
	//int  GetMoney( ){ return mMoney; }
		
	// �洢&ȡ����Ǯ
	int StoreMoney( int nMoney, int nBindMoney );
	int TakeMoney( int nMoney, int nBindMoney );  	
	
	
public:

	bool CreateFromTlv2( PBItemBox* pBuffer );
	void GetTlvBuffer2( PBItemBox* pBuffer, int tStart = 0, int tEnd = BOX_LIMIT );	

	virtual void DeleteUnusedItem( int vCharID );
};

// �½������࣬�̳�CItemBox����¼��ʯ��Ƕ���¼�
class CBaggage : public CItemBox
{
public:
	int mUpgIndex1;					// ����װ��������
	int mUpgIndex2;					// ��ʯ������
	int mUpgIndex3;					// ���׷�������
	int mRuneIndex1;				// �ŷ���ʱװ��������
	int mRuneIndex2;				// �ŷ���ʱ���ĵ�����
	int mJewelIndex0;				// �ⱦʯʱװ��������
	int mJewelIndex[ JEWELNUM ];	// �ⱦʯʱ��ʯ������
	int mYuanIndex0;				// ��װ��ʱԪ���������
	int mYuanIndex[ YUANNUM ];		// ��װ��ʱװ��������
	int	mYuanNum;					// ��װ��ʱ����װ��������
	int mSlotIndex1;				// ����ʱװ��������
	int mSlotIndex2;				// ����ʱԪ����������
	int mComposeIndex;				// �ϳɵ�����
	int mEquipIndex;                // ���󶨻��߽���󶨵�װ��������
	int mBindItemIndex;             // ��ʯ������	
	int mEqtForReusmBindIndex;		// ���ָ��ֶ��󶨵���Ʒ������
	int mTaskLockIndex;				// �����������İ�������
	int mTeleSymbolIndex;			// ʹ�ô��ͷ������İ�������
	int mAddIndex1;					// ���Ӱ�������1
	int mAddIndex2;					// ���Ӱ�������2
	int mRemoveIndex1;				// ժ����ʯ����1
	int mRemoveIndex2;				// ժ����ʯ����2
	int mJudgeIndex1;				// ��������1
	int mJudgeIndex2;				// ��������2
	int mChangeIndex1;				// ת������1
	int mChangeIndex2;				// ת������2
	int mJewComIndex[ COMPOSENUM ]; // ��ʯ�ϳ�����
	int	mJewComNum;					// ��ʯ�ϳ�����
	int mMWIndex;					// ��������������
	int mMWStoneIndex;				// �����������Եı�ʯ����
	int mMultiIndex;				// ���Ӻϳ�

public:
	CBaggage(  )
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

	virtual ~CBaggage( ){}

	virtual int Initialize( );

	virtual int Resume( )
	{
		return 0;
	}
	void SetTaskLockIndex( int vIndex ){ mTaskLockIndex = vIndex; }
	int  GetTaskLockIndex( ){ return mTaskLockIndex ; }

	void SetMWLockIndex( int vIndex ){ mMWIndex = vIndex; }
	int  GetMWLockIndex( ){ return mMWIndex ; }

	void SetMWStoneLockIndex( int vIndex ){ mMWStoneIndex = vIndex; }
	int  GetMWStoneLockIndex( ){ return mMWStoneIndex ; }

	void SetTeleSymbolIndex( int vIndex ) { mTeleSymbolIndex = vIndex; }
	int GetTeleSymbolIndex(){ return mTeleSymbolIndex; }

	int AddUpgItem( unsigned int vIndex );

	int DelUpgItem( unsigned int vIndex );

	int AddRuneItem( unsigned int vIndex );

	int DelRuneItem( unsigned int vIndex );

	int AddJewelItem( unsigned int vSrcIndex, unsigned int vDesIndex );

	int DelJewelItem( unsigned int vIndex );

	int AddSlotItem( unsigned int vIndex );

	int DelSlotItem( unsigned int vIndex );

	int AddYuanItem( unsigned int vIndex );

	int DelYuanItem( unsigned int vIndex );

	int AddComposeItem( unsigned int vIndex );

	int DelComposeItem( );

	int GetEquipIndex() {return mEquipIndex;}

	int AddAddItem( unsigned int vIndex );

	int DelAddItem( unsigned int vIndex );

	int AddRemoveItem( unsigned int vIndex );

	int DelRemoveItem( unsigned int vIndex );

	int AddJudgeItem( unsigned int vIndex );

	int DelJudgeItem( unsigned int vIndex );

	int AddChangeItem( unsigned int vIndex );

	int DelChangeItem( unsigned int vIndex );

	int AddJewComItem( unsigned int vIndex );

	int DelJewComItem( unsigned int vIndex );

	int AddMultiItem( unsigned int vIndex );

	int DelMultiItem( unsigned int vIndex );

	virtual void DeleteUnusedItem( int vCharID );
};


class CEquipment : public CItemList< EQUIP_LIMIT >
{
public:
	
	enum
	{
		MIN_PRO_AWARD_NUM = 4,
	};

	CEquipment(  )
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
	
	virtual int Initialize() { CItemList<EQUIP_LIMIT>::Initialize(); return 0;}
	virtual int Resume() { CItemList<EQUIP_LIMIT>::Resume();  return 0;}

	virtual ~CEquipment( ){}
	
	static int GetPartType( unsigned short vPart );
	
	unsigned short GetIncSkillLevel( unsigned short vSkillID );
	unsigned short GetValueByID( unsigned short vSkillID, CTemplateProperty::PROPERTY_FUNC vType );
	int	GetStateID( StateList& vBuffList,CTemplateProperty::PROPERTY_FUNC vType );
	
	// װ��ĳ��װ��
	int Equip( CPropertyPlayer* pProperty, CItemBox& rBaggage, unsigned int vSrcIndex, unsigned int &vDesIndex );

	// ж��ĳ��װ��
	int UnEquip( CPropertyPlayer* pProperty, CItemBox& rBaggage, unsigned short vPart, unsigned int vIndex = ~0 );

	int GetSuit( unsigned short vFunc, unsigned short vType, unsigned short vSkillID = 0 );
	// �����װ�ӳ���ֵ
	int	GetSuitInc( unsigned short vFunc );
	// �����װ�ӳɰٷֱ�
	int GetSuitPer( unsigned short vFunc );

	int GetFixNumber( CTemplateProperty::PROPERTY_FUNC vFunc, int vEquipProType = 0, CPropertyPlayer *pProperty = NULL );
	int GetPerNumber( CTemplateProperty::PROPERTY_FUNC vFunc );

	// ��÷���ֵ
	void GetLightPoint( int &WeaponLevel, int &ChestLevel, int &WeaponJewel, int &ChestJewel );

	unsigned int GetFixPAttackUpper( CPropertyPlayer* pProperty );
	unsigned int GetFixPAttackLower( CPropertyPlayer* pProperty );
	unsigned int GetFixMAttackUpper( CPropertyPlayer* pProperty );
	unsigned int GetFixMAttackLower( CPropertyPlayer* pProperty );
	unsigned int GetFixPDefence( CPropertyPlayer* pProperty );
	unsigned int GetFixMDefence( CPropertyPlayer* pProperty );

	virtual void DeleteUnusedItem( int vCharID );
};




// ********************************************************************** //
// CShortcut
// ********************************************************************** //

class CShortcut
{
public:
	unsigned int	mShortcut;
	unsigned int	mType;
	unsigned int	mIndex;
	unsigned int    mLabelType;
	unsigned int	mLabelIndex;
	int mParam1;
public:
	//TODO
	CShortcut( ) {}

	CShortcut( unsigned int vShortcut , unsigned int vType , unsigned int vIndex, unsigned int vLabelType, unsigned int vLabelIndex, int nParam1 ) : mShortcut( vShortcut ),
		 mType( vType ), mIndex( vIndex ), mLabelType( vLabelType ), mLabelIndex( vLabelIndex ), mParam1( nParam1 )
	{
	}


};

// ********************************************************************** //
// CShortcutList
// ********************************************************************** //

class CShortcutList
{
public:
	unsigned short	mShortcutNumber;
	CShortcut		mShortcut[ 48 ];
	int				mHelpActionStatus[ MAX_HELPACTON_INT_NUM ];	// ����ָ������״̬ 

public:

	CShortcutList( ) : mShortcutNumber( 0 )
	{
		memset( mHelpActionStatus, 0, sizeof( mHelpActionStatus ) );
	}

public:
	void Clear( )
	{
		mShortcutNumber = 0;
		::memset( mShortcut, 0, sizeof( mShortcut ) );
		::memset( mHelpActionStatus, 0, sizeof( mHelpActionStatus ) );
	}

	CShortcut GetShortcut( int vIndex );
	
	void SetShortcut( unsigned int vShortcut, unsigned int vType, unsigned int vIndex, unsigned int vLabelType, unsigned int vLabelIndex, int nParam1 );
	
	void CreateFromTlv2( PBShortcutList* pBuffer );	

	void GetTlvBuffer2( PBShortcutList* pBuffer );
	
	void SetHelpStatus( int Status, int Index );
	
	int  GetHelpStatus(  int Index ); 
	

};

// ********************************************************************** //
// CDamage
// ********************************************************************** //
class CDamage
{
public:
	int		mSrcEntityID;			// ����˺���ʵ��ID
	int		mDamageValue;			// �˺�ֵ�ۼ�
public:
	//TODO
	CDamage( )
	{
		if ( CObj::msCreateMode )
		{
			mSrcEntityID = INVALID_OBJ_ID;
			mDamageValue = 0;
		}
	}

	CDamage( int vSrcEntityID /*= 0*/, int vDamageValue /*= 0 */) : mSrcEntityID( vSrcEntityID ), mDamageValue( vDamageValue )
	{
	}

	~CDamage() {}
};

// ********************************************************************** //
// CDamageList
// ********************************************************************** //
class CDamageList
{
public:
	CDamage		mDamage[ DAMAGELIMIT ];		// ����¼512��ʵ���˺�

	int			mNumber;			// �˺��ߵ�����

public:

	CDamageList( )
	{
		if ( CObj::msCreateMode )
		{
			mNumber = 0;
		}
	}

	~CDamageList( ) {}

	float GetDamagePer( int vEntityID, int tMaxHP );
	

	int InsertDamage( const CDamage& rDamage );
	

	int RemoveDamage( int vEntityID );
	

	void ClearDamage( )
	{
		::memset( mDamage, 0, sizeof( CDamage ) * DAMAGELIMIT );
		mNumber = 0;
	}
};


// ���ڼ�¼��������Ʒ����ʱ
class CProduce
{
public:
	unsigned short mType1;
	unsigned short mType2;
	unsigned short mType3;
	unsigned short mLevel;
	unsigned short mRank;
	unsigned short mNumber;
	int	mTimer;	
public:

	//TODO
	CProduce( ) {}

	void Clear( )
	{
		mType1	= 0;
		mType2	= 0;
		mType3	= 0;
		mLevel	= 0;
		mRank	= 0;
		mNumber = 0;
		mTimer	= 0;
	}
};

class ComplexPos
{
public:
	ComplexPos()
	{
		if ( CObj::msCreateMode )
		{
			mLineID = 0;
			mMapID  = 0;
			mPos.mX = -1;
			mPos.mY = -1;
		}
	}
	unsigned int mLineID;
	unsigned int mMapID;
	CWTPoint mPos;
};


enum STATE_FROM
{
	NONE		= 0,
	EQUITMENT	= 1,
	BUFF		= 2,
	SKILL		= 3,
};
struct StateParam
{
	bool		mInState;
	STATE_FROM	mFrom;
	int			mIndex;
	int			mParames1;
	int			mParames2;
	int			mBuffAdd;

	StateParam( )
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

	int Initialize( )
	{
		Clean( );
		return SUCCESS;
	}

	int Resume( )
	{
		return 0;
	}

	void Clean( )
	{
		mInState	= false;
		mFrom		= NONE;
		mIndex		= 0;
		mParames1	= 0;
		mParames2	= 0;
		mBuffAdd	= 0;
	}
};
struct TripEntityInfo
{
	int mTripEntityID;
	int mTripIndex;

	TripEntityInfo()
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

	int Initialize( )
	{
		Clean( );
		return SUCCESS;
	}

	int Resume( )
	{
		return 0;
	}

	void Clean()
	{
		mTripEntityID = 0;
		mTripIndex = 0;
	}
};

/************************************************************************/
/* �����ṹ                                                                     */
/************************************************************************/
class CPlayerRepetion
{
private:
	struct 			RepetionData
	{
		int			mIntData[ 13 ];
		int			mCount;
		int			mWeekCount;
		uint64_t	mLastSaveTime;
		int			mSignUp;
		int			mIntoTime;
		int			mDieCount;		
	};
private:
	unsigned short	mBackLineID;
	unsigned short	mBackMapID;
	unsigned short	mBackPosX;
	unsigned short	mBackPosY;
	bool			mLoadFalse;
	int				mCampID;			// ��Ӫ, PVPս��		

	KEY_TYPE		mOldRepeKey;		// fuck all 
	RepetionData	mRepeData[ _REPE_MAX_COUNT_ ];

	int				mInRepetion;
	int				mInRepetionIndex;
	
	bool			mCheckResult;		// �����������֤���
	int				mAnswerCount;		// �������	
	int				mGlobalSceneStatus;	// ȫ�ַ�����״̬
	int				mGlobalWarOfflineTime;// ��ȫ�ָ������뿪��ʱ��
	KEY_TYPE		mRepetionKey;		// ��������ĸ���key(û�н��븱��֮ǰ�͸�ֵ)
public:
	CPlayerRepetion( ) 
	{
		if( CObj::msCreateMode == 1 )
		{
			Initialize( );
		}
		else
		{

		}
	}

	int Initialize( )
	{
		mBackLineID = 0;
		mBackMapID = 0;
		mBackPosY = 0;
		mBackPosX = 0;
		mLoadFalse = false;
//		memset( mRepetionCount,0, sizeof( mRepetionCount ) );
		mOldRepeKey = 0;
		memset( mRepeData, 0, sizeof( mRepeData ) );
		mCampID = 0;
		
		mInRepetion = 0;
		mInRepetionIndex = 0;
		mCheckResult = 0;
		mAnswerCount = 0;
		mGlobalSceneStatus = 0;
		mGlobalWarOfflineTime = 0;
		mRepetionKey = 0;
		return SUCCESS;
	}

	int Resume( )
	{
		return SUCCESS;
	}
	
	void SetGlobalSceneStatus( int nStatus ){ mGlobalSceneStatus = nStatus; }
	int GetGlobalSceneStatus(){ return mGlobalSceneStatus; }
	void SetGlobalWarOffLineTime( int nTime ){ mGlobalWarOfflineTime = nTime; }
	int GetGlobalWarOffLineTime(){ return mGlobalWarOfflineTime; }

	unsigned short GetBackLineID( )	{ return mBackLineID; }
	unsigned short GetBackMapID( )	{ return mBackMapID; }
	unsigned short GetPosX( )			{ return mBackPosX; }
	unsigned short GetPosY( )			{ return mBackPosY; }
	int GetRepetionCount( unsigned int vIndex, unsigned int* vCount );
	int GetRepetionWeekCount( unsigned int vIndex, unsigned int* vCount );

	int SetBackLineID( unsigned short vBackLineID ) { mBackLineID = vBackLineID; return SUCCESS; }
	int SetBackMapID( unsigned short vBackMapID ) { mBackMapID = vBackMapID; return SUCCESS; }
	int SetPosX( unsigned short vPosX ) { mBackPosX = vPosX; return SUCCESS; }
	int SetPosY( unsigned short vPosY ) { mBackPosY = vPosY; return SUCCESS; }
	int SetCampID( int vCampID ) { mCampID = vCampID; return SUCCESS; }
	int GetCampID( ) { return mCampID; }
	int IncRepetionCount( unsigned int vIndex ) ;
	
	int SetInRepetion( ) { mInRepetion = 1; return SUCCESS; }
	int SetUnRepetion( ) { mInRepetion = 0; return SUCCESS; }
	int GetInRepetion( ) { return mInRepetion; }
	int SetInRepetionIndex( int vRepetionIndex ) { mInRepetionIndex = vRepetionIndex; return mInRepetionIndex; }
	int GetInRepetionIndex( ){ return mInRepetionIndex; }

	

	int DecRepetionCount( unsigned int vIndex );

	int SetRepetion( unsigned int vIndex, unsigned int vCount, unsigned int vWeekCount, unsigned int vSignUp = 0 ,unsigned int vIntoTime = 0, unsigned int vDieCount = 0 );
	int RepetionSignUp( unsigned int vIndex);
	int RepetionClearSignUp( unsigned int vIndex);
	int GetSignUpTime( unsigned int vIndex );

	int SetRepetionIntoTime( unsigned int vIndex );
	int RepetionClearIntoTime( unsigned int vIndex );
	int GetIntoTime( unsigned int vIndex );

	int AddDieCount( unsigned int vIndex );
	int GetDieCount( unsigned int vIndex );
	int ClearDieCount( unsigned int vIndex );

	int ChangeRepetionCount( unsigned int vIndex, int vCount );

	int CleanRepetion( )
	{
		unsigned int i = 0;
		for( i = 0; i < ARRAY_CNT( mRepeData ); i++ )
		{
			mRepeData[ i ].mCount = 0;			
			mRepeData[ i ].mLastSaveTime = 0;	
		}
		mLoadFalse = true;
		return SUCCESS;
	}

	int CleanWeekRepetion( );

	int SetIntData( unsigned short vRepetionIndex, unsigned int vIndex, int vData )
	{
		LK_ASSERT( vRepetionIndex < ARRAY_CNT( mRepeData ), return ERR_INVALID_PARAMETER );
		LK_ASSERT( vIndex < ARRAY_CNT( mRepeData[ vRepetionIndex ].mIntData ), return ERR_INVALID_PARAMETER );

		if( mRepeData[ vRepetionIndex ].mIntData[ vIndex ] < 0 )
		{
			mRepeData[ vRepetionIndex ].mIntData[ vIndex ] = 0;
		}

		mRepeData[ vRepetionIndex ].mIntData[ vIndex ] = ( vData >= 0 ) ? vData : 0;
		return SUCCESS;
	}

	int GetIntData( unsigned short vRepetionIndex, unsigned int vIndex, int* vData )
	{
		LK_ASSERT( vRepetionIndex < ARRAY_CNT( mRepeData ), return ERR_INVALID_PARAMETER );
		LK_ASSERT( vIndex < ARRAY_CNT( mRepeData[ vRepetionIndex ].mIntData ), return ERR_INVALID_PARAMETER );

		*vData = mRepeData[ vRepetionIndex ].mIntData[ vIndex ];

		return SUCCESS;;
	}

	int SetOldRepeKey( KEY_TYPE vKey ) { mOldRepeKey = vKey; return SUCCESS; }
	KEY_TYPE GetOldRepeKey( ) { return mOldRepeKey; }

	int PB2Repetion( PBRepetion* vpPB, CEntityPlayer* vpPlayer );
	int Repetion2PB( PBRepetion* vpPB, KEY_TYPE vKey );
	
	// Get & Set CheckResult
	bool GetCheckResult(){ return mCheckResult; }
	void SetCheckResult( bool bCheckResult ){ mCheckResult = bCheckResult; }
	
	// Get & Set AnswerCount
	int GetAnswerCount() { return mAnswerCount; }
	void SetAnswerCount( int nAnswerCount ) { mAnswerCount = nAnswerCount; }
	
	// ���������֤
	void ClearQuestionVerifyInfo()
	{
		mCheckResult = false;		// �����������֤���
		mAnswerCount = 0;			// �������	
	}
	// Get&Set mRepetionKey
	KEY_TYPE GetRepetionKey(){ return mRepetionKey; }
	void SetRepetionKey( KEY_TYPE nKey ){ mRepetionKey = nKey; }
};

class CPlayerExchange
{
private:
	int 	mMoney;
	int		mYb;

public:
	CPlayerExchange( )
	{
		if( CObj::msCreateMode == 1 )
		{
			Initialize( );
		}
		else
		{

		}	
	}

	int Initialize( )
	{
		mMoney = 0;
		mYb = 0;
		return SUCCESS;
	}

	int SetMoney( int vMoney ) { mMoney = vMoney; return SUCCESS; }
	int SetYb( int vYb ) { mYb = vYb; return SUCCESS; }
	int GetMoney( ) { return mMoney; }
	int GetYb( ) { return mYb; }
};

// ********************************************************************** //
// CPropertyFormula
// ********************************************************************** //

class CPropertyFormula
{
public:
	// �õ���ս������״̬��HP�ָ��ٶ�
	static unsigned int GetNormalSitHPRSpeed( CPropertyCharacter* pProperty );

	// �õ���ս������״̬��MP�ָ��ٶ�
	static unsigned int GetNormalSitMPRSpeed( CPropertyCharacter* pProperty );

	// �õ�ս������״̬��HP�ָ��ٶ�
	static unsigned int GetBattleSitHPRSpeed( CPropertyCharacter* pProperty );

	// �õ�ս������״̬��MP�ָ��ٶ�
	static unsigned int GetBattleSitMPRSpeed( CPropertyCharacter* pProperty );

	// �õ���ս��״̬��HP�ָ��ٶ�
	static unsigned int GetNormalHPRSpeed( CPropertyCharacter* pProperty );

	// �õ���ս��״̬��MP�ָ��ٶ�
	static unsigned int GetNormalMPRSpeed( CPropertyCharacter* pProperty );

	// �õ�ս��״̬��HP�ָ��ٶ�
	static unsigned int GetBattleHPRSpeed( CPropertyCharacter* pProperty );

	// �õ�ս��״̬��MP�ָ��ٶ�
	static unsigned int GetBattleMPRSpeed( CPropertyCharacter* pProperty );

	// ���㼼�ܿ����˺�
	static unsigned int GetResAttack( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateSkill* pSkill );

	// ���㼼�������˺�
	static unsigned int GetPSkillAttack( 	CEntityCharacter* pSrcEntity,
											CEntityCharacter* pDesEntity,
											CTemplateSkill* pSkill, 
											EResultType& rResult
										);

	// ���㼼�ܷ����˺�
	static unsigned int GetMSkillAttack( 	CEntityCharacter* pSrcEntity,
											CEntityCharacter* pDesEntity,
											CTemplateSkill* vpSkill, 
											EResultType& rResult
										);

	// ������ͨ�������˺�
	static unsigned int GetPNormalAttack(	CEntityCharacter* pSrcEntity,
											CEntityCharacter* pDesEntity, 
											EResultType& rResult
										);

	// ������ͨħ�������˺�
	static unsigned int GetMNormalAttack(	CEntityCharacter* pSrcEntity,
											CEntityCharacter* pDesEntity,
											EResultType& rResult
										);

	// �õ������˺��ӳɹ̶�ֵ
	static int GetAddFixDamage( CPropertyCharacter* pProperty );

	// �õ������˺��ӳɰٷֱ�
	static int GetAddPerDamage( CPropertyCharacter* pProperty );

	// �õ��������˺�����̶�ֵ
	static int GetDecFixPDamage( CPropertyCharacter* pProperty );

	// �õ��������˺�����ٷֱ�
	static int GetDecPerPDamage( CPropertyCharacter* pProperty );

	// �õ����������˺�����̶�ֵ
	static int GetDecFixMDamage( CPropertyCharacter* pProperty );

	// �õ����������˺�����ٷֱ�
	static int GetDecPerMDamage( CPropertyCharacter* pProperty );
	
	// ��ȡ�˺�͵ȡHP�ٷֱ�
	static int GetStealHP( CPropertyCharacter* pProperty );
		
	// ��ȡ�˺�͵ȡMP�ٷֱ�
	static int GetStealMP( CPropertyCharacter* pProperty );

	// �õ���������
	static unsigned int GetPAttackValue( CPropertyCharacter* pProperty, bool bIsMagicWeapon = false );

	// �õ�����������
	static unsigned int GetMAttackValue( CPropertyCharacter* pProperty, bool bIsMagicWeapon = false );

	// �õ���������ֵ
	static unsigned int GetSkillHitrate( 	unsigned short vSkillID, 
											unsigned short vSkillLevel, 
											CPropertyCharacter* pProperty 
										);

	// �õ����������ֵ
	static CPropertyValue GetPAttackUpper( CPropertyCharacter* pProperty );

	// �õ������������ֵ
	static CPropertyValue GetMAttackUpper( CPropertyCharacter* pProperty );

	// �õ���������Сֵ
	static CPropertyValue GetPAttackLower( CPropertyCharacter* pProperty );

	// �õ�����������Сֵ
	static CPropertyValue GetMAttackLower( CPropertyCharacter* pProperty );

	// �õ����������
	static CPropertyValue GetPDefence( CPropertyCharacter* pProperty );

	// �õ�����������
	static CPropertyValue GetMDefence( CPropertyCharacter* pProperty );

	// �õ���������
	static int GetPImmunity( int vLevel, CPropertyCharacter* pProperty );

	// �õ���������
	static int GetMImmunity( int vLevel, CPropertyCharacter* pProperty );

	// �õ�������
	//static CPropertyValue GetPResist( CPropertyCharacter* pProperty );

	// �õ���������
	//static CPropertyValue GetMResist( CPropertyCharacter* pProperty );

	// �õ�����
	static CPropertyValue GetStr( CPropertyPlayer* pProperty );

	// �õ��ǻ�
	static CPropertyValue GetWis( CPropertyPlayer* pProperty );

	// �õ�����
	static CPropertyValue GetSpr( CPropertyPlayer* pProperty );

	// �õ�����
	static CPropertyValue GetCon( CPropertyPlayer* pProperty );

	// �õ�����
	static CPropertyValue GetSta( CPropertyPlayer* pProperty );

	// �õ��չ�����ֵ
	static CPropertyValue GetNormalHitrate( CPropertyCharacter* pProperty );

	// �õ��չ�����ֵ
	static CPropertyValue GetNormalDuck( CPropertyCharacter* pProperty );

	// �õ���������ֵ( ��Ӱ )
	static CPropertyValue GetSkillDuck( CPropertyCharacter* pProperty );

	// �õ���������ֵ
	static CPropertyValue GetIgnoreDuck( CPropertyCharacter* pProperty );

	// �õ�����һ���ȼ�
	static CPropertyValue GetDeathRate( CPropertyCharacter* pProperty, bool bIsMagicWeapon = false );

	// �õ�����һ���˺��ӳ�
	static CPropertyValue GetDeathValue( CPropertyCharacter* pProperty );

	// �õ�����һ������
	static CPropertyValue GetDeathDefense( CPropertyCharacter* pProperty );

	// �õ�HP���ֵ
	static CPropertyValue GetMaxHP( CPropertyCharacter* pProperty );

	// �õ�MP���ֵ
	static CPropertyValue GetMaxMP( CPropertyCharacter* pProperty );

	//// �õ��쳣״̬��������
	//static CPropertyValue GetAbnResist( CProperty* pProperty );

	//// �õ�����״̬����
	//static CPropertyValue GetFireResist( CProperty* pProperty );

	//// �õ�����״̬����
	//static CPropertyValue GetWaterResist( CProperty* pProperty );

	//// �õ�ŭ��״̬����
	//static CPropertyValue GetWindResist( CProperty* pProperty );

	//// �õ�����״̬����
	//static CPropertyValue GetLightResist( CProperty* pProperty );

	//// �õ�����״̬����
	//static CPropertyValue GetEarthResist( CProperty* pProperty );

	//// �õ�����״̬����
	//static CPropertyValue GetShadowResist( CProperty* pProperty );

	// �õ������ƶ��ٶ�
	static CPropertyValue GetWalkSpeed( CPropertyCharacter* pProperty );

	// �õ������ƶ��ٶ�
	static CPropertyValue GetRunSpeed( CPropertyCharacter* pProperty );

	// �õ��ƶ��ٶ�
	static CPropertyValue GetRunSpeed( int vEntityType, int vValueID );

	static CPropertyValue GetSkillLess( CPropertyCharacter* pProperty, int vSkillGenerID );

	// ����������
	static float GetHitrate( int vSrcLevel, int vDesLevel, int vHitValue );

	// ����������
	static float GetDuckRate( int vSrcLevel, int vDuckValue, int vIgnoreValue );

	// ���㱩����
	static float GetDeathRate( int vDesLevel, int vDeathRate, int vDeathDefense );
};



