#include "stdafx.hpp"
#include "taskmodule.h"
#include "promessage_pb.hxx.pb.h"
#include "scenelogic.h"
#include "property.h"
#include "mapobjmanager.h"
#include "taskmessage_pb.hxx.pb.h"
#include "mapmodule.h"
#include "teammodule.h"
#include "teamtype.h"
#include "propertymodule.h"
#include "entity_searcher.h"
#include "message_factory.h"
#include "logservertype.h"
#include "message_maker.h"
#include "sceneobj_manager_imp.h"
#include "logmodule.h"
#ifdef LEAK_CHK_DEBUG_NEW
#include "debug_new.h"
#endif


template<> CTaskModule* CSingleton< CTaskModule >::spSingleton = NULL;
template<> CTaskLuaInterface* CSingleton< CTaskLuaInterface>::spSingleton = NULL;
CPropertyPlayer* CTaskLuaInterface::mpProperty = NULL;
CTaskList* CTaskLuaInterface:: mpTaskList = NULL;
CEntityPlayer* CTaskLuaInterface::mpPlayer = NULL;
unsigned short CTaskLuaInterface::mCurTaskID = 0;
std::map<int, int>* CTaskLuaInterface::mpTmpChecker = NULL;

char	CTaskModule::sModuleName[ NAME_LENGTH ] = "Task";


// --------------------------------------------------------------------------------------
unsigned int CTaskModule::CountSize()
{
	unsigned int tSize = sizeof( CTaskModule );
	return tSize;
}

// ���¼��������ļ�
void CTaskModule::OnLoadConfig()
{
	TASK_LOG* tpTask = CSceneCfgManager::GetSingletonPtr()->GetTask_log();
	if( tpTask != NULL )
	{
		INIT_ROLLINGFILE_LOG( tpTask->mIdentifier, tpTask->mDirectory, (LogLevel)tpTask->mPriority, tpTask->mMaxfilesize, tpTask->mMaxbackupindex );
	}
	TASKLUA_LOG* tpLua = CSceneCfgManager::GetSingletonPtr()->GetTasklua_log();
	if( tpLua != NULL )
	{
		INIT_ROLLINGFILE_LOG( tpLua->mIdentifier, tpLua->mDirectory, (LogLevel)tpLua->mPriority, tpLua->mMaxfilesize, tpLua->mMaxbackupindex );
	}

	bool bRet = false;
	PERF_FUNC( "RegisterLua", bRet = RegisterLua() );

	if(!bRet)
	{
		LOG_ERROR( "TASK", "reg Lua module failed��please check Lua load log");	 
	}

	// ע�����lua�ļ��Ļص�����
	const char* pcDirPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data");
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcDirPath, ".lua", CTaskModule::LoadLuaFileCallback);
	
	pcDirPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/tasks");
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcDirPath, ".lua", CTaskModule::LoadLuaFileCallback);
}

// ��һ�쵽��
void CTaskModule::OnNewDayCome(  )
{	
	CSceneObjManagerImp* pSceneneObjManagerImp = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp;
	for( CSceneObjManagerImp::ObjMng_Task::iterator tTaskIt = pSceneneObjManagerImp->mTaskList.begin( ); 
		tTaskIt != pSceneneObjManagerImp->mTaskList.end( ); 
		++tTaskIt 
		)
	{
		// ����������
		CTaskList* pList = (CTaskList*) (&(*tTaskIt));
		if (OnTaskPlayerNewDayCome(pList, true)) // ֪ͨ�ͻ���
		{
			SendTaskMsg2Client( pList );
		}
	}

}

// ��һ�ܵ���
void CTaskModule::OnNewWeekCome(  )
{
	CSceneObjManagerImp* pSceneneObjManagerImp = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp;
	for( CSceneObjManagerImp::ObjMng_Task::iterator tTaskIt = pSceneneObjManagerImp->mTaskList.begin( ); 
		tTaskIt != pSceneneObjManagerImp->mTaskList.end( ); 
		++tTaskIt 
		)
	{
		// ����������
		CTaskList* pList = (CTaskList*) (&(*tTaskIt));
		pList->OnNewWeekCome();
	}
}


// ����lua�ڴ���亯��
//static void *lk_alloc_for_lua (void *ud, void *ptr, size_t osize, size_t nsize) {
//	(void)ud;
//	(void)osize;
//	if (nsize == 0) {
//		delete [] (char*)(ptr);
//		return NULL;
//	}
//	else
//	{
//		if( osize == 0 )
//		{
//			return ((void*)(debug_new char[nsize]));
//		}
//		else
//		{
//			if( nsize > osize )
//			{
//				void* nptr = ((void*)(debug_new char[nsize]));
//				memcpy( nptr, ptr, osize );
//				delete [] (char*)(ptr);
//				return nptr;
//			}
//			else
//			{
//				return ptr;
//			}
//		}
//	}
//}


bool CTaskModule::RegisterLua()
{
	if(L) lua_close(L); L = NULL;
	L = lua_open( );
	if (L == NULL)
	{
		printf("open LUA state failed");
		exit(0);
	}
	luaL_openlibs( L );

	// ������ ��ֹ������֮ǰ�����ݻ���
	CStorageTaskManager::m_Storage.clear();
	mTaskDropMgr.ClearDrop();

	// ע��CProperty
	// lua_tinker::class_add<CTaskLuaInterface>(L, "Task");
	lua_tinker::def(L, "PlayerHasItem",       &CTaskLuaInterface::HasItem);
	lua_tinker::def(L, "PlayerAwardMoney",    &CTaskLuaInterface::AwardBDMoney);
	lua_tinker::def(L, "AwardCommonMoney",    &CTaskLuaInterface::AwardCommonMoney);
	lua_tinker::def(L, "PlayerAwardExpr",     &CTaskLuaInterface::AwardExpr);

	//lua_tinker::def(L, "AwardExprInLoop",     &CTaskLuaInterface::AwardExprInLoop);
	//lua_tinker::def(L, "AwardMoneyInLoop",    &CTaskLuaInterface::AwardMoneyInLoop);

	lua_tinker::def(L, "PlayerAwardItem",			  &CTaskLuaInterface::AwardItem);
	lua_tinker::def(L, "PlayerAwardFreeItem",		  &CTaskLuaInterface::PlayerAwardFreeItem);
	lua_tinker::def(L, "PlayerRemoveItem",			  &CTaskLuaInterface::RemoveItem);
	lua_tinker::def(L, "AwardLevelEqt",				  &CTaskLuaInterface::AwardLevelEqt);
	lua_tinker::def(L, "PlayerAwardItemByMetier",     &CTaskLuaInterface::AwardItemByMetier);
	lua_tinker::def(L, "PlayerAwardTask",     &CTaskLuaInterface::AwardTask);
	lua_tinker::def(L, "PlayerAwardTeleport", &CTaskLuaInterface::AwardTeleport);
	lua_tinker::def(L, "AwardChangeMetier",   &CTaskLuaInterface::AwardChangeMetier);

	lua_tinker::def(L, "CheckCollectItem",	  &CTaskLuaInterface::CheckCollectItem);
	lua_tinker::def(L, "InitStaticStorageTask",	  &CTaskLuaInterface::InitStaticStorageTask);
	lua_tinker::def(L, "LoadTaskComplete",	  &CTaskLuaInterface::LoadTaskComplete);	
	lua_tinker::def(L, "RegDropTable",		  &CTaskLuaInterface::RegDropTable);
	lua_tinker::def(L, "RegLevelTask",		  &CTaskLuaInterface::RegLevelTask);
	lua_tinker::def(L, "CheckEvent",		  &CTaskLuaInterface::CheckEvent);
	lua_tinker::def(L, "ClearEvent",		  &CTaskLuaInterface::ClearEvent);
	
	lua_tinker::def(L, "IsSpaceOK",			&CTaskLuaInterface::IsSpaceOK);
	lua_tinker::def(L, "GetTaskState",      &CTaskLuaInterface::GetTaskState);
	lua_tinker::def(L, "SetTaskState",      &CTaskLuaInterface::SetTaskState);
	lua_tinker::def(L, "GetPlayer",			&CTaskLuaInterface::GetPlayer);
	//lua_tinker::def(L, "GetPlayerRegion",   &CTaskLuaInterface::GetPlayerRegion);
	lua_tinker::def(L, "GetTask",			&CTaskLuaInterface::GetTask);

	lua_tinker::def(L, "GetNextSubTaskID",				&CTaskLuaInterface::GetNextSubTaskID);
	lua_tinker::def(L, "GetCurSubTaskID",				&CTaskLuaInterface::GetCurSubTaskID);
	lua_tinker::def(L, "PlayerGetLoopTask",				&CTaskLuaInterface::PlayerGetLoopTask);
	lua_tinker::def(L, "GetLastLoopTaskID",				&CTaskLuaInterface::GetLastLoopTaskID);
	lua_tinker::def(L, "InsertLoopTask",				&CTaskLuaInterface::InsertLoopTask);
	lua_tinker::def(L, "GetTodayCompletedTimes",		&CTaskLuaInterface::GetTodayCompletedTimes);
	lua_tinker::def(L, "SetAbortLoopTaskData",			&CTaskLuaInterface::SetAbortLoopTaskData);
	lua_tinker::def(L, "GetCurSubTaskIndex",			&CTaskLuaInterface::GetCurSubTaskIndex);
	
	lua_tinker::def(L, "IsTaskEnd",						&CTaskLuaInterface::IsTaskEnd);
	
	lua_tinker::def(L, "Debug",							&CTaskLuaInterface::Debug);
	lua_tinker::def(L, "Error",							&CTaskLuaInterface::Error);
	lua_tinker::def(L, "CheckStorageTaskInList",		&CTaskLuaInterface::CheckStorageTaskInList);
	lua_tinker::def(L, "RemoveStorageTask",				&CTaskLuaInterface::RemoveStorageTask);

	lua_tinker::def(L, "AwardBuff",						&CTaskLuaInterface::AwardBuff);
	lua_tinker::def(L, "SetEvent",						&CTaskLuaInterface::SetEvent);
	lua_tinker::def(L, "IsTragedyTaskAcceptable",		&CTaskLuaInterface::IsTragedyTaskAcceptable);
	lua_tinker::def(L, "ChangeCurNpc2Ogre",				&CTaskLuaInterface::ChangeCurNpc2Ogre);
	lua_tinker::def(L, "CheckNpcOwner",					&CTaskLuaInterface::CheckNpcOwner);
	lua_tinker::def(L, "AwardBox",						&CTaskLuaInterface::AwardBox);
	lua_tinker::def(L, "DestroyNpc",					&CTaskLuaInterface::DestroyNpc);
	lua_tinker::def(L, "StartSendNpc",					&CTaskLuaInterface::StartSendNpc);
	lua_tinker::def(L, "CreateNpc",						&CTaskLuaInterface::CreateNpc);
	lua_tinker::def(L, "GetTodayTimesByGroupID",		&CTaskLuaInterface::GetTodayTimesByGroupID);
	lua_tinker::def(L, "GetWeekTimesByGroupID",			&CTaskLuaInterface::GetWeekTimesByGroupID);
	lua_tinker::def(L, "CommonCheck",					&CTaskLuaInterface::CommonCheck);
	lua_tinker::def(L, "CommonAward",					&CTaskLuaInterface::CommonAward);
	lua_tinker::def(L, "InviteFamilyMembers",			&CTaskLuaInterface::InviteFamilyMembers);
	lua_tinker::def(L, "GetFamilyAvgLevel",				&CTaskLuaInterface::GetFamilyAvgLevel);
	lua_tinker::def(L, "StartTimeLimitTaskTimer",		&CTaskLuaInterface::StartTimeLimitTaskTimer);
	lua_tinker::def(L, "CheckMutexByTask",				&CTaskLuaInterface::CheckMutexByTask);
	lua_tinker::def(L, "SetRedirectFailTask",			&CTaskLuaInterface::SetRedirectFailTask);
	lua_tinker::def(L, "RegMonitorNpc",					&CTaskLuaInterface::RegMonitorNpc);
	lua_tinker::def(L, "GetWatchNpcState",				&CTaskLuaInterface::GetWatchNpcState);
	lua_tinker::def(L, "SendSysMail",					&CTaskLuaInterface::SendSysMail);
	lua_tinker::def(L, "RegProtectFlagTask",			&CTaskLuaInterface::RegProtectFlagTask);
	lua_tinker::def(L, "CommonGetData",					&CTaskLuaInterface::CommonGetData);
	lua_tinker::def(L, "GetCurCampID",					&CTaskLuaInterface::GetCurCampID);
	lua_tinker::def(L, "GetTodayAcceptTimesByGroupID",	&CTaskLuaInterface::GetTodayAcceptTimesByGroupID);
	lua_tinker::def(L, "GetWeakCampLevel",				&CTaskLuaInterface::GetWeakCampLevel);
	lua_tinker::def(L, "PublishCheck",					&CTaskLuaInterface::PublishCheck);


	lua_tinker::class_add<CTask>(L, "CTask");
	lua_tinker::class_mem<CTask>(L, "mTaskID",			&CTask::mTaskID);
	lua_tinker::class_mem<CTask>(L, "mState",			&CTask::mTaskProgress);
	lua_tinker::class_def<CTask>(L, "SetTaskData",		&CTask::SetTaskData);
	lua_tinker::class_def<CTask>(L, "GetTaskData",      &CTask::GetTaskData);
	lua_tinker::class_def<CTask>(L, "RegEventTick",     &CTask::RegEventTick);

	lua_tinker::class_add<region>(L, "region");
	lua_tinker::class_mem<region>(L, "mMapID",   &region::mMapID);
	lua_tinker::class_mem<region>(L, "mX",       &region::mX);
	lua_tinker::class_mem<region>(L, "mY",       &region::mY);


	lua_tinker::class_add<CDir>(L, "CDir");
	lua_tinker::class_mem<CDir>(L, "bad",   &CDir::bad);
	lua_tinker::class_con<CDir>(L, lua_tinker::constructor<CDir, const char*>);
	lua_tinker::class_def<CDir>(L, "file", &CDir::file);

	// ����interface�ļ�
	/*lua_tinker::dofile(L, "../config/data/task_data/task_comm.lua");
	lua_tinker::dofile(L, "../config/data/task_data/awards.lua");	
	lua_tinker::dofile(L, "../config/data/task_data/country_build.lua");	
	lua_tinker::dofile(L, "../config/data/task_data/task_global.lua");
	lua_tinker::dofile(L, "../config/data/task_data/loop_awards.lua");
	lua_tinker::dofile(L, "../config/data/task_data/tragedy_tasks.lua");
	lua_tinker::dofile(L, "../config/data/task_data/task_func.lua");
	lua_tinker::dofile(L, "../config/data/task_data/task_interface.lua");
	lua_tinker::dofile(L, "../config/data/task_data/server_base_data.lua");
	lua_tinker::dofile(L, "../config/data/task_data/extra_awards.lua");*/
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/task_comm.lua"));
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/awards.lua"));	
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/country_build.lua"));	
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/task_global.lua"));
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/loop_awards.lua"));
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/tragedy_tasks.lua"));
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/task_func.lua"));
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/task_interface.lua"));
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/server_base_data.lua"));
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/extra_awards.lua"));
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/refresh_awards.lua"));
	lua_tinker::dofile(L, CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"task_data/task_refresh_func.lua"));
	

	//// �õ�NPC�������б��洢�������Ч��
	//mNpcTaskList

	// ���ó�ʼ���ӿ�
	if (! CTaskLuaInterface::Call<bool>(NULL, NULL, "init_tasks") )
	{
		printf("call init_tasks failed");
		exit(0);
	}
	return true;
}

//  ����������
void CTaskModule::OnLaunchServer( )
{
	OnLoadConfig();
}

//  �˳�������
void CTaskModule::OnExitServer( )
{
	if(L) lua_close(L); L = NULL;

	// ���std::map����������
	mTaskDropMgr.ClearDrop();
}

//  ������Timer
void CTaskModule::OnTimer( unsigned int vTickCount, unsigned int vTickOffset )
{
	mSendNpcMgr.OnTimer( vTickOffset );

	mRefreshStorageTaskTimer += vTickOffset;
	if ( mRefreshStorageTaskTimer >= (int)CSceneCfgManager::GetSingletonPtr()->GetTask_cfg()->mRefreshstoragetime*1000 )
	{
		mRefreshStorageTaskTimer = 0;
		CStorageTaskManager::RefreshStorageOnTime();
	}

}

//  ��������
int CTaskModule::OnCreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName )
{
	return SUCCESS;

}




// ���յ��������������������������·����Ϣ ������ 
void CTaskModule::OnTaskInvitedRoutMsg( const char* szSrcName, const char* szDesName , unsigned short unTaskID )
{
	CEntityPlayer* pDesPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton( ).GetPlayerByName(szDesName);
	LK_ASSERT( pDesPlayer != NULL, return );

	SendInviteTaskMsg( szSrcName, pDesPlayer, unTaskID ) ;
}



// ������Ҷ���������Ļ�Ӧ
void CTaskModule::OnPlayerReplyTaskInvite( CEntityPlayer* pPlayer, const char* szRequesterName, unsigned short usTaskID, unsigned short usAgreeCode )
{
	LK_ASSERT( pPlayer != NULL, return );
	if ( !mTaskInviteInfMgr.ChkReg( pPlayer->GetEntityID(), szRequesterName , usTaskID ))
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_INVITE_TIMEOUT );
		return;
	}

	CMessagePlayerInviteTaskResponseNotice msg; // �������������
	CMessage tMessage;
	msg.set_srcplayername( pPlayer->GetCharName() );
	msg.set_taskid( usTaskID );
	msg.set_agreeflag( usAgreeCode );

	msg.mutable_router()->set_srcname( pPlayer->GetCharName() );
	msg.mutable_router()->set_desname( szRequesterName );
	msg.mutable_router()->set_send2player( 0 );
	msg.mutable_router()->set_routertype( CMessageRouter::ROUTER_NAME );
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid( ID_S2C_INVITE_TASK_RESPONSE_NOTICE );

	CSceneLogic::GetSingleton( ).Send2Player( szRequesterName, &tMessage );

	if ( usAgreeCode == 1 ) // �����ͬ���ˣ� �߽������߼�
	{
		// �Ȼ����������ʵ��ID
		int nRequesterID = 0;
		CEntityPlayer* tpSrcPlayer = CSceneLogic::GetSingleton().GetPlayerByName( szRequesterName );
		if ( tpSrcPlayer != NULL )
			nRequesterID = tpSrcPlayer->GetEntityID();
		if (!PlayerObtainTask( pPlayer, usTaskID, true, 0, nRequesterID ) ) // �������ͬһ������ ��������ID��0
		{
			Send2ClientOprFailed(pPlayer);
		}else
		{
			LogEventPlayerAcceptTask(pPlayer, usTaskID);
		}
	}
}


