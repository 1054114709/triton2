
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
#include "servermessage_pb.hxx.pb.h"
#ifdef LEAK_CHK_DEBUG_NEW
#include "debug_new.h"
#endif
// ���������� ����һЩ����
void CTaskModule::OnLoadGlobalData( CMessage* pMessage, int vParameter1, int vParameter2 )
{
	LK_ASSERT( pMessage != NULL, return );

	CMessageExecuteSqlResponse3* pSqlRes = (CMessageExecuteSqlResponse3*)pMessage->msgpara();
	LK_ASSERT( pSqlRes != NULL, return );


	if ( pSqlRes->resultcode() == 0 )
	{
		LOG_ERROR( "TASK", "Execute Sql For Player  Login failed"  );
		return;
	}

	if( pSqlRes->rowcount() == 0 ) // û������
	{
		return ;
	}
	if( pSqlRes->rowcount() != 1)
	{
		LOG_WARN("TASK", "load global data returned %d line?", pSqlRes->rowcount());
	}

	PBTaskPublishInfo tData;
	if (pSqlRes->fieldvaluelen(0) <3) // �յ�
		return;

	if( tData.ParseFromArray( pSqlRes->fieldvalue(0).c_str(), (int)pSqlRes->fieldvaluelen(0) ) == true )
	{
		LOG_INFO("TASK", "load publish info line" );
	}
	else
	{
		LOG_ERROR("TASK", "parse data error!!");
	}
}
// ���� ����
void CTaskModule::OnMessageUpgEquipRequest( CEntityPlayer* pPlayer, CMessage* pMessage)
{
	if ( pPlayer == NULL || pMessage == NULL )
	{
		LOG_DEBUG( "TASK", "[ %s : %d ] [ %s ]", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}
	FireEvent( pPlayer, EVENT_UPEQT, 0 );
}

// ����
void CTaskModule::OnMessageProduceEquipRequest( CEntityPlayer* pPlayer, CMessage* pMessage)
{
	CMessageProduceEquipRequest* pMsg = ( CMessageProduceEquipRequest* )pMessage->msgpara( );
	if ( pMsg == NULL )
	{
		LOG_DEBUG( "pro", "[ %s : %d ] [ %s ]", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}
	FireEvent( pPlayer, EVENT_PRODUCE_WEAPON, 0 ); // ����ֻ�������������� ��������ʲô ������������

	//if ( pMsg->type1() == EQUIP_WEAPON ) // ����
	//{
	//	FireEvent( pPlayer, EVENT_PRODUCE_WEAPON, 0 );
	//}
	//else if( pMsg->type1() == EQUIP_HELM || pMsg->type1() == EQUIP_BODY || pMsg->type1() == EQUIP_SHOE || pMsg->type1() == EQUIP_BRACER )// ����
	//{
	//	FireEvent( pPlayer, EVENT_PRODUCE_PREVENT, 0 );
	//}
}

// ����ҩƷ
void CTaskModule::OnMessageProducePhysRequest( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	CMessageProduceEquipRequest* pMsg = ( CMessageProduceEquipRequest* )pMessage->msgpara( );
	if ( pMsg == NULL )
	{
		LOG_DEBUG( "pro", "[ %s : %d ] [ %s ]", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}
	FireEvent( pPlayer, EVENT_PRODUCE_DRUG, 0 );
}

// ��Ƕ����
void CTaskModule::OnMessageInsertRuneRequest( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	if ( pPlayer == NULL || pMessage == NULL  )
	{
		LOG_DEBUG( "TASK", "[ %s : %d ] [ %s ]", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}
	FireEvent( pPlayer, EVENT_CHARSTONE, 0 );
}

// ��Ƕ��ʯ
void CTaskModule::OnMessageInsertJewelRequest( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	if ( pPlayer == NULL || pMessage == NULL  )
	{
		LOG_DEBUG( "TASK", "[ %s : %d ] [ %s ]", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}
	FireEvent( pPlayer, EVENT_JEWEL, 0 );
}

// ����
void CTaskModule::PlayerOpenSlot( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	if ( pPlayer == NULL || pMessage == NULL )
	{
		LOG_DEBUG( "TASK", "[ %s : %d ] [ %s ]", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}
	FireEvent( pPlayer, EVENT_HOLE, 0 );
}

// ��װ��
void CTaskModule::OnMessageEatEquipRequest( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	if ( pPlayer == NULL || pMessage == NULL )
	{
		LOG_DEBUG( "TASK", "[ %s : %d ] [ %s ]", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}
	FireEvent( pPlayer, EVENT_STOVE, 0 );
}

// ѧϰ����
void CTaskModule::OnMessageStudySkillRequest( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	if ( pPlayer == NULL || pMessage == NULL )
	{
		LOG_DEBUG( "TASK", "[ %s : %d ] [ %s ]", __LK_FILE__, __LINE__, __FUNCTION__ );
		return;
	}
	FireEvent( pPlayer, EVENT_SKILL, 0 );
}

// ������Һ�NPC��ɶԻ�����Ϣ
void CTaskModule::OnMessagePlayerEndTalk( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer, return );

	//if (pPlayer->IsOverseas() && !(IS_NEUTRAL_LINE_ID(pPlayer->GetLineID()) ) )
	//	return ;

	CMessageEndTalkRequest* pMsg = ( CMessageEndTalkRequest* )pMessage->msgpara( );

	// �ж�NPC�Ϸ� ��ұ���վ��NPC�Ա߽����� �ʰ��������
	CEntityNpc* tpEntity = dynamic_cast<CEntityNpc*>(CSceneObjManager::GetSingletonPtr()->GetObject( pMsg->npcentityid() ) );

	if ( tpEntity != NULL ) 
	{
		if( pPlayer->IsWithinDistance( tpEntity, MAX_NPC_TALK_GIRD) == false ) // �ںϷ�����֮�ڲ��ж�
		{
			//LOG_ERROR("TASK", "player not near npc! player ID=%d", pPlayer->GetCharID() );
			return;
		}

		// ֻ���Ѻò��ܶԻ�
		if ( !( tpEntity->IsFunNpc() && tpEntity->IsFriendlyTo(pPlayer) ) )
		{
			return;
		}

		// �ж�NPC�ǲ����ѱ�����߻���״̬
		if ( tpEntity->GetNpcChangeState() != 0 || tpEntity->GetSendNpcState() != 0  )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_NPC_BUSY );
			Send2ClientOprFailed( pPlayer );
			return;
		}

		// ����й��� �����ǲ����Լ��� ���ǵĻ����öԻ�
		if ( tpEntity->GetOwnercharID() != 0 && tpEntity->GetOwnercharID() != (int)pPlayer->GetCharID() )
		{
			CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_NOT_YOUR_NPC );
			return;
		}
	}
	else
	{
		LOG_ERROR("TASK", "player not near npc! player ID=%d", pPlayer->GetCharID() );
		return;
	}

	CPropertyNPC* pPropertyNpc = (CPropertyNPC*)tpEntity->GetProperty();
	LK_ASSERT( pPropertyNpc, return );

	CTaskList*	pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );
	pList->SetTalkNpcEntityID(pMsg->npcentityid());

	CTask* pTask = pList->GetTask(pMsg->taskid());
	LK_ASSERT( pTask, return );
	if ( pTask->IsTalkedWithNpc(pPropertyNpc->GetPropertyTempID()) ) // �Ѿ��Ի�����
	{
		//CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_TALKWITHNPC_FAILED );
		pList->SetTalkNpcEntityID(0);
		return;
	}

	// ����״̬���ǽ����еĻ� ������Ի�
	//if (pTask->mTaskProgress != TASK_BEGIN)
	//{
	//	pList->SetTalkNpcEntityID(0);
	//	return;
	//}

	if ( !pTask->AddTalkedWithNpc(pPropertyNpc->GetPropertyTempID()) )
	{
		//CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_TALKWITHNPC_FAILED );
		pList->SetTalkNpcEntityID(0);
		return;
	}

	// ����ɹ����Ի�
	LOG_DEBUG( "TASK", "player %s talk with NPC %d end", pPlayer->GetCharNameShow(), pPropertyNpc->GetPropertyTempID() );

	CMessageNpcTalkStateChangeNotice msg;
	msg.set_taskid(pMsg->taskid());
	msg.set_npctempid(pPropertyNpc->GetPropertyTempID());
	msg.set_state( 1 );
	CMessage   tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_NPCTALKCHANGE);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
	CTaskLuaInterface::Call<int, unsigned short, int, unsigned int>( pPlayer, pList, "on_end_talk_with_npc", pMsg->taskid(), pPropertyNpc->GetPropertyTempID(), pPlayer->GetEntityID() );
	pList->SetTalkNpcEntityID(0);
}

//  �ͻ��˷�����Ϣ
void CTaskModule::OnClientMessage( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	const CMessageHead&  tHead = pMessage->msghead();

	switch(tHead.messageid())
	{
		//  ��ҷ�����������
	case ID_C2S_REQUEST_ABORTTASK:
		{
			CMessageAbortTaskRequest* tpAbortTask = (CMessageAbortTaskRequest*) pMessage->msgpara();

			PERF_FUNC( "PlayerAbortTask", PlayerAbortTask( pPlayer, tpAbortTask->taskid() ) );
			LogEventPlayerCancelTask( pPlayer, tpAbortTask->taskid(),1);
			break;
		}

		//  ��ҽ�����������
	case ID_C2S_REQUEST_OBTAINTASK:
		{
			CMessageObtainTaskRequest* tpTaskAccept = (CMessageObtainTaskRequest*) pMessage->msgpara();

			OnPlayerObtainTask(pPlayer, tpTaskAccept->taskid(), tpTaskAccept->npcentityid() );

			break;
		}

		//  ��ҽ�����������
	case ID_C2S_REQUEST_ENDTASK:
		{
			CMessageTaskEndRequest* tpTaskEnd = (CMessageTaskEndRequest*) pMessage->msgpara();

			CEntityNpc* tpEntityNpc = dynamic_cast<CEntityNpc*>(CSceneObjManager::GetSingletonPtr()->GetObject( tpTaskEnd->npcentityid() ) );
			if ( tpEntityNpc == NULL )
				break;

			// NPC���Ѻ� ���ܽ�����
			if ( !( tpEntityNpc->IsFunNpc() && tpEntityNpc->IsFriendlyTo(pPlayer) ) )
			{
				return;
			}

			int nBagIndex = -1;
			if ( tpTaskEnd->has_bagindex() )
			{
				nBagIndex = tpTaskEnd->bagindex();
			}
			OnPlayerEndTask( pPlayer, tpTaskEnd->taskid(), tpTaskEnd->selectid(), nBagIndex ) ;
			break;
		}

		//  ���������������
	case ID_C2S_REQUEST_TASK_SEARCH:
		{
			PERF_FUNC( "OnPlayerSearchTask", OnPlayerSearchTask(pPlayer) );
			break;
		}

		//  ���������������
	case ID_C2S_INVITE_TASK_REQUEST:
		{
			CMessagePlayerInviteTaskRequest* tpTaskInvite = (CMessagePlayerInviteTaskRequest*) pMessage->msgpara();
			OnPlayerInviteTask(pPlayer, tpTaskInvite );
			break;
		}

		//  ��һ�Ӧ�����ߵ���������
	case ID_C2S_INVITE_TASK_RESPONSE_REQUEST:
		{
			CMessagePlayerInviteTaskResponseRequest* pTaskInvite = (CMessagePlayerInviteTaskResponseRequest*) pMessage->msgpara();
			OnPlayerReplyTaskInvite(pPlayer, pTaskInvite->srcplayername().c_str(), pTaskInvite->taskid(), pTaskInvite->agreeflag() );
			break;
		}

		// ���ʹ������ ������������
	case ID_C2S_REQUEST_OBTAINSCROLLTASK:
		{
			CMessageObtainScrollTaskRequest* pMsg = (CMessageObtainScrollTaskRequest*) pMessage->msgpara();
			OnMessagePlayerUseScroll(pPlayer, pMsg );
			break;
		}

		// �ͻ��˻�ȡ��ҰNPCͷ��
	case ID_C2S_REQUEST_GETTIP:
		{
			OnMessageRefreshNpcTip(pPlayer, pMessage );
			break;
		}

		// �����ɺ�ĳNPC�ĶԻ�
	case ID_C2S_REQUEST_ENDTALK:
		{
			OnMessagePlayerEndTalk(pPlayer, pMessage );
			break;
		}

		// ��ҽ�����Ŷ�������
	case ID_C2S_REQUEST_LOCKBAG:
		{
			OnMessagePlayerLockBaggage(pPlayer, pMessage );
			break;
		}

		// ���ȡ�¶���
	case ID_C2S_REQUEST_TAKEOFFITEM:
		{
			OnMessagePlayerTakeoffItem(pPlayer, pMessage );
			break;
		}

		// �ͻ��˻�ȡ��������б�
	case ID_C2S_REQUEST_GETFAMILYTASK:
		{
			OnMessagePlayerGeFamilyTask( pPlayer, pMessage );
			break;
		}
		// �ͻ��˻�ȡ���������б�
	case ID_C2S_REQUEST_GETCORPSTASK:
		{
			OnMessagePlayerGeCorpsTask( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_GETCOUNTRYTASK:
		{
			OnMessagePlayerGetCountryTask( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_GETCAMPTASK:
		{
			OnMessagePlayerGetCampTask( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_GETCHAIRMANTASK:
		{
			OnMessagePlayerGetChairManTasks( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_REFRESHTASK:
		{
			CMessageTaskRefreshRequest* tpTaskRefresh = (CMessageTaskRefreshRequest*) pMessage->msgpara();
			OnPlayerRefreshTask(pPlayer, tpTaskRefresh->taskid(), tpTaskRefresh->refreshitemindex(), tpTaskRefresh->npcentityid() );
			break;
		}
	case ID_C2S_REQUEST_CHECK_GROUPPUBLISH:
		{
			OnMessagePlayerCheckGroupPublishTask( pPlayer, pMessage );
			break;
		}
	case ID_C2S_REQUEST_PLAYERPUBLISHTASK:
		{
			OnMessageGroupPublishTask( pPlayer, pMessage );
			break;
		}
	default:
		{
			LOG_ERROR("TASK", "error msg id:%d", tHead.messageid() );
		}
	}
}


void CTaskModule::OnGateMessage( CEntityPlayer* pPlayer, CMessage* pMessage )
{


}

// ����ʹ��������Ϣ
void CTaskModule::OnMessagePlayerUseScroll( CEntityPlayer* pPlayer, CMessageObtainScrollTaskRequest* pMsg )
{
	int nScrollID = pMsg->scrollid();
	CTplItemScroll *tpItem = (CTplItemScroll *)CDataStatic::SearchTpl( nScrollID );
	if ( tpItem == NULL )
	{
		LOG_ERROR("TASK", "player %d used no such scroll in template! id=%d", pPlayer->GetCharID(), nScrollID );
		return;
	}

	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	if ( pProperty->BaggageHasItem( nScrollID ) <= 0 )
	{
		LOG_ERROR("TASK", "player %d(%s) has no scroll ID=%d", pPlayer->GetCharID(), pPlayer->GetCharNameShow(), nScrollID );
		return;
	}

	bool bRet = false;
	PERF_FUNC("PlayerObtainTask", bRet = PlayerObtainTask( pPlayer, tpItem->mGetTaskID, true ));

	if (bRet)
	{
		uint64_t ullGUID = 0;
		bool tBind = false;
		if (CPropertyModule::GetSingleton( ).PlayerRemoveItemByID( pPlayer, nScrollID, 1, tBind, &ullGUID) == 0)
		{
			LogEventLostItemByUse(pPlayer, ullGUID, nScrollID, 1);
		}

		LogEventPlayerAcceptTask(pPlayer, tpItem->mGetTaskID);
	}
	else
	{
		Send2ClientOprFailed(pPlayer);
	}
}
int  CTaskModule::OnPlayerInviteTask(CEntityPlayer* pPlayer, CMessagePlayerInviteTaskRequest* pMsg )
{
	int unTaskID = pMsg->taskid();
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList, return 0 );

	if ( CTaskLuaInterface::Call<int, unsigned short>(pPlayer, pList, "is_task_can_invite", unTaskID ) == 0 )
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_CANT_DO_INVITE );
		return 0;
	}

	LK_ASSERT( unTaskID > 0, return 0 );
	for (int i = 0 ; i < pMsg->playernames_size(); ++i )
	{
		CEntityPlayer* pDesPlayer = (CEntityPlayer*)CSceneLogic::GetSingleton( ).GetPlayerByName( pMsg->playernames(i).c_str());
		if ( pDesPlayer == NULL /*|| pDesProperty == NULL*/ ) // ����˲��ڱ�������
		{
			CMessageDoPlayerInviteTaskMsg msg; // ����������ڷ��������д���

			CMessage tMessage;

			msg.set_taskid( unTaskID );

			msg.mutable_router()->set_srcname( pPlayer->GetCharName() );
			msg.mutable_router()->set_desname( pMsg->playernames(i).c_str() );
			msg.mutable_router()->set_send2player( 0 );
			//msg.mutable_router()->set_sendback( 1 );
			msg.mutable_router()->set_routertype( CMessageRouter::ROUTER_NAME );

			tMessage.set_msgpara((uint32_t) &msg);

			tMessage.mutable_msghead()->set_messageid( ID_S2S_DOPLAYER_INVITE_TASK_MSG );
			if ( CSceneLogic::GetSingleton().GetPlayerByName( pMsg->playernames(i).c_str() ) == NULL )
				CSceneLogic::GetSingleton( ).Send2Player( pMsg->playernames(i).c_str(), &tMessage );
			else
				OnRouterMessage( &tMessage );

			continue;
		}
		else
		{
			SendInviteTaskMsg( pPlayer->GetCharName(), pDesPlayer,  unTaskID ) ;
		}
	}
	return 0;
}

// ����������Ϣ����
void CTaskModule::OnInviteTaskDesOffLine( CMessageDoPlayerInviteTaskMsg* pMessage )
{
	CMessageRouter* pRouter = pMessage->mutable_router();
	LK_ASSERT( pRouter != NULL , return );

	CMessagePlayerInviteTaskErrorMsg msg; 

	CMessage tMessage;

	msg.set_taskid( pMessage->taskid() );
	msg.set_myname( pRouter->desname().c_str() );
	msg.set_typeid_( ERROR_OFFLINE );

	msg.mutable_router()->set_srcname( pRouter->desname().c_str() );
	msg.mutable_router()->set_desname( pRouter->srcname().c_str() );
	msg.mutable_router()->set_send2player( 1 ); // �����ͻ��ˣ�(������)
	msg.mutable_router()->set_routertype( CMessageRouter::ROUTER_NAME );

	tMessage.set_msgpara((uint32_t) &msg);

	tMessage.mutable_msghead()->set_messageid( ID_S2C_PLAYER_INVITE_TASK_ERROR_MSG );

	CSceneLogic::GetSingleton( ).Send2Player( pRouter->srcname().c_str(), &tMessage );

}

void CTaskModule::OnMessagePlayerTakeoffItem( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	LK_ASSERT( pProperty, return );

	bool ret;
	int nBagIndex = pProperty->GetBaggage()->GetTaskLockIndex();
	if (nBagIndex != -1 ) // ����
	{
		CPropertyModule::GetSingleton().LockBaggage( pPlayer->GetEntityID(), nBagIndex, LOCKTYPE_NONE, ret );
	}
}

// �ͻ��˻�ȡ���������б�
void CTaskModule::OnMessagePlayerGeCorpsTask( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer, return );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	CMessageGetCorpsTaskResponse msg;

	// Ӧ�ͻ���Ҫ�� �����Ϣֻȡ2������
	int tTypeID[] = {TASKGROUP_CORPS_IN, TASKGROUP_CORPS_OUT, TASKGROUP_CORPS_CHALANGE, TASKGROUP_SAVEFLAG1, TASKGROUP_SAVEFLAG2,TASKGROUP_SAVEFLAG3,TASKGROUP_SAVEFLAG4};

	for ( unsigned int i = 0; i < ARRAY_CNT(tTypeID); ++i )
	{
		// ȡ�û�����б�
		lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, unsigned int>(pPlayer, pList, "get_activity_tasks", tTypeID[i] );
		int n = luaL_getn(L, -1);

		if (n >= MAX_NPC_TASK_NUM)
		{
			LOG_ERROR("TASK", " max active Task num is 64!! recv%d", n );
			n = 63;
		}

		// ��ñ��������������ɴ��� �Ա��ڷ����ͻ���
		int tTodayNum = pList->mTaskGroupMgr.GetTodayTimes(tTypeID[i]);
		for(int i =1; i<=n; ++i)
		{
			lua_rawgeti(L, -1, i);
			SingleFamilyTaskResponse* tpResp = msg.add_tasks();
			tpResp->set_taskids(lua_tinker::pop<int>(L)) ;
			tpResp->set_todaytimes(tTodayNum);
		}
	}

	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_RESPONSE_GETCORPSTASK);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}


// �ͻ��˻�ȡ���������б�
void CTaskModule::OnMessagePlayerGeFamilyTask( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer, return );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	//CMessageGetFamilyTaskRequest* pMsg = ( CMessageGetFamilyTaskRequest* )pMessage->msgpara( );
	CMessageGetFamilyTaskResponse msg;

	// Ӧ�ͻ���Ҫ�� �����Ϣֻȡ3������
	int tTypeID[4] = {TASKGROUP_FAMILY_HONNER, TASKGROUP_FAMILY_KILL, TASKGROUP_FAMILY_SEND, TASKGROUP_FAMILY_CHALANGE	};

	for ( unsigned int i = 0; i < ARRAY_CNT(tTypeID); ++i )
	{
		// ȡ�û�����б�
		lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, unsigned int>(pPlayer, pList, "get_activity_tasks", tTypeID[i] );
		int n = luaL_getn(L, -1);

		if (n >= MAX_NPC_TASK_NUM)
		{
			LOG_ERROR("TASK", " max active Task num is 64!!" );
			n = 63;
		}

		// ��ñ��������������ɴ��� �Ա��ڷ����ͻ���
		int tTodayNum = pList->mTaskGroupMgr.GetTodayTimes(tTypeID[i]);
		for(int i =1; i<=n; ++i)
		{
			lua_rawgeti(L, -1, i);
			SingleFamilyTaskResponse* tpResp = msg.add_tasks();
			tpResp->set_taskids(lua_tinker::pop<int>(L)) ;
			tpResp->set_todaytimes(tTodayNum);
		}
	}

	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_RESPONSE_GETFAMILYTASK);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}

void CTaskModule::OnMessagePlayerGetCampTask( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer, return );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	CMessageGetCampTaskResponse msg;

	// Ӧ�ͻ���Ҫ�� �����Ϣֻȡ2������
	int tTypeID[] = { TASKGROUP_CAMP_TF1,
		TASKGROUP_CAMP_TF2,
		TASKGROUP_CAMP_RB,
		TASKGROUP_CAMP_SB,
		TASKGROUP_CAMP_SQ1,
		TASKGROUP_CAMP_SQ2,
		TASKGROUP_CAMP_SQ3,
		TASKGROUP_CAMP_SQ4
	};

	for ( unsigned int i = 0; i < ARRAY_CNT(tTypeID); ++i )
	{
		// ȡ�û�����б�
		lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, unsigned int>(pPlayer, pList, "get_activity_tasks", tTypeID[i] );
		int n = luaL_getn(L, -1);

		if (n >= MAX_NPC_TASK_NUM)
		{
			LOG_ERROR("TASK", " max active Task num is 64!! recv%d", n );
			n = 63;
		}

		// ��ñ��������������ɴ��� �Ա��ڷ����ͻ���
		int tTodayNum = pList->mTaskGroupMgr.GetTodayTimes(tTypeID[i]);
		for(int i =1; i<=n; ++i)
		{
			lua_rawgeti(L, -1, i);
			SingleFamilyTaskResponse* tpResp = msg.add_tasks();
			tpResp->set_taskids(lua_tinker::pop<int>(L)) ;
			tpResp->set_todaytimes(tTodayNum);
		}
	}

	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_RESPONSE_GETCAMPTASK);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}
