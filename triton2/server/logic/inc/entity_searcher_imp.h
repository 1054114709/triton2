#ifndef __ENTITY_SEACHER_IMP__
#define __ENTITY_SEACHER_IMP__

#include "entity_searcher.h"
#include "entity.h"
#include "sceneobj_manager.h"
#include "mapobjmanager.h"
#include "propertymodule.h"


// �����ɼ����е����
template < class Check >
void SeenPlayerContainserSearcher<Check>::Visit( CEntity* pEntity  )
{
	CSeenPlayerContainer::SeenPlayerVector::iterator it = pEntity->GetSeenPlayersContainer().mPlayers.begin();

	for( ; it != pEntity->GetSeenPlayersContainer().mPlayers.end(); )
	{
		CEntity* pSeenEntity = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject(*it);
		if( pSeenEntity == NULL )
		{
			LOG_ERROR( "default", "can't find %d in entity(%d)'s viewlist, map(%d) pos(%d,%d) ", 
				*it, pEntity->GetEntityID(), pEntity->GetMapID(), pEntity->GetPosX(), pEntity->GetPosY() );
			
			// share vector������ɾ����������hash_map
			pEntity->GetSeenPlayersContainer().mPlayers.erase( it++ );

			continue ;
		}

		++it;

		if( m_Check( pSeenEntity) )
		{
			m_rEntitys.push_back( pSeenEntity );
		}
	}

}


// �����ɼ����е�NPC
template < class Check >
void SeenNpcContainserSearcher<Check>::Visit( CEntity* pEntity  )
{
	if( pEntity->IsNpc() == false )
	{
		return ;
	}

	CEntityNpc* pNpc = (CEntityNpc*)pEntity;

	CSeenCharactorNpcContainer::SeenNpcCharactorPool::iterator it = pNpc->GetSeenNpcsContainer().mNpcCharactors.begin();

	for( ; it != pNpc->GetSeenNpcsContainer().mNpcCharactors.end();)
	{
		CEntity* pSeenEntity = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject(*it);
		if( pSeenEntity == NULL )
		{
			LOG_ERROR( "default", "can't find %d in entity(%d)'s viewlist, map(%d) pos(%d,%d) ", 
				*it, pEntity->GetEntityID(), pEntity->GetMapID(), pEntity->GetPosX(), pEntity->GetPosY() );

			// share vector������ɾ����������hash_map
			pNpc->GetSeenNpcsContainer().mNpcCharactors.erase( it++ );

			continue ;
		}

		++it;

		if( m_Check( pSeenEntity) )
		{
			m_rEntitys.push_back( pSeenEntity );
		}
	}

}



// ��ͼ��������( -> ���б������� -> �����������ʵ�� )
template< class Check >
void MapRegionEntitySearcher<Check>::Visit( CMapObject* pMap )
{
	int nTopLeftX = std::max( m_TopLeft.mX, 0 );
	int nTopLeftY = std::max( m_TopLeft.mY, 0 );
	int nBottomRightX = std::min( m_BottomRight.mX, (int)pMap->GetWidth()-1 );
	int nBottomRightY = std::min( m_BottomRight.mY, (int)pMap->GetHight()-1 );

	for ( int x = nTopLeftX; x <= nBottomRightX; x ++ )
	{
		for ( int y = nTopLeftY; y <= nBottomRightY; y ++ )
		{
			CMapCell* tpCell = pMap->GetCell( CWTPoint( x, y ) );
			LK_ASSERT( tpCell != NULL, continue );

			tpCell->Tick( m_Check );
			// ��ǰ����
			if( m_Check.GetResult() == EM_OBJFUN_ENTITY_TERMINATE)
			{
				return;
			}
		}
	}

}


// �ٻ�����������
struct MapCellSearchEnemy
{
	MapCellSearchEnemy( CEntityPet* pPet ) :
		mpSelfEntity( pPet ), mpMapObject( pPet->GetMapObject() ), mEnemys(NULL)  {}
	~MapCellSearchEnemy() {}

