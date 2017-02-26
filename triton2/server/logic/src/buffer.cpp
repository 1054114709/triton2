#include "stdafx.hpp"
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

// ********************************************************************** //
// CBuffObject
// ********************************************************************** //

// Buff����ֵӰ����ֵ(�̶���ֵ��ٷֱ�)
unsigned int CBuffObject::GetAffectNumber( CTemplateBuff::BUFF_FUN_TYPE vBuffType )
{
	unsigned int tValue = 0;

	CTemplateBuff* tpBuffTpl = (CTemplateBuff*) CDataStatic::SearchTpl( mBuffID );	
	for ( unsigned int i = 0; ( tpBuffTpl != NULL ) && ( i < sizeof( tpBuffTpl->mBuff ) / sizeof( tpBuffTpl->mBuff[ 0 ] ) ); i++ ) 																	
	{																				
		if ( tpBuffTpl->mBuff[ i ].mBuffFunc == 0 )									
			break;																	
		if ( tpBuffTpl->mBuff[ i ].mBuffFunc == vBuffType )		
		{																			
			tValue += tpBuffTpl->mBuff[ i ].mBuffParam[ 0 ];					
		}																			
	}

	return tValue;
}

// �õ�buff�����ü��; -1��ʾʧ�ܣ�0��ʾ�ǳ���������buff; >0��ʾ�Ǽ��������buff
int CBuffObject::GetBuffActionTime( ) 
{
	CTemplateBuff* tpBuffTpl = (CTemplateBuff*) CDataStatic::SearchTpl( mBuffID );
	if ( tpBuffTpl == NULL )
	{
		return -1;
	}

	return tpBuffTpl->mBuffActionTime;
}


void CBuffObject::ChangeParames( int vBuffID, int vIndex, int vParames )
{
	mParames[ vIndex ] = vParames;
}

void CBuffObject::ChangeParames2( int vBuffID, int vIndex, int vParames2 )
{
	mParames2[ vIndex ] = vParames2;
}



// ********************************************************************** //
// CBuffList
// ********************************************************************** //

// �õ�BuffList����ֵӰ��Ĺ̶���ֵ
unsigned int CBuffList::GetFixNumber( CTemplateBuff::BUFF_FUN_TYPE vBuffType )
{
	unsigned int tValue = 0;
	unsigned int i = 0;

	for( i = 0; i < mBuffNumber; i++ )
	{
		tValue += mBuffList[ i ].GetAffectNumber( vBuffType );
	}

	return tValue;
}

int CBuffList::GetPerNumber( CTemplateBuff::BUFF_FUN_TYPE vBuffType )
{
	int tValue = 0;
	unsigned int i = 0;

	for( i = 0; i < mBuffNumber; i++ )
	{
		tValue += mBuffList[ i ].GetAffectNumber( vBuffType );
	}

	return tValue;
}

//  �Ƿ���buff
bool CBuffList::HasBuff( int nBuffID )
{
	for( unsigned int i = 0 ; i < mBuffNumber; i++ )
	{
		if( mBuffList[i].mBuffID == (unsigned int)nBuffID )
		{
			return true;
		}
	}

	return false;
}


//////////////////////////////////////////////////////////////////////////
// Buff
//////////////////////////////////////////////////////////////////////////



// �������buff, ������ʱ��
int CBuffList::RemoveAllBuff( CEntityCharacter* pEntity )
{
	for ( unsigned int i = 0; i < mBuffNumber; i ++ )
	{
		if ( mBuffList[ i ].mBuffTimerID != INVALID_OBJ_ID )
		{
			pEntity->GetTimerReciver()->ClearTimer( mBuffList[ i ].mBuffTimerID );
		}
	}

	Clean();

	return SUCCESS;
}


