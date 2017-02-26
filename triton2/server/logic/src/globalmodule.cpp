#include "globalmodule.h"
#include "globalserver_pb.hxx.pb.h"
#include "scenelogic.h"
#include "coremessage_pb.hxx.pb.h"
#include "mapmodule.h"
#include "repetionmodule.h"
#include "proclient_svr.h"
#include "sceneobj_manager_imp.h"
#include "activitymodule.h"
template<> CGlobalModule * CSingleton<CGlobalModule>::spSingleton = NULL;

// ***********************************************************
//  Function:		CountSize
//  Description:	��������ȫ�ַ���������Ϣ 				
//  Output:			
//  Date:	03/30/2011
// **********************************************************
unsigned int CGlobalModule::CountSize( )
{
	return sizeof( CGlobalModule );
}

// ***********************************************************
//  Function:		����ʵ��
//  Description:	��������ȫ�ַ���������Ϣ 				
//  Output:			
//  Date:	03/30/2011
// **********************************************************
void CGlobalModule::OnDestroyEntity( CEntity* pEntity, int vCode )
{
	LK_ASSERT( pEntity != NULL, return )
	if ( pEntity->IsPlayer() )
	{
		CEntityPlayer *tpPlayer = ( CEntityPlayer * )pEntity;
		CGlobalTeleInfo * tpTeleInfo =  GetGlobalTeleInfo( tpPlayer->GetCharID() );
#ifdef _FB_
		// ��ս���뿪�����Ƿ�������ʱ֪ͨս������뿪		
		//if ( tpTeleInfo != NULL )
		//{
		//	CRepetion* tpRepetion = CRepetionModule::GetSingleton().GetRepetion( tpPlayer );
		//	LK_ASSERT( tpRepetion != NULL, return )
		//	if ( IS_DUNGEONSERVER_LINE( CSceneLogic::GetSingleton().GetLineID() ) &&
		//		tpTeleInfo->mTeleType == EGLOBALTELE_TYPE_RETURNTOGATE )
		//	{
		//		lua_tinker::table vParame( CRepetionModule::GetSingletonPtr( )->mLua );
		//		vParame.set( "entityid", tpPlayer->get_id() );
		//		vParame.set( "playerlevel",tpPlayer->GetLevel() );
		//		vParame.set( "playername", tpPlayer->GetName() );
		//		vParame.set( "playercountryid",tpPlayer->GetCountryID() );
		//		vParame.set( "playerlevel",tpPlayer->GetLevel() );
		//		vParame.set( "playermapid",tpPlayer->GetMapID());
		//		tpRepetion->DoEvent( tpRepetion->GetRepetionInfo( ), REPETION_LEAVE_EVENT, &vParame );
		//	}		
		//}
	
#endif		

		// ���������Ϣ
		CPlayerRepetion *tpPlayerRepetion = ( (CPropertyPlayer *)tpPlayer->GetProperty() )->GetRepetion();
		if ( tpPlayerRepetion != NULL && ( vCode == SAVE_LEAVEGAME || vCode == SAVE_KICKOUT || vCode == SAVE_RETURN2GATE ))
		{
			if ( tpPlayerRepetion->GetGlobalSceneStatus() == EGLOBALWAR_STATUS_APPLYSUCESS )
			{				
				PlayerLeaveGlobalWar( tpPlayer->GetCharID(), EREASON_LEAVEWAR_APPLYFAILED );
				tpPlayerRepetion->SetGlobalSceneStatus( EGLOBALWAR_STATUS_NULL );
			}

			if ( tpPlayerRepetion->GetGlobalSceneStatus() == EGLOBALWAR_STATUS_APPLY )
			{
				tpPlayerRepetion->SetGlobalSceneStatus( EGLOBALWAR_STATUS_NULL );
			}
		}
		DeleteGlobalTeleInfo( tpPlayer->GetCharID() );
	}
}

// ***********************************************************
//  Function:		OnSaveData
//  Description:	�洢���� 				
//  Output:			
//  Date:	04/13/2011
// **********************************************************
bool CGlobalModule::OnSaveData( CEntityPlayer* pPlayer, int vSaveCode )
{ 	
	return true;
}