	CEntityPet* mpSelfEntity;
	CMapObject* mpMapObject;
	CEntityCharacter* mEnemys;

	int GetResult( ) { return EM_OBJFUN_NONE; }
	void SetResult( int )  {;} 

	//����ֵ: false-��ֹ����; true-����
	bool operator ()( unsigned int unEntityID )
	{
		CEntity* tpDesEntity = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject( unEntityID );
		LK_ASSERT( tpDesEntity != NULL, return true ); // ���жϱ���,�κ������һֱ����ȥ

		// ���ܹ������� �� �Լ�
		if( (mpSelfEntity->GetOwnerID() == unEntityID) || ( mpSelfEntity->GetEntityID() == unEntityID ) )
			return false;

		//// �ж� & ��� & �Ǿ��԰�ȫ��
		if( CPropertyModule::GetSingletonPtr()->EntityPKValid( mpSelfEntity, tpDesEntity, NULL, false ) )
		{
			mEnemys = (CEntityCharacter*)tpDesEntity;
		}
		return false;
	}

	void Visit()
	{
		int nTopLeftX = std::max( mpSelfEntity->GetPosX()-5, 0 );
		int nTopLeftY = std::max( mpSelfEntity->GetPosY()-5, 0 );
		int nBottomRightX = std::min( mpSelfEntity->GetPosX()+5, (int)mpMapObject->GetWidth()-1 );
		int nBottomRightY = std::min( mpSelfEntity->GetPosY()+5, (int)mpMapObject->GetHight()-1 );

		for ( int x = nTopLeftX; x <= nBottomRightX; x ++ )
		{
			for ( int y = nTopLeftY; y <= nBottomRightY; y ++ )
			{
				CMapCell* tpCell = mpMapObject->GetCell( CWTPoint( x, y ) );
				LK_ASSERT( tpCell != NULL, continue );

				tpCell->Tick( *this );

				// �ҵ�һ���ͷ���
				if( mEnemys != NULL )
				{
					return ;
				}
			}
		}
	}

};



// ��Χ��������(���Դ��뼼��)
struct MapCellSearchEnemys
{
	MapCellSearchEnemys( CEntityCharacter* pSelf, int nLimit, int nRange, CTemplateSkill* pSkill ) :
		mpSelfEntity( pSelf ), mpMapObject( mpSelfEntity->GetMapObject() ),
		mEnemyLimit(nLimit), mSkillTpl( pSkill ), mRange( nRange ) {}
	~MapCellSearchEnemys() {}

	CEntityCharacter* mpSelfEntity;
	CMapObject* mpMapObject;
	std::vector<CEntityCharacter*> mEnemys;
	int mEnemyLimit;	// ��������
	CTemplateSkill* mSkillTpl;
	int mRange; // ���÷�Χ

	int GetResult( ) { return EM_OBJFUN_NONE; }
	void SetResult( int )  {;} 

	//����ֵ: false-��ֹ����; true-����
	bool operator ()( unsigned int unEntityID )
	{
		CEntity* tpDesEntity = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject( unEntityID );
		LK_ASSERT( tpDesEntity != NULL, return true ); 

		if ( CPropertyModule::GetSingleton().EntityPKValid( mpSelfEntity, 
			tpDesEntity, 
			mSkillTpl,
			mSkillTpl ? true : false ) == true )
		{
			mEnemys.push_back( (CEntityCharacter*)tpDesEntity );
		}

		return true;
	}

	void Visit()
	{
		int nTopLeftX = std::max( mpSelfEntity->GetPosX()-mRange, 0 );
		int nTopLeftY = std::max( mpSelfEntity->GetPosY()-mRange, 0 );
		int nBottomRightX = std::min( mpSelfEntity->GetPosX()+mRange, (int)mpMapObject->GetWidth()-1 );
		int nBottomRightY = std::min( mpSelfEntity->GetPosY()+mRange, (int)mpMapObject->GetHight()-1 );

		for ( int x = nTopLeftX; x <= nBottomRightX; x ++ )
		{
			for ( int y = nTopLeftY; y <= nBottomRightY; y ++ )
			{
				CMapCell* tpCell = mpMapObject->GetCell( CWTPoint( x, y ) );
				LK_ASSERT( tpCell != NULL, continue );

				tpCell->Tick( *this );

				if( mEnemys.size() >= (unsigned int)mEnemyLimit )
				{
					return;
				}
			}
		}
	}

};


