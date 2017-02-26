#ifndef _IBSTORE_MODULE_H_
#define _IBSTORE_MODULE_H_


#include "ibstore.h"
#include "ibstore_pb.hxx.pb.h"
#include "message_pb.hxx.pb.h"
#include "entity.h"
#include "modulemanager.h"
#include "servercore.h"
#include "servertool.h"
#include "sequence.h"

using namespace SceneServer;

#define WORLD_SERVER_ID(WORLDID, SERVERID) (WORLDID * 100 + 8)

// ********************************************************************** //
// CIbTrans
//
// ���ڽ����еĽ���, ������ڹ����ڴ���
//
// ********************************************************************** //

class CSession;

class CIbTrans: public CObj
{
	enum 
	{
		em_invalid_purchase = 0,
	};

  private:
	unsigned int m_nTransID;  	// �̳ǽ��׵�ΨһID
	unsigned int m_nRoleID;	    // ��ҽ�ɫID
	unsigned int m_nAccountID; 	// ��ҵ��ʺ�ID

	int m_nGoodsID;    // ��ƷID
	int m_nGoodsCount;  // ��Ʒ������

	int m_nItemID;     // ��ƷID
	int m_nItemCount;  // ����Ʒ��������Ʒ������

	int m_nPriceUnit;  // ��Ʒ�Ƽ۵�λ
	int m_nPriceValue; // ����
	int m_nDiscount;   // �ۿۺ�۸�

	int  m_nPileLimit; // ��Ʒ����ѵ�������
	int  m_iStatus;    // ��ǰ���׵�״̬

	time_t m_tmTransTime;	//����ʱ��
	int m_nSex;
	int m_nMetier;
	int m_nLevel;
	int m_nIP;
	int m_nBalanceBeforePurchase; // ����ǰ���

	int m_nFameType;

  public:
	CIbTrans()
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

	~CIbTrans()
	{
	}

	int Initialize()
	{
		m_nTransID = em_invalid_purchase;

		m_nRoleID = 0;
		m_nAccountID = 0;

		m_nGoodsID = 0;
		m_nGoodsCount = 0;

		m_nItemID = 0;
		m_nItemCount = 0;

		m_nPriceUnit = 0;
		m_nPriceValue = 0;
		m_nDiscount = 0;

		m_nPileLimit = 0;

		m_tmTransTime = 0;

		m_nSex = 2;
		m_nMetier = 7;
		m_nLevel = 1;
		m_nIP = 0;
		m_nBalanceBeforePurchase = 0;

		return 0;
	}

	int Resume()
	{
		return 0;
	}

	// TransID
	void SetTransID(unsigned int nTransID) { m_nTransID = nTransID; }
	unsigned int  GetTransID() { return m_nTransID; }

	// RoleID
	void SetRoleID (unsigned int nRoleID) { m_nRoleID = nRoleID; }
	unsigned int GetRoleID() { return m_nRoleID; }

	// AccountID
	void SetAccountID( unsigned int nAccountID ) { m_nAccountID = nAccountID; }
	unsigned int GetAccountID() { return m_nAccountID; }

	// GoodsID
	void SetGoodsID(int nGoodsID) { m_nGoodsID = nGoodsID; }
	int GetGoodsID() { return m_nGoodsID; }

	// GoodsCount
	void SetGoodsCount(int nCount) { m_nGoodsCount = nCount; }
	int GetGoodsCount() { return m_nGoodsCount; }

	// ItemID
	void SetItemID(int nIbItemID) { m_nItemID = nIbItemID; }
	int GetItemID() { return m_nItemID; }

	// ItemCount
	void SetItemCount(int nCount) { m_nItemCount = nCount; }
	int GetItemCount() { return m_nItemCount; }

	// PriceUnit
	void SetPriceUnit(unsigned int nPriceUnit) { m_nPriceUnit = nPriceUnit; }
	int GetPriceUnit() { return m_nPriceUnit; }