// ***********************************************************
//  Function:		OnCreateEntity
//  Description:	����ʵ�� 				
//  Output:			
//  Date:	04/13/2011
// **********************************************************
void CGlobalModule::OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst )
{
	LK_ASSERT( pEntity != NULL, return )
	if ( pEntity->IsPlayer() )
	{
		CEntityPlayer *tpPlayer = ( CEntityPlayer * )pEntity;
		CPropertyPlayer *tpProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
		CPlayerRepetion *tpReption = tpProperty->GetRepetion();
		//������ڿ����������һ��buff
		if ( IS_GLOBAL_SCENESERVER( tpPlayer->GetLineID() ) )
		{
			CTemplateGlobalMapConfig *tpConfig = (CTemplateGlobalMapConfig*)CDataStatic::GetTemp( TEMP_GLOBALMAPCONFIG );
			if ( tpConfig != NULL )
			{
				CTemplateBuff* tpBuff = (CTemplateBuff*)CDataStatic::SearchTpl( tpConfig->mBuffID );
				if ( tpBuff != NULL )
				{
					tpPlayer->EntityInsertBuff( tpPlayer, tpBuff );
				}
			}
		}
		if ( tpReption->GetGlobalSceneStatus() == EGLOBALWAR_STATUS_INWAR )
		{
			if ( time( NULL ) - tpReption->GetGlobalWarOffLineTime() <= MAX_OFFLINETIME )
			{
				GlobalTelePort( tpPlayer, EGLOBALTELE_TYPE_GLOBALSERVER, ESERVERTYPE_DUNGEON );
			}
			else
			{
				tpReption->SetGlobalSceneStatus( EGLOBALWAR_STATUS_NULL );
			}
		}
		else
		{			
			if ( vFirst == true )
			{
				tpReption->SetGlobalSceneStatus( EGLOBALWAR_STATUS_NULL );
			}			
		}
	}
}

// ***********************************************************
//  Function:		OnServerMessgage
//  Description:	��������ȫ�ַ���������Ϣ 				
//  Output:			
//  Date:	03/30/2011
// **********************************************************
void CGlobalModule::OnServerMessgage( CMessage *pMsg )
{
	LK_ASSERT( pMsg != NULL, return )
	switch ( pMsg->mutable_msghead()->messageid() )
	{
		case ID_D2S_RESPONSE_GLOBALTELEPORT:
		{
			OnMsgGlobalTeleResponse( pMsg );
			break;
		}

		case ID_D2S_NOTIFY_WARENABLE:
		{	
			OnMessageWarEnableNotify( pMsg );
			break;
		}		
		case ID_D2S_REQPONSE_PLAYERAPPLYWAR:
		{
			OnMessageApplyWarResponse( pMsg );
			break;
		}
		case ID_S2S_NOTIFY_KICKGLOBALPLAYER:
		{
			OnMessageKickPlayer( pMsg );
			break;
		}			
		default:
			break;
	}
}

