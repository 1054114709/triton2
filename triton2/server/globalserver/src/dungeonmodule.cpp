#include "dungeonmodule.h"
#include "tinyxml.h"
#include "globalserver_pb.hxx.pb.h"
#include "dungeonlogic.h"
#include "errcode.h"
#include "dungeontype.h"
#include "dunobjmanager.h"
template<>  CDungeonModule * CSingleton<CDungeonModule>::spSingleton = NULL;

// ����������
void CDungeonModule::OnLaunchServer( )
{
	mGlobalServerConfig.Initialize();
	mServerManager.Initialize();
	mLevelConfig.Initialize();	
	for ( int i = 0; i < ARRAY_CNT(mWarRegInfoManager); ++i )
	{
		mWarRegInfoManager[i].Initialize();
	}	
	mGlobalPlayerList.initailize();
}

// �˳�������
void CDungeonModule::OnExitServer( )
{

}

// ������Timer
void CDungeonModule::OnTimer( unsigned int vTickCount, unsigned int vTickOffset )
{
	if ( mTimer.Elapse( vTickOffset ) == true )
	{		
		RemoveTimeOutRole();
		DeleteValidWarRegInfo();
		AddWarMemberFromWaitList();		
		CheckWarRegInfo();
	}
}

// ��������
void CDungeonModule::OnLoadConfig( )
{	
	ReadServerConfig( "../config/data/serverlist.xml" );
	ReadLevelConfig( "../config/data/levelconfig.xml" );
	ReadDungeonConfig( "../config/data/dungeonconfig.xml" );
	ReadGameConfig( "../config/data/gameconfig.xml" );
}

// ���շ�������Ϣ
void CDungeonModule::OnServerMessage( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID )
{
	LK_ASSERT( pMsg != NULL, return )
	switch( pMsg->mutable_msghead()->messageid() )
	{
		case ID_S2D_REQUEST_GLOBALTELEPORT:
		{
			OnMessageGlobalTeleportRequest( pMsg, nGameID, nSrcFe, nSrcID );
			break;
		}
		case ID_G2D_RESPONSE_CHANGESERVER:
		{
			OnMessageRoleGlobalTeleResponse( pMsg, nGameID, nSrcFe, nSrcID );
			break;
		}	

		case ID_G2D_RESPONSE_CREATEREPETION:
		{
			OnMessageCreateRepetionResponse( pMsg, nGameID, nSrcFe, nSrcID );
			break;
		}		

		case ID_S2D_REQUEST_PLAYERAPPLYWAR:
		{
			OnMessagePlayerApplyWarRequest( pMsg, nGameID, nSrcFe, nSrcID );
			break;
		}

		case ID_S2D_NOTIFY_PLAYERLEAVEWAR:
		{
			OnMessagePlayerLeaveWarNotify( pMsg, nGameID, nSrcFe, nSrcID );
			break;
		}

		case ID_S2D_NOTIFY_WAREND:		
		{
			OnMessageWarEndNotify( pMsg, nGameID, nSrcFe, nSrcID );
			break;
		}
		case ID_S2S_NOTIFY_KICKGLOBALPLAYER :
		{
			OnMessageKickPlayer( pMsg, nGameID, nSrcFe, nSrcID );
			break;
		}
		case ID_S2S_NOTIFY_KICKGLOBALPLAYERACK :
		{
			OnMessageKickGlobalPlayerACK( pMsg, nGameID, nSrcFe, nSrcID );
			break;
		}
		case ID_S2S_NOTIFY_SYNCGLOBALPLAYE:
		{
			OnMessageSyncGlobalPlayer( pMsg, nGameID, nSrcFe, nSrcID );
			break;
		}
		default:
			break;
	}
}