CBuffObject* CBuffList::InsertBuff( unsigned int vBuffID, int vPersistTime, CEntityCharacter* pSrcEntity, unsigned int& vLastBuffID, int vAttack, CEntityCharacter* pDstEntity, int* vListID, int* vResultCode )
{
	LK_ASSERT( pDstEntity != NULL, return 0 );

	vLastBuffID = 0;
	CTemplateBuff* tpBuffTpl2 = (CTemplateBuff*) CDataStatic::SearchTpl( vBuffID );
	if ( tpBuffTpl2 == NULL )
	{
		LOG_ERROR( "pro", "[%s:%d] buff id %d not found", __FUNCTION__, __LINE__, vBuffID );
		*vResultCode = ERROR_USESKILL_INSERTBUFF_UNTEMPLATE;
		return NULL;
	}

	int nNewBuffIdx = -1;
	bool tNewListID = true;

	for( unsigned int i = 0; i < mBuffNumber && i < ARRAY_CNT( mBuffList ); i ++ )
	{
		CTemplateBuff* tpBuffTpl1 = (CTemplateBuff*) CDataStatic::SearchTpl( mBuffList[ i ].mBuffID );
		if ( tpBuffTpl1 == NULL )
		{
			LOG_ERROR( "pro", "[%s:%d] buff id %d not found", __FUNCTION__, __LINE__, mBuffList[ i ].mBuffID );
			continue;
		}

		// �����Ҫȥ���ӵ�Ч��
		if ( tpBuffTpl2->mRemoveCountID == mBuffList[ i ].mBuffID )
		{
			mBuffList[ i ].mBuffSuperCount--;
			if ( mBuffList[ i ].mBuffSuperCount == 0 )
			{
				pDstEntity->EntityRemoveBuff( mBuffList[ i ].mBuffID );	
			}
			*vResultCode = ERROR_USESKILL_INSERTBUFF_REMOVECOUNT;
			return NULL;
		}

		// ���Buffϵ��ID��ͬ
		if ( tpBuffTpl1->mBuffSeriesID == tpBuffTpl2->mBuffSeriesID )
		{
			if( ( tpBuffTpl1->mTempID == tpBuffTpl2->mTempID )
				&& ( tpBuffTpl1->mBuffSuperposition != CTemplateBuff::NONE_SUPERPOSITION ) )
			{
				if( tpBuffTpl1->mBuffSuperposition == CTemplateBuff::TIME_SUPERPOSITION )
				{
					// ʱ���������Buff
					// ��ǰʱ��Buffʣ��ʱ������¼�Buffʱ��

					CTimerItem* tpTimer = CTimerMng::GetSingletonPtr( )->GetTimer( mBuffList[ i ].mBuffTimerID );
					int tLastTime = ( tpTimer == NULL ) ? 0 : tpTimer->mMillSeconds;
					// ����ʱ�䲻��Խ��,����������
					if(  (int)(tLastTime + vPersistTime) < 0 )
					{			
						// ���ش���
						*vResultCode = ERROR_USESKILL_BUFFTIME_LIMIT;
						return NULL;
					}
					else
					{
						mBuffList[ i ].mPersistTime = tLastTime + vPersistTime;	
					}
					
					mBuffList[ i ].mBuffSuperCount = 1;

					tNewListID = false;

					nNewBuffIdx = i;

					*vResultCode = ERROR_USESKILL_INSERTBUFF_TIMEADD;
					break;
				}
				else if( tpBuffTpl1->mBuffSuperposition == CTemplateBuff::FUNC_SUPERPOSITION )
				{
					// ֻ�й��ܵ��ӵ�buff�ż��������
					mBuffList[ i ].mBuffSuperCount++;
					continue;
				}
			}
			else if ( ( tpBuffTpl2->mIdenValue >= tpBuffTpl1->mIdenValue ) && 
				( tpBuffTpl1->mBuffSuperposition == CTemplateBuff::NONE_SUPERPOSITION ))
			{
				vLastBuffID = mBuffList[ i ].mBuffID;
				*vListID = mBuffList[ i ].mListID;
				mBuffList[ i ].mBuffID		= vBuffID;
				mBuffList[ i ].mPersistTime	= vPersistTime;
				mBuffList[ i ].mSrcEntityID	= pSrcEntity->GetEntityID();
				mBuffList[ i ].mLastInterval= tpBuffTpl2->mBuffFirstActionTime;
				mBuffList[ i ].mTimerType	= tpBuffTpl2->mTimerType;
				mBuffList[ i ].mBackDamage	= 0;
				mBuffList[ i ].mAttack = vAttack;
				mBuffList[ i ].mBuffSuperCount = 1;

				nNewBuffIdx = i;
				break;
			}

			*vResultCode = ERROR_USESKILL_INSERTBUFF_LARGE;
			return NULL;
		}
	}

	if( nNewBuffIdx == -1 && mBuffNumber < ARRAY_CNT( mBuffList ) )
	{
		mBuffList[ mBuffNumber ].mBuffID        = vBuffID;
		mBuffList[ mBuffNumber ].mPersistTime   = vPersistTime;
		mBuffList[ mBuffNumber ].mSrcEntityID   = pSrcEntity->GetEntityID();
		mBuffList[ mBuffNumber ].mLastInterval= tpBuffTpl2->mBuffFirstActionTime;
		mBuffList[ mBuffNumber ].mTimerType = tpBuffTpl2->mTimerType;
		mBuffList[ mBuffNumber ].mBackDamage    = 0;
		mBuffList[ mBuffNumber ].mAttack = vAttack;
		mBuffList[ mBuffNumber ].mBuffSuperCount = 1;

		nNewBuffIdx = mBuffNumber;

		*vResultCode = SUCCESS;
		mBuffNumber++;
	}


	// Ϊbuff�ҵ���λ��
	if( nNewBuffIdx != -1 )
	{

		if( tNewListID == true )
		{
			mBuffListID++;
			mBuffList[ nNewBuffIdx ].mListID = mBuffListID;//sBuffListID;
		}

		// ʱ����buff
		if( tpBuffTpl2->mLastTime > 0 )
		{
			// ���֮ǰ��timer,��ɾ��
			if( mBuffList[ nNewBuffIdx ].mBuffTimerID != INVALID_OBJ_ID )
			{
				pDstEntity->GetTimerReciver()->ClearTimer( mBuffList[ nNewBuffIdx ].mBuffTimerID );
				mBuffList[ nNewBuffIdx ].mBuffTimerID = INVALID_OBJ_ID;
			}

			int nOtherInfo[4] = { MESSAGE_PROPERTY, vBuffID, mBuffList[ nNewBuffIdx ].mListID, 0 };
			mBuffList[ nNewBuffIdx ].mBuffTimerID = pDstEntity->GetTimerReciver()->SetTimer( pDstEntity->GetEntityID(), 
				TIMER_BUFF_FUNCTION,
				tpBuffTpl2->mBuffActionTime > 0 ? tpBuffTpl2->mBuffActionTime : mBuffList[ nNewBuffIdx ].mPersistTime,
				3,
				nOtherInfo);
		} 

		return &mBuffList[ nNewBuffIdx ];

	}

	*vResultCode = ERROR_USESKILL_INSERTBUFF_FULL;
	return NULL;
}