// ̤��(����,����,���)����
struct MapCellPedalSearcher
{
	MapCellPedalSearcher( CEntityPedal* pPedal ) :
		mpSelfEntity( pPedal ), mpMapObject( pPedal->GetMapObject() ) {}
	~MapCellPedalSearcher() {}

	CEntityPedal* mpSelfEntity;
	CMapObject* mpMapObject;
	std::vector<CEntityCharacter*> mEntitysOnPedal;

	int GetResult( ) { return EM_OBJFUN_NONE; }
	void SetResult( int )  {;} 

	//����ֵ: false-��ֹ����; true-��������
	bool operator ()( unsigned int unEntityID )
	{
		CEntity* tpDesEntity = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject( unEntityID );
		if( tpDesEntity == NULL )
		{
			LOG_ERROR( "map", "[%s:%d] map[id:%d index:%d] can't find entity %d", __FUNCTION__, __LINE__,
				mpMapObject->GetMapID(), mpMapObject->GetMapIndex(), unEntityID );
			return true; // ���жϱ���,�κ������һֱ����ȥ
		}

		switch ( mpSelfEntity->GetPedalType() )
		{
		case PEDAL_TRAP:
			{
				// �ж� & ��� & �Ǿ��԰�ȫ��
				if( tpDesEntity->IsCharacter() &&  mpSelfEntity->IsHostileTo( tpDesEntity ) && tpDesEntity->IsAlive() )
				{
					if( tpDesEntity->IsPlayer() || tpDesEntity->IsPet() )
					{
						if( mpMapObject->IsAbsSafe() == false )
						{
							mEntitysOnPedal.push_back( (CEntityCharacter*)tpDesEntity );
						}
					}
					else
					{
						mEntitysOnPedal.push_back( (CEntityCharacter*)tpDesEntity );
					}
				}

				break;
			}
		case PEDAL_TELEPORT:
		case PEDAL_HIEROGRAM:
			{
				if( tpDesEntity->IsPlayer() && tpDesEntity->IsAlive() )
				{
					mEntitysOnPedal.push_back( (CEntityCharacter*)tpDesEntity );
				}
				break;
			}
		case PEDAL_NEEDFIRE:
			{
				if( tpDesEntity->IsPlayer() && tpDesEntity->IsAlive() )
				{
					mEntitysOnPedal.push_back( (CEntityCharacter*)tpDesEntity );
				}
				break;
			}
		default:
			{
				break;
			}
		}

		return true;
	}

	// ����������Χ
	void Visit()
	{
		int nTopLeftX = std::max( mpSelfEntity->GetSrcRect().TopLeft().mX , 0 );
		int nTopLeftY = std::max(mpSelfEntity->GetSrcRect().TopLeft().mY, 0 );
		if ( mpMapObject == NULL )
			return;
		int nBottomRightX = std::min( mpSelfEntity->GetSrcRect().BottomRight().mX, (int)mpMapObject->GetWidth()-1 );
		int nBottomRightY = std::min(  mpSelfEntity->GetSrcRect().BottomRight().mY, (int)mpMapObject->GetHight()-1 );

		for ( int x = nTopLeftX; x <= nBottomRightX; x ++ )
		{
			for ( int y = nTopLeftY; y <= nBottomRightY; y ++ )
			{
				CMapCell* tpCell = mpMapObject->GetCell( CWTPoint( x, y ) );
				LK_ASSERT( tpCell != NULL, continue );

				tpCell->Tick( *this );

				// �ҵ�һ������ʵ��Ϳ���
				if( mEntitysOnPedal.size() > 0 )
					return ;

			}
		}
	}

