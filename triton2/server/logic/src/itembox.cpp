#include "stdafx.hpp"
#include "proclient_svr.h"
#include "coremessage_pb.hxx.pb.h"
#include "promessage_pb.hxx.pb.h"
#include "sceneobj_manager.h"
#include "scenelogic.h"
#include "westserver.h"
#include "servercore.h"
#include "entity.h"
#include "template.h"
#include "property.h"
#include "entity.h"
#include "pro_define.h"
#include "propertymodule.h"
#include "scenecfg_manager.h"
#include "repetionmodule.h"
#include <llimits.h>
#include "buffer.h"

//////////////////////////////////////////////////////////////////////////
// CItemBox
//////////////////////////////////////////////////////////////////////////

// ����ָ�������ϵ��ض�������Ʒ����
unsigned int CItemBoxToolkit::ComputeItemNum( int nIdx, unsigned int nItemID, int nType  )
{
	CItemObject* tpItemObj = mItemBox->GetItemObjPtr( nIdx ); 
	if ( tpItemObj != NULL && tpItemObj->IsSameItemGroup( nItemID, nType) )
		return tpItemObj->GetItemNum();

	return 0;
}

// ����һ�������ڵ��ض�������Ʒ����
unsigned int CItemBoxToolkit::ComputeItemNum( int nBegin, int nEnd, unsigned int nItemID,  int nType )
{
	unsigned int nTotalNum = 0;
	for ( int i = nBegin; i < nEnd; i ++ )
	{	
		nTotalNum += ComputeItemNum( i, nItemID, nType );
	}
	return nTotalNum;
}

// ���������������ض�������Ʒ����
unsigned int CItemBoxToolkit::ComputeItemNum( unsigned int nItemID, int nType )
{
	unsigned int nNum = ComputeItemNum( 0, mItemBox->mReleaseIndex, nItemID, nType );

	for ( int i = 0; i < mItemBox->mKitBagIndex; ++i )
	{
		int tBeginIndex = 0;
		int tEndIndex	= 0;
		int tRet = mItemBox->GetKitBagIndexRange( BAGTYPE_KITBAG, i, tBeginIndex, tEndIndex );
		if ( tRet != SUCCESS )
		{	 
			continue;
		}		
		nNum += ComputeItemNum( tBeginIndex, tEndIndex + 1, nItemID, nType );
	}

	return nNum;
}

//
//// �õ�ָ����������Ʒ��ʹ�ô���
//int CItemBoxToolkit::GetItemUsedNum( int nIdx, unsigned int nItemID )
//{
//	CItemObject* tpItemObj = mItemBox->GetItemObjPtr( nIdx );
//	LK_ASSERT( tpItemObj != NULL, return 0 );
//
//	if ( tpItemObj && tpItemObj->GetItemID() == nItemID )
//	{
//		return tpItemObj->GetUsedTimes();
//	}
//	else
//	{
//		return 0;
//	}
//}
//
//// �õ�ָ��һ����������Ʒ��ʹ�ô���
//int CItemBoxToolkit::GetItemUsedNum( int nBegin, int nEnd, unsigned int nItemID )
//{
//	int nCount = 0;
//	for ( int i = nBegin; i < nEnd; i ++ )
//	{
//		nCount += GetItemUsedNum( i );
//	}
//	return nCount;
//}
//
//// �õ�������ָ����Ʒ��ʹ�ô���
//int CItemBoxToolkit::GetItemUsedNum( unsigned int nItemID )
//{
//	int nCount = GetItemUsedNum( 0, mItemBox->mReleaseIndex, nItemID );
//	for ( int i = 0; i < mItemBox->mKitBagIndex; ++i )
//	{
//		int tBeginIndex = 0;
//		int tEndIndex	= 0;
//		int tRet = mItemBox->GetKitBagIndexRange( BAGTYPE_KITBAG, i, tBeginIndex, tEndIndex );
//		if ( tRet != SUCCESS )
//		{	 
//			continue;
//		}		
//		nCount += GetItemUsedNum( tBeginIndex, tEndIndex, nItemID );
//	}
//	return nCount;
//}


// ����ָ�������϶�ָ����Ʒ��ʣ��ѵ���
int CItemBoxToolkit::GetLeftPileNum( int nIdx, unsigned int nItemID, bool bEmptyCounted /* = true */ )
{
	// -1��ʾ���ҿո�����
	if( nItemID == (unsigned int)(-1) ) 
	{
		if( mItemBox->operator[](nIdx) == INVALID_OBJ_ID )
			return 1;
		return 0;
	}
	else
	{
		CTplItem* tpItem = (CTplItem*) CDataStatic::SearchTpl( nItemID );
		if ( tpItem == NULL )
			return 0;

		// ����ǿո��ӣ��������ѵ���
		if( mItemBox->operator[](nIdx) == INVALID_OBJ_ID && bEmptyCounted )
			return tpItem->mPileLimit;

		CItemObject* tpItemObj = mItemBox->GetItemObjPtr( nIdx );
		if( tpItemObj == NULL )
			return 0;

		if ( tpItemObj->GetItemID() == nItemID )
		{
			return  tpItem->mPileLimit - tpItemObj->GetItemNum();
		}
		else
		{
			return 0;
		}

	}
}

// ����һ�������ڶ�ָ����Ʒ��ʣ��ѵ���
int CItemBoxToolkit::GetLeftPileNum( int nBegin, int nEnd, unsigned int nItemID, bool bEmptyCounted /* = true */ )
{
	int nCount = 0;
	for ( int i = nBegin; i < nEnd; ++i )
	{
		nCount += GetLeftPileNum( i, nItemID, bEmptyCounted );
	}
	return nCount;
}

// �õ������ڶ�ָ����Ʒ��ʣ��ѵ���
int CItemBoxToolkit::GetLeftPileNum( unsigned int nItemID, bool bEmptyCounted /* = true */ )
{
	int nCount = GetLeftPileNum( 0, mItemBox->mReleaseIndex, nItemID, bEmptyCounted );
	for ( int i = 0; i < mItemBox->mKitBagIndex; ++i )
	{
		// ��������ʱ����
		if ( mItemBox->CheckKitBagExpiredTime( i ) )
		{
			continue;
		}
		int tBeginIndex = 0;
		int tEndIndex	= 0;
		int tRet = mItemBox->GetKitBagIndexRange( BAGTYPE_KITBAG, i, tBeginIndex, tEndIndex );
		if ( tRet != SUCCESS )
		{	 
			continue;
		}		
		nCount += GetLeftPileNum( tBeginIndex, tEndIndex + 1, nItemID, bEmptyCounted );
	}
	return nCount;
}

// �õ�ָ��������ָ�����͵ĵ��߸���
int CItemBoxToolkit::GetCertainTypeItemNum( int nIdx, int nType, int nFuncType )
{
	CItemObject* tpItemObj = mItemBox->GetItemObjPtr( nIdx );	
	if ( tpItemObj == NULL )
	{
		return 0;
	}

	CTplItem *tpItem = ( CTplItem * )CDataStatic::SearchTpl( tpItemObj->GetItemID() );
	if ( tpItem == NULL )
	{
		return 0;
	}

	if ( tpItem->mItemType != nType )
	{
		return 0;
	}

	if ( tpItem->mItemType != CTplItem::ITEM_FUNCITEM )
	{
		return tpItemObj->GetItemNum();
	}

	CTplFuncItem *tpFuncItem = ( CTplFuncItem * )tpItem;
	if ( tpFuncItem->mFuncCode == nFuncType )
	{
		return tpItemObj->GetItemNum();	
	}

	return 0;
}

