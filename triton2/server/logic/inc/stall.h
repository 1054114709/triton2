#pragma once

#include "coretype.h"
#include "stallmessage_pb.hxx.pb.h"

//#define STALL_TYPE_ALL 0
//#define STALL_TYPE_MONEY 1
//#define STALL_TYPE_YB 2

// ��̯��Ʒ
struct GOODS
{
	unsigned int ItemID;	// ����id
	unsigned int Number;
	unsigned int Price;
	unsigned int Index;		// ̯λ����
	unsigned int BagIdx;	// ��������
	unsigned int PriceType; // �۸�����
	unsigned int Status;   // ��Ʒ��״̬

	enum 
	{
		EGOODS_STATUS_NONE = 0,		// ����״̬
		EGOODS_STATUS_TRADING,		// ��Ʒ���ڱ����ף����ʱ����Ҫ��������Ʒ�ģ���ֹ���첽�������ظ�����
	};

	GOODS() {
		if ( CObj::msCreateMode )
		{
			ItemID = 0;
			Number = 0;
			Price = 0;
			Index = 0;
			BagIdx = 0;
			PriceType = 0;
			Status = EGOODS_STATUS_NONE;
		}		
	}

	GOODS( unsigned int vItemID, unsigned int vNum, unsigned int vPrice, unsigned int vStallIdx, unsigned int vBagIdx, unsigned int vPriceType ) :
	ItemID( vItemID ), Number( vNum ), Price( vPrice ), Index( vStallIdx ), BagIdx( vBagIdx ), PriceType(vPriceType), Status(EGOODS_STATUS_NONE) {  }
};

class CStall : public CObj
{
private:
	char	mStallName[ NAME_LENGTH ];	// ̯λ����
	unsigned int mMasterID;				// ̯��entityid
	char	mAdContent[ 2 * NAME_LENGTH ];	// �������
	int		mStallType; ////��̯���� 0:�����֣�1����2��Ԫ��

	typedef lk::vector< GOODS, MAX_STALL_INDEX > StallType;
	StallType mStall;					// ̯λ��Ʒ

public:
	CStall();
	~CStall();

public:
	virtual int Initialize();
	virtual int Resume();

	// init stall object
	int InitStall( unsigned int vMasterID, unsigned int vStallType );

	// insert goods into stall booth
	int InsertGoods( unsigned int vItemID, unsigned int vNum, unsigned int vPrice, unsigned int vStallIdx, unsigned int vBagIdx,unsigned int vPriceType );

	// remove goods from stall booth
	int RemoveGoods( unsigned int vBagIndex, unsigned int vStallIndex, unsigned int vNumber );

	// update goods price
	int UpdatePrice( unsigned int vStallIndex, unsigned int vPrice, unsigned int vPriceType );

	// lock goods in baggage
	bool LockGoods( unsigned int vIndex );

	// unlock goods
	bool UnLockGoods( unsigned int vIndex );

	// update stall name
	inline void UpdateStallName( const char* pName ) { LK_ASSERT( pName != NULL, return ); strncpy( mStallName, pName, sizeof( mStallName ) - 1 ); }

	// update ad content
	inline void UpdateAdContent( const char* pAd ) { LK_ASSERT( pAd != NULL, return ); strncpy( mAdContent, pAd, sizeof( mAdContent ) - 1 ); }

	// get stall name
	inline const char* GetStallName() { return mStallName; }

	// get ad content
	inline const char* GetAdContent() { return mAdContent; }

	// get stall by index
	int GetGoodsIndex( unsigned int vStallIndex, unsigned int& tItemIndex, unsigned int& tItemNum, unsigned int& tPrice, unsigned int& tItemID, unsigned int& tPriceType );	

	// get stall goods list
	int GetStallInfo( CMessageClickStallResponse* tpResponse );

	// �õ�/�޸İ�̯��Ʒ��״̬
	int GetGoodsStatus( unsigned int nStallIndex );
	void SetGoodsStatus( unsigned int nStallIndex, int Status );


	// release all goods in booth
	int ReleaseGoods( );

	void SaveData( CEntityPlayer* pPlayer );

	inline const int GetStallType() { return mStallType; };
};