int CBuffList::RemoveBuff( unsigned int vBuffID, CEntityCharacter* pEntity, int* vListID  )
{

	for ( unsigned int i = 0; i < mBuffNumber && i < ( ARRAY_CNT( mBuffList ) ) ; i ++ )
	{
		if ( mBuffList[ i ].mBuffID == vBuffID && ( ( *vListID == 0 ) ? true : *vListID == mBuffList[ i ].mListID ) )
		{
			if( mBuffList[i].mBuffTimerID != INVALID_OBJ_ID )
			{
				pEntity->GetTimerReciver()->ClearTimer( mBuffList[i].mBuffTimerID );
				mBuffList[i].mBuffTimerID = INVALID_OBJ_ID;
			}

			*vListID = mBuffList[ i ].mListID;

			// ����������һ��buff,Ҫ������buff����������֤���������� 
			if( i < ( mBuffNumber - 1 ) )
			{
				mBuffList[ i ] = mBuffList[ mBuffNumber - 1 ];

				// ���buff�ڴ�ؼ�����
				mBuffList[ mBuffNumber - 1 ].Initialize();
			}
			else
			{
				// ���buff�ڴ�ؼ�����
				mBuffList[ i ].Initialize();
			}


			mBuffNumber --;

			return i;
		}
	}

	return -1;
}