// ɾ��ָ��������ָ�������ĵ���
int CItemBoxToolkit::RemoveItem( int nIdx, unsigned int nItemID, unsigned int nNumber, int nType )
{
	int nRemovedNum = 0;
	CItemObject* tpItemObj = mItemBox->GetItemObjPtr( nIdx ); 
	if ( tpItemObj != NULL && tpItemObj->IsSameItemGroup( nItemID, nType ) )
	{
		if ( nNumber == (unsigned int)~0 )
		{
			nRemovedNum = tpItemObj->GetItemNum();
			CSceneObjManager::GetSingletonPtr()->DestroyObject( mItemBox->operator []( nIdx ) );
			mItemBox->operator []( nIdx ) = INVALID_OBJ_ID;
		}
		else
		{
			// ԭ�����߼�����,û�п��ǵ�vNumber�����
			int mOldNum = tpItemObj->GetItemNum();
			tpItemObj->SetItemNum( std::max( 0, (int)( tpItemObj->GetItemNum() - nNumber ) ) );
			nRemovedNum = mOldNum - tpItemObj->GetItemNum();

			if ( tpItemObj->GetItemNum() == 0 )
			{
				CSceneObjManager::GetSingletonPtr()->DestroyObject( mItemBox->operator []( nIdx ) );
				mItemBox->operator []( nIdx ) = INVALID_OBJ_ID;						
			}
		}
	}
	return nRemovedNum;
}


/** ��ָ����������ָ����������
**  ����������ǿյģ�����ֵΪ����pTplItem�����ѵ������������ո�ʱ��������ʱֻ�Ǽ�¼����������������������ߡ�
**	����������ǿգ����Һ�Ҫ����ĵ���id��ͬ����ʱ��ʼ�ѵ����㡣
*/
int CItemBoxToolkit::InsertItem( int nIdx, CItemObject* pItem, CTplItem *pTplItem )
{
	CItemObject* pItemObj = mItemBox->GetItemObjPtr ( nIdx );
	if ( pItemObj == NULL ) 
	{
		// �ո��ӵ��ڽ������Բ���һ���ѣ�ʵ�������ǵ������ϱ������ȶѵ������Բ���ֱ�ӷ��롣

		return pTplItem->mPileLimit;
	}
	else
	{
		// ���;���ҵ�����һ���ĵ���,���ز���ĸ���
		if ( pItemObj->GetItemID() == pItem->GetItemID() && pItemObj->GetBindStatus() == pItem->GetBindStatus() )
		{
			int tUpper = pTplItem->mPileLimit - pItemObj->GetItemNum();
			if ( tUpper > 0 )
			{
				int tRemain		= std::max( 0, (int)( pItem->GetItemNum() - tUpper ) );
				int tMoveNumber	= pItem->GetItemNum() - tRemain;
				pItemObj->SetItemNum( pItemObj->GetItemNum() + tMoveNumber );
				pItem->SetItemNum( tRemain );
				return tMoveNumber;
			}
			return 0;
		}
		else
		{
			// ��ͬ���͵��߲���0��
			return 0;
		}
	}
}


/**
** �������ж�ָ��������װ�����Ƿ�󶨵���
** INVALID_OBJ_ID����װ��������װ������δ�󶨻���װ�����Ѿ����
** 
*/

int CItemBoxToolkit::CheckEquipBindTime( int nIdx )
{
	CItemObject *tpItemObj = mItemBox->GetItemObjPtr( nIdx );
	if ( tpItemObj ==  NULL )
	{
		return INVALID_OBJ_ID;
	}

	CTplItem *tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tpItemObj->GetItemID() );
	if ( tpTplItem == NULL )
	{
		return INVALID_OBJ_ID;
	}
	if ( !tpTplItem->IsEquipable() )
	{
		return INVALID_OBJ_ID;
	}		

	if ( (tpTplItem->mProcessType & CTplItem::PROCESSTYPE_CANBIND) == 0 )
	{
		return INVALID_OBJ_ID;
	}
	if ( (tpItemObj->GetBindStatus() & ITEM_BINDSTATUS_FREEBIND ) == 0  )
	{
		return INVALID_OBJ_ID;
	}
	CItemEquipment *tpEquipment = ( CItemEquipment * )tpItemObj;
	int				LeftTime    =  tpEquipment->GetBindFreeTime( ) - time( 0 );
	if ( LeftTime <= 0 )
	{	
		int BindStatus =  tpItemObj->GetBindStatus( );
		BindStatus &= ~ITEM_BINDSTATUS_FREEBIND;
		return INVALID_OBJ_ID;		
	}
	return tpItemObj->get_id();
}

/* �������õ�ָ��������װ����������
** ���أ�<0 ����װ��������װ��������Ҫ����; 0����ʧ�;õ�װ������������Ϊ0; >0����ʧ�;õ�װ���������������0
**/
int CItemBoxToolkit::GetEquipMendMoney( int nIdx )
{
	CItemObject* tpSrcItem = mItemBox->GetItemObjPtr( nIdx );
	if ( tpSrcItem == NULL )
	{
		return -1;
	} 		

	int tItemMendMoney = 0;
	CTplItem* tpTplItem =( CTplItem * )CDataStatic::SearchTpl( tpSrcItem->GetItemID() );
	if( tpTplItem == NULL )
	{
		LOG_ERROR("pro"," [%s,%d][%s]Item( ItemID :%d)  does not exist int template! ",
			__LK_FILE__,__LINE__,__FUNCTION__ , tpSrcItem->GetItemID() );
		return -1;
	}    
	if( tpTplItem->IsEquipable() )
	{
		CItemEquipment * tpEuipmentItem = ( CItemEquipment * ) tpSrcItem;
		tItemMendMoney = tpEuipmentItem->GetMendMoney();			
		if( tItemMendMoney > 0 ||  tpEuipmentItem->GetLostDurability() > 0  )
		{
			// ĳЩ�����װ��ά�޲�ҪǮ�����ǻ��ǻ���;�
			return tItemMendMoney;			
		}
		return -1;
	}

	return -1;
}


void CItemBox::DeleteUnusedItem( int vCharID )
{
	CItemList<BOX_LIMIT>::DeleteUnusedItem( vCharID );
}

template<int NUMBER>
void CItemList<NUMBER>::DeleteUnusedItem( int vCharID )
{
	for ( int i = 0; i < NUMBER; i ++ )
	{
		if( mpItems[ i ] == INVALID_OBJ_ID )
		{
			continue;
		}

		lk::vector<int, 20>::iterator it = CSceneServer::GetSingleton().mDeleteList.begin();
		for ( ; it != CSceneServer::GetSingleton().mDeleteList.end(); ++it )
		{
			CItemObject *tpItemObject = (CItemObject*)CSceneObjManager::GetSingleton().GetObject( mpItems[ i ] );
			if ( tpItemObject == NULL )
			{
				continue;
			}
			if ( *it == (int)(tpItemObject->GetItemID()) )
			{
				CSceneObjManager::GetSingletonPtr( )->DestroyObject( mpItems[ i ] ) ;
				mpItems[ i ] = INVALID_OBJ_ID;
				LOG_ERROR( "pro" ,"Delete Unused Item %d Player %d", *it, vCharID );
				continue;
			}
		}
	}
}


// ===========================================================================================================

int CItemBox::Initialize( )
{
	mReleaseIndex = BAGGAGE_BASE;
	for ( int i = 0 ; i <  MAX_KITBAG_NUM ; i++ )
	{
		mKitbag[ i ] = INVALID_OBJ_ID;
		mKitLocked[i] = 0;
	}
	mKitBagStatus = 0;//STORAGE_STATUS_INVALID;
	mKitBagIndex = 0;

	mItemPair.initailize();
	return 0;
}