// �ͻ��˻�����������б�
void CTaskModule::OnMessagePlayerGetChairManTasks( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	// ����Ϣ��ʱ����
	return;
}
// �ͻ��˻�ȡ���������б�
// TODO �Ժ��ٳ���
void CTaskModule::OnMessagePlayerGetCountryTask( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer, return );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	CMessageGetCountryTaskResponse msg;

	// Ӧ�ͻ���Ҫ�� �����Ϣֻȡ2������
	int tTypeID[] = { TASKGROUP_COUNTRY7, TASKGROUP_COUNTRY_ALL };

	for ( unsigned int i = 0; i < ARRAY_CNT(tTypeID); ++i )
	{
		// ȡ�û�����б�
		lua_tinker::table ret = CTaskLuaInterface::Call<lua_tinker::table, unsigned int>(pPlayer, pList, "get_activity_tasks", tTypeID[i] );
		int n = luaL_getn(L, -1);

		if (n >= MAX_NPC_TASK_NUM)
		{
			LOG_ERROR("TASK", " max active Task num is 64!! recv%d", n );
			n = 63;
		}

		// ��ñ��������������ɴ��� �Ա��ڷ����ͻ���
		int tTodayNum = pList->mTaskGroupMgr.GetTodayTimes(tTypeID[i]);
		for(int i =1; i<=n; ++i)
		{
			lua_rawgeti(L, -1, i);
			SingleFamilyTaskResponse* tpResp = msg.add_tasks();
			tpResp->set_taskids(lua_tinker::pop<int>(L)) ;
			tpResp->set_todaytimes(tTodayNum);
		}
	}

	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_RESPONSE_GETCOUNTRYTASK);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}