// ���������
void CDungeonModule::OnMessageGlobalTeleportRequest( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessageGlobalTeleportRequest *tpMsg = ( CMessageGlobalTeleportRequest * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )

	// ѡȡ��������ID
	int tServerKey = 0;
	CGlobalTeleData tTeleData;
	CGlobalPlayer *tpPlayer = NULL;
	if ( tpMsg->servertype() == ESERVERTYPE_DUNGEON )
	{	
		// ��ȡע����Ϣ
		tpPlayer = GetGlobalPlayer( tpMsg->roleid() );
		if ( tpPlayer == NULL )
		{
			SendResponseGlobalTeleport( EDUNGEON_ERROR_NOTAPPLIED, tpMsg->roleid(), nGameID, tpMsg->serverid(), NULL, tTeleData );
			LOG_ERROR( "default","GlobalTele:can not find role info by roleid: %d",tpMsg->roleid());
			return;			
		}		
		CWarRegInfo *tpWarRegInfo = ( CWarRegInfo * )CDunobjManager::GetSingleton().GetObject( tpPlayer->mWarRegKey );
		if ( tpWarRegInfo == NULL )
		{
			SendResponseGlobalTeleport( EDUNGEON_ERROR_NOTAPPLIED, tpMsg->roleid(), nGameID, tpMsg->serverid(), NULL, tTeleData );
			LOG_ERROR( "default","GlobalTele:can not find WarReginfo by roleid: %d, warkey:",tpMsg->roleid(), tpPlayer->mWarRegKey);
			return;			
		}
		tServerKey = tpWarRegInfo->mServerKey;		
		CRoleInfo *tpRoleInfo = tpWarRegInfo->GetRoleInfo( tpMsg->roleid() );
		if ( tpRoleInfo != NULL )
		{
			tTeleData.mTeamFlag = tpRoleInfo->mTeamFlag;		
		}
		
		// �ָ�״̬
		if ( tpMsg->teletype() == EGLOBALTELE_TYPE_GLOBALSERVER )
		{
			tpWarRegInfo->ChangeRoleStatus( tpMsg->roleid(), CRoleInfo::ESTATUS_NORMAL );			
			tTeleData.mRepetionKey = tpWarRegInfo->mReptionKey;
		}
		// ����ԭ������,ɾ�����
		else if( tpMsg->teletype() == EGLOBALTELE_TYPE_RETURNTOGAME )
		{
			tpWarRegInfo->DeleteRoleInfo( tpMsg->roleid() );			
		}
	}
	else
	{
		CGameConfig *tpGameConfig = mGlobalServerConfig.GetGameConfig( tpMsg->worldid() );
		if ( tpGameConfig == NULL )
		{
			
			SendResponseGlobalTeleport( EDUNGEON_ERROR_CANNOTGLOBALTELE, tpMsg->roleid(), nGameID, tpMsg->serverid(), NULL, tTeleData );			
			return;
		}
		tpPlayer = RegPlayerToServer( tpMsg->roleid(), tpMsg->worldid() );
		if ( tpPlayer == NULL )
		{
			SendResponseGlobalTeleport( EDUNGEON_ERROR_CANNOTGLOBALTELE, tpMsg->roleid(), nGameID, tpMsg->serverid(), NULL, tTeleData );			
			return;
		}
		tServerKey = mServerManager.SelectServerWithMinNum( tpGameConfig->mServerListID, EServerType( tpMsg->servertype()), CServerManager::ESELECT_TYPE_BYROLENUM, mGlobalServerConfig );
	}
	
	if ( tServerKey <= 0 )
	{
		SendResponseGlobalTeleport( EDUNGEON_ERROR_CANNOTGLOBALTELE, tpMsg->roleid(), nGameID, tpMsg->serverid(), NULL, tTeleData );			
		LOG_ERROR( "default","can not find server information (type:%d)", tpMsg->servertype() );
		return;
	}

	// ����ԭ������,ɾ�����
	if( tpMsg->teletype() == EGLOBALTELE_TYPE_RETURNTOGAME )
	{
		DeleteGlobalPlayer( tpMsg->roleid() );
		LOG_INFO("default", "Globarwar: delete role id :%d because return to game", tpMsg->roleid());
	}	
		
	// ����Ǹ����Ļ��ø�����key��ֵ
	int tServerListID = -1;
	CGlobalServerInfo *tpServerInfo = mGlobalServerConfig.GetGlobalServerInfo( tServerKey, tServerListID );	
	if ( tpServerInfo == NULL )
	{
		SendResponseGlobalTeleport( EDUNGEON_ERROR_CANNOTGLOBALTELE, tpMsg->roleid(), nGameID, tpMsg->serverid(), NULL, tTeleData );			
		LOG_ERROR( "default","can not find server information (type:%d,key:%d)", tpMsg->servertype(), tServerKey );		
		return;
	}	
	
	// ��¼serverkey
	if ( tpPlayer == NULL )
	{
		SendResponseGlobalTeleport( EDUNGEON_ERROR_CANNOTGLOBALTELE, tpMsg->roleid(), nGameID, tpMsg->serverid(), NULL, tTeleData );			
		return;
	}
	tpPlayer->mServerKey = tServerKey;

	// ������Լ���������������ֱ�ӿ���Ϳ�����	
	// ���Ϳ������Ϣ��Ӧ	
	// Ŀ�곡���ͱ�����һ�¿���ֱ�Ӵ���
	if ( tpServerInfo->mWorldID == tpMsg->worldid() && tpMsg->teletype() == EGLOBALTELE_TYPE_GLOBALSERVER )
	{			
		tTeleData.mLineID = tpServerInfo->mLineID;
		tTeleData.mRepetionIndex = tpServerInfo->mReptionIndex;		
		if ( tpMsg->has_mapdata() )
		{
			tTeleData.mMapID = tpMsg->mutable_mapdata()->mapid();
			tTeleData.mPosX =  tpMsg->mutable_mapdata()->posx();
			tTeleData.mPosY =  tpMsg->mutable_mapdata()->posy();			
		}
		else
		{
			tTeleData.mMapID = tpServerInfo->mGlobalMapInfo.mMapID;
			tTeleData.mPosX = tpServerInfo->mGlobalMapInfo.mPosX;
			tTeleData.mPosY = tpServerInfo->mGlobalMapInfo.mPosY;
		}
		SendResponseGlobalTeleport( SUCCESS, tpMsg->roleid(), tpMsg->worldid(), tpMsg->serverid(), NULL, tTeleData );
		return;
	}

	else if ( tpMsg->originalworldid() == 0 && tpMsg->teletype() != EGLOBALTELE_TYPE_GLOBALSERVER )
	{		
		tTeleData.mLineID = tpMsg->originalserverid();	
		if ( tpMsg->has_mapdata() )
		{
			tTeleData.mMapID = tpMsg->mutable_mapdata()->mapid();
			tTeleData.mPosX =  tpMsg->mutable_mapdata()->posx();
			tTeleData.mPosY =  tpMsg->mutable_mapdata()->posy();			
		}
		else
		{
			tTeleData.mMapID = tpServerInfo->mOriginalMapInfo.mMapID;
			tTeleData.mPosX = tpServerInfo->mOriginalMapInfo.mPosX;
			tTeleData.mPosY = tpServerInfo->mOriginalMapInfo.mPosY;	
		}		
		SendResponseGlobalTeleport( SUCCESS, tpMsg->roleid(), tpMsg->worldid(), tpMsg->serverid(), NULL, tTeleData );
		return;
	}

	// �޸ķ�������������
	//int tNum = tpMsg->teletype() == EGLOBALTELE_TYPE_GLOBALSERVER ? 1 : -1;	
	//mServerManager.ChangeServerSatus( tServerKey, tNum, 0, mGlobalServerConfig, CServerManager::ESELECT_TYPE_BYROLENUM, EServerType(tpMsg->servertype()) );		

	// �����ط�����Ϣ
	CMessage tMsgHead;
	CMessageChangeServerRequest tMsgGlobalTele;
	tMsgHead.mutable_msghead()->set_messageid( ID_D2G_REQUEST_CHANGESERVER );
	tMsgHead.set_msgpara( (int)&tMsgGlobalTele );
	
	int tGameID = 0;
	if ( tpMsg->teletype() == EGLOBALTELE_TYPE_GLOBALSERVER )
	{
		tMsgGlobalTele.set_lineid( tpServerInfo->mLineID );
		if ( tpMsg->has_mapdata() )
		{
			tMsgGlobalTele.set_mapid( tpMsg->mutable_mapdata()->mapid() );			
			tMsgGlobalTele.set_posx( tpMsg->mutable_mapdata()->posx() );
			tMsgGlobalTele.set_posy( tpMsg->mutable_mapdata()->posy() );	
			if (  tpMsg->mutable_mapdata()->lineid() > 0 )
			{
				tMsgGlobalTele.set_lineid( tpMsg->mutable_mapdata()->lineid() ); 
			}
		}
		else
		{
			tMsgGlobalTele.set_mapid( tpServerInfo->mGlobalMapInfo.mMapID );
			tMsgGlobalTele.set_posx( tpServerInfo->mGlobalMapInfo.mPosX );
			tMsgGlobalTele.set_posy( tpServerInfo->mGlobalMapInfo.mPosY );
		}				
		if ( tpMsg->originalworldid() > 0 )
		{
			tMsgGlobalTele.set_worldid( tpMsg->originalworldid() );
		}
		else
		{
			tMsgGlobalTele.set_worldid( tpMsg->worldid() );
		}		
		tMsgGlobalTele.set_key( tTeleData.mRepetionKey );
		tMsgGlobalTele.set_teamflag( tTeleData.mTeamFlag );
		tGameID = tpServerInfo->mWorldID;
	}
	else
	{
		tMsgGlobalTele.set_lineid( tpMsg->originalserverid() );
		if ( tpMsg->has_mapdata() )
		{
			tMsgGlobalTele.set_mapid( tpMsg->mutable_mapdata()->mapid() );			
			tMsgGlobalTele.set_posx( tpMsg->mutable_mapdata()->posx() );
			tMsgGlobalTele.set_posy( tpMsg->mutable_mapdata()->posy() );
			if (  tpMsg->mutable_mapdata()->lineid() > 0 )
			{
				tMsgGlobalTele.set_lineid( tpMsg->mutable_mapdata()->lineid() ); 
			}
		}
		else
		{
			tMsgGlobalTele.set_mapid( tpServerInfo->mOriginalMapInfo.mMapID );
			tMsgGlobalTele.set_posx( tpServerInfo->mOriginalMapInfo.mPosX );
			tMsgGlobalTele.set_posy( tpServerInfo->mOriginalMapInfo.mPosY );
		}				
		tGameID = tpMsg->originalworldid( );
		if ( tpMsg->teletype() == EGLOBALTELE_TYPE_RETURNTOGAME )
		{
			tMsgGlobalTele.set_worldid( tpMsg->originalworldid( ) );
		}		
		else
		{
			tMsgGlobalTele.set_worldid( 0 );
		}
	}
	
	tMsgGlobalTele.set_roleid( tpMsg->roleid() );	
	tMsgGlobalTele.set_serverid( tpMsg->serverid() );
	tMsgGlobalTele.set_currentworldid( tpMsg->worldid() );
	tMsgGlobalTele.set_serverkey( tServerKey );
	tMsgGlobalTele.set_accountid( tpMsg->accountid() );
	tMsgGlobalTele.set_gameid( tpMsg->gameid() );
	tMsgGlobalTele.set_mac( tpMsg->mutable_mac()->c_str() );
	CDungeonLogic::GetSingleton().Send2Gate( &tMsgHead, tGameID );
}