unsigned int CItemBox::Space( )
{
	// ��ӶԱ������ж�	
	for ( unsigned int i = 0; i < BOX_LIMIT; i ++ )
	{
		// ��������ʱ����
		if ( operator [] (i) == INVALID_OBJ_ID && CheckIndexValid( i, true ) )
			return i;
	}

	return ~0;
}


bool CItemBox::Lock( int vItemIndex, int vLock )
{
	if ( vLock == LOCKTYPE_NONE )
	{
		if( operator []( vItemIndex ) != INVALID_OBJ_ID )
		{
			//mpItems[ vItemIndex ]->mLocked = vLock;

			CItemObject* tpItemObj = GetItemObjPtr ( vItemIndex );
			LK_ASSERT( tpItemObj != NULL, return false );

			tpItemObj->SetLockStatus( vLock );

		}
		return true;
	}

	if ( operator []( vItemIndex ) != INVALID_OBJ_ID )
	{
		CItemObject* tpItemObj = GetItemObjPtr ( vItemIndex );
		LK_ASSERT( tpItemObj != NULL, return false );

		if ( tpItemObj->GetLockStatus() == LOCKTYPE_NONE )
		{
			tpItemObj->SetLockStatus( vLock );
			return true;
		}
	}

	return false;
}


bool CItemBox::HasItem( unsigned int vItemID, unsigned int vNumber, int vType )
{
	return HasItem( vItemID, vType ) >= (int)vNumber;
}

int CItemBox::HasItem( unsigned int vItemID, int vType )
{
	CItemBoxToolkit tBoxToolkit(this);
	return tBoxToolkit.ComputeItemNum( vItemID, vType );
}

//// �õ�ʹ�ô���
//int	CItemBox::GetItemUsedTimes( int vItemID )
//{
//	for ( unsigned int i = 0; i < BOX_LIMIT; i ++ )
//	{			
//		CItemObject* tpItemObj = GetItemObjPtr( i );
//		LK_ASSERT( tpItemObj != NULL, continue );
//
//		if ( tpItemObj && (int)tpItemObj->GetItemID() == vItemID )
//			return tpItemObj->GetUsedTimes();
//	}
//	
//	for ( int i = 0; i < mKitBagIndex; ++i )
//	{
//		int tBeginIndex = 0;
//		int tEndIndex	= 0;
//		int tRet = GetKitBagIndexRange( BAGTYPE_KITBAG, i, tBeginIndex, tEndIndex );
//		if ( tRet != SUCCESS )
//		{	 
//			continue;
//		}		
//		for ( int j = tBeginIndex; j <= tEndIndex; ++j )
//		{
//			CItemObject* tpItemObj = GetItemObjPtr( j ); 
//			if ( tpItemObj &&  tpItemObj->GetItemID() == (unsigned int)vItemID )
//				return tpItemObj->GetUsedTimes();
//		}
//	}  	
//	return 0;
//}
//


// �ж�ָ����λ���Ƿ�����Щ����
bool CItemBox::HasItem( unsigned int vIndex, unsigned int vItemID, unsigned int vNumber, int vType )
{
	CItemBoxToolkit tBoxToolkit(this);
	return tBoxToolkit.ComputeItemNum( vIndex, vItemID, vType ) >= vNumber;
}

// ����ָ��λ���ϵĵ�������
int CItemBox::GetItemNum( unsigned int vIndex, unsigned int vItemID, int vType )
{
	CItemBoxToolkit tBoxToolkit(this);
	return tBoxToolkit.ComputeItemNum( vIndex, vItemID, vType );
}

bool CItemBox::Space( int* pItemID, int* pNumber, int vNumber )
{
	LK_ASSERT( pItemID != NULL && pNumber != NULL, return false );

	// ����ո�����
	CItemBoxToolkit tBoxToolkit(this);
	int tEmptyNumber = tBoxToolkit.GetLeftPileNum( (unsigned int)(-1) );

	for ( int j = 0; j < vNumber; j ++ )
	{
		if ( pItemID[ j ] == 0 )
			break;

		int tItemNumber = tBoxToolkit.GetLeftPileNum( (unsigned int)pItemID[ j ], false );

		// �����ų��Ѵ��ڵ����ṩ�Ŀ�λ�󣬻��ж��ٸ�������Ҫ����
		pNumber[ j ] = std::max( pNumber[ j ] - tItemNumber, 0 );
	}

	int tSlotNumber = 0;
	// ����ʣ�µĵ�����Ҫ���ٸ���λ
	for ( int j = 0; j < vNumber; j ++ )
	{
		if ( pItemID[ j ] == 0 )
			break;

		CTplItem* tpItem = (CTplItem*) CDataStatic::SearchTpl( pItemID[ j ] );
		if ( tpItem == NULL )
			break;

		tSlotNumber += pNumber[ j ] / tpItem->mPileLimit;

		// �����Ҫ���������ǵ������ߵ�����������ô��Ҫ���һ����λ
		if ( pNumber[ j ] % tpItem->mPileLimit > 0 )
			tSlotNumber ++;
	}

	// �����λ����Ҫ�Ŀ�λ��
	if ( tEmptyNumber >= tSlotNumber )
		return true;

	return false;
}

// �ýӿ�Ч���е�ͣ��Ⱥ������Ż���
bool CItemBox::Space( unsigned int vItemID, unsigned int vNumber )
{
	CItemBoxToolkit tBoxToolkit(this);
	return tBoxToolkit.GetLeftPileNum( vItemID ) >= (int)vNumber;
}

int CItemBox::AddKitBag( int nIndex, int nNewKitBagID, int &rOldKitBagObjID, int nNewKitBagObjID )
{ 
	if ( nIndex < 0 || nIndex >= mKitBagIndex )
	{
		return -1;
	}

	// TODO::����ģ���ȡ������С	
	CTplItem *tpTplItem =    ( CTplItem * )CDataStatic::SearchTpl( nNewKitBagID );
	LK_ASSERT( tpTplItem != NULL, return -1 );
	if ( tpTplItem->mItemType != CTplItem::ITEM_KITBAG )
	{
		return -1;
	}
	CTplKitBag *tpNewKitBag =( CTplKitBag * )tpTplItem;	

	int tOldKitBagIndexNum = 0;

	if ( mKitbag[nIndex] != INVALID_OBJ_ID )
	{
		CItemKitBag *tpItemKitBag = ( CItemKitBag * )CSceneObjManager::GetSingleton().GetObject( mKitbag[nIndex] );
		LK_ASSERT( tpItemKitBag != NULL, return -1 )
		CTplKitBag *tpOldKitBag = ( CTplKitBag * )CDataStatic::SearchTpl( tpItemKitBag->GetItemID() );
		LK_ASSERT( tpOldKitBag != NULL, return -1 )		
		tOldKitBagIndexNum = tpOldKitBag->mIndexNum;
	}

	// �õ���չ�����е���Ʒ����
	int nItemCount = 0;
	GetItemCountInBag(BAGTYPE_KITBAG, nIndex, nItemCount);
	if (nItemCount > 0 && tpNewKitBag->mIndexNum < tOldKitBagIndexNum )
	{
		return ERR_KITBAG_CANNOTSWAP;		
	}	

	if ( mReleaseIndex + tpNewKitBag->mIndexNum - tOldKitBagIndexNum > BOX_LIMIT  )
	{
		return ERR_KITBAG_CANNOTADD;
	}

	//mReleaseIndex += tpNewKitBag->mIndexNum - tOldKitBagIndexNum;

	rOldKitBagObjID =	mKitbag[nIndex];
	mKitbag[nIndex] = nNewKitBagObjID;	 
	return SUCCESS;						
}