void CTaskModule::OnMessagePlayerLockBaggage( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	CMessageLockBaggageRequest* pMsg = ( CMessageLockBaggageRequest* )pMessage->msgpara( );
	// ���ж��ܲ��ܷ���ȥ
	CPropertyPlayer* pProperty = (CPropertyPlayer*)pPlayer->GetProperty();
	LK_ASSERT( pProperty, return );

	CItemObject* pObj = pProperty->GetBaggage()->GetItemObjPtr(pMsg->itemindex());
	LK_ASSERT( pObj, return );

	// �ж��ǲ��ǰ�
	if (pObj->GetBindStatus() == ITEM_BINDSTATUS_FREE || pObj->GetBindStatus() == ITEM_BINDSTATUS_BINDED) // �󶨺ͷǰ󶨿��Խ�
	{
		int nBagIndex = pProperty->GetBaggage()->GetTaskLockIndex();

		bool ret;
		if (nBagIndex != -1 && nBagIndex != (int)pMsg->itemindex()) // �Ѿ����� �Ƚ���
		{
			CPropertyModule::GetSingleton().LockBaggage( pPlayer->GetEntityID(), nBagIndex, LOCKTYPE_NONE, ret );
		}

		CMessageLockBaggageResponse msg;
		msg.set_itemindex(pMsg->itemindex());
		CMessage tMessage;
		tMessage.set_msgpara((uint32_t) &msg);
		tMessage.mutable_msghead()->set_messageid(ID_S2C_LOCKBAG_RESPONSE);
		CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
		pProperty->GetBaggage()->SetTaskLockIndex(pMsg->itemindex());
		CPropertyModule::GetSingleton().LockBaggage( pPlayer->GetEntityID(), pMsg->itemindex(), LOCKTYPE_TASK_RECVITEM, ret );
	}
	else
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_ITEM_BIND_ERROR );
	}
}

