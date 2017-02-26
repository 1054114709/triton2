#include "servertool.h"	 
#include "message_pb.hxx.pb.h"
#include "entity.h"	     
#include "modulemanager.h"
#include "marriagemodule.h"
#include "teammodule.h"
#include "marriagemessage_pb.hxx.pb.h"
#include "template.h"
#include "property.h"
#include "proclient_svr.h"
#include "marriagemanager.h"
#include "scenelogic.h"
#include "marriagetype.h"
#include "propertymodule.h"
#include "errcode.h"
#include "mapobjmanager.h"
#include "entity_searcher.h"
#include "entity_searcher_imp.h"
#include "scenecfg_manager.h"
#include "npcmodule.h"
#include "mailmodule.h"
#include "activitymodule.h"
#include "friendmodule.h"

char CMarriageModule::sModuleName[NAME_LENGTH] = { 0 };
template<> CMarriageModule * CSingleton< CMarriageModule >::spSingleton = NULL;
CMarriageManager *gpMarriageManager = NULL;
// ***********************************************************
//  Function:		CountSize
//  Description:	������ģ��Ĵ�С 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************	 
unsigned int CMarriageModule::CountSize()
{
	unsigned int tSize = sizeof( CMarriageManager );	
	tSize += sizeof( CMarriageModule );
	return tSize;
}

// ***********************************************************
//  Function:		OnLaunchServer
//  Description:	���������� 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
void CMarriageModule::OnLaunchServer( )
{
	 CMarriageManager::mShmPtr = mShmPtr;
	 gpMarriageManager = new CMarriageManager;
	 if ( gpMarriageManager == NULL )
	 {
		 LOG_ERROR( "marriage", "[ %s : %d ][ %s ]Launch Error", __LK_FILE__, __LINE__, __FUNCTION__ );
		 printf( "Create MarriageManager Faild, So Exit\n");
		 exit(1);
	 }
	 
	OnLoadConfig();	
}


// ***********************************************************
//  Function:		OnExitServer
//  Description:	�˳������� 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
void CMarriageModule::OnExitServer( )
{
	
}

// ***********************************************************
//  Function:		OnTimer
//  Description:	������Timer 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
void CMarriageModule::OnTimer( unsigned int vTickCount, unsigned int vTickOffsekt )
{
	if ( mWeddingNpcTimer.Elapse( vTickOffsekt ) == true )
	{
		CheckWeddingNpc();		
	}
	
	if ( mMarriageStatusTimer.Elapse( vTickOffsekt ) == true )
	{
		CheckWeddingStatus();		
	}
	
	if ( mBaitangTimer.Elapse( vTickOffsekt ) == true )
	{    
		bool tChangeTimer = CheckNewlyBaitangStatus();
		if ( tChangeTimer == true )
		{
			mBaitangTimer = CWTimer( BAITANGSTATUS_TIMER_LENGTH );
		}
		else
		{
			mBaitangTimer = CWTimer( MARRIAGESTATUS_TIMER_LENGTH );
		}		
	}
}

// ***********************************************************
//  Function:		OnCreateMap
//  Description:	�������� 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
int CMarriageModule::OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName )
{
	  return SUCCESS;
}

// ***********************************************************
//  Function:		OnRouterMessage
//  Description:	·����Ϣ 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
void CMarriageModule::OnRouterMessage( CMessage* pMessage )
{  
	LK_ASSERT( pMessage != NULL, return )		
	switch( pMessage->mutable_msghead()->messageid() )
	{
		case ID_S2C_NOTIFY_SPOUSEDIVORCE:
		{
			OnRoterMessageSpouseDivorce( pMessage );
			break;
		}		  
	}
}

// ***********************************************************
//  Function:		OnClientMessage
//  Description:	�ͻ��˷�����Ϣ 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
void CMarriageModule::OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	if ( pPlayer == NULL || pMessage == NULL )
	{
		return;
	}
	
	switch ( pMessage->mutable_msghead()->messageid() )
	{
		case ID_C2S_REQUEST_APPLYMARRY:
		{
			OnMessageApplyMarryRequest( pPlayer, pMessage );
			break;
		}		
		
		case ID_C2S_REQUEST_REPLYMARRY:
		{
			OnMessageReplyMarryRequest( pPlayer, pMessage );
			break;
		}		
		
		case ID_C2S_REQUEST_BEGINWEDDING:
		{
			OnMessageBegginWeddingRequest( pPlayer, pMessage );
			break;
		}		

		case ID_C2S_REQUEST_REPLYBEGINWEDDING:
		{
			OnMessageReplyBeginWeddingRequest( pPlayer, pMessage );
			break;
		}

		case ID_C2S_REQUEST_REPLYENTERMARRIAGEHALL:
		{
			OnMessageReplyEnterMarriageHallRequest( pPlayer, pMessage );
			break;
		}	

		case ID_C2S_REQUEST_NEWLYWEDENTERHALL:
		{
			OnMessageNewlywedEnterHallRequest( pPlayer, pMessage );
			break;
		}		

		case ID_C2S_REQUEST_GUESTENTERHALL:
		{
			OnMessageGuestEnterHallRequest( pPlayer, pMessage );
			break;
		}		

		case ID_C2S_REQUEST_BAITANG:
		{
			OnMessageBaiTangRequest( pPlayer, pMessage );
			break;
		}		

		case ID_C2S_REQUEST_PUTKEEPSAKE:
		{
			OnMessagePutKeepsakeRequest( pPlayer, pMessage );
			break;
		}		  		

		case ID_C2S_REQUEST_EXCHANGKEEPSAKE:
		{
			OnMessageExchangeKeepsakeRequest( pPlayer, pMessage );
			break;
		}		  	

		case ID_C2S_REQUEST_DIVORCE:
		{
			OnMessageDivorceRequest( pPlayer, pMessage );
			break;
		}	
		
		case ID_C2S_REQUEST_GETCAMPMARRAIGEINFO:
		{
			OnMessageGetCampMarriageInfoRequest( pPlayer, pMessage );
			break;
		}		
		
		case ID_C2S_REQUEST_USESYSINVITATION:
		{
			OnMessageUseSysInvitation( pPlayer, pMessage );
			break;
		}
		
		case ID_C2S_REQUEST_STARTKEEPSAKEEXCHANGE:
		{
			OnMessageStartKeepsakeExchangeRequest( pPlayer, pMessage );
			break;
		}
		
		case ID_C2S_REQUEST_STOPKEEPSAKEEXCHANGE:
		{
			OnMessageStopKeepsakeRequest( pPlayer, pMessage );
			break; 
		}
		
		case ID_C2S_REQUEST_INVITATIONEXCHANGE:
		{
			OnMessageInvitationExchange( pPlayer, pMessage );
			break;
		}
		
		case ID_C2S_REQUEST_TELETOWEDDINGNPC:
		{
			OnMessageTeletoMarriageNpcRequest( pPlayer, pMessage );
			break;
		}
		
		case ID_C2S_REQUEST_REVIEWWEDDING:
		{
			OnMessageReviewWeddingRequest( pPlayer, pMessage );
			break;
		}
	}  			
}

// ***********************************************************
//  Function:		OnCreateEntity
//  Description:	����ʵ�� 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
void CMarriageModule::OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst )
{
	LK_ASSERT( pEntity != NULL, return )
		
	if ( pEntity->IsPlayer() )
	{			
		CEntityPlayer *tpPlayer = ( CEntityPlayer * )pEntity;
		if ( tpPlayer->GetNationality() == CSceneLogic::GetSingleton().GetLineID() )
		{
			// ����Ӫ��ҵ�¼�����ȼ���Ƿ��Ѿ���ǿ�����
			if ( tpPlayer->GetMarriageID() != 0 )
			{
				CMarriageInfo *tpMarriage = CMarriageManager::GetSingleton().GetMarriageInfo( tpPlayer->GetMarriageID() );
				if ( tpMarriage == NULL )
				{
					LOG_INFO( "marriage","[%d] player ( roleid:%d ) divorced, change marriageid:%d to 0 ", __LINE__, tpPlayer->GetCharID(),
						tpPlayer->GetMarriageID() );
					
					// �Ѿ����
					tpPlayer->SetMarriageID( 0 );
					
					// ȥ�����ƺ�
					CTemplateMarriageConfig *tpConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
					if( tpConfig != NULL )
					{
						CPropertyModule::GetSingleton().OnPlayerDelTitleEvent( tpPlayer, tpConfig->mMarriageTitleID );
					}
				}
				else
				{
					SendPersonMarriageInfoNotify( tpPlayer, tpMarriage );
					
					if ( tpMarriage->GetMarriageStatus() == MARRIAGESTATUS_WEDDINGINWAIT )
					{
						if ( tpMarriage->GetWeddingStatus() == WEDDINGSTATUS_TIMENEAR || tpMarriage->GetWeddingStatus() == WEDDINGSTATUS_INTIME )
						{
							SendMarriageTipsNotify( tpMarriage, tpPlayer );
						}			
					}  		
				}
			}			
		}
		else
		{
			// ������Ӫ��ҵ�¼������ݿ���ػ�����Ϣ						
			if ( tpPlayer->GetMarriageID() != 0 )
			{	
				CMarriageInfo *tpMarriage = CMarriageManager::GetSingleton().GetMarriageInfoOfOtherCamp( tpPlayer->GetMarriageID() );
				if ( tpMarriage == NULL )
				{
					LoadPlayerMarriageInfo( tpPlayer );	
				}
				else
				{
					SendPersonMarriageInfoNotify( tpPlayer, tpMarriage );
				}				
			}
		}			
	}
}

// ***********************************************************
//  Function:		OnDestroyEntity
//  Description:	����ʵ�� 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
void CMarriageModule::OnDestroyEntity( CEntity* pEntity, int vCode )
{	
	LK_ASSERT( pEntity != NULL, return )	
	if ( pEntity->IsPlayer() )
	{	 
		CEntityPlayer *tpPlayer = ( CEntityPlayer * )pEntity; 	
		if ( tpPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
		{				
			CMarriageInfo *tpMarriage = CMarriageManager::GetSingleton().GetMarriageInfoOfOtherCamp( tpPlayer->GetMarriageID() );
			if ( tpMarriage != NULL )
			{
				int tSpouseID = 0;
				if ( tpMarriage->GetBrideID() == tpPlayer->GetCharID() )
				{
					tSpouseID = tpMarriage->GetGroomID();
				}
				else
				{
					tSpouseID = tpMarriage->GetBrideID();
				}
				
				CEntityPlayer *tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tSpouseID );
				if ( tpSpouse == NULL )
				{
					CMarriageManager::GetSingleton().DeleteOtherCampMarriageInfo( tpPlayer->GetMarriageID() );
				}			
			}			
		}	
		else
		{
			CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( tpPlayer->GetCharID() );
		}
	}	
}

// ***********************************************************
//  Function:		OnSaveData
//  Description:	�洢���� 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
bool CMarriageModule::OnSaveData( CEntityPlayer* pPlayer, int vSaveCode )
{
	//if ( vSaveCode == CEntityPlayer::STATE_LEAVEGAME || vSaveCode == CEntityPlayer::STATE_FORCEEXIT || vSaveCode == CEntityPlayer::STATE_KICKOUT
	//	|| vSaveCode == CEntityPlayer::STATE_REDIRECT || vSaveCode == CEntityPlayer::STATE_RETURNTOGATE || vSaveCode == CEntityPlayer::STATE_INWAIT
	//	|| vSaveCode == CEntityPlayer::STATE_REDIRECT_INWAIT )
	//{
	//	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	//	if ( tpMarriageConfig != NULL )
	//	{
	//		for ( unsigned int i = 0; i < ARRAY_CNT( tpMarriageConfig->mWeddinInfo ); ++i )
	//		{
	//			if ( pPlayer->GetMapID() == tpMarriageConfig->mWeddinInfo[i].mWeddingHallMapID )
	//			{
	//				pPlayer->SetMapID( tpMarriageConfig->mMapID );
	//				pPlayer->SetPosX( tpMarriageConfig->mPosX );
	//				pPlayer->SetPosY( tpMarriageConfig->mPosY );
	//				break;
	//			}
	//		}
	//	}
	//}
	return true;
}

// ***********************************************************
//  Function:		OnLoadConfig
//  Description:	�������� 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
void CMarriageModule::OnLoadConfig( )
{
	InitializeSysWeddingInfo( "../config/data/marriage/WeddingTime.xml" );
	InitializeWeddingNpcPath( "../config/data/marriage/WeddingPath.xml" );	
	
	MARRIAGE_LOG *tpCfg = CSceneCfgManager::GetSingleton().GetMarriage_log();
	if ( tpCfg != NULL )
	{
		INIT_ROLLINGFILE_LOG( tpCfg->mIdentifier, tpCfg->mDirectory, ( LogLevel )tpCfg->mPriority, tpCfg->mMaxfilesize, tpCfg->mMaxbackupindex );
	}
}

// ***********************************************************
//  Function:		OnTimeoutMessage
//  Description:	��ʱ��Ϣ 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
void CMarriageModule::OnTimeoutMessage( CMessage* pMessage )
{	
	LK_ASSERT( pMessage != NULL, return )	
	CTimerItem* pTimerItem = (CTimerItem*) pMessage->msgpara();
	LK_ASSERT( pMessage != NULL, return );
		
	switch( pTimerItem->mTimerMark ) 	
	{ 		
		case TIMER_WEDDING:
		{
			OnTimeOutWeddingEnd( pTimerItem );
		}
		break;			
		
		case TIMER_WEDDINGNOTIFY:
		{
		   OnTimeWeddingNotify( pTimerItem );
		}
		break;
		
		case TIMER_MARRIAGEAPPLY:
		{
			OnTimeOutMarryApplyTimeOut( pTimerItem );
		}
		break;
		
		case TIMER_WEDDINGONSTREET:
		{
		   OnTimeOutWeddingOnStreet( pTimerItem );
		}
		break;
	default:
		break;
	}
}

// ***********************************************************
//  Function:		Initialize
//  Description:	��ʼ�� 				
//  Output:			
//  Date:	02/23/2010
// **********************************************************
int CMarriageModule::Initialize()
{
	mMarriageComplete = false;
	mCampInfoComplete = false;
	mWeddingNpcTimer = CWTimer( WEDDINGNPC_TIMER_LENGTH );
	mMarriageStatusTimer = CWTimer( MARRIAGESTATUS_TIMER_LENGTH );
	mBaitangTimer = CWTimer( MARRIAGESTATUS_TIMER_LENGTH );
	return SUCCESS;
}

// ***********************************************************
//  Function:		OnMessageApplyMarryRequest
//  Description:	���������Ϣ���� 				
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessageApplyMarryRequest( CEntityPlayer *pPlayer, CMessage* pMessage )
{ 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )		
	CMessageApplyMarryRequest *tpMsg = ( CMessageApplyMarryRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )		
	
	// ���ڱ���Ӫ���ܽ���
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID( ) )
	{
		return;
	}		
	
	// npc�����ж�
	
	// �Ƿ���л���
	if ( tpMsg->holdwedding() == 0 )
	{
		PlayerMarryApply( pPlayer, 0, 0, tpMsg->weddingmodule() );
		return;
	}
	
	// �����ģ�Ƿ�Ϸ�
	if ( tpMsg->weddingmodule() < 0 || tpMsg->weddingmodule() >= MAX_WEDDING_MODULENUM )
	{
		return;
	}
	
	// ����ʱ��
	int tTimeNow = time( NULL );	
	CWeddingSysTime *tpSysTime = CMarriageManager::GetSingleton().GetWeddingTimeInfo( tpMsg->timeid() );
	if ( tpSysTime == NULL )
	{
		LOG_ERROR( "marriage","[%s,%d] wrong timeid:%d, roleid:%d  ",__FUNCTION__,__LINE__ , tpMsg->timeid(), pPlayer->GetCharID() );
		return;
	}
	
	tm *tpLocalTime = NULL;
	if ( tpMsg->dayid() == 0 )
	{
		tpLocalTime = localtime( (time_t*)&tTimeNow );
	}
	else if ( tpMsg->dayid() == 1 )
	{
		tTimeNow +=	DAYSECOUNDS;
		tpLocalTime = localtime( (time_t*)&tTimeNow );		
	}
	else if ( tpMsg->dayid() == 2 )
	{
		tTimeNow +=	DAYSECOUNDS*2;
		tpLocalTime = localtime( (time_t*)&tTimeNow );		
	}
	else
	{
		LOG_ERROR( "marriage","[%s,%d] wrong dayid:%d, roleid:%d", __FUNCTION__, __LINE__, tpMsg->dayid(), pPlayer->GetCharID() );
		return;
	}	
	
	if ( tpMsg->weddingmodule() == 0 && tpSysTime->mCommonAllowed == 1 )
	{
		// LOG_ERROR( "marriage","[%s,%d] wedding module wrong , roleid:%d", __FUNCTION__, __LINE__, pPlayer->GetCharID() );		
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRYAPPLY_WRONGMODULE );
		return;
	}
	
	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	if ( tpMarriageConfig == NULL )
	{
		LOG_ERROR( "marriage","wrong marriage config template" );
		return;
	}	
	
	
	tpLocalTime->tm_hour = tpSysTime->mBeginTime;
	tpLocalTime->tm_min = 0;
	tpLocalTime->tm_sec = 0;
	int tWeddingTime = mktime( tpLocalTime );		
	int tTimeLength = tpMarriageConfig->mWeddinInfo[tpMsg->weddingmodule()].mWeddingLength*60; 	
		
	PlayerMarryApply( pPlayer, tWeddingTime, tTimeLength, tpMsg->weddingmodule() );
}

// ***********************************************************
//  Function:		SendResponseApplyMarryResponse
//  Description:	���������Ϣ��Ӧ 				
//  Output:			
//  Date:	02/25/2010
// ********************************************************** 
void CMarriageModule::SendApplyMarryResponse( CEntityPlayer *pPlayer, int nErrcode )
{
	CMessage tMsgHead;
	CMessageApplyMarryResponse tMsgApplyMarry;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_APPLYMARRY );	
	tMsgHead.set_msgpara( (int)&tMsgApplyMarry );
	tMsgApplyMarry.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendMarryRequestNotify
//  Description:	���������Ϣ֪ͨ 				
//  Output:			
//  Date:	02/25/2010
// ********************************************************** 
void CMarriageModule::SendMarryRequestNotify( CEntityPlayer *pPlayer, const char *pName, int nRoleID, int nWeddingTime, int nWeddingModule )
{
	CMessage tMsgHead;
	CMessageMarryRequestNotify tMsgMarryRequest;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_MARRYREQUEST );
	tMsgHead.set_msgpara( (int)&tMsgMarryRequest );
	

	
	tMsgMarryRequest.set_roleid( nRoleID );
	if ( pName != NULL )
	{
		tMsgMarryRequest.set_rolename( pName );
	}	
	
	if( nWeddingTime > 0 )
	{
		tm *tpLocalTime = localtime( ( time_t * )&nWeddingTime );
		tMsgMarryRequest.set_weddingmodule( nWeddingModule );
		tMsgMarryRequest.set_year( tpLocalTime->tm_year + 1900 );
		tMsgMarryRequest.set_month( tpLocalTime->tm_mon + 1 );
		tMsgMarryRequest.set_day( tpLocalTime->tm_mday );
		tMsgMarryRequest.set_begintime( tpLocalTime->tm_hour );
	}
	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		OnMessageReplyMarryRequest
//  Description:	�𸴽�����Ϣ���� 				
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessageReplyMarryRequest( CEntityPlayer *pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageReplyMarryRequest *tpMsg = ( CMessageReplyMarryRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// �жϹ�����npc
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}
	
	// �ж�npc����		
	
	PlayerReplyMarry( pPlayer, tpMsg->result() );
}

// ***********************************************************
//  Function:		SendReplyMarryResponse
//  Description:	�𸴽�����Ϣ��Ӧ 				
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendReplyMarryResponse( CEntityPlayer *pPlayer, int nErrcode, const char *pSpouseName /* = NULL */, int nResult /* = 0 */, int nMarriageStatus /* = 0 */ )
{  
	LK_ASSERT( pPlayer != NULL, return )	
	CMessage tMsgHead;
	CMessageReplyMarryResponse tMsgReplyMarry;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_REPLYMARRY );
	tMsgHead.set_msgpara( (int)&tMsgReplyMarry );
	
	tMsgReplyMarry.set_errcode( nErrcode );
	if ( pSpouseName != NULL )
	{
		tMsgReplyMarry.set_spousename( pSpouseName );
	}
	tMsgReplyMarry.set_result( nResult );
	tMsgReplyMarry.set_marriagestatus( nMarriageStatus );	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendPersonalMarriedNotify
//  Description:	��ҽ��ɹ�����Ϣ 				
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendPersonalMarriedNotify( const char *pGroomName, const char *pBrideName, int nServerSequence )
{
	CMessage tMsgHead;
	CMessagePersonMarriedNotify tMsgPersonMarriedNotify;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_PERSONMARRIED );
	tMsgHead.set_msgpara( (int)&tMsgPersonMarriedNotify );
	
	if ( pGroomName != NULL )
	{						
		tMsgPersonMarriedNotify.set_groomname( pGroomName );
	}
	
	if ( pBrideName != NULL )
	{
		tMsgPersonMarriedNotify.set_bridename( pBrideName );
	}
	
	tMsgPersonMarriedNotify.set_serversequence( nServerSequence );
	
	CSceneLogic::GetSingleton().SendWorldMessage( &tMsgHead );
}

// ***********************************************************
//  Function:		SendMarriageTipsNotify
//  Description:	�������� 				
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendMarriageTipsNotify( CMarriageInfo *pMarriageInfo, CEntityPlayer *pPlayer /* = NULL */ )
{	
	LK_ASSERT( pMarriageInfo != NULL, return )		
		
	CMessage tMsgHead;
	CMessageMarriageTipsNotify tMarriageTips;	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_MARRIAGETIPS );
	tMsgHead.set_msgpara( (int)&tMarriageTips );
	
	tMarriageTips.set_weddingtime( pMarriageInfo->GetWeddingTime() );
	tMarriageTips.set_weddingstatus( pMarriageInfo->GetWeddingStatus() );
	
	if ( pPlayer != NULL )
	{
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
		return;
	}
	
	CEntityPlayer *tpGroom = CSceneLogic::GetSingleton().GetPlayerByCharID( pMarriageInfo->GetGroomID() );
	CEntityPlayer *tpBride = CSceneLogic::GetSingleton().GetPlayerByCharID( pMarriageInfo->GetBrideID() );
	if ( tpGroom != NULL )
	{
		CSceneLogic::GetSingleton().Send2Player( tpGroom, &tMsgHead );
	}
	
	if ( tpBride != NULL )						 
	{
		CSceneLogic::GetSingleton().Send2Player( tpBride, &tMsgHead );
	}
}

// ***********************************************************
//  Function:		OnMessageBegginWeddingRequest
//  Description:	��ʼ�������Ϣ���� 				
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessageBegginWeddingRequest( CEntityPlayer *pPlayer, CMessage* pMessage )
{  
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageBeginWeddingRequest *tpMsg = ( CMessageBeginWeddingRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return ) 
	
	// �����ж�
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}
	
	// npc�ж�
	
	PlayerBeginWedding( pPlayer );
}

// ***********************************************************
//  Function:		SendBeginWeddingResponse
//  Description:	��ʼ�������Ϣ��Ӧ 				
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendBeginWeddingResponse( CEntityPlayer *pPlayer, int nErrcode )
{	
	LK_ASSERT( pPlayer != NULL, return )
	
	CMessage tMsgHead;
	CMessageBeginWeddingResponse tMsgBeginWedding;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_BEGINWEDDING );		
	tMsgHead.set_msgpara( (int)&tMsgBeginWedding );
	
	tMsgBeginWedding.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendMarriageNoticeNotify
//  Description:	��ʼ��������һ������ʼ�����֪ͨ 				
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendMarriageNoticeNotify( CEntityPlayer *pPlayer )
{  
	LK_ASSERT( pPlayer != NULL, return )	
	CMessage tMsgHead;
	CMessageBeginWeddingNotify tMsgMarriageNotice;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_BEGINWEDDING );
	tMsgHead.set_msgpara( (int)&tMsgMarriageNotice );
	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		OnMessageReplyBeginWeddingRequest
//  Description:	����ż��ʼ�������Ϣ���� 				
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessageReplyBeginWeddingRequest( CEntityPlayer *pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageReplyBeginWeddingRequest *tpMsg = ( CMessageReplyBeginWeddingRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// �жϹ���
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}
	
	PlayerReplyWeddingBegin( pPlayer, tpMsg->result() );		
}

// ***********************************************************
//  Function:		SenndReplyBeginWeddingResponse
//  Description:	����ż��ʼ�������Ϣ��Ӧ 				
//  Output:			
//  Date:	02/25/2010
// **********************************************************	
void CMarriageModule::SenndReplyBeginWeddingResponse( CEntityPlayer *pPlayer, int nErrcode )
{  
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageReplyBeginWeddingResponse tMsgReplyBeginWedding;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_REPLYBEGINWEDDING );	
	tMsgHead.set_msgpara( (int)&tMsgReplyBeginWedding );
	
	tMsgReplyBeginWedding.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendWeddingNotify
//  Description:	 ����ʼ��֪ͨ(ȫ��֪ͨ) 				
//  Output:			
//  Date:	02/25/2010
// **********************************************************	
void CMarriageModule::SendWeddingNotify( CMarriageInfo *pMarriageInfo )
{ 
	LK_ASSERT( pMarriageInfo != NULL, return )
	CMessage tMsgHead;
	CMessageWeddingStartNotify tMsgWeddingStart;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_WEDDINGSTART );
	tMsgHead.set_msgpara( (int)&tMsgWeddingStart );
	
	tMsgWeddingStart.set_groomname( pMarriageInfo->GetGroomName() );
	tMsgWeddingStart.set_bridename( pMarriageInfo->GetBrideName() );
		
	tMsgWeddingStart.set_weddingtimelength( pMarriageInfo->GetWeddingTimeLength() );
	tMsgWeddingStart.set_weddingmodule( pMarriageInfo->GetWeddingModule() );
	tMsgWeddingStart.set_brideid( pMarriageInfo->GetBrideID() );
	tMsgWeddingStart.set_groomid( pMarriageInfo->GetGroomID() );
	tMsgWeddingStart.set_campid( CSceneLogic::GetSingleton().GetLineID() );
	
	if ( pMarriageInfo->GetWeddingModule() == 2 )
	{
		CSceneLogic::GetSingleton().SendWorldMessage( &tMsgHead );	
	}
	else
	{
		CSceneLogic::GetSingleton().SendCountryMessage( &tMsgHead, CSceneLogic::GetSingleton().GetLineID() );
	}
}

// ***********************************************************
//  Function:		SendEnterMarriageHallNotify
//  Description:	�������õ�֪ͨ		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendEnterMarriageHallNotify( CEntityPlayer *pPlayer )
{
	LK_ASSERT( pPlayer != NULL, return )
	
	CMessage tMsgHead;
	CMessageEnterMarriageHallNotify tMsgEnterMarriageHall;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_ENTERMARRIAGEHALL );	
	tMsgHead.set_msgpara( (int)&tMsgEnterMarriageHall );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		OnMessageReplyEnterMarriageHallRequest
//  Description:	�Ƿ�ͬ��������õĴ�����		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessageReplyEnterMarriageHallRequest( CEntityPlayer *pPlayer, CMessage* pMessage )
{ 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageReplyEnterMarriageHallRequest *tpMsg = ( CMessageReplyEnterMarriageHallRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// ��Ӫ��npc�ж�	
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}	
	
	//TODO:: npc�ж�
	PlayerEnterMarriageHall( pPlayer, true );		
}

// ***********************************************************
//  Function:		SendReplyEnterMarriageHallResponse
//  Description:	�Ƿ�ͬ��������õĴ𸴻�Ӧ		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendReplyEnterMarriageHallResponse( CEntityPlayer *pPlayer, int nErrcode )
{ 
	LK_ASSERT( pPlayer != NULL, return )	
	CMessage tMsgHead;
	CMessageReplyEnterMarriageHallResponse tMsgReplyEnterMarriageHall;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_REPLYENTERMARRIAGEHALL );
	tMsgHead.set_msgpara( (int)&tMsgReplyEnterMarriageHall );
	
	tMsgReplyEnterMarriageHall.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		OnMessageNewlywedEnterHallRequest
//  Description:	��������������õ���Ϣ����		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessageNewlywedEnterHallRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pPlayer != NULL, return )	
	CMessageNewlyEnterHallRequest *tpMsg = ( CMessageNewlyEnterHallRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// �жϹ���
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}
	
	// TODO:npc���񼰾����ж�
	
	PlayerEnterMarriageHall( pPlayer, true );
}

// ***********************************************************
//  Function:		SendNewlywedEnterHallResponse
//  Description:	��������������õ���Ϣ��Ӧ		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendNewlywedEnterHallResponse( CEntityPlayer *pPlayer, int nErrcode, int nWeddingModule, int nBaitangEnd )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageNewlyEnterHallResponse tMsgEnterHall;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_NEWLYWEDENTERHALL );
	tMsgHead.set_msgpara( (int)&tMsgEnterHall );													
	tMsgEnterHall.set_errcode( nErrcode );
	tMsgEnterHall.set_weddingmodule( nWeddingModule ); 
	tMsgEnterHall.set_baitangend( nBaitangEnd );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );	
}

// ***********************************************************
//  Function:		OnMessageGuestEnterHallRequest
//  Description:	ӵ��������������������õ���Ϣ����		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessageGuestEnterHallRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageGuestEnterHallRequest *tpMsg = ( CMessageGuestEnterHallRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// �жϹ���
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}		
	if( pPlayer->GetMarriageID() == CMarriageManager::GetSingleton().GetCurrentWeddingID() )
	{
		PlayerEnterMarriageHall( pPlayer, true );
	}
	else
	{
		PlayerEnterMarriageHall( pPlayer, false );	
	}
}

// ***********************************************************
//  Function:		SendGuestEnterHallResponse
//  Description:	ӵ��������������������õ���Ϣ��Ӧ		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendGuestEnterHallResponse( CEntityPlayer *pPlayer, int nErrcode )
{ 
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageGuestEnterHallResponse tMsgEnterMarriageHall;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_GUESTENTERHALL );
	tMsgHead.set_msgpara( (int)&tMsgEnterMarriageHall );
	tMsgEnterMarriageHall.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		OnMessageBaiTangRequest
//  Description:	���˰��õ�����		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessageBaiTangRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageBaitangRequest *tpMsg = ( CMessageBaitangRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// �жϹ���
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}
	
	// TODO:npc����;����ж�
	CEntity *tpEntity = NULL;
	
	PlayerBaitang( pPlayer, tpEntity );		
}

// ***********************************************************
//  Function:		SendBaitangResponse
//  Description:	���˰��õĻ�Ӧ		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendBaitangResponse( CEntityPlayer *pPlayer, int nErrcode )
{	
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageBaitangResponse tMsgBaitang;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_BAITANG );	
	tMsgHead.set_msgpara( (int)&tMsgBaitang );
	
	tMsgBaitang.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendBaitangNotify
//  Description:	���˰��õĻ�Ӧ		
//  Output:			
//  Date:	02/25/2010
// **********************************************************		
void CMarriageModule::SendBaitangNotify( CEntityPlayer *pPlayer, const char *pGroomName, const char *pBrideName, int nGroomEntityID, int nBrideEntityID )
{	
	LK_ASSERT( pGroomName != NULL && pBrideName != NULL && pPlayer != NULL, return )	
	CMessage tMsgHead;
	CMessageBaitangNotify tMsgBaitang;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_BAITANG );
	tMsgHead.set_msgpara( (int)&tMsgBaitang );
	tMsgBaitang.set_brideentityid( nBrideEntityID );
	tMsgBaitang.set_groomentityid( nGroomEntityID );
	
	CMapModule::GetSingleton().MessageBroadCast( pPlayer, &tMsgHead, false, true );
}

// ***********************************************************
//  Function:		OnMessagePutKeepsakeRequest
//  Description:	�����������Ϣ����		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessagePutKeepsakeRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{	 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessagePutKeepSakeRequest *tpMsg = ( CMessagePutKeepSakeRequest * )pMessage->msgpara();
	LK_ASSERT( pPlayer != NULL, return )

	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}
	
	// npc ��������ж�
	PlayerPutKeepsake( pPlayer, tpMsg->keepsakeindex() );
}

// ***********************************************************
//  Function:		SendPutKeepsakeResponse
//  Description:	�����������Ϣ��Ӧ		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendPutKeepsakeResponse( CEntityPlayer *pPlayer, int nErrcode, int nIndex )
{ 
	LK_ASSERT( pPlayer != NULL, return )	
	CMessage tMsgHead;
	CMessagePutKeepSakeResponse tMsgPutKeepsaek;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_PUTKEEPSAKE );
	tMsgHead.set_msgpara( (int)&tMsgPutKeepsaek );
	tMsgPutKeepsaek.set_errcode( nErrcode );
	tMsgPutKeepsaek.set_index( nIndex );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendPutKeepSakeNotify
//  Description:	���ͷ��������֪ͨ		
//  Output:			
//  Date:	04/14/2010
// **********************************************************
void CMarriageModule::SendTimeToPutKeepSakeNotify( CMarriageInfo *pMarriage, CEntityPlayer *pPlayer /* = NULL */ )
{  
	LK_ASSERT( pMarriage != NULL, return )
	
	CMessage tMsgHead;
	CMessageTimeToPutKeepsakeNotify tMsgPutKeepsake;	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_TIMETOPUTKEEPSAKE );
	tMsgHead.set_msgpara( (int)&tMsgPutKeepsake );
	tMsgPutKeepsake.set_groomroleid( pMarriage->GetGroomID() );
	tMsgPutKeepsake.set_brideroleid( pMarriage->GetBrideID() );	
	if ( pPlayer == NULL )
	{
		CTemplateMarriageConfig *tpConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
		if ( tpConfig == NULL )
		{
			return;
		}	
	
		int tWeddingModule = pMarriage->GetWeddingModule();
		if ( tWeddingModule < 0 || tWeddingModule >= (int)ARRAY_CNT( tpConfig->mWeddinInfo ) )
		{
			return;
		}		
		int tMapID = tpConfig->mWeddinInfo[ tWeddingModule ].mWeddingHallMapID;
		SendMapMessage( tMapID, &tMsgHead );
	}
	else
	{		
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );			
	}
	
}

// ***********************************************************
//  Function:		OnMessageExchangeKeepsakeRequest
//  Description:	�������������		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessageExchangeKeepsakeRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{  
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	CMessageExchangeKeepsakeRequest *tpMsg = ( CMessageExchangeKeepsakeRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// �жϹ���
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}
	
	PlayerExchangeKeepsake( pPlayer );
}

// ***********************************************************
//  Function:		SendExchangeKeepsakeResponse
//  Description:	��������Ļ�Ӧ��Ϣ		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendExchangeKeepsakeResponse( CEntityPlayer *pPlayer, int nErrcode )
{ 
	LK_ASSERT( pPlayer != NULL, return )	
	CMessage tMsgHead;
	CMessageExchangeKeepsakeResponse tMsgExchangeKeepsake;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_EXCHANGKEEPSAKE );
	tMsgHead.set_msgpara( (int)&tMsgExchangeKeepsake );
	
	tMsgExchangeKeepsake.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendExchangeKeepsakeNotify
//  Description:	���������֪ͨ		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendExchangeKeepsakeNotify( const char *pGroomName, CItemObject *pBrideKeepsake, const char *pBrideName, CItemObject *pGroomKeepsake )
{
	
}

// ***********************************************************
//  Function:		OnMessageDivorceRequest
//  Description:	������Ϣ����		
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessageDivorceRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageDivorceRequest *tpMsg = ( CMessageDivorceRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// ֻ���ڱ��������
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}
	
	// npc����;����ж�  		
	PlayerDivorce( pPlayer );
}

// ***********************************************************
//  Function:		SendVivorceResponse
//  Description:	������Ϣ��Ӧ		
//  Output:			
//  Date:	03/04/2010
// **********************************************************
void CMarriageModule::SendVivorceResponse( CEntityPlayer *pPlayer, int nErrcode )
{ 
	LK_ASSERT( pPlayer != NULL, return )	
	CMessage tMsgHead;
	CMessageDivorceResponse tMsgDivorce;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_DIVORCE );
	tMsgHead.set_msgpara( (int)&tMsgDivorce );
	tMsgDivorce.set_errcode( nErrcode )	;
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		BroadCastDivorce
//  Description:	������Ϣ֪ͨ		
//  Output:			
//  Date:	03/04/2010
// **********************************************************	
void CMarriageModule::BroadCastDivorce( CEntityPlayer *pPlayer, const char *pGroomName, const char *pBrideName, int nGroomCharID, int nBrideCharID )
{
	if ( pPlayer == NULL )
	{
		return;
	}
	
	CMessage tMsgHead;
	CMessageDivorceNotify tMsgDivorce;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_DIVORCE );		
	tMsgHead.set_msgpara( (int)&tMsgDivorce );
	
	if ( pGroomName != NULL )
	{
		tMsgDivorce.set_groomname( pGroomName );
	}
	
	if ( pBrideName != NULL )
	{
		tMsgDivorce.set_bridename( pBrideName );
	}
	
	tMsgDivorce.set_bridecharid( nBrideCharID );
	tMsgDivorce.set_groomcharid( nGroomCharID );
	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
	
}

// ***********************************************************
//  Function:		SendDivorceNotify
//  Description:	������Ϣ֪ͨ		
//  Output:			
//  Date:	02/25/2010
// **********************************************************	
void CMarriageModule::SendDivorceNotify( CEntityPlayer *pPlayer, int nRoleID )
{
	LK_ASSERT( pPlayer != NULL, return )
	
	CMessage tMsgHead;
	CMessageSpouseDivorceNotify tMsgDivorce;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_SPOUSEDIVORCE );	
	tMsgHead.set_msgpara( (int)&tMsgDivorce );
	tMsgDivorce.mutable_router()->set_routertype( CMessageRouter::ROUTER_CHAR );
	tMsgDivorce.mutable_router()->set_srccharid( pPlayer->GetCharID() );
	tMsgDivorce.mutable_router()->set_srcname( pPlayer->GetCharName() );
	tMsgDivorce.mutable_router()->set_descharid( nRoleID );	
	
	CSceneLogic::GetSingleton().Send2Player( nRoleID, &tMsgHead );
}

// ***********************************************************
//  Function:		SendMarryResultNotify
//  Description:	�����֪ͨ(�Է��Ƿ�ͬ��)		
//  Output:			
//  Date:	02/25/2010
// **********************************************************	
void CMarriageModule::SendMarryResultNotify( CEntityPlayer *pPlayer, int nResult, const char *pSpuseName, int nMarriageStatus )
{
	CMessage tMsgHead;
	CMessageMarryResultNotify 	tMsgMarryResultNotify;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_MARRYRESULT );
	tMsgHead.set_msgpara( (int)&tMsgMarryResultNotify );
	
	tMsgMarryResultNotify.set_result( nResult );
	if ( pSpuseName != NULL )
	{
		tMsgMarryResultNotify.set_spousename( pSpuseName );
	}
	
	tMsgMarryResultNotify.set_marriagestatus( nMarriageStatus );
	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendBeginWeddinResultNotify
//  Description:	��ʼ����Ľ��֪ͨ(��ż�Ƿ�ͬ��)
//  Output:			
//  Date:	02/25/2010
// **********************************************************	
void CMarriageModule::SendBeginWeddinResultNotify( CEntityPlayer *pPlayer, int nResult )
{	
	LK_ASSERT( pPlayer != NULL, return )	
	CMessage tMsgHead;
	CMessageBeginWeddingResultNofiy tMsgBeginWeddingResult;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_BEGINWEDINGRESULT );
	tMsgHead.set_msgpara( (int)&tMsgBeginWeddingResult );
	tMsgBeginWeddingResult.set_result( nResult );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );	
}

// ***********************************************************
//  Function:		OnMessageGetCampMarriageInfoRequest
//  Description:	��ȡ����Ӫ������Ϣ����Ϣ����
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnMessageGetCampMarriageInfoRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{ 
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )		
	CMessageGetCampMarriageInfoRequest *tpMsg = ( CMessageGetCampMarriageInfoRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// ��Ӫ�ж�
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}
	
	// npc�ж�
	PlayerGetMarriageInfo( pPlayer );
}

// ***********************************************************
//  Function:		SendGetCampMarriageInfoResponse
//  Description:	����Ӫ������Ϣ����Ϣ��Ӧ
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendGetCampMarriageInfoResponse( CEntityPlayer *pPlayer )
{
	
}

// ***********************************************************
//  Function:		SendPersonMarriageInfoNotify
//  Description:	���͸��˵Ļ�����Ϣ
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::SendPersonMarriageInfoNotify( CEntityPlayer *pPlayer, CMarriageInfo *pMarriageInfo )
{	
	LK_ASSERT( pPlayer != NULL && pMarriageInfo != NULL, return )
	CMessage tMsgHead;
	CMessagePersonMarriageInfoNotify tMsgMarriageInfo;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_PERSONMARRIAGEINFO );
	tMsgHead.set_msgpara( (int)&tMsgMarriageInfo );
	
	if ( pPlayer->GetCharID() == pMarriageInfo->GetGroomID() )
	{	
		tMsgMarriageInfo.set_spousename( pMarriageInfo->GetBrideName() ); 		
	}
	else
	{	
		tMsgMarriageInfo.set_spousename( pMarriageInfo->GetGroomName() ); 		
	}		
	
	tMsgMarriageInfo.set_roleid( pPlayer->GetCharID() );
	
	tMsgMarriageInfo.set_marriagestatus( pMarriageInfo->GetMarriageStatus() );
	if ( pMarriageInfo->GetMarriageStatus() == MARRIAGESTATUS_WEDDINGEND || pMarriageInfo->GetMarriageStatus() == MARRIAGESTATUS_WEDDINGFAILED )
	{
		tMsgMarriageInfo.set_marriagestatus( MARRIAGESTATUS_MARRY );	
	}
	tMsgMarriageInfo.set_weddingtime( pMarriageInfo->GetWeddingTime() );	

	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		CMapModule::GetSingleton().MessageBroadCast( pPlayer, &tMsgHead, false, true );
	}
	else
	{
		CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
	}	
}	

// ***********************************************************
//  Function:		OnRoterMessageSpouseDivorce
//  Description:	��ż����·����Ϣ
//  Output:			
//  Date:	02/25/2010
// **********************************************************
void CMarriageModule::OnRoterMessageSpouseDivorce( CMessage *pMessage )
{ 
	LK_ASSERT( pMessage != NULL, return )	
	CMessageSpouseDivorceNotify *tpMsg = ( CMessageSpouseDivorceNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	if (  tpMsg->router().sendback() == 0 && tpMsg->router( ).routerreason( ) == CMessageRouter::REASON_SUCCESS )
	{	
		CEntityPlayer *tpPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMsg->router().descharid() );
		LK_ASSERT( tpPlayer != NULL, return )	
		
		if ( tpPlayer->GetNationality() == CSceneLogic::GetSingleton().GetLineID() )
		{
			return;
		}		
		
		CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfoOfOtherCamp( tpPlayer->GetMarriageID() );
		if ( tpMarriageInfo != NULL )
		{

			LOG_INFO( "marriage","[%d] player ( roleid:%d ) divorced, change marriageid:%d to 0 ", __LINE__, tpPlayer->GetCharID(),
				tpPlayer->GetMarriageID() );
			BroadCastDivorce( tpPlayer, tpMarriageInfo->GetGroomName(), tpMarriageInfo->GetBrideName(), tpMarriageInfo->GetGroomID(), tpMarriageInfo->GetBrideID() );
		}
																									  
		CMarriageManager::GetSingleton().DeleteOtherCampMarriageInfo( tpPlayer->GetMarriageID() );
		
		tpPlayer->SetMarriageID( 0 );	 
						
		// ȥ�����޳ƺ�
		CTemplateMarriageConfig *tpConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
		if ( tpConfig != NULL )
		{
			CPropertyModule::GetSingleton().OnPlayerDelTitleEvent( tpPlayer, tpConfig->mMarriageTitleID );
		}
			
		//CSceneLogic::GetSingleton().Send2Player( tpPlayer, pMessage );
	}
}

// ***********************************************************
//  Function:		CheckMarriageNpc
//  Description:	���npc�ķ���;���
//  Output:			
//  Date:	03/10/2010
// **********************************************************
bool CMarriageModule::CheckMarriageNpc( CEntityPlayer *pPlayer, int nEntityID )
{
	if ( pPlayer == NULL )
	{
		return false;
	}
	
	CEntityFuncNpc *tpFuncNpc = dynamic_cast< CEntityFuncNpc * >( CSceneObjManager::GetSingleton().GetObject( nEntityID ) );
	if ( tpFuncNpc == NULL )
	{
		return false;
	}
	
	if ( pPlayer->IsWithinDistance( tpFuncNpc, MAX_NPC_TALK_GIRD ) != false )
	{																		
		return false;
	}
	
	CPropertyNPC *tpProperty =  ( CPropertyNPC * )tpFuncNpc->GetProperty();
	CTemplateNpc *tpTemplateNpc = ( CTemplateNpc * )CDataStatic::SearchTpl( tpProperty->GetPropertyTempID() );
	if ( tpTemplateNpc == NULL )
	{							
		return false;
	}
	
	if ( tpTemplateNpc->mMarriageService != CTemplateNpc::MARRIAGETYPE_MARRIAGE )
	{
		return false;
	}
	return true;
}

// ***********************************************************
//  Function:		OnMessageUseSysInvitation
//  Description:	ʹ��ϵͳ����������
//  Output:			
//  Date:	03/16/2010
// **********************************************************
void CMarriageModule::OnMessageUseSysInvitation( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageUseSysInvitationRequest *tpMsg = ( CMessageUseSysInvitationRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	UseSysInvitation( pPlayer, tpMsg->itemindex(), tpMsg->mutable_receivedname()->c_str() );
}

// ***********************************************************
//  Function:		SendUseSysInvitationResponse
//  Description:	����ʹ��ϵͳ�����Ļ�Ӧ��Ϣ
//  Output:			
//  Date:	03/16/2010
// **********************************************************
void CMarriageModule::SendUseSysInvitationResponse( CEntityPlayer *pPlayer, int nErrcode )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageUseSysInvitationResponse tMsgUseSysInvitation;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_USESYSINVITATION );	
	tMsgHead.set_msgpara( (int)&tMsgUseSysInvitation );	
	
	tMsgUseSysInvitation.set_errcode( nErrcode );	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendNewlyMarriedNotify
//  Description:	�������˽��ɹ���֪ͨ
//  Output:			
//  Date:	04/12/2010
// **********************************************************
void CMarriageModule::SendNewlyMarriedNotify( CMarriageInfo *tpMarriage )
{
	LK_ASSERT( tpMarriage != NULL, return )
	CMessage tMsgHead;
	CMessageNewlyMarriedNotify tMsgNewlyMarried;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_NEWLYMARRIED );
	tMsgHead.set_msgpara( (int)&tMsgNewlyMarried );
	
	tMsgNewlyMarried.set_bridename( tpMarriage->GetBrideName() );
	tMsgNewlyMarried.set_groomname( tpMarriage->GetGroomName() );
	tMsgNewlyMarried.set_weddingmodule( tpMarriage->GetWeddingModule() );
	tMsgNewlyMarried.set_weddingtime( tpMarriage->GetWeddingTime() );
	tMsgNewlyMarried.set_weddingtimelength( tpMarriage->GetWeddingTimeLength() );
	tMsgNewlyMarried.set_campid( tpMarriage->GetCampID() );
	tMsgNewlyMarried.set_seversequence( tpMarriage->GetServerSequence() );
	tMsgNewlyMarried.set_brideid( tpMarriage->GetBrideID() );
	tMsgNewlyMarried.set_groomid( tpMarriage->GetGroomID() );
	
	if ( tpMarriage->GetWeddingTime() > 0 && tpMarriage->GetWeddingModule() == 2 )
	{
		CSceneLogic::GetSingleton().SendWorldMessage( &tMsgHead );
	}
	else
	{
		CSceneLogic::GetSingleton().SendCountryMessage( &tMsgHead, CSceneLogic::GetSingleton().GetLineID() );
	} 
}					    