// ȡ�±���
int CItemBox::TakeKitBag( int nKitBagIndex, int &rKitBagObjID )
{
	int tCount = 0;
	int tRet = GetItemCountInBag( BAGTYPE_KITBAG, nKitBagIndex, tCount );
	if ( tRet != SUCCESS )
	{
		return tRet;
	}

	if ( tCount > 0 )
	{
		return ERR_KITBAG_TAKEKITBAG_NOTEMPTY; 
	}

	rKitBagObjID = mKitbag[nKitBagIndex];
	mKitbag[nKitBagIndex] = INVALID_OBJ_ID;
	return SUCCESS;
}

int CItemBox::GetKitBagIDByIndex( int nIndex )
{
	if ( nIndex >= 0 && nIndex < mKitBagIndex )
	{
		return mKitbag[nIndex];
	}
	return INVALID_OBJ_ID;
}


int  CItemBox::GetItemTotalCount(int nItemID)
{
	ITEMNUMBERPAIR::iterator iter = mItemPair.find(nItemID);

	return iter != mItemPair.end() ? iter->second : 0;
}

void CItemBox::ResetPair( int vItemID, int vNumber)
{
	ITEMNUMBERPAIR::iterator iter = mItemPair.find(vItemID);
	if ( iter != mItemPair.end())
	{
		iter->second += vNumber;
		if (iter->second <= 0) 
		{
			mItemPair.erase(iter);
		}
	}else
	{
		if ( vNumber > 0)
		{
			mItemPair.insert(ITEMNUMBERPAIR::value_type(vItemID, vNumber));
		}
	}
}

int CItemBox::RemoveItem( unsigned int vIndex, unsigned int vNumber /*= 0xFFFF*/ )
{
	if ( operator []( vIndex ) == INVALID_OBJ_ID )
		return ERROR_REMOVEITEM_ITEMNOTEXIST;

	if ( vNumber == (unsigned int)~0 )
	{
		CSceneObjManager::GetSingletonPtr()->DestroyObject ( operator []( vIndex ) );
		operator []( vIndex ) = INVALID_OBJ_ID;
		return ERROR_REMOVEITEM_SUCCESS;
	}	

	CItemObject* pItemObj =  (CItemObject*) CSceneObjManager::GetSingletonPtr()->GetObject( operator []( vIndex ) );
	LK_ASSERT( pItemObj != NULL, return ERROR_OBJECT_NOTFOUND ) ;

	if ( vNumber > pItemObj->GetItemNum() )
	{
		return ERROR_REMOVEITEM_ITEMNOTEXIST;
	}

	ResetPair( pItemObj->GetItemID(), -vNumber);

	pItemObj->SetItemNum( std::max( 0,(int)( pItemObj->GetItemNum() - vNumber ) ) );
	if ( pItemObj->GetItemNum() == 0 )
	{
		CSceneObjManager::GetSingletonPtr()->DestroyObject ( operator []( vIndex ) );
		operator []( vIndex ) = INVALID_OBJ_ID;
		return ERROR_REMOVEITEM_SUCCESS;
	}

	return ERROR_REMOVEITEM_SUCCESS;
}

int CItemBox::InsertItem( CItemObject* pItem, int vIndex )
{
	/*if ( vIndex < 0 || vIndex >= ( int )mReleaseIndex )
	{
	return -1;
	}*/

	// TODO::������������Ƿ���Ч(��������ʱ��)
	if ( !CheckIndexValid( vIndex, true ) )
	{
		return 	ERROR_MOVEITEM_DESINVALID;
	}

	if( operator[]( vIndex ) != INVALID_OBJ_ID )
	{
		return	ERROR_MOVEITEM_DESINVALID;
	}	  
	operator[]( vIndex ) = pItem->get_id();


	ResetPair( pItem->GetItemID(), pItem->GetItemNum() );
	return SUCCESS;	
}

int CItemBox::InsertItem( CItemObject* pItem, int *vIndex, int *vNumber, int &vLen )
{
	// �������ģ�����,���ǵ��߽���ʱ���ǿ�,˵��û��ע��
	if ( pItem == NULL )
		return ERROR_ITEM_ITEMNOTREGISTER;

	// �������ģ���Ҳ���
	CTplItem* tpItem = (CTplItem*) CDataStatic::SearchTpl( pItem->GetItemID() );
	if ( tpItem == NULL )
		return ERROR_ITEM_DATANOTEXIST;

	// ���߸���Ϊ��
	if( pItem->GetItemNum() == 0 || vLen != 0 || (int)pItem->GetItemNum() > tpItem->mPileLimit * BOX_LIMIT )
	{
		return ERROR_INSERTITEM_INVALIDNUM;
	}

	int nInsertingNumber  = pItem->GetItemNum();
	int nInsertingItemID  = pItem->GetItemID();

	// ���ռ乻����
	if ( Space( pItem->GetItemID(), pItem->GetItemNum() ) == false )
		return ERROR_INSERTITEM_NOSPACE;

	CItemObject* pItemObj = NULL;
	int tEmpty[ BOX_LIMIT ] = { -1 };
	int tEmptyNum = 0;

	CItemBoxToolkit tBoxToolkit(this);
	int nInsertedNum = 0;

	for ( unsigned int i = 0; i < mReleaseIndex; i++ )
	{
		nInsertedNum = tBoxToolkit.InsertItem( i, pItem, tpItem );
		// ���������һ�ѣ�˵���ø����ǿյ�
		if( nInsertedNum == tpItem->mPileLimit )
		{
			tEmpty[ tEmptyNum ] = i;
			tEmptyNum++;
		}
		else if( nInsertedNum > 0 ) // �ڷǿո����ϲ���
		{
			vIndex[ vLen ] = i;
			vNumber[ vLen ] = nInsertedNum;
			vLen++;

			if( pItem->GetItemNum() == 0 )
			{
				ResetPair(nInsertingItemID, nInsertingNumber);
				return ERROR_INSERTITEM_SUCCESS;
			}
		}
		if ( vLen >= BOX_LIMIT )
			break;
	}

	// TODO:��������
	for( int i = 0; i < mKitBagIndex; ++i )
	{
		int tBeginIndex = 0;
		int tEndIndex = 0;	

		// TODO::��������ʱ��  		
		if ( CheckKitBagExpiredTime( i ) )
		{
			continue;
		}

		int tRet = GetKitBagIndexRange( BAGTYPE_KITBAG, i, tBeginIndex, tEndIndex );
		if ( tRet != SUCCESS )
		{
			continue;
		}	

		for( int j = tBeginIndex; j <= tEndIndex; ++j )
		{
			nInsertedNum = tBoxToolkit.InsertItem( j, pItem, tpItem );
			// ���ȫ�����룬˵���ø����ǿյ�
			if( nInsertedNum == tpItem->mPileLimit )
			{
				tEmpty[ tEmptyNum ] = j;
				tEmptyNum++;
			}
			else if( nInsertedNum > 0 ) // �ڷǿո����ϲ���
			{
				vIndex[ vLen ] = j;
				vNumber[ vLen ] = nInsertedNum;
				vLen++;	

				if( pItem->GetItemNum() == 0 )
				{
					ResetPair(nInsertingItemID, nInsertingNumber);
					return ERROR_INSERTITEM_SUCCESS;
				}
			}
			if ( vLen >= BOX_LIMIT )
				break;
		}
	}

	for( int i = 0; i < tEmptyNum; i++ )
	{
		if ( tEmpty[ i ] == -1 )
			break;
		pItemObj = GetItemObjPtr ( tEmpty[ i ] );

		if ( pItemObj == NULL )
		{
			vIndex[ vLen ] = tEmpty[ i ];
			vNumber[ vLen ] = std::min( tpItem->mPileLimit, (int)pItem->GetItemNum() );
			vLen++;

			if ( (int)pItem->GetItemNum() > tpItem->mPileLimit )
			{
				CItemObject* tpNewItem = CItemRunTime::Clone( pItem->GetItemID(), tpItem->mPileLimit );
				LK_ASSERT(tpNewItem != NULL, continue);				

				tpNewItem->SetGUID();
				// ��������Ʒ��ԭ��Ʒ��״̬һ��
				tpNewItem->SetBindStatus( pItem->GetBindStatus() );

				operator []( tEmpty[ i ] ) = tpNewItem->get_id();
				pItem->SetItemNum( pItem->GetItemNum() - tpItem->mPileLimit );				
				continue;
			}
			else
			{
				operator []( tEmpty[ i ] )  = pItem->get_id ();
				break;
			}

			if ( vLen >= BOX_LIMIT )
				break;
		}
	}

	ResetPair(nInsertingItemID, nInsertingNumber);
	return ERROR_INSERTITEM_SUCCESS;
}