void CDungeonModule::SendResponseGlobalTeleport( int nErrcode, int nRoleID, int nGameID, int nServerID, const char *pGateAddr, CGlobalTeleData &rTeleData )
{
	CMessage tMsgHead;
	CMessageGlobalTeleportResponse tMsgGlobalTeleport;
	tMsgHead.mutable_msghead()->set_messageid( ID_D2S_RESPONSE_GLOBALTELEPORT );
	tMsgHead.set_msgpara( (int)&tMsgGlobalTeleport );
	tMsgGlobalTeleport.set_errcode( nErrcode );
	if ( pGateAddr != NULL )
	{		
		tMsgGlobalTeleport.set_addr( pGateAddr );		
	}
	tMsgGlobalTeleport.set_roleid( nRoleID );
	tMsgGlobalTeleport.set_logintoken( rTeleData.mLoginToken );
	tMsgGlobalTeleport.set_reptionkey( rTeleData.mRepetionKey );
	tMsgGlobalTeleport.set_mapid( rTeleData.mMapID );
	tMsgGlobalTeleport.set_posx( rTeleData.mPosX );
	tMsgGlobalTeleport.set_posy( rTeleData.mPosY );
	tMsgGlobalTeleport.set_lineid( rTeleData.mLineID );
	tMsgGlobalTeleport.set_repetionindex( rTeleData.mRepetionIndex );
	tMsgGlobalTeleport.set_teamflag( rTeleData.mTeamFlag );
	tMsgGlobalTeleport.set_sceneworldid( rTeleData.mSceneWorldID );
	CDungeonLogic::GetSingleton().Send2Gate( &tMsgHead, nGameID );
}