// ***********************************************************
//  Function:		PlayerMarryApply
//  Description:	���������
//  Output:			
//  Date:	02/26/2010
// **********************************************************	
void CMarriageModule::PlayerMarryApply( CEntityPlayer *pPlayer, int nWeddingTime, int nWeddingTimeLength, int nWeddingModule )
{			
	LK_ASSERT( pPlayer != NULL, return )
	
	// �жϽ�鷽�Ƿ��л���
	if ( pPlayer->GetMarriageID() != 0 )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_MARRIED );
		return;			
	}
	
	// �����Ҵ��ڻ���������Ϣ�������ڽ��
	if ( CMarriageManager::GetSingleton().GetMarriageApplyInfo( pPlayer->GetCharID() ) != NULL )
	{
		return;
	}
	
	if ( nWeddingTime < 0 || nWeddingTimeLength < 0 || nWeddingTimeLength > DEFAULT_WEDDINGMAXTIMELENGTH )
	{
		return;
	}
	
	// ������л���Ļ�������ʼʱ��������ڱ�����һ�μ��
	if ( nWeddingTime - time(NULL) <= VALIDTIMELENGTH_TOWEDING && nWeddingTime > 0 )
	{			
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_INVALIDWEDDINGTIME );
		return;
	}
	
	// �жϻ�����û���ظ�(�Է�ͬ����ټ��һ��)
	if ( CMarriageManager::GetSingleton().CheckWeddingTime( nWeddingTime, nWeddingTimeLength ) == false && nWeddingTime > 0 )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_WRONGWEDDINGTIME );		
		return;
	}			   	
		
	
	// �Ƿ��ж���,û�ж��鲻�ܽ��
	int tTeamID  = CTeamModule::GetSingleton().InTeam( pPlayer->GetCharID() );
	if ( tTeamID == INVALID_OBJ_ID )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_HASNOTEAM );
		return;				
	}		
	
	// �ж϶�������
	CEntityPlayer *tTeamList[TEAMNUM] = { NULL };	
	int tTeamCount = 0;
	int tRtn = CTeamModule::GetSingletonPtr()->OnGetMemberList( tTeamID,tTeamList, ARRAY_CNT( tTeamList ), tTeamCount );
	if ( tRtn < 0 || tTeamCount != 2 )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_HASNOTEAM );		
		return;
	}  	 
	
	// �ж��ǲ��Ƕӳ�
	CTeam* tpTeam = ( CTeam* ) CSceneObjManager::GetSingleton().GetObject( tTeamID );
	LK_ASSERT( tpTeam != NULL, return )
	if ( ( unsigned int )tpTeam->GetHeaderID() != pPlayer->GetCharID() )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_NOTTEAMHEADER );		
		return;
	}
		
	
	if ( tTeamList[0] == NULL || tTeamList[1] == NULL )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_HASNOTEAM );		
		return;
	}
	
	// �Ƿ��Ա��෴
	if ( tTeamList[0]->GetSex() == tTeamList[1]->GetSex() )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_SAMESEX );				
		return;		
	}
	
	// �ж�˫���Ƿ��Ѿ����
	if ( tTeamList[0]->GetMarriageID() != 0 || tTeamList[1]->GetMarriageID() != 0 )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_OTHERMARRIED );						
		return;
	}
	
	// ˫���Ƿ���Ӫ��ͬ
	if ( tTeamList[0]->GetNationality() != tTeamList[1]->GetNationality() )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_NOTSAMECAMP );								
		return;
	}
	
	CEntityPlayer *tpOtherPlayer = NULL;
	if ( tTeamList[0]->GetCharID() != pPlayer->GetCharID() )
	{
		tpOtherPlayer = tTeamList[0];
	}
	else
	{
		tpOtherPlayer = tTeamList[1];
	}
	if ( tpOtherPlayer == NULL )
	{							
		return;
	}
	
	CMarriageInfo *tpMarriageApplyInfo = CMarriageManager::GetSingleton().GetMarriageApplyInfo( tpOtherPlayer->GetCharID() );
	if ( tpMarriageApplyInfo != NULL )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_OTHERHASMARRIAGEAPPLY );								
		return;
	}
	
	// TODO:�ж��Ƿ���ָ��������
		
	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	if ( tpMarriageConfig == NULL )
	{
		LOG_ERROR( "marriage","[%s,%d] Empty MarriageConfig ",__FUNCTION__,__LINE__ );
		return;
	}
	
	// �ж�˫���ȼ��Ƿ���������
	if ( tTeamList[0]->GetLevel() < tpMarriageConfig->mMarriageLevel || tTeamList[1]->GetLevel() < tpMarriageConfig->mMarriageLevel )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_MARRIAGELEVELLOW );										
		return;
	}
	
	// �ж���û�н���֤����
	int tItemReduced = 0;
	CFriendModule::GetSingleton().CheckItemNumAffectedByIntimacy( tTeamList[0]->GetCharID(), tTeamList[1]->GetCharID(), tItemReduced );
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	if ( tpMarriageConfig->mBasicMarriageItem > 0 && tpMarriageConfig->mBasicMarriageItemNum > 0 )
	{	  
		if ( tpProperty->GetBaggage()->HasItem( tpMarriageConfig->mBasicMarriageItem, tpMarriageConfig->mBasicMarriageItemNum - tItemReduced, BIND_ALL ) == false )
		{
			SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_HASNOBASICITEM );
			return;
		}	
	}			 		
	
	// �жϽ�Ǯ���㹻
	if ( nWeddingModule < 0 || ( unsigned int )nWeddingModule >= sizeof( tpMarriageConfig->mWeddinInfo ) )
	{
		return;
	}
	
	int tMoneyNeed = 0;
	int tMarriageItemID = 0;
	if ( nWeddingTime == 0 )
	{
		tMoneyNeed = tpMarriageConfig->mMarriageMoney;
	}
	else
	{
		tMoneyNeed = tpMarriageConfig->mMarriageMoney + tpMarriageConfig->mWeddinInfo[nWeddingModule].mMoneyNeeded;	
		tMarriageItemID = tpMarriageConfig->mWeddinInfo[nWeddingModule].mMarriageItemID;
	}			
	
	if ( tpProperty->GetMoney() < tMoneyNeed )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_MONEYNOTENOUGH );												
		return;
	}
	
	if ( tMarriageItemID > 0 )
	{
		if ( tpProperty->GetBaggage()->HasItem( tMarriageItemID, 1, BIND_ALL ) == false )
		{
			SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_NOMARRIAGEITEM );
			return;
		}
	}
	
	// �жϰ��������Ƿ��㹻
	CPropertyPlayer *tpTeam1Property = ( CPropertyPlayer * )tTeamList[0]->GetProperty();
	CPropertyPlayer *tpTeam2Property = ( CPropertyPlayer * )tTeamList[1]->GetProperty();
	if ( tpTeam1Property->GetBaggage()->Space( -1, 3 ) == false 
		|| tpTeam2Property->GetBaggage()->Space( -1, 3 ) == false )
	{
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_NOTENOUGHBAGSPACE );														
		return;
	}	  	
	
	int tGroomID = 0;
	int tBrideID = 0;
	if ( tTeamList[0]->GetSex() == 2 )
	{
		tGroomID = tTeamList[0]->GetCharID();
		tBrideID = tTeamList[1]->GetCharID();	
	}
	else
	{	
		tGroomID = tTeamList[1]->GetCharID();	
		tBrideID = tTeamList[0]->GetCharID();		
	}
	
	
	// ����һ��������Ļ�����Ϣ
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().CreatMarriageApplyInfo( tGroomID, tBrideID, nWeddingTime, nWeddingTimeLength, nWeddingModule );	
	if ( tpMarriageInfo == NULL )
	{		
		SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_FAILED );		
		return;
	}
	
	// ������Ϣ
	int tOtherInfo = MESSAGE_MARRIAGE;
	CTimerMng::GetSingleton().SetTimer( tpMarriageInfo->get_id(), TIMER_MARRIAGEAPPLY, MARRY_APPLY_VALIDTIMELENGTH, 1, &tOtherInfo );
	
	// ֪ͨ�Է���������
	SendMarryRequestNotify( tpOtherPlayer, pPlayer->GetCharName(), pPlayer->GetCharID(), nWeddingTime, nWeddingModule );	
	
	// ���ͽ��֪ͨ
	SendApplyMarryResponse( pPlayer, SUCCESS );
}

// ***********************************************************
//  Function:		PlayerReplyMarry
//  Description:	��Ҵ𸴽������
//  Output:			
//  Date:	02/27/2010
// **********************************************************	
void CMarriageModule::PlayerReplyMarry( CEntityPlayer *pPlayer, int nResult )
{ 
	LK_ASSERT( pPlayer != NULL, return )		
		
	// �жϽ�鷽�Ƿ��л���
	if ( pPlayer->GetMarriageID() != 0 )
	{
		//SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_HASNOTEAM );
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );	
		return;			
	}


	// �Ƿ��ж���,û�ж��鲻�ܽ��
	int tTeamID  = CTeamModule::GetSingleton().InTeam( pPlayer->GetCharID() );
	if ( tTeamID == INVALID_OBJ_ID )
	{
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );		
		SendReplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_HASNOTEAM );
		return;				
	}		

	// �ж϶�������
	CEntityPlayer *tTeamList[TEAMNUM] = { NULL };	
	int tTeamCount = 0;
	int tRtn = CTeamModule::GetSingletonPtr()->OnGetMemberList( tTeamID,tTeamList, ARRAY_CNT( tTeamList ), tTeamCount );
	if ( tRtn < 0 || tTeamCount != 2 )
	{
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );
		SendReplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_HASNOTEAM );		
		return;
	} 	 	 
	
	CEntityPlayer *tpOtherPlayer = NULL;
	if ( tTeamList[0]->GetCharID() == pPlayer->GetCharID() )
	{
		tpOtherPlayer = tTeamList[1];
	}
	else
	{
		tpOtherPlayer = tTeamList[0];
	}
	
	if ( tpOtherPlayer == NULL )
	{
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );
		return;
	}
	
	// �ж϶Է��Ƿ��Ѿ����
	if ( tpOtherPlayer->GetMarriageID() != 0 )
	{
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );
		return;
	}
	
	// ��ȡ����������Ϣ
	CMarriageInfo *tpMarriageApplyInfo = CMarriageManager::GetSingleton().GetMarriageApplyInfo( pPlayer->GetCharID() );
	if ( tpMarriageApplyInfo == NULL )
	{ 		
		SendReplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_INVALIDAPPLY );				
		return;
	}
	
	// �ж϶Է��Ƿ������
	if ( tpMarriageApplyInfo->GetGroomID() != tpOtherPlayer->GetCharID() && tpMarriageApplyInfo->GetBrideID() != tpOtherPlayer->GetCharID() )
	{
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );
		return;
	}
	
	// ��ͬ����
	if ( nResult != 1 )
	{
		// �������������Ϣ
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );
		SendMarryResultNotify( tpOtherPlayer, nResult, pPlayer->GetCharName(), 0 );				
		return;
	}
	
	// ͬ����
	const char *tpGroomName = NULL;
	const char   *tpBrideName = NULL;
	if ( tpMarriageApplyInfo->GetGroomID() == pPlayer->GetCharID() )
	{
		tpGroomName = pPlayer->GetCharName();
		tpBrideName = tpOtherPlayer->GetCharName();
	}
	else
	{
		tpGroomName = tpOtherPlayer->GetCharName();
		tpBrideName = pPlayer->GetCharName();	
	}	
	
	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	if ( tpMarriageConfig == NULL )
	{
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );
		LOG_ERROR( "marriage","[%s,%d] Empty MarriageConfig ",__FUNCTION__,__LINE__ );
		return;
	}	
	
	// �ж���û�н���֤����
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )tpOtherPlayer->GetProperty();	
	int tItemReduced = 0;
	CFriendModule::GetSingleton().CheckItemNumAffectedByIntimacy( tTeamList[0]->GetCharID(), tTeamList[1]->GetCharID(), tItemReduced );
	if ( tpMarriageConfig->mBasicMarriageItem > 0 && tpMarriageConfig->mBasicMarriageItemNum )
	{	  
		if ( tpProperty->GetBaggage()->HasItem( tpMarriageConfig->mBasicMarriageItem, tpMarriageConfig->mBasicMarriageItemNum - tItemReduced, BIND_ALL ) == false )
		{		
			CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );  		
			SendApplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_HASNOBASICITEM );			
			return;
		}	
	}			 		

	// �жϽ�Ǯ���㹻	
	int tMoneyNeed = 0;
	int tMarriageItemID = 0;
	if ( tpMarriageApplyInfo->GetWeddingTime() == 0 )
	{
		tMoneyNeed = tpMarriageConfig->mMarriageMoney;
	}
	else
	{	
		tMoneyNeed =  tpMarriageConfig->mMarriageMoney + tpMarriageConfig->mWeddinInfo[tpMarriageApplyInfo->GetWeddingModule()].mMoneyNeeded;
		tMarriageItemID = tpMarriageConfig->mWeddinInfo[tpMarriageApplyInfo->GetWeddingModule()].mMarriageItemID;
	}	
	
	if ( tpProperty->GetMoney() < tMoneyNeed )
	{
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( tpOtherPlayer->GetCharID() );
		SendReplyMarryResponse( tpOtherPlayer, EM_MARRIAGE_MARRY_MONEYNOTENOUGH );												
		return;
	}
	
	if ( tMarriageItemID > 0 )
	{
		if ( tpProperty->GetBaggage()->HasItem( tMarriageItemID, 1, BIND_ALL ) == false )
		{
			CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );
			SendReplyMarryResponse( tpOtherPlayer, EM_MARRIAGE_MARRY_NOMARRIAGEITEM );			
			return;
		}
	}

	// �жϰ��������Ƿ��㹻
	CPropertyPlayer *tpTeam1Property = ( CPropertyPlayer * )tTeamList[0]->GetProperty();
	CPropertyPlayer *tpTeam2Property = ( CPropertyPlayer * )tTeamList[1]->GetProperty();
	if ( tpTeam1Property->GetBaggage()->Space( -1, 3 ) == false 
		|| tpTeam2Property->GetBaggage()->Space( -1, 3 ) == false )
	{
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );
		SendReplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_NOTENOUGHBAGSPACE );														
		return;
	}  
		
	// �۳���Ǯ
	if ( CPropertyModule::GetSingleton().PlayerChangeMoney( tpOtherPlayer, tMoneyNeed, true, false ) != SUCCESS )
	{
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( tpOtherPlayer->GetCharID() );
		SendReplyMarryResponse( pPlayer, EM_MARRIAGE_MARRY_MONEYNOTENOUGH );
		return;
	}
	
	// ���������Ϣ
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().CreatMarriageInfo( tpGroomName, tpMarriageApplyInfo->GetGroomID(), tpBrideName, tpMarriageApplyInfo->GetBrideID(), tpMarriageApplyInfo->GetWeddingTime(), tpMarriageApplyInfo->GetWeddingTimeLength(), tpMarriageApplyInfo->GetWeddingModule(), CSceneLogic::GetSingleton().GetLineID() );
	if ( tpMarriageInfo == NULL )
	{		
		// �������������Ϣ	
		CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );	
		LOG_ERROR( "marriage","[%s,%d] creat marriageinfo wrong, GroomID:%d, BrideID:%d ", __FUNCTION__, __LINE__, tpMarriageApplyInfo->GetGroomID(), tpMarriageApplyInfo->GetBrideID() );							
		return;
	}
	CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( pPlayer->GetCharID() );	
	
	bool bBind = false;
	
	// �۳���֤����
	if ( tpMarriageConfig->mBasicMarriageItem > 0  && tpMarriageConfig->mBasicMarriageItemNum )
	{	
		uint64_t tGuID = 0;
		CPropertyModule::GetSingleton().PlayerRemoveItemByID( tpOtherPlayer, tpMarriageConfig->mBasicMarriageItem, tpMarriageConfig->mBasicMarriageItemNum - tItemReduced , bBind, &tGuID );				
		LogEventLostItemByUse(pPlayer, tGuID, tpMarriageConfig->mBasicMarriageItem, tpMarriageConfig->mBasicMarriageItemNum - tItemReduced ); 
	}	 		
	
	// �۳�����
	if ( tMarriageItemID > 0 )
	{
		uint64_t tGuID = 0;
		CPropertyModule::GetSingleton().PlayerRemoveItemByID( tpOtherPlayer, tMarriageItemID, 1, bBind, &tGuID );	
		LogEventLostItemByUse( pPlayer, tGuID, tMarriageItemID, 1 );
	}	   
	
	// ������Ʒ	
	int tMaleKeepsakeID = 0;
	int tFemaleKeepsakeID = 0;
	int tInvitationID = 0;
	int tInvitationNum = 0;
	int tMaleItemID = 0;
	int tFemaleItemID = 0;
	
	if ( tpMarriageInfo->GetWeddingTime() == 0  )
	{
		tMaleKeepsakeID = tpMarriageConfig->mMaleKeepsakeID;
		tFemaleKeepsakeID = tpMarriageConfig->mFemaleKeepsakeID;
		tInvitationID = tpMarriageConfig->mInvitationID;
		tInvitationNum = tpMarriageConfig->mInvitationNum;	
		tMaleItemID = tpMarriageConfig->mMaleItemID;
		tFemaleItemID = tpMarriageConfig->mFemaleItemID;
	}
	else
	{	
		int tRandNum = rand()%3;
		if ( tRandNum == 0 )
		{
			tMaleKeepsakeID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mMaleKeepsakeID;
		}
		else if ( tRandNum == 1 )
		{
			tMaleKeepsakeID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mMaleKeepsakeTwo;
		}
		else	
		{
			tMaleKeepsakeID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mMaleKeepsakeThree;	
		}
		
		tRandNum = rand()%3;
		if( tRandNum == 0 )
		{
			tFemaleKeepsakeID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mFemaleKeepsakeID;	
		}
		else if ( tRandNum == 1 )
		{
			tFemaleKeepsakeID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mFemaleKeepsakeTwo;
		}
		else
		{
			tFemaleKeepsakeID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mFemaleKeepsakeThree;
		}
				
		tInvitationID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mInvitationCardID;
		tInvitationNum = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mInvitationCardNum;
		tMaleItemID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mMaleItemID;
		tFemaleItemID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mFemaleItemID;
	}
		
	if( tInvitationID > 0 && tInvitationNum > 0 )
	{
		CPropertyModule::GetSingleton().PlayerInsertItem( tTeamList[0], tInvitationID, tInvitationNum );
		CPropertyModule::GetSingleton().PlayerInsertItem( tTeamList[1], tInvitationID, tInvitationNum );
	}
	
	if ( tTeamList[0]->GetSex() == 2 )
	{
		CPropertyModule::GetSingleton().PlayerInsertItem( tTeamList[1], tFemaleKeepsakeID, 1 );
		CPropertyModule::GetSingleton().PlayerInsertItem( tTeamList[0], tMaleKeepsakeID, 1 );
		
		CPropertyModule::GetSingleton().PlayerInsertItem( tTeamList[1], tFemaleItemID, 1 );
		CPropertyModule::GetSingleton().PlayerInsertItem( tTeamList[0], tMaleItemID, 1 );
	}
	else
	{
		CPropertyModule::GetSingleton().PlayerInsertItem( tTeamList[0], tFemaleKeepsakeID, 1 );
		CPropertyModule::GetSingleton().PlayerInsertItem( tTeamList[1], tMaleKeepsakeID, 1 );
		CPropertyModule::GetSingleton().PlayerInsertItem( tTeamList[0], tFemaleItemID, 1 );
		CPropertyModule::GetSingleton().PlayerInsertItem( tTeamList[1], tMaleItemID, 1 );
	}	
	
	SendMarryResultNotify( tpOtherPlayer, nResult, pPlayer->GetCharName(), tpMarriageInfo->GetMarriageStatus() );					
	
	// �����ɹ�֮����ɾ��������Ϣ
	CreatMarriageDBInfo( tpMarriageInfo );	
	
	// ���ͳɹ���Ϣ
	SendReplyMarryResponse( pPlayer, SUCCESS, tpOtherPlayer->GetCharName(), nResult, tpMarriageInfo->GetMarriageStatus() );
	
	// ������Ӫ��Ϣ
	UpDateCampDBInfo( CMarriageManager::GetSingleton().GetCampInfo() );	
	
	// ����ƺ���Ϣ
	CPropertyModule::GetSingleton().OnPlayerAddTitleEvent( tTeamList[0], tpMarriageConfig->mMarriageTitleID );
	CPropertyModule::GetSingleton().OnPlayerAddTitleEvent( tTeamList[1], tpMarriageConfig->mMarriageTitleID );
	
	LOG_INFO( "marriage","player( roleid:%d ) married player( roleid:%d ) at time:%d ", pPlayer->GetCharID(), tpOtherPlayer->GetCharID(), time(NULL) );
}

// ***********************************************************
//  Function:		PlayerBeginWedding
//  Description:	��ҿ�ʼ�����������Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::PlayerBeginWedding( CEntityPlayer *pPlayer, CEntity *pNpc /* = NULL */ )
{ 
	LK_ASSERT( pPlayer != NULL, return )	
	
	// ��ȡ��ҵĻ�����Ϣ
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfo( pPlayer->GetMarriageID() ); 
	if ( tpMarriageInfo == NULL )
	{
		SendBeginWeddingResponse( pPlayer, EM_MARRIAGE_BEGINWEDDING_WRONGSTATUS );
		return;
	}
	
	LOG_INFO( "marriage","[%d] player start wedding at time:%d, roleid:%d, WeddingStatus:%d, MarriageStatus:%d, weddingTime:%d  ",__LINE__, time(NULL), 
		pPlayer->GetCharID(), tpMarriageInfo->GetWeddingStatus(),  tpMarriageInfo->GetMarriageStatus(), tpMarriageInfo->GetWeddingTime() );
		
	// �жϻ���״̬
	int tWeddingStatus = tpMarriageInfo->GetWeddingStatus( );
	if ( tWeddingStatus != WEDDINGSTATUS_INTIME || tpMarriageInfo->GetMarriageStatus() != MARRIAGESTATUS_WEDDINGINWAIT )
	{			
		// ���״̬����
		SendBeginWeddingResponse( pPlayer, EM_MARRIAGE_BEGINWEDDING_WRONGSTATUS );
		return;	
	}	
	
	// �ж�����һ���Ƿ�����
	CEntityPlayer *tpSpouse = NULL;
	if ( pPlayer->GetCharID() == tpMarriageInfo->GetGroomID() )
	{
		tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetBrideID() );
	}
	else
	{
		tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetGroomID() );
	}
	
	if ( tpSpouse == NULL )
	{
		SendBeginWeddingResponse( pPlayer, EM_MARRIAGE_WEDDING_SPOUSEOFFLINE );
		return;
	}
	
	// ˫�������ж�
	/*if ( pNpc->IsWithinDistance( pPlayer, MAX_NPC_TALK_GIRD ) == false || pNpc->IsWithinDistance( pPlayer, MAX_NPC_TALK_GIRD ) == false )
	{
		return;
	}*/
		
		
	// ���͸�����һ��֪ͨ
	SendMarriageNoticeNotify( tpSpouse );
	SendBeginWeddingResponse( pPlayer, SUCCESS );
}