void CBuffList::CreateFromTlv2( CPropertyCharacter* vpCharacter, PBBuffList* pBuffer )
{
	LK_ASSERT( vpCharacter != NULL, return );

	int nTempBuffNum = 0;

	for ( unsigned int i = 0; i <  ARRAY_CNT(mBuffList) && i < (unsigned int)pBuffer->buffobjects_size(); i ++ )
	{
		const PBBuffObject& tpBuffObject = pBuffer->buffobjects( i );

		mBuffList[ nTempBuffNum ].mTimerType	= tpBuffObject.timertype();

		if ( mBuffList[ nTempBuffNum ].mTimerType == CTemplateBuff::BUFF_TIMER_TYPE_REAL )
		{
			time_t tTime = time( NULL );
			unsigned long long tTime64 = tTime * 1000;
			if( tTime64 >= tpBuffObject.persisttime( ) )
			{
				// buff�Ѿ�����
				mBuffList[ nTempBuffNum ].mPersistTime = 0;
				continue;
			}
			else
			{
				mBuffList[ nTempBuffNum ].mPersistTime = tpBuffObject.persisttime( ) - tTime64;
			}
		}
		else
		{
			//TODO: buff����ʱ��̫��������24�죩Ҳ��Խ�磬����Ŀǰ��û����ô����ʱ�䣬����һ�������ˣ�����ע��	
			//����ʱ�� -1 Ϊ������buff
			mBuffList[ nTempBuffNum ].mPersistTime = tpBuffObject.persisttime();
			if( mBuffList[ nTempBuffNum ].mPersistTime <= 0 && mBuffList[ nTempBuffNum ].mPersistTime != -1 )
			{
				mBuffList[ nTempBuffNum ].mPersistTime = 0;
				continue;
			}
		}

		//		sBuffListID++;	
		mBuffListID++;
		mBuffList[ nTempBuffNum ].mBuffID		= tpBuffObject.buffid();
		mBuffList[ nTempBuffNum ].mListID		= mBuffListID;
		mBuffList[ nTempBuffNum ].mBuffSuperCount = 
			( tpBuffObject.supercount( ) == 0 ) ? 1 : tpBuffObject.supercount( ); 

		// ���ʣ��ʱ�����ģ��ʱ�� ��ǿ�����ó�ģ��ʱ��
		CTemplateBuff* tpTplBuff = (CTemplateBuff*)CDataStatic::SearchTpl( mBuffList[ nTempBuffNum ].mBuffID );
		if ( tpTplBuff == NULL )
		{
			LOG_ERROR("pro", "no such buff in player?? buffid=%d", mBuffList[ nTempBuffNum ].mBuffID );
			continue;
		}

		// buff ʵʱ����״̬
		for( unsigned int j = 0; j < ARRAY_CNT( tpTplBuff->mBuff ); j++ )
		{
			if( tpTplBuff->mBuff[ j ].mBuffFunc != CTemplateBuff::BUFFINC_NONE )
			{
				vpCharacter->AttachBuffState( 0, &tpTplBuff->mBuff[ j ], tpTplBuff->mTempID );
			}
		}

		mBuffList[ nTempBuffNum ].mBackDamage = tpBuffObject.backdamage();

		int tParamesSize = tpBuffObject.parames_size();
		for ( int j = 0; j < tParamesSize && j < MAX_BUFFFUN_COUNT; j++ )
		{
			mBuffList[ nTempBuffNum ].mParames[ j ] = tpBuffObject.parames( j );
		}
		tParamesSize = tpBuffObject.parames2_size();
		for ( int j = 0; j < tParamesSize && j < MAX_BUFFFUN_COUNT; j++)
		{
			mBuffList[ nTempBuffNum ].mParames2[ j ] = tpBuffObject.parames2( j );
		}

		nTempBuffNum++;
	}

	mBuffNumber = std::min(  ( int)pBuffer->buffnumber(), (int)nTempBuffNum );

	PBTransform *tpTran = pBuffer->mutable_transform();

	mTransform.mHasTransform = tpTran->has_hastransform();
	mTransform.mSexID = tpTran->sex();
	mTransform.mStateID = tpTran->stateid();
	mTransform.mWeaponID = tpTran->weaponid();
	mTransform.mClothID = tpTran->clothid();
	mTransform.mFashionID = tpTran->fashionid();
	mTransform.mNpcID = tpTran->npcid();

	//TODO: ֮ǰ����һ�δ���hastransform��д��boolֵ�ˣ������Ÿ�Ϊint,
	// �����޸�һ�Σ�����hastransformΪ1��(��Ϊbuffidһ����һ����1�������)��������Ϊ0�������ṹҲҪ����
	if( mTransform.mHasTransform == 1)
	{
		mTransform.Clear();
	}
}