	// PriceValue
	void SetPriceValue(unsigned int nPriceValue) { m_nPriceValue = nPriceValue; }
	int GetPriceValue() { return m_nPriceValue; } 

	// Discount
	void SetDiscount(unsigned int nPriceValue) { m_nDiscount = nPriceValue; }
	int GetDiscount() { return m_nDiscount; } 

	// PileLimit
	void SetPileLimit(int nPileLimit) { m_nPileLimit = nPileLimit; }
	int GetPileLimit() { return m_nPileLimit; }

	// m_tmTransTime
	void SetTransTime(time_t nTimeStampt) { m_tmTransTime = nTimeStampt; }
	time_t GetTransTime() { return m_tmTransTime; }
	
	// Sex, Metier, Level, IP
	void SetRoleSex(int nSex) { m_nSex = nSex; }
	void SetRoleMetier (int nMetier) { m_nMetier = nMetier; }
	void SetRoleLevel ( int nLevel ) { m_nLevel = nLevel; }
	void SetRoleIP ( int nIP ) { m_nIP = nIP; }

	int GetRoleSex() { return m_nSex; }
	int GetRoleMetier() { return m_nMetier; }	
	int GetRoleLevel() { return m_nLevel;}
	int GetRoleIP() { return m_nIP; }

	void  SetBalanceBeforePurchase(int nBalance) { m_nBalanceBeforePurchase = nBalance;}
	int GetBalanceBeforePurchase() {return m_nBalanceBeforePurchase;}

	// FameType 
	int GetFameType() { return m_nFameType; }
	void SetFameType( int nFameType ) { m_nFameType = nFameType; }
};

// ********************************************************************** //
// CFuncTrans
//
// ���ڽ����еĽ���, ������ڹ����ڴ���
//
// ********************************************************************** //

class CFuncTrans: public CObj
{
private:
	unsigned int m_nTransID;  	// ���ܽ��׵�ΨһID
	unsigned int m_nRoleID;	    // ��ҽ�ɫID
	unsigned int m_nAccountID; 	// ��ҵ��ʺ�ID

	int m_nFuncsID;    // ����ID
	int m_nFuncsCount;  // ���������

	//int m_nItemID;     // ��ƷID
	//int m_nItemCount;  // ����Ʒ��������Ʒ������

	int m_nPriceType;  // �������� Ԫ������Ԫ������Ǯ���󶨽�Ǯ
	int m_nPriceValue; // ����

	//int  m_nPileLimit; // ��Ʒ����ѵ�������
	int  m_iStatus;    // ��ǰ���׵�״̬

	time_t m_tmTransTime;	//����ʱ��
	int m_nSex;
	int m_nMetier;
	int m_nLevel;
	int m_nIP;
	int m_nBalanceBeforePurchase; // ����ǰ���
	int m_ExtraData1;			//��������1
	int m_ExtraData2;			//��������2

public:
	CFuncTrans()
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

	~CFuncTrans()
	{
	}

	int Initialize()
	{
		m_nTransID = 0;
		m_nRoleID = 0;
		m_nAccountID = 0;
		m_nFuncsID = 0;
		m_nFuncsCount = 0;
		m_nPriceType = -1;
		m_nPriceValue = 0;
		m_iStatus = 0;
		m_tmTransTime = 0;
		m_nSex = 2;
		m_nMetier = 0;
		m_nIP = 0;
		m_nBalanceBeforePurchase = 0; 
		m_nLevel = 0;
		m_ExtraData1 = 0;
		m_ExtraData2 = 0;
		return 0;
	}

	int Resume()
	{
		return 0;
	}

	void SetTransID( unsigned int vTransID ){  m_nTransID = vTransID;}
	unsigned int GetTransID( ){ return m_nTransID ;}

	void SetRoleID( unsigned int vRoleID ) {  m_nRoleID = vRoleID ;}
	unsigned int GetRoleID( ){ return m_nRoleID;}

	void  SetAccountID( unsigned int vAccountID ){  m_nAccountID = vAccountID ;}
	unsigned int GetAccountID( ){ return m_nAccountID; }