// ɾ������
CItemObject* CItemBox::EraseItem( int vSrcIndex, int vNumber )
{
	CItemObject* tpSrcItem = GetItemObjPtr( vSrcIndex  ) ;
	if ( tpSrcItem == NULL )
		return NULL;

	int nRemovingItemID = tpSrcItem->GetItemID();

	vNumber = ( vNumber == -1 ) ? tpSrcItem->GetItemNum() : vNumber;

	if ( vNumber <= 0 )
	{
		return NULL;
	}

	tpSrcItem->SetItemNum( std::max( 0, (int)( tpSrcItem->GetItemNum() - vNumber ) ) );
	if ( tpSrcItem->GetItemNum() == 0 )
	{
		operator []( vSrcIndex ) = INVALID_OBJ_ID;
		tpSrcItem->SetItemNum( vNumber );

		ResetPair( nRemovingItemID, -vNumber);
		return tpSrcItem;
	}

	ResetPair( nRemovingItemID, -vNumber);

	// ������߻���ʣ�࣬��ô�����еĵ��߲���"��"����, 
	// ��Ҫͨ���õ��߿�¡һ��һģһ���ĵ��ߣ����������Ƕ���������
	//char tItemBuffer[ ITEMOBJ_BUFFLEN ] = { 0 };
	//char* tpBuffer = tItemBuffer;
	//tpSrcItem->GetItemBinaryBuffer( tItemBuffer, vNumber );
	//return CItemRunTime::CloneFromBinary( tpBuffer );
	PBItemObject tPBObject;
	tpSrcItem->GetItemBinaryBuffer2( &tPBObject, vNumber );
	PBItemObject *tpPBObject = &tPBObject;
	return CItemRunTime::CloneFromBinary2( tpPBObject );
} 