void CBuffList::GetTlvBuffer2( PBBuffList* pBuffer )
{
	if( mBuffNumber > ARRAY_CNT( mBuffList ) )
	{
		mBuffNumber = ARRAY_CNT( mBuffList ) ;
	}

	int nTempBuffNumber = 0;
	for ( unsigned int i = 0; i < mBuffNumber; i ++ )
	{
		PBBuffObject* tpPBBuffObject = pBuffer->add_buffobjects();

		tpPBBuffObject->set_buffid( mBuffList[ i ].mBuffID );
		tpPBBuffObject->set_timertype( mBuffList[ i ].mTimerType );
		tpPBBuffObject->set_listid( mBuffList[ i ].mListID );
		tpPBBuffObject->set_supercount( mBuffList[ i ].mBuffSuperCount );
		if ( mBuffList[ i ].mTimerType == CTemplateBuff::BUFF_TIMER_TYPE_REAL )
		{
			if( mBuffList[ i ].mPersistTime <= 0 && mBuffList[ i ].mPersistTime != -1)
			{
				continue;
			}

			unsigned long long tTime64 = time( NULL ) * 1000;
			tpPBBuffObject->set_persisttime( ( unsigned long long )mBuffList[ i ].mPersistTime + tTime64 );
		} 
		else
		{
			// ��ǰBuff���ܳ�ʱ, ����ûɾ�� | -1��ʾ������buff
			if( mBuffList[ i ].mPersistTime <= 0 && mBuffList[ i ].mPersistTime != -1)
			{
				continue;
			}

			tpPBBuffObject->set_persisttime( mBuffList[ i ].mPersistTime );
		}

		tpPBBuffObject->set_backdamage( mBuffList[ i ].mBackDamage );

		for ( int j = 0; j < MAX_BUFFFUN_COUNT; j++ )
		{
			tpPBBuffObject->add_parames( mBuffList[ i ].mParames[ j ] );
			tpPBBuffObject->add_parames2( mBuffList[ i ].mParames2[ j ] );
		}

		nTempBuffNumber++;
	}

	pBuffer->set_buffnumber( nTempBuffNumber );

	PBTransform *tpTran = pBuffer->mutable_transform();
	tpTran->set_hastransform( mTransform.mHasTransform );
	tpTran->set_sex( mTransform.mSexID );
	tpTran->set_stateid( mTransform.mStateID );
	tpTran->set_weaponid( mTransform.mWeaponID );
	tpTran->set_clothid( mTransform.mClothID );
	tpTran->set_fashionid( mTransform.mFashionID );
	tpTran->set_npcid( mTransform.mNpcID );
}