// �������ܣ����͸����������� ����������Ϣ ͬʱ��¼��������(�ڱ������˵ķ�����)
int CTaskModule::SendInviteTaskMsg( const char* pSrcPlayerName, CEntityPlayer* pDesPlayer, unsigned short unTaskID, int nInvitingPlayerID /*= -1*/ )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pDesPlayer->GetTaskToken( ));
	LK_ASSERT( pList, return 0 );

	int task_state = pList->GetTaskState( unTaskID );

	if ( task_state == TASK_BEGIN || task_state == TASK_FAILED || task_state == TASK_TOEND )
	{
		// ����  �Է����������������  ���ͻ��˷���Ϣ
		CMessagePlayerInviteTaskErrorMsg msg; 

		CMessage tMessage;

		msg.set_taskid( unTaskID );
		msg.set_myname( pDesPlayer->GetCharName() );
		msg.set_typeid_( ERROR_GOT );

		msg.mutable_router()->set_srcname( pDesPlayer->GetCharName() );
		msg.mutable_router()->set_desname( pSrcPlayerName );
		msg.mutable_router()->set_send2player( 1 ); // �����ͻ��ˣ�(������)
		msg.mutable_router()->set_routertype( CMessageRouter::ROUTER_NAME );

		tMessage.set_msgpara((uint32_t) &msg);

		tMessage.mutable_msghead()->set_messageid( ID_S2C_PLAYER_INVITE_TASK_ERROR_MSG );

		CSceneLogic::GetSingleton( ).Send2Player( pSrcPlayerName, &tMessage );
		return -1;
	}
	else if( task_state == TASK_COMPLETE || task_state == TASK_END )
	{
		// ����  �Է��Ѿ�����������  ���ͻ��˷���Ϣ
		CMessagePlayerInviteTaskErrorMsg msg; 

		CMessage tMessage;

		msg.set_taskid( unTaskID );
		msg.set_myname( pDesPlayer->GetCharName() );
		msg.set_typeid_( ERROR_COMPLETED );

		msg.mutable_router()->set_srcname( pDesPlayer->GetCharName() );
		msg.mutable_router()->set_desname( pSrcPlayerName );
		msg.mutable_router()->set_send2player( 1 ); // �����ͻ��ˣ�(������)
		msg.mutable_router()->set_routertype( CMessageRouter::ROUTER_NAME );

		tMessage.set_msgpara((uint32_t) &msg);

		tMessage.mutable_msghead()->set_messageid( ID_S2C_PLAYER_INVITE_TASK_ERROR_MSG );

		CSceneLogic::GetSingleton( ).Send2Player( pSrcPlayerName, &tMessage );
		return -1;
	}
	pList->SetInvitingPlayerID( nInvitingPlayerID );
	bool bRet = IsTaskAcceptable( pDesPlayer, pList, unTaskID ) ; 
	pList->SetInvitingPlayerID( -1 );
	if ( bRet )// ����ܽ��������
	{
		// �жϰ�����û��
		// ȡ��������Ҫ���ŵĵ���, ��ΪTestBaggageSpace�Ľӿ�����
		CItemsPair tExtendItems;
		PERF_FUNC( "GetTaskExtendItems" , GetTaskExtendItems( pDesPlayer, unTaskID, tExtendItems) );

		//  ���ռ��Ƿ����㣬�����������ô�����ܽӣ�ͬʱ�ͻ���Ҳ����ر�����Ի�����
		if (tExtendItems.size() > 0 )
		{
			const int BAGGAGESPACE = 4;
			int tExtendItemID[BAGGAGESPACE] = {0};
			int tExtendItemNumber[BAGGAGESPACE] = {0}; 
			CItemsPair::iterator iter = tExtendItems.begin();
			for(int i = 0; iter != tExtendItems.end(); ++iter,++i)
			{
				tExtendItemID[i] = iter->first;
				tExtendItemNumber[i] = iter->second;
			}
			CPropertyPlayer* pDesProperty = (CPropertyPlayer*)pDesPlayer->GetProperty();
			if ( pDesProperty->TestBaggageSpace( tExtendItemID, tExtendItemNumber, BAGGAGESPACE ) == false )
			{
				CMessagePlayerInviteTaskErrorMsg msg; 
				CMessage tMessage;
				msg.set_taskid( unTaskID );
				msg.set_myname( pDesPlayer->GetCharName() );
				msg.set_typeid_( ERROR_CANT_ACCEPT );
				msg.mutable_router()->set_srcname( pDesPlayer->GetCharName() );
				msg.mutable_router()->set_desname( pSrcPlayerName );
				msg.mutable_router()->set_send2player( 1 ); // �����ͻ��ˣ�(������)
				msg.mutable_router()->set_routertype( CMessageRouter::ROUTER_NAME );
				tMessage.set_msgpara((uint32_t) &msg);
				tMessage.mutable_msghead()->set_messageid( ID_S2C_PLAYER_INVITE_TASK_ERROR_MSG );
				CSceneLogic::GetSingleton( ).Send2Player( pSrcPlayerName, &tMessage );
				return -1;
			}
		}

		int ret = mTaskInviteInfMgr.RegInvite( pDesPlayer->GetEntityID(), pSrcPlayerName , unTaskID );
		if ( 0 == ret )
		{
			// �Ǽ���Ϣ�ɹ�
			// �����Է�
			CMessagePlayerInviteTaskNotice msg;

			CMessage tMessage;

			msg.set_taskid( unTaskID );
			msg.set_srcplayername( pSrcPlayerName );

			tMessage.set_msgpara((uint32_t) &msg);

			tMessage.mutable_msghead()->set_messageid( ID_S2C_INVITE_TASK_NOTICE );

			CSceneLogic::GetSingleton( ).Send2Player( pDesPlayer, &tMessage );

			return 0;
		}
		else if ( -1 == ret )
		{
			return -1;
		}
		else if ( -2 == ret )
		{
			return -1;
		}

	}
	else
	{
		// ����  �Է����ܽ� ���ͻ��˷���Ϣ
		CMessagePlayerInviteTaskErrorMsg msg; 

		CMessage tMessage;

		msg.set_taskid( unTaskID );
		msg.set_myname( pDesPlayer->GetCharName() );
		msg.set_typeid_( ERROR_CANT_ACCEPT );

		msg.mutable_router()->set_srcname( pDesPlayer->GetCharName() );
		msg.mutable_router()->set_desname( pSrcPlayerName );
		msg.mutable_router()->set_send2player( 1 ); // �����ͻ��ˣ�(������)
		msg.mutable_router()->set_routertype( CMessageRouter::ROUTER_NAME );

		tMessage.set_msgpara((uint32_t) &msg);

		tMessage.mutable_msghead()->set_messageid( ID_S2C_PLAYER_INVITE_TASK_ERROR_MSG );

		CSceneLogic::GetSingleton( ).Send2Player( pSrcPlayerName, &tMessage );
	}
	return 0;
}

// �������� Ч�ʰ�������
int  CTaskModule::OnPlayerSearchTask(CEntityPlayer* pPlayer )
{
	CMessagePlayerSearchResponse msg;

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken());
	LK_ASSERT( pList, return 0 );

	const int nCurLevel = pPlayer->GetLevel();
	LK_ASSERT ( nCurLevel > 0 && nCurLevel <= MAX_GRADE , return -1 );

	int nStartLevel = std::max(1, nCurLevel-(int)CSceneCfgManager::GetSingletonPtr()->GetTask_cfg()->mSearchmaindownlevel);
	int nEndLevel   = std::min(MAX_GRADE, nCurLevel+(int)CSceneCfgManager::GetSingletonPtr()->GetTask_cfg()->mSearchmainuplevel);
	// ������������
	for (int i = nStartLevel; i <= nEndLevel ; ++i)
	{
		for( int j = 0; j < mLevelTasksN[0][i]; ++j  )
		{
			if ( pList->GetTaskState(mLevelTasks[0][i][j]) == -1 )
			{
				bool bRet = false;
				PERF_FUNC("IsTaskAcceptable", bRet = IsTaskAcceptableExpress( pPlayer, pList, mLevelTasks[0][i][j]) );

				if (bRet )
				{
					//CTask tTask;
					//tTask.mTaskID = mLevelTasks[0][i][j];
					msg.add_taskids(mLevelTasks[0][i][j]);
				}
			}
		}
	}

	nStartLevel = std::max(1, nCurLevel-(int)CSceneCfgManager::GetSingletonPtr()->GetTask_cfg()->mSearchxydownlevel);
	nEndLevel   = std::min(MAX_GRADE, nCurLevel+(int)CSceneCfgManager::GetSingletonPtr()->GetTask_cfg()->mSearchxyuplevel);

	// ������������
	for (int i = nStartLevel; i <= nEndLevel ; ++i)
	{
		for( int j = 0; j < mLevelTasksN[2][i]; ++j  )
		{
			if ( pList->GetTaskState(mLevelTasks[2][i][j]) == -1 )
			{
				bool bRet = false;
				PERF_FUNC("IsTaskAcceptable", bRet = IsTaskAcceptableExpress( pPlayer, pList, mLevelTasks[2][i][j]) );
				if (bRet)
				{
					//CTask tTask;
					//tTask.mTaskID = mLevelTasks[2][i][j];
					msg.add_taskids(mLevelTasks[2][i][j]);
				}
			}
		}
	}

	nStartLevel = std::max(1, nCurLevel-(int)CSceneCfgManager::GetSingletonPtr()->GetTask_cfg()->mSearchzhidownlevel);
	nEndLevel   = std::min(MAX_GRADE, nCurLevel+(int)CSceneCfgManager::GetSingletonPtr()->GetTask_cfg()->mSearchzhiuplevel);

	// ����֧������
	for (int i = nStartLevel; i <= nEndLevel ; ++i)
	{
		for( int j = 0; j < mLevelTasksN[1][i]; ++j  )
		{
			if ( pList->GetTaskState(mLevelTasks[1][i][j]) == -1 )
			{
				bool bRet = false;
				PERF_FUNC("IsTaskAcceptable", bRet = IsTaskAcceptableExpress( pPlayer, pList, mLevelTasks[1][i][j]) );
				if (bRet)
				{
					//CTask tTask;
					//tTask.mTaskID = mLevelTasks[1][i][j];
					msg.add_taskids(mLevelTasks[1][i][j]);
				}
			}
		}
	}

	CMessage   tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_TASK_SEARCH);
	//printf("-----������%d������ID---", msg.taskids_size());
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
	return 0;

}

// ���յ���ҽ����������ʱ��
int  CTaskModule::OnPlayerObtainTask(CEntityPlayer* pPlayer, unsigned short unTaskID, int nNpcEntityID )
{
	//  �������ȷ�ػ��������ô���ܹرնԻ�
	LK_ASSERT( pPlayer, return -1 );
	CEntityNpc* tpEntityNpc = dynamic_cast<CEntityNpc*>(CSceneObjManager::GetSingletonPtr()->GetObject( nNpcEntityID ) );
	if ( tpEntityNpc == NULL && nNpcEntityID != 0 )
		return -1;

	// ֻ���ڹ��ں������������������ (������ڹ��� ���Ҳ��������� �Ͳ��ý�����)
	//if (pPlayer->IsOverseas() && !(IS_NEUTRAL_LINE_ID(pPlayer->GetLineID()) ) )
	//	return -1;

	// ֻ���Ѻò��ܽ�����
	if ( tpEntityNpc != NULL )
	{
		if( !( tpEntityNpc->IsFunNpc() && tpEntityNpc->IsFriendlyTo(pPlayer) ) )
		{
			return -1;
		}
	}

	// ���NPC�Ѿ��Ǳ�ֻ��߻�����״̬ �����������
	if ( tpEntityNpc != NULL )
	{
		if ( tpEntityNpc->GetNpcChangeState() != 0 || tpEntityNpc->GetSendNpcState() != 0  )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_NPC_BUSY );
			Send2ClientOprFailed( pPlayer );
			return -1;
		}
	}

	bool bRet = false;
	PERF_FUNC("PlayerObtainTask", bRet = PlayerObtainTask( pPlayer, unTaskID, false, nNpcEntityID ));
	if (!bRet)
	{
		Send2ClientOprFailed(pPlayer);
	}else
	{
		LogEventPlayerAcceptTask(pPlayer, unTaskID);
	}
	return 0;
}


// ���յ���ҽ����������ʱ��
int  CTaskModule::OnPlayerEndTask(CEntityPlayer* pPlayer, unsigned short unTaskID, unsigned short unSelect, int nBagIndex )
{
	//  �������ȷ�ص��ύ������ô���ܹرնԻ�
	LK_ASSERT( pPlayer, return -1 );
	// ֻ���ڹ��ں����������������� (������ڹ��� ���Ҳ��������� �Ͳ��ý�����)
	//if (pPlayer->IsOverseas() && !(IS_NEUTRAL_LINE_ID(pPlayer->GetLineID()) ) )
	//	return -1;

	bool bRet = false;
	CPropertyPlayer* pPro = (CPropertyPlayer*)pPlayer->GetProperty();
	LK_ASSERT( pPro, return false);

	//int nBagIndex = pPro->GetBaggage()->GetTaskLockIndex();
	PERF_FUNC( "PlayerEndTask", bRet = PlayerEndTask( pPlayer, unTaskID,  unSelect, false, nBagIndex ) );
	if (!bRet)
	{
		Send2ClientOprFailed(pPlayer);
	}else
	{
		LogEventPlayerEndTask(pPlayer, unTaskID);
	}
	return 0;
}

int CTaskModule::OnPlayerRefreshTask(CEntityPlayer* pPlayer, unsigned short unTaskID, int mRefreshItemIndex, int nNpcEntityID )
{
	LK_ASSERT( pPlayer, return -1 );
	bool bRet = false;
	bRet = PlayerRefreshTaskAward(pPlayer, unTaskID, mRefreshItemIndex, nNpcEntityID );
	if (!bRet)
	{
		return -1;
	}
	else
	{
		LogEventPlayerRefreshTask(pPlayer, unTaskID);
	}
	return 0;
}
// �õ������ͻ��˵�NPC�����б����Ϣ
bool CTaskModule::GetNpcTaskList( CEntityPlayer* pPlayer, CTaskList* pList2, int vNpcID, NpcTaskList* pList)
{
	if (vNpcID != 0)
	{
		// ȡ�÷��������б�
		lua_tinker::table t1 = CTaskLuaInterface::Call<lua_tinker::table, int>(pPlayer, pList2, "get_npc_extend_tasks", vNpcID);
		int n = luaL_getn(L, -1);

		if (n >= MAX_NPC_TASK_NUM)
		{
			LOG_ERROR("TASK", " max NPC Task num is 64!!" );
			n = 63;
		}
		pList->set_extendnumber(n);
		for(int i =1; i<=n; ++i)
		{
			lua_rawgeti(L, -1, i);
			pList->add_extendtaskid(lua_tinker::pop<int>(L)) ;
		}

		// ȡ�û��������б�
		lua_tinker::table t2 = CTaskLuaInterface::Call<lua_tinker::table, int>(pPlayer, pList2, "get_npc_back_tasks", vNpcID);
		int m = luaL_getn(L, -1);
		pList->set_callbacknumber(m);
		for(int i =1; i<=m; ++i)
		{
			lua_rawgeti(L, -1, i);
			pList->add_callbacktaskid(lua_tinker::pop<int>(L)) ;
		}
		
		pList->set_npcid(vNpcID) ;

		return true;
	}

	return false;
}



//  ����ʵ��
void CTaskModule::OnCreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst )
{
	if ( pEntity->IsPlayer() )
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*) pEntity;
		LK_ASSERT( tpPlayer != NULL , return );

		CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(tpPlayer->GetTaskToken( ));
		if (pList != NULL)
		{			
			pList->SetOwnerEntityID(tpPlayer->GetEntityID());
			// ����ÿ������
			DaylyDispos(tpPlayer);

			// ����ÿ������
			WeeklyDispos(tpPlayer);

			// ��ʱ����δ���� ������ʱ��
			CPropertyPlayer*  pProperty= ( CPropertyPlayer* ) tpPlayer->GetProperty();
			bool bIsNewDay = IsANewDay((time_t)pProperty->GetLastDaylyDisposTime(), time(0));
			std::vector<unsigned short> _fail_list;	// ʧ�ܵ������б�
			for ( int i = 0 ; i < pList->mTaskNumber && i < TASK_LIST_SIZE; ++i )
			{
				// �ѳ�ʼ���¼��ŵ����� ��Ϊ����϶�ȫ������������� �������� 
				// ��������л��������
				CTaskModule::GetSingleton().RegTaskEventTick( &(pList->mTaskList[i]) );

				if ( pList->mTaskList[i].mGameTimeLeft > 0 )	// ��ʱ���� ��û��ʱ��(ʣ������)
				{
					int nLeftTime = 0;
					// ��鿴��������ʱ�仹����Ϸʱ��
					int tLmtType = GetTimeLmtType( pList->mTaskList[i].mTaskID );
					if ( tLmtType == TIMETYPE_GAME )
					{
						nLeftTime = pList->mTaskList[i].mGameTimeLeft;
					}
					else if ( tLmtType == TIMETYPE_PHYSICAL ) // ����ʱ��
					{
						nLeftTime = pList->mTaskList[i].mGameTimeLeft - (int)(time(0)-pList->mLastLogOffTime); // �۳�������ߵ�ʱ��
						if ( nLeftTime <= 0 ) // ����ʧ����!����ʱ���ѳ�ʱ
						{
							_fail_list.push_back(pList->mTaskList[i].mTaskID);
							pList->mTaskList[i].mGameTimeLeft = -1;
						}
						else
						{
							pList->mTaskList[i].mGameTimeLeft = nLeftTime;
						}
					}
					else
					{
						LOG_ERROR("TASK", "task %d time lmt:%d ?", pList->mTaskList[i].mTaskID, tLmtType);
					}

					if ( nLeftTime > 0 )	// ������ʱ��
					{
						int nTimerOtherInfo[ TIMER_OTHER_INFO ] = { MESSAGE_PROPERTY, pList->mTaskList[i].mTaskID, 0, 0};
						pList->mTaskList[i].mTimerID = tpPlayer->GetTimerReciver()->SetTimer( tpPlayer->GetEntityID()
							, TIMER_TASKTIMELIMIT, pList->mTaskList[i].mGameTimeLeft*1000, 2, nTimerOtherInfo );
					}
				}
				else if ( pList->mTaskList[i].mGameTimeLeft == 0 )
				{
					LOG_WARN("TASK", "task %d left time = 0? so qiao??", pList->mTaskList[i].mTaskID );
				}

				if ( bIsNewDay && IsDailyFail(pList->mTaskList[i].mTaskID) ) // ��һ�� ���ü���ǲ��� ��ʧ��
				{
					_fail_list.push_back(pList->mTaskList[i].mTaskID);
				}
			}

			std::vector<unsigned short> tumb;
			for( int i = 0; i < pList->mTaskNumber; ++i )
			{
				if ( !CTaskLuaInterface::Call<bool, unsigned short, const char*>( tpPlayer, pList, "check_task", pList->mTaskList[i].mTaskID, "onCreateEntity" ) )
				{
					tumb.push_back( pList->mTaskList[i].mTaskID );
					continue;
				}
			}

			// �ɵ�
			for ( std::vector<unsigned short>::iterator it = tumb.begin(); it != tumb.end(); ++it )
			{
				pList->RemoveTask( *it );
			}

			// ����Ϣ
			SendTaskMsg2Client( pList );

			// ������ʧ�� ��Ϊʧ�ܿ���ɾ�� ���Բ�����ѭ���е���
			// Ӧ�õȸ��ͻ��˷����б��ٴ���
			for ( std::vector<unsigned short>::iterator it = _fail_list.begin(); it != _fail_list.end(); ++it )
			{
				OnTaskFailed( tpPlayer, *it );
			}

			// ��ʱ����
			TempDispos( tpPlayer, pList );

			for (int i = 0; i < TASK_LIST_SIZE; ++i)
			{
				unsigned short taskID = pList->mRememberRefreshNum[i].rTaskID;
				int taskColor = pList->mRememberRefreshNum[i].rTaskColor;
				Send2ClientRefreshResult( tpPlayer, taskID, taskColor, i );
			}
		}
		else // ���֣�
		{
			//SetDefaultTask(tpPlayer);
		}
	}
	else if ( pEntity->IsFunNpc() || pEntity->IsOgre() )
	{
		CEntityNpc* tpNpc = (CEntityNpc*)pEntity;
		if ( -2 == mNpcMonitor.OnNpcCreated( (int)tpNpc->GetNpcID(), tpNpc->GetEntityID() ) )
		{
			LOG_ERROR("TASK", "npc tempid=%d  re reged!", tpNpc->GetNpcID() );
		}
	}
}

//  ����ʵ��
void CTaskModule::OnDestroyEntity( CEntity* pEntity, int vCode )
{
	if ( pEntity->IsPlayer() )
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*) pEntity;
		CSceneObjManager::GetSingletonPtr()->DestroyObject( tpPlayer->GetTaskToken( ) );
	}
	else if ( pEntity->IsFunNpc() )
	{
		CEntityNpc* tpNpc = (CEntityNpc*)pEntity;
		mNpcMonitor.OnNpcDestroyed( (int)tpNpc->GetNpcID() ) ;
	}
}

//  �洢����
bool CTaskModule::OnSaveData( CEntityPlayer* pPlayer , int vSaveCode )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList, return false);

	// ������(ֻҪ���Ƕ�ʱ��  ����Ϊ����)
	if (vSaveCode != SAVE_TIMETRIGER)
	{
		if ( pList->GetSendNpcEntityID() != INVALID_OBJ_ID )
			mSendNpcMgr.ClearPlayerSendSession( pPlayer, true ); // ������
		if (pList->GetBossNpcEntityID() != 0)
		{
			// �ָ���BOSS��״̬
			CEntityNpc* pNpc = (CEntityNpc*)CSceneLogic::GetSingleton().GetEntity( pList->GetBossNpcEntityID() );
			if (pNpc == NULL)
			{
				LOG_ERROR("TASK", "battling NPC disappeared? ID=%d", pList->GetBossNpcEntityID() );
			}
			else
			{
				OnNpcRecoverdState( pPlayer->GetCharID(), pNpc->GetTaskID(), pNpc->GetNpcID() );
			}
		}

		// ������ϵ����� ��û�����߾�ʧ�ܵ� (���Ҳ��)
		// �����û����ʱ����Ҫ����ʣ��ʱ���
		std::vector<unsigned short> _fail_list;	// ʧ�ܵ������б�
		for ( int i = 0; i < std::min( pList->mTaskNumber, (unsigned short)TASK_LIST_SIZE ); ++i )
		{
			if ( (pList->GetTaskState(pList->mTaskList[i].mTaskID) == TASK_BEGIN) 
				&& (IsOffFail(pList->mTaskList[i].mTaskID) == 1) )
			{
				_fail_list.push_back(pList->mTaskList[i].mTaskID);
				continue;
			}

			if ( (pList->mTaskList[i].mExFlags&EXFLAG_PROTECT_FLAG_TASK) == EXFLAG_PROTECT_FLAG_TASK ) // �������� ȡ��ע��
			{
				mNpcMonitor.RemoveGlobalTaskAction( pList->mTaskList[i].GetFirstParamByEvent(EVENT_PROTECT_FLAG)
					, pPlayer, pList->mTaskList[i].mTaskID );
				if ( pList->mTaskList[i].mTaskProgress == TASK_BEGIN )
					_fail_list.push_back(pList->mTaskList[i].mTaskID);
				continue;
			}

			// �������ʧ�� �Ͳ��ô���timer�� ��Ϊʧ�������ɵ�timer��
			if ( pList->mTaskList[i].mTimerID != INVALID_OBJ_ID )  // ��ʱ����δ����
			{
				CTimerItem* tpTimer = CTimerMng::GetSingleton().GetTimer(pList->mTaskList[i].mTimerID);
				if ( tpTimer == NULL )
				{
					LOG_ERROR("TASK", "task%d can't find timer? timerid=%d", pList->mTaskList[i].mTaskID, pList->mTaskList[i].mTimerID );
				}
				else
				{
					// ����ʣ��ʱ��(����)
					pList->mTaskList[i].mGameTimeLeft = tpTimer->mMillSeconds/1000;

					// �ɵ���ʱ��
					int tRet = pPlayer->GetTimerReciver()->ClearTimer( pList->mTaskList[i].mTimerID );
					if ( tRet != 0 )
						LOG_ERROR("TASK", "OnSaveData del1 timer returned %d, timerid=%d taskid=%d"
						, tRet, pList->mTaskList[i].mTimerID, pList->mTaskList[i].mTaskID );
					 pList->mTaskList[i].mTimerID = INVALID_OBJ_ID;
				}
			}
		}

		for ( std::vector<unsigned short>::iterator it = _fail_list.begin(); it != _fail_list.end(); ++it )
		{
			OnTaskFailed( pPlayer, *it );
		}

		// ����ǲ������ٻ�������NPC �о͸ɵ�
		if ( pPlayer->GetCallNpcEntityID() != INVALID_OBJ_ID )
		{
			//CEntity* tpNpc = CSceneLogic::GetSingleton().GetEntity(pPlayer->GetCallNpcEntityID());
			//CSceneLogic::GetSingleton().DestroyEntity( tpNpc, 0 );
			// ���ӳ�ɾ���б�
			CSceneLogic::GetSingleton().AddDeleteList( pPlayer->GetCallNpcEntityID() );
		}
	}	

	char tBuffer[ PLAYER_DATALEN ] = { 0 }; 
	int  tBufferSize = sizeof(tBuffer);

	PBTaskList tPBTask;

	pList->GetTlvBuffer2( &tPBTask );
	if (vSaveCode != SAVE_TIMETRIGER)
	{
		tPBTask.set_lastlogoff(time(0));
	}
	tPBTask.SerializePartialToArray( tBuffer, tBufferSize );

	//pPlayer->mBuffer.PushBuffer( sModuleName, tBuffer, tPBTask.ByteSize() );

	char tEscapStr[ PLAYER_DATALEN ] = {0};
	char* tPointer = tEscapStr;

	int tRealLen = EscapeDataString( &tPointer, sizeof(tEscapStr)-1, tBuffer, tPBTask.ByteSize() );

	LK_ASSERT( tRealLen != -1 && "while escape_data_string, dst buff overflow" , return false);

	int tIsCallBack = SQL_NEED_CALLBACK;
	if ( vSaveCode == SAVE_TIMETRIGER )
		tIsCallBack = SQL_NONE;

	CMessagePlayerProperty* tpSave = CSceneLogic::GetSingletonPtr( )->GetSavePlayerProperty( );
	
	tpSave->mutable_role_task( )->CopyFrom( tPBTask );
	return true;

