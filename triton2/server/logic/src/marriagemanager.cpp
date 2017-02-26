#include "marriagemanager.h"
#include "sceneobj_manager.h"
#include "template.h"
#include "timermanager.h"
#include "scenelogic.h"

CSharedMem *CMarriageManager::mShmPtr = NULL;

template<> CMarriageManager *CSingleton< CMarriageManager >::spSingleton = NULL;

// ***********************************************************
//  Function:		Initialize
//  Description:				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
int CMarriageManager::Initialize( )
{
	memset( &mCampInfo, 0, sizeof( mCampInfo ) );
	mMarriageInfoList.initailize();
	mWeddingList.initailize();
	mMarriageApplyInfo.initailize();
	mOtherCampMarriageInfo.initailize();
	memset( mNpcPath, 0, sizeof( mNpcPath ) );
	mWeddingTimeInfo.initailize();
	mWeddingTimer.initailize();
	return SUCCESS;
}

// ***********************************************************
//  Function:		Resume
//  Description:				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
int CMarriageManager::Resume()
{
	return SUCCESS;
}

// ***********************************************************
//  Function:		operator new
//  Description:				
//  Output:			
//  Date:	02/23/2010
// *********************************************************
void *CMarriageManager::operator new( size_t nSize )
{
	return ( void* ) mShmPtr->CreateSegment( nSize );
}

// ***********************************************************
//  Function:		operator delete
//  Description:				
//  Output:			
//  Date:	02/23/2010
// *********************************************************
void CMarriageManager::operator delete( void *pPointer )
{
	
}

// ***********************************************************
//  Function:		CountSize
//  Description:				
//  Output:			
//  Date:	02/23/2010
// *********************************************************
unsigned int CMarriageManager::CountSize()
{
	return sizeof( CMarriageManager );
}

// ***********************************************************
//  Function:		Initialize
//  Description:				
//  Output:			
//  Date:	02/28/2010
// *********************************************************
int CMarriageInfo::Initialize()
{
	memset( mGroomName, 0, sizeof( mGroomName ) );
	memset( mBrideName, 0, sizeof( mGroomName ) );
	mGroomID = 0;	
	mBrideID = 0;
	mMarriageStatus = MARRIAGESTATUS_MARRY ;
	mWeddingTime = 0;
	mWeddingTimeLength = 0;
	mCampSequence = 0;
	mServerSequence = 0;
	mWeddingModule = 0;
	mCampID = 0;
	memset( mWeddingNpcPosIndex, 0, sizeof( mWeddingNpcPosIndex ) );
	memset( mWeddinNpcID, 0, sizeof( mWeddinNpcID ) );
	mWeddingEventStatus = 0;	
	mGroomKeepsakeIndex = -1;
	mGroomKeepsakeStatus = KEEPSAKSTATUS_EMPTY;
	mBrideKeepsakeIndex = -1;
	mBrideKeepsakeStatus = KEEPSAKSTATUS_EMPTY;
	memset( mSynchMark, 0, sizeof( mSynchMark ) );	
	mWaitSynMark = 0;
	return SUCCESS;
}

// ***********************************************************
//  Function:		Resume
//  Description:				
//  Output:			
//  Date:	02/28/2010
// *********************************************************
int CMarriageInfo::Resume()
{
	return SUCCESS;
}

// ***********************************************************
//  Function:		JudgeTimeInvalidate
//  Description:	�ж�ĳ�����ʱ���Ƿ�����ڵ�ʱ���໥��ͻ			
//  Output:			
//  Date:	02/24/2010
// *********************************************************
bool CMarriageInfo::JudgeTimeValide( int nTime, int nTimeLength )
{		
	if ( nTime > mWeddingTime )
	{
		if (  ( nTime - mWeddingTime ) >= ( mWeddingTimeLength + WEDDING_TIME_DUARING ) )
		{
			return true;
		}
	}
	
	if ( mWeddingTime > nTime )
	{
		if ( ( mWeddingTime - nTime ) >= nTimeLength )
		{
			return true;
		}		 
	}
	
	return false;
}