	// �������÷�Χ
	void Visit2()
	{
		// ���
		mEntitysOnPedal.clear();

		int nTopLeftX = std::max( mpSelfEntity->GetActRect().TopLeft().mX , 0 );
		int nTopLeftY = std::max(mpSelfEntity->GetActRect().TopLeft().mY, 0 );
		if ( mpMapObject == NULL )
			return;
		int nBottomRightX = std::min( mpSelfEntity->GetActRect().BottomRight().mX, (int)mpMapObject->GetWidth()-1 );
		int nBottomRightY = std::min(  mpSelfEntity->GetActRect().BottomRight().mY, (int)mpMapObject->GetHight()-1 );

		for ( int x = nTopLeftX; x <= nBottomRightX; x ++ )
		{
			for ( int y = nTopLeftY; y <= nBottomRightY; y ++ )
			{
				CMapCell* tpCell = mpMapObject->GetCell( CWTPoint( x, y ) );
				LK_ASSERT( tpCell != NULL, continue );

				tpCell->Tick( *this );

			}
		}
	}
	
};


// ����һ����Ʒ�����
struct MapCellDropPosSearcher
{
	MapCellDropPosSearcher( CWTPoint& rPos, CMapObject* pMapObject ) 
		: mPos( rPos ), mpMapObject( pMapObject ), mHasItem( false ) {}
	~MapCellDropPosSearcher() {}

	CWTPoint& mPos;
	CMapObject* mpMapObject;
	bool mHasItem; 

	int GetResult( ) { return EM_OBJFUN_NONE; }
	void SetResult( int )  {;} 

	//����ֵ: false-��ֹ����; true-��������
	bool operator ()( unsigned int unEntityID )
	{
		CEntity* tpDesEntity = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject( unEntityID );
		LK_ASSERT( tpDesEntity != NULL, return true); 

		if( tpDesEntity->IsItem() || tpDesEntity->IsRedStone() )
		{
			mHasItem = true;
			return false; // �ҵ�����ֹ
		}
		return true;
	}

	void Visit()
	{
		CMapCell* tpCell = mpMapObject->GetCell( mPos );
		LK_ASSERT( tpCell != NULL, return );

		tpCell->Tick( *this );
	}
};


// ����һ��NPC������(��̬����)
struct MapCellNpcCreatePosSearcher
{
	MapCellNpcCreatePosSearcher( CWTPoint& rPos, CMapObject* pMapObject, EEntityType nSrcType ) 
		: mPos( rPos ), mpMapObject( pMapObject ), mHasNpc( false ), mSrcType(nSrcType) {}
	~MapCellNpcCreatePosSearcher() {}

	CWTPoint& mPos;
	CMapObject* mpMapObject;
	bool mHasNpc; 
	EEntityType mSrcType;

	int GetResult( ) { return EM_OBJFUN_NONE; }
	void SetResult( int )  {;} 

	//����ֵ: false-��ֹ����; true-��������
	bool operator ()( unsigned int unEntityID )
	{
		CEntity* tpDesEntity = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject( unEntityID );
		LK_ASSERT( tpDesEntity != NULL, return true); 

		if( tpDesEntity->GetEntityType() == mSrcType ) // ͬ�಻����
		{
			mHasNpc = true;
			return false; // �ҵ�����ֹ
		}
		return true;
	}

	void Visit()
	{
		CMapCell* tpCell = mpMapObject->GetCell( mPos );
		LK_ASSERT( tpCell != NULL, return );

		tpCell->Tick( *this );
	}
};


// ����һ����������Ƿ��а�̯
struct MapCellStallSearcher
{
	MapCellStallSearcher( const CWTPoint& rPos, CMapObject* pMapObject ) 
		: mPos( rPos ), mpMapObject( pMapObject ), mHasStall( false ) {}
	~MapCellStallSearcher() {}

	const CWTPoint& mPos;
	CMapObject* mpMapObject;
	bool mHasStall;

	int GetResult( ) { return EM_OBJFUN_NONE; }
	void SetResult( int )  {;} 