//	return CSceneLogic::GetSingletonPtr()->ExecuteSql( saveplayer_task, vSaveCode, pPlayer->get_id(), pPlayer->GetCharID(), tIsCallBack, 
//		UPDATE, "update UMS_ROLE_DETAIL_%02d set role_task = '%s', save_bitflag = save_bitflag + '%d' where role_id = %d",
//		pPlayer->GetAccountID()%16, tEscapStr, LSSTATE_TASK,  pPlayer->GetCharID() );

}


void CTaskModule::OnEntityDie( CEntity* pOwnerEntity, CEntity* pDesEntity )
{
	LK_ASSERT( pOwnerEntity != NULL && pDesEntity != NULL , return );

	if ( pOwnerEntity->IsPet() ) // �ǳ��������
	{
		CEntityPet* tpPet = (CEntityPet*)pOwnerEntity;
		pOwnerEntity = tpPet->GetOwner();
		LK_ASSERT( pOwnerEntity!=NULL, return );
	}

	if( !pOwnerEntity->IsPlayer() ||  ( !pDesEntity->IsOgre() && !pDesEntity->IsFunNpc() && !pDesEntity->IsBlock() ) )
		return;

	CEntityNpc* tpEntityNpc = (CEntityNpc*)pDesEntity;
	mNpcMonitor.OnNpcDied( tpEntityNpc->GetNpcID() );

	if (pDesEntity->IsFunNpc()) // �����NPC ��������ٻ����������Ǹ���
	{
		// ��NPC״̬Ū��ȥ
		// ��״̬�Ļ�ȥ ����PK״̬��������������ܻ�ȥ֮ǰ������
		tpEntityNpc->SetTaskID( 0 );// ���� changestate�Ȳ��� ���ܻ�ȥ�ٸ�
		if (tpEntityNpc->GetOwnercharID() != 0)
		{
			pOwnerEntity = CSceneLogic::GetSingleton().GetPlayerByCharID(tpEntityNpc->GetOwnercharID());
			if (pOwnerEntity == NULL) // �����Ѿ������� ��NPC�Ͱ�����
			{
				tpEntityNpc->SetOwnerCharID(0);
				return;
			}
		}
		tpEntityNpc->SetOwnerCharID(0);
	}

	CPropertyCharacter* pDesProperty = (CPropertyCharacter*)pDesEntity->GetProperty();


	LOG_DEBUG("TASK", "ogre died��ID=%d", pDesProperty->GetPropertyTempID( ) );
	//  step1: �õ�Դ��������Ϣ and ׼������
	CEntityPlayer* pTeamMates[TEAM_NUMBER] = {NULL};
	int tRtn = 0, tTeamNum = 0;
	tRtn = CTeamModule::GetSingleton().OnGetMemberList( (CEntityPlayer*)pOwnerEntity, pTeamMates, ARRAY_CNT( pTeamMates ), tTeamNum );
	if ( tRtn < 0 )
	{
		LOG_ERROR( "team", "task, get team list failed.id=%d, [%s:%d]", pOwnerEntity->GetEntityID(), __LK_FILE__, __LINE__);
		return ;
	}

	CItemsPair tSpecialTaskItem; // �п�����Ҫ�ַ��������������
	std::map< unsigned short, unsigned short >  tmpUpList[TEAM_NUMBER]; // ��Ҫ����������������ʵ��ID������ID�б�
	CMessageUpdateTaskConditions update[TEAM_NUMBER]; // ������Ϣ

	// step2: ������Ա���ϵ�����
	if ( tTeamNum == 0 )
	{
		LOG_ERROR("TASK", "error in get team member num" );
		return;
	}

	//printf("1--%d\n", a.elapsed() );
	//a.start();

	int  nIndex = -1;
	int  n = 0 ;

	while( ++n <= tTeamNum )
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*)pOwnerEntity;
		// ������
		if (tTeamNum > 1)
		{
			tpPlayer = CTeamModule::GetSingleton().GetTurnOwnerOnTask( pTeamMates[0] );
			if ( tpPlayer == NULL )
				continue;

			//CWTPoint pt01 = CWTPoint( tpPlayer->GetPosX(), tpPlayer->GetPosY() );
			//CWTPoint pt02 = CWTPoint( pOwnerEntity->GetPosX(), pOwnerEntity->GetPosY() );
			if ( tpPlayer->IsWithinDistance( pDesEntity, TEAM_VALID_DISTANCE ) == false )
			{ 
				continue; // ��������
			}

			for( int i = 0 ; i < tTeamNum; ++i )
			{
				LK_ASSERT(pTeamMates[i], continue);
				if ( tpPlayer->GetEntityID() == pTeamMates[i]->GetEntityID() )
				{
					nIndex = i;
					break;
				}
			}

			if ( nIndex == -1 ) // ������
				continue;
		}
		else
		{
			// ���Լ�
			nIndex = 0;
		}

		//printf("2.1--%d\n", a.elapsed() );
		//a.start();

		// �õ�������������ϵ����񣬵�����Ʒ

		OnTaskDropItems( tpPlayer, pDesProperty, tSpecialTaskItem, tmpUpList[nIndex], &update[nIndex] );

		//printf("2.2--%d\n", a.elapsed() );
		//a.start();
	}

	// step2��ɣ��õ�����ͨ��ƷӦ�ö�������
	for( int i = 0; i < tTeamNum && i < (int)ARRAY_CNT(pTeamMates); ++i)
	{
		if ( pTeamMates[i] == NULL )
		{
			LOG_ERROR("TASK","team BUG !! NULL pointor ! LINE=%d", __LINE__ );
			continue;
		}
		CPropertyPlayer*  pProperty= ( CPropertyPlayer* ) pTeamMates[i]->GetProperty();
		if ( NULL == pProperty ) 
		{
			LOG_ERROR("TASK", "error, NULL pointer,file=%s, FUNC=%s, line = %d", __FILE__, __FUNCTION__, __LINE__);
			continue;
		}

		OnTaskOgreDie( pOwnerEntity, pTeamMates[i], pDesProperty, tSpecialTaskItem, tmpUpList[i], &update[i] ) ;

		// ˳�������

		CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pTeamMates[i]->GetTaskToken( ));
		LK_ASSERT( pList, continue );

		// ���ͻ��˷�������Ϣ
		SendUpdateConditions2Client( pTeamMates[i], &update[i] );

		for ( std::map<unsigned short, unsigned short>::iterator it = tmpUpList[i].begin(); it != tmpUpList[i].end(); ++it)
		{
			// �����⼸��û��Ҫ
			CTask* pTask = pList->GetTask( it->first );
			LK_ASSERT( pTask, continue );
#ifdef _DEBUG_
			if ( pTask->mWatchEventN > 0 ) // ��û���, ֻ֪ͨ�ͻ���ˢ������
			{
				LOG_ERROR("TASK", "err ! entitydie update watch > 0 !");
				continue;
			}
#endif
			bool bAutoEnd = false;
			PERF_FUNC("UpdateTaskProgress", UpdateTaskProgress( pTeamMates[i], pTask, bAutoEnd, 1 ) );
			if ( bAutoEnd ) // �������Ҫ�Զ����
			{
				PERF_FUNC( "PlayerEndTask", PlayerEndTask( pTeamMates[i], it->first, -100, true ) );
				LogEventPlayerEndTask( pTeamMates[i], it->first);
			}
		}
	}

	//printf("3--%d\n", a.elapsed() );
	//printf("~~~total--%d\n\n", b.elapsed() );
}

void CTaskModule::NotifyClientUpTask( CEntityPlayer* pPlayer, CTask* pTask, int nPreState, unsigned int nEventID, unsigned int nParam )
{
	LK_ASSERT( pPlayer!=NULL && pTask!=NULL, return );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList, return );
	LK_ASSERT( pTask != NULL, return );

	// ����Ǹ�����Ʒ �����½ӿ�֪ͨ
	if ( nEventID == EVENT_ITEMCHANGE)
	{
		if (pTask->GetTaskProgress() == TASK_BEGIN || nPreState == TASK_BEGIN )
		{
			CMessageUpdateTaskConditions msg;
			TaskCondition* pCondition = msg.add_contions();
			LK_ASSERT( pCondition, return );
			pCondition->set_taskid( pTask->mTaskID );
			pCondition->set_tempid( nParam );
			pCondition->set_num( 0 ); // ��Ʒ��������
			pCondition->set_condition( CONDITION_ITEM );
			SendUpdateConditions2Client( pPlayer, &msg );
		}
		return;
	}

	// ��֤/����timer
	if (pTask->mTimerID != INVALID_OBJ_ID)
	{
		CTimerItem* tpTimer = CTimerMng::GetSingleton().GetTimer(pTask->mTimerID);
		if ( tpTimer == NULL )
		{
			LOG_ERROR("TASK", "task%d can't find timer? timerid=%d", pTask->mTaskID, pTask->mTimerID );
		}
		else
		{
			// ����ʣ��ʱ��(����)
			pTask->mGameTimeLeft = tpTimer->mMillSeconds/1000;
		}
	}


	CMessageUpdateTaskNotice msg;
	TaskStruct* tpTask = msg.mutable_task();
	pTask->GetTaskDataStruct(tpTask);
	CMessage   tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_UPDATE);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}



// �������������Ʒ ���أ��Ƿ������������Ʒ
bool CTaskModule::OnTaskDropItems( CEntityPlayer* pPlayer, CProperty* pDesProperty, CItemsPair& rSpecial, std::map<unsigned short, unsigned short>& rUpList, CMessageUpdateTaskConditions* pUpdateMsg )
{
	//Clock a;
	//a.start();
	//printf("in OnTaskDropItems\n" );

	bool bret = false;
	CPropertyPlayer* tpProperty = (CPropertyPlayer*) pPlayer->GetProperty();
	LK_ASSERT ( NULL != tpProperty, return false)

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );

	for (int k = 0; k < pList->mTaskNumber; ++k)
	{
		//printf("0.1--%d\n", a.elapsed() );
		//a.start();
		if ( pList->mTaskList[k].mTaskProgress != TASK_BEGIN )
			continue;
		if ( !pList->mTaskList[k].IsEventTick( EVENT_OGREDIE, pDesProperty->GetPropertyTempID( )) )
			continue;

		int nDropID = 0;
		int n = 0;
		int nMaxn = 0;

		if( mTaskDropMgr.GetDropItems( pList->mTaskList[k].mTaskID, pDesProperty->GetPropertyTempID( ), nDropID, n, nMaxn ) )
		{
			CTplItem* tpItem = (CTplItem*)CDataStatic::SearchTpl( nDropID );
			if (tpItem != NULL && ( tpItem->mItemType != CTplItem::ITEM_TASK || tpItem->mItemType != CTplItem::ITEM_SPECIAL_TASK || 
				tpItem->mItemType != CTplItem::ITEM_TOKEN ) )
			{
				if (tpItem->mItemType == CTplItem::ITEM_SPECIAL_TASK) // ���������������Ʒ�����±�ǣ�������ı�����Ա�ĵط��ֱ𷢷�
				{
					rSpecial.push_back(std::make_pair<int, int>( nDropID, 1));
					bret = true; // ���������Ҳ��
				}
				else
				{
					int tNeedNum = nMaxn - tpProperty->BaggageHasItem(nDropID);				
					if ( tNeedNum <= 0 ) // �������ͨ������ߣ�����һ�û�Ѽ���
						continue;

					int tNum = std::min( tNeedNum, n );
					// ����������û
					if ( ! tpProperty->TestBaggageSpace( &nDropID, &tNum, 1 ) )
					{
						CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_INSERTITEM_NOSPACE );
						break;
					}
					else
					{
						//printf("0.22--%d\n", a.elapsed() );
						//a.start();
						// ���������Ʒ���뵽��Ʒ����
						CItemObject* pInsItemPile = 
							CPropertyModule::GetSingleton( ).PlayerInsertItem( pPlayer, nDropID, tNum, true );

						if ( pInsItemPile != NULL)
						{
							LogEventGetItemByRunTask(pPlayer, pInsItemPile->GetGUID(), 
									nDropID, tNum, pList->mTaskList[k].mTaskID, pDesProperty->GetPropertyTempID());
						}

						bret      = true;
						// bIsDrop   = true;
						if ( pList->mTaskList[k].mWatchEventN > 0 && pList->mTaskList[k].mWatchEventN-tNum <= 0 )
						{
							// ���������
							rUpList.insert( std::make_pair(pList->mTaskList[k].mTaskID, pList->mTaskList[k].mTaskID) );
						}
						pList->mTaskList[k].mWatchEventN -= tNum;
						TaskCondition* pCondition = pUpdateMsg->add_contions();
						LK_ASSERT( pCondition, return false );
						pCondition->set_taskid( pList->mTaskList[k].mTaskID );
						pCondition->set_tempid( nDropID );
						pCondition->set_num( tNum );
						pCondition->set_condition( CONDITION_ITEM );
						LOG_DEBUG("TASK", "minused mWatchEventN=%d", pList->mTaskList[k].mWatchEventN );
					}
				}
			}

			//printf("0.23--%d\n", a.elapsed() );
			//a.start();
		}
		//if ( bIsDrop )
		//{
		//	rUpList.insert( make_pair(pList->mTaskList[k].mTaskID, pList->mTaskList[k].mTaskID) );
		//}
		//printf("0.3--%d\n", a.elapsed() );
		//a.start();
	}
	return bret;
}


// ����������� �������� �ͱ������������������  �б仯�ͷ���true
bool CTaskModule::OnTaskOgreDie( CEntity* pOwnerEntity, CEntityPlayer* pPlayer, CProperty* pDesProperty, CItemsPair& rSpecialTaskItem, std::map<unsigned short, unsigned short>& rUpList , CMessageUpdateTaskConditions* pUpdateMsg  )
{
	if ( pPlayer == NULL ) 
		return false;

	bool bret = false;
	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();

	// ȡ����ҵ�ǰ�������б�
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );

	// ��Ŀǰ��������һ�������������� 
	bool bIsStorageTaskUpdated = false; // �������Ƿ��Ѿ��������� (������ͬʱֻ����1��)
	for(int i = 0; i < pList->mTaskNumber; ++i)
	{
		// �ȿ���Ҫ����Ҫĳ������������Ʒ
		std::vector< std::pair<int, int> >::iterator it = rSpecialTaskItem.begin();
		for(; it != rSpecialTaskItem.end(); ++it)
		{
			if ( pList->mTaskList[i].IsEventTick( EVENT_ITEMCHANGE, it->first )
				&& !pProperty->GetTaskBaggage( )->HasItem(it->first) )
			{
				// ����������û
				int num = 1;
				if ( ! pProperty->TestBaggageSpace( &it->first, &num, 1 ) )
				{
					CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_INSERTITEM_NOSPACE );
				}
				else
				{
					// ���������Ʒ���뵽��Ʒ����(����������Ʒ)
					CItemObject * pInsItemPile = CPropertyModule::GetSingleton( ).PlayerInsertItem( pPlayer, it->first, 1, true);
					if ( pInsItemPile != NULL)
					{
						LogEventGetItemByRunTask(pPlayer, pInsItemPile->GetGUID(), 
								it->first, 1, pList->mTaskList[i].mTaskID, pDesProperty->GetPropertyTempID());
					}

					
					if ( pList->mTaskList[i].mWatchEventN > 0 && pList->mTaskList[i].mWatchEventN-1 <= 0 )
					{
						// ���������
						rUpList.insert( std::make_pair(pList->mTaskList[i].mTaskID, pList->mTaskList[i].mTaskID) );
					}
					pList->mTaskList[i].mWatchEventN --;
					TaskCondition* pCondition = pUpdateMsg->add_contions();
					LK_ASSERT( pCondition, return false );
					pCondition->set_taskid( pList->mTaskList[i].mTaskID );
					pCondition->set_tempid( it->first );
					pCondition->set_num( 1 );
					pCondition->set_condition( CONDITION_ITEM );

					// pList->mTaskList[i].mWatchEventN--;
					LOG_DEBUG("TASK", "minused mWatchEventN=%d", pList->mTaskList[i].mWatchEventN );
					bret = true;
				}
			}
		}

		//if ( !counted ) // û�������жϹ���
		//{
		// ���ɱ����ORGE��������أ�����Ҫ�����������,������ÿ���˶�����һ��
		// ���²���update�߼�������Ϊ�����ͳһ����update��
		if ( pPlayer->IsWithinDistance( pOwnerEntity, TEAM_VALID_DISTANCE ) == false )
			continue; // ��������

		if ( pList->mTaskList[i].mTaskProgress != TASK_BEGIN )
			continue;

		int nThisTaskType = GetTaskType( pList->mTaskList[i].mTaskID );
		if (nThisTaskType == TASKTYPE_STORAGE && bIsStorageTaskUpdated )
			continue; // ������ֻ����1��

		int _ret_num = 0;
		int _ret_id  = CONDITION_LEVELOGRE; // û��ģ��ID��ɱ�� ����Ϊ�ȼ�ɱ��

		// ���ж��ǲ��ǵȼ�ɱ������
		if ( (pList->mTaskList[i].mExFlags&EXFLAG_LEVELKILLOGRE) == EXFLAG_LEVELKILLOGRE )
		{
			// �ȼ�ɱ�� ���⴦��
			_ret_num = CTaskLuaInterface::Call<int, CTask*, int>(pPlayer, pList, "on_level_orge_die", &pList->mTaskList[i], pDesProperty->GetLevel() );
		}
		else
		{
			if ( !pList->mTaskList[i].IsEventTick( EVENT_OGREDIE, pDesProperty->GetPropertyTempID( )) )
				continue;
			lua_tinker::table Params(L);
			Params.set("id", pDesProperty->GetPropertyTempID( ) );
			Params.set("n", 1);		
			lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, CTask*, lua_tinker::table>(pPlayer, pList, "on_orge_die", &pList->mTaskList[i], Params);
			_ret_num = ret.get<int>("num");
			_ret_id  = ret.get<int>("id");
		}
		
		if( _ret_num  > 0 ) // lua�ж�ɱ�ֳɹ���
		{
			TaskCondition* pCondition = pUpdateMsg->add_contions();
			LK_ASSERT( pCondition, return false );
			pCondition->set_taskid( pList->mTaskList[i].mTaskID );
			pCondition->set_tempid( _ret_id );
			pCondition->set_num( _ret_num );
			pCondition->set_condition( CONDITION_OGREDIE );

			// ��¼��־
			LogEventTaskAction( pPlayer, pList->mTaskList[i].mTaskID, EM_TASK_ACTION, EVENT_OGREDIE, _ret_id );

			if ( pList->mTaskList[i].mWatchEventN > 0 && pList->mTaskList[i].mWatchEventN-1 <= 0 )
			{
				// ���������
				rUpList.insert( std::make_pair( pList->mTaskList[i].mTaskID, pList->mTaskList[i].mTaskID ) );
			}
			//counted = true;
			pList->mTaskList[i].mWatchEventN--;
			LOG_DEBUG("TASK", "minused mWatchEventN=%d", pList->mTaskList[i].mWatchEventN );
			bret = true;

			if ( nThisTaskType == TASKTYPE_STORAGE )
				bIsStorageTaskUpdated = true;
		}
	}
	return bret;
}

