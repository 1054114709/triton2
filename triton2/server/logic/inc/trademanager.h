#pragma once


#include "tradetype.h"
#include "trade.h"
#include "time.h"
#include "trademessage_pb.hxx.pb.h"
#include "sceneobj_define.h"
#include "sceneobj_manager.h"


class CSharedMem;
class CEntityPlayer;


// ���׹�ϵ��
struct TRADE_MAP
{
	unsigned int mOriginID;			// ���뷢����
	unsigned int mTargetID;			// ��ϵ��
	time_t		 mCreatedTime;		// ���뷢��ʱ��

	TRADE_MAP() 
	{
		if( CObj::msCreateMode )
		{
			mOriginID = 0;
			mTargetID = 0;
			mCreatedTime = 0;
		}
	}
	TRADE_MAP( unsigned int vOriginID, unsigned int vTargetID, int vCreatedTime ) :
	mOriginID( vOriginID ), mTargetID( vTargetID ), mCreatedTime( vCreatedTime ) { }
};

class CTrade;

class CTradeManager : public CSingleton < CTradeManager >
{
private:
	typedef lk::vector< TRADE_MAP, SERVER_TRADEUNIT_MAX >	TradeMapList;
	typedef lk::vector< int, SERVER_TRADEUNIT_MAX >		TradeList;

	TradeMapList	mTradeMap;			// ���׹�ϵ�˱�
	TradeList		mTradeList;			// ���׶����

public:
	CTradeManager( );
	~CTradeManager( );
	static CSharedMem* mShmPtr;
	static unsigned int CountSize( );

	void* operator new( size_t nSize );
	void  operator delete( void *pMem );

	void* operator new(size_t size, const char* file, int line);
	void operator delete(void* pointer, const char* file, int line);

	//��������
	CTrade* CreateTrade( unsigned int vSrcEntityID, unsigned int vDesEntityID );

	// ������ҽ�����Ʒ�б�: ��ӡ��Ƴ���Ʒ
	int UpdateTradeInfo( CEntityPlayer* pPlayer, unsigned int vItemIndex, unsigned int vTradeIndex,	unsigned int vCount, TRADE_TYPE vType );

	// ��ȡ���׶���
	CTrade* GetTrade( unsigned int vEntityID );

	// ��ӽ��׶���
	int AddTrade( CTrade* pTrade );

	// ��ӽ����˼�¼
	int InsertTradeMap( unsigned int vSrcEntityID, unsigned int vDesEntityID );

	// ɾ�������˼�¼
	int EraseTradeMap( TRADE_MAP* pTradeMap );

	bool IsInTradeMap( unsigned int vEntityID );

	// �Ƿ�æ
	bool IsBusy( unsigned int vEntityID );

	// �Ƿ��ظ�����
	bool IsInviteRepeated( unsigned int vSrcEntityID, unsigned int vDesEntityID );

	// �ж�����������������(20��)
	bool IsOverUpperLimit( unsigned int vEntityID );

	// �Ƿ�����Ч����
	bool IsValidDistance( CEntityPlayer* pOriginPlayer, CEntityPlayer* pTargetPlayer );

	// ����������Ϣ
	int LockTradeInfo( unsigned int vEntityID );

	// ���״���
	int ProcTrade( unsigned int vEntityID );

	//int ProcNpcTrade( unsigned int vEntity, unsigned int vBagIndex, unsigned int vShopIndex, unsigned int vCount, unsigned int vPrice );

	// ��������
	int EndTrade( unsigned int vEntityID, TRADE_CLOST_TYPE vType );

	// ɾ�����׶���
	int DeleteTrade( CTrade* pTrade );

	// �ƺ���
	int DoClean( );

	// ��������ϵ�Ƿ�ʧЧ
	int CheckValidInvite( long vNowTime );

	// �õ����׹�ϵ
	TRADE_MAP* GetTradeMap( unsigned int vSrcEntityID, unsigned int vDesEntityID );

	// ɾ����������
	int DeleteAllInvite( unsigned int vEntityID );

	// ֪ͨ�ͻ��˸�����Ʒ�б���Ϣ
	void OnSendNotifyTradeGoodsCallBack( int vEntityID, int vType, /*char* pBuff*/PBItemObject* tpItem, int vItemIndex, int vTradeIndex, bool vIsSelf );

	// ֪ͨ�ͻ��˸��½��׽��
	void OnSendNotifyTradeMoneyCallBack( int vEntityID, int vMoney, bool vIsSelf ); 

	// ֪ͨ�͑����i��������Ϣ
	void OnSendLockTradeCallBack( int vEntityID, bool vFlag, int vCode ); 

	// ֪ͨ�͑����P�]����
	void OnSendTradeCloseCallBack( int vEntityID, int vCode );

	void OnSendTradeMsgCallBack( int vDesEntityID, unsigned int vSrcEntityID, int vCode );

	void OnSendTradeMsgCallBack( CEntityPlayer* pPlayer, unsigned int vEntityID, int vCode );

	void AddGoods( CEntityPlayer* pPlayer, unsigned int vItemIndex, unsigned int vTradeIndex, unsigned int vCount );

	void SendErrorNotice( CEntityPlayer* pPlayer, int vCode );
};