// ***********************************************************
//  Function:		SendRouterMsg2Client
//  Description:	�����ͻ���·����Ϣ
//  Input:			��Ϣ
//  OutPut:			NULL
//  Return:			NULL
//  Others:
//  Date:			2009.4.1
// **********************************************************
void CTaskModule::SendRouterMsg2Client( CMessage* pMessage )
{
	Message* pUnknownMessage = (Message*) pMessage->msgpara();
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessage->GetDescriptor();
	const ::google::protobuf::Reflection*  pReflection = pUnknownMessage->GetReflection();
	if (pDescriptor == NULL || pReflection == NULL) return; 
	const ::google::protobuf::FieldDescriptor*  pFieldDescriptor = pDescriptor->FindFieldByNumber(1);
	if (pFieldDescriptor == NULL) return;
	LK_ASSERT(pFieldDescriptor->type() == ::google::protobuf::FieldDescriptor::TYPE_MESSAGE, return );
	const Message& tRouter = pReflection->GetMessage(*pUnknownMessage, pFieldDescriptor); 
	CMessageRouter* pRouter = (CMessageRouter*) &tRouter;

	if ( pRouter->sendback() == 1 )
		return;

	CEntityPlayer* pPlayer = NULL;
	if ( pRouter->routertype() == CMessageRouter::ROUTER_NAME )
	{
		pPlayer = CSceneLogic::GetSingleton().GetPlayerByName( pRouter->desname().c_str() );
		CSceneLogic::GetSingleton( ).Send2Player( pPlayer, pMessage );
	}
	else if ( pRouter->routertype() == CMessageRouter::ROUTER_CHAR )
	{
		pPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( pRouter->descharid() );
		CSceneLogic::GetSingleton( ).Send2Player( pPlayer, pMessage );
	}
}

