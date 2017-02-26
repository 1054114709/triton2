#include "stdafx.hpp"
#include "activitymodule.h"
#include "westserver.h"
#include "servercore.h"
#include "entity.h"
#include "servertool.h"
#include "property.h"
#include "message_pb.hxx.pb.h"
#include "coremessage_pb.hxx.pb.h"
#include "promessage_pb.hxx.pb.h"
#include  "sceneobj_manager.h"
#include "propertymodule.h"	
#include "template.h"
#include "activitymessag_pb.hxx.pb.h"
#include "timer_define.h"
#include "errcode.h"
#include "scenecfg_manager.h"
#include "sceneobj_manager_imp.h"
#include "scenelogic.h"
#include "corpsmodule.h"
#include "logmodule.h"
#include "taskmodule.h"
#include "achievemodule.h"
#include "entity_searcher.h"
#include "entity_searcher_imp.h"
#include "mailmodule.h"
#ifdef LEAK_CHK_DEBUG_NEW
#include "debug_new.h"
#include "ActivityYqs.h"
#include "ActivityYqsCfg.h"
#endif

template<> CActivityModule  * CSingleton< CActivityModule >::spSingleton = NULL;

// ģ����
 char CActivityModule::sModuleName[ NAME_LENGTH ]="ActivityModule";	 

// ***********************************************************
//  Function:		CountSize
//  Description:	
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// **********************************************************
unsigned int CActivityModule::CountSize(  )
{
	unsigned int tSize = sizeof( CActivityModule );	
	return tSize;
}

// ***********************************************************
//  Function:		OnLaunchServer
//  Description:	����������
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// ********************************************************** 
void CActivityModule::OnLaunchServer( )
{	
    // ��ʼ��ҡǮ����־��Ϣ
    CActivityYqs::GetSingleton().Initialize();

	OnLoadConfig();
   
	// ���������� ���ļ���ȡ�ϴΰٻ�����ˢ��ʱ��
	FILE* fp=fopen("weekcharm.timer", "r");
	if ( fp != NULL )
	{
		fscanf(fp, "%d", &mLastClearWeekCharmTime);
		fclose(fp);
	}
}


// ***********************************************************
//  Function:		OnExitServer
//  Description:	�˳�������
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// **********************************************************	  
void CActivityModule::OnExitServer( )
{

}		 

// ***********************************************************
//  Function:		OnTimer
//  Description:	������Timer
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// **********************************************************  
void CActivityModule::OnTimer( unsigned int vTickCount, unsigned int vTickOffsekt )
{  
	if ( mTimer.Elapse( vTickOffsekt ) == true )
	{
		CheckInvestTime( );
	}
	if( mHydrangeaTimer.Elapse( vTickOffsekt ) == true )
	{
		CheckHydrageaActivityTime();
		CheckNpcPath();
	}	
	if ( mInvestRecordTimer.Elapse( vTickOffsekt ) == true )
	{
		WriteInvestResultToFile();
	}
	if ( mDoubleActive == true )
	{
		/*if ( mDoubleTimer.Elapse( vTickOffsekt ) == true )*/
		if( mEndTime < (unsigned int) time(NULL) )
		{
			mDoubleActive = false;
			mDoubleIndex = -1;
			CPropertyModule::GetSingletonPtr()->FireActivityDiploid( NULL, 0, true );
		}
	}
	for ( int i = 0; i < mNpcNum; i++ )
	{
		if ( mNpcInfo[ i ].mState == STATE_SUBMITTING )
		{
			if ( mNpcInfo[ i ].mSubmitTimer.Elapse( vTickOffsekt ) == true )
			{
				mNpcInfo[ i ].mState = STATE_FIGHTING;
				// ֪ͨ��س�Ա����ս��
				SendMsgBattleStart( mNpcInfo[ i ].mNpcID );
				mNpcInfo[ i ].mWarTimer = CWTimer( MAXFIGHTTIME * 60 * 1000 );
				LOG_INFO("activity", "NPC %d battle", mNpcInfo[ i ].mNpcID);
			}
			if ( mNpcInfo[ i ].mNotifyTimer.Elapse( vTickOffsekt ) == true )
			{
				SendMsgBidTimeOut( mNpcInfo[ i ].mNpcID, 0 );
			}
		}
#ifndef _GATE_CTRL_CORPS_	//�򿪴˺궨����رվ��ž��۽�����ѯ����GateServerʵ�ִ˹���
		CCorpsModule::GetSingleton().OnStartFireBattleTimer( mNpcInfo[ i ].mEntityID );
#endif
		if ( mNpcInfo[ i ].mState == STATE_FIGHTING )
		{
			if ( mNpcInfo[ i ].mWarTimer.Elapse( vTickOffsekt ) == true )
			{
				mNpcInfo[ i ].mState = STATE_BIDDING;
				LOG_INFO("activity", "NPC %d end", mNpcInfo[ i ].mNpcID);
			}
		}
	}
}

// ***********************************************************
//  Function:		OnCreateMap
//  Description:	��������
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// ********************************************************** 
int CActivityModule::OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName )
{
	return SUCCESS;	
}

// ***********************************************************
//  Function:		OnRouterMessage
//  Description:	·����Ϣ
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::OnRouterMessage( CMessage* pMessage )
{
	
}

// ***********************************************************
//  Function:		OnClientMessage
//  Description:	�ͻ��˷�����Ϣ
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// ********************************************************* 
void CActivityModule::OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	switch( pMessage->mutable_msghead()->messageid() )
	{
		case ID_C2S_REQUEST_CHECKANSWER:
		{
			OnMessageCheckAnswer( pPlayer, pMessage );
		}	
		break;
		case ID_C2S_NOTIFY_QUESTIONTIMEREND:
		{
			OnMessageQuestionTimeEnd( pPlayer, pMessage );		
		}
		break;	
		
		case ID_C2S_NOTIFY_IFANSWERNOW:
		{
			OnMessageIfAnswerNow( pPlayer, pMessage );	
		}
		break;
		
		case ID_C2S_NOTIFY_IFBEGINQUEST:
		{
		
			OnMessageIfBeginQuest( pPlayer, pMessage );
		}
		break;
		case ID_C2S_NOTIFY_STOPANSWER:
		{
			OnMessageStopAnswer( pPlayer, pMessage );	
		}		
		break;
		case ID_C2S_NOTIFY_USEQUESTIONPAPER:
		{
			OnMessageUsePaper( pPlayer, pMessage );
		}
		break;
		case ID_C2S_NOTIFY_INVESTANSWER:
		{
			OnMessageInvestAnwerNotify( pPlayer, pMessage );
		}
		break;
		
		case ID_C2S_REQUEST_GRABHYDRANGEA:
		{
			OnMessageGrabeHydrangeaRequest( pPlayer, pMessage );
		}
		break;
		
		case ID_C2S_REQUEST_THROWHYDRANGEA:
		{
			OnMessageThrowHydrangeaRequest( pPlayer, pMessage );
		}
		break;

        case ID_C2S_HANDIN_REQUEST:
        {
            CActivityYqs::GetSingleton().OnMessageHandinRequest( pPlayer, pMessage );
        }
        break;
        case ID_C2S_GETCAMPRANKFORYQS_REQUEST:
        {
            CActivityYqs::GetSingleton().OnMessageGetCampRankInfoForClient( pPlayer,pMessage );
        }
        break;
        case ID_C2S_GETPLAYERRANKFORYQS_REQUEST:
        {
            CActivityYqsPlayerRankInfo::GetSingleton().OnMessageGetPlayerRankInfoRequest( pPlayer, pMessage );
        }
        break;
		
		case ID_C2S_REQUEST_ANSWERVERIFY:
		{
			OnMessageAnswerVerifyRequest( pPlayer, pMessage );
		}
		break;
		case ID_C2S_GETGIFT_REQUEST:
		{
			OnMessagePlayerGetGiftRequest( pPlayer, pMessage );
			break;
		}
		case ID_C2S_REQUEST_GETTREASUREBOWLINFO:
		{
			OnMessageGetTreasureBowl( pPlayer, pMessage );
			break;	
		}
		case ID_C2S_REQUEST_STARTTREASUREBOWL:
		{
			OnMessageStartTreasureBowl( pPlayer, pMessage );
			break;
		}
		default:
			break;
	}		
}

// ***********************************************************
//  Function:		OnCreateEntity
//  Description:	����ʵ��
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::OnCreateEntity( CEntity* pEntity , CCreator* pCreator, bool vFirst )
{	
	LK_ASSERT(pEntity != NULL, return )	
	if ( pEntity->IsPlayer() )
	{
		CPropertyPlayer  *tpProperty = ( CPropertyPlayer  * )pEntity->GetProperty();
		CAnswerStatus  *tpAnserStatus = ( CAnswerStatus *)CSceneObjManager::GetSingletonPtr()->CreateObject( OBJTYPE_ANSWERSTATUS );
		if ( tpAnserStatus == NULL )
		{
			tpProperty->SetAnswerStatusObjID( -1 );
			return;
		}
		tpProperty->SetAnswerStatusObjID( tpAnserStatus->get_id() );	
		Send2PlayerNowActivitys(( CEntityPlayer * )pEntity);

		OnlineGift4CreateEntity( (CEntityPlayer*)pEntity, HELPID_ONLINEGIFT, vFirst );
		// �ͺ���2�� �ȼ��ͺ��� 
		OnlineGift4CreateEntity( (CEntityPlayer*)pEntity, HELPID_ONLINEGIFT2, vFirst );


		// ����ϴδ���ʱ����ˢ��֮ǰ������ձ��ܵ�����ֵ����ֵ
		if (tpProperty->mActivityInfo.mLastSave <= mLastClearWeekCharmTime )
		{
			if ( mLastClearWeekCharmTime - tpProperty->mActivityInfo.mLastSave < 7*24*3600 ) // ���1������ 
				tpProperty->SetLastWeekIncCharm(tpProperty->GetWeekIncCharm());
			else
				tpProperty->SetLastWeekIncCharm(0);

			tpProperty->SetWeekIncCharm(0);
			LOG_ERROR( "Activity", "#ACT clear chm in create char:%d", ((CEntityPlayer*)pEntity)->GetCharID() );	
		}
	}			
	else if ( pEntity->IsOgre() || pEntity->IsFunNpc() )
	{
		if ( pCreator == NULL )
		{
			return;
		}
		CProperty *tpProperty = pEntity->GetProperty();
		CheckOgreActivityInfoOnCreate( tpProperty->GetPropertyTempID(), pEntity->GetEntityID() );	 
				
		// ���ｫ��ɱ������һ�������֪ͨ
		COgreInfo *tpOgreInfo = mOgreActivityManager.GetOgreInfo( tpProperty->GetPropertyTempID() );		
		if ( tpOgreInfo != NULL )
		{
			if (tpOgreInfo->mBossOgre == 1 )
			{
				COgreCreator *tpOgreCreator = ( COgreCreator * )pCreator;
				CCreator* tpCreator = CCreatorManager::GetSingletonPtr()->GetCreator( tpOgreCreator->mMaxEnmity );
				if ( tpCreator != NULL && tpOgreCreator->mMaxEnmity > 0 )
				{
					CEntityCharacter *tpDesEntity = (CEntityCharacter*)CSceneObjManager::GetSingletonPtr( )->GetObject( tpCreator->mHasOgre );
					if ( tpDesEntity != NULL )
					{
						CProperty *tpDesProperty = tpDesEntity->GetProperty();
						int tIntParam[ 2 ] = { 0 };
						tIntParam[ 0 ] = tpProperty->GetPropertyTempID();
						tIntParam[ 1 ] = tpDesProperty->GetPropertyTempID();								
						CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_OGREKILLBOSSPRENOTICE, pEntity->GetLineID(), tIntParam, ARRAY_CNT(tIntParam), NULL, NULL );											
					}
				}					
			}	
		}		
	}
}


void CActivityModule::OnlineGift4CreateEntity(CEntityPlayer* pPlayer, int nActivityID, bool vFirst )
{
	std::vector<int> tIntParams;
	tIntParams.push_back(pPlayer->GetEntityID());
	CPropertyPlayer  *tpProperty = ( CPropertyPlayer  * )pPlayer->GetProperty();
	SinglePlayerActivityInfo* tpInf = tpProperty->GetActivityInfo( nActivityID );
	if (tpInf == NULL)
	{
		tIntParams.push_back(0);
		tIntParams.push_back(0);
	}
	else
	{
		tIntParams.push_back(tpInf->nState);
		// ����������� �����ϴ����ߴ���ʱ�������� �����������ʱ�����
		//if ( vFirst )
		//{
			// ԭ������ʵ����ֻ��¼�˸���״̬ʱ�䵽�ϴα���ʱ�� ���������ĳ���ʱ��  ����ѧ
			tIntParams.push_back( tpInf->GetDuringTime(pPlayer) ); //tpProperty->mActivityInfo.mLastSave -tpInf->chg_tm);
		//}
		//else
		//{
			// ���ֵӦ�����ϴ����ߵ����ڵġ���
		//	LOG_DEBUG("Activity", "KF:tm0:%d, tm:%d", time(0),tpInf->chg_tm );
		//	tIntParams.push_back(time(0)-tpInf->chg_tm);
	//	}
	}

	tIntParams.push_back(vFirst);
	tIntParams.push_back(nActivityID);
	std::vector<std::string> tStrParams;
	FireActivityEvent(nActivityID, ACTIVITY_ACTION_ONCREATE, tIntParams, tStrParams );
}

// ***********************************************************
//  Function:		OnDestroyEntity
//  Description:	����ʵ��
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************  
void CActivityModule::OnDestroyEntity( CEntity* pEntity, int vCode )
{
	LK_ASSERT( pEntity != NULL, return )
	if ( pEntity->IsPlayer() )
	{
		CPropertyPlayer *tpProperty =( CPropertyPlayer * ) pEntity->GetProperty(); 		
		CAnswerStatus *tpAnswer = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject( tpProperty->GetAnswerStatusObjID() );
		if ( tpAnswer == NULL )
		{						
			return;
		}	
		
		if ( tpAnswer->GetRoleverifyType() == VERIFYKIND_NULL )
		{
			CSceneObjManager::GetSingleton().DestroyObject(  tpProperty->GetAnswerStatusObjID() );
			return;
		}

		NotifyQuestionVerifyResult( ( CEntityPlayer * )pEntity, tpAnswer->GetRoleVerifyKind(), false, VERIFYREASON_OFFLINE ); 		
			
		CSceneObjManager::GetSingleton().DestroyObject(  tpProperty->GetAnswerStatusObjID() );
	}
	else if ( pEntity->IsOgre() )
	{		
		CProperty *tpProperty = pEntity->GetProperty();
		CheckOgreActivityInfoOnDeath( tpProperty->GetPropertyTempID(), 0  );
	}
}

// ***********************************************************
//  Function:		OnSaveData
//  Description:	�洢����
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************   
bool CActivityModule::OnSaveData( CEntityPlayer* pPlayer, int vSaveCode )
{
	CPropertyPlayer *tpProperty =( CPropertyPlayer * )pPlayer->GetProperty(); 	
	// ��������� ���ǿ�� ���ۼ�����ʱ��
	//if ( vSaveCode == SAVE_RETURN2GATE || vSaveCode == SAVE_LEAVEGAME || vSaveCode == SAVE_KICKOUT || vSaveCode == SAVE_FORCEEXIT )
	//{
		//for ( ACTIVITYINFO_TYPE::iterator it = tpProperty->mActivityInfo.mStates.begin(); it != tpProperty->mActivityInfo.mStates.end(); ++it )
		//{
		//	it->second.nRealLastedTime += (time(0)-pPlayer->GetLastLoginTime());
		//	LOG_ERROR( "Activity","%d----%d", it->first, it->second.nRealLastedTime );
		//}
	//}
	PBGuideData data;
	tpProperty->GetGuideData()->GetPB(&data);
	CMessagePlayerProperty* tpSave = CSceneLogic::GetSingletonPtr( )->GetSavePlayerProperty( );
	tpSave->mutable_role_guide()->CopyFrom( data );
	return true;
}

// ***********************************************************
//  Function:		OnLoadConfig
//  Description:	��������
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************  
void CActivityModule::OnLoadConfig( )
{ 
	ACTIVITY_LOG* tpCfg = CSceneCfgManager::GetSingletonPtr( )->GetActivity_log( );
	if( tpCfg != NULL )
	{
		INIT_ROLLINGFILE_LOG( tpCfg->mIdentifier, tpCfg->mDirectory, (LogLevel)tpCfg->mPriority, tpCfg->mMaxfilesize, tpCfg->mMaxbackupindex);
	}
	/*InitialQuestionFile( "../config/data/activity/QuestionLib.xml" );
	InitailInvestQuestionFile( "../config/data/activity/InvestConf.xml" );
	InitialDoubleExpFile( "../config/data/activity/DoubleExp.xml" );	
	InitialHydrangea("../config/data/activity/Hydranagea.xml");
	InitialOgreActivityConfig("../config/data/activity/OgreActivity.xml");*/
	
	InitialQuestionFile(CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/QuestionLib.xml" ));
	const char* pcConfigPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/QuestionLib.xml" );
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CActivityModule::LoadQuestionFileCallback);

	InitailInvestQuestionFile( CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/InvestConf.xml" ));
	pcConfigPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/InvestConf.xml" );
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CActivityModule::LoadInvestQuestionFileCallback);

	InitialDoubleExpFile( CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/DoubleExp.xml" ));	
	pcConfigPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/DoubleExp.xml" );
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CActivityModule::LoadDoubleExpFileCallback);

	InitialHydrangea(CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/Hydranagea.xml"));
	pcConfigPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/Hydranagea.xml");
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CActivityModule::LoadHydrangeaCallback);

	InitialOgreActivityConfig(CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/OgreActivity.xml"));
	pcConfigPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/OgreActivity.xml");
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CActivityModule::LoadOgreActivityConfigCallback);
	
	InitialTreasureBowlConfig();
	pcConfigPath =  CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/TreasureBowl.xml" );
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CActivityModule::LoadTreasureBowlConfigCallback);
	
	GetInvestResult();
	
	RegisterLua();
	const char* pcDirPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity" );
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcDirPath, ".lua", CActivityModule::LoadLuaFileCallback);
	
    // ��ȡҡǮ���������Ϣ
    CActivityYqsCfg::GetSingleton().LoadConfigure();
	pcConfigPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/ActivityYQS.xml");
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CActivityModule::LoadActivityYqsConfigCallback);
	
	ReadRoleValidQuestionConfig();
	pcConfigPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"question/config.xml");
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CActivityModule::LoadRoleValidQuestionConfigCallback);

}

bool CActivityModule::RegisterLua()
{
	if(L) lua_close(L); L = NULL;
	L = lua_open( );
	if (L == NULL)
	{
		printf("ACT open LUA state failed");
		exit(0);
	}
	luaL_openlibs( L );
	//lua_tinker::dofile(L, "../config/data/activity/lucky_bag_cfg.lua");
	//lua_tinker::dofile(L, "../config/data/activity/lucky_bag_main.lua");
	//lua_tinker::dofile(L, "../config/data/activity/activity.lua");
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/lucky_bag_cfg.lua"));
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/lucky_bag_main.lua"));
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/activity.lua"));

	lua_tinker::def(L, "GetPlayerLevel",				&CActivityModule::GetPlayerLevel);
	lua_tinker::def(L, "GetPlayerMetier",				&CActivityModule::GetPlayerMetier);
	lua_tinker::def(L, "GetPlayerBagSpaceNum",			&CActivityModule::GetPlayerBagSpaceNum);
	lua_tinker::def(L, "InsertItem",					&CActivityModule::InsertItem);
	lua_tinker::def(L, "SendErrNotice",					&CActivityModule::SendErrNotice);
	lua_tinker::def(L, "Log_Error",						&CActivityModule::Log_Error);
	lua_tinker::def(L, "GetPlayerGender",				&CActivityModule::GetPlayerGender);
	lua_tinker::def(L, "SendSysMail",					&CActivityModule::SendSysMail);
	lua_tinker::def(L, "GetCampID",						&CActivityModule::GetCampID);
	lua_tinker::def(L, "ChangeAllActivityState",		&CActivityModule::ChangeAllActivityState);
	lua_tinker::def(L, "ChangeSingleActivityState",		&CActivityModule::ChangeSingleActivityState);
	lua_tinker::def(L, "GetActivityState",				&CActivityModule::GetActivityState);
	lua_tinker::def(L, "EntityInsertBuff",				&CActivityModule::EntityInsertBuff);
	lua_tinker::def(L, "EntityTeleport",				&CActivityModule::EntityTeleport);
	lua_tinker::def(L, "CheckPileLimit",				&CActivityModule::CheckPileLimit);
	lua_tinker::def(L, "NotifyGetGiftResult",			&CActivityModule::NotifyGetGiftResult);
	
	return true;
}


// ***********************************************************
//  Function:		OnTimeoutMessage
//  Description:	��ʱ����ʱ��Ϣ
//  Input:		
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// ********************************************************* 
void CActivityModule::OnTimeoutMessage( CMessage* pMessage )
{	
	CTimerItem* pTimerItem = (CTimerItem*) pMessage->msgpara();
	LK_ASSERT( pMessage != NULL, return );
	switch( pTimerItem->mTimerMark ) 	
	{ 
		case TIMER_ANSWERSTATUS_TOTALTIMEEND:
		{
			OnMsgTotalQuestTimeOut( pTimerItem );
		}
		break;		
		case TIMER_ANSWERSTATUS_SINGLETIMEEND:
		{
			OnMsgSingleQuestTimeOut( pTimerItem );
		}
		break;			
		
		
		case TIMER_HYDRANGEATHROW:
		{
			OnTimeOutHydrangeaThrow( pTimerItem );
		}
		break;
		
		case TIMER_HYDRANGEAHOLD:
		{
			OnTimeOutHydrangeaHold( pTimerItem );
		}
		break;
		
		case TIMER_HYDRANGEAGRAB:
		{
			OnTimeOutHydrangeaGrab( pTimerItem );
		}
		break;
			
		case TIMER_HYDRANGEAACTIVITY:
		{
			OnTimeOutHydrangeaActivity( pTimerItem );
		}
		break;
		
		case TIMER_HYDRANGEASUGAR:
		{
			OnTimeOutHydrangeaSugar( pTimerItem );			
		}
		break; 		
		
		case TIMER_OGREACTIVITY_TIMEEND:
		{
			EndOgreActivity( pTimerItem );
		}
		break;
		
		case TIMER_QUESTIONVERIFY:
		{
			OnTimeOutAnswerVerify( pTimerItem );
		}
		break;				
		default:
		break;
	}
}
// ***********************************************************
//  Function:		InitialQuestionFile
//  Description:	��ʼ������ļ�
//  Input:			const char *pFileName
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
int CActivityModule::InitialQuestionFile( const char *pDir )
{
	LK_ASSERT( pDir!=NULL, return -1);
	
	TiXmlDocument tDoc;
	TiXmlElement  *pRootElement		= NULL;
	TiXmlElement  *pLibElement		= NULL; 
	TiXmlElement  *pQuestElement	= NULL;
	
	//*/LK_ASSERT( tDoc.LoadFile( "../config/data/activity/QuestionLib.xml" ) == true, return -1 );	
	LK_ASSERT( tDoc.LoadFile( CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"activity/QuestionLib.xml") ) == true, return -1 );	

	pRootElement = tDoc.FirstChildElement();
	if ( pRootElement == NULL )
	{
		return -1;
	}
	TiXmlElement *tpQuestionLib = pRootElement->FirstChildElement( "LIBRARY_QUESTIONLIB" );
	if ( tpQuestionLib == NULL )
	{
		return -1;
	}
	
	mQuestionMng.Initialize();
	
	// �Ƚϸ��ڵ�
	for ( pLibElement =  tpQuestionLib->FirstChildElement( "LIBRARY" ); pLibElement != NULL; pLibElement = pLibElement->NextSiblingElement( "LIBRARY" ) )
	{			
		// ��ȡ���id������		
		mQuestionMng.AddNewLib( atoi(pLibElement->Attribute( "ID" )), pLibElement->Attribute( "AppType" ) );
		for ( pQuestElement = pLibElement->FirstChildElement(); pQuestElement != NULL; pQuestElement = pQuestElement->NextSiblingElement( ) )
		{
			// ��ȡ��Ŀid�ʹ�
			mQuestionMng.AddQuestion( pQuestElement->Attribute("ID"), pQuestElement->Attribute("Answer") );
		}			
	}	
	
	TiXmlElement *tpNpcPrizeElement = pRootElement->FirstChildElement( "NpcPrize" );
	if ( tpNpcPrizeElement == NULL )
	{
		return 1;
	}
	
	CItemPrize tItemPrize;
	TiXmlElement *tpPrize = tpNpcPrizeElement->FirstChildElement( "Item" );
	for ( ; tpPrize != NULL; tpPrize = tpPrize->NextSiblingElement( "Item" ) )
	{
		tItemPrize.ItemPrizeID = atoi( tpPrize->Attribute( "ID" ) );
		tItemPrize.ItemPrizeNum = atoi( tpPrize->Attribute( "Num" ) );
		mQuestionMng.InsertNpcPrize( tItemPrize );	
	}
	
	return 1;	
}  

// ***********************************************************
//  Function:		OnMessageIfBeginQuest
//  Description:	�Ƿ�ʼ����
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::OnMessageIfBeginQuest( CEntityPlayer *tpPlayer, CMessage * pMessage )
{	   	
	LK_ASSERT( tpPlayer != NULL, return );
	CMessageIfBeginQuest *tpMsg = ( CMessageIfBeginQuest * )pMessage->msgpara( );
	LK_ASSERT( tpMsg != NULL, return )	;
	PlayerBeginQuestion( tpPlayer, tpMsg->ifbegin() );
}

// ***********************************************************
//  Function:		OnMessageCheckAnswer
//  Description:	������ϢOnMessageCheckAnswer
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::OnMessageCheckAnswer( CEntityPlayer *tpPlayer, CMessage * pMessage )
{		
	LK_ASSERT( tpPlayer != NULL && pMessage != NULL, return );
	CMessageCheckAnswerRequest *tpCheckAnswer = ( CMessageCheckAnswerRequest * )pMessage->msgpara();	
	LK_ASSERT( tpCheckAnswer != NULL, return );
	PlayerCheckAnswerRequest( tpPlayer, tpCheckAnswer->questionid(), tpCheckAnswer->answer() );
}  

//***********************************************************
//  Function:		OnMessageQuestionTimeEnd
//  Description:	
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::OnMessageQuestionTimeEnd(CEntityPlayer *tpPlayer, CMessage * pMessage)
{	
	LK_ASSERT( tpPlayer != NULL && pMessage != NULL, return );
	CMessageQuestionTimeEnd *tpQuestTimeEnd = ( CMessageQuestionTimeEnd * )pMessage->msgpara();	
	LK_ASSERT( tpQuestTimeEnd != NULL, return );
	StopCurrentQuestion( tpPlayer, tpQuestTimeEnd->questionid() );
}


// ***********************************************************
//  Function:		OnMessageIfAnswerNow
//  Description:	
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************

void CActivityModule::OnMessageIfAnswerNow( CEntityPlayer *tpPlayer, CMessage * pMessage )
{
	LK_ASSERT( tpPlayer != NULL && pMessage != NULL, return );
	CMessageIfAnswerNow *tpMsgIfAnswerNow = ( CMessageIfAnswerNow * )pMessage->msgpara();	
	LK_ASSERT( tpMsgIfAnswerNow != NULL, return );
	PlayerBeginPaperQuest( tpPlayer, tpMsgIfAnswerNow->result( ) );
}

// ***********************************************************
//  Function:		OnMsgTotalQuestTimeOut
//  Description:	�������ʱ�䵽
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::OnMsgTotalQuestTimeOut( CTimerItem* pTimerItem )
{	
	LK_ASSERT( pTimerItem != NULL, return );
	LK_ASSERT(  pTimerItem->mOtherInfoLength == 2, return );
	int CharID = pTimerItem->mOwnerID;	
	CEntityPlayer *tpPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetPlayerByCharID( CharID );	
	LK_ASSERT( tpPlayer != NULL, return );
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();	
	CAnswerStatus *tpAnswer = ( CAnswerStatus* )CSceneObjManager::GetSingleton().GetObject( tpProperty->GetAnswerStatusObjID() );
	LK_ASSERT( tpAnswer != NULL, return );									 	
	LK_ASSERT( tpAnswer->GetAppType() == pTimerItem->mOtherInfo[1], return );
	EndAnswerQuestion( tpPlayer, tpAnswer, pTimerItem->mOtherInfo[1] );	
	CTimerMng::GetSingleton().ClearTimer( pTimerItem->get_id() );			 
}

// *********************************************************
//  Function:		OnMsgSingleQuestTimeOut
//  Description:	�������ʱ�䵽
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************  
void CActivityModule::OnMsgSingleQuestTimeOut( CTimerItem* pTimerItem )
{
	LK_ASSERT( pTimerItem != NULL, return );
	CEntityPlayer *tpPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetPlayerByCharID( pTimerItem->mOwnerID );
	LK_ASSERT( tpPlayer != NULL, return );
	CPropertyPlayer *pProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	CAnswerStatus *tpAnswer = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject( pProperty->GetAnswerStatusObjID() );
	LK_ASSERT( tpAnswer != NULL, return );
	
	// ��ȡ����ĿID
	int NewQuestionID = tpAnswer->GetNewQuestID();
	
	// û������Ŀ����������
	if ( NewQuestionID == -1 )
	{
		EndAnswerQuestion( tpPlayer, tpAnswer, tpAnswer->GetAppType() );
	}
	
	// ��������Ŀ
	else
	{
		SendMsgNewQuestion( tpPlayer, NewQuestionID, tpAnswer->GetCurrentQuestIndex() );
	}
} 


