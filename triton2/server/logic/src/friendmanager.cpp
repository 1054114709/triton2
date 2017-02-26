#include "westserver.h"
#include "friendmanager.h"


// CFriendItem class=================================================================================================


// ***********************************************************
//  Function:		AddFriend	
//  Description:	��Ӻ���
//  Input:			����ID��״̬�����ҵĹ�ϵ
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::AddFriend( int nSrcCharID, EPlayerShow enStat, EPlayerRels enRel ) 
{
	return AddFriend( nSrcCharID, enStat, enRel, 0 ) ;
}


// ***********************************************************
//  Function:		SetMyStatus	
//  Description:	��״̬
//  Input:			״̬
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::SetMyStatus( EPlayerShow enStat )
{
	mSettings.euMyStatus = enStat;
	return 0;
}

// ***********************************************************
//  Function:		AddFriend	
//  Description:	��Ӻ��� ������ؽ������ڼ��غ��ѵ�ʱ����ã�
//  Input:			����ID��״̬�����ҵĹ�ϵ����ID
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::AddFriend( int nSrcCharID, EPlayerShow enStat, EPlayerRels enRel, short nGroupID ) 
{
	st_friend key( nSrcCharID );
	key.enStatus = enStat;
	key.enRel2Me = enRel;
	key.nGroupId = nGroupID; 
	key.nIntimacyDegree = 0;
	key.nLastTimeAllOnline = time( NULL );
	return mFriends.insert(key);
}



// ***********************************************************
//  Function:		DelFriend	
//  Description:	ɾ������
//  Input:			����ID
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::DelFriend( int nSrcCharID )
{
	st_friend key( nSrcCharID );
	return mFriends.remove(key);
}



// ***********************************************************
//  Function:		DelEnemy	
//  Description:	ɾ�����
//  Input:			���ID
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2009.7.16
// **********************************************************
int		CFriendItem::DelEnemy( int nSrcCharID )
{
	st_enemy key( nSrcCharID );
	st_enemy* pEnemy = mEnemys.find(key);
	if (pEnemy == NULL)
		return -1;
	unsigned long ulOldTime = pEnemy->nKillTime;
	mEnemys.remove(key);
	st_enemy_map key2( ulOldTime, nSrcCharID );
	mEnemyKillTimeMap.remove(key2);
	return 0;
}



// ***********************************************************
//  Function:		MoveFriend	
//  Description:	�ƶ�����
//  Input:			����ID, Ŀ����ID
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.11.20
// **********************************************************
int		CFriendItem::MoveFriend( int nCharID, int nDesGroupID )
{
	if ( nDesGroupID < 0 || nDesGroupID > PLAYER_GROUP_COUNT )
	{
		return -1;
	}

	st_friend key( nCharID );
	st_friend* pfriend = mFriends.find(key);

	if( pfriend ) //�ҵ���
	{
		pfriend->nGroupId = nDesGroupID ;
		return 0;
	}
	return -1;
}

// ***********************************************************
//  Function:		AddBlack	
//  Description:	��Ӻ�����
//  Input:			����ID
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::AddBlack( int nSrcCharID ) 
{
	int nRet = mBlacks.insert(nSrcCharID);

	if( nRet == -2 ) 
		return ERROR_ADDBLACKFAIL;
	else if( nRet == -1 ) 
	{
		return ERROR_ADDBLACKFAIL_EXSIT;
	}

	return 0;
}


// ***********************************************************
//  Function:		IsBlack	
//  Description:	�Ƿ������
//  Input:			����ID
//  OutPut:			NULL
//  Return:			bool
//  Others:
//  Date:			2008.11.20
// **********************************************************
bool		CFriendItem::IsBlack( int nSrcCharID ) 
{
	return mBlacks.find(nSrcCharID) != NULL;
}


// ***********************************************************
//  Function:		DelBlack	
//  Description:	ɾ��������
//  Input:			����ID
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::DelBlack( int nSrcCharID ) 
{
	return mBlacks.remove(nSrcCharID);
}


// ***********************************************************
//  Function:		GetRefuseAll	
//  Description:	�����Ƿ�ܾ������������
//  Input:			0,1
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
unsigned char	CFriendItem::GetRefuseAll( ) const
{
	return mSettings.nIsRefuseAllAddInf;
}

// ***********************************************************
//  Function:		SetRefuseAll	
//  Description:	�����Ƿ�ܾ������������
//  Input:			0,1
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::SetRefuseAll( unsigned char nFlag ) 
{
	if ( nFlag == 0 || nFlag == 1 )
	{
		mSettings.nIsRefuseAllAddInf = nFlag;
	}
	else
	{
		LOG_ERROR( "FRIEND", "error in set refuse all, src flag = %d", nFlag );
	}
	return 0;
}


