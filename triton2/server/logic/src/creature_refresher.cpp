#include "stdafx.hpp"
#include "creature_refresher.h"
#ifdef LEAK_CHK_DEBUG_NEW
#include "debug_new.h"
#endif

template<> CCreatureRefresher* CSingleton< CCreatureRefresher >::spSingleton = NULL;


CCreatureRefresher::CCreatureRefresher()
{
	if ( CObj::msCreateMode )
	{
		Initailze();
	} 
	else
	{
		Resume();
	}
}


CCreatureRefresher::~CCreatureRefresher()
{
}

void CCreatureRefresher::Initailze()
{
	mDelayRefreshList.initailize();
	mDelayRefreshTimer = CWTimer(300);
}

void CCreatureRefresher::Resume()
{

}

// ��ָ����ʱ��ˢ��NPC����Ҫ�������е�Creator��Ŀǰ�������еĵ�ͼ��ˢ��
void CCreatureRefresher::OnTimeRefreshEvent( int vIndex )
{
	time_t tval;
	struct tm *now;        
	time(&tval);
	now = localtime(&tval);

	CCreatorManager::PedalRefreshList::iterator tBegin = CCreatorManager::GetSingleton().mPedalList.begin();
	CCreatorManager::PedalRefreshList::iterator tEnd = CCreatorManager::GetSingleton().mPedalList.end();
	for ( ;tBegin != tEnd; ++tBegin )
	{
		CPedalCreator *pCreator = (CPedalCreator *)CSceneObjManager::GetSingleton().GetObject( *tBegin );
		if ( pCreator == NULL )
		{
			continue;
		}
		for ( int i = 0; i < pCreator->mRandCount; i++ )
		{			
			if ( pCreator->mRandList[ i ].mActive == true )
			{
				// �����˵ĵ�ʱҪ�ص�
				if ( now->tm_hour != pCreator->mRandList[ i ].mHour || 
					 now->tm_min * 60 + now->tm_sec >= pCreator->mExistTime )
				{
					CEntityPedal *tpPedal = (CEntityPedal*)CSceneLogic::GetSingleton().GetEntity( pCreator->mPedalID );
					if ( tpPedal != NULL )
					{
						CSceneLogic::GetSingleton().DestroyEntity( tpPedal, 0 );
						pCreator->mPedalID = 0;
						break;
					}					
				}
				// ʱ�䵽��Ҫ����
				if ( now->tm_hour == pCreator->mRandList[ i ].mHour && now->tm_min < pCreator->mExistTime / 60 )
				{
					if ( pCreator->mPedalID == 0 )
					{
						unsigned int tEntityID = 0;
						CMapModule::GetSingleton().CreateNpc( pCreator->mDefaultLineID, pCreator->mDefaultMapID, 0, pCreator, tEntityID );
						pCreator->mPedalID = tEntityID;
						break;
					}					
				}
			}
		}
	}

	//CSceneObjManagerImp::ObjMng_OgreCreator::iterator tBeginIter = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp->mOgreCreatorPool.begin();
	//CSceneObjManagerImp::ObjMng_OgreCreator::iterator tEndIter = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp->mOgreCreatorPool.end();
	CCreatorManager::TimeRefreshList::iterator tBeginIter = CCreatorManager::GetSingletonPtr()->mRefreshList.begin();
	CCreatorManager::TimeRefreshList::iterator tEndIter = CCreatorManager::GetSingletonPtr()->mRefreshList.end();
	for ( ; tBeginIter != tEndIter; ++tBeginIter)
	{
		COgreCreator *pCreator = (COgreCreator *) CSceneObjManager::GetSingletonPtr()->GetObject( *tBeginIter );
		if ( pCreator == NULL )
			continue;		
		bool tCanReflesh = false;
		for ( int j = 0; j < pCreator->mRCount6; j++ )
		{
			RefreshDate tTime = pCreator->mRefreshTime[ j ];
			if ( tTime.mYear <= 0 && tTime.mMonth <= 0 && tTime.mDate <= 0 && tTime.mHour < 0 && tTime.mMinute < 0 && tTime.mDay < 0 )
				continue;
			if ( tTime.mYear > 0 )
			{
				if ( ( tTime.mYear - 1900 ) != now->tm_year )
					continue;
			}
			if ( tTime.mMonth > 0 )
			{
				if ( tTime.mMonth != ( now->tm_mon + 1 ) )
					continue;
			} 
			if ( tTime.mDate > 0 )
			{
				if ( tTime.mDate != now->tm_mday )
					continue;
			}
			if ( tTime.mHour >= 0 && tTime.mMinute >= 0 )
			{
				// �����ͬһʱ���
				if ( tTime.mHour == now->tm_hour )
				{
					if ( tTime.mMinute != now->tm_min + 10 )
						continue;
				}
				// �����ǰʱ���ˢ��ʱ����һСʱ
				else if ( now->tm_hour - tTime.mHour == 23 || tTime.mHour - now->tm_hour == 1 )
				{
					if ( tTime.mMinute + 50 != now->tm_min )
					{
						continue;
					}
				}
				else
				{
					continue;
				}				
			}
			if ( tTime.mDay > 0 )
			{
				if ( now->tm_wday == 0 )
				{
					if ( tTime.mDay != 7 )
						continue;
				}
				else
				{
					if ( tTime.mDay != now->tm_wday )
						continue;
				}				
			}
			tCanReflesh = true;
			break;
		}
		if ( tCanReflesh == true )
		{
			// ˢ���µ�NPC
			// �����ǰ�й֣�����ˢ
			if ( pCreator->mHasOgre != 0 )
			{
				CEntityOgre *tpOgre = (CEntityOgre*) CSceneObjManager::GetSingletonPtr()->GetObject( pCreator->mHasOgre );
				if ( tpOgre != NULL )
				{
					CTemplateBuff *tplBuff = (CTemplateBuff*)CDataStatic::SearchTpl( pCreator->mTimeBuffID );
					tpOgre->EntityInsertBuff( tpOgre, tplBuff );
				}
			}
			else
			{
				unsigned int tEntityID = 0;
				CMapModule::GetSingleton().CreateNpc( pCreator->mLineID, pCreator->mMapID, vIndex, pCreator, tEntityID, 0, CWTPoint(0,0), true );
			}
			
			/*CDelayRefreshedCreature tCreature( pCreator->mLineID, pCreator->mMapID, vIndex, pCreator->get_id() );
			AddToDelayRefreshList( tCreature );*/
		}
	}
}