// �������ɵ�����
void CTaskModule::ClearCompletedTask( CEntityPlayer* pPlayer, unsigned short usTaskID )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );
	pList->SetEnd(usTaskID);
}


void CTaskModule::ClearTragedy(CEntityPlayer* pPlayer, int nIndex )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );
	pList->mTragedyTaskMgr.Clear(nIndex);
}

// bIsSystemCall���Ƿ�ϵͳ���� ����� �������� ��Ϊ�Ȿ�����ǻ�������� ������ѭ��
void CTaskModule::PlayerAbortTask(CEntityPlayer* pPlayer, unsigned short vTaskID, bool bIsDebug, bool bIsSystemCall )
{
	LK_ASSERT(pPlayer, return);
	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();

	if ( !bIsDebug && IsTaskAbortAble(vTaskID) == 0 && CSceneCfgManager::GetSingletonPtr()->GetTask_cfg()->mIscanabort == 1 )// �����ܷ���
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_CANTABORTMAIN );
		return;
	}
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	CTask* pTask = pList->GetTask(vTaskID);
	if( pTask == NULL) 
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_ABORTINVALID );
		return;
	}

	if ( (pTask->mExFlags&EXFLAG_PROTECT_FLAG_TASK) == EXFLAG_PROTECT_FLAG_TASK ) // �������� ȡ��ע��
	{
		mNpcMonitor.RemoveGlobalTaskAction( pTask->GetFirstParamByEvent(EVENT_PROTECT_FLAG)
			, pPlayer, vTaskID );
	}

	int nTaskType = GetTaskType(vTaskID);
	// ����ǿ��������ӻ��б� ���������б���ͻ���
	if (nTaskType == TASKTYPE_STORAGE)
	{
		if ( pList->mStorageTaskMgr.OnAbortTask(vTaskID) ) // ���������������ȥ��
			SendStorageTaskList2Client( pPlayer, pList, pProperty->GetTalkNpcEntityID( ) );
	}

	// ����ǽ������� ���������״̬
	if ( nTaskType == TASKTYPE_TRAGEDY )
	{
		int			   tIndex = CTaskLuaInterface::Call<int, unsigned short>( pPlayer, pList, "get_tragedy_id", vTaskID );
		int			   tState = TRAGEDY_ACTIVE;
		unsigned short tNextID = vTaskID;
		pList->mTragedyTaskMgr.SetState(tIndex, (enTragedyTaskState)tState);
		pList->mTragedyTaskMgr.SetNextTask(tIndex, tNextID);
		SendTragedyInfo2Client( pPlayer, &tIndex, &tNextID, &tState, 1 );
	}

	// �������� ����
	if ( nTaskType == TASKTYPE_CHAIRMAN )
	{
		pList->mChairManTaskMgr.OnAborted();
	}

	if ( !bIsSystemCall )
	{
		// ��������������ȥ����
		mSendNpcMgr.ClearPlayerSendSession( pPlayer, false );
	}

	// ɾ�������б��е����� ���������Ʒ ���ͻ��˷�ʧ����Ϣ
	// OnTaskFailed(pPlayer, vTaskID, true);

	// �ɵ�timer id
	if( pTask->mTimerID != INVALID_OBJ_ID )
	{
		int tRet = pPlayer->GetTimerReciver()->ClearTimer( pTask->mTimerID );
		if ( tRet != 0 )
			LOG_ERROR("TASK", "abort del timer returned %d, timerid=%d taskid=%d", tRet, pTask->mTimerID, vTaskID );

		LOG_DEBUG("TASK", "abort del timer returned %d, timerid=%d taskid=%d", tRet, pTask->mTimerID, vTaskID );
		pTask->mTimerID = INVALID_OBJ_ID;
		pTask->mGameTimeLeft = -1;
	}


	pList->RemoveTask( vTaskID );
	
	// ȡ�÷��ŵ���Ʒ

	CItemsPair tmp; 

	// ȡ�÷�����Ʒ
	PERF_FUNC( "GetTaskExtendItems", GetTaskExtendItems( pPlayer, vTaskID, tmp) );
	DropItems( pPlayer, tmp, vTaskID);

	// ɾ���Ѿ��ռ�����Ʒ
	DropCompleteItems(pPlayer, vTaskID, true);

	CTaskLuaInterface::Call<int,int>( pPlayer, pList, "on_abort_task", vTaskID); // ��LUA�ﴦ������ǻ�����ȷǳ�������Ҫ���⴦��
	if ( GetTaskType(vTaskID) == TASKTYPE_LOOP ) // ������Ҫ���⴦��
	{
		pList->mLoopTaskData.SetAbortData( );
		CTaskLuaInterface::Call<int, int, int>( pPlayer, pList, "init_loop_tasks" , pPlayer->GetMetier(), pPlayer->GetLevel() ); // ˢ�»�����
	}

	if ( nTaskType == TASKTYPE_PUBLISH )
	{
		pList->SetPublishTaskState(vTaskID, PUBLISHED_TASK, GetTaskPublishType(vTaskID));
	}

	int vColor = pList->GetTaskColor(vTaskID);
	for (int i = 0; i < TASK_LIST_SIZE; ++ i)
	{
		if (pList->mRememberRefreshNum[i].rTaskID == vTaskID)
		{
			pList->RemoveTaskColor(vTaskID);
			Send2ClientRemoveTaskColor(pPlayer, vTaskID, vColor);
			break;
		}
	}

	FireEvent( pPlayer, EVENT_TASKCHANGE, vTaskID ) ;
	 

	CMessageAbortTaskNotice msg;
	msg.set_taskid( vTaskID );
	CMessage   tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_ABORT_TASK);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}


//  ��һ������
bool CTaskModule::PlayerObtainTask( CEntityPlayer* pPlayer, unsigned short vTaskID, bool bIsNoChkNpc, int nNpcEntityID, int nInvitingPlayerID )
{
	LK_ASSERT(pPlayer, return false);
	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();

	// ȡ����ҵ������б���Ϣ
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );

	// ��������Ƿ���ɻ����ڽ�����
	if(pList->GetTaskState(vTaskID) != -1)
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_HASACCEPT );
		return false;
	}

	int NowTime = time(0);
	int CDtime = GetTaskReaccept(vTaskID);
	int NeedTime = pList->GetEndTime(vTaskID) + CDtime - NowTime;
	if ( CDtime != 0 &&  pList->GetEndTime(vTaskID) != 0)
	{
		if ( NeedTime > 0 )
		{
			Send2ClientUnReaccpetTask(pPlayer, vTaskID, NeedTime );	
			return false;
		}
	}

	// �����Ƿ���Խ�, ����lua�ű�
	bool bRet = false;

	// �ж�NPC�Ϸ� ��ұ���վ��NPC�Ա߽����� �ʰ��������
	int nNpcID = 0;
	CEntity* tpEntity = CSceneLogic::GetSingleton( ).GetEntity( nNpcEntityID );
	if ( tpEntity != NULL ) 
	{
		if( tpEntity->IsNpc() && pPlayer->IsWithinDistance( tpEntity, MAX_NPC_TALK_GIRD) ) // �ںϷ�����֮�ڲ��ж�
		{
			CPropertyNPC* pPropertyNpc = (CPropertyNPC*)tpEntity->GetProperty();
			if ( pPropertyNpc == NULL )
			{
				LOG_ERROR("TASK", "npc property is null, line=%d", __LINE__ );
			}
			else
			{
				nNpcID = pPropertyNpc->GetPropertyTempID();
			}
		}
	}

	pList->SetTalkNpcEntityID( nNpcEntityID );

	pList->SetInvitingPlayerID( nInvitingPlayerID ); // �ڽ����������Ĵ����л��õ����ֵ

	int nTaskType = GetTaskType( vTaskID );

	//  δ�������� ���ɽ�

	if(nTaskType == TASKTYPE_PUBLISH)
	{
		int SelfState = pList->GetPublishStateByType(vTaskID, GetTaskPublishType(vTaskID));
		if(SelfState == UNPUBLISH_TASK)
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_UNPUBLISHED);
			return false;
		}
	}

	// ��������� �������� �����NPC  �ⲿҪ�󲻼���ʱ��Ҳ�����
	if ( bIsNoChkNpc 
		|| nTaskType == TASKTYPE_SCROLL 
		|| nTaskType == TASKTYPE_TRAGEDY 
		|| nTaskType == TASKTYPE_FAMILY 
		|| nTaskType == TASKTYPE_PUBLISH )
	{
		PERF_FUNC( "IsTaskAcceptable", bRet = IsTaskAcceptable(pPlayer, pList, vTaskID, 0 ) );
	}
	else if( nNpcID != 0 )
	{
		PERF_FUNC( "IsTaskAcceptable", bRet = IsTaskAcceptable(pPlayer, pList, vTaskID, nNpcID ) );
	}
	pList->SetInvitingPlayerID( -1 );

	if ( IsTeamLoop(vTaskID) == 1 )
	{
		// �������ӻ����� �ж����г�Ա(�ڷ�Χ�ڣ���ɴ���û����������ͬ�������������б�û��)
		// ��ȡ�������б�
		CTeam* tpTeam = ( CTeam* ) CSceneObjManager::GetSingleton().GetObject( CTeamModule::GetSingleton().InTeam( pPlayer->GetCharID() ) );
		if (tpTeam == NULL)
		{
			CPropertyModule::GetSingleton().SendProErrorNotice(pPlayer, ERROR_TASK_TEAMLOOP_YOUNOTHEAD);
			return false;
		}
		if ( tpTeam->GetHeaderID() != pPlayer->GetCharID() )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice(pPlayer, ERROR_TASK_TEAMLOOP_YOUNOTHEAD);
			return false;
		}
		int nTeamMember[TEAMNUM] = {0};
		int nMemberNum=0;
		tpTeam->GetMemberList(nTeamMember, TEAMNUM, nMemberNum);
		LK_ASSERT(nMemberNum <= TEAMNUM, return false );
		// �ж�����
		int nMemberLmt = GetTeamMember(vTaskID);
		int vColor = pList->GetTaskColor(vTaskID);
		if (nMemberLmt != nMemberNum)
		{
			CPropertyModule::GetSingleton().SendProErrorNotice(pPlayer, ERROR_TASK_TEAMLOOP_MEMBERLESS);
			return false;
		}
		for (int i = 0 ; i < nMemberNum; ++i )
		{
			CEntityPlayer* tpMember = CSceneLogic::GetSingleton().GetPlayerByCharID(nTeamMember[i]);
			if (tpMember == NULL)
			{
				CPropertyModule::GetSingleton().SendProErrorNotice(pPlayer, ERROR_TASK_TEAMLOOP_MEMBERERR);
				return false;
			}
			if ( pPlayer->IsWithinDistance( tpMember, TEAM_VALID_DISTANCE ) == false )
			{
				CPropertyModule::GetSingleton().SendProErrorNotice(pPlayer, ERROR_TASK_TEAMLOOP_MEMBERERR);
				return false;
			}
			CTaskList* tpList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(tpMember->GetTaskToken( ));
			LK_ASSERT( tpList,  return false );
			for (int j = 0; j < std::min(tpList->mTaskNumber, (unsigned short)TASK_LIST_SIZE); ++j)
			{
				if (IsTeamLoop(tpList->mTaskList[j].mTaskID) == 1)
				{
					SendTeamLoopErrNotify( pPlayer, tpMember->GetCharName(), ERROR_TASK_TEAMLOOP_MEMBERGOT);
					return false;
				}
				if (tpList->GetTodayTeamLoopNum() >= MAX_TEAMLOOP_EVERYDAY)
				{
					SendTeamLoopErrNotify( pPlayer, tpMember->GetCharName(), ERROR_TASK_TEAMLOOP_MEMBERCOMP);
					return false;
				}
				if (tpList->mTaskNumber >= TASK_LIST_SIZE)
				{
					SendTeamLoopErrNotify( pPlayer, tpMember->GetCharName(), ERROR_TASK_TEAMLOOP_MEMBERFULL);
					return false;
				}
			}
			// ��������Ա�ɲ����Խ�
			if ( !IsTaskAcceptable(tpMember, tpList, vTaskID, nNpcID ) )
			{
				SendTeamLoopErrNotify( pPlayer, tpMember->GetCharName(), ERROR_TASK_TEAMLOOP_CANT_ACCEPT);
				return false;
			}
		}

		// ���г�Աû���� ����� �����в����������
		for (int i = 0 ; i < nMemberNum; ++i )
		{
			CEntityPlayer* tpMember = CSceneLogic::GetSingleton().GetPlayerByCharID(nTeamMember[i]);
			if (tpMember == NULL)
			{
				continue;
			}
			if (tpMember->GetEntityID() == pPlayer->GetEntityID())
				continue;
			PlayerFastObtainTask(tpMember, vTaskID, vColor);
		}
	}

	// ������������� �����ж� 
	// �õ�����ID (���Ǵ۸Ŀͻ��������֤����ʧ��)
	unsigned short usChairManId = 0;
	if ( nTaskType == TASKTYPE_CHAIRMAN )
	{
		usChairManId = CTaskLuaInterface::Call<unsigned short, unsigned short>
			( pPlayer, pList, "get_chairman_id", vTaskID );

		if ( usChairManId == 0 || !pList->mChairManTaskMgr.CheckAcceptChairMan(usChairManId) )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_GOT_CHAIRMAN );
			pList->SetTalkNpcEntityID(0);
			return false;
		}
	}

	if(!bRet)
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_ACCEPTINVALID );
		pList->SetTalkNpcEntityID(0);
		return false;
	}

	// ������ ���⴦��
	if ( nTaskType == TASKTYPE_STORAGE )
	{
		if ( pList->mStorageTaskMgr.GetGotNum() >= MAX_STORAGETASK_LIST_NUM )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_STORAGEMAX );
			pList->SetTalkNpcEntityID(0);
			return false;
		}
	}

	// ������ ���⴦��
	if ( nTaskType == TASKTYPE_LOOP )
	{
		// �жϻ�������ȴʱ��
		int nCDtime = CTaskLuaInterface::Call<int, unsigned short>(pPlayer, pList, "get_loop_task_punish_time", vTaskID );
		if ( (int)(time(0) - pList->mLoopTaskData.GetLastAbortTime()) < nCDtime )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_LOOP_CD_NOTEND );
			return false;
		}
	}

	// �������� ���⴦��
	if ( nTaskType == TASKTYPE_CHAIRMAN )
	{
		pList->mChairManTaskMgr.ResetTasks( usChairManId ) ;
		pList->mChairManTaskMgr.OnAccepted();
	}

	//  ȡ��������Ҫ���ŵĵ���, ��ΪTestBaggageSpace�Ľӿ�����
	CItemsPair mExtendItems;
	PERF_FUNC( "GetTaskExtendItems" , GetTaskExtendItems( pPlayer, vTaskID, mExtendItems) );
	
	//  ���ռ��Ƿ����㣬�����������ô�����ܽӣ�ͬʱ�ͻ���Ҳ����ر�����Ի�����
	if (mExtendItems.size() > 0 )
	{
		const int BAGGAGESPACE = 4;
		int mExtendItemID[BAGGAGESPACE] = {0};
		int mExtendItemNumber[BAGGAGESPACE] = {0}; 
		CItemsPair::iterator iter = mExtendItems.begin();
		for(int i = 0; iter != mExtendItems.end(); ++iter,++i)
		{
			mExtendItemID[i] = iter->first;
			mExtendItemNumber[i] = iter->second;
		}
		if ( pProperty->TestBaggageSpace( mExtendItemID, mExtendItemNumber, BAGGAGESPACE ) == false )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_NOSPACE );
			pList->SetTalkNpcEntityID(0);
			return false;
		}
	}
	
	LOG_DEBUG( "TASK", "player want to get task , id = %d", vTaskID);

	//  ��������
	CTask vTask; 
	vTask.mTaskID = vTaskID;
	int tRet = pList->InsertTask(vTask);

	if ( tRet == ERROR_TASK_SUCCESS )
	{

		CTask* pTask = pList->GetTask(vTaskID);
		LK_ASSERT( pTask, return false );

		//  ����ɹ��Ļ�����񣬷����������
		CItemsPair::iterator iter = mExtendItems.begin();
		for (; iter != mExtendItems.end() ; ++iter )
		{
			if ( iter->first == 0 )	break;

			CItemObject *pInsItemPile = 
				CPropertyModule::GetSingleton( ).PlayerInsertItem( pPlayer, iter->first, iter->second, true);

			if ( pInsItemPile != NULL)
			{
				LogEventGetItemByAcceptTask(pPlayer, pInsItemPile->GetGUID(), iter->first, iter->second, vTaskID);
			}

		}

		// ��ʼ��һ����������
		CTaskLuaInterface::Call<int, CTask*>( pPlayer, pList, "init_this_task", pTask); //  ��ʼ�������õ��������Ҫɱ�ֵ�������

		// ֪ͨ�ͻ���
		CMessageObtainTaskNotice msg;
		TaskStruct* tpTask = msg.mutable_task();
		pTask->GetTaskDataStruct(tpTask);
		if ( GetTaskType(pTask->mTaskID ) == TASKTYPE_LOOP ) // �ǻ�����
		{
			if ( msg.has_looptask() )
			{
				LOG_ERROR( "TASK", "player %s has loop err!", pPlayer->GetCharNameShow() );
			}
			else
			{
				LoopTaskStruct* tpLoop = msg.mutable_looptask();
				GetLoopTaskClientData( pPlayer, pList, tpLoop);
			}
		}

		CMessage   tMessage;
		tMessage.set_msgpara((uint32_t) &msg);
		tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_OBTAINTASK);
		CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );

		//  �ж�һ�������Ƿ����(ǿ��ˢ��)
		FireEvent( pPlayer, 0 );
		bool bEnd;
		UpdateTaskProgress( pPlayer, pTask, bEnd, 1 );

		// �жϽ������� ��״̬
		// ����ǽ������� ���������״̬
		if (GetTaskType(vTaskID) == TASKTYPE_TRAGEDY )
		{
			int			   tIndex = CTaskLuaInterface::Call<int, unsigned short>( pPlayer, pList, "get_tragedy_id", vTaskID );
			int			   tState = TRAGEDY_GOT;
			unsigned short tNextID = vTaskID;
			pList->mTragedyTaskMgr.SetNextTask(tIndex, tNextID);
			pList->mTragedyTaskMgr.SetState(tIndex, (enTragedyTaskState)tState);
			SendTragedyInfo2Client( pPlayer, &tIndex, &tNextID, &tState, 1 );
		}

		// ����ǿ����񣬷������б���ͻ���
		if ( GetTaskType(vTaskID) == TASKTYPE_STORAGE )
			SendStorageTaskList2Client( pPlayer, pList, pProperty->GetTalkNpcEntityID( ) );

		// ��������ӿ�����Ҫ�ж��Ƿ�������������� �Ա��ڴ�����NPC
		pList->SetInvitingPlayerID( nInvitingPlayerID );
		DoTaskObtAwards( pPlayer, pList, vTaskID );
		// ����������ʵʱ���� ���ô��� ���㴫�߿���� ����ľͲ������ ����Ҳû��ϵ
		pList->SetInvitingPlayerID( -1 );
		pList->SetTalkNpcEntityID(0);

		// ȡ����ID �����Ϊ0  Ҫ������ ���ӽ��ܴ���
		int tGroupID = CTaskLuaInterface::Call<int, unsigned short>( pPlayer, pList, "get_task_group_id", vTaskID );
		if ( tGroupID != 0 )
		{
			pList->mTaskGroupMgr.OnAcceptOneTask( tGroupID );
		}

		if ( GetTaskType(vTaskID) == TASKTYPE_PUBLISH )
		{
			pList->SetPublishTaskState(vTaskID,ACCEPTED_TASK, GetTaskPublishType(vTaskID));  // �ı����񷢲�״̬
		}
	}
	else
	{
		pList->SetTalkNpcEntityID(0);
		pList->SetInvitingPlayerID( -1 );
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, tRet );
	}

	return tRet == ERROR_TASK_SUCCESS;
}

//  ���ˢ��������
bool CTaskModule::PlayerRefreshTaskAward(CEntityPlayer* pPlayer, unsigned short vTaskID,int mRefreshItemIndex, int nNpcEntityID )
{
	LK_ASSERT(pPlayer, return false);

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );
	
	// ���ɽӵ�����
	if ( IsTaskAcceptable( pPlayer, pList, vTaskID, nNpcEntityID ) == false )
	{
		Send2ClientOprFailed(pPlayer);
		LOG_ERROR("TASK", "task is not acceptable!");
		//return false;
	}

	// ����ˢ�µ�����
	if ( IsRefreshAward(vTaskID) == false )  
	{
		Send2ClientUnRefreshed(pPlayer);
		LOG_ERROR("TASK", "task is unrefreshable!");
		return false;
	}

	// �������ӻ����� ���ж��ǲ��Ƕӳ�
	if (IsTeamLoop(vTaskID) == 1) 
	{
		CTeam* tpTeam = ( CTeam* ) CSceneObjManager::GetSingleton().GetObject(CTeamModule::GetSingleton().InTeam( pPlayer->GetCharID() ) );
		if (tpTeam == NULL || tpTeam->GetHeaderID() != pPlayer->GetCharID())
		{
			LOG_ERROR("TASK","You are not the team leader!");
			return false;
		}
	}

	int vTaskColor = CTaskLuaInterface::Call<int, unsigned short>( pPlayer, pList, "get_refreshed_type", vTaskID );
	
	//  �˴������ж���Ч����	
	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	LK_ASSERT( pProperty, return false );

	CItemObject* pObj = pProperty->GetBaggage()->GetItemObjPtr(mRefreshItemIndex);
	if (pObj == NULL)
	{
		LOG_ERROR("TASK", "load bag data failed  player entityID=%d  index=%d", pPlayer->GetEntityID(), mRefreshItemIndex );
		return false;
	}
	int64_t vGuID = pObj->GetGUID();
	int32_t vItemID = pObj->GetItemID();

	// ˢ������۳���Ӧ��ˢ�µ���
	if (CPropertyModule::GetSingleton().PlayerRemoveItem( pPlayer, (unsigned int)mRefreshItemIndex, 1) == 0)
	{ 
		LogEventLostItemByUse( pPlayer, vGuID, vItemID, 1);	
		LOG_DEBUG("TASK","remove item success!");
	}
	else
	{
		LOG_ERROR("TASK",  "clear task(id=%d) item(%d)  from (roleid=%d) error", 
			vTaskID,  vItemID, pPlayer->GetCharID());
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_LESS_RECV_ITEM );
		Send2ClientOprFailed( pPlayer );
		return false;
	}
	int vTaskNumber = pList->InsertRefreshedTask(vTaskID, vTaskColor);
	Send2ClientRefreshResult(pPlayer, vTaskID, vTaskColor, vTaskNumber);

	return true;
}

