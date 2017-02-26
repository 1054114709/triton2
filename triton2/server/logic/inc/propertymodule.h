#pragma once
#include "template.h"
#include "pro_define.h"
#include "logservertype.h"	  
#include "servercore.h"
#include "servertool.h"
#include "lk_hashmap.h"
#include "stallmessage_pb.hxx.pb.h"
#include "mapmodule.h"

class CFuncResult;
class CObj;
class CEntity;
class CEntityPlayer;
class CEntityCharacter;
class CEntityPet;
class CProperty;
class CPropertyCharacter;
class CPropertyPlayer;
class TiXmlDocument;

class CSpecialRelive
{
public:
	int			mMapID;	
	int			mLineID;	
	int			mX;
	int			mY;
};

class CRelivePosition : public CObj
{
public:
	CRelivePosition()
	{
		if (CObj::msCreateMode)
		{
			Initialize();
		}
		else
		{
			Resume();
		}
	}
	virtual ~CRelivePosition() {}

	// ��ʼ��
	virtual int Initialize()
	{
		mPosition.Clear();
		mReliveMapID = 0;
		mLineID = 0;
		mMapID = 0;
		mSpecial = 0;
		memset( mCampPos, 0, sizeof(mCampPos) );
		return 0;
	}

	// �ָ�
	virtual int Resume() {return 0;}

public:
	CWTPoint	mPosition;		// ���������
	int			mReliveMapID;	// �����ͼ, 0��ʾ��ǰ��ͼ
	int			mLineID;
	int			mMapID;			// ��ͼID
	int			mSpecial;
	CSpecialRelive  mCampPos[ WORLD_NUM ];		// ����Ӫ�����

public:
	CSpecialRelive *GetPosByNation( int vWorldID )
	{
		if ( vWorldID >= WORLD_FIRST && vWorldID < WORLD_NUM )
		{
			return &mCampPos[ vWorldID ];
		}
		return NULL;
	}

	void AddSpecialRelive( int vWorldID, int vLineID, int vMapID, int vX, int vY )
	{
		if ( vWorldID >= WORLD_FIRST && vWorldID < WORLD_NUM )
		{
			mCampPos[ vWorldID ].mLineID = vLineID;
			mCampPos[ vWorldID ].mMapID = vMapID;
			mCampPos[ vWorldID ].mX = vX;
			mCampPos[ vWorldID ].mY = vY;
			mSpecial ++;
		}
	}
};
enum ETimer
{
	STATE_INTERVAL		= 200,		// ״̬�仯ʱ����
	REFRESH_INTERVAL	= 3000,		// �ָ�ʱ����
};


class CDropFrom
{
public:
	enum 
	{
		em_drop_from_item,
		em_drop_from_npc,
	}emDropFrom;

	union 
	{
		CEntity* pEntity;
		CItemObject* pItemObject;
	} mFrom;

	CDropFrom(CEntity* pEntity)
	{
		emDropFrom = em_drop_from_npc;
		mFrom.pEntity = pEntity;
	}

	CDropFrom(CItemObject* pItemObject)
	{
		emDropFrom = em_drop_from_item;
		mFrom.pItemObject = pItemObject;
	}
};

enum EExchangeFlag
{
	em_exchange_by_stall,
	em_exchange_by_trade,
	em_exchange_by_stall_yb,
};

// �ڵ���Ʒ
class CRedstoneController : public CObj
{
private:
	int mEntityID;				// �ڵ���������ʵ��ID
	int mOnwerID;				// �ڵ���ӵ����ID�������ڵ�������ȷ��
	int mRedStoneTmpID;			// �ڵ���ģ��ID
	bool mDestroyEntity;		// �ڵ���������ʱ�Ƿ������ڵ���������ʵ��
	int	mLastNumber;			// �ϴη��侭��ʱ������
public:
	// ����&��ȡ�ڵ���������ʵ��ID
	void SetEntityID( int nEntityID ){ mEntityID = nEntityID; }
	int GetEntityID( ){ return mEntityID; }
	
	// ����&��ȡ�ڵ���ӵ����ID
	void SetOwnerID( int nOnwerID ){ mOnwerID = nOnwerID; }
	int	GetOwnerID( ){ return mOnwerID; }
	
	// ����&��ȡ�ڵ���ģ��ID
	void SetRedstoneTmpID( int nRedstoneTmpID ){  mRedStoneTmpID = nRedstoneTmpID; }
	int	 GetRedstoneTmpID(){ return mRedStoneTmpID; }
	
	// ����&��ȡ�Ƿ������ڵ�ʵ��
	void SetDestroyEntity( bool bDestroyEntity ){ mDestroyEntity = bDestroyEntity; }	
	bool GetDestroyEntity(){ return mDestroyEntity; }
	
	// ����&��ȡ�ϴη��侭��ʱ������
	void SetLastNumber( int nNumber ){ mLastNumber = nNumber; }
	int GetLastNumber(){ return mLastNumber; }
public:
	CRedstoneController()
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
	~CRedstoneController( ){ }	
public:
	int Initialize()
	{	
		mEntityID = 0;
		mOnwerID = 0;
		mRedStoneTmpID = 0;
		mDestroyEntity = false;
		mLastNumber = 0;
		return SUCCESS;
	}
	int Resume()
	{
		return SUCCESS;
	}	
};



class CPropertyModule : public CLogicModule, public CSingleton< CPropertyModule >
{
public:
	static char	sModuleName[ NAME_LENGTH ];
	CWTimer								mRecTimer;			// �ָ���ʱ��
	CWTimer								mStateTimer;		// ״̬��ʱ��
	CWTimer								mAureoleTimer;		// aureole timer
	CWTimer								mDaliyRefreshTimer;	// ÿ��ˢ�¼�ʱ��
	CWTimer								mPkTimer;			// ����pkˢ�¼�ʱ��
	unsigned int						mLastWeeklyTimer;	// ����ÿ�������ʱ��
	unsigned int						mLastDaylyTimer;	// ����ÿ�������ʱ��

	typedef lk::hash_map< int, int, 200 >	RelivePositionMap; // ����ͼ������

	RelivePositionMap					mRelivePosition;	// ����ͼ������
	int									mBorderMapID;		// �߾������ͼ
	int									mBorderPosX;		// �߾������X
	int									mBorderPosY;		// �߾������Y

	CClientControlData					mClientCtrlData;	// ���ƿͻ���ģ�������

public:
	

public:
	CPropertyModule( );
	~CPropertyModule( );

	static unsigned int CountSize();				    

public:
	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );

	// ��һ�쵽��
	void OnNewDayCome( );

	// ��һ�ܵ���
	void OnNewWeekCome( );
	
	// ��������
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName );

	// ·����Ϣ
	virtual void OnRouterMessage( CMessage* pMessage );

	// �ͻ��˷�����Ϣ
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �ڲ���ʱ��Ϣ
	virtual void OnTimeoutMessage( CMessage* pMessage );

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst );

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );

	// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer , int vSaveCode );

	// ��������
	virtual void OnLoadConfig( );

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }

public:

	int SaveItemInfo( CEntityPlayer* pPlayer, int* apPkgIdx, int nIdxNum, int nSaveCode );

	// ʵ���Ƿ�ͬһ�����ҵ�ʵ��
	bool EntityIsNative( CEntity* pSrcEntity, CEntity* pDesEntity );

	// ʵ���Ƿ�ͬһ��ͬ�˹��ҵ�ʵ��
	bool EntityIsAlly(	CEntity* pSrcEntity, CEntity* pDesEntity );

	// �ͷż���
	void FireSkill(	CEntityCharacter* pSrcEntity, 
					CEntityCharacter* pDesEntity, 
					CTemplateSkill* pSkill, 
					CEntityCharacter** vEntityList,
					int vEntityListNum,
					bool bIsMagicWeapon = false // �Ƿ񷨱�����
				);
	
	// PKģʽ�ж�
	bool EntityPKValid(	CEntity* pSrcEntity, 				
						CEntity* pDesEntity, 
						CTemplateSkill* pNormalSkill, 
						bool vIsSkill = true
					);

	// ʵ��ɾ�����и���BUFF
	void EntityRemoveDebuff( CEntityCharacter* pEntity );
	
	// ���BUFF
	void EntityClearbuff( CEntityCharacter* pEntity, int vNum, int vBuffType );

	// ʵ���ܵ��˺�
	void EntityDamaged( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, int vDamage, EResultType vResultType, int vSkillType = 0 );

	// ��������Ч�����˺�����������Ŀ��
	void EntityAttackSkill( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateNormalSkill* pNormalSkill, int vSkillType, int vDamageRate = SERVER_PERCENT_INT );

	// ����BUFFЧ��������Ŀ��
	void EntityBuffSkill( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, int* pBuffList, int nBuffNum, int vDamage, int vSkillType = 0 );

	// �ͷż���ʱ,�ж������Ƿ�����
	bool SkillWeaponValid( CPropertyPlayer* pSrcProperty, CTemplateSkill* pSkill );

	// ��������������Ե�
	void ResetAllPP( CEntityPlayer* pEntity );

	// ����������м��ܵ�
	void ResetAllSP( CEntityPlayer* pEntity );

	// ������������컯��
	int ResetAllTalent( CEntityPlayer* pEntity, int vStep );

	// �������һ�㼼�ܵ�
	void ResetSingleSP( CEntityPlayer* pEntity, unsigned short vGenerID, unsigned char vCol, unsigned char vRow );

	// ������ü��ܵ�
	int ClickSP( CEntityPlayer* pEntity, unsigned short vGenerID, unsigned char vCol, unsigned char vRow, unsigned int& vSkillID, int& vIndex, int& vMoney, int& vBindMoney );

	// ��һ����Ϊֵ
	void PlayerObtainTalentExp( CEntityPlayer* pEntity, int vExp );

	// ��ҵ���컯��
	int PlayerClickTalentPoint( CEntityPlayer* pEntity, int vRow, int vCol );

	// ����컯����
	int PlayerIncreaseTalent( CEntityPlayer* pEntity, int vStep );

	// ��һ��ĳ��Ż�ֵ
	int PlayerObtainWizardValue( CEntityPlayer* pEntity, int vType, int vValue );

	// ����ù�ѫ�һ��Ż�ֵ
	void PlayerChangeHonorToWizard( CEntityPlayer* pPlayer, int vHonor, int vType );
 
	// ��һ�þ���
	// �¼Ӳ���vReason, �������Դ�ֻ�������, ��Ϊ��ֵľ�����Ҫ���������,����Ĳ���
	// vReason = 0 ���, 1 ����	 ( �鿴ö�� EExpReason)
	int PlayerObtainExp( CEntityPlayer* pEntity, int vExp, int vReason = EXPREASON_TASK, int* pMemberList = NULL, int vMemberCount = 1, int vLevel = 0, CEntity* pNPCEntity = NULL );

	// ��һ�ý�Ǯ
	void PlayerObtainMoney( CEntityPlayer* pEntity, int vInitMoney, int vDeltaMoney, int* pMemberList, int vMemberCount, int vLevel );

	// ��õ���ʱ����ϵͳ����
	void OnTaskObtainItem( CEntityPlayer* pEntity, unsigned int vItemID, unsigned short vNumber );

	// ʧȥ����ʱ����ϵͳ����
	void OnTaskRemoveItem( CEntityPlayer* pPlayer, unsigned int vItemID, unsigned short vNumber );

	// ��һ��һ���Ѿ����ڵĵ���, ���ش˵���
	CItemObject* PlayerInsertItem( CEntityPlayer* pEntity, CItemObject* pItem , bool vIsFromTask = false, bool bBind = false );

	// ��һ�õ���
	// ���ذ����д˵��ߣ�����Ƕѵ���Ʒ���������һ�ѵ�����
	CItemObject* PlayerInsertItem( CEntityPlayer* pEntity, 
			unsigned int vItemID, unsigned int vNumber, bool vIsFromTask = false, int nLevel = 0, const char* szMadeByName = NULL, bool bBind = false, int nInvalidTime=0);

	// ������Ʒ
	int CreateItem(CTplItem* tpItem,  uint32_t vNumber, int  vLevel, CItemObject** tpItemObj);

	// ���Ի���Ʒ
	int PersonalizeItem(CEntityPlayer* pEntity, CTplItem* tpItem , CItemObject* pItemObj, const char* szMadeByName);

	// �����Ʒ��Ĵ���
	void  AfterInsertedItem(CEntityPlayer* pEntity, CTplItem* pTplItem, CItemObject* tpItemObj, bool bIsCalledFromTask);

	// ���ʧȥ����
	int PlayerRemoveItem( CEntityPlayer* pPlayer, 
			unsigned int vItemIndex, int vItemNumber, uint64_t *pullGUID = NULL, bool vIsTask = false ); 

	// ���ʧȥ����
	int PlayerRemoveItemByID( CEntityPlayer* pPlayer, 
			unsigned int vItemID, unsigned int vItemNumber, bool &vBind, uint64_t *pullGUID = NULL, int vType = BIND_ALL );

	// ����޸�ְҵ
	void PlayerChangeMetier( CEntityPlayer* pEntity, unsigned short vMetierID );

	// ����ƶ�����
	void MoveItem( CEntityPlayer* pEntity, unsigned short vSrcIndex, unsigned char vSrcSlot, unsigned short vDesIndex, unsigned char vDesSlot, unsigned short vNumber );

	// ���װ������
	void EquipItem( CEntityPlayer* pEntity, unsigned int vSrcIndex, unsigned int vDesIndex = ~0 );

	// ���ж�µ���
	void UnEquipItem( CEntityPlayer* pEntity, unsigned short vPart, unsigned int& vIndex, bool bDestroy=false );

	// ʵ��ʹ�ü���(����ֶΣ��Ƿ񷨱�)
	bool UseSkill( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, unsigned short vSkillID, unsigned short vSkillLevel, int vListID, unsigned int vIndex, CEntityCharacter** vEntityList, int vEntityListNum, bool bIsMagicWeapon = false, bool bUseByItem = false );

	int CloseAureole( CEntityCharacter* pSrcEntity );

	int UseAureoleSkill( CEntityCharacter* pSrcEntity, CTemplateAureoleSkill* pAureoleSkill, CEntityCharacter** vEntityList, int vEntityListNum );

	void AddResultToPB( PBFuncResult* vPBResult, CFuncResult* vResult );

	int ResultListSend( ); 

	// ���ʹ�õ���
	void UseItem( CEntityPlayer* pEntity, int vPos, unsigned short vIndex, unsigned int vParam );
	void UseTaskItem( CEntityPlayer* pEntity, unsigned short vIndex );

	// �õ����԰ٷֱ�
	void GetPropertyPercent( CEntityCharacter* pEntity, int& vHPPercent, int& vMPPercent, int& vCurAP, int& vLevel );

	// NPC��ͨ����
	void OnNpcNormalAttack( CEntityNpc* pSrcNpc, CEntityCharacter* pTarget );

	// NPCʹ�ü���
	void OnNpcUseSkill( CEntityNpc* pSrcNpc, CEntityCharacter* pTarget, unsigned int vSkillID, unsigned int vSkillLevel );

	// ��齻������
	int CheckChange( CEntityPlayer* tpSrcEntity, CEntityPlayer* tpDesEntity, int tSrcNumber, int tDesNumber, int tSrcMoney, int tDesMoney );

	// �����������
	int ExchangeBaggage( CEntityPlayer* tpSrcEntity, CEntityPlayer* tpDesEntity, int tSrcNumber, short* tpSrcItemList, int tDesNumber, short* tpDesItemList, int tSrcMoney, int tDesMoney, EExchangeFlag emExchange );

	// �����ҽ�Ǯ
	unsigned int GetPlayerMoney( unsigned int vEntityID );

	// ������ҽ�Ǯ
	int SetPlayerMoney( unsigned int vEntityID, int vMoney );

	// �õ������ַ�����
	void GetItemString( unsigned int tEntityID, int tBaggageIndex, int tItemNumber, char* tpItemBuffer, int& vLockType, int& vBufferSize );

	int GetItemBinary( unsigned int tEntityID, int tBaggageIndex, int tItemNumber, PBItemObject* tpItemObject, int& vLockType, bool bIsCheck );

	// �õ�����������
	unsigned int GetBaggageRelease( CEntity* tpSrcEntity );

	// ��ʵ�屻�������ʱ����
	//void OnEntityTrap( CEntityCharacter* tpDesEntity, unsigned int tSrcEntityID, unsigned int tSkillID, unsigned int tSkillLevel, int tEntityNumber, CEntityCharacter** tpEntityList, bool& tIsOK );

	// ����������
	void LockBaggage( unsigned int vEntityID, int vBaggageIndex, int vLockType, bool& tIsOK );

	//// �ʼ�ϵͳɾ����ҵ���
	//void MailEraseItem( CEntity* tpPlayer, int tItemNumber, unsigned short* tpItemIndex, int tMoney, int& tBackType );

	//// �ʼ�ϵͳ�����ҵ���
	//void MailAppendItem( CEntity* tpPlayer, char* tpItemBuffer, int tMoney, int& tBackType );

	// ���õ�һ��
	void ResetFirstEntity( unsigned int vEntityID );

	// ���ٷֱȻظ�
	void RecoverPer( CEntity* tpDesEntity, int tPer );

	// ���������������
	
	// �õ����BUFF	��Ϣ
	CBuffList* GetBuffInfo( unsigned int vEntityID );

	void PlayerCloseDialog2( CEntityPlayer* pPlayer );

	void PlayerChangeMetier2( CEntityPlayer* pPlayer, unsigned int nDesMetier );

	int PlayerObtainExp2( CEntityPlayer* pEntity, int vExp, int vListID, int vReason,int* pMemberList, int vMemberCount );
	// �ж�����Ƿ���������NPC�Ի�״̬

	bool PlayerInBusy( unsigned int vEntityID );

     // ��ѯ����
	int HasItem( unsigned int vEntityID, unsigned int vItemID, unsigned int vNumber, int& tBackType, int IfCountLockItem = 1, int vType = BIND_ALL );

	// ��ѯָ���������Ƿ���ָ�������ĵ���
	bool HasItemOnIndex( unsigned int unEntityID, int nIndex, unsigned int unItemID, unsigned int unNumber, int nType = BIND_ALL );

	// ����ָ�������ϵĵ��߸���
	int GetItemNumOnIndex( unsigned int unEntityID, unsigned int unItemID, int nIndex, int nType = BIND_ALL );

	 // �����ض����ӵĵ���
	void ConsumeItemByIndex( unsigned int vEntityId, unsigned int vItemId, int vItemNum, int vItemIndex, int& tBackType );

	// ����˺��б�
	void RemoveDamage( unsigned int tSrcEntityID, unsigned int tDesEntityID );
	
	// ����Ҽ�������ʱ��,�Ѷ����е�����������ʾ
	void DisplayTripPlayerAddTeam( CEntityPlayer* pSrcEntity, CEntityPlayer** pTeamMemberList, int vTeamNum );

	// ������뿪�����ʱ��,�Ѷ����е�����������Ұ����ʧ
	void DisappearTripPlayerLeaveTeam( CEntityPlayer* pSrcEntity, CEntityPlayer** pTeamMemberList, int vTeamNum );

	// �������ɢ��ʱ��,�Ѷ����Ա�и��������������Ա����Ұ����ʧ
	void DisappearTripTeamDisband( CEntityPlayer** pTeamMemberList, int vTeamNum );