	//����ֵ: false-��ֹ����; true-��������
	bool operator ()( unsigned int unEntityID )
	{
		CEntity* tpDesEntity = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject( unEntityID );
		LK_ASSERT( tpDesEntity != NULL, return true);

		if ( tpDesEntity->IsPlayer() && tpDesEntity->IsAlive() == true )
		{
			if (  ((CEntityPlayer*) tpDesEntity )->HasStall() == true )
			{
				mHasStall = true;
				return false; // �ҵ�����ֹ
			}
		}

		return true;
	}

	void Visit()
	{
		CMapCell* tpCell = mpMapObject->GetCell( mPos );
		LK_ASSERT( tpCell != NULL, return );

		tpCell->Tick( *this );
	}

};


// ����npc����,�����Ƿ�ռ��
//(��������npc���ܻ�������һ�����磬�������npc��)
struct MapCellNpcOccupiedSearcher
{
	MapCellNpcOccupiedSearcher( CWTPoint& rPos, CEntityNpc* pNpc ) 
		: mPos( rPos ), mpNpc( pNpc ), mIsOccupied( false ) {}
	~MapCellNpcOccupiedSearcher() {}

	CWTPoint& mPos;		//�����һ���Ǻ�npc��һ����ͼ�ϣ�����û����
	CEntityNpc* mpNpc;	//npc����
	bool mIsOccupied;	//ռ��

	int GetResult( ) { return EM_OBJFUN_NONE; }
	void SetResult( int )  {;} 

	//����ֵ: false-��ֹ����; true-��������
	bool operator ()( unsigned int unEntityID )
	{
		CEntity* tpDesEntity = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject( unEntityID );
		LK_ASSERT( tpDesEntity != NULL, return true); 

		// ����(����)npc��ͨ����
		if( mpNpc->IsFunNpc() )
		{
			mIsOccupied = false;
			return false; // ��ֹ����
		}
		// ����
		if( mpNpc->IsOgre() && tpDesEntity->IsNpc() )
		{
			mIsOccupied = true;
			return false; // ��ֹ����
		}
		
		return true;
	}

	void Visit()
	{
		CMapObject* pMapObj = mpNpc->GetMapObject();
		LK_ASSERT( pMapObj != NULL, return );

		CMapCell* tpCell = pMapObj->GetCell( mPos );
		if( tpCell == NULL )
			return;

		tpCell->Tick( *this );
	}
};



// �ڵ�������Ӫ
struct MapCellRedStoneSearcher
{
	MapCellRedStoneSearcher( CEntity* pNpc, int nRadius, int nCampID, CEntityPlayer **pIDList, int nSize, int nMetierID ) 
		:  mpNpc( pNpc ), mRadius( nRadius ), mCampID( nCampID ), mPlayerIDList( pIDList ), mArraySize( nSize ), mPlayerCount( 0 )
		,mMetierID( nMetierID )		
	{ }
	~MapCellRedStoneSearcher() {}					   
	
	CEntity* mpNpc;					// �ڵ�ʵ��	
	int		 mRadius;				// �ڵ������ð뾶
	int		 mCampID;				// ����������ӪID
	CEntityPlayer **mPlayerIDList;	// �洢��ҵ�����
	int			   mArraySize;	
	int			   mPlayerCount;	// ��ҵ�����
	int			   mMetierID;		// ְҵID

	int GetResult( ) { return EM_OBJFUN_NONE; }
	void SetResult( int )  {;} 

	bool operator ()( unsigned int unEntityID )
	{
		CEntity* tpDesEntity = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject( unEntityID );
		LK_ASSERT( tpDesEntity != NULL, return true); 

		// �ж��ǲ�����Ҳ������
		if( !tpDesEntity->IsPlayer() )
		{
			return true;
		}
		
		// �жϹ���ID
		if ( ( ( CEntityPlayer * )tpDesEntity )->GetNationality() != mCampID && mCampID != 0 )
		{
			return true;
		}
		
		// �ж�����
		if ( ( ( CEntityPlayer * )tpDesEntity )->GetMetier() != mMetierID && mMetierID != 0 )
		{
			return true;
		}
		
		// �����С�ж�
		if ( mPlayerCount >= mArraySize )
		{
			return false;
		}				
		
		mPlayerIDList[ mPlayerCount ]  = ( CEntityPlayer * )tpDesEntity;
		++mPlayerCount;
		return true;
	}
	