void CTaskModule::OnMessageRefreshNpcTip( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	// һ�ɸ�Ϊ�ͻ����ϱ� ���������� 
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );
	CMessageGetTipRequest* pMsg = ( CMessageGetTipRequest* )pMessage->msgpara( );
	LK_ASSERT( pMsg, return );

	int nNpcNum = pMsg->npcentityid_size();
	LOG_DEBUG( "TASK", "OnMessageRefreshNpcTip refresh NPC num=%d\n", nNpcNum );
	LK_ASSERT( nNpcNum > 0 && nNpcNum <= CLIENTREQUESTMAX_GETTIPS ,return );

	CMessageNpcTaskTipNotice msg;
	for ( int i = 0; i < nNpcNum; ++i )
	{
		if (pMsg->idtype() == 1 ) // ��ȡ�����ͼ��ͷ�� ��ģ��ID
		{
			int temp_id = pMsg->npcentityid(i);
			msg.add_npcentityid( temp_id );
			unsigned short tip = CTaskLuaInterface::Call<unsigned short, int>( pPlayer, pList, "get_npc_tip", temp_id );
			msg.add_tip(tip) ;
		}
		else
		{
			CEntityNpc* pEntity =  dynamic_cast<CEntityNpc*>(CSceneObjManager::GetSingletonPtr()->GetObject( pMsg->npcentityid(i)) );
			if ( pEntity == NULL )
			{
				LOG_ERROR("TASK", "bad entity id-- %d!", pMsg->npcentityid(i) );
				continue;
			}
			else if( pEntity->IsFunNpc() == false && pEntity->IsOgre() == false )
			{
				LOG_ERROR("TASK", "bad entity id not npc!-- %d!", pMsg->npcentityid(i) );
				continue;
			}

			if( pEntity->IsWithinViewDistance( pPlayer ) == false )
				continue;

			CProperty* pPropty = pEntity->GetProperty();
			LK_ASSERT( pPropty, continue );

			unsigned short tTip = GetNpcTip( pPlayer, pPropty->GetPropertyTempID(), pList, pMsg->npcentityid(i) );
			LOG_DEBUG( "TASK", "ReSendAllNpcTipInEye send NPC TIP, temp ID=%d, tip=%d\n", pPropty->GetPropertyTempID(), tTip);

			msg.add_npcentityid( pEntity->GetEntityID() );
			msg.add_tip(tTip) ;
		}
	}
	msg.set_idtype(pMsg->idtype());
	CMessage   tMessage;
	tMessage.set_msgpara((uint32_t) &msg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_NOTICE_NPCTASKTIP);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );

}