public:
	// ����һ�ι������߱�������������װ�����;ö�
	void EquipmentDurability( CEntity *pEntity, int  IsAttacker , int EntityType );
	
	// װ���Ƿ���
    bool EquipmentAvailable( CEntity* pSrcEntity  ,int EptPart ) ;	

	// ����ʱ�������ȫ��װ�����;ö�
    void ChangeDurabilityOnDeath( CEntity* pEntity  ); 
    
	// �������װ��
	void OnMessageMendEquipment( CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��������װ��
	bool MendAllEquipment( CEntityPlayer *pPlayer);

	// ������װ��  
	void MendSigleEquipment( CEntityPlayer *pPlayer,int IsInPackage, int Index);
public:
	// �۳��ʼ���Ʒ
	void RemoveMailItem( CEntityPlayer * tpPlayer, int PackageIndex, int ItemNum  );
public:	

	//// ��òֿ�����ĵ�����Ϣ�����ڿͻ������
	//void GetStorageInfo( CEntityPlayer *pPlayer );

public:
	// ʵ�������߼�
	void EntityRelive( CEntity* pEntity );

	// ��Ҹ����߼�
	void PlayerRelive( CEntityPlayer* pPlayer, ERelive vReliveType, int vHPPer, int vMPPer );

	// ����޸Ŀ����
	void PlayerSetShortcut( CEntityPlayer* pPlayer, unsigned int vShortcut, unsigned int vType, unsigned int vIndex, unsigned int vLabelType, unsigned int vLabelIndex, int nParam1 );

	// ��һ�ý�Ǯ
	int PlayerChangeMoney( CEntityPlayer* pPlayer, int vMoney, bool vPayout, bool vIsBind );

	// ��һ��Ԫ��
	bool PlayerChangeYuanbao(CEntityPlayer* pPlayer, int nAmount, bool vIsBind);

	// ��Ҷ������
	//void PlayerThrowMoney( CEntityPlayer* pPlayer, int vMoney );	

	// ��Ҷ�������
	void PlayerThrowItem( CEntityPlayer* pPlayer, int vItemIndex, int vNumber  );

	// ������ٵ���
	void PlayerDestroyItem( CEntityPlayer* pPlayer, int vItemIndex, int vNumber  );

	// ��Ҷ����ֿ����
	void PlayerThrowStorItem( CEntityPlayer* pPlayer, int vItemIndex, int vNumber , bool bForce=false );
	
	// ��ҳ��۵���
	void PlayerSellItem( CEntityPlayer* pPlayer, int vEntityID, int vItemIndex, int vNumber );

	// ��ҹ������
	void PlayerPurchase( CEntityPlayer* pPlayer, int vEntityID, int vPageIndex, int vItemIndex, int vNumber, int nNpcID );

	// �������װ��
	void PlayerProduceEquip( CEntityPlayer* pPlayer, unsigned short vType1, unsigned short vType2, unsigned short vType3, unsigned short vLevel, unsigned short vRank, int vType );
	
	// �����������
	void PlayerUpItem( CEntityPlayer* pPlayer, int vIndex1, int vIndex2, int *vIndex3, int vType, int nNpcEntityID );

	// �����Ƕ����
	void PlayerInsertRune( CEntityPlayer* pPlayer, int vIndex1, int vIndex2 );

	// �����Ƕ��ʯ
	void PlayerInsertJewel( CEntityPlayer* pPlayer, int vIndex0, int *vIndex );

	// ��Ҵ�װ�����
	void PlayerOpenSlot( CEntityPlayer* pPlayer, int vIndex1, int vIndex2 );

	// Ԫ�����װ��
	void PlayerEatEquip( CEntityPlayer* pPlayer, int vIndex0, int *vIndex );

	// ��Ʒ�ϳ�
	void PlayerComposeItem( CEntityPlayer* pPlayer, int vIndex );

	// ��ҵ���̵����
	int PlayerClickShop( CEntityPlayer* pPlayer, unsigned int vEntityID );

	// ��ҵ���ʼ�����
	int PlayerClickMail( CEntityPlayer* pPlayer, unsigned int vEntityID );

	// ��ҵ����������
	int PlayerClickUpg( CEntityPlayer* pPlayer,unsigned  int vEntityID );

	// ��ҵ�����ͷ���
	int PlayerClickTele( CEntityPlayer* pPlayer, unsigned int vEntityID );

	// ��ҵ���ֿ����
	int PlayerClickStorage( CEntityPlayer* pPlayer, unsigned int vEntityID );

	// ��ҵ���سǷ���
	int PlayerClickTown( CEntityPlayer* pPlayer, unsigned int vEntityID );
	
	// ��ҵ�װ���󶨷���
	int PlayerClickBind( CEntityPlayer* pPlayer, unsigned int vEntityID );
	
	// ��ҵ��ÿ�ո�������
	int PlayerClickWelfare( CEntityPlayer* pPlayer, unsigned int vEntityID );

	// ��ҵ��ת������
	int PlayerClickChange( CEntityPlayer* pPlayer, unsigned int vEntityID );

	// ��ҵ����������
	int PlayerClickJudge( CEntityPlayer* pPlayer, unsigned int vEntityID );

	// ��ҵ���һ�����
	int PlayerClickExchange( CEntityPlayer* pPlayer, unsigned int vEntityID );

	// ��ҵ����ѫ����
	int PlayerClickHonor( CEntityPlayer* pPlayer, unsigned int vEntityID );

	// ��ҹرնԻ���
	void PlayerCloseDialog( CEntityPlayer* pPlayer );

	// ��ҵ������NPC
	void PlayerClickNpc( CEntityPlayer* pPlayer, int vEntityID );

	void PlayerClickStoreBox( CEntityPlayer* vpPlayer, CEntityBox* vpBox );

	// ���ʰȡ����
	void PlayerPickItem( CEntityPlayer* pPlayer, int vEntityID );

	// ��ҹر��ض��Ľ���
	void PlayerCloseWindow( CEntityPlayer* pPlayer, int vType );
public:
	// ��װ��
	int  BindItem(  CEntityPlayer *tpPlayer, CItemObject *tpItemObj , int BindWay ,  int ItemIndex = -1 );
	
	// ����� 
	int FreeItemBind( CItemObject *tpItemObj, int IfBindOnItem = 0 );

	// ��ȡ��Ʒ��״̬
	int GetItemObjBindStatus( CItemObject *tpItemIbj );

	// ������Ʒ��֪ͨ
	void SendBindNotice( CEntityPlayer * tpPlayer, int BindResult,  int Index , int PackKind , int BindStatus , int BindFreeTime = 0 );

	// ������Ҫȡ������ֶ��󶨵���Ʒ
	void PlayerAddEqtForResumeBind( CEntityPlayer *pPlayer, int EqtIndex );
	
	// ȡ����Ҫȡ������ֶ��󶨵���Ʒ
	void PlayerTakeEqtForResumeBind( CEntityPlayer *pPlayer );
	
	// �ָ��ֶ���
	void PlayerResumeBind( CEntityPlayer *pPlayer, int vItemIndex );	
	
	// �ж���Ʒ�Ľ����ʱ���Ƿ��ѵ�
	int CheckItemBindFreeTime( CItemObject *tpItemObject );		 
			
	// ��Ӱ���Ʒ
	void PlayerInsertBindItem( CEntityPlayer *pPlayer, int ItemIndex );
	
	// ж������Ʒ
	void PlayerTakeBindItem( CEntityPlayer *pPlayer, int ItemIndex );
	
	// ��Ӵ�����󶨵���Ʒ
	void PlayerInsertItemForFree( CEntityPlayer *pPlayer, int ItemIndex );
	
	// ж�´��������Ʒ
	void PlayerTakeItemForFree( CEntityPlayer *pPlayer, int ItemIndex );	 
	
	// �ж���Ʒ�Ƿ��ް�
	int IfItemFree( CItemObject *tpItemObj );
	
	// �ж���Ʒ�Ƿ���ͨ��
	int IfItemBinded( CItemObject *tpItemObj );
	
	// �ж���Ʒ�Ƿ��ֶ���
	int IfItemBindedByItem( CItemObject *tpItemObj ); 	
	
	// �ж���Ʒ�Ƿ����ֶ����״̬
	int IfItemBindFree(  CItemObject *tpItemObj );
	
	// ����ҵ�½��ʱ���������ϴ��ڰ󶨽��״̬����Ʒ�����б���	
	void GetItemForFreeFromPlayer( CEntityPlayer *pPlayer  );
	
	// ����Ҵ���װ���󶨽��״̬����Ʒ�����б���
	void InsertFreeItemIntoList( int ChaiId ,  CItemObject *tpItemObj );

	void PlayerAddSlot( CEntityPlayer *pPlayer, int vIndex1, int vIndex2 );

	void PlayerRemoveJewel( CEntityPlayer *pPlayer, int vIndex1, int vIndex2, int vIndex3 );

	void PlayerJudge( CEntityPlayer *pPlayer, int vIndex1, int vIndex2 );

	void PlayerChangeRes( CEntityPlayer *pPlayer, int vIndex1, int vIndex2 );

	void PlayerJewCom(CEntityPlayer *pPlayer, int *vJewIndex, int vCardIndex);

	void PlayerMultiCom( CEntityPlayer *pPlayer, int vComposeID, int vComposeType, int vEquipIndex = -1 );

	
	void OnMessageListActivityMenu(CEntityPlayer* tpPlayer, CMessage* tpMessage);

	void OnMessageListActivityItem(CEntityPlayer* tpPlayer, CMessage* tpMessage);

	void OnMessageMinusActivityItem(CEntityPlayer* tpPlayer, CMessage* tpMessage);
private:

	// �������
	bool CreatePlayer( CEntityPlayer* pEntity, bool bFirst = false );
	
public:

	// �ٻ�����ʱ�ȼ���������
	void SummonBeastLevelUp( CEntity* vpSrcEntity, unsigned int vTickOffset, bool bBroadCast = true );

	bool CreateMessageEntityRelifeNotice( CMessage* pTotalMessage, CEntity* pEntity, CMessageEntityRelifeNotice* pMessage );
	bool CreateMessageEntityDisappearNotice( CMessage* pTotalMessage, CEntity* pEntity, CMessageEntityDisappearNotice* pMessage );
	bool CreateMessagePlayerReliveNotice( 
		CMessage* pTotalMessage, 
		CMessagePlayerReliveNotice* pMessage, 
		unsigned int vEntityID , 
		unsigned short vPosX, 
		unsigned short vPosY, 
		unsigned int vCurHP, 
		unsigned int vCurMP,
		unsigned int vMaxHP,
		unsigned int vMaxMP
		);

	bool CreateMessageChangeMetierNotice(
		CMessage* pTotalMessage, 
		CMessageChangeMetierNotice* pMessage,
		unsigned int vEntityID,
		unsigned char vMetierID
		);


	bool CreateMessageInsertItemNotice(
		CMessage* pTotalMessage, 
		CMessageInsertItemNotify* pMessage,
		int	vPos,
		int vItemID,
		int *vIndex,
		int *vNumber,
		int vLen,
		int vBind = 0
		);

	bool CreateMessageInsertEquipNotice(
		CMessage* pTotalMessage, 
		CMessageInsertEquipNotify* pMessage,
		CItemObject* pItemObj,
		int	vPos, int nIndex
		);

	bool CreateMessagePlayerChangeEquipNotice(
		CMessage* pTotalMessage, 
		CMessagePlayerChangeEquipNotice* pMessage,
		unsigned int vEntityID,
		unsigned short vPart,
		unsigned int vItemID,
		unsigned int vCurHP,
		unsigned int vCurMP,
		unsigned int vMaxHP,
		unsigned int vMaxMP,
		unsigned int vWeaponLevel,
		unsigned int vChestLevel,
		unsigned int vWeaponJewel,
		unsigned int vChestJewel,
		unsigned int vMWID,
		unsigned int vFashionID,
		unsigned int vMarriageEquipID,
		unsigned int vMWQLID
		);

	bool CreateMessageEntityRefreshNotice(
		CMessage* pTotalMessage, 
		CMessageEntityRefreshNotice* pMessage,
		unsigned int vEntityID,
		unsigned int vCurHP,
		unsigned int vCurMP,
		unsigned int vMaxHP,
		unsigned int vMaxMP
		);


	bool CreateMessageNotifyDirectionCallBack(
		CMessage* pTotalMessage, 
		CMessageNotifyDirectionCallBack* pMessage,
		unsigned int vEntityID,
		int vDirection
		);

	bool CreateMessageNotifyPetLevelUp(
		CMessage* pTotalMessage, 
		CMessagePetLevelUpNotice* pMessage,
		unsigned int vEntityID,
		int vLevel
		);

 
	/************************************************************************/
	/*      ������Ϣ�ĺ���                                                  */
	/************************************************************************/
	// ��������Ӳֿ���Ʒ������Ϣ
	void OnMessageThrowStorItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �������ʹ�ü���������Ϣ
	void OnMessageUseSkillRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ���������ͨ����������Ϣ
	//void OnMessageNormalAttackRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �������ʰȡ����������Ϣ
	void OnMessagePickItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������ҵ��npc������Ϣ
	void OnMseeageClickNpcRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������ҹ�����Ʒ������Ϣ
	void OnMessagePurchaseItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �����������Ʒ������Ϣ
	void OnMessageSellItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �����������Ʒ������Ϣ
	void OnMessageThrowItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ��������ӽ�Ǯ������Ϣ
	//void OnMessageThrowMoneyRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ����������ÿ����������Ϣ
	void OnMessageSetShortcutRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ������Ҹ���������Ϣ
	void OnMessagePlayerReliveRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ��������ƶ�����������Ϣ
	void OnMessageMoveItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �������ָ����Ϣ ��Σ��:��debug�汾�����δ˹��ܡ�
	void OnMessageProDebugNotice( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �������װ������������Ϣ
	void OnMessageEquipItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �������ж��װ��������Ϣ
	void OnMessageUnEquipItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ������ҵ�����ܵ�������Ϣ
	void OnMessageClickSkillPointRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �����������һ������������Ϣ
	void OnMessageResetSPPRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �����������һ������������Ϣ
	void OnMessageResetSSPRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �������ʹ�õ���������Ϣ
	void OnMessageUseItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �����������װ��������Ϣ
	void OnMessageProduceEquipRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ����������������Ʒ������Ϣ
	void OnMessageUpgAddItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �������ȡ��������Ʒ������Ϣ
	void OnMessageUpgDelItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �����������װ��������Ϣ
	void OnMessageUpgEquipRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �����������ҩƷ������Ϣ
	void OnMessageProducePhysRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ������ҷ������������Ϣ
	void OnMessagePushRuneRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	//���� ��� ����ת��������Ϣ
	void OnMessageChangeRuneRequest ( CEntityPlayer * pPlayer,CMessage *pMessage);
	//���� ��� ������������Ϣ
	void OnMessageRuneComRequest( CEntityPlayer* pPlayer,CMessage* pMessage);

	// �������ȥ������������Ϣ
	void OnMessagePopRuneRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ������Ҳ������������Ϣ
	void OnMessageInsertRuneRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������Ҳ�����Ƕ��ʯ������Ϣ
	void OnMessageInsertPushJewelRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �������ȡ����Ƕ��ʯ������Ϣ
	void OnMessageInsertPopJewelRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ���������Ƕ��ʯ������Ϣ
	void OnMessageInsertJewelRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������ҷ��뱻��װ��������Ϣ
	void OnMessageEatPushEquipRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �������ȡ������װ��������Ϣ
	void OnMessageEatPopEquipRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ������ҳ�װ��������Ϣ
	void OnMessageEatEquipRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������ҷ���ϳ�װ��������Ϣ
	void OnMessageComposePushRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �������ȡ���ϳ�װ��������Ϣ
	void OnMessageComposePopRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ������ҷ��뿪����Ʒ������Ϣ
	void OnMessageOpenPushRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �������ȡ��������Ʒ������Ϣ
	void OnMessageOpenPopRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ������Ҵ���������Ϣ
	void OnMessagePlayerTeleRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �������ָ����Ϣ ��Σ��:��debug�汾�����δ˹��ܡ� 
	void OnMessageProDebugCommand( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// �������֪ͨ������Ϣ
	void OnMessageNotifyDirection( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ������Ҹı����ģʽ������Ϣ
	void OnMessageChangePetModeRequest( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ������һ�ûع���Ʒ����Ϣ
	void OnMessageObtainSaleItemString( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ������һع���Ʒ������Ϣ
	void OnMessageBuyBackItem( CEntityPlayer* pPlayer, CMessage* pMessage  );

	// ��������ƶ��ֿ���Ʒ������Ϣ
 /*   void OnMessageMoveStorageItem( CEntityPlayer* pPlayer, CMessage* pMessage );*/

	// ������Ұ���Ʒ����
	void OnMessageBindItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage );	

	// ���������Ӱ���Ʒ����
	void OnMessageAddItemRequest( CEntityPlayer * pPlayer, CMessage* pMessage );

	// �������ж�°���Ʒ����
	void OnMessageTakeItemRequest( CEntityPlayer *pPlayer, CMessage* PMessage );     

	// ���������Ӵ������Ʒ
	void OnMessageAddItemForFreeRequest(  CEntityPlayer *pPlayer, CMessage* PMessage  );    

	// �������ж�´��������Ʒ 
	void OnMessageTakeItemForFreeRequet(  CEntityPlayer *pPlayer, CMessage* PMessage  ); 

	//  ������ҽ���ֶ��󶨵�����
	void OnMessageFreeItem(  CEntityPlayer *pPlayer, CMessage* PMessage  ) ;

	// �������ѧϰ����������Ϣ
	void OnMessageStudySkillRequest( CEntityPlayer* pPlayer, CMessage* pMessage );		

	// ������Ҽ����Ե�
	void OnMessageAddPropertyPointRequest( CEntityPlayer* pPlayer, CMessage* pMessage );	

	// ����������ûسǵ�������Ϣ
	void OnMessageSetTownRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������Ҹı�pkģʽ������Ϣ
	void OnMessageChangePKModeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������Ҳ鿴������Ϣ����
	void OnMessageLookPropertyRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������ҿ���鿴�������������Ϣ����
	void OnMessageLookPropertyRouterRequest( CMessage* pMessage );

	// �������ػ�Ӧ�Ĳ鿴�������������Ϣ
	void OnMessageLookPropertyRouterResponse( CMessage* pMessage );

	// ��������ռ�������Ʒ������Ϣ
	void OnMessageTaskCollectRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������Ҹı����װ��������Ϣ
	void OnMessageChangeHelpStatus( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ���������˫����
	void OnMessageObtainDiploidRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������Ҷ���˫��ʱ��(�ⶳ)
	void OnMessageFreezeDiploidRequest( CEntityPlayer* pPlayer, CMessage* pMessage );	

	// ������Ҳ�ѯʣ�����˫ʱ��
	void OnMessageQueryDiploidTimeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );	
	
	// �������ʹ�ó������ü�������
	void OnMessageUseContinuedSkillRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	//// ������ҵ���󶨷���������Ϣ
	//void OnMessageClickBindServiceRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �����������ֶ���װ��������Ϣ
	void OnMessageAddEqtForResumeBind( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �������ȡ���ֶ���װ��������Ϣ
	void OnMessageTakeEqtForResumeBind( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ��������ֶ���������Ϣ
	void OnMessageResumeBind( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	//// ������ҵ��"�ڵ�"������Ϣ
	void OnMessageClickRedStoneRequest( CEntityPlayer* pPlayer, CMessage* pMessage ); 	

	// �ͻ���֪ͨ�ڵ��������
	void OnMessageRedStoneTimerEnd( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ����ͻ��˴򿪷�����������Ϣ
	void OnMessageOpenServiceRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ͻ����ֶ�ɾ��BUFF������
	void OnMessageActiveRemoveBuffRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ����ͻ����������������
	void OnMessageSetPassWordRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ����ͻ��˼�����������
	void OnMessageCheckPasswordRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
		
	// ����ͻ����޸����������
	void OnMessageModifyPasswordRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ����ͻ�������2������ѡ���֪ͨ
	//void OnMessageSetPasswordOption( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ͻ��˵�����ͷ�����
	void OnMessageClickTeleSymbolRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ����ͻ��˴洢��Ǯ������
	void OnMessageStorMoneyRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ����ͻ���ȡ����Ǯ������
	void OnMessageTakeStorMoneyRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ������Ϣ���ñ���������
	void OnMessageAddKitBagRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ����򿪱�������Ϣ����
	void OnMessageOpenKitBag( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ���±�������Ϣ����
	void OnMessageTakeKitBag( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ����������Ӱ��۷�������
	void OnMessagePushAddSlotRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ����������Ӱ����ó�����
	void OnMessagePopAddSlotRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ����������Ӱ�������
	void OnMessageAddSlotRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// �������ժ����ʯ��������
	void OnMessagePushRemoveJewelRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// �������ժ����ʯ�ó�����
	void OnMessagePopRemoveJewelRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// �������ժ����ʯ����
	void OnMessageRemoveJewelRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Ҽ���װ����������
	void OnMessagePushJudgeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Ҽ���װ���ó�����
	void OnMessagePopJudgeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Ҽ���װ������
	void OnMessageJudgeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// �������ת�����Է�������
	void OnMessagePushChangeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// �������ת�������ó�����
	void OnMessagePopChangeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// �������ת����������
	void OnMessageChangeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Һϳɱ�ʯ��������
	void OnMessagePushJewComRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Һϳɱ�ʯ�ó�����
	void OnMessagePopJewComRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Һϳɱ�ʯ����
	void OnMessageJewComRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Ҹ��Ӻϳɷ�������
	void OnMessagePushMultiComRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Ҹ��Ӻϳ��ó�����
	void OnMessagePopMultiComRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Ҹ��Ӻϳ�����
	void OnMessageMultiComRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������ҷ��뿨Ƭ����
	void OnMessagePushCardRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������ҵ���컯������
	void OnMessageClickTalentPointRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ��������컯��������
	void OnMessageIncreaseTalentRequest( CEntityPlayer* pPlayer, CMessage* pMessage ); 	
	// ���������������ŵ�����
	void OnMessageInitialLifeSkillRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������ҽ�������ܵ�����
	void OnMessageLevelUpLifeSkillRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// �������ѧϰ�¼����䷽������
	void OnMessageStudyComposeRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Ҹ�װ����ħ������
	void OnMessageSetMagicStoneRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������ҷֽ�װ��������
	void OnMessageDecompoundEquipRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ������Ҫ�о��Ĳ���
	void OnMessageAddMaterialRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ȡ���о�����
	void OnMessageTakeMaterialRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ���������
	void OnMessageForgetLifeSkill( CEntityPlayer* pPlayer, CMessage* pMessage );
	// �������ѡ��ƺ�����
	void OnMessageSelectTitleRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �Զ��һ�����
	void OnMessageAutoPlayerGameRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �һ���ҩ����
	void OnMessageBuyPhysicRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// �Ż��ӵ�����
	void OnMessageAddWizardPointRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ��������
	void OnMessageGetTrendRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// Զ������װ�� [3/5/2010 GaoHong]
	void OnMessageRemoteMendAllEquip( CEntityPlayer* npPlayer, CMessage* npMessage );
	
	// ���ô��ֽ�װ����������Ϣ
	void OnMessageAddDecompoundEquipRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	
	// ���´��ֽ�װ����������Ϣ
	void OnMessageTakeDecompoundEquipRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ����װ����������
	void OnMessageChangeEquipProRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// ���������ʯ����
	void OnMessageOpenStoneRequest( CEntityPlayer* pPlayer, CMessage* pMessage );	
	// װ����������
	void OnMessageGetStarRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	// װ����������
	void OnMessageAddStarRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// nBeginTime: ���ʼʱ�䣬nEndTime: �����ʱ��, nRate: ���� 0 ���ر�
	void FireActivityDiploid( CEntityPlayer* pPlayer, int nRate, int nBeginTime = 0, int nEndTime = 0 );

	// nBeginTime: ���ʼʱ�䣬nEndTime: �����ʱ��, nRate: ����
	void FireActivityDiploid( CEntityPlayer* pPlayer, int nRate, bool bAllInScene = false, int nBeginTime = 0, int nEndTime = 0 );

	// �������Ӱ��۷����Ӧ
	void SendPushAddSlotResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// �������Ӱ����ó���Ӧ
	void SendPopAddSlotResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// �������Ӱ��ۻ�Ӧ
	void SendAddSlotResponse( CEntityPlayer* pPlayer, int vResult, int vSlot );
	// ����ժ����ʯ�����Ӧ
	void SendPushRemoveJewelResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// ����ժ����ʯ�ó���Ӧ
	void SendPopRemoveJewelResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// ����ժ����ʯ��Ӧ
	void SendRemoveJewelResponse( CEntityPlayer* pPlayer, int vResult );
	// ���ͼ���װ�������Ӧ
	void SendPushJudgeResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// ���ͼ���װ���ó���Ӧ
	void SendPopJudgeResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// ���ͼ���װ����Ӧ
	void SendJudgeResponse( CEntityPlayer* pPlayer, int vResult, int vProperty1, int vProperty2, int vProperty3 );
	// ����ת�����Է����Ӧ
	void SendPushChangeResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// ����ת�������ó���Ӧ
	void SendPopChangeResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// ����ת�����Ի�Ӧ
	void SendChangeResponse( CEntityPlayer* pPlayer, int vResult, int vType );
	// ���ͺϳɱ�ʯ�����Ӧ
	void SendPushJewComResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// ���ͺϳɱ�ʯ�ó���Ӧ
	void SendPopJewComResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// ���ͺϳɱ�ʯ��Ӧ
	void SendJewComResponse( CEntityPlayer* pPlayer, int vResult );
	// ���͸��Ӻϳɷ����Ӧ
	void SendPushMultiComResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// ���͸��Ӻϳ��ó���Ӧ
	void SendPopMultiComResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	// ���͸��Ӻϳɻ�Ӧ
	void SendMultiComResponse( CEntityPlayer* pPlayer, int vComposeID, int vResult, int nIndex = -1 );
	// ���ͷ��뿨Ƭ��Ӧ
	void SendPushCardResponse( CEntityPlayer* pPlayer, int vResult, int vItemID );
	// ���ͻ����Ϊֵ֪ͨ
	void SendTalentChangeNotify( CEntityPlayer* pPlayer, int vTalentExp, int vTalentPoint, int vTalentChange, int vTalentLevel );
	// ���͵���컯���Ӧ
	void SendClickTalentPointResponse( CEntityPlayer* pPlayer, int vResult, int vRow, int vCol, int vTalentExp, int vTalentPoint, int vTalentStep );
	// �����컯���׻�Ӧ
	void SendIncreaseTalentResponse( CEntityPlayer* pPlayer, int vResult, int vTalentExp, int vTalentPoint, int vTalentStep );	
	// ���ͳ�ʼ������ܵĻ�Ӧ
	void SendResponseInitializeLifeSkill( CEntityPlayer *pPlayer, int nErrcode, int nLifeSkillType, int nLifeSkillKind, int nDegreeValue, int nSkillLevel );			
	// ��������ܽ��׵Ļ�Ӧ��Ϣ
	void SendResponseLevelUPLifeSkill( CEntityPlayer *pPlayer, int nErrcode, int nLifeSkillType, int nSpecializeDegree, int nLifeSkillLevel );	
	// ����ѧϰ�¼����䷽�Ļ�Ӧ��Ϣ
	void SendResponseStudyCompose( CEntityPlayer *pPlayer, int nErrcode, int nSpecializeDegree, int nComposeID, int nLifeSkillType, int nStudyWay );	
	// ���͸�ħ�Ļ�Ӧ��Ϣ
	void SendResponseSetMagicStone( CEntityPlayer *pPlayer, int nErrcode, int nEquipIndex, int nAttribute, int nStoneID,  int nMagicNum = 0, int nSlotType = SLOT_BAGGAGE );
	// ����װ���ֽ�Ļ�Ӧ��Ϣ
	void SendResponseDecompoundEquip( CEntityPlayer *pPlayer, int nErrcode, int nEquipIndex );
	// ���ͷ��ò��ϵ���Ϣ��Ӧ
	void SendResponseAddMaterial( CEntityPlayer *pPlayer, int nErrcode, int nBagIndex, int nPosIndex );
	// ȡ���о�����
	void SendResponseTakeMaterial( CEntityPlayer* pPlayer, int nErrcode, int nPosIndex );
	// ������������Ըı��֪ͨ
	void SendNotifyLifeSkillAttribute( CEntityPlayer* pPlayer, int nLifeSkillType, int nSpecializeDegree );
	// ������������ܵ���Ϣ��Ӧ
	void SendResponseForgetLifeSkill( CEntityPlayer *pPlayer, int nErrcode, int nLifeSkillType );
	
	// ���ͷ��ô��ֽ�װ���Ļ�Ӧ��Ϣ
	void SendResponseAddDecompoundEquipRequest( CEntityPlayer *pPlayer, int nErrcode, int nEquipIndex );
	
	// ����ȡ�´��ֽ�װ���Ļ�Ӧ��Ϣ
	void SendResponseTakerDecompoundEquipResponse( CEntityPlayer *pPlayer, int nErrcode, int nEquipIndex );
	// �����������
	void SendGetTrendResponse( CEntityPlayer *pPlayer, int vResult, int vTrend );

	// �����ϼ�������
	void OnMessageInterruptSkill( CEntityPlayer* pPlayer, CMessage* pMessage );

	// time out message
	void OnTimeoutMessageSkillCoolDown( CMessage* pMsg );
	void OnTimeoutMessageEntityDisappear( CMessage* pMsg );
	void OnTimeoutMessageEntityClear( CMessage* pMsg );
	void OnTimeoutMessageEntityRelive( CMessage* pMsg );
	void OnTimeoutMessageEntityProtectTimeOver( CMessage* pMsg );
	void OnTimeoutMessageEntityAliveRefresh( CMessage* pMsg );
	void OnTimeoutMessageEndRedstoneProtect(CMessage* pMsg);
	void OnTimeOutMessageRedStoneClear( CMessage* pMsg );
	void OnTimeOutMessageFireRedStoneMagic( CMessage* pMsg );	
	void OnTimeoutMessageDiploidTime( CMessage* pMsg );
	void OnTimeOutMessageRedstoneProcess( CMessage* pMsg );
	void OnTimeOutMessageAssignment( CMessage* pMsg );
	void OnTimeOutMessageYellowStatus( CMessage* pMsg );
	void OnTimeOutMessageRefreshTen( CMessage* pMsg );
	void OnTimeOutMessageRefreshFive( CMessage* pMsg );
	void OnTimerItemChange( CMessage* pMsg );
	void OnTimeOutMessageCreateOgreTen( CMessage* pMsg );
	void OnTimeOutMessageFireBattle( CMessage* pMsg ); 
	void OnTimeOutMessageStartBattle( CMessage* pMsg );
	void OnTimeOutMessageTimeLimitTask(CMessage *pMsg);
	void OnTimeOutMessageCDGroup(CMessage* pMsg);
	void OnTimeoutMessageBuffEvent( CMessage* pMsg );
	void OnTimeOutMessageNonProtect( CMessage* pMsg );

	// ������Ϣ�ĺ���
	void SendItemBindedNotice( CEntityPlayer *tpPlayer, int ItemIndex, int ItemPos );
	void SendYourProDataNotice( CEntityPlayer* vpPlayer );
	void SendClickNpcResponse( CEntity* pPlayer, unsigned int vNpcEntityID );
	void SendCloseDialogNotice( CEntity* pPlayer );
	void SendUpdateMoneyNotice( CEntity* pPlayer, int vMoney, int vTotal );
	void SendUpdateBindMoneyNotice( CEntity* pPlayer, int vMoney, int vTotal );
	void SendRemoveItemNotice( CEntity* pPlayer, int vPos, unsigned short vItemIndex, unsigned short vNumber );
	void SendLockItemNotice( unsigned int vEntityID, int vIndex, int vLockType );
	void SendLockItemNotice( CEntity* pPlayer, int vIndex, int vLockType );
	void SendObtainExpNotice( CEntity* pPlayer, int vExpDelta, unsigned long long vExp, int vListID, bool IsLevelUp,  int vOffLineExp, int vLeftTime );
	void SendObtainHonorNotice( CEntity* pPlayer, int vChangeHonor );
	void SendMoveItemNotice( CEntity* pPlayer,unsigned short vSrcIndex, unsigned short vDesIndex, unsigned short vNumber, unsigned char vSrcSlot, unsigned char vDesSlot, int nErrcode, int nSrcNum, int nDesNum );
	void SendProErrorNotice( CEntity* pPlayer, int vType );
	void SendEquipItemNotice( CEntity* pPlayer, unsigned int vSrcIndex,  int nErrcode, unsigned int vDesIndex = ~0 );
	void SendUnEquipItemNotice( CEntity* pPlayer, unsigned short vPart, unsigned int vIndex, int nErrcode );
	void SendClickSkillPointResponse( CEntity* pPlayer, unsigned short vGenerID, unsigned char vCol, unsigned char vRow );
	void SendResetAPPResponse( CEntity* pPlayer, int nRet );
	void SendResetSSPResponse( CEntity* pPlayer, unsigned short vGenerID, unsigned char vCol, unsigned char vRow );
	void SendResetASPResponse( CEntity* pPlayer, int nRet );
	void SendResetTalentResponse( CEntity* pPlayer, int nRet, int nStep, int nPoint );
	void SendTelePortResponse( CEntity* pPlayer, unsigned short vIndex, int mPosX, int mPosY );
	void SendUpgAddItemResponse( CEntity* pPlayer, unsigned short vIndex1, unsigned short vIndex2 );
	void SendUpgDelItemResponse( CEntity* pPlayer, unsigned short vIndex1, unsigned short vIndex2 );
	void SendUpgEquipNotice( CEntity* pPlayer, unsigned short vResult, int vType, int nIndex, unsigned short vLevel = 0 );
	void SendProFinNotice( CEntity* pPlayer, int vResult, int vLeftNum  = 0 );
	void SendProBreakNotice( CEntity* pPlayer, int vResult );
	void SendPushRuneResponse( CEntity* pPlayer, int vIndex1, int vIndex2 );
	void SendPopRuneResponse( CEntity* pPlayer, int vIndex1, int vIndex2 );
	void SendInsertRuneNotice( CEntity* pPlayer, int vResult );
	void SendInsertPushJewelResponse( CEntity* pPlayer, int vIndex1, int vIndex2 );
	void SendInsertPopJewelResponse( CEntity* pPlayer, int vIndex1, int vIndex2 );
	void SendInsertJewelNotice( CEntity* pPlayer, int vResult, int vBind );
	void SendEatPushEquipResponse( CEntity* pPlayer, int vIndex1, int vIndex2 );
	void SendEatPopEquipResponse( CEntity* pPlayer, int vIndex1, int vIndex2 );
	void SendEatEquipNotice( CEntity* pPlayer, int vIndex, int vNumber );
	void SendComposePushResponse( CEntity* pPlayer, int vIndex1, int vIndex2 );
	void SendComposePopResponse( CEntity* pPlayer, int vIndex );
	void SendComoseNotice( CEntity* pPlayer, int vIndex, int vItemID, int vNumber1, int vNumber2 );
	void SendOpenPushResponse( CEntity* pPlayer, int vIndex1, int vIndex2 );
	void SendOpenPopResponse( CEntity* pPlayer, int vIndex1, int vIndex2 );
	void SendOpenSlotNotice( CEntity* pPlayer, int vIndex1, int vIndex2, int vNumber );
	void SendSyncPosNotice( CEntity* pPlayer, unsigned int vEntityID, int vPosX, int vPosY );
	void SendProExpNotice( CEntity* pPlayer, unsigned int vProLevel, unsigned int vProExp );
	void SendChangeSpeedToSeenEntity( CEntity* pEntity );
	void SendRideHorseNotice( CEntity* pEntity, unsigned int vTempID, int vResult );
	void SendStudySkillResponse( CEntityPlayer* pPlayer, int* tGenerIDList, int* tColList, int* tRowList, int tCount, unsigned int* tSkillIDList, int* tIndexList );
	void SendChangePKModeResponse( CEntityPlayer* pPlayer, int vRet );
	void SendLookPropertyResponse( CEntityPlayer* pPlayer, CEntityPlayer* pLooker, int vType );
	void SendLookPropertyRouterRequest( CEntityPlayer* pPlayer, int vCharID, int vType );
	void SendLookPropertyRouterResponse( CEntityPlayer* pPlayer, int vCharID, int vType );
	void SendLookPropertyResponse( CEntityPlayer* pPlayer, CMessageLookPropertyResponse* pLookMessage, int vType );
	void SendTripEntityDisplay( CEntityPlayer* pPlayer, CEntityPedal* pEntityPedal );
	void SendTripEntityDisplay( std::vector<CEntityPlayer*>* pTeamVec, CEntityPedal* pEntityPedal );
	void SendTripEntityDisappear( CEntityPlayer* pPlayer, CEntityPedal* pEntityPedal );
	void SendTripEntityDisappear( std::vector<CEntityPlayer*>* pTeamVector, CEntityPedal* pEntityPedal );
	void SendClickRedStone( CEntityPlayer *pPlayer, int EntityID, int Result );
	void SendStopRedStoneTimer( CEntityPlayer *pPlayer, int EntityId );
	void SendChangeStatus( CEntityPlayer *pPlayer, int Status );
	void SendMsgRedstoneStarted( CEntityPlayer *pPlayer, int TeamID );
	void SendUseItemResponse( CEntityPlayer *pPlayer, int vResult, int vPos, int vIndex, int vItemID, int vParam1 = 0, int vParam2 = 0, int vParam3 = 0 );
	void SendMsgBeginRedstoneMagic( CEntityRedStone *tpRedstone );
	void SendSetPasswordResponse( CEntityPlayer *pPlayer, int Errcode, int nStatus );
	void SendModifyPasswordResponse( CEntityPlayer *pPlayer, int Errcode, int nStatus );
	void SendCheckPasswordResponse( CEntityPlayer *pPlayer, int Errcode, int nStatus );
	void SendEventNotify( int vEventID, int vCountryID, int *vIntParam, int vSize, char *vStringParam1, char *vStringParam2, int vWorldID = 0 );
	void SendActiveCardNotice( CEntity* pPlayer, int vType, int vPos, int vItemID );
	
	void SendStorMoneyResponse( CEntityPlayer* pPlayer, int nErrcode, int nMoney, int nBindMoney, int nLmtMoney=0 );
	void SendTakeStorMoneyResponse( CEntityPlayer* pPlayer, int nErrcode, int nMoney, int nBindMoney, int nLmtMoney=0 );		
	
	void SendAddKitBagResponse( CEntityPlayer* pPlayer, int nErrcode, int nBagIndex, int nDesIndex, int nDestSlot, int nExpiredTime, int nBindStatus );		
	
	void SendAddDecompoundEquipResponse( CEntityPlayer* pPlayer, int nErrcode, int nEquipIndex );
	void SendTakeDecompoundEquipResponse( CEntityPlayer* pPlayer, int nErrcode, int nEquipIndex );
	void SendClientCtrlInfo(CEntityPlayer *pPlayer);
	void SetItemValidTime( CEntityPlayer* pPlayer, CTplItem* pTplItem, CItemObject* pItemObj);
	void StartItemValidTimer( CEntityPlayer* pPlayer, CItemObject* pItemObj);
	void OnTimeoutMessageDestroyItem(CMessage* pMsg);
	void CheckPlayerItems( CEntityPlayer* pPlayer );
	void SendPickItemResponse( CEntityPlayer* pPlayer, int vEntityID );
	void SendBindItemNotify( CEntityPlayer* pPlayer, int vIndex, int vStatus );

	void OnMessagePlayerUseFlowerRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	void PlayerUseFlower( int nSrcCharID, const char* pSrcName, CEntityPlayer* pDesPlayer, int nItemID, int nBagIndex );
	void OnMessageS2SUseFlowerRequest( CMessage* pMessage );
	void OnMessageS2SUseFlowerResponse( CMessage* pMessage );
	void OnUseFlowerSuccess( CEntityPlayer* pSrcPlayer , int nBagIndex);
	void SendChangeEquipProResponse( CEntityPlayer* pPlayer, int vResult, int vIndex1, int vIndex2 );
	void NotifyClientStartTimer(CEntityPlayer* pPlayer, EPosType vType, int nIndex, unsigned int tTime );
	void OnTimeOutMessageTitleDisappear(CMessage* pMsg);

public:
	/* �ڵ���غ��� */
	
	// �����ڵ��ı���ʱ��
	void EndRedStoneProtect( CTimerItem *tpTimer );
	
	// �ڵ�����Ϣʱ�䵽
	void ClearRedStone( CTimerItem *tpTimer );
	
	// �ڵ�������ʱ�䵽
	void RedStoneMagicTime( CTimerItem *tpTimer );
	
	// �ж϶����Ƿ����ڵ�
	bool IfRedStone( int ItemID, bool &bIfStart );

	// �ж϶����Ƿ���������
	bool IsItemAdapter( int nTempID );
	// �ж��ǲ���ĳ���͵���Ʒ
	bool CheckItemType( int nTempID, int vType );

	// ��ҵ���ڵ�
	void PlayerClickRedStone( CEntityPlayer *pPlayer, int RedStoneEnittyID );	
	
	// �ж϶����Ա�Ƿ��Ѿ��ɹ��������ڵ�
	bool CheckTeamRedstoneEffect( int nTeamID );
	
	// ���ö����Ա�Ѿ��������ڵ�
	void SetRedstoneEffect( int nTeamID, int nRedstoneID );
	
	// �ͻ���ֹͣ�ڵ��Ķ���
	void StopRedStonTimer( CEntityPlayer *pPlayer, int RedStoneEnittyID );
	
	// ��ʼ����
	void BeginRedStoneMagic( CEntityRedStone *tpRedStone, CEntityPlayer *pPlayer );
	
	// ������ȡ����
	void RedStoneAllotExp( CEntity *tpRedStone, int nOwenerID, int nRedStoneTmpID,  int LeftTime, int &rLastNum );
	
	// ���������ڵ�
	void CreatFamilyRedStone( CEntityPlayer *pPlayer, int nRedStoneTmpID );
	
	// �������帱���ڵ�
	void CreatFamilyRepetionRedstone( int nRedStoneTmpID, int nFamilyID, int nLineID, int nMapID, int nPosX, int nPosY, int nMapIndex, KEY_TYPE nRepetionKey );
	
	// ���������ڵ�
	void CreateCountryRedstone( int nLineID, int nMapID, int nMapIndex, int nPosX, int nPosY, int nCountryID, int nRedstoneTmpID );
			
	// �����ڵ���ȡ����
	void AllotFamilyExp( CEntityRedStone *tpRedStone, int nLeftTime, CTplRedStone *tpTplRedStone );
	
	// �ı���Ӷ�Ա���ڵ�״̬
	void ChangeTeamLeaverStatus( CEntityPlayer *pPlayer );
	
	// ����ұ�����ڵ���״̬
	void ClearRedstoneStatus( CEntityRedStone* tpRestone ); 
	
	// ���͹����ڵ���������Ϣ֪ͨ
	void SendNotifyCountryRedstoneStarted( CEntityPlayer *pPlayer, int nRedstoneType );

	// PK��ֵ����
	void ProcessPKValueOnDie( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity );
	void ProcessPKValueOnAttack( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity );
	void SendPKValueMessage( CEntityPlayer* pPlayer, int nValue );
	void SendYellowStateNotice( CEntityPlayer* pPlayer, bool bOpen );
	void DecExpOnPkDie( CEntityPlayer* pPlayer );
	
public:
	bool CheckSpecialUseCondition( CEntity* pSrcEntity, CTemplateSkill* tpSkill );

	void EntityTeleportBuffer( CEntityCharacter* pSrcEntity, int nTeleType, int nDistance );

	//bool EntityCanMove( CEntity* pEntity );

	void EntityCharge( CEntityCharacter* pSrcEntity, CEntity* pDesEntity );

	void EntityInsertDamageList( CEntity* pSrcEntity, CEntity* pDesEntity, int vDamage = 0 );

	// �Ƿ�����
	void CheckPKIsYellow( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity );

	// �Ƿ�����
	void CheckPKIsRed( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity );

	// NPC����������Ʒ
	void DropItemByNpcDie( CEntity* pOwnerEntity, CEntity* pDesEntity, CTemplateOgre* pTempOgre );

	// ���ݵ���������Ʒ
	void DropItemByID( CEntity* pOwnerEntity, CEntity* pDesEntity, int vDropID, const CDropFrom& vDropFrom, int *vNumber = NULL, int vDropType = 0, bool vNeedSend = false );

	int PlayerClickStudySkill( CEntityPlayer* pPlayer, unsigned int vEntityID );

	void StudySkillByChangeMetier( CPropertyPlayer* pProperty, int vMetierID, int* tGenerIDList, int* tColList, int* tRowList, int& tCount, int vMaxNum, unsigned int* tSkillIDList, int* tIndexList );

	void ActionSelfBless( CEntityCharacter* pSrcEntity, CTemplateNormalSkill* pNormalSkill, int vDamage, int vSkillType, bool& vbIfSrcDurReduced, bool& vbEntityType );
	void ActionSeenBless( CEntityCharacter* pSrcEntity, CTemplateNormalSkill* pNormalSkill, int vDamage, int vSkillType, bool& vbIfSrcDurReduced, bool& vbEntityType );

	void ActionAttackSingle( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateNormalSkill* pNormalSkill, int vSkillType, bool& vbIfSrcDurReduced, bool& vbEntityType );

	void ActionAttackRange( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateNormalSkill* pNormalSkill, int vSkillType, bool& vbIfSrcDurReduced, bool& vbEntityType, CEntityCharacter** vEntityList, int vEntityListNum );

	void ActionCussOrBlessSingle( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateNormalSkill* pNormalSkill, int vDamage, int vSkillType );

	void ActionCussOrBlessRange( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateNormalSkill* pNormalSkill, int vDamage, int vSkillType, bool& vbEntityType, CEntityCharacter** vEntityList, int vEntityListNum );

	void ActionTrip( CEntityCharacter* pSrcEntity, CTemplateSkill* pSkill, bool& vbIfSrcDurReduced );

	void ActionTeamBless( CEntityCharacter* pSrcEntity, CTemplateNormalSkill* pNormalSkill, int vDamage, int vSkillType, bool& vbIfSrcDurReduced, bool& vbEntityType );

	void ActionPetBless( CEntityCharacter* pSrcEntity, CTemplateNormalSkill* pNormalSkill, int vDamage, int vSkillType, bool& vbIfSrcDurReduced );

	void ActionRelive( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateNormalSkill* pNormalSkill, int vDamage, int vSkillType, bool& vbIfSrcDurReduced );

	void ActionTeleport( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateNormalSkill* pNormalSkill, int vDamage, int vSkillType, bool& vbIfSrcDurReduced );

	void ActionSummon( CEntityCharacter* pSrcEntity, CTemplateNormalSkill* pNormalSkill, bool& vbIfSrcDurReduced );

	void ActionAureole( CEntityCharacter* pSrcEntity, CTemplateSkill* pSkill, bool& vbIfSrcDurReduced, CEntityCharacter** vEntityList, int vEntityListNum );

	void ActionContinuedAttackRange( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateNormalSkill* pNormalSkill, CEntityCharacter** vEntityList, int vEntityListNum );
	
	void ActionContinuedCussOrBlessRange( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateNormalSkill* pNormalSkill, CEntityCharacter** vEntityList, int vEntityListNum );

	// ����һ���NPC��BUFF
	bool InsertBuff( CEntityCharacter* pDesEntity, int nBuffID, int nBuffTime = 0 ,int *nResultCode = NULL);
	// ����һ���NPC���ϸɵ�BUFF
	int RemoveBuff( CEntityCharacter* pDesEntity, int nBuffID );

	void SetDefaultValue( CEntityPlayer* pEntity );

	void SaveStallInfo(
		CEntityPlayer *pEntity,
		const char* pName,
		const char* pAd,
		int* pNumAry, 
		int* pPriceAry, 
		int* pItemIndexAry, 
		int* pStallIndexAry, 
		int* pPriceTypeAry,
		int vNumber,
		int vStallType);
	int GetStallInfo( CEntityPlayer* pPlayer, const int vStallType, char* pName, char* pAd, int* pItemIndexAry, int* pStallIndexAry, int* pPriceAry, int* pPriceTypeAry );

	void BuffByDamage( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, EResultType vResultType, int vSkillType, int& vDamage, int& tDesDamage, int& tShieldDamage, bool& tMagicShield );

	void CheckBuffEntityUseSkill( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity );

	// ��ù�ѫ
	void PlayerObtainHonor( CEntityPlayer* pSrcEntity, CEntityPlayer* pDesEntity, int* pMemberList = NULL, int vMemberCount = 1 );
	// ��ѫ������
	void PlayerChangeHonorToExp( CEntityPlayer *pPlayer, int vHonor );
	// ��Ǯ�����ù�ѫ
	void PlayerReliveHonor( CEntityPlayer* pPlayer, CPropertyPlayer* pProperty );
	void OnPlayerObtainHonor( CEntityPlayer* tpPlayer, int vHonor );

	void CheckBuffGetSkillAttackDesEntity( CEntityCharacter* pDesEntity, CTemplateSkill* vpSkill, int& tDesBuffFix, int& tDesBuffPer );
	void CheckBuffGetSkillAttackSrcEntity( CEntityCharacter* pSrcEntity, CTemplateSkill* vpSkill, int& tDeathRate, int& tDeathValue, int& tIgnoreRate, int tIgnoreType );
	void CheckBuffGetNormalAttackSrcEntity( CEntityCharacter* pSrcEntity, int& tDeathRate, int& tDeathValue );

	// ���ÿ�ܵ�ˢ�µ�
	void WeekRefresh();

	// ��������
	void ContinuedAttackSkill( CEntityCharacter* pSrcEntity, CTemplateNormalSkill* pNormalSkill, CWTPoint& vPos, CEntityCharacter** vEntityList, int vEntityListNum );

	// ���������ף��
	void ContinuedCussOrBlessSkill( CEntityCharacter* pSrcEntity, CTemplateNormalSkill* pNormalSkill, CWTPoint& vPos, CEntityCharacter** vEntityList, int vEntityListNum );

	// �⻷�����ϱ�
	void ContinuedAureoleSkill( CEntityCharacter* pSrcEntity, CTemplateAureoleSkill* pAureoleSkill, CWTPoint& vPos, CEntityCharacter** vEntityList, int vEntityListNum );
	/////	��Щ��UseItem�ĺ���
	// ʹ��ҩƷ
	int OnUsePhysics( CEntity *pEntity, CTplItem *tpItem, CItemObject* tpSrcItem, int vIndex, int &vRemainHP, int &vRemainMP, int &vRemainAP );
	// ʹ���������
	int OnUseRandomTP( CEntity *pEntity, int vIndex );
	// ʹ�ü��䴫��
	int OnUseRemberTP( CEntity *pEntity, int vIndex );
	// ʹ�ûسǵ���
	int OnUseTownTP( CEntity *pEntity, int vIndex );
	// ʹ������
	int OnUseHorse( CEntity *pEntity, CTplItem *tpItem, CItemObject* tpSrcItem );
	// ʹ�����ɷ��ؾ�
	int OnUseReturnPaper( CEntity *pEntity, CTplItem *tpItem, int vIndex );
	// ʹ�ô��ͷ�
	int OnUseTeleSymbol( CEntity *pEntity, CTplItem *tpItem, int vIndex, unsigned short vTeleOrder, int& nUsedTimes );
	// ʹ��¯ʯ
	int OnUseStove( CEntity *pEntity, CTplItem *tpItem, CItemObject* tpSrcItem, int vIndex );
	// ʹ�òر�ͼ
	int OnUseMineMap( CEntity* pEntity, CTplItem* tpItem, int vIndex );
	// ʹ������
	int OnUseToken( CEntity* pEntity, CTplItem* tpItem, int vIndex );
	// ʹ�ÿ�Ƭ
	int OnUseCard( CEntity* pEntity, CTplItem* tpItem, int vIndex );
	// ʹ�����
	int OnUseGiftBag( CEntity* pEntity, CTplItem* tpItem, int vIndex, int vParam );
	// ʹ������ܾ���
	int OnUseLifeSkillScroll( CEntity* pEntity, CTplItem* tpItem, int vIndex );

	// ʹ�� ��������Ʒ
	int OnUseFuncItem( CEntity* pEntity, CTplItem* tpItem, int vIndex );
	
	// ʹ�ú��
	int OnUseRedPaper( CEntity* pEntity, CTplItem* tpItem, int vIndex );
	
	// ʹ�úڹ���
	int OnUseBlackPills( CEntity* pEntity, CTplItem* tpItem, int vIndex );
	
	// �������߾��鵤��ʱ�� nTemplateID: ���߾��鵤�� templateid
	int ChangeOffLineTimeToExp( CEntityPlayer *pPlayer, int nIndex = -1 ,int nTemplateID = -1);

	// ʹ�û�Ա����
	int OnUseVipItem( CEntity* pEntity, CTplItem* tpItem, int vIndex );
	void SendVipNotice( CEntityPlayer* npPlayer, bool bFlag );
	void RefreshVip( CEntityPlayer* npPlayer );

	// ʹ��ϴ�����
	int OnUseCleanItem( CEntity* pEntity, CTplItem* tpItem, int vIndex );
	
	// ʹ�ü�������ع���Ʒ
	int OnUseLeagueBagItem( CEntity* pEntity, CTplItem* tpItem, int vIndex );	
	
	// ���Ĺ���
	int ChangeNationality( CEntityPlayer* vpEntity, CampDef vCamp );

	// ��˫����
	int RefreshDiploid( CEntityPlayer* pEntity, bool bOnLine );

	// ÿ��һ0��Ҫ���������(������ �����´����ߵ�ʱ���Զ�����)
	int WeeklyDispose( CEntityPlayer* pPlayer, bool bIsOnline );
	int DaylyDispose( CEntityPlayer* pPlayer, bool bIsOnline );

	// �漴������Ʒ
	int RandomDropItem( CEntityPlayer* pEntity, int vDropID, const CDropFrom& vDropFrom, int vDropType );
	// ��������и���buff
	int RandomHitBuff( CEntityPlayer* pEntity, int vBuffID );
	// ��������ˢ��������
	int BrushOgre( CEntityPlayer* pEntity, int vOgreID, int vNum, bool bNotify, bool bNormal );
	// ���븱��
	int LoginRepetion( CEntityPlayer* pEntity, CTplMineMap* tpMap);
	
	// drop item 
	int DropItemOnPkDie( CEntityPlayer* pPlayer );
	int DropEquip( CEntityPlayer* pPlayer );
	int DropItem( CEntityPlayer* pPlayer, int vNum );

	// ������� [12/14/2009 Macro]
	// npPlayer :		��������, 
	// nPrisonTime :	����ʱ��(����)
	// return : -1 ʧ��, 0 �ɹ�
	int OnEventCoopEntity( CEntityPlayer* npPlayer, int nPrisonTime );
	
	// �����ͷ� [1/8/2010 Macro]
	int OnEventUnCoopEntity( CEntityPlayer* npPlayer );

	void OnEventNotifyPrisonTime( CEntityPlayer* npPlayer );
	void SendPrisonTimeNotice( CEntityPlayer* npPlayer, int nPrisonTime );

	void SendUseItemNotify( CEntityPlayer* pPlayer, int vItemID );
	
	// ����ʹ�úڹ����֪ͨ��Ϣ
	void SendUseBlackPillsNotify( CEntityPlayer *pPlayer, int nOffLineTime, int nPillsLeftTime, int nPillsIndex, int nExp, int nOffLineTimeConsumed, int nBlackPillID, int nErrcode );
		
protected:
	static CEntityResultList mResultList;
	static CEntityResultList mSingleList;

	// ��������Ϣʱ��ʵ��ɾ���б�
	unsigned int mEntityDeleteList[ FUNC_LIMIT ];
	unsigned int mDeleteListCount;
	
public:
	inline CEntityResultList* GetResultList() { return &mResultList; }
	inline CEntityResultList* GetSingleList() { return &mSingleList; }

	// Ϭ��ר��
	void UseSkillForServer( CEntityCharacter* pSrcEntity, CEntityCharacter* pDesEntity, CTemplateSkill* pSkill, CEntityCharacter** vEntityList, int vEntityListNum );

	//// ����ü���
	//int PlayerUseSkill( );

	//// �ٻ����ü���
	//int PetUseSkill();


	// ָ��ˢ��
	void PlayerGetOgre( CEntityPlayer* pPlayer, int nOgreID );
	void CreateNpc( CEntityPlayer* pPlayer, int nNpcTempID, EEntityType nEntityType, CWTPoint& pos, int nLifeTime = 0, bool bIsSetOwner = false, bool bIsShout = false, int nDestMapID = 0, int nIsShowOwner = 0 );
	void CreateHierogram( CTplHierogram* pTpl, CWTPoint* tpPos, CMapObject* pMapObject );

	// ��ʼ��ʵ��ɾ���б�
	void InitDeleteList( );

	// ���ʵ��ɾ���б�
	void AddDeleteList( unsigned int nEntityID );

	// ���ʵ��ɾ���б��е�ʵ��
	void ClearDeleteList( );

	// NPC�����
	int FuncNpcChange2Ogre( CEntityPlayer* pPlayer, CEntityNpc* pEntityNpc, unsigned short vTaskID =0 );

	// NPC�����(�����սʧ��)
	void RecoverNpcState( CEntityNpc* pEntity );

	// ���ù���NPC״̬ (�ڱ�ɹ�������û�ȥ)
	void ResetFuncNpc( CEntityNpc* pEntity );

	// ֪ͨ�ͻ��� NPC ��PK״̬ ����
	void NotifyClientNpcPKTypeChanged( CEntityNpc* pEntityNpc );

	// ���߼���а��ֵ
	void RefreshPkValue( CEntityPlayer* npPlayer, int nTickOffset );

	// ˢ�³ƺŸ�������
	void RefreshTitleAddProperty( CEntityPlayer* npPlayer );

	// ���ߴ������ֵ
	void RefreshApValue( CEntityPlayer* vpPlayer );

	// ʹ���ٻ�����Ʒ
	int OnUseItemCall(CEntity *pEntity, CTplItem *tpItem, int vIndex);

	// ʹ�ü�������Ʒ
	int OnUseItemSkill(CEntity *pEntity, CTplItem *tpItem, int vIndex);	

	// �����ƺŻ�ȡ�¼�
	// vType: �ƺ�����:���񡢺��ѡ�����
	// vParam1����ȡ�óƺŵ�����
	// vParam2 ...
	int FireTitleEvent( CEntityPlayer* vpPlayer, int vType, int vParam1, int vParam2 = 0 );

	// ��ģ����ã�������ӳƺ�
	// nTitleID :���ƺ�ID
	int OnPlayerAddTitleEvent( CEntityPlayer* vpPlayer, int nTitleID, int nValidTime = 0 );
	// ɾ��һ���ƺ�
	int OnPlayerDelTitleEvent( CEntityPlayer* npPlayer, int nTitleID );

	int InsertTitleSkill( CEntityPlayer* vpPlayer, int* vTitleList, int vNum );

	// �Զ��ػ� �̳ǹ���ĵ������󶨷ǰ󶨴���
	int GetStoreItemID( int* npItemList, int nLen, int nType, int nIndex );


	// ֪ͨ�ͻ��˸��³ƺ�����
	void SendNotifyClientUpdateTitle(CEntityPlayer *vpPlayer, int vType, int vTitleID);
	void SendNotifyUpdateCurrentTitle( CEntityPlayer *vpPlayer, int vTitleID, const char *pTitleName = NULL );

	void OnEventSaveStallRecord( CEntityPlayer* vpPlayer, CStallRecord* vpRecord ,const int vStallType);
	void OnEventGetStallRecord( CEntityPlayer* vpPlayer, CMessageStallGetRecordResponse* vpMessage, const int vStallType );
	
	// ����ʵ���ʱ����������Ʒ ����û�зǷ���
	void CheckBagContent( CEntityPlayer *pPlayer );
	void CheckEquipment( CEntityPlayer *pPlayer ) ;

	// ��ҵ���ʱ��Ʒ��ʱ���˴���
	// ��������ң�Ŀ����Ʒ����Ʒ����λ��, �������ͣ�0����ʱɾ����1��ʱ��ɾ��)
	int OnPlayerItemOverTime( CEntityPlayer* pPlayer, CItemObject* pItemObj, EPosType posType, int nTimeoutType );
	void CheckItemInvilidDate( CEntityPlayer* pPlayer, bool bIsNotify );

	// �����������ʱ���Բر�ͼ���������Ƶ�������Ҫ���������Ľӿ�
	template< typename TYPE_ITEM, typename TYPE_OBJ >
	int SetItemPosRandom( TYPE_ITEM* vpTplItem, TYPE_OBJ* vpObj )
	{
		if ( vpTplItem == NULL || vpObj == NULL )
		{
			return -1;
		}
		int tIndex = 0; 
		int	tPosIndex[ MAX_MINEPOS ] = { 0 };
		for ( int i = 0; i < (int)ARRAY_CNT( vpTplItem->mPos ); i ++ )
		{
			if ( vpTplItem->mPos[ i ].mMapID == 0 )
			{
				continue;
			}
			tPosIndex[ tIndex ++ ] = i;
		}
		int tRandom = RAND( tIndex );

		if ( tRandom >= (int)ARRAY_CNT( vpTplItem->mPos ) )
		{
			return -1;
		}		

		vpObj->SetMapID( vpTplItem->mPos[ tRandom ].mMapID );
		vpObj->SetPosX( vpTplItem->mPos[ tRandom ].mPosX );
		vpObj->SetPosY( vpTplItem->mPos[ tRandom ].mPosY );
		return SUCCESS;
	}

	void NotifyRefreshMagicWeaponProperty( CEntityPlayer* pPlayer, int nBagIndex );
	void NotifyRefreshMagicWeaponProperty( CEntityPlayer* pPlayer, int nType, int nBagIndex );
	int  OnMagicWeaponObtainExp( CEntityPlayer* pPlayer, int nExp, bool bIsPile=false );
	void OnTimeOutMessageMagicWeaponIncMp( CMessage* pMsg );
	void OnTimeOutMessageMagicWeaponDecHp( CMessage* pMsg );
	void OnMessageMWAddPotential( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnMessageChangeExpScaleRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnMessageMWAddSkillPoints( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnMessageMWJudgeSkill( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnMessageLockMWInBagRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnMessagePlayerTakeOffMW( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnMessagePlayerJudgeMWProperty( CEntityPlayer* pPlayer, CMessage* pMessage );

	void RefreshPlayerProperty( CEntityPlayer* pPlayer );
	void OnMessageMWUseSkillBookRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnMessageChangePKDrop( CEntityPlayer* pPlayer, CMessage* pMessage );

	void OnMessageProcessMultiBuffRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnMessageMagicWeaponClearPointAddMWRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnMessageMagicWeaponClearPointRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	void OnMessageGetHelpRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ��������͵��ߵĴ��͵��б�
	void OnMessageGetTeleList( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �����Ӵ��͵�
	void OnMessageAddTelePoint( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ���ɾ�����͵�
	void OnMessageDelTelePoint( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ���ʹ�ô��͵���
	void OnMessageUseTeleItem( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �յ��ͻ�����ȡԪ������
	void OnMessageDrawGoldenYB( CEntityPlayer* pPlayer, CMessage* pMessage );

	// �յ��ͻ��˲�ѯԪ���������
	void OnMessageQueryGoldenYB( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ������ͻ��˵Ĵ���֪ͨ
	void SendMultiTeleportNotify( CAsynTeleport vTeleport, char *vName );

	// ������ͻ��˵Ĵ���֪ͨ
	void SendSingleTeleportNotify( int vCharID, ComplexPos vPos, char *vName, int vTokenID );
	
	// �����ڵ�(ֱ������)
	void StartRedstone( CEntity *pEntity, int nOwnerID, int nRedstoneTmpID, bool bDestroyEntity = true );
	
	// �������밲ȫʱ������Ϣ
	void OnMessageSetPwdProtectTimeRequest(  CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// �������ð�ȫ���밲ȫʱ������Ϣ��Ӧ
	void SendResponseSetPwdProtectTime( CEntityPlayer *pPlayer, int nErrcode, int nTimeLength );
	
	// ���Ͱ�ȫ����״̬�ı��֪ͨ
	void SendNotifyChangePasswordStatus( CEntityPlayer *pPlayer, int nPasswordStatus, const char *pPassword = NULL );

	// ֪ͨ���� vip �仯
	void SendVipFlagUpdateToGate( CEntityPlayer *npPlayer );
	
	// ����Ʒ������ͨ�󶨵���Ϣ����
	void OnMessageCommonBindRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ������ͨ�󶨵Ļ�Ӧ��Ϣ
	void SendCommonBindResponse( CEntityPlayer *pPlayer, int nErrcode, int nItemIndex, int nItemSlot );
	
	// �ͻ��˿�ʼ�������Ϣ����
	void OnMessageStartProgressRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// �ͻ��˿�ʼ�������Ϣ��Ӧ
	void SendStartProgressResponse( CEntityPlayer *pPlayer, int nErrcode );
	
	// ʹ���廨�����Ϣ����
	void OnMessageUseKitbagNeedleRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ����ʹ���廨��Ļ�Ӧ��Ϣ
	void SendUseKitbagNeedleResponse( CEntityPlayer *pPlayer, int nErrcode, int nKitbagSlot, int nKitbagIndex, int nNeedleIndex, int nExpiredTime, int nTimeLength );
	
	// ��ȫ����������������������
	void OnMessageLockPasswordRequest( CEntityPlayer *pPlayer, CMessage *pMessage );
	
	// ���ͱ����������������Ļ�Ӧ��Ϣ
	void SendLockPasswordResponse( CEntityPlayer *pPlayer, int nErrcode, int nStatus );

	// ѧϰ��ħ־��������
	void OnMessageLearnOgreSkillRequest(CEntityPlayer* pPlayer, CMessage* pMessage );

	// ��ѯ���͵�����
	void OnMessageQueryPedalRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	void SendGetItemNotify( CEntityPlayer *pPlayer, int vItemID, int vNum, int vType, int vSpecial = 0, int vLevel = 0 );
	
	// �����װ���ܷ�ʹ��
	int CheckMarriageEquipmentValid( CEntityPlayer *pPlayer, CTplItem *pTplItem, CItemObject *pItemObj, CEntity *pEntity );

	// ��¼���ɶѵ�������ҵ�������
	void LogIbItemUsed( CEntityPlayer* pPlayer, CItemObject * tpThrowItem);
	
	// �ж���Ҷ���
	void StopProgress( CEntityPlayer *pPlayer );

	// ʹ���ټ���Ʒ
	int OnMessageUseSummonItemRequest( CEntityPlayer* pEntity, CMessage *pMessage );

	// ֪ͨ��Աʰȡ��Ʒ
	void SendPickItemNotify( CEntityPlayer *pPlayer, int vItemID );

	// ����װ��ӡ����
	void OnMessageAddExtraRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	void OnMessageWarOperateRequest( CEntityPlayer* pPlayer, CMessage* pMessage );
	void SendChangeOwnCampNotify( CEntityNpc *tpNpc );
	void SendWarEventNotify( int vEventID, int vMapID, int vPosX, int vPosY, int vSrcCampID, int vDesCampID, int vValue, int vTempID, const char *vName );

	void ObtainWarHonor( CEntityPlayer *pPlayer, int vValue, bool vSelf );
	
	// ��¼װ����ͨ�󶨵�ʱ��
	void SetEquipBindTime( CItemObject *pItem );

	// ���ͱ���״̬
	void SendPlayerTransformNotify( CEntityPlayer *pPlayer );
	// ѧϰ����ɽ����
	void OnMessageLearnFangCunSkillRequest( CEntityPlayer* pPlayer, CMessage *pMessage );
	void SendLearnFangCunSkillResponse( CEntityPlayer* pPlayer, int vResult, int vSkillID, int vItemIndex, int vObjIndex );

	void OnMessageHonorToItemRequest( CEntityPlayer* pPlayer, CMessage* pMessage );

	void OnPlayerLevelUp( CEntityPlayer *pPlayer, int vUpLevel );
	
	// �����������鵤�ĺ���
	void AddExpToExpContainer( CEntityPlayer *pPlayer, int nExp );
	
	// �����������鵤����ı��֪ͨ
	void SendExpContainerNotify( CEntityPlayer *pPlayer, unsigned long long nExp, int nExpAdded, int nIndex, int nExpPillsID );
	
	// ʹ�þ��鵤
	int OnUseExpPills(CEntity *pEntity, CTplItem *tpItem, int vIndex);

	//����Ԫ��������Ϣ
	void SendUpdateYuanbaoNotice( CEntity* pPlayer, const int vAmount, const int vType );

    // ҡǮ������临��
    void OnTimeoutMessageEntityRelive2( CMessage* pMsg );
    
    // ʹ��ʱװ�廨��
    void UseFashionNeedle( CEntityPlayer *pPlayer, int nNeedleIndex, int nFashionIndex, int nFashionslot );
	// ��ʯ����
	void OnMessageJewelCarveRequest( CEntityPlayer* pPlayer, CMessage *pMessage );
	
	// ���������񻨵���Ϣ����
	void OnMessageStartDigitalFireworks( CEntityPlayer* pPlayer, CMessage *pMessage );	
	
	// ���Ͳ��������񻨵Ļ�Ӧ��Ϣ
	void SendResponseStartDigitalFireworks( CEntityPlayer *pPlayer, int nErrcode );

	void LogRoleDamage( CEntityPlayer* pSrcPlayer, CEntityPlayer* pDesPlayer, int vSkillID, int vRealDamage, int vResultType );

	// ����ʱװ��ʾ״̬
    void OnMessageChangeFashionShow( CEntityPlayer* pPlayer, CMessage* pMessage );
    
	// ����װ����ʾ״̬
	void OnMessageChangeEquipShow( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����װ����ʯ������Ϣ
	void SendUpgAndJewNotice( CEntityPlayer *pPlayer, int vType, int vLevel, CItemObject *pObject );

	// ��ѯBOSS
	void OnMessageQueryBossRequest( CEntityPlayer* pPlayer, CMessage *pMessage );

	// �����������
	void OnMessageDecomposeMW( CEntityPlayer* pPlayer, CMessage *pMessage );
	void OnMessageMWQLPrintRequest( CEntityPlayer* pPlayer, CMessage *pMessage );
	void OnMessageMWQuickUpRequest( CEntityPlayer* pPlayer, CMessage *pMessage );
	void OnMessageQilinComposeRequest( CEntityPlayer* pPlayer, CMessage *pMessage );
	void MWLevelUp(CEntityPlayer* pPlayer, int nLevel);

	void OnMessageBagLockRequest( CEntityPlayer *pPlayer,  CMessage *pMessage );
	void OnMessageQueryAroundPlayerRequest( CEntityPlayer *pPlayer,  CMessage *pMessage );

	void SendPlayerRepetData(CEntityPlayer * pPlayer, int vRepetionIndex, int vDataIndex );
	// int nSlotType����,  int nIndexλ��, int nIndexNum ��������,int nAddTime ���ϵ�ʱ��
	bool AddBagInvalidTime( CEntityPlayer *pPlayer, int nSlotType, int nIndex, int nIndexNum,int nAddTime );
	//��� vipʱ�� ���� vip���Գ�Ϊvip
	bool AddVIPTime( CEntity *pEntity, int tAddTime );

	// ���ؿͻ��˹��ܿ������õĻص�����
	static void LoadClientCtrlConfigCallback(const char* pcConfigPath);

	void ChangeCombatFame( CEntityPlayer *pPlayer, int vDeltaFame );
	void ChangeRepeFame( CEntityPlayer *pPlayer, int vDeltaFame );
	void ChangeCommonFame( CEntityPlayer *pPlayer, int vDeltaFame );
	void SendSyncFameNotify( CEntityPlayer *pPlayer, int vCombatDelta, int vRepeDelta, int vCommonDelta );

	// ����
	void OnMessageSpiritOpenRequest(CEntityPlayer* pPlayer, CMessage *pMessage);
	void OnMessageSpiritCastingRequest(CEntityPlayer* pPlayer, CMessage *pMessage);
	void OnMessageSpiritUpgradeRequest(CEntityPlayer* pPlayer, CMessage *pMessage);
	void OnMessageSpiritDowngradeRequest(CEntityPlayer* pPlayer, CMessage *pMessage);
	int	 PlayerSpiritUpgrade(CEntityPlayer *pPlayer, int *apnSpiritIndex, int nUpgradeItemIndex);
	int  PlayerSpiritDowngrade(CEntityPlayer *pPlayer, int nPosition, int nType, int nSlot, int nItemIndex);
	void OnMessageSpiritInfoRequest(CEntityPlayer* pPlayer, CMessage *pMessage);
	void SendSpiritInfo(CEntityPlayer* pPlayer);
	int  PlayerSpiritCasting(CEntityPlayer *pPlayer, int nPositionIndex, int nTypeIndex, int nSlotIndex, int nItemIndex);
};