	void SetFuncsID( int vFuncsID ) {  m_nFuncsID = vFuncsID ;}
	int GetFuncsID( ){ return m_nFuncsID ;}

	void SetFuncsCount( int vFuncsCount ){  m_nFuncsCount = vFuncsCount; }
	int GetFuncsCount( ){ return m_nFuncsCount ;}

	void SetPriceType( int vPriceType ) {  m_nPriceType = vPriceType ;}
	int GetPriceType( ) { return  m_nPriceType ;}

	void SetPriceValue( int vPriceValue ) {  m_nPriceValue = vPriceValue ;}
	int GetPriceValue( ) { return m_nPriceValue ;}

	void SetStatus ( int vStatus ) {  m_iStatus = vStatus ;}
	int GetStatus( ) { return m_iStatus; }  

	void SetTransTime( int vTransTime ){ m_tmTransTime = vTransTime ;}
	int GetTransTime( ) { return m_tmTransTime ;}

	void SetSex( int vSex ){ m_nSex = vSex ;}
	int GetSex( ){  return m_nSex; }

	void SetMetier( int vMetier ){ m_nMetier = vMetier ;}
	int GetMetier( ) { return m_nMetier ; }

	void SetIP( int vIP ){ m_nIP = vIP; }
	int GetIP( ){ return m_nIP; }

	void SetLevel( int vLevel ){ m_nLevel = vLevel ;}
	int GetLevel(){ return m_nLevel;}

	void  SetBalanceBeforePurchase(int nBalance) { m_nBalanceBeforePurchase = nBalance;}
	int GetBalanceBeforePurchase() {return m_nBalanceBeforePurchase;}

	void SetExtraData( int vExtraData1 ,int vExtraData2){ m_ExtraData1 = vExtraData1;  m_ExtraData2 = vExtraData2; }
	int GetExtraDatat1(){ return m_ExtraData1 ;}
	int GetExtraDatat2(){ return m_ExtraData2 ;}
};

// �̳�ģ��
class CIbStoreModule : public CLogicModule, public CSingleton< CIbStoreModule >
{
private:
	enum  { em_trans_fail = 0, em_trans_ok = 1 };
	enum  { em_ibitem_limit = 1024 };

	typedef lk::hash_map<int, CGoods, em_ibitem_limit> goods_t;
	typedef lk::hash_map<int, CPromotion, em_ibitem_limit> promotion_t;
	typedef lk::hash_map<int, CFuncConsume, em_ibitem_limit> funcconsum_t;

	typedef goods_t::const_iterator const_iterator;
	typedef goods_t::iterator iterator;
	typedef goods_t::value_type value_type;

	
	PBIbStore* m_ppbIbStore;
	CSequence* m_pSequence;

	PBIbSubTab* m_ppbFocus;
	char m_szBulletin[1024];
	int  m_nVersion;
	size_t m_nFocus;

	size_t m_nStore;
	goods_t m_tGoods;
	promotion_t m_tPromotion;
	funcconsum_t m_tFuncConsume;
	bool m_bFuncIsLoad;

	// insert pIbItem
	bool InsertGoods(CGoods& pIbItem);

	// find nItemID
	CGoods* GetGoods(int nGoodsID);


	// insert pFuncItem
	bool InsertFuncs(CFuncConsume & func);

	// find Func by DI
	CFuncConsume* GetFuncs( int nFuncID);

	CWTimer mLoadInterval;

public:
	CIbStoreModule();
	~CIbStoreModule();


	static unsigned int CountSize();

public:
	// ����������
	virtual void OnLaunchServer( );

	// �˳�������
	virtual void OnExitServer( );

	// ������Timer
	virtual void OnTimer( unsigned int vTickCount, unsigned int vTickOffset );