	// ����Ѱ���ڵ���������Ӫ�����
	void Visit( )
	{
		
		CMapObject* pMapObj = mpNpc->GetMapObject();
		LK_ASSERT( pMapObj != NULL, return );
					
		int nTopLeftX = std::max( mpNpc->GetPosX() - mRadius , 0 );
		int nTopLeftY = std::max( mpNpc->GetPosY() - mRadius, 0 );
		int nBottomRightX = std::min( mpNpc->GetPosX() + mRadius, (int)pMapObj->GetWidth()-1 );
		int nBottomRightY = std::min( mpNpc->GetPosY() + mRadius, (int)pMapObj->GetHight()-1 );

		for ( int x = nTopLeftX; x <= nBottomRightX; x ++ )
		{
			for ( int y = nTopLeftY; y <= nBottomRightY; y ++ )
			{
				CMapCell* tpCell = pMapObj->GetCell( CWTPoint( x, y ) );
				LK_ASSERT( tpCell != NULL, continue );
				tpCell->Tick( *this );
			}
		}				
	}
};


// �ڵ���������
struct MapCellCountryRedStoneSearcher
{
	MapCellCountryRedStoneSearcher( CEntity* pNpc, int nRadius, int nCountryID, CEntityPlayer **pIDList, int nSize ) 
		:  mpNpc( pNpc ), mRadius( nRadius ), mCountryID( nCountryID ), mPlayerIDList( pIDList ), mArraySize( nSize ), mPlayerCount( 0 )		
	{ }
	~MapCellCountryRedStoneSearcher() {}					   

	CEntity* mpNpc;					// �ڵ�ʵ��	
	int		 mRadius;				// �ڵ������ð뾶
	int		 mCountryID;				// �������Ĺ���ID
	CEntityPlayer **mPlayerIDList;	// �洢��ҵ�����
	int			   mArraySize;	
	int			   mPlayerCount;	// ��ҵ�����

	int GetResult( ) { return EM_OBJFUN_NONE; }
	void SetResult( int )  {;} 

	bool operator ()( unsigned int unEntityID )
	{
		CEntity* tpDesEntity = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject( unEntityID );
		LK_ASSERT( tpDesEntity != NULL, return true); 

		// �ж��ǲ�����Ҳ������
		if( !tpDesEntity->IsPlayer() )
		{
			return true;
		}

		// �жϹ���ID
		if ( ( ( CEntityPlayer * )tpDesEntity )->GetCountryID() != mCountryID )
		{
			return true;
		}

		// �����С�ж�
		if ( mPlayerCount >= mArraySize )
		{
			return false;
		}				

		mPlayerIDList[ mPlayerCount ]  = ( CEntityPlayer * )tpDesEntity;
		++mPlayerCount;
		return true;
	}

	// ����Ѱ���ڵ���������Ӫ�����
	void Visit( )
	{

		CMapObject* pMapObj = mpNpc->GetMapObject();
		LK_ASSERT( pMapObj != NULL, return );

		int nTopLeftX = std::max( mpNpc->GetPosX() - mRadius , 0 );
		int nTopLeftY = std::max( mpNpc->GetPosY() - mRadius, 0 );
		int nBottomRightX = std::min( mpNpc->GetPosX() + mRadius, (int)pMapObj->GetWidth()-1 );
		int nBottomRightY = std::min( mpNpc->GetPosY() + mRadius, (int)pMapObj->GetHight()-1 );

		for ( int x = nTopLeftX; x <= nBottomRightX; x ++ )
		{
			for ( int y = nTopLeftY; y <= nBottomRightY; y ++ )
			{
				CMapCell* tpCell = pMapObj->GetCell( CWTPoint( x, y ) );
				LK_ASSERT( tpCell != NULL, continue );
				tpCell->Tick( *this );
			}
		}				
	}
};

#endif // __ENTITY_SEACHER_IMP__