//***********************************************************
//  Function:		OnMessageStopAnswer
//  Description:	
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::OnMessageStopAnswer( CEntityPlayer *tpPlayer, CMessage * pMessage )
{
	LK_ASSERT( tpPlayer != NULL && pMessage != NULL, return );
	CMessageStopAnser *tpMsg = ( CMessageStopAnser * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	PlayerStopQuestionAnswer( tpPlayer, tpMsg->endtype() );
}

//***********************************************************
//  Function:		OnMessageStopAnswer
//  Description:	
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::OnMessageUsePaper( CEntityPlayer *tpPlayer, CMessage * pMessage )
{
	LK_ASSERT( tpPlayer != NULL && pMessage != NULL, return );
	CMessageUseQuestionPaper *tpMsg = ( CMessageUseQuestionPaper * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	PlayerUseQuestionPaper( tpPlayer, tpMsg->itemindex() );	
}

// ***********************************************************
//  Function:		PlayerBeginNpcQuest
//  Description:	��ҿ�ʼnpc����
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// ********************************************************* 
void CActivityModule::PlayerBeginNpcQuest( CEntityPlayer *tpPlayer )
{	
	LK_ASSERT( tpPlayer != NULL, return );
	CPropertyPlayer *pProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	CAnswerStatus *tpAnswerStatus = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject( pProperty->GetAnswerStatusObjID() );		
	LK_ASSERT( tpAnswerStatus != NULL, return );
	LK_ASSERT( tpAnswerStatus->GetAppType() == APPTYPE_NPC, return );
	
	// ��մ���״̬�����Ϣ		
	tpAnswerStatus->ClearStatus();					
	 	
	// ������ҵ�ÿ�մ���Ϊ�Ѵ���״̬
	pProperty->SetWelfareStatus( 1 );  	
	
	// ���ô���״̬Ϊnpc����		
	tpAnswerStatus->SetAppType( APPTYPE_NPC );		
			
	// ��ȡ��һ����Ŀ		
	LK_ASSERT( CDataStatic::spRedStoneExpTable != NULL, return );
	CTemplateQuestionExpTable *tpTable = ( CTemplateQuestionExpTable * )CDataStatic::spQuestionExpTable;
	int QuestionNum = mQuestionMng.CreatQuestion( APPTYPE_NPC, tpTable->mNpcQuestionNum, tpAnswerStatus->mQuestionIDSet,
		tpAnswerStatus->mAnswerSet );  	
	if ( QuestionNum <= 0 )
	{	
		LOG_ERROR( "activity","[%s,%d][%s] Get Npc Question Error! ",__LK_FILE__,__LINE__,__FUNCTION__ );	
		tpAnswerStatus->ClearStatus();
		return;
	}		   	

	// ������Ŀ����	
	tpAnswerStatus->SetQuestionNum( QuestionNum );
		
	// ���͵�һ����Ŀ  
	int QuestionID = tpAnswerStatus->GetNewQuestID();		
	if ( QuestionID == -1 )
	{
		// û����Ŀ
		tpAnswerStatus->ClearStatus();
		return;
	}			
	
	// ���ô��ⳬʱ��ʱ��
	
	/*int TimerData[3] ={ 0 };
	
	TimerData[0] = MESSAGE_ACTIVITY;	
	TimerData[1] = APPTYPE_NPC;
	
	int TimerID = tpPlayer->GetTimerReciver()->SetTimer( tpPlayer->GetCharID(),TIMER_ANSWERSTATUS_TOTALTIMEEND,	
	TOTAL_QUESTION_TIMELENGTH,2,TimerData );	
	tpAnswerStatus->SetTotalTimerID( TimerID );
	*/
	SendMsgNewQuestion( tpPlayer, QuestionID, tpAnswerStatus->GetCurrentQuestIndex() );
}

// ***********************************************************
//  Function:		PlayerCheckAnswerRequest
//  Description:	�����Ŀ��
//  Input:			int QuestionID		��ĿID
//  Input:			int Anser		��Ŀ��
//  OutPut:			
//  Return:		
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::PlayerCheckAnswerRequest( CEntityPlayer *tpPlayer, int QuestionID, int Answer )
{	
	LK_ASSERT( tpPlayer != NULL, return );
	CPropertyPlayer *pProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	CAnswerStatus *tpAnswerStatus = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject( pProperty->GetAnswerStatusObjID() );	 	
	LK_ASSERT( tpAnswerStatus != NULL, return );
	int tRet = tpAnswerStatus->CheckAnswer( QuestionID, Answer );		
	if ( tRet == -1 )
	{
		LOG_ERROR( "activity","[%s,%d][%s] Error when check answer of QuestionID:%d",__LK_FILE__,__LINE__,__FUNCTION__,QuestionID );
		return;
	}
	
	// �𰸴��󣬷��;ɵ���Ŀ���ͻ���	
	if ( tRet == 0 )
	{
		//TODO: ���������
		SendMsgCheckAnswer( tpPlayer,QuestionID,tRet,tpAnswerStatus->GetCurrentQuestIndex() );
		return;
	}	  
	
	// ����ȷ����������Ŀ���ͻ���			
	if ( tRet == 1 )
	{		
		// ��ȡ�µ���ĿID
		int NewQuestionID = tpAnswerStatus->GetNewQuestID();
		
		//TODO:	���赥���ʱ��	
		/*if ( tpAnswerStatus->GetSingleTimerID() == 0 )
		{
			
			tpPlayer->GetTimerReciver()->SetTimer( tpPlayer->GetCharID(), TIMER_ANSWERSTATUS_SINGLETIMEEND, 
			EACH_QUESTION_TIMELENGTH );
		}
		else
		{
			 CTimerItem *tpTimer = ( CTimerItem * )CSceneObjManager::GetSingleton().GetObject(
			 tpAnswerStatus->GetSingleTimerID() );
			 if ( tpTimer == NULL )
			 {
				 tpPlayer->GetTimerReciver()->SetTimer( tpPlayer->GetCharID(), TIMER_ANSWERSTATUS_SINGLETIMEEND, 
					 EACH_QUESTION_TIMELENGTH );
			 }
			 tpTimer->mMillSeconds = EACH_QUESTION_TIMELENGTH;
		}*/
		// ������Ŀ�Ѿ�����
		if ( NewQuestionID == -1 )
		{			
			SendMsgCheckAnswer( tpPlayer, NewQuestionID, tRet,  tpAnswerStatus->GetCurrentQuestIndex(), 1 );
			EndAnswerQuestion( tpPlayer, tpAnswerStatus, 1 );												
			return;
		}
		SendMsgCheckAnswer( tpPlayer, NewQuestionID, tRet,  tpAnswerStatus->GetCurrentQuestIndex() );
	}
}



// ***********************************************************
//  Function:		PlayerBeginPaperQuest
//  Description:	��ʼ������
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::PlayerBeginPaperQuest( CEntityPlayer *tpPlayer, int Result )
{
	LK_ASSERT( tpPlayer != NULL, return );
	CPropertyPlayer *pProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	CAnswerStatus *tpAnswer = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject( pProperty->GetAnswerStatusObjID() );	
	LK_ASSERT( tpAnswer != NULL, return );
	if ( tpAnswer->GetAppType() != APPTYPE_QUESTIONPAPER )
	{		
		CPropertyModule::GetSingleton().SendProErrorNotice( tpPlayer, ERR_ACTIVITY_INANSWERSTATUS );
		return;
	}
	CItemObject *tpItemObj = ( CItemObject * )pProperty->GetBaggage()->GetItemObjPtr( tpAnswer->GetPaperIndex() );	
	LK_ASSERT( tpItemObj != NULL, return );
	CTplItem *tpTplItem	= ( CTplItem * )CDataStatic::SearchTpl( tpItemObj->GetItemID() );
	if ( tpTplItem == NULL )
	{
		LOG_ERROR( "activity","[%s,%d][%s] Wrong template id: %d!",__LK_FILE__,__LINE__,__FUNCTION__,tpItemObj->GetItemID() );
		return;
	}  	
	if ( tpTplItem->mItemType != ITEM_QUESTIONPAPER )
	{
		LOG_ERROR( "activity","[%s,%d][%s] Item(id:%d) is not QuestionPaper!",__LK_FILE__,__LINE__,__FUNCTION__,tpItemObj->GetItemID() );
		return;
	}	  		
	CTplQuestionPaper *tpQuestionTable = ( CTplQuestionPaper * )tpTplItem;
	if( Result == 1 )	
	{			
		// ���þ���ӳ�
		tpAnswer->SetExpRate( tpQuestionTable->mExpAddRae );
		
		// ��ȡ��Ŀ����	
		int QuestionNum	= GetQuestNumOfPaper( tpItemObj->GetItemID() );
			
		// �����Ĵ�����������ȷ	
		if( QuestionNum<=0 )	
		{		
			// ������Ʒ		
			pProperty->GetBaggage()->Lock( tpAnswer->GetPaperIndex(), LOCKTYPE_NONE );	
			CPropertyModule::GetSingleton().SendLockItemNotice( tpPlayer,tpAnswer->GetPaperIndex(),	LOCKTYPE_NONE );
											
			// ����״̬	
			tpAnswer->ClearStatus();
			return;		
		}				
		
		// ������Ŀ	
		int QuestNumCreated = mQuestionMng.CreatQuestion( APPTYPE_QUESTIONPAPER,QuestionNum, tpAnswer->mQuestionIDSet, tpAnswer->mAnswerSet );
			 
		// ��������Ŀ��������ȷ		
		if( QuestNumCreated <= 0 )
		{			
			// ������Ʒ	
			pProperty->GetBaggage()->Lock( tpAnswer->GetPaperIndex(), LOCKTYPE_NONE );
			CPropertyModule::GetSingleton().SendLockItemNotice( tpPlayer,tpAnswer->GetPaperIndex(),	LOCKTYPE_NONE );	
			// ����״̬	
  			tpAnswer->ClearStatus();	
			return;	
		}		
	
		// ������Ŀ����	
		tpAnswer->SetQuestionNum( QuestNumCreated );	
		
		// ��ȡ��һ������Ϣ	
		int NewQuestionID = tpAnswer->GetNewQuestID();	
			
		if ( NewQuestionID == -1 )
		{
			// ������Ʒ	
			pProperty->GetBaggage()->Lock( tpAnswer->GetPaperIndex(), LOCKTYPE_NONE ); 
			CPropertyModule::GetSingleton().SendLockItemNotice( tpPlayer,tpAnswer->GetPaperIndex(),	LOCKTYPE_NONE  );						
			// ����״̬			
			tpAnswer->ClearStatus();
			return;		
		}		
		
		// ɾ������	
		uint64_t ullGUID = tpItemObj->GetGUID();
		int nTplID = tpItemObj->GetItemID();
		if (CPropertyModule::GetSingletonPtr()->PlayerRemoveItem( tpPlayer,tpAnswer->GetPaperIndex() , 1 ) == 0)
		{
			LogEventLostItemByUse(tpPlayer, ullGUID, nTplID, 1);
		}
		
		// ���߽���
		pProperty->GetBaggage()->Lock( tpAnswer->GetPaperIndex(), LOCKTYPE_NONE );
		CPropertyModule::GetSingleton().SendLockItemNotice( tpPlayer, tpAnswer->GetPaperIndex(), LOCKTYPE_NONE );

		// TODO: ��ʱ������
		/*int TimerData[3] = {0};
		
		TimerData[0] = MESSAGE_ACTIVITY;
		TimerData[1] = APPTYPE_QUESTIONPAPER;		
		tpPlayer->GetTimerReciver()->SetTimer( tpPlayer->GetCharID(),TIMER_ANSWERSTATUS_TOTALTIMEEND,
		TOTAL_QUESTION_TIMELENGTH,2,TimerData );*/
		SendMsgNewQuestion( tpPlayer, NewQuestionID, tpAnswer->GetCurrentQuestIndex() );
	}	
	else
	{	
		// ������Ʒ	
		pProperty->GetBaggage()->Lock( tpAnswer->GetPaperIndex(), LOCKTYPE_NONE );	
		CPropertyModule::GetSingleton().SendLockItemNotice(tpPlayer,tpAnswer->GetPaperIndex(),LOCKTYPE_NONE );
				
		// ����״̬	
		tpAnswer->ClearStatus();
	}
}

// ***********************************************************
//  Function:		StopCurrentQuestion
//  Description:	ֹͣ��ǰ��Ŀ
//  Input:			int  QuestionID
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::StopCurrentQuestion( CEntityPlayer *tpPlayer, int  QuestionID )
{
	LK_ASSERT( tpPlayer != NULL, return );
	CPropertyPlayer *pProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
		
	// ��ȡ״̬
	CAnswerStatus *tpAnswerStatus = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject( pProperty->GetAnswerStatusObjID() );
	if ( tpAnswerStatus == NULL )
	{	
		LOG_ERROR( "activity","[%s,%d][%s] Empty  CAnswerStatus of Player:%d",__LK_FILE__,__LINE__,__FUNCTION__, tpPlayer->GetCharID() );
		return;
	}	
	if ( tpAnswerStatus->GetAppType() == APPTYPE_NULL )
	{
		LOG_ERROR( "activity","[%s,%d][%s]Wrong Apptype of player:%d",__LK_FILE__,__LINE__,__FUNCTION__,tpPlayer->GetCharID() );		
		return;
	}
		
	// ��ȡ����ĿID	
	int NewQuestionID = tpAnswerStatus->GetNewQuestID();
		
	// ����ĿΪ��	
	if ( NewQuestionID == -1 )
	{
		EndAnswerQuestion( tpPlayer, tpAnswerStatus, 1 );
		//tpAnswerStatus->ClearStatus();
	}		
		
	// ����Ŀ����
	else
	{		
		SendMsgNewQuestion( tpPlayer, NewQuestionID, tpAnswerStatus->GetCurrentQuestIndex() );	
	}
}		

// **********************************************************
//  Function:		PlayerStopQuestionAnswer
//  Description:	���ֹͣ����
//  Input:			int EntType		ֹͣ�����жϻ��߷���
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::PlayerStopQuestionAnswer( CEntityPlayer *tpPlayer, int EntType )
{
	LK_ASSERT( tpPlayer != NULL, return );
	CPropertyPlayer *pProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	CAnswerStatus *tpAnswerStatus = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject( pProperty->GetAnswerStatusObjID() );	
	if ( tpAnswerStatus == NULL )
	{
		LOG_ERROR( "activity","[%s,%d][%s] Empty CAnswerStatus of Player:%d  ",__LK_FILE__,__LINE__,__FUNCTION__, tpPlayer->GetCharID() );
		return;
	}	
	EndAnswerQuestion( tpPlayer, tpAnswerStatus, EntType );
}

// ***********************************************************
//  Function:		EndAnswerQuestion
//  Description:	������Ҵ���
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::EndAnswerQuestion( CEntityPlayer *tpPlayer, CAnswerStatus *tpAnswer, int EndType )
{
	LK_ASSERT( tpPlayer != NULL && tpAnswer != NULL, return );
	
	// �ж�״̬
	if ( tpAnswer->GetAppType() == APPTYPE_NULL )
	{
		// TODO: ���Ǵ���
		return;
	}
	
	// ��ô�Ե���Ŀ����	
	int RightAnserNum = tpAnswer->GetRightAnswerNum();	
	
	// ���侭��	
	if ( RightAnserNum > 0 )
	{
		CTemplateQuestionExpTable *tpExpTable = ( CTemplateQuestionExpTable * )CDataStatic::spQuestionExpTable;
		if ( tpExpTable == NULL )
		{
			LOG_ERROR( "activity","[%s,%d][%s]CTemplateQuestionExpTable has not been loaded! ",__LK_FILE__,__LINE__,__FUNCTION__ );
			return;
		}
		int Exp = 0;
		int CharID = tpPlayer->GetCharID();		
		if ( tpAnswer->GetAppType() == APPTYPE_NPC )
		{ 	
			Exp = tpExpTable->mExp[tpPlayer->GetLevel()]*RightAnserNum*tpExpTable->mNpcExpAddRate;
			int nFinalExp = CPropertyModule::GetSingleton().PlayerObtainExp2( tpPlayer, Exp,0,EXPREASON_ACTIVITY,&CharID,1 );

			if ( nFinalExp > 0)
			{
				LogEventGetExpByQuestion(tpPlayer, Exp, nFinalExp, tpAnswer->GetAppType(), tpExpTable->mTempID);	
			}
			
			// npc����ȫ����ȷ֮���ȡ��Ʒ����
			if ( RightAnserNum == tpAnswer->GetQuestionNum() )
			{
				CItemPrize tItemPrize[MAX_NPCPRIZE_NUM];
				int tNum = MAX_NPCPRIZE_NUM;
				int tRet = mQuestionMng.GetNpcPrize( tItemPrize, tNum );
				if ( tRet == SUCCESS )
				{
					for ( int i = 0; i < tNum; ++i )
					{
						CPropertyModule::GetSingleton().PlayerInsertItem( tpPlayer, tItemPrize[i].ItemPrizeID, tItemPrize[i].ItemPrizeNum );
					}				
				}	
			}		

			// ֪ͨ���� ����ˢ��
			CTaskModule::GetSingleton().FireEvent( tpPlayer, EVENT_COMPLETE_QUESTION, SPECIALID_COMPLETEQUESTION );
		}		
		else if( tpAnswer->GetAppType() == APPTYPE_QUESTIONPAPER )
		{
			Exp = tpExpTable->mExp[tpPlayer->GetLevel()]*RightAnserNum*tpAnswer->GetExpRate();
			int nFinalExp = CPropertyModule::GetSingleton().PlayerObtainExp2( tpPlayer, Exp, 0, EXPREASON_ACTIVITY, &CharID, 1 );

			if ( nFinalExp > 0)
			{
				LogEventGetExpByQuestion(tpPlayer, Exp, nFinalExp, tpAnswer->GetAppType(), tpExpTable->mTempID);	
			}
		}			
						
		// TODO:�����ʱ��
		//CTimerMng::GetSingleton().ClearTimer( tpAnswer->GetTotalTimerID() ) ;
	}	
	
	SendMsgEndAnswerQuestion( tpPlayer, EndType  );		
	// ����״̬	
	tpAnswer->ClearStatus( );
}

// ***********************************************************
//  Function:		PlayerBeginQuestion
//  Description:	��ҿ�ʼ����
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::PlayerBeginQuestion( CEntityPlayer *tpPlayer, int Result )
{
	LK_ASSERT( tpPlayer != NULL, return );
	CPropertyPlayer *pProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	CAnswerStatus *tpAnswer = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject(
		pProperty->GetAnswerStatusObjID() );
	if ( tpAnswer ==  NULL )
	{
		LOG_ERROR( "activity","[%s,%d][%s]Empty CAnswerStatus of player:%d",__LK_FILE__,__LINE__,__FUNCTION__, tpPlayer->GetCharID() );
		return;
	}  
	if ( tpAnswer->GetAppType() == APPTYPE_QUESTIONPAPER )
	{
		// �����Ĵ���
		PlayerBeginPaperQuest( tpPlayer, Result );		
	}  	
	else if( tpAnswer->GetAppType() == APPTYPE_NPC )
	{
		// ��ʼÿ���ʴ����
		if ( Result == 1 )
		{
			if ( pProperty->GetBaggage()->Space( -1, 1 ) == false )
			{
				CPropertyModule::GetSingleton().SendProErrorNotice( tpPlayer, ERR_ACTIVITY_NOSPACE );				
				return;
			}
			PlayerBeginNpcQuest( tpPlayer );
			
		}
		else
		{
			tpAnswer->SetAppType( APPTYPE_NULL );
		} 		
	}
}

// ***********************************************************
//  Function:		PlayerUseQuestionPaper
//  Description:	���ʹ�ô����
//  Input:			int PaperIndex  ����ڰ������������
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::PlayerUseQuestionPaper( CEntityPlayer *tpPlayer, int PaperIndex ) 
{
	LK_ASSERT( tpPlayer != NULL, return );
	CPropertyPlayer *pProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	CItemObject *tpItemObj = ( CItemObject * )pProperty->GetBaggage(  )->GetItemObjPtr( PaperIndex );
	if ( tpItemObj == NULL )
	{	
		LOG_ERROR( "activity","[%s,%d][%s] Empty itemobject in index:%d of player:%d ",
			__LK_FILE__,__LINE__,__FUNCTION__, PaperIndex, tpPlayer->GetCharID() );	
		return;
	}
	CTplItem *tpItem =( CTplItem * )CDataStatic::SearchTpl( tpItemObj->GetItemID() );
	if ( tpItem == NULL )
	{
		LOG_ERROR( "activity","[%s,%d][%s] Item template:%d of player:%d  does not exist!",
			__LK_FILE__,__LINE__,__FUNCTION__, tpItemObj->GetItemID(), tpPlayer->GetCreatorID() );
		return;
	}
	if ( tpItem->mItemType != ITEM_QUESTIONPAPER )
	{
		LOG_ERROR( "activity","[%s,%d][%s] Item template:%d of player:%d is not questionpaper!",
			__LK_FILE__,__LINE__,__FUNCTION__, tpItemObj->GetItemID(), tpPlayer->GetCreatorID() );
		return;
	}
	CAnswerStatus *tpAnswer = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject( pProperty->GetAnswerStatusObjID() );
	if ( tpAnswer == NULL )
	{
		LOG_ERROR( "activity","[%s,%d][%s] Empty CAnswerStatus of Player:%d!",
			__LK_FILE__,__LINE__,__FUNCTION__,tpPlayer->GetCreatorID() );
		return;
	}
	
	// ����Ѿ����ڴ���״̬�����ٽ��д���
	if ( tpAnswer->GetAppType() != APPTYPE_NULL )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( tpPlayer, ERR_ACTIVITY_INANSWERSTATUS );
		return;
	} 
	
	// ����״̬
	tpAnswer->SetAppType( APPTYPE_QUESTIONPAPER );	
	
	// ��¼���λ��
	tpAnswer->SetPaperIndex( PaperIndex );
	
	// ��������
	pProperty->GetBaggage()->Lock( PaperIndex, LOCKTYPE_QUESIONPAPER );
	CPropertyModule::GetSingleton().SendLockItemNotice( tpPlayer, PaperIndex, LOCKTYPE_QUESIONPAPER );		
	
	// ���Ϳ��Դ������Ϣ
	SendMsgUseQuestionPaper( tpPlayer, 1 );
}

// ***********************************************************
//  Function:	SendMsgCheckAnswer	
//  Description: ������Ŀ�Ĵ𰸼����	
//  Input:		int Result
//  Input:		int QuestionID
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************

void CActivityModule::SendMsgCheckAnswer( CEntityPlayer *tpPlayer, int QuestionID, int Result, int QuestionIndex, int IfLastQuestion )
{
	LK_ASSERT( tpPlayer != NULL, return );
	CMessageCheckAnswerResponse MsgCheckAnswer;
	CMessage					MsgHead;
	MsgCheckAnswer.set_result( Result );
	MsgCheckAnswer.set_questionid( QuestionID );
	MsgCheckAnswer.set_iflastquestion( IfLastQuestion );
	MsgCheckAnswer.set_questionindex( QuestionIndex );
	MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_CHECKANSER );
	MsgHead.set_msgpara( (int)&MsgCheckAnswer );
	CSceneLogic::GetSingleton().Send2Player( tpPlayer, &MsgHead ) ;
}


// ***********************************************************
//  Function:	SendMsgNewQuestion	
//  Description: ��������Ŀ֪ͨ	
//	Input:		int QuestionID   ��ĿID 	
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::SendMsgNewQuestion( CEntityPlayer *tpPlayer, int QuestionID,  int QuestionIndex )
{
	LK_ASSERT( tpPlayer != NULL, return );
	CMessage MsgHead;
	CMessageQuestionNew	MsgQuestionNew;
	MsgQuestionNew.set_questionid( QuestionID );
	MsgQuestionNew.set_questionindex( QuestionIndex );
	MsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_QUESTIONNEW );
	MsgHead.set_msgpara( (int)&MsgQuestionNew );
	CSceneLogic::GetSingleton().Send2Player( tpPlayer, &MsgHead );
}

// ***********************************************************
//  Function:	 	SendMsgEndAnswerQuestion
//  Description:	���ͽ����������Ϣ
//  Input:			int Result		��������	
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::SendMsgEndAnswerQuestion( CEntityPlayer *tpPlayer, int Result )
{
	LK_ASSERT( tpPlayer != NULL, return );
	CMessage MsgHead;
	CMessageAnswerEnd MsgEndAnswerQuestion;
	MsgEndAnswerQuestion.set_endtype(  Result );
	MsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_ENDANSWER );
	MsgHead.set_msgpara( (int)&MsgEndAnswerQuestion );
	CSceneLogic::GetSingleton().Send2Player( tpPlayer, &MsgHead );	
}


// ***********************************************************
//  Function:	 SendMsgUseQuestionPaper	
//  Description: ����ʹ��	
//  Input:		 int Result			1��ʾ����ʹ�� 0��ʾ����ʹ��
//  OutPut:			
//  Return:			
//  Others:
//  Date:		
// *********************************************************
void CActivityModule::SendMsgUseQuestionPaper( CEntityPlayer *tpPlayer, int Result )
{
	LK_ASSERT( tpPlayer != NULL, return );
	CMessage				 MsgHead;
	CMessageUsePaperResponse MsgUsePaper;	
	MsgUsePaper.set_result( Result );
	MsgHead.mutable_msghead( )->set_messageid( ID_S2C_RESPONSE_USEQUESIONPAPER );
	MsgHead.set_msgpara( (int)&MsgHead );
	CSceneLogic::GetSingleton( ).Send2Player( tpPlayer, &MsgHead );	
}


// ***********************************************************
//  Function:		GetQuestNumOfPaper
//  Description:	��ô�������Ŀ����
//  Input:			int ItemID
//  OutPut:			
//  Return:			int    -1��ʾ��������ֵ��ʾ��Ŀ������
//  Others:
//  Date:	11/20/2008
// **********************************************************
int  CActivityModule::GetQuestNumOfPaper( int ItemID )
{	
	CTplItem *tpTplItem = ( CTplItem * )CDataStatic::SearchTpl( ItemID );
	if( tpTplItem == NULL )
	{	
		return -1;
	}
	
	if ( tpTplItem->mItemType != ITEM_QUESTIONPAPER )
	{
		return -1;
	}	
	CTplQuestionPaper *tpTplQuestionPaper = ( CTplQuestionPaper * )tpTplItem;
	int	QuestNumRate[MAX_QUESTION_NUM+1] = { 0 };	
	int TotalNum=0;	
	for ( int i = 1 ; i <= MAX_QUESTION_NUM; i ++ )	
	{
		QuestNumRate[i] = QuestNumRate[i-1] + tpTplQuestionPaper->mQuestionRate[i-1];
		TotalNum = TotalNum + tpTplQuestionPaper->mQuestionRate[i-1];
	}	
	if ( TotalNum <= 0 )	
	{
		return -1;
	}	
	int RandNum = rand()%(TotalNum+1);
	int QuestNum = 0;		
	for ( QuestNum = 1;  QuestNum <= MAX_QUESTION_NUM; ++QuestNum )	
	{		
		if( RandNum < QuestNumRate[QuestNum] && RandNum  >= QuestNumRate[QuestNum-1] )
		{
			break;	
		}	
	}	
	return QuestNum;
}

// ***********************************************************
//  Function:		InitailInvestQuestionFile
//  Description:	��ʼ���ʾ��������
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:	05/11/2009
// **********************************************************
int CActivityModule::InitailInvestQuestionFile( const char *pFileName )
{	
	LK_ASSERT( pFileName != NULL, return -1 ) 	
	TiXmlDocument tDoc;
	
	LK_ASSERT( tDoc.LoadFile( CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"/activity/InvestConf.xml" )) == true, return -1 );
	

	TiXmlElement *pRootElement = tDoc.RootElement();
	LK_ASSERT( pRootElement != NULL, return -1 )
	TiXmlElement *pLibElement = NULL; 
	TiXmlElement *pQuestionElement = NULL;	
	TiXmlElement *pPrizeElement = NULL;	
	CInvestQuestionLib tInvestLib;
	for ( pLibElement = pRootElement->FirstChildElement( ); pLibElement != NULL;
			pLibElement = pLibElement->NextSiblingElement( ) )
	{
		tInvestLib.Initialize();
		
		tInvestLib.SetLibID( atoi( pLibElement->Attribute("ID") ) );
		tInvestLib.SetMaxQuestionNum( atoi ( pLibElement->Attribute( "NUMLIMIT" ) ) );
		
		// ����Ŀ����
		 pQuestionElement = pLibElement->FirstChildElement( "InvestQuestion" );		 
		 for ( pQuestionElement = pQuestionElement->FirstChildElement() ;
				pQuestionElement != NULL;
				pQuestionElement =  pQuestionElement->NextSiblingElement( ) )
		 {
			tInvestLib.InsertQuestion( atoi( pQuestionElement->Attribute("ID") )
				, atoi( pQuestionElement->Attribute("SELECTED") ) );
		 }		 
	
		 // ����������		 		 		 
		 pPrizeElement = pLibElement->FirstChildElement( "PrizeList" );
		 tInvestLib.SetExpPrize( atoi(pPrizeElement->Attribute( "EXP" ) ) );
		 tInvestLib.SetMoney( atoi( pPrizeElement->Attribute( "MONEY" ) ) );
		 tInvestLib.SetBindMoney( atoi( pPrizeElement->Attribute("BINDMONEY") ) );
		 tInvestLib.SetCowry( atoi( pPrizeElement->Attribute("COWRY") ) );
		 for ( pPrizeElement = pPrizeElement->FirstChildElement();
				 pPrizeElement != NULL;
				 pPrizeElement = pPrizeElement->NextSiblingElement() )
		 {
			tInvestLib.InsertItemPrize( atoi( pPrizeElement->Attribute( "ID" ) ), 
				atoi( pPrizeElement->Attribute( "NUM" ) ) );			
		 }	
		 mInvestQuestionMng.InsertInvestQuestLib( &tInvestLib );
	}	
	return 0;	
}

// ***********************************************************
//  Function:		SendMsgInvestNotify
//  Description:	����ҷ��͵����ʾ��֪ͨ
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:	05/11/2009
// **********************************************************
void CActivityModule::SendMsgInvestNotify( CEntityPlayer *tpPlayer, CInvestQuestionLib *pQuestionLib )
{	 
	LK_ASSERT( tpPlayer != NULL && pQuestionLib != NULL, return )		
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	
	int QuestionNum = pQuestionLib->CreatInvestQuestionID();
	if ( QuestionNum <= 0 )
	{
		return;
	}
	CAnswerStatus *tpAnswerStatus = ( CAnswerStatus *)CSceneObjManager::GetSingleton().GetObject( 
		tpProperty->GetAnswerStatusObjID() );
	LK_ASSERT( tpAnswerStatus != NULL, return );
	tpAnswerStatus->SetInvestLibID( pQuestionLib->GetLibID() );
	
	CMessage MsgHead;
	CMessageInvestQuestionNotify MsgInvestQuestion;	
	MsgHead.mutable_msghead()->set_messageid( ID_S2C_NOIIFY_INVESTQUESTION );
	MsgHead.set_msgpara( (int)&MsgInvestQuestion );
	for ( int i = 0; i < QuestionNum; ++i )
	{
		MsgInvestQuestion.add_questionid( pQuestionLib->GetQuestion( i ) );
	}	
	CSceneLogic::GetSingleton().Send2Player( tpPlayer, &MsgHead );
}