//  ��Ҹ�������
bool CTaskModule::UpdateTaskProgress(CEntityPlayer* pPlayer, CTask* pTask, bool& bIsAutoEnd, int nSend , unsigned int nEventID, unsigned int nParam)
{
//  ��Ҹ������� ����״̬������������£���
//  nSend = 1 : ����״̬���ı�Ҳ֪ͨ�ͻ��ˣ�(���ڵ��߽���,���ֵȷǳ������)
//  ������£��ڽ����񣬽����񣬷������񡣡����ط����õĸ���

	//Clock a;
	//a.start();
	// �������������ݷ����˱����������Ϣ
	if (pTask == NULL || pTask->mTaskID == 0)
	{
		LOG_ERROR("TASK", "task is null or task id = 0 in update task, pTask is %d", (int)pTask);
		return false;
	}

	int prev_state = pTask->mTaskProgress;

	// Ҫ��update_task��������������״̬��
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );
	CTaskLuaInterface::Call<bool, CTask*>( pPlayer, pList, "update_task", pTask ); // ����ֵ��û�����ô��

	//printf("--3.1--%d\n", a.elapsed() );
	//a.start();
	if( nSend == 1 )
	{
		NotifyClientUpTask(pPlayer, pTask, prev_state, nEventID, nParam);
	}
	//printf("--3.2--%d\n", a.elapsed() );
	//a.start();
	if (pTask->mTaskProgress != prev_state)
	{
		// ���״̬��COMPLETE��BEGIN��˵�������˻ع�
		if( pTask->mTaskProgress == TASK_BEGIN && prev_state == TASK_COMPLETE)
		{
			CMessageResetTaskNotice msg;
			msg.set_taskid(pTask->mTaskID);
			CMessage   tMessage;
			tMessage.set_msgpara((uint32_t) &msg);
			tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_RESET);
			CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
		}

		// �������״̬�����״̬����֪ͨ����������
		if(pTask->mTaskProgress == TASK_COMPLETE)
		{
			// �ɵ�timer id  (��������ɲ��ɵ���ʱ�� �����Ÿɵ�)
			//if( pTask->mTimerID != INVALID_OBJ_ID )
			//{
			//	pPlayer->GetTimerReciver()->ClearTimer( pTask->mTimerID );
			//	pTask->mTimerID = INVALID_OBJ_ID;
			//}
#ifdef _FB_
			// ����Ϭ��Ľӿ�
			CRepetionModule::GetSingleton().EndTask( pPlayer, pTask->mTaskID, true );
#endif
			if (CTaskLuaInterface::Call<bool,unsigned short>( pPlayer, pList,"is_direct_complete", pTask->mTaskID)) // ������ֱ����ɵģ�
			{
				bIsAutoEnd = true;
				return true;
			}
			
			CMessageTaskCompleteNotice msg;
			msg.set_taskid(pTask->mTaskID);
			CMessage   tMessage;
			tMessage.set_msgpara((uint32_t) &msg);
			tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_COMPLETE);
			CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );

			// ���Ҫ���� ��ͬ�����Ҫ�����
			if ( IsCompleteShare( pTask->mTaskID ) == 1 )
			{
				CSeenPlayerContainer tSeenPlayers = pPlayer->GetSeenPlayersContainer();  // �õ�ͬ�������
				std::vector<unsigned int> tPlayers;
				for ( CSeenPlayerContainer::SeenPlayerVector::iterator it = tSeenPlayers.mPlayers.begin(); 
					it != tSeenPlayers.mPlayers.end(); ++it )
				{
					CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(*it);
					LK_ASSERT( tpPlayer != NULL, continue );
					if ( tpPlayer->GetNationality() == pPlayer->GetNationality() )
						tPlayers.push_back( *it );
				}
				OnForceTaskComplete( tPlayers, pTask->mTaskID );
			}
		}
		//PERF_FUNC("ReSendAllNpcTipInEye", ReSendAllNpcTipInEye(pPlayer, vpPlayerProperty) );
	}
	//printf("--3.3--%d\n", a.elapsed() );

	return true;
}

//  ��ҽ�������
bool CTaskModule::PlayerEndTask( CEntityPlayer* pPlayer, unsigned short vTaskID, short vSelect, bool bIsAuto, int vBagIndex )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );

	// ��鲢����һ������״̬
	CTask* pTask = pList->GetTask(vTaskID);
	if(pTask == NULL)
	{
		return false;
	}
	int ltime = time(0);										// ��ǰʱ��
	int vDelayNum = GetFinishDelayTime(vTaskID);				// ����ò��ܽ�����
	int LiftTime = pTask->mTaskBeginTime + vDelayNum - ltime;	// ������ʣ��ʱ��
	if (vDelayNum > 0)
	{
		if ( pTask->GetTaskProgress() != TASK_COMPLETE )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_NOTCOMPLETE );
			return false;
		}

		if (LiftTime > 0)
		{
			CMessageUnFinishTaskTime msg;
			msg.set_taskid(vTaskID);
			msg.set_needtime(LiftTime);
			CMessage   tMessage;
			tMessage.set_msgpara((uint32_t) &msg);
			tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTIFY_UNFINISHTIMEERR);
			CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
			return false;
		}
	}
	if (vSelect != -100)
	{
		// ���һ���û���������OptionID�Ƿ�������ķ�Χ��
		int max_option = CTaskLuaInterface::Call<int, int>( pPlayer, pList, "get_max_award_option", vTaskID);

		if ( ((vSelect > max_option || vSelect < 1) && max_option != 0)
			|| (vSelect != 0 && max_option == 0) )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_MUTI_AWARD_ERROR );
			return false;
		}
	}

	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	LK_ASSERT( pProperty, return false );

	int nNum	= 0;
	// ��鴫��İ�������
	if ( vBagIndex >= 0 )
	{
		CItemObject* pObj = pProperty->GetBaggage()->GetItemObjPtr(vBagIndex);
		if (pObj == NULL)
		{
			LOG_ERROR("TASK", "load bag data failed  player entityID=%d  index=%d", pPlayer->GetEntityID(), vBagIndex );
			return false;
		}
		// ��lua���жϵ��׸ÿۼ���  �����-1 ��ʾ����Ҫ������� -2 ��ʾ����
		nNum = CTaskLuaInterface::Call<int, unsigned short, int, int>( pPlayer, pList, "check_recv_bag_item", vTaskID, pObj->GetItemID(), pObj->GetItemNum() );
		if (nNum > (int)pObj->GetItemNum())
		{
			LOG_ERROR("TASK", "clear more?? player = %s", pPlayer->GetCharNameShow() );
			return false;
		}

		if (nNum == -1)
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_BAD_RECV_ITEM );
			Send2ClientOprFailed( pPlayer );
			return false;
		}
		else if (nNum == -2)
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_LESS_RECV_ITEM );
			Send2ClientOprFailed( pPlayer );
			return false;
		}
		else if (nNum == 0)
		{
			LOG_ERROR("TASK", "check_recv_bag_item return 0");
			return false;
		}
	}
	else // û�зŶ�����ȥ �ж��ǲ���ȷʵҪ�Ŷ���
	{
		if (CTaskLuaInterface::Call<int, unsigned short>(pPlayer, pList, "is_need_give_item", vTaskID ) == 1 ) // Ҫ�Ŷ�����
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_BAD_RECV_ITEM );
			Send2ClientOprFailed( pPlayer );
			return false;
		}
	}

	//  ȡ����������, ��������Ʒ�ڳ����д�������lua�д���
	//  �жϽ�����Ҫ�Ŀռ��Ƿ�����
	if ( !TestAwardNeedSpace(pPlayer, vTaskID, vSelect) )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_NOSPACE );

		return false;
	}

	DisposeEndTask(pPlayer, vTaskID, false, bIsAuto, vSelect, vBagIndex, nNum );

	return true;
	
}

bool CTaskModule::DisposeEndTask( CEntityPlayer* pPlayer, unsigned short vTaskID, bool bIsTeamMember, bool bIsAuto, int vSelect, int nIndex , int nClearNum )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false);

	CTask* pTask = pList->GetTask(vTaskID);
	LK_ASSERT( pTask!=NULL, return false);

	if ( (pTask->mExFlags&EXFLAG_PROTECT_FLAG_TASK) == EXFLAG_PROTECT_FLAG_TASK ) // �������� ȡ��ע��
	{
		mNpcMonitor.RemoveGlobalTaskAction( pTask->GetFirstParamByEvent(EVENT_PROTECT_FLAG)
			, pPlayer, pTask->mTaskID );
	}

	// �ɵ���ʱ��
	if( pTask->mTimerID != INVALID_OBJ_ID )
	{
		int tRet = pPlayer->GetTimerReciver()->ClearTimer( pTask->mTimerID );
		if ( tRet != 0 )
			LOG_ERROR("TASK", "OnTaskFailed del2 timer returned %d, timerid=%d taskid=%d"
			, tRet, pTask->mTimerID, vTaskID );

		pTask->mTimerID = INVALID_OBJ_ID;
		pTask->mGameTimeLeft = -1;
	}

	// �������

	// �������ӻ�����
	int nAwardNum=0;
	if (IsTeamLoop(vTaskID) == 1)
	{
		// ����
		pList->PlusTodayTeamLoopNum();

		// �����20���� �����⽱��
		//if (pList->GetTodayTeamLoopNum() == MAX_TEAMLOOP_EVERYDAY )
		CTaskLuaInterface::Call<int, int, int, int, int, int>(pPlayer, pList, "do_extra_awards", TEAMLOOP_ENDLOOP, vTaskID, pList->GetTodayTeamLoopNum(), 0, 0 );

		if (!bIsTeamMember)
		{
			//int nEndNum=0;
			// ���ǲ��Ƕӳ�
			CTeam* tpTeam = ( CTeam* ) CSceneObjManager::GetSingleton().GetObject(CTeamModule::GetSingleton().InTeam( pPlayer->GetCharID() ) );
			if (tpTeam != NULL && tpTeam->GetHeaderID() == pPlayer->GetCharID())
			{
				// ������Ա
				int nTeamMember[TEAMNUM] = {0}; // ��ɫID
				int nMemberNum=0;
				int nAwardMember[TEAMNUM] = {0}; // ʵ��ID
				tpTeam->GetMemberList(nTeamMember, TEAMNUM, nMemberNum);
				LK_ASSERT(nMemberNum <= TEAMNUM, return false );
				for (int i = 0 ; i < nMemberNum; ++i )
				{
					CEntityPlayer* tpMember = CSceneLogic::GetSingleton().GetPlayerByCharID(nTeamMember[i]);
					if (tpMember == NULL)
					{
						continue;
					}
					if (tpMember->GetEntityID() == pPlayer->GetEntityID())
						continue;

					if ( pPlayer->IsWithinDistance( tpMember, TEAM_VALID_DISTANCE ) == false )
					{
						continue;
					}

					if ( tpMember->IsAlive() == false )
					{
						continue;
					}

					CTaskList* tpList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(tpMember->GetTaskToken( ));
					LK_ASSERT( tpList,  continue );
					CTask* pThisTask = tpList->GetTask(vTaskID);
					if (pThisTask != NULL && pThisTask->mTaskProgress == TASK_COMPLETE)
					{
						if (DisposeEndTask(tpMember, vTaskID, true))
						{
							//++nEndNum;
							nAwardMember[nAwardNum++] = tpMember->GetEntityID();
						}
					}
				}

				// ������񶼽����ˡ�����ʼ�����⽱�� �������û����
				for (int i = 0; i < nAwardNum; ++i)
				{
					CEntityPlayer* tpMember = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(nAwardMember[i]);
					if (tpMember == NULL)
					{
						continue;
					}

					CTaskList* tpList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(tpMember->GetTaskToken( ));
					LK_ASSERT( tpList,  continue );

					CTaskLuaInterface::Call<int, int, int, int, int, int>(tpMember, tpList, "do_extra_awards", TEAMLOOP_TEAMEXTRA, vTaskID, nAwardNum+1, 0, 0 );
				}
			}
		}
	}

	int tTaskType = GetTaskType(vTaskID);
	if ( tTaskType == TASKTYPE_LOOP )
	{
		// �����������е�
		int tWeekTimes = pList->mLoopTaskData.OnCompletedTask(vTaskID);
		if ( tWeekTimes > 0 ) // �ոռ����˱��ܵ�����ɴ��� ȥlua����Ӧ���� ����
		{
			int tRet = CTaskLuaInterface::Call<int, unsigned short, int>( pPlayer, pList, "on_weekly_end_loop_added", vTaskID, tWeekTimes );
			if ( tRet == 1 )
			{
				CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_ON_END_A_NEW_LOOP );
			}
		}

		FireEvent( pPlayer, EVENT_COMPLETE_LOOP, SPECIALID_COMPLETELOOPTASK );
	}

	bool bIsStorageTask = false;
	if ( tTaskType == TASKTYPE_STORAGE )
	{
		pList->mStorageTaskMgr.OnEndTask(vTaskID);
		// ˢ�¿�����
		pList->RefreshTasks(REFRESH_BACK);
		// fireevent
		FireEvent( pPlayer, EVENT_COMPLETESTORAGETASK, SPECIALID_COMPLETESTORAGE );
		bIsStorageTask = true;
	}

	//  ˢ��һ�����ϵ�����Ū������״̬�ı��(������Զ���ɵľ����ˣ�����Χ����µ�)
	if (! bIsAuto)
	{
		FireEvent( pPlayer, EVENT_TASKCHANGE, vTaskID );
	}

	// ������ɺ�����������ظ���ɣ���Ҫ�ڰ������������б�
	if(! IsTaskRepeateAble(vTaskID))
	{
		LOG_DEBUG("player %s set taskend:%d", pPlayer->GetCharNameShow(), vTaskID);
		pList->SetEnd(vTaskID);
	}
	else
	{
		pList->SetEndTime(vTaskID,time(0));
	}

	CMessageTaskEndNotice msg;
	msg.set_taskid(vTaskID);
	if ( bIsStorageTask )
	{
		StorageTaskStruct* tpStorage = msg.mutable_storagetask();
		GetStorageTaskData( pPlayer, pList, tpStorage );
	}
	CMessage   tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_TASKEND);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );

	// ����ǻ���������һ��
	if ( tTaskType == TASKTYPE_LOOP && CTaskLuaInterface::Call<bool,unsigned short>(pPlayer, pList, "is_the_end_loop", vTaskID)) 
	{
		pList->mLoopTaskData.SetEndLoopData( );
		CTaskLuaInterface::Call<int, int, int>( pPlayer, pList, "init_loop_tasks" , pPlayer->GetMetier(), pPlayer->GetLevel() ); // ˢ�»�����
		FireEvent( pPlayer, EVENT_ENDLOOP, 0 );
	}

	// ����ǽ������� ���������״̬
	if ( tTaskType == TASKTYPE_TRAGEDY )
	{
		lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, unsigned short>( pPlayer, pList, "get_next_tragedy", vTaskID );
		unsigned short tNextID = ret.get<unsigned short>("task_id");
		int			   tIndex  = ret.get<int>("index");

		if (tNextID == 0)
		{
			LOG_ERROR("TASK", "next tragedy = 0?? this id=%d", vTaskID );
		}
		else
		{
			pList->mTragedyTaskMgr.SetNextTask( tIndex, tNextID );
			LOG_DEBUG("TASK", "player%s save next index=%d, nextid=%d", pPlayer->GetCharNameShow(), tIndex, tNextID );
			int tState = TRAGEDY_ACTIVE;
			if (tNextID == vTaskID)
			{
				tState = TRAGEDY_COMPLETED; // ���������
				// ��������ɵĽ�������
				pList->mTragedyTaskMgr.PlusCompleted();
				// �����⽱�� ������� ����1 ���򷵻�0
				if ( 1 == CTaskLuaInterface::Call<int, int>( pPlayer, pList, "on_completed_tragedy", pList->mTragedyTaskMgr.GetCompleted() ) )
				{
					CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_ON_END_TRAGEDY10);
				}
			}
			pList->mTragedyTaskMgr.SetState(tIndex, (enTragedyTaskState)tState);
			SendTragedyInfo2Client( pPlayer, &tIndex, &tNextID, &tState, 1 );
		}
	}

	// ������������� ���޸�״̬
	if ( tTaskType == TASKTYPE_CHAIRMAN )
	{
		// �޸�״̬
		pList->mChairManTaskMgr.OnTaskEnd( ) ;
		
		// ���⽱��
		lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, int, int>( pPlayer, pList, 
			"on_completed_chairmantask", pList->mChairManTaskMgr.GetCurID(), pList->mChairManTaskMgr.GetCompleteNum() ) ;
		if ( ret.get<bool>("is_finished") )
		{
			// ȫ������� ��Ϊ�ɽ���״̬
			pList->mChairManTaskMgr.ResetTasks( 0 ) ;
			//ResetChairManTasks(pPlayer, pList->mChairManTaskMgr.GetCurID() );
		}

		if ( ret.get<bool>("is_awarded") ) // ����н����ˡ�����
		{
			CPropertyModule::GetSingleton().SendProErrorNotice(pPlayer, ERROR_TASK_CHAIRMAN_AWARDED );
		}
	}
	if (tTaskType == TASKTYPE_PUBLISH)
	{
		pList->SetPublishTaskState(vTaskID,FINISHED_TASK, GetTaskPublishType(vTaskID));  // �ı����񷢲�״̬
	}

	// ��LUA���������Ҫ�ľ����Ǯ(�Ѿ����ٷ��ؽ�Ǯ���飡)
	lua_tinker::table data_ret = CTaskLuaInterface::Call<lua_tinker::table, unsigned short>( pPlayer, pList, "get_task_end_info", vTaskID );
	
	// ��ȡ���尲���Ƚ���
	CFamilyModule::GetSingleton().OnTaksChangeStability( vTaskID, pPlayer );

	// ȡ����ID �����Ϊ0  Ҫ������
	int tGroupID = data_ret.get<int>("groupid");
	if ( tGroupID != 0 )
	{
		pList->mTaskGroupMgr.OnEndOneTask( tGroupID );
	}

	// ��������״̬ Ϊ�����µ����̲�����
	pTask->mTaskProgress = TASK_TOEND;

	// ɾ������������ռ��ĵ���
	DropCompleteItems(pPlayer, vTaskID, false, nIndex , nClearNum );

	// �����������++
	CPropertyPlayer* pPro = (CPropertyPlayer*)pPlayer->GetProperty();
	LK_ASSERT(pPro!=NULL, return false);
	pPro->SetCompletedTaskNum(pPro->GetCompletedTaskNum()+1);

	//  ��������б����Ƴ�
	pList->RemoveTask(vTaskID);
	int vColor = pList->GetTaskColor(vTaskID);

	// �üӵ����������ٽ��� ����౶�Ͳ�����
	// ��ע�⣡�����������������Ϊ�������ִ�д��Ϳ��������
	PERF_FUNC("DoTaskAwards", DoTaskAwards( pPlayer, pList, vTaskID, vSelect,vColor) );
	if (IsTeamLoop(vTaskID) == 1)
		CTaskLuaInterface::Call<int, int, int, int, int, int>(pPlayer, pList, "do_extra_awards", TEAMLOOP_TEAMEXTRA, vTaskID, nAwardNum+1, 0, 0 );

	for (int i = 0; i < TASK_LIST_SIZE; ++ i)
	{
		if (pList->mRememberRefreshNum[i].rTaskID == vTaskID)
		{
			pList->RemoveTaskColor(vTaskID);
			Send2ClientRemoveTaskColor(pPlayer, vTaskID, vColor);
			break;
		}
	}

	return true;
}

// ���ͽ������������Ϣ���ͻ���
void CTaskModule::SendTragedyInfo2Client( CEntityPlayer* pPlayer, int *anIndex, unsigned short *asNextID, int *anState, int n, int nIsFirst )
{
	CMessageTragedyTaskUpdateNotice msg;
	CMessage   tMessage;

	for (int i=0; i<n; ++i)
	{
		TragedyStruct *pSt = msg.add_tragedyinfo();
		pSt->set_nexttragedytask( asNextID[i] );
		pSt->set_tragedyindex( anIndex[i] );
		pSt->set_tragedystate( anState[i] );
	}

	msg.set_islogin(nIsFirst);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_TRAGEDYTASKUPDATE);
	tMessage.set_msgpara((uint32_t) &msg);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}