// ***********************************************************
//  Function:		OnMsgGlobalTeleResponse
//  Description:	����������͵Ļ�Ӧ��Ϣ 				
//  Output:			
//  Date:	03/30/2011
// **********************************************************
void CGlobalModule::OnMsgGlobalTeleResponse( CMessage *pMsg )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessageGlobalTeleportResponse *tpMsg = ( CMessageGlobalTeleportResponse * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CEntityPlayer *tpPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMsg->roleid() );
	if ( tpPlayer == NULL )
	{
		LOG_ERROR( "default"," player is off line,[roleid:%d] ", tpMsg->roleid() );
		return;
	}	

	if ( tpMsg->errcode() != SUCCESS )
	{
		LOG_ERROR( "repetion","can not teleport to globalserver ,roleid:%d,errcode:%d", tpMsg->roleid(), tpMsg->errcode() );		
		CPropertyModule::GetSingleton().SendProErrorNotice( tpPlayer, tpMsg->errcode() );
		return;
	}	

	CGlobalTeleInfo *tpInfo = GetGlobalTeleInfo( tpPlayer->GetCharID() );
	if ( tpInfo == NULL )
	{
		LOG_ERROR( "repetion","can not find globalteleinfo ,roleid:%d", tpMsg->roleid() );		
		return;
	}

	// ���ͻ��˷��ͻ�Ӧ��Ϣ
	if ( tpInfo->mSceneType == ESERVERTYPE_DUNGEON )
	{
		if ( tpInfo->mTeleType == EGLOBALTELE_TYPE_GLOBALSERVER )
		{
			CRepetionModule::GetSingleton().SendResponsePlayerEnterGlobalWar( tpPlayer,tpMsg->errcode() );
		}
		else if( tpInfo->mTeleType == EGLOBALTELE_TYPE_RETURNTOGAME )
		{
			// CRepetionModule::GetSingleton().SendResponsePlayerLeaveGlobalWar( tpPlayer, tpMsg->errcode() );
		}	
	}	
	else if ( tpInfo->mSceneType == ESERVERTYPE_SCENESER )
	{

	}

	if ( tpMsg->errcode() != SUCCESS )
	{
		return;
	}

	// �ж��Ƿ���ȥȫ�ָ���
	if ( tpInfo->mSceneType == ESERVERTYPE_DUNGEON &&  tpInfo->mTeleType == EGLOBALTELE_TYPE_GLOBALSERVER )
	{
		( (CPropertyPlayer *)tpPlayer->GetProperty() )->GetRepetion(  )->SetGlobalSceneStatus( EGLOBALWAR_STATUS_NULL );
	}

	// ֪ͨ����ɾ����ɫ��Ϣ,���̺��ٿ��	
	tpInfo->mLoginToken = tpMsg->logintoken();
	tpInfo->mSceneWorldID = tpMsg->sceneworldid();
	if ( tpMsg->has_addr() )
	{
		tpInfo->mAddr = lk::CString64( tpMsg->addr( ).c_str( ) );
	}
	else
	{
		// ͬ������
		if ( tpMsg->reptionkey() == 0 )
		{
			CMapModule::GetSingleton().Teleport( tpMsg->lineid(),tpMsg->mapid(),tpMsg->posx(), tpMsg->posy(), tpPlayer, 0, tpMsg->reptionkey() );
		}
		else
		{	
			// ���������ӪID					
			CRepetionModule::GetSingleton().PlayerIntoBattleByKey( tpPlayer, tpMsg->repetionindex(), tpMsg->teamflag(), tpMsg->reptionkey() );
		}
		return;
	}	
	tpPlayer->SetCommState( CEntityPlayer::STATE_LEAVEGAME );	
	CSceneLogic::GetSingleton().PlayerLeaveFromGame( tpPlayer );	
}

// ***********************************************************
//  Function:		OnMessageWarEnableNotify
//  Description:	���Խ��븱����֪ͨ 				
//  Output:			
//  Date:	04/08/2011
// **********************************************************
void CGlobalModule::OnMessageWarEnableNotify( CMessage *pMsg )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessageWarEnableNotify *tpMsg = ( CMessageWarEnableNotify * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CEntityPlayer *tpPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMsg->roleid() );

	// ����Ѿ�����
	if ( tpPlayer == NULL )
	{
		PlayerLeaveGlobalWar( tpMsg->roleid(), EREASON_LEAVEWAR_RETURNBACK );
		return;
	}

	// ״̬����ȷ
	if ( ((CPropertyPlayer *)tpPlayer->GetProperty())->GetRepetion()->GetGlobalSceneStatus() != EGLOBALWAR_STATUS_APPLYSUCESS )
	{
		PlayerLeaveGlobalWar( tpMsg->roleid(), EREASON_LEAVEWAR_RETURNBACK );
		return;
	}

	// ����ս������ӪID
	( ( CPropertyPlayer * )tpPlayer->GetProperty() )->GetRepetion()->SetCampID( tpMsg->teamflag() );
	( ( CPropertyPlayer * )tpPlayer->GetProperty() )->GetRepetion()->SetGlobalWarOffLineTime( time(NULL) );
	( ( CPropertyPlayer * )tpPlayer->GetProperty() )->GetRepetion()->SetGlobalSceneStatus( EGLOBALWAR_STATUS_APPLYSUCESS );
	CRepetionModule::GetSingleton().SendNotifyCanEnterGlobalWar( tpPlayer, _REPE_GLOBALWAR_INDEX_ );
}