// ***********************************************************
//  Function:		PlayerReplyWeddingBegin
//  Description:	��Ҵ𸴻���ʼ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::PlayerReplyWeddingBegin( CEntityPlayer *pPlayer, int nResult )
{
	LK_ASSERT( pPlayer != NULL, return )
	
	// ��ȡ��ҵĻ�����Ϣ
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfo( pPlayer->GetMarriageID() );
	if ( tpMarriageInfo == NULL )
	{
		LOG_ERROR( "marriage","[%s,%d] can not find marriage information by id:%d of player :%d",__FUNCTION__, __LINE__, pPlayer->GetMarriageID(), pPlayer->GetCharID() );  
		return;
	}
	
	// �жϻ���״̬
	if ( tpMarriageInfo->GetWeddingStatus() != WEDDINGSTATUS_INTIME || tpMarriageInfo->GetMarriageStatus() != MARRIAGESTATUS_WEDDINGINWAIT )
	{			
		return;
	}	
	
	CEntityPlayer *tpSpouse = NULL;
	if ( tpMarriageInfo->GetGroomID() == pPlayer->GetCharID() )
	{	
		tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetBrideID() );	
	}
	else
	{
		tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetGroomID() );
	}	
	
	if ( tpSpouse == NULL )
	{
		SenndReplyBeginWeddingResponse( pPlayer, EM_MARRIAGE_WEDDING_SPOUSEOFFLINE );
		return;
	}
	
	// TODO:�����ж�
	if ( tpSpouse != NULL )
	{	
		SendBeginWeddinResultNotify( tpSpouse, nResult );
	}
	
	SenndReplyBeginWeddingResponse( pPlayer, SUCCESS );	
	
	// �ж��Ƿ�ͬ�⿪ʼ����
	if ( nResult != 1 )
	{				
		return;
	}
	
	StartWedding( tpMarriageInfo, WEDDINGSTARTTYPE_PLAYER );
}

// ***********************************************************
//  Function:		NewlyEnterMarriageHall
//  Description:	��ҿ�ʼ��������
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::PlayerEnterMarriageHall( CEntityPlayer *pPlayer, bool bNewly )
{ 
	LK_ASSERT( pPlayer != NULL, return )	
	
	// ��������˽���
	if ( bNewly == true )
	{
		// �鿴����״̬
		CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfo( pPlayer->GetMarriageID() );
		if ( tpMarriageInfo == NULL )
		{
			SendNewlywedEnterHallResponse( pPlayer, EM_MARRIAGE_ENTERHALL_NOMARRIAGE, 0, 0 );
			return;
		}
		
		if ( tpMarriageInfo->GetMarriageStatus() != MARRIAGESTATUS_WEDDINGONHALL || tpMarriageInfo->GetServerSequence() != CMarriageManager::GetSingleton().GetCurrentWeddingID() )
		{  	
			SendNewlywedEnterHallResponse( pPlayer, EM_MARRIAGE_ENTERHALL_WRONGTIME, tpMarriageInfo->GetWeddingModule(), 0 );		
			return;
		}									
		
		CTemplateMarriageConfig *tpMarriageConfig =	( CTemplateMarriageConfig *	)CDataStatic::mMarriageConfig;
		LK_ASSERT( tpMarriageConfig != NULL, return ) 
		int tWeddingHallMapID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mWeddingHallMapID;
		int tPosX = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mPosX;
		int tPosY = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mPosY;
		CMapModule::GetSingleton().Teleport( CSceneLogic::GetSingleton().GetLineID(), tWeddingHallMapID, tPosX, tPosY ,pPlayer );				
		int tBaitangEnd = 0;
		if ( tpMarriageInfo->GetWeddingEventStatus() & EVENT_BAITANGEND )
		{
			tBaitangEnd = 1;
		}
		SendNewlywedEnterHallResponse( pPlayer, SUCCESS, tpMarriageInfo->GetWeddingModule(), tBaitangEnd );				
		int tBufferID = 0;	
		int tOldBufferID = 0;	
		if ( tpMarriageInfo->GetBrideID() == pPlayer->GetCharID() )
		{
			tBufferID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mBrideBufferID;
			tOldBufferID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mFemaleBufferID;
		}
		else
		{
			tBufferID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mGroomBufferID;
			tOldBufferID = tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mMaleBufferID;
		}	
			
		if ( pPlayer->HasBuff( tOldBufferID ) )
		{	  
			CPropertyModule::GetSingleton().RemoveBuff( pPlayer, tOldBufferID );	   			
		}
		
		if( pPlayer->HasBuff( tBufferID ) == false )
		{
			CPropertyModule::GetSingleton().InsertBuff( pPlayer, tBufferID );			
		}
		return;
	}
	
	// ��ȡ����Ӫ��ǰ���ھ��л���Ļ�����Ϣ
	CMarriageInfo *tpMarriage = CMarriageManager::GetSingleton().GetMarriageInfo( CMarriageManager::GetSingleton().GetCurrentWeddingID() );
	if ( tpMarriage == NULL )
	{
		SendGuestEnterHallResponse( pPlayer, EM_MARRIAGE_ENTERHALL_NOHOLDWEDDING );
		return;
	}
	
	if ( tpMarriage->GetMarriageStatus() != MARRIAGESTATUS_WEDDINGONHALL )
	{
		SendGuestEnterHallResponse( pPlayer, EM_MARRIAGE_ENTERHALL_NOTENTERHALL );
		return;
	}
	
	// �����������������������
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	
	// ������������
	bool bCheckResult = false;
	for ( unsigned int i = 0; i < tpProperty->GetBaggage()->mReleaseIndex; ++i )
	{																	
		CItemObject *tpItemObject = tpProperty->GetBaggage()->GetItemObjPtr( i ); 
		if ( tpItemObject == NULL )
		{			
			continue;
		}
		
		// ��ȡģ����Ϣ
		CTplItem *tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tpItemObject->GetItemID() );		
		if ( tpTplItem == NULL )
		{
			LOG_ERROR( "marriage","[%s,%d] can not find template information by ItemID:%d, roleid:%d ",__FUNCTION__,__LINE__, tpItemObject->GetItemID(), pPlayer->GetCharID() );
			continue;
		}
		
		// �ж��ǲ�������
		if ( tpTplItem->mItemType != CTplItem::ITEM_INVITATION )
		{
			continue;
		}
		
		CItemInvitation *tpInvitation = ( CItemInvitation * )tpItemObject;
		if ( strncmp( tpInvitation->GetGroomName(), tpMarriage->GetGroomName(), NAME_LENGTH - 1 ) != 0 )
		{
			continue;
		}
		
		if ( strncmp( tpInvitation->GetBrideName(), tpMarriage->GetBrideName(), NAME_LENGTH - 1 ) != 0 )
		{
			continue;
		}
		
		bCheckResult = true;
		break;	
	}
	
	for ( int i = 0; i < tpProperty->GetBaggage()->GetKitBagIndex(); ++i )
	{
		if ( bCheckResult == true )
		{
			break;
		}
		int tBeginIndex = -1;
		int tEndIndex	= -1;
		int tRet = tpProperty->GetBaggage()->GetKitBagIndexRange( BAGTYPE_KITBAG, i, tBeginIndex, tEndIndex );
		if ( tRet != SUCCESS )
		{
			continue;
		}
		for ( int j = tBeginIndex; j <= tEndIndex; ++j )
		{
			CItemObject *tpItemObject = tpProperty->GetBaggage()->GetItemObjPtr( j ); 
			if ( tpItemObject == NULL )
			{			
				continue;
			}

			// ��ȡģ����Ϣ
			CTplItem *tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tpItemObject->GetItemID() );		
			if ( tpTplItem == NULL )
			{
				LOG_ERROR( "marriage","[%s,%d] can not find template information by ItemID:%d, roleid:%d ",__FUNCTION__,__LINE__, tpItemObject->GetItemID(), pPlayer->GetCharID() );
				continue;
			}

			// �ж��ǲ�������
			if ( tpTplItem->mItemType != CTplItem::ITEM_INVITATION )
			{
				continue;
			}

			CItemInvitation *tpInvitation = ( CItemInvitation * )tpItemObject;
			if ( strncmp( tpInvitation->GetGroomName(), tpMarriage->GetGroomName(), NAME_LENGTH - 1 ) != 0 )
			{
				continue;
			}

			if ( strncmp( tpInvitation->GetBrideName(), tpMarriage->GetBrideName(), NAME_LENGTH - 1 ) != 0 )
			{
				continue;
			}

			bCheckResult = true;
			break;
		}		
	}
	
	if ( bCheckResult != true )
	{
		SendGuestEnterHallResponse( pPlayer, EM_MARRIAGE_ENTERHALL_HASNOINVITATION );
		return;
	}
	
	SendGuestEnterHallResponse( pPlayer, SUCCESS );
	
	CTemplateMarriageConfig *tpMarriageConfig =	( CTemplateMarriageConfig *	)CDataStatic::mMarriageConfig;
	LK_ASSERT( tpMarriageConfig != NULL, return ) 
	int tWeddingHallMapID = tpMarriageConfig->mWeddinInfo[tpMarriage->GetWeddingModule()].mWeddingHallMapID;
	int tPosX = tpMarriageConfig->mWeddinInfo[tpMarriage->GetWeddingModule()].mPosX;
	int tPosY = tpMarriageConfig->mWeddinInfo[tpMarriage->GetWeddingModule()].mPosY;
	
	// TODO::���͵�����
	CMapModule::GetSingleton().Teleport( CSceneLogic::GetSingleton().GetLineID(), tWeddingHallMapID, tPosX, tPosY, pPlayer );
}

// ***********************************************************
//  Function:		OnTimeOutWeddingEnd
//  Description:	�������
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::OnTimeOutWeddingEnd( CTimerItem* pTimer )
{ 
	LK_ASSERT( pTimer != NULL, return );
	
	// ��������			
	EndWedding();
		
	//  ���ټ�ʱ��
	CMarriageManager::GetSingleton().ClearAllWeddingTime();
}

// ***********************************************************
//  Function:		EndWedding
//  Description:	��������
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::EndWedding()
{
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetCurrentWeddingInfo();
	if ( tpMarriageInfo == NULL )
	{
		//  ���ټ�ʱ��		
		return;
	}

	// ���û���״̬
	tpMarriageInfo->SetMarriageStatus( MARRIAGESTATUS_WEDDINGEND );	

	// �������Ӫ�����ڽ��еĻ���Ļ���ID
	CMarriageManager::GetSingleton().SetCurrentWeddingID( 0 );

	// ������ñ�
	CTemplateMarriageConfig *tpMarriageConfig =	( CTemplateMarriageConfig *	)CDataStatic::mMarriageConfig;
	if ( tpMarriageConfig == NULL )
	{
		LOG_ERROR( "marriage","[%d] can not find marriage templage config ",__LINE__ );	   					
		return;
	}
	
	SendWeddingEndNotify( tpMarriageInfo );

	// TODO:�������о��л���������˶����ͳ�ȥ
	CMapObject *tpMapObj = CMapObjManager::GetSingleton( ).GetMapObject( CSceneLogic::GetSingleton().GetLineID(), tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mWeddingHallMapID, INVALID_MAP_INDEX );
	LK_ASSERT( tpMapObj != NULL, return )	
	MapPlayerChecker tMapChecker;
	CWTPoint tTopLeft(0,0);
	CWTPoint tBottomRight(10000,10000);
	MapRegionEntitySearcher<MapPlayerChecker>	mSearcher( tMapChecker, tTopLeft, tBottomRight );
	mSearcher.Visit( tpMapObj );
	for ( int i = 0; i < tMapChecker.mNum; ++i )
	{
		if ( tMapChecker.mPlayerList[i] == NULL )
		{
			continue;
		}	 

		// ��ÿ���˴��������涼���ͳ�ȥ		
		CMapModule::GetSingleton().Teleport( (unsigned short)CSceneLogic::GetSingleton().GetLineID(), (unsigned short)tpMarriageConfig->mMapID, tpMarriageConfig->mPosX, tpMarriageConfig->mPosY, tMapChecker.mPlayerList[i] );
	}	

	ClearWeddingInfo( tpMarriageInfo );
	UpDateMarriageInfo( tpMarriageInfo );
}

// ***********************************************************
//  Function:		OnTimeOutMarryApplyTimeOut
//  Description:	�������ʧЧ
//  Output:			
//  Date:	03/11/2010
// **********************************************************
void CMarriageModule::OnTimeOutMarryApplyTimeOut( CTimerItem* pTimer )
{	
	LK_ASSERT( pTimer != NULL, return )	
	CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( pTimer->mOwnerID );
	if ( tpMarriageInfo == NULL )
	{
		//LOG_ERROR( "marriage","[%d] can not find marriage info by objid:%d",__LINE__,pTimer->mOwnerID );
		CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );	
		return;
	}
	CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( tpMarriageInfo->GetGroomID() );
	
	//  ���ټ�ʱ��
	CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );	
}

// ***********************************************************
//  Function:		OnTimeWeddingNotify
//  Description:	���ͻ���֪ͨ
//  Output:			
//  Date:	03/01/2010
// **********************************************************
void CMarriageModule::OnTimeWeddingNotify( CTimerItem* pTimer )
{		
	LK_ASSERT( pTimer != NULL, return )
	CMarriageInfo *tpMarriage = CMarriageManager::GetSingleton().GetCurrentWeddingInfo(  );
	if ( tpMarriage == NULL )
	{
		CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );
		LOG_ERROR( "marriage","[%s,%d] can not find marriage info by id:%d ",__FUNCTION__,__LINE__, pTimer->mOwnerID );
		return;
	}
	
	if ( pTimer->mCalledNum == 0 )
	{
		CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );
	}	
	
	SendWeddingNotify( tpMarriage );	
	
	CEntity *tpNpcEntity = CSceneLogic::GetSingleton().GetEntity( tpMarriage->GetWeddingNpcID( 0 ) );
	if( tpNpcEntity != NULL )
	{
		CActivityModule::GetSingleton().SendThrowSugarNotify( tpNpcEntity );
	}
}

// ***********************************************************
//  Function:		OnTimeOutWeddingOnStreet
//  Description:	�������н���
//  Output:			
//  Date:	03/16/2010
// **********************************************************
void CMarriageModule::OnTimeOutWeddingOnStreet( CTimerItem* pTimer )
{  
	LK_ASSERT( pTimer != NULL, return )
	
	//  ���ټ�ʱ��
	CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );	
	CMarriageInfo *tpMarriage = CMarriageManager::GetSingleton().GetCurrentWeddingInfo();  	
	LK_ASSERT( tpMarriage != NULL, return );
	if ( tpMarriage->GetMarriageStatus() != MARRIAGESTATUS_WEDDINGONSTREET )
	{
		return;
	}
			
	ClearWeddingInfo( tpMarriage );
	InitialWeddingHall( tpMarriage );	
}	

// ***********************************************************
//  Function:		PlayerBaitang
//  Description:	��Ұ���
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::PlayerBaitang( CEntityPlayer *pPlayer, CEntity *pEntity )
{  
	LK_ASSERT( pPlayer != NULL && pEntity != NULL, return )	
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfo( pPlayer->GetMarriageID() );
	LK_ASSERT( tpMarriageInfo != NULL, return )
	CEntityPlayer *tpOtherPlayer = NULL;
	if ( pPlayer->GetCharID() == tpMarriageInfo->GetGroomID() )
	{
		tpOtherPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetBrideID() );
	}
	else
	{
		tpOtherPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetGroomID() );
	}
	
	if ( tpOtherPlayer == NULL )
	{  		
		return;
	}
	
	// TODO::�ж�����
	
	// ���Ͱ��õ�֪ͨ
	int tGroomEntityID = 0;
	int tBrideEntityID = 0;
	if ( tpMarriageInfo->GetGroomID() == pPlayer->GetCharID() )
	{
		tGroomEntityID = pPlayer->GetEntityID();
		tBrideEntityID = tpOtherPlayer->GetEntityID();
	}
	else
	{
		tGroomEntityID = tpOtherPlayer->GetEntityID();
		tBrideEntityID = pPlayer->GetEntityID();
	}
	SendBaitangNotify( tpOtherPlayer, tpMarriageInfo->GetGroomName(), tpMarriageInfo->GetBrideName(), tGroomEntityID, tBrideEntityID );
}

// ***********************************************************
//  Function:		PlayerGetMarriageInfo
//  Description:	��һ�ȡ�����Ϣ�б�
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::PlayerGetMarriageInfo( CEntityPlayer *pPlayer )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageGetCampMarriageInfoResponse tMsgGetMarriageInfo;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_GETCAMPMARRIAGEINFO );
	tMsgHead.set_msgpara( (int)&tMsgGetMarriageInfo );
	
	// ��ʼ��ʱ���б�	
	int tTimeNow = time( NULL ); 
	int tTimeTomorrow = tTimeNow + DAYSECOUNDS;
	int tTimeDayAfterTomorrow = tTimeNow + DAYSECOUNDS*2;	
	tm *tpLocalTime = NULL;
	CMarriageManager::SysWeddingTimeList *tpWeddingTimeInfo = CMarriageManager::GetSingleton().GetWeddingTimeInfoList( );	
	for ( CMarriageManager::SysWeddingTimeList::iterator it = tpWeddingTimeInfo->begin(); it != tpWeddingTimeInfo->end(); ++it )
	{
		PBMarriageInfo *tpMarriageInfoA = tMsgGetMarriageInfo.mutable_marriagelista()->add_marriageinfo();					
		tpMarriageInfoA->set_timeid( it->first );	
		tpMarriageInfoA->set_weddingtime( (it->second).mBeginTime );
		tpMarriageInfoA->set_weddingendtime( (it->second).mEndTime );
		tpMarriageInfoA->set_commoallowed( (it->second).mCommonAllowed );
		
		PBMarriageInfo *tpMarriageInfoB = tMsgGetMarriageInfo.mutable_marriagelistb()->add_marriageinfo();					
		PBMarriageInfo *tpMarriageInfoC = tMsgGetMarriageInfo.mutable_marriagelistc()->add_marriageinfo();					
		
		tpMarriageInfoB->CopyFrom( *tpMarriageInfoA );
		tpMarriageInfoC->CopyFrom( *tpMarriageInfoA );		
		
		CMarriageInfo *tpMarriageInfo = NULL;
		tpLocalTime = localtime( (time_t*)&tTimeNow ); 
		tpLocalTime->tm_hour = (it->second).mBeginTime;
		tpLocalTime->tm_min	 = 0;
		tpLocalTime->tm_sec = 0;
		tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfoConfictedWithTime( mktime( tpLocalTime ),  ( (it->second).mEndTime - (it->second).mBeginTime )*3600 );
		
		if ( tpMarriageInfo != NULL )
		{
			tpMarriageInfoA->set_groomname( tpMarriageInfo->GetGroomName() );
			tpMarriageInfoA->set_bridename( tpMarriageInfo->GetBrideName() );
			tpMarriageInfoA->set_timeused( 1 );
		}
		
		tpMarriageInfo = NULL;
		tpLocalTime = localtime( (time_t*)&tTimeTomorrow );
		tpLocalTime->tm_hour = (it->second).mBeginTime;
		tpLocalTime->tm_min = 0;
		tpLocalTime->tm_sec = 0;
		tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfoConfictedWithTime( mktime( tpLocalTime ),  ( (it->second).mEndTime - (it->second).mBeginTime )*3600 );
		
		if ( tpMarriageInfo != NULL )
		{
			tpMarriageInfoB->set_groomname( tpMarriageInfo->GetGroomName() );
			tpMarriageInfoB->set_bridename( tpMarriageInfo->GetBrideName() );
			tpMarriageInfoB->set_timeused( 1 );
		}	
		
		tpMarriageInfo = NULL;
		tpLocalTime = localtime( (time_t*)&tTimeDayAfterTomorrow );
		tpLocalTime->tm_hour = (it->second).mBeginTime;
		tpLocalTime->tm_min = 0;
		tpLocalTime->tm_sec = 0;
		tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfoConfictedWithTime( mktime( tpLocalTime ),  ( (it->second).mEndTime - (it->second).mBeginTime )*3600 );

		if ( tpMarriageInfo != NULL )
		{
			tpMarriageInfoC->set_groomname( tpMarriageInfo->GetGroomName() );
			tpMarriageInfoC->set_bridename( tpMarriageInfo->GetBrideName() );
			tpMarriageInfoC->set_timeused( 1 );
		}												
	}	
	
	// ����ʱ��		
	tpLocalTime = localtime( (time_t*)&tTimeNow );
	tMsgGetMarriageInfo.mutable_marriagelista()->set_year( tpLocalTime->tm_year + 1900 );
	tMsgGetMarriageInfo.mutable_marriagelista()->set_month( tpLocalTime->tm_mon + 1 );
	tMsgGetMarriageInfo.mutable_marriagelista()->set_day( tpLocalTime->tm_mday );	

	tpLocalTime = localtime( (time_t*)&tTimeTomorrow );
	tMsgGetMarriageInfo.mutable_marriagelistb()->set_year( tpLocalTime->tm_year + 1900 );
	tMsgGetMarriageInfo.mutable_marriagelistb()->set_month( tpLocalTime->tm_mon + 1 );
	tMsgGetMarriageInfo.mutable_marriagelistb()->set_day( tpLocalTime->tm_mday );	
	
	
	tpLocalTime = localtime( (time_t*)&tTimeDayAfterTomorrow );
	tMsgGetMarriageInfo.mutable_marriagelistc()->set_year( tpLocalTime->tm_year + 1900 );
	tMsgGetMarriageInfo.mutable_marriagelistc()->set_month( tpLocalTime->tm_mon + 1 );
	tMsgGetMarriageInfo.mutable_marriagelistc()->set_day( tpLocalTime->tm_mday );		
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		PlayerPutKeepsake
//  Description:	��ҷ������������
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::PlayerPutKeepsake( CEntityPlayer *pPlayer, int nKeepSeekIndex )
{
	LK_ASSERT( pPlayer != NULL, return )	
	
	// ��ȡ������Ϣ
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfo( pPlayer->GetMarriageID() );
	if ( tpMarriageInfo == NULL )
	{
		SendPutKeepsakeResponse( pPlayer, EM_MARRIAGE_EXCHANGEKEEPSAKE_NOTMARRIED, nKeepSeekIndex );
		return;
	}   
	
	// ��ȡģ����Ϣ		
	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	LK_ASSERT( tpMarriageConfig != NULL, return )	
	
	CEntityPlayer *tpSpouse = NULL;
	if( tpMarriageInfo->GetBrideID() == pPlayer->GetCharID() )
	{
		tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetGroomID() );
	}
	else
	{
		tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetBrideID() );
	}	
	
	if( tpSpouse == NULL )
	{
		SendPutKeepsakeResponse( pPlayer, EM_MARRIAGE_PUTKEEPSAKE_SPOUSEOFFLINE, nKeepSeekIndex );
		return;
	}			

	//if ( tpMarriageInfo->GetMarriageStatus() != MARRIAGESTATUS_WEDDINGONHALL )
	//{
	//	SendPutKeepsakeResponse( pPlayer, EM_MARRIAGE_PUTKEEPSAKE_NOTINHALL );
	//	return;
	//}
	//
	//// ������ڻ������������ܽ��иò���
	//if ( pPlayer->GetMapID() != tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mWeddingHallMapID )
	//{
	//	SendPutKeepsakeResponse( pPlayer, EM_MARRIAGE_PUTKEEPSAKE_WEDDINGNOTHOLD );
	//	return;
	//}	
	
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	int tOldIndex =  tpMarriageInfo->GetKeepsakeIndex( pPlayer->GetSex() );
	if ( nKeepSeekIndex == -1 )
	{
		tpProperty->GetBaggage()->Lock( tOldIndex, LOCKTYPE_NONE );		
		tpMarriageInfo->SetKeepsakeIndex( nKeepSeekIndex, pPlayer->GetSex() );
		tpMarriageInfo->SetKeepsakeStatus( KEEPSAKSTATUS_EMPTY, pPlayer->GetSex() );
		CPropertyModule::GetSingleton().SendLockItemNotice( pPlayer, tOldIndex, LOCKTYPE_NONE ); 
		return;
	}
	
	CItemObject *tpItemObject = tpProperty->GetBaggage()->GetItemObjPtr( nKeepSeekIndex );
	if ( tpItemObject == NULL )
	{
		LOG_ERROR( "marriage","empty keepsake, roleid:%d, keepsakeindex:%d", pPlayer->GetCharID(), nKeepSeekIndex );
		return;
	} 
	
	// ����з�������
	bool tValideKeepsake = false;
	if ( pPlayer->GetSex() == 2 )
	{			
		for ( int i = 0; i < ( int )ARRAY_CNT( tpMarriageConfig->mMaleKeepsakeInfo ); ++i )
		{
			if ( tpMarriageConfig->mMaleKeepsakeInfo[i].mKeepsakeID == (int)tpItemObject->GetItemID() )
			{		
				tValideKeepsake = true;																				
				break;
			}
		}
	}
	else
	{
		for ( int i = 0; i < ( int )ARRAY_CNT( tpMarriageConfig->mFemaleKeepsakeInfo ); ++i )
		{
			if ( tpMarriageConfig->mFemaleKeepsakeInfo[i].mKeepsakeID == (int)tpItemObject->GetItemID() )
			{		
				tValideKeepsake = true;																				
				break;
			}
		}
	}
	
	if ( tValideKeepsake == false )
	{
		SendPutKeepsakeResponse( pPlayer, EM_MARRIAGE_PUTKEEPSAKE_WRONGKEEPSAKE, nKeepSeekIndex );
		return;			
	}
	
	if ( tOldIndex >= 0 )
	{
		tpProperty->GetBaggage()->Lock( tOldIndex, LOCKTYPE_NONE );
		CPropertyModule::GetSingleton().SendLockItemNotice( pPlayer, tOldIndex, LOCKTYPE_NONE );
	}
	
	tpMarriageInfo->SetKeepsakeIndex( nKeepSeekIndex, pPlayer->GetSex() );
	tpProperty->GetBaggage()->Lock( nKeepSeekIndex, LOCKTYPE_KEEPSAKE );
	tpMarriageInfo->SetKeepsakeStatus( KEEPSAKESTATUS_PUT, pPlayer->GetSex() );
	CPropertyModule::GetSingleton().SendLockItemNotice( pPlayer, nKeepSeekIndex, LOCKTYPE_KEEPSAKE );
	SendPutKeepsakeResponse( pPlayer, SUCCESS, nKeepSeekIndex );
}