// ������
bool CTaskModule::DoTaskAwards(CEntityPlayer* pPlayer, CTaskList* pList,unsigned short vTaskID, unsigned short vSelect,int vTaskColor)
{
	CTaskLuaInterface::mCurTaskID = vTaskID;
	return CTaskLuaInterface::Call<bool, unsigned short, unsigned short, int>(pPlayer, pList, "do_task_awards", vTaskID, vSelect, vTaskColor);
}

bool CTaskModule::DoTaskObtAwards( CEntityPlayer* pPlayer, CTaskList* pList, unsigned short vTaskID)
{
	return CTaskLuaInterface::Call<bool, unsigned short, unsigned int>( pPlayer, pList, "do_task_obt_awards", vTaskID, pPlayer->GetEntityID() );
}

bool CTaskModule::GetTaskExtendItems(CEntityPlayer* pPlayer, unsigned short vTaskID, CItemsPair& vItemsPair)
{
	LK_ASSERT( pPlayer , return false );

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );

	// ��������Ľ�����ƷҲ������������
	lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, unsigned short>( pPlayer, pList, "get_items_extend", vTaskID);
	
	int n = luaL_getn(L, -1);
	for (int i = 1; i<= n; ++i)
	{
		lua_rawgeti(L, -1, i);
		lua_tinker::table inside = lua_tinker::pop<lua_tinker::table>(L);

		int id = inside.get<int>("id");
		int m =  inside.get<int>("n");
		
		vItemsPair.push_back( std::make_pair<int, int>( id, m));
	}

	return true;
}

bool CTaskModule::TestAwardNeedSpace(CEntityPlayer* pPlayer, unsigned short vTaskID, unsigned short vSelectID)
{
	CItemsPair vItemsPair;
	bool bRet = false;

	PERF_FUNC( "GetTaskAwardItems", bRet = GetTaskAwardItems( pPlayer, vTaskID, vItemsPair, vSelectID) );

	if (bRet)
	{
		unsigned short n = vItemsPair.size();
		int vItemID[24] = {0};
		int vNumber[24] = {0};

		if (n > 0 && n <= 24)
		{
			CItemsPair::iterator iter = vItemsPair.begin();

			for(int i = 0; iter != vItemsPair.end(); ++iter,++i)
			{
				vItemID[i] = iter->first;
				vNumber[i] = iter->second;
			}

			CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
			return pProperty->TestBaggageSpace(&vItemID[0], &vNumber[0], n);
		}
		else
		{
			return n == 0;
		}
	}

	return true;
}

// ����NPC ģ��ID  �������0�� ��Ҫ��֤  ��Ϊ�Ǵӽ���������� ��������0 
bool CTaskModule::IsTaskAcceptable( CEntityPlayer* pPlayer, CTaskList* pTaskList, unsigned short vTaskID, int vNpcTempID )
{
	return CTaskLuaInterface::Call<bool, unsigned short, int>(pPlayer, pTaskList, "check_acceptable", vTaskID, vNpcTempID );
}

// �򵥰汾�ļ�������Ƿ�ɽ� ����麯������  Ŀǰֻ������������
bool CTaskModule::IsTaskAcceptableExpress( CEntityPlayer* pPlayer, CTaskList* pTaskList, unsigned short vTaskID )
{
	return CTaskLuaInterface::Call<bool, unsigned short>(pPlayer, pTaskList, "check_acceptable_express", vTaskID );
}

bool CTaskModule::GetTaskAwardItems( CEntityPlayer* pPlayer, unsigned short vTaskID, CItemsPair& vItemsPair, unsigned short vSelectID)
{
	LK_ASSERT( pPlayer , return false );

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );
	int vColor = pList->GetTaskColor(vTaskID);
	lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, unsigned short, unsigned short>( pPlayer, pList, "get_awards_items", vTaskID, vSelectID,vColor);
	
	int n = luaL_getn(L, -1);
	for (int i = 1; i<= n; ++i)
	{
		lua_rawgeti(L, -1, i);
		lua_tinker::table inside = lua_tinker::pop<lua_tinker::table>(L);

		int id = inside.get<int>("id");
		int m =  inside.get<int>("n");
		
		vItemsPair.push_back(std::make_pair<int, int>(id, m));
	}

	return true;
}
bool CTaskModule::GetTaskCompleteItems(CEntityPlayer* pPlayer, unsigned short vTaskID, CItemsPair& vItemsPair)
{
	LK_ASSERT( pPlayer , return false );

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );

	lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, unsigned short>( pPlayer, pList, "get_collect_items", vTaskID);
	
	int n = luaL_getn(L, -1);
	for (int i = 1; i<= n; ++i)
	{
		lua_rawgeti(L, -1, i);
		lua_tinker::table inside = lua_tinker::pop<lua_tinker::table>(L);

		int id = inside.get<int>("id");
		int n =  inside.get<int>("n");
		
		vItemsPair.push_back( std::make_pair<int, int>( id, n));
		LOG_DEBUG( "TASK", "get complete item %d : %d->%d ", i, id, n);
	}
	
	return true;
}

// �����Ʒ ���ж���û�У�û��ֱ�ӷ���false
bool CTaskModule::DropItems(CEntityPlayer* pPlayer, const CItemsPair& vItemsPair, int nTaskID )
{
	// ���
	for ( CItemsPair::const_iterator iter = vItemsPair.begin(); iter != vItemsPair.end(); ++iter )
	{
		if ( iter->first != 0 )
		{
			uint64_t ullGUID = 0;
			bool tBind = false;
			if ( CPropertyModule::GetSingleton( ).PlayerRemoveItemByID( pPlayer, iter->first, iter->second, tBind, &ullGUID) == 0)
			{
				LogEventLostItemByAbortTask(pPlayer, ullGUID, iter->first, iter->second, nTaskID);
			}
		}
	}
	return true;
}

void CTaskModule::DropCompleteItems(CEntityPlayer* pPlayer, unsigned short vTaskID, bool aborted, int nIndex , int nClearNum)
{
	//  ɾ�����񷢷ŵĵ��߻������������Ҫ���������,ֻ��ɾ����������еĵ���
	//const int COMPLETEITEMSIZE = 8;

	CItemsPair vItemsPair;
	PERF_FUNC( "GetTaskCompleteItems", GetTaskCompleteItems( pPlayer, vTaskID, vItemsPair) );

	LOG_DEBUG( "TASK", "get clear items total=%d", vItemsPair.size());

	//if((int)vItemsPair.size() > COMPLETEITEMSIZE)
	//{
	//	return;
	//}

	CItemsPair::iterator iter = vItemsPair.begin();

	// ȡ����������ص������Ҫ����Ʒ
	for (; iter != vItemsPair.end(); ++iter )
	{
		if ( iter->first != 0 )
		{
			CTplItem* tpItemTpl = (CTplItem*) CDataStatic::SearchTpl( iter->first );
			if ( tpItemTpl != NULL )
			{
				//  ������ʱ��ֻ���������ߣ�
				if ( IS_TASK_ITEM( tpItemTpl ) || !aborted )
				{
					LOG_DEBUG( "TASK", "clear item , ID=%d, num=%d", iter->first, iter->second );
					uint64_t ullGUID = 0;
					bool tBind = false;
					int nLeft = CPropertyModule::GetSingleton( ).PlayerRemoveItemByID( pPlayer, iter->first, iter->second, tBind, &ullGUID);
					if ( aborted )
					{
						if ( iter->second - nLeft  != 0)
						{
							LogEventLostItemByAbortTask( pPlayer, ullGUID, iter->first, iter->second - nLeft, vTaskID);
						}
					}else
					{
						if ( iter->second - nLeft  != 0)
						{
							LogEventLostItemByEndTask( pPlayer, ullGUID, iter->first, iter->second - nLeft, vTaskID);
						}
					}
				}
			}
		}
	}

	// �����ҽ��Ŀ�ѡ��Ʒ
	if ( nIndex >= 0)
	{
		CItemObject* tpSrcItem = ((CPropertyPlayer*) pPlayer->GetProperty())->GetBaggage( )->GetItemObjPtr( nIndex );

		if ( tpSrcItem != NULL)
		{
			uint64_t ullGUID = tpSrcItem->GetGUID();
			int nItemID = tpSrcItem->GetItemID();
			if (CPropertyModule::GetSingleton().PlayerRemoveItem( pPlayer, (unsigned int)nIndex, nClearNum) ==0)
			{
				LogEventLostItemByEndTask(pPlayer, ullGUID, nItemID, nClearNum, vTaskID);
			}else
			{
				LOG_ERROR("TASK",  "clear task(id=%d) item(%d) num(%d) from (roleid=%d) error", 
							vTaskID, nItemID, nClearNum, pPlayer->GetCharID());
			}
		}
	}

}

// =========================================================�������ӿ�====================
void CTaskModule::UpdateTaskWrapper( CEntityPlayer* pPlayer, unsigned int nEventID, unsigned int nParam, int nSend )
// ����ӿڽ������ڸ���������ϵ������������ж��������仯��ʱ�����
// TODO: ����task id , tick id �����Ч�ʣ���
// ���ӿ�ֻ�ܹ�fireevent����
{
	LK_ASSERT( pPlayer , return );

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );


	int tTaskNum = pList->mTaskNumber;

	std::vector<unsigned short> nAutoEndIDs;
	for ( int i = 0; i < tTaskNum; i ++ )
	{
		bool bAutoEnd = false;
		if ( pList->mTaskList[i].IsEventTick( nEventID, nParam ) || nEventID <= 0 )
		{
			if ( pList->mTaskList[i].mTaskProgress == TASK_TOEND || pList->mTaskList[i].mTaskProgress == TASK_FAILED ) // ����״̬ ��ʧ��״̬ ������
				continue;

			// �����������BUG��������������� ��������  �Ͳ���ˢ״̬��
			int nNpcProtect = pList->mTaskList[i].GetFirstParamByEvent(EVENT_PROTECT_FLAG);
			if ( nNpcProtect != 0 && pList->mTaskList[i].mTaskProgress == TASK_COMPLETE )
				continue;

			// ��¼��־
			LogEventTaskAction( pPlayer, pList->mTaskList[i].mTaskID, EM_TASK_ACTION, nEventID, nParam );

			if ( (nEventID & EVENT_MASK_REGINTASK ) == EVENT_MASK_REGINTASK )
			{
				// ���ؼ����Ժ��Ѿ����˵�����
				int tRet = CTaskLuaInterface::Call<int, CTask*, unsigned int, int>( pPlayer, pList, "set_colletor_value", &(pList->mTaskList[i]), nParam, 1 ); 
				int nNotifyFlag = 0; // ֪ͨ�ͻ��˵������������ͱ�־
				if ( nEventID == EVENT_KILLFOREIGNER )
					nNotifyFlag = CONDITION_KILL_FOREIGNER;
				else if ( nEventID == EVENT_COMPLETESTORAGETASK )
					nNotifyFlag = CONDITION_COMPLETE_STORAGE;
				else if ( nEventID == EVENT_COMPLETE_LOOP )
					nNotifyFlag = CONDITION_COMPLETE_LOOP;
				else if ( nEventID == EVENT_COMPLETE_QUESTION )
					nNotifyFlag = CONDITION_COMPLETE_QUESTION;

				if ( nNotifyFlag != 0 )
				{
					CMessageUpdateTaskConditions msg;
					TaskCondition* pCondition = msg.add_contions();
					pCondition->set_taskid( pList->mTaskList[i].mTaskID );
					pCondition->set_tempid( nNotifyFlag );
					pCondition->set_num( tRet);
					pCondition->set_condition( CONDITION_OGREDIE );
					SendUpdateConditions2Client( pPlayer, &msg );
				}
			}
			PERF_FUNC("UpdateTaskProgress", UpdateTaskProgress(pPlayer, &(pList->mTaskList[i]), bAutoEnd, nSend, nEventID, nParam ) );

			if ( bAutoEnd ) // �������Ҫ�Զ����
				nAutoEndIDs.push_back( pList->mTaskList[i].mTaskID );
		}
	}

	for ( std::vector<unsigned short>::iterator it = nAutoEndIDs.begin(); it != nAutoEndIDs.end(); ++it )
	{
		PERF_FUNC( "PlayerEndTask", PlayerEndTask( pPlayer, *it, -100, true ) );
		LogEventPlayerEndTask( pPlayer, *it);
	}

}
void CTaskModule::OnPlayerChangeMoney(CEntityPlayer* pPlayer)
{
	FireEvent( pPlayer, EVENT_CHANGEMONEY );
}
void CTaskModule::OnTaskObtainItem( CEntityPlayer* pPlayer, unsigned int vItemID, unsigned short vNumber )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	CTplItem *tpItem = (CTplItem *)CDataStatic::SearchTpl( vItemID );
	LK_ASSERT( tpItem, return);
	if ( IS_TASK_ITEM( tpItem ) )
	{
		for ( int i = 0; i < pList->mTaskNumber; i ++ )
		{
			if ( pList->mTaskList[i].IsEventTick( EVENT_ITEMCHANGE, vItemID ) )
			{
				if ( pList->mTaskList[i].mWatchEventN <= vNumber )
				{
					pList->mTaskList[i].mWatchEventN = 0;
				}
				else
				{
					pList->mTaskList[i].mWatchEventN -= vNumber;
				}
				break; // ������Ʒ�����ظ�����
			}
		}
	}

	FireEvent( pPlayer, EVENT_ITEMCHANGE, vItemID );
}

// ��ҵ��NPC��ʱ��
void CTaskModule::OnPlayerClickNpc( CEntityPlayer* pPlayer, int vEntityID)
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	CEntity* pEntity = CSceneLogic::GetSingleton().GetEntity(vEntityID);
	LK_ASSERT( pEntity, return );
	if( pEntity->IsFunNpc() || pEntity->IsOgre() ) 
	{	
		pList->SetTalkNpcEntityID(vEntityID);
		CEntityNpc* pEntityNpc	   = (CEntityNpc*) pEntity;
		CPropertyNPC* pPropertyNpc = (CPropertyNPC*)pEntityNpc->GetProperty();

		CTemplateNpc* tpNpcTpl = (CTemplateNpc*) CDataStatic::SearchTpl( pPropertyNpc->GetPropertyTempID() );
		LK_ASSERT ( tpNpcTpl != NULL, return );

		// �жϻʰ�����
		if ( tpNpcTpl->mStorageTaskNPC == 1 ) // �ǻʰ�NPC
		{	
			SendStorageTaskList2Client( pPlayer, pList, vEntityID );
			pList->SetTalkNpcEntityID(0);
			return;
		}

		CMessageNpcTaskListNotice msg;
		NpcTaskList* tpList = msg.mutable_list();
		CMessage   tMessage;
		tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_NPCTASKLIST);

		bool bRet = false;
		PERF_FUNC("GetNpcTaskList", bRet = GetNpcTaskList( pPlayer, pList, pEntityNpc->GetNpcID( ), tpList) );

		if (bRet)
		{
			LOG_DEBUG( "TASK", "prepear send player NPC task list, NPC ID=%d extend=%d, back=%d"
				, tpList->npcid(), tpList->extendnumber(), tpList->callbacknumber() );

			tMessage.set_msgpara((uint32_t) &msg);
			CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
		}
		else
		{
			// ��¼ȡ��NPC�����б�ʧ����Ϣ
			LOG_ERROR( "TASK", "error in get npc task list, npcid=%d", pEntityNpc->GetNpcID( ));
		}


		if ( pPropertyNpc == NULL )
		{
			LOG_ERROR("TASK", "npc property is null, line=%d", __LINE__ );
			pList->SetTalkNpcEntityID(0);
			return;
		}
		pList->SetTalkNpcEntityID(0);
	}
}

// ���Ϳ������б�
void CTaskModule::SendStorageTaskList2Client( CEntityPlayer* pPlayer, CTaskList* pList, int vEntityID )
{
	// �жϻʰ�����
	CEntity* pEntity = CSceneLogic::GetSingleton().GetEntity(vEntityID);
	if ( pEntity == NULL ) // ������п��ܵ�
		return;

	if( pEntity->IsFunNpc() == false )
	{
		return ;
	}

	CPropertyNPC* pPropertyNpc = (CPropertyNPC*)pEntity->GetProperty();

	if ( pPropertyNpc == NULL )
	{
		LOG_ERROR("TASK", "npc property is null, line=%d", __LINE__ );
		return;
	}

	CTemplateNpc* tpNpcTpl = (CTemplateNpc*) CDataStatic::SearchTpl( pPropertyNpc->GetPropertyTempID() );
	if ( tpNpcTpl == NULL )
		return ;

	if ( tpNpcTpl->mStorageTaskNPC == 1 && pPlayer->GetLevel() >= tpNpcTpl->mDownLevel && pPlayer->GetLevel() <= tpNpcTpl->mUpLevel )
	{
		CMessageNpcStorageTaskListNotice msg2;
		CMessage   tMessage;
		NpcTaskList* tpList2 = msg2.mutable_list();
		pList->GetStorgeTaskList( tpList2, tpNpcTpl->mStorageTaskID );
		tpList2->set_npcid( pPropertyNpc->GetPropertyTempID() );
		tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_NPCSTORAGETASKLIST);
		tMessage.set_msgpara((uint32_t) &msg2);
		CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
	}
}


void CTaskModule::OnTaskRemoveItem (CEntityPlayer* pPlayer, unsigned int vItemID, unsigned short vNumber )
{
	FireEvent( pPlayer,  EVENT_ITEMCHANGE, vItemID );
}


// ע�������¼�
void CTaskModule::RegTaskEventTick( CTask* pTask )
{
	CTaskLuaInterface::Call<bool, CTask*>( NULL, NULL, "reg_task_tick", pTask ); // ����϶�֮ǰ���ù���
}


// ע��������ȼ�����
void CTaskModule::RegLevelTask( unsigned short usLevel, unsigned short usTaskID )
{
	enTaskType tType = (enTaskType)GetTaskType(usTaskID ) ;
	if( usLevel > 0 && usLevel <= MAX_GRADE )
	{
		if (tType==TASKTYPE_MAIN)
			mLevelTasks[0][ usLevel ][mLevelTasksN[0][ usLevel ]++] = usTaskID ;
		else if (tType==TASKTYPE_LATERAL)
			mLevelTasks[1][ usLevel ][mLevelTasksN[1][ usLevel ]++] = usTaskID ;
		else if (tType==TASKTYPE_WEST)
			mLevelTasks[2][ usLevel ][mLevelTasksN[2][ usLevel ]++] = usTaskID ;
	}
}

// ע������
void CTaskModule::RegDropTable( unsigned short usTaskID, int nOgreID, int nItemID, int n, int nP, int nMaxn )
{
	mTaskDropMgr.RegDrop( usTaskID, nOgreID, nItemID, n, nP, nMaxn );
}


// ���ⲿ���õĻ��NPC TIP�ӿ�
unsigned short CTaskModule::GetNpcTip( CEntityPlayer* pPlayer, int nNpcTempID, int nNpcEntityID )
{
	if ( pPlayer == NULL )
		return TASKTIP_NONE;

	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	if ( pProperty == NULL )
		return TASKTIP_NONE;

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return TASKTIP_NONE );

	unsigned short tip = TASKTIP_NONE;
	
	PERF_FUNC("GetNpcTip", tip = GetNpcTip( pPlayer, nNpcTempID, pList, nNpcEntityID ) );
	return tip;

}

// ����ͷ��
unsigned short CTaskModule::GetNpcTip( CEntityPlayer* pPlayer, int nNpcID, CTaskList* pTaskList, int nNpcEntityID )
{
	LK_ASSERT( pPlayer !=NULL,   return TASKTIP_NONE );
	LK_ASSERT( pTaskList !=NULL, return TASKTIP_NONE );

	CEntityNpc* tpEntityNpc = dynamic_cast<CEntityNpc*>(CSceneObjManager::GetSingletonPtr()->GetObject( nNpcEntityID ) );
	if ( tpEntityNpc == NULL )
		return TASKTIP_NONE;

	// ֻ���Ѻò�����ͷ��
	if ( !( tpEntityNpc->IsFunNpc() && tpEntityNpc->IsFriendlyTo(pPlayer) ) )
	{
		return TASKTIP_NONE;
	}

	pTaskList->SetTalkNpcEntityID(nNpcEntityID);
	unsigned short tip = CTaskLuaInterface::Call<unsigned short, int>( pPlayer, pTaskList, "get_npc_tip", nNpcID );

	if ( tip == TASKTIP_ACTIVE || tip == TASKTIP_COMPLETE )
	{
		pTaskList->SetTalkNpcEntityID(0);
		return tip;
	}

	CTemplateNpc* tpNpcTpl = (CTemplateNpc*) CDataStatic::SearchTpl( nNpcID );
	if ( tpNpcTpl == NULL )
	{
		pTaskList->SetTalkNpcEntityID(0);
		return tip;
	}

	// �жϻʰ�����
	if ( tpNpcTpl->mStorageTaskNPC == 1 && pPlayer->GetLevel() >= tpNpcTpl->mDownLevel && pPlayer->GetLevel() < tpNpcTpl->mUpLevel ) // ˢ�»ʰ�����ͷ��
	{	
		if ( pTaskList->mStorageTaskMgr.GetTaskNum() > 0 || ( pTaskList->mStorageTaskMgr.GetTaskNum() == 0 && pTaskList->mStorageTaskMgr.GetGotNum() == 0 ) )
		{
			pTaskList->SetTalkNpcEntityID(0);
			return TASKTIP_ACTIVE;
		}
		else
		{
			pTaskList->SetTalkNpcEntityID(0);
			return TASKTIP_NONE;
		}
	}

	pTaskList->SetTalkNpcEntityID(0);
	return tip;
}