// ***********************************************************
//  Function:		OnMessageApplyWarResponse
//  Description:	��ұ�������Ϣ��Ӧ 				
//  Output:			
//  Date:	04/08/2011
// **********************************************************
void CGlobalModule::OnMessageApplyWarResponse( CMessage *pMsg )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessagePlayerApplyWarResponse *tpMsg = ( CMessagePlayerApplyWarResponse * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	CEntityPlayer *tpPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMsg->roleid() );
	if ( tpPlayer == NULL  )
	{
		// ֪ͨȫ�ָ���������ɾ�������Ϣ
		PlayerLeaveGlobalWar( tpMsg->roleid(), EREASON_LEAVEWAR_APPLYFAILED );
		return;
	}	
	CGlobalWarInfo tWarInfo;
	if ( tpMsg->errcode() != SUCCESS )
	{	
		CRepetionModule::GetSingleton().SendResponsePlayerApplyWar( tpPlayer, tpMsg->errcode(), tWarInfo, tpMsg->minlevel(), tpMsg->maxlevel() );
		return;
	}

	// �����ɹ�
	( ( CPropertyPlayer * )tpPlayer->GetProperty() )->GetRepetion()->SetGlobalSceneStatus( EGLOBALWAR_STATUS_APPLYSUCESS );
	( ( CPropertyPlayer * )tpPlayer->GetProperty() )->GetRepetion()->SetGlobalWarOffLineTime( time(NULL) );
	
	CRepetionModule::GetSingleton().SendResponsePlayerApplyWar( tpPlayer, SUCCESS, tWarInfo, tpMsg->minlevel(), tpMsg->maxlevel() );

	// ��¼��־
	LOG_NOTICE( REPETION_LOG, "Player (Role_ID:%d,Level:%d) apply GlobalWar SUCCESS", tpPlayer->GetCharID(), tpPlayer->GetLevel() );

	// ������Խ���ս���ͷ���Ϣ
	if ( tpMsg->canstart() == 1 )
	{		
		( ( CPropertyPlayer * )tpPlayer->GetProperty() )->GetRepetion()->SetCampID( tpMsg->teamflag() );
		CRepetionModule::GetSingleton().SendNotifyCanEnterGlobalWar( tpPlayer, _REPE_GLOBALWAR_INDEX_ );
	}
}

// ***********************************************************
//  Function:		PlayerApplyWar
//  Description:	���ս������ 				
//  Output:			
//  Date:	04/08/2011
// **********************************************************
int CGlobalModule::PlayerApplyWar( CEntityPlayer *pPlayer, int nRepetionIndex /* = _REPE_GLOBALWAR_INDEX_ */ )
{
	LK_ASSERT( pPlayer != NULL, return -1 )
	CPlayerRepetion *tpRepetion = ( ( CPropertyPlayer *)pPlayer->GetProperty() )->GetRepetion();
	tpRepetion->SetGlobalSceneStatus( EGLOBALWAR_STATUS_APPLY );

	// ����Ƿ���
	if ( CActivityModule::GetSingleton().GetActivityStateByID( HELPID_LINGYD ) == ACTIVITYSTATE_NOT_START )
	{
		return SUCCESS;
	}

	// ��鸱���������
	CRepetionInfo *tpRepetionInfo = CRepetionModule::GetSingleton().GetRepetionInfo( _REPE_GLOBALWAR_INDEX_ );
	if ( tpRepetionInfo == NULL )
	{
		return SUCCESS;
	}

	int tRet = CRepetionModule::GetSingleton().PlayerIntoRepetionCheck( pPlayer, tpRepetionInfo, CHECK_COUNT_KEY );
	if ( tRet != SUCCESS )
	{
		CGlobalWarInfo tGlobalWarInfo;
		CRepetionModule::GetSingleton().SendResponsePlayerApplyWar( pPlayer, tRet, tGlobalWarInfo, 0, 0 );
		return SUCCESS;
	}

	// �������buffs
	CTemplateGlobalMapConfig *tpConfig = ( CTemplateGlobalMapConfig * )CDataStatic::GetTemp( TEMP_GLOBALMAPCONFIG );
	if ( tpConfig == NULL )
	{
		return -1;
	}
	if ( pPlayer->HasBuff( tpConfig->mEscapeBuffID ) == true )
	{
		CGlobalWarInfo tGlobalWarInfo;
		CRepetionModule::GetSingleton().SendResponsePlayerApplyWar( pPlayer, EDUNGEON_ERROR_HASESCAPEBUFF, tGlobalWarInfo, 0, 0 );
		return -1;
	}	
	if ( pPlayer->HasBuff( GLOBALWAR_TIMELIMIT_BUFF ) == true )
	{
		CGlobalWarInfo tGlobalWarInfo;
		CRepetionModule::GetSingleton().SendResponsePlayerApplyWar( pPlayer, EDUNGEON_ERROR_HASTIMELIMITBUFF, tGlobalWarInfo, 0, 0 );
		return -1;
	}
	// �������ȼ��ж�
	CMessage tMsgHead;
	CMessagePlayerApplyWarRequest tMsgApplyWar;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2D_REQUEST_PLAYERAPPLYWAR );
	tMsgHead.set_msgpara( (int)&tMsgApplyWar );
	tMsgApplyWar.set_roleid( pPlayer->GetCharID() );
	tMsgApplyWar.set_rolelevel( pPlayer->GetLevel() );
	tMsgApplyWar.set_serverid( CSceneLogic::GetSingleton().GetLineID() );
	tMsgApplyWar.set_worldid( CSceneLogic::GetSingleton().GetWorldID() );
	tMsgApplyWar.set_repetionindex( nRepetionIndex );
	CSceneLogic::GetSingleton().Send2GlobalDunServer( &tMsgHead );
	return SUCCESS;
}