// ***********************************************************
//  Function:		PlayerExchangeKeepsake
//  Description:	�������������
//  Output:			
//  Date:	03/03/2010
// **********************************************************
void CMarriageModule::PlayerExchangeKeepsake( CEntityPlayer *pPlayer )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfo( pPlayer->GetMarriageID() );
	if ( tpMarriageInfo == NULL )
	{
		//LOG_ERROR( "marriage","can not find marriage info by id:%d, roleid:%d", pPlayer->GetMarriageID(), pPlayer->GetCharID() );
		SendExchangeKeepsakeResponse( pPlayer, EM_MARRIAGE_EXCHANGEKEEPSAKE_NOTMARRIED );
		return;
	}
	
	/*if ( tpMarriageInfo->GetMarriageStatus() != MARRIAGESTATUS_WEDDINGONHALL )
	{
		return;
	}*/
	
	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	LK_ASSERT( tpMarriageConfig != NULL, return )  
		
	// ������ڻ������������ܽ��иò���
	/*if ( pPlayer->GetMapID() != tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mWeddingHallMapID )
	{
		return;
	}*/
	
	tpMarriageInfo->SetKeepsakeStatus( KEEPSAKESTATUS_EXCHANGE, pPlayer->GetSex() );
	
	CEntityPlayer *tpGroom = NULL;
	CEntityPlayer *tpBride = NULL;
	if ( pPlayer->GetCharID() == tpMarriageInfo->GetGroomID() )
	{
		tpGroom = pPlayer;
		tpBride = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetBrideID() );
	}
	else
	{
		tpBride = pPlayer;
		tpGroom = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetGroomID() );
	}
	
	if ( tpGroom == NULL || tpBride == NULL )
	{
		SendExchangeKeepsakeResponse(  pPlayer, EM_MARRIAGE_EXCHANGEKEEPSAKE_NEWLYOFFLINE );
		return;
	}
	
	if ( tpMarriageInfo->GetGroomKeepsakeIndex() < 0 || tpMarriageInfo->GetBrideKeepsakeIndex() < 0 )
	{
		SendExchangeKeepsakeResponse(  pPlayer, EM_MARRIAGE_EXCHANGEKEEPSAKE_EMPTYKEEPSAKE );
		return;
	}		
	
	SendExchangeKeepsakeResponse(  pPlayer, SUCCESS );
	
	if ( tpMarriageInfo->GetGroomKeepsakeStatus() != KEEPSAKESTATUS_EXCHANGE || tpMarriageInfo->GetBrideKeepsakeStatus() != KEEPSAKESTATUS_EXCHANGE )
	{	
		return;
	}			
	
	// ���Խ���
	CPropertyPlayer *tpGroomProperty = ( CPropertyPlayer * )tpGroom->GetProperty();
	CPropertyPlayer *tpBrideProperty = ( CPropertyPlayer * )tpBride->GetProperty();
	CItemObject *tpGroomKeepsake = tpGroomProperty->GetBaggage()->GetItemObjPtr( tpMarriageInfo->GetGroomKeepsakeIndex() );
	CItemObject *tpBrideKeepsake = tpBrideProperty->GetBaggage()->GetItemObjPtr( tpMarriageInfo->GetBrideKeepsakeIndex() );
	if ( tpGroomKeepsake == NULL || tpBrideKeepsake == NULL )
	{
		return;
	}
	
	// �ҵ���������ɵ�����ID  
	int tGroomRingID = 0;
	int tBrideRingID = 0;
	for ( int i = 0; i < ( int )ARRAY_CNT( tpMarriageConfig->mMaleKeepsakeInfo ); ++i )
	{
		if ( tpMarriageConfig->mMaleKeepsakeInfo[i].mKeepsakeID == (int)tpGroomKeepsake->GetItemID() )
		{		
			tGroomRingID = tpMarriageConfig->mMaleKeepsakeInfo[i].mEquipID;																				
			break;
		}
	}
	
	for ( int i = 0; i < ( int )ARRAY_CNT( tpMarriageConfig->mFemaleKeepsakeInfo ); ++i )
	{
		if ( tpMarriageConfig->mFemaleKeepsakeInfo[i].mKeepsakeID == (int)tpBrideKeepsake->GetItemID() )
		{		
			tBrideRingID = tpMarriageConfig->mFemaleKeepsakeInfo[i].mEquipID;																				
			break;
		}
	}
	
	if ( tGroomRingID == 0 || tBrideRingID == 0 )
	{
		return;
	}
	
	// ����Ľ�ָ
	CTplItem *tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tBrideRingID );
	if ( tpTplItem == NULL )
	{
		LOG_ERROR( "marriage","[%d] can not find item template by id:%d ",__LINE__, tBrideRingID );
		return;			
	}
	
	if ( tpTplItem->mItemType != CTplItem::ITEM_ARMOR && tpTplItem->mItemType != CTplItem::ITEM_WEAPON )
	{	
		LOG_ERROR( "marriage","[%d] item is not marriage item id:%d ",__LINE__, tBrideRingID );		
		return;
	}
	
	if ( ( (CTemplateEquipment *) tpTplItem )->mEquipType != CTemplateEquipment::PART_MARRY )
	{
		LOG_ERROR( "marriage","[%d] item is not marriage item id:%d ",__LINE__, tBrideRingID );		
		return;
	}
	
	CItemObject *tpBrideItem = NULL;
	int tResult = CPropertyModule::GetSingleton().CreateItem( tpTplItem, 1, 0, &tpBrideItem );
	if ( tResult != SUCCESS || tpBrideItem == NULL )
	{
		LOG_ERROR( "marriage"," creat marriage item error, tmpid:%d, roleid:%d ", tBrideRingID, tpBride->GetCharID() );
		return;
	}
	
	// ����Ľ�ָ
	tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tGroomRingID );
	if ( tpTplItem == NULL )
	{
		LOG_ERROR( "marriage","[%d] can not find item template by id:%d ",__LINE__, tGroomRingID );
		return;			
	}

	if ( tpTplItem->mItemType != CTplItem::ITEM_ARMOR && tpTplItem->mItemType != CTplItem::ITEM_WEAPON )
	{	
		LOG_ERROR( "marriage","[%d] item is not marriage item id:%d ",__LINE__, tGroomRingID );		
		return;
	}

	if ( ( (CTemplateEquipment *) tpTplItem )->mEquipType != CTemplateEquipment::PART_MARRY )
	{
		LOG_ERROR( "marriage","[%d] item is not marriage item id:%d ",__LINE__, tGroomRingID );		
		return;
	}

	CItemObject *tpGroomItem = NULL;
	tResult = CPropertyModule::GetSingleton().CreateItem( tpTplItem, 1, 0, &tpGroomItem );
	if ( tResult != SUCCESS || tpGroomItem == NULL )
	{
		LOG_ERROR( "marriage"," creat marriage item error, tmpid:%d, roleid:%d ", tGroomRingID, tpGroom->GetCharID() );
		return;
	}	
	
	// ������Ϣ
	( ( CItemEquipment * ) tpBrideItem )->SetSpouseID( tpBride->GetCharID() );
	( ( CItemEquipment * )tpBrideItem )->SetSpouseName( tpBride->GetCharName() );
	
	( ( CItemEquipment * )tpGroomItem )->SetSpouseID( tpGroom->GetCharID() );
	( ( CItemEquipment * )tpGroomItem )->SetSpouseName( tpGroom->GetCharName() );
	
	// ��������
	CPropertyModule::GetSingleton().PlayerRemoveItem( tpGroom, tpMarriageInfo->GetGroomKeepsakeIndex(), 1 );
	CPropertyModule::GetSingleton().PlayerRemoveItem( tpBride, tpMarriageInfo->GetBrideKeepsakeIndex(), 1 );
	
	CPropertyModule::GetSingleton().PlayerInsertItem( tpGroom, tpBrideItem, false, false );
	CPropertyModule::GetSingleton().PlayerInsertItem( tpBride, tpGroomItem, false, false );	
	/*CItemObject *tpGroomRing = CPropertyModule::GetSingleton().PlayerInsertItem( tpGroom, tBrideRingID, 1 );
	CItemObject *tpBrideRing = CPropertyModule::GetSingleton().PlayerInsertItem( tpBride, tGroomRingID, 1 );
	*/
	tpMarriageInfo->SetGroomKeepsakeIndex( -1 );
	tpMarriageInfo->SetBrideKeepsakeIndex( -1 );
	
	if ( tpMarriageInfo->GetMarriageStatus() == MARRIAGESTATUS_WEDDINGONHALL )
	{
		SendKeepsakeExchangeResultNotify( tpMarriageInfo, tGroomRingID, tBrideRingID );
	}
	else
	{
		SendKeepsakeExchangeResultNotify( tpMarriageInfo, tGroomRingID, tBrideRingID, tpBride );
		SendKeepsakeExchangeResultNotify( tpMarriageInfo, tGroomRingID, tBrideRingID, tpGroom );	
	}	
}

// ***********************************************************
//  Function:		PlayerDivoce
//  Description:	�����������
//  Output:			
//  Date:	03/03/2010
// **********************************************************
void CMarriageModule::PlayerDivorce( CEntityPlayer *pPlayer )
{	 
	LK_ASSERT( pPlayer != NULL, return )	
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfo( pPlayer->GetMarriageID() );
	if ( tpMarriageInfo == NULL )
	{
		LOG_ERROR( "marriage","[%s,%d] can not find marriage info by id:%d, roleid:%d ",__FUNCTION__, __LINE__, pPlayer->GetMarriageID(), pPlayer->GetCharID() );
		SendVivorceResponse( pPlayer, EM_MARRIAGE_DIVOCE_NOMARRIAGE );
		return;
	}
	
	// �жϽ��״̬
	if ( tpMarriageInfo->GetMarriageStatus() == MARRIAGESTATUS_WEDDINGONSTREET || tpMarriageInfo->GetMarriageStatus() == MARRIAGESTATUS_WEDDINGONHALL )
	{
		SendVivorceResponse( pPlayer, EM_MARRIAGE_DIVORCE_ONWEDDING );
		return;
	}
	
	int tSpouseID = 0;
	if ( pPlayer->GetCharID() == tpMarriageInfo->GetGroomID() )
	{
		tSpouseID = tpMarriageInfo->GetBrideID();
	}
	else
	{
		tSpouseID = tpMarriageInfo->GetGroomID();
	}	
	
	// ��ȡ�����Ϣ���ñ�
	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	LK_ASSERT( tpMarriageConfig != NULL, return )	
	
	// ������������û��������	
	bool tBind = false;
	uint64_t tGuID = 0;
	int tRet = CPropertyModule::GetSingleton().PlayerRemoveItemByID( pPlayer, tpMarriageConfig->mDivorceItemID, 1, tBind, &tGuID );
	if ( tRet != SUCCESS )
	{		
		SendVivorceResponse( pPlayer, EM_MARRIAGE_DIVOCE_HASNODOVICEITEM );
		LogEventLostItemByUse( pPlayer, tGuID, tpMarriageConfig->mDivorceItemID, 1 );
		return;
	}  	
	
	// ȥ�����޳ƺ�
	CPropertyModule::GetSingleton().OnPlayerDelTitleEvent( pPlayer, tpMarriageConfig->mMarriageTitleID );	
	
	// ɾ��������ݿ���Ϣ
	DeleteMarriageDBInfo( tpMarriageInfo );	  	
	
	// ���Է���������֪ͨ
	CEntityPlayer *tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tSpouseID );
	if ( tpSpouse != NULL )
	{	
		LOG_INFO( "marriage","[%d] Player ( roleid:%d ) chanage marriageid :%d to 0 ", __LINE__, tpSpouse->GetCharID(), tpSpouse->GetMarriageID() );
		tpSpouse->SetMarriageID( 0 );		
		BroadCastDivorce( tpSpouse, tpMarriageInfo->GetGroomName(), tpMarriageInfo->GetBrideName(), tpMarriageInfo->GetGroomID(), tpMarriageInfo->GetBrideID() );				
		CPropertyModule::GetSingleton().OnPlayerDelTitleEvent( tpSpouse, tpMarriageConfig->mMarriageTitleID );			
	}																																								
	else
	{
		SendDivorceNotify( pPlayer, tSpouseID );
	}	
	
	// ������ҵĽ��ID
	LOG_INFO( "marriage","[%d] Player ( roleid:%d ) chanage marriageid :%d to 0  because of divorce", __LINE__, pPlayer->GetCharID(), pPlayer->GetMarriageID() );
	pPlayer->SetMarriageID( 0 );
	
	// �ı���ѵ����ܶ�
	CFriendModule::GetSingleton().ChangeIntimacy( tpMarriageInfo->GetBrideID(), tpMarriageInfo->GetGroomID(), ENTIMACY_CHANGE_TYPE_DIVORCE
		, CFriendModule::GetSingleton().GetFriendBlessConfig()->GetIntimacyConfig()->mDivorceReduced );

	// ɾ�������ϵ���һ�����Ϣ
	CMarriageManager::GetSingleton().DeleteMarriageInfo( tpMarriageInfo->GetServerSequence() );	
	
	SendVivorceResponse( pPlayer, SUCCESS );
}

// ***********************************************************
//  Function:		PlayerCancelWedding
//  Description:	�������ȡ������
//  Output:			
//  Date:	04/12/2010
// **********************************************************
void CMarriageModule::PlayerCancelWedding( CEntityPlayer *pPlayer )
{
	
}

// ***********************************************************
//  Function:		UseSysInvitation
//  Description:	ʹ��ϵͳ����
//  Output:			
//  Date:	03/17/2010
// **********************************************************
void CMarriageModule::UseSysInvitation( CEntityPlayer *pPlayer, int nIndex, const char *pName )
{
	LK_ASSERT( pPlayer != NULL && pName != NULL, return )
	
	if ( pPlayer->GetMarriageID() == 0 )
	{
		SendUseSysInvitationResponse( pPlayer, EM_MARRIAGE_INVITATION_NOTMARRIED );
		return;
	}
	
	CEntityPlayer *tpPlayer = CSceneLogic::GetSingleton().GetPlayerByName( pName );
	if ( tpPlayer == NULL )
	{
		CMessage tMsgHead;
		CMessageGetPlayerMailiInfoRequest MsgRoleInfo;	
		MsgRoleInfo.set_charid( pPlayer->GetCharID() );	
		MsgRoleInfo.set_rolename( pName );
		MsgRoleInfo.set_queryway( 0 );
		MsgRoleInfo.set_querytype( ROLEQUERYTYPE_MARRIAGEINVITATION );
		MsgRoleInfo.add_querydata( nIndex );
		tMsgHead.mutable_msghead( )->set_messageid( ID_C2G_REQUEST_GETMAILINFO );
		tMsgHead.set_msgpara( (int)&MsgRoleInfo );
		CSceneLogic::GetSingletonPtr( )->Send2Gate( &tMsgHead );			
	}
	else
	{
		SendInvitationByMail( pPlayer, nIndex, tpPlayer->GetCharID(), tpPlayer->GetCharName() ); 
	}
}

// ***********************************************************
//  Function:		SendInvitationByMail
//  Description:	�����ͨ��ϵͳ�ʼ���������
//  Output:			
//  Date:	03/18/2010
// **********************************************************
void CMarriageModule::SendInvitationByMail( CEntityPlayer *pPlayer, int nSysInvitationIndex, int nRoleID, const char *pName )
{	
	LK_ASSERT( pPlayer != NULL && pName != NULL, return )	
	
	if ( pPlayer->GetMarriageID() == 0 )
	{
		SendUseSysInvitationResponse( pPlayer, EM_MARRIAGE_INVITATION_NOTMARRIED );	
		return;
	}
	
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfoByID( pPlayer->GetNationality(), pPlayer->GetMarriageID() );
	if ( tpMarriageInfo == NULL )
	{
		SendUseSysInvitationResponse( pPlayer, EM_MARRIAGE_INVITATION_NOTMARRIED );	
		return;
	}
	
	if ( tpMarriageInfo->GetWeddingTime() == 0 )
	{
		SendUseSysInvitationResponse( pPlayer, EM_MARRIAGE_INVITATION_NOTMARRIED );	
		return;
	}
	
	if ( (int)tpMarriageInfo->GetBrideID() == nRoleID || (int)tpMarriageInfo->GetGroomID() == nRoleID )
	{
		SendUseSysInvitationResponse( pPlayer, EM_MARRIAGE_INVITATION_SELFSEND );	
		return;
	}
		
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )	pPlayer->GetProperty();
	CItemObject *tpSysInvitation = ( CItemObject * )tpProperty->GetBaggage()->GetItemObjPtr( nSysInvitationIndex );
	if ( tpSysInvitation == NULL )
	{
		return;
	}
	
	CTplItem *tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tpSysInvitation->GetItemID() );
	if ( tpTplItem == NULL )
	{
		LOG_ERROR( "marriage","can not find invitation by tmpid:%d", tpSysInvitation->GetItemID() );
		return;
	}
	
	if ( tpTplItem->mItemType != CTplItem::ITEM_SYSINVITATION )
	{
		LOG_ERROR( "marriage","[%d]template is not sysinvitation, tmpid:%d", __LINE__, tpSysInvitation->GetItemID() );
		SendUseSysInvitationResponse( pPlayer, EM_MARRIAGE_INVITATION_NOTINVITATION );
		return;
	}	
	
	CTplSysInvitation *tpTplSysInvitation = ( CTplSysInvitation * )tpTplItem;
	tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tpTplSysInvitation->mInvitationID );
	if ( tpTplItem == NULL )
	{
		LOG_ERROR( "marriage","[%d]can not find invitation by tmpid:%d", __LINE__, tpTplSysInvitation->mInvitationID );
		return;
	}	
	
	if ( tpTplItem->mItemType != CTplItem::ITEM_INVITATION )
	{	
		LOG_ERROR( "marriage","[%d]template is not invitation, tmpid:%d", __LINE__, tpTplSysInvitation->mInvitationID );
		return;
	}
	
	CItemObject *tpItemObj = NULL;
	int tResult = CPropertyModule::GetSingleton().CreateItem( tpTplItem, 1, 0, &tpItemObj );
	if ( tResult != SUCCESS || tpItemObj == NULL )
	{
		LOG_ERROR( "marriage","[%d] creat invitation error, roleid:%d",__LINE__,pPlayer->GetCharID() );
		return;
	}	
	
	CItemInvitation *tpInvitaton = ( CItemInvitation * )tpItemObj;
	tpInvitaton->SetBrideName( tpMarriageInfo->GetBrideName() );
	tpInvitaton->SetGroomName( tpMarriageInfo->GetGroomName() );
	tpInvitaton->SetWeddingTime( tpMarriageInfo->GetWeddingTime() );
	tpInvitaton->SetWeddingTimeLength( tpMarriageInfo->GetWeddingTimeLength() );
	char tName[NAME_LENGTH] = { 0 };
	sprintf( tName,"%d", SYSMAIL_INVITATION_ID );
	CMailModule::GetSingleton().SendSysMail( pName, nRoleID, "", tName, "", &tpItemObj, 1, pPlayer->GetNationality() );
	CPropertyModule::GetSingleton().PlayerRemoveItem( pPlayer, nSysInvitationIndex, 1 );
	SendUseSysInvitationResponse( pPlayer, SUCCESS );
}

// ***********************************************************
//  Function:		GetSysWeddingTimeUsed
//  Description:	��ȡ��ռ�õ�ʱ�����Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
PBMarriageInfo *CMarriageModule::GetSysWeddingTimeUsed( CMarriageInfo *tpMarriageInfo, PBMarriageList &rTimeList, time_t nTime )
{
	if ( tpMarriageInfo == NULL )
	{
		return NULL;
	}
			
	for ( int i = 0; i < rTimeList.marriageinfo_size(); ++i )
	{
		int tTime = nTime;
		tm *tpLocalTime = localtime( (time_t*)&tTime );		
		int tBeginTime = rTimeList.mutable_marriageinfo( i )->weddingtime();
		int tEndTime = rTimeList.mutable_marriageinfo( i )->weddingendtime();
		tpLocalTime->tm_hour = tBeginTime;		
		tpLocalTime->tm_min = 0;
		tpLocalTime->tm_sec = 0;
		int tTimeLength = ( tEndTime - tBeginTime )*3600;
		tTime = mktime( tpLocalTime );
		if ( tpMarriageInfo->JudgeTimeValide( tTime, tTimeLength ) == false )
		{
			return rTimeList.mutable_marriageinfo( i );
		}
	}
	return NULL;
}	

// ***********************************************************
//  Function:		InitializeSysWeddingInfo
//  Description:	��ʼ��ϵͳ����ʱ��
//  Output:			
//  Date:	03/02/2010
// **********************************************************
int CMarriageModule::InitializeSysWeddingInfo( const char *pFileName )
{		
	CMarriageManager::GetSingleton().InitialWeddingTimeInfo( );
	LK_ASSERT( pFileName != NULL, return -1 )
	TiXmlDocument tDoc;	
	LK_ASSERT( tDoc.LoadFile( pFileName ), return -1 )
	TiXmlElement *tpRootElement = tDoc.RootElement();
	LK_ASSERT( tpRootElement != NULL, return -1 )				
	TiXmlElement *tpTimeInfo = tpRootElement->FirstChildElement( "WeddingInfo" );
	LK_ASSERT( tpTimeInfo != NULL, return -1 )	
	for ( ; tpTimeInfo != NULL; tpTimeInfo = tpTimeInfo->NextSiblingElement() )
	{	  
		CWeddingSysTime tSysTime;
		int tTimeID = atoi( tpTimeInfo->Attribute( "TimeID" ) );
		tSysTime.mBeginTime = atoi( tpTimeInfo->Attribute( "BeginTime" ) );
		tSysTime.mEndTime = atoi( tpTimeInfo->Attribute( "EndTime" ) );
		tSysTime.mCommonAllowed = atoi( tpTimeInfo->Attribute( "CommonAllowed" ) );
		CMarriageManager::GetSingleton().InsertSysWeddingTimeInfo( tTimeID, tSysTime );
	}	
	return SUCCESS;
}	