// �����¼�
void CTaskModule::FireEvent( CEntityPlayer* pPlayer, unsigned int nEventID, unsigned int nParam )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	//LOG_NOTICE("TASK", "player %s(%d) ticked %x ! param =%d", pPlayer->GetCharNameShow(), pPlayer->GetCharID(), nEventID, nParam);

	// �ж�ȫ������
	if ( ( nEventID & EVENT_MASK_GLOBAL ) == EVENT_MASK_GLOBAL && ( pList->mTickEvents & (1<<(nEventID&EVENT_MASK_ID)) )==0 )
	{
		return;
	}

	if ( ( nEventID & EVENT_MASK_RECORD ) == EVENT_MASK_RECORD ) // ��Ҫ��¼�¼���
	{
		pList->mEventMgr.RegEvent( nEventID, nParam );
	}

	if ( nEventID == EVENT_METIERCHANGE ) // תְҪ���⴦��
	{
		pList->mLoopTaskData.Clear(); // �������������
		ClearTasksByType( pPlayer, TASKTYPE_LOOP );
		CTaskLuaInterface::Call<int, int, int>( pPlayer, pList, "init_loop_tasks" , pPlayer->GetMetier(), pPlayer->GetLevel() ); // ˢ�»�����
	}

	if ( ( nEventID & EVENT_MASK_NOTIFY ) == EVENT_MASK_NOTIFY )
	{
		PERF_FUNC( "UpdateTaskWrapper", UpdateTaskWrapper( pPlayer, nEventID, nParam, 1 ) );
	}
	else
	{
		PERF_FUNC( "UpdateTaskWrapper", UpdateTaskWrapper( pPlayer, nEventID, nParam, 0 ) );
	}
}

// ���ʹ���������  ���ش�����
int CTaskModule::UseTaskItem( CEntityPlayer* pEntity, unsigned short vIndex, int &tItemID )
{
	CPropertyPlayer* pProperty = (CPropertyPlayer*)pEntity->GetProperty();

	CItemObject* tpSrcItem = (CItemObject*)pProperty->GetTaskBaggage( )->GetItemObjPtr( vIndex );

	if ( tpSrcItem == NULL )
		return ERROR_ITEMNOTEXIST;
	CTplItemTask *tpItem = (CTplItemTask *)CDataStatic::SearchTpl( tpSrcItem->GetItemID() );
	tItemID = tpSrcItem->GetItemID();

	if ( tpItem == NULL )
		return ERROR_TPLNOTEXIST;
	else if ( IS_NOT_TASK_ITEM( tpItem ) )
		return ERROR_NOTTASKIITEM;
	else if ( tpItem->mUseTimes == 0 )
		return ERROR_CANTUSE;

	else if ( (!(tpItem->mX == -1 && tpItem->mY == -1)) && (!( pEntity->GetPosX() >= tpItem->mX - tpItem->mWide/2 && pEntity->GetPosX() <= tpItem->mX + tpItem->mWide/2 
		&& pEntity->GetPosY() >= tpItem->mY - tpItem->mHeight/2 && pEntity->GetPosY() <= tpItem->mY + tpItem->mHeight/2 ) ) )
		return ERROR_OUTOFRANGE;

	else if ( pEntity->GetMapID() != tpItem->mMapID )
		return ERROR_OUTOFRANGE;

	// TODO �����ж�
	//if ( pEntity->GetLineID() != pEntity->mCharProfile.mNationality )
	//	return ERROR_OUTNATION;
	
	if ( tpItem->mGiveItemID != 0 ) // Ҫ���ŵ���
	{
		int n = 1;
		if ( pProperty->TestBaggageSpace( &tpItem->mGiveItemID, &n, 1) )
		{
			CItemObject *pInsItemPile = 
				CPropertyModule::GetSingleton().PlayerInsertItem( pEntity, tpItem->mGiveItemID, 1, false );

			if (pInsItemPile != NULL)
			{
				LogEventGetItemByTaskItem(pEntity, pInsItemPile->GetGUID(), tpItem->mGiveItemID, 1, 0, tItemID);
			}
		}
		else
			return ERROR_BAGGAGEFULL;
	}

	tpSrcItem->SetUsedTimes( tpSrcItem->GetUsedTimes() + 1 );

	if ( tpSrcItem->GetUsedTimes() >= tpItem->mUseTimes ) // ������
	{
		// ɾ��1������
		uint64_t ullGUID = tpSrcItem->GetGUID();
		int nTplID = tpSrcItem->GetItemID();

		if (CPropertyModule::GetSingleton().PlayerRemoveItem( ( CEntityPlayer* )pEntity, vIndex, 1, NULL, true) == 0)
		{
			LogEventLostItemByUse(( CEntityPlayer* )pEntity, ullGUID, nTplID, 1);
		}

		tpSrcItem->SetUsedTimes( 0 );
	}
	FireEvent( pEntity, EVENT_USEITEM, tpSrcItem->GetItemID() );
	
	return SUCCESS;
}


// ����ʧ��(�����player������null)
void CTaskModule::OnTaskFailed( CEntityPlayer* pPlayer, unsigned short usTaskID, bool bForce, bool bRemoveNpcMonitor )
{
	if ( pPlayer == NULL )
		return;

	LOG_DEBUG("TASK", "in OnTaskFailed player: %s ", pPlayer->GetCharNameShow() ); 

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	CTask* pTask = pList->GetTask( usTaskID );
	if (pTask == NULL)
		return;

	// �������ǿ�ƴ��� ��ôֻ�з�BEGIN��ʱ���������
	if ( !bForce && pTask->mTaskProgress != TASK_BEGIN )
	{
		return;
	}

	if (bRemoveNpcMonitor)
	{
		if ( (pTask->mExFlags&EXFLAG_PROTECT_FLAG_TASK) == EXFLAG_PROTECT_FLAG_TASK ) // �������� ȡ��ע��
		{
			mNpcMonitor.RemoveGlobalTaskAction( pTask->GetFirstParamByEvent(EVENT_PROTECT_FLAG)
				, pPlayer, usTaskID );
		}	
	}

	// �ɵ�timer id
	if( pTask->mTimerID != INVALID_OBJ_ID )
	{
		int tRet = pPlayer->GetTimerReciver()->ClearTimer( pTask->mTimerID );
		if ( tRet != 0 )
			LOG_ERROR("TASK", "OnTaskFailed del timer returned %d, timerid=%d taskid=%d", tRet, pTask->mTimerID, usTaskID );

		LOG_DEBUG("TASK", "OnTaskFailed del timer returned %d, timerid=%d taskid=%d", tRet, pTask->mTimerID, usTaskID );
		pTask->mTimerID = INVALID_OBJ_ID;
		pTask->mGameTimeLeft = -1;
	}

	// �������ʧ�ܺ������Ե�,�����mCompleteTasks �б�
	if( IsTaskRetryAble(usTaskID) == 0 )
	{
		pList->SetFailed( usTaskID );
	}

	pTask->SetTaskProgress( TASK_FAILED );

#ifdef _FB_
	// ����Ϭ��Ľӿ�
	CRepetionModule::GetSingleton().EndTask( pPlayer, pTask->mTaskID, false );
#endif

	CMessageTaskFailNotice msg;
	msg.set_taskid( usTaskID );
	CMessage   tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_TASKFAIL);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );

	LOG_DEBUG("TASK", "in OnTaskFailed end player: %s ", pPlayer->GetCharNameShow() ); 
	// ���ʧ���Զ�������������
	if ( IsAutoAbort( usTaskID) == 1 )
	{
		PlayerAbortTask( pPlayer, usTaskID, false, true );
		LogEventPlayerCancelTask(pPlayer, usTaskID,2);
	}
}

// ���ʹ��RMB����ˢ�¿�����
bool CTaskModule::OnRefreshStorageTask( CEntityPlayer* pPlayer )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );

	int tRefreshLmt = lua_tinker::get<int>( L, "rmb_refresh_storage_lmt");
	if (pList->mStorageTaskMgr.GetTodayRMBTimes() >= tRefreshLmt)
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_MAX_RMB_REFRESH); 
		return false;
	}
	else
	{
		pList->mStorageTaskMgr.PlusTodayRMBTimes();
	}

	pList->RefreshTasks( REFRESH_RMB );
	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	SendStorageTaskList2Client( pPlayer, pList,  pProperty->GetTalkNpcEntityID() );
	return true;
}

// ˢ�¿����� ��������
int CTaskModule::RefreshStorageTask( unsigned short usTaskID, ETaskRefreshType etype, unsigned short* pOutArr )
{
	// �������luaȷ������Ҫ�ⲿ����
	lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, int, int>( NULL, NULL, "refresh_storge_tasks", usTaskID, etype );

	int n = luaL_getn( L, -1); //min( luaL_getn( L, -1), MAX_STORAGETASK_LIST_NUM );

	for ( int i = 1; i <= n; ++i)
	{
		lua_rawgeti(L, -1, i);
		unsigned short a = lua_tinker::pop<unsigned short>(L);
		*pOutArr++ = a; // lua_tinker::pop<unsigned short>(L);
		LOG_DEBUG("TASK", "refresh %d  style=%d", a, etype);
	}
	LOG_DEBUG("TASK", "refresh %d end! num=%d", usTaskID, n );
	return n;
}


// ��Ϭ��ӵĽӿ� �ж�ĳ�����Ƿ����������
bool CTaskModule::IsTaskOnPlayer( CEntityPlayer* pPlayer, unsigned short usTaskID )
{
	if ( pPlayer == NULL )
		return false;

	// ȡ����ҵ�ǰ�������б�
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );

	return (pList->GetTask(usTaskID) != NULL);
}

// �ɼ��ӿ� �����׵� �����Ƿ�ɹ�  ����ɼ���ֲ��ID
bool CTaskModule::OnCollectItem( CEntityPlayer* pPlayer, CTemplateCollect* pNpcTpl )
{
	LK_ASSERT(pPlayer, return false);
	LK_ASSERT(pNpcTpl, return false);

	bool bRet = false;

	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	
	// ���������ܵĲɼ�npc�ý��а����ж�
	
	if( pNpcTpl->mSkillType == CTemplateCollect::LIFESKILL_LIFESKILL )
	{	
		int tNum = 0;	
		int tCheckIDList[20] = { 0 };
		int tCheckNumList[20] = { 0 };	
		for ( int i = 0; i < (int)ARRAY_CNT( pNpcTpl->mItemID ) 
			&& i < (int)ARRAY_CNT( pNpcTpl->mItemProbality )
			&& tNum < ( int )ARRAY_CNT( tCheckIDList )
			&& tNum < ( int )ARRAY_CNT( tCheckNumList ); i++ )
		{
			if ( pNpcTpl->mItemID[ i ] <= 0 || pNpcTpl->mItemNum[ i ] <= 0 )
			{					
				break;
			}
			
			int tRand = RAND(SERVER_PERCENT_INT);
			if( tRand > pNpcTpl->mItemProbality[ i ] )
			{
				continue;
			}		
			
			tCheckIDList[ tNum ] = pNpcTpl->mItemID[ i ];
			tCheckNumList[ tNum ] = RAND(SERVER_PERCENT_INT) % pNpcTpl->mItemNum[ i ] + 1;
			tNum++;
		}

		if( tNum <= 0 )
		{
			return false;
		}

		
		if( !pProperty->GetBaggage()->Space( -1, tNum ) )
		{
			//CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_LIFESKILL_BAGFULLWHENCOLLECT );
			// ��������ռ䲻�������ӵ�����
			int tpCharIDList[TEAMNUM] = { 0 };
			tpCharIDList[0]	= pPlayer->GetCharID();
			for ( int i = 0; i < tNum; ++i )
			{  				
				CItemCreator tCreator( tCheckIDList[i], 5, pPlayer->GetPosX( ), pPlayer->GetPosY( ), tpCharIDList, NULL );				
				unsigned int tEntityID = 0;
				CMapModule::GetSingleton().CreateNpc( pPlayer->GetLineID(),
					pPlayer->GetMapID(),
					pPlayer->GetMapIndex(),
					&tCreator,
					tEntityID
					);
			}			
			return true;				
		}
		
		for ( int i = 0; i < tNum; ++i )
		{  				
			CItemObject *pInsItemPile = 
				CPropertyModule::GetSingleton().PlayerInsertItem( pPlayer, tCheckIDList[i], tCheckNumList[i], false );

			if (pInsItemPile != NULL)
			{
				LogEventGetItemByCollect( pPlayer, pInsItemPile->GetGUID(), 
					tCheckIDList[i], tCheckNumList[i], pPlayer->GetPosX(), pPlayer->GetPosY(),  0 );
			}
		}	
		return true;			
	}	

	// �ж���û���������	
	for ( int i = 0 ; i < MAX_COLLECT_TASKS; ++i )
	{
		if (pNpcTpl->mTaskID[i] != 0 && IsTaskOnPlayer(pPlayer, pNpcTpl->mTaskID[i]))
		{
			CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
			LK_ASSERT( pList,  return false );
			if ( CTaskLuaInterface::Call<int, unsigned short, int>(pPlayer, pList,"get_collect_items_num_by_id", pNpcTpl->mTaskID[i], pNpcTpl->mItemID[i] )
				- pProperty->BaggageHasItem(pNpcTpl->mItemID[i]) > 0)
			{
				// ���� ����fireevent����������Ǹ�������false 			
				CItemObject *pInsItemPile = NULL;
				pInsItemPile = CPropertyModule::GetSingleton().PlayerInsertItem( pPlayer, pNpcTpl->mItemID[i], pNpcTpl->mItemNum[i], false);
				if ( pInsItemPile != NULL)
				{
					LogEventGetItemByCollect(pPlayer, pInsItemPile->GetGUID(), 
						pNpcTpl->mItemID[i], pNpcTpl->mItemNum[i], pPlayer->GetPosX(), pPlayer->GetPosY(),  pNpcTpl->mTaskID[i]);
				}
				int tRand = RAND(SERVER_PERCENT_INT);
				if( tRand < pNpcTpl->mExtraItemProbality[i] )
				{
					pInsItemPile = CPropertyModule::GetSingleton().PlayerInsertItem( pPlayer, pNpcTpl->mItemID[i], RAND(SERVER_PERCENT_INT)%pNpcTpl->mExtraItemNum[i]+1, false);
					if ( pInsItemPile != NULL)
					{
						LogEventGetItemByCollect(pPlayer, pInsItemPile->GetGUID(), 
							pNpcTpl->mItemID[i], pNpcTpl->mItemNum[i]+RAND(SERVER_PERCENT_INT)%pNpcTpl->mExtraItemNum[i]+1, pPlayer->GetPosX(), pPlayer->GetPosY(),  pNpcTpl->mTaskID[i]);
					}
				}
				bRet = true;
			}
		}	
	}	 

	return bRet;
}

// �õ���������
int CTaskModule::GetTaskType( unsigned short vTaskID )
{
	return CTaskLuaInterface::Call<int, unsigned short>( NULL, NULL, "get_task_type_by_id", vTaskID ); // ȷ������Ҫ�ⲿ����
}

// ����������
void CTaskModule::SetDefaultTask( CEntityPlayer* pPlayer, const char* pTaskTypeName )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	if (pList == NULL) // �����б�
	{
		pList = (CTaskList*)CSceneObjManager::GetSingletonPtr( )->CreateObject( OBJTYPE_TASKLIST );	
		if ( pList == NULL ) // û��Դ��
		{
			LOG_FATAL("TASK", "can't create player data !!!  charid=%d", pPlayer->GetCharID() );
			return;
		}
		pPlayer->SetTaskToken(pList->get_id());
		pList->SetOwnerEntityID(pPlayer->GetEntityID());
	}

	unsigned short tTaskID = lua_tinker::get<unsigned short>( L, pTaskTypeName);
	if (tTaskID > 0)
	{
		PERF_FUNC("PlayerObtainTask", PlayerObtainTask( pPlayer, tTaskID, true ));
		LogEventPlayerAcceptTask( pPlayer, tTaskID);
	}

}

// �ɵ���������
void CTaskModule::ClearTasks( CEntityPlayer* pPlayer )
{
	LK_ASSERT( pPlayer, return );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	//unsigned short tasks[TASK_LIST_SIZE] = {0};
	//for (int i = 0; i < pList->mTaskNumber; ++i)
	//{
	//	tasks[i] = pList->mTaskList[i].mTaskID;
	//}
	//ClearTasks( pPlayer, tasks, pList->mTaskNumber);

	pList->Initialize();
	CMessageClearTaskNotify msg;
	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_CLEARTASKNOTIFY);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}

// ��������������� (˽��)
void CTaskModule::ClearTasksByType( CEntityPlayer* pPlayer, enTaskType nType )
{
	LK_ASSERT( pPlayer, return );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	unsigned short tasks[TASK_LIST_SIZE] = {0};
	int n = 0;

	for (int i = 0; i < pList->mTaskNumber; ++i)
	{
		if (GetTaskType(pList->mTaskList[i].mTaskID) == (int)nType)
			tasks[n++] = pList->mTaskList[i].mTaskID;
	}
	ClearTasks( pPlayer, tasks, n);
}

// �������� �������ͻ��˷���Ϣ(˽��)
void CTaskModule::ClearTasks( CEntityPlayer* pPlayer, unsigned short *aTaskID, int n )
{
	LK_ASSERT( pPlayer, return );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );
	LK_ASSERT( aTaskID,  return );
	CMessageAbortTaskNotice msg;
	CMessage tMessage;
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_ABORT_TASK);

	for ( int i = 0; i < n; ++i )
	{
		if (aTaskID[i] <= 0)
			continue;

		pList->RemoveTask( aTaskID[i] );
		msg.set_taskid( aTaskID[i] );
		tMessage.set_msgpara((uint32_t) &msg);
		CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
	}
}

// �����ͻ����������ʧ�ܵ���Ϣ
void CTaskModule::Send2ClientOprFailed( CEntityPlayer* pPlayer)
{
	CMessageTaskOprFailNotice tError;
	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &tError);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_TASKOPRFAIL);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}



// �����ͻ���ˢ��������ʧ�ܵ���Ϣ
void CTaskModule::Send2ClientRefreshFailed( CEntityPlayer* pPlayer)
{
	CMessageTaskRefreshFailNotice tError;
	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &tError);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_TASKREFRESHFAIL);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}

// �����ͻ������񲻿�ˢ�� 

void CTaskModule::Send2ClientUnRefreshed( CEntityPlayer* pPlayer)
{
	CMessageTaskUnRefreshNotice tError;
	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &tError);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_TASKUNREFRESHED);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}

// �����ͻ���ˢ����������Ʒ��
void CTaskModule::Send2ClientRefreshResult( CEntityPlayer* pPlayer, unsigned short vTaskID, int vTaskColor, unsigned short vTaskNumber )
{
	CMessageTaskRefreshResult tResult;
	tResult.set_taskid(vTaskID);
	tResult.set_taskcolor(vTaskColor);
	tResult.set_tasknumber(vTaskNumber);
	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &tResult);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_TASKREFRESHRESULT);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}

// ֪ͨ�ͻ���  ɾ����������Ʒ��

void CTaskModule::Send2ClientRemoveTaskColor( CEntityPlayer* pPlayer, unsigned short vTaskID, int vTaskColor )
{
	CMessageRmoveTaskColor tRemove;
	tRemove.set_taskid(vTaskID);
	tRemove.set_taskcolor(vTaskColor);
	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &tRemove);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_REMOVETASKCOLOR);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}

// ֪ͨ�ͻ���  ���������ȴʱ�仹δ��

void CTaskModule::Send2ClientUnReaccpetTask( CEntityPlayer* pPlayer, unsigned short vTaskID, int vNeedTime )
{
	CMessageUnReaccpetTask tUnaccept;
	tUnaccept.set_taskid(vTaskID);
	tUnaccept.set_needtime(vNeedTime);
	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &tUnaccept);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_TASKUNREACCEPT);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}

// ��û��������� ��ֵ����Ϣ
// nMsgType = 1   �����б� 
// nMsgType = 2   ��������Ϣ 
void CTaskModule::GetLoopTaskClientData( CEntityPlayer* pPlayer, CTaskList* pList, LoopTaskStruct* pLoopStruct )
{
	LK_ASSERT( pList, return );
	LK_ASSERT( pPlayer, return );
	LK_ASSERT( pLoopStruct , return );
	
	pLoopStruct->set_nextloopid( pList->mLoopTaskData.GetCurSubTaskIndex() + 2);
	pLoopStruct->set_completedloops( pList->mLoopTaskData.GetCompletedTimes() );
	pLoopStruct->set_todaymultiloops( pList->mLoopTaskData.GetTodayCompletedTimes() );
	pLoopStruct->set_weekmultiloops( pList->mLoopTaskData.GetWeekLoops() );
	pLoopStruct->set_loopid( pList->mLoopTaskData.GetCurSubTaskIndex() + 1 );

	//unsigned short usCurSubTaskID = pList->mLoopTaskData.GetSubTaskIDbyIndex( pList->mLoopTaskData.GetCurSubTaskIndex() );
	// LUA��get_looptaskdata�ӿ���Ҫ��û�����ľ�̬���ݣ�����ֻҪ�����������ֻ���������һ��������ID�Ϳ�����
	unsigned short usCurSubTaskID = pList->mLoopTaskData.GetOneSubTaskID();
	if (usCurSubTaskID == 0)
	{
		return;
	}

	lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, unsigned short>( pPlayer, pList, "get_looptaskdata", usCurSubTaskID );
	pLoopStruct->set_looptaskid( ret.get<int>("loopid") );
	pLoopStruct->set_totalmultiloops( ret.get<int>("day_total") );
	pLoopStruct->set_weektotalmultiloops( ret.get<int>("week_total") );
	// �¼ӣ�ÿ����ɵ�ǰx�λ�����Ľ���
	pLoopStruct->set_awardmultipletoday( ret.get<int>("day_multi") );
}