// ***********************************************************
//  Function:		GetLastRefresh	
//  Description:	�õ��ϴ�ˢ��ʱ��
//  Input:			NULL
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
unsigned int	CFriendItem::GetLastRefresh( ) const
{
	return mSettings.nLastRefrershTime;
}

// ***********************************************************
//  Function:		SetLastRefresh	
//  Description:	�����ϴ�ˢ��ʱ��
//  Input:			ʱ�� time_t
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::SetLastRefresh( unsigned int vTime )
{
	mSettings.nLastRefrershTime = vTime;
	return 0;
}

// ***********************************************************
//  Function:		GetMyStatus	
//  Description:	�õ��ҵ�״̬
//  Input:			NULL
//  OutPut:			NULL
//  Return:			EPlayerShow
//  Others:
//  Date:			2008.11.4
// **********************************************************
EPlayerShow  CFriendItem::GetMyStatus()
{
	return mSettings.euMyStatus;
}

// ***********************************************************
//  Function:		SetFriendStatus	
//  Description:	�ı����״̬
//  Input:			����ID��״̬
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::SetFriendStatus( int nSrcCharID, EPlayerShow enStat )
{
	st_friend key( nSrcCharID );
	st_friend* pFriend = mFriends.find( key );

	if( pFriend == NULL ) 
	{
		return -1;
	}

	pFriend->enStatus = enStat ;
	return 0;
}



// ***********************************************************
//  Function:		GetGroupName	
//  Description:	ȡ��������
//  Input:			��ID
//  OutPut:			NULL
//  Return:			����
//  Others:
//  Date:			2008.10.31
// **********************************************************
const char*	CFriendItem::GetGroupName( unsigned char nGroupID ) const
{
	return mSettings.szGroupName[ nGroupID ];
}


// ***********************************************************
//  Function:		GetFriendCharIDList	
//  Description:	�õ�ȫ�����ѵ�charid�б�
//  Input:			�Ƿ�Ҫ���ߵ�
//  OutPut:			�б�
//  Return:			�ɹ�=0
//  Others:
//  Date:			2008.11.1
// **********************************************************
int		CFriendItem::GetFriendCharIDList( std::vector<int>& rList, bool bIsOnlyOnline ) const
{
	for ( int i = 0 ; i < mFriends.GetNum(); ++i )
	{
		const st_friend* pFriend = mFriends.GetByIndex(i);
		if ( pFriend != NULL && (!bIsOnlyOnline || ( bIsOnlyOnline && pFriend->enStatus != AT_OFFLINE ) ) )
		{
			rList.push_back( pFriend->nCharID );
		}
	}
	return 0;
}


// ***********************************************************
//  Function:		GetBlackCharIDList	
//  Description:	�õ�ȫ��������id�б�
//  Input:			NULL
//  OutPut:			����ͷָ�룬 ����
//  Return:			�ɹ�=0
//  Others:
//  Date:			2008.11.1
// **********************************************************
int		CFriendItem::GetBlackCharIDList( int* pBlacks, int& nNum ) const
{
	nNum    = mBlacks.GetNum();
	if (nNum > 0)
		memcpy( pBlacks , mBlacks.GetByIndex(0), sizeof(int)*nNum );
	return 0;
}

// ***********************************************************
//  Function:		GetFriend	
//  Description:	����ID��ú�������
//  Input:			id, ��������
//  OutPut:			��������
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::GetFriend( int nCharID, st_friend& rFriend )
{
	st_friend key( nCharID );
	st_friend* pFriend = mFriends.find(key);

	if( pFriend == NULL ) // û�ҵ�
	{
		return -1;
	}

	rFriend = *pFriend ;
	return 0;
}


// ***********************************************************
//  Function:		IsFriend	
//  Description:	�ǲ����ҵĺ��ѣ�
//  Input:			id
//  OutPut:			NULL
//  Return:			bool
//  Others:
//  Date:			2008.11.4
// **********************************************************
bool	CFriendItem::IsFriend( int nCharID )
{
	st_friend key( nCharID );
	return mFriends.find(key) != NULL;
}

// ***********************************************************
//  Function:		IsEnemy	
//  Description:	�ǲ����ҵĳ�У�
//  Input:			id
//  OutPut:			NULL
//  Return:			bool
//  Others:
//  Date:			2008.12.18
// **********************************************************
bool	CFriendItem::IsEnemy( int nCharID )
{
	st_enemy key( nCharID );
	return mEnemys.find(key) != NULL;
}