// ��ĳһ����ˢ�ּ���ˢ��,������Ǳ�ɱ�Ĺֵ�ʵ��,�ҵ���Ӧ��Creator����ˢ��
void CCreatureRefresher::OnNumericalRefreshEvent( CEntityNpc* pNpc )
{
	COgreCreator *tCreator = (COgreCreator*)CSceneObjManager::GetSingletonPtr()->GetObject( pNpc->GetCreatorID( ) );
	if ( tCreator != NULL )
	{
		tCreator->mCurrentCount = 0;
		for( int i = 0; i < tCreator->mRCount4; i++ )
		{
			int tCountID = tCreator->mRefresh4[ i ];
			//				COgreCreator *tTempCreator = (COgreCreator*)CSceneObjManager::GetSingletonPtr()->GetObject( CMapObjManager::mOgreCreator[ tCountID ] );
			COgreCreator* tTempCreator = ( COgreCreator*)CCreatorManager::GetSingletonPtr()->GetCreator( tCountID );
			if ( tTempCreator != NULL )
			{
				if ( tTempCreator->mCurrentCount >= 0 )
				{
					tTempCreator->mCurrentCount++;
					if ( tTempCreator->mCurrentCount >= tTempCreator->mCountNum )
					{
						unsigned int tEntityID = 0;
						CMapModule::GetSingleton().CreateNpc( pNpc->GetLineID(), pNpc->GetMapID(), pNpc->GetMapIndex(), tTempCreator, tEntityID );
						/*CDelayRefreshedCreature tCreature( pNpc->mLineID, pNpc->mMapID, pNpc->GetMapIndex(), pNpc->get_id() );
						AddToDelayRefreshList( tCreature );*/
						tTempCreator->mCurrentCount = -1;
					}
				}
			}
		}									
	}
}

// ��ˢ��ĳ���ֵ�ʱ�����ͬʱˢ������Ĺ�,������ʼ��ˢ�ֵ����Ҫˢ�ֵĵ�ͼ���
void CCreatureRefresher::OnPossibilityRefreshEvent( COgreCreator *pCreator, int vIndex )
{
	for ( int i = 0; i < pCreator->mRCount3; i++ )
	{
		int tIndex =  pCreator->mRefresh3[ i ];
		if ( tIndex < 0 || tIndex >= OGREINDEX )
			continue;
		int tRand1 = RAND(SERVER_PERCENT_INT);
		if ( tRand1 > pCreator->mRefreshRate )
			continue;
		COgreCreator *pTempCreator = (COgreCreator*)CSceneObjManager::GetSingletonPtr()->GetObject( CCreatorManager::GetSingletonPtr()->mOgreCreator[ tIndex ] );
		if ( pTempCreator != NULL )
		{
			unsigned int tEntityID = 0;
			CMapModule::GetSingleton().CreateNpc( pTempCreator->mLineID, pTempCreator->mMapID, vIndex, pTempCreator, tEntityID );
//			AddToDelayRefreshList( CDelayRefreshedCreature( pTempCreator->mLineID, pTempCreator->mMapID, vIndex, pTempCreator->get_id() ) );
			/*CDelayRefreshedCreature tCreature( pTempCreator->mLineID, pTempCreator->mMapID, vIndex, pTempCreator->get_id() );
			AddToDelayRefreshList( tCreature );*/
		}
	}
}