// �Ƴ���ĳNPC�ĶԻ� ����ҿ����ٴζԻ���
void CTaskModule::RemoveTalkWithNpc( CEntityPlayer* pPlayer, unsigned short vTaskID, int nNpcTempID )
{
	LK_ASSERT( pPlayer, return );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	CTask* pTask = pList->GetTask(vTaskID);
	if ( pTask == NULL )
		return ; // ��������Ѿ�����

	if ( pTask->RemoveTalkedWithNpc( nNpcTempID ) )
	{
		// ֪ͨ�ͻ���
		CMessageNpcTalkStateChangeNotice msg;
		msg.set_taskid( vTaskID );
		msg.set_npctempid( nNpcTempID );
		msg.set_state( 0 );
		CMessage   tMessage;
		tMessage.set_msgpara((uint32_t) &msg);
		tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_NPCTALKCHANGE);
		CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
	}
	else
	{
		LOG_ERROR("TASK" ,"player %s and NPC %d's talk not found, please check logic", pPlayer->GetCharNameShow(), nNpcTempID );
	}	
}

// ��Һͱ���NPCս��ʧ��
void CTaskModule::OnNpcRecoverdState( int nPlayerCharID, unsigned short usTaskID, int nNpcTempID )
{
	if ( nPlayerCharID == 0 || usTaskID == 0 || nNpcTempID == 0 )
		return;

	CEntityPlayer* pPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID(nPlayerCharID);
	if ( pPlayer == NULL ) // �����Ѿ�������
		return;

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	// �ָ��Ի�
	RemoveTalkWithNpc( pPlayer, usTaskID, nNpcTempID );
	// �ָ�ս���е�NPC ID
	pList->SetBossNpcEntityID(0);
}

// ���Ը��ṩ�Ļ���������ֵĽӿ�
const char* CTaskModule::GetTaskName( unsigned short vTaskID )
{
	return lua_tinker::call<const char*, unsigned short, unsigned short>(L, "get_ctrl", vTaskID, CTRL_NAME);
}

bool CTaskModule::GetSendNpcCurTarget( int nEntityID, CWTPoint& rPoint )
{
	return mSendNpcMgr.GetNpcCurTarget( nEntityID, rPoint );
}

// �õ�lua������ڴ�ʹ��kb
int CTaskModule::GetLuaVMUsedMem( )
{
	return lua_getgccount( L );
}

// �õ���ǰ���ڻ���NPC
// ��������ҵ�ID
CEntityNpc* CTaskModule::GetCurSendNpc( CEntityPlayer* pPlayer )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return NULL );

	CEntityNpc* pEntityNpc = (CEntityNpc*)CSceneLogic::GetSingleton().GetEntity( pList->GetSendNpcEntityID() );
	return pEntityNpc;
}

// �õ�����״̬�ӿ�
int CTaskModule::GetTaskState( CEntityPlayer* pPlayer, unsigned short usTaskID )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return NULL );

	return pList->GetTaskState( usTaskID );
}

// ǿ��ĳ�������
int CTaskModule::OnForceTaskComplete( std::vector<unsigned int>& rEntitys, unsigned short usTaskID )
{
	for ( std::vector<unsigned int>::iterator it = rEntitys.begin(); it != rEntitys.end(); ++it )
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity( *it );
		LK_ASSERT( tpPlayer != NULL, continue );
		CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(tpPlayer->GetTaskToken( ));
		LK_ASSERT( pList,  return NULL );
		CTask* tpTask = pList->GetTask(usTaskID);
		if ( tpTask != NULL )
		{
			tpTask->SetTaskProgress( TASK_COMPLETE );
			// �����ʱ��δ���� �ɵ���ʱ��
			if( tpTask->mTimerID != INVALID_OBJ_ID )
			{
				int tRet = tpPlayer->GetTimerReciver()->ClearTimer( tpTask->mTimerID );
				if ( tRet != 0 )
					LOG_ERROR("TASK", "abort del timer returned %d, timerid=%d taskid=%d", tRet, tpTask->mTimerID, usTaskID );

				LOG_DEBUG("TASK", "abort del timer returned %d, timerid=%d taskid=%d", tRet, tpTask->mTimerID, usTaskID );
				tpTask->mTimerID = INVALID_OBJ_ID;
			}

			CMessageTaskCompleteNotice msg;
			msg.set_taskid(usTaskID);
			CMessage   tMessage;
			tMessage.set_msgpara((uint32_t) &msg);
			tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_COMPLETE);
			CSceneLogic::GetSingleton( ).Send2Player( tpPlayer, &tMessage );
		}
	}
	return 0;
}

// ÿ������
void CTaskModule::DaylyDispos( CEntityPlayer* pPlayer )
{
	CPropertyPlayer* tpProPlayer = (CPropertyPlayer*) pPlayer->GetProperty();

	if ( !IsANewDay((time_t)tpProPlayer->GetLastDaylyDisposTime(), time(0)) )
		return ;

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );
	OnTaskPlayerNewDayCome(pList);
}

// ÿ������
void CTaskModule::WeeklyDispos( CEntityPlayer* pPlayer )
{
	CPropertyPlayer* tpProPlayer = (CPropertyPlayer*) pPlayer->GetProperty();

	if ( !IsANewWeek((time_t)tpProPlayer->GetLastWeeklyDisposTime(), time(0)) )
		return ;

	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );
	pList->OnNewWeekCome();
}

// ��ÿ��������ݽӿ�
int  CTaskModule::GetStorageTaskData( CEntityPlayer* pPlayer, CTaskList* pTaskList, StorageTaskStruct* pData )
{
	LK_ASSERT( pPlayer!=NULL && pTaskList!=NULL && pData!=NULL, return -1 );
	pData->set_todaycompletes( pTaskList->mStorageTaskMgr.GetTodayCompleted() );
	lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table>( pPlayer, pTaskList, "get_storage_task_extra_awards" );
	int multi = ret.get<int>("multi");
	if ( multi <= 0 )
		multi = 1;
	pData->set_awardmultipletoday( multi );	// ����
	pData->set_totalmultiloops( ret.get<int>("times") );	// ÿ��x��
	return 0;
}

// ������ʱ����ʱ
int	CTaskModule::OnTaskTimeOut( CEntityPlayer* pPlayer, unsigned short usTaskID )
{
	// ע�⣺Ŀǰ������õ�2������ ����ɵ���ʱ���� ������� ��Ӧ��������ɵ���ʱ�� ����ģ�
	int tType = GetTimeOutFlag( usTaskID );
	if ( tType == TIMEOUT_FAIL )
	{
		OnTaskFailed( pPlayer, usTaskID );
	}
	else if ( tType == TIMEOUT_COMPLETE )
	{
		CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
		LK_ASSERT( pList,  return -1 );
		if ( pList->GetTaskState(usTaskID) == TASK_BEGIN ) // ֻ�н����е�������óɹ�
		{
			std::vector< unsigned int > players;
			players.push_back( pPlayer->GetEntityID() );
			OnForceTaskComplete( players, usTaskID );
		}
	}
	return 0;
}

// �����ͼ��ʱ�����
int  CTaskModule::OnPlayerRedirectMap( CEntityPlayer* pPlayer )
{
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return -1 );
	if ( pList->mRedirectFailTask != 0 )
	{
		OnTaskFailed( pPlayer, pList->mRedirectFailTask, false );
	}
	return 0;
}

// ǿ��ˢĳNPC��ͷ��
void CTaskModule::ForceRefreshNpcTip( int nNpcEntityID )
{
	if ( nNpcEntityID == INVALID_OBJ_ID )
		return;
	LOG_DEBUG("TASK", "%s", __FUNCTION__ );

	CEntityNpc* tpEntityNpc = dynamic_cast<CEntityNpc*>(CSceneObjManager::GetSingletonPtr()->GetObject( nNpcEntityID ) );
	if ( tpEntityNpc == NULL )
		return ;

	CProperty* pPropty = tpEntityNpc->GetProperty();

	CSeenPlayerContainer tSeenPlayer = tpEntityNpc->GetSeenPlayersContainer();
	// �����ɼ���
	for (CSeenPlayerContainer::SeenPlayerVector::iterator it = tSeenPlayer.mPlayers.begin()
		; it != tSeenPlayer.mPlayers.end(); ++it )
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(*it);
		if ( tpPlayer == NULL )
			continue;

		CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(tpPlayer->GetTaskToken( ));
		LK_ASSERT( pList,  continue );

		CMessageNpcTaskTipNotice msg;

		if( tpEntityNpc->IsWithinViewDistance( tpPlayer ) == false )
			continue;

		unsigned short tTip = GetNpcTip( tpPlayer, pPropty->GetPropertyTempID(), pList, nNpcEntityID );
		LOG_DEBUG( "TASK", "send NPC TIP, temp ID=%d, tip=%d\n", pPropty->GetPropertyTempID(), tTip);

		msg.add_npcentityid( nNpcEntityID );
		msg.add_tip(tTip) ;

		CMessage   tMessage;
		tMessage.set_msgpara((uint32_t) &msg);
		tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_NPCTASKTIP);
		CSceneLogic::GetSingleton( ).Send2Player( tpPlayer, &tMessage );
	}
}



bool CTaskModule::OnCheckLaunch()
{
	// �������ݿ��ȫ������
	// ������������
	// ��reload ���Բ�д��load_config
	//if (CObj::msCreateMode)
	//{
	//	CSceneLogic* tpLogic = CSceneLogic::GetSingletonPtr( );
	//	LK_ASSERT( tpLogic!=NULL, return false );
	//	tpLogic->ExecuteSql( load_task_global, 0, 0, 0, SQL_NEED_CALLBACK,
	//		SELECT, "select publish_info from UMS_TASK_GLOBAL_DATA" );
	//}
	return true;
}



// ���/������������
int CTaskModule::ResetChairManTasks( CEntityPlayer* pPlayer, unsigned short usChairManID )
{
	LK_ASSERT( pPlayer, return 0 );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return 0 );

	pList->mChairManTaskMgr.Initialize();

	// �������luaȷ������Ҫ�ⲿ����
	lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, int>( NULL, NULL, "refresh_chairman_tasks", usChairManID );

	int n = luaL_getn( L, -1); //min( luaL_getn( L, -1), MAX_STORAGETASK_LIST_NUM );
	if ( n > CHAIRMAN_TASK_NUM || n <= 0 )
	{
		LOG_ERROR("TASK", "Got %d ChairmanTasks?", n );
		return 0;
	}

	unsigned short usTasks[CHAIRMAN_TASK_NUM] = {0};
	for ( int i = 1; i <= n; ++i)
	{
		lua_rawgeti(L, -1, i);
		usTasks[i-1] = lua_tinker::pop<unsigned short>(L);
		LOG_DEBUG("TASK", "refresh Chairman %d ", usTasks[i-1] );
	}
	LOG_DEBUG("TASK", "refresh Chairman %d end! num=%d", usChairManID, n );
	//pList->mChairManTaskMgr.ResetTasks( usTasks, CHAIRMAN_TASK_NUM, usChairManID );
	return n;
}



// ��ʱ�������
void CTaskModule::TempDispos( CEntityPlayer* pPlayer, CTaskList* pList )
{
	if ( pPlayer == NULL || pList == NULL )
		return;

	// ������������
	for (CHAIRMAN_COMPLETED_TYPE::iterator it = pList->mChairManTaskMgr.mCompleted.begin();
		it != pList->mChairManTaskMgr.mCompleted.end(); ++it )
	{
		// ������������ID�õ��б�
		int nRealCompleted=0;
		lua_tinker::table t1 = CTaskLuaInterface::Call<lua_tinker::table, int>
			(pPlayer, pList, "get_chairman_list_by_chairmanid", it->first );

		int nNum = luaL_getn(L, -1);
		for(int i =1; i<=nNum; ++i)
		{
			lua_rawgeti(L, -1, i);
			unsigned short task_id = (unsigned short)lua_tinker::pop<int>(L);
			// �ж����û
			if ( pList->mCompleteTasks.find(task_id) != pList->mCompleteTasks.end() )// �����
			{
				++nRealCompleted;
			}
		}
		if ( nRealCompleted != it->second ) // ��һ����
		{
			LOG_ERROR("TASK", "*CHAIRMAN* player %d(%s) chairid %d realcomp %d indb %d", pPlayer->GetCharID(),
				pPlayer->GetCharNameShow(), it->first, nRealCompleted, it->second );
			it->second = nRealCompleted;
		}
		else
		{
			LOG_DEBUG("TASK", "*CHAIRMAN* player %d(%s) chairid %d realcomp %d OK", pPlayer->GetCharID(),
				pPlayer->GetCharNameShow(), it->first, nRealCompleted );
		}
	}
	// �����ϵ���������ϴһ�� ��ֹ���ݶԲ���
	int nChairman=0;
	for ( int i = 0; i < TASK_LIST_SIZE; ++i )
	{
		if ( GetTaskType( pList->mTaskList[i].mTaskID ) == TASKTYPE_CHAIRMAN )
			++nChairman;
	}
	if ( pList->mChairManTaskMgr.GetAcceptedNum() != nChairman )
	{
		LOG_ERROR("TASK", "player %d acc=%d rel=%d", pPlayer->GetCharID(), pList->mChairManTaskMgr.GetAcceptedNum()
			, nChairman);
		pList->mChairManTaskMgr.SetAcceptedNum(nChairman);
	}
}

// ǿ������������������
void CTaskModule::SetTodayTimesByGroupID( CEntityPlayer* pPlayer, int nGroupID, int nNum )
{
	LK_ASSERT( pPlayer, return );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );
	pList->mTaskGroupMgr.SetTodayTimes( nGroupID, nNum );
}

// �����б�ÿ�촦�� �Ѱ��������ߵ����
// �����Ƿ��б�����������������
bool CTaskModule::OnTaskPlayerNewDayCome(CTaskList* pTaskList, bool bIsOnline )
{
	pTaskList->OnNewdayCome();
	bool bRet = false;
	// ����ÿ��Ҫ�����
	// �����������ȷ�ϲ��������Ϣ ���Դ���NULL
	lua_tinker::table t1 = CTaskLuaInterface::Call<lua_tinker::table>(NULL, NULL, "get_day_clear_tasks");
	int n = luaL_getn(L, -1);
	for(int i =1; i<=n; ++i)
	{
		lua_rawgeti(L, -1, i);
		unsigned short tTaskID = lua_tinker::pop<int>(L);
		if (pTaskList->IsTaskEnd(tTaskID)) // �����
		{
			bRet = true;
			pTaskList->ClearTaskEndFlag(tTaskID) ;
		}
	}

	std::vector<unsigned short> _fail_list;	// ʧ�ܵ������б�
	if ( bIsOnline ) // �����û�и���ʧ�ܵ� �еĻ���ʧ��
	{
		for ( int i = 0 ; i < pTaskList->mTaskNumber && i < TASK_LIST_SIZE; ++i )
		{
			if ( IsDailyFail(pTaskList->mTaskList[i].mTaskID) ) // ��һ�� ���ü���ǲ��� ��ʧ��
			{
				_fail_list.push_back(pTaskList->mTaskList[i].mTaskID);
			}
		}
	}

	CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton().GetEntity(pTaskList->GetOwnerEntityID());
	if (tpPlayer != NULL)
	{
		for ( std::vector<unsigned short>::iterator it = _fail_list.begin(); it != _fail_list.end(); ++it )
		{
			OnTaskFailed( tpPlayer, *it );
		}
	}

	// �����ӻ��������
	if (pTaskList->GetTodayTeamLoopNum() >= MAX_TEAMLOOP_EVERYDAY)
	{
		pTaskList->ZeroTodayTeamLoopNum();
	}

	return bRet;
}

void CTaskModule::SendTaskMsg2Client( CTaskList* pList )
{
	CEntityPlayer *tpPlayer = ( CEntityPlayer * )CSceneLogic::GetSingleton().GetEntity( pList->GetOwnerEntityID() );	
	LK_ASSERT(tpPlayer != NULL, return );

	// ���ͻ��˷�������
	CMessageTaskListNotice msg;
	for( int i = 0; i < pList->mTaskNumber; ++i )
	{
		TaskStruct* tpTask = msg.add_tasks();
		pList->mTaskList[i].GetTaskDataStruct(tpTask);
	}
	LoopTaskStruct* tpLoop = msg.mutable_looptask();
	GetLoopTaskClientData( tpPlayer, pList, tpLoop);
	StorageTaskStruct* tpStorage = msg.mutable_storagetask();
	GetStorageTaskData( tpPlayer, pList, tpStorage );
	msg.set_tasknum(pList->mTaskNumber);
	for ( lk::hash_map<unsigned short, unsigned short, COMPLETE_TASK_NUM>::iterator it = pList->mCompleteTasks.begin()
		; it != pList->mCompleteTasks.end(); ++it )
	{
		msg.add_completedtasks( it->first );
	}

	for ( lk::hash_map<unsigned short, int, COMPLETE_TASK_NUM>::iterator it = pList->mRepeatTasks.begin()
		; it != pList->mRepeatTasks.end(); ++it )
	{
		msg.add_repeatetasks( it->first );
		msg.add_endtime( it->second );
	}

	// �������������б�
	lua_tinker::table t1 = CTaskLuaInterface::Call<lua_tinker::table>
		(tpPlayer, pList, "get_all_chairman_list" );

	int nNum = luaL_getn(L, -1);
	for(int i =1; i<=nNum; ++i)
	{
		lua_rawgeti(L, -1, i);
		msg.add_chairmansectionids(lua_tinker::pop<int>(L));
	}
	CMessage   tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_TASKLIST);
	CSceneLogic::GetSingleton( ).Send2Player( tpPlayer, &tMessage );

	int anIndex[TRAGEDY_TASK_SIZE] = {0};
	unsigned short asNextID[TRAGEDY_TASK_SIZE] = {0};
	int anState[TRAGEDY_TASK_SIZE] = {0};
	int n = pList->mTragedyTaskMgr.GetAllInfo( anIndex, asNextID, anState );
	SendTragedyInfo2Client( tpPlayer, anIndex, asNextID, anState , n, 1);
}

int  CTaskModule::SendTeamLoopErrNotify( CEntityPlayer* pPlayer, const char* pName, int nErrCode)
{
	if (pName == NULL)
		return -1;

	CMessageGetTeamLoopErrNotify msg;
	msg.set_charname(pName);
	msg.set_errcode(nErrCode);
	CMessage   tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTIFY_GETTEAMLOOPERR);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
	return 0;
}

// ���ٽ����� ���ڱ���
int CTaskModule::PlayerFastObtainTask( CEntityPlayer* pPlayer, unsigned short vTaskID, int taskColor )
{
	LK_ASSERT( pPlayer,  return -1 );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return -1 );
	//  ��������
	CTask vTask; 
	vTask.mTaskID = vTaskID;
	int tRet = pList->InsertTask(vTask);
	if ( tRet == ERROR_TASK_SUCCESS )
	{
		CTask* pTask = pList->GetTask(vTaskID);
		LK_ASSERT( pTask, return -2 );

		// ��ʼ��һ����������
		CTaskLuaInterface::Call<int, CTask*>( pPlayer, pList, "init_this_task", pTask); //  ��ʼ�������õ��������Ҫɱ�ֵ�������

		// ֪ͨ�ͻ���
		CMessageObtainTaskNotice msg;
		TaskStruct* tpTask = msg.mutable_task();
		pTask->GetTaskDataStruct(tpTask);

		CMessage   tMessage;
		tMessage.set_msgpara((uint32_t) &msg);
		tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_OBTAINTASK);
		CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );

		//  �ж�һ�������Ƿ����(ǿ��ˢ��)
		FireEvent( pPlayer, 0 );
		DoTaskObtAwards( pPlayer, pList, vTaskID );

		// ȡ����ID �����Ϊ0  Ҫ������ ���ӽ��ܴ���
		int tGroupID = CTaskLuaInterface::Call<int, unsigned short>( pPlayer, pList, "get_task_group_id", vTaskID );
		if ( tGroupID != 0 )
		{
			pList->mTaskGroupMgr.OnAcceptOneTask( tGroupID );
		}
		int vColor = pList->GetTaskColor(vTaskID);
		pList->InsertRefreshedTask(vTaskID, vColor);
		return 0;
	}
	return -3;
}

void CTaskModule::LoadLuaFileCallback(const char* pcConfigPath)
{
	if (CTaskModule::GetSingleton().m_bHasReloadLua)
	{
		return;
	}

	CTaskModule::GetSingleton().RegisterLua();
	CTaskModule::GetSingleton().m_bHasReloadLua = true;
}

bool CTaskModule::CheckPublishCondition(CEntityPlayer* pPlayer, unsigned short vTaskID)
{
	LK_ASSERT(pPlayer !=NULL, return false );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return false );

	return CTaskLuaInterface::Call<bool, unsigned short>(pPlayer, pList, "check_publish_condition", vTaskID );
}


int CTaskModule::GetGroupNeedMoney(CEntityPlayer* pPlayer, unsigned int vTaskType, unsigned short vTaskID)
{
	LK_ASSERT(pPlayer !=NULL, return -1 );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return -1 );
	switch(vTaskType)
	{
	case CORPS_PUBLISH_TASK:
		{
			return CTaskLuaInterface::Call<int, unsigned short>(pPlayer, pList, "get_need_corps_money", vTaskID );
			break;
		}
	default:break;
	}
	return 0;
}