CBuffObject* CBuffList::GetBuffObjectByID( int nBuffID )
{
	for ( unsigned int i = 0; mBuffNumber > 0 && i < ( ARRAY_CNT( mBuffList ) ) ; i ++ )
	{
		if ( mBuffList[ i ].mBuffID == (unsigned int)nBuffID )
		{
			return &mBuffList[ i ];
		}
	}

	return NULL;
}

// �õ�������ʾ�õ�buff��Ϣ
void CBuffList::GetTlvBufferTeamShow( PBBuffList* pBuffer )
{
	if( mBuffNumber > ARRAY_CNT( mBuffList ) )
	{
		mBuffNumber = ARRAY_CNT( mBuffList ) ;
	}

	pBuffer->set_buffnumber( mBuffNumber );

	for ( unsigned int i = 0; i < mBuffNumber; i ++ )
	{
		PBBuffObject* tpPBBuffObject = pBuffer->add_buffobjects();

		tpPBBuffObject->set_buffid( mBuffList[ i ].mBuffID );
		tpPBBuffObject->set_listid( mBuffList[ i ].mListID );
	}

	if( mTransform.mHasTransform )
	{
		PBTransform* pPBTrans = pBuffer->mutable_transform();
		GetTransform( pPBTrans );
	}
}

// �õ��������������ʾ��buff��Ϣ
void CBuffList::GetTlvBufferShow( PBBuffList* pBuffer )
{
	if( mBuffNumber > ARRAY_CNT( mBuffList ) )
	{
		mBuffNumber = ARRAY_CNT( mBuffList );
	}

	pBuffer->set_buffnumber( mBuffNumber );

	for ( unsigned int i = 0; i < mBuffNumber; i ++ )
	{
		PBBuffObject* tpPBBuffObject = pBuffer->add_buffobjects();

		tpPBBuffObject->set_buffid( mBuffList[ i ].mBuffID );
		tpPBBuffObject->set_listid( mBuffList[ i ].mListID );
		if ( mBuffList[ i ].mTimerType == CTemplateBuff::BUFF_TIMER_TYPE_REAL )
		{
			tpPBBuffObject->set_persisttime( mBuffList[ i ].mPersistTime );
		} 
		else
		{
			tpPBBuffObject->set_persisttime( mBuffList[ i ].mPersistTime );
		}
	}

	if( mTransform.mHasTransform )
	{
		PBTransform* pPBTrans = pBuffer->mutable_transform();
		GetTransform( pPBTrans );
	}
}


void CBuffList::RefreshBuffLeftTime( )
{
	for( unsigned int i = 0; i < mBuffNumber; i++ )
	{
		if( mBuffList[ i ].GetBuffTimerID() != INVALID_OBJ_ID )
		{
			// buff�Ƚ����⣬���ܼ򵥵İ�ʣ��ʱ���д��������buffÿ�����ü��������ʱ��
			CTimerItem* pTimerItem = CTimerMng::GetSingletonPtr()->GetTimer( mBuffList[ i ].GetBuffTimerID() );
			if( pTimerItem != NULL )
			{
				// ���ڳ���������buff,ֱ��ˢ��ʣ��ʱ��
				if( mBuffList[ i ].GetBuffActionTime( ) == 0 )
				{
					//TODO: Ŀǰbuffʱ�仹û�кܳ��ģ�����24�죬����ֻ��΢�����
					mBuffList[ i ].mPersistTime = pTimerItem->mMillSeconds ;	
				}
			}

			//TODO: ���ڼ�������õ�buff,��������ʹ������崻���Ҳ������һ�μ�������, һ�㶼��10s����
		}
	}
}