// ***********************************************************
//  Function:		GetFriendNum	
//  Description:	�õ���������
//  Input:			NULL
//  OutPut:			NULL
//  Return:			bool
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::GetFriendNum( )
{
	return mFriends.GetNum();
}

// ***********************************************************
//  Function:		OnBeKilled	
//  Description:	������
//  Input:			ɱ���ҵ�charid
//  OutPut:			��ɱ������ɱ������, ��Ҫ�Ƴ��ĳ��ID
//  Return:			������Ѿ����ڵĳ�У�����1  �������ӵ� ����2  ����-1  ����
//  Others:
//  Date:			2009.7.14
// **********************************************************
int	CFriendItem::OnBeKilled( int nCharID, int& nBeKilled, int& nKilled,  int& nOutDelCharID)
{
	st_enemy key( nCharID );
	st_enemy* pEnemy = mEnemys.find(key);

	if(pEnemy) // �Ѵ��ڵĳ��
	{
		unsigned long _old_kill_time = pEnemy->nKillTime;
		pEnemy->nBeKilled += 1;
		pEnemy->nKillTime = time(0);
		nBeKilled = pEnemy->nBeKilled;
		nKilled   = pEnemy->nKilled;
		// �޸�map���ֵ(ɾ���¼�)
		st_enemy_map _todelmap( _old_kill_time, nCharID );
		mEnemyKillTimeMap.remove(_todelmap);
		mEnemyKillTimeMap.insert( st_enemy_map(time(0), nCharID) );
		return 1;
	}
	else
	{
		st_enemy _new( nCharID, 0, 1, 0, AT_ONLINE, time(0) );

		if( mEnemys.GetNum() >= ENEMIES_LIMIT ) // �����˳������  ��Ҫɾ��һ��
		{
			int nDelCharID = GetEarlyestEnemyNoLocked();
			if ( nDelCharID != 0 )
			{
				st_enemy _todel( nDelCharID );
				st_enemy* _todel_enemy = mEnemys.find(_todel);
				LK_ASSERT(_todel_enemy!=NULL, return -1);
				unsigned long _todel_KillTime = _todel_enemy->nKillTime;
				mEnemys.remove( _todel );

				st_enemy_map _todelmap( _todel_KillTime, nDelCharID );
				mEnemyKillTimeMap.remove(_todelmap);

				mEnemys.insert( _new );
				mEnemyKillTimeMap.insert( st_enemy_map( time(0), nCharID ) );
				nBeKilled = 1;
				nKilled   = 0;
				nOutDelCharID = nDelCharID;
				return 2;
			}
			else
			{
				return -1;
			}
		}
		// ��������
		mEnemys.insert( _new );
		mEnemyKillTimeMap.insert( st_enemy_map( time(0), nCharID ) );
		nBeKilled = 1;
		nKilled   = 0;
		return 2;
	}
	return -1;
}

// ***********************************************************
//  Function:		OnKilled	
//  Description:	ɱ����Ŀ�����
//  Input:			charid
//  OutPut:			ɱ�����Ĵ�������ɱ�Ĵ���
//  Return:			����ڳ���б�����true
//  Others:
//  Date:			2008.11.26
// **********************************************************
bool    CFriendItem::OnKilled( int nCharID, int& nKillHim, int& nBeKilled )
{
	st_enemy key( nCharID );
	st_enemy* pEnemy = mEnemys.find( key );

	if( pEnemy != NULL ) // �Ѵ��ڵĳ��
	{
		unsigned long _old_kill_time = pEnemy->nKillTime;
		pEnemy->nKilled += 1;
		pEnemy->nKillTime = time(0);
		nBeKilled = pEnemy->nBeKilled;
		nKillHim  = pEnemy->nKilled;
		// �޸�map���ֵ(ɾ���¼�)
		st_enemy_map _todelmap( _old_kill_time, nCharID );
		mEnemyKillTimeMap.remove(_todelmap);
		mEnemyKillTimeMap.insert( st_enemy_map(time(0), nCharID) );
		return true;
	}
	return false;

}