// ***********************************************************
//  Function:		OnMessageInvestAnwerNotify
//  Description:	��ҵ����ʾ�Ļش�
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:	05/11/2009
// **********************************************************
void CActivityModule::OnMessageInvestAnwerNotify( CEntityPlayer *tpPlayer, CMessage * pMessage )
{
	LK_ASSERT( tpPlayer != NULL && pMessage != NULL, return )
	CMessageInvestAnswerNotify *tpMsg = ( CMessageInvestAnswerNotify * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	
	// TODO:��ʱ�����Ȳ�����
	if ( tpMsg->ifanswernow() != 1 )
	{
		return;
	} 		
	
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	CAnswerStatus *tpAnswerstatus = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject(
		 tpProperty->GetAnswerStatusObjID() );
	LK_ASSERT( tpAnswerstatus != NULL, return )
	LK_ASSERT( tpAnswerstatus->GetInvestLibID() != 0, return )
	CInvestQuestionLib *tpInvestLib = mInvestQuestionMng.GetInvestQuestLib( tpAnswerstatus->GetInvestLibID() );
	LK_ASSERT( tpInvestLib != NULL, return )
	
	// ���Ž���
	// ����
	int CharID = tpPlayer->GetCharID();
	int Exp	   = tpInvestLib->GetExpPrize();
	int nFinalExp = CPropertyModule::GetSingleton().PlayerObtainExp2( tpPlayer, Exp, 0, EXPREASON_ACTIVITY, &CharID, 1 );

	if ( nFinalExp > 0)
	{
		LogEventGetExpByInvestigation(tpPlayer, Exp, nFinalExp,  tpAnswerstatus->GetInvestLibID());	
	}

	CTemplateLevelMoneyLmt* tpMoneyTable = (CTemplateLevelMoneyLmt*)CDataStatic::GetTemp(TEMP_MONEYLMT_CFG);
	LK_ASSERT( tpMoneyTable!=NULL, return );
	LK_ASSERT( tpPlayer->GetLevel() >= 0 && tpPlayer->GetLevel() < TMP_MAX_GRADE, return );
	
	// ��Ǯ	
	if ( tpInvestLib->GetMoney() > 0 )
	{
		if ( (unsigned int)(tpPlayer->GetMoney()+tpInvestLib->GetMoney()) > tpMoneyTable->mLmtTable[tpPlayer->GetLevel()].mBagMoneyLmt)
		{
			// ��ϵͳ�ʼ�
			CPropertyModule::GetSingleton().SendProErrorNotice( tpPlayer, ERR_MONEYOVER_SYSMAIL );
			CMailModule::GetSingleton().SendSysMailBySysID( SYSMAIL_QUESTION_AWARD, tpPlayer->GetName(), tpPlayer->GetCharID(),
				NULL, NULL, 0, tpPlayer->GetNationality(), tpInvestLib->GetMoney() ); 
		}
		else
		{
			if (CPropertyModule::GetSingleton().PlayerChangeMoney( tpPlayer, tpInvestLib->GetMoney(), false, false ) == SUCCESS)
				LogEventGetMoneyByQuestLib(tpPlayer, CYuanBao::em_unbind_money, 
					tpInvestLib->GetMoney(), tpAnswerstatus->GetInvestLibID());
		}
	}

	if ( tpInvestLib->GetBindMoney() > 0 )
	{
		int tMoney = tpInvestLib->GetBindMoney();
		// �ж�Ǯ�Ƿ����
		if ( (unsigned int)(tpPlayer->GetBindMoney()+tpInvestLib->GetBindMoney()) > tpMoneyTable->mLmtTable[tpPlayer->GetLevel()].mBagBindMoneyLmt )
		{
			// ��Ǯ ������ӵ�
			CPropertyModule::GetSingleton().SendProErrorNotice(tpPlayer, ERR_BAG_BIND_MONEY_UPLMT);
			tMoney = std::min((int)(tpMoneyTable->mLmtTable[tpPlayer->GetLevel()].mBagBindMoneyLmt-tpPlayer->GetBindMoney()), tMoney);
		}
		if ( CPropertyModule::GetSingleton().PlayerChangeMoney( tpPlayer, tMoney, false, true ) == SUCCESS)
			LogEventGetMoneyByQuestLib(tpPlayer, CYuanBao::em_bind_money, 
				tpInvestLib->GetBindMoney(), tpAnswerstatus->GetInvestLibID());
	}

	
	// ��Ʒ����
	int tItemNum = tpInvestLib->GetItemPrizeNum();
	CItemPrize tItemPrize;
	for ( int i = 0; i < tItemNum; ++i )
	{	
		tpInvestLib->GetItemPrize( i, tItemPrize );

		CItemObject* pInsItemPile = 
			CPropertyModule::GetSingleton().PlayerInsertItem( tpPlayer, tItemPrize.ItemPrizeID, tItemPrize.ItemPrizeNum, false );

		if ( pInsItemPile )
		{
			LogEventGetItemByInvest(tpPlayer,  pInsItemPile->GetGUID(),
					tItemPrize.ItemPrizeID, tItemPrize.ItemPrizeNum, tpAnswerstatus->GetInvestLibID());
		}
	}
		
	// �Ѵ�����Ϣ�洢�����ݿ���	 		
	int tQuestionList[MAX_QUESTIONNUM_EACHLIB];
	int tAnswerList[MAX_QUESTIONNUM_EACHLIB];
	for ( int i = 0; i < tpMsg->questionid_size(); ++i )
	{  
		tQuestionList[i] = tpMsg->questionid( i );
		tAnswerList[i]	 = tpMsg->questionanswer( i );			
	}
	int InvestEdition = 1;
	SaveInvestAnswerToDB( tpPlayer, InvestEdition, tpAnswerstatus->GetInvestLibID(), tQuestionList, tAnswerList, tpMsg->questionid_size() );
	tpAnswerstatus->SetInvestLibID( 0 );
	
	tpProperty->SetInvestStatus( tpProperty->GetInvestStatus() | INVEST_STATUS_LEVELINVEST );
}

// ***********************************************************
//  Function:		OnEventInvestQuestion
//  Description:	�����ʾ���¼�������
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:	05/12/2009
// **********************************************************
void CActivityModule::OnEventInvestQuestion( int InvestType, int ID, CEntityPlayer *pPlayer /* = NULL */ )
{  
	int LibID = CREATELIBID( InvestType, ID );
	CInvestQuestionLib *pInvestLib = mInvestQuestionMng.GetInvestQuestLib( LibID );
	if ( pInvestLib == NULL )
	{
		return;
	}
	
	if ( InvestType == INVEST_TYPE_LEVEL || InvestType == INVEST_TYPE_MAP )
	{
		LK_ASSERT( pPlayer != NULL, return )
		CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
		if ( ( tpProperty->GetInvestStatus() & INVEST_STATUS_LEVELINVEST ) == false )
		{
			SendMsgInvestNotify( pPlayer, pInvestLib );
		}		
		return;
	}
	
	if ( InvestType == INVEST_TYPE_TIME )
	{ 
		CSceneObjManagerImp* pSceneneObjManagerImp = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp;
		for( CSceneObjManagerImp::ObjMng_EntityPlayer::iterator tPlayerIt = pSceneneObjManagerImp->mEntityPlayerPool.begin( ); 
				tPlayerIt != pSceneneObjManagerImp->mEntityPlayerPool.end( ); 
				tPlayerIt++ 
			)
		{
			CEntityPlayer* tpPlayer = &( *tPlayerIt );
			if ( tpPlayer == NULL )
			{
				continue;
			}
			SendMsgInvestNotify( pPlayer, pInvestLib );
		}
	}
}

// ***********************************************************
//  Function:		SaveInvestAnswerToDB
//  Description:	�ѵ����ʾ�Ĵ𰸴洢�����ݿ���
//  Input:			int vLibedition �汾
//  Input:			int *pQuestionList ��Ŀ�б�
//  Input: 			int *pQuestionList ���б�
//  Input:			int vQuestionNum   ��Ŀ����
//  OutPut:			
//  Return:			
//  Others:
//  Date:	05/11/2009
// **********************************************************
void CActivityModule::SaveInvestAnswerToDB( CEntityPlayer *tpPlayer, int vLibedition, int LibID, int *pQuestionList, int *pAnswerList, int vQuestionNum )
{	 
	LK_ASSERT( tpPlayer != NULL, return ) 			
	
	CInvestQuestionLib *tpQuestionLib = mInvestQuestionMng.GetInvestQuestLib( LibID );
	if ( tpQuestionLib == NULL )
	{
		return;
	}			  	
		
	char AnserBuff[MAX_INVESTANSER_DBBUFFERLENGTH] = { 0 };
	char *pPos = AnserBuff;
	for( int i = 0; i < vQuestionNum; ++i )
	{
		sprintf( pPos, "%d:\t",pQuestionList[i] );
		pPos = strchr( pPos, '\t' );
		if ( pAnswerList[i]&OPTION_A )
		{
			sprintf( pPos, "A-\t" );
			pPos = strchr( pPos, '\t' );
		}
		if ( pAnswerList[i]&OPTION_B )
		{
			sprintf( pPos, "B-\t" );
			pPos = strchr( pPos, '\t' );
		}
		if ( pAnswerList[i]&OPTION_C )
		{
			sprintf( pPos, "C-\t" );
			pPos = strchr( pPos, '\t' );
		}	
		if ( pAnswerList[i]&OPTION_D )
		{
			sprintf( pPos, "D-\t" );
			pPos = strchr( pPos, '\t' );
		}	
		if ( pAnswerList[i]&OPTION_E )
		{
			sprintf( pPos, "E-\t" );
			pPos = strchr( pPos, '\t' );
		}
		if ( pAnswerList[i]&OPTION_F )
		{
			sprintf( pPos, "F-\t" );
			pPos = strchr( pPos, '\t' );
		}	
		if ( pAnswerList[i]&OPTION_G )
		{
			sprintf( pPos, "G-\t" );
			pPos = strchr( pPos, '\t' );
		}	
		if ( pAnswerList[i]&OPTION_H )
		{
			sprintf( pPos, "H-\t" );
			pPos = strchr( pPos, '\t' );
		}
		if ( pAnswerList[i]&OPTION_I )
		{
			sprintf( pPos, "I-\t" );
			pPos = strchr( pPos, '\t' );
		}
		if ( pAnswerList[i]&OPTION_J )
		{
			sprintf( pPos, "J-\t" );
			pPos = strchr( pPos, '\t' );
		}
		if ( pAnswerList[i]&OPTION_K )
		{
			sprintf( pPos, "K-\t" );
			pPos = strchr( pPos, '\t' );
		}
		if ( pAnswerList[i]&OPTION_L )
		{
			sprintf( pPos, "L-\t" );
			pPos = strchr( pPos, '\t' );
		}
		if ( pAnswerList[i]&OPTION_M )
		{
			sprintf( pPos, "M-\t" );
			pPos = strchr( pPos, '\t' );
		}		
		sprintf( pPos, "&&&&\t" );
		pPos = strchr( pPos, '\t' );
		
		tpQuestionLib->RecordAnswer( pQuestionList[i], pAnswerList[i] );
	}
	const char *stmfmt = "insert into UMS_INVEST_ANSWER( invest_answer, role_id, role_name, role_level, edition, library_id ) \
		 values( '%s', %d, '%s', %d, %d, %d ) ";               \
	CSceneLogic::GetSingletonPtr()->ExecuteSql( saveinvestanswer, 0, 0, tpPlayer->GetCharID(), SQL_NONE,INSERT, stmfmt,
	AnserBuff, tpPlayer->GetCharID(), tpPlayer->GetCharName(), tpPlayer->GetLevel(), vLibedition, LibID );			
}

// ***********************************************************
//  Function:		CheckInvestTime
//  Description:	ÿ�����㶼���һ����û����Ӧ�ĵ�������
//  Input:		
//  Input:			
//  Input: 		
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:	05/11/2009
// **********************************************************
void CActivityModule::CheckInvestTime( )
{ 
	static int LastTime = 0;
	
	// һСʱ�Ƚ�һ��
	time_t TimeNow = time( 0 );
	if ( TimeNow - LastTime > 3600 )
	{  
		LastTime = TimeNow;		
		tm *vLocaltm = localtime( &TimeNow );
		int Month = vLocaltm->tm_mon + 1; 	
		int ID = MAKETIMEID( Month, vLocaltm->tm_mday, vLocaltm->tm_hour );	
		OnEventInvestQuestion( INVEST_TYPE_TIME, ID );	
	} 						   
}

int CActivityModule::InitialDoubleExpFile( const char *pDir )
{
	LK_ASSERT( pDir!=NULL, return -1);
	TiXmlDocument tDoc;
	TiXmlElement  *pRootElement		= NULL;
	LK_ASSERT( tDoc.LoadFile( pDir ), return -1 );		
	pRootElement = tDoc.FirstChildElement();
	if ( pRootElement == NULL )
	{
		return -1;
	}

	// ���ʱ��
	mDoubleTime.clear();
	mEndTime = 0;

	/*
	memset( mDoubleTime, 0, sizeof(mDoubleTime) );
	memset( mExistTime, 0, sizeof(mExistTime) );
	mCount = 0;
	*/


	// �Ƚϸ��ڵ�
	TiXmlElement* tpSubEle = pRootElement->FirstChildElement( "DoubleDate" );
	LK_ASSERT ( tpSubEle != NULL, return false );
	for( TiXmlElement* tpDoubleDate = tpSubEle->FirstChildElement() ; tpDoubleDate != NULL; tpDoubleDate = tpDoubleDate->NextSiblingElement( ) )
	{
		std::string tEleName1 = tpDoubleDate->Value( );
		if ( tEleName1 == "Double" )
		{
			const char* tpDate	= tpDoubleDate->Attribute( "DoubleDate" );
			LK_ASSERT( tpDate != NULL && strlen(tpDate) >= 12, return -1 );

			const char* tpTime	= tpDoubleDate->Attribute( "Time" );
			LK_ASSERT( tpTime != NULL && atoi(tpTime) > 0, return -1);

			if ( AppendDoubleTime(tpDate, atoi(tpTime)) == false)
			{
				LOG_ERROR("activity", "load double time from(%s, %s) error", tpDate, tpTime);
				continue;
			}

			/*
			char tYear[5] = {0}, tMonth[3] = {0}, tDate[3] = {0};
			char tHour[3] = {0}, tMinute[3] = {0}, tDay[2] = {0};
			memcpy( tYear,	 tpDate,	  4 );
			memcpy( tMonth,	 tpDate + 4,  2 );
			memcpy( tDate,	 tpDate + 6,  2 );
			memcpy( tHour,	 tpDate + 8,  2 );
			memcpy( tMinute, tpDate + 10, 2 );
			memcpy( tDay,	 tpDate + 12, 1 );
			mDoubleTime[ mCount ].mYear		= atoi( tYear );
			mDoubleTime[ mCount ].mMonth		= atoi( tMonth );
			mDoubleTime[ mCount ].mDate		= atoi( tDate );
			mDoubleTime[ mCount ].mHour		= atoi( tHour );
			mDoubleTime[ mCount ].mMinute	= atoi( tMinute );
			mDoubleTime[ mCount ].mDay		= atoi( tDay );
			const char* tpTime	= tpDoubleDate->Attribute( "Time" );
			LK_ASSERT( tpTime != NULL, return -1 );
			mExistTime[ mCount ] = atoi( tpTime );
			mCount++;	
			if ( (unsigned int)mCount >= ARRAY_CNT( mDoubleTime ) )
				break;
			*/
		}
	}	
	return 1;	
}  


void CActivityModule::CheckDoubleTime( )
{
	if ( mDoubleTime.size() == 0 || mDoubleActive == true )
	{
		return;
	}

	time_t tval;
	struct tm *now;        
	time(&tval);
	now = localtime(&tval);

	for ( size_t j = 0; j < mDoubleTime.size(); j++ )
	{
		/*
		RefreshDate tTime = mDoubleTime[ j ].first;
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
			//if ( tTime.mHour != now->tm_hour )
			//	continue;

			//else if ( tTime.mMinute != now->tm_min )
			//	continue;

			//TODO: ������©�������ܵ���1�����ڹر�˫���������ִ���һ�Σ�Ȼ����1�������ֱ��ر�
			int tConfigMin = tTime.mHour * 60 + tTime.mMinute;
			int tNowMin = now->tm_hour * 60 + now->tm_min;
			if ( tNowMin - tConfigMin < 0 || tNowMin - tConfigMin > mDoubleTime[ j ].second / 60 )
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
		mDoubleActive = true;
	
		//TODO: ��Ϊǰ���ǲ��ܸ���ˢ��ֻ�ܵ���ˢ����ô�����ǰ����ʱ��
		now->tm_hour = tTime.mHour;
		now->tm_min = tTime.mMinute;

		unsigned int tTimeBegin = mktime(now);
		unsigned int tTimeEnd = tTimeBegin + mDoubleTime[ j ].second ;
		
		mEndTime = tTimeEnd;
		
		// ����ʱ��(��)˫���жϣ�ȷ��������������1���Ӵ���2�ε�����
		if( mEndTime < (unsigned int) time(NULL) )
		{
			return ;
		}

		//mDoubleTimer = time(NULL)- CWTimer( mExistTime[ j ] * 1000 );
		*/

		RefreshDate tTime = mDoubleTime[ j ].first;
		if ( tval >= mDoubleTime[j].first.timet() && tval < mDoubleTime[j].first.timet() + mDoubleTime[j].second )
		{
			mDoubleActive = true;
			mEndTime = tval + mDoubleTime[j].second;

			mDoubleIndex = j;
				CPropertyModule::GetSingletonPtr()->FireActivityDiploid( NULL, mDoubleTime[ mDoubleIndex ].rate, true, 
						mDoubleTime[ mDoubleIndex ].first.mHour * 60 + mDoubleTime[ mDoubleIndex ].first.mMinute, 
						mDoubleTime[ mDoubleIndex ].second);
			//mExistTime[ j ] );

			return;
		}
	}

	//// ����Ѿ��ǿ���״̬, û�з�����������Ҫ�ر�һ��˫��
	//if( mDoubleActive == true )
	//{
	//	mDoubleActive = false;
	//	mDoubleIndex = -1;
	//	CPropertyModule::GetSingletonPtr()->FireActivityDiploid( NULL, false, true );	
	//}
}

int CActivityModule::GetDoubleState( int &vBeginTime, int &vEndTime )
{
	if ( mDoubleActive == true )
	{
		vBeginTime = mDoubleTime[ mDoubleIndex ].first.mHour * 60 + mDoubleTime[ mDoubleIndex ].first.mMinute;
		//vEndTime = mExistTime[ mDoubleIndex ];
		vEndTime = mDoubleTime[ mDoubleIndex ].second;

		
		return mDoubleTime[mDoubleIndex].rate;
	}

	return 0;
}

void CActivityModule::AddNpcInfo( int vNpcID, int vEntityID )
{
	if ( (unsigned int)mNpcNum >= ARRAY_CNT( mNpcInfo ) - 1 )
	{
		return;
	}
	mNpcInfo[ mNpcNum ].mNpcID = vNpcID;
	mNpcInfo[ mNpcNum ].mEntityID = vEntityID;
	mNpcNum ++;
}

bool CActivityModule::CanBidNpc( int vNpcID )
{
	for ( int i = 0; i < mNpcNum; i++ )
	{
		if ( mNpcInfo[ i ].mNpcID == vNpcID )
		{
			if ( mNpcInfo[ i ].mState == STATE_BIDDING )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

void CActivityModule::CheckNpcTime( )
{
	time_t tval;
	struct tm *now;        
	time(&tval);
	now = localtime(&tval);

	for ( int i = 0; i < mNpcNum; i++ )
	{
		CTemplateNpc *tplNpc = (CTemplateNpc*)CDataStatic::SearchTpl( mNpcInfo[ i ].mNpcID );
		if ( tplNpc == NULL )
		{
			continue;
		}
		if ( tplNpc->mBidDay == 0 )
		{
			continue;
		}
		if ( ( ( ( tplNpc->mBidDay & CTemplateNpc::WDAY_MONDAY ) != CTemplateNpc::WDAY_MONDAY ) && now->tm_wday == 1 )	     || 
			 ( ( ( tplNpc->mBidDay & CTemplateNpc::WDAY_TUESDAY ) != CTemplateNpc::WDAY_TUESDAY ) && now->tm_wday == 2 )     ||
			 ( ( ( tplNpc->mBidDay & CTemplateNpc::WDAY_WEDENSDAY ) != CTemplateNpc::WDAY_WEDENSDAY ) && now->tm_wday == 3 ) ||
			 ( ( ( tplNpc->mBidDay & CTemplateNpc::WDAY_THURSDAY ) != CTemplateNpc::WDAY_THURSDAY ) && now->tm_wday == 4 )   ||
			 ( ( ( tplNpc->mBidDay & CTemplateNpc::WDAY_FRIDAY ) != CTemplateNpc::WDAY_FRIDAY ) && now->tm_wday == 5 )		 ||
			 ( ( ( tplNpc->mBidDay & CTemplateNpc::WDAY_SATURDAY ) != CTemplateNpc::WDAY_SATURDAY ) && now->tm_wday == 6 )	 ||
			 ( ( ( tplNpc->mBidDay & CTemplateNpc::WDAY_SUNDAY ) != CTemplateNpc::WDAY_SUNDAY ) && now->tm_wday == 0 ) )
		{
			continue;
		}
		if ( tplNpc->mBidHour >= 0 && tplNpc->mBidMinute >= 0 )
		{
			int tConfigMin = tplNpc->mBidHour * 60 + tplNpc->mBidMinute;
			int tNowMin = now->tm_hour * 60 + now->tm_min;
			// ���˽�ֹʱ��,���뱨��״̬
			if ( tNowMin - tConfigMin >= 0 && tNowMin - tConfigMin <= SUBMITTIME && mNpcInfo[ i ].mState == STATE_BIDDING )
			{
				mNpcInfo[ i ].mState = STATE_SUBMITTING;
				mNpcInfo[ i ].mSubmitTimer = CWTimer( SUBMITTIME * 60 * 1000 );
				mNpcInfo[ i ].mNotifyTimer = CWTimer( NOTIFYTIME * 60 * 1000 );
				// ֪ͨ��Ӧ������峤ȥ����
				SendMsgBidTimeOut( mNpcInfo[ i ].mNpcID, 1 );
				LOG_INFO("activity", "NPC %d submit", mNpcInfo[ i ].mNpcID);
			}
		}
	}
}

void CActivityModule::SendMsgBidTimeOut( int vNpcID, int vFirst )
{
	CMessage tTotalMessage;
	CMessageHead* tpHead = NULL;
	tpHead = tTotalMessage.mutable_msghead();
	if ( tpHead == NULL )
	{
		LOG_DEBUG( "default", "[ %s : %d ] [ %s ]", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}

	tpHead->set_messageid( ID_S2G_NOTIFY_BIDTIMEOUT );

	CMessageBidTimeOutNotify tMessage;
	tMessage.set_npcid( vNpcID );
	tMessage.set_first( vFirst );

	tTotalMessage.set_msgpara( (long)&tMessage );
	CSceneLogic::GetSingletonPtr()->Send2Gate( &tTotalMessage );
}

void CActivityModule::SendMsgBattleStart( int vNpcID )
{
	CMessage tTotalMessage;
	CMessageHead* tpHead = NULL;
	tpHead = tTotalMessage.mutable_msghead();
	if ( tpHead == NULL )
	{
		LOG_DEBUG( "default", "[ %s : %d ] [ %s ]", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}

	tpHead->set_messageid( ID_S2G_REQUEST_BATTLESTART );

	CMessageBattleStartRequest tMessage;
	tMessage.set_npcid( vNpcID );

	tTotalMessage.set_msgpara( (long)&tMessage );
	CSceneLogic::GetSingletonPtr()->Send2Gate( &tTotalMessage );
}

void CActivityModule::DebugTimeOut( int vNpcID )
{
	for ( int i = 0; i < mNpcNum; i++ )
	{
		CTemplateNpc *tplNpc = (CTemplateNpc*)CDataStatic::SearchTpl( mNpcInfo[ i ].mNpcID );
		if ( tplNpc == NULL )
		{
			continue;
		}
		if ( mNpcInfo[ i ].mNpcID == vNpcID )
		{
			mNpcInfo[ i ].mState = STATE_SUBMITTING;
			mNpcInfo[ i ].mSubmitTimer = CWTimer( SUBMITTIME * 60 * 1000 );
			mNpcInfo[ i ].mNotifyTimer = CWTimer( NOTIFYTIME * 60 * 1000 );
			SendMsgBidTimeOut( mNpcInfo[ i ].mNpcID, 1 );
		}
	}
}

void CActivityModule::DebugBattleStart( int vNpcID )
{
	for ( int i = 0; i < mNpcNum; i++ )
	{
		CTemplateNpc *tplNpc = (CTemplateNpc*)CDataStatic::SearchTpl( mNpcInfo[ i ].mNpcID );
		if ( tplNpc == NULL )
		{
			continue;
		}
		if ( mNpcInfo[ i ].mNpcID == vNpcID )
		{
			if ( mNpcInfo[ i ].mState == STATE_SUBMITTING )
			{
				mNpcInfo[ i ].mState = STATE_FIGHTING;
				SendMsgBattleStart( mNpcInfo[ i ].mNpcID );
			}
		}
	}
}

void CActivityModule::DebugBattleEnd( int vNpcID )
{
	for ( int i = 0; i < mNpcNum; i++ )
	{
		CTemplateNpc *tplNpc = (CTemplateNpc*)CDataStatic::SearchTpl( mNpcInfo[ i ].mNpcID );
		if ( tplNpc == NULL )
		{
			continue;
		}
		if ( mNpcInfo[ i ].mNpcID == vNpcID )
		{
			if ( mNpcInfo[ i ].mState == STATE_FIGHTING )
			{
				mNpcInfo[ i ].mState = STATE_BIDDING;
			}
		}
	}
}

bool CActivityModule::AppendDoubleTime(time_t nStartTime, time_t nEndTime, int nRate)
{
	CDoubleTime::iterator iter = mDoubleTime.begin();
	for (; iter != mDoubleTime.end(); ++iter)
	{
		int nThisTime = iter->first.timet();
		int nExistTime = iter->second;

		if(( nThisTime  >= nStartTime && nThisTime < nEndTime)
		|| ( nStartTime >= nThisTime && nStartTime < nThisTime + nExistTime))
		{
			return false;
		}
	}

	if ( nEndTime <= nStartTime ) return false;

	time_t seconds = nStartTime;
	struct tm* pnow = localtime(&seconds);

	char tpDate[32] = {0}; 
	strftime(tpDate,  sizeof(tpDate) - 1, "%Y%m%d%H%M00", pnow); 

	return AppendDoubleTime(tpDate, nEndTime - nStartTime, nRate);
}

bool CActivityModule::AppendDoubleTime(const char* tpDate, int nExistTime, int nRate)
{
	if ( mDoubleTime.max_size() ==  mDoubleTime.size() ) return false;

	char tYear[5] = {0}, tMonth[3] = {0}, tDate[3] = {0};
	char tHour[3] = {0}, tMinute[3] = {0}, tDay[2] = {0};
	memcpy( tYear,	 tpDate,	  4 );
	memcpy( tMonth,	 tpDate + 4,  2 );
	memcpy( tDate,	 tpDate + 6,  2 );
	memcpy( tHour,	 tpDate + 8,  2 );
	memcpy( tMinute, tpDate + 10, 2 );
	memcpy( tDay,	 tpDate + 12, 1 );

	RefreshDate nDoubleTime;	

	nDoubleTime.mYear	= atoi( tYear );
	nDoubleTime.mMonth	= atoi( tMonth );
	nDoubleTime.mWeek	= 0; // Ĭ�ϳ�ʼ����0
	nDoubleTime.mDate	= atoi( tDate );
	nDoubleTime.mHour	= atoi( tHour );
	nDoubleTime.mMinute	= atoi( tMinute );
	nDoubleTime.mDay	= atoi( tDay );

	mDoubleTime.push_back(CDoubleTime::value_type(nDoubleTime, nExistTime, nRate));

	return true;
}

bool CActivityModule::RemoveDoubleTime(time_t pnStartTime, time_t nEndTime )
{
	time_t nStartTime = pnStartTime - (pnStartTime % 60);
	time_t pnExistTime = nEndTime - pnStartTime;

	CDoubleTime::iterator iter = mDoubleTime.begin();
	for (int index = 0; iter != mDoubleTime.end(); ++iter, ++index)
	{
		int nThisTime = iter->first.timet();
		int nExistTime = iter->second;

		if(nStartTime == nThisTime && nExistTime == pnExistTime)
		{
			if ( index == mDoubleIndex )
			{
				mDoubleActive = false;
				mDoubleIndex = -1;
				CPropertyModule::GetSingletonPtr()->FireActivityDiploid( NULL, 0, true );

			}

			mDoubleTime.erase(iter);
			return true;
		}

		if (nStartTime == 0 && nEndTime == 0 && index == mDoubleIndex )
		{
			mDoubleActive = false;
			mDoubleIndex = -1;
			CPropertyModule::GetSingletonPtr()->FireActivityDiploid( NULL, 0, true );

			mDoubleTime.erase(iter);
			return true;
		}
	}

	return false;
}

void CActivityModule::OnGateMessage( CMessage* pMessage )
{
	LK_ASSERT(pMessage != NULL && pMessage->msgpara() != 0, return);
	const CMessageHead& tHead = pMessage->msghead();

	switch( tHead.messageid( ) )
	{
	case ID_G2S_TODAYACTIVITYS_LIST_NOTIFY:
		{
			OnGateMessageTodayActivityList(pMessage);
			break;
		}
	case ID_G2S_ACTIVITY_CHANGE_NOTIFY:
		{
			OnGateMessageActivityChgNotice(pMessage);
			break;
		}
    case ID_G2S_GETCAMPRANKFORYQS_RESPONSE:
        {
            CActivityYqs::GetSingleton().OnMesageGetCampRankInfoForGate( pMessage );
            break;
        }
    case ID_G2S_UPDATEYQSGROWING_RESPONSE:
        {
            CActivityYqs::GetSingleton().OnMessageUpdateYQSGrowingResponse( pMessage );
            break;
        }
    case ID_G2S_SETTLE_NOTICE:
        {
            CActivityYqs::GetSingleton().OnMessageSettleNotice( pMessage );
            break;
        }
    case ID_G2S_YAOQIANSHUSTART_NOTICE:
        {
            CActivityYqs::GetSingleton().OnMessageActivityStartNotice( pMessage );
            break;
        }
	case ID_G2S_ACTIVITY_EVENT_NOTIFY:
		{
			OnGateMessageActivityEventNotice(pMessage);
			break;
		}
	default:
		{
			LOG_ERROR("activity", "There is no action for msg id(%d)", tHead.messageid());
			break;
		}
	}
}

// �ɵ�Ŀǰ���л ����
void CActivityModule::ClearActivitys()
{
	for ( ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.begin(); it != mSceneActivityMgr.end(); ++it )
	{
		for ( int i = 0; i < it->second.m_OgreIndexNum; ++i )
		{
			COgreCreator* pCreator = ( COgreCreator*)CCreatorManager::GetSingletonPtr()->GetCreator( it->second.m_OgreIndex[i] );
			if ( pCreator != NULL )
			{
				if( pCreator->mHasOgre != 0 )
				{
					CEntity* pOldEntity = CSceneLogic::GetSingletonPtr()->GetEntity( pCreator->mHasOgre );
					if (pOldEntity != NULL)
						CSceneLogic::GetSingletonPtr()->DestroyEntity( pOldEntity, 0 ); // ���ٵ�
					pCreator->mHasOgre = 0;
				}
			}
		}
	}
	mSceneActivityMgr.clear();
	mAvtivityOgreMgr.clear();
	for (int i = 0 ; i < MAX_MAP_ID; ++i )
	{
		mMapAddDropTable[i].clear();
	}	
	memset(mMapRepDropTable, 0, sizeof(mMapRepDropTable));
}

// �������ؽ����б�
void CActivityModule::OnGateMessageTodayActivityList( CMessage* pMessage )
{
	CMessageTodayActivitysNotify* tpMsg = (CMessageTodayActivitysNotify*) pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	//mSceneActivityMgr.clear();
	ClearActivitys();
	for ( int i = 0; i < tpMsg->activitylist_size(); ++i )
	{
		SingleActivityObj singleObj = tpMsg->activitylist(i);
		ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.find(singleObj.activityid( ));
		if ( it != mSceneActivityMgr.end() ) // �Ѵ�����
		{
			it->second.PushTime( singleObj.timetype( ), singleObj.timeinfo( ) );
		}
		else // �¼�
		{
			CActivityInfo obj;
			obj.m_nLmtLevel = singleObj.lmtlevel( );
			obj.m_nMaxTimes = singleObj.maxtimes( );
			obj.m_nCurState = singleObj.state();
			obj.PushTime( singleObj.timetype( ), singleObj.timeinfo( ) );
			mSceneActivityMgr.insert( std::make_pair( singleObj.activityid( ), obj ) );
		}
		LOG_NOTICE("Activity", "Gate Tell Me Activity %d CurState %d", 
			singleObj.activityid( ),  singleObj.state() );
	}

	// ���ص�����Ϣ
	for ( int i = 0; i < tpMsg->activityinfo_size(); ++i )
	{
		SingleActivityInfo singleObj = tpMsg->activityinfo(i);

		// ������ڵĵ�����Ϣ
		for ( int j = 0; j < singleObj.dropinfo_size(); ++j )
		{
			DropInfo tDrop = singleObj.dropinfo(j);
			ACTIVITY_OGRE_TYPE::iterator itFind = mAvtivityOgreMgr.find(tDrop.ogreid());
			if ( itFind == mAvtivityOgreMgr.end() ) // ���
			{
				CActivityOgreData data;
				data.m_nActivityID = singleObj.activityid();
				data.m_nDropID = tDrop.dropid();
				mAvtivityOgreMgr.insert(std::pair<int,CActivityOgreData>(tDrop.ogreid(), data));
				LOG_NOTICE("Activity", "act %d reg DROP %d-%d", singleObj.activityid(), tDrop.ogreid(), tDrop.dropid() );
			}
			else
			{
				LOG_ERROR("Activity", "Ogre %d's Drop Info in act%d!", tDrop.ogreid(), itFind->second.m_nActivityID );
			}
		}

		// ���ع���������Ϣ
		for ( int j = 0; j < singleObj.ogreindex_size(); ++j )
		{
			ACTIVITY_MGR_TYPE::iterator itFind = mSceneActivityMgr.find(singleObj.activityid());
			if ( itFind == mSceneActivityMgr.end() ) // û�ҵ���
			{
				LOG_ERROR("Activity", "can't find act %d? from ogreidx %d", singleObj.activityid(), singleObj.ogreindex(j));
				continue;
			}
			if (! itFind->second.PushOgreIndex(singleObj.ogreindex(j)))
			{
				LOG_ERROR("Activity", "OgreIndexTooMany! Actid=%d", singleObj.activityid() );
				continue;
			}
			// �������ڽ��У�ˢ����
			if ( itFind->second.m_nCurState == ACTIVITYSTATE_STARTED )
			{
				// ˢ��
				COgreCreator* pCreator = ( COgreCreator*)CCreatorManager::GetSingletonPtr()->GetCreator( singleObj.ogreindex(j) );
				if ( pCreator != NULL && pCreator->mHasOgre == 0 )
				{
					pCreator->mActivity = singleObj.activityid();
					unsigned int tEntityID = 0;
					CMapModule::GetSingleton().CreateNpc( CSceneLogic::GetSingleton().GetLineID(), pCreator->mMapIndex, 0, (CCreator*)pCreator, tEntityID );
					LOG_DEBUG("Activity", "Refresh OGRE1 Idx%d Entity%d", singleObj.ogreindex(j), tEntityID );
				}
			}
		}
	}

#ifdef _DEBUG_
	for ( ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.begin(); it != mSceneActivityMgr.end(); ++it )
	{
		LOG_DEBUG("Activity", "----------- Activity id:%d -----------", it->first );
		for (TIMELIST_TYPE::iterator it2 = it->second.mTimeList.begin(); it2 != it->second.mTimeList.end(); ++it2 )
		{
			LOG_DEBUG("Activity", "time: %d - %d", it2->m_nStartTime, it2->m_nEndTime );
		}
	}
#endif
}

// �������ط����Ļ���֪ͨ
void CActivityModule::OnGateMessageActivityChgNotice( CMessage* pMessage )
{
	CMessageActivityChangeNotify* tpMsg = (CMessageActivityChangeNotify*) pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );

	CMessageActivityChange2CliNotify msg;

    LOG_DEBUG( "YaoQianShu", "[ %s:%d ][%s] OnGateMessageActivityChgNotice", __LK_FILE__, __LINE__, __FUNCTION__ );
    // ���ҡǮ������֪ͨ
   for ( int i = 0; i < tpMsg->activitylist_size(); ++i )
    {
        SingleActivity singleObj = tpMsg->activitylist(i);
        LOG_DEBUG( "YaoQianShu", "[ %s:%d ][%s] OnGateMessageActivityChgNotice activity(%d) change state(%d)", 
            __LK_FILE__, __LINE__, __FUNCTION__, singleObj.activityid(), singleObj.activitystate() );
        CActivityYqs::GetSingleton().CheckActivity( singleObj.activityid(), singleObj.activitystate() );
    }


	CMessage tMessage;
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTIFY_ACTIVITYCHANGED);
	tMessage.set_msgpara( (long) &msg );

	std::vector<CEntityPlayer*> tPlayers;
	CSceneLogic::GetSingleton().GetPlayersInScene(tPlayers);

	// ֪ͨ���
	for ( std::vector<CEntityPlayer*>::iterator itPlayer = tPlayers.begin(); itPlayer != tPlayers.end(); ++itPlayer )
	{
		msg.clear_activitylist();
		for ( int i = 0; i < tpMsg->activitylist_size(); ++i )
		{
			SingleActivity singleObj = tpMsg->activitylist(i);
			ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.find( singleObj.activityid() );
			if ( it != mSceneActivityMgr.end() )
			{
				if ( (*itPlayer)->GetLevel() < it->second.m_nLmtLevel )
					continue;
			}
			//LOG_NOTICE("Activity", "Gate Tell Me Activity%d new State %d", singleObj.activityid(), singleObj.activitystate() );
			SingleActivityNewState* tpSend2Cli = msg.add_activitylist();
			LK_ASSERT( tpSend2Cli != NULL, continue );
			tpSend2Cli->set_activityid( singleObj.activityid() );
			tpSend2Cli->set_activitystate( singleObj.activitystate());
			tpSend2Cli->set_completetimes( GetTodayCompleteTimes(*itPlayer, singleObj.activityid()) );
		}

		CSceneLogic::GetSingleton().Send2Player( *itPlayer, &tMessage );
	}	

	// �޸�״̬ ��֪ͨLUA���д���
	for ( int i = 0; i < tpMsg->activitylist_size(); ++i )
	{
		SingleActivity singleObj = tpMsg->activitylist(i);
		ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.find( singleObj.activityid() );
		if ( it == mSceneActivityMgr.end() )
		{
			LOG_ERROR("Activity", "can't find activity-x %d ??", singleObj.activityid() );
			continue;
		}
		else
		{
			it->second.m_nCurState = singleObj.activitystate();

			std::vector<int> tIntParams;
			std::vector<std::string> tStrParams;
			if ( it->second.m_nCurState == ACTIVITYSTATE_NOT_START ) // ������
			{
				FireActivityEvent( singleObj.activityid(), ACTIVITY_END, tIntParams, tStrParams );
			}
			else if ( it->second.m_nCurState == ACTIVITYSTATE_STARTED ) // ��ʼ��
			{
				FireActivityEvent( singleObj.activityid(), ACTIVITY_START, tIntParams, tStrParams );
			}
		}
	}	

	// ��� ɾ����ͼˢ��
	for ( int i = 0; i < tpMsg->activitylist_size(); ++i )
	{
		SingleActivity singleObj = tpMsg->activitylist(i);
		ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.find( singleObj.activityid() );
		if ( it == mSceneActivityMgr.end() )
		{
			LOG_ERROR("Activity", "can't find activity %d -x3 ??", singleObj.activityid() );
			continue;
		}
		else
		{
			it->second.m_nCurState = singleObj.activitystate();

			if ( it->second.m_nCurState == ACTIVITYSTATE_NOT_START ) // ������
			{
				// ��ͼ��ӵ����
				for ( int j=0; j< singleObj.mapdrops_size(); ++j )
				{
					MapDrop tMap = singleObj.mapdrops(j);
					for ( int k = 0; k < tMap.mapids_size(); ++k )
					{
						if ( tMap.mapids(k) <=0 || tMap.mapids(k) >= MAX_MAP_ID )
						{
							LOG_ERROR("Activity", "Error mapid x %d in ACT %d", tMap.mapids(k), singleObj.activityid() );
							continue;
						}
						if (tMap.droptype() == DROPTYPE_ADD)
						{
							// ���� ɾ�� ֻɾ1�� ɾ����OK
							for ( ACTIVITY_MAP_DROP_TYPE::iterator itd = mMapAddDropTable[tMap.mapids(k)].begin(); 
								itd != mMapAddDropTable[tMap.mapids(k)].end(); ++itd )
							{
								if ( (unsigned int)(*itd) == tMap.dropid())
								{
									mMapAddDropTable[tMap.mapids(k)].erase(itd);
									LOG_NOTICE("Activity", "ACT %d erased %d from map %d", singleObj.activityid(),
										*itd, tMap.mapids(k) );
									break;
								}
							}
						}
						else if (tMap.droptype() == DROPTYPE_REPLACE)
						{
							mMapRepDropTable[tMap.mapids(k)]=0;
							LOG_NOTICE("Activity", "ACT %d REMOVE REPLACE %d", singleObj.activityid(),
								tMap.mapids(k) );
						}
					}
				}
			}
			else if ( it->second.m_nCurState == ACTIVITYSTATE_STARTED ) // ��ʼ��
			{
				// ��ͼ��ӵ����
				for ( int j=0; j< singleObj.mapdrops_size(); ++j )
				{
					MapDrop tMap = singleObj.mapdrops(j);
					for ( int k = 0; k < tMap.mapids_size(); ++k )
					{
						if ( tMap.mapids(k) <=0 || tMap.mapids(k) >= MAX_MAP_ID )
						{
							LOG_ERROR("Activity", "Error mapid %d in ACT %d", tMap.mapids(k), singleObj.activityid() );
							continue;
						}
						if (tMap.droptype() == DROPTYPE_ADD)
						{
							mMapAddDropTable[tMap.mapids(k)].push_back(tMap.dropid());
							LOG_NOTICE("Activity", "ACT %d pushed %d to map %d", singleObj.activityid(),
								tMap.dropid(), tMap.mapids(k) );
						}
						else if (tMap.droptype() == DROPTYPE_REPLACE)
						{
							if ( mMapRepDropTable[tMap.mapids(k)] != 0 )
							{
								LOG_ERROR("Activity", "mapid %d in ACT %d had drop %d now rep %d", 
									tMap.mapids(k), singleObj.activityid(), mMapRepDropTable[tMap.mapids(k)], tMap.dropid() );
							}
							mMapRepDropTable[tMap.mapids(k)]=tMap.dropid();
							LOG_NOTICE("Activity", "ACT %d ADD REPLACE %d:%d", singleObj.activityid(),
								tMap.mapids(k) , tMap.dropid() );
						}
					}
				}
			}
		}
	}	

	// ����ˢ��
	for ( int i = 0; i < tpMsg->activitylist_size(); ++i )
	{
		SingleActivity singleObj = tpMsg->activitylist(i);
		ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.find( singleObj.activityid() );
		if ( it == mSceneActivityMgr.end() )
		{
			LOG_ERROR("Activity", "can't find activity %d -x2 ??", singleObj.activityid() );
			continue;
		}
		else
		{
			LOG_NOTICE("Activity", "ACTID[%d] REF OGRE NUM %d", singleObj.activityid(), it->second.m_OgreIndexNum );
			for (int j = 0; j < it->second.m_OgreIndexNum; ++j )
			{
				COgreCreator* pCreator = (COgreCreator*)CCreatorManager::GetSingletonPtr()->GetCreator( it->second.m_OgreIndex[j] );
				if (pCreator == NULL)
				{
					LOG_ERROR("Activity", "ACTID[%d] OgreIdx %d NULL?",singleObj.activityid(), it->second.m_OgreIndex[j] );
					continue;
				}
				if (singleObj.activitystate() == ACTIVITYSTATE_STARTED)
				{
					// ˢ��
					if ( pCreator->mHasOgre == 0 )
					{
						unsigned int tEntityID = 0;
						pCreator->mActivity = singleObj.activityid();
						CMapModule::GetSingleton().CreateNpc( CSceneLogic::GetSingleton().GetLineID(), pCreator->mMapIndex, 0, (CCreator*)pCreator, tEntityID );
						LOG_NOTICE("Activity", "ACTID[%d] Refresh OGRE Idx%d Entity%d", singleObj.activityid(), it->second.m_OgreIndex[j], tEntityID );
					}
					else
					{
						LOG_ERROR("Activity", "ACTID[%d] Ref Idx %d HasOgre=%d", singleObj.activityid(), it->second.m_OgreIndex[j], pCreator->mHasOgre );
					}
				}
				else if (singleObj.activitystate() == ACTIVITYSTATE_NOT_START)
				{
					// ����� �ɵ���
					if( pCreator->mHasOgre != 0 )
					{
						CEntity* pOldEntity = CSceneLogic::GetSingletonPtr()->GetEntity( pCreator->mHasOgre );
						CSceneLogic::GetSingletonPtr()->DestroyEntity( pOldEntity, 0 ); // ���ٵ�
						pCreator->mHasOgre = 0;
						LOG_NOTICE("Activity", "ACTID[%d] Kill OGRE Idx %d HasOgre=%d", singleObj.activityid(), it->second.m_OgreIndex[j], pCreator->mHasOgre );
					}
					else
					{
						LOG_ERROR("Activity", "ACTID[%d] Kill Idx %d HasOgre=%d", singleObj.activityid(), it->second.m_OgreIndex[j], pCreator->mHasOgre );
					}
				}
			}	
		}
	}	
}

// ����������ڽ����еĻ�б�
void CActivityModule::Send2PlayerNowActivitys( CEntityPlayer* pPlayer )
{
	if (pPlayer==NULL)
		return;

	CMessageActivityChange2CliNotify msg;

	CMessage tMessage;
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTIFY_ACTIVITYCHANGED);
	tMessage.set_msgpara( (long) &msg );

	for ( ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.begin(); it != mSceneActivityMgr.end(); ++it )
	{
		if ( it->second.m_nCurState == ACTIVITYSTATE_STARTED && pPlayer->GetLevel() >= it->second.m_nLmtLevel )
		{
			SingleActivityNewState* tpSend2Cli = msg.add_activitylist();
			LK_ASSERT( tpSend2Cli != NULL, continue );
			tpSend2Cli->set_activityid( it->first );
			tpSend2Cli->set_activitystate(ACTIVITYSTATE_STARTED);
			tpSend2Cli->set_completetimes( GetTodayCompleteTimes(pPlayer, it->first) );
		}
	}
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMessage );
}


// ���ͻ��˷��ͻָ����Ϣ
void CActivityModule::SendHelpInfo2Client( CEntityPlayer* pPlayer )
{
	CMessageGetHelpDataResponse msg;

	for (ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.begin(); it != mSceneActivityMgr.end(); ++it)
	{
		// ���ȼ�����
		if ( pPlayer->GetLevel() < it->second.m_nLmtLevel )
			continue;
		PBSingleHelpData* pData = msg.add_helpdatas();
		pData->set_helpid(it->first);
		pData->set_completed( GetTodayCompleteTimes( pPlayer, it->first ));
		pData->set_weektimes( GetWeekCompleteTimes( pPlayer, it->first ) );
	}

	// ���ָ����Ϣ
	FillGuideIncInfo( pPlayer, msg.mutable_todayup() );
	CMessage tMessage;
	tMessage.mutable_msghead()->set_messageid( ID_S2C_GETHELPDATARESPONSE );
	tMessage.set_msgpara( (long) &msg );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMessage );
}

// �ж�ʱ���Ƿ�ʼ�� ��ʱ�˷���true ʱ���ʽ��HHMM �ģ��ר��
bool CActivityModule::IsPassed( int nTime )
{
	time_t t = time( 0 );
	tm tmp;
	localtime_r( &t, &tmp);

	int tHour = nTime/100;
	int tMini = nTime%100;

	if ( tmp.tm_hour > tHour ) // Сʱ������
	{
		return true;
	}
	else if ( tmp.tm_hour == tHour ) // Сʱ���
	{
		if ( tmp.tm_min >= tMini ) // ���ӳ�����
		{
			return true;
		}
	}
	return false;
}

void CActivityModule::FillGuideIncInfo( CEntityPlayer* pPlayer, PBTodayIncItem* pData )
{
	LK_ASSERT( pPlayer&&pData, return );
	CPropertyPlayer* tpProPlayer = (CPropertyPlayer*)pPlayer->GetProperty();

	int tAchiveID = CAchieveModule::GetSingleton().GetAchieveDataUnit(pPlayer->GetCharID());
	CAchieveDataUnit* tpAchive = (CAchieveDataUnit*)CSceneObjManager::GetSingleton().GetObject(tAchiveID);
	if (tpAchive != NULL)
	{
		 pData->set_achiveup( tpAchive->mTotalPoint-tpProPlayer->GetGuideData()->mAchiveBak );
	}
	pData->set_killup(tpProPlayer->GetKillNumIn()+tpProPlayer->GetKillNumOut()-tpProPlayer->GetGuideData()->mKillBak );
	int tLevelCha = pPlayer->GetLevel() - tpProPlayer->GetGuideData()->mLevelBak ;

	pData->set_levelup( tLevelCha );
	if ( tLevelCha > 0 ) // ����������
	{
		pData->set_expup((int)tpProPlayer->GetExp()); // TODO LY ����ÿ��Ӧ�õò�����ô�ྭ�� ����32λ
	}
	else
	{
		pData->set_expup((int)(tpProPlayer->GetExp()-tpProPlayer->GetGuideData()->mExpBak));
	}
	pData->set_honorup(tpProPlayer->GetHonor()-tpProPlayer->GetGuideData()->mHonorBak);
}

int  CActivityModule::GetActivityStateByID( int nActivityID )
{
	ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.find(nActivityID);
	if ( it == mSceneActivityMgr.end() )
	{
		return ACTIVITYSTATE_NOT_START;
	}
	else
	{
		return it->second.m_nCurState;
	}
}

int  CActivityModule::GetActivityOgreDropID( int nOgreTempID )
{
	// ���õ��ID
	ACTIVITY_OGRE_TYPE::iterator it = mAvtivityOgreMgr.find(nOgreTempID);
	if ( it == mAvtivityOgreMgr.end() ) // �Ҳ���
	{
		return 0;
	}
	else
	{
		int tActivityID = it->second.m_nActivityID;
		// ��û״̬
		if ( GetActivityStateByID(tActivityID) == ACTIVITYSTATE_STARTED )
		{
			return it->second.m_nDropID;
		}
	}
	return 0;
}

// �õ����������ɴ���
int  CActivityModule::GetTodayCompleteTimes( CEntityPlayer* pPlayer,  int nActivityID )
{
	if ( pPlayer == NULL )
		return 0;
	CPropertyPlayer* pPro = (CPropertyPlayer*)pPlayer->GetProperty();
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return 0 );
	CPlayerRepetion* tpPlayerRepetion = CRepetionModule::GetSingletonPtr( )->GetPlayerRepetion( pPlayer );
	if( tpPlayerRepetion == NULL )
	{
		return 0;
	}
	int nRetValue = 0;
	switch(nActivityID)
	{
	case HELPID_LONGGONG :
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_LONGGONG_EASY_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_PANTAO:
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_PANTAO_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_FAMILY_XIANTAO:
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_FAMILY_TASTE_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_HUANGFENGD:
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_HUANGFENGDONG_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_DAYANTA:
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_DAYANTA_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_LIANHUADONG:
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_LIANHUADONG_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_QUESTION:
		{
			nRetValue = (pPro->GetWelfareStatus());
			break;
		}
	case HELPID_CORPSBATTLE:
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(CORPS_BATTLE_SCABBLE, pPlayer));
			break;
		}
	case HELPID_FAMILY_BATTLE:
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_FAMILY_INDEX_ , (unsigned int*)&nRetValue );
			break;
		}
	case HELPID_DOUBLE:  // ˫������
		{
			CTemplateDiploidTimeTable* tpTplDiploid = ( CTemplateDiploidTimeTable* ) CDataStatic::GetTemp( TEMP_DOUBLE );
			LK_ASSERT( tpTplDiploid != NULL, return 0 );

			nRetValue = pPro->GetDiploid()/1000/60/60;
			break;
		}
	case HELPID_TODAY_LOOPS:  // ��������ʦ������
		{
			nRetValue = pList->mLoopTaskData.GetTodayCompletedTimes();
			break;
		}
	case HELPID_WEEK_LOOPS:  // ��������ʦ������
		{
			nRetValue = pList->mLoopTaskData.GetWeekLoops();
			break;
		}
	case HELPID_STORAGETASK:  // �����ʰ�����
		{
			nRetValue = pList->mStorageTaskMgr.GetTodayCompleted();
			break;
		}
	case HELPID_MINEMAP:  // �ر�ͼ����
		{
			nRetValue =  pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_MINEMAP);
			break;
		}
	case HELPID_FAMILY_SEND:  // ���廤������
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_FAMILY_SEND );
			break;
		}
	case HELPID_FAMILY_CHALLEGE:  // ������ս����
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_FAMILY_CHALANGE );
			break;
		}
	case HELPID_CORPS_RAO:  // �����ű�����
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_CORPS_OUT);
			break;
		}
	case HELPID_CORPS_SHOU:  // �����ر�����
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_CORPS_IN);
			break;
		}
	case HELPID_CORPS_CHALLEGE:  // ������ս����
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_CORPS_CHALANGE );
			break;
		}
	case HELPID_CORPS_SHOUQI:  // ������������
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SAVEFLAG1 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SAVEFLAG2 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SAVEFLAG3 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SAVEFLAG4 );
			break;
		}
	case HELPID_SELLSELF:  // ë���Լ�
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_COUNTRY7);
			break;
		}
	case HELPID_FAMILY_HONOR:  // ������ҫ����
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_FAMILY_HONNER);
			break;
		}
	case HELPID_BATTLE: // ��ս����ɽ
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_HUAGUOSHAN_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_COUNTRY_BUILD: // ���彨������
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_COUNTRY_ALL );
			break;
		}
	case HELPID_COUNTRY_HONOR:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_CAMP_SB );				
			break;
		}
	case HELPID_COUNTRY_FLAG:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_CAMP_TF1 );				
			break;
		}
	case HELPID_COUNTRY_DOOR:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_CAMP_TF2 );				
			break;
		}
	case HELPID_COUNTRY_JIAOZI:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SPRING9 );				
			break;
		}
	case HELPID_COUNTRY_QINGHUA:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SPRING5 );				
			break;
		}
	case HELPID_COUNTRY_WENQING:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SPRING1 );				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SPRING2 );				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SPRING3 );				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SPRING4 );				
			break;
		}
	case HELPID_COUNTRY_FULI: 
		{
			nRetValue = 0;				
			break;
		}
	case HELPID_FAMILY_CHUYAO:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_FAMILY_KILL );				
			break;
		}
	case HELPID_XUNXIAN:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_XUNXIAN1 );				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_XUNXIAN2 );				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_XUNXIAN3 );				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_XUNXIAN4 );				
			break;
		}
	case HELPID_SISHEN:
		{				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SISHEN2 );							
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SISHEN4 );							
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SISHEN6 );				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SISHEN7 );				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SISHEN8 );				
			break;
		}
	case HELPID_STONE:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SPRING10 );				
			break;
		}
	case HELPID_STONE2:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SPRING11 );				
			break;
		}
	case HELPID_HUANGFENG:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SPRING6 );				
			break;
		}
	case HELPID_CHIHUO:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SPRING7 );				
			break;
		}
	case HELPID_HEISHUI:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_SPRING8 );				
			break;
		}

		// Ԫ����
	case HELPID_YUANXIAOJIE:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_SPRING12 );
			break;
		}
	// ������Ե
	case HELPID_CLOUD_ACTIVITY:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_SISHEN1 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_SISHEN3 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_SISHEN5 );
			break;
		}
		// ���п�ս
	case HELPID_FLY_FB:
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_FLY_WAR_MAP_ID_, pPlayer));
			break;
		}
		// �ͻ�����
	case HELPID_ROSE:
		{
			unsigned int tKey = CPersonalTimesMgr::MakeKey(TIMESMGR_USEFLOWER, 0);
			nRetValue = pPro->GetTimesMgr()->GetTimes(tKey) ;
			break;
		}
		//������յ�ָ���ƴ�
	case HELPID_FOGUANG:
		{
			unsigned int tKey = CPersonalTimesMgr::MakeKey(TIMESMGR_FOGUANG, 0);
			nRetValue = pPro->GetTimesMgr()->GetTimes(tKey) ;
			break;
		}
		//��������ÿ��Ĥ�ݼƴ�
	case HELPID_DAY_SJ:
		{
			//unsigned int tKey = CPersonalTimesMgr::MakeKey(TASKDAILY_MOBAI, 0);
			//nRetValue = pPro->GetTimesMgr()->GetTimes(tKey) ;
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKDAILY_MOBAI);				
			break;
		}
		// ���������
	case HELPID_REDPAPER:
		{
			unsigned int tKey = CPersonalTimesMgr::MakeKey(TIMESMGR_USEGIFT, 0);
			nRetValue = pPro->GetTimesMgr()->GetTimes(tKey) ;
			break;
		}
		// ��̽����
	case HELPID_CITAN:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_CITAN1 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_CITAN2 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_CITAN3 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_CITAN4 );
			break;
		}
		// ɱ����������
	case HELPID_KILLZHUREN:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_KILLZHUREN1 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_KILLZHUREN2 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_KILLZHUREN3 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_KILLZHUREN4 );
			break;
		}
		// ɱ����������
	case HELPID_KILLWEIBIN:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_KILLWEIBIN1 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_KILLWEIBIN2 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_KILLWEIBIN3 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_KILLWEIBIN4 );
			break;
		}
	case HELPID_YUHUAYUAN: // ����԰����
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_GRAND_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_DUOBAO2:  // ����յ�
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_LIULI1 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_LIULI2 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_LIULI3 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_LIULI4 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_LIULI5 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_LIULI6 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_LIULI7 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_LIULI8 );
			break;
		}
	case HELPID_ZHONGQIU2: // ����
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_YUEGONG1 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_YUEGONG2 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_YUEGONG3 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_YUEGONG4 );
			break;
		}
	case HELPID_YUNXIAOTA: // ������
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_TOWER_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_TREASUREBOWL:
		{
			CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
			nRetValue = tpProperty->GetTreasureBowlInfo()->GetTotalNum();
			break;
		}
	case HELPID_NEW_XUNBAO2:  // ��Ѱ������յ
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_NEW_LIULZ1);
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_NEW_LIULZ2);
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_NEW_LIULZ3);
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_NEW_LIULZ4);
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_NEW_LIULZ5);
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_NEW_LIULZ6);
			break;
		}
	case HELPID_2011_SPRING3:  // ���ڻ
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_NEWYEAR_SZ1);
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_NEWYEAR_SZ2);
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_NEWYEAR_SZ3);
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_NEWYEAR_SZ4);
			break;
		}
	case HELPID_QIXI: // ����԰
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_GRAND_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_DATAOSHA:
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_DALUANDOU_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_CITAN_NEW:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(530033 );				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(530036 );				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(530039 );				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(530042 );				
			break;
		}
	case HELPID_WUDIDONG:
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_WUDITON_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_HANSHI:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_QMJ1);				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_QMJ2);				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_QMJ3);		
			break;
		}
	case HELPID_TEAMLOOP:
		{
			nRetValue = pList->GetTodayTeamLoopNum();			
			break;
		}
	case HELPID_STWMG:
		{
			nRetValue = (CRepetionModule::GetSingleton().GetPlayerJoinRepetionTakeCount(_REPE_SHITU_MAP_ID_, pPlayer));
			break;
		}
	case HELPID_YUENAN:
		{
			
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_BALANCE1 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_BALANCE2 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_BALANCE3 );
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_BALANCE4 );
			break;
		}
	case HELPID_HAVOC_IN_HEAVEN:
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( TASKGROUP_HAVOC_HEAVEN1);				
			nRetValue += pList->mTaskGroupMgr.GetTodayTimes(TASKGROUP_HAVOC_HEAVEN2);
			break;
		}

	default: // ���û�ҵ� ����Ϊ���°��ͨ�ù��� ֱ��������Ľӿ�
		{
			nRetValue = pList->mTaskGroupMgr.GetTodayTimes( nActivityID );
			break;
		}
	}
	return nRetValue;
}