// ***********************************************************
//  Function:		GlobalTelePort
//  Description:	�������� 					
//  Output:			
//  Date:	03/30/2011
// **********************************************************
int CGlobalModule::GlobalTelePort( CEntityPlayer *pPlayer, EGlobalTeleType eTeleType , EServerType nServerType /* = ESERVERTYPE_DUNGEON */, CGlobalMapData *pMapData /* = NULL */ )
{
	LK_ASSERT( pPlayer != NULL, return -1 )
	CMessage tMsgHead;
	CMessageGlobalTeleportRequest tGlobalTele;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2D_REQUEST_GLOBALTELEPORT );
	tMsgHead.set_msgpara( (int)&tGlobalTele );
	tGlobalTele.set_roleid( pPlayer->GetCharID() );
	tGlobalTele.set_servertype( nServerType );
	tGlobalTele.set_serverid( CSceneServer::GetSingleton().mThisServerID );
	tGlobalTele.set_worldid( CSceneLogic::GetSingleton().GetWorldID()  );
	tGlobalTele.set_accountid( pPlayer->GetAccountID() );
	tGlobalTele.set_gameid( pPlayer->GetGameID() );
	//if ( eTeleType != EGLOBALTELE_TYPE_GLOBALSERVER )
	if ( pPlayer->GetRoleWorldID() > 0 && pPlayer->GetRoleWorldID() != CSceneLogic::GetSingleton().GetWorldID() )	
	{				
		tGlobalTele.set_originalworldid( pPlayer->GetRoleWorldID() );				
		// tGlobalTele.set_teletype( eTeleType );		
	}
	if ( eTeleType != EGLOBALTELE_TYPE_GLOBALSERVER )
	{
		tGlobalTele.set_originalserverid( pPlayer->GetNationality() );
	}
	tGlobalTele.set_teletype( eTeleType );		
	if ( pMapData != NULL )
	{
		tGlobalTele.mutable_mapdata()->set_mapid( pMapData->mMapID );
		tGlobalTele.mutable_mapdata()->set_posx( pMapData->mPosX );
		tGlobalTele.mutable_mapdata()->set_posy( pMapData->mPosY );
		tGlobalTele.mutable_mapdata()->set_lineid( pMapData->mLineID );
	}	

	CGlobalTeleInfo tInfo;
	tInfo.mTeleType = eTeleType;
	tInfo.mSceneType = nServerType;
	InsertGlobalTeleInfo( pPlayer->GetCharID(), tInfo );
	CSceneLogic::GetSingleton().Send2Gate( &tMsgHead );
	//CSceneLogic::GetSingleton().Send2GlobalDunServer( &tMsgHead );
}