// ***********************************************************
//  Function:		GetTlvBuffer2	
//  Description:	�õ���е�TLV
//  Input:			PBEnemyData
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2008.11.27
// **********************************************************
void CFriendItem::GetTlvBuffer2( PBFriend* pBuffer )
{
	PBFriendGlobalData* tpGlobalData = pBuffer->mutable_global();

	for (int i = 0; i < PLAYER_GROUP_COUNT; ++i )
	{
		tpGlobalData->add_groupnames( GetGroupName(i+1) );
	}
	tpGlobalData->set_isrefuseall(GetRefuseAll()); 

	PBFriendData* tpFriendData = pBuffer->mutable_friend_();
	for ( int i = 0 ; i < mFriends.GetNum(); ++i )
	{
		st_friend* pFriend = mFriends.GetByIndex(i);
		if (pFriend)
		{
			tpFriendData->add_playerid(pFriend->nCharID);
			tpFriendData->add_groupid(pFriend->nGroupId);
			tpFriendData->add_rel2me(pFriend->enRel2Me);	
			tpFriendData->add_intimacydegree( pFriend->nIntimacyDegree );
			tpFriendData->add_lasttimeallonline( pFriend->nLastTimeAllOnline );	
			tpFriendData->add_dailyintimacy( pFriend->nDailyIntimacy );
			tpFriendData->add_lastupdatetime( pFriend->nLastUpdateTime );
		}
	}
	tpFriendData->set_blesstimes( mBlessTimes );
	
	PBEnemyData* tpEnemyData = pBuffer->mutable_enemy();
	for ( int i = 0 ; i < mEnemys.GetNum(); ++i )
	{
		st_enemy* pEnemy = mEnemys.GetByIndex(i);
		if (pEnemy)
		{
			tpEnemyData->add_playerid( pEnemy->nPlayerId );
			tpEnemyData->add_killed( pEnemy->nKilled );
			tpEnemyData->add_bekilled( pEnemy->nBeKilled );
			tpEnemyData->add_islocked( pEnemy->nIsLocked );
			tpEnemyData->add_killtime( pEnemy->nKillTime );
		}
	}

	for ( int i = 0 ; i < mBlacks.GetNum(); ++i )
	{
		int* pBlack = mBlacks.GetByIndex(i);
		if (pBlack)
			pBuffer->add_blacklist(*pBlack);
	}

	int nSize = (int)m_LatestContactList.size();
	for (int i = 0; i < nSize; i++)
	{
		int nCharID = m_LatestContactList[i];
		pBuffer->add_latestcontact(nCharID);
	}	
}



// ***********************************************************
//  Function:		CreateFromTlv2	
//  Description:	��TLV��ȡ���
//  Input:			PBEnemyData
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2008.11.27
// **********************************************************
void CFriendItem::CreateFromTlv2( PBFriend* pBuffer )
{
	if ( pBuffer == NULL )
	{
		LOG_ERROR( "FRIEND", "[ %s : %d ] pBuff is NULL", __LK_FILE__, __LINE__ ); 
		return;
	}

	if (pBuffer->has_global())
	{
		PBFriendGlobalData* tpGlobalData = pBuffer->mutable_global();
		if (tpGlobalData->groupnames_size() == PLAYER_GROUP_COUNT)
		{	
			for (int i = 0; i < PLAYER_GROUP_COUNT; ++i )
			{
				SetGroupName( i+1, tpGlobalData->groupnames(i).c_str() );
				//tpGlobalData->add_groupnames( GetGroupName(i+1) );
			}
		}
		else
		{
			LOG_ERROR("FRIEND", "read group name num %d", tpGlobalData->groupnames_size());
		}
		if (tpGlobalData->has_isrefuseall())
			SetRefuseAll( tpGlobalData->isrefuseall() );
	}

	if (pBuffer->has_friend_())
	{
		PBFriendData* tpFriendData = pBuffer->mutable_friend_();

		for ( int i = 0 ; i < tpFriendData->playerid_size(); ++i )
		{
			st_friend stnew;
			stnew.nCharID = tpFriendData->playerid(i);
			stnew.nGroupId = tpFriendData->groupid(i);
			stnew.enRel2Me = (EPlayerRels)tpFriendData->rel2me(i);
			if ( i < tpFriendData->intimacydegree_size() )
			{
				stnew.nIntimacyDegree = tpFriendData->intimacydegree( i );			
			}
			if ( i < tpFriendData->lasttimeallonline_size() )
			{
				stnew.nLastTimeAllOnline = tpFriendData->lasttimeallonline(i);
			}		
			if ( i < tpFriendData->dailyintimacy_size() )
			{
				stnew.nDailyIntimacy = tpFriendData->dailyintimacy( i );
			}
			if ( i < tpFriendData->lastupdatetime_size( ) )
			{
				stnew.nLastUpdateTime = tpFriendData->lastupdatetime( i );
			}
			
			mFriends.insert(stnew);		
		}
		mBlessTimes = tpFriendData->blesstimes();
	}

	if (pBuffer->has_enemy())
	{
		PBEnemyData* tpEnemyData = pBuffer->mutable_enemy();
		LK_ASSERT( tpEnemyData , return );
		for ( int i = 0 ; i < tpEnemyData->playerid_size() ; ++i )
		{
			st_enemy stnew( tpEnemyData->playerid(i), tpEnemyData->killed(i), tpEnemyData->bekilled(i), tpEnemyData->islocked(i)
				, 0, tpEnemyData->killtime(i) );
			mEnemys.insert(stnew);	
			st_enemy_map stnewmap( tpEnemyData->killtime(i), tpEnemyData->playerid(i) );
			mEnemyKillTimeMap.insert(stnewmap);
		}
	}

	for ( int i = 0 ; i < pBuffer->blacklist_size(); ++i )
	{
		mBlacks.insert( pBuffer->blacklist(i) );
	}

	int nSize = pBuffer->latestcontact_size();
	for (int i = 0; i < nSize; i++)
	{
		int nCharID = pBuffer->latestcontact(i);
		m_LatestContactList.push_back(nCharID);
	}
}