// ֪ͨ�ͻ��˸�����������
void CTaskModule::SendUpdateConditions2Client( CEntityPlayer* pPlayer, CMessageUpdateTaskConditions* pMsg )
{
	LK_ASSERT( pPlayer, return );
	LK_ASSERT( pMsg, return );
	if ( pMsg->contions_size() == 0 )
		return;
	CMessage   tMessage;
	tMessage.set_msgpara((uint32_t) pMsg);
	tMessage.mutable_msghead()->set_messageid(ID_S2C_UPDATE_CONDITIONS);
	CSceneLogic::GetSingleton( ).Send2Player( pPlayer, &tMessage );
}

//  ·����Ϣ
void CTaskModule::OnRouterMessage( CMessage* pMessage )
{
	const CMessageHead&  tHead = pMessage->msghead();

	switch(tHead.messageid())
	{
	case ID_S2S_DOPLAYER_INVITE_TASK_MSG:
		{
			CMessageDoPlayerInviteTaskMsg* pMsg = (CMessageDoPlayerInviteTaskMsg*) pMessage->msgpara();

			CMessageRouter* pRouter = pMsg->mutable_router();
			LK_ASSERT( pRouter != NULL , return );

			if ( pRouter->routerreason() == CMessageRouter_EMRouterReason_REASON_OFFLINE 
				|| pRouter->routerreason() == CMessageRouter_EMRouterReason_REASON_REDIRECT )
			{
				OnInviteTaskDesOffLine( pMsg );
			}
			else
			{
				OnTaskInvitedRoutMsg( pRouter->srcname().c_str(), pRouter->desname().c_str(), (unsigned short)pMsg->taskid() );
			}

			break;
		}
	case ID_S2C_INVITE_TASK_RESPONSE_NOTICE:
	case ID_S2C_PLAYER_INVITE_TASK_ERROR_MSG:
		{
			SendRouterMsg2Client( pMessage );
			break;
		}
	}

}