int CItemBox::Move( unsigned int vSrcIndex, unsigned int vDesIndex, CItemBox& rDesBox, unsigned int vNumber , int &rMoveNum )
{

	/*if ( &rDesBox == NULL )
	{
	return ERROR_MOVEITEM_ITEMNOTEXIST;
	}*/
	//if ( vSrcIndex < 0 || vDesIndex < 0 )
	//{
	//	LOG_ERROR( "pro", "[%s:%d] src index %d or dst index %d invalid", __FUNCTION__, __LINE__, vSrcIndex, vDesIndex );
	//	return ERROR_MOVEITEM_ITEMNOTEXIST;
	//}

	// ��֤����
	if ( ( !CheckIndexValid( vSrcIndex ) ) || ( !rDesBox.CheckIndexValid( vDesIndex ) ) )
	{
		LOG_ERROR( "pro", "[%s:%d] src index %d or dst index %d invalid", __FUNCTION__, __LINE__, vSrcIndex, vDesIndex );
		return ERROR_MOVEITEM_DESINDEXINVALID;
	}

	// ��������ʱ����
	EBagType tDesBagType;
	int		 tDesKitBagIndex = 0;
	int tRet = rDesBox.GetBagTypeByIndex( vDesIndex, tDesBagType, tDesKitBagIndex );
	if ( tRet != SUCCESS )
	{
		return ERROR_MOVEITEM_ITEMNOTEXIST;
	}

	if ( tDesBagType == BAGTYPE_KITBAG && rDesBox.CheckKitBagExpiredTime( tDesKitBagIndex ) )
	{
		return ERROR_MOVEITEM_KITBAGINVALID;		
	}

	bool bSrcBoxExpired = false;
	int tSrcKitbagIndex = -1;
	EBagType tSrcKitbagType;
	tRet = GetBagTypeByIndex( vSrcIndex, tSrcKitbagType, tSrcKitbagIndex );
	if ( tRet != SUCCESS )
	{
		return ERROR_MOVEITEM_ITEMNOTEXIST;
	}

	if ( tSrcKitbagType == BAGTYPE_KITBAG && CheckKitBagExpiredTime( tSrcKitbagIndex ) )
	{
		bSrcBoxExpired = true;
	}



	/*if ( vSrcIndex >= mReleaseIndex ||  vDesIndex >= rDesBox.mReleaseIndex  )
	{
	LOG_ERROR( "pro", "[%s:%d] src index %d or dst index %d invalid", __FUNCTION__, __LINE__, vSrcIndex, vDesIndex );
	return ERROR_MOVEITEM_ITEMNOTEXIST;
	}*/

	CItemObject* tpSrcItem = GetItemObjPtr( vSrcIndex );
	CItemObject* tpDesItem = rDesBox.GetItemObjPtr( vDesIndex );

	if ( tpSrcItem == NULL )
		return ERROR_MOVEITEM_ITEMNOTEXIST;

	if ( tpSrcItem->GetLockStatus() != LOCKTYPE_NONE )
		return ERROR_MOVEITEM_ITEMLOCKED;

	// �ƶ�������������Ʒ����
	if ( vNumber > tpSrcItem->GetItemNum() )
	{
		return ERROR_MOVEITEM_SRCINVALID;
	}

	// ʵ���ƶ�����Ʒ����
	rMoveNum = 0;

	// �����ͬλ�õ���
	if ( this == &rDesBox )
	{
		if ( vSrcIndex == vDesIndex )
			return ERROR_MOVEITEM_SAMEINDEX;

		if ( tpDesItem != NULL )
		{
			if ( tpDesItem->GetLockStatus() != LOCKTYPE_NONE )
				return ERROR_MOVEITEM_ITEMLOCKED;

			CTplItem* tpItem = (CTplItem*) CDataStatic::SearchTpl( tpDesItem->GetItemID() );
			if ( tpItem == NULL )
				return ERROR_MOVEITEM_ITEMNOTEXIST;

			// �����ͬһ�ֵ���
			if ( tpSrcItem->GetItemID() == tpDesItem->GetItemID() && tpSrcItem->GetBindStatus() == tpDesItem->GetBindStatus() )
			{
				unsigned int tUpper = tpItem->mPileLimit - tpDesItem->GetItemNum();
				if ( tUpper == 0 )
				{
					// Ŀ��װ������, ��ô���߻�λ
					if ( vNumber == tpSrcItem->GetItemNum() )
					{
						operator[ ]( vSrcIndex ) = tpDesItem->get_id();
						rDesBox[ vDesIndex ] = tpSrcItem->get_id();

						// ��¼�ƶ�������
						rMoveNum = tpSrcItem->GetItemNum();
					}
					else
					{
						return ERROR_MOVEITEM_SRCINVALID;
					}

					return ERROR_MOVEITEM_SUCCESS;
				}

				unsigned int tMoveNumber = std::min( tpSrcItem->GetItemNum(), std::min( tUpper, vNumber ) );

				tpSrcItem->SetItemNum( tpSrcItem->GetItemNum() - tMoveNumber );
				tpDesItem->SetItemNum( tpDesItem->GetItemNum() + tMoveNumber );

				// ��¼�ƶ�������				
				rMoveNum = tMoveNumber;

				if ( tpSrcItem->GetItemNum() == 0 )
				{
					CSceneObjManager::GetSingletonPtr()->DestroyObject( tpSrcItem->get_id() );
					operator[ ] ( vSrcIndex ) = INVALID_OBJ_ID;
				}

				return ERROR_MOVEITEM_SUCCESS;
			}
		}

		// �������ͬһ�ֵ���
		if ( tpDesItem == NULL || tpSrcItem->GetItemID() != tpDesItem->GetItemID() || tpSrcItem->GetBindStatus() != tpDesItem->GetBindStatus() )
		{
			// ���߻�λ
			if ( vNumber == tpSrcItem->GetItemNum() )
			{
				if ( bSrcBoxExpired == true && tpDesItem != NULL )
				{
					return ERROR_MOVEITEM_KITBAGINVALID;
				}

				operator[ ] ( vSrcIndex ) = tpDesItem == NULL ? INVALID_OBJ_ID : tpDesItem->get_id( );
				rDesBox[ vDesIndex ] = tpSrcItem->get_id( );

				// ��¼�ƶ�������
				rMoveNum = tpSrcItem->GetItemNum();
			}
			else if ( vNumber < tpSrcItem->GetItemNum() )
			{
				if ( tpDesItem == NULL )
				{
					CItemObject* pItemObj = CItemRunTime::Clone( tpSrcItem->GetItemID(), tpSrcItem->GetItemNum() );
					LK_ASSERT( pItemObj != NULL, return ERROR_MOVEITEM_SRCINVALID );
					rDesBox[ vDesIndex ] = pItemObj->get_id ();
					//pItemObj->Copy( tpSrcItem );
					pItemObj->SetBindStatus( tpSrcItem->GetBindStatus() );
					pItemObj->SetItemNum( vNumber );
					tpSrcItem->SetItemNum( tpSrcItem->GetItemNum() - vNumber );

					// ��¼�ƶ�������
					rMoveNum = vNumber;
				}
				else
					return ERROR_MOVEITEM_DESINVALID;
			}
			else
				return ERROR_MOVEITEM_SRCINVALID;
		}
	}

	// �������ͬλ�õ���
	if ( this != &rDesBox )
	{
		if ( tpDesItem != NULL )
		{
			CTplItem* tpItem = (CTplItem*) CDataStatic::SearchTpl( tpDesItem->GetItemID() );
			if ( tpItem == NULL )
				return ERROR_MOVEITEM_ITEMNOTEXIST;

			// �����ͬһ�ֵ���
			if ( tpSrcItem->GetItemID() == tpDesItem->GetItemID() && tpSrcItem->GetBindStatus() == tpDesItem->GetBindStatus() )
			{
				int tUpper		= tpItem->mPileLimit - tpDesItem->GetItemNum();

				// ���߻�λ
				if ( tUpper == 0 )
				{	
					if ( vNumber != tpSrcItem->GetItemNum() )
					{
						return	ERROR_MOVEITEM_SRCINVALID;
					}
					int tNumber = tpSrcItem->GetItemNum();
					tpSrcItem->SetItemNum( tpDesItem->GetItemNum() );
					tpDesItem->SetItemNum( tNumber );

					// ��¼�ƶ�������
					rMoveNum = tNumber;

					ResetPair(tpSrcItem->GetItemID(), tpSrcItem->GetItemNum() - tNumber);
					rDesBox.ResetPair(tpSrcItem->GetItemID(), tNumber - tpSrcItem->GetItemNum() );

					return 	ERROR_MOVEITEM_SUCCESS;									
				}
				int tRemain		= std::max( 0, (int)( tUpper ) );
				int tMoveNumber	= std::min( ( unsigned int )tRemain , std::min( vNumber, tpSrcItem->GetItemNum() ) );
				tpSrcItem->SetItemNum( tpSrcItem->GetItemNum() - tMoveNumber );
				tpDesItem->SetItemNum( tpDesItem->GetItemNum() + tMoveNumber );

				// ��¼�ƶ�������
				rMoveNum = tMoveNumber;

				ResetPair(tpSrcItem->GetItemID(), -tMoveNumber);
				rDesBox.ResetPair(tpSrcItem->GetItemID(), tMoveNumber);

				if ( tpSrcItem->GetItemNum() == 0 )
				{
					CSceneObjManager::GetSingletonPtr()->DestroyObject( tpSrcItem->get_id () );
					operator[ ] ( vSrcIndex ) = INVALID_OBJ_ID;
				}
			}
		}

		// �������ͬһ�ֵ���
		if ( tpDesItem == NULL || tpSrcItem->GetItemID() != tpDesItem->GetItemID() || tpSrcItem->GetBindStatus() != tpDesItem->GetBindStatus() )
		{
			if ( vNumber < tpSrcItem->GetItemNum() && vNumber > 0 )
			{
				// ԭ��ƷҪ�����
				if ( rDesBox.GetItemObjPtr( vDesIndex  ) != INVALID_OBJ_ID )
				{
					return ERROR_MOVEITEM_DESINVALID;
				}
				CItemObject *tpMoveItem = CItemRunTime::Clone( tpSrcItem->GetItemID(), vNumber );
				LK_ASSERT( tpMoveItem != NULL, return ERROR_MOVEITEM_SRCINVALID );
				tpMoveItem->SetItemNum( vNumber );
				tpMoveItem->SetBindStatus( tpSrcItem->GetBindStatus() );
				tpSrcItem->SetItemNum( tpSrcItem->GetItemNum() - vNumber );
				rDesBox[ vDesIndex ] = tpMoveItem->get_id();

				// ��¼�ƶ�������
				rMoveNum = vNumber;

				ResetPair(tpSrcItem->GetItemID(), - vNumber);
				rDesBox.ResetPair(tpSrcItem->GetItemID(), vNumber);
				return ERROR_MOVEITEM_SUCCESS;
			}

			if ( bSrcBoxExpired == true && tpDesItem != NULL )
			{
				return ERROR_MOVEITEM_KITBAGINVALID;
			}

			// ���߻�λ
			operator[ ]( vSrcIndex ) = tpDesItem == NULL ? INVALID_OBJ_ID : tpDesItem->get_id ();
			rDesBox[ vDesIndex ] =  tpSrcItem->get_id();

			// ��¼�ƶ�������				
			rMoveNum = tpSrcItem->GetItemNum();

			ResetPair(tpSrcItem->GetItemID(), -tpSrcItem->GetItemNum() );
			rDesBox.ResetPair(tpSrcItem->GetItemID(), tpSrcItem->GetItemNum() );
			if ( tpDesItem != NULL )
			{
				ResetPair(tpDesItem->GetItemID(), tpDesItem->GetItemNum() );
				rDesBox.ResetPair(tpDesItem->GetItemID(), -tpDesItem->GetItemNum() );
			}
		}
	}

	return ERROR_MOVEITEM_SUCCESS;
}

// �Ƿ���ĳ�����͵���Ʒ
int CItemBox::HasItemOfCertainType( int nType, int &rNum, int &rIndex, int nFuncType /* = 0 */ )
{		
	CItemBoxToolkit tBoxToolkit(this);

	rNum = 0;
	for ( unsigned int i = 0; i < mReleaseIndex; i ++ )
	{
		if( tBoxToolkit.GetCertainTypeItemNum( i, nType, nFuncType ) > 0 )
		{
			if ( rIndex == -1 )
			{
				rIndex = i;	
			}			
			rNum++;
		}
	}

	// ��鱳��
	for ( int i = 0; i < mKitBagIndex; ++i )
	{
		int tBeginIndex = 0;
		int tEndIndex	= 0;
		int tRet = GetKitBagIndexRange( BAGTYPE_KITBAG, i, tBeginIndex, tEndIndex );
		if ( tRet != SUCCESS )
		{
			continue;
		}

		for ( int j = tBeginIndex; j <= tEndIndex; j++ )
		{
			if( tBoxToolkit.GetCertainTypeItemNum( j, nType, nFuncType ) > 0  )	
			{
				if ( rIndex == -1 )
				{
					rIndex = j;
				}				
				rNum++;
			}
		}					
	}
	return SUCCESS;			
}