// �õ����������ɴ���
int  CActivityModule::GetWeekCompleteTimes( CEntityPlayer* pPlayer,  int nActivityID )
{
	if ( pPlayer == NULL )
		return 0;
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return 0 );

	CPlayerRepetion* tpPlayerRepetion = CRepetionModule::GetSingletonPtr( )->GetPlayerRepetion( pPlayer );
	if( tpPlayerRepetion == NULL )
	{
		return 0;
	}

	unsigned int nRetValue = 0;
	switch(nActivityID)
	{
	case HELPID_LONGGONG :
		{
			unsigned int nTimes = 0;
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_LONGGONG_INDEX_ , &nTimes );
			nRetValue += nTimes;
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_LONGGONG_EASY_INDEX_ , &nTimes );
			nRetValue += nTimes;
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_LONGGONG_HARD_INDEX_ , &nTimes );
			nRetValue += nTimes;
			break;
		}
	case HELPID_PANTAO:
		{
			unsigned int nTimes = 0;
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_PANTAO_INDEX_ , &nTimes );
			nRetValue += nTimes;
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_PANTAO_EASY_INDEX_ , &nTimes );
			nRetValue += nTimes;
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_PANTAO_HARD_INDEX_ , &nTimes );
			nRetValue += nTimes;
			break;
		}
	case HELPID_FAMILY_XIANTAO:
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_FAMILY_TASTE_INDEX_ , &nRetValue );
			break;
		}
	case HELPID_HUANGFENGD:
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_HORNETSHOLE_INDEX_ , &nRetValue );
			break;
		}
	case HELPID_DAYANTA:
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_DAYANTA_INDEX_ , &nRetValue );
			break;
		}
	case HELPID_LIANHUADONG:
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_LIANHUADONG_INDEX_ , &nRetValue );
			break;
		}
	case HELPID_CORPSBATTLE:
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_CORPS_BATTLE_INDEX_ , &nRetValue );
			break;
		}
	case HELPID_FAMILY_BATTLE:
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_FAMILY_INDEX_ , &nRetValue );
			break;
		}
	case HELPID_WEEK_LOOPS:  // ��������ʦ������
		{
			nRetValue = pList->mLoopTaskData.GetWeekLoops();
			break;
		}
	case _REPE_HUAGUOSHAN_INDEX_: // ��ս����ɽ
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_HUAGUOSHAN_INDEX_ , &nRetValue );
			break;
		}
		// ���п�ս
	case HELPID_FLY_FB:
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_FLY_WAR , &nRetValue );
			break;
		}
	case HELPID_YUHUAYUAN: // ����԰����
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_GRAND_INDEX_ , &nRetValue );
			break;
		}
	case HELPID_YUNXIAOTA:
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_TOWNER_INDEX_ , &nRetValue );
			break;
		}
	case HELPID_WUDIDONG:
		{
			tpPlayerRepetion->GetRepetionWeekCount( _REPE_WUDIDONG_INDEX_ , &nRetValue );
			break;
		}
	default:
		{
			nRetValue = pList->mTaskGroupMgr.GetWeekTimes( nActivityID );
			break;
		}
	}
	return nRetValue;
}