// ���ط��ؿ��֪ͨ
void CDungeonModule::OnMessageRoleGlobalTeleResponse( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessageChangeServerResponse *tpMsg = ( CMessageChangeServerResponse * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	

	int tServerListID = -1;
	CGlobalServerInfo *tpServerInfo = mGlobalServerConfig.GetGlobalServerInfo( tpMsg->serverkey(), tServerListID );
	LK_ASSERT( tpServerInfo != NULL, return )	
	if ( tpMsg->errcode() != SUCCESS )
	{
		DeleteGlobalPlayer( tpMsg->roleid() );
		LOG_INFO("default", "Globarwar: delete role id: %d because Global Tele error", tpMsg->roleid());
	}
	
	const char *pGateAddr = NULL;
	if ( tpMsg->has_addr() )
	{
		pGateAddr = tpMsg->mutable_addr()->c_str();
	}		
	CGlobalTeleData tTeleData;
	tTeleData.mSceneWorldID = nGameID;//tpServerInfo->mWorldID;// Ӧ����Ҫ���ﳡ����WorldID
	tTeleData.mLoginToken = tpMsg->logintoken();	
	SendResponseGlobalTeleport( tpMsg->errcode(), tpMsg->roleid(), tpMsg->worldid(), tpMsg->serverid(), pGateAddr, tTeleData );
}

// ***************************************************************
// Function:   CreateReption
// Description: ��������
// Others:         
// Date:         04/08/2011 
//***************************************************************
int CDungeonModule::CreateReption( CWarRegInfo *pWarRegInfo, int nServerListID /* = 0 */, int nRepetionIndex /* = 0 */ )
{
	LK_ASSERT( pWarRegInfo != NULL, return -1 )
	int tServerKey = mServerManager.SelectServerWithMinNum( nServerListID, ESERVERTYPE_DUNGEON, CServerManager::ESELECT_TYPE_BYWARNUM, mGlobalServerConfig, nRepetionIndex );
	if ( tServerKey == 0 )
	{
		return -1;
	}

	int tServerListID = -1;
	CGlobalServerInfo *tpServerInfo = mGlobalServerConfig.GetGlobalServerInfo( tServerKey, tServerListID );
	if ( tpServerInfo == NULL )
	{
		LOG_ERROR( "default","get globalserverinfo wrong, serverkey:%d", tServerKey );
		return -1;
	}

	// ��������ս������1	
	//mServerManager.ChangeServerSatus( tServerKey, 0, 1, mGlobalServerConfig );
	pWarRegInfo->mServerKey = tServerKey;	

	CMessage tMsgHead;
	CMessageCreateRepetionRequest tMsgCreateReption;
	tMsgHead.mutable_msghead()->set_messageid( ID_D2G_REQUEST_CREATEREPETION );
	tMsgHead.set_msgpara( (int)&tMsgCreateReption );
	tMsgCreateReption.set_regkey( pWarRegInfo->mRegKey );
	tMsgCreateReption.set_reptionindex( tpServerInfo->mReptionIndex );
	CLevelSection *tpSection = mLevelConfig.GetLeveSection( pWarRegInfo->mLevelID );
	if ( tpSection != NULL )
	{
		tMsgCreateReption.set_repetionlevel( tpSection->mMinLevel ); 
	}
	CDungeonLogic::GetSingleton().Send2Gate( &tMsgHead, tpServerInfo->mWorldID );
	return SUCCESS;
}

// ***************************************************************
// Function:   OnMessageCreateRepetionResponse
// Description: ���������Ļ�Ӧ��Ϣ
// Others:         
// Date:         04/08/2011 
//***************************************************************
void CDungeonModule::OnMessageCreateRepetionResponse( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessageCreateRepetionResponse *tpMsg = ( CMessageCreateRepetionResponse * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CWarRegInfo *tpWarRegInfo = (CWarRegInfo *)CDunobjManager::GetSingleton().GetObject( tpMsg->regkey() );
	if ( tpWarRegInfo == NULL )
	{
		LOG_ERROR( "default","can not find WarRegInfo by RegKey:%d", tpMsg->regkey() );
		return;
	}
	if ( tpMsg->errcode() != SUCCESS )
	{
		tpWarRegInfo->mStatus = CWarRegInfo::EWARSTATUS_INITIAL;
		LOG_ERROR( "default","can not find WarRegInfo by RegKey:%d", tpMsg->regkey() );
		return;
	}
	int tServerListID = 0;
	mGlobalServerConfig.GetGlobalServerInfo( tpWarRegInfo->mServerKey, tServerListID );	
	tpWarRegInfo->mReptionKey = tpMsg->reptionkey();
	tpWarRegInfo->mStatus = CWarRegInfo::EWARSTATUS_START;

	tpWarRegInfo->AssignTeam( mGlobalServerConfig.GetWarStartNum( tServerListID ) );

	// ������ҿ��Խ��븱����֪ͨ
	NotifyWarEnable( tpWarRegInfo );
}

// ***************************************************************
// Function:   OnMessagePlayerApplyWarRequest
// Description: ��ұ���
// Others:         
// Date:         04/08/2011 
//***************************************************************
void CDungeonModule::OnMessagePlayerApplyWarRequest( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessagePlayerApplyWarRequest *tpMsg = ( CMessagePlayerApplyWarRequest * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	
	int tLevelID = mLevelConfig.GetIDByLevel( tpMsg->rolelevel() );
	if ( tLevelID <= 0 )
	{
		// ���ܱ���
		SendApplyWarResponse( nGameID, nSrcID, EDUNGEON_ERROR_LEVELLOW, 0, tpMsg->roleid(), 0, 0, 0, 0 );
		return;
	}	
	
	// �Ȳ��Ҹ�����Ϣ
	CGlobalPlayer *tpPlayer = GetGlobalPlayer( tpMsg->roleid() );
	if ( tpPlayer == NULL )
	{
		// �����ɹ�,ע�������Ϣ
		tpPlayer = RegPlayerToServer( tpMsg->roleid(), tpMsg->worldid(), tpMsg->repetionindex() );
	}	

	// ��ȡս��������
	CWarRegInfoManager *tpManager = GetWarManagerByWorldID( tpMsg->worldid(), tpMsg->repetionindex() );
	if ( tpManager == NULL )
	{
		SendApplyWarResponse( nGameID, nSrcID, EDUNGEON_ERROR_MAXAPPLYNUM, 0, tpMsg->roleid(), 0, 0, 0, 0 );		
		DeleteGlobalPlayer( tpMsg->roleid() );
		return;
	}

	if ( tpManager->CheckApply( tpMsg->roleid() ) == true )
	{
		// �Ѿ�������
		// �����ٱ��������ˣ�����ɾ�������Ϣ����2011.11.10 by lipeng
		//DeleteGlobalPlayer( tpMsg->roleid() );
		tpManager->DeleteRoleWarRegInfo( tpMsg->roleid() );
		SendApplyWarResponse( nGameID, nSrcID, EDUNGEON_ERROR_HASAPPLIED, 0, tpMsg->roleid(), 0, 0, 0, 0 );
		return;
	}		

	if ( tpPlayer == NULL )
	{
		SendApplyWarResponse( nGameID, nSrcID, EDUNGEON_ERROR_MAXAPPLYNUM, 0, tpMsg->roleid(), 0, 0, 0, 0 );
		return;
	}	
	
	CRoleInfo tRoleInfo;
	tRoleInfo.mGameID = tpMsg->worldid();
	tRoleInfo.mRoleID = tpMsg->roleid();
	int tCanStart = 0;
	int tWarRegKey = 0;
	int tRegKey = 0;
	int tTeamFlag = 0; 
	int tRet = tpManager->RegRoleInfo( tRoleInfo, tRegKey, tLevelID );
	if ( tRet == SUCCESS )
	{
		CWarRegInfo *tpWarRegInfo = tpManager->GetWarRegInfoByRegKey( tRegKey );
		if ( tpWarRegInfo != NULL )
		{
			if ( tpWarRegInfo->IsRepetionStart() )
			{
				tTeamFlag = tRoleInfo.mTeamFlag;			
				tCanStart = 1;
				tpPlayer->mWarRegKey = tpWarRegInfo->mRegKey;
			}			
			tWarRegKey = tpWarRegInfo->mRegKey;
		}		 
	}
	else
	{	
		SendApplyWarResponse( nGameID, nSrcID, tRet, 0, tpMsg->roleid(), 0, 0, 0, 0 );
		DeleteGlobalPlayer( tpMsg->roleid() );
		return;
	}
	int tMinLevel = 0;
	int tMaxLevel = 0;
	mLevelConfig.GetLevelRange( tLevelID, tMinLevel, tMaxLevel );
	LOG_NOTICE( "default","Player(RoleID:%d) Apply GlobalWarSucess(Level:%d-%d,WarRegKey:%d)", tpMsg->roleid(), tMinLevel, tMaxLevel, tWarRegKey );
	SendApplyWarResponse( nGameID, nSrcID, tRet, tWarRegKey, tpMsg->roleid(), tCanStart, tMinLevel, tMaxLevel, tTeamFlag );

	// ��¼������־
	LOG_INFO("default", "Globalwar Apply successfully, role id:%d", tpMsg->roleid());
}

// ***************************************************************
// Function:   SendApplyWarResponse
// Description: ���ͱ����Ļ�Ӧ��Ϣ
// Others:         
// Date:         04/08/2011 
//***************************************************************
void CDungeonModule::SendApplyWarResponse( int nGameID, int nServerID, int nErrcode, int nRegKey, int nRoleID, int nCanStart, int nMinLevel, int nMaxLevel, int nTeamFlag )
{
	CMessage tMsgHead;
	CMessagePlayerApplyWarResponse tMsgApplyWar;
	tMsgHead.mutable_msghead()->set_messageid( ID_D2S_REQPONSE_PLAYERAPPLYWAR );
	tMsgHead.set_msgpara( (int)&tMsgApplyWar );
	tMsgApplyWar.set_regkey( nRegKey );
	tMsgApplyWar.set_canstart( nCanStart );
	tMsgApplyWar.set_errcode( nErrcode );
	tMsgApplyWar.set_roleid( nRoleID );
	tMsgApplyWar.set_minlevel( nMinLevel );
	tMsgApplyWar.set_maxlevel( nMaxLevel );
	tMsgApplyWar.set_teamflag( nTeamFlag );
	CDungeonLogic::GetSingleton().Send2Scene( &tMsgHead, nGameID, nServerID );
}

// ***************************************************************
// Function:   NotifyWarEnable
// Description: ���Ϳ��Խ�������֪ͨ
// Others:         
// Date:         04/08/2011 
//***************************************************************
void CDungeonModule::NotifyWarEnable( CWarRegInfo *pWarRegInfo )
{
	LK_ASSERT( pWarRegInfo != NULL, return )
	for ( int i = 0; i < pWarRegInfo->mRoleNum; ++ i )
	{
		CGlobalPlayer *tpPlayer = GetGlobalPlayer( pWarRegInfo->mRoleInfo[i].mRoleID );
		if ( tpPlayer == NULL )
		{
			continue;
		}
		tpPlayer->mWarRegKey = pWarRegInfo->mRegKey;
		pWarRegInfo->mRoleInfo[i].mRoleStatus = CRoleInfo::ESTATUS_WAIT;
		pWarRegInfo->mRoleInfo[i].mOffTime = time( NULL );
		NotifyPlayerWarEnable( pWarRegInfo->mRoleInfo[i].mGameID, pWarRegInfo->mRoleInfo[i].mRoleID, pWarRegInfo->mRegKey, pWarRegInfo->mRoleInfo[i].mTeamFlag );
	}
}

// ***************************************************************
// Function:   NotifyPlayerWarEnable
// Description: �����֪ͨ���Խ���ս��
// Others:         
// Date:         04/08/2011 
//***************************************************************
void CDungeonModule::NotifyPlayerWarEnable( int nGameID, int nRoleID, int nWarRegKey, int nTeamFlag )
{	
	CMessage tMsgHead;
	CMessageWarEnableNotify tMsgWarEnable;
	tMsgHead.mutable_msghead()->set_messageid( ID_D2S_NOTIFY_WARENABLE );
	tMsgHead.set_msgpara( (int)&tMsgWarEnable );
	tMsgWarEnable.set_roleid( nRoleID );
	tMsgWarEnable.set_warregkey( nWarRegKey );
	tMsgWarEnable.set_teamflag( nTeamFlag );
	CDungeonLogic::GetSingleton().Send2Gate( &tMsgHead, nGameID );
}

// ***************************************************************
// Function:   OnMessagePlayerLeaveWarNotify
// Description: ����뿪ս������Ϣ֪ͨ
// Others:         
// Date:         04/08/2011 
//***************************************************************
void CDungeonModule::OnMessagePlayerLeaveWarNotify( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessagePlayerLeaveWarNotify *tpMsg = ( CMessagePlayerLeaveWarNotify * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CGlobalPlayer *tpPlayer = GetGlobalPlayer( tpMsg->roleid() );
	if ( tpPlayer == NULL )
	{
		return;
	}	
	CWarRegInfoManager *tpWarManager = GetWarManagerByWorldID( tpPlayer->mWorldID, tpPlayer->mRepetionIndex );
	if ( tpWarManager == NULL )
	{
		return;
	}

	// һ��ֱ��ɾ����Ϣ,һ�ֽ��е���ʱ����ɾ��
	if ( tpMsg->reason() == EREASON_LEAVEWAR_OFFLINE )
	{
		CWarRegInfo *tpWarRegInfo = ( CWarRegInfo * )CDunobjManager::GetSingleton().GetObject( tpPlayer->mWarRegKey );
		if ( tpWarRegInfo != NULL )
		{	
			// �ı�״̬			
			tpWarRegInfo->ChangeRoleStatus( tpMsg->roleid(), CRoleInfo::ESTATUS_OFFLINE );			
		}		
		else
		{
			tpWarManager->DeleteFromWaitList( tpMsg->roleid() );
			DeleteGlobalPlayer( tpMsg->roleid() );
			LOG_INFO("default", "Globarwar: delete role id: %d because offline", tpMsg->roleid());
		}
	}
	else
	{
		tpWarManager->DeleteRoleWarRegInfo( tpMsg->roleid() );
		DeleteGlobalPlayer( tpMsg->roleid() );
		LOG_INFO("default", "Globarwar: delete role id: %d because offline", tpMsg->roleid());
	}
}

// ***************************************************************
// Function:   OnMessageWarEndNotify
// Description: ս��������֪ͨ
// Others:         
// Date:         04/08/2011 
//***************************************************************
void CDungeonModule::OnMessageWarEndNotify( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID )
{	
	LK_ASSERT( pMsg != NULL, return )	
	CMessageWarEndNotify *tpMsg = ( CMessageWarEndNotify * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CWarRegInfo *tpWarRegInfo = ( CWarRegInfo * )CDunobjManager::GetSingleton().GetObject( tpMsg->warregkey() );
	if ( tpWarRegInfo != NULL )
	{
		//mServerManager.ChangeServerSatus( tpWarRegInfo->mServerKey, 0, -1, mGlobalServerConfig );
		if ( tpMsg->reason() == EREASON_ENDWAR_BATTLEEND )
		{
			tpWarRegInfo->mStatus = CWarRegInfo::EWARSTATUS_BATTLEEND;
		}
		else if( tpMsg->reason() == EREASON_ENDWAR_REPETIONEND )
		{
			DeleteWarRegInfo( tpWarRegInfo );
		}		
		LOG_INFO("default", "GlobarWar:delete WarRegInfo id: %d because war end", tpWarRegInfo->get_id());
	}		
}

// ***************************************************************
// Function:   OnMessageKickPlayer
// Description: �������˵���Ϣ����
// Others:         
// Date:         04/08/2011 
//***************************************************************
void CDungeonModule::OnMessageKickPlayer( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessageKickGlobalPlayerNotify *tpMsg = ( CMessageKickGlobalPlayerNotify * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	CGlobalPlayer *tpPlayer =  GetGlobalPlayer( tpMsg->roleid() );
	if ( tpPlayer == NULL )
	{
		return;
	}

	int tServerListID = 0;
	CGlobalServerInfo *tpServerInfo = mGlobalServerConfig.GetGlobalServerInfo( tpPlayer->mServerKey, tServerListID );
	if ( tpServerInfo == NULL )
	{
		return;
	}
	
	CWarRegInfoManager *tpWarManager = GetWarManagerByWorldID( tpServerInfo->mWorldID, tpPlayer->mRepetionIndex );
	if ( tpWarManager != NULL )
	{	
		CWarRegInfo *tpWarRegInfo = ( CWarRegInfo * )CDunobjManager::GetSingleton().GetObject( tpPlayer->mWarRegKey );
		if ( tpWarRegInfo != NULL )
		{
			tpWarRegInfo->DeleteRoleInfo( tpMsg->roleid() );						
		}	
		else
		{
			tpWarManager->DeleteFromWaitList( tpMsg->roleid() );			
		}		
	}	
	DeleteGlobalPlayer( tpMsg->roleid() );	
	CDungeonLogic::GetSingleton().Send2Gate( pMsg, tpServerInfo->mWorldID );
}

// ***************************************************************
// Function:   OnMessageKickGlobalPlayerACK
// Description: �������˵�֪ͨ
// Others:         
// Date:         05/14/2011 
//***************************************************************
void CDungeonModule::OnMessageKickGlobalPlayerACK( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessageKickGlobalPlayerACK *tpMsg = ( CMessageKickGlobalPlayerACK * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	CGlobalPlayer *tpPlayer =  GetGlobalPlayer( tpMsg->roleid() );
	if ( tpPlayer != NULL )
	{
		int tServerListID = 0;
		CGlobalServerInfo *tpServerInfo = mGlobalServerConfig.GetGlobalServerInfo( tpPlayer->mServerKey, tServerListID );
		if ( tpServerInfo == NULL )
		{
			return;
		}

		CWarRegInfoManager *tpWarManager = GetWarManagerByWorldID( tpServerInfo->mWorldID, tpPlayer->mRepetionIndex );
		if ( tpWarManager != NULL )
		{	
			CWarRegInfo *tpWarRegInfo = ( CWarRegInfo * )CDunobjManager::GetSingleton().GetObject( tpPlayer->mWarRegKey );
			if ( tpWarRegInfo == NULL )
			{
				tpWarManager->DeleteFromWaitList( tpMsg->roleid() );
				DeleteGlobalPlayer( tpMsg->roleid() );
			}				
		}
		else
		{
			DeleteGlobalPlayer( tpMsg->roleid() );
		}		
	}
	CDungeonLogic::GetSingleton().Send2Gate( pMsg, tpMsg->roleworldid() );
}

// ***************************************************************
// Function:   AddWarMemberFromWaitList
// Description: �ӵȴ��б�����ӳ�Ա��ս����
// Others:         
// Date:         04/11/2011 
//***************************************************************
void CDungeonModule::AddWarMemberFromWaitList()
{
	for ( int i = 0; i < ARRAY_CNT(mWarRegInfoManager); ++i )
	{
		if ( mWarRegInfoManager[i].GetWarManagerStatus() == CWarRegInfoManager::EMANAGER_STATUS_USED )
		{
			CRoleInfo tRoleInfo[100];
			int tWarRegKey[100];
			int tNum = 100;
			mWarRegInfoManager[i].FetchRoleIntoWarFromWaitlist( tRoleInfo, tWarRegKey, tNum );			
			if ( tNum > 0 )
			{
				for ( int i = 0; i < tNum; ++i )
				{
					CGlobalPlayer *tpPlayer = GetGlobalPlayer( tRoleInfo->mRoleID );
					if ( tpPlayer != NULL )
					{
						tpPlayer->mWarRegKey = tWarRegKey[i];
						NotifyPlayerWarEnable( tRoleInfo[i].mGameID, tRoleInfo[i].mRoleID, tWarRegKey[i], tRoleInfo[i].mTeamFlag );						
					}					
				}		
			}	
		}		
	}	
}

// ***************************************************************
// Function:   CheckWarRegInfo
// Description: ����Ƿ��п��Կ�����ս����Ϣ
// Others:         
// Date:         04/11/2011 
//***************************************************************
void CDungeonModule::CheckWarRegInfo()
{	
	for ( int i = 0; i < ARRAY_CNT(mWarRegInfoManager); ++i )
	{
		if ( mWarRegInfoManager[i].GetWarManagerStatus() == CWarRegInfoManager::EMANAGER_STATUS_USED )
		{
			int tNum = mWarRegInfoManager[i].CheckWarRegInfo( mDungeonConfig.mWarTimeInterval );
			if ( tNum > 0 )
			{	
				CWarRegInfoManager::WarEnableList::iterator it = mWarRegInfoManager[i].GetWarEnableList().begin();
				for ( ; it != mWarRegInfoManager[i].GetWarEnableList().end(); ++it )
				{
					CWarRegInfo *tpWarRegInfo = (CWarRegInfo *)CDunobjManager::GetSingleton().GetObject( *it );
					if ( tpWarRegInfo == NULL )
					{				
						continue;
					}
					int tWarNum = mWarRegInfoManager[i].GetWarNumOfCertainLevel( tpWarRegInfo->mLevelID );
					CLevelSection *tpSection = mLevelConfig.GetLeveSection( tpWarRegInfo->mLevelID );
					if ( tpSection != NULL )
					{
						// ͬʱ������ս�����Ѿ�����
						if ( tpSection->mMaxWarNum <= tWarNum )
						{					
							continue;
						}
					}
					// ������Ϣ��ս���б���
					int tServerListID = mWarRegInfoManager[i].GetServerListID();
					mWarRegInfoManager[i].InsertWarRegInfo2List( tpWarRegInfo );
					mWarRegInfoManager[i].GetWarEnableList().erase( it-- );
					tpWarRegInfo->mStatus = CWarRegInfo::EWARSTATUS_CREATEREPTION;
					tpWarRegInfo->mServerListID = mWarRegInfoManager[i].GetServerListID();
					mWarRegInfoManager[i].SetLastWarStartTime( time(NULL) );					
					CreateReption( tpWarRegInfo, mWarRegInfoManager[i].GetServerListID(), mWarRegInfoManager->GetRepetionIndex() );		
				}		
			}
		}		
	}	
}

// ***************************************************************
// Function:   DeleteOfflineRole
// Description: ɾ������ʱ����������
// Others:         
// Date:         04/11/2011 
//***************************************************************
void CDungeonModule::RemoveTimeOutRole()
{	
	std::vector<int> tRoleIDList;
	for ( int i = 0; i < ARRAY_CNT(mWarRegInfoManager); ++i )
	{
		if ( mWarRegInfoManager[i].GetWarManagerStatus() == CWarRegInfoManager::EMANAGER_STATUS_USED )
		{
			mWarRegInfoManager[i].RemoveTimeOutRole( mDungeonConfig.mMaxOffLineTime, mDungeonConfig.mMaxWaitTime, tRoleIDList );
			mWarRegInfoManager[i].DeleteTimeOutWaitList( mDungeonConfig.mActivityTime, tRoleIDList );
		}		
	}	
	for ( std::vector<int>::iterator it = tRoleIDList.begin(); it != tRoleIDList.end(); ++it )
	{
		DeleteGlobalPlayer( *it );
		LOG_INFO("default", "Globarwar: delete role id: %d because timeout", *it);
	}
}

// ***************************************************************
// Function:   DeleteValidWarRegInfo
// Description: ɾ����Ч��ս����Ϣ
// Others:         
// Date:         04/11/2011 
//***************************************************************
void CDungeonModule::DeleteValidWarRegInfo()
{	
	for ( int i = 0; i < ARRAY_CNT(mWarRegInfoManager); ++i )
	{
		if ( mWarRegInfoManager[i].GetWarManagerStatus() == CWarRegInfoManager::EMANAGER_STATUS_USED )
		{
			std::vector<int> tDeleteWarRegInfoID;
			mWarRegInfoManager[i].DeleteValidWarRegInfo( mDungeonConfig.mMaxWarAliveTime, mDungeonConfig.mWarProctectTime, tDeleteWarRegInfoID );	
			std::vector<int>::iterator it = tDeleteWarRegInfoID.begin();
			for ( ; it != tDeleteWarRegInfoID.end(); ++it )
			{				
				CWarRegInfo *tpWarRegInfo = (CWarRegInfo *)CDunobjManager::GetSingleton().GetObject( *it );
				if ( tpWarRegInfo == NULL )
				{
					continue;
				}
				//mServerManager.ChangeServerSatus( tpWarRegInfo->mServerKey, 0, -1, mGlobalServerConfig, CServerManager::ESELECT_TYPE_BYWARNUM );
				mWarRegInfoManager[i].DeleteWarRegInfo( tpWarRegInfo->mRegKey );		
				CDunobjManager::GetSingleton().DestroyObject( tpWarRegInfo->mRegKey );
				LOG_INFO("default", "GlobarWar:delete WarRegInfo id:%d because timeout", tpWarRegInfo->get_id());
			}			
		}		

		// ����������Ѿ����о����
		if ( mWarRegInfoManager[i].IsManagerFree() == true )
		{
			mWarRegInfoManager[i].Initialize();
		}
	}	
}

// ��ȡȫ�ַ�������������Ϣ
int CDungeonModule::ReadServerConfig( const char *pFile )
{
	LK_ASSERT( pFile != NULL, return -1 )
	TiXmlDocument tDoc;	
	LK_ASSERT( tDoc.LoadFile( pFile ) == true, return -1 )
	TiXmlElement *tpRoot = tDoc.RootElement();
	LK_ASSERT( tpRoot != NULL, return -1 )
	mGlobalServerConfig.InitializeServerList();
	TiXmlElement *tpServerListElement = tpRoot->FirstChildElement( "ServerList" );
	for ( ; tpServerListElement != NULL; tpServerListElement = tpServerListElement->NextSiblingElement() )
	{
		int tListID = 0;
		if ( tpServerListElement->Attribute( "ListID" ) != NULL )
		{
			tListID = atoi( tpServerListElement->Attribute( "ListID" ) );
		}
		if ( tpServerListElement->Attribute( "WarStartNum" ) != NULL )
		{			
			mGlobalServerConfig.SetWarStartNum( tListID, atoi( tpServerListElement->Attribute( "WarStartNum" ) ) );
		}
		
		// ����ս����ս����ʼ�������¸�ֵ
		SetWarStartNum( tListID, mGlobalServerConfig.GetWarStartNum( tListID ) );
		TiXmlElement *tpServerElement = tpServerListElement->FirstChildElement( "server" );
		LK_ASSERT( tpServerElement != NULL, return -1 )				
		
		for ( ; tpServerElement != NULL; tpServerElement = tpServerElement->NextSiblingElement() )
		{
			CGlobalServerInfo tGlobalServerInfo;
			int tKey = 0;
			if ( tpServerElement->Attribute( "ServerKey" ) != NULL )
			{
				tKey = atoi( tpServerElement->Attribute( "ServerKey" ) );
			}

			if ( tpServerElement->Attribute( "ServerType" ) != NULL )
			{
				tGlobalServerInfo.mServerType = atoi( tpServerElement->Attribute( "ServerType" ) );
			}

			if ( tpServerElement->Attribute( "WorldID" ) != NULL )
			{
				tGlobalServerInfo.mWorldID = atoi( tpServerElement->Attribute( "WorldID" ) );
			}

			if ( tpServerElement->Attribute( "LineID" ) != NULL )
			{
				tGlobalServerInfo.mLineID = atoi( tpServerElement->Attribute( "LineID" ) );
			}

			if ( tpServerElement->Attribute( "Addr" ) != NULL )
			{
				tGlobalServerInfo.mAddr = lk::CString64( tpServerElement->Attribute( "Addr" ) );
			}

			if ( tpServerElement->Attribute( "ReptionIndex" ) != NULL )
			{
				tGlobalServerInfo.mReptionIndex = atoi( tpServerElement->Attribute( "ReptionIndex" ) );
			}

			TiXmlElement *tpMapInfo = tpServerElement->FirstChildElement( "GlobalMapInfo" );
			if ( tpMapInfo != NULL )
			{
				if ( tpMapInfo->Attribute( "PosX" ) != NULL )
				{
					tGlobalServerInfo.mGlobalMapInfo.mPosX = atoi( tpMapInfo->Attribute( "PosX" ) );
				}

				if ( tpMapInfo->Attribute( "PosY" ) != NULL )
				{
					tGlobalServerInfo.mGlobalMapInfo.mPosY = atoi( tpMapInfo->Attribute( "PosY" ) );
				}
				if ( tpMapInfo->Attribute( "MapID" ) != NULL )
				{
					tGlobalServerInfo.mGlobalMapInfo.mMapID = atoi( tpMapInfo->Attribute( "MapID" ) );
				}
			}
			else
			{
				LOG_ERROR( "default","read server config error!" );
			}

			tpMapInfo = tpServerElement->FirstChildElement( "OriginalMapInfo" );
			if ( tpMapInfo != NULL )
			{
				if ( tpMapInfo->Attribute( "PosX" ) != NULL )
				{
					tGlobalServerInfo.mOriginalMapInfo.mPosX = atoi( tpMapInfo->Attribute( "PosX" ) );
				}

				if ( tpMapInfo->Attribute( "PosY" ) != NULL )
				{
					tGlobalServerInfo.mOriginalMapInfo.mPosY = atoi( tpMapInfo->Attribute( "PosY" ) );
				}
				if ( tpMapInfo->Attribute( "MapID" ) != NULL )
				{
					tGlobalServerInfo.mOriginalMapInfo.mMapID = atoi( tpMapInfo->Attribute( "MapID" ) );
				}
			}
			else
			{
				LOG_ERROR( "default","read server config error!" );
			}		

			mGlobalServerConfig.InsertGlobalServerInfo( tListID, tKey, tGlobalServerInfo );
		} 	
	}	
}

// ��ȡ�ȼ�����
int CDungeonModule::ReadLevelConfig( const char *pFile )
{
	LK_ASSERT( pFile != NULL, return -1 );
	TiXmlDocument tDoc;
	LK_ASSERT( tDoc.LoadFile( pFile ) == true, return -1 );
	TiXmlElement *tpRoot = tDoc.RootElement();
	LK_ASSERT( tpRoot != NULL, return -1 )
	mLevelConfig.Initialize();
	if ( tpRoot->Attribute( "MaxLevel" ) != NULL )
	{
		mLevelConfig.SetMaxLevel( atoi( tpRoot->Attribute( "MaxLevel" ) ) );
	}
	TiXmlElement *tpLevelSection = tpRoot->FirstChildElement( "LevelSection" );
	LK_ASSERT( tpLevelSection != NULL, return -1 )
	for ( ; tpLevelSection != NULL; tpLevelSection = tpLevelSection->NextSiblingElement() )
	{
		CLevelSection tLevelSection;
		if ( tpLevelSection->Attribute( "MinLevel" ) != NULL )
		{
			tLevelSection.mMinLevel = atoi( tpLevelSection->Attribute( "MinLevel" ) );
		}
		if ( tpLevelSection->Attribute( "LevelID" ) != NULL )
		{
			tLevelSection.mLevelID = atoi( tpLevelSection->Attribute( "LevelID" ) );
		}
		if ( tpLevelSection->Attribute( "MaxWarNum" ) != NULL )
		{
			tLevelSection.mMaxWarNum = atoi( tpLevelSection->Attribute( "MaxWarNum" ) );
		}
		mLevelConfig.InsertLevelSection( tLevelSection );
	}
	return SUCCESS;
}

// ***************************************************************
// Function:   ReadDungeonConfig
// Description: ��һ������
// Others:         
// Date:         04/11/2011 
//***************************************************************
int CDungeonModule::ReadDungeonConfig( const char *pFile )
{
	LK_ASSERT( pFile != NULL, return -1 )
	TiXmlDocument tDoc;
	LK_ASSERT( tDoc.LoadFile( pFile ) == true, return -1 )
	TiXmlElement *tpRoot = tDoc.RootElement();
	LK_ASSERT( tpRoot != NULL, return -1 )
	TiXmlElement *tpMaxWarAliveTime = tpRoot->FirstChildElement( "MaxWarAliveTime" );
	if ( tpMaxWarAliveTime != NULL )
	{
		mDungeonConfig.mMaxWarAliveTime = atoi( tpMaxWarAliveTime->Attribute( "DataValue" ) );
	}
	TiXmlElement *tpWarTimeInterval = tpRoot->FirstChildElement( "WarTimeInterval" );
	if ( tpWarTimeInterval != NULL )
	{
		mDungeonConfig.mWarTimeInterval = atoi( tpWarTimeInterval->Attribute( "DataValue" ) );
	}
	TiXmlElement *tpTimeInterval = tpRoot->FirstChildElement( "TimeInterval" );
	if ( tpTimeInterval != NULL )
	{
		mDungeonConfig.mTimeInterval = atoi( tpTimeInterval->Attribute( "DataValue" ) );  
		mTimer = CWTimer(mDungeonConfig.mTimeInterval);
	}
	TiXmlElement *tpWarProtectTime = tpRoot->FirstChildElement( "WarProtectTime" );
	if ( tpWarProtectTime != NULL )
	{
		mDungeonConfig.mWarProctectTime = atoi( tpWarProtectTime->Attribute( "DataValue" ) );  
	}
	TiXmlElement *tpActivityTime = tpRoot->FirstChildElement( "ActivityTime" );
	if ( tpActivityTime != NULL )
	{
		mDungeonConfig.mActivityTime = atoi( tpActivityTime->Attribute( "DataValue" ) );  
	}	
	TiXmlElement *tpMaxOffLineTime = tpRoot->FirstChildElement( "MaxOffLineTime" );
	if ( tpMaxOffLineTime != NULL )
	{
		mDungeonConfig.mMaxOffLineTime = atoi( tpMaxOffLineTime->Attribute( "DataValue" ) );  
	}
	TiXmlElement *tpMaxWaitTime = tpRoot->FirstChildElement( "MaxWaitTime" );
	if ( tpMaxWaitTime != NULL )
	{
		 mDungeonConfig.mMaxWaitTime = atoi( tpMaxWaitTime->Attribute( "DataValue" ) );  
	}
	return SUCCESS;
}

// ***************************************************************
// Function:   ReadGameConfig
// Description:��ȡ��Ϸ����
// Others:         
// Date:         04/11/2011 
//***************************************************************
int CDungeonModule::ReadGameConfig( const char *pFile )
{
	LK_ASSERT( pFile != NULL, return -1 )		
	TiXmlDocument tDoc;
	LK_ASSERT( tDoc.LoadFile( pFile ) == true, return -1 )
	TiXmlElement *tpRoot = tDoc.RootElement();
	LK_ASSERT( tpRoot != NULL, return -1 )
	mGlobalServerConfig.InitializeGameConfig();
	TiXmlElement *tpGameConfig = tpRoot->FirstChildElement( "Game" );
	for ( ; tpGameConfig != NULL; tpGameConfig = tpGameConfig->NextSiblingElement( ) )
	{
		int tWorldID = 0;
		if ( tpGameConfig->Attribute( "WorldID" ) != NULL )
		{
			tWorldID = atoi( tpGameConfig->Attribute( "WorldID" ) );
		}
		int tServerListID = 0;
		if ( tpGameConfig->Attribute( "ServerListID" ) != NULL )
		{
			tServerListID = atoi( tpGameConfig->Attribute( "ServerListID" ) );
		}
		CGameConfig tGameConfig;
		tGameConfig.mServerListID = tServerListID;
		mGlobalServerConfig.InsertGameConfig( tWorldID, tGameConfig );
	}
	return SUCCESS;
}

// ***************************************************************
// Function:   CreateWarManager
// Description:����һ������������
// Others:         
// Date:         04/11/2011 
//***************************************************************
CWarRegInfoManager *CDungeonModule::CreateWarManager( int nServerListID, int nRepetionIndex )
{
	for ( int i = 0; i < ARRAY_CNT(mWarRegInfoManager); ++i )
	{
		if ( mWarRegInfoManager[i].GetWarManagerStatus() == CWarRegInfoManager::EMANAGER_STATUS_UNUSED )
		{	
			mWarRegInfoManager[i].SetServerListID( nServerListID );
			mWarRegInfoManager[i].SetRepetionIndex( nRepetionIndex );
			mWarRegInfoManager[i].SetWarManagerStatus( CWarRegInfoManager::EMANAGER_STATUS_USED );
			mWarRegInfoManager[i].SetWarStartNum( mGlobalServerConfig.GetWarStartNum( nServerListID ) );
			return &mWarRegInfoManager[i];
		}
	}
	return NULL;
}

// ***************************************************************
// Function:   GetWarManager
// Description: ��ȡһ����������������Ϣ
// Others:         
// Date:         04/11/2011 
//***************************************************************
CWarRegInfoManager *CDungeonModule::GetWarManager( int nServerListID, int nRepetionIndex )
{
	for ( int i = 0; i < ARRAY_CNT(mWarRegInfoManager); ++i )
	{
		if ( mWarRegInfoManager[i].GetServerListID() == nServerListID &&
			 mWarRegInfoManager[i].GetRepetionIndex() == nRepetionIndex &&
			 mWarRegInfoManager[i].GetWarManagerStatus() == CWarRegInfoManager::EMANAGER_STATUS_USED )
		{	
			return &mWarRegInfoManager[i];
		}
	}
	return NULL;
}

// ***************************************************************
// Function:   GetWarManager
// Description: ��ȡһ������������
// Others:         
// Date:         05/09/2011 
//***************************************************************
CWarRegInfoManager *CDungeonModule::GetWarManagerByWorldID( int nWorldID, int nRepetionIndex )
{
	CGameConfig *tpConfig = mGlobalServerConfig.GetGameConfig( nWorldID );
	if ( tpConfig == NULL )
	{
		return NULL;
	}		
	return GetWarManager( tpConfig->mServerListID, nRepetionIndex );
}


// ***************************************************************
// Function:   DeleteWarManager
// Description: ɾ������������
// Others:         
// Date:         04/11/2011 
//***************************************************************
int CDungeonModule::DeleteWarManager( int nServerListID, int nRepetionIndex )
{
	for ( int i = 0; i < ARRAY_CNT(mWarRegInfoManager); ++i )
	{
		if ( mWarRegInfoManager[i].GetServerListID() == nServerListID &&
			 mWarRegInfoManager[i].GetRepetionIndex() == nRepetionIndex )
		{	
			mWarRegInfoManager[i].Initialize();
			return SUCCESS;
		}
	}
	return SUCCESS;
}

// ***************************************************************
// Function:   DeleteWarRegInfo
// Description: ɾ��ս����Ϣ
// Others:         
// Date:         04/11/2011 
//***************************************************************
void CDungeonModule::DeleteWarRegInfo( CWarRegInfo *pWarRegInfo )
{
	if ( pWarRegInfo == NULL )
	{
		return;
	}
	for ( int i = 0; i < ARRAY_CNT(mWarRegInfoManager); ++i )
	{
		if ( mWarRegInfoManager[i].GetWarManagerStatus() == CWarRegInfoManager::EMANAGER_STATUS_USED )
		{	
			mWarRegInfoManager[i].DeleteWarRegInfo( pWarRegInfo->mRegKey );						
		}
	}
	CDunobjManager::GetSingleton().DestroyObject( pWarRegInfo->get_id() );	
}

// ***************************************************************
// Function:   SetWarStartNum
// Description: ����ս����������
// Others:         
// Date:         04/11/2011 
//***************************************************************
void CDungeonModule::SetWarStartNum( int nServerListID, int nWarStartNum )
{
	for ( int i = 0; i < ARRAY_CNT(mWarRegInfoManager); ++i )
	{
		if ( mWarRegInfoManager[i].GetWarManagerStatus() == CWarRegInfoManager::EMANAGER_STATUS_USED )
		{	
			if ( mWarRegInfoManager[i].GetServerListID() == nServerListID )
			{
				mWarRegInfoManager[i].SetWarStartNum( nWarStartNum );
			}								
		}
	}
}


// ***************************************************************
// Function:   InsertGlobalPlayer
// Description:����һ����ɫ��Ϣ
// Others:         
// Date:         04/11/2011 
//***************************************************************
int CDungeonModule::InsertGlobalPlayer( int nCharID, CGlobalPlayer &rPlayer )
{
	if ( mGlobalPlayerList.size() == mGlobalPlayerList.max_size() )
	{
		return -1;
	}
	mGlobalPlayerList.insert( GlobalPlayerList::value_type( nCharID, rPlayer ) );
	return SUCCESS;
}

// ***************************************************************
// Function:   GetGlobalPlayer
// Description:��ȡ��ɫ��Ϣ
// Others:         
// Date:         04/11/2011 
//***************************************************************
CGlobalPlayer *CDungeonModule::GetGlobalPlayer( int nCharID )
{	
	GlobalPlayerList::iterator it = mGlobalPlayerList.find( nCharID );
	if ( it != mGlobalPlayerList.end() )
	{
		return &it->second;
	}
	return NULL;
}
// ***************************************************************
// Function:   DeleteGlobalPlayer
// Description:ɾ��ĳ����ɫ��Ϣ
// Others:         
// Date:         04/11/2011 
//***************************************************************
int CDungeonModule::DeleteGlobalPlayer( int nCharID )
{
	GlobalPlayerList::iterator it = mGlobalPlayerList.find( nCharID );
	if ( it != mGlobalPlayerList.end() )
	{
		mGlobalPlayerList.erase( it );
	}
	return SUCCESS;
}

// ***************************************************************
// Function:   RegPlayerToServer
// Description:��ȫ�ַ��������������Ϣ
// Others:         
// Date:         04/11/2011 
//***************************************************************
CGlobalPlayer* CDungeonModule::RegPlayerToServer( int nRoleID, int nWorldID, int nRepetionIndex /* = 0 */ )
{
	CGameConfig *tpConfig = mGlobalServerConfig.GetGameConfig( nWorldID );
	if ( tpConfig == NULL )
	{
		return NULL;
	}
	CGlobalPlayer tGlobalPlayer;
	tGlobalPlayer.mWorldID = nWorldID;
	tGlobalPlayer.mRepetionIndex = nRepetionIndex;
	int tRet = InsertGlobalPlayer( nRoleID, tGlobalPlayer );
	if ( tRet < 0 )
	{
		return NULL;
	}

	// ���������������0������Ҫ��������������
	if ( nRepetionIndex > 0 )
	{
		if ( GetWarManager( tpConfig->mServerListID, nRepetionIndex ) == NULL )
		{
			CreateWarManager( tpConfig->mServerListID, nRepetionIndex );
		}
	}
	return GetGlobalPlayer( nRoleID );
}

// ***************************************************************
// Function:   OnEventTeleToGlobalSceneServer
// Description:���͵�ȫ�ַ�����
// Others:         
// Date:         04/11/2011 
//***************************************************************
void CDungeonModule::OnEventTeleToGlobalSceneServer()
{

}

// ***************************************************************
// Function:   OnEventReturnToOriginalScene
// Description:���ص�ԭʼ������
// Others:         
// Date:         04/11/2011 
//***************************************************************
void CDungeonModule::OnEventReturnToOriginalScene()
{

}

// ***************************************************************
// Function:   OnEventCreateRepetion
// Description:��������
// Others:         
// Date:         04/11/2011 
//***************************************************************
void CDungeonModule::OnEventCreateRepetion()
{
		
}

// ***************************************************************
// Function:   OnEventDestroyRepetion
// Description:���ٸ���
// Others:         
// Date:         04/11/2011 
//***************************************************************
void CDungeonModule::OnEventDestroyRepetion()
{

}

// ͬ�����ƶ����
// ***************************************************************
// Function:   OnMessageSyncGlobalPlayer
// Description:ͬ�����ƶ����
// Others:         
// Date:         09/15/2011 
//***************************************************************
void CDungeonModule::OnMessageSyncGlobalPlayer( CMessage *pMsg, int nGameID, int nSrcFe, int nSrcID )
{
	LK_ASSERT( pMsg != NULL, return )
	CMessageSyncGlobalPlayeNotify *tpMsg = ( CMessageSyncGlobalPlayeNotify * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	for ( int i = 0; i < tpMsg->worldplayerlist_size(); ++i )
	{ 
		PBWorldPlayer *tpWorldPlayer = tpMsg->mutable_worldplayerlist( i );
		if ( tpWorldPlayer != NULL )
		{
			for ( int j = 0; j < tpWorldPlayer->roleid_size(); ++j )
			{
				CGlobalPlayer *tpPlayer = GetGlobalPlayer( tpWorldPlayer->roleid( j ) );
				if ( tpPlayer == NULL )
				{
					// �����Ϣ�Ѿ����������ߵ������
					CMessage tMsgHead;
					CMessageKickGlobalPlayerNotify tMsgKickPlayer;
					tMsgHead.mutable_msghead()->set_messageid( ID_S2S_NOTIFY_KICKGLOBALPLAYER );
					tMsgHead.set_msgpara( (int)&tMsgKickPlayer );
					tMsgKickPlayer.set_roleid( tpWorldPlayer->roleid( j ) );
					CDungeonLogic::GetSingleton().Send2Gate( &tMsgHead, nGameID );
				}
			}
		}
	}
}