// ***********************************************************
//  Function:		CheckSynchMark
//  Description:	����Ƿ����е㶼��������Ҫͬ����λ��			
//  Output:			
//  Date:	04/16/2010
// *********************************************************
bool CMarriageInfo::CheckSynchMark( )
{
	bool tResult = true;
	for ( int i = 0; i < (int)ARRAY_CNT( mSynchMark ); ++i )
	{
		if ( mSynchMark[i] < 0 )
		{
			continue;
		}
		
		if ( mSynchMark[i] != mWaitSynMark && mWeddinNpcID[i] > 0 )
		{
			tResult = false;
			break;
		}	
	}
	return tResult;
}

// ***********************************************************
//  Function:		GetWeddingStatus
//  Description:	��ȡ����ľ���״̬			
//  Output:			
//  Date:	02/24/2010
// *********************************************************	
int CMarriageInfo::GetWeddingStatus( )
{
	if ( mMarriageStatus == MARRIAGESTATUS_MARRY )
	{
		return WEDDINGSTATUS_NOTSET;
	}	
	
	int tTimeNow = time( NULL );
	if ( mMarriageStatus == MARRIAGESTATUS_WEDDINGEND || mMarriageStatus == MARRIAGESTATUS_WEDDINGFAILED )
	{
		return	WEDDINGSTATUS_FINISHED;
	}		
	
	if ( mWeddingTime - tTimeNow > WEDDING_TIPSTIME )
	{
		return WEDDINGSTATUS_NOTINTIME;
	}	
	
	if ( mWeddingTime - tTimeNow >= 0 && mWeddingTime - tTimeNow <= WEDDING_TIPSTIME )
	{
		return	WEDDINGSTATUS_TIMENEAR;
	}
	
	if ( tTimeNow - mWeddingTime >= 0 && tTimeNow - mWeddingTime <= WEDDING_VALIDETIME )
	{
		return	WEDDINGSTATUS_INTIME;
	}
	
	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	if ( tpMarriageConfig == NULL )
	{
		return WEDDINGSTATUS_EXPIRED;
	}
	
	// ����Ƿ��Ѿ���������ʱ��
	if ( tTimeNow - mWeddingTime >= tpMarriageConfig->mWeddinInfo[mWeddingModule].mWeddingLength*60 )
	{
		return WEDDINGSTATUS_EXPIRED;		
	}
	
	if ( tTimeNow - mWeddingTime >= WEDDING_VALIDETIME && mMarriageStatus == MARRIAGESTATUS_WEDDINGINWAIT )
	{
		return WEDDINGSTATUS_EXPIRED;
	}
		
	return 	WEDDINGSTATUS_INTIME;
}

// ***********************************************************
//  Function:		InitialWeddingInfo
//  Description:	��ʼ��������Ϣ			
//  Output:			
//  Date:	04/17/2010
// *********************************************************	
void CMarriageInfo::InitialWeddingInfo()
{
	InitializeSyncMark();
	InitializeNpcID();
	InitializeNpcPosIndex();
	mWaitSynMark = 0;	
}