void CActivityModule::OnMessageGetActivityInfo( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );
	CMessageGetActivityInfoRequest* tpReq = ( CMessageGetActivityInfoRequest* ) pMessage->msgpara();
	LK_ASSERT( tpReq != NULL , return );

	if ( tpReq->activityid_size() > HELPID_SIZE )
		return;

	CMessageGetActivityTimesResponse msg;
	for ( int i = 0; i < tpReq->activityid_size(); ++i )
	{
		ActivityInfo_4MSG* tpsingle = msg.add_info();
		LK_ASSERT( tpsingle != NULL, continue );
		tpsingle->set_activityid( tpReq->activityid(i) );
		tpsingle->set_times( GetTodayCompleteTimes( pPlayer, tpReq->activityid(i) ) );
	}
	
	msg.set_typeid_(tpReq->typeid_());
	CMessage	MsgHead;
	MsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_GETACTVITYINFO );
	MsgHead.set_msgpara( (int)&msg );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &MsgHead ) ;
}


// �����������֪ͨ
void CActivityModule::SendThrowHydrangeaNotify( int nThrowType, CEntityPlayer *pDesPlayer, CEntity *pNpc, CEntityPlayer *pSrcPlayer )
{
	LK_ASSERT( pDesPlayer != NULL, return )	
	CMessage tMsgHead;
	CMessageThrowHydrangeaNotify tMsgThrowHydrangea;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_THROWHYDRANGEA );
	tMsgHead.set_msgpara( (int)&tMsgThrowHydrangea );
	
	if ( pDesPlayer != NULL )
	{
		tMsgThrowHydrangea.set_receivername( pDesPlayer->GetCharName() );
		tMsgThrowHydrangea.set_desposx( pDesPlayer->GetPosX() );
		tMsgThrowHydrangea.set_desposy( pDesPlayer->GetPosY() );
	}
	
	if ( nThrowType == THROWTYPE_BYPLAYER )
	{
		if ( pSrcPlayer != NULL )
		{
			tMsgThrowHydrangea.set_throwername( pSrcPlayer->GetCharName() );
			tMsgThrowHydrangea.set_srcposx( pSrcPlayer->GetPosX() );
			tMsgThrowHydrangea.set_srcposy( pSrcPlayer->GetPosY() );
		}
	}
	else
	{
		if ( pNpc != NULL )
		{
			tMsgThrowHydrangea.set_srcposx( pNpc->GetPosX() );
			tMsgThrowHydrangea.set_srcposy( pNpc->GetPosY() );
		}
	}		
	tMsgThrowHydrangea.set_throwtype( nThrowType );	
	CSceneLogic::GetSingleton().SendCountryMessage( &tMsgHead, CSceneLogic::GetSingleton().GetLineID() );
}

// �����������֪ͨ
void CActivityModule::SendGrabHydrangeaEnableNotify( CEntityPlayer *pPlayer, CEntity *pEntity )
{
	LK_ASSERT( pPlayer != NULL && pEntity != NULL, return )	
	CMessage tMsgHead;
	CMessageGrabHydrangeaEnableNotify tMsgGrabHydrangeaEnable;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_GRABHYDRANGEAENABLE );
	tMsgHead.set_msgpara( (int)&tMsgGrabHydrangeaEnable );
	tMsgGrabHydrangeaEnable.set_hydrangeaholder( pPlayer->GetCharName() );
	
	CMapModule::GetSingleton().MessageBroadCast( pEntity, &tMsgHead, false );
}	

// ������Ļ�Ӧ��Ϣ
void CActivityModule::SendGrabHydrangeaResponse( CEntityPlayer *pPlayer, int nErrcode )
{
	LK_ASSERT( pPlayer != NULL, return )	
	CMessage tMsgHead;
	CMessageGrabHydrangeaResponse tMsgGrabHydrangea;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_GRABHYDRANGEA );
	tMsgHead.set_msgpara( (int)&tMsgGrabHydrangea );
	tMsgGrabHydrangea.set_errcode( nErrcode );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ������Ľ��֪ͨ
void CActivityModule::SendGrabHydrangeaResultNotify( CEntityPlayer *pDesPlayer, int nSrcPosX, int nSrcPosY, const char *pSrcName /* = NULL */ )
{	
	CMessage tMsgHead;
	CMessageGrabHydrangeaResultNotify tMsgGrabResult;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_GRABHYDRANGEARESULT );	
	tMsgHead.set_msgpara( (int)&tMsgGrabResult );
	
	if ( pSrcName != NULL )
	{
		tMsgGrabResult.set_srcname( pSrcName );
	}	
		
	tMsgGrabResult.set_srcposx( nSrcPosX );
	tMsgGrabResult.set_srcposy( nSrcPosY );	
	
	if( pDesPlayer != NULL )
	{
		tMsgGrabResult.set_desname( pDesPlayer->GetCharName() );
		tMsgGrabResult.set_desposx( pDesPlayer->GetPosX() );
		tMsgGrabResult.set_desposy( pDesPlayer->GetPosY() );
	}
	CSceneLogic::GetSingleton().SendCountryMessage( &tMsgHead, CSceneLogic::GetSingleton().GetLineID() );
}

// �������Ľ��֪ͨ
void CActivityModule::SendHydrangeaResultNotify( CEntityPlayer *pPlayer )
{  
	if ( pPlayer == NULL )
	{
		return;
	}
	
	CMessage tMsgHead;
	CMessageHydrangeaResultNotify tMsgHydrangeaResult;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_HYDRANGEAREASULT );
	tMsgHead.set_msgpara( (int)&tMsgHydrangeaResult ); 	
	tMsgHydrangeaResult.set_rolename(  pPlayer->GetCharName() );
	tMsgHydrangeaResult.set_rolesex( pPlayer->GetSex() );
	CSceneLogic::GetSingleton().SendCountryMessage( &tMsgHead, CSceneLogic::GetSingleton().GetLineID() );
}

// ��������ʼ��֪ͨ
void CActivityModule::SendStartHydrangeaNotify( int nMapID, int nPosX, int nPosY )
{
	CMessage tMsgHead;
	CMessageStartHydrangeaNotify tMsgStartHydrangea;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_STARTHYDRANGEA );
	tMsgHead.set_msgpara( (int)&tMsgStartHydrangea );
	tMsgStartHydrangea.set_mapid( nMapID );
	tMsgStartHydrangea.set_posx( nPosX );
	tMsgStartHydrangea.set_posy( nPosY );
	CSceneLogic::GetSingleton().SendCountryMessage( &tMsgHead, CSceneLogic::GetSingleton().GetLineID() );		
}

// ������Ļ�Ӧ��Ϣ	
void CActivityModule::SendThrowHydrangeaResponse( CEntityPlayer *pPlayer, int nErrcode )
{
	 LK_ASSERT( pPlayer != NULL, return )
	 CMessage tMsgHead;
	 CMessageThrowHydrangeaResponse tMsgThrowHydrangea;
	 
	 tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_THROWHYDRANGEA );
	 tMsgHead.set_msgpara( (int)&tMsgThrowHydrangea );
	 tMsgThrowHydrangea.set_errcode( nErrcode );
	 CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// �������������Ϣ
void CActivityModule::OnMessageGrabeHydrangeaRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{	
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	int tRet = mHydrangeaActivityManager.GrabHydrangea( pPlayer->GetCharID() );		
	SendGrabHydrangeaResponse( pPlayer, tRet );
}

// �����������
void CActivityModule::OnMessageThrowHydrangeaRequest( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )	
	PlayerThrowHydrangea( pPlayer );
}

// ***********************************************************
//  Function:		InitialHydrangea
//  Description:	��ʼ������·������
//  Input:		
//  Input:			
//  Input: 		
//  Input:			
//  OutPut:			
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
int CActivityModule::InitialHydrangea( const char *pFileName )
{
	LK_ASSERT( pFileName != NULL, return -1 )
	TiXmlDocument tDoc;
	LK_ASSERT( tDoc.LoadFile( pFileName ), return -1 )
	TiXmlElement *tpRoot = tDoc.FirstChildElement( "HydrangeaCongfig" );
	LK_ASSERT( tpRoot != NULL, return -1 )
	TiXmlElement *tpNpcConfig = tpRoot->FirstChildElement( "NpcConfig" );
	LK_ASSERT( tpNpcConfig != NULL, return -1 )		
	
	mHydrangeaNpcManager.InitializeConfig();			
	TiXmlElement *tpNpcInfo = tpNpcConfig->FirstChildElement( "NpcInfo" );
	for ( ; tpNpcInfo != NULL; tpNpcInfo = tpNpcInfo->NextSiblingElement() )
	{	
		CHydrangeaNpcPath tNpcPath;		
		
		tNpcPath.mMapID = atoi( tpNpcInfo->Attribute( "MapID" ) );
		tNpcPath.mNpcTmpID = atoi( tpNpcInfo->Attribute( "NpcTempID" ) );
		int tActivityID =  atoi( tpNpcInfo->Attribute( "ActivityID" ) );
		int tIndex = 0;
		for ( TiXmlElement *tpPath = tpNpcInfo->FirstChildElement( "Path" ); tpPath != NULL;
				tpPath = tpPath->NextSiblingElement() )
		{
			tNpcPath.mNpcPath[tIndex].mX = atoi( tpPath->Attribute( "x" ) );
			tNpcPath.mNpcPath[tIndex].mY = atoi( tpPath->Attribute( "y" ) );
			++tIndex;
		}
		
		mHydrangeaNpcManager.InsertNpcPath( tNpcPath, tActivityID );
	}
	
	TiXmlElement *tpTimeConfig = tpRoot->FirstChildElement( "TimeConfig" );
	LK_ASSERT( tpTimeConfig != NULL, return -1 )
	for ( TiXmlElement *tpTimeInfo = tpTimeConfig->FirstChildElement("Time"); tpTimeInfo != NULL;
			tpTimeInfo = tpTimeInfo->NextSiblingElement() )
	{
		CTimeInfo tTimeInfo;
		tTimeInfo.mHour = atoi( tpTimeInfo->Attribute( "Hour" ) );
		tTimeInfo.mMinute = atoi( tpTimeInfo->Attribute( "Minute" ) );
		tTimeInfo.mWeekDay = atoi( tpTimeInfo->Attribute( "WeekDay" ) ); 
		tTimeInfo.mActivityID = atoi( tpTimeInfo->Attribute( "ActivityID" ) ); 
		mHydrangeaNpcManager.InsertTimeInfo( tTimeInfo );
	}																						
	return SUCCESS;				
}

// ***********************************************************
//  Function:		InitialTreasureBowlConfig
//  Description:	��ʼ���۱����������Ϣ
//  Return:			
//  Others:
//  Date:	11/02/2010
// **********************************************************
int CActivityModule::InitialTreasureBowlConfig()
{	
	TiXmlDocument tDoc;	
	LK_ASSERT( tDoc.LoadFile( CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"/activity/TreasureBowl.xml" ) ) == true, return -1 );
	TiXmlElement *tpRoot = tDoc.FirstChildElement( "TreasureConfig" );
	LK_ASSERT( tpRoot != NULL, return -1 )
	TiXmlElement *tpProbality = tpRoot->FirstChildElement( "ProbabilityConfig" );
	LK_ASSERT( tpProbality != NULL, return -1 )
	
	
	mTreasureBowlManager.Initialize();
	if ( tpRoot->Attribute( "TotalNum" ) != NULL )
	{
		mTreasureBowlManager.SetTotalNum( atoi( tpRoot->Attribute( "TotalNum" ) ) );
	}
	for ( TiXmlElement *tpProbalityItem = tpProbality->FirstChildElement( "Probability" );
			tpProbalityItem != NULL; tpProbalityItem = tpProbalityItem->NextSiblingElement() )
	{
		CTreasureBowlProbality tTreasureBowlProbality;
		int tProbalityID = 0;
		if ( tpProbalityItem->Attribute( "ID" ) != NULL )
		{
			tProbalityID = atoi( tpProbalityItem->Attribute( "ID" ) );
		}
		unsigned int i = 0;
		for ( TiXmlElement *tpNumItem = tpProbalityItem->FirstChildElement( "NumberProbality" );
				tpNumItem != NULL; tpNumItem = tpNumItem->NextSiblingElement() )
		{
			if ( i >= ARRAY_CNT( tTreasureBowlProbality.mNum ) || i >= ARRAY_CNT( tTreasureBowlProbality.mProbality ) )
			{
				LOG_ERROR( "activity","[%s,%d] NumberProbality Wrong: Index:%d ", __FUNCTION__, __LINE__, i );
				break;
			}
			if ( tpNumItem->Attribute( "ItemNum" ) != NULL )
			{
				tTreasureBowlProbality.mNum[i] = atoi( tpNumItem->Attribute( "ItemNum" ) );				
			}
			
			if ( tpNumItem->Attribute( "Probality" ) != NULL )
			{
				tTreasureBowlProbality.mProbality[i] = atoi( tpNumItem->Attribute( "Probality" ) );				
			}
			++i;
		}
		mTreasureBowlManager.InsertTreasureBowlProbality( tProbalityID, tTreasureBowlProbality );		
	}
	
	TiXmlElement *tpExchangeConfig = tpRoot->FirstChildElement( "ExchangeConfig" );
	LK_ASSERT( tpExchangeConfig != NULL, return -1 )
	
	for ( TiXmlElement *tpItemConfig = tpExchangeConfig->FirstChildElement( "Item" );
			tpItemConfig != NULL; tpItemConfig = tpItemConfig->NextSiblingElement() )
	{
		CTreasureItemExchangeInfo tExchangeInfo;
		int tOldItemID = 0;
		
		if ( tpItemConfig->Attribute( "OldID" ) != NULL )
		{	 
			tOldItemID = atoi( tpItemConfig->Attribute( "OldID" ) );
		}
		
		if ( tpItemConfig->Attribute( "NewID" ) != NULL )
		{
			tExchangeInfo.mExchangeItemID = atoi( tpItemConfig->Attribute( "NewID" ) );
		}
		
		if ( tpItemConfig->Attribute( "ProbalityID" ) != NULL )
		{
			tExchangeInfo.mProbilityID = atoi( tpItemConfig->Attribute( "ProbalityID" ) );
		}
		
		if ( tpItemConfig->Attribute( "TipsNum" ) != NULL )
		{
			tExchangeInfo.mTipsNum = atoi( tpItemConfig->Attribute( "TipsNum" ) );
		}
		
		if ( tpItemConfig->Attribute( "UsedTime" ) != NULL )
		{
			tExchangeInfo.mUseTime = atoi( tpItemConfig->Attribute( "UsedTime" ) );
		}
		
		if ( tpItemConfig->Attribute( "TaxMoney" ) != NULL )
		{
			tExchangeInfo.mTaxMoney = atoi( tpItemConfig->Attribute( "TaxMoney" ) );
		}

		if ( tpItemConfig->Attribute( "TipsType" ) != NULL )
		{
			tExchangeInfo.mTipsType = atoi( tpItemConfig->Attribute( "TipsType" ) );				
		}
		mTreasureBowlManager.InsertTreasureBowlExchangeInfo( tOldItemID, tExchangeInfo );
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		StartHydrangeaActivity
//  Description:	��ʼ����
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
void CActivityModule::StartHydrangeaActivity( int nActivityID )
{	
	CTemplateActivityConfig *tpConfig = ( CTemplateActivityConfig * )CDataStatic::mActivityConfig;
	if ( tpConfig == NULL )
	{
		LOG_ERROR( "activity","CTemplateActivityConfig not config" );
		return;
	}
	
	mHydrangeaNpcManager.SetActivityID( nActivityID );
	
	// ����������ʼ��֪ͨ
	CHydrangeaNpcPath *tpNpcPath = mHydrangeaNpcManager.GetHydrangeaNpcPath( 0, nActivityID );
	if ( tpNpcPath == NULL )
	{
		return;
	}
	SendStartHydrangeaNotify( tpNpcPath->mMapID, tpNpcPath->mNpcPath[0].mX, tpNpcPath->mNpcPath[0].mY );
	
	// ����npc
	int tNpcNum = mHydrangeaNpcManager.GetNpcNum();
	for ( int i = 0; i < tNpcNum; ++i )
	{
		CHydrangeaNpcPath *tpNpcPath = mHydrangeaNpcManager.GetHydrangeaNpcPath( i, nActivityID );
		if ( tpNpcPath == NULL )
		{
			continue;
		}
		
		if ( tpNpcPath->mNpcTmpID == 0 )
		{
			continue;
		}
		
		unsigned int tEntityID = 0;
		CNpcCreator tNpcCreator;
		tNpcCreator.set_id( 0 );
		tNpcCreator.mNpcID = tpNpcPath->mNpcTmpID;
		tNpcCreator.mPosition = CWTPoint( tpNpcPath->mNpcPath[0].mX, tpNpcPath->mNpcPath[0].mY ); 
		CMapModule::GetSingleton().CreateNpc( (unsigned short)CSceneLogic::GetSingleton().GetLineID(), tpNpcPath->mMapID, INVALID_MAP_INDEX, &tNpcCreator, tEntityID );		
		CEntityNpc *tpEntity = ( CEntityNpc * )CSceneLogic::GetSingleton().GetEntity( tEntityID );
		if ( tpEntity == NULL )
		{
			continue;
		}
		CNpcModule::GetSingletonPtr()->OnSleep( tpEntity, false );
		CNpcModule::GetSingleton().OnMoveNpc( tEntityID, tpNpcPath->mNpcPath[0].mX, tpNpcPath->mNpcPath[0].mY );
		mHydrangeaNpcManager.SetNpcPosIndex( i, 0 );
		mHydrangeaNpcManager.SetNpcEntityID( i, tEntityID );
	}	 	

	// �����ƶ��ڵ�
	/*int tEntityID = mHydrangeaNpcManager.GetNpcEntityID( 0 );
	CEntity *tpNpc = CSceneLogic::GetSingleton().GetEntity( tEntityID );
	if ( tpNpc != NULL )
	{  		
		CPropertyModule::GetSingleton().StartRedstone( tpNpc, CSceneLogic::GetSingleton().GetLineID(), tpConfig->mHydrangeaRedStone, false );	
	}*/
	
	// �������׻�ļ�ʱ��
	int tOtherInfo = MESSAGE_ACTIVITY;
	int tTimerID = CTimerMng::GetSingleton().SetTimer( 0, TIMER_HYDRANGEAACTIVITY, tpConfig->mHydrangeaActivityTime, 1, &tOtherInfo );
	mHydrangeaActivityManager.SetActivityTimerID( tTimerID );
		
	// ���������׳��ļ�ʱ��
	CTimerMng::GetSingleton().SetTimer( 0, TIMER_HYDRANGEATHROW, tpConfig->mHydrangeaThrowTime, 1, &tOtherInfo );
	
	// ����ϲ�Ǽ�ʱ��
	if ( tpConfig->mSugarSpreadTime > 0 )
	{
		int tTimes = tpConfig->mHydrangeaActivityTime/tpConfig->mSugarSpreadTime;
		if ( tTimes > 0 )
		{
			CTimerMng::GetSingleton().SetTimer( 0, TIMER_HYDRANGEASUGAR, tpConfig->mSugarSpreadTime, 1, &tOtherInfo, tTimes );
		}			
	} 
	
	mHydrangeaActivityManager.SetActivityStatus( HYDRANGEASTATUS_START );		
}

// ***********************************************************
//  Function:		EndHydrangeaActivity
//  Description:	��������
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
void CActivityModule::EndHydrangeaActivity()
{
	if ( mHydrangeaActivityManager.GetActivityStatus() == HYDRANGEASTATUS_NULL )
	{
		return;
	}
	
	int tHydrangeaHolder = mHydrangeaActivityManager.GetHydrangeaHolderID();
	CEntityPlayer *pPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tHydrangeaHolder );
	if ( pPlayer != NULL )
	{
		SendHydrangeaResultNotify( pPlayer );
		pPlayer->SetHydrangeaStatus( PLAYER_HYDRANGEASTATUS_OWEN );
	}	
	ClearHydrangeaInfo();
	mHydrangeaActivityManager.SetActivityStatus( HYDRANGEASTATUS_NULL );
}

// ***********************************************************
//  Function:		ClearHydrangeaInfo
//  Description:	�����������Ϣ
//  Return:			
//  Others:
//  Date:	04/08/2010
// **********************************************************
void CActivityModule::ClearHydrangeaInfo()
{
	for( int i = 0; i < mHydrangeaNpcManager.GetNpcNum(); ++i )
	{
		if ( mHydrangeaNpcManager.GetNpcEntityID( i ) != 0 )
		{				
			CEntity *tpEntity = CSceneLogic::GetSingleton().GetEntity( mHydrangeaNpcManager.GetNpcEntityID( i ) );
			if ( tpEntity != NULL )
			{
				CSceneLogic::GetSingleton().DestroyEntity( tpEntity, 0 );
			}			
			mHydrangeaNpcManager.SetNpcEntityID( i, 0 );
		}
	}
	
	if ( mHydrangeaActivityManager.GetActivityTimerID() != 0 )
	{
		CTimerMng::GetSingleton().ClearTimer( mHydrangeaActivityManager.GetActivityTimerID() );
		mHydrangeaActivityManager.SetActivityTimerID( 0 );
	}
	mHydrangeaNpcManager.SetActivityID( 0 );
}

// ***********************************************************
//  Function:		CheckNpcPath
//  Description:	���npc���ƶ�·��
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
void CActivityModule::CheckNpcPath()
{
	if ( mHydrangeaActivityManager.GetActivityStatus() == HYDRANGEASTATUS_NULL )
	{
		return;
	}
	
	int tNpcNum = mHydrangeaNpcManager.GetNpcNum();
	bool tNpcAllReached = true;
	for ( int i = 0; i < tNpcNum; ++i )
	{
		int tEntityID = mHydrangeaNpcManager.GetNpcEntityID( i );
		if ( tEntityID == 0 )
		{
			continue;
		}
		CEntityNpc *tpEntity = (CEntityNpc *)CSceneLogic::GetSingleton().GetEntity( tEntityID );
		if ( tpEntity == NULL )
		{					 
			continue;
		}
		CNpcModule::GetSingletonPtr()->OnSleep( tpEntity, false );
		bool tReachEnd = false;		
		bool tStepComplete = mHydrangeaNpcManager.CheckNpcPos( i, tpEntity->GetPosX(), tpEntity->GetPosY(), tReachEnd );
		if ( tReachEnd == true )
		{
			CSceneLogic::GetSingleton().DestroyEntity( tpEntity, 0 );
			mHydrangeaNpcManager.SetNpcPosIndex( i , 0 );
		}
		else
		{	
			if ( tStepComplete == true )
			{	
				CWTPoint tPos;				
				int tPosIndex = mHydrangeaNpcManager.GetNpcPosIndex( i );
				mHydrangeaNpcManager.GetNpcPos( i, tPosIndex + 1, tPos );
				mHydrangeaNpcManager.SetNpcPosIndex( i, tPosIndex + 1 ); 				
				tpEntity->SetOrginPos( tPos );	
				CNpcModule::GetSingleton().OnMoveNpc( tEntityID, tPos.mX, tPos.mY );		
			}					 
			tNpcAllReached = false;
		}			
	}
	
	// ����Ƿ�����npc�������յ�
	if ( tNpcAllReached == true )
	{
		EndHydrangeaActivity();
	}
}

// ***********************************************************
//  Function:		CheckHydrageaActivityTime
//  Description:	������������Ƿ�ʼ
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
void CActivityModule::CheckHydrageaActivityTime()
{ 
	if ( mHydrangeaActivityManager.GetActivityStatus() != HYDRANGEASTATUS_NULL )
	{
		return;
	}
	
	time_t tTimeNow = time( 0 );
	tm *tpTime = localtime( &tTimeNow );
	CTimeInfo tTimeInfo;
	tTimeInfo.mHour = tpTime->tm_hour;
	tTimeInfo.mMinute = tpTime->tm_min;
	tTimeInfo.mWeekDay = tpTime->tm_wday;	
	int tActivityID = 0;
	if ( mHydrangeaNpcManager.CheckActivityTime( tTimeInfo, tActivityID ) == true )
	{	
				
		ClearHydrangeaInfo();		
		StartHydrangeaActivity( tActivityID ); 				
	}		
}

// ***********************************************************
//  Function:		OnTimeOutHydrangeaActivity
//  Description:	�������׼�ʱ��
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
void CActivityModule::OnTimeOutHydrangeaActivity( CTimerItem *pTimer )
{  
	LK_ASSERT( pTimer != NULL, return )	
	CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );
	mHydrangeaActivityManager.SetActivityTimerID( 0 );
	EndHydrangeaActivity();		
}

// ***********************************************************
//  Function:		OnTimeOutHydrangeaThrow
//  Description:	������ļ�ʱ��
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
void CActivityModule::OnTimeOutHydrangeaThrow( CTimerItem *pTimer )
{
	LK_ASSERT( pTimer != NULL, return )	
	CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );
	ThrowHydrangeaBySys();   
}

// ***********************************************************
//  Function:		OnTimeOutHydrangeaSugar
//  Description:	��ϲ�ǵļ�ʱ��
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
void CActivityModule::OnTimeOutHydrangeaSugar( CTimerItem *pTimer )
{	
	LK_ASSERT( pTimer != NULL, return )	
	if ( mHydrangeaActivityManager.GetActivityStatus() == HYDRANGEASTATUS_NULL )
	{			
		CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );																
		return;
	}		
	
	// �ҵ�һ���˲���һ������buff
	CEntity *tpEntity = CSceneLogic::GetSingleton().GetEntity( mHydrangeaNpcManager.GetNpcEntityID( 0 ) );
	if ( tpEntity == NULL )
	{
		CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );
		return;
	}

	CTemplateActivityConfig *tpConfig = ( CTemplateActivityConfig * )CDataStatic::mActivityConfig;
	if ( tpConfig == NULL )
	{
		CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );
		return;
	}
	
	SendThrowSugarNotify( tpEntity );
	MapPlayerChecker tPlayerChecker;
	tPlayerChecker.mEntityPtr = tpEntity;
	tPlayerChecker.mDistance = VIEW_RADIUS_X;
	tPlayerChecker.mLineID	= CSceneLogic::GetSingleton().GetLineID();			
	std::vector<CEntity *> tPlayerVector;
	SeenPlayerContainserSearcher<MapPlayerChecker> mSceenContainsers( tPlayerChecker, tPlayerVector );
	mSceenContainsers.Visit( tpEntity );
	if ( tPlayerChecker.mNum > 0 && tpConfig->mSugarSpreadNum )
	{
		int tPlayerNum = rand()%tpConfig->mSugarSpreadNum;
		for ( int i = 0; i < tPlayerChecker.mNum && i < tPlayerNum; ++i )
		{
			int tBuffIndex = rand()%( ARRAY_CNT(tpConfig->mHydrangeaSugarID) );
			if ( tpConfig->mHydrangeaSugarID[tBuffIndex] <= 0 )
			{
				continue;
			}		
			
			int tRandNum = rand()%( tPlayerChecker.mNum - i );
			if ( tPlayerChecker.mPlayerList[tRandNum+i] != NULL )
			{
				CPropertyModule::GetSingleton().InsertBuff( tPlayerChecker.mPlayerList[tRandNum+i], tpConfig->mHydrangeaSugarID[tBuffIndex] );
				tPlayerChecker.mPlayerList[tRandNum+i] = tPlayerChecker.mPlayerList[i];
			}	  		
		}		
	} 
	
	if ( pTimer->mCalledNum == 0 )
	{
		CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );
	}			
}

// ***********************************************************
//  Function:		OnTimeOutHydrangeaHold
//  Description:	ռ������ļ�ʱ��
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
void CActivityModule::OnTimeOutHydrangeaHold( CTimerItem *pTimer )
{ 
	LK_ASSERT( pTimer != NULL, return )	
	CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );
	if ( mHydrangeaActivityManager.GetActivityStatus() != HYDRANGEASTATUS_HOLD )
	{
		return;
	}
	
	CEntity *tpEntity = CSceneLogic::GetSingleton().GetEntity( mHydrangeaNpcManager.GetNpcEntityID( 0 ) );
	if ( tpEntity == NULL )
	{
		return;
	}
	
	int tHolderID = mHydrangeaActivityManager.GetHydrangeaHolderID();
	CEntityPlayer *tpPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tHolderID );
	if ( tpPlayer != NULL )
	{
		// �������npcһ���ķ�Χ�����ջ�����	
		if ( tpPlayer->IsWithinDistance( tpEntity, VIEW_RADIUS_Y ) == false )
		{							
			tpPlayer->SetHydrangeaStatus( PLAYER_HYDRANGEASTATUS_NULL );
			SendSetHydrangeaStatusNotify( tpPlayer, PLAYER_HYDRANGEASTATUS_NULL );
			ThrowHydrangeaBySys();			
		}
		else
		{
			mHydrangeaActivityManager.InitializeGrab();
			SendGrabHydrangeaEnableNotify( tpPlayer, tpEntity );	
			mHydrangeaActivityManager.SetActivityStatus( HYDRANGEASTATUS_GRAB );				
			CTemplateActivityConfig *tpConfig = ( CTemplateActivityConfig * )CDataStatic::mActivityConfig;
			if ( tpConfig == NULL )
			{
				return;
			}
			int tOtherInfo = MESSAGE_ACTIVITY;
			CTimerMng::GetSingleton().SetTimer( 0, TIMER_HYDRANGEAGRAB, tpConfig->mHydrangeaGrabTime+1000, 1, &tOtherInfo );		
		}		
	}
	else
	{
		// ��Ҳ�����ϵͳ��һ����ҷ���
		ThrowHydrangeaBySys();
	}
}

// ***********************************************************
//  Function:		OnTimeOutHydrangeaGrab
//  Description:	��������ļ�ʱ��
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
void CActivityModule::OnTimeOutHydrangeaGrab( CTimerItem *pTimer )
{  
	LK_ASSERT( pTimer != NULL, return )
	CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );	
	if ( mHydrangeaActivityManager.GetActivityStatus() == HYDRANGEASTATUS_NULL )
	{
		return;
	}	
	
	int tOriginalID = mHydrangeaActivityManager.GetOriginalHolder();
	CEntityPlayer *tpOriginalPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tOriginalID );
	
	int tHolderID = mHydrangeaActivityManager.GetHydrangeaHolderID();
	CEntityPlayer *tpHolderPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tHolderID );
	if ( tpOriginalPlayer != NULL )
	{
		tpOriginalPlayer->SetHydrangeaStatus( PLAYER_HYDRANGEASTATUS_NULL );
	}
	if ( tpHolderPlayer == NULL )
	{			
		// ��Ҳ�����ϵͳ��һ����ҷ���
		ThrowHydrangeaBySys();				
	}			
	else
	{			
		tpHolderPlayer->SetHydrangeaStatus( PLAYER_HYDRANGEASTATUS_HOLD );
		PlayerGrabHydrangea( tpOriginalPlayer, tpHolderPlayer );
	}
}