// ��ȡ��Ʒ����
int CItemBox::GetItemType( int vSrcInde, int &rType )
{
	CItemObject* tpItemObj = GetItemObjPtr( vSrcInde );		
	if ( tpItemObj == NULL )
	{
		return -1;
	}
	CTplItem *tpItem = ( CTplItem * )CDataStatic::SearchTpl( tpItemObj->GetItemID() );
	if ( tpItem == NULL )
	{
		return -1;
	}
	rType = tpItem->mItemType;
	return SUCCESS;	
}

bool CItemBox::CreateFromTlv2( PBItemBox* pBuffer )
{
	mReleaseIndex = pBuffer->releaseindex( );

	// ��ֹԽ��
	if ( mReleaseIndex >= BOX_LIMIT )
	{
		mReleaseIndex = BOX_LIMIT - 1;
	}

	for ( int i = 0; i < MAX_KITBAG_NUM && i < pBuffer->kitbag_size(); ++i )
	{
		PBItemObject* tpItemKitBag = pBuffer->mutable_kitbag( i );
		mKitLocked[i] = pBuffer->kitlocked(i);
		if ( tpItemKitBag->itemid() == 0 )
		{
			continue;
		}
		CItemObject *tpItemObj = CItemRunTime::CloneFromBinary2( tpItemKitBag );
		if ( tpItemObj == NULL )
		{
			LOG_ERROR( "pro", "Item Clone fuction didn't register. item id %d", tpItemKitBag->itemid() );
			return false;
		}
		mKitbag[i] = tpItemObj->get_id();
	}

	if (CItemList<BOX_LIMIT>::CreateFromTlv2( pBuffer ) == true)
	{
		for ( unsigned int i = 0; i < BOX_LIMIT; i ++ )
		{
			CItemObject* tpItemObj = GetItemObjPtr( i );	
			if ( tpItemObj == NULL ) continue;

			ResetPair(tpItemObj->GetItemID(), tpItemObj->GetItemNum());
		}

		return true;
	}

	return false;
}

void CItemBox::GetTlvBuffer2( PBItemBox* pBuffer, int tStart, int tEnd )
{	
	// ��ֹԽ��
	if ( mReleaseIndex >= BOX_LIMIT )
	{
		mReleaseIndex = BOX_LIMIT - 1;
	}

	pBuffer->set_releaseindex( mReleaseIndex );


	for ( int i = 0; i < mKitBagIndex; ++i )
	{
		int tKitBagID = GetKitBagIDByIndex( i );
		pBuffer->add_kitlocked( mKitLocked[i] );

		PBItemObject* pItemKitBag = pBuffer->add_kitbag( );
		CItemObject *tpItemObj = ( CItemObject * )CSceneObjManager::GetSingleton().GetObject( tKitBagID );
		if ( tpItemObj == NULL )
		{
			pItemKitBag->set_itemid( 0 );
			continue;
		}
		tpItemObj->GetItemBinaryBuffer2( pItemKitBag, 1 );
	}

	CItemList<BOX_LIMIT>::GetTlvBuffer2( pBuffer, tStart, tEnd );
}

int CItemBox::GetTlvSize2( )
{
	return 0;
}

// ***************************************************************
//  Function:	 GetKitBagIndexLimit
//  Description: ��ȡָ��λ�ñ����ĸ�������
//	Input:		 int nKitBagIndex ������������е�����	
//	OutPut:			
//	Return:			
//	Others:
//  Date:	 12/16/2009	
// 
// ***************************************************************
int CItemBox::GetKitBagIndexLimit( int nKitBagIndex, int &rNum )
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	rNum = 0;
	CItemKitBag *tpItemKitBag =  GetKitBagItemByIndex( nKitBagIndex );
	if ( tpItemKitBag == NULL )
	{
		return -1;
	}

	CTplKitBag *tpTplKitBag  = ( CTplKitBag * )CDataStatic::SearchTpl( tpItemKitBag->GetItemID() );
	if ( tpTplKitBag == NULL )
	{
		return -1;
	}	

	rNum = tpTplKitBag->mIndexNum;
	return SUCCESS;
}							    

// ***************************************************************
//  Function:	 GetBagTypeByIndex
//  Description: ��ȡָ���������ڵİ�������
//	Input:		 int nIndex ������������е�����
//	Input:		 EBagType &rSlotType �������ͻ�����( �������ֿ� )���Ǳ���
//	Input:		 int &rBagIndex		 ����������Ϊ����ʱ��ʾ�ڼ�����λ�ı���		
//	OutPut:			
//	Return:			
//	Others:
//  Date:	 12/16/2009	
// 
// *************************************************************** 
int CItemBox::GetBagTypeByIndex( int nIndex, EBagType &rSlotType, int &rBagIndex )
{
	if ( nIndex < 0 || nIndex >= BOX_LIMIT )
	{
		return -1;
	}

	rBagIndex = 0;	
	if ( nIndex >=0 && (unsigned int)nIndex < mReleaseIndex )
	{
		rSlotType = BAGTYPE_BASEBAG;
		return SUCCESS;
	}

	rSlotType = BAGTYPE_KITBAG;	
	rBagIndex = ( nIndex - mReleaseIndex )/MAXKITBAGINDEXNUM;

	/*if ( ( nIndex - mReleaseIndex )%MAXKITBAGINDEXNUM > 0 )
	{
	++rBagIndex;
	}*/			

	if ( rBagIndex >= mKitBagIndex )
	{
		return -1;
	}

	int tNum = 0;

	int tRet = GetKitBagIndexLimit( rBagIndex, tNum );
	if ( tRet != SUCCESS )
	{
		return -1;
	}

	if ( (unsigned int)nIndex >= ( mReleaseIndex + MAXKITBAGINDEXNUM*rBagIndex + tNum ) )
	{
		return -1;
	}	
	return SUCCESS;	
}

// ***************************************************************
//  Function:	 CheckKitBagExpiredTime
//  Description: ���ĳ��λ�õı����Ѿ�����
//	Input:		 int nKitBagIndex �������ڵ���λ����	 
//	OutPut:			
//	Return:			
//	Others:
//  Date:	 12/16/2009	
// 
// *************************************************************** 
bool CItemBox::CheckKitBagExpiredTime( int nKitBagIndex )
{ 
	CItemKitBag *tpItemKitBag = GetKitBagItemByIndex( nKitBagIndex );
	if ( tpItemKitBag == NULL )
	{
		return true;
	}

	if ( (tpItemKitBag->GetInvalidTime() < (unsigned int)time( NULL ) )
		&& (tpItemKitBag->GetInvalidTime() >(unsigned int)( 0 ) ) )
	{
		return true;
	}

	return false;
}