// ***********************************************************
//  Function:		InitializeWeddingNpcPath
//  Description:	��ʼ��npc���ƶ�·��
//  Output:			
//  Date:	03/03/2010
// **********************************************************
int CMarriageModule::InitializeWeddingNpcPath( const char *pFileName )
{
	 CMarriageManager::GetSingleton().InitialNpcPathInfo();
	 LK_ASSERT( pFileName != NULL, return -1 )
	 TiXmlDocument tDoc;
	 LK_ASSERT( tDoc.LoadFile( pFileName ), return -1 )

	 TiXmlElement *tpRoot = tDoc.RootElement();
	 LK_ASSERT( tpRoot != NULL, return -1 ) 	 
	 TiXmlElement *tpNpcElement = tpRoot->FirstChildElement( "NpcInfo" );	 
	 for ( ; tpNpcElement != NULL; tpNpcElement = tpNpcElement->NextSiblingElement() )
	 {
		CWeddingNpcPath tWeddingNpcPath;
		tWeddingNpcPath.mMapID		= atoi( tpNpcElement->Attribute( "MapID" ) );
		tWeddingNpcPath.mNpcTmpID	= atoi( tpNpcElement->Attribute( "NpcTempID" ) );
		tWeddingNpcPath.mMapIndex = atoi( tpNpcElement->Attribute( "MapIndex" ) );
		int tWeddingModule = atoi( tpNpcElement->Attribute( "WeddingModule" ) );
		TiXmlElement *tpPathElement = tpNpcElement->FirstChildElement( "Path" );
		int i = 0;
		for ( ; tpPathElement != NULL; tpPathElement = tpPathElement->NextSiblingElement() )
		{
			if ( i < (int)ARRAY_CNT( tWeddingNpcPath.mNpcPath ) )
			{
				tWeddingNpcPath.mNpcPath[i].mPosX = atoi( tpPathElement->Attribute( "x" ) );
				tWeddingNpcPath.mNpcPath[i].mPosY = atoi( tpPathElement->Attribute( "y" ) );
				tWeddingNpcPath.mNpcPath[i].mSynchMark = atoi( tpPathElement->Attribute( "synmark" ) );				
				++i;
			}		
		}
		CMarriageManager::GetSingleton().InsertNpcPath( tWeddingModule, tWeddingNpcPath );
	 }
	 return SUCCESS;
}	

// ***********************************************************
//  Function:		ClearWeddingInfo
//  Description:	�����ҵĻ�����Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
int CMarriageModule::ClearWeddingInfo( CMarriageInfo *pMarriage )
{	
	LK_ASSERT( pMarriage != NULL, return -1 )
	
	// ������Ӧ��npc
	for ( int i = 0; i < MAX_WEDDING_NPCNUM; ++i )
	{
		if ( pMarriage->GetWeddingNpcID( i ) == 0 )
		{
			continue;
		}
		CEntityFuncNpc *tpEntity = ( CEntityFuncNpc * )CSceneLogic::GetSingleton().GetEntity( pMarriage->GetWeddingNpcID( i ) );
		if ( tpEntity == NULL )
		{
			continue;
		}	
		CSceneLogic::GetSingleton().DestroyEntity( tpEntity, 0 );
	}
	
	return SUCCESS;
}    

// ***********************************************************
//  Function:		CreatMarriageDBInfo
//  Description:	������������ݿ���Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::CreatMarriageDBInfo( CMarriageInfo *tpMarriageInfo )
{	
	LK_ASSERT( tpMarriageInfo != NULL, return )	
	const char *tpSql = "insert UMS_MARRIAGE( groom_id, bride_id, groom_name, bride_name, marriage_status, wedding_time, wedding_timelength, camp_sequence, camp_id, marriage_time, wedding_module ) \
	 value( %d,%d,'%s','%s',%d,%d,%d,%d,%d,%d,%d ) ";
	CSceneLogic::GetSingleton().ExecuteSql( session_creatmarriageinfo, tpMarriageInfo->get_id(), 0, tpMarriageInfo->GetGroomID(), SQL_NEED_CALLBACK | SQL_LATEST_INC_ID, INSERT, 
		tpSql, tpMarriageInfo->GetGroomID(), tpMarriageInfo->GetBrideID(), tpMarriageInfo->GetGroomName(), tpMarriageInfo->GetBrideName(), tpMarriageInfo->GetMarriageStatus(), 
		tpMarriageInfo->GetWeddingTime(), tpMarriageInfo->GetWeddingTimeLength(), tpMarriageInfo->GetCampSequence(), tpMarriageInfo->GetCampID(), time(NULL), tpMarriageInfo->GetWeddingModule() );
}

// ***********************************************************
//  Function:		OnSessionCreatMarriageDBInfo
//  Description:	�����������ݿ���Ϣ�ķ�����Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::OnSessionCreatMarriageDBInfo( CMessage *pMessage, int nParam1, int nParam2 )
{  
	LK_ASSERT( pMessage != NULL, return )		
	CMessageExecuteSqlResponse3 *tpResponseMsg = ( CMessageExecuteSqlResponse3 * )pMessage->msgpara();
	if ( tpResponseMsg == NULL )
	{
		return;
	}
	
	CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( nParam1 );
	LK_ASSERT( tpMarriageInfo != NULL, return )
		
	if ( tpResponseMsg->resultcode() != 1 )
	{
		//CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( tpMarriageInfo->GetGroomID() );	
		LOG_ERROR( "marriage","[%s,%d] creat marriagedbinfo wrong, groomid:%d, brideid:%d",__FUNCTION__,__LINE__,tpMarriageInfo->GetGroomID(), tpMarriageInfo->GetBrideID() );
		CSceneObjManager::GetSingleton().DestroyObject( tpMarriageInfo->get_id() );		
		return;
	}	
	
	// ɾ��������Ϣ
	//CMarriageManager::GetSingleton().DeleteMarriageApplyInfo( tpMarriageInfo->GetGroomID() );			
	
	// ������˫�����û���ID		
	CEntityPlayer *tpGroom = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetGroomID() );
	if ( tpGroom != NULL )
	{
		tpGroom->SetMarriageID( tpResponseMsg->latestautoincid() );
		
	}
	else
	{
		LOG_ERROR( "marriage","player roleid:%d offline when set marriageid:%d", tpMarriageInfo->GetGroomID(), tpResponseMsg->latestautoincid() );
	}
	
	CEntityPlayer *tpBride = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetBrideID() );
	if ( tpBride != NULL )
	{
		tpBride->SetMarriageID( tpResponseMsg->latestautoincid() );
	}
	else
	{
		LOG_ERROR( "marriage","player roleid:%d offline when set marriageid:%d", tpMarriageInfo->GetGroomID(), tpResponseMsg->latestautoincid() );
	}
	
	// ���뵽��������	
	CMarriageManager::GetSingleton().InsertMarriageInfo( tpResponseMsg->latestautoincid(), tpMarriageInfo );	
	
	// ���ͽ��ɹ�����Ϣ
	SendNewlyMarriedNotify( tpMarriageInfo );
	
	if ( tpBride != NULL )
	{
		CSceneLogic::GetSingleton().SavePlayer( tpBride, SAVE_TIMETRIGER );
	}
	
	if ( tpGroom != NULL )
	{
		CSceneLogic::GetSingleton().SavePlayer( tpGroom, SAVE_TIMETRIGER );
	}
	
	LOG_INFO( "marriage"," groom( roleid:%d ) and bride( roleid:%d ) marry sucess, marriageid:%d  ", tpMarriageInfo->GetGroomID(), tpMarriageInfo->GetBrideID(), tpResponseMsg->latestautoincid() );				
}

// ***********************************************************
//  Function:		CheckWeddingStatus
//  Description:	������״̬
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::CheckWeddingStatus( )
{ 
	CMarriageManager::MarriageInfoList &tpMarriageList = CMarriageManager::GetSingleton().GetMarriageInfoList();	
	for ( CMarriageManager::MarriageInfoList::iterator it = tpMarriageList.begin(); it != tpMarriageList.end(); ++it )
	{
		CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().GetObject( it->second );
		if ( tpMarriageInfo == NULL )
		{
			continue;
		}			
		
		switch ( tpMarriageInfo->GetWeddingStatus() )
		{
			case WEDDINGSTATUS_NOTSET:
			{
				break;	
			}
			
			case WEDDINGSTATUS_TIMENEAR:
			{					
				if ( !( tpMarriageInfo->GetWeddingEventStatus() & EVENT_WEDDINGNOTIFY ) )
				{
					tpMarriageInfo->SetWeddingEventStatus( tpMarriageInfo->GetWeddingEventStatus() | EVENT_WEDDINGNOTIFY );
					SendMarriageTipsNotify( tpMarriageInfo );					
				}				
				break;
			}
			
			case WEDDINGSTATUS_INTIME:
			{
				if ( !( tpMarriageInfo->GetWeddingEventStatus() & EVENT_WEDDINGINTIMENOTIFY ) )
				{											
					tpMarriageInfo->SetWeddingEventStatus( tpMarriageInfo->GetWeddingEventStatus() | EVENT_WEDDINGINTIMENOTIFY );
					SendMarriageTipsNotify( tpMarriageInfo );
					
				}			
				break;
			}
			
			case WEDDINGSTATUS_EXPIRED:
			{
				if ( tpMarriageInfo->GetMarriageStatus() != MARRIAGESTATUS_WEDDINGEND && 
					tpMarriageInfo->GetServerSequence() != CMarriageManager::GetSingleton().GetCurrentWeddingID() )
				{
					tpMarriageInfo->SetMarriageStatus( MARRIAGESTATUS_WEDDINGFAILED );	
					UpDateMarriageInfo( tpMarriageInfo );
					LOG_INFO( "marriage","wedding info expired, marriageid:%d, weddingtime:%d, time:%d ", tpMarriageInfo->GetServerSequence(), 
						tpMarriageInfo->GetWeddingTime( ), time(NULL) );
				}
				break;	
			}
				
			case WEDDINGSTATUS_NOTINTIME:
			{
				break;	
			}
			
			case WEDDINGSTATUS_FINISHED:
			{
				break;
			}
			default:
				break;
		}
	}
}

// ***********************************************************
//  Function:		CheckWeddingNpc
//  Description:	������npc���ƶ����
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::CheckWeddingNpc(  )
{	
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton( ).GetCurrentWeddingInfo( );
	if ( tpMarriageInfo == NULL )
	{	 
		return;
	}
	
	if ( tpMarriageInfo->GetMarriageStatus() != MARRIAGESTATUS_WEDDINGONSTREET )
	{
		return;
	}
	
	// �Ƿ����е�npc���Ѿ��ƶ���ָ��λ��
	bool tNpcAllReached = true;		  	
	for ( int i = 0; i < MAX_WEDDING_NPCNUM; ++i )
	{		
		if ( tpMarriageInfo->GetWeddingNpcID( i ) == 0 )
		{
			tpMarriageInfo->SetSynchMark( i, -1 );		
			continue;
		}
		CEntityFuncNpc *tpEntity = ( CEntityFuncNpc * )CSceneLogic::GetSingleton().GetEntity( tpMarriageInfo->GetWeddingNpcID( i ) );
		if ( tpEntity == NULL )
		{
			tpMarriageInfo->SetWeddingNpcID( i, 0 );
			tpMarriageInfo->SetSynchMark( i, -1 );		
			continue;
		}			
		CNpcModule::GetSingletonPtr()->OnSleep( tpEntity, false );
				
		bool tReachEnd = false;
		bool tStepComplete = CMarriageManager::GetSingleton().CheckNpcPos( tpMarriageInfo->GetWeddingNpcPosIndex( i ), tpMarriageInfo->GetWeddingModule(), i,
		tpEntity->GetPosX(), tpEntity->GetPosY(), tReachEnd ); 	
				
		if ( tReachEnd == true )
		{
			tpMarriageInfo->SetWeddingNpcID( i, 0 );
			CSceneLogic::GetSingleton().DestroyEntity( tpEntity, 0 );
			tpMarriageInfo->SetSynchMark( i, -1 );		
		}
		else
		{				
			if ( tStepComplete == true )
			{
				CNpcPos tPos;
				CMarriageManager::GetSingleton().GetNpcMovePos( tpMarriageInfo->GetWeddingModule(), i, tpMarriageInfo->GetWeddingNpcPosIndex(i), tPos ); 				
								
				// �����ǰλ����Ҫͬ������ֻ�ܵ�����npc������ͬ����֮����ܼ����ƶ�
				bool tCanMoveOn = true;					 						
				tpMarriageInfo->SetSynchMark( i, tPos.mSynchMark );		
												
				// ���µ�ͬ����
				if ( tPos.mSynchMark > tpMarriageInfo->GetWaitSynMark() )
				{
					tpMarriageInfo->SetWaitSynMark( tPos.mSynchMark );
				}  									
						
				if ( tPos.mSynchMark == tpMarriageInfo->GetWaitSynMark() && tpMarriageInfo->GetWaitSynMark() > 0 )
				{
					tCanMoveOn = tpMarriageInfo->CheckSynchMark();
					if ( tCanMoveOn == true )
					{								
						tpMarriageInfo->SetWaitSynMark( tpMarriageInfo->GetWaitSynMark() + 1 );
					}
				}						
									
				if ( tCanMoveOn == true )
				{						
					CNpcPos tPos;
					int tRet = CMarriageManager::GetSingleton().GetNpcMovePos( tpMarriageInfo->GetWeddingModule(), i, tpMarriageInfo->GetWeddingNpcPosIndex(i) + 1, tPos ); 
					if ( tRet == -1 )
					{
						CSceneLogic::GetSingleton().DestroyEntity( tpEntity, 0 );
						tpMarriageInfo->SetWeddingNpcID( i, 0 );	
						tpMarriageInfo->SetSynchMark( i, -1 );			
					}
					else
					{
						tpEntity->SetOrginPos( CWTPoint( tPos.mPosX, tPos.mPosY ) );		
						CNpcModule::GetSingleton().OnMoveNpc( tpEntity->GetEntityID(), tPos.mPosX, tPos.mPosY );				
						tpMarriageInfo->SetWeddingNpcPosIndex( i, tpMarriageInfo->GetWeddingNpcPosIndex( i ) + 1 );	
					}						
				}			
																
			}			
			tNpcAllReached = false;
		}
	}			
	
	if ( tNpcAllReached == true )
	{
		InitialWeddingHall( tpMarriageInfo );
	}
}

// ***********************************************************
//  Function:		CreatWeddingInfo
//  Description:	��������������Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::CreatWeddingInfo( CMarriageInfo *pMarriageInfo )
{
	
}

// ***********************************************************
//  Function:		InitialWeddingHall
//  Description:	��ʼ������
//  Output:			
//  Date:	04/13/2010
// **********************************************************
void CMarriageModule::InitialWeddingHall( CMarriageInfo *tpMarriageInfo )
{
	LK_ASSERT( tpMarriageInfo != NULL, return );
	
	if( tpMarriageInfo->GetMarriageStatus() != MARRIAGESTATUS_WEDDINGONSTREET )
	{	
		return;
	} 	  
	
	// �������֪ͨ��ʱ��
	CMarriageManager::GetSingleton().ClearWeddingTimer( TIMER_WEDDINGNOTIFY );			
	
	// ���Խ�������
	tpMarriageInfo->SetMarriageStatus( MARRIAGESTATUS_WEDDINGONHALL );

	// ���»���״̬��Ϣ
	UpDateMarriageInfo( tpMarriageInfo );

	// �����˷��ͽ������õ�֪ͨ
	CEntityPlayer *tpGroom = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetGroomID() );
	if ( tpGroom != NULL )
	{
		SendEnterMarriageHallNotify( tpGroom );
	}

	CEntityPlayer *tpBride = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetBrideID() );
	if ( tpBride != NULL )
	{
		SendEnterMarriageHallNotify( tpBride );
	}

	// ���������ڵ�
	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	if ( tpMarriageConfig == NULL )
	{
		return;
	}

	CMapObject *tpMapObj = CMapObjManager::GetSingleton( ).GetMapObject( CSceneLogic::GetSingleton().GetLineID(), tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mWeddingHallMapID, INVALID_MAP_INDEX );
	LK_ASSERT( tpMapObj != NULL, return )		

		CWTPoint tTopLeft(0,0);
	CWTPoint tBottomRight(10000,10000);
	MapFuncNpcChecker tMapChecker;
	MapRegionEntitySearcher<MapFuncNpcChecker>	mSearcher( tMapChecker, tTopLeft, tBottomRight );
	mSearcher.Visit( tpMapObj );

	if ( tMapChecker.mEntityID != 0 )
	{
		CEntity *tpEntity = CSceneLogic::GetSingleton().GetEntity( tMapChecker.mEntityID );
		if ( tpEntity != NULL )
		{
			CPropertyModule::GetSingleton().StartRedstone( tpEntity, CSceneLogic::GetSingleton().GetLineID(), tpMarriageConfig->mWeddinInfo[tpMarriageInfo->GetWeddingModule()].mWeddingHallRedstoneID, false );				
		}
	}			
}

// ***********************************************************
//  Function:		SendWeddingEndNotify
//  Description:	���ͻ��������֪ͨ
//  Output:			
//  Date:	04/13/2010
// **********************************************************
void CMarriageModule::SendWeddingEndNotify( CMarriageInfo *pMarriageInfo )
{  
	LK_ASSERT( pMarriageInfo != NULL, return )	
	CMessage tMsgHead;
	CMessageWeddingEndNotify tMsgWeddingWeddingEnd;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_WEDDINGEND );	
	tMsgHead.set_msgpara( (int)&tMsgWeddingWeddingEnd );
	
	CEntityPlayer *tpGroom = CSceneLogic::GetSingleton().GetPlayerByCharID( pMarriageInfo->GetGroomID() );
	if( tpGroom != NULL )
	{
		CSceneLogic::GetSingleton().Send2Player( tpGroom, &tMsgHead );
	}
	
	CEntityPlayer *tpBride = CSceneLogic::GetSingleton().GetPlayerByCharID( pMarriageInfo->GetBrideID() );
	if ( tpBride != NULL )
	{
		CSceneLogic::GetSingleton().Send2Player( tpBride, &tMsgHead );
	}	
}

// ***********************************************************
//  Function:		CheckNewlyBaitangStatus
//  Description:	������״̬
//  Output:			
//  Date:	04/13/2010
// **********************************************************
bool CMarriageModule::CheckNewlyBaitangStatus( )
{
	CMarriageInfo *tpMarriage = CMarriageManager::GetSingleton().GetCurrentWeddingInfo();
	if ( tpMarriage == NULL )
	{
		return false;
	}
	
	if ( tpMarriage->GetMarriageStatus() != MARRIAGESTATUS_WEDDINGONHALL )
	{
		return false;
	}
	
	if ( tpMarriage->GetWeddingEventStatus() & EVENT_BAITANGEND )
	{
		return false;
	}
	
	CEntityPlayer *tpGroom = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriage->GetGroomID() );
	if ( tpGroom == NULL )
	{
		return false;
	}
	
	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	LK_ASSERT( tpMarriageConfig != NULL, return false )
	
	CEntityPlayer *tpBride = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriage->GetBrideID() );
	if ( tpBride == NULL )
	{
		return false;
	}  	
	
	if ( tpMarriage->GetWeddingEventStatus() & EVENT_WEDDINGBAITANG )
	{
		SendTimeToPutKeepSakeNotify( tpMarriage );
		tpMarriage->SetWeddingEventStatus( tpMarriage->GetWeddingEventStatus() | EVENT_BAITANGEND );
		CPropertyModule::GetSingleton().RemoveBuff( tpGroom, tpMarriageConfig->mBaitangBuffID );
		CPropertyModule::GetSingleton().RemoveBuff( tpBride, tpMarriageConfig->mBaitangBuffID );
	}
	else
	{	
		// �ж�����
		if ( tpGroom->GetMapID() != tpBride->GetMapID() )
		{
			return false;
		}
		if ( CDataStatic::IsInBaitangPos( tpMarriage->GetWeddingModule(), tpGroom->GetMapID(), tpBride->GetPosX(), tpBride->GetPosY(), tpGroom->GetPosX(), tpGroom->GetPosY() ) == true )
		{
			SendBaitangNotify( tpBride, tpMarriage->GetGroomName(), tpMarriage->GetBrideName(), tpGroom->GetEntityID(), tpBride->GetEntityID() );
			tpMarriage->SetWeddingEventStatus( tpMarriage->GetWeddingEventStatus() | EVENT_WEDDINGBAITANG );
			
			// ������˫���϶���buff
			CPropertyModule::GetSingleton().InsertBuff( tpGroom, tpMarriageConfig->mBaitangBuffID );
			CPropertyModule::GetSingleton().InsertBuff( tpBride, tpMarriageConfig->mBaitangBuffID );			
			return true;
		}	
	}	
	return false;
}

// ***********************************************************
//  Function:		LoadMarriageCountFromDB
//  Description:	���ػ�����Ļ�����¼����
//  Output:			
//  Date:	02/28/2010
// **********************************************************
void CMarriageModule::LoadMarriageCountFromDB( int nCampID )
{  
	const char *tpSql = "select count(*) from UMS_MARRIAGE where camp_id=%d" ;
	CSceneLogic::GetSingleton().ExecuteSql( session_marriage_loadmarriagenum, 0, 0, 0, SQL_NEED_CALLBACK, SELECT, tpSql, nCampID );
}

// ***********************************************************
//  Function:		OnSessionLoadMarriageCountFromDB
//  Description:	���ػ�����Ļ�����¼���������ݿⷵ����Ϣ
//  Output:			
//  Date:	02/28/2010
// **********************************************************
void CMarriageModule::OnSessionLoadMarriageCountFromDB( CMessage *pMessage, int nParam1, int nParam2 )
{
	LK_ASSERT( pMessage != NULL, return )		
	CMessageExecuteSqlResponse3 *tpResponseMsg = ( CMessageExecuteSqlResponse3 * )pMessage->msgpara();
	if ( tpResponseMsg == NULL )
	{
		return;
	}

	if ( tpResponseMsg->resultcode() != 1 )
	{
		printf( "load marriage count from database error" );
		LOG_ERROR( "marriage","load marriage count from database error" );
		return;
	}
	
	int tMarriageNum = 	atoi( tpResponseMsg->mutable_fieldvalue( 0 )->c_str() );
	
	if ( tMarriageNum > 0 )
	{
		LoadMarriageInfoFromDB( tMarriageNum, 0 );	
	}
	else
	{
		mMarriageComplete = true;	
		LOG_INFO( "marriage","load marriage infomation complete ! number :0 " );
	}
}

// ***********************************************************
//  Function:		LoadMarriageInfoFromDB
//  Description:	���ػ��������ݿ���Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::LoadMarriageInfoFromDB( int nTotalCount, int nLoadCount )
{
	int tCampID = CSceneLogic::GetSingleton().GetLineID();
	const char *tpSql = "select server_sequence, groom_id, bride_id, groom_name, bride_name, marriage_status, wedding_time, wedding_timelength, camp_sequence, wedding_module from UMS_MARRIAGE where camp_id=%d limit %d,%d" ;
	CSceneLogic::GetSingleton().ExecuteSql( session_marriage_loadmarriageinfo, nTotalCount, nLoadCount , 0, SQL_NEED_CALLBACK, SELECT, tpSql, tCampID, nLoadCount, MARRIAGELOADNUM );
}