// ���һ��ʱ���ˢ�³�����Ĺ֣����������Ҫת��Ĺ�
void CCreatureRefresher::OnLifetimeRefreshEvent( CEntityNpc* pNpc, int index )
{
	COgreCreator *pCreator = (COgreCreator*)CSceneObjManager::GetSingletonPtr()->GetObject( pNpc->GetCreatorID( ) );

	if ( pCreator == NULL )
	{
		return;
	}

	if( index == 0 )
	{
		for ( int i = 0; i < pCreator->mRCount2; i++ )
		{
			if ( (int)pNpc->GetNpcID( ) == pCreator->mRefresh2[ i ].mOldID )
			{
				unsigned int tEntityID = 0;				

				if ( pCreator->mRefresh2[ i ].mNewID == 0 )
				{
					pCreator->mHasOgre = 0;
					pCreator->mCurrentCount = 0;
				}
				else
				{
					CMapModule::GetSingleton().CreateNpc( pNpc->GetLineID(), pNpc->GetMapID(), pNpc->GetMapIndex(), pCreator, tEntityID, pCreator->mRefresh2[ i ].mNewID, pNpc->mPos );
				}
				break;
			}
		}
	}
	else
	{
		if( index < pCreator->mRCount2 )
		{
			if( ( int )pNpc->GetNpcID( ) == pCreator->mRefresh2[ index ].mOldID )
			{
				unsigned int tEntityID = 0;
				CMapModule::GetSingleton().CreateNpc( pNpc->GetLineID(), pNpc->GetMapID(), pNpc->GetMapIndex(),
					pCreator, tEntityID, pCreator->mRefresh2[ index ].mNewID, pNpc->mPos );
			}
		}
	}
}

// ���ݴ����Creator���ظ������ɵ�NpcID
int CCreatureRefresher::OnDeathRefreshEvent( COgreCreator* pCreator )
{
	int tRand = RAND(SERVER_PERCENT_INT);
	short tLow = 0;
	short tHigh = 0;
	for ( int i = 0; i < pCreator->mRCount1; i++ )
	{
		tLow += ( i == 0 ) ? 0 : pCreator->mRefresh1[ i - 1 ].mOgreRand;
		tHigh += pCreator->mRefresh1[ i ].mOgreRand;
		if ( tRand >= tLow && tRand <= tHigh )
			return pCreator->mRefresh1[ i ].mOgreID;
	}
	return 0;
}

// ���ݴ����Creator���ж��Ƿ��������Creator�й�ͬ���ɵĹ�ϵ������ʵ��ˢ�ֵ�Creator
COgreCreator* CCreatureRefresher::OnMutiMapRefreshEvent( COgreCreator* pCreator )
{
	int tRand = RAND(SERVER_PERCENT_INT);
	short tLow = 0;
	short tHigh = 0;
	for ( int i = 0; i < pCreator->mRCount5; i++ )
	{
		tLow += ( i == 0 ) ? 0 : pCreator->mRefresh5[ i - 1 ].mOgreRand;
		tHigh += pCreator->mRefresh5[ i ].mOgreRand;
		if ( tRand >= tLow && tRand <= tHigh )
		{
			int tIndex = pCreator->mRefresh5[ i ].mIndex;
			CCreator *pCreator = CCreatorManager::GetSingletonPtr()->GetCreator( tIndex );
			if ( pCreator != NULL && pCreator->GetCreatorType() == ENTITYTYPE_OGRE )
			{
				COgreCreator *tpOgreCreator = (COgreCreator*)pCreator;//CSceneObjManager::GetSingletonPtr()->GetObject( CMapObjManager::mOgreCreator[ tIndex ] );
				return tpOgreCreator;
			}
			else 
			{
				return NULL;
			}			
			
		}
	}
	return NULL;
}



// ���뵽�ӳ�ˢ���б�
bool CCreatureRefresher::AddToDelayRefreshList( const CDelayRefreshedCreature& rCreature )
{
	mDelayRefreshList.push_back( rCreature );
	return true;

}

// ���ӳ�ˢ���б�ɾ��
bool CCreatureRefresher::RemoveFromDelayRefreshList( CDelayRefreshedCreature& rCreature )
{
	//mDelayRefreshList.push_back( *pCreature );
	return true;

}


// ����ӳ�ˢ���б�
void CCreatureRefresher::ClearDelayRefreshList( )
{
	mDelayRefreshList.clear();
}

// ִ���ӳ�ˢ��
int CCreatureRefresher::DoDelayRefresh( )
{

	for( TDelayRefreshList::iterator it = mDelayRefreshList.begin(); 
		it != mDelayRefreshList.end();
		++it )
	{
		CItemCreator* pCreator = (CItemCreator*)CSceneObjManager::GetSingletonPtr()->GetObject( (*it).mCreatorID );
		LK_ASSERT( pCreator != NULL, continue );

		unsigned int tEntityID = 0;
		CMapModule::GetSingleton().CreateNpc( (*it).mLineID, (*it).mMapID, (*it).mMapIndex,
			(CCreator*)pCreator, tEntityID );

		CSceneObjManager::GetSingletonPtr()->DestroyObject( (*it).mCreatorID );
	}
	
	ClearDelayRefreshList();

	return 0;
}


// ��ʱ��
void CCreatureRefresher::OnTimer( unsigned int vTickCount, unsigned int vTickOffset )
{
	if( mDelayRefreshTimer.Elapse( vTickOffset) )
	{
		DoDelayRefresh();
	}
}