// ***************************************************************
//  Function:	 GetKitBagItemByIndex
//  Description: ��ȡָ����λ�ı�����Ʒ
//	Input:		 int nKitBagIndex �������ڵ���λ����	 
//	OutPut:			
//	Return:			
//	Others:
//  Date:	 12/16/2009	
// 
// *************************************************************** 
CItemKitBag *CItemBox::GetKitBagItemByIndex( int nKitBagIndex )
{
	if ( nKitBagIndex >= mKitBagIndex || nKitBagIndex < 0 )
	{
		LOG_ERROR( "pro","item index( %d ) over limit( %d )  ", nKitBagIndex, mKitBagIndex );
		return NULL;
	}

	if ( mKitbag[nKitBagIndex] == INVALID_OBJ_ID )
	{
		//LOG_ERROR( "pro","there is no item in index( %d )  ", nKitBagIndex );
		return NULL;
	}

	CItemObject *tpItemObj = ( CItemObject * )CSceneObjManager::GetSingleton().GetObject( mKitbag[nKitBagIndex] );			
	if ( tpItemObj == NULL )
	{
		return NULL;
	}

	CTplItem *tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tpItemObj->GetItemID() );
	if ( tpTplItem == NULL )
	{
		return NULL;
	}

	if ( tpTplItem->mItemType != CTplItem::ITEM_KITBAG )
	{
		return NULL;
	}
	return ( CItemKitBag * )tpItemObj;
}

bool CItemBox::ChangeKitBagItemByIndex(int index, int itemid,int isBind)
{
	if ( index >= mKitBagIndex || index < 0 )
	{
		LOG_ERROR( "pro","item index( %d ) over limit( %d )  ", index, mKitBagIndex );
		return FALSE;
	}

	if ( mKitbag[index] == INVALID_OBJ_ID )
	{
		//LOG_ERROR( "pro","there is no item in index( %d )  ", nKitBagIndex );
		return FALSE;
	}
	CItemObject *tpItemObj = ( CItemObject * )CSceneObjManager::GetSingleton().GetObject( mKitbag[index] );			
	if ( tpItemObj == NULL )
	{
		return FALSE;
	}
	tpItemObj->SetItemID(itemid);
	if (isBind == ITEM_BINDSTATUS_BINDED)
	{
		tpItemObj->SetBindStatus(ITEM_BINDSTATUS_BINDED);
	}
	return TRUE;

}

// ***************************************************************
//  Function:	 CheckIndexValid
//  Description: ��������Ƿ���Ч
//	Input:		 int nIndex �������������
//	OutPut:		 	
//	Return:			
//	Others:
//  Date:	 12/16/2009	
// 
// *************************************************************** 
bool CItemBox::CheckIndexValid( int nIndex, bool bExceptExpiredKitbag /* = false */ )
{
	EBagType tBagType;
	int		 tBagIndex;
	int tRet = GetBagTypeByIndex( nIndex, tBagType, tBagIndex );
	if ( tRet != SUCCESS )
	{
		return false;
	}

	if ( bExceptExpiredKitbag == false || tBagType == BAGTYPE_BASEBAG )
	{
		return true;
	}

	if ( CheckKitBagExpiredTime( tBagIndex ) )
	{	
		return false;
	}				
	return true;
	/*if ( tBagType == BAGTYPE_BASEBAG )
	{
	return true;
	}

	if ( tBagType != BAGTYPE_KITBAG )
	{								
	return false;
	}

	CItemKitBag *tpItemKitBag = GetKitBagItemByIndex( tBagIndex );
	if ( tpItemKitBag == NULL )
	{	 
	return false;
	}	*/	
}

// ***************************************************************
//  Function:	 GetKitBagIndexRange
//  Description: ��ȡְλλ�ñ�������ȡʼĩλ��
//	Input:		 EBagType emSlotTyp ��������
//	Input:		 int nBagIndex		��������λ����
//	Input:		 int &rBeginIndex	ָ����λ��������ʼ����( �ڴ���е����� )
//	Input:		 int &rEndIndex		ָ����λ���������һ������( �ڴ���е����� )
//	OutPut:		 	
//	Return:			
//	Others:
//  Date:	 12/16/2009	
// 
// *************************************************************** 
int CItemBox::GetKitBagIndexRange(  EBagType emSlotTyp, int nBagIndex, int &rBeginIndex, int &rEndIndex )
{
	if ( emSlotTyp == BAGTYPE_BASEBAG )
	{
		rBeginIndex = 0;
		rEndIndex = mReleaseIndex - 1;
		return SUCCESS;
	}	

	if ( emSlotTyp != BAGTYPE_KITBAG )
	{
		return -1;
	}

	int tNum = 0;
	int tRet = GetKitBagIndexLimit( nBagIndex, tNum );
	if ( tRet != SUCCESS )
	{
		return -1;	
	}

	rBeginIndex = mReleaseIndex + nBagIndex*MAXKITBAGINDEXNUM;
	rEndIndex	= mReleaseIndex + nBagIndex*MAXKITBAGINDEXNUM + tNum - 1; 
	return SUCCESS;
}

// ***************************************************************
//  Function:	 GetItemOfBag
//  Description: ��ȡָ��λ�ð�������Ʒ��PB�ṹ
//	Input:		 EBagType emSlotType ��������(��ͨ�����Ǳ���)
//	Input:		 int nBagIndex		 ��������λ����(������)
//	Input:		 PBItemBox &rItemBox ָ����λ��������ʼ����( �ڴ���е����� )
//	OutPut:		 	
//	Return:			
//	Others:
//  Date:	 12/16/2009	
// 
// *************************************************************** 
int CItemBox::GetItemInBag( EBagType emSlotType, int nBagIndex, PBItemBox &rItemBox )
{			
	int tBegInIndex = 0;
	int tEndIndex	= 0;

	if ( emSlotType == BAGTYPE_BASEBAG )
	{
		tBegInIndex = 0;
		tEndIndex = mReleaseIndex - 1;
	}
	else
	{
		int tRet = GetKitBagIndexRange( emSlotType, nBagIndex, tBegInIndex, tEndIndex );
		if ( tRet != SUCCESS )
		{
			return -1;
		}
	}

	for ( int i = tBegInIndex; i <= tEndIndex; ++i )
	{
		CItemObject *tpItemObject =	 GetItemObjPtr( i );
		if ( tpItemObject == NULL )
		{
			continue;
		}
		PBItemObject *pbItem = rItemBox.add_itemobjects( );		
		tpItemObject->GetItemBinaryBuffer2( pbItem );
		pbItem->set_index( i );
	}
	return SUCCESS;
}

// ***************************************************************
//  Function:	 GetItemCountInBag
//  Description: ��ȡָ��������Ʒ����
//	Input:		 EBagType emSlotType ��������(��ͨ�����Ǳ���)
//	Input:		 int nBagIndex		 ��������λ����(������)
//	Input:		 PBItemBox &rItemBox ָ����λ��������ʼ����( �ڴ���е����� )
//	OutPut:		 	
//	Return:			
//	Others:
//  Date:	 12/16/2009	
// 
// *************************************************************** 
int CItemBox::GetItemCountInBag( EBagType emSlotType, int nBagIndex, int &rCount )
{
	int tBegInIndex = 0;
	int tEndIndex	= 0;

	if ( emSlotType == BAGTYPE_BASEBAG )
	{
		tBegInIndex = 0;
		tEndIndex = mReleaseIndex - 1;
	}
	else
	{
		int tRet = GetKitBagIndexRange( emSlotType, nBagIndex, tBegInIndex, tEndIndex );
		if ( tRet != SUCCESS )
		{
			return -1;
		}
	}
	rCount = 0;
	for ( int i = tBegInIndex; i <= tEndIndex; ++i )
	{
		CItemObject *tpItemObject =	 GetItemObjPtr( i );
		if ( tpItemObject == NULL )
		{
			continue;
		}	
		++rCount;		 		
	}	
	return SUCCESS;
}

// ������������ߣ��������Ʒ����
void CItemBox::Clear( )
{
	for ( int i = 0; i < mKitBagIndex; ++i )
	{
		if ( mKitbag[i] != INVALID_OBJ_ID )
		{
			CSceneObjManager::GetSingleton().DestroyObject( mKitbag[i] );
			mKitbag[i] = INVALID_OBJ_ID;
		}
	}

	CItemList<BOX_LIMIT>::Clear();
}