// ***********************************************************
//  Function:		CreatMarriageInfo
//  Description:	����һ��������Ϣ			
//  Output:			
//  Date:	02/26/2010
// *********************************************************
CMarriageInfo * CMarriageManager::CreatMarriageInfo( const char *pGroomName, int nGroomID, const char *pBrideName, int nBrideID, int nWeddingTime, int nWeddingTimeLength, int nWeddingModule, int nCampID )
{
	if ( pGroomName == NULL || pBrideName == NULL )
	{
		return NULL;
	}
	
	 CMarriageInfo *tpGroomMarriageInfo = GetMarriageByRoleID( nGroomID );
	 CMarriageInfo *tpBrideMarriageInfo = GetMarriageByRoleID( nBrideID );
	 if ( tpGroomMarriageInfo != NULL || tpBrideMarriageInfo != NULL )
	 {			
		return NULL;
	 }
	
	CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().CreateObject( OBJTYPE_MARRIAGEINFO );
	if ( tpMarriageInfo == NULL )
	{
		return NULL;
	}
	tpMarriageInfo->SetGroomName( pGroomName );
	tpMarriageInfo->SetGroomID( nGroomID );
	tpMarriageInfo->SetBrideName( pBrideName );
	tpMarriageInfo->SetBrideID( nBrideID );
	tpMarriageInfo->SetWeddingTime( nWeddingTime );
	tpMarriageInfo->SetWeddingTimeLength( nWeddingTimeLength );
	tpMarriageInfo->SetWeddingModule( nWeddingModule );
	tpMarriageInfo->SetCampSequence( mCampInfo.mMarriageNum );
	tpMarriageInfo->SetCampID( nCampID );
	++mCampInfo.mMarriageNum;	
	if ( nWeddingTime > 0 )
	{
		tpMarriageInfo->SetMarriageStatus( MARRIAGESTATUS_WEDDINGINWAIT );
	}
	else
	{
		tpMarriageInfo->SetMarriageStatus( MARRIAGESTATUS_MARRY );	
	}
	return tpMarriageInfo;
}