// ***********************************************************
//  Function:		OnMessageKickPlayer
//  Description:	�߳���� 				
//  Output:			
//  Date:	03/30/2011
// **********************************************************
void CGlobalModule::OnMessageKickPlayer( CMessage *pMsg )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessageKickGlobalPlayerNotify *tpMsg = ( CMessageKickGlobalPlayerNotify * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CSceneLogic::GetSingleton().KickPlayer( tpMsg->roleid(), EM_KICKOUT_SERVERMAINTANCE );
}

// ***********************************************************
//  Function:		InsertGlobalTeleInfo
//  Description:	����һ��ȫ�ִ�����Ϣ 				
//  Output:			
//  Date:	03/30/2011
// **********************************************************
int CGlobalModule::InsertGlobalTeleInfo( int nRoleID, CGlobalTeleInfo &rInfo )
{
	mGlobalTeleInfo.insert( GlobalTeleInfoList::value_type( nRoleID, rInfo ) );
	return 0;
}

// ***********************************************************
//  Function:		GetGlobalTeleInfo
//  Description:	��ȡһ��ȫ�ִ�����Ϣ 				
//  Output:			
//  Date:	03/30/2011
// **********************************************************
CGlobalTeleInfo *CGlobalModule::GetGlobalTeleInfo( int nRoleID )
{
	GlobalTeleInfoList::iterator it = mGlobalTeleInfo.find( nRoleID );
	if ( it != mGlobalTeleInfo.end() )
	{
		return (&it->second);
	}
	return NULL;
}

// ***********************************************************
//  Function:		DeleteGlobalTeleInfo
//  Description:	ɾ��һ��ȫ�ִ�����Ϣ 				
//  Output:			
//  Date:	03/30/2011
// **********************************************************
int CGlobalModule::DeleteGlobalTeleInfo( int nRoleID )
{
	GlobalTeleInfoList::iterator it = mGlobalTeleInfo.find( nRoleID );
	if ( it != mGlobalTeleInfo.end() )
	{
		mGlobalTeleInfo.erase( it );
	}
	return 0;
}

// ***********************************************************
//  Function:		Initialize
//  Description:	 				
//  Output:			
//  Date:	03/30/2011
// **********************************************************
int CGlobalModule::Initialize()
{
	mGlobalTeleInfo.initailize();
	mOutTimer = CWTimer(3000);
	mSyncTimer = CWTimer(5000);
	return 0;
}	

// ***********************************************************
//  Function:		PlayerLeaveGlobalWar
//  Description:	�뿪ս��				
//  Output:			
//  Date:	04/12/2011
// **********************************************************
void CGlobalModule::PlayerLeaveGlobalWar( int nRoleID, int nReason /* = EREASON_LEAVEWAR_RETURNBACK */ )
{	
	CMessage tMsgHead;
	CMessagePlayerLeaveWarNotify tMsgLeaveWar;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2D_NOTIFY_PLAYERLEAVEWAR );
	tMsgHead.set_msgpara( (int)&tMsgLeaveWar );
	tMsgLeaveWar.set_roleid( nRoleID );
	tMsgLeaveWar.set_reason( nReason );
	CSceneLogic::GetSingleton().Send2GlobalDunServer( &tMsgHead );
}

// ***********************************************************
//  Function:		EndGlobalWar
//  Description:	����ս��				
//  Output:			
//  Date:	04/12/2011
// **********************************************************
void CGlobalModule::EndGlobalWar( int nReason, int nRegKey )
{
	CMessage tMsgHead;	
	CMessageWarEndNotify tMsgEndWar;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2D_NOTIFY_WAREND );
	tMsgHead.set_msgpara( (int)&tMsgEndWar );
	tMsgEndWar.set_reason( nReason );
	tMsgEndWar.set_warregkey( nRegKey );
	CSceneLogic::GetSingleton().Send2GlobalDunServer( &tMsgHead );
}