//************************************************/
//	   ���ܣ���������ϵͳ						 //
//	   ʱ�䣺2011/09/07							 //
//     ���ߣ�ZGC								 //
//     �汾��0.8								 //
//************************************************/


// ����������Ϣ  �������ӵ��ͻ��˵�����֮��  ֱ�ӷ��͸�����
void CTaskModule::OnMessageGroupPublishTask( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer,  return );	
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );
	CMessagePublishGroupTaskRequest* pMsg = ( CMessagePublishGroupTaskRequest* )pMessage->msgpara( );
	LK_ASSERT( pMsg,  return );

	bool ret = CheckPublishCondition(pPlayer, pMsg->taskid());
	if (ret == false)
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, ERROR_TASK_PUBLISH_CONDITION_UNENOUGH );
		return;
	}
	else
	{
		unsigned int CharID = pPlayer->GetCharID();
		int vNeedMoney = GetGroupNeedMoney(pPlayer, pMsg->publishtype(), pMsg->taskid());

		//  �����ط���Ϣ
		CMessage tMsg;
		CMessageGatePublishGroupRequest tPublish;
		tPublish.set_charid(CharID);
		tPublish.set_taskid(pMsg->taskid());
		tPublish.set_publishtype(pMsg->publishtype());
		tPublish.set_paygroupmoney(vNeedMoney);
		tPublish.set_taskstate(PUBLISHED_TASK);
		tMsg.mutable_msghead()->set_messageid( ID_S2G_REQUEST_PLAYERPBULISHTASK );
		tMsg.set_msgpara( (uint32)&tPublish );

		CSceneLogic::GetSingletonPtr( )->Send2Gate( &tMsg );

	}
	
}