	// ��������
	virtual int OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName );

	// ·����Ϣ
	virtual void OnRouterMessage( CMessage* pMessage );

	// ������Ϣ
	void OnGateMessage( CMessage* pMessage );

	// �ͻ��˷�����Ϣ
	virtual void OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage );

	// ����ʵ��
	virtual void OnCreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst );

	// ����ʵ��
	virtual void OnDestroyEntity( CEntity* pEntity, int vCode );

	// �洢����
	virtual bool OnSaveData( CEntityPlayer* pPlayer, int vSaveCode );

	// ��������
	virtual void OnLoadConfig( );

	// ����������ϼ��
	virtual bool OnCheckLaunch( ) { return true; }

	// ������Ʒ�����첽����
	void OnSessionPlayerPayAmount( CMessage *tpMessage, int nRoleID, int nTransID);

	// ������Ʒ�첽����ʱ
	void OnSeessionTimeoutPlayerPayAmount( CSession* pSession );

	// ���ʹ���֪ͨ����� 
	void SendIbStorePromotion2Player( CEntityPlayer* pPlayer);

	// ������Ʒ������� 
	void IncPurchaseTimes4Player(CEntityPlayer* tpPlayer, CGoods* pGoods, int nNum, time_t t);

	// ������Ʒ������� 
	std::pair<int, int> GetPurchaseTimes4Player(CEntityPlayer* tpPlayer, CGoods* pGoods, time_t t);

public:

	// �̳���Ʒ�б����� from Client
	void OnMessageListIbItemsRequest(CEntityPlayer *pPlayer, CMessage *pMessage );

	// ��ҳ�ֵ֪ͨ
	void OnMessageUserChargeNotice( CMessage* pMessage);

	// ������Ʒ����
	void OnMessagePurchaseIbItemRequest(CEntityPlayer *pPlayer, CMessage *pMessage );

	// ֪ͨ��ҽ���ʧ��
	void SendPurchaseError(CEntityPlayer* tpEntity, int nError);

	// ͬ���̳���Ʒ�б�
	void OnMessageSynIbStoreResponse(CMessage *tpMessage );

	// �յ�������ȡԪ����Ӧ
	void OnMessageDrawYuanBaoResponse( CMessage* pMessage);

	// �յ����ز�ѯԪ������Ӧ
	void OnMessageQueryYuanBaoResponse( CMessage* pMessage);

	static char sModuleName[ NAME_LENGTH ];

	bool Send2DBPurchaseRequest(CEntityPlayer* pPlayer, CIbTrans* tpTrans, CGoods* pGoods, bool IsYuanbao);

	void OnMessageLockGoodsResponse( CMessage* pMessage );

	void OnMessageIbStorePromotionNotice( CMessage* pMessage);

	// ��������ҷ���ϵͳ�ʼ�
	void SendIbItem2OfflinePlayer(int nRoleID, CTplItem* ptpl, int nItemCount, uint64_t ullTransID);

	// ͬ�����ܸ����б� 
	void OnMessageSynFuncStoreResponse( CMessage *tpMessage );

	//���ܸ����б����� from Client
	void OnMessageGetFuncConsumesRequest(CEntityPlayer *pPlayer, CMessage *pMessage );

	//��ҹ��ܸ�������
	void OnMessagePurchaseFuncRequest(CEntityPlayer * pPlayer, CMessage *pMessage );
	//���͹��ܸ���ʧ����Ϣ
	void SendPurchaseFuncError(CEntityPlayer* tpEntity, int nError);
	//���ܸ������ݿ�����
	bool Send2DBPurchaseFuncRequest(CEntityPlayer* pPlayer, CFuncTrans* tpTrans, CFuncConsume* pFuncConsume);
	//���ܸ������ݿ���Ӧ
	void OnSessionPlayerPayFunc(CMessage *tpMessage, int nRoleID, int nTransID);
	//���ܸ������ݿⳬʱ
	void OnSessionTimeoutPlayerPayFunc( CSession* pSession );
	
	void PurchaseFuncByMoney( CEntityPlayer * pPlayer,CMessagePurchaseFuncRequest *pPurchaseFunc );

	void PurchaseFuncByYB( CEntityPlayer * pPlayer,CMessagePurchaseFuncRequest *pPurchaseFunc );

};

#endif