// ***********************************************************
//  Function:		SetEnemyState	
//  Description:	���ó�е�״̬
//  Input:			charid
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2008.11.28
// **********************************************************
void    CFriendItem::SetEnemyState( int nCharID, unsigned char nState )
{
	st_enemy key( nCharID );
	st_enemy* pEnemy = mEnemys.find( key );

	if( pEnemy ) 
	{
		pEnemy->nState = nState ;
	}
}



// ***********************************************************
//  Function:		GetEnemyCharIDList	
//  Description:	�õ�ȫ����е�charid�б�
//  Input:			�Ƿ�Ҫ���ߵ�
//  OutPut:			�б�
//  Return:			�ɹ�=0
//  Others:
//  Date:			2008.11.1
// **********************************************************
int		CFriendItem::GetEnemyCharIDList( std::vector<int>& rList, bool bIsOnlyOnline ) const
{
	for ( int i = 0 ; i < mEnemys.GetNum(); ++i )
	{
		const st_enemy* pEnemy = mEnemys.GetByIndex(i);
		LK_ASSERT( pEnemy, continue );
		if (!bIsOnlyOnline || ( bIsOnlyOnline && pEnemy->nState != AT_OFFLINE ) )
		{
			rList.push_back( pEnemy->nPlayerId );
		}
	}

	return 0;
}


// ***********************************************************
//  Function:		GetEnemy	
//  Description:	����ID��ó������
//  Input:			id, ��������
//  OutPut:			�������
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.12.5
// **********************************************************
int		CFriendItem::GetEnemy( int nCharID, st_enemy& rEnemy )
{
	st_enemy key( nCharID );
	st_enemy* pEnemy = mEnemys.find( key );

	if( pEnemy == NULL ) // û�ҵ�
	{
		return -1;
	}

	rEnemy = *pEnemy ;
	return 0;
}

// ***********************************************************
//  Function:		LockEnemy	
//  Description:	�������
//  Input:			id
//  OutPut:			NULL
//  Return:			�ɹ� ��������״̬
//  Others:
//  Date:			2008.12.8
// **********************************************************
int		CFriendItem::LockEnemy( int nDesCharID, int nLockType )
{
	if ( nDesCharID <= 0 )
		return -1;

	st_enemy key( nDesCharID );
	st_enemy* pEnemy = mEnemys.find( key );

	if( pEnemy==NULL ) // û�ҵ�
	{
		return -1;
	}

	if ( nLockType == LOCK_TYPE_LOCK )
		pEnemy->nIsLocked = 1;
	else if ( nLockType == LOCK_TYPE_FREE )
		pEnemy->nIsLocked = 0;
	else
		return -1;

	return pEnemy->nIsLocked;
}


// ***********************************************************
//  Function:		SetGroupName	
//  Description:	����������
//  Input:			��ID������
//  OutPut:			NULL
//  Return:			0=�ɹ�
//  Others:
//  Date:			2008.10.31
// **********************************************************
int		CFriendItem::SetGroupName( unsigned char nGroupID, const char* szGroupName )
{
	if ( nGroupID <= 0 || nGroupID >= PLAYER_GROUP_COUNT + 1 )
	{
		LOG_ERROR( "FRIEND", "error in SetGroupName groupid = %d", nGroupID );
		return -1;
	}
	else
	{
		strncpy( mSettings.szGroupName[ nGroupID ], szGroupName, GROUP_NAME_LENGTH - 1 );
		mSettings.szGroupName[ nGroupID ][ GROUP_NAME_LENGTH - 1 ] = '\0';
	}
	return 0;
}

