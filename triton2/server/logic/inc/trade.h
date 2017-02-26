#pragma once

#include "tradetype.h"
#include "errcode.h"
#include "lk_vector.h"
#include "lk_hashmap.h"
#include "object.h"

class CMessage;
class CEntityPlayer;

// ������Ʒ
struct TRADE_GOODS
{
	unsigned int	mEntityID;		// ��Ʒ������
	unsigned short	mItemIndex;		// ��������
	unsigned int	mTradeIndex;	// ����������
	unsigned int	mCount;			// ��Ʒ����
	int m_nItemObjID;				// ��Ʒ�Ķ���ID, ֻ������ʹ��
	unsigned int	mItemID;		// ��Ʒģ��ID

	TRADE_GOODS() 
	{
		if ( CObj::msCreateMode )
		{
			mEntityID = 0;
			mItemIndex = 0;
			mTradeIndex = 0;
			mCount = 0;
			mItemID = 0;

			m_nItemObjID = -1;
		}
	}

	TRADE_GOODS( unsigned int vEntityID, unsigned int vItemIndex, unsigned int vTradeIndex, unsigned int vCount, int nItemObjID, int nItemID ) :
	mEntityID( vEntityID ), mItemIndex( vItemIndex ), mTradeIndex( vTradeIndex ), mCount( vCount ), m_nItemObjID(nItemObjID), mItemID( nItemID )  {  }
};

typedef lk::vector< TRADE_GOODS, TRADE_COUNT_MAX > TRADE_GOODS_LIST_TYPE;

// �������
struct TRADE_PLAYER 
{
	unsigned int				mEntityID;
	unsigned int				mCharID;
	TRADE_STATE					mState;			// ����״̬
	TRADE_GOODS_LIST_TYPE		mGoods;			// ������Ʒ�б�
	unsigned int				mMoney;	

	TRADE_PLAYER()
	{
		if ( CObj::msCreateMode )
		{
			mEntityID = 0;
			mCharID = 0;
			mState = emNoneState;
			mMoney = 0;
			mGoods.initailize();
		}			
	}
};

class CTrade : public CObj
{
public:
	TRADE_PLAYER mOrigin;		// ���׷�����
	TRADE_PLAYER mTarget;		// ���׶Է�

public:
	CTrade( );
	~CTrade( );

	// ��ʼ��
	virtual int Initialize();

	// �ָ�
	virtual int Resume();

	// ��ʼ���׶���
	int InitTrade( unsigned int vSrcEntityID, unsigned int vDesEntityID );	

	// ���״���
	int ProcTrade( unsigned int vEntityID );

	// �ж�����Ƿ��ڽ�����
	bool IsInTrade( unsigned int vEntityID );

	// �ı����״̬
	int ChangeTradeState( unsigned int vEntityID, TRADE_STATE vState );
	
	// �ж���Ʒ�Ƿ��ڽ��׹�����
	bool IsGoodsInTrade( TRADE_GOODS_LIST_TYPE* pGoodsList, unsigned int vItemIndex, unsigned int vTradeIndex );		

	// ɾ����Ʒ
	int DelGoodsByIndex( TRADE_GOODS_LIST_TYPE* pGoodsList, unsigned int vItemIndex, unsigned int vTradeIndex );

	// �����Ʒ
	int InsertGoods( unsigned int vEntityID, unsigned int vItemIndex, unsigned int vTradeIndex, unsigned int vCount , int nItemObjID, int nItemID );

	//// ����۳���Ʒ�б�
	//int InsertNpcGoods( unsigned int vEntityID, unsigned int vPrice, unsigned int vCount );

	unsigned int GetOriginEntityID( unsigned int vEntityID );
	unsigned int GetTargetEntityID( unsigned int vEntityID );

	TRADE_PLAYER* GetOriginPlayer( unsigned int vEntityID );
	TRADE_PLAYER* GetTargetPlayer( unsigned int vEntityID );

	// �������� 
	int LockPackage( unsigned int vEntityID, unsigned int vItemIndex );

	// ��������
	int UnLockPackage( unsigned int vEntityID, unsigned int vItemIndex );

	// �����жϣ���������
	int UnLockTrade( unsigned int vEntityID );

	int GetOriginGoodsList( TRADE_GOODS** pGoodsList, int tNum, unsigned int vEntityID );
	int GetTargetGoodsList( TRADE_GOODS** pGoodsList, int tNum, unsigned int vEntityID);

	int GetOriginGoodsNum( unsigned int vEntityID );
	int GetTargetGoodsNum( unsigned int vEntityID );

	int GetOriginMoney( unsigned int vEntityID );
	int GetTargetMoney( unsigned int vEntityID );

	void SetOriginMoney( unsigned int vEntityID, unsigned int vMoney );
	void SetTargetMoney( unsigned int vEntityID, unsigned int vMoney );

	int ProcessState( unsigned int vEntityID );

	inline void ClearGoods() { mOrigin.mGoods.clear(); mTarget.mGoods.clear(); }

	TRADE_STATE GetOriginState( unsigned int vEntityID );
	TRADE_STATE GetTargetState( unsigned int vEntityID );

	bool CanGoodsUpdate( unsigned int vEntityID, unsigned int vItemIndex, unsigned int vTradeIndex );
	int RemoveGoods( unsigned int vEntityID, unsigned int vItemIndex, unsigned int vTradeIndex );
};