void CTaskModule::OnMessagePlayerCheckGroupPublishTask( CEntityPlayer* pPlayer, CMessage* pMessage )
{
	LK_ASSERT( pPlayer,  return );	
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );
	CMessageCheckGroupPublishRequest* pMsg = ( CMessageCheckGroupPublishRequest* )pMessage->msgpara( );
	LK_ASSERT( pMsg,  return );

	unsigned int CharID = pPlayer->GetCharID();
	
		//  �����ط���Ϣ
	CMessage tMsg;
	CMessageGateCheckGroupPublishRequest tPublish;
	tPublish.set_charid(CharID);
	tPublish.set_publishtype(pMsg->publishtype());
	tMsg.mutable_msghead()->set_messageid( ID_S2G_REQUEST_CHECKPUBLISHBOARD );
	tMsg.set_msgpara( (uint32)&tPublish );

	CSceneLogic::GetSingletonPtr( )->Send2Gate( &tMsg );

}



//  ���ػ�Ӧ�������������������  ��ת��������
void CTaskModule::OnMessageGatePublishResponse(CMessage* pMessage )
{
		
	CMessageGatePublishGroupResponse* pMsg = ( CMessageGatePublishGroupResponse* )pMessage->msgpara( );
	LK_ASSERT( pMsg,  return );

	CEntityPlayer* pPlayer = ( CEntityPlayer* ) CSceneLogic::GetSingleton().GetPlayerByCharID( pMsg->charid() );
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	// �ظ������������

	if (pMsg->result() == SUCCESS)
	{
		pList->InsertPublishTask(pMsg->taskid(), pMsg->publishtype(), PUBLISHED_TASK);

		LogEventPlayerPublishTask(pPlayer, pMsg->taskid(), pMsg->publishtype());

		CMessage tMessage;
		CMessagePublishGroupTaskResponse tState;
		tState.set_taskid(pMsg->taskid());
		tState.set_publishtype(pMsg->publishtype());
		tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_PLAYERPUBLISHTASK );
		tMessage.set_msgpara( (uint32)&tState );

		CSceneLogic::GetSingletonPtr( )->Send2Player( pPlayer,&tMessage );
	}
	// ��������δ�ɹ�
	else
	{
		CPropertyModule::GetSingleton().SendProErrorNotice( pPlayer, pMsg->result());
	}
}


//  ���ػ�Ӧ��Ҳ鿴��������չ�������
void CTaskModule::OnMessageChechPublishResponse(CMessage* pMessage )
{

	CMessageGateCheckGroupPublishResponse* pMsg = ( CMessageGateCheckGroupPublishResponse* )pMessage->msgpara( );
	LK_ASSERT( pMsg,  return );

	CEntityPlayer* pPlayer = ( CEntityPlayer* ) CSceneLogic::GetSingleton().GetPlayerByCharID( pMsg->charid() );
	LK_ASSERT( pPlayer,  return );	
	CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr()->GetObject(pPlayer->GetTaskToken( ));
	LK_ASSERT( pList,  return );

	// �ظ������鿴������
	if(pMsg->result() == SUCCESS)
	{
		PBGroupInfo *pInfo = pMsg->mutable_groupinfo();
		GroupTempInfo _newInfo( pInfo->groupid(), pInfo->grouplevel(), pInfo->groupmoney(), pInfo->playerposition() );
		pList->SetGroupInfo(_newInfo);

		CMessage tMessage;
		CMessageCheckGroupPublishResponse tState;

		if (pMsg->tasks_size() == 0)
		{
			pList->mCorpsPublishTask.initailize();
			PBPubslishList *pTask = tState.add_tasks();
			pTask->set_taskid(UNEXIST_TASK);
			pTask->set_taskstate(UNEXIST_TASK);
		}

		else
		{
			for( int i = 0; i < pMsg->tasks_size(); ++i )
			{
				PBGroupTasks tpTask = pMsg->tasks(i);
				int SelfState = pList->GetPublishStateByType(tpTask.taskid(), pMsg->publishtype());

				if (tpTask.taskstate() == 1)// ���������δ����  ��������ϵ�����״̬Ҳ��δ����
				{
					pList->InsertPublishTask(tpTask.taskid(), pMsg->publishtype(), tpTask.taskstate());
				}
				else if(tpTask.taskstate() < SelfState)		// �����������ÿ��������ϵ�״̬����һ������������ϵ�����״̬Ϊ׼
				{
					tpTask.set_taskstate(SelfState);
				}
				else
				{
					pList->InsertPublishTask(tpTask.taskid(), pMsg->publishtype(), tpTask.taskstate());
				}

				PBPubslishList *pTask = tState.add_tasks();
				pTask->set_taskid(tpTask.taskid());
				pTask->set_taskstate(tpTask.taskstate());
			}
		}
		
		tState.set_publishtype(pMsg->publishtype());
		tMessage.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_CHECK_GROUPPUBLISH );
		tMessage.set_msgpara( (uint32)&tState );

		CSceneLogic::GetSingletonPtr( )->Send2Player( pPlayer, &tMessage );
	}
}

// �������ط�������Ϣ
void CTaskModule::OnGateMessage( CMessage* pMessage)
{
	LK_ASSERT(pMessage, return);
	const CMessageHead&  tHead = pMessage->msghead();

	switch(tHead.messageid())
	{
	case ID_G2S_RESPONSE_PBULISHTASKRESULT: 
		{
			OnMessageGatePublishResponse( pMessage );
			break;
		}
	case ID_G2S_RESPONSE_CHECKPUBLISHBOARD:
		{
			OnMessageChechPublishResponse( pMessage );
			break;
		}
	default:
		{
			break;
		}
	}
}