// ***********************************************************
//  Function:		InsertMarriageInfo
//  Description:	����һ����ҵĻ�����Ϣ			
//  Output:			
//  Date:	02/26/2010
// *********************************************************
int CMarriageManager::InsertMarriageInfo( int nServerSequence, CMarriageInfo *tpMarriageInfo )
{  
	if ( tpMarriageInfo == NULL )
	{
		return -1;
	}
	
	tpMarriageInfo->SetServerSequence( nServerSequence );
	mMarriageInfoList.insert( MarriageInfoList::value_type( nServerSequence, tpMarriageInfo->get_id() ) );
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetMarriageInfo
//  Description:	��ȡ��ҵĻ�����Ϣ			
//  Output:			
//  Date:	02/26/2010
// *********************************************************
CMarriageInfo * CMarriageManager::GetMarriageInfo( int nServerSequenceID )
{ 
	CMarriageInfo *tpMarriageInfo = NULL;
	MarriageInfoList::iterator it = mMarriageInfoList.find( nServerSequenceID );	
	if ( it != mMarriageInfoList.end() )
	{  		
		tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
	}
	return tpMarriageInfo;
}
 
// ***********************************************************
//  Function:		GetMarriageByRoleID
//  Description:	��ȡĳ����ҵ���Ϣ��ͨ����ɫID			
//  Output:			
//  Date:	02/26/2010
// *********************************************************
CMarriageInfo * CMarriageManager::GetMarriageByRoleID( unsigned int nRoleID )
{
	for ( MarriageInfoList::iterator it = mMarriageInfoList.begin(); it != mMarriageInfoList.end(); ++it )
	{
		CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		if ( tpMarriageInfo == NULL )
		{
			LOG_ERROR( "marriage","can not find marriageinfo by id:%d, roleid:%d", it->first, nRoleID );
			continue;
		}
		
		if ( tpMarriageInfo->mGroomID == nRoleID || tpMarriageInfo->mBrideID == nRoleID )
		{
			return tpMarriageInfo;
		}
	} 		
	
	return NULL;
}

// ***********************************************************
//  Function:		DeleteMarriageInfo
//  Description:	ɾ��ĳ��������Ϣ			
//  Output:			
//  Date:	02/26/2010
// *********************************************************
int CMarriageManager::DeleteMarriageInfo( int nServerSequenceID )
{		
	MarriageInfoList::iterator it = mMarriageInfoList.find( nServerSequenceID );
	if ( it != mMarriageInfoList.end() )
	{
		CSceneObjManager::GetSingleton().DestroyObject( it->second );
		mMarriageInfoList.erase( it );
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetWeddingMarriageInfo
//  Description:	��ȡ��ǰ���Խ��л���ļ���			
//  Output:			
//  Date:	02/26/2010
// *********************************************************
CMarriageInfo *CMarriageManager::GetWeddingMarriageInfo( )
{
	int tTimeNow = time( NULL );
	for ( MarriageInfoList::iterator it = mMarriageInfoList.begin(); it != mMarriageInfoList.end(); ++it )
	{
		CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		if ( tpMarriageInfo == NULL )
		{
			LOG_ERROR( "marriage","can not find marriageinfo by id:%d ", it->first );
			continue;
		}
				
		if ( ( tpMarriageInfo->GetMarriageStatus() == MARRIAGESTATUS_WEDDINGINWAIT ) && ( tTimeNow >= tpMarriageInfo->GetWeddingTime() ) && tTimeNow <= ( tpMarriageInfo->mWeddingTime + tpMarriageInfo->mWeddingTimeLength ) )
		{
			return tpMarriageInfo;	
		} 			
	} 		
	return NULL;
}

// ***********************************************************
//  Function:		CheckWeddingTime
//  Description:	������ʱ���Ƿ����Ҫ��			
//  Output:			
//  Date:	02/26/2010
// *********************************************************
bool CMarriageManager::CheckWeddingTime( int nWeddingTime, int nWeddingTimeLength )
{
	bool tCheckResult = CheckMarriageWeddingTime( nWeddingTime, nWeddingTimeLength );
	if ( tCheckResult == true )
	{
		tCheckResult = CheckMarriageApplyWeddingTime( nWeddingTime, nWeddingTimeLength );
	}		
	return tCheckResult;
}

// ***********************************************************
//  Function:		CheckMarriageWeddingTime
//  Description:	����Ƿ���Ѿ�������ҵĻ���ʱ���ͻ			
//  Output:			
//  Date:	03/04/2010
// *********************************************************
bool CMarriageManager::CheckMarriageWeddingTime( int nWeddingTime, int nWeddingTimeLength )
{
	bool tCheckResult = true;
	for ( MarriageInfoList::iterator it = mMarriageInfoList.begin(); it != mMarriageInfoList.end(); ++it )
	{
		CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		if ( tpMarriageInfo == NULL )
		{
			LOG_ERROR( "marriage","can not find marriageinfo by id:%d", it->first );
			continue;
		}

		if ( tpMarriageInfo->GetMarriageStatus() == MARRIAGESTATUS_MARRY )
		{
			continue;
		}

		if ( tpMarriageInfo->JudgeTimeValide( nWeddingTime, nWeddingTimeLength ) == false )
		{
			tCheckResult = false;
			break;			
		}	 			
	} 	
	return tCheckResult;
}

// ***********************************************************
//  Function:		GetMarriageInfoConfictedWithTime
//  Description:	��ȡ�͵�ǰʱ����ͻ�Ļ�����Ϣ			
//  Output:			
//  Date:	03/10/2010
// *********************************************************
CMarriageInfo *CMarriageManager::GetMarriageInfoConfictedWithTime( int nWeddingTime, int nWeddingTimeLength )
{
	for ( MarriageInfoList::iterator it = mMarriageInfoList.begin(); it != mMarriageInfoList.end(); ++it )
	{
		CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		if ( tpMarriageInfo == NULL )
		{
			LOG_ERROR( "marriage","can not find marriageinfo by id:%d", it->first );
			continue;
		}

		if ( tpMarriageInfo->GetMarriageStatus() == MARRIAGESTATUS_MARRY )
		{
			continue;
		}

		if ( tpMarriageInfo->JudgeTimeValide( nWeddingTime, nWeddingTimeLength ) == false )
		{
			return tpMarriageInfo;			
		}	 			
	} 	
	return NULL;
}

// ***********************************************************
//  Function:		CheckMarriageApplyWeddingTime
//  Description:	����Ƿ�����������ҵĻ���ʱ���ͻ			
//  Output:			
//  Date:	03/04/2010
// *********************************************************
bool CMarriageManager::CheckMarriageApplyWeddingTime( int nWeddingTime, int nWeddingTimeLength )
{  	
	bool tCheckResult = true;
	
	// ���������ʱ����Ϣ��ʱ���������ܱ���������
	for ( MarriageApplyInfo::iterator it = 	mMarriageApplyInfo.begin(); it != mMarriageApplyInfo.end(); ++it )
	{
		CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( *it );
		if ( tpMarriageInfo == NULL )
		{
			continue;
		}
		if ( tpMarriageInfo->GetMarriageStatus() == MARRIAGESTATUS_MARRY )
		{
			continue;
		}
		if ( tpMarriageInfo->JudgeTimeValide( nWeddingTime, nWeddingTimeLength ) == false )
		{
			tCheckResult = false;
			break;			
		}	 			
	}	
	return tCheckResult;
}

// ***********************************************************
//  Function:		GetMarriageApplyInfo
//  Description:	��ȡĳ��������Ļ�����Ϣ			
//  Output:			
//  Date:	02/26/2010
// *********************************************************
CMarriageInfo *CMarriageManager::GetMarriageApplyInfo( unsigned int nRoleID )
{ 
	for ( MarriageApplyInfo::iterator it = 	mMarriageApplyInfo.begin(); it != mMarriageApplyInfo.end(); ++it )
	{
		CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( *it );
		if ( tpMarriageInfo == NULL )
		{
			continue;
		}
		if ( tpMarriageInfo->GetGroomID() == nRoleID || tpMarriageInfo->GetBrideID() == nRoleID )
		{
			return tpMarriageInfo;
		}
	}	
	
	return NULL;
}

// ***********************************************************
//  Function:		GetMarriageInfoByMarriageID
//  Description:	��ȡ��ҵĻ�����Ϣ			
//  Output:			
//  Date:	02/26/2010
// *********************************************************
CMarriageInfo *CMarriageManager::GetMarriageInfoByMarriageID( int nMarriageID )
{ 
	MarriageInfoList::iterator it = mMarriageInfoList.find( nMarriageID );
	if ( it != mMarriageInfoList.end() )
	{
		return ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
	}																		  
	return NULL; 
}	

// ***********************************************************
//  Function:		CreatMarriageApplyInfo
//  Description:	����һ��������Ļ�����Ϣ			
//  Output:			
//  Date:	02/26/2010
// *********************************************************
CMarriageInfo * CMarriageManager::CreatMarriageApplyInfo( int nGroomID, int nBrideID, int nWeddingTime, int nWeddingTimeLength, int nWeddingModule )
{
	if ( GetMarriageApplyInfo( nGroomID  ) != NULL || GetMarriageApplyInfo( nBrideID ) != NULL )
	{
		return NULL;
	}
	
	CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().CreateObject( OBJTYPE_MARRIAGEINFO );
	if ( tpMarriageInfo == NULL )
	{
		return NULL;
	}
	
	tpMarriageInfo->SetGroomID( nGroomID );
	tpMarriageInfo->SetBrideID( nBrideID );
	tpMarriageInfo->SetWeddingTime( nWeddingTime );
	tpMarriageInfo->SetWeddingTimeLength( nWeddingTimeLength );
	tpMarriageInfo->SetWeddingModule( nWeddingModule );
	mMarriageApplyInfo.push_back( tpMarriageInfo->get_id() );
	return tpMarriageInfo;
}

// ***********************************************************
//  Function:		DeleteMarriageApplyInfo
//  Description:	ɾ��һ��������Ļ�����Ϣ			
//  Output:			
//  Date:	02/26/2010
// *********************************************************
int CMarriageManager::DeleteMarriageApplyInfo( unsigned int nRoleID )
{ 
	for ( MarriageApplyInfo::iterator it = 	mMarriageApplyInfo.begin(); it != mMarriageApplyInfo.end(); ++it )
	{
		CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( *it );
		if ( tpMarriageInfo == NULL )
		{
			continue;
		}
		if ( tpMarriageInfo->GetGroomID() == nRoleID || tpMarriageInfo->GetBrideID() == nRoleID )
		{
			CSceneObjManager::GetSingleton().DestroyObject( tpMarriageInfo->get_id() );
			mMarriageApplyInfo.erase( it );
			break;
		}
	}		
	return SUCCESS;
}

// ***********************************************************
//  Function:		InsertOtherCampMarriageInfo
//  Description:	��¼һ������������ҵĻ�����Ϣ			
//  Output:			
//  Date:	03/01/2010
// *********************************************************
int CMarriageManager::InsertOtherCampMarriageInfo( CMarriageInfo *pMarriageInfo )
{	
	LK_ASSERT( pMarriageInfo != NULL, return -1 ) 	
	if ( mOtherCampMarriageInfo.size() >= SERVER_CAP_MARRIAGEINFO )
	{
		return -1;
	}
	mOtherCampMarriageInfo.insert( MarriageInfoList::value_type( pMarriageInfo->GetServerSequence(), pMarriageInfo->get_id() ) );
	return SUCCESS;
}

// ***********************************************************
//  Function:		DeleteOtherCampMarriageInfo
//  Description:	ɾ������������ҵĻ�����Ϣ			
//  Output:			
//  Date:	03/01/2010
// *********************************************************
void CMarriageManager::DeleteOtherCampMarriageInfo( int nMarriageID )
{	
	MarriageInfoList::iterator it = mOtherCampMarriageInfo.find( nMarriageID );
	if ( it != mOtherCampMarriageInfo.end() )
	{
		CSceneObjManager::GetSingleton().DestroyObject( it->second );
		mOtherCampMarriageInfo.erase( it );
	}
}

// ***********************************************************
//  Function:		GetMarriageInfoOfOtherCamp
//  Description:	��ȡһ���ڱ���Ӫ��������Ӫ��ҵĻ�����Ϣ			
//  Output:			
//  Date:	03/01/2010
// *********************************************************
CMarriageInfo * CMarriageManager::GetMarriageInfoOfOtherCamp( int nMarriageID )
{
	MarriageInfoList::iterator it = mOtherCampMarriageInfo.find( nMarriageID );
	if ( it != mOtherCampMarriageInfo.end() )
	{
		return ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );		
	}	
	return NULL;
}

// ***********************************************************
//  Function:		GetMarriageInfoByID
//  Description:	��ȡ��ҵĻ�����Ϣ			
//  Output:			
//  Date:	03/01/2010
// *********************************************************
CMarriageInfo* CMarriageManager::GetMarriageInfoByID( int nCampID, int nMarriageID )
{	
	if ( nCampID == CSceneLogic::GetSingleton().GetLineID() )
	{
		 return GetMarriageInfoByMarriageID( nMarriageID );
	}
	else
	{
		 return GetMarriageInfoOfOtherCamp( nMarriageID );
	}		
}

// ***********************************************************
//  Function:		CheckNpcPos
//  Description:	��ȡ��ǰλ��Ӧ���ƶ�����һλ��			
//  Output:			 bool &rReachEnd �Ƿ��ƶ���ָ��λ��	
//  Date:	03/01/2010
// *********************************************************
bool CMarriageManager::CheckNpcPos( int nNpcPosIndex, int nWeddingModule, int nNpcIndex, int nNpcPosX, int nNpcPosY, bool &rReachEnd )
{
	rReachEnd = false;
	if ( nWeddingModule < 0 || nWeddingModule >= MAX_WEDDING_MODULENUM )
	{
		return true;
	}
	
	if ( nNpcIndex < 0 || nNpcIndex >= MAX_WEDDING_NPCNUM )
	{
		return true;
	}
	
	if ( nNpcPosIndex < 0 || nNpcPosIndex >= MAX_WEDDINGNPCPATH_STEPS )
	{
		return true;
	}
	
	if ( mNpcPath[nWeddingModule].mNpcPathInfo[nNpcIndex].mNpcPath[nNpcPosIndex].mPosX != nNpcPosX 
		|| mNpcPath[nWeddingModule].mNpcPathInfo[nNpcIndex].mNpcPath[nNpcPosIndex].mPosY != nNpcPosY )
	{
		return false;
	}
	
	if ( nNpcPosIndex == MAX_WEDDINGNPCPATH_STEPS - 1 )
	{	 
		rReachEnd = true;
	}
	else
	{
		if ( mNpcPath[nWeddingModule].mNpcPathInfo[nNpcIndex].mNpcPath[nNpcPosIndex+1].mPosX == 0 
			&&	mNpcPath[nWeddingModule].mNpcPathInfo[nNpcIndex].mNpcPath[nNpcPosIndex+1].mPosY == 0  )
		{
			rReachEnd = true;
		}
	}	  		
	return true;
}

// ***********************************************************
//  Function:		GetWeddingNpcInfo
//  Description:	��ȡĳ�ֹ�ģ��npc·����Ϣ
//  Output:			bool �Ƿ��ƶ���ָ��λ��	
//  Date:	03/01/2010
// *********************************************************	
CWeddingNpcInfo *CMarriageManager::GetWeddingNpcInfo( int nWeddingModule )
{  
	if ( nWeddingModule < 0 || nWeddingModule >= MAX_WEDDING_MODULENUM )
	{
		return NULL;	
	}
	return &mNpcPath[nWeddingModule];	
}

// ***********************************************************
//  Function:		GetNpcMovePos
//  Description:	 ��ȡnpc���ƶ������
//  Output:			
//  Date:	03/02/2010
// *********************************************************	
int CMarriageManager::GetNpcMovePos( int nWeddingModule, int nNpcIndex, int nNpcPosIndex, CNpcPos &rNpcPos )
{
	
	if ( nWeddingModule < 0 || nWeddingModule >= MAX_WEDDING_MODULENUM )
	{
		return -1;
	}

	if ( nNpcIndex < 0 || nNpcIndex >= MAX_WEDDING_NPCNUM )
	{
		return -1;
	}

	if ( nNpcPosIndex < 0 || nNpcPosIndex >= MAX_WEDDINGNPCPATH_STEPS  )
	{
		return -1;
	}
	
	rNpcPos.mPosX = mNpcPath[nWeddingModule].mNpcPathInfo[nNpcIndex].mNpcPath[nNpcPosIndex].mPosX;
	rNpcPos.mPosY = mNpcPath[nWeddingModule].mNpcPathInfo[nNpcIndex].mNpcPath[nNpcPosIndex].mPosY;
	rNpcPos.mSynchMark = mNpcPath[nWeddingModule].mNpcPathInfo[nNpcIndex].mNpcPath[nNpcPosIndex].mSynchMark;
	return SUCCESS;
}

// ***********************************************************
//  Function:		InsertNpcPath
//  Description:	����һ��npc��·����Ϣ
//  Output:			
//  Date:	03/02/2010
// *********************************************************	
int CMarriageManager::InsertNpcPath( int nWeddingModule, CWeddingNpcPath &rNpcPath )
{
	if ( nWeddingModule < 0 || nWeddingModule >= MAX_WEDDING_MODULENUM )
	{
		return -1;
	}
	for ( int i = 0; i < MAX_WEDDING_NPCNUM; ++i )
	{
		if ( mNpcPath[nWeddingModule].mNpcPathInfo[i].mNpcTmpID == 0 )
		{
			memcpy( &mNpcPath[nWeddingModule].mNpcPathInfo[i], &rNpcPath, sizeof(CWeddingNpcPath) );
			break;
		}
	}
	return SUCCESS;		
}

// ***********************************************************
//  Function:		InsertSysWeddingTimeInfo
//  Description:	����һ��ϵͳ����ʱ���
//  Output:			
//  Date:	03/02/2010
// *********************************************************
int CMarriageManager::InsertSysWeddingTimeInfo( int nTimeID, CWeddingSysTime &rWeddingTime )
{
	mWeddingTimeInfo.insert( SysWeddingTimeList::value_type( nTimeID, rWeddingTime ) );
	return SUCCESS;	
}  

// ***********************************************************
//  Function:		GetWeddingTimeInfo
//  Description:	��ȡָ��ID�Ļ���ʱ���
//  Output:			
//  Date:	03/02/2010
// *********************************************************
CWeddingSysTime* CMarriageManager::GetWeddingTimeInfo( int nTimeID )
{
	SysWeddingTimeList::iterator it = mWeddingTimeInfo.find( nTimeID );
	if ( it != mWeddingTimeInfo.end() )
	{
		return &(it->second);
	}
	return NULL;
}

// ***********************************************************
//  Function:		DeleteWeddingTimeInfoByID
//  Description:	ɾ��һ��ϵͳʱ���
//  Output:			
//  Date:	03/02/2010
// *********************************************************
void CMarriageManager::DeleteWeddingTimeInfoByID( int nTimeID )
{
	SysWeddingTimeList::iterator it = mWeddingTimeInfo.find( nTimeID );
	if ( it != mWeddingTimeInfo.end() )
	{
		mWeddingTimeInfo.erase( it );
	}
}

// ***********************************************************
//  Function:		InitialWeddingTimeInfo
//  Description:	��ʼ������ʱ������
//  Output:			
//  Date:	03/02/2010
// *********************************************************
int CMarriageManager::InitialWeddingTimeInfo()
{
	mWeddingTimeInfo.initailize();
	return SUCCESS;
}

// ***********************************************************
//  Function:		InitialNpcPathInfo
//  Description:	��ʼ��npc��·����Ϣ
//  Output:			
//  Date:	03/02/2010
// *********************************************************
int CMarriageManager::InitialNpcPathInfo( )
{
	memset( mNpcPath, 0, sizeof( mNpcPath )	);
	return SUCCESS;
}

// ***********************************************************
//  Function:		SetWeddingTimer
//  Description:	���û���ʱ��
//  Output:			
//  Date:	04/12/2010
// *********************************************************
int CMarriageManager::SetWeddingTimer( int nTimeMark, int nTimerID )
{ 
	WeddingTimeList::iterator it = mWeddingTimer.find( nTimeMark );
	if( it == mWeddingTimer.end() )
	{
		mWeddingTimer.insert( WeddingTimeList::value_type( nTimeMark, nTimerID ) );
	}
	else
	{
		CTimerMng::GetSingleton().ClearTimer( it->second );
	}		
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetWeddingTimerID
//  Description:	��ȡ����ʱ��
//  Output:			
//  Date:	04/12/2010
// *********************************************************
int CMarriageManager::GetWeddingTimerID( int nTimerMark )
{
	WeddingTimeList::iterator it = mWeddingTimer.find( nTimerMark );
	if ( it != mWeddingTimer.end() )
	{
		return it->second;
	}
	return 0;
}

// ***********************************************************
//  Function:		ClearWedingTimer
//  Description:	�������ʱ��
//  Output:			
//  Date:	04/12/2010
// *********************************************************
int CMarriageManager::ClearWeddingTimer( int nTimerMark )
{
	WeddingTimeList::iterator it = mWeddingTimer.find( nTimerMark );
	if ( it != mWeddingTimer.end() )
	{
		CTimerMng::GetSingleton().ClearTimer( it->second );
		mWeddingTimer.erase( it );		
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		ClearAllWeddingTime
//  Description:	������ж�ʱ��
//  Output:			
//  Date:	04/12/2010
// *********************************************************
int CMarriageManager::ClearAllWeddingTime()
{
	WeddingTimeList::iterator it = mWeddingTimer.begin();
	for( ; it != mWeddingTimer.end(); ++it )
	{
		CTimerMng::GetSingleton().ClearTimer( it->second );
	}		
	mWeddingTimer.initailize();		
	return SUCCESS;
}