// ***********************************************************
//  Function:		ThrowHydrangeaBySys
//  Description:	ϵͳ��������
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
void CActivityModule::ThrowHydrangeaBySys()
{
	if ( mHydrangeaActivityManager.GetActivityStatus() == HYDRANGEASTATUS_NULL )
	{
		return;
	}
	
	// ��Ҳ�����ϵͳ��һ����ҷ���
	CEntity *tpEntity = CSceneLogic::GetSingleton().GetEntity( mHydrangeaNpcManager.GetNpcEntityID( 0 ) );
	if ( tpEntity == NULL )
	{
		return;
	}
	
	CTemplateActivityConfig *tpConfig = ( CTemplateActivityConfig * )CDataStatic::mActivityConfig;
	if ( tpConfig == NULL )
	{
		return;
	}
	
	MapPlayerChecker tPlayerChecker;
	tPlayerChecker.mEntityPtr = tpEntity;
	tPlayerChecker.mDistance = VIEW_RADIUS_X;
	tPlayerChecker.mLineID	= CSceneLogic::GetSingleton().GetLineID();			
	std::vector<CEntity *> tPlayerVector;
	SeenPlayerContainserSearcher<MapPlayerChecker> mSceenContainsers( tPlayerChecker,tPlayerVector );
	mSceenContainsers.Visit( tpEntity );
	
	if ( tPlayerChecker.mNum > 0 )
	{
		int tRandNum = rand()%tPlayerChecker.mNum;
		if ( tPlayerChecker.mPlayerList[tRandNum] != NULL )
		{
			SendThrowHydrangeaNotify( THROWTYPE_BYNPC, tPlayerChecker.mPlayerList[tRandNum], tpEntity, NULL );	
			mHydrangeaActivityManager.SetHydrangeaHolderID( tPlayerChecker.mPlayerList[tRandNum]->GetCharID() );
			mHydrangeaActivityManager.SetActivityStatus( HYDRANGEASTATUS_HOLD );
			tPlayerChecker.mPlayerList[tRandNum]->SetHydrangeaStatus( PLAYER_HYDRANGEASTATUS_HOLD );

			int tOtherInfo = MESSAGE_ACTIVITY;
			int tTimerID = CTimerMng::GetSingleton().SetTimer( 0, TIMER_HYDRANGEAHOLD, tpConfig->mHydrangeaHolderTime, 1, &tOtherInfo );				
			if ( mHydrangeaActivityManager.GetHydrangeaHolderTimerID() != 0 )
			{
				CTimerMng::GetSingleton().ClearTimer( mHydrangeaActivityManager.GetHydrangeaHolderTimerID() );	
			}
			
			CTemplateRedStoneExpTable *tpTable = ( CTemplateRedStoneExpTable * )CDataStatic::SearchTpl( tpConfig->mHydrangeaExpTableID );
			if ( tpTable != NULL )
			{
				int tExp  = tpTable->mExp[tPlayerChecker.mPlayerList[tRandNum]->GetLevel()];
				int tPlayerCharID = tPlayerChecker.mPlayerList[tRandNum]->GetCharID();
				CPropertyModule::GetSingleton().PlayerObtainExp2( tPlayerChecker.mPlayerList[tRandNum] , tExp, 0, EXPREASON_ACTIVITY,&tPlayerCharID, 1 );
			}						
			mHydrangeaActivityManager.SetHydrangeaHolderTimerID( tTimerID );
		}
	}
	else
	{
		// ���������׳��ļ�ʱ��
		int tOtherInfo = MESSAGE_ACTIVITY;
		CTimerMng::GetSingleton().SetTimer( 0, TIMER_HYDRANGEATHROW, 2000, 1, &tOtherInfo );
		mHydrangeaActivityManager.SetActivityStatus( HYDRANGEASTATUS_START );	
	}	
}

// ***********************************************************
//  Function:		PlayerGrabHydrangea
//  Description:	������
//  Return:			
//  Others:
//  Date:	03/31/2010
// **********************************************************
void CActivityModule::PlayerGrabHydrangea( CEntityPlayer *pOriginalPlayer, CEntityPlayer *pNewPlayer )
{	
	LK_ASSERT( pNewPlayer != NULL, return )	
	CTemplateActivityConfig *tpConfig = ( CTemplateActivityConfig * )CDataStatic::mActivityConfig;
	if ( tpConfig == NULL )
	{
		return;
	}
	
	if ( mHydrangeaActivityManager.GetActivityStatus() == HYDRANGEASTATUS_NULL )
	{
		return;
	}
	
	CEntity *tpEntity = CSceneLogic::GetSingleton().GetEntity( mHydrangeaNpcManager.GetNpcEntityID( 0 ) );
	if ( tpEntity == NULL )
	{
		return;
	}
	
	mHydrangeaActivityManager.SetActivityStatus( HYDRANGEASTATUS_HOLD );
		
	if ( pOriginalPlayer != NULL )
	{
		SendGrabHydrangeaResultNotify( pNewPlayer, pOriginalPlayer->GetPosX(), pOriginalPlayer->GetPosY(), pOriginalPlayer->GetCharName() );	
	}
	else
	{
		SendGrabHydrangeaResultNotify( pNewPlayer, tpEntity->GetPosX(), tpEntity->GetPosY() );
	}
	
	
	
	// ���ü�ʱ��
	CTemplateRedStoneExpTable *tpTable = ( CTemplateRedStoneExpTable * )CDataStatic::SearchTpl( tpConfig->mHydrangeaExpTableID );
	if ( tpTable != NULL )
	{
		int tExp  = tpTable->mExp[pNewPlayer->GetLevel()];
		int tPlayerCharID = pNewPlayer->GetCharID();
		CPropertyModule::GetSingleton().PlayerObtainExp2( pNewPlayer, tExp, 0, EXPREASON_ACTIVITY, &tPlayerCharID, 1 );
	}		
	
	int tOtherInfo = MESSAGE_ACTIVITY;
	int tTimerID = CTimerMng::GetSingleton().SetTimer( 0, TIMER_HYDRANGEAHOLD, tpConfig->mHydrangeaHolderTime, 1, &tOtherInfo );		
	if ( mHydrangeaActivityManager.GetHydrangeaHolderTimerID() != 0 )
	{
		CTimerMng::GetSingleton().ClearTimer( mHydrangeaActivityManager.GetHydrangeaHolderTimerID() );	
	}
	mHydrangeaActivityManager.SetHydrangeaHolderTimerID( tTimerID );	
	
}

// ***********************************************************
//  Function:		PlayerThrowHydrangea
//  Description:	������
//  Return:			
//  Others:
//  Date:	04/07/2010
// **********************************************************
void CActivityModule::PlayerThrowHydrangea( CEntityPlayer *pPlayer )
{
	LK_ASSERT( pPlayer != NULL, return )
	if ( mHydrangeaActivityManager.GetActivityStatus() == HYDRANGEASTATUS_NULL )
	{
		SendThrowHydrangeaResponse( pPlayer, ERR_THROWHYDRANGEA_ACTIVITYEND );
		return;
	}

	if ( mHydrangeaActivityManager.GetActivityStatus() != HYDRANGEASTATUS_HOLD )
	{
		SendThrowHydrangeaResponse( pPlayer, ERR_THROWHYDRANGEA_NOTALLOWED );
		return;
	}  							
	
	if ( mHydrangeaActivityManager.GetHydrangeaHolderID() != (int)pPlayer->GetCharID() )
	{
		SendThrowHydrangeaResponse( pPlayer, ERR_THROWHYDRANGEA_NOTHOLDER );
		return;	
	}
	
	CEntity *tpEntity = CSceneLogic::GetSingleton().GetEntity( mHydrangeaNpcManager.GetNpcEntityID( 0 ) );
	if( tpEntity == NULL )
	{
		SendThrowHydrangeaResponse( pPlayer, ERR_THROWHYDRANGEA_ACTIVITYEND );
		return;
	}
	
	if ( pPlayer->IsWithinDistance( tpEntity, VIEW_RADIUS_Y ) == false )
	{
		SendThrowHydrangeaResponse( pPlayer, ERR_THROWHYDRANGEA_FARDISTANCE );
		return;
	}
	
	CTemplateActivityConfig *tpConfig = ( CTemplateActivityConfig * )CDataStatic::mActivityConfig;
	if ( tpConfig == NULL )
	{
		return;
	}
		
	MapPlayerChecker tPlayerChecker;
	tPlayerChecker.mEntityPtr = tpEntity;
	tPlayerChecker.mDistance = VIEW_RADIUS_X;
	tPlayerChecker.mLineID	= CSceneLogic::GetSingleton().GetLineID();			
	std::vector<CEntity *> tPlayerVector;
	SeenPlayerContainserSearcher<MapPlayerChecker> mSceenContainsers( tPlayerChecker,tPlayerVector );
	mSceenContainsers.Visit( tpEntity );
	if ( tPlayerChecker.mNum <= 0 )
	{
		SendThrowHydrangeaResponse( pPlayer, ERR_THROWHYDRANGEA_FAILED );
		return;
	}
	
	int tRandNum = rand()%tPlayerChecker.mNum;
	if (  tPlayerChecker.mPlayerList[tRandNum] == NULL )
	{
		SendThrowHydrangeaResponse( pPlayer, ERR_THROWHYDRANGEA_FAILED );
		return;
	}
	

	if ( tPlayerChecker.mPlayerList[tRandNum]->GetCharID() == pPlayer->GetCharID() )
	{
		SendThrowHydrangeaResponse( pPlayer, ERR_THROWHYDRANGEA_FAILED );
		return;
	}
	
	SendThrowHydrangeaNotify( THROWTYPE_BYPLAYER, tPlayerChecker.mPlayerList[tRandNum], NULL, pPlayer );	
	mHydrangeaActivityManager.SetHydrangeaHolderID( tPlayerChecker.mPlayerList[tRandNum]->GetCharID() );
	mHydrangeaActivityManager.SetActivityStatus( HYDRANGEASTATUS_HOLD );
	tPlayerChecker.mPlayerList[tRandNum]->SetHydrangeaStatus( PLAYER_HYDRANGEASTATUS_HOLD );
	
	// ���ü�ʱ��
	CTemplateRedStoneExpTable *tpTable = ( CTemplateRedStoneExpTable * )CDataStatic::SearchTpl( tpConfig->mHydrangeaExpTableID );
	if ( tpTable != NULL )
	{
		int tExp  = tpTable->mExp[tPlayerChecker.mPlayerList[tRandNum]->GetLevel()];
		int tPlayerCharID = tPlayerChecker.mPlayerList[tRandNum]->GetCharID();
		CPropertyModule::GetSingleton().PlayerObtainExp2( tPlayerChecker.mPlayerList[tRandNum], tExp, 0, EXPREASON_ACTIVITY, &tPlayerCharID, 1 );	
		
		tExp = tpTable->mExp[pPlayer->GetLevel()];
		tPlayerCharID = pPlayer->GetCharID();
		CPropertyModule::GetSingleton().PlayerObtainExp2( pPlayer, tExp, 0, EXPREASON_ACTIVITY, &tPlayerCharID, 1 );
	}
	
	int tOtherInfo = MESSAGE_ACTIVITY;
	int tTimerID = CTimerMng::GetSingleton().SetTimer( 0, TIMER_HYDRANGEAHOLD, tpConfig->mHydrangeaHolderTime, 1, &tOtherInfo );	
	if ( mHydrangeaActivityManager.GetHydrangeaHolderTimerID() != 0 )
	{
		CTimerMng::GetSingleton().ClearTimer( mHydrangeaActivityManager.GetHydrangeaHolderTimerID() );	
	}
	
	mHydrangeaActivityManager.SetHydrangeaHolderTimerID( tTimerID );		
	pPlayer->SetHydrangeaStatus( HYDRANGEASTATUS_NULL );
	SendThrowHydrangeaResponse( pPlayer, SUCCESS );		 		
}

// ***********************************************************
//  Function:		SendSetHydrangeaStatusNotify
//  Description:	���������������״̬��֪ͨ
//  Return:			
//  Others:
//  Date:	04/08/2010
// **********************************************************
void CActivityModule::SendSetHydrangeaStatusNotify( CEntityPlayer *pPlayer, int nStatus )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageSetHydrangeaStatusNotify tMsgSetHydrangeaStatus;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_SETHYDRANGEASTATUS );
	tMsgHead.set_msgpara( (int)&tMsgSetHydrangeaStatus );
	tMsgSetHydrangeaStatus.set_roleentityid( pPlayer->GetEntityID() );
	tMsgSetHydrangeaStatus.set_hydrangeastatus( nStatus );	
	CMapModule::GetSingleton().MessageBroadCast( pPlayer, &tMsgHead, false, true );
}

// ***********************************************************
//  Function:		ClearHydrangeaStatus
//  Description:	�����ҵ�����״̬
//  Return:			
//  Others:
//  Date:	04/08/2010
// **********************************************************
void CActivityModule::ClearHydrangeaStatus( CEntityPlayer *pPlayer )
{  
	LK_ASSERT( pPlayer != NULL, return )
	if ( pPlayer->GetHydrangeaStatus() != PLAYER_HYDRANGEASTATUS_NULL )
	{
		pPlayer->SetHydrangeaStatus( PLAYER_HYDRANGEASTATUS_NULL );
		SendSetHydrangeaStatusNotify( pPlayer, PLAYER_HYDRANGEASTATUS_NULL );
	}	
}

// ***********************************************************
//  Function:		SendThrowSugarNotify
//  Description:	����ɢϲ�ǵ�֪ͨ
//  Return:			
//  Others:
//  Date:	04/07/2010
// **********************************************************
void CActivityModule::SendThrowSugarNotify( CEntity *pEntity )
{
	LK_ASSERT( pEntity != NULL, return );
	CMessage tMsgHead;
	CMessageThrowSugarNotify tMsgThrowSugar;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_NPCTHROWSUGAR );
	tMsgHead.set_msgpara( (int)&tMsgThrowSugar );
	tMsgThrowSugar.set_npcentityid( pEntity->GetEntityID() );
	CMapModule::GetSingleton().MessageBroadCast( pEntity, &tMsgHead, false );
}

// ������Ǭ����������
int  CActivityModule::OnUseLuckyBag( CEntityPlayer* pPlayer, CTplFuncItem* pItem, int vIndex )
{
	if (pPlayer == NULL)
		return -1;
	CPropertyPlayer* tpPro = (CPropertyPlayer*)pPlayer->GetProperty();
	CItemObject* pSrcItem = tpPro->GetBaggage()->GetItemObjPtr(vIndex);
	LK_ASSERT( pItem!=NULL && pSrcItem!=NULL, return -1 );

	// ���Ҫ�������ɲ���ʹ�� �����������
	if ( pItem->mParams[1] == 1 && (pPlayer->GetMetier() == 0 || pPlayer->GetMetier() == 7) )
	{
		return ERROR_ITEM_REAUEST_MENPAI;
	}

	//CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();

	lua_tinker::table ret = lua_tinker::call<lua_tinker::table, unsigned int, int>( L, "on_use_lucky_bag",
		pPlayer->GetEntityID(), pItem->mParams[0] );
	// �жϰ����ռ�
	int nType = ret.get<int>("award_type");
	int nItemID = ret.get<int>("item_id");
	int nNum = ret.get<int>("num");
	int nNotifyType = ret.get<int>("notify_type");
	int nStar = ret.get<int>("star");
	if ( nStar > 0 )
		nStar = ITEMUPLIMIT+nStar;

	switch(nType)
	{
	case LUCKYBAG_AWARD_ITEM:
		{
			// ���ʣ��������������� һ�ɲ��ÿ�
			//if (GetPlayerBagSpaceNum(pPlayer->GetEntityID()) < nNum)
			// �жϰ����Ƿ���
			CPropertyPlayer* pProperty=(CPropertyPlayer*)pPlayer->GetProperty();
			if ( !pProperty->TestBaggageSpace( &nItemID, &nNum, 1 ) )
			{
				// ����
				CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_INSERTITEM_NOSPACE );	
				return ERROR_INSERTITEM_NOSPACE;
			}
			else
			{
				// ����
				CItemObject *pInsItemPile = CPropertyModule::GetSingleton().PlayerInsertItem( pPlayer, nItemID, nNum, false, nStar );
				if ( pInsItemPile != NULL)
				{
					LogEventGetItemByDirectIns( pPlayer, 
						pInsItemPile->GetGUID(), nItemID, nNum, 
						CDropFrom::em_drop_from_item, 
						pSrcItem->GetItemID(), 
						pSrcItem->GetGUID() ); 

					// �����Ҫ�㲥 ��㲥
					if ( nNotifyType != 0 )
					{
						// 4����Ӫ��Ҫ�㲥
						int nParam[4] = {0};
						nParam[0] = pPlayer->GetCharID();
						nParam[1] = pItem->mTempID;
						nParam[2] = nItemID;
						nParam[3] = nNum;
						CPropertyModule::GetSingleton().SendEventNotify( nNotifyType, 1, nParam, 4, (char*)pPlayer->GetCharName(), NULL );
						CPropertyModule::GetSingleton().SendEventNotify( nNotifyType, 2, nParam, 4, (char*)pPlayer->GetCharName(), NULL );
						CPropertyModule::GetSingleton().SendEventNotify( nNotifyType, 3, nParam, 4, (char*)pPlayer->GetCharName(), NULL );
						CPropertyModule::GetSingleton().SendEventNotify( nNotifyType, 4, nParam, 4, (char*)pPlayer->GetCharName(), NULL );
					}
					break;
				}
				else
				{
					return -1;
				}
			}
			break;
		}
	case LUCKYBAG_AWARD_MONEY:
		{
			break;
		}
	case LUCKYBAG_AWARD_BAG:
		{
			break;
		}
	case LUCKYBAG_AWARD_OTHER:
		{
			break;
		}
	case LUCKYBAG_AWARD_TELEPORT: // ��������
		{
			int nLineID   = ret.get<int>("line_id"); // �����0 ���͵�ǰ��
			int nMapID    = ret.get<int>("map_id"); 
			int nPosX     = ret.get<int>("pos_x");  
			int nPosY     = ret.get<int>("pos_y");  

			if ( nLineID == 0 )
			{
				nLineID = pPlayer->GetNationality();
			}
			// �����Ҫ�㲥 ��㲥
			if ( nNotifyType != 0 )
			{
				// 4����Ӫ��Ҫ�㲥
				int nParam[4] = {0};
				nParam[0] = pPlayer->GetCharID();
				nParam[1] = pItem->mTempID;
				nParam[2] = 0;
				nParam[3] = 0;
				CPropertyModule::GetSingleton().SendEventNotify( nNotifyType, 1, nParam, 4, (char*)pPlayer->GetCharName(), NULL );
				CPropertyModule::GetSingleton().SendEventNotify( nNotifyType, 2, nParam, 4, (char*)pPlayer->GetCharName(), NULL );
				CPropertyModule::GetSingleton().SendEventNotify( nNotifyType, 3, nParam, 4, (char*)pPlayer->GetCharName(), NULL );
				CPropertyModule::GetSingleton().SendEventNotify( nNotifyType, 4, nParam, 4, (char*)pPlayer->GetCharName(), NULL );
			}
			// ����ǿ�� ���ȿ۳���Ʒ�ٴ���
			if ( pPlayer->GetLineID() != nLineID )
			{
				uint64_t ullGUID = 0;
				if ( CPropertyModule::GetSingleton().PlayerRemoveItem( pPlayer, vIndex, 1, &ullGUID ) == 0)
				{
					LogEventLostItemByUse( pPlayer, ullGUID, pItem->mTempID, 1);
				}
				CMapModule::GetSingleton().Teleport( (unsigned short)nLineID, nMapID, nPosX, nPosY, pPlayer );
				return -1;
			}
			else
			{
				CMapModule::GetSingleton().Teleport( (unsigned short)nLineID, nMapID, nPosX, nPosY, pPlayer );
			}
			break;
		}
	case 0: // û�ɹ� ���ÿ�
		{
			return -1;
		}
	default:
		{
			LOG_ERROR("activity", "luckybag no such type:%d", nType );
			return -1;
		}
	}

	return SUCCESS;
}

// �õ���ҵȼ�
int CActivityModule::GetPlayerLevel( int nEntityID )
{
	CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(nEntityID);
	if ( tpPlayer != NULL )
		return tpPlayer->GetLevel();
	return 0;
}

// �õ��������
int CActivityModule::GetPlayerMetier( int nEntityID )
{
	CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(nEntityID);
	if ( tpPlayer != NULL )
		return tpPlayer->GetMetier();
	return 0;
}

// �õ�����Ա�
int CActivityModule::GetPlayerGender( int nEntityID )
{
	CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(nEntityID);
	if ( tpPlayer != NULL )
		return tpPlayer->GetSex();
	return 0;
}

// �õ������ӪID
int  CActivityModule::GetCampID( int nEntityID )
{
	CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(nEntityID);
	if ( tpPlayer != NULL )
		return tpPlayer->GetNationality();
	return 0;
}


// �õ���Ұ����ո���
int CActivityModule::GetPlayerBagSpaceNum( int nEntityID )
{
	CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(nEntityID);
	if ( tpPlayer != NULL )
	{
		CPropertyPlayer* pPro = (CPropertyPlayer*)tpPlayer->GetProperty();
		CItemBoxToolkit tItemBoxTooKit( pPro->GetBaggage() );
		return  ( tItemBoxTooKit.GetLeftPileNum( -1 ) );
	}
	return 0;
}

// ����ҽ�����Ʒ (֧�ּ���װ��)
int CActivityModule::InsertItem( lua_tinker::table param )
{
	int nEntityID= param.get<int>("entity_id");
	int nItemID  = param.get<int>("item_id");
	int nNum	 = param.get<int>("num");
	int nStar	 = param.get<int>("star");
	int nInvalidTime = param.get<int>("invalid_time");
	
	CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(nEntityID);
	if ( tpPlayer == NULL )
	{
		return 0;
	}

	if ( nStar > 0 )
		nStar = ITEMUPLIMIT+nStar;

	CItemObject *pInsItemPile = CPropertyModule::GetSingleton().PlayerInsertItem( tpPlayer, nItemID, nNum, false, nStar, NULL, false, nInvalidTime );
	if ( pInsItemPile != NULL)
	{
		LogEventGetItemByDirectIns( tpPlayer, 
			pInsItemPile->GetGUID(), nItemID, nNum, 
			CDropFrom::em_drop_from_item, 
			0, 
			0 ); 
		return 1;
	}
	return 0;
}

// ���ʹ�����
int CActivityModule::SendErrNotice( int nEntityID, int nErrID )
{
	CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(nEntityID);
	if ( tpPlayer == NULL )
	{
		return 0;
	}
	CPropertyModule::GetSingleton().SendProErrorNotice( tpPlayer, nErrID );
	return 1;
}

// ��¼��־
void CActivityModule::Log_Error( const char* pStr )
{
	if (pStr == NULL)
		return;
	LOG_ERROR( "Activity", "[LUA]%s", pStr );	
}

// ***********************************************************
//  Function:		WriteInvestResultToFile
//  Description:	���ͳ�ƽ��
//  Return:			
//  Others:
//  Date:	04/21/2010
// **********************************************************
int CActivityModule::WriteInvestResultToFile()
{
	CInvestQuestionManage::INVESTLIBLIST *tpLibList = mInvestQuestionMng.GetQuestionLibList();			
	if ( tpLibList == NULL )
	{
		return -1;
	}
			
	const char *tpLogDir = "../log/investlog/";
	char tDirName[LOGNAMELENGTH] = { 0 };
	sprintf( tDirName, "%s", tpLogDir );
	CreatDir( tDirName, 0700 );

	time_t tTime = time( NULL );
	tm	   *tTm = localtime( &tTime );
	char tLogName[LOGNAMELENGTH] = { 0 };
	sprintf( tLogName,"Invest_%4d%02d%02d.xml", tTm->tm_year + 1900, tTm->tm_mon+1, tTm->tm_mday );	
	
	TiXmlDocument *tpDoc = new TiXmlDocument;			
	if ( tpDoc == NULL )
	{
		return -1;
	}
	TiXmlElement tRootElement( "InvestAnswer" );
	CInvestQuestionManage::INVESTLIBLIST::iterator it = tpLibList->begin();
	for ( ; it != tpLibList->end(); ++it )
	{
		TiXmlElement tLibElement( "InvestLib");		
		char tLibBuffer[50] = { 0 };
		sprintf( tLibBuffer, "%d", (it->second).GetLibID() );
		tLibElement.SetAttribute( "LibID", tLibBuffer );
				
		for ( int i = 0; i < MAX_QUESTIONNUM_EACHLIB; ++i ) 
		{
			CInvestAnswer *tpAnswer =  (it->second).GetAnswerInfo( i );
			if ( tpAnswer == NULL )
			{
				continue;				
			}
			if ( tpAnswer->mQuestionID == 0 )
			{
				continue;
			}
			TiXmlElement tQuestion( "QuestionID" );			  
			char tQuestionIDBuffer[50] = { 0 };
			sprintf( tQuestionIDBuffer, "%d", tpAnswer->mQuestionID );
			tQuestion.SetAttribute( "ID", tQuestionIDBuffer );
			for ( int i = 0; i < MAX_OPTION_NUM; ++i )
			{
				if ( tpAnswer->mAnswerCount[i] > 0 )
				{
					char tOptionBuffer[50] = { 0 };
					sprintf( tOptionBuffer, "%c", i+'A' );
					TiXmlElement tAnswerCount( "Answer" );
					tAnswerCount.SetAttribute( "Option", tOptionBuffer );
					tAnswerCount.SetAttribute( "CountSelected", tpAnswer->mAnswerCount[i] );
					tQuestion.InsertEndChild( tAnswerCount );
				}											
			}	
			tLibElement.InsertEndChild( tQuestion );	  
		}	
		tRootElement.InsertEndChild( tLibElement ); 		
	}
	tpDoc->InsertEndChild( tRootElement );
	char tSavepath[100] = { 0 };
	sprintf( tSavepath, "%s/%s", tDirName, tLogName );
	tpDoc->SaveFile( tSavepath );	
	delete tpDoc;
	mInvestQuestionMng.SetInvestOutput( true );
	return SUCCESS;
}

// ***********************************************************
//  Function:		GetInvestResult
//  Description:	��ȡ֮ǰ��ͳ�ƽ��
//  Return:			
//  Others:
//  Date:	04/21/2010
// **********************************************************
int CActivityModule::GetInvestResult()
{		
	time_t tTime = time( NULL );	
	tm	   *tTm = localtime( &tTime );
	char tLogName[LOGNAMELENGTH] = { 0 };
	sprintf( tLogName,"Invest_%04d%02d%02d.xml", tTm->tm_year + 1900, tTm->tm_mon, tTm->tm_mday );
	TiXmlDocument tDoc;
	sprintf( tLogName, "../log/investlog/Invest_%04d%02d%02d.xml", tTm->tm_year + 1900, tTm->tm_mon+1, tTm->tm_mday );	
	if ( tDoc.LoadFile( tLogName ) == false )
	{
		return 0;
	}
	mInvestQuestionMng.ClearAllLibAnswer();	
	TiXmlElement *tpRoot = tDoc.FirstChildElement( "InvestAnswer" );
	if ( tpRoot == NULL )
	{
		return 0;
	}
	
	TiXmlElement *tpLib = tpRoot->FirstChildElement( "InvestLib" );
	for ( ; tpLib != NULL; tpLib = tpLib->NextSiblingElement( ) )
	{
		int tLibID = 0;
		if ( tpLib->Attribute( "LibID" ) == NULL )
		{
			continue;
		}
		
		tLibID = atoi( tpLib->Attribute( "LibID" ) );
		CInvestQuestionLib *tpLibInfo = mInvestQuestionMng.GetInvestQuestLib( tLibID );
		if ( tpLibInfo == NULL )
		{
			continue;
		}
		
		TiXmlElement * tpAnswerElement = tpLib->FirstChildElement( "QuestionID" );
		for ( ; tpAnswerElement != NULL; tpAnswerElement = tpAnswerElement->NextSiblingElement() )
		{
			int tQuestionID = 0;
			if ( tpAnswerElement->Attribute( "ID" ) != NULL )
			{
				tQuestionID = atoi( tpAnswerElement->Attribute("ID" ) );
			}
			
			if ( tQuestionID == 0 )
			{
				continue;
			}		
			
			for ( TiXmlElement *tpOptionElement = tpAnswerElement->FirstChildElement( ); tpOptionElement != NULL;
				tpOptionElement = tpOptionElement->NextSiblingElement() )
			{
				if ( tpOptionElement->Attribute( "Option" ) == NULL )
				{
					continue;
				}
				
				int tOptionIndex = ( tpOptionElement->Attribute( "Option" ) )[0] - 'A';
				if ( tpOptionElement->Attribute( "CountSelected" ) == NULL ) 
				{
					continue;
				}
				
				int tOptionCount = atoi( tpOptionElement->Attribute( "CountSelected" ) );
				tpLibInfo->SetOptionCount( tQuestionID, tOptionIndex, tOptionCount  );
			}											
		}
	}
	return SUCCESS;			
}

// ***********************************************************
//  Function:		OnNewDayCome
//  Description:	��һ�쵽��
//  Date:	04/22/2010
// **********************************************************
void CActivityModule::OnNewDayCome( )
{
	// �������������ҵĺ��״̬
	std::vector<CEntityPlayer*> tPlayers;
	CSceneLogic::GetSingleton().GetPlayersInScene(tPlayers);
	CMessageGetOnlineGiftResponse msg;
	msg.set_retcode(0);
	CMessage tMsgHead;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_GETGIFT_RESPONSE );
	tMsgHead.set_msgpara( (int)&msg );
	// ֪ͨ���
	for ( std::vector<CEntityPlayer*>::iterator itPlayer = tPlayers.begin(); itPlayer != tPlayers.end(); ++itPlayer )
	{
		CSceneLogic::GetSingleton().Send2Player( (*itPlayer), &tMsgHead );
	}
}


int CActivityModule::ChangeRepetionIDToActivityID( int nRepetionID  )
{
	int nHelpID = 0;
	switch( nRepetionID )
	{
	case _REPE_LONGGONG_INDEX_:
	case _REPE_LONGGONG_EASY_INDEX_:
	case _REPE_LONGGONG_HARD_INDEX_:
		{
			nHelpID = HELPID_LONGGONG;
			break;
		}
	case _REPE_PANTAO_INDEX_:
	case _REPE_PANTAO_EASY_INDEX_:
	case _REPE_PANTAO_HARD_INDEX_:
		{
			nHelpID = HELPID_PANTAO;
			break;
		}
	case _REPE_HORNETSHOLE_INDEX_:
		{
			nHelpID = HELPID_HUANGFENGD;
			break;
		}
	case _REPE_DAYANTA_INDEX_:
		{
			nHelpID = HELPID_DAYANTA;
			break;
		}
	case _REPE_LIANHUADONG_INDEX_:
		{
			nHelpID = HELPID_LIANHUADONG;
			break;
		}
	case _REPE_FLY_WAR:
		{
			nHelpID = HELPID_FLY_FB;
			break;
		}
	case _REPE_FAMILY_TASTE_INDEX_:
		{
			nHelpID = HELPID_FAMILY_XIANTAO;
			break;
		}
	case _REPE_FAMILY_CHALLENGE_INDEX_:
		{
			nHelpID = HELPID_FAMILY_BATTLE;
			break;
		}
	case _REPE_CORPS_CHALLEGE_INDEX_:
		{
			nHelpID = HELPID_CORPSBATTLE;
			break;
		}
	default:
		{
			LOG_ERROR( "activity", "unkonw repetion id %d",  nRepetionID );
			break;
		}
	}
	
	return nHelpID;
		
}