// ***********************************************************
//  Function:		GetEarlyestEnemyNoLocked	
//  Description:	�õ������ û�����ĳ��
//  Input:			NULL
//  OutPut:			NULL
//  Return:			charid
//  Others:
//  Date:			2009.7.14
// **********************************************************
int		CFriendItem::GetEarlyestEnemyNoLocked()
{
	for (int i = 0 ; i < ENEMIES_LIMIT; ++i )
	{
		st_enemy_map* pEnemy = mEnemyKillTimeMap.GetByIndex(i);
		if (pEnemy != NULL)
		{
			// ��������û
			st_enemy key( pEnemy->nCharID );
			st_enemy* pEnemyData = mEnemys.find(key);
			if ( pEnemyData == NULL )
			{
				LOG_ERROR("FRIEND", "in GetEarlyestEnemyNoLocked can't find enemy!! id=%d", pEnemy->nCharID );
				continue;
			}
			if ( pEnemyData->nIsLocked == 0 )
				return pEnemy->nCharID;	
		}
	}
	return 0;
}

// ���������ϵ�ˣ�����Ѵ��ڣ����Ȱ�ɾ�����м�¼���ٰ���������ϵ����ӵ�ͷ����
// ��������ڣ�ÿ�ζ���������ͷ����ͬʱɾ��ĩβ���
int CFriendItem::AddLatestContacter(int nCharID)
{
	int nCount = m_LatestContactList.size();
	for (int i = 0; i < nCount; i++)
	{
		if (m_LatestContactList[i] == nCharID)
		{
			m_LatestContactList.erase(m_LatestContactList.begin() + i);
		}
	}
	
	int nSize = m_LatestContactList.size();
	if (nSize >= LATEST_CONTACT_MAX)
	{
		m_LatestContactList.erase(m_LatestContactList.begin());
	}
	m_LatestContactList.push_back(nCharID);

	return 0;
}

int CFriendItem::GetContacterCount()
{
	return m_LatestContactList.size();
}

int CFriendItem::GetContacter(int nIndex)
{
	int nCount = GetContacterCount();
	if (nIndex < 0 || nIndex >= nCount)
	{
		return 0;
	}

	return m_LatestContactList[nIndex];
}

st_friend *CFriendItem::GetFriendByRoleID( int nRoleID )
{
	return mFriends.find( nRoleID );
}

// ***********************************************************
//  Function:		UpdateLastTimeAllOnLine	
//  Description:	�������к��ѵ����һ��ͬʱ����ʱ��
//  Date:			2011.06.27
// **********************************************************
int	CFriendItem::UpdateLastTimeAllOnLine( int nRoleID, int nTime )
{
	st_friend *tpFrind = mFriends.find( nRoleID );
	if ( tpFrind == NULL )
	{
		return -1;
	}		
	tpFrind->nLastTimeAllOnline = nTime;
	return 0;	
}

// ***********************************************************
//  Function:		UpdateIntimacyDegree	
//  Description:	���º�ĳ�����ѵ����ܶ�
//  Date:			2011.06.27
// **********************************************************
int	CFriendItem::UpdateIntimacyDegree( int nRoleID, int nValue )
{
	st_friend *tpFrind = mFriends.find( nRoleID );
	if ( tpFrind == NULL )
	{
		return -1;
	}	
	tpFrind->nIntimacyDegree = nValue;
	return 0;
}

// ***********************************************************
//  Function:		GetFriendIntimacyDegree	
//  Description:	��ȡĳ�����ѵ����ܶ�
//  Date:			2011.06.27
// **********************************************************
int	CFriendItem::GetFriendIntimacyDegree( int nRoleID )
{
	st_friend *tpFrind = mFriends.find( nRoleID );
	if ( tpFrind == NULL )
	{
		return 0;
	}	
	return tpFrind->nIntimacyDegree;	
}

// ***********************************************************
//  Function:		GetLastTimeAllOnLine	
//  Description:	��ȡ��ĳ�����ѵ����һ�ι�ͬ����ʱ��
//  Date:			2011.06.27
// **********************************************************
int	CFriendItem::GetLastTimeAllOnLine( int nRoleID )
{
	st_friend *tpFrind = mFriends.find( nRoleID );
	if ( tpFrind == NULL )
	{
		return 0;
	}	
	return tpFrind->nLastTimeAllOnline;	
}