// ***********************************************************
//  Function:		OnSessionLoadMarriageInfoFromDB
//  Description:	��ȡ���ݿ��л�����Ϣ�����Ļ�Ӧ��Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::OnSessionLoadMarriageInfoFromDB( CMessage *pMessage, int nParam1, int nParam2 )
{
	LK_ASSERT( pMessage != NULL, return )		
	CMessageExecuteSqlResponse3 *tpResponseMsg = ( CMessageExecuteSqlResponse3 * )pMessage->msgpara();
	if ( tpResponseMsg == NULL )
	{
		printf( "load marriage info from database error, totalnum:%d, loadnum:%d", nParam1, nParam2 );
		LOG_ERROR( "marriage","load marriage info from database error, totalnum:%d, loadnum:%d", nParam1, nParam2 );
		return;
	}

	if ( tpResponseMsg->resultcode() != 1 )
	{
		printf( "load marriage info from database error, totalnum:%d, loadnum:%d", nParam1, nParam2 );
		LOG_ERROR( "marriage","load marriage info from database error, totalnum:%d, loadnum:%d", nParam1, nParam2 );
		return;		
	}
	
	int tRowNum = tpResponseMsg->rowcount();
	int	tColumn	= tpResponseMsg->colcount();	
	
	if ( tColumn != 10 )
	{
		printf( "wrong marriage information column number, totalcolumnnum:%d, realcolumnnum:%d ", 9, tColumn );
		LOG_ERROR( "marriage","wrong marriage information column number, totalcolumnnum:%d, realcolumnnum:%d ", 9, tColumn );
		return;
	}
	
	int tCampID = CSceneLogic::GetSingleton().GetLineID();
	for ( int i = 0; i < tRowNum; ++i )
	{			
		CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().CreateObject( OBJTYPE_MARRIAGEINFO );
		if ( tpMarriageInfo == NULL )
		{
			printf( "creat marriage object error!" );
			LOG_ERROR( "marriage","creat marriage object error!" );
			return;				
		}
		
		tpMarriageInfo->SetServerSequence( atoi( tpResponseMsg->mutable_fieldvalue( 0 + i*tColumn )->c_str() ) );				
		tpMarriageInfo->SetGroomID( atoi( tpResponseMsg->mutable_fieldvalue( 1 + i*tColumn )->c_str() ) );				
		tpMarriageInfo->SetBrideID( atoi( tpResponseMsg->mutable_fieldvalue( 2 + i*tColumn )->c_str() ) );						
		tpMarriageInfo->SetGroomName( tpResponseMsg->mutable_fieldvalue( 3 + i*tColumn )->c_str() );						
		tpMarriageInfo->SetBrideName( tpResponseMsg->mutable_fieldvalue( 4 + i*tColumn )->c_str() );						
		tpMarriageInfo->SetMarriageStatus( atoi( tpResponseMsg->mutable_fieldvalue( 5 + i*tColumn )->c_str() ) );						
		tpMarriageInfo->SetWeddingTime( atoi( tpResponseMsg->mutable_fieldvalue( 6 + i*tColumn )->c_str() ) );						
		tpMarriageInfo->SetWeddingTimeLength( atoi( tpResponseMsg->mutable_fieldvalue( 7 + i*tColumn )->c_str() ) );						
		tpMarriageInfo->SetCampSequence( atoi( tpResponseMsg->mutable_fieldvalue( 8 + i*tColumn )->c_str() ) );						
		tpMarriageInfo->SetCampID( tCampID );
		tpMarriageInfo->SetWeddingModule( atoi( tpResponseMsg->mutable_fieldvalue( 9 + i*tColumn )->c_str() ) );						
				
		CMarriageManager::GetSingleton().InsertMarriageInfo( tpMarriageInfo->GetServerSequence(), tpMarriageInfo );
	}
	
	if ( tRowNum < MARRIAGELOADNUM || nParam1 <= nParam2 + tRowNum )
	{	
		LOG_INFO( "marriage"," Load marriageinfo complete, totalnum:%d, numload:%d", nParam1, tRowNum ) ;		
		if ( nParam1 != nParam2 + tRowNum )
		{
			printf( "load marriage number error, totalnum:%d, currentnum%d", nParam1, nParam2 + tRowNum );
			LOG_ERROR( "marriage","load marriage number error, totalnum:%d, currentnum%d", nParam1, nParam2 + tRowNum );
			return;
		}
		mMarriageComplete = true;
		return;
	}
	else
	{
		LoadMarriageInfoFromDB( nParam1, nParam2 + tRowNum );
		LOG_INFO( "marriage"," Load marriageinfo complete, totalnum:%d, loadcount:%d", nParam1, nParam2 + tRowNum ) ;		
	}
}

// ***********************************************************
//  Function:		LoadCampInfo
//  Description:	��ȡ���ݿ�����Ӫ��Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::LoadCampInfo( int nCampID )
{  	
	const char *tpSql = "select marriednum from UMS_CAMP where campid=%d";
	CSceneLogic::GetSingleton().ExecuteSql( session_marriage_loadcampinfo, 0, 0, 0, SQL_NEED_CALLBACK, SELECT, tpSql, nCampID );
}

// ***********************************************************
//  Function:		OnSessionLoadCampInfo
//  Description:	��ȡ���ݿ�����Ӫ��Ϣ�ķ�����Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::OnSessionLoadCampInfo( CMessage *pMessage, int nParam1, int nParam2 )
{
	if ( pMessage == NULL )
	{
		LOG_ERROR( "marriage"," load campinfo error! " );
		return;
	}
	
	LK_ASSERT( pMessage != NULL, return )		
	CMessageExecuteSqlResponse3 *tpResponseMsg = ( CMessageExecuteSqlResponse3 * )pMessage->msgpara();
	if ( tpResponseMsg == NULL )
	{
		LOG_ERROR( "marriage", "msg null" );
		return;
	}

	if ( tpResponseMsg->resultcode() != 1 )
	{
		LOG_ERROR( "marriage","load camp info from database error" );
		return;	
	}	
	
	int tMarriedNum = 1;		
	if ( tpResponseMsg->rowcount() < 1 || tpResponseMsg->colcount() < 1 )
	{
		// ��û����Ӫ��Ϣ���ȴ�������
		CreatCampDBInfo( CSceneLogic::GetSingleton().GetLineID(), tMarriedNum );		
	}
	else
	{
		tMarriedNum = atoi( tpResponseMsg->mutable_fieldvalue( 0 )->c_str() );	
	}
	 
	CMarriageManager::GetSingleton().GetCampInfo()->SetMarriageNum( tMarriedNum );
	CMarriageManager::GetSingleton().GetCampInfo()->SetCampID( CSceneLogic::GetSingleton().GetLineID() );
	mCampInfoComplete = true;
}

// ***********************************************************
//  Function:		LoadPlayerMarriageInfo
//  Description:	������ҵĻ�����Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::LoadPlayerMarriageInfo( CEntityPlayer *pPlayer )
{ 
	LK_ASSERT( pPlayer != NULL, return )	
	const char *tpSql = "select server_sequence, groom_id, bride_id, groom_name, bride_name, marriage_status, wedding_time, wedding_timelength, camp_sequence, wedding_module from UMS_MARRIAGE where server_sequence = %d " ;
	CSceneLogic::GetSingleton().ExecuteSql( session_marriage_loadplayermarriageinfo, pPlayer->GetCharID(), 0, pPlayer->GetCharID(), SQL_NEED_CALLBACK, SELECT, tpSql, pPlayer->GetMarriageID() );
}

// ***********************************************************
//  Function:		LoadPlayerMarriageInfo
//  Description:	������ҵĻ�����Ϣ�����ݿⷵ����Ϣ
//  Output:			
//  Date:	02/27/2010
// **********************************************************
void CMarriageModule::OnsessionLoadPlayerMarriageInfo( CMessage *pMessage, int nRoleID, int nParam2 )
{	
	if ( pMessage == NULL )
	{
		LOG_ERROR( "marriage"," load player marriage info error, roleid:%d! ", nRoleID );
		return;
	}	
	
	CEntityPlayer *pPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( nRoleID );
	if ( pPlayer == NULL )
	{
		return;
	}
	
	CMessageExecuteSqlResponse3 *tpResponseMsg = ( CMessageExecuteSqlResponse3 * )pMessage->msgpara();
	if ( tpResponseMsg == NULL )
	{
		return;
	}

	if ( tpResponseMsg->resultcode() != 1 )
	{
		LOG_ERROR( "marriage","load player marriage info from database error, roleid:%d", nRoleID );	
		return;
	}	
	
	if ( tpResponseMsg->rowcount() < 1 || tpResponseMsg->colcount() != 10 )
	{
		// ����Ѿ����
		LOG_INFO( "marriage","[%d]change player ( roleid:%d ) marriageid:%d becasue of divorce", __LINE__, pPlayer->GetCharID(), pPlayer->GetMarriageID() );
		pPlayer->SetMarriageID( 0 );
		
		// ȥ�����ƺ�
		CTemplateMarriageConfig *tpConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
		if( tpConfig != NULL )
		{
			CPropertyModule::GetSingleton().OnPlayerDelTitleEvent( pPlayer, tpConfig->mMarriageTitleID );
		}
		return;
	}
	
	CMarriageInfo *tpMarriageInfo = ( CMarriageInfo * )CSceneObjManager::GetSingleton().CreateObject( OBJTYPE_MARRIAGEINFO );
	if ( tpMarriageInfo == NULL )
	{
		LOG_ERROR( "marriage","creat marriage object error for player, roleid:%d !", __FUNCTION__, __LINE__, nRoleID );
		return;
	}

	tpMarriageInfo->SetServerSequence( atoi( tpResponseMsg->mutable_fieldvalue( 0 )->c_str() ) );				
	tpMarriageInfo->SetGroomID( atoi( tpResponseMsg->mutable_fieldvalue( 1 )->c_str() ) );				
	tpMarriageInfo->SetBrideID( atoi( tpResponseMsg->mutable_fieldvalue( 2 )->c_str() ) );						
	tpMarriageInfo->SetGroomName( tpResponseMsg->mutable_fieldvalue( 3 )->c_str() );						
	tpMarriageInfo->SetBrideName( tpResponseMsg->mutable_fieldvalue( 4 )->c_str() );						
	tpMarriageInfo->SetMarriageStatus( atoi( tpResponseMsg->mutable_fieldvalue( 5 )->c_str() ) );						
	tpMarriageInfo->SetWeddingTime( atoi( tpResponseMsg->mutable_fieldvalue( 6 )->c_str() ) );						
	tpMarriageInfo->SetWeddingTimeLength( atoi( tpResponseMsg->mutable_fieldvalue( 7 )->c_str() ) );						
	tpMarriageInfo->SetCampSequence( atoi( tpResponseMsg->mutable_fieldvalue( 8 )->c_str() ) );	
	tpMarriageInfo->SetWeddingModule( atoi( tpResponseMsg->mutable_fieldvalue( 9 )->c_str() ) );	
	int tRet = CMarriageManager::GetSingleton().InsertOtherCampMarriageInfo( tpMarriageInfo );
	if ( tRet == -1 )
	{
		LOG_ERROR( "marriage","[%s,%d] Insert player marriage info error, roleid:%d ", __FUNCTION__, __LINE__, nRoleID );
		CSceneObjManager::GetSingleton().DestroyObject( tpMarriageInfo->get_id() );
		return;	
	}
	
	SendPersonMarriageInfoNotify( pPlayer, tpMarriageInfo );
	
	/*if ( tpMarriageInfo->GetWeddingStatus() == WEDDINGSTATUS_TIMENEAR || tpMarriageInfo->GetWeddingStatus() == WEDDINGSTATUS_INTIME )
	{
		SendMarriageTipsNotify( tpMarriageInfo );
	}		*/		
}

// ***********************************************************
//  Function:		CreatCampDBInfo
//  Description:	������Ӫ��Ϣ��
//  Output:			
//  Date:	03/01/2010
// **********************************************************
void CMarriageModule::CreatCampDBInfo( int nCampID, int nMarriedNum )
{
	const char *tpSql = "insert UMS_CAMP( campid, marriednum ) values( %d,%d )";	
	CSceneLogic::GetSingleton().ExecuteSql( session_creatcampinfo, nCampID, 0, 0, SQL_NEED_CALLBACK, INSERT, tpSql, nCampID, nMarriedNum );	
}

// ***********************************************************
//  Function:		OnSessionCreatCampDBInfo
//  Description:	������Ӫ��Ϣ��
//  Output:			
//  Date:	03/01/2010
// **********************************************************
void CMarriageModule::OnSessionCreatCampDBInfo( CMessage *pMessage, int nCampID, int nParam2 )
{
	if ( pMessage == NULL )
	{
		LOG_ERROR( "marriage", "OnSessionCreatCampDBInfo failed, msg is null" );
		return;
	}
	
	CMessageExecuteSqlResponse3 *tpResponseMsg = ( CMessageExecuteSqlResponse3 * )pMessage->msgpara();
	if ( tpResponseMsg == NULL )
	{
		LOG_ERROR( "marriage", "msg para is null" );
		return;
	}
	
	if ( tpResponseMsg->resultcode() != 1 )
	{
		LOG_ERROR( "marriage","creat campinfo error, campid:%d", nCampID );
		return;
	}
	
	LOG_INFO( "marriage","campinfo created, campid:%d", nCampID );
}

// ***********************************************************
//  Function:		UpDatePlayerMarriageID
//  Description:	������ҽ�ɫ��Ϣ�еĻ���ID�ֶ�
//  Output:			
//  Date:	03/01/2010
// **********************************************************
void CMarriageModule::UpDatePlayerMarriageID( int nRoleID, int nMarriageID )
{		
	const char *tpSql = "update UMS_ROLE set role_marriageid = %d where role_id=%d";
	CSceneLogic::GetSingleton().ExecuteSql( ssion_updatemarriageid, 0, 0, nRoleID, SQL_NONE, UPDATE,
	tpSql, nMarriageID, nRoleID );
}

// ***********************************************************
//  Function:		UpDateMarriageInfo
//  Description:	������ҵĻ�����Ϣ���ݿ�
//  Output:			
//  Date:	03/01/2010
// **********************************************************
void CMarriageModule::UpDateMarriageInfo( CMarriageInfo *tpMarriageInfo )
{
	LK_ASSERT( tpMarriageInfo != NULL, return )
	const char *tpSql = "update UMS_MARRIAGE set marriage_status = %d, wedding_time=%d, wedding_timelength=%d where server_sequence =%d";
	CSceneLogic::GetSingleton().ExecuteSql( ssion_updatemarriageinfo, 0, 0, 0, SQL_NONE, UPDATE, 
		tpSql, tpMarriageInfo->GetMarriageStatus(),  tpMarriageInfo->GetWeddingTime(), tpMarriageInfo->GetWeddingTimeLength(), tpMarriageInfo->GetServerSequence() );
}

// ***********************************************************
//  Function:		UpDateCampDBInfo
//  Description:	�������ݿ����Ӫ��Ϣ
//  Output:			
//  Date:	03/01/2010
// **********************************************************
void CMarriageModule::UpDateCampDBInfo( CCampInfo *tpCampInfo )
{
	LK_ASSERT( tpCampInfo != NULL, return )	
	const char *tpSql = "update UMS_CAMP set marriednum = %d where campid=%d";
	CSceneLogic::GetSingleton().ExecuteSql( ssion_updatecampinfo, 0, 0, 0, SQL_NONE, UPDATE, tpSql,
		tpCampInfo->GetMarriageNum(), tpCampInfo->GetCampID() );
}

// ***********************************************************
//  Function:		DeleteMarriageDBInfo
//  Description:	ɾ�����ݿ�Ļ�����Ϣ
//  Output:			
//  Date:	03/01/2010
// **********************************************************
void CMarriageModule::DeleteMarriageDBInfo( CMarriageInfo *tpMarriage )
{ 
	LK_ASSERT( tpMarriage != NULL, return )
	const char *tpSql = "delete from UMS_MARRIAGE where server_sequence=%d";
	CSceneLogic::GetSingleton().ExecuteSql( session_deletemarriageinfo, 0, 0, 0, SQL_NONE, UPDATE, tpSql, tpMarriage->GetServerSequence() );
}

// ***********************************************************
//  Function:		OnMessageStartKeepsakeExchangeRequest
//  Description:	��ʼ����һ�����Ϣ����
//  Output:			
//  Date:	04/14/2010
// **********************************************************
void CMarriageModule::OnMessageStartKeepsakeExchangeRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	
	if ( pPlayer->GetMarriageID() == 0 )
	{
		SendStartKeepsakeExchangeResponse( pPlayer, EM_MARRIAGE_PUTSAKEEXCHANGE_ONMARRIED );
		return;
	}
	
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfo( pPlayer->GetMarriageID() );
	if ( tpMarriageInfo == NULL )
	{
		SendStartKeepsakeExchangeResponse( pPlayer, EM_MARRIAGE_EXCHANGEKEEPSAKE_NOTMARRIED );
		return;
	}
	
	CEntityPlayer *tpSpouse = NULL;
	if ( tpMarriageInfo->GetGroomID() == pPlayer->GetCharID() )
	{
		tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetBrideID() );
	}
	else
	{
		tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetGroomID() );	
	}	
	
	if ( tpSpouse == NULL )
	{
		SendStartKeepsakeExchangeResponse( pPlayer, EM_MARRIAGE_EXCHANGEKEEPSAKE_NEWLYOFFLINE );
		return;
	}
	
	if ( pPlayer->IsWithinViewDistance( tpSpouse ) == false )
	{
		SendStartKeepsakeExchangeResponse( pPlayer, EM_MARRIAGE_PUTSAKEEXCHANGE_WITHOUTDISTANCE );
		return;
	}	
	
	tpMarriageInfo->SetGroomKeepsakeStatus( KEEPSAKSTATUS_EMPTY );
	tpMarriageInfo->SetBrideKeepsakeStatus( KEEPSAKSTATUS_EMPTY );
	tpMarriageInfo->SetBrideKeepsakeIndex( -1 );  
	tpMarriageInfo->SetGroomKeepsakeIndex( -1 );
	
	SendTimeToPutKeepSakeNotify(  tpMarriageInfo, tpSpouse );
	SendStartKeepsakeExchangeResponse( pPlayer, SUCCESS );
}

// ***********************************************************
//  Function:		SendStartKeepsakeExchangeResponse
//  Description:	���Ϳ�ʼ����һ�����Ϣ��Ӧ
//  Output:			
//  Date:	04/14/2010
// **********************************************************
void CMarriageModule::SendStartKeepsakeExchangeResponse( CEntityPlayer *pPlayer, int nErrcode )
{	
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageStartKeepsakeExchangeResponse tMsgStartKeepsake;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_STARTKEEPSAKEEXCHANGE );
	tMsgHead.set_msgpara( (int)&tMsgStartKeepsake );
	
	tMsgStartKeepsake.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		OnMessageStopKeepsakeRequest
//  Description:	��ֹ����һ�����Ϣ����
//  Output:			
//  Date:	04/14/2010					  
// **********************************************************
void CMarriageModule::OnMessageStopKeepsakeRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfo( pPlayer->GetMarriageID() );
	if ( tpMarriageInfo == NULL )
	{
		return;
	}					
	
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )	pPlayer->GetProperty();
	CItemObject *tpItemKeepsake = tpProperty->GetBaggage()->GetItemObjPtr( tpMarriageInfo->GetKeepsakeIndex( pPlayer->GetSex() ) );
	if ( tpItemKeepsake != NULL )
	{
		if ( tpItemKeepsake->GetLockStatus() == LOCKTYPE_KEEPSAKE )
		{
			tpItemKeepsake->SetLockStatus( LOCKTYPE_NONE );
			CPropertyModule::GetSingleton().SendLockItemNotice( pPlayer, tpMarriageInfo->GetKeepsakeIndex( pPlayer->GetSex() ), LOCKTYPE_NONE );
		}
	}
	tpMarriageInfo->SetKeepsakeIndex(  -1, pPlayer->GetSex() );
	tpMarriageInfo->SetKeepsakeStatus( KEEPSAKSTATUS_EMPTY, pPlayer->GetSex() );
	SendStopKeepsakeResponse( pPlayer, SUCCESS );	
	
	CEntityPlayer *tpSpouse = NULL;
	if ( tpMarriageInfo->GetGroomID() == pPlayer->GetCharID() )
	{
		tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetBrideID() );		
	}
	else
	{
		tpSpouse = CSceneLogic::GetSingleton().GetPlayerByCharID( tpMarriageInfo->GetGroomID() );
	}
	
	if ( tpSpouse == NULL )
	{
		return;
	}	
	
	
	CPropertyPlayer *tpSpouseProperty = ( CPropertyPlayer * )tpSpouse->GetProperty();
	CItemObject *tpSpouseKeepsake = tpSpouseProperty->GetBaggage()->GetItemObjPtr( tpMarriageInfo->GetKeepsakeIndex( tpSpouse->GetSex() ) );
	if ( tpSpouseKeepsake != NULL )
	{
		if ( tpSpouseKeepsake->GetLockStatus() == LOCKTYPE_KEEPSAKE )
		{
			tpSpouseKeepsake->SetLockStatus( LOCKTYPE_NONE );
			CPropertyModule::GetSingleton().SendLockItemNotice( tpSpouse, tpMarriageInfo->GetKeepsakeIndex( tpSpouse->GetSex() ), LOCKTYPE_NONE );
		}
	}
	
	tpMarriageInfo->SetKeepsakeIndex( -1, tpSpouse->GetSex() );
	tpMarriageInfo->SetKeepsakeStatus( KEEPSAKSTATUS_EMPTY, tpSpouse->GetSex() );
	SendStopKeepsakeNotify( tpSpouse );
}

// ***********************************************************
//  Function:		SendStopKeepsakeResponse
//  Description:	��ֹ����һ�����Ϣ��Ӧ
//  Output:			
//  Date:	04/14/2010					  
// **********************************************************
void CMarriageModule::SendStopKeepsakeResponse( CEntityPlayer *pPlayer, int nErrcode )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessage  tMsgHead;
	CMessageStopKeepsakeExchangeResponse tMsgStopKeepsake;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_STOPKEEPSAKEEXCHANGE );
	tMsgHead.set_msgpara( (int)&tMsgStopKeepsake );
	
	tMsgStopKeepsake.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendStopKeepsakeNotify
//  Description:	������ֹ�������Ϣ֪ͨ
//  Output:			
//  Date:	04/14/2010					  
// **********************************************************
void CMarriageModule::SendStopKeepsakeNotify( CEntityPlayer *pPlayer )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageStopKeepsakeExchangeNotify tMsgStopKeepsakeExchange;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_STOPKEEPSAKEEXCHANGE );
	tMsgHead.set_msgpara( (int)&tMsgStopKeepsakeExchange );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		OnMessageInvitationExchange
//  Description:	�����һ�������
//  Output:			
//  Date:	04/14/2010					  
// **********************************************************
void CMarriageModule::OnMessageInvitationExchange( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessageInvitationExchangeRequest *tpMsg = ( CMessageInvitationExchangeRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	// ����������ж�
	
	InvitationExchange( pPlayer, tpMsg->itemindex() );
}

// ***********************************************************
//  Function:		SendInvitationExchangeResponse
//  Description:	���������һ�����Ϣ��Ӧ
//  Output:			
//  Date:	04/14/2010					  
// **********************************************************
void CMarriageModule::SendInvitationExchangeResponse( CEntityPlayer *pPlayer, int nErrcode )
{		
	LK_ASSERT( pPlayer != NULL, return )		
	CMessage tMsgHead;
	CMessageInvitationExchangeResponse tMsgInvitationExchange;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_INVITATIONEXCHANGE );	
	tMsgHead.set_msgpara( (int)&tMsgInvitationExchange );
	tMsgInvitationExchange.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendKeepsakeExchangeNotify
//  Description:	�������ｻ���Ľ��֪ͨ
//  Output:			
//  Date:	04/14/2010					  
// **********************************************************
void CMarriageModule::SendKeepsakeExchangeResultNotify( CMarriageInfo *pMarriage, int nGroomItemID, int nBrideItemID, CEntityPlayer *pPlayer /* = NULL */ )
{
	LK_ASSERT( pMarriage != NULL, return )
	CMessage tMsgHead;
	CMessageExchangeResultNotify tMsgExchange;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_EXCHANGERESULT );
	tMsgHead.set_msgpara( (int)&tMsgExchange );
	tMsgExchange.set_groomroleid( pMarriage->GetGroomID() );
	tMsgExchange.set_brideroleid( pMarriage->GetBrideID() );
	tMsgExchange.set_groomitemid( nGroomItemID );
	tMsgExchange.set_brideitemid( nBrideItemID );
	tMsgExchange.set_groomname( pMarriage->GetGroomName() );
	tMsgExchange.set_bridename( pMarriage->GetBrideName() );
	
	if ( pMarriage->GetMarriageStatus() == MARRIAGESTATUS_WEDDINGONHALL )
	{
		CTemplateMarriageConfig *tpConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
		if ( tpConfig == NULL )
		{
			return;
		}			

		int tWeddingModule = pMarriage->GetWeddingModule();
		if ( tWeddingModule < 0 || tWeddingModule >= (int)ARRAY_CNT( tpConfig->mWeddinInfo ) )
		{
			return;
		}
		
		int tMapID = tpConfig->mWeddinInfo[ tWeddingModule ].mWeddingHallMapID;
		SendMapMessage( tMapID, &tMsgHead );
	}				    
	else
	{	
		if ( pPlayer != NULL )
		{
			CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );	
		}	
	}	
}