void CBuffList::SetTransform( CEntityCharacter *pEntity, int nBuffID )
{
	// ������������ǿվ����״̬
	if ( pEntity == NULL )
	{
		mTransform.Clear();
		return;
	}
	if ( pEntity->IsPlayer() )
	{
		CEntityPlayer *tpPlayer = (CEntityPlayer*)pEntity;
		CPropertyPlayer *tpProperty = (CPropertyPlayer*)tpPlayer->GetProperty();
		CBuffList* tpBuff = tpProperty->GetBuffList( );
		bool tHasTransform = false;
		// ����Է�Ҳ�б�������
		if ( tpBuff->mTransform.mSexID != 0 )
		{
			mTransform.mSexID = tpBuff->mTransform.mSexID;
			tHasTransform = true;
		}
		if ( tpBuff->mTransform.mStateID != 0 )
		{
			mTransform.mStateID = tpBuff->mTransform.mStateID;
			tHasTransform = true;
		}
		if ( tpBuff->mTransform.mWeaponID != 0 )
		{
			mTransform.mWeaponID = tpBuff->mTransform.mWeaponID;
			tHasTransform = true;
		}
		if ( tpBuff->mTransform.mClothID != 0 )
		{
			mTransform.mClothID = tpBuff->mTransform.mClothID;
			tHasTransform = true;
		}
		if ( tpBuff->mTransform.mFashionID != 0 )
		{
			mTransform.mFashionID = tpBuff->mTransform.mFashionID;
			tHasTransform = true;
		}
		if ( tpBuff->mTransform.mNpcID != 0 )
		{
			mTransform.mNpcID = tpBuff->mTransform.mNpcID;
			tHasTransform = true;
		}

		if ( tHasTransform == false )
		{
			mTransform.mSexID = tpPlayer->GetSex();
			int tStateID = tpProperty->GetStateParam( STATE_TRANSFORM ).mParames1;
			CTemplateNpc *tplNpc = (CTemplateNpc*)CDataStatic::SearchTpl( tStateID );
			if ( tplNpc != NULL )
			{
				mTransform.mStateID = tStateID;
			}
			//CTemplateEquipment *tplEquip = NULL;
			CItemEquipment* tpWeapon	= (CItemEquipment*) tpProperty->GetEquipment( )->GetItemObjPtr( EQUIPMENT_WEAPON );
			if ( tpWeapon != NULL && tpWeapon->IsOvertimed() == false )
			{
				mTransform.mWeaponID = tpWeapon->GetItemID();
			}	
			CItemEquipment* tpChest		= (CItemEquipment*) tpProperty->GetEquipment( )->GetItemObjPtr( EQUIPMENT_CHEST );
			if ( tpChest != NULL && tpChest->IsOvertimed() == false )
			{
				mTransform.mClothID = tpChest->GetItemID();
			}
			CItemEquipment* tpFashion	= (CItemEquipment*) tpProperty->GetEquipment( )->GetItemObjPtr( EQUIPMENT_FASHION );
			if ( tpFashion != NULL && tpFashion->IsOvertimed() == false )
			{
				mTransform.mFashionID = tpFashion->GetItemID();
			}
		}

		mTransform.mHasTransform = nBuffID;

	}
	if ( pEntity->IsNpc() )
	{
		CEntityNpc *tpNpc = (CEntityNpc*)pEntity;
		CTemplateNpc *tplNpc = (CTemplateNpc*)CDataStatic::SearchTpl( tpNpc->GetNpcID() );
		if ( tplNpc != NULL )
		{
			mTransform.mNpcID = tpNpc->GetNpcID();
			mTransform.mHasTransform = nBuffID;
		}
	}
}

void CBuffList::GetTransform( PBTransform *pTran )
{
	if ( pTran == NULL )
		return;
	
	//TODO: ���û�з���ɽ����״̬���Ͳ�������Щ��Ϣ ������û��һ���õ��жϷ���ɽ��Ϣ��״̬
	pTran->set_hastransform( mTransform.mHasTransform );
	pTran->set_sex( mTransform.mSexID );
	pTran->set_stateid( mTransform.mStateID );
	pTran->set_weaponid( mTransform.mWeaponID );
	pTran->set_clothid( mTransform.mClothID );
	pTran->set_fashionid( mTransform.mFashionID );
	pTran->set_npcid( mTransform.mNpcID );
}