// ***********************************************************
//  Function:		InitialOgreActivityConfig
//  Description:	��ʼ������ñ�
//  Date:	07/19/2010
// **********************************************************
int CActivityModule::InitialOgreActivityConfig( const char *pFileName )
{
	LK_ASSERT( pFileName != NULL, return -1 )	
	TiXmlDocument tDoc;
	if( tDoc.LoadFile( pFileName ) == false )
	{
		return -1;
	}	
	mOgreActivityManager.Initialize();	
	TiXmlElement *tpRootElement = tDoc.RootElement();
	LK_ASSERT( tpRootElement != NULL, return -1 )
	TiXmlElement *tpOgreInfo = tpRootElement->FirstChildElement();
	for ( ; tpOgreInfo != NULL; tpOgreInfo = tpOgreInfo->NextSiblingElement() )
	{
		COgreInfo tOgreInfo;
		if ( tpOgreInfo->Attribute( "ActivityType" ) != NULL )
		{
			tOgreInfo.mActivityType = atoi( tpOgreInfo->Attribute( "ActivityType" ) );
		}
		
		if ( tpOgreInfo->Attribute( "LiveTime" ) != NULL )
		{
			tOgreInfo.mLiveTime = atoi( tpOgreInfo->Attribute( "LiveTime" ) );
		}
		
		if ( tpOgreInfo->Attribute( "KillerID" ) != NULL )
		{
			tOgreInfo.mKillerID = atoi( tpOgreInfo->Attribute( "KillerID" ) );
		}
		
		if ( tpOgreInfo->Attribute( "TempID" ) != NULL )
		{
			tOgreInfo.mTempID = atoi( tpOgreInfo->Attribute( "TempID" ) );
		}
		
		if ( tpOgreInfo->Attribute( "ErrCode" ) != NULL )
		{
			tOgreInfo.mErrcode = atoi( tpOgreInfo->Attribute( "ErrCode" ) );	 			
		}
		
		if ( tpOgreInfo->Attribute( "BossOgre" ) != NULL )
		{
			tOgreInfo.mBossOgre = atoi( tpOgreInfo->Attribute( "BossOgre" ) );	 			
		}
		
		if ( tpOgreInfo->Attribute("DeathErrcode" ) != NULL )
		{
			tOgreInfo.mDeathErrcode = atoi( tpOgreInfo->Attribute( "DeathErrcode" ) );
		}
		
		mOgreActivityManager.InsertOgreInfo( tOgreInfo );		
	}	
	return SUCCESS;
}

// ***********************************************************
//  Function:		CheckOgreActivityInfoOnCreate
//  Description:	ˢ�¹���ʱ������Ļ��Ϣ
//  Date:	07/19/2010
// **********************************************************
int CActivityModule::CheckOgreActivityInfoOnCreate( int nTempID, int nEntityID /* = 0 */ )
{
	COgreInfo *tpOgreInfo = mOgreActivityManager.GetOgreInfo( nTempID );
	if ( tpOgreInfo == NULL )
	{
		return SUCCESS;
	}	
	
	// ����֪ͨ	
	CTemplateOgre *tpTplOgre = (CTemplateOgre *)CDataStatic::SearchTpl( nTempID) ;						
	LK_ASSERT( tpTplOgre != NULL, return  -1 )	
	CEntity *tpEntity = CSceneLogic::GetSingleton().GetEntity( nEntityID );
	if ( tpEntity != NULL && tpOgreInfo->mBossOgre == 1 )
	{
		int tIntParam[ 4 ] = { 0 };
		tIntParam[ 0 ] = tpEntity->GetNpcID();
		tIntParam[ 1 ] = tpEntity->GetMapID();
		tIntParam[ 2 ] = tpEntity->GetPosX();
		tIntParam[ 3 ] = tpEntity->GetPosY();
		CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_REFRESHBOSS, tpEntity->GetLineID(), tIntParam, ARRAY_CNT(tIntParam), NULL, NULL );
	}		
	
	switch( tpOgreInfo->mActivityType )
	{
		case OGREACTIVITY_STARTOGRESIEGE:
		{			
			CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_STARTOGRESIEGE, CSceneLogic::GetSingleton().GetLineID(), NULL, 0, NULL, NULL );
			break;
		}		  		
		default:
			break;
	}
	
	if ( tpOgreInfo->mLiveTime > 0 )
	{
		int tIntParam[ 3 ] = { 0 };
		tIntParam[ 0 ] = nTempID;
		tIntParam[ 1 ] = tpOgreInfo->mLiveTime;
		tIntParam[ 2 ] = tpOgreInfo->mErrcode;
		CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_SHOWOGRELIVETIME, CSceneLogic::GetSingleton().GetLineID(), tIntParam, ARRAY_CNT( tIntParam ), NULL, NULL );
	}	
	
	tpOgreInfo->SetEntityID( nEntityID ); 	
	return SUCCESS;
}	

// ***********************************************************
//  Function:		CheckOgreActivityInfoOnDeath
//  Description:	��������ʱ������Ļ��Ϣ
//	OutPut:	bool �Ƿ�����
//  Date:	07/19/2010
// **********************************************************
int CActivityModule::CheckOgreActivityInfoOnDeath( int nTempID, int nKillerID )
{
	COgreInfo *tpOgreInfo = mOgreActivityManager.GetOgreInfo( nTempID );
	if ( tpOgreInfo == NULL )
	{
		return SUCCESS;
	}		
	
	int tKillerOgreTmpID = 0;
	CEntity *tpEntity = CSceneLogic::GetSingleton().GetEntity( nKillerID );
	if ( tpEntity != NULL )
	{
		if ( tpEntity->IsOgre() )
		{
			tKillerOgreTmpID = tpEntity->GetProperty()->GetPropertyTempID();
		}				
	}
	
	if ( tpEntity != NULL && tpOgreInfo->mBossOgre == 1 )
	{
		if ( tpEntity->IsPlayer() )
		{
			int tIntParam[ 3 ] = { 0 };
			tIntParam[ 0 ] = nTempID;
			tIntParam[ 1 ] = RAND(4);
			tIntParam[ 2 ] = tpOgreInfo->mErrcode;
			int tCountryID = tpEntity->GetLineID( );
			if( IS_REPETION_LINE_ID( tCountryID ) == false )
			{
				CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_PLAYERKILLBOSS, tCountryID, tIntParam, 
					ARRAY_CNT(tIntParam), (char *)(((CEntityPlayer*)tpEntity)->GetName( )), NULL );
			}			
		}

		else if ( tpEntity->IsOgre() )
		{
			CProperty *tpProperty = tpEntity->GetProperty();		
			int tIntParam[ 3 ] = { 0 };
			tIntParam[ 0 ] = tpProperty->GetPropertyTempID();
			tIntParam[ 1 ] = nTempID;
			tIntParam[ 2 ] = tpOgreInfo->mErrcode;
			int tCountryID = tpEntity->GetLineID( );

			if( IS_REPETION_LINE_ID( tCountryID ) == false )
			{
				CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_OGREKILLBOSS, tCountryID, tIntParam, 
					ARRAY_CNT(tIntParam),  NULL, NULL );				
			}												
		}
		
		if ( tpOgreInfo->mDeathErrcode != 0 )
		{
			CMessage tMsgHead;		
			tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_PROERROR );   
			CMessageProErrorNotice tMessage;
			tMessage.set_errorcode( tpOgreInfo->mDeathErrcode );
			tMsgHead.set_msgpara( (int)&tMessage );
			CSceneLogic::GetSingleton().SendCountryMessage( &tMsgHead, CSceneLogic::GetSingleton().GetLineID() );
		}
	}

	switch( tpOgreInfo->mActivityType )
	{
		case OGREACTIVITY_ENDOGRESIEGE:
		{						
			if ( tpOgreInfo->IsDead() == true )
			{
				break;
			}
			int tIntParam[ 3 ] = { 0 };
			tIntParam[ 0 ] = nTempID;
			tIntParam[ 1 ] = tKillerOgreTmpID;		
			tIntParam[ 1 ] = tpOgreInfo->mErrcode;
			if ( tpOgreInfo->mKillerID == 0 )
			{	
				if ( nKillerID == 0 )
				{					
					CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_ENDOGRESIEGE, CSceneLogic::GetSingleton().GetLineID(), tIntParam, ARRAY_CNT( tIntParam ), NULL, NULL );																			
					
					// �������ٽ����				
					int tOtherInfo = MESSAGE_ACTIVITY;
					CTimerMng::GetSingleton().SetTimer( 0, TIMER_OGREACTIVITY_TIMEEND, 1000, 1, &tOtherInfo );					
				}			
			}			
			else if ( tpOgreInfo->mKillerID == 1  )
			{
				if ( nKillerID > 0 )
				{
					CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_ENDOGRESIEGE, CSceneLogic::GetSingleton().GetLineID(), tIntParam, ARRAY_CNT( tIntParam ), NULL, NULL );										
					
					// �������ٽ����				
					int tOtherInfo = MESSAGE_ACTIVITY;
					CTimerMng::GetSingleton().SetTimer( 0, TIMER_OGREACTIVITY_TIMEEND, 1000, 1, &tOtherInfo );					
				}
			}
			else if( tpOgreInfo->mKillerID == 2 )
			{
				if ( nKillerID > 0 )
				{
					CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_ENDOGRESIEGE, CSceneLogic::GetSingleton().GetLineID(), tIntParam, ARRAY_CNT( tIntParam ), NULL, NULL );																			
				}
				else
				{
					CMessage tMsgHead;		
					tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_PROERROR );   
					CMessageProErrorNotice tMessage;
					tMessage.set_errorcode( ERR_GRASSJELLYEND );
					tMsgHead.set_msgpara( (int)&tMessage );
					CSceneLogic::GetSingleton().SendCountryMessage( &tMsgHead, CSceneLogic::GetSingleton().GetLineID() );
				}				

				// �������ٽ����				
				int tOtherInfo = MESSAGE_ACTIVITY;
				CTimerMng::GetSingleton().SetTimer( 0, TIMER_OGREACTIVITY_TIMEEND, 1000, 1, &tOtherInfo );					
			}
			break;
		}

		default:
			break;
	}	 
	
	if( tpOgreInfo->mBossOgre == 1 )
	{
		tpOgreInfo->ClearEntityID();	
	}
	return SUCCESS;
}

// ***********************************************************
//  Function:		EndOgreActivity
//  Description:	��������
//	OutPut:		
//  Date:	07/21/2010
// **********************************************************
int CActivityModule::EndOgreActivity( CTimerItem *pTimer )
{
	LK_ASSERT( pTimer != NULL, return -1 )		
	CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );	
	mOgreActivityManager.EndOgreActivity( 0 );
	return 0;
}

// ***********************************************************
//  Function:		GetActivityOgreInfo
//  Description:	��ȡ��ֵ���Ϣ
//	OutPut:		
//  Date:	07/23/2010
// **********************************************************
COgreInfo * CActivityModule::GetActivityOgreInfo( int nTempID )
{
	return mOgreActivityManager.GetOgreInfo( nTempID );	
}

// ***********************************************************
//  Function:		ReadRoleValidQuestionConfig
//  Description:	��ȡ��Ƭ��֤������
//	OutPut:		
//  Date:	09/01/2010
// **********************************************************
void CActivityModule::ReadRoleValidQuestionConfig()
{
	//const char* pFileName = "../config/data/question/config.xml";
	const char* pFileName =CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"question/config.xml");
	LOG_INFO("default", "[%s:%d][%s] Load role valid question config. (file=%s)",
		__LK_FILE__, __LINE__, __FUNCTION__, pFileName);
		
	// �������ļ�
	TiXmlDocument tDoc;
	if( !tDoc.LoadFile(pFileName) )
	{
		LOG_ERROR( "default", "[%s:%d][%s] Load xml %s failed", 
			__LK_FILE__, __LINE__, __FUNCTION__, pFileName);
		return;
	}
	
	InitializeRoleValidQuestionInfo();
	
	TiXmlElement* tpRoot = tDoc.FirstChildElement();
	// ��ȡ�鶨����Ϣ
	TiXmlElement* tpGroups = tpRoot->FirstChildElement("Groups");
	if(NULL != tpGroups)
	{
		// ����������
		TiXmlElement* tpGroup = tpGroups->FirstChildElement("Group");
		while(NULL != tpGroup){
			// �������
			int groupId = atoi(tpGroup->Attribute("id"));
			const char* groupName = tpGroup->Attribute("name");
			SRoleValidQuestionGroup& group = mRoleValidQuestionGroups[groupId];
			// ��������ѡ��
			TiXmlElement* tpOption = tpGroup->FirstChildElement("Option");
			while(NULL != tpOption){
				// �������(ÿ�����64��)
				int optionId = atoi(tpOption->Attribute("id"));
				group.count = optionId + 1;
				SRoleValidQuestionOption& option = group.options[optionId];
				// ����ѡ����
				option.groupId = groupId;
				option.id = optionId;
				// ����ѡ����Դ
				const char* resource = tpOption->Attribute("resource");
				//sprintf(option.filename, "../config/data/question/%s/%s", groupName, resource);
				char stfile[128] = {0};
				sprintf(stfile,"question/%s/%s", groupName, resource);
				sprintf(option.filename, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),stfile));
				//memcpy(option.filename, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),stfile),1024);
				int handle = open(option.filename, O_RDONLY);
				option.length = read(handle, option.data, ROLE_VALID_QUESTION_RESOURCE_LENGTH);
				close(handle);
				LOG_INFO("default", "[%s:%d][%s] Read question resource file. [group=%d, id=%d, file=%s(%d)]",
					__LK_FILE__, __LINE__, __FUNCTION__, groupId, optionId, option.filename, option.length);
				// ������һ��
				tpOption = tpOption->NextSiblingElement("Option");
			}
			// ������һ��
			tpGroup = tpGroup->NextSiblingElement("Group");
		}
	}
	// ��ȡ���ⶨ����Ϣ
	TiXmlElement* tpQuestions = tpRoot->FirstChildElement("Questions");
	if(NULL != tpQuestions)
	{
		mRoleValidQuestionRange = atoi( tpQuestions->Attribute( "random_range" ) );
		mTalentTableID = atoi( tpQuestions->Attribute( "talent_tableid" ) );
		
		// ����������
		mRoleValideQuestionCount = 0;
		TiXmlElement* tpQuestion = tpQuestions->FirstChildElement("Question");
		while(NULL != tpQuestion){
			// �������
			int questionId = atoi(tpQuestion->Attribute("id"));
			mRoleValideQuestionCount = questionId + 1;
			SRoleValidQuestion& question = mRoleValidQuestions[questionId];
			// ���ñ��
			question.id = questionId;
			question.typeId = atoi(tpQuestion->Attribute("type"));
			question.resultId = atoi(tpQuestion->Attribute("result"));
			// ��������(���Ʋ��ô���1K)
			strcpy(question.description, tpQuestion->Attribute("description"));
			LOG_INFO("default", "[%s:%d][%s] Read question. [id=%d, description=%s]",
				__LK_FILE__, __LINE__, __FUNCTION__, questionId, question.description);
			// ������һ��
			tpQuestion = tpQuestion->NextSiblingElement("Question");
		}
	}
	LOG_INFO("default", "[%s:%d][%s] Load question resource success. [file=%s]",
		__LK_FILE__, __LINE__, __FUNCTION__, pFileName);	
}

// ***********************************************************
//  Function:		BuildQuestionVerifyMsg
//  Description:	����������֤����Ϣ
//	OutPut:		
//  Date:	09/02/2010
// **********************************************************
void CActivityModule::BuildQuestionVerifyMsg( CMessageQuestionVerifyNotify &rMsg, SRoleValidQuestionOption* pResults )
{
	LK_ASSERT( pResults != NULL, return )
	// ��������
	srand(time(NULL));
	// �����ȡһ������
	SRoleValidQuestionOption* pOptions[4];
	SRoleValidQuestionOption* pResultOption;
	SRoleValidQuestionOption* pResultOptions[4];
	SRoleValidQuestion& question = mRoleValidQuestions[rand() % mRoleValideQuestionCount];
	LOG_DEBUG("default", "[%s:%d][%s] Random question. (question=%d, type=%d, result=%d)",
		__LK_FILE__, __LINE__, __FUNCTION__, question.id, question.typeId, question.resultId);
	// ������������ѡ��
	int count = 0;
	SRoleValidQuestionOption* pAllOptions[ROLE_VALID_QUESTION_OPTION_COUNT * ROLE_VALID_QUESTION_GROUP_COUNT];
	for(int j=0; j<ROLE_VALID_QUESTION_GROUP_COUNT; j++){
		if(j != question.resultId){
			SRoleValidQuestionGroup& group = mRoleValidQuestionGroups[j];
			for(int i=0; i<group.count; i++){
				pAllOptions[count++] = &group.options[i];
			}
		}
	}
	// �������ͻ�ȡ����
	switch(question.typeId){
	  case 0:{
		  // ��ȡ��һ�����ѡ��
		  SRoleValidQuestionGroup& resultGroup = mRoleValidQuestionGroups[question.resultId];
		  pResultOption = &resultGroup.options[rand() % resultGroup.count];
		  pOptions[0] = pResultOption;
		  // ���ѡ��3������ѡ��
		  for(int n=1; n<4; n++){
			  int index = rand() % count;
			  LOG_DEBUG("default", "[%s:%d][%s] Option random (n=%d, index=%d)", __LK_FILE__, __LINE__, __FUNCTION__, n, index);
			  pOptions[n] = pAllOptions[index];
		  }
		  break;
			 }
			 // �ĸ�����ѡȡ�ǽ����һ��(����3�����һ��)
	  case 1:{
		  // ���ѡ��һ�����ѡ��
		  pResultOption = pAllOptions[rand() % count];
		  pOptions[0] = pResultOption;
		  // ���ѡ��һ������ѡ��
		  SRoleValidQuestionGroup& resultGroup = mRoleValidQuestionGroups[question.resultId];
		  for(int n=1; n<4; n++){
			  int index = rand() % resultGroup.count;
			  LOG_DEBUG("default", "[%s:%d][%s] Option random (n=%d, index=%d)", __LK_FILE__, __LINE__, __FUNCTION__, n, index);
			  pOptions[n] = &resultGroup.options[index];
		  }
		  break;
			 }
			 // �ĸ�����ѡȡ�ǽ����һ��(����3��Ϊһ��)
	  case 2:{
		  // ������鲻һ�������
		  int resultIndex = rand() % ROLE_VALID_QUESTION_GROUP_COUNT;
		  SRoleValidQuestionGroup* pResultGroup = &mRoleValidQuestionGroups[resultIndex];
		  SRoleValidQuestionGroup* pOtherGroups[ROLE_VALID_QUESTION_GROUP_COUNT];
		  int othrerIndex = 0;
		  for(int n=0; n<ROLE_VALID_QUESTION_GROUP_COUNT; n++){
			  if(n != resultIndex){
				  pOtherGroups[othrerIndex++] = &mRoleValidQuestionGroups[n];
			  }
		  }
		  SRoleValidQuestionGroup* pOtherGroup = pOtherGroups[rand() % (ROLE_VALID_QUESTION_GROUP_COUNT-1)];
		  // ���ɴ�
		  pOptions[0] = &pResultGroup->options[rand() % pResultGroup->count];
		  for(int n=1; n<ROLE_VALID_QUESTION_GROUP_COUNT; n++){
			  pOptions[n] = &pOtherGroup->options[rand() % pOtherGroup->count];
		  }
		  break;
			 }
	}
	// ���봦��
	for(int n=0; n<4; n++){
		BuildQuestionOptionData(pOptions[n], &pResults[n]);
	}
	for(int n=0; n<4; n++){
		pOptions[n] = &pResults[n];
	}
	// ��ס���
	pResultOption = &pResults[0];
	LOG_INFO("default", "[%s:%d][%s] Member question result. (question=%d, group=%d, option=%d, file=%s(%d)",
		__LK_FILE__, __LINE__, __FUNCTION__, question.id,
		pResultOption->groupId, pResultOption->id, pResultOption->filename, pResultOption->length);
			
	// ���ѡ��4�����
	for(int n=0; n<ROLE_VALID_QUESTION_GROUP_COUNT; n++){
		int index = rand() % (ROLE_VALID_QUESTION_GROUP_COUNT - n);
		LOG_DEBUG("default", "[%s:%d][%s] Result random (index=%d)", __LK_FILE__, __LINE__, __FUNCTION__, index);
		pResultOptions[n] = pOptions[index];
		for(int i=index; i<ROLE_VALID_QUESTION_GROUP_COUNT - 1; i++){
			pOptions[i] = pOptions[i+1];
		}
	}
	// �����Ϣ	
	rMsg.set_questionid(question.id);
	rMsg.set_question(question.description);
	for(int n=0; n<4; n++){
		LOG_DEBUG("default", "[%s:%d][%s] Send question (question=%d, group=%d, option=%d, file=%s(%d)",
			__LK_FILE__, __LINE__, __FUNCTION__, question.id,
			pResultOptions[n]->groupId, pResultOptions[n]->id, pResultOptions[n]->filename, pResultOptions[n]->length);
	}
	// ����ѡ��
	rMsg.set_optiona(pResultOptions[0]->data, pResultOptions[0]->length);
	rMsg.set_optionb(pResultOptions[1]->data, pResultOptions[1]->length);
	rMsg.set_optionc(pResultOptions[2]->data, pResultOptions[2]->length);
	rMsg.set_optiond(pResultOptions[3]->data, pResultOptions[3]->length);
}

// ***********************************************************
//  Function:		BuildQuestionOptionData
//  Description:	���������
//	OutPut:		
//  Date:	09/02/2010
// **********************************************************
void CActivityModule::BuildQuestionOptionData(SRoleValidQuestionOption* pInputOption, SRoleValidQuestionOption* pOutputOption)
{				  
	LK_ASSERT( pInputOption != NULL && pOutputOption != NULL, return )
	// ���û�������
	int length = pInputOption->length;
	int dateLength = length >> 1;
	uint16* pInput = (uint16*)pInputOption->data;
	uint16* pOutput = (uint16*)pOutputOption->data;
	pOutputOption->groupId = pInputOption->groupId;
	memcpy(pOutputOption->filename, pInputOption->filename, ROLE_VALID_QUESTION_DESCRIPTION_LENGTH);
	pOutputOption->id = pInputOption->id;
	pOutputOption->length = length ;
	// ���ɻ���
	int type = rand() % 2;
	uint16 randColor[24];
	int clength = (rand() % 12) + 12;
	for(int n=0; n<clength; n++){
		randColor[n] = rand() % mRoleValidQuestionRange;
	}
	// ����ͼ��
	uint16 bgcolor = rand() % 0xFFFF;
	for(int n=0; n<dateLength; n++){
		uint16 color = *pInput++;
		if(0 == color){
			color = bgcolor;
		}else if(type > 0){
			uint16 rcolor = randColor[n % clength];
			uint16 r = color >> 11;
			r = (r+rcolor < 0x1F) ? r + rcolor : 0x1F;
			uint16 g = (color >> 5) & 0x3F;
			g = (g+rcolor < 0x3F) ? g + rcolor : 0x3F;
			uint16 b = color & 0x001F;
			b = (b+rcolor < 0x1F) ? b + rcolor : 0x1F;
			color = (r<<11) | (g<<5) | b;
		}else{
			uint16 rcolor = randColor[n % clength];
			uint16 r = color >> 11;
			r = (r > rcolor) ? r - rcolor : 0;
			uint16 g = (color >> 5) & 0x3F;
			g = (g > rcolor) ? g - rcolor : 0;
			uint16 b = color & 0x001F;
			b = (b > rcolor) ? b - rcolor : 0;
			color = (r<<11) | (g<<5) | b;
		}
		*pOutput++ = color;
	}
}

// ***********************************************************
//  Function:		NotifyQuestionVerify
//  Description:	֪ͨ������֤
//	OutPut:		
//  Date:	09/02/2010
// **********************************************************
void CActivityModule::NotifyQuestionVerify( CEntityPlayer *pPlayer,  int nVerifyKind, int nVerifyType, int nVerifyTimeLength )
{
	LK_ASSERT( pPlayer != NULL, return )	
	CPropertyPlayer *pProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	CAnswerStatus *tpAnswerStatus = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject( pProperty->GetAnswerStatusObjID() );
	LK_ASSERT( tpAnswerStatus != NULL, return )
	
	if ( nVerifyKind == VERIFYKIND_NULL )
	{
		return;
	}
	
	if ( tpAnswerStatus->GetRoleVerifyKind() !=  VERIFYKIND_NULL )
	{
		return;
	}
	
	// ����״̬
	tpAnswerStatus->SetRoleVerifyKind( nVerifyKind );
	tpAnswerStatus->SetRoleVerifyType( nVerifyType );	
	
	// ������Ŀ
	CMessage tMsgHead;
	CMessageQuestionVerifyNotify tMsgVerify;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_QUESTIONVERIFY );
	tMsgHead.set_msgpara( (int)& tMsgVerify );
	
	SRoleValidQuestionOption tQuestionResultOption[4];	
	BuildQuestionVerifyMsg( tMsgVerify, tQuestionResultOption );
	
	// ��¼��Ŀ��	
	tpAnswerStatus->SetQuestionVerifyData( tQuestionResultOption[0].data, tQuestionResultOption[0].length );	
	
	// ���ü�ʱ��	
	if ( nVerifyType & VERIFYTYPE_TIMEOUT )
	{
		// �������ⳬʱ��ʱ��
		int tOtherInfo[3] = { 0 };
		tOtherInfo[0] = MESSAGE_ACTIVITY;
		tOtherInfo[1] = pPlayer->GetEntityID();	  	
		int tTimerID = CTimerMng::GetSingleton().SetTimer( 0, TIMER_QUESTIONVERIFY, nVerifyTimeLength*1000, 2, tOtherInfo );		
		tpAnswerStatus->SetVerifyTimeID( tTimerID );
	}
	
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		OnMessageAnswerVerifyRequest
//  Description:	�ͻ��˴�����֤�Ľ��֪ͨ
//	OutPut:		
//  Date:	09/02/2010
// **********************************************************
void CActivityModule::OnMessageAnswerVerifyRequest( CEntityPlayer *pPlayer, CMessage *pMsg )
{
	LK_ASSERT( pPlayer != NULL && pMsg != NULL, return )	
	CMessageAnswerVerifyRequest *tpMsg = ( CMessageAnswerVerifyRequest * )pMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
	
	CPropertyPlayer *tpProperty =( CPropertyPlayer * ) pPlayer->GetProperty(); 		
	CAnswerStatus *tpAnswer = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject( tpProperty->GetAnswerStatusObjID() );
	LK_ASSERT( tpAnswer != NULL, return )
	
	if ( tpAnswer->GetRoleVerifyKind() == VERIFYKIND_NULL )
	{
		return;
	}
	
	bool tCheckResult = tpAnswer->CheckQuestionVerifyData( tpMsg->mutable_answer()->c_str(), tpMsg->mutable_answer()->length() );
	int tVerifyKind = tpAnswer->GetRoleVerifyKind();
	tpAnswer->ClearQuestionVerifyInfo();			
	if ( tpAnswer->GetVerifyTimeID() != 0 )
	{
		CTimerMng::GetSingleton().ClearTimer( tpAnswer->GetVerifyTimeID() );
		tpAnswer->SetVerifyTimeID( 0 );
	}
	NotifyQuestionVerifyResult( pPlayer, tVerifyKind, tCheckResult, VERIFYREASON_ANSWER );	
	SendResponseAnswerVerify( pPlayer, tCheckResult );
}

void CActivityModule::OnMessagePlayerGetGiftRequest( CEntityPlayer *pPlayer, CMessage *pMsg )
{
	CMessageGetOnlineGiftRequest* ppmsg = (CMessageGetOnlineGiftRequest*)pMsg->msgpara(); // ������Ҷ���
	LK_ASSERT( ppmsg != NULL, return )
		CPropertyPlayer* tpPro = (CPropertyPlayer*)pPlayer->GetProperty();
	int nActID = 0;
	SinglePlayerActivityInfo* tpInf = NULL;//tpPro->GetActivityInfo( nActID );

	if (ppmsg->gifttype() == 0) // �ͺ���һ��
	{
		nActID = HELPID_ONLINEGIFT;
		tpInf = tpPro->GetActivityInfo( nActID );
		if (tpInf == NULL)
			return;
	}
	else
	{
		nActID = HELPID_ONLINEGIFT2;
		tpInf = tpPro->GetActivityInfo( nActID );
		if (tpInf == NULL)
			return;

		if (tpInf->nParam3==1)
			return;
	}

	int nCurState=tpInf->nState;

	std::vector<int> tIntParams;
	tIntParams.push_back(pPlayer->GetEntityID());
	tIntParams.push_back(tpInf->nState);
	tIntParams.push_back(tpInf->GetDuringTime(pPlayer));
	tIntParams.push_back(nActID);
	tIntParams.push_back(pPlayer->GetLevel());
	tIntParams.push_back(ppmsg->gifttype());

	std::vector<std::string> tStrParams;
	int nRet = FireActivityEvent(nActID, ACTIVITY_ACTION_GETGIFT, tIntParams, tStrParams );
	// 0�ɹ� ���� ʧ�� 1����
	if (nRet == 0 && tpInf->nState==nCurState ) // ����Ѿ���ȡ���(״̬�Ѿ��޸ľͲ�����)
	{
		tpInf->nParam3=1;
	}
}

// ***********************************************************
//  Function:		NotifyGetGiftResult
//  Description:	�ظ���ȡ����
//	OutPut:		
//  Date:	
// **********************************************************
void CActivityModule::NotifyGetGiftResult( int nEntityID , int nRet, int nGiftType )
{
	CEntityPlayer* pPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(nEntityID);
	if (pPlayer == NULL)
		return;

	CMessageGetOnlineGiftResponse msg;
	msg.set_retcode(nRet);
	msg.set_gifttype(nGiftType);
	CMessage tMsgHead;
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_GETGIFT_RESPONSE );
	tMsgHead.set_msgpara( (int)&msg );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		NotifyQuestionVerifyResult
//  Description:	������֤�Ľ��
//	OutPut:		
//  Date:	09/02/2010
// **********************************************************
void CActivityModule::NotifyQuestionVerifyResult( CEntityPlayer *pPlayer, int nVerifyKind, bool bResult, int nReason /* = VERIFYTYPE_NULL */ )
{
	LK_ASSERT( pPlayer != NULL, return )
	
	switch ( nVerifyKind )
	{
		case VERIFYKIND_REPETION:
		{
			CRepetionModule::GetSingleton().RepetionQuestionVerifyResult( pPlayer, bResult, nReason );
			break;
		}
		default:
			break;
	}	
	
	if ( bResult == true )
	{
		if ( mTalentTableID > 0 )
		{
			CTemplateLevelExp *tpTable = ( CTemplateLevelExp * )CDataStatic::SearchTpl( mTalentTableID );
			if ( tpTable != NULL )
			{
				// ������Ϊֵ
				CPropertyModule::GetSingleton().PlayerObtainTalentExp( pPlayer, tpTable->mLevelExp[pPlayer->GetLevel()] );
			}
		}
		
	}
}