// ***********************************************************
//  Function:		InvitationExchange
//  Description:	���ｻ��
//  Output:			
//  Date:	04/14/2010					  
// **********************************************************
void CMarriageModule::InvitationExchange( CEntityPlayer *pPlayer, int nItemIndex )
{
	LK_ASSERT( pPlayer != NULL, return )
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )	pPlayer->GetProperty();
	CItemObject *tpItemobj = tpProperty->GetBaggage()->GetItemObjPtr( nItemIndex );
	if ( tpItemobj == NULL )
	{
		SendInvitationExchangeResponse( pPlayer, EM_MARRIAGE_INVITATIONEXCHANGE_ITEMNOTEXIST );
		return;
	}
	
	CTplItem *tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( tpItemobj->GetItemID() );
	if ( tpTplItem == NULL )
	{
		SendInvitationExchangeResponse( pPlayer, EM_MARRIAGE_INVITATIONEXCHANGE_ITEMNOTEXIST );
		return;
	}
	
	if ( tpTplItem->mItemType != CTplItem::ITEM_INVITATION )
	{
		SendInvitationExchangeResponse( pPlayer, EM_MARRIAGE_INVITATIONEXCHANGE_WRONGITEM );
		return;
	}
	
	CItemInvitation *tpInvitation = ( CItemInvitation * )tpItemobj;
	if( ( tpInvitation->GetWeddingTime() + tpInvitation->GetWeddingTimeLength() ) > time( NULL ) )
	{
		SendInvitationExchangeResponse( pPlayer, EM_MARRIAGE_INVITATIONEXCHANGE_WEDDINGNOTEND );
		return;
	}
			
	 	
	SendInvitationExchangeResponse( pPlayer, SUCCESS );	
	
	CTplInvitation *tpTplInvitation = ( CTplInvitation * )tpTplItem;	
	CPropertyModule::GetSingleton().PlayerRemoveItem( pPlayer, nItemIndex, 1 );
	CPropertyModule::GetSingleton().PlayerInsertItem( pPlayer, tpTplInvitation->mExchangeItemID, 1 );
	
}

// ***********************************************************
//  Function:		SendMapMessage
//  Description:	��������ͼ����ҷ�����Ϣ
//  Output:			
//  Date:	04/14/2010					  
// **********************************************************
void CMarriageModule::SendMapMessage( int nMapID, CMessage *pMessage )
{ 
	LK_ASSERT( pMessage != NULL, return )
	CMapObject *tpMapObj = CMapObjManager::GetSingleton( ).GetMapObject( CSceneLogic::GetSingleton().GetLineID(), nMapID, INVALID_MAP_INDEX );
	LK_ASSERT( tpMapObj != NULL, return )	
	MapPlayerChecker tMapChecker;
	CWTPoint tTopLeft(0,0);
	CWTPoint tBottomRight(10000,10000);
	MapRegionEntitySearcher<MapPlayerChecker>	mSearcher( tMapChecker, tTopLeft, tBottomRight );
	mSearcher.Visit( tpMapObj );
	for ( int i = 0; i < tMapChecker.mNum; ++i )
	{
		if ( tMapChecker.mPlayerList[i] == NULL )
		{
			continue;
		}	 

		// ��ÿ���˴��������涼���ͳ�ȥ		
		CSceneLogic::GetSingleton().Send2Player( tMapChecker.mPlayerList[i], pMessage );
	}		
}

// ��ȡnpc��ͷ��Ӧ����ʾ����������
const char *CMarriageModule::GetNewlyName( CEntity *tpEntity )
{
	if ( tpEntity == NULL )
	{
		return NULL;
	}
	
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetCurrentWeddingInfo();
	if ( tpMarriageInfo == NULL )
	{
		return NULL;
	}
	
	CProperty *tpProperty = tpEntity->GetProperty();
	if ( tpProperty == NULL )
	{
		return NULL;
	}
	
	CTemplateMarriageConfig *tpConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	if ( tpConfig == NULL )
	{
		return NULL;
	}
	
	if ( tpConfig->mWeddingNpc[tpMarriageInfo->GetWeddingModule()][0] == (int)tpProperty->GetPropertyTempID() )
	{
		return tpMarriageInfo->GetGroomName();
	}
	
	if ( tpConfig->mWeddingNpc[tpMarriageInfo->GetWeddingModule()][1] == (int)tpProperty->GetPropertyTempID() )
	{
		return tpMarriageInfo->GetBrideName();
	}
	
	return NULL;
}

// ***********************************************************
//  Function:		OnMessageTeletoMarriageNpcRequest
//  Description:	�����͵�����npc����Ϣnpc����Ϣ��Ӧ
//  Output:			
//  Date:	04/14/2010					  
// **********************************************************
void CMarriageModule::OnMessageTeletoMarriageNpcRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageTeleToWeddingNpcRequest *tpMsg = ( CMessageTeleToWeddingNpcRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}
	
	CMarriageInfo *tpMarriage = CMarriageManager::GetSingleton().GetMarriageInfo( pPlayer->GetMarriageID() );			
	if ( tpMarriage == NULL )
	{
		return;
	}
	
	CTemplateMarriageConfig *tpConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	LK_ASSERT( tpConfig != NULL, return )		
	CMapModule::GetSingleton().Teleport( (unsigned short)CSceneLogic::GetSingleton().GetLineID(), (unsigned short)tpConfig->mMarriageNpcMapID, tpConfig->mMarriageNpcPosX, tpConfig->mMarriageNpcPosY, pPlayer );		
	
	SendTeletoMarriageNpcResponse( pPlayer, SUCCESS );	  	
}

// ***********************************************************
//  Function:		SendTeletoMarriageNpcResponse
//  Description:	���������͵�����npc����Ϣ��Ӧ
//  Output:			
//  Date:	04/14/2010					  
// **********************************************************
void CMarriageModule::SendTeletoMarriageNpcResponse( CEntityPlayer *pPlayer, int nErrcode )
{  
	LK_ASSERT( pPlayer != NULL, return )	
	
	CMessage tMsgHead;
	CMessageTeleToWeddingNpcResponse tMsgTeletoMarriageNpc;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_TELETOWEDDINGNPC );	
	tMsgHead.set_msgpara( (int)&tMsgTeletoMarriageNpc );
	tMsgTeletoMarriageNpc.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		StartWedding
//  Description:	��ʼ����
//  Output:			
//  Date:	04/14/2010					  
// **********************************************************
void CMarriageModule::StartWedding( CMarriageInfo *pMarriageInfo, EWeddingStartType emType )
{
	LK_ASSERT( pMarriageInfo != NULL, return )
	
	CEntityPlayer *tpBride = NULL;
	CEntityPlayer *tpGroom = NULL;
	
	if ( emType == WEDDINGSTARTTYPE_PLAYER )
	{
		tpBride = CSceneLogic::GetSingleton().GetPlayerByCharID( pMarriageInfo->GetBrideID() );
		tpGroom = CSceneLogic::GetSingleton().GetPlayerByCharID( pMarriageInfo->GetGroomID() );
	}
	
	// �����һ���Ķ�ʱ��
	CMarriageManager::GetSingleton().ClearAllWeddingTime();

	// �����һ���Ļ���δ�������������Ӧ����Ϣ
	CMarriageInfo *tpLastWeddingMarriage = CMarriageManager::GetSingleton().GetCurrentWeddingInfo();
	if ( tpLastWeddingMarriage != NULL )
	{
		ClearWeddingInfo( tpLastWeddingMarriage );
		tpLastWeddingMarriage->SetMarriageStatus( MARRIAGESTATUS_WEDDINGEND );
	}

	// �����������
	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	if ( tpMarriageConfig == NULL )
	{								
		return;
	}

	pMarriageInfo->InitialWeddingInfo( );	
	
	if ( tpBride != NULL )
	{
		CPropertyModule::GetSingleton().InsertBuff( tpBride, tpMarriageConfig->mWeddinInfo[pMarriageInfo->GetWeddingModule()].mMaleBufferID );		
	}
	
	if ( tpGroom != NULL )
	{
		CPropertyModule::GetSingleton().InsertBuff( tpGroom, tpMarriageConfig->mWeddinInfo[pMarriageInfo->GetWeddingModule()].mFemaleBufferID );		
	}


	// ������Ӫ��ǰ���ھ��л���Ļ���ID
	CMarriageManager::GetSingleton().SetCurrentWeddingID( pMarriageInfo->GetServerSequence() );	

	// ���û�����Ϣ��״̬
	pMarriageInfo->SetMarriageStatus( MARRIAGESTATUS_WEDDINGONSTREET );

	// ����֪ͨ
	SendWeddingNotify( pMarriageInfo );

	// ���û��������ʱ��
	int tOtherInfo = MESSAGE_MARRIAGE;
	int tTimerID = 0;	
	tTimerID = CTimerMng::GetSingleton().SetTimer( pMarriageInfo->GetServerSequence(), TIMER_WEDDING, pMarriageInfo->GetWeddingTimeLength()*1000, 1, &tOtherInfo );	
	CMarriageManager::GetSingleton().SetWeddingTimer( TIMER_WEDDING, tTimerID );

	// ���û���ʱ֪ͨ�ļ�ʱ��	  TIMER_WEDDINGNOTIFY
	tOtherInfo =  MESSAGE_MARRIAGE;
	tTimerID = CTimerMng::GetSingleton().SetTimer( pMarriageInfo->GetServerSequence(), TIMER_WEDDINGNOTIFY, WEDDING_NOTIFY_INTERVAL*1000, 1, &tOtherInfo, pMarriageInfo->GetWeddingTimeLength()/WEDDING_NOTIFY_INTERVAL );		
	CMarriageManager::GetSingleton().SetWeddingTimer( TIMER_WEDDINGNOTIFY, tTimerID );	 


	// ���û������н�����ʱ��
	tOtherInfo =  MESSAGE_MARRIAGE;
	tTimerID = CTimerMng::GetSingleton().SetTimer( pMarriageInfo->GetServerSequence(), TIMER_WEDDINGONSTREET, WEDDING_ONSTREET_TIMELENGTH*1000, 1, &tOtherInfo );		
	CMarriageManager::GetSingleton().SetWeddingTimer( TIMER_WEDDINGONSTREET, tTimerID );	


	// ���»��������ݿ���Ϣ
	UpDateMarriageInfo( pMarriageInfo );

	// ����npc
	CWeddingNpcInfo *tpWeddingNpcInfo = CMarriageManager::GetSingleton().GetWeddingNpcInfo( pMarriageInfo->GetWeddingModule() );
	LK_ASSERT( tpWeddingNpcInfo != NULL, return )
	for ( int i = 0; i < (int)ARRAY_CNT( tpWeddingNpcInfo->mNpcPathInfo ); ++ i )
	{
		if ( tpWeddingNpcInfo->mNpcPathInfo[i].mNpcTmpID == 0 )
		{
			break;
		}
		unsigned int tEntityID = 0;
		CNpcCreator tCreator;								
		tCreator.set_id(0);
		tCreator.mNpcID = tpWeddingNpcInfo->mNpcPathInfo[i].mNpcTmpID;
		tCreator.mPosition = CWTPoint( tpWeddingNpcInfo->mNpcPathInfo[i].mNpcPath[0].mPosX, tpWeddingNpcInfo->mNpcPathInfo[i].mNpcPath[0].mPosY );						

		CMapModule::GetSingleton().CreateNpc( (unsigned short)CSceneLogic::GetSingleton().GetLineID(), (unsigned short)tpWeddingNpcInfo->mNpcPathInfo[i].mMapID, INVALID_MAP_INDEX, &tCreator, tEntityID );
		CEntityNpc *tpEntity = ( CEntityNpc * )CSceneLogic::GetSingleton().GetEntity( tEntityID ) ;
		if ( tpEntity == NULL )
		{
			LOG_ERROR( "marriage","creat wedding npc error, tempid:%d", tpWeddingNpcInfo->mNpcPathInfo[i].mNpcTmpID );
			continue;
		}			
		CNpcModule::GetSingletonPtr()->OnSleep( tpEntity, false );
		CNpcModule::GetSingleton().OnMoveNpc( tEntityID, tpWeddingNpcInfo->mNpcPathInfo[i].mNpcPath[0].mPosX, tpWeddingNpcInfo->mNpcPathInfo[i].mNpcPath[0].mPosY );
		pMarriageInfo->SetWeddingNpcPosIndex( i, 0 );
		pMarriageInfo->SetWeddingNpcID( i, tpEntity->GetEntityID() );		
	}	
	
	if ( tpBride != NULL )
	{
		CMapModule::GetSingleton().Teleport( (unsigned short)CSceneLogic::GetSingleton().GetLineID(), (unsigned short)tpWeddingNpcInfo->mNpcPathInfo[0].mMapID, tpWeddingNpcInfo->mNpcPathInfo[0].mNpcPath[0].mPosX, tpWeddingNpcInfo->mNpcPathInfo[0].mNpcPath[0].mPosY, tpBride );
	}
		
	if ( tpGroom != NULL )
	{
		CMapModule::GetSingleton().Teleport( (unsigned short)CSceneLogic::GetSingleton().GetLineID(), (unsigned short)tpWeddingNpcInfo->mNpcPathInfo[0].mMapID, tpWeddingNpcInfo->mNpcPathInfo[0].mNpcPath[0].mPosX, tpWeddingNpcInfo->mNpcPathInfo[0].mNpcPath[0].mPosY, tpGroom );	
	}	
}

// ***********************************************************
//  Function:		OnMessageReviewWeddingRequest
//  Description:	���²���������Ϣ����
//  Output:			
//  Date:	05/24/2010					  
// **********************************************************
void CMarriageModule::OnMessageReviewWeddingRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageReviewWeddingRequest *tpMsg = ( CMessageReviewWeddingRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )		
	if ( pPlayer->GetNationality() != CSceneLogic::GetSingleton().GetLineID() )
	{
		return;
	}
	PlayerReviewWedding( pPlayer, tpMsg->weddingmodule(), tpMsg->timeid(), tpMsg->dayid() );
}

// ***********************************************************
//  Function:		SendReviewWeddingResponse
//  Description:	���²���������Ϣ��Ӧ
//  Output:			
//  Date:	05/24/2010					  
// **********************************************************
void CMarriageModule::SendReviewWeddingResponse( CEntityPlayer *pPlayer, int nErrcode )
{
	CMessage tMsgHead;
	CMessageReviewWeddingResponse tMsgReviewWedding;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_REVIEWWEDDING );
	tMsgHead.set_msgpara( (int)&tMsgReviewWedding );
	
	tMsgReviewWedding.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendReviewWeddingNotify
//  Description:	���²���������Ϣ֪ͨ
//  Output:			
//  Date:	05/24/2010					  
// **********************************************************
void CMarriageModule::SendReviewWeddingNotify( CMarriageInfo *pMarriage )
{
	LK_ASSERT( pMarriage != NULL, return )
	CMessage tMsgHead;
	CMessageReviewWeddingNotify tMsgReviewWedding;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_REVIEWWEDDING );
	tMsgHead.set_msgpara( (int)&tMsgReviewWedding );
	
	tMsgReviewWedding.set_brideid( pMarriage->GetBrideID() );
	tMsgReviewWedding.set_groomid( pMarriage->GetGroomID() );
	tMsgReviewWedding.set_bridename( pMarriage->GetBrideName() );
	tMsgReviewWedding.set_groomname( pMarriage->GetGroomName() );
	tMsgReviewWedding.set_weddingtime( pMarriage->GetWeddingTime() );
	tMsgReviewWedding.set_weddingtimelength( pMarriage->GetWeddingTimeLength() );
	tMsgReviewWedding.set_campid( CSceneLogic::GetSingleton().GetLineID() );	
	
	if ( pMarriage->GetWeddingTime() > 0 && pMarriage->GetWeddingModule() == 2 )
	{
		CSceneLogic::GetSingleton().SendWorldMessage( &tMsgHead );
	}
	else
	{
		CSceneLogic::GetSingleton().SendCountryMessage(  &tMsgHead, CSceneLogic::GetSingleton().GetLineID() );	
	}
}

// ***********************************************************
//  Function:		PlayerReviewWedding
//  Description:	������»��߲������
//  Output:			
//  Date:	05/24/2010					  
// **********************************************************
void CMarriageModule::PlayerReviewWedding( CEntityPlayer *pPlayer, int nWeddingModule, int nTimeID, int nDayID )
{
	LK_ASSERT( pPlayer != NULL, return )
	
	if( pPlayer->GetMarriageID() <= 0 )
	{
		SendReviewWeddingResponse( pPlayer, EM_MARRIAGE_REVIEWWEDDING_NOTMARRY );
		return;
	} 
	
	CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
	if ( tpMarriageConfig == NULL )
	{
		LOG_ERROR( "marriage","wrong marriage config template" );
		return;
	}	
	
	CMarriageInfo *tpMarriageInfo = CMarriageManager::GetSingleton().GetMarriageInfo( pPlayer->GetMarriageID() );
	if ( tpMarriageInfo == NULL )
	{	 
		LOG_ERROR( "marriage","[%d] can not find marriage info by id:%d, roleid:%d ",__LINE__, pPlayer->GetMarriageID(), pPlayer->GetCharID() );
		SendReviewWeddingResponse( pPlayer, EM_MARRIAGE_REVIEWWEDDING_NOTMARRY );
		return;
	}
	
	// �ж���û�л������
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();	
	if ( tpProperty->GetBaggage()->HasItem( tpMarriageConfig->mWeddinInfo[nWeddingModule].mWeddingScroll, 1, BIND_ALL ) == false )
	{
		SendReviewWeddingResponse( pPlayer, EM_MARRIAGE_REVIEWWEDDING_HASNOWEDDINGSCROLL );
		return;
	}
	
	// �жϽ��״̬
	int tWeddingStatus = tpMarriageInfo->GetWeddingStatus();
	if ( tWeddingStatus !=  WEDDINGSTATUS_NOTSET && tWeddingStatus != WEDDINGSTATUS_EXPIRED && tWeddingStatus != WEDDINGSTATUS_FINISHED )
	{
		SendReviewWeddingResponse( pPlayer, EM_MARRIAGE_REVIEWWEDDING_WRONGSTATUS );
		return;
	}
	
	
	
	// �����ģ�Ƿ�Ϸ�
	if ( nWeddingModule < 0 || nWeddingModule >= MAX_WEDDING_MODULENUM )
	{
		return;
	}
	
	// ����ʱ��
	int tTimeNow = time( NULL );	
	CWeddingSysTime *tpSysTime = CMarriageManager::GetSingleton().GetWeddingTimeInfo( nTimeID );
	if ( tpSysTime == NULL )
	{
		LOG_ERROR( "marriage","[%s,%d] wrong timeid:%d, roleid:%d  ",__FUNCTION__,__LINE__ , nTimeID, pPlayer->GetCharID() );
		return;
	}
	
	tm *tpLocalTime = NULL;
	if ( nDayID == 0 )
	{
		tpLocalTime = localtime( (time_t*)&tTimeNow );
	}
	else if ( nDayID == 1 )
	{
		tTimeNow +=	DAYSECOUNDS;
		tpLocalTime = localtime( (time_t*)&tTimeNow );		
	}
	else if ( nDayID == 2 )
	{
		tTimeNow +=	DAYSECOUNDS*2;
		tpLocalTime = localtime( (time_t*)&tTimeNow );		
	}
	else
	{
		LOG_ERROR( "marriage","[%s,%d] wrong dayid:%d, roleid:%d", __FUNCTION__, __LINE__, nDayID, pPlayer->GetCharID() );
		return;
	}	
	
	if ( nTimeID == 0 && tpSysTime->mCommonAllowed == 1 )
	{
		LOG_ERROR( "marriage","[%s,%d] wedding module wrong , roleid:%d", __FUNCTION__, __LINE__, pPlayer->GetCharID() );		
		SendReviewWeddingResponse( pPlayer, EM_MARRIAGE_MARRYAPPLY_WRONGMODULE );
		return;
	}	 	
	
	tpLocalTime->tm_hour = tpSysTime->mBeginTime;
	tpLocalTime->tm_min = 0;
	tpLocalTime->tm_sec = 0;
	int tWeddingTime = mktime( tpLocalTime );		
	int tTimeLength = tpMarriageConfig->mWeddinInfo[nWeddingModule].mWeddingLength*60; 	
	
	if ( CMarriageManager::GetSingleton().CheckWeddingTime( tWeddingTime, tTimeLength ) == false )
	{
		SendReviewWeddingResponse( pPlayer, EM_MARRIAGE_REVIEWWEDDING_TIMESELECTED );
		return;
	}
	 
	if ( tWeddingTime - tpMarriageInfo->GetWeddingTime() <= DAYSECOUNDS/2 )
	{
		SendReviewWeddingResponse( pPlayer, EM_MARRIAGE_REVIEWWEDDING_WEDDINGCOOLTIME );
		return;
	}
	
	if ( tWeddingTime - time(NULL) <= VALIDTIMELENGTH_TOWEDING )
	{
		SendReviewWeddingResponse( pPlayer, EM_MARRIAGE_REVIEWWEDDING_TIMETOONEAR );
		return;
	}
	
	// �鿴�����ռ��Ƿ��㹻
	if ( tpProperty->GetBaggage()->Space( -1, 1 ) == false  )
	{
		SendReviewWeddingResponse( pPlayer, EM_MARRIAGE_REVIEWWEDDING_NOSPACE );
		return;
	}	 	 
	
	bool tBind = false;
	uint64_t tGuID = 0;
	CPropertyModule::GetSingleton().PlayerRemoveItemByID( pPlayer, tpMarriageConfig->mWeddinInfo[nWeddingModule].mWeddingScroll, 1, tBind, &tGuID );		
	LogEventLostItemByUse( pPlayer, tGuID, tpMarriageConfig->mWeddinInfo[nWeddingModule].mWeddingScroll, 1 );
	CPropertyModule::GetSingleton().PlayerInsertItem( pPlayer, tpMarriageConfig->mWeddinInfo[nWeddingModule].mInvitationCardID,
		tpMarriageConfig->mWeddinInfo[nWeddingModule].mInvitationCardNum*2 );
	LOG_INFO( "marriage","[%d] player roleid:%d reviewwedding at time:%d ",__LINE__, pPlayer->GetCharID(), tWeddingTime );
	tpMarriageInfo->SetWeddingTime( tWeddingTime );
	tpMarriageInfo->SetWeddingTimeLength( tTimeLength );
	tpMarriageInfo->SetMarriageStatus( MARRIAGESTATUS_WEDDINGINWAIT );
	SendReviewWeddingResponse( pPlayer, SUCCESS );	
	SendReviewWeddingNotify( tpMarriageInfo );	
	UpDateMarriageInfo( tpMarriageInfo );
}