// ***********************************************************
//  Function:		OnTimer
//  Description:	����ʱ�¼� 				
//  Output:			
//  Date:	03/30/2011
// **********************************************************
void CGlobalModule::OnTimer( unsigned int vTickCount, unsigned int vTickOffsekt )
{
	if ( mSyncTimer.Elapse( vTickOffsekt ) == true )
	{
		SyncGlobalPlayer();
	}

	if ( IS_GLOBAL_SCENESERVER( CSceneLogic::GetSingleton().GetLineID() ) == false )
		return;
	CTemplateGlobalMapConfig *tpConfig = (CTemplateGlobalMapConfig*)CDataStatic::GetTemp( TEMP_GLOBALMAPCONFIG );
	if ( tpConfig == NULL )
	{
		return;
	}
	if ( mOutTimer.Elapse( vTickOffsekt ) == true )
	{
		CSceneObjManagerImp* pSceneneObjManagerImp = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp ;
 
        for( CSceneObjManagerImp::ObjMng_EntityPlayer::iterator tPlayerIt = pSceneneObjManagerImp->mEntityPlayerPool.begin( );
                tPlayerIt != pSceneneObjManagerImp->mEntityPlayerPool.end( );
                ++tPlayerIt
            )
        {
			CEntityPlayer* tpSrcEntity = &( *tPlayerIt );
			if ( tpSrcEntity->HasBuff( tpConfig->mBuffID ) == false )
			{
				CGlobalMapData tMapData;
				tMapData.mMapID = tpConfig->mOutMap;
				tMapData.mPosX = tpConfig->mOutX;
				tMapData.mPosY = tpConfig->mOutY;
				CGlobalModule::GetSingleton().GlobalTelePort( tpSrcEntity, EGLOBALTELE_TYPE_RETURNTOGAME, ESERVERTYPE_SCENESER, &tMapData );
			}
		}
	}	
}


// ***********************************************************
//  Function:		GetGlobalteleType
//  Description:	��ȡ��������				
//  Output:			
//  Date:	04/27/2011
// **********************************************************
int CGlobalModule::GetGlobalteleType( int nCharID  )
{
	CGlobalTeleInfo *tpGlobalTeleInfo = GetGlobalTeleInfo( nCharID );
	if ( tpGlobalTeleInfo == NULL )
	{
		return -1;
	}
	return tpGlobalTeleInfo->mTeleType;
}


// ***********************************************************
//  Function:		SyncGlobalPlayer
//  Description:	ͬ�����ƶ��е����(���ȫ�ַ�����û�������Ϣ��ֱ���߳�)				
//  Output:			
//  Date:	09/15/2011
// **********************************************************
int CGlobalModule::SyncGlobalPlayer()
{
	if ( IS_DUNGEONSERVER_LINE( CSceneLogic::GetSingleton().GetLineID() ) == false )
		return SUCCESS;	
	
	CMessage tMsgHead;
	CMessageSyncGlobalPlayeNotify tMsgSyncGlobalPlayer;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2S_NOTIFY_SYNCGLOBALPLAYE );
	tMsgHead.set_msgpara( (int)&tMsgSyncGlobalPlayer );

	CSceneObjManagerImp* pSceneneObjManagerImp = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp ;
	for( CSceneObjManagerImp::ObjMng_EntityPlayer::iterator tPlayerIt = pSceneneObjManagerImp->mEntityPlayerPool.begin( );
		tPlayerIt != pSceneneObjManagerImp->mEntityPlayerPool.end( );
		++tPlayerIt
		)
	{
		CEntityPlayer* tpSrcEntity = &( *tPlayerIt );	
		if ( tpSrcEntity->GetRoleWorldID() != CSceneLogic::GetSingleton().GetLineID() )
		{
			PBWorldPlayer *tpWorldPlayer = NULL;
			for ( int i = 0; i < tMsgSyncGlobalPlayer.worldplayerlist_size(); ++i )
			{
				if ( tMsgSyncGlobalPlayer.mutable_worldplayerlist( i )->worldid() == tpSrcEntity->GetRoleWorldID() )
				{
					tpWorldPlayer = tMsgSyncGlobalPlayer.mutable_worldplayerlist( i );
					break;
				}
			}
			if ( tpWorldPlayer == NULL )
			{
				tpWorldPlayer = tMsgSyncGlobalPlayer.add_worldplayerlist();
				tpWorldPlayer->set_worldid( tpSrcEntity->GetRoleWorldID() );
			}
			tpWorldPlayer->add_roleid( tpSrcEntity->GetCharID() );
		}
	}
	if ( tMsgSyncGlobalPlayer.worldplayerlist_size() > 0 )
	{
		CSceneLogic::GetSingleton().Send2GlobalDunServer( &tMsgHead );
	}
	return SUCCESS;
}