// ***********************************************************
//  Function:		SendResponseAnswerVerify
//  Description:	���ʹ�����֤�Ľ��
//	OutPut:		
//  Date:	09/02/2010
// **********************************************************
void CActivityModule::SendResponseAnswerVerify( CEntityPlayer *pPlayer, int nResult )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageAnswerVerifyResponse tMsgAnswerVerify;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_ANSWERVERIFY );
	tMsgHead.set_msgpara( (int)&tMsgAnswerVerify );
	tMsgAnswerVerify.set_errcode( SUCCESS );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		OnTimeOutAnswerVerify
//  Description:	������֤��ʱ
//	OutPut:		
//  Date:	09/02/2010
// **********************************************************
void CActivityModule::OnTimeOutAnswerVerify( CTimerItem *pTimer )
{
	LK_ASSERT( pTimer != NULL, return )
		
	CEntityPlayer *tpPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetEntity( pTimer->mOtherInfo[1] );	
	CTimerMng::GetSingleton().ClearTimer( pTimer->get_id() );	
	if ( tpPlayer == NULL )
	{
		return;
	}	  		
	
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	CAnswerStatus *tpAnswer = ( CAnswerStatus * )CSceneObjManager::GetSingleton().GetObject( tpProperty->GetAnswerStatusObjID() );	
	LK_ASSERT( tpAnswer != NULL, return )
	tpAnswer->SetVerifyTimeID( 0 );	
	if ( tpAnswer->GetRoleverifyType() == VERIFYKIND_NULL )
	{
		return;
	}
	
	int tVerifyKind = tpAnswer->GetRoleVerifyKind();		
	tpAnswer->ClearQuestionVerifyInfo(); 
	NotifyQuestionVerifyResult( tpPlayer, tVerifyKind, false, VERIFYREASON_TIMEOUT ); 	
	
}

// ��ϵͳ�ʼ�
bool CActivityModule::SendSysMail( lua_tinker::table param )
{
	// ************�����б�**************//
	// char_name
	// char_id
	// id  ϵͳ�ʼ�ID
	// camp_id �����ӪID
	// money
	// item_id1~5
	// item_num1~5

	int nItemIDs[5] = { param.get<int>("item_id1"), param.get<int>("item_id2"), param.get<int>("item_id3")
		, param.get<int>("item_id4"), param.get<int>("item_id5") };

	int nItemNums[5] = { param.get<int>("item_num1"), param.get<int>("item_num2"), param.get<int>("item_num3")
		, param.get<int>("item_num4"), param.get<int>("item_num5") };

	int nTotalNum = 0;
	for ( int i = 0; i < 5; ++i )
	{
		if ( nItemIDs[i] == 0 )
			break;
		++nTotalNum;
	}

	CMailModule::GetSingleton().SendSysMail( param.get<char*>("char_name"), param.get<int>("char_id")
		, "", param.get<char*>("id"), "", nItemIDs, nItemNums, nTotalNum
		, param.get<int>("camp_id"), param.get<int>("money"), param.get<int>("char_id") ) ;

	return true;
}

// ������¼� (�ⲿ����)
int  CActivityModule::FireActivityEvent( int nActivityID, int nEventID, const std::vector<int>& rIntParams, std::vector<std::string>& rStrParams  )
{
	lua_tinker::table param(L);
	for ( std::vector<int>::const_iterator it = rIntParams.begin(); it != rIntParams.end(); ++it )
	{
		char tag[256]={0};
		snprintf(tag, 255, "IntParam%d", it - rIntParams.begin()+1 );
		param.set<int>(tag, *it );
	}
	for ( std::vector<std::string>::const_iterator it = rStrParams.begin(); it != rStrParams.end(); ++it )
	{
		char tag[256]={0};
		snprintf(tag, 255, "StringParam%d", it - rStrParams.begin()+1 );
		param.set<char*>(tag, (char*)it->c_str() );
	}

	int nRet = lua_tinker::call<int, int, int, lua_tinker::table>( L, "fire_activity_event", 
		nActivityID, nEventID, param );	
	return nRet;
}

// �������ػ�¼�֪ͨ
void CActivityModule::OnGateMessageActivityEventNotice( CMessage* pMessage )
{
	LOG_ERROR( "Activity", "#ACT OnGateMessageActivityEventNotice" );	
	CMessageActivityEventNotify* tpMsg = (CMessageActivityEventNotify*) pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );
	std::vector<int> tIntParams;
	std::vector<std::string> tStrParams;
	for ( int i = 0; i < tpMsg->intparams_size(); ++i )
	{
		tIntParams.push_back(tpMsg->intparams(i) );
	}
	for ( int i = 0; i < tpMsg->strparams_size(); ++i )
	{
		tStrParams.push_back( std::string( tpMsg->strparams(i).c_str() ) );
	}
	if (tpMsg->activityid() != 0)
		FireActivityEvent( tpMsg->activityid(), tpMsg->eventid(), tIntParams, tStrParams );

	// ���������ҵı�������ֵ
	CSceneObjManagerImp* pSceneneObjManagerImp = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp;
	for( CSceneObjManagerImp::ObjMng_EntityPlayer::iterator tPlayerIt = pSceneneObjManagerImp->mEntityPlayerPool.begin( ); 
		tPlayerIt != pSceneneObjManagerImp->mEntityPlayerPool.end( ); 
		++ tPlayerIt
		)
	{
		CEntityPlayer* tpSrcEntity = &( *tPlayerIt );

		// �ǳ���Ҫ��ontimerֻ�����Ѿ��ڳ����е����
		if( tpSrcEntity->GetCommState() != CEntityPlayer::STATE_INMAP ) 
		{
			continue;
		}
		CPropertyPlayer* tpPro = (CPropertyPlayer*)tpSrcEntity->GetProperty();
		tpPro->SetLastWeekIncCharm(tpPro->GetWeekIncCharm());
		tpPro->SetWeekIncCharm(0);
		LOG_ERROR( "Activity", "#ACT clear chm online char:%d", tpSrcEntity->GetCharID() );	
	}
	// д�����ļ�����ˢ��ʱ���������������������ȡ
	mLastClearWeekCharmTime=time(0);
	FILE* fp=fopen("weekcharm.timer", "w+");
	if ( fp != NULL )
	{
		fprintf(fp, "%d", (int)time(0));
		fclose(fp);
	}
	else
	{
		LOG_ERROR("Activity", "error in write 2 weekcharm.timer" );
	}
}

// ��ʼ����Ƭ��֤��Ϣ
int CActivityModule::InitializeRoleValidQuestionInfo()
{	
	mTalentTableID = 0;
	memset( mRoleValidQuestions, 0, sizeof( mRoleValidQuestions ) );	
	memset( mRoleValidQuestionGroups, 0, sizeof( 0 ) ) ;			
	mRoleValideQuestionCount = 0;
	return SUCCESS;
}

// �޸���һ��Ϣ&֪ͨ
int CActivityModule::ChangeActivityState( CEntityPlayer* pPlayer, int nActivityID, int nNewState, int nStateParam1, int nStateParam2, bool bIsNotify, bool bIsSetTime )
{
	LK_ASSERT(pPlayer!=NULL, return -1);
	// ���ȼ�  ��������� ֱ��return
	ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.find( nActivityID );
	if ( it != mSceneActivityMgr.end() )
	{
		if ( pPlayer->GetLevel() < it->second.m_nLmtLevel )
			return -1;
	}
	CPropertyPlayer* tpPro = (CPropertyPlayer*)pPlayer->GetProperty();
	SinglePlayerActivityInfo inf;
	SinglePlayerActivityInfo* pActIf = tpPro->GetActivityInfo(nActivityID);
	if ( pActIf != NULL )
	{
		inf = *pActIf;
	}
	else
	{
		if (!bIsSetTime)
		{
			inf.chg_tm=time(0);
			inf.nRealLastedTime=0;
			inf.nLastedSavedTime=0;
			inf.bIsChanged=true;
			LOG_ERROR("Activity", "NULL not set?? tm0=%d", time(0));
		}
	}
	inf.nState=nNewState;
	inf.nParam1=nStateParam1;
	inf.nParam2=nStateParam2;
	inf.nParam3=0;
	if (bIsSetTime)
	{
		inf.chg_tm=time(0);
		inf.nRealLastedTime=0;
		inf.nLastedSavedTime=0;
		inf.bIsChanged=true;
	}
	LOG_DEBUG("Activity", "inftm=%d", inf.chg_tm );
	tpPro->UpdateActivityInfo( nActivityID, inf );

	if (bIsNotify) // Ҫ֪ͨ�ͻ��� Ҫ�ֱ���ͬ�Ļ
	{
		switch ( nActivityID )
		{
		case HELPID_ONLINEGIFT: // �����ͺ���
			{
				// ֪ͨ�ͻ��� ʱ���ǲ���1  ��ƷID�ǲ���2
				CMessageStartGiftTimerNotify msg;
				msg.set_secs(nStateParam1);
				msg.set_giftid( nStateParam2 );
				CMessage tMsgHead;
				tMsgHead.mutable_msghead()->set_messageid( ID_S2C_GIFTTIMER_NOTIFY );
				tMsgHead.set_msgpara( (int)&msg );
				CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
				break;
			}
		case HELPID_ONLINEGIFT2: // �����ͺ���2�� ���ȼ�
			{
				// ���������ȡ ��֪ͨ
				SinglePlayerActivityInfo* tpInf = tpPro->GetActivityInfo( HELPID_ONLINEGIFT2 );
				if (tpInf == NULL)
					break;

				if (tpInf->nParam3==1)
					break;

				// ֪ͨ�ͻ��� ʱ���ǲ���1  ��ƷID�ǲ���2
				CMessageStartGiftTimerNotify msg;
				msg.set_secs(nStateParam1);
				msg.set_giftid( nStateParam2 );
				msg.set_gifttype(1);
				CMessage tMsgHead;
				tMsgHead.mutable_msghead()->set_messageid( ID_S2C_GIFTTIMER_NOTIFY );
				tMsgHead.set_msgpara( (int)&msg );
				CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
				break;
			}
		default:
			{
				break;
			}
		}
	}
	return 0;
}

// ��û״̬
int  CActivityModule::GetActivityState( int nActivityID )
{
	return CActivityModule::GetSingleton().GetActivityStateByID(nActivityID);
}

// �޸�ȫ����һ״̬ 
// ������
int  CActivityModule::ChangeAllActivityState( lua_tinker::table param )
{
	int nActivityID = param.get<int>("activity_id");
	int nNewState  = param.get<int>("state");
	int nStateParam1 = param.get<int>("param1");
	int nStateParam2 = param.get<int>("param2");
	bool bIsNotify = param.get<bool>("notify");
	bool bIsSetTime = param.get<bool>("set_time");

	std::vector<CEntityPlayer*> tPlayers;
	CSceneLogic::GetSingleton().GetPlayersInScene(tPlayers);

	// ֪ͨ���
	for ( std::vector<CEntityPlayer*>::iterator itPlayer = tPlayers.begin(); itPlayer != tPlayers.end(); ++itPlayer )
	{
		CActivityModule::GetSingleton().ChangeActivityState( *itPlayer, nActivityID, nNewState, nStateParam1, nStateParam2, bIsNotify, bIsSetTime );
	}
	return 0;
}

// �޸���һ״̬
int  CActivityModule::ChangeSingleActivityState( lua_tinker::table param )
{
	CEntityPlayer* pPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(param.get<int>("entity_id"));
	if (pPlayer == NULL)
		return -1;

	int nActivityID = param.get<int>("activity_id");
	int nNewState  = param.get<int>("state");
	int nStateParam1 = param.get<int>("param1");
	int nStateParam2 = param.get<int>("param2");
	bool bIsNotify = param.get<bool>("notify");
	bool bIsSetTime = param.get<bool>("set_time");

	CActivityModule::GetSingleton().ChangeActivityState( pPlayer, nActivityID, nNewState, nStateParam1, nStateParam2, bIsNotify, bIsSetTime );
	return 0;
}

// ��Ӧ�������
int CActivityModule::OnPlayerLevelUp(CEntityPlayer* pPlayer)
{
	if ( pPlayer == NULL)
		return -1;
	// TODO Ŀǰ�ͺ������������� ��ʱд��C++�� �Ժ���˿���д��LUA�ﴦ��
	// ������ͻȻ���� 
	ACTIVITY_MGR_TYPE::iterator it = mSceneActivityMgr.find( HELPID_ONLINEGIFT );
	if ( it != mSceneActivityMgr.end() )
	{
		if ( pPlayer->GetLevel()-1 < it->second.m_nLmtLevel && pPlayer->GetLevel() >= it->second.m_nLmtLevel )
		{
			std::vector<int> tIntParams;
			tIntParams.push_back(pPlayer->GetEntityID());
			tIntParams.push_back(0);
			tIntParams.push_back(0);
			tIntParams.push_back(1);
			tIntParams.push_back(HELPID_ONLINEGIFT);
			std::vector<std::string> tStrParams;
			FireActivityEvent(HELPID_ONLINEGIFT, ACTIVITY_ACTION_ONCREATE, tIntParams, tStrParams ); // ģ�������߾���
		}
	}

	int nMinLv = lua_tinker::call<int>( L, "get_min_level_for_gift2" );	
	// �ͺ���2 ҲҪ���������� TODO �Ժ���� ��������

	if ( nMinLv != 0 && pPlayer->GetLevel()-1 < nMinLv && pPlayer->GetLevel() >= nMinLv )
	{
		std::vector<int> tIntParams;
		tIntParams.push_back(pPlayer->GetEntityID());
		tIntParams.push_back(0);
		tIntParams.push_back(0);
		tIntParams.push_back(1);
		tIntParams.push_back(HELPID_ONLINEGIFT2);
		std::vector<std::string> tStrParams;
		FireActivityEvent(HELPID_ONLINEGIFT2, ACTIVITY_ACTION_ONCREATE, tIntParams, tStrParams ); // ģ�������߾���
	}


	// �ͺ���2 Ҫ���������¼�
	// ���������Ĵ����õ�

	if ( nMinLv != 0 && pPlayer->GetLevel() >= nMinLv )
	{
		CPropertyPlayer  *tpProperty = ( CPropertyPlayer  * )pPlayer->GetProperty();
		SinglePlayerActivityInfo* tpInf = tpProperty->GetActivityInfo( HELPID_ONLINEGIFT2 );
		if (tpInf != NULL) // Ϊ��˵��û�����ݣ��϶��������津���ģ�����ᡣ����
		{
			std::vector<int> tIntParams;
			tIntParams.push_back(pPlayer->GetEntityID()); //1
			tIntParams.push_back(tpInf->nState); //2
			// ����LUA �ѽ���ʱ��
			LOG_DEBUG("Activity", "KF:tm0:%d, tm:%d", time(0),tpInf->chg_tm );
			tIntParams.push_back(time(0)-tpInf->chg_tm);
			tIntParams.push_back(HELPID_ONLINEGIFT2);
			tIntParams.push_back(tpInf->nParam3);
			tIntParams.push_back(pPlayer->GetLevel());
			std::vector<std::string> tStrParams;
			FireActivityEvent(HELPID_ONLINEGIFT2, ACTIVITY_ACTION_LEVELUP, tIntParams, tStrParams ); // ģ�������߾���
		}
	}


	return 0;
}


// �������BUFF
int  CActivityModule::EntityInsertBuff( int nEntityID, int nBuff, int nBuffTime )
{
	CEntityCharacter* tpChar = (CEntityCharacter*)CSceneLogic::GetSingleton().GetEntity(nEntityID);
	if (tpChar!=NULL)
	{
		if ( !CPropertyModule::GetSingleton().InsertBuff( tpChar, nBuff, nBuffTime ) )
			return -1;
	}
	return 0;
}

// ����ʵ��
int  CActivityModule::EntityTeleport( lua_tinker::table param )
{
	int nEntityID = param.get<int>("entity_id");
	int nLineID   = param.get<int>("line_id"); // �����0 ���͵�ǰ��
	int nMapID    = param.get<int>("map_id"); 
	int nPosX     = param.get<int>("pos_x");  
	int nPosY     = param.get<int>("pos_y");  
	CEntityPlayer* tpEntity = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(nEntityID);
	if ( tpEntity == NULL )
		return -1;
	if ( nLineID == 0 )
	{
		nLineID = tpEntity->GetNationality();
	}
	CMapModule::GetSingleton().Teleport( (unsigned short)nLineID, nMapID, nPosX, nPosY, tpEntity );
	return 0;
}

int  CActivityModule::GetReplaceDropID(CEntity* pEntity)
{
	// Ŀǰֻ�е�ͼӰ�� ���յ�ͼ����
	if ( pEntity->GetMapID() < 0 || pEntity->GetMapID() >= MAX_MAP_ID )
	{
		LOG_ERROR("Activity", "error MAPID %d", pEntity->GetMapID());
		return 0;
	}
	return mMapRepDropTable[pEntity->GetMapID()];
}

void CActivityModule::GetAddDropID(CEntity* pEntity, std::vector<int>& vAddIDs)
{
	if ( pEntity->GetMapID() < 0 || pEntity->GetMapID() >= MAX_MAP_ID )
	{
		LOG_ERROR("Activity", "error MAPID2 %d", pEntity->GetMapID());
		return ;
	}
	for (ACTIVITY_MAP_DROP_TYPE::iterator it = mMapAddDropTable[pEntity->GetMapID()].begin();
		it != mMapAddDropTable[pEntity->GetMapID()].end(); ++it )
	{
		vAddIDs.push_back(*it);
	}
}

// ���ѵ�
bool  CActivityModule::CheckPileLimit( int nEntityID, int nTempID, int nNum )
{
	CEntityPlayer* tpEntity = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(nEntityID);
	if ( tpEntity == NULL )
		return false;
	CPropertyPlayer* pProperty=(CPropertyPlayer*)tpEntity->GetProperty();

	bool bRet = pProperty->TestBaggageSpace( &nTempID, &nNum, 1 );
	return bRet;
}

// ***********************************************************
//  Function:		OnMessageGetTreasureBowl
//  Description:	��ѯ��Ʒ�۱���Ϣ
//	OutPut:		
//  Date:	10/11/2010
// **********************************************************
void CActivityModule::OnMessageGetTreasureBowl( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )			
	CMessageGetTreasureBowlInfoRequest *tpMsg = ( CMessageGetTreasureBowlInfoRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	if ( GetActivityStateByID( HELPID_TREASUREBOWL ) == ACTIVITYSTATE_NOT_START )
	{
		return;
	}
		
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	CItemObject *tpItem = tpProperty->GetBaggage()->GetItemObjPtr( tpMsg->itemindex() );
	LK_ASSERT( tpItem != NULL, return )
	CTreasureItemExchangeInfo *tpTreasureItem = mTreasureBowlManager.GetTreasureBowlExchangeInfo( tpItem->GetItemID() );
	if ( tpTreasureItem == NULL )
	{
		SendResponseGetTreasureBowl( pPlayer, ERROR_TREASUREBOWL_CANNOTUSED, tpMsg->itemindex() );
		return;
	}
	
	tpProperty->GetTreasureBowlInfo()->RefreshExchangeTime();
	int tItemUsedTimes = 0;
	tpProperty->GetTreasureBowlInfo()->GetExchangeItem( tpItem->GetItemID(), tItemUsedTimes );
	int tItemTotalTimes = tpTreasureItem->mUseTime;
	int tAllUsedTimes = tpProperty->GetTreasureBowlInfo()->GetTotalNum();
	int tAllTotalTimes = mTreasureBowlManager.GetTotalNum();
	SendResponseGetTreasureBowl( pPlayer, SUCCESS, tpMsg->itemindex(), tItemUsedTimes, tItemTotalTimes, tAllUsedTimes, tAllTotalTimes, tpTreasureItem->mTaxMoney );
}

// ***********************************************************
//  Function:		SendResponseGetTreasureBowl
//  Description:	���Ͳ�ѯ��Ʒ�Ļ�Ӧ��Ϣ
//	OutPut:		
//  Date:	10/11/2010
// **********************************************************
void CActivityModule::SendResponseGetTreasureBowl( CEntityPlayer *pPlayer, int nErrcode, int nItemIndex, int nItemUsedTimes /* = 0 */, int nItemTatolTimes /* = 0 */, int nAllUsedTimes /* = 0 */, int nTotalTimes /* = 0 */, int nTaxMoney /* = 0 */ )
{
	LK_ASSERT( pPlayer != NULL, return )	
	CMessage tMsgHead;
	CMessageGetTreasureBowlInfoResponse tMsgGetTreasureBowl;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_GETTREASUREBOWLINFO );
	tMsgHead.set_msgpara( (int)&tMsgGetTreasureBowl );
	tMsgGetTreasureBowl.set_itemusedtimes( nItemUsedTimes );
	tMsgGetTreasureBowl.set_errcode( nErrcode );
	tMsgGetTreasureBowl.set_itemtotaltimes( nItemTatolTimes );
	tMsgGetTreasureBowl.set_allusedtimes( nAllUsedTimes );
	tMsgGetTreasureBowl.set_alltotaltimes( nTotalTimes );	
	tMsgGetTreasureBowl.set_index( nItemIndex );
	tMsgGetTreasureBowl.set_taxmoney( nTaxMoney );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		OnMessageStartTreasureBowl
//  Description:	��ʼ��Ʒ�۱�
//	OutPut:		
//  Date:	10/11/2010
// **********************************************************
void CActivityModule::OnMessageStartTreasureBowl( CEntityPlayer *pPlayer, CMessage *pMessage )
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return )
	CMessageStartTreasureBowlRequest *tpMsg = ( CMessageStartTreasureBowlRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return )	
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
	CItemObject *tpItem = tpProperty->GetBaggage()->GetItemObjPtr( tpMsg->itemindex() );
	LK_ASSERT( tpItem != NULL, return )
	
	if ( GetActivityStateByID( HELPID_TREASUREBOWL ) == ACTIVITYSTATE_NOT_START )
	{
		return;
	}	
	
	// �ж�npc
	CEntityNpc* tpEntity = dynamic_cast< CEntityNpc* >( CSceneObjManager::GetSingletonPtr( )->GetObject( tpMsg->entityid() ) );
	LK_ASSERT( tpEntity != NULL, return )
	if ( tpEntity->GetEntityType() != ENTITYTYPE_FUNCNPC )
	{
		return;
	}
		
	// �����ж�
	CPropertyNPC * tpNpcProperty = ( CPropertyNPC * )tpEntity->GetProperty(); 
	CTemplateNpc *tpTmpNpc = ( CTemplateNpc * )CDataStatic::SearchTpl( tpNpcProperty->GetPropertyTempID() );
	LK_ASSERT( tpTmpNpc != NULL, return )
	if ( tpTmpNpc->mTreasureBowlService == 0 )
	{
		return;
	}
	
	if ( pPlayer->IsWithinDistance( tpEntity, MAX_NPC_TALK_GIRD ) == false )
	{
		return;
	}	
		
	CTreasureItemExchangeInfo *tpExchangeInfo = mTreasureBowlManager.GetTreasureBowlExchangeInfo( tpItem->GetItemID() );
	if ( tpExchangeInfo == NULL )
	{
		SendResponseStartTreasureBowl( pPlayer, ERROR_TREASUREBOWL_CANNOTUSED );
		return;
	}

	// �󶨵���Ʒ
	if ( tpItem->GetBindStatus() != ITEM_BINDSTATUS_FREE )
	{
		SendResponseStartTreasureBowl( pPlayer, ERROR_TREASUREBOWL_CANNOTUSED );
		return;
	}
	
	// �жϽ�Ǯ
	if ( tpProperty->GetMoney() < tpExchangeInfo->mTaxMoney )
	{
		SendResponseStartTreasureBowl( pPlayer, ERROR_TREASUREBOWL_MONEYNOTENOUGH );
		return;
	}
	
	int tAllTotalNum = mTreasureBowlManager.GetTotalNum();
	int tItemTotalNum = tpExchangeInfo->mUseTime;
	
	int tAllUsedTimes = tpProperty->GetTreasureBowlInfo()->GetTotalNum();
	int tItemUsedTimes = 0;
	tpProperty->GetTreasureBowlInfo()->GetExchangeItem( tpItem->GetItemID(), tItemUsedTimes );	
	
	if ( tAllUsedTimes >= tAllTotalNum )
	{
		SendResponseStartTreasureBowl( pPlayer, ERROR_TREASUREBOWL_TOTALTIMELIMIT );
		return;
	}
	
	if ( tItemUsedTimes >= tItemTotalNum )
	{
		SendResponseStartTreasureBowl( pPlayer, ERROR_TREASUREBOWL_ITEMTIMELIMIT );
		return;
	}	 
	
	// �жϰ���������
	if ( tpProperty->GetBaggage()->Space( -1, MAX_TREASUREBOWL_SPACENUM ) == false )
	{
		SendResponseStartTreasureBowl( pPlayer, ERROR_TREASUREBOWL_BAGGAGEFULL );
		return;
	}	 
	
	// ���þ۱���Ʒ�ľ۱���Ϣ
	tpProperty->GetTreasureBowlInfo()->SetExchangeItem( tpItem->GetItemID() );	
		
	// �۱�
	int tNewItemID = 0;
	int tNewItemNumber = 0;
	int tRet = mTreasureBowlManager.StartTreasureBowl( tpItem->GetItemID(), tNewItemNumber, tNewItemID );
	if ( tRet != SUCCESS || tNewItemNumber <= 0 )
	{
		SendResponseStartTreasureBowl( pPlayer, ERROR_TREASUREBOWL_FAILED );		
		return;
	}  		
	SendResponseStartTreasureBowl( pPlayer, SUCCESS,  tpMsg->itemindex(), tNewItemID );

	// �۳��۱���Ʒ
	int tOldItemID = tpItem->GetItemID();
	uint64_t tGuID = 0;
	CPropertyModule::GetSingleton().PlayerRemoveItem( pPlayer, tpMsg->itemindex(), 1, &tGuID );
	LogEventLostItemByUse( pPlayer, tGuID, tpItem->GetItemID(), 1 );
	
	// ����۱��ɹ������Ʒ
	for ( int i = 0; i < tNewItemNumber; ++i )
	{
		CItemObject *tpItemObj = CPropertyModule::GetSingleton().PlayerInsertItem( pPlayer, tNewItemID, 1 );
		if ( tpItemObj != NULL )
		{
			LogEventGetItemByTreasureBowl( pPlayer, tpItemObj->GetGUID(), tNewItemID, 1 );
		}		
	}	
	
	// �۳���Ǯ
	CPropertyModule::GetSingleton().PlayerChangeMoney( pPlayer, tpExchangeInfo->mTaxMoney, true, false );	
	
	// �����Ҫ��ʾ�ͽ�����ʾ
	if ( tNewItemNumber >= tpExchangeInfo->mTipsNum )
	{
		SendTreasureBowlSuccessNotify( pPlayer, tOldItemID, tNewItemID, tNewItemNumber, tpExchangeInfo->mTipsType );
	}
}

// ***********************************************************
//  Function:		SendResponseStartTreasureBowl
//  Description:	���Ϳ�ʼ��Ʒ�۱��Ļ�Ӧ��Ϣ
//	OutPut:		
//  Date:	10/11/2010
// **********************************************************
void CActivityModule::SendResponseStartTreasureBowl( CEntityPlayer *pPlayer, int nErrcode, int nItemIndex /* = 0 */, int nNewItemID /* = 0 */ )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageStartTreasureBowlResponse tMsgStartTreasureBowl;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_STARTTREASUREBOWL );
	tMsgHead.set_msgpara( (int)&tMsgStartTreasureBowl );
	tMsgStartTreasureBowl.set_errcode( nErrcode );
	tMsgStartTreasureBowl.set_itemindex( nItemIndex );
	tMsgStartTreasureBowl.set_newitemid( nNewItemID );
	CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
}

// ***********************************************************
//  Function:		SendTreasureBowlSuccessNotify
//  Description:	���;۱��ɹ�����Ӫ��ʾ
//	OutPut:		
//  Date:	11/19/2010
// **********************************************************
void CActivityModule::SendTreasureBowlSuccessNotify(CEntityPlayer *pPlayer, int nOldItemID, int nNewItemID, int nItemNum, int nTipsType )
{
	LK_ASSERT( pPlayer != NULL, return )
	CMessage tMsgHead;
	CMessageTreasureBowlSuccessNotify tMsgTreasureBowlSuccess;
	
	tMsgHead.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_TREASUREBOWLSUCCESS );
	tMsgHead.set_msgpara( (int)&tMsgTreasureBowlSuccess );
	
	tMsgTreasureBowlSuccess.set_rolename( pPlayer->GetCharName() );
	tMsgTreasureBowlSuccess.set_newitemid( nNewItemID );
	tMsgTreasureBowlSuccess.set_olditemid( nOldItemID );
	tMsgTreasureBowlSuccess.set_itemnum( nItemNum );	
	if ( nTipsType == 0 )
	{
		CSceneLogic::GetSingleton().SendCountryMessage( &tMsgHead, pPlayer->GetNationality() );
	}
	else if ( nTipsType == 1 )
	{
		CSceneLogic::GetSingleton().SendWorldMessage( &tMsgHead );	
	}
}

void CActivityModule::LoadQuestionFileCallback(const char *pcConfigPath)
{
	printf("begin to reload question file ... \n");
	CActivityModule::GetSingleton().InitialQuestionFile(pcConfigPath);
	printf("reload question file done !!! \n");
}

void CActivityModule::LoadLuaFileCallback(const char *pcConfigPath)
{
	lua_State* pLuaState = CActivityModule::GetSingleton().L;
	if (pLuaState == NULL)
	{
		return;
	}

	lua_tinker::dofile(pLuaState, pcConfigPath);
}

void CActivityModule::LoadInvestQuestionFileCallback(const char *pcConfigPath)
{
	CActivityModule::GetSingleton().InitailInvestQuestionFile(pcConfigPath);
}

void CActivityModule::LoadDoubleExpFileCallback(const char* pcConfigPath)
{
	CActivityModule::GetSingleton().InitialDoubleExpFile(pcConfigPath);
}

void CActivityModule::LoadHydrangeaCallback(const char* pcConfigPath)
{
	CActivityModule::GetSingleton().InitialHydrangea(pcConfigPath);
}

void CActivityModule::LoadOgreActivityConfigCallback(const char* pcConfigPath)
{
	CActivityModule::GetSingleton().InitialOgreActivityConfig(pcConfigPath);
}

void CActivityModule::LoadTreasureBowlConfigCallback(const char* pcConfigPath)
{
	CActivityModule::GetSingleton().InitialTreasureBowlConfig();
}

void CActivityModule::LoadActivityYqsConfigCallback(const char* pcConfigPath)
{
	CActivityYqsCfg::GetSingleton().LoadConfigure();
}

void CActivityModule::LoadRoleValidQuestionConfigCallback(const char *pcConfigPath)
{
	CActivityModule::GetSingleton().ReadRoleValidQuestionConfig();
}