// ***********************************************************
//  Function:		InsertLevelIntervalInfo	
//  Description:	
//  Date:			2011.03.08
// **********************************************************
int CFriendBlessConfig::InsertBlessExpInfo( int nTimes, int nOgreNum )
{
	unsigned int tIndex = 0;	
	for ( ; tIndex < ARRAY_CNT( mBlessExpInfoList ) ; ++tIndex )
	{
		if ( mBlessExpInfoList[tIndex].mTimes <= 0 || nTimes < mBlessExpInfoList[tIndex].mTimes )
		{
			break;
		}
	}		

	if ( mBlessExpInfoList[tIndex].mTimes > 0 )
	{
		for (unsigned int i = tIndex + 1; i < ARRAY_CNT( mBlessExpInfoList ); ++i )
		{
			CBlessExpInfo tBlessInfo = mBlessExpInfoList[i];
			mBlessExpInfoList[i] = mBlessExpInfoList[tIndex];
			mBlessExpInfoList[tIndex] = tBlessInfo;
		}
	}

	mBlessExpInfoList[tIndex].mOgreNum = nOgreNum;
	mBlessExpInfoList[tIndex].mTimes = nTimes;
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetBlessExpInfo	
//  Description:	
//  Date:			2011.03.08
// **********************************************************
int CFriendBlessConfig::GetBlessExpInfo( int nTimes )
{
	for ( unsigned int i = 0; i < ARRAY_CNT( mBlessExpInfoList ); ++i )
	{
		if ( nTimes <= mBlessExpInfoList[i].mTimes )
		{
			return mBlessExpInfoList[i].mOgreNum;
		}
	}
	return 0;
}

// ***********************************************************
//  Function:		Initialize	
//  Description:	
//  Date:			2011.06.28
// **********************************************************
int CSwornTeam::Initialize()
{
	mSwornID = 0;
	mSwornMemberList.initailize();
	memset( mSwornName, 0, sizeof( mSwornName ) );
	mCampID = 0;
	return 0;
}

// ***********************************************************
//  Function:		KickMember	
//  Description:	
//  Date:			2011.06.28
// **********************************************************
int CSwornTeam::KickMember( int nRoleID, int nKickedRoleID )
{
	if ( nRoleID != mSwornID )
	{
		return ERROR_SWORN_KICK_HASNORIGHT;
	}
	if ( HasMember( nRoleID ) == false )
	{
		return ERROR_SWORN_KICK_NOTINSWORNTEAM;
	}
	DeleteMember( nKickedRoleID );
	return SUCCESS;
}

// ***********************************************************
//  Function:		LeaveSwornTeam	
//  Description:	
//  Date:			2011.06.28
// **********************************************************
int CSwornTeam::LeaveSwornTeam( int nRoleID )
{
	if ( HasMember( nRoleID ) == false )
	{
		return ERROR_SWORN_LEAVE_NOTINSWORNTEAM;
	}		
	DeleteMember( nRoleID );
	// ������ϴ��˳�������ѡ���ϴ�
	if ( nRoleID == mSwornID )
	{	
		mSwornID = FindFirstPos(  );
	}	
	return SUCCESS;
}

// ***********************************************************
//  Function:		DisbandSwornTeam	
//  Description:	
//  Date:			2011.06.28
// **********************************************************
int CSwornTeam::DisbandSwornTeam( int nRoleID )
{
	if ( HasMember( nRoleID ) == false )
	{
		return ERROR_SWORN_LEAVE_NOTINSWORNTEAM;
	}	
	return SUCCESS;
}	

// ***********************************************************
//  Function:		HasMember	
//  Description:	
//  Date:			2011.06.28
// **********************************************************
bool CSwornTeam::HasMember( int nRoleID )
{
	SwornMemberList::iterator it = mSwornMemberList.begin();
	for ( ; it != mSwornMemberList.end(); ++it )
	{
		if ( it->mRoleID == nRoleID )
		{
			return true;
		}
	}
	return false;
}

// ***********************************************************
//  Function:		DeleteMenber	
//  Description:	
//  Date:			2011.06.28
// **********************************************************
int CSwornTeam::DeleteMember( int nRoleID )
{
	SwornMemberList::iterator it = mSwornMemberList.begin();
	for ( ; it != mSwornMemberList.end(); ++it )
	{
		if ( it->mRoleID == nRoleID )
		{				
			mSwornMemberList.erase( it );			
			// ���µ�������
			ChangePos( );
			return 0;
		}
	}
	return -1;
}

// ***********************************************************
//  Function:		FindFirstPos	
//  Description:	�ϴ��뿪������ѡ���ϴ�
//  Date:			2011.06.28
// **********************************************************
int CSwornTeam::FindFirstPos()
{	
	int tRoleID = 0;
	int tRolePos = 100;
	SwornMemberList::iterator it = mSwornMemberList.begin();		
	for ( ; it != mSwornMemberList.end(); ++it )
	{
		if ( it->mTeamPos < tRolePos )
		{
			tRoleID = it->mRoleID;
			tRolePos = it->mTeamPos;			
		}
	}
	return tRoleID;
}

// ***********************************************************
//  Function:		GetTeamPos	
//  Description:	��ȡĳ���˵Ľ����λ
//  Date:			2011.06.29
// **********************************************************
int CSwornTeam::GetTeamPos( int nRoleID )
{
	SwornMemberList::iterator it = mSwornMemberList.begin();		
	for ( ; it != mSwornMemberList.end(); ++it )
	{
		if ( it->mRoleID == nRoleID )
		{			
			return it->mTeamPos;			
		}
	}
	return 0;
}

// ***********************************************************
//  Function:		ChangeRoleStatus	
//  Description:	
//  Date:			2011.06.28
// **********************************************************
int CSwornTeam::ChangeRoleStatus( int nRoleID, int nStatus )
{
	SwornMemberList::iterator it = mSwornMemberList.begin();		
	for ( ; it != mSwornMemberList.end(); ++it )
	{
		if ( it->mRoleID == nRoleID )
		{			
			it->mRoleStatus = nStatus;			
			break;
		}
	}
	return 0;
}

// ***********************************************************
//  Function:		GetOnLineNum	
//  Description:	
//  Date:			2011.06.29
// **********************************************************
int CSwornTeam::GetOnLineNum( )
{
	int tNum = 0;
	SwornMemberList::iterator it = mSwornMemberList.begin();		
	for ( ; it != mSwornMemberList.end(); ++it )
	{
		if ( it->mRoleStatus == EROLE_STATUS_ONLINE )
		{			
			++tNum;						
		}
	}
	return tNum;
}

// ***********************************************************
//  Function:		SetFromPB	
//  Description:	
//  Date:			2011.06.28
// **********************************************************
int CSwornTeam::SetFromPB( PBSwornTeam &rSwornTeam )
{
	for ( int i = 0; i < rSwornTeam.swornmember_size(); ++i )
	{
		CSwornMember tMember;
		tMember.mRoleID = rSwornTeam.mutable_swornmember( i )->roleid();
		tMember.mTeamPos = rSwornTeam.mutable_swornmember( i )->teampos();
		mSwornMemberList.push_back( SwornMemberList::value_type( tMember ) );
	}	
	return SUCCESS;
}

// ***********************************************************
//  Function:		CreateTlvPB	
//  Description:	
//  Date:			2011.06.28
// **********************************************************
int CSwornTeam::CreateTlvPB( PBSwornTeam &rSwornTeam )
{
	SwornMemberList::iterator it = mSwornMemberList.begin();
	for ( ; it != mSwornMemberList.end(); ++it )
	{
		PBSwornMember *tpMember = rSwornTeam.add_swornmember();
		tpMember->set_roleid( it->mRoleID );
		tpMember->set_teampos( it->mTeamPos );
	}	
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetRoleIDList	
//  Description:	
//  Date:			2011.06.28
// **********************************************************
int CSwornTeam::GetRoleIDList( int *pRoleIDList, int &rNum )
{
	if ( pRoleIDList == NULL )
	{
		return -1;
	}
	int tNum = rNum;
	rNum = 0;
	SwornMemberList::iterator it = mSwornMemberList.begin();
	for ( ; it != NULL; ++it )
	{
		if ( rNum < tNum )
		{
			pRoleIDList[rNum] = it->mRoleID;
			++rNum;
		}
	}	
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetMaxPos	
//  Description:	
//  Date:			2011.08.30
// **********************************************************
int CSwornTeam::GetMaxPos()
{
	int tRolePos = 0;
	SwornMemberList::iterator it = mSwornMemberList.begin();		
	for ( ; it != mSwornMemberList.end(); ++it )
	{
		if ( it->mTeamPos > tRolePos )
		{
			tRolePos = it->mTeamPos;
		}
	}
	return tRolePos;
}

// ***********************************************************
//  Function:		ChangePos	
//  Description:	��Ϊ�뿪���ı���λ
//  Date:			2011.09.06
// **********************************************************
int CSwornTeam::ChangePos( )
{
	int tRolePos = 0;
	for ( int i = 1; i <= mSwornMemberList.size(); ++i )
	{
		int tMinPos = 100;		
		SwornMemberList::iterator tChangePos = NULL;
		SwornMemberList::iterator it = mSwornMemberList.begin();		
		for ( ; it != mSwornMemberList.end(); ++it )
		{
			if ( it->mTeamPos < i )
			{
				 continue;
			}
			if ( it->mTeamPos < tMinPos )
			{
				tMinPos = it->mTeamPos;
				tChangePos = it;
			}
		}
		if ( tChangePos != NULL )
		{
			tChangePos->mTeamPos = i;
		}
	}	
	return 0;
}