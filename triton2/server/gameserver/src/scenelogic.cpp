// ********************************************************************** //
// Logic.cpp
// �����������߼�
// ��ɳ����������߼�ģ��Ĵ���,�������Ϣ���ɸ����е��߼�ģ��
//
// Author: Black
// ********************************************************************** //
#include "stdafx.hpp"
#include "servercore.h"
#include "base.h"
#include "servercore.h"
#include "clienthandle.h"
#include "db_msg_pb.hxx.pb.h"
#include "servermessage_in.h"
#include "coremessage_pb.hxx.pb.h"
#include "taskmodule.h"
#include "npcmodule.h"
#include "teammodule.h"
#include "chatmodule.h"
#include "trademodule.h"
#include "stallmodule.h"
#include "friendmodule.h"
#include "friendmanager.h"
#include "mailmodule.h"
#include "timerinterface.h"
#include "maildboperate.h"
#include "sceneobj_manager.h"
#include "sceneobj_manager_imp.h"
#include "gmmodule.h"
#include "gmmessage_pb.hxx.pb.h"
#include "activitymodule.h"
#include "familymodule.h"
#include "corpsmodule.h"
#include "maptplmanager.h"
#include "ibstoremodule.h"
#include "rankmodule.h"
#include "proclient_svr.h"
#include "mapmodule.h"
#include "propertymodule.h"
#include "teammodule.h"
#include "dirtyword.h"
#include "message_queue.h"
#include "message_dispatcher.h"
#include "mapobjmanager.h"
#include "repetionmodule.h"
#include "judgemodule.h"
#include "maildboperate.h"
#include "property_pb.hxx.pb.h"
#include <google/protobuf/stubs/common.h>
#include "achievemodule.h"
#include "worldmodule.h"
#include "judgemodule.h"
#include "boursemodule.h"
#include "marriagemodule.h"
#include "lk_proto.h"
#include "speedup_checker.h"
#include "property.h"
#include "mailmanager.h"
#include "mailmodule.h"
#include "mailtype.h"
#include "ActivityYqs.h"
#include "globalmodule.h"
#include "scenelogic.h"

extern void Show();

using namespace SceneServer;
// ********************************************************************** //
// CSceneServer
// ********************************************************************** //
template<> CSceneServer* CSingleton< CSceneServer >::spSingleton = NULL;
 
CSharedMem* CSceneServer::mShmPtr = NULL;

CSceneServer::CSceneServer( ) 
{
}

CSceneServer::~CSceneServer( ) 
{ 
} 

void* CSceneServer::operator new( size_t size )
{
	return ( void* ) mShmPtr->CreateSegment( size );
}

void  CSceneServer::operator delete( void* pointer )
{

}

void* CSceneServer::operator new(size_t size, const char* file, int line)
{
	return operator new ( size );
}
void CSceneServer::operator delete(void* pointer, const char* file, int line)
{

}


int CSceneServer::PrepareToRun()
{
	CSceneLogic::GetSingletonPtr( )->Launch();

	mShmPtr->SetInitMode( SHM_INIT );
	CObj::msCreateMode = 1;
	return 0;
}

void CSceneServer::CheckRunFlags()
{
	if ( IsRunFlagSet( EFLG_CTRL_QUIT ) )
	{
		ClearRunFlag( );

		LOG_NOTICE( "default", "recv signal to shutdown server" );
		CSceneLogic::GetSingletonPtr()->SetServerStatus( EM_SERVERSTATUS_SHUDOWNING );
	}
	else if ( IsRunFlagSet( EFLG_CTRL_RELOAD ) )
	{
		ClearRunFlag( );

		// �ȼ���ָ������
		LOG_NOTICE( "default", "xyj-gameserver  reload  appointed config  ! ..." );
		printf("xyj-gameserver  reload  appointed config ! ...\n");
		int nRetCode = ReLoadAppointedConfig();

		// ָ�����ü��ز��ɹ���reloadȫ������
		if (nRetCode != SUCCESS)
		{
			LOG_NOTICE( "default", "xyj-gameserver reload appointed cfg fail ..." );
			printf( "xyj-gameserver reload appointed cfg fail ...\n" );

			LOG_NOTICE( "default", "xyj-gameserver got command to reload all cfg , now reloading ..." );
			printf( "Have got command to reload all cfg , now reloading ...\n" );

			//CSceneCfgManager::GetSingletonPtr()->Initialize( (char*) ("../config/data/scene_config/sceneconfig.xml") );
			CSceneCfgManager::GetSingletonPtr()->Initialize( const_cast<char*>( CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(), const_cast<char*>("scene_config/sceneconfig.xml")) ));
			ReadConfig();
			CModuleManager::GetSingleton( ).LoadConfig( );

			CSpeedChecker::ShowConfig( );

			LOG_NOTICE( "default", "xyj-gameserver  reload all cfg complte ! ..." );
			printf( "reload all cfg complte ! ...\n" );
			// do reload
		}
		else
		{
			LOG_NOTICE( "default", "xyj-gameserver  reload  appointed config complte ! ..." );
			printf("xyj-gameserver  reload  appointed config complte ! ...\n");
		}
	}	
	else if ( IsRunFlagSet( EFLG_CTRL_COREDUMP ) )
	{
		ClearRunFlag( );

		LOG_INFO( "default", "coredump complte ! ..." );

		WRITE_COREDUMP("core.scenserver");
	}
}

void CSceneServer::SetRunFlag( int vFlag )
{
	mRunFlag = vFlag;
}

void CSceneServer::ClearRunFlag( )
{
	mRunFlag = EFLG_CTRL_NO;
}

bool CSceneServer::IsRunFlagSet( int vFlag )
{
	return mRunFlag == vFlag;
}

void CSceneServer::Run ()
{
    CSpeedChecker::ShowConfig( );

	while ( true )
	{
		// ������б�־( �������������ļ�/ֹͣ������ )
		CheckRunFlags();

		// ��鶨ʱ��
		CheckTimer();
		
		// ���շ�������Ϣ����Ϣ����(����ѭ��������N��)
		RecvServerMsg(2000);
		
		// ���տͻ�����Ϣ����Ϣ����(����ѭ��������N��)
		RecvClientMsg(2000);

#ifdef _USE_MESSAGE_QUEUE_
		// ������Ϣ�����е���Ϣ
		CMessageDispatcher::GetSingletonPtr( )->DispachMsg( );
#endif

		// ����Ƿ���ȫ����
		if( CheckLaunchServer() == 1 )
		{
			break;
		}
	}
}

void CSceneServer::OnMessage( int vCommHandle, CMessage* pMessage )
{
}

void CSceneServer::OnClose( int vCommHandle )
{
	return;
}

unsigned int CSceneServer::CountSize()
{
	unsigned int tTempSize = 0;
	unsigned int tSize = 0;
	
	tTempSize = sizeof( CSceneServer );
	tSize += tTempSize;
	LOG_INFO( "default", "SceneServer::CountSize() = %d", tTempSize );

	tTempSize = CSceneLogic::CountSize();
	tSize += tTempSize;
	LOG_INFO( "default", "CSceneLogic::CountSize() = %d", tTempSize );

	tTempSize = CClientHandle::CountSize();
	tSize += tTempSize;
	LOG_INFO( "default", "CClientHandle::CountSize() = %d", tTempSize );

	tTempSize = CSceneObjManager::CountSize();
	tSize += tTempSize;
	LOG_INFO( "default", "CSceneObjManager::CountSize() = %u", tTempSize );

	tTempSize = CMessageQueue::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CMessageQueue::CountSize() = %d", tTempSize );

	tTempSize = CSceneCfgManager::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CSceneCfgManager::CountSize() = %d", tTempSize );

	tTempSize = CTimerMng::CountSize();
	tSize += tTempSize;
	LOG_INFO( "default", "CTimerMng::CountSize() = %d", tTempSize );

	tTempSize = CPropertyModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CPropertyModule::CountSize() = %d", tTempSize );

	tTempSize= CMapModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CMapModule::CountSize() = %d", tTempSize );

	tTempSize = CNpcModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CNpcModule::CountSize() = %d", tTempSize );

	tTempSize = CTeamModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CTeamModule::CountSize() = %d", tTempSize );

	tTempSize = CChatModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CChatModule::CountSize() = %d", tTempSize );

	tTempSize = CTaskModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CTaskModule::CountSize() = %d", tTempSize );

	tTempSize = CFriendModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CFriendModule::CountSize() = %d", tTempSize );

	tTempSize = CMailModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CMailModule::CountSize() = %d", tTempSize );

	tTempSize = CStallModule::CountSize();
	tSize += tTempSize;
	LOG_INFO( "default", "CStallModule::CountSize() = %d", tTempSize );

	tTempSize = CGMModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CGMModule::CountSize() = %d", tTempSize );

	tTempSize = CActivityModule::CountSize();
	tSize += tTempSize;
	LOG_INFO( "default", "CActivityModule::CountSize() = %d", tTempSize );

	tTempSize = CMapTplManager::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CMapTplManager::CountSize() = %d", tTempSize );

	tTempSize = CCreatorManager::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CCreatorManager::CountSize() = %d", tTempSize );
	
	tTempSize = CFamilyModule::CountSize( );
	tSize += tTempSize;
	LOG_DEBUG( "default", "CFamilyModule::CountSize() = %d", tTempSize );
	
	
	tTempSize = CIbStoreModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CIbStoreModule::CountSize() = %d", tTempSize );
	

	tTempSize = CCorpsModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CCorpsModule::CountSize() = %d", tTempSize );

	tTempSize = CRankModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CRankModule::CountSize() = %d", tTempSize );	

	tTempSize = CRepetionModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CRepetionModule::CountSize() = %d", tTempSize );	

	tTempSize = CTradeModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CTradeModule::CountSize() = %d", tTempSize );	

	tTempSize = CJudgeModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CJudgeModule::CountSize() = %d", tTempSize );	

	tTempSize = CWorldModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CWorldModule::CountSize() = %d", tTempSize );	

	tTempSize = CAchieveModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CAchieveModule::CountSize() = %d", tTempSize );	
	
	tTempSize = CMarriageModule::CountSize( );
	tSize += tTempSize;
	LOG_INFO( "default", "CMarriageModule::CountSize() = %d", tTempSize );

	tTempSize = CGlobalModule::CountSize();
	tSize += tTempSize;
	LOG_INFO( "default", "CGlobalModule::CountSize() = %d", tTempSize );

	return tSize;
}

//************************************
// Method:    ShuntDownServer
// FullName:  SceneServer::CSceneServer::ShuntDownServer
// Access:    public 
// Returns:   int
// Qualifier: ��ȫ�رշ��������ߵ�������ң���õȴ��̳ɹ����˳�
//************************************
//void CSceneServer::ShutDownServer()
//{
//	// ֹͣ���������
//	CSceneLogic::GetSingletonPtr( )->ShutDownServer( );
//
//	//CSceneLogic::GetSingletonPtr( )->KickAllExcept( 0 );
//	
//}

int CSceneServer::ProcessTimeOutMsg( CMessage* vMsg )
{
	LK_ASSERT( vMsg && vMsg->msghead().messageid() == ID_INTER_TIMEOUT, return -1 );
	
	CTimerItem* pTimerItem = (CTimerItem*) vMsg->msgpara();

	switch( pTimerItem->mOtherInfo[0] )
	{
		case MESSAGE_PROPERTY:
			CPropertyModule::GetSingletonPtr( )->OnTimeoutMessage( vMsg );
			break;
		case MESSAGE_ACTIVITY:
			CActivityModule::GetSingletonPtr( )->OnTimeoutMessage( vMsg );
			break;
		case MESSAGE_REPETION:
			CRepetionModule::GetSingletonPtr( )->OnTimeoutMessage( vMsg );
			break;
		case MESSAGE_MARRIAGE:
			CMarriageModule::GetSingleton().OnTimeoutMessage( vMsg );
			break;
		default:
			break;
	}
	
	return 0;
}

// ����ȫ�ַ���������Ϣ
int CSceneServer::ProcessDunserverMsg( CMessage* vMsg )
{
	LK_ASSERT( vMsg != NULL, return -1 )	
	CGlobalModule::GetSingleton().OnServerMessgage( vMsg );
}

int CSceneServer::ProcessClientMsg( CMessage* pMessage )
{
	LK_ASSERT(pMessage != NULL, return -1);

	// �������Ƿ���������(��ȫ�˳����̲������������)
	if(  CSceneLogic::GetSingletonPtr()->GetServerStatus() != EM_SERVERSTATUS_RUN )
		return 0;

	// �õ���Ҷ���
	CEntityPlayer* tpPlayer = (CEntityPlayer*)CSceneObjManager::GetSingletonPtr()->GetObject( pMessage->msghead().srcid() );
	if ( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "Invalid Player obj_id %d while ProcessClientMsg", pMessage->msghead().srcid() );
		return -1;
	}
	
	LK_ASSERT(pMessage->has_msghead() == true, return -1);
	unsigned short nModuleClass =  REGION_OF_MESSAGE( pMessage->msghead().messageid());
	
	// �����׷�ٵ��ʺţ������д��־����
	if ( tpPlayer->GetIfTracePlayer() )
	{
		tpPlayer->WriteMsgInfo( pMessage );
	}

	// ��֤�ͻ���������Ϣ���к�
	if( pMessage->msghead().msgseq() > tpPlayer->GetCurRequestSeq() )
	{
		tpPlayer->SetCurRequestSeq( pMessage->msghead().msgseq() );
	}
	else if(  pMessage->msghead().msgseq() < tpPlayer->GetCurRequestSeq() )
	{
		LOG_ERROR( "default", "[%s:%d] player %s:%d invaid msgseq %d,server now is %d, msgid %d",
			__FUNCTION__, __LINE__, tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(),
			pMessage->msghead().msgseq(), tpPlayer->GetCurRequestSeq(), pMessage->msghead().messageid() );
		return -1;
	}
	// ��ǰֵ�ۼ�
	tpPlayer->SetCurRequestSeq( 1 + tpPlayer->GetCurRequestSeq()  );

	// ���ֻ���ڳ����У����ܺͳ�����������ͨ
	if ( tpPlayer->GetCommState( ) == CEntityPlayer::STATE_INMAP )
	{
		tpPlayer->GetClientInfo( )->m_tLastActiveTime = time(NULL); // ����Ծʱ��

		// ֻ������ڳ����вż�ⷢ��Ƶ��
		bool tRet = CSceneLogic::GetSingleton( ).CheckMsgFrequency( tpPlayer );
		if ( !tRet )
		{
			CSceneLogic::GetSingleton().KickPlayer( tpPlayer->GetCharID(), EM_KICKOUT_UNKOWNACTION );
			LOG_ERROR( "default", " Player charid: %d name: %s send message too frequency ", tpPlayer->GetCharID(), tpPlayer->GetCharNameShow() );
			return -1;
		}

		switch (nModuleClass)
		{
		case MESSAGE_CORE:
			{
				OnGlobalClientMessge( tpPlayer, pMessage );
				break;
			}
		case MESSAGE_PROPERTY:
			{
				CPropertyModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}
		case MESSAGE_MAP:
			{
				CMapModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}
		case MESSAGE_TASK:
			{
				CTaskModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}
		case MESSAGE_CHAT:
			{
				CChatModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}
		case MESSAGE_FRIEND:
			{			
				CFriendModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}
		case MESSAGE_TEAM:
			{	
				CTeamModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}
		case MESSAGE_MAIL:
			{
				CMailModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}			
		case MESSAGE_TRADE:
			{
				CTradeModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}			
		case MESSAGE_STALL:
			{
				CStallModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}
		case MESSAGE_ACTIVITY:
			{
				CActivityModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}			
		case MESSAGE_FAMILY:
			{		
				CFamilyModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;	
			}
		case MESSAGE_CORPS:
			{
				CCorpsModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;	 
			}			
		case MESSAGE_RANK:
			{
				CRankModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}
		case MESSAGE_REPETION:
			{
				CRepetionModule::GetSingletonPtr( )->OnClientMessage( tpPlayer, pMessage );
			}
			break;
		case MESSAGE_IB:
			{
				CIbStoreModule::GetSingletonPtr()->OnClientMessage(tpPlayer, pMessage);
			break;
			}
		case MESSAGE_JUDGE:
			{
				CJudgeModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}

		case MESSAGE_COUNTRY:
			{
				CWorldModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}

		case MESSAGE_ACHIEVE:
			{
				CAchieveModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}
		case MESSAGE_MARRIAGE:
			{
				CMarriageModule::GetSingleton().OnClientMessage( tpPlayer, pMessage );
				break;
			}
		case MESSAGE_BOURSE:
			{
				CBourseModule::GetSingletonPtr( )->OnClientMessage( tpPlayer, pMessage );
				break;
			}	

		default:
			{
				LOG_ERROR("default", "[%s:%d]No Action fo MessageID(%d)",  __FUNCTION__, __LINE__, pMessage->msghead().messageid());
				break;
			}
		}
	}
	else
	{
		if( nModuleClass == MESSAGE_CORE )
		{
			OnGlobalClientMessge( tpPlayer, pMessage );
		}
	}
	// �ɵ�ɾ���б���Ķ���
	CSceneLogic::GetSingleton().DoDeleteList();
	return 0;
}

//************************************
// Method:    OnGlobalClientMessge
// FullName:  SceneServer::CSceneServer::OnGlobalClientMessge
// Access:    public 
// Returns:   int
// Qualifier: �������Կͻ��˵���Χ��Ϣ���б���ģ����Ϣ
// Parameter: CMessage * pMsg
// Parameter: CEntityPlayer * pPlayer
//************************************
int CSceneServer::OnGlobalClientMessge ( CEntityPlayer* pPlayer, CMessage* pMsg )
{

	switch( pMsg->msghead().messageid() )
	{
		// �ͻ��������뿪��Ϸ
	case  ID_C2S_REQUEST_LEAVEGAME:
		{
			OnMessageLeaveGameRequestEvent( pMsg, pPlayer ) ;
			break;
		}
		// �ͻ���������볡��
	case  ID_C2S_REQUEST_REDIRECTSCENE:
		{
			OnMessageRedirectSceneRequestEvent( pMsg, pPlayer );
			break;
		}
		// �ͻ���������볡��
	case ID_C2S_REQUEST_LOGINSCENE:
		{
			OnMessageLoginSceneRequestEvent( pMsg, pPlayer );	
			break;
		}
		// �ͻ������󷵻�����
	case ID_C2S_REQUEST_RETURN2GATE:
		{
			OnMessageReturn2GateRequestEvent( pMsg, pPlayer );	
			break;
		}
		// �ͻ���ping����������
	case ID_C2S_REQUEST_PING:
		{
			OnMessagePlayerPingRequest( pMsg, pPlayer );
			break;
		}
		// ��¼�ͻ���������Ϣ
	case ID_C2S_REQUEST_CLIENTINFO:
		{
			//TODO: û��ǿ������Ļ�����ͳ�ƹ��ܹر�
			OnMessageClientInfoRequest( pMsg, pPlayer);
			break;
		}
		// ����ͻ��˷��������
	case ID_C2S_NOTIFY_CLIENTANTIBOTDATA:
		{
			OnMessageClientAntiBotDataNotify( pMsg, pPlayer );
			break;
		}

		// ����ͻ����ϱ������ģ���������
	case ID_C2S_NOTIFY_CLIENTANTIBOTSTARTRET:
		{
			OnMessageClientAntiBotStartRetNotify( pMsg, pPlayer );
			break;
		}
	case ID_C2S_REQUEST_INVITE_CAMP:
		{
			OnMessageInviteCamp( pPlayer, pMsg);
			break;
		}
	case ID_C2S_REQUEST_CHANGE_CAMP:
		{
			OnMessageChangeSingleCamp( pPlayer,pMsg);
			break;
		}

	case ID_C2S_REQUEST_CHANGE_CAMP_CONDITION:
		{
			OnMessageChangeCampConditionRequst( pPlayer,pMsg);
			break;
		}
	case ID_S2C_NOTIFY_CHANGE_CAMP_SUCCESED:
		{
			OnMessageChangeCampSuccesBroadCast(pPlayer,pMsg);
			break;
		}

	default:
		{
			LOG_ERROR("default", "No Action fo MessageID(%d)",  pMsg->msghead().messageid());
			break;
		}
	}

	return 0;
}

int CSceneServer::ProcessDataMsg( CMessage* vMsg )
{
	LK_ASSERT( vMsg != NULL, return -1 );

	switch( vMsg->msghead().messageid() )
	{
	case ID_S2S_EXECUTESQL_RESPONSE:
		{
			CSceneLogic::GetSingletonPtr( )->OnFireSession( vMsg );
			break;
		}
	case ID_D2S_LOADPLAYERITEMINFO_RESPONSE:
		{
			CSceneLogic::GetSingletonPtr()->OnMessageLoadPlayerItemInfoFromDB( vMsg );	
			break;
		}

	case ID_D2S_SAVEPLAYERITEMINFO_RESPONSE:
		{	
			CSceneLogic::GetSingletonPtr()->OnMessageSaveItemInfoToDBResponse( vMsg );
			break;
		}
	case ID_D2S_LOADPLAYERPROPERTY_RESPONSE:
		{
			CSceneLogic::GetSingletonPtr( )->OnMessageLoadPlayerProperty( vMsg );
		}
		break;
	case ID_D2S_BOURSE_PLAYER_NOTICE:
		{
			CBourseModule::GetSingletonPtr( )->PlayerSelfDocListNotice( vMsg );
		}
		break;
	case ID_D2S_BOURSE_ACCOUNT_NOTICE:
		{
			CBourseModule::GetSingletonPtr( )->OnMessageD2SBourseAccountNotice( vMsg );	
		}
		break;
	case ID_D22_BOURSE_LOG:
		{
			CBourseModule::GetSingletonPtr( )->OnMessageS2LBourseLog( vMsg );
		}
		break;
	case ID_D2S_BOURSE_LOG:
		{
			CBourseModule::GetSingletonPtr( )->OnMessageD2SBourseLog( vMsg );
		}
		break;
	default:
		{
			LOG_ERROR( "default", "unkown data message id %d", vMsg->msghead().messageid() );
			break;
		}
	}
	return 0;
}


//************************************
// Method:    OnRouterMessageByModule
// FullName:  SceneServer::CSceneServer::OnRouterMessageByModule
// Access:    public 
// Returns:   int
// Qualifier: �����������ص�·����Ϣ
// Parameter: CMessage * vMsg
//************************************
int CSceneServer::OnRouterMessageByModule (CMessage* vMsg)
{
	LK_ASSERT(vMsg != NULL && vMsg->msgpara() != 0, return -1);
	Message* pUnknownMessage = (Message*) vMsg->msgpara();

	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessage->GetDescriptor();
	const ::google::protobuf::Reflection*  pReflection = pUnknownMessage->GetReflection();
	LK_ASSERT ( pDescriptor != NULL && pReflection != NULL, return -1 ); 

	// ȡ�õ�һ���ֶΣ���������CMessageRouter ����
	const ::google::protobuf::FieldDescriptor*  pFieldDescriptor = pDescriptor->FindFieldByNumber(1);
	LK_ASSERT(pFieldDescriptor != NULL, return -1);
	LK_ASSERT(pFieldDescriptor->type() == ::google::protobuf::FieldDescriptor::TYPE_MESSAGE, return -1);

	const Message& tRouter = pReflection->GetMessage(*pUnknownMessage, pFieldDescriptor); 		
	CMessageRouter* tpRouterMessage = (CMessageRouter*)&tRouter;

	// ����Ƿ���Ŀ����ҵ�
	if ( tpRouterMessage->sendback() == 0 )
	{
		// �ж���Ϣ��Ŀ������Ƿ����, �������򷵻�
		if ( tpRouterMessage->routertype() == CMessageRouter::ROUTER_NAME )
		{
			CEntityPlayer* tpPlayer = CSceneLogic::GetSingletonPtr( )->GetPlayerByName( tpRouterMessage->desname().c_str() );
			if (tpPlayer == NULL) 
			{
				LOG_ERROR("default", "[%s:%d] player %s dosn't exist ", __FUNCTION__, __LINE__, tpRouterMessage->desname().c_str() );
				return -1;
			}
		}
		else if ( tpRouterMessage->routertype() == CMessageRouter::ROUTER_CHAR )
		{
			if (tpRouterMessage->descharid() != 0 )
			{
				CEntityPlayer* tpPlayer = CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( tpRouterMessage->descharid() );
				if (tpPlayer == NULL) 
				{
					LOG_ERROR("default", "[%s:%d] player %d dosn't exist", __FUNCTION__, __LINE__, tpRouterMessage->descharid());
					return -1;
				}
			}
		}
		else
		{
			LOG_ERROR("default", "[%s:%d] wrong type", __FUNCTION__, __LINE__ );
			return -1;
		}
	}

	// Ŀ��ģ����Ӧ��Ϣ����Դģ����Ӧ��ص���Ϣ
	unsigned short nModuleClass =  REGION_OF_MESSAGE( vMsg->msghead().messageid() ) ;
	switch( nModuleClass )
	{
		// ����ģ��·����Ϣ
		case MESSAGE_CHAT: 
		{
			CChatModule::GetSingleton().OnRouterMessage(vMsg);
			break;
		}
		// ����ģ��·����Ϣ
		case MESSAGE_FRIEND:
		{
			CFriendModule::GetSingleton().OnRouterMessage(vMsg);
			break;
		}
		// ����ģ��·����Ϣ
		case MESSAGE_PROPERTY:
		{
			CPropertyModule::GetSingleton().OnRouterMessage(vMsg);
			break;
		}
		// ����ģ��·����Ϣ
		case MESSAGE_TASK:
		{
			CTaskModule::GetSingleton().OnRouterMessage(vMsg);
			break;
		}
		// �ʼ�ģ��·����Ϣ
		case MESSAGE_MAIL:
		{
			CMailModule::GetSingleton().OnRouterMessage(vMsg);
			break;
		}
		
		// ���ģ�����Ϣ
		case MESSAGE_MARRIAGE:
		{
			CMarriageModule::GetSingleton().OnRouterMessage( vMsg );
			break;
		}		
		

		default:
		{
			LOG_ERROR("default", "[%s:%d]there is no action for message(0x%x)", 
				__FUNCTION__, __LINE__, vMsg->msghead().messageid());
			break;
		}
	}

	return 0;
}

int CSceneServer::ProcessRouterMsg( CMessage* vMsg )
{
	LK_ASSERT( vMsg != NULL, return -1 );
	
	// �ж��Ƿ��Ƿ������ң�������߾��ŵ���Ϣ
	if ( vMsg->mutable_msghead()->dstfe() == FE_COUNTRY	)
	{
		CSceneLogic::GetSingleton().SendSceneMessage( vMsg, vMsg->mutable_msghead()->dstid() );
		return 0;
	}
	if ( vMsg->mutable_msghead()->dstfe() == FE_FAMILY || vMsg->mutable_msghead()->dstfe() == FE_CORPS )
	{
		CEntityPlayer *tpPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( vMsg->mutable_msghead()->dstid() );
		if ( tpPlayer != NULL )
		{
			CSceneLogic::GetSingleton().Send2Player( tpPlayer, vMsg );
		}		
		return 0;
	}

	// �жϸ���Ϣ�ǲ���·����Ϣ
	if ( ( vMsg->msghead().messageid() & CMessageRouter::MSGROUTER ) == CMessageRouter::MSGROUTER )
	{
		return OnRouterMessageByModule(vMsg);
	}	

	// ȡ����Ϣ����ģ��
	unsigned short usMessageModule = REGION_OF_MESSAGE(  vMsg->msghead().messageid() );


	switch ( usMessageModule )
	{
		// ȫ�ֿ�����Ϣ���������κ�ģ��
	case MESSAGE_GLOBAL:
	case MESSAGE_CORE:
		{
			OnGlobalGateMessage( vMsg );
			break;
		}
		// ����ģ��������Ϣ
	case MESSAGE_FRIEND:
		{
			CFriendModule::GetSingleton( ).OnGateMessage( vMsg );
			break;
		}
		// ���ģ��������Ϣ
	case MESSAGE_TEAM:
		{
			CTeamModule::GetSingleton().OnGateMessage( vMsg );
			break;
		}
		// �ʼ�ģ��������Ϣ
	case MESSAGE_MAIL:
		{		
            CMailModule::GetSingleton().OnGateMessage( vMsg );
			break;	
		}
		// GMģ��������Ϣ
	case MESSAGE_GM:
		{
			CGMModule::GetSingleton().OnGateMessage(vMsg);
			break;
		}
		// �̳�ģ��������Ϣ
	case MESSAGE_IB:
		{
			CIbStoreModule::GetSingleton().OnGateMessage( vMsg );
			break;
		}
	case MESSAGE_CORPS:
		{
			CCorpsModule::GetSingleton().OnGateMessage( vMsg );
			break;
		}
	case MESSAGE_FAMILY:
		{
			CFamilyModule::GetSingleton().OnGateMsg( vMsg );
			break;
		}
	case MESSAGE_RANK:
		{
			CRankModule::GetSingleton().OnGateMessage( vMsg );
			break;
		}
	case MESSAGE_REPETION:
		{
			CRepetionModule::GetSingletonPtr( )->OnRouterMessage( vMsg );
			break;
		}
	case MESSAGE_JUDGE:
		{
			CJudgeModule::GetSingleton().OnRouterMessage( vMsg );
			break;
		}

	case MESSAGE_COUNTRY:
		{
			CWorldModule::GetSingleton().OnGateMessage( vMsg );
			break;
		}

	case MESSAGE_ACHIEVE:
		{
			CAchieveModule::GetSingleton().OnRouterMessage( vMsg );
			break;
		}
	case MESSAGE_ACTIVITY:
		{
			CActivityModule::GetSingleton().OnGateMessage( vMsg );
			break;
		}
	case MESSAGE_BOURSE:
		{
			CBourseModule::GetSingletonPtr( )->OnRouterMessage( vMsg );
			break;
		}
	case MESSAGE_GLOBALDUNGEON:
		{
			CGlobalModule::GetSingleton().OnServerMessgage( vMsg );
			break;	
		}
	case MESSAGE_TASK:
		{
			CTaskModule::GetSingleton().OnGateMessage(vMsg);
			break;
		}
	default:
		{
			LOG_ERROR( "default", "[%s:%d] no one care this messageid %d", __FUNCTION__, __LINE__, vMsg->msghead().messageid() );
			break;
		}
	}

	return 0;
}

int CSceneServer::OnMessageKickOffPlayerRequest( CMessage* tpMessage )
{
	LK_ASSERT(tpMessage != NULL && tpMessage->has_msgpara() == true, return -1);
	CMessageKickOffPlayerRequest* tpMsg = ( CMessageKickOffPlayerRequest* )( tpMessage->msgpara() );
	LK_ASSERT(tpMsg != NULL, return -1);

	int nKickResult = CSceneLogic::GetSingletonPtr()->KickPlayer(tpMsg->charid(), tpMsg->reason(), tpMsg->anotherip());
	
	if ( nKickResult == EM_KICKOUT_NOTHISCHAR)
	{
		CMessageKickOffPlayerResponse tKickOffResponse;
		tKickOffResponse.set_accountid(tpMsg->accountid());
		tKickOffResponse.set_roleworldid(tpMsg->roleworldid());
		tKickOffResponse.set_charid( tpMsg->charid() );
		tKickOffResponse.set_result(EGATE_KICKOFFPLAYER_NOTIN_SCENE);

		CMessage tMessage;
		tMessage.set_msgpara((uint32_t) &tKickOffResponse);
		pbmsg_sethead(&tMessage, ID_S2G_KICKOFF_PLAYER_RESPONSE, 0, 0, 0, 0, 0, 0);
		CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );
	}
					
	return nKickResult;
}

int CSceneServer::OnMessageClientInfoRequest( CMessage* vpMessage, CEntityPlayer* pPlayer )
{
	LK_ASSERT( vpMessage != NULL && pPlayer != NULL, return -1 );
/*	
	CMessageSendClientInfoRequest* tpRequest = ( CMessageSendClientInfoRequest* ) vpMessage->msgpara();
	
	tpSceneLogic->ExecuteSql( save_clienthost, 0, 0, pPlayer->GetAccountID(), SQL_NONE, INSERT, 
		"insert into GMS_CLIENTHOST_INFO(mac, hostinfo) values('%s', '%s');", tpRequest->macaddr().c_str(), tpRequest->hostinfo().c_str() );
*/
	return SUCCESS;
}

//************************************
// Method:    OnMessageTracePlayerNotify
// FullName:  ���ط��͵Ķ���ҽ���׷�ٵ���Ϣ֪ͨ
// Access:    public 
// Returns:   int
// Qualifier: 
// Parameter: 
// Parameter: 
//************************************
int CSceneServer::OnMessageTracePlayerNotify( CMessage* vpMessage ) 
{  
	LK_ASSERT( vpMessage != NULL, return -1 )
	CMessageNotifyTracedPlayer *tpMsg = ( CMessageNotifyTracedPlayer * )vpMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return -1 )
	for ( int i = 0; i < tpMsg->playerlist_size(); ++i )
	{ 
		CTracedPlayerInfo *tpTracePlayerInfo = tpMsg->mutable_playerlist( i );
		if ( tpTracePlayerInfo->roleid_size() == 0 )
		{
			CEntityPlayer *tpPlayer = CSceneLogic::GetSingleton().GetPlayerByAccountID( tpTracePlayerInfo->accountid() );
			if ( tpPlayer == NULL )
			{
				continue;
			}			 
						
			if ( !tpPlayer->GetIfTracePlayer() )
			{
				tpPlayer->SetIfTarcePlayer( true );
				tpPlayer->InitializeLog();
			}					
		}
		for ( int j = 0; j < tpTracePlayerInfo->roleid_size(); ++j )
		{
			CEntityPlayer *tpPlayer = CSceneLogic::GetSingleton().GetPlayerByCharID( tpTracePlayerInfo->roleid( j ) );
			if ( tpPlayer != NULL )
			{ 
				if ( !tpPlayer->GetIfTracePlayer() )
				{
					tpPlayer->SetIfTarcePlayer( true );
					tpPlayer->InitializeLog();
				}				
				break;
			}  			
		}  			
	}	
	return 0;   	   				
}

//************************************
// Method:    OnMessageClientAntiBotDataNotify
// FullName:  SceneServer::CSceneServer::OnMessageClientAntiBotDataNotify
// Access:    public 
// Returns:   int
// Qualifier: ���ܿͻ��˷�������ݣ���ת��������ҷ�����
// Parameter: CMessage * pMsg
// Parameter: CEntityPlayer * pPlayer
//************************************
int CSceneServer::OnMessageClientAntiBotDataNotify( CMessage* pMsg, CEntityPlayer* pPlayer )
{
	LK_ASSERT( pMsg != NULL && pPlayer != NULL, return -1 );

	CMessageSendAntiBotDataToServerNotify* tpAntitBotNotify = (CMessageSendAntiBotDataToServerNotify*)pMsg->msgpara();

	NoticeApexProxy_UserData( pPlayer->GetCharID(), tpAntitBotNotify->clientdata().c_str(), tpAntitBotNotify->length() );
	
	return 0;
}


//************************************
// Method:    OnMessageClientAntiBotStartRetNotify
// FullName:  SceneServer::CSceneServer::OnMessageClientAntiBotStartRetNotify
// Access:    public 
// Returns:   int
// Qualifier: ����ͻ��˷����ģ���������
// Parameter: CMessage * pMsg
// Parameter: CEntityPlayer * pPlayer
//************************************
int CSceneServer::OnMessageClientAntiBotStartRetNotify(  CMessage* pMsg, CEntityPlayer* pPlayer )
{
	LK_ASSERT( pMsg != NULL && pPlayer != NULL, return -1 );

	CMessageClientAntiBotStartRetNotify* tpAntiBotStartRet = (CMessageClientAntiBotStartRetNotify*)pMsg->msgpara();
	
	int nRet = tpAntiBotStartRet->startret();

	NoticeApexClient_Ret( pPlayer->GetCharID(), (const char*)&nRet );

	LOG_NOTICE( "apex", "client(%d:%s)->server ccstart ret %d", pPlayer->GetCharID(), pPlayer->GetCharNameShow(), nRet );

	return 0;
}

int CSceneServer::OnMessagePlayerRedirectErrEvent( CMessage* vpMessage )
{
	LK_ASSERT((vpMessage != NULL && vpMessage->has_msgpara() == true),  return 0);
	CMessageRedirectGErrorCode* tpMessage = ( CMessageRedirectGErrorCode* )vpMessage->msgpara();	
	LK_ASSERT(tpMessage != NULL, return 0);

	CEntityPlayer* tpPlayer = ( CEntityPlayer* )CSceneLogic::GetSingletonPtr()->GetPlayerByCharID(tpMessage->charid());	

	if( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]Player Cannt find, charid = %d", __LK_FILE__, __LINE__, __FUNCTION__,
			tpMessage->charid( ) );
		return 0;
	}

	LOG_INFO( "default", "[ %s : %d ][ %s ]Player( %d : %s ) Redirect Scene( %d : %d ) Err( %d )", __LK_FILE__, 
		__LINE__, __FUNCTION__, tpPlayer->GetCharID(), tpPlayer->GetCharNameShow(), tpPlayer->GetTLineID( ),
		tpPlayer->GetTMapID( ), tpMessage->errorcode( ) );

	// �����Ŀ�곡���յ�����
	if (tpPlayer->GetCommState() == CEntityPlayer::STATE_REDIRECT_INWAIT)	
	{
		CSceneLogic::GetSingleton().PlayerLeaveFromGame(tpPlayer);
		return 0;
	}
	

	// ԭ�����Ĵ���
	tpPlayer->SetCommState( CEntityPlayer::STATE_INMAP );	
//	if( IS_REPETION_LINE_ID( tpMessage->lineid( ) ) == true )
//	{
//		( ( CPropertyPlayer* )tpPlayer->GetProperty( ) )->GetRepetion( )->DecRepetionCount( tpMessage->mapid( ) );
//	}
	
	int tDirect;
	switch( tpMessage->errorcode( ) )
	{
		case REDIRECT_PLAYER_IN_MAP:
			{
				tDirect = ERR_REDIRECT_PLAYER_IN_MAP;
			}
			break;
		case REDIRECT_OBJECT_IS_FULL:
			{
				tDirect = ERR_REDIRECT_OBJECT_IS_FULL;
			}
			break;
		case REDRIECT_ERR_UNKNOW:
			{
				tDirect = ERR_REDRIECT_UNKNOW;
			}
			break;
		case ERR_REDIRECT_MAP_NOTOPEN:
		case REDIRECT_MAP_NOTOPEN:
			{
				tDirect = ERR_REDIRECT_MAP_NOTOPEN;
			}
			break;
		case REDIRECT_MAP_PLAYER_IS_FULL:
			{
				tDirect = ERR_REDIRECT_MAP_PLAYER_IS_FULL;
			}
			break;
		case ERR_BATTLE_TIMEOUT:
		case ERR_BATTLE_NOT_PERMITED:
			{
				tDirect = tpMessage->errorcode( );
			}
			break;
		case ERR_REPETION_PVP_LEVEL_NOTFOUND:
			{
				tDirect = ERR_REPETION_PVP_LEVEL_NOTFOUND;
			}
			break;
		case ERR_REPETION_PVP_WAITLIST_FULL:
			{
				tDirect = ERR_REPETION_PVP_WAITLIST_FULL;
			}
			break;
		default:
			{
				tDirect = ERR_REDRIECT_UNKNOW;
				LOG_ERROR( "default", "[ %s : %d ][ %s ]Player Redirect Map ErrorCode( %d ) Cannt Find", __LK_FILE__,
					__LINE__, __FUNCTION__, tpMessage->errorcode( ) );
//				return ERR_UNKNOWN;
			}
			break;
	}

	CMessage tMsg;
	CMessageProErrorNotice tMsgFact;

	tMsgFact.set_errorcode( tDirect );
	tMsg.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_PROERROR );
	tMsg.set_msgpara( (uint32)&tMsgFact ); 

	CSceneLogic::GetSingletonPtr( )->Send2Player( tpMessage->charid( ), &tMsg );

	return 0;
}

// ***************************************************************
//  Function:		OnMessagePlayerRedirectMapNotice
//  Description:	��������ض����ͼ��Ϣ
//	Input:			
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			10/27/2008
// 
// ***************************************************************
int CSceneServer::OnMessagePlayerRedirectMapNotice( CMessage* vpMessage )
{
	CMessagePlayerRedirectMapNotice* tpMessage = ( CMessagePlayerRedirectMapNotice* )( vpMessage->msgpara() );
	unsigned short tLineID = tpMessage->lineid( );
	unsigned short tMapID = tpMessage->mapid( );

	CMapObject* tpMapObj = CMapObjManager::GetSingletonPtr( )->GetMapObject( tLineID, tMapID, INVALID_MAP_INDEX,
		tpMessage->key( ) );

	if( tpMapObj == NULL )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]Cannt get MapObject from ObjManager", __LK_FILE__, 
			__LINE__, __FUNCTION__ );
		SendRedirectErrCode( tpMessage->charid( ), tLineID, tMapID, REDIRECT_OBJECT_IS_FULL ); 
		return 0;	
	}

	CEntityPlayer* tpPlayer = CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( tpMessage->charid( ) );
	if( tpPlayer != NULL )
	{
		// player in scene
		int tPosX = 0;
		int tPosY = 0;
#ifdef _FB_
		CRepetionInfo* tpInfo = CRepetionModule::GetSingletonPtr( )->GetRepetionInfoByMapID( tMapID );
		if( tpInfo != NULL )
		{
			const BattleCamp* tpCamp = tpInfo->GetBattleCamp( tpMessage->camp( ) );
			if( ( tpCamp != NULL ) && ( tpInfo->IsBattle( ) == true ) )
			{
				tPosX = tpCamp->mPosX;
				tPosY = tpCamp->mPosY;
			}
			else
			{
				tPosX = tpMessage->posx( );
				tPosY = tpMessage->posy( );
			}
		}
		else
		{
			SendRedirectErrCode( tpMessage->charid( ), tLineID, tMapID, REDIRECT_MAP_NOTOPEN );
			return 0;
		}

		CPlayerRepetion* tpRepetion = ( ( CPropertyPlayer* )tpPlayer->GetProperty( ) )->GetRepetion( );
		tpRepetion->SetCampID( tpMessage->camp( ) );
#else
		tPosX = tpMessage->posx( );
		tPosY = tpMessage->posy( );
#endif
		bool tRtn = true;
		tRtn = CMapModule::GetSingletonPtr( )->Teleport( tpMapObj->GetLineID( ), tpMapObj->GetMapID( ), tPosX, tPosY, 
			tpPlayer, tpMapObj->GetMapIndex( ) );

		if( tRtn == true )
		{
			LOG_INFO( "default", "[ %s : %d ][ %s ] Player( %d ) Redirect Into Scene In Self Scene( %d : %d : %lld )"
				" OK", __LK_FILE__, __LINE__, __FUNCTION__, tpPlayer->GetCharID( ), tpMapObj->GetLineID( ), 
				tpMapObj->GetMapID( ), tpMapObj->GetKey( ) );
		}	
		else
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ] Player( %d ) Redirect Into Scene In Self Scene( %d : %d : %lld )"
				" Fail", __LK_FILE__, __LINE__, __FUNCTION__, tpPlayer->GetCharID( ), tpMapObj->GetLineID( ), 
				tpMapObj->GetMapID( ), tpMapObj->GetKey( ) );
		}

		return SUCCESS;
	}
	else
	{
		tpPlayer = ( CEntityPlayer* )CSceneObjManager::GetSingletonPtr()->CreateObject ( OBJTYPE_ENTITY_PLAYER );
		if( tpPlayer == NULL )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ]Cannt get EntityPlayer Object from ObjManager", __LK_FILE__, 
				__LINE__, __FUNCTION__ );
			SendRedirectErrCode( tpMessage->charid( ), tLineID, tMapID, REDIRECT_MAP_PLAYER_IS_FULL );
			return 0;
		}

		if( IS_REPETION_LINE_ID( tLineID ) == true )
		{
			LOG_NOTICE( "default", "[ %s : %d ][ %s ] Player( %d ) Redirect Into, Map( %d : %lld )",
				__LK_FILE__, __LINE__, __FUNCTION__, tpMessage->charid( ), tMapID, tpMessage->key( ) );

			if( tpMapObj->IsFull( ) == true )
			{
				SendRedirectErrCode( tpMessage->charid( ), tLineID, tMapID, REDIRECT_MAP_PLAYER_IS_FULL );
				CSceneObjManager::GetSingletonPtr( )->DestroyObject( tpPlayer->get_id( ) );
				return 0;
			}

			tpMapObj->AddPlayerWaitInCount( );

		}
	}

	tpPlayer->SetEntityType( ENTITYTYPE_PLAYER );
	tpPlayer->SetCharID( tpMessage->charid( ) );
	tpPlayer->SetAccountID( tpMessage->accountid( ) );
	tpPlayer->SetLoginToken( tpMessage->logintoken( ) ); 	
	#ifdef _FB_
		CRepetionInfo* tpInfo = CRepetionModule::GetSingletonPtr( )->GetRepetionInfoByMapID( tMapID );
		if( tpInfo != NULL )
		{
			const BattleCamp* tpCamp = tpInfo->GetBattleCamp( tpMessage->camp( ) );
			if( ( tpCamp != NULL ) && ( tpInfo->IsBattle( ) == true ) )
			{
				tpPlayer->SetPosX( tpCamp->mPosX );
				tpPlayer->SetPosY( tpCamp->mPosY );
			}
			else
			{
				tpPlayer->SetPosX( tpMessage->posx( ) );
				tpPlayer->SetPosY( tpMessage->posy( ) );
			}
		}
		else
		{
			tpPlayer->SetPosX( tpMessage->posx( ) );
			tpPlayer->SetPosY( tpMessage->posy( ) );
		}

		CPlayerRepetion* tpRepetion = ( ( CPropertyPlayer* )tpPlayer->GetProperty( ) )->GetRepetion( );
		tpRepetion->SetCampID( tpMessage->camp( ) );	
	#else
	tpPlayer->SetPosX( tpMessage->posx( ) );
	tpPlayer->SetPosY( tpMessage->posy( ) );
	#endif	
	tpPlayer->SetEntityID( tpPlayer->get_id( ) );
	tpPlayer->SetCommHandle( tpMessage->commhandle( ) );
	tpPlayer->SetLeaveTimer( 10000 );
    tpPlayer->SetDirection( DIR_DOWN );
    tpPlayer->SetMotionState( MOTION_IDLE );
	tpPlayer->SetAliveStatus( ALIVE_NORMAL );
    tpPlayer->SetHasTarget( false );
    tpPlayer->SetTeamFlag( tpMessage->teamflag() );
	//tpPlayer->SetTeamID( TEAM_NONE );
	tpPlayer->SetMapID( tpMapObj->GetMapID( ) );
	tpPlayer->SetLineID( tpMapObj->GetLineID( ) );
	tpPlayer->SetIndex( tpMapObj->GetMapIndex( ) );
	tpPlayer->GetProperty()->SetEntityID( tpPlayer->get_id( ) );
	tpPlayer->SetPKMode( PKMODE_TRAINING );
	// ��ʾ�ǿ�����������
	tpPlayer->SetCommState( CEntityPlayer::STATE_REDIRECT_INWAIT );	   
	
	
	// ��ʶ����;�����Ϣ
	if ( tpMessage->familyid() > 0 )
	{
		tpPlayer->SetFamilyID( tpMessage->familyid() );
		CMemberInfo tMemberInfo;
		tMemberInfo.mIfHasFamilyApplies = tpMessage->ifhasapplies();
		tMemberInfo.mFamilyContribute = tpMessage->familycontribute();
		tMemberInfo.mFamilyMoney = tpMessage->familymoney();
		tMemberInfo.mFamilyHeaderID = tpMessage->familyheaderid();
		tMemberInfo.mFamilyPost = tpMessage->familypost();
		
		if ( tpMessage->corpsid() > 0 )
		{
			tpPlayer->SetCorpsID( tpMessage->corpsid() );
			tMemberInfo.mIfHasCorpsApply = tpMessage->ifhascorpsapply();
			tMemberInfo.mCorpsHeaderID = tpMessage->corpsheaderid();			
			tMemberInfo.mCorpsPost = tpMessage->corpspost();
			tMemberInfo.mCorpsContribute = tpMessage->corpscontribute();
			tMemberInfo.mCorpsMoney = tpMessage->corpsmoney();
		}	 	
		tMemberInfo.mEntityID = tpPlayer->GetEntityID();
		CFamilyModule::GetSingleton().InsertFamilyMember( tpMessage->corpsid(), tpMessage->familyid(), tpPlayer->GetCharID(), tMemberInfo, tpMessage->familyname().c_str(), tpMessage->corpsname().c_str() );
	}
	if ( tpMessage->unionid() > 0 )
	{
		tpPlayer->SetUnionID( tpMessage->unionid() );
		if ( tpMessage->has_unionname() )
		{
			tpPlayer->SetUnionName( tpMessage->unionname().c_str() );	
		}
		tpPlayer->SetHeadCorpsID( tpMessage->headcorpsid() );
	}
	tpPlayer->SetCountryID( tpMessage->countryid() );
	tpPlayer->SetOfficialID( tpMessage->officialid() );
	tpPlayer->SetKingID( tpMessage->kingid() );
	// ��������������������ID
	tpPlayer->SetRoleWorldID( tpMessage->roleworldid() );
	// ���ô�����ʽ
	tpPlayer->SetCreatMethod( PLAYERCREAT_TELEPORT );
	
	if ( tpMessage->iftracedplayer() )
	{
		tpPlayer->SetIfTarcePlayer( true );
		tpPlayer->InitializeLog();
	}
	
	// ������������뱣��ʱ��
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	tpProperty->GetRolePassword()->InitialPass( tpMessage->mutable_password()->c_str(), tpMessage->protecttime(), tpMessage->protecttimelength(), tpMessage->passwordstatus() );
	tpProperty->GetRolePassword()->SetEntityID(tpPlayer->GetEntityID());

	// if has team, create team data in local scene based by gate 
	CTeamModule::GetSingleton().CreateTeamMsgOnRedirect( tpMessage->mutable_teammsg(), tpPlayer );

	// ���ʱ�����ʵ���Ѿ�����,��Ȼ�ͻ��˻�û����,��������ٻ����ѿ��Դ���
	if ( tpMessage->pettempid( ) != 0 )
	{
		CPetCreator* tpCreator = (CPetCreator*) CSceneObjManager::GetSingletonPtr()->CreateObject( OBJTYPE_CREATOR_PET );
		if( tpCreator != NULL )
		{
			tpCreator->mPos = tpPlayer->GetPos( );
			tpCreator->mDirection = tpPlayer->GetDirection( );
			tpCreator->mPetID = tpMessage->pettempid( );
			tpCreator->mSrcEntityID = tpPlayer->GetEntityID( );
			tpCreator->mOnlineTime = tpMessage->petonlinetime();
			tpCreator->mPetMode = tpMessage->petmode();
		
			tpPlayer->SetPetCreatorID( tpCreator->get_id() );
		}
	}
	
	CMessage tMessage;
	CMessagePlayerRedirectEnterMapResponse tMsgFact;

	tMsgFact.set_commhandle( tpPlayer->GetCommHandle( ) );
	tMsgFact.set_charid( tpPlayer->GetCharID( ) );
	tMsgFact.set_lineid( tpPlayer->GetLineID( ) );
	tMsgFact.set_mapid( tpPlayer->GetMapID( ) );
	tMsgFact.set_posx( tpPlayer->GetPosX( ) );
	tMsgFact.set_posy( tpPlayer->GetPosY( ) );
    tMessage.mutable_msghead()->set_messageid( ID_S2G_REDIRECT_ENTER_MAP_RESPONSE );
    tMessage.set_msgpara( (uint32)&tMsgFact );	

	CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );

	CSceneLogic::GetSingletonPtr()->mPlayerInWait.insert( CSceneLogic::PLAYERID_MAP::value_type( tpMessage->charid(), tpPlayer->get_id() ) );

	LOG_NOTICE( "default", "[ %s : %d ][ %s ]Player( %d : %s  ) Redirect Into Scene, Pos( %d : %d ), Waiting "
		" Clinet Connect", __LK_FILE__, __LINE__, __FUNCTION__, tpPlayer->GetCharID(), 
		tpPlayer->GetCharNameShow(), tpPlayer->GetPosX( ), tpPlayer->GetPosY( ) );
	
	// �޸Ĵ�����ʽ
	tpPlayer->SetCreatMethod( PLAYERCREAT_MOVE );
		
	return 0;
}

int CSceneServer::SendRedirectErrCode( int vCharID, unsigned short vLineID, unsigned short vMapID, REDIRECT_ERR vCode )
{
	CMessage tMessage;
    CMessageRedirectSErrorCode tSendMsg;
    tSendMsg.set_charid( vCharID );
    tSendMsg.set_errorcode( vCode );
	tSendMsg.set_lineid( vLineID );
	tSendMsg.set_mapid( vMapID );

    tMessage.mutable_msghead()->set_messageid( ID_S2G_REDIRECT_S_ERROR_CODE );
    tMessage.set_msgpara( (uint32)&tSendMsg );	

	CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );
	return 0;
}



//************************************
// Method:    OnGlobalGateMessage
// FullName:  SceneServer::CSceneServer::OnGlobalGateMessage
// Access:    public 
// Returns:   int
// Qualifier: �������ط�����ȫ�ֿ�����Ϣ(������ĳ���ض�ģ��)
// Parameter: CMessage * pMsg
//************************************
int CSceneServer::OnGlobalGateMessage( CMessage* pMsg )
{
	switch( pMsg->msghead().messageid() )
	{
		// ·�ɷ�����֪ͨ��ҿ糡��ʱ,Ŀ�곡��û���ҵ�
	case  ID_G2S_SCENE_NOT_OPEN_NOTICE:
		{
			OnMessageSceneNotOpenNoticeEvent( pMsg );	
			break;
		}
		// ֪ͨ������Ϣ
	case ID_G2S_COUNTRY_INFO:
		{
			OnMessageGetCountryInfo( pMsg );	
			break;
		}
		// ·�ɷ�����֪ͨ����л������ɹ�
	case ID_G2S_PLAYER_REDIRECT_RESPONSE:
		{
			OnMessagePlayerRedirectResponseEvent( pMsg );
			break;
		}
		// ·�ɷ�����֪ͨ����ע��ɹ�
	case ID_G2S_SERVER_INFO_RESPONSE:
		{
			LOG_INFO( "default", "Register SceneServer Successfull." );
			OnMessageServerInfoResponse(pMsg);
			break;
		}
		// ·�ɷ�����֪ͨ����������ͼ
	case ID_G2S_CREATE_MAP_NOTICE:
		{
			OnMessageCreateMapNoticeEvent( pMsg );
			break;
		}
		// ·�ɷ�����֪ͨ��������������ҽ�����Ϸ
	case ID_G2S_PLAYER_ENTER_MAP_NOTICE:
		{
			OnMessagePlayerEnterMapNoticeEvent( pMsg );
			break;
		}
		// ·�ɷ�����֪ͨ����������,�Ѿ�ȷ����ҷ���,���ڵȴ����
	case ID_G2S_PLAYER_RETURN2GATE_RESPONSE:
		{
			OnMessagePlayerReturn2GateReponseEvent( pMsg );	
			break;
		}
		// �ض����ͼ֪ͨ
	case ID_G2S_REDIRECT_MAP_NOTICE:
		{
			OnMessagePlayerRedirectMapNotice( pMsg );	
			break;
		}
		// �ض��������
	case ID_G2S_REDIRECT_G_ERROR_CODE:
		{
			OnMessagePlayerRedirectErrEvent( pMsg );
			break;
		}
		// ������������
	case ID_G2S_KICKOFF_PLAYER_REQUEST:
		{
			OnMessageKickOffPlayerRequest( pMsg );
			break;
		}
		
	case ID_G2S_TRACEDPLAYER_NOTIFY:
		{
			OnMessageTracePlayerNotify( pMsg );
			break;
		}			
	case ID_G2S_NOTIFY_CREATE_REPETION:
		{
			OnMessageCreateRepetion( pMsg );
		}
		break;
	case ID_G2S_ENTITY_GM_MOVE:
		{
			OnMessageSceneGMMove( pMsg );
		}
		break;
	case ID_G2S_ROLE_MOVE:
		{
			OnMessageRoleMove( pMsg );
		}
		break;
	case ID_G2S_NOTIFY_RESETROLEPASSWORD:
		{
			OnMessageResetPlayerPassword( pMsg );
		}
		break;

	case ID_G2S_NOTIFY_SAFE_SHUTDOWN:
		{
			OnMessageShutdownNotify( pMsg );
			break;
		}
	case ID_G2S_REQUEST_RESAVEPLAYER:
		{
			CSceneLogic::GetSingleton().OnMessageResavePlayer( pMsg );
			break;
		}
	case ID_S2C_RSPONSE_CHANGE_CAMP:
		{
			OnMessageChangCampResponse( pMsg);
			break;
		}
	default:
		{
			LOG_ERROR( "default", "[%s:%d] unknown message id %d", __FUNCTION__, __LINE__, pMsg->msghead().messageid() );
			break;
		}
	}

	return 0;
}


int CSceneServer::OnMessageLeaveGameRequestEvent( CMessage* pMsg, CEntityPlayer* pPlayer )
{	
	LK_ASSERT( pMsg != NULL && pPlayer != NULL, return -1 );

	CMessageLeaveGameRequest* tpMesg = ( CMessageLeaveGameRequest* )( pMsg->msgpara() );

	//if( pPlayer->GetCommState() == CEntityPlayer::STATE_REDIRECT )
	//{
	//	// ������̱Ƚ����⣬��Ҫ�ͻ������յ�RedirectSceneNotice�������������һ�η���ҹر���Ϣ���ͻ��˻�����ǿ�ƹر�socket.
	//	// ��ʵ֮ǰ����Ѿ����������ˣ�ֻ��Ҫ�ر�һ�¿ͻ��˼��ɡ�

	//	if ( pPlayer->IsSaving())
	//	{
	//		LOG_NOTICE("default", "player (%d:%s) is saving, direct exit and do nothing", 
	//				pPlayer->GetCharID(), pPlayer->GetCharNameShow());

	//		pPlayer->SetCommState(CEntityPlayer::STATE_LEAVEGAME);
	//	}else
	//	{
	//		LOG_NOTICE("default", "delete unused entity (%d) role (%d:%s)", pPlayer->get_id(),
	//				pPlayer->GetCharID(), pPlayer->GetCharNameShow());

	//		CSceneLogic::GetSingletonPtr()->DestroyEntity( pPlayer, SAVE_REDIRECT );
	//		CSceneLogic::GetSingletonPtr()->DestroyPlayerInstance( pPlayer, EM_LEAVE_REDIRECT, EM_SAVE2DB );
	//	}

	//	return 0;
	//}

	//TODO: Ӧ�����ְ�ȫ�˳���ǿ���˳�
	pPlayer->SetCommState( tpMesg->leavetype() == 0 ? CEntityPlayer::STATE_LEAVEGAME : CEntityPlayer::STATE_FORCEEXIT );
	CSceneLogic::GetSingleton().PlayerLeaveFromGame(pPlayer);

	return 0;
}

int CSceneServer::OnMessageRedirectSceneRequestEvent( CMessage* pMsg, CEntityPlayer* pPlayer )
{

	CMessageRedirectSceneRequest* tpMsg = ( CMessageRedirectSceneRequest* )( pMsg->msgpara() );
	CSceneLogic* tpLogic = CSceneLogic::GetSingletonPtr( );
	LOG_INFO( "default", "Player Begin Redirect Connect Scene" );
	if( tpLogic == NULL )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]CseneLogic::GetSingletonPtr() is NULL", __LK_FILE__, __LINE__, 
			__FUNCTION__);
		assert( 0 );
		return -1 ;
	}



	CSceneLogic::PLAYERID_MAP::iterator tFindIter = tpLogic->mPlayerInWait.find( tpMsg->charid() );
	if ( tFindIter == tpLogic->mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]Invalid Player %d Enter", __LK_FILE__, __LINE__, __FUNCTION__,
			tpMsg->charid() );
		return -1;
	}

	
	CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr( )->GetObject( tFindIter->second );
	if( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]Player %d didn't In Server", __LK_FILE__, __LINE__, __FUNCTION__,
			tFindIter->second );
		return -1;
	}

	tpPlayer->SetRedirect(true);
//	tpLogic->mPlayerInWait.erase( tFindIter );
	if( tpPlayer->GetRoleWorldID() <= 0 || tpPlayer->GetRoleWorldID() == CSceneLogic::GetSingleton().GetWorldID() )
	{
		if ( tpPlayer->GetLoginToken( ) != tpMsg->logintoken() || tpPlayer->GetAccountID() != tpMsg->accountid() )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ]Invalid Player %d, Token[%d:%d] AccountID[%d:%d] ", __LK_FILE__,
				__LINE__, __FUNCTION__, tpMsg->charid(), tpPlayer->GetLoginToken( ), tpMsg->logintoken(), 
				tpPlayer->GetAccountID(), tpMsg->accountid() );
			return -1;
		}
	}

	

	CMapObject* tpMapObj = CMapObjManager::GetSingletonPtr( )->GetMapObject( tpPlayer->GetLineID( ), 
		tpPlayer->GetMapID( ), tpPlayer->GetMapIndex( ) );
	if( tpMapObj == NULL )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]Player( %s : %d : %d )Redirect Inot Map, Buf Map( %d : %d : %d"
			" ) Cannt find", __LK_FILE__, __LINE__, __FUNCTION__, tpPlayer->GetCharNameShow( ), tpPlayer->GetCharID(), 
			tpPlayer->GetEntityID(), tpPlayer->GetLineID( ), tpPlayer->GetMapID( ),
			tpPlayer->GetMapIndex( ) );
		return -1;
	}

	tpMapObj->DelPlayerWaitInCount( );

	LOG_INFO( "default", "Player( %d ) Redirect Connect Into Scene, Pos( %d : %d )", tpPlayer->GetCharID(),
		tpPlayer->GetPosX( ), tpPlayer->GetPosY( ) );

	//CMessage tMsg;
	//CMessageLoginSceneResponse tMsgFact;
	//CMessageHead* tpHead = tMsg.mutable_msghead();

	//tpHead->set_messageid( ID_S2C_RESPONSE_LOINGSCENE );
	//tMsgFact.set_csdialogid( tpPlayer->get_id() );

	//tMsgFact.set_key(tpPlayer->GetKey( ),KEYLEN);
	//tMsg.set_msgpara( (uint32)&tMsgFact );

	//CSceneLogic::GetSingletonPtr()->Send2Player( tpPlayer, &tMsg );

	LoadPlayerFromDB( tpMsg->accountid(), tpMsg->charid( ), tpPlayer->GetRoleWorldID() );

	return 0;
}

int CSceneServer::OnMessageLoginSceneRequestEvent( CMessage* pMsg, CEntityPlayer* pPlayer )
{
	CMessageLoginSceneRequest* tpMsg = ( CMessageLoginSceneRequest* )( pMsg->msgpara() );
	CSceneLogic* tpLogic = CSceneLogic::GetSingletonPtr( );

	LOG_INFO( "default", "Player( %d : %s ) Begin Login Scene...", pPlayer->GetCharID(), pPlayer->GetCharNameShow() );

	if( tpLogic == NULL )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]CseneLogic::GetSingletonPtr() is NULL", __LK_FILE__, __LINE__, 
			__FUNCTION__);
		assert( 0 );
		return -1 ;
	}
	
	CSceneLogic::PLAYERID_MAP::iterator tFindIter = tpLogic->mPlayerInWait.find( tpMsg->charid() );
	if ( tFindIter == tpLogic->mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]Invalid Player %d, not in waiting queue", __LK_FILE__, __LINE__,
			__FUNCTION__, tpMsg->charid() );
		return -1;
	}

	CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr( )->GetObject( tFindIter->second );
	if( tpPlayer == NULL)
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]Can't Find EntityPlayer ObjID=%d", __LK_FILE__, __LINE__, __FUNCTION__,
			tFindIter->second );
		return -1;
	}	

	//if ( tpPlayer->mCommState == CEntityPlayer::STATE_KICKOUT)
		if ( tpPlayer->GetLoginToken( ) != tpMsg->logintoken() || tpPlayer->GetAccountID() != tpMsg->accountid() )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ]Invalid Player %d, Token[%d:%d] Account[%d:%d]", __LK_FILE__,
					__LINE__, __FUNCTION__, tpMsg->charid(), tpPlayer->GetLoginToken( ), tpMsg->logintoken(), 
					tpPlayer->GetAccountID(), tpMsg->accountid() );
		}

	// ��ѯ�����������
	LoadPlayerFromDB(tpMsg->accountid(),  tpMsg->charid( ), tpPlayer->GetRoleWorldID() );

	return SUCCESS;
}

int CSceneServer::LoadPlayerFromDB( unsigned int nAccountID, unsigned int vCharID, int nDesGameID /* = 0 */ )
{
	CSceneLogic* tpLogic = CSceneLogic::GetSingletonPtr( );
	if( tpLogic == NULL )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]CseneLogic::GetSingletonPtr() is NULL", __LK_FILE__, __LINE__, __FUNCTION__);
		return -1 ;
	}


//	int nSplitID = nAccountID % 16; 

	tpLogic->LoadPlayerInfo( nAccountID, vCharID, nDesGameID );
	tpLogic->LoadPlayerProperty( nAccountID, vCharID, nDesGameID );

//	tpLogic->ExecuteSql( loadplayerforlogin_charprofile, vCharID, 0, vCharID, SQL_NEED_CALLBACK,
//		SELECT, "select role_id, account_id, role_name, gender_id, metier_id, "
//					"nationality_id, face_type, line_id, map_id, role_level, "
//					"role_expr, role_money, pos_x, pos_y, is_alive, "
//					"login_time, online_duration, save_status, save_bitflag, bounded_money, "
//					"role_password, check_sum, role_status_param, silver_yb, storage_money, storage_bounded_money " 
//				"from UMS_ROLE where role_id = %d", vCharID );

//	tpLogic->ExecuteSql( loadplayerforlogin_property, vCharID, 0, vCharID, SQL_NEED_CALLBACK,
//		SELECT, "select role_hp, role_mp, role_ap, role_basic, role_skill, role_buff,"
//		"role_cdgroup, role_pvp, role_title, role_activity, role_talent, role_mw, role_lifeskill,"
//		"role_statistic, role_monster_record, role_tele_pos, role_wizard, role_client,"
//		"save_bitflag from UMS_ROLE_DETAIL_%02d "
//		"where role_id = %d", nSplitID, vCharID);
//
	//tpLogic->ExecuteSql( loadplayerforlogin_baggage, vCharID, 0, vCharID, SQL_NEED_CALLBACK,
	//	SELECT, "select role_package, role_task_package from UMS_ROLE_DETAIL_%02d where role_id = %d", nSplitID, vCharID );

	int nPkgIdx[3] = { PACKAGE_BAGGAGE, PACKAGE_EQUIPMENT, PACKAGE_TASK };
	LoadPlayerItemInfoFromDB( nAccountID, vCharID, nPkgIdx, 3, nDesGameID );

	//tpLogic->ExecuteSql( loadplayerforlogin_storage, vCharID, 0, vCharID, SQL_NEED_CALLBACK,
	//	SELECT, "select role_storage from UMS_ROLE_DETAIL_%02d where role_id = %d", nSplitID, vCharID );
	nPkgIdx[0] = PACKAGE_STORAGE;
	LoadPlayerItemInfoFromDB( nAccountID, vCharID, nPkgIdx, 1, nDesGameID );

//	tpLogic->ExecuteSql( loadplayerforlogin_task, vCharID, 0, vCharID, SQL_NEED_CALLBACK,
//		SELECT, "select role_task from UMS_ROLE_DETAIL_%02d where role_id = %d", nSplitID, vCharID );

//	tpLogic->ExecuteSql( loadplayerforlogin_friend, vCharID, 0, vCharID, SQL_NEED_CALLBACK,
//		SELECT, "select role_friend from UMS_ROLE_DETAIL_%02d where role_id = %d", nSplitID, vCharID );

//	tpLogic->ExecuteSql( loadplayerforlogin_repetion, vCharID, 0, vCharID, SQL_NEED_CALLBACK,
//		SELECT, "select role_repetion from UMS_ROLE_DETAIL_%02d where role_id = %d", nSplitID, vCharID );	

	tpLogic->ExecuteSql (loadplayerforlogin_yuanbao, vCharID, nAccountID, vCharID, SQL_NEED_CALLBACK, 
		SELECT, "select golden_yb, account_status from UMS_ACCOUNT where account_id = %d", nAccountID);	

    tpLogic->LoadPlayerYaoQianShuInfoFromDB( nAccountID, vCharID );
    tpLogic->LoadPlayerPickStoreBoxFromDB( nAccountID,vCharID );

	return SUCCESS;

}

// �����ݿ������ҵ�����Ϣ
int CSceneServer::LoadPlayerItemInfoFromDB( int nAccountID, int nCharID, int* panPkgIdx, int nNumber, int nDesGameID )
{
	CMessage tMessage;
	CMessageLoadPlayerItemInfoRequest tReqPara;

	tMessage.mutable_msghead()->set_messageid( ID_S2D_LOADPLAYERITEMINFO_REQUEST );
	tMessage.set_msgpara( (unsigned int)(&tReqPara) );

	tReqPara.set_accountid( nAccountID );
	tReqPara.set_charid( nCharID );

	CSession* pSession= (CSession*) CSceneObjManager::GetSingletonPtr()->CreateObject( OBJTYPE_SESSION );
	LK_ASSERT( pSession != NULL, return -1 ); 

	pSession->SetSessionType( SESSION_LOAD_PLAYER_BAGGAGE );
	pSession->SetParam1( nCharID );
	
	pSession->SetTimer( CWTimer(30000) ); 

	tReqPara.set_sessionid( pSession->get_id() );

	for( int i = 0; i < nNumber; i++ )
	{
		tReqPara.add_packageidx( panPkgIdx[i] );
		pSession->SetParam( 2 + i, panPkgIdx[i] ); // �Ӳ���2��ʼ��ʾ��������
	}

	if( SceneServer::CSceneLogic::GetSingletonPtr()->Send2Data( nAccountID, tMessage, nDesGameID ) < 0 )
	{
		LOG_ERROR( "default", "[%s:%d] player %d send messag to data failed.", __FUNCTION__, __LINE__ , nCharID );
		return -1;
	}

	return 0;
}

int CSceneServer::ReLoadAppointedConfig()
{
	// ����һЩ���ر�־
	CTaskModule::GetSingleton().m_bHasReloadLua = false;
	CRepetionModule::GetSingleton().m_bReloadFlag = false;

	// ������reload���ļ��嵥
	const char* pcReloadCfg = "../config/data/reload.cfg";
	if (pcReloadCfg == NULL)
	{
		return -1;
	}
	
	FILE* pFile = fopen(pcReloadCfg, "rb");
	if (pFile == NULL)
	{
		printf("error: can not find %s !!!\n", pcReloadCfg);
		return -1;
	}
	int nLength = get_file_length(pcReloadCfg);
	if (nLength == 0)
	{
		return -1;
	}
	
	char acFilePath[256] = {0};
	while (!feof(pFile))
	{
		char* pcRead = fgets(acFilePath, 256, pFile);
		if (pcRead == NULL)
		{
			continue;
		}
		
		// ȥ�����з�
		char* pcTemp = acFilePath;
		while (pcTemp != NULL && *pcTemp != '\0')
		{
			if (*pcTemp == '\r' || *pcTemp == '\n')
			{
				*pcTemp = '\0';
			}
			pcTemp++;
		}
		
		int nRetCode = ReLoadOneConfig(acFilePath);
		if (nRetCode == SUCCESS)
		{
			LOG_NOTICE( "default", "xyj-gameserver  reload  %s  success! ...", acFilePath);
			printf("reload config %s  success ...\n", acFilePath);
		}
		else
		{
			LOG_NOTICE( "default", "xyj-gameserver  reload  %s fail !!!", acFilePath);
			printf("reload config %s  fail !!! ...\n", acFilePath);
		}		
	}

	return 0;
}

int CSceneServer::ReLoadOneConfig(const char *pcConfigFilePath)
{
	if (pcConfigFilePath == NULL)
	{
		return -1;
	}

	LoadConfigFunclist::iterator iter;
	
	iter = m_LoadConfigFuncList.find(pcConfigFilePath);
	if (iter != m_LoadConfigFuncList.end())
	{
		TmLoadConfigCallback pFuncCallback = iter->second;
		if (pFuncCallback != NULL)
		{
			pFuncCallback(pcConfigFilePath);

			return 0;
		}
	}
	
	int nStrLen = strlen(pcConfigFilePath);
	char acKey[256] = {0};
	char acTemp[256] = {0};
	strncpy(acTemp, pcConfigFilePath, 256);
	char* pcTemp = const_cast<char*>(acTemp) + nStrLen - 1;
	char* pcExtendName = NULL;
	if (pcTemp == NULL)
	{
		return -1;
	}
	
	for (int i = nStrLen; i > 0; i--)
	{
		if (*(pcTemp) == '.')
		{
			pcExtendName = pcTemp;
			break;
		}
		pcTemp--;
	}

	pcTemp = const_cast<char*>(acTemp) + nStrLen - 1;
	for (int i = nStrLen; i > 0; i--)
	{
		if (*(pcTemp) == '/')
		{
			*pcTemp = '\0';
			break;
		}
		pcTemp--;
	}

	if (pcExtendName == NULL)
	{
		return -1;
	}
	
	snprintf(acKey, 256, "%s+%s", acTemp, pcExtendName);

	iter = m_LoadConfigFuncList.find(acKey);
	if (iter != m_LoadConfigFuncList.end())
	{
		TmLoadConfigCallback pFuncCallback = iter->second;
		if (pFuncCallback != NULL)
		{
			pFuncCallback(pcConfigFilePath);

			return 0;
		}
	}

	return -1;
}

int CSceneServer::RegisterLoadConfigCallback(const char* pcConfigPath, TmLoadConfigCallback pFuncCallback)
{
	if (pcConfigPath == NULL || pFuncCallback == NULL)
	{
		return -1;
	}
	
	LoadConfigFunclist::value_type PairValue(pcConfigPath, pFuncCallback);
	m_LoadConfigFuncList.insert(PairValue);

	//printf( "register LoadconfigCallback for %s ...\n", pcConfigPath);
	return 0;
}

int CSceneServer::RegisterLoadConfigCallback(const char* pcDirPath, const char* pcExtName, TmLoadConfigCallback pFuncCallback)
{
	if (pcDirPath == NULL || pcExtName == NULL)
	{
		return -1;
	}

	char acKey[256] = {0};
	snprintf(acKey, 256, "%s+%s", pcDirPath, pcExtName);
	RegisterLoadConfigCallback(acKey, pFuncCallback);

	return 0;
}

void CSceneServer::LoadDirtyWordCallback(const char* pcConfigPath)
{
	CDirtyWord::GetSingletonPtr( )->OI_Dirty_start();
}

void CSceneServer::LoadTemplateCallback(const char* pcConfigPath)
{
	int tRet = 0;
	PERF_FUNC( "LoadTemplate", tRet = CDataStatic::Initialize() );
	// ����ģ��	
	if ( tRet < 0 )
	{
		printf( "load template failed %d\n", tRet );
		LOG_FATAL( "default", "load template failed %d\n", tRet  );
	}	
}

void CSceneServer::LoadSceneConfigCallback(const char* pcConfigPath)
{
	CSceneCfgManager::GetSingletonPtr()->Initialize(const_cast<char*>(pcConfigPath));
}
// ���ݿ������ҵ�����Ϣ��Ӧ
int CSceneLogic::OnMessageLoadPlayerItemInfoFromDB( CMessage* pMsg  )
{
	CMessageLoadPlayerItemInfoResponse* pResPara = (CMessageLoadPlayerItemInfoResponse*) pMsg->msgpara();
	int nCharID = pResPara->charid();
	int nSessionID = pResPara->sessionid();

	LOG_DEBUG( "default", "player %d load iteminfo return, session %d ", nCharID, nSessionID );

	CSession* pSession = (CSession*)CSceneObjManager::GetSingletonPtr()->GetObject( nSessionID );
	if( pSession == NULL )
	{
		LOG_ERROR( "[%s:%d] can't find session %d", __FUNCTION__ , __LINE__, nSessionID );
		return 0;
	}
	
	CSceneObjManager::GetSingletonPtr()->DestroyObject( nSessionID );


	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( nCharID );
	if ( tFindIter == mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-1", 
			__LK_FILE__, __LINE__, nCharID );
		return -1;
	}

	CEntityPlayer* pPlayer = (CEntityPlayer*) CSceneLogic::GetSingletonPtr()->GetEntity( tFindIter->second );
	if(  pPlayer == NULL )
	{
		LOG_ERROR( "default", "[%s:%d] can't find entity %d", __FUNCTION__, __LINE__, tFindIter->second );
		return -1;
	}

#ifdef _DEBUG_
	LOG_DEBUG( "pro", "player %s:%d load iteminfo %s",  pPlayer->GetCharNameShow(), pPlayer->GetCharID(), pResPara->ShortDebugString().c_str());
#endif

	// ֻ�з��سɹ��������½���
	if( pResPara->errcode() != CMessageLoadPlayerItemInfoResponse::SUCCES )
	{
		LOG_FATAL( "default", "[%s:%d] player %s:%d load iteminfo failed %d", 
			__FUNCTION__, __LINE__, pPlayer->GetCharNameShow(), pPlayer->GetCharID(), pResPara->errcode() );
		return 0;
	}

	// ���뱣֤��һ������ݼ�����ɲ����½���
	if( (pPlayer->GetLoadState() & LSSTATE_CHARPROFILE) == 0 )
	{
		LOG_ERROR( "default", "player %s's charprofile is not ready ", pPlayer->GetCharNameShow() );
		return -1;
	}

	CPropertyPlayer* tpProperty = (CPropertyPlayer*)pPlayer->GetProperty( );

	// �ж��Ƿ����º�( �´�����ɫ��blob���� )
	if ( pPlayer->IsNewCharacter() == false )
	{
		int iPkgIdx = 0;
		bool bParseRtn = false;

		for( int i = 0; i < pResPara->packageidx_size(); i++ )
		{
			iPkgIdx = pResPara->packageidx( i );

			switch( iPkgIdx )
			{
			case PACKAGE_BAGGAGE:
				{
					bParseRtn = tpProperty->GetBaggage( )->CreateFromTlv2( pResPara->mutable_itembox(i) );
					break;
				}
			case PACKAGE_STORAGE:
				{
					bParseRtn = tpProperty->GetStorage( )->CreateFromTlv2( pResPara->mutable_itembox(i) ) ;
					break;
				}
			case PACKAGE_EQUIPMENT:
				{
					bParseRtn = tpProperty->GetEquipment( )->CreateFromTlv2( pResPara->mutable_itembox(i) );
					break;
				}
			case PACKAGE_TASK:
				{
					bParseRtn = tpProperty->GetTaskBaggage( )->CreateFromTlv2( pResPara->mutable_itembox(i) );
					break;
				}
			default:
				{
					LOG_ERROR( "default", "[%s:%d] wrong idx %d", __FUNCTION__, __LINE__, iPkgIdx );
					bParseRtn = false;
					break;
				}

			}

			if( bParseRtn != true )
			{
				LOG_FATAL( "pro", "player %s : %d load itembox %d blob failed",
					pPlayer->GetCharNameShow(), pPlayer->GetCharID(), iPkgIdx );
				KickPlayerWithoutSave( pPlayer, EM_NOSAVE );
				return -1;
			}

			if ( !pPlayer->IsRedirect())
			{
				// LogValuableEquip(pPlayer->GetCharID(), pResPara->mutable_itembox(i));
			}
		}

	}

	// �������д��̷�ʽ, �ֿ�һ��; ����,װ��,�����һ��
	if( pResPara->packageidx_size() == 3 )
	{
		pPlayer->SetLoadState( pPlayer->GetLoadState( ) | LSSTATE_BAGGAGE );
	}
	else if( pResPara->packageidx_size() == 1 )
	{
		pPlayer->SetLoadState( pPlayer->GetLoadState( ) | LSSTATE_STORAGE );
	}

	OnLoadPlayer_Final( pPlayer, pPlayer->GetCharID(), 0 );

	return 0;

}



// ���ݿ������ҵ�����Ϣ��ʱ
int CSceneLogic::OnTimeoutLoadPlayerItemInfoFromDB( unsigned int unCharID, int iPkgIdx  )
{
	LOG_ERROR( "default", "player  %d load item %d info timeout", unCharID, iPkgIdx );
	return 0;
}


int CSceneLogic::OnTimeoutSaveItemInfoToDB( int nCharID )
{
	LOG_ERROR( "default", "player  %d save item info timeout", nCharID );
	return 0;
}




//************************************
// Method:    OnMessageReturn2GateRequestEvent
// FullName:  SceneServer::CSceneServer::OnMessageReturn2GateRequestEvent
// Access:    public 
// Returns:   int
// Qualifier: ���磺�ͻ���ѡ��ĳ����ɫ����볡�����������ܾ����룬��ʱ�ͻ��˻ᷢ����Ϣ���ٴλص����أ�ѡ���б�
// Parameter: CMessage * pMsg
// Parameter: CEntityPlayer * pPlayer
//************************************
int CSceneServer::OnMessageReturn2GateRequestEvent( CMessage* pMsg, CEntityPlayer* pPlayer )
{
	if ( pPlayer->GetCommState( ) == CEntityPlayer::STATE_INMAP )
	{
		// ֪ͨ���أ���ҽ�Ҫ�ص�����
		/*
		CMessagePlayerReturn2GateNotice tMsgFact;
		CMessage						tMsg;
		CMessageHead* 					tpHead = tMsg.mutable_msghead();
		tpHead->set_messageid( ID_S2G_PLAYER_RETURN2GATE_NOTICE );
		tMsgFact.set_charid( pPlayer->GetCharID() );
		tMsgFact.set_accountid( pPlayer->GetAccountID() );
		tMsg.set_msgpara( (uint32)&tMsgFact );
		CSceneLogic::GetSingletonPtr()->Send2Gate( &tMsg );
		*/
		// �����������������,�򷵻�ԭ����������	
		if ( pPlayer->GetRoleWorldID() != CSceneLogic::GetSingleton().GetWorldID() &&
			 pPlayer->GetRoleWorldID() > 0	)
		{
			bool tMark = false;
			if ( IS_DUNGEONSERVER_LINE( CSceneLogic::GetSingleton().GetLineID() ) == true )
			{
				pPlayer->SetCommState( CEntityPlayer::STATE_LEAVEGAME );
				CGlobalMapData tMapData;
				CPropertyPlayer *tpProperty = ( CPropertyPlayer * )pPlayer->GetProperty();
				tMapData.mLineID = tpProperty->GetRepetion( )->GetBackLineID( );
				tMapData.mMapID = tpProperty->GetRepetion()->GetBackMapID();
				tMapData.mPosX = tpProperty->GetRepetion()->GetPosX();
				tMapData.mPosY = tpProperty->GetRepetion()->GetPosY();
				CGlobalModule::GetSingleton().GlobalTelePort( pPlayer, EGLOBALTELE_TYPE_RETURNTOGATE, ESERVERTYPE_DUNGEON, &tMapData );
				tMark = true;				
			}
			else if ( IS_GLOBAL_SCENESERVER( CSceneLogic::GetSingleton().GetLineID() ) == true )
			{
				pPlayer->SetCommState( CEntityPlayer::STATE_LEAVEGAME );
				// CSceneLogic::GetSingletonPtr( )->PlayerLeaveFromGame( pPlayer );				
				CGlobalModule::GetSingleton().GlobalTelePort( pPlayer, EGLOBALTELE_TYPE_RETURNTOGATE, ESERVERTYPE_SCENESER );
				tMark = true;				
			}
			if ( tMark == true )
			{
				CMessage tMsgHead;
				CMessageReturn2GateResponse tMsgReturn2Gate;
				tMsgHead.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_RETURN2GATE );
				tMsgHead.set_msgpara( (int)&tMsgReturn2Gate );
				tMsgReturn2Gate.set_returntype( 1 );
				CSceneLogic::GetSingleton().Send2Player( pPlayer, &tMsgHead );
				return 0;
			}
		}	
		pPlayer->SetCommState( CEntityPlayer::STATE_RETURNTOGATE );
		CSceneLogic::GetSingletonPtr( )->PlayerLeaveFromGame( pPlayer );
	}
	return 0;
}

int CSceneServer::OnMessageServerInfoResponse(CMessage* pMsg)
{
	CMessageServerInfoResponse* tpMsg = ( CMessageServerInfoResponse* )( pMsg->msgpara() );
	if ( tpMsg == NULL)  return -1;

	// �������ط�����ע��״̬
	mbGateIsRegisted = true;

	int nDefaultGameID = CSceneLogic::GetSingletonPtr()->GetGameID();
	CSceneLogic::GetSingletonPtr()->SetWorldID(tpMsg->worldid());
	CSceneLogic::GetSingletonPtr()->SetLineID( tpMsg->lineid() );
	CSceneLogic::GetSingletonPtr()->SetGameID( tpMsg->gameid() );
	
	LOG_NOTICE( "default", "[%s] set gameid from %d to %d", __FUNCTION__, nDefaultGameID, tpMsg->gameid() );
	
	// �󲿷�����¶���Ĭ��gameid,ֻ�������������Ҫ���¼���һ�鲿���߼�����
	if( nDefaultGameID != (int)tpMsg->gameid() )
	{
		LOG_NOTICE( "default", "[%s] reload config for gameid %d", __FUNCTION__,  tpMsg->gameid() );
		//CSceneServer::GetSingletonPtr( )->ReadConfig();
		CSceneCfgManager::GetSingletonPtr()->Initialize( const_cast<char*>(CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(), const_cast<char*>("scene_config/sceneconfig.xml")) ));
	}

	CModuleManager::GetSingleton( ).LoadConfig( );

	// ���ػ�����Ϣ
	CMarriageModule::GetSingleton().LoadCampInfo( tpMsg->lineid() );
	CMarriageModule::GetSingleton().LoadMarriageCountFromDB( tpMsg->lineid() );

    // ����ҡǮ���û����а�
    CActivityYqsPlayerRankInfo::GetSingleton().LoadPlayerRankInfoFromDB();

	return 0;
}

int CSceneServer::OnMessageSceneNotOpenNoticeEvent( CMessage* pMsg )
{
	CMessageSceneNotOpenNotice* tpMsg = ( CMessageSceneNotOpenNotice* )( pMsg->msgpara() );
	CEntityPlayer* tpPlayer = CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( tpMsg->charid() );
	if ( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]When  redirect scene, dest scene not found, player %d didn't find", 
			__LK_FILE__, __LINE__, __FUNCTION__, tpMsg->charid() );
		return -1;
	}

	tpPlayer->SetCommState( CEntityPlayer::STATE_INMAP );

	CMessageGateErrorNotice tMsgFact;
	CMessage				tMsg;
	CMessageHead* tpHead = tMsg.mutable_msghead();
	tpHead->set_messageid( ID_G2C_NOTIFY_GATEERROR );
	tMsgFact.set_errorcode( EGATE_THESCENE_ISNOT_ONLINE );
	tMsg.set_msgpara( (uint32)&tMsgFact );
	CSceneLogic::GetSingletonPtr( )->Send2Player( tpPlayer, &tMsg );

	return 0;
}

int CSceneServer::OnMessageGetCountryInfo( CMessage* pMsg )
{
	CMessageCountryInfo* tpInfo = ( CMessageCountryInfo* )( pMsg->msgpara( ) );
	unsigned int tLength = tpInfo->length();

	if( tpInfo->has_countrylist() == true )
	{
		memcpy( mCountryArrary, tpInfo->countrylist().c_str(), 
			( sizeof( mCountryArrary ) >= tLength ) ? tLength : sizeof( mCountryArrary ) );
	}
	
	return 0;
}

int CSceneServer::OnMessagePlayerRedirectResponseEvent( CMessage* pMsg )
{
	CMessagePlayerRedirectResponse* tpMessage = (CMessagePlayerRedirectResponse*)( pMsg->msgpara() );
	CEntityPlayer* tpPlayer = CSceneLogic::GetSingletonPtr()->GetPlayerByCharID( tpMessage->charid( ) );
	if ( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "[%s:%d] can't find player %d", __FUNCTION__, __LINE__, tpMessage->charid( ) );
		return 0;
	}

	CMessage						tMsg;
	CMessageReconnectSceneNotice 	tMsgFact;

	if( tpMessage->has_address( ) == true )
	{
		tMsgFact.set_address( tpMessage->address( ).c_str( ) );
	}

	tMsgFact.set_lineid( tpMessage->lineid( ) );
	tMsgFact.set_mapid( tpMessage->mapid( ) );
	tMsgFact.set_posx( tpMessage->posx( ) );
	tMsgFact.set_posy( tpMessage->posy( ) );
	tMsg.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_RECONNECTSCENE );
	tMsg.set_msgpara( (uint32)&tMsgFact );

	LOG_INFO( "default", "Player[ %d : %s]Redirect Scene( %d : %d ) End, Scene all Playe Count Is[%d]", 
		tpPlayer->GetCharID(), tpPlayer->GetCharNameShow(), tpMessage->lineid( ), tpMessage->mapid( ),
		CSceneLogic::GetSingletonPtr()->GetPlayerNumber( ) - 1 );


	//TODO: DestroyEntity��DestroyPlayerInstance�ŵ��յ��ͻ���ǿ�ƹر�socketʱ���� 

	// �����Ѿ������ҷ�����������
	CSceneLogic::GetSingletonPtr()->DestroyEntity( (CEntityPlayer*)tpPlayer, SAVE_REDIRECT );

	//TODO:  �����Ϣ������󷢣���Ϊ�������Ϣ��ͻ��˾Ϳ�ʼ����Կ�� �������Ϣ�������ʧ��
	// �������ﻹͶ��ȡ���ˣ���˴�ʱplayer�Ѿ�destroy���ˣ������ݻ����ڴ��С�Ҫ�ġ���������������������
	CSceneLogic::GetSingletonPtr()->Send2Player( tpPlayer, &tMsg );	

	CSceneLogic::GetSingletonPtr()->DestroyPlayerInstance( (CEntityPlayer*)tpPlayer,  EM_LEAVE_REDIRECT, EM_SAVE2DB );

	return 0;	
}

//************************************
// Method:    PlayerLeaveFromGame
// FullName:  SceneServer::CSceneLogic::PlayerLeaveFromGame
// Access:    public 
// Returns:   int
// Qualifier: ���е�����뿪��������Ҫͳһ�߸ýӿڣ�
//			[����]: LeaveFromGame -> SavePlayer -> OnSavePlayer -> DestroyEntity
// Parameter: CEntityPlayer * tpPlayer
//************************************
int CSceneLogic::PlayerLeaveFromGame(CEntityPlayer* tpPlayer) 
{
	LK_ASSERT ( tpPlayer != NULL, return -1 );

	// ֪ͨ��ģ�����׼���뿪,����һЩ���̲���
	OnPlayerLeave( tpPlayer, tpPlayer->GetCommState() );

	// ���������Ҫ�����BUFF	
	CPropertyPlayer* tpProperty = ( CPropertyPlayer* ) tpPlayer->GetProperty();
	
	switch ( tpPlayer->GetCommState( ) )
	{	
	case CEntityPlayer::STATE_LEAVEGAME:
		{			
			tpProperty->RemoveBuffOnLogOff( );
			PERF_FUNC( "SavePlayer", SavePlayer( (CEntityPlayer*) tpPlayer, SAVE_LEAVEGAME ) );
			break;
		}
	case CEntityPlayer::STATE_FORCEEXIT:
		{
			tpProperty->RemoveBuffOnLogOff( );
			PERF_FUNC( "SavePlayer", SavePlayer( (CEntityPlayer*) tpPlayer, SAVE_FORCEEXIT ) );
			break;
		}
	case CEntityPlayer::STATE_KICKOUT:
		{
			tpProperty->RemoveBuffOnLogOff( );
			PERF_FUNC( "SavePlayer", SavePlayer( (CEntityPlayer*) tpPlayer, SAVE_KICKOUT ) );
			break;
		}
	case CEntityPlayer::STATE_REDIRECT:
		{
			PERF_FUNC( "SavePlayer", SavePlayer( (CEntityPlayer*) tpPlayer, SAVE_REDIRECT ) );
			break;
		}
	case CEntityPlayer::STATE_RETURNTOGATE:
		{
			tpProperty->RemoveBuffOnLogOff( );
			PERF_FUNC( "SavePlayer", SavePlayer( (CEntityPlayer*) tpPlayer, SAVE_RETURN2GATE ) );
			break;
		}
	case CEntityPlayer::STATE_INWAIT:
	case CEntityPlayer::STATE_REDIRECT_INWAIT:
		{
			PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( tpPlayer->GetCharID() );
			if ( tFindIter != mPlayerInWait.end( ) )
			{
				if (tFindIter->second == tpPlayer->get_id())
				{

#ifdef _FB_	
					// ����Ҵӵȴ�����ɾ��
	                CMapObject* tpMapObj = ( CMapObject* )CMapObjManager::GetSingletonPtr( )->GetMapObject(
    	                tpPlayer->GetLineID( ), tpPlayer->GetMapID( ), tpPlayer->GetMapIndex( ) );

        	        if( tpMapObj == NULL )
					{
						LOG_ERROR( "default", "[ %s : %d ][ %s ]Waiting Player( %d ) Cannt"
							" GetMapObject( %d : %d : %d )", __LK_FILE__, __LINE__, __FUNCTION__, 
						tpPlayer->GetCharID( ), tpPlayer->GetLineID( ), tpPlayer->GetMapID( ), 
						tpPlayer->GetMapIndex( ) );
					}
					else
					{

                		tpMapObj->DelPlayerWaitInCount( );

               		 	CMapModule::GetSingletonPtr( )->OnDestroyEntity( tpPlayer, SAVE_KICKOUT );					
					}
#endif

					mPlayerInWait.erase( tFindIter );
					LOG_DEBUG( "default" , "player %d leave from game while in wait", tpPlayer->GetCharID() );
				}
				else
				{
					LOG_ERROR("dafault", "player id(%d) not match waitqueue id(%d)", 
						tpPlayer->get_id(), tFindIter->second);
				}
			}
			else
			{
				LOG_ERROR("dafault", "player(%d) status is INWAIT, but not in InWait queue", tpPlayer->get_id());
			}

			// ������ʧ��֮ǰ�Ѿ������ٻ���creator id������
			if( tpPlayer->GetPetCreatorID() != INVALID_OBJ_ID )
			{
				CSceneObjManager::GetSingletonPtr()->DestroyObject(  tpPlayer->GetPetCreatorID() );
				tpPlayer->SetPetCreatorID( INVALID_OBJ_ID );
			}

			DestroyPlayerInstance( tpPlayer, EM_LEAVE_LEAVEGAME, EM_NOSAVE  );
			break;
		}
	default:
		{
			LOG_ERROR( "default", "[%s:%d] wrong player status %d", __FUNCTION__, __LINE__, tpPlayer->GetCommState( ) );
			break;
		}
	}


	LOG_INFO( "default", "[ %s : %d ][ %s ]Player [%d:%s] socket(%d) socktime(%d) commstat(%d) Wan't to LeaveGame, Scene Player num[%d]", 
			__LK_FILE__, __LINE__, __FUNCTION__,
			tpPlayer->GetCharID(), tpPlayer->GetCharNameShow(), tpPlayer->GetCommHandle(), tpPlayer->GetClientInfo()->mSockTime, 
			tpPlayer->GetCommState(), mPlayerContainer.size() );

	return 0;
}


int CSceneServer::OnMessageCreateMapNoticeEvent( CMessage* pMsg )
{
	CMessageCreateMapNotice* tpMsg = ( CMessageCreateMapNotice* )( pMsg->msgpara() );

	// ��ͼ�������ɹ��Ļ���ֱ�Ӿ�ͣ��
	if ( tpMsg->rtncode() == 0 )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ]Create Map Faild��because:%s", __LK_FILE__, 
			__LINE__, __FUNCTION__, tpMsg->notice().c_str() );

		// ��ʾһ��
		printf( "Error: create map failed: %s",  tpMsg->notice().c_str() );

		exit(-1);
	}

	CMessageCreateMapResponse	tMsgFact;
	CMessage					tMsg;
	CMessageHead* 				tpHead = tMsg.mutable_msghead();

	tpHead->set_srcfe(FE_SCENCESERVER);
	tpHead->set_srcid(mThisServerID);
	tpHead->set_dstfe(FE_GATESERVER);
	tpHead->set_dstid(2);
	tpHead->set_messageid( ID_S2G_CREATE_MAP_RESPONSE );

	int tServerID = 0;

	for ( int i = 0; i < tpMsg->lineid_size() && i < (int)tpMsg->count(); ++ i )
	{
		int tRtn = SUCCESS;
		int tLineID = tpMsg->lineid( i );
		tServerID = tLineID;
		if( IS_REPETION_LINE_ID( tLineID ) == false )
		{
			tRtn = CSceneLogic::GetSingletonPtr( )->CreateMap( tpMsg->lineid( i ), tpMsg->mapid( i ), 0, 
				tpMsg->tplname( i ).c_str() );
			CObj::msCreateMode = 1;

			if( tRtn != SUCCESS )
			{
				LOG_ERROR( "default", "[ %s : %d ][ %s ] CreateMap %d Error, tRtn = %d", __LK_FILE__, __LINE__, __FUNCTION__,
					tpMsg->mapid( i ), tRtn );
				// ��ʾ
				printf( "Error:Create Map failed.LineID:%d,MapID:%d", tpMsg->lineid( i ), tpMsg->mapid( i ) );
				continue ;
			}
		}
		else
		{
#ifdef _FB_
			int tMapID = tpMsg->mapid( i );

			CMapTpl* tpMapTpl = CMapTplManager::GetSingleton( ).CreateMapTpl( tpMsg->tplname( i ).c_str(), 
				tpMsg->mapid( i ), tpMsg->lineid( i ) );
			if ( tpMapTpl == NULL )
			{
				LOG_ERROR( "default", "[ %s : %d ][ %s ]LoadMap Err, MapID is %d", __LK_FILE__, __LINE__, 
					__FUNCTION__, tpMsg->mapid( i ) );
				return -1;
			}

			CPropertyModule::GetSingletonPtr( )->OnCreateMap( tpMsg->lineid( i ), tpMsg->mapid( i ), 0, 
				tpMsg->tplname( i ).c_str() );

			CRepetionInfo* tpRepetionInfo = NULL;
			while( ( tpRepetionInfo = CRepetionModule::GetSingletonPtr( )->GetRepetionInfoByMapID( tMapID,
					( tpRepetionInfo != NULL ) ? tpRepetionInfo->GetRepetionIndex( ) + 1 : 0 ) ) != NULL )
			{
				if( tpRepetionInfo == NULL )
				{
					LOG_ERROR( "default", "[ %s : %d ][ %s ]Map( %d ) Is Not A RepetionMap", __LK_FILE__, __LINE__,
							__FUNCTION__, tMapID );
					break;
				}

				if( tpRepetionInfo->MapIsInRepetion( tMapID ) == false )
				{
					LOG_ERROR( "default", "[ %s : %d ][ %s ] Map( %d ) Is Not A RepetionMap", __LK_FILE__, __LINE__,
							__FUNCTION__, tMapID );
					continue;
				}

				if( tpRepetionInfo->GetBeginMapID( ) == tMapID )
				{
					//ֻ�м��س�ʼ��ͼ��ʱ��������ػ�Ӧ

					CMessage tMessage;
					CMessageRegistRepetionInfo tMsgInfo;

					tMessage.set_msgpara((uint32_t) &tMsgInfo);
					pbmsg_sethead(&tMessage, ID_S2G_REGIST_REPETION_INFO, 0, 0, 0, 0, 0, 0);

					tMsgInfo.set_lineid( tLineID );
					tMsgInfo.set_repetionid( tpRepetionInfo->GetRepetionIndex( ) );
					for( int i = 0; i < tpRepetionInfo->GetMapSizeMax( ); i++ )
					{
						int tMapID = tpRepetionInfo->GetMapID( i );
						if( tMapID != INVALID_MAP_ID )
						{
							tMsgInfo.add_mapid( tMapID );
						}
					}
					tMsgInfo.set_playermax( tpRepetionInfo->GetPlayerCountMax( ) );
					tMsgInfo.set_backmapid( tpRepetionInfo->GetBackMapID( ) );
					tMsgInfo.set_backposx( tpRepetionInfo->GetBackPosX( ) );
					tMsgInfo.set_backposy( tpRepetionInfo->GetBackPosY( ) );
					tMsgInfo.set_countmax( 
							CSceneObjManager::GetSingletonPtr( )->mSceneObjManagerImp->mRepetion.max_size( ) );
					tMsgInfo.set_relogin( tpRepetionInfo->GetRelogin() );

					tMsgInfo.set_isontimeopen( tpRepetionInfo->IsOnTimeOpen() == true ?  1: 0);
					tMsgInfo.set_notlimittime( tpRepetionInfo->NotLimitTime() == true ? 1:0);
					for( unsigned int i = 0; i < WAIT_LIST_MAX; i++ )
					{
						WaitList* tpList = tpRepetionInfo->GetWaitListLevel( i );
						if( tpList == NULL )
						{
							break;
						}

						if( tpList->mLevelMin ==  0 )
						{
							break;
						}

						BattleLevel* tpLevel = tMsgInfo.add_level( );
						LK_ASSERT( tpLevel != NULL, continue );
						tpLevel->set_levelmin( tpList->mLevelMin );
						tpLevel->set_levelmax( tpList->mLevelMax );
					} 

					int i = 0;
					const DateSpace* tDateSpace = tpRepetionInfo->GetBattleOpenSpace( i );
					while( tDateSpace != NULL )
					{
						PBDateSpace* tPB = tMsgInfo.add_space( );
						LK_ASSERT( tPB != NULL, continue );	

						tPB->mutable_start( )->set_year( tDateSpace->mBegin.mYear );
						tPB->mutable_start( )->set_month( tDateSpace->mBegin.mMonth );
						tPB->mutable_start( )->set_week( tDateSpace->mBegin.mWeek );
						tPB->mutable_start( )->set_day( tDateSpace->mBegin.mDay );
						tPB->mutable_start( )->set_hr( tDateSpace->mBegin.mHr );
						tPB->mutable_start( )->set_minute( tDateSpace->mBegin.mMinute );
						tPB->mutable_start( )->set_sec( tDateSpace->mBegin.mSec );

						tPB->mutable_finish( )->set_year( tDateSpace->mEnd.mYear );
						tPB->mutable_finish( )->set_month( tDateSpace->mEnd.mMonth );
						tPB->mutable_finish( )->set_week( tDateSpace->mEnd.mWeek );
						tPB->mutable_finish( )->set_day( tDateSpace->mEnd.mDay );
						tPB->mutable_finish( )->set_hr( tDateSpace->mEnd.mHr );
						tPB->mutable_finish( )->set_minute( tDateSpace->mEnd.mMinute );
						tPB->mutable_finish( )->set_sec( tDateSpace->mEnd.mSec );

						i++;
						tDateSpace = tpRepetionInfo->GetBattleOpenSpace( i );
					}

					CSceneLogic::GetSingletonPtr( )->Send2Gate( &tMessage );
				}
			}
#endif
		}

		
		tMsgFact.add_lineid( tpMsg->lineid( i ) );
		tMsgFact.add_mapid( tpMsg->mapid( i ) );
		tMsgFact.add_tplname( tpMsg->tplname( i ).c_str() );
		LOG_NOTICE( "default", "Line %d Map[%s:%d] Create Sccusess", tpMsg->lineid( i ), tpMsg->tplname( i ).c_str(), tpMsg->mapid( i ) );
	}

	tMsg.set_msgpara( (uint32)&tMsgFact );
	CSceneLogic::GetSingletonPtr( )->Send2Gate( &tMsg );

	mCreateMapStatus = 1;
	return 0;
}



// ***************************************************************
//  Function:		OnMessagePlayerEnterMapNoticeEvent
//  Description:	���� ���ط�����֪ͨ������ҽ������Ϣ
//	Input:			pMsg - ��Ϣָ��
//	OutPut:			��
//	Return:			��
//	Others:			
//  Date:			11/01/2008
// 
// ***************************************************************
int CSceneServer::OnMessagePlayerEnterMapNoticeEvent( CMessage* pMsg )
{
	CMessagePlayerEnterMapNotice* tpMsg = ( CMessagePlayerEnterMapNotice* )( pMsg->msgpara() );

	// ���������δ׼���ã����ش�����
	if ( CSceneLogic::GetSingletonPtr()->GetServerStatus() != EM_SERVERSTATUS_RUN )
	{
		CMessagePlayerEnterMapResponse	tMsgFact;
		CMessage						tMsg;
		CMessageHead* 					tpHead = tMsg.mutable_msghead();

		tpHead->set_messageid( ID_S2G_PLAYER_ENTER_MAP_RESPONSE );
		tpHead->set_srcfe( FE_SCENCESERVER);
		tpHead->set_srcid( mThisServerID);
		tpHead->set_dstfe( FE_GATESERVER);
		tpHead->set_dstid( 2);

		tMsgFact.set_accountid( tpMsg->accountid() );
		tMsgFact.set_charid( tpMsg->charid() );
		tMsgFact.set_lineid( tpMsg->lineid() );
		tMsgFact.set_mapid( tpMsg->mapid() );
		tMsgFact.set_posx( tpMsg->posx() );
		tMsgFact.set_posy( tpMsg->posy() );
		tMsg.set_msgpara( (uint32)&tMsgFact );

		tMsgFact.set_errorcode(EM_KICKOUT_SERVERMAINTANCE);

		CSceneLogic::GetSingletonPtr( )->Send2Gate( &tMsg );
		return -1;
	}

	//�����ж�����Ƿ�����
	CEntityPlayer* tpPlayer = CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID(tpMsg->charid());
	if ( tpPlayer == NULL ) 
	{
		CSceneLogic::PLAYERID_MAP::iterator tFindIter = CSceneLogic::GetSingletonPtr()->mPlayerInWait.find( tpMsg->charid() );
		if ( tFindIter != CSceneLogic::GetSingletonPtr()->mPlayerInWait.end( ) )
		{
			tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
		}
	}

	if (tpPlayer != NULL)
	{
		LOG_ERROR("default", "player(%d:%s) has already in this server(sokfd = %d,%d)",
				tpPlayer->GetCharID(), tpPlayer->GetCharNameShow(), 
				tpPlayer->GetClientInfo( )->mSockIndex, tpPlayer->GetCommHandle( ));

		if ( tpPlayer->GetCommState( ) !=  CEntityPlayer::STATE_INWAIT && tpPlayer->GetCommState( ) !=  CEntityPlayer::STATE_REDIRECT_INWAIT  )
		{
			tpPlayer->SetCommState( CEntityPlayer::STATE_LEAVEGAME );
		}

		CSceneLogic::GetSingletonPtr()->PlayerLeaveFromGame(tpPlayer);
	}

	tpPlayer = ( CEntityPlayer* )CSceneObjManager::GetSingletonPtr()->CreateObject ( OBJTYPE_ENTITY_PLAYER );	
	CMapObject* tpMapObj = CMapObjManager::GetSingletonPtr( )->GetMapObject( tpMsg->lineid(), tpMsg->mapid(), 
		INVALID_MAP_INDEX, tpMsg->key( ) );
	if( tpPlayer == NULL || tpMapObj == NULL )
	{

		CMessagePlayerEnterMapResponse	tMsgFact;
		CMessage						tMsg;
		CMessageHead* 					tpHead = tMsg.mutable_msghead();

		tpHead->set_messageid( ID_S2G_PLAYER_ENTER_MAP_RESPONSE );
		tpHead->set_srcfe( FE_SCENCESERVER);
		tpHead->set_srcid( mThisServerID);
		tpHead->set_dstfe( FE_GATESERVER);
		tpHead->set_dstid( 2);

		tMsgFact.set_accountid( tpMsg->accountid() );
		tMsgFact.set_charid( tpMsg->charid() );
		tMsgFact.set_lineid( tpMsg->lineid() );
		tMsgFact.set_mapid( tpMsg->mapid() );
		tMsgFact.set_posx( tpMsg->posx() );
		tMsgFact.set_posy( tpMsg->posy() );
		tMsg.set_msgpara( (uint32)&tMsgFact );

		if( tpPlayer == NULL )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ] create player %d failed ", __LK_FILE__, __LINE__, __FUNCTION__,
				tpMsg->charid());
			tMsgFact.set_errorcode(EGAME_SCENESERVER_IS_FULLLIST);
		}
		else
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ] lind %d map %d index %d key %lld", __LK_FILE__, __LINE__, __FUNCTION__ ,
				tpMsg->lineid(), tpMsg->mapid(), INVALID_MAP_INDEX, tpMsg->key( ) );
			tMsgFact.set_errorcode(EGAME_SCENESERVER_MAP_NOT_EXIST);
		}

		CSceneLogic::GetSingletonPtr( )->Send2Gate( &tMsg );
		return -1;
	}	
	tpPlayer->SetEntityID( tpPlayer->get_id( ) );
	tpPlayer->SetEntityType( ENTITYTYPE_PLAYER );
	tpPlayer->SetAccountID( tpMsg->accountid() );
	tpPlayer->SetCharID( tpMsg->charid() );
	tpPlayer->SetLineID( tpMsg->lineid() );
	tpPlayer->SetMapID( tpMsg->mapid() );
	tpPlayer->SetIndex( tpMapObj->GetMapIndex( ) );
	tpPlayer->SetLoginToken( tpMsg->logintoken() );
	tpPlayer->SetCommHandle( 0 );
	tpPlayer->SetCommState( CEntityPlayer::STATE_INWAIT );
	tpPlayer->SetWaitTimer( 60 * 1 * 1000 );
	tpPlayer->SetLeaveTimer( 60 * 5 * 1000 );
	tpPlayer->SetDirection( DIR_DOWN );
	tpPlayer->SetMotionState( MOTION_IDLE );
	tpPlayer->SetAliveStatus( ALIVE_NORMAL );
	tpPlayer->SetHasTarget( false );
	tpPlayer->SetPKMode( PKMODE_TRAINING );
	tpPlayer->GetProperty()->SetEntityID( tpPlayer->get_id( ) );
	if( ( ( int )tpMsg->posx( ) ) !=  tpPlayer->GetPosX( ) )
	{
		tpPlayer->SetPosX( tpMsg->posx( ) );
	}
	if( ( ( int )tpMsg->posy( ) ) != tpPlayer->GetPosY( ) )
	{
		tpPlayer->SetPosY( tpMsg->posy( ) );
	}
	if ( tpMsg->roleworldid() == CSceneLogic::GetSingleton().GetWorldID() )
	{
		tpPlayer->SetRoleWorldID( 0 );
	}
	else
	{
		tpPlayer->SetRoleWorldID( tpMsg->roleworldid() );
	}
	
	
	// ����������		
	if ( tpMsg->familyid() > 0 )
	{				
		CMemberInfo tMemberInfo;	
		tpPlayer->SetFamilyID( tpMsg->familyid( ) );		
		tMemberInfo.mIfHasFamilyApplies =  tpMsg->ifhasapplies();
		tMemberInfo.mFamilyHeaderID = tpMsg->familyheaderid();	 	
		tMemberInfo.mFamilyPost = tpMsg->familypost();	
		tMemberInfo.mFamilyContribute = tpMsg->familycontribute();			
		tMemberInfo.mFamilyMoney = tpMsg->familymoney();	
					
		if ( tpMsg->corpsid() > 0 )
		{
			tpPlayer->SetCorpsID( tpMsg->corpsid() );
			tpPlayer->SetHeadCorpsID( tpMsg->headcorpsid() );
			tMemberInfo.mIfHasCorpsApply = tpMsg->ifhascorpsapply();	
			tMemberInfo.mCorpsHeaderID = tpMsg->corpsheaderid();
			tMemberInfo.mCorpsPost = tpMsg->corpspost();			
			tMemberInfo.mCorpsContribute = tpMsg->corpscontribute();	
			tMemberInfo.mCorpsMoney = tpMsg->corpsmoney();		
		}	
		tMemberInfo.mEntityID = tpPlayer->GetEntityID();
		CFamilyModule::GetSingleton().InsertFamilyMember( tpMsg->corpsid(), tpMsg->familyid(), tpPlayer->GetCharID(), tMemberInfo, tpMsg->familyname().c_str(), tpMsg->corpsname().c_str() );
	}	
	
	CPropertyPlayer *tpProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	tpProperty->GetRolePassword()->InitialPass( tpMsg->mutable_password()->c_str(), tpMsg->protecttime(), tpMsg->protecttimelength(), tpMsg->passwordstatus() );
	tpProperty->GetRolePassword()->SetEntityID(tpPlayer->GetEntityID());
	
	
	// ����
	tpPlayer->SetUnionID( tpMsg->unionid() );
	if ( tpMsg->has_unionname() )
	{
		tpPlayer->SetUnionName( tpMsg->mutable_unionname()->c_str() );	
	}	
	tpPlayer->SetHeadCorpsID( tpMsg->headcorpsid() );
	tpPlayer->SetCountryID( tpMsg->countryid() );
	tpPlayer->SetOfficialID( tpMsg->officialid() );
	tpPlayer->SetKingID( tpMsg->kingid() );
	if ( tpMsg->iftracedplayer() )
	{
		tpPlayer->SetIfTarcePlayer( true );	
		tpPlayer->InitializeLog();
	}	
	
	if ( tpMsg->has_validseconds())
	{
		tpPlayer->SetValidSeconds( tpMsg->validseconds() );
	} 		
		
	// ����ҷ���ȴ�����
	CSceneLogic::GetSingletonPtr( )->mPlayerInWait.insert( CSceneLogic::PLAYERID_MAP::value_type( tpMsg->charid(), tpPlayer->get_id() ) );
																		 
	// ֪ͨ·�ɷ�������ҽ��볡����Ӧ
	CMessagePlayerEnterMapResponse	tMsgFact;
	CMessage						tMsg;
	CMessageHead* 					tpHead = tMsg.mutable_msghead();

	tpHead->set_messageid( ID_S2G_PLAYER_ENTER_MAP_RESPONSE );
	tpHead->set_srcfe( FE_SCENCESERVER);
	tpHead->set_srcid( mThisServerID);
	tpHead->set_dstfe( FE_GATESERVER);
	tpHead->set_dstid( 2);

	tMsgFact.set_accountid( tpMsg->accountid() );
	tMsgFact.set_charid( tpMsg->charid() );
	tMsgFact.set_lineid( tpMsg->lineid() );
	tMsgFact.set_mapid( tpMsg->mapid() );
	tMsgFact.set_posx( tpMsg->posx() );
	tMsgFact.set_posy( tpMsg->posy() );
	tMsgFact.set_errorcode(0);
	tMsg.set_msgpara( (uint32)&tMsgFact );

	CSceneLogic::GetSingletonPtr( )->Send2Gate( &tMsg );

	LOG_INFO( "default", "Account[%d], Charactor[charid:%d charname:%s entityid:%d] is going to enter scenece...", 
			tpPlayer->GetAccountID(), tpPlayer->GetCharID(), tpPlayer->GetCharNameShow(), tpPlayer->GetEntityID( ) );	
	return 0;
}

//************************************
// Method:    OnMessagePlayerReturn2GateReponseEvent
// FullName:  SceneServer::CSceneServer::OnMessagePlayerReturn2GateReponseEvent
// Access:    public 
// Returns:   int
// Qualifier: ����ȷ����ҿ��Է���
// Parameter: CMessage * pMsg
//************************************
int CSceneServer::OnMessagePlayerReturn2GateReponseEvent( CMessage* pMsg )
{
	CMessagePlayerReturn2GateResponse* tpMsg = ( CMessagePlayerReturn2GateResponse* )( pMsg->msgpara() );
	CEntityPlayer* tpPlayer = CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( tpMsg->charid() );
	if ( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ] Player( %d ) Cann't find", __LK_FILE__, __LINE__, __FUNCTION__,
			tpMsg->charid() );
		return -1;
	}
	
	// �����Ѿ������ҷ�����������		
	tpPlayer->SetCommState( CEntityPlayer::STATE_RETURNTOGATE );
	CSceneLogic::GetSingletonPtr( )->PlayerLeaveFromGame( tpPlayer );
	return 0;
}

// ***************************************************************
//  Function: 	OnMessagePlayerPingRequest   
//  Description:����ͻ���ping��Ϣ
//  Date: 		10/18/2008
// 
// ***************************************************************
int CSceneServer::OnMessagePlayerPingRequest( CMessage* pMsg, CEntityPlayer* pPlayer)
{
	LK_ASSERT( pMsg != NULL && pPlayer != NULL, return -1 );

	CMessageClientPingServerRequest* pReqMsg = (CMessageClientPingServerRequest*) pMsg->msgpara();

	// ��¼�ͻ���pingֵ
	pPlayer->GetClientInfo( )->mNetSpeed = pReqMsg->latestpingvalue();

	// ˢ��PING��ʱ��
	if( mPingCheck != 0 )
	{
		bool tRefrush = pPlayer->RefrushPingTime( );	
		if( tRefrush == false )
		{
			// ˢ��ʧ��˵��2��PING��ʱ�����
			pPlayer->SpeedCheckTeleport( );
		}
	}

	CMessageClientPingServerResponse tResMsg;
	tResMsg.set_clientlocaltime( pReqMsg->clientlocaltime() );
	tResMsg.set_servertime( LINEKONG::GetTickCount() );

	CMessage tMsg;

	// ��Ϣ��־����, ��ʱ�� msgseq �ֶ�����ʾ�Ƿ��¼��Ϣ
	//tMsg.mutable_msghead()->set_msgseq( 1 );

	tMsg.mutable_msghead()->set_srcfe( FE_SCENCESERVER );
	tMsg.mutable_msghead()->set_dstfe( FE_CLIENT );
	tMsg.mutable_msghead()->set_messageid( ID_S2C_RESPONSE_PING );
	tMsg.set_msgpara( (uint32)&tResMsg );

	CSceneLogic::GetSingletonPtr( )->Send2Player( pPlayer, &tMsg );
	return 0;
}

int CSceneServer::ReadServerConfig( )
{
	LOG_INFO( "default", "Read Server Config Begin..." );

	TiXmlDocument tDoc;
	tDoc.LoadFile( "../config/sceneserver.xml" );

	TiXmlElement* tpRootEle = tDoc.FirstChildElement( "sceneserver" );
	if( tpRootEle == NULL )
	{
		LOG_ERROR( "default", "Sceneserver XML Error, No Root Eelement" ); 
		printf( "Sceneserver XML Error, No Root Eelement\n" );
		return -1;
	}

	TiXmlElement* tpElement = tpRootEle->FirstChildElement( "proxy_server" );
	if( tpElement == NULL )
	{
		LOG_ERROR( "default", "Sceneserver XML Error, No proxy_server data" ); 
		printf( "Sceneserver XML Error, No proxy_server data\n" );
		return -1;
	}
	else
	{
		const char* tpAddress = tpElement->Attribute( "Address" );
		if ( tpAddress == NULL )
		{
			LOG_ERROR( "default", "Sceneserver XML Error, No ProxyAddress data" ); 
			printf( "Sceneserver XML Error, No ProxyAddress data\n" );
			return -1;
		}

		mProxyServerAddr = tpAddress;
	}

	
	tpElement = tpRootEle->FirstChildElement( "scenece_server" );
	if ( tpElement == NULL )
	{
		LOG_ERROR( "default", "Sceneserver XML Error, No scenece_server data" ); 
		printf( "Sceneserver XML Error, No scenece_server data\n" );
		return -1;
	}
	else
	{
		const char* tpWanAddr		= tpElement->Attribute( "WanAddr" );
		const char* tpServerID 		= tpElement->Attribute( "ServerID" );
		const char* tpLanAddr		= tpElement->Attribute( "LanAddr" );
		if ( tpWanAddr == NULL || tpServerID == NULL)
		{
			LOG_ERROR( "default", "Sceneserver XML Error, No SceneAddress data" ); 
			printf( "Sceneserver XML Error, No SceneAddress data\n" );
			return -1;
		}

		mSceneserverWanAddr = tpWanAddr;
		mThisServerID = atoi(tpServerID);

		if ( tpLanAddr != NULL )
		{
			mSceneServerLanAddr = tpLanAddr;
		}
	}
	

	// Save
	TiXmlDocument tSaveDoc;
	//tSaveDoc.LoadFile( "../config/data/scene_config/dberrconfig.xml" );
	tSaveDoc.LoadFile( const_cast<char*>(CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(), const_cast<char*>("scene_config/dberrconfig.xml" ))));
	TiXmlElement* tpSaveElement = tSaveDoc.FirstChildElement( );
	for( ; tpSaveElement != NULL; tpSaveElement = tpSaveElement->NextSiblingElement( ) )
	{
		std::string tEleName = tpSaveElement->Value( );
		if( tEleName == "SavePath" )
		{
			const char* tpPath = tpSaveElement->Attribute( "path" );
			if( tpPath == NULL )
			{
				LOG_ERROR( "default", "Sceneserver dberrconfig XML Error, No Save Path" );
				printf( "Sceneserver dberrconfig XML Error, No Save Path\n" );
				return -1;
			}

			mSavePath = tpPath;
		}

		if( tEleName == "SaveBak" )
		{
			const char* tpPath = tpSaveElement->Attribute( "path" );
			if( tpPath == NULL )
			{
				LOG_ERROR( "default", "Sceneserver dberrconfig XML Error, No Save Path" );
				printf( "Sceneserver dberrconfig XML Error, No Save Path\n" );
				return -1;
			}

			mBakPath = tpPath;
		}
	}

	// Save
	TiXmlDocument tDelDoc;
	/*tDelDoc.LoadFile( "../config/data/scene_config/deletelist.xml" );*/
	tDelDoc.LoadFile( CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(),"scene_config/deletelist.xml" ));
	TiXmlElement* tpDelElement = tDelDoc.FirstChildElement( );
	for( ; tpDelElement != NULL; tpDelElement = tpDelElement->NextSiblingElement( ) )
	{
		std::string tEleName = tpDelElement->Value( );
		if( tEleName == "Item" )
		{
			const char* tpID = tpDelElement->Attribute( "id" );
			if( tpID == NULL )
			{
				continue;
			}

			mDeleteList.push_back( atoi(tpID) );
		}
	}

	LOG_INFO( "default", "Read Server Config End..." );
	return 0;
}



int CSceneServer::ReadConfig( )
{
	// �������ƴ�
	CDirtyWord::GetSingletonPtr( )->OI_Dirty_start();

	int tRet = 0;
	PERF_FUNC( "LoadTemplate", tRet = CDataStatic::Initialize() );
	// ����ģ��	
	if ( tRet < 0 )
	{
		printf( "load template failed %d\n", tRet );
		LOG_FATAL( "default", "load template failed %d\n", tRet  );
		return -1;
	}	

	// ����������־
	DEFAULT_LOG* tpDefault = CSceneCfgManager::GetSingletonPtr()->GetDefault_log();
	if ( tpDefault != NULL )
	{
		// �����־���⣬��Ϊ֮ǰ�Ѿ��������ˣ�����ֻ�ǳ�ʼ��
		INIT_ROLLINGFILE_LOG( tpDefault->mIdentifier, tpDefault->mDirectory, (LogLevel)tpDefault->mPriority, tpDefault->mMaxfilesize, tpDefault->mMaxbackupindex );
	}

	LOG_NOTICE( "default", "Template Ver %d", CDataStatic::sTemplateVersion );

	mPingCheck = CSceneCfgManager::GetSingletonPtr( )->GetScenelogic_cfg( )->mPingcheck;

	// �߼�������
	CSceneLogic::GetSingletonPtr()->ReadConfig();

	return 0;
}

int CSceneServer::Initailize( int vInitFlag )
{	
	if( vInitFlag == 1 )
	{
		mThisServerID = 0;
		mPingCheck = 0;
		mProxyServerAddr.clear();
		mSceneserverWanAddr.clear();
		mSceneServerLanAddr.clear();
		mSceneName.clear();
		mSavePath.clear();
		mBakPath.clear();

		mLastTickCount = LINEKONG::GetTickCount();
		mLastPorxyKeepAliveTime = time(0);
		mLastGateKeepAliveTime = time(0);
		mLastLogStatInfoTime = time(0);
		mTimerOfKeepAlive = CWTimer(5000);

		// ��������ע����Ϣ
		mbGateIsRegisted				= false;

		mLaunchStatus = 0;
		mCreateMapStatus = 0;
		m_LoadConfigFuncList.initailize();
	}

	mDeleteList.clear();

	ClearRunFlag( ); //��ʼ����״̬

	CClientHandle::mShmPtr =  mShmPtr;
	mClientHandle = new CClientHandle;
	LK_ASSERT( mClientHandle != NULL, return -1 );

	CSceneObjManager::mShmPtr = mShmPtr;
	CSceneObjManager* tpScenObjMng = new CSceneObjManager;
	LOG_INFO( "default", "CSceneObjManager addr %6x", tpScenObjMng);

	// �ָ��������ݵ�ָ��
	if( vInitFlag == 0 )
	{
		CSceneObjManagerImp* pSceneneObjManagerImp = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp;
		CSceneObjManagerImp::ObjMng_NpcPolicy::iterator tPolicyIt;
		for( tPolicyIt = pSceneneObjManagerImp->mNpcPolicy.begin( ); tPolicyIt != pSceneneObjManagerImp->mNpcPolicy.end( ); ++tPolicyIt )
		{
			CNpcPolicy* tpPolicy = &( *tPolicyIt );
			tpPolicy->Resume();
		}
	}

	CSceneLogic::mShmPtr = mShmPtr;
	CSceneLogic* tpSceneLogic = new CSceneLogic;
	LK_ASSERT( tpSceneLogic != NULL, return -1 );
	LOG_NOTICE( "default", "CSceneLogic addr %6x", tpSceneLogic);

	CLogicModule::mShmPtr = mShmPtr;
	CModuleManager*	tpModuleManager = new CModuleManager;
	LK_ASSERT( tpModuleManager != NULL, return -1 );
	LOG_NOTICE( "default", "CModuleManager addr %6x", tpModuleManager);

	CMessageQueue::mShmPtr = mShmPtr;
	CMessageQueue* tpMessageQueue = new CMessageQueue;
	LK_ASSERT( tpMessageQueue != NULL, return -1 );
	LOG_NOTICE( "default", "CMessageQueue addr %6x", tpMessageQueue);

	CCreatorManager::mShmPtr = mShmPtr;
	CCreatorManager* gpCreatorManager = new CCreatorManager;
	if ( gpCreatorManager == NULL )
		return -1;

	CSceneCfgManager::mShmPtr = mShmPtr;

	// ������Դ
	CSceneCfgManager* tpSceneCfg = new CSceneCfgManager;
	if ( tpSceneCfg == NULL )
		return -1;

	// û�г�Ա����������new�ڹ����ڴ���
	CMessageDispatcher* tpMessageDispatcher = new CMessageDispatcher;
	if ( tpMessageDispatcher == NULL )
		return -1;

	// ��Ϣ����
	CMessageFactory* tpMessageFactory = new CMessageFactory;
	if ( tpMessageFactory == NULL )
		return -1;
	
	// ��ʱ��������
	CTimerMng::mShmPtr = mShmPtr;
	CTimerMng* tpTimerMng = new CTimerMng;
	if ( tpTimerMng == NULL )
		return -1;

	return 0;
}

void CSceneServer::CheckTimer ()
{
	unsigned int tNowCount = LINEKONG::GetTickCount();
	unsigned int tInterval = tNowCount - mLastTickCount;

	if ( tInterval < 100 )
	{
		return ;
	}
	
	
	PERF_FUNC( "ChkTimerQ", CTimerMng::GetSingletonPtr()->CheckTimerQueue( tInterval ) );

	mLastTickCount = tNowCount ;

	CSceneLogic* tpLogic = CSceneLogic::GetSingletonPtr( );
	tpLogic->OnTimer( tNowCount, tInterval );
	

	// �������5��
	if (mTimerOfKeepAlive.Elapse(tInterval) == true) 
	{
		SCENELOGIC_CFG* tpSceneCfg = CSceneCfgManager::GetSingletonPtr()->GetScenelogic_cfg();
		if( tpSceneCfg == NULL )
		{
			return;
		}

		time_t tNow = time(NULL);

		// ���proxy�Ͽ�������2��proxy����û�л�Ӧ
		if ( mProxyClient.GetSocket()->GetStatus() != tcs_connected
			|| (tNow - mLastPorxyKeepAliveTime) >= (int) (tpSceneCfg->mToproxyheartbeatsec * 2) )
		{
			if (Connect2Proxy() == true)
			{
				if( Regist2ProxyServer() == true )
				{
					// ע��proxy�ɹ�������������
					SendKeepAliveToProxy();
				}
				else
				{
					LOG_ERROR( "default", "Register Proxy Server Failed" );
				}
			}
		}

		// ����proxy����
		if(  tNow - mLastPorxyKeepAliveTime >= (int)(tpSceneCfg->mToproxyheartbeatsec) )
		{
			SendKeepAliveToProxy();
		}

		// ����gate����
		if( tNow - mLastGateKeepAliveTime >= (int)(tpSceneCfg->mTogateheartbeatsec) )
		{
			// �ж��Ѿ���������ע�Ṧ�ܣ���δ�ɹ����������ط���������ע����Ϣ
			if( mbGateIsRegisted == false )
			{
                LOG_WARN( "default", "Try to regist to gate server at time( %lld  )", (long long)tNow );
				bool lbForRegist2Gate = Regist2GateServer(  );
				if ( lbForRegist2Gate == false )
				{
					LOG_ERROR( "default", "send regist message to gate server failed at time( %lld )!", (long long)tNow );
				}
			}

			SendKeepAliveToGate();
			time(&mLastGateKeepAliveTime);
		}

		/*
		if( tNow - mLastLogStatInfoTime >= (int)(tpSceneCfg->mTologstatinfosec) )
		{
			CSceneLogic::GetSingleton().mStatInfo.LogStatInfo();
			CSceneLogic::GetSingleton().mStatInfo.SaveStatInfo();
			mLastLogStatInfoTime = tNow;
		}
		*/
	}
}

int CSceneServer::CheckLaunchServer()
{

	// ��ȫ�˳�
	if( CSceneLogic::GetSingletonPtr()->GetServerStatus() == EM_SERVERSTATUS_EXIT )
	{
		printf( "\n" );
		printf("-------------------------------------------\n");
		printf("|             Congratulation!             |\n");
		printf("|	xyj-gameserver(ID:%02d) exit success! |\n", mThisServerID);
		printf("-------------------------------------------\n");

		LOG_NOTICE( "default", "-------------------------------------------\n");
		LOG_NOTICE( "default", "|             Congratulation!             |\n");
		LOG_NOTICE( "default", "|	xyj-gameserver(ID:%02d) exit success! |\n", mThisServerID);
		LOG_NOTICE( "default", "-------------------------------------------\n");

		return 1;
	}
	else if( CSceneLogic::GetSingletonPtr()->GetServerStatus() == EM_SERVERSTATUS_SHUDOWNING )
	{
		printf(".");
		CSceneLogic::GetSingletonPtr( )->KickAllExcept( 0 );
	}


	if ( mLaunchStatus != 0 )
		return 0;
	
	if ( mCreateMapStatus == 0 )
		return 0;

	bool bRet = CModuleManager::GetSingletonPtr()->CheckLaunchServer();
	if ( bRet )
	{
		mLaunchStatus = 1;

		printf("\n-------------------------------------------\n");
		printf("|             Congratulation!             |\n");
		printf("|  xyj-gameserver(ID:%02d) startup success! |", mThisServerID);
		printf("\n-------------------------------------------\n");

		LOG_NOTICE( "default", "xyj-gameserver startup success!");

		// ֪ͨ��ģ������������ɹ�
		CModuleManager::GetSingletonPtr()->LaunchComplete();
	}

	return 0;
}

int CSceneServer::RecvServerMsg(int vMsgCount)
{
	fd_set fds_read;
	struct timeval stMonTime = {0};
	int iMaxFD = 0;

	FD_ZERO( &fds_read );

	// add router fd
	int iTempFD = mProxyClient.GetSocket()->GetSocketFD();
	int iTempStatus = mProxyClient.GetSocket()->GetStatus();

	if ( iTempFD > 0 && iTempStatus == tcs_connected )
	{
		FD_SET(iTempFD, &fds_read);
		if(iTempFD > iMaxFD)
		{
			iMaxFD = iTempFD;
		}
	}

	// select 
	int iOpenFDNum = select( iMaxFD + 1, &fds_read, NULL, NULL, &stMonTime );

	if ( iOpenFDNum <= 0 )
	{
		return 0;
	}

	// Recv Data From Server
	BYTE tCodeBuff[ MAX_CODE_LEN ];
	unsigned short tBuffLen = sizeof( tCodeBuff );
	int iRet = -1;

#ifdef _USE_MESSAGE_QUEUE_	
	BYTE tMsgPara[ MAX_CODE_LEN ];
	unsigned short tParaLen = sizeof( tMsgPara );
#endif //_USE_MESSAGE_QUEUE_

	iTempFD = mProxyClient.GetSocket()->GetSocketFD();
	if ( iTempFD >0 && FD_ISSET(iTempFD, &fds_read) )
	{
		if( mProxyClient.GetSocket()->RecvData() < 0 )
		{
			LOG_ERROR( "default", "[%s:%d] recv proxy code failed", __FUNCTION__, __LINE__ );
			return -1;
		}

		CProxyHead tProxyHead;
		CMessage tMessage;

		// Recv Data From Proxy
		while ( 1 )
		{
			tBuffLen = sizeof( tCodeBuff );
			iRet = mProxyClient.GetSocket()->GetOneCode( tBuffLen, tCodeBuff );
			if ( iRet <= 0  )
			{
				//LOG_ERROR( "default", "Get One Code From Router server Faild %d", iRet );
				break;
			}

			if( tBuffLen == 0 || tBuffLen > sizeof(tCodeBuff))
			{
				LOG_ERROR( "default", "Code Len %d impossible", tBuffLen );
				break;
			}
			
			//TODO: ��proxy������Ϣ����ʽӦ�ö���һ���ģ���������Ͳ���Ҫclear,ÿ�ζ�ֱ�Ӹ���ԭ������
			//tProxyHead.Clear();
			//tMessage.Clear();

#ifdef _USE_MESSAGE_QUEUE_	

			int decode_ret = pbmsg_getheadpb( (char*)tCodeBuff, tBuffLen  , &tProxyHead, &tMessage, (char*)tMsgPara, &tParaLen );
			if( decode_ret <= 0 )
			{
				LOG_ERROR("default", "decode router message failed %d", decode_ret );
				continue;
			}

			if (tProxyHead.has_opflag() && CMD_KEEPALIVE == tProxyHead.opflag() && tProxyHead.srcfe() == CET_PROXYSERVER)
			{
				LOG_DEBUG("default", "RecvFromProxy: %s", tProxyHead.ShortDebugString().c_str());

				time(&mLastPorxyKeepAliveTime);	
				continue;
			} 

			if(tMessage.mutable_msghead()->has_srcfe() == false)
			{
				tMessage.mutable_msghead()->set_srcfe( FE_PROXYSERVER );
			}


			iRet = CMessageDispatcher::GetSingletonPtr( )->AppendMsg ( &tMessage, (void*)tMsgPara, tParaLen );

			if( iRet != CMessageDispatcher::Success )
			{
				if ( iRet != CMessageDispatcher::Err_MsgQueueFull )
				{
					LOG_FATAL( "default", "MessageQueue Full" );
					break;
				}
				else
				{
					LOG_ERROR( "default", "MessageQueue AppendMsg Faild %d", iRet );
					continue;
				}

			}
#else

			int decode_ret = pbmsg_getheadmsg( (unsigned char*)tCodeBuff, tBuffLen  , &tProxyHead, &tMessage );
			if( decode_ret <= 0 )
			{
				LOG_ERROR("default", "decode router message failed %d", decode_ret );
				continue;
			}

			if (tProxyHead.has_opflag() && CMD_KEEPALIVE == tProxyHead.opflag() && tProxyHead.srcfe() == CET_PROXYSERVER)
			{
#ifdef _DEBUG_
				LOG_DEBUG("default", "RecvFromProxy: %s", tProxyHead.ShortDebugString().c_str());
#endif
				time(&mLastPorxyKeepAliveTime);	
				continue;
			}

			if(tMessage.mutable_msghead()->has_srcfe() == false)
			{
				tMessage.mutable_msghead()->set_srcfe( FE_PROXYSERVER );
			}


			CMessageDispatcher::GetSingletonPtr()->ProcessMessage( &tMessage );
#endif

		}

	}


	return 0;
}


int CSceneServer::RecvClientMsg(int vMsgCount)
{
	int vRecvCount = 0;

	while( vRecvCount < vMsgCount )
	{
		int vRecvRet = mClientHandle->Recv (  );

		vRecvCount ++;

		// �����ѿ�
		if ( vRecvRet == CLIENTHANDLE_QUEUE_EMPTY )
		{
			// ������пգ�˯�� 1 ms 
			struct timespec tv;
			tv.tv_sec = 0;
			tv.tv_nsec = 1000; 

			nanosleep( &tv, NULL );
			break;
		}
		else if ( vRecvRet != CLIENTHANDLE_SUCCESS )
		{
			//LOG_FATAL( "default", "ClientHandle->Recv faild %d", vRecvRet );
			continue;
		}
	}
	
	return 0;
}

void CSceneServer::OnTimer( unsigned int vTickCount )
{

}

void CSceneServer::OnAccept( int vCommHandle )
{

}

bool CSceneServer::Connect2Proxy()
{
	char tIP[ 64 ] = {0};
	short tPort = 0;
	int tServerID = mThisServerID ;

	SplitSockAddr( mProxyServerAddr.c_str(), tIP, tPort );
	mProxyClient.Initialize( FE_PROXYSERVER, tServerID, inet_addr( tIP ), tPort );

	// ����ʹ������IP
	if( mSceneServerLanAddr.length() > 0  )
	{
		SplitSockAddr( mSceneServerLanAddr.c_str(), tIP, tPort );
	}
	else
	{
		SplitSockAddr( mSceneserverWanAddr.c_str(), tIP, tPort );
	}

	if ( mProxyClient.ConnectToServer( tIP ) )
	{
		LOG_ERROR( "default", "Connect to ProxyServer(%s) use %s Faild", mProxyServerAddr.c_str(), tIP );
		return false;
	}

	return true;
}

bool CSceneServer::Regist2ProxyServer()
{
	// ������ ProxyServer ����ע����Ϣ
	CProxyHead tHead;
	char message_buffer[PLAYER_DATALEN];
	pbmsg_setproxy(&tHead, CET_GAMESERVER, CET_PROXYSERVER, mThisServerID, 1, TRANS_P2P, CMD_REGSERVER);

	unsigned short message_length  = tHead.ByteSize() + 4;
	*((unsigned short*) message_buffer)  = message_length;
	*((unsigned short*) (message_buffer+2))  = tHead.ByteSize();

	if(tHead.SerializeToArray(message_buffer+4, message_length - 4))
	{
		LOG_DEBUG("default", "regist to proxyserver (%d): head=[%d:%s]",  message_length , tHead.ByteSize(), tHead.ShortDebugString().c_str());
		if( mProxyClient.GetSocket()->SendOneCode(message_length, (BYTE*)message_buffer) == 0 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}else
	{
		LOG_INFO("default", "regist to proxyserver error");
		return false;
	}
}

bool CSceneServer::Regist2GateServer()
{
	// �����ط�����ע��
	CMessageServerInfoNotice	tMsgFact;
	CMessage					tMsg;
	CMessageHead* 				tpHead = tMsg.mutable_msghead();

	tpHead->set_messageid( ID_S2G_SERVER_INFO_NOTICE );
	tpHead->set_srcfe( FE_SCENCESERVER);
	tpHead->set_srcid( mThisServerID);
	tpHead->set_dstfe( FE_GATESERVER);
	tpHead->set_dstid( 2);
	tMsgFact.set_address( mSceneserverWanAddr.c_str( ) );
	//tMsgFact.set_servername( mSceneName.c_str( ) );
	tMsgFact.set_serverversion( VERSION );
	tMsgFact.set_templateversion( CDataStatic::sTemplateVersion );
	tMsgFact.set_taskversion( CDataStatic::sTaskVersion );
	tMsgFact.set_serverid ( mThisServerID);
	tMsgFact.set_launchmode (mShmPtr->GetInitMode () == SHM_INIT ? GAME_LAUNCH_BY_INITIAL: GAME_LAUNCH_BY_RECOVERY);
	tMsgFact.set_playercapacity (SERVER_CAP_PLAYER); 
	tMsg.set_msgpara( (uint32)&tMsgFact );

	return CSceneLogic::GetSingletonPtr()->Send2Gate( &tMsg );
}

int CSceneServer::ConnectToServer( )
{
	// ÿ�����ӷ�����ǰ��������һ��keepaliveʱ��
	mLastGateKeepAliveTime = time(NULL);
	mLastPorxyKeepAliveTime = time(NULL); 

	if (Connect2Proxy() == true)
	{
		if( Regist2ProxyServer() == false )
		{
			printf( "Register To ProxyServer Faild\n" );
			LOG_ERROR( "default", "Register To ProxyServer Faild" );
			return -1;
		}
		else
		{
			// ����proxy�ɹ�����������һ��������Ϣ
			SendKeepAliveToProxy();
			LOG_NOTICE( "default", "Register To ProxyServer Success, Now Send KeepAlive" );

			//CSceneLogic::GetSingleton().mStatInfo.LoadStatInfo();
		}

		if( Regist2GateServer() == false )
		{
			printf( "Register To GateServer Faild\n" );
			LOG_ERROR( "default", "Register To GateServer Faild" );
			return -1;
		}
	}
	else
	{
		printf( "Connect To ProxyServer Faild\n" );
		LOG_ERROR( "default", "Connect To ProxyServer Faild" );
		return -1;
	}

	return 0;
}



// ********************************************************************** //
// CSceneLogic
// ********************************************************************** //
template<>  CSceneLogic* CSingleton< CSceneLogic >::spSingleton = NULL;

CSharedMem* CSceneLogic::mShmPtr = NULL;

unsigned int CSceneLogic::CountSize( )
{
	return sizeof( CSceneLogic );
}

CSceneLogic::CSceneLogic( ) : mTimer( 1000 ), mSavePerf(0)
{
	if ( mShmPtr->GetInitMode () == SHM_INIT )
	{
		LOG_INFO( "default", "CSceneLogic Initailize");
		Initailize();
	} 
	else
	{
		LOG_INFO( "default", "CSceneLogic Resume");
		Resume();
	}
}

CSceneLogic::~CSceneLogic( )
{
}

int CSceneLogic::Initailize(  )
{
	mPlayerInWait.initailize();
	mPlayerInLost.clear();
	mPlayerCommIndex.initailize();
	mPlayerNameIndex.initailize();
	mPlayerContainer.initailize();
	mNpcContainer.initailize();
	mDeleteList.initailize();

	mTimer = 0;
	mStateCheckTimer = CWTimer(1000);
	mDailyTimer = CWTimer(20000);

	CalcCurrentDay( );
	mEvent = CEvent( );
	mServerStatus = EM_SERVERSTATUS_RUN;
	mTimeMemCheck = CWTimer(2000);
	mWorldID = 0;
	mLineID = 0;

	// ����ʱ��ʼ��һ�Σ�������ٴθ���gateserver�Ļ�Ӧ������ʼ��
#ifdef _DEBUG_
	mGameID = 504; 
#else
	mGameID = 4;
#endif


	return 1;
}

int CSceneLogic::Resume()
{
	return 0;
}



void* CSceneLogic::operator new( size_t size )
{
	return ( void* ) mShmPtr->CreateSegment( size );
}

void  CSceneLogic::operator delete( void* pointer )
{

}

void* CSceneLogic::operator new(size_t size, const char* file, int line)
{
	return operator new ( size );
}
void CSceneLogic::operator delete(void* pointer, const char* file, int line)
{

}

void CSceneLogic::OnTimer( unsigned int vTickCount, unsigned int vTickOffset )
{
	// ÿ��2���ӣ��������еȴ��е���Һ��쳣���ߣ�û�����߰��������
	if ( mTimer.Elapse( vTickOffset ) == true )
	{
		std::vector< unsigned int > tPlayerTomb;
		PLAYERID_MAP::iterator tBeginIter	= mPlayerInWait.begin( );
		PLAYERID_MAP::iterator tEndIter		= mPlayerInWait.end( );

		// ����ʱ���ӵ����
		for ( ; tBeginIter != tEndIter; tBeginIter ++ )
		{
			CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr( )->GetObject( tBeginIter->second );
			if( tpPlayer == NULL )
			{
				LOG_ERROR( "default", "player %d,%d can't find in objmanager",tBeginIter->first, tBeginIter->second );
				continue;
			}

			if ( tpPlayer->GetWaitTimer( )->Elapse( mTimer.mMaxDuration ) == true )
			{
				LOG_ERROR( "default", "player[%d:%s] object id(%d) didn't connect in the specific time", 
						tpPlayer->GetCharID(), tpPlayer->GetCharNameShow(), tBeginIter->second);

				tPlayerTomb.push_back( tBeginIter->second );
			}
		}

		for ( size_t i = 0; i < tPlayerTomb.size( ); i ++ )
		{
			CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject(tPlayerTomb[i]);
			PlayerLeaveFromGame(tpPlayer);
		}

		// ����ʱ��Session
		std::vector< unsigned int > tExpireSession;
		CSceneObjManagerImp::ObjMng_Session::iterator tSessionBeginIter = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp->mSession.begin();
		CSceneObjManagerImp::ObjMng_Session::iterator tSessionEndIter	 = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp->mSession.end();
		for ( ; tSessionBeginIter != tSessionEndIter; ++tSessionBeginIter )
		{
			CSession *pSession = (CSession *) &(*tSessionBeginIter);
			if ( pSession->GetTimer().Elapse( mTimer.mMaxDuration ) == true )
			{
				tExpireSession.push_back( pSession->get_id() );				
			}
		}

		for ( size_t i = 0; i < tExpireSession.size( ); i ++ )
		{
			OnSessionTimeOut( tExpireSession[ i ] );
			LOG_DEBUG( "default", "destroy session %d",tExpireSession[ i ] );
			CSceneObjManager::GetSingletonPtr()->DestroyObject( tExpireSession[ i ] );
		}
		
		tExpireSession.clear();
		
		// ��鷴����ӳٴ���( ����Offset��ʱ�������ã������ڲ���û���õ���
		mAHControlMng.OnTimer( vTickCount, vTickOffset);

		// ���server���ڰ�ȫ�˳�,���ñ�־׼���˳�
		if( GetServerStatus() ==  EM_SERVERSTATUS_SHUDOWNING )
		{
			// ֱ����������û����ң�����ʽ�˳�
			if( mPlayerContainer.empty() )
			{
				LOG_INFO( "default", "-------------------------------------------------" );
				LOG_INFO( "default", "- All Players Have Logout, Now Shutdown Server. -" );
				LOG_INFO( "default", "-------------------------------------------------" );

				//mStatInfo.SaveStatInfo();
				mServerStatus = EM_SERVERSTATUS_EXIT;
			}
		}

		mTimer = CWTimer( 2000 );
	}

	// ����������״̬��1. ��ʱ���� 2. �����������.����
	OnCheckOnlieStateEvent( vTickCount, vTickOffset );

	// �������е�ģ��, ֪ͨģ���������ʱ����
	CModuleManager::GetSingleton( ).Timer( vTickCount, vTickOffset );

	mSavePerf += vTickOffset;
	if (mSavePerf >= 60000)
	{
		PERF_LOG;

		char cObjDumpBuff[20480] = {0};
		unsigned int unBuffLen = sizeof(cObjDumpBuff);

		CSceneObjManager::GetSingletonPtr()->Dump(cObjDumpBuff, unBuffLen);
		LOG_INFO( "stat", "%s", cObjDumpBuff );

		unBuffLen = sizeof(cObjDumpBuff);
		CTimerMng::GetSingletonPtr()->Dump(cObjDumpBuff, unBuffLen);
		LOG_INFO( "stat", "%s", cObjDumpBuff );

		unBuffLen = sizeof(cObjDumpBuff);
		CMessageQueue::GetSingletonPtr()->Dump(cObjDumpBuff, unBuffLen);
		LOG_INFO( "stat", "%s", cObjDumpBuff );

		unBuffLen = sizeof(cObjDumpBuff);
		CSceneServer::GetSingletonPtr()->mClientHandle->Dump(cObjDumpBuff, unBuffLen);
		LOG_INFO( "stat", "%s", cObjDumpBuff );
		
		LOG_INFO( "stat", "Task Lua: %d", CTaskModule::GetSingletonPtr()->GetLuaVMUsedMem() );
		LOG_INFO( "stat", "Repetion Lua: %d", CRepetionModule::GetSingletonPtr()->GetLuaVMUsedMem() );
		mSavePerf = 0;

		// ��ӡ�ڴ�ʹ�����
		Show();
	}

	if( mDailyTimer.Elapse( vTickOffset ) == true )
	{
		DailyRefresh();
	}

	// �ɵ�ɾ���б���Ķ���
	DoDeleteList();
}

void CSceneLogic::DoDeleteList()
{
	for( unsigned int i = 0; i < mDeleteList.size(); i++ )
	{
		CEntity *pEntity = CSceneLogic::GetSingletonPtr( )->GetEntity( mDeleteList[ i ] );
		if ( pEntity == NULL )
			continue;
		CSceneLogic::GetSingleton( ).DestroyEntity( pEntity, 0 );
	}
	mDeleteList.clear();
}

void CSceneLogic::AddDeleteList( unsigned int unEntityID )
{
	mDeleteList.push_back( unEntityID );
}


void CSceneLogic::DailyRefresh()
{
	time_t tval;
	struct tm *now;        
	time(&tval);
	now = localtime(&tval);
	static int tLastSec = 0;
	int tNowWeek = now->tm_wday;
	if ( now->tm_hour == (int)CSceneCfgManager::GetSingleton().GetProperty_cfg()->mRefresh_hour
		&& now->tm_min == (int)CSceneCfgManager::GetSingleton().GetProperty_cfg()->mRefresh_minute )
	{
		// Ϊ�˱���һ���ڵĶ���޸�
		if ( time( NULL ) - tLastSec > 1000 )
		{
			mCurrentDay++;
			tLastSec = time( NULL );

			LOG_NOTICE( "default", "new day comme , now do some refresh" );
			CModuleManager::GetSingletonPtr()->OnNewDayCome( );
			
			// �ж���ˢ��
			if( tNowWeek == (int)CSceneCfgManager::GetSingleton().GetProperty_cfg()->mRefresh_week  )
			{
				WeeklyRefresh();
			}
		}			
	}
}

// ÿ��ˢ��
void CSceneLogic::WeeklyRefresh()
{
	LOG_NOTICE( "default", "new week comme , now do some refresh" );
	CModuleManager::GetSingletonPtr()->OnNewWeekCome( );	
}


// TODO:��ʱ�޸�
int CSceneLogic::ExecuteSql( int vSessionType, int vParam1, int vParam2, int vPlayerCharID, int vCallBack, SQLTYPE vSqlType, const char* pSQL, ... )
{
	// ����ǿ��ս������ȫ�ֳ������δ˹���
	//if ( IS_DUNGEONSERVER_LINE( mLineID ) == true || IS_GLOBAL_SCENESERVER( mLineID ) == true )
	//{
	//	return 0;
	//}
	
	va_list tArgs;

	char tSqlCommand[ PLAYER_DATALEN ] = { 0 };

	va_start( tArgs, pSQL );
	::vsprintf( tSqlCommand, pSQL, tArgs );
	va_end( tArgs );

	// �����д�ļ�
	//if( vParam1 == SAVE_FILE )
	//{
	//	//���浽�ļ���
	//	Save2File( vSessionType, vPlayerCharID, (const char*)tSqlCommand );
	//	return true;
	//}

	int nSessionID = 0;
	if ( vCallBack & SQL_NEED_CALLBACK )
	{
		CSession* pSession= (CSession*) CSceneObjManager::GetSingletonPtr()->CreateObject( OBJTYPE_SESSION );
		if( pSession == NULL) return false;
		nSessionID = pSession->get_id();
		pSession->assign( nSessionID, vSessionType, vParam1, vParam2 );
	}

	CMessageExecuteSqlRequest msg;
	msg.set_sessionid(nSessionID);
	msg.set_sql(tSqlCommand);
	msg.set_callback( vCallBack & SQL_NEED_CALLBACK ? 1 : 0 );
	if( vCallBack & SQL_LATEST_INC_ID )
		msg.set_latestautoincid(1);

	msg.set_sqltype(vSqlType);
	msg.set_sessiontype( vParam1 );

	CMessage   tMessage;
	CProxyHead tProxyHead;

	tMessage.set_msgpara((uint32_t) &msg);
	pbmsg_sethead(&tMessage, ID_S2S_EXECUTESQL_REQUEST, 0, 0, FE_SCENCESERVER, FE_DATASERVER, CSceneServer::GetSingleton().mThisServerID, 1);
	tProxyHead.set_srcfe( CET_GAMESERVER );
	tProxyHead.set_dstfe( CET_DBSERVER );
	tProxyHead.set_srcid( CSceneServer::GetSingleton().mThisServerID );
	tProxyHead.set_dstid( 1 ); // TODO: ��ʱд�������ݿ������Ŀǰֻ��1̨
	// �� charid ����dbsvrd����ִ���̵߳�key����֤һ��������в�������һ���߳�ִ��
	tProxyHead.set_uin( vPlayerCharID );

	// �����ɫ�ڱ�������ȡ����ID(�����ڵȴ����������)
	CEntityPlayer* tpPlayer = NULL;
	CSceneLogic::PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( vPlayerCharID );
	if ( tFindIter != mPlayerInWait.end( ) )
	{
		tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr( )->GetObject( tFindIter->second );		
	}
	else
	{
		tpPlayer = GetPlayerByCharID( vPlayerCharID );
	}
	if ( tpPlayer != NULL )
	{
		tProxyHead.set_srcgameid( GetWorldID() );
		tProxyHead.set_desgameid( tpPlayer->GetRoleWorldID() );
	}				
	

	BYTE message_buffer[ PLAYER_DATALEN ] = {0};
	int message_length = pbmsg_setmsg<CProxyHead>(tProxyHead, tMessage, (char*)message_buffer, sizeof(message_buffer));      

	if (message_length > 0)        
	{
		int nRet = Send2Data( message_buffer, message_length ) ;
		if( nRet < 0 )
		{
			LOG_ERROR( "default", "[%s:%d] player %d send 2 data failed %d", __FUNCTION__, __LINE__, vPlayerCharID, nRet );
		}
		return nSessionID;
	}
	else                                                                                             
	{                                                                                                 
		LOG_ERROR("default", "pbmsg_setmsg encoding message (%x) error", tMessage.msghead().messageid());
		return nSessionID;
	}               

}

void CSceneLogic::Save2File( int vSessionType, int vPlayerCharID, ::google::protobuf::Message* vpMsg, const char* pKey, std::vector<std::string>& rFirlds, unsigned int nAccountID )
{
	char tCharPath[ 512 ] = { 0 };
	char tCharPath2[ 512 ] = { 0 };
	int tRtn = GetSaveFilePath( vPlayerCharID, tCharPath, sizeof( tCharPath ) );
	if( tRtn != SUCCESS )
	{
		return;
	}
	// дXML
	if ( vSessionType == SESSION_SAVE_PLAYER_BAGGAGE ) // ����ǰ������ ��дxml�ļ�
	{
		//snprintf( tCharPath2, 511, "rm %s/*.xml -rf", tCharPath );
		//system(tCharPath2);
		CMessageSavePlayerItemInfoRequest* tpReqPara = (CMessageSavePlayerItemInfoRequest*)vpMsg;
		for ( int i = 0; i < tpReqPara->itembox_size(); ++i )
		{
			LK_ASSERT( (int)rFirlds.size() > i, continue );
			std::string key_name = rFirlds[i]+std::string(".xml");
			if( ( int )(strlen( tCharPath ) + key_name.length()) >= 512 )
			{
				LOG_ERROR( "default", "Not Enough Path Space %s / %s", tCharPath, key_name.c_str() );
				continue;
			}
			snprintf( tCharPath2, 511, "%s/%s", tCharPath, key_name.c_str() );
			FILE* tpFile = NULL;
			tpFile = fopen( tCharPath2, "w" );
			if( tpFile == NULL )
			{
				LOG_ERROR( "default", "Cannt Get Open File1 %s", tCharPath2 );
				continue;
			}
			const PBItemBox& rBox = tpReqPara->itembox(i);
			CMaxString xmlbuf("");
			protobuf2xml(rBox, xmlbuf, rFirlds[i].c_str(), rBox.GetDescriptor()->name().c_str(), xml_format);
			fputs(xmlbuf.c_str(), tpFile );
			fclose( tpFile );
		}
	}
	else
	{
		snprintf( tCharPath2, 511, "rm %s/%s.* -rf", tCharPath, pKey );
		system(tCharPath2);
		if( ( int )(strlen( tCharPath ) + strlen(pKey)) >= 505 )
		{
			LOG_ERROR( "default", "Not Enough Path2 Space %s / %s", tCharPath, pKey );
			return;
		}
		snprintf( tCharPath2, 511, "%s/%s.xml", tCharPath, pKey );
		FILE* tpFile = NULL;
		tpFile = fopen( tCharPath2, "w" );
		if( tpFile == NULL )
		{
			LOG_ERROR( "default", "Cannt Get Open File2 %s", tCharPath2 );
			return;
		}
		CMaxString xmlbuf("");
		protobuf2xml( *vpMsg, xmlbuf, pKey, vpMsg->GetDescriptor()->name().c_str(), xml_format);
		fputs(xmlbuf.c_str(), tpFile );
		fclose( tpFile );
	}

	// ��������˺�ID
	char tAccFileName[530] = {0};
	snprintf( tAccFileName, 529, "%s/%s", tCharPath, "account.txt");
	FILE* fpSave = fopen( tAccFileName, "w+");
	if ( fpSave == NULL )
	{
		LOG_ERROR("default", "open account file failed");
		return;
	}
	else
	{
		fprintf( fpSave, "%d", nAccountID );
		fclose(fpSave);
	}
	// ���ñ����־
	std::string key_name = "save_flag.txt";
	if( ( int )(strlen( tCharPath ) + key_name.length()) >= 512 )
	{
		LOG_ERROR( "default", "Not Enough Path Space2 %s / %s", tCharPath, key_name.c_str() );
		return ;
	}
	snprintf( tCharPath2, 511, "%s/%s", tCharPath, key_name.c_str() );
	FILE* tpFile = NULL;
	tpFile = fopen( tCharPath2, "w" );
	if( tpFile != NULL ) // �д洢��־�ļ�
	{
		fprintf( tpFile, "0" );
		fclose( tpFile);
	}
}

void CSceneLogic::OnMessageResavePlayer( CMessage* pMsg )
{
	if ( pMsg ==  NULL )
		return;
	CMessageReSavePlayerRequest* tpMsg = ( CMessageReSavePlayerRequest* )pMsg->msgpara( );
	if ( tpMsg ==  NULL )
		return;
	ReSavePlayerFromFile( tpMsg->roleid() );
}

// ���ļ��������� д��DB
int  CSceneLogic::ReSavePlayerFromFile( int vCharID )
{
	char tCharPath[512] = {0};
	char tCharPath2[512] = {0};
	int tRtn = GetSaveFilePath( vCharID, tCharPath, sizeof( tCharPath ) );
	if( tRtn != SUCCESS )
	{
		return -1;
	}

	// ��鱾��������û����������Լ��ǲ�����Ҫ���̵�״̬
	std::string key_name = "save_flag.txt";
	if( ( int )(strlen( tCharPath ) + key_name.length()) >= 512 )
	{
		LOG_ERROR( "default", "[RESAVE]Not Enough Path Space %s / %s", tCharPath, key_name.c_str() );
		return -2;
	}
	snprintf( tCharPath2, 511, "%s/%s", tCharPath, key_name.c_str() );
	FILE* tpFile = NULL;
	int nFlag = 0;

	tpFile = fopen( tCharPath2, "r" );
	if( tpFile != NULL ) // �д洢��־�ļ�
	{
		fscanf( tpFile, "%x", &nFlag );
		fclose( tpFile);
	}
	else // û�д��̼�¼ ����
	{
		LOG_ERROR("default", "[RESAVE]player %d not here", vCharID );
		return 0;
	}

	// ��������˺�ID
	int  nAccountID = 0;
	char tAccFileName[530] = {0};
	snprintf( tAccFileName, 529, "%s/%s", tCharPath, "account.txt");
	FILE* fpAcc = fopen( tAccFileName, "r");
	if ( fpAcc == NULL )
	{
		LOG_ERROR("default", "[RESAVE]open account file failed");
		return -1;
	}
	else
	{
		fscanf( fpAcc, "%d", &nAccountID );
		fclose(fpAcc);
	}

	if ( nAccountID == 0 )
	{
		LOG_ERROR("default", "[RESAVE]nAccountID=0 ? roleid=%d", vCharID );
		return -1;
	}

	if ( nFlag == SAVE_ITEM_FULL_FLAG ) // �������
	{
		int nMapID = 0;
		int nLineID = 0;
		int nPosX = 0;
		int nPosY = 0;
		GetPlayerPosInfoFromXml( vCharID, nLineID, nMapID, nPosX, nPosY );
		if ( nMapID == 0 || nLineID == 0 )
		{
			LOG_ERROR("default", "[RESAVE] nMapID=%d  nLineID=%d  charid=%d", nMapID, nLineID, vCharID );
			return -1;
		}
		CMessageReSavePlayerResponse msg;
		msg.set_roleid(vCharID);
		msg.set_result(0);
		msg.set_accountid(nAccountID);
		msg.set_lineid(nLineID);
		msg.set_mapid( nMapID );
		msg.set_posx( nPosX );
		msg.set_posy( nPosY );

		CMessage tMessage;
		tMessage.set_msgpara((uint32_t) &msg);
		pbmsg_sethead(&tMessage, ID_S2G_RESPONSE_RESAVEPLAYER, 0, 0, 0, 0, 0, 0);
		CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );
		return 0;
	}

	// ���������ļ����µ������ļ�....
	DIR *dir;
	struct dirent *dp;
	if ((dir = opendir (tCharPath)) == NULL) 
	{
		perror(strerror(errno));
		return -2;
	}

	while((dp = readdir (dir)) != NULL)
	{
		if (dp->d_name[0] != '.')
		{
			std::string fn = std::string(dp->d_name);
			std::string ext = fn.substr( fn.length() - 4 );
			std::string main_fn = fn.substr( 0, fn.length() - 4 );
			char tmpname[530] = {0};
			snprintf( tmpname, 529, "%s/%s", tCharPath, fn.c_str());
			if ( ext == std::string(".xml") )
			{
				// xml file
				ReSavePlayerInfoFromXml(tmpname, vCharID, nAccountID );
			}
		}
	}

	closedir(dir); dir = NULL;
	return 0;
}

int  CSceneLogic::ReSavePlayerInfoFromXml( const char* xmlfile, int nCharID, unsigned int nAccountID )
{
	TiXmlDocument xmldoc;
	xmldoc.LoadFile( xmlfile );

	TiXmlElement* tpRoot= xmldoc.FirstChildElement();
	if (tpRoot == NULL)
	{
		LOG_ERROR( "default", "[RESAVE]load role_detail from xmlfile(%s) failure.", xmlfile);
		return -1;
	}

	int nPosIndex = -1;
	int nSessionType = -1;
	std::string fn = std::string(xmlfile);
	int npos = fn.rfind('/');
	std::string main_fn = fn.substr( npos+1, fn.length()-npos-5 );
	if ( main_fn == std::string("role_equipment") )
	{
		nPosIndex = PACKAGE_EQUIPMENT;
		nSessionType = SESSION_SAVE_PLAYER_BAGGAGE;
	}
	else if ( main_fn == std::string("role_package") )
	{
		nPosIndex = PACKAGE_BAGGAGE;
		nSessionType = SESSION_SAVE_PLAYER_BAGGAGE;
	}
	else if ( main_fn == std::string("role_storage") )
	{
		nPosIndex = PACKAGE_STORAGE;
		nSessionType = SESSION_SAVE_PLAYER_BAGGAGE;
	}
	else if ( main_fn == std::string("role_task_package") )
	{
		nPosIndex = PACKAGE_TASK;
		nSessionType = SESSION_SAVE_PLAYER_BAGGAGE;
	}
	else if ( main_fn == std::string("saveplayer_charprofile") )
	{
		nSessionType = saveplayer_charprofile;
	}
	else if ( main_fn == std::string("saveplayer_property_all") )
	{
		nSessionType = saveplayer_property_all;
	}
	else
	{
		LOG_ERROR("default", "[RESAVE]error xml file while resave:%s", xmlfile );
		return -1;
	}

	CSession* pSession= (CSession*) CSceneObjManager::GetSingletonPtr()->CreateObject( OBJTYPE_SESSION );
	LK_ASSERT( pSession != NULL, return -1 ); 
	pSession->SetSessionType( nSessionType );
	pSession->SetParam1( RESAVE_FROMFILE );
	pSession->SetParam2( nCharID );
	pSession->SetTimer( CWTimer(30000) ); 

	if (nSessionType == SESSION_SAVE_PLAYER_BAGGAGE)
	{
		CMessage tMessage;
		CMessageSavePlayerItemInfoRequest tReqPara;

		tMessage.mutable_msghead()->set_messageid( ID_S2D_SAVEPLAYERITEMINFO_REQUEST );
		tMessage.set_msgpara( (unsigned int)(&tReqPara) );

		tReqPara.set_accountid( nAccountID );
		tReqPara.set_charid( nCharID );
		tReqPara.set_sessionid( pSession->get_id() );

		pSession->SetParam( 3,nPosIndex); // �ӵ�3��������ʼ����
		tReqPara.add_packageidx( nPosIndex );
		PBItemBox* pItemBox = tReqPara.add_itembox();
		LK_ASSERT( pItemBox != NULL, return -1 );
		if ( 0 != xml2protobuf( tpRoot, pItemBox, NULL ) )
		{
			LOG_ERROR("default", "[RESAVE]error in xml2protobuf! file=%s", xmlfile );
			return -10;
		}
		if( SceneServer::CSceneLogic::GetSingletonPtr()->Send2Data( nAccountID, tMessage ) < 0 )
		{
			LOG_ERROR( "default", "[RESAVE][%s:%d] player acc %d send messag to data failed.", __FUNCTION__, __LINE__, nAccountID );
			return -1;
		}
	}
	else
	{
		CMessageSavePlayerRequest tSaveRequest;
		if ( 0 != xml2protobuf( tpRoot, &tSaveRequest, NULL ) )
		{
			LOG_ERROR("default", "[RESAVE]error in xml2protobuf! file=%s", xmlfile );
			return -10;
		}
	
		// У��detailid��roleid
		if ( (int)tSaveRequest.detailid() != (int)nAccountID % 16 || (int)tSaveRequest.roleid() != (int)nCharID )
		{
			LOG_ERROR("default", "[RESAVE]tSaveRequest parse check failed! %d != %d  %d != %d", tSaveRequest.detailid() , nAccountID % 16 , tSaveRequest.roleid() , nCharID );
			return -3;
		}
		tSaveRequest.set_sessionid(pSession->get_id());
		SendMsg2Data( &tSaveRequest, nAccountID, ID_S2D_SAVEPLAYER_REQUEST );
	}

	return 0;
}

// ��xml�����ҵ�ͼ����ID
void CSceneLogic::GetPlayerPosInfoFromXml( int vCharID, int& rLineID, int& rMapID, int& rPosX, int& rPosY )
{
	char tCharPath[512] = {0};
	int tRtn = GetSaveFilePath( vCharID, tCharPath, sizeof( tCharPath ) );
	if( tRtn != SUCCESS )
	{
		return ;
	}
	char tmpname[530] = {0};
	snprintf( tmpname, 529, "%s/saveplayer_charprofile.xml", tCharPath);

	TiXmlDocument xmldoc;
	xmldoc.LoadFile( tmpname );
	TiXmlElement* tpRoot= xmldoc.FirstChildElement();
	if (tpRoot == NULL)
	{
		LOG_ERROR( "default", "[RESAVE]load role_detail from xmlfile(%s) failure.", tmpname);
		return ;
	}
	CMessageSavePlayerRequest tSaveRequest;
	if ( 0 != xml2protobuf( tpRoot, &tSaveRequest, NULL ) )
	{
		LOG_ERROR("default", "[RESAVE]error in xml2protobuf! file=%s", tmpname );
		return ;
	}
	CMessagePlayerInfo inf = tSaveRequest.info();
	rLineID = inf.line_id();
	rMapID  = inf.map_id();
	rPosX   = inf.pos_x();
	rPosY   = inf.pos_y();
}

// ���±���ɹ�
int CSceneLogic::OnResaveSuccess( int nCharID, int nResaveFlag )
{
	char tCharPath[512] = {0};
	char tCharPath2[512] = {0};
	int tRtn = GetSaveFilePath( nCharID, tCharPath, sizeof( tCharPath ) );
	if ( tRtn != SUCCESS )
	{
		return -1;
	}

	std::string key_name = "save_flag.txt";
	if( ( int )(strlen( tCharPath ) + key_name.length()) >= 512 )
	{
		LOG_ERROR( "default", "[RESAVE]Not Enough Path Space %s / %s", tCharPath, key_name.c_str() );
		return -2;
	}
	snprintf( tCharPath2, 511, "%s/%s", tCharPath, key_name.c_str() );
	FILE* tpFile = NULL;
	int nFlag = 0;

	tpFile = fopen( tCharPath2, "r" );
	if( tpFile != NULL ) // �д洢��־�ļ�
	{
		fscanf( tpFile, "%x", &nFlag );
		fclose( tpFile);
	}

	nFlag |= (1<<nResaveFlag);
	tpFile = fopen( tCharPath2, "w" );
	if ( tpFile == NULL )
	{
		LOG_ERROR( "default", "[RESAVE]Cannt Get Open File3 %s", tCharPath2 );
		return -3;
	}
	else
	{
		fprintf(tpFile, "%x", nFlag );
		fclose(tpFile);
	}

	if ( nFlag == SAVE_ITEM_FULL_FLAG ) // �������
	{
		int  nAccountID = 0;
		char tAccFileName[530] = {0};
		snprintf( tAccFileName, 529, "%s/%s", tCharPath, "account.txt");
		FILE* fpAcc = fopen( tAccFileName, "r");
		if ( fpAcc == NULL )
		{
			LOG_ERROR("default", "[RESAVE]open account file failed");
			return -1;
		}
		else
		{
			fscanf( fpAcc, "%d", &nAccountID );
			fclose(fpAcc);
		}

		if ( nAccountID == 0 )
		{
			LOG_ERROR("default", "[RESAVE]nAccountID=0 ? roleid=%d", nCharID );
			return -1;
		}

		// �ظ���Ϣ������
		int nMapID = 0;
		int nLineID = 0;
		int nPosX = 0;
		int nPosY = 0;
		GetPlayerPosInfoFromXml( nCharID, nLineID, nMapID, nPosX, nPosY );
		if ( nMapID == 0 || nLineID == 0 )
		{
			LOG_ERROR("default", "[RESAVE] nMapID=%d  nLineID=%d  charid=%d", nMapID, nLineID, nCharID );
			return -1;
		}
		CMessageReSavePlayerResponse msg;
		msg.set_roleid(nCharID);
		msg.set_result(0);
		msg.set_accountid(nAccountID);
		msg.set_lineid(nLineID);
		msg.set_mapid( nMapID );
		msg.set_posx( nPosX );
		msg.set_posy( nPosY );

		CMessage tMessage;
		tMessage.set_msgpara((uint32_t) &msg);
		pbmsg_sethead(&tMessage, ID_S2G_RESPONSE_RESAVEPLAYER, 0, 0, 0, 0, 0, 0);
		CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );
	}
	return 0;
}

int CSceneLogic::GetSaveFilePath( int vPlayerCharID, char* pPath, int vPathLen )
{
	const char* tPath = CSceneServer::GetSingletonPtr( )->mSavePath.c_str( );
	const char* tBack = CSceneServer::GetSingletonPtr( )->mBakPath.c_str( );

	//CEntityPlayer* tpEntity = ( CEntityPlayer* )CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( vPlayerCharID );
	//LK_ASSERT_STR( tpEntity != NULL, return ERR_INVALID_PARAMETER, "Cannt Get Player From CharID %d", vPlayerCharID );

	char tCharPath[ 512 ] = { 0 };
	//	char tCharPathBak[ 521 ] = { 0 };

	LK_ASSERT( tPath != NULL, return ERR_UNKNOWN );
	LK_ASSERT( tBack != NULL, return ERR_UNKNOWN );

	LK_ASSERT( tPath[ 0 ] != '\0', return ERR_UNKNOWN );
	LK_ASSERT( tBack[ 0 ] != '\0', return ERR_UNKNOWN );

	int tRtn = mkdir( tPath, 0777 );	
	if( tRtn == -1 )
	{
		if( errno != EEXIST )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ] Cannt Create Directory %s", __LK_FILE__, __LINE__, __FUNCTION__,
					tPath );
			return ERR_UNKNOWN;
		}
	}

	snprintf( tCharPath, sizeof( tCharPath ), "%s%d", tPath, vPlayerCharID );
	tRtn = mkdir( tCharPath, 0777 );
	if( tRtn == -1 )
	{
		if( errno != EEXIST )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ] Cannt Create Directory %s", __LK_FILE__, __LINE__, __FUNCTION__,
					tCharPath );
			return ERR_UNKNOWN;
		}
		else
		{
			tRtn = mkdir( tBack, 0777 );
			if( tRtn == -1 )
			{
				if( errno != EEXIST )
				{
					LOG_ERROR( "default", "[ %s : %d ][ %s ] Cannt Create Directory %s", __LK_FILE__, __LINE__, 
							__FUNCTION__, tBack );
					return ERR_UNKNOWN;
				}
			}
		}
	}

	snprintf( pPath, vPathLen, "%s%d", tPath, vPlayerCharID );	

	return SUCCESS;
}

// ��������
int CSceneLogic::CreateMap( unsigned short vLineID, unsigned short vMapID, unsigned short vIndex, const char* pTplName )
{
	CMapObject* tpMapObj = CMapObjManager::GetSingletonPtr( )->CreateMap( vLineID, vMapID, vIndex, pTplName );
	if( tpMapObj != NULL )
	{
		return SUCCESS;
	}

	return ERR_UNKNOWN;
}

void CSceneLogic::CreateEntity( CEntity* pEntity, CCreator* pCreator, bool vFirst )
{
	LK_ASSERT( pEntity != NULL, return );

	// ������������
	if ( pEntity->IsPlayer() )
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*) pEntity;
		tpPlayer->SetCommHandle( tpPlayer->GetClientInfo( )->mSockIndex );

		pEntity->GetProperty()->SetPropertyTempID( tpPlayer->GetMetier() );
			
		// ����������
		
		std::pair<PLAYERID_MAP::iterator, bool> vRet4CharID;
		vRet4CharID = mPlayerContainer.insert( PLAYERID_MAP::value_type( tpPlayer->GetCharID(), tpPlayer->get_id() ) );
		if (vRet4CharID.second == false)
		{
			LOG_ERROR("default", "FATAL ERROR, CharID(%d) has two Player Object(prev=%d, sec=%d)",
				tpPlayer->GetCharID(), vRet4CharID.first->second, tpPlayer->get_id());
		}

		std::pair<PLAYERID_MAP::iterator, bool> vRet4Comm;
		vRet4Comm = mPlayerCommIndex.insert( PLAYERID_MAP::value_type( tpPlayer->GetClientInfo( )->mSockIndex, tpPlayer->get_id() ) );
		if (vRet4Comm.second == false)
		{
			LOG_ERROR("default", "FATAL ERROR, CharID(%d) has two Player Object(prev=%d, sec=%d)",
				tpPlayer->GetCharID(), vRet4Comm.first->second, tpPlayer->get_id());
		}else
		{
			LOG_NOTICE( "pro", "Insert %d to comm map ", tpPlayer->GetClientInfo( )->mSockIndex);
		}

		std::pair<PLAYERNAME_MAP::iterator, bool> vRet4Name;
		vRet4Name = mPlayerNameIndex.insert( PLAYERNAME_MAP::value_type( tpPlayer->GetCharName(), tpPlayer->get_id() ) );
		if (vRet4Name.second == false)
		{
			LOG_ERROR("default", "FATAL ERROR, CharID(%d) has two Player Object(prev=%d, sec=%d)", 
				tpPlayer->GetCharID(), vRet4Name.first->second, tpPlayer->get_id());
		}

		// ÿ�ռ���ˢ��
		tpPlayer->DailyCountRefresh( CSceneLogic::GetSingletonPtr()->GetCurrentDay() );


		// �ǿ��������Ϸ�Ÿ�����ҷ�֪ͨ

		// ֪ͨ�������ҽ���
		NoticeApexProxy_UserLogin( tpPlayer->GetCharID() );		
	}
	
	// �����NPC����
	else if ( pEntity->IsNpc() )
	{
		CEntityNpc* tpNpc = ( CEntityNpc* )pEntity;
		pEntity->GetProperty( )->SetPropertyTempID( tpNpc->GetNpcID( ) );
		CPropertyCharacter* pPro = (CPropertyCharacter*)pEntity->GetProperty( );
		LK_ASSERT( pPro, return );

		int tLevel = 0;
		int tSpeed = 0;

		if ( pEntity->IsOgre( ) || pEntity->IsFunNpc() )
		{						
			CTemplateOgre *tplOgre = (CTemplateOgre *)CDataStatic::SearchTpl( tpNpc->GetNpcID() );						
			if ( tplOgre != NULL )
			{
				if ( tplOgre->mDisplayLevel == CTemplateOgre::OGRESHOW_BOSS )
				{															
					//COgreCreator *tpOgreCreator = ( COgreCreator * )pCreator;					
					int tIntParam[ 4 ] = { 0 };
					tIntParam[ 0 ] = tpNpc->GetNpcID();
					tIntParam[ 1 ] = tpNpc->GetMapID();
					tIntParam[ 2 ] = tpNpc->GetPosX();
					tIntParam[ 3 ] = tpNpc->GetPosY();
					CPropertyModule::GetSingletonPtr()->SendEventNotify( NOTICE_REFRESHBOSS, tpNpc->GetLineID(), tIntParam, ARRAY_CNT(tIntParam), NULL, NULL );
				}				
			}
			CTemplateOgre *tempNpc = (CTemplateOgre*)CDataStatic::SearchTpl( tpNpc->GetNpcID( ) );
			LK_ASSERT_STR( tempNpc, return, "NpcID %d", tpNpc->GetNpcID( ) );
			tLevel = tempNpc->mLevel;
			tSpeed = tempNpc->mRunSpeed;
			// ��Ӣд��־
			if ( tempNpc->mDisplayLevel == CTemplateOgre::OGRESHOW_VIP )
			{
				LOG_INFO( "pro", "Create Stone Ogre %d", pCreator->GetIndex() );
			}			
		}
		else if ( pEntity->IsPet( ) )
		{
			CEntityPet *pPet = (CEntityPet*)tpNpc;
			CEntityPlayer *pOwner = (CEntityPlayer*)CSceneLogic::GetSingletonPtr()->GetEntity( pPet->GetOwnerID( ) );
			if ( pOwner != NULL )
			{
				tLevel = pOwner->GetLevel( );
			}
			CTemplateSummonBeast *tplPet = (CTemplateSummonBeast*)CDataStatic::SearchTpl( pPet->GetNpcID( ) );
			if ( tplPet != NULL )
			{
				tSpeed = tplPet->mPetData[ pPet->GetCurLevel( ) ].mSpeed;
			}
		}
		else if( pEntity->IsCollect( ) )
		{
			tLevel = 0;
			tSpeed = 0;
		}
		else if ( pEntity->IsFunNpc( ) )
		{
			CTemplateNpc *tempNpc = (CTemplateNpc*)CDataStatic::SearchTpl( tpNpc->GetNpcID( ) );
			LK_ASSERT_STR( tempNpc, return, "NpcID %d", tpNpc->GetNpcID( ) );
			tLevel = tempNpc->mLevel;
			tSpeed = tempNpc->mRunSpeed;
		}	

		pPro->SetLevel( tLevel );
		pPro->SetTranChangeLevel( tLevel );
		pPro->SetCurSpeed( tSpeed );

		mNpcContainer.insert( NPCID_MAP::value_type( pEntity->GetEntityID( ), pEntity->get_id() ) );
	}

	else if( pEntity->IsDrop() )
	{
		CEntityDrop* tpDrop = ( CEntityDrop* )pEntity;
		pEntity->GetProperty( )->SetPropertyTempID( tpDrop->GetNpcID( ) );
		mNpcContainer.insert( NPCID_MAP::value_type( pEntity->GetEntityID( ), pEntity->get_id() ) );
	}
	else if( pEntity->IsPedal() )
	{
		CEntityPedal* tpPedal = ( CEntityPedal* )pEntity;
		pEntity->GetProperty( )->SetPropertyTempID( tpPedal->GetNpcID( ) );
		mNpcContainer.insert( NPCID_MAP::value_type( pEntity->GetEntityID( ), pEntity->get_id() ) );
	}
	else if( pEntity->IsCollect() )
	{
		CEntityCollect* tpCollect = ( CEntityCollect* )pEntity;
		pEntity->GetProperty( )->SetPropertyTempID( tpCollect->GetNpcID( ) );
		mNpcContainer.insert( NPCID_MAP::value_type( pEntity->GetEntityID( ), pEntity->get_id() ) );
	}
	else if (  pEntity->IsRedStone() )
	{
		CEntityRedStone * tpRedStone = ( CEntityRedStone * )pEntity;	
		tpRedStone->SetStatus( REDSTONE_STATUS_PROTECT );
		mNpcContainer.insert( NPCID_MAP::value_type( pEntity->GetEntityID() , pEntity->get_id() ) );
	}
	else if ( pEntity->IsGhost() )
	{
		//CEntityGhost * tpGhost = (CEntityGhost *) pEntity;
		mNpcContainer.insert( NPCID_MAP::value_type( pEntity->GetEntityID() , pEntity->get_id() ) );
	}
	
	// ֪ͨ��ģ��ʵ�彨����
	CModuleManager::GetSingleton( ).CreateEntity( pEntity, pCreator, vFirst );

	// ��������˳�ʼˢbuff,�������entity��ȫ��������֮����buff.��Ϊbuff�͵�ͼ����ص�
	if ( (pCreator != NULL) && (pCreator->GetCreatorType() == ENTITYTYPE_OGRE) )
	{
		COgreCreator *pOgreCreator = (COgreCreator*)pCreator;
		CTemplateBuff *tplBuff = (CTemplateBuff*)CDataStatic::SearchTpl( pOgreCreator->mInitBuffID );
		((CEntityNpc*)pEntity)->EntityInsertBuff( (CEntityNpc*)pEntity, tplBuff );		
		CProperty *tpProperty = pEntity->GetProperty();
		//LogEventGetBuffByMAP((CEntityPlayer*)(pEntity),pOgreCreator->mInitBuffID,tplBuff->mLastTime,pEntity->GetMapID()) ;
		CTemplateOgre *tplOgre = (CTemplateOgre *)CDataStatic::SearchTpl(tpProperty->GetPropertyTempID() );								

		// ���������һ�����
		CCreator* tpCreator = CCreatorManager::GetSingletonPtr()->GetCreator( pOgreCreator->mMaxEnmity );
		if ( tpCreator != NULL )
		{
			CEntityCharacter *tpDesEntity = (CEntityCharacter*)CSceneObjManager::GetSingletonPtr( )->GetObject( tpCreator->mHasOgre );
			if ( tpDesEntity != NULL && tplOgre != NULL )
			{		
				CNpcModule::GetSingleton().OnAttacked( tpDesEntity,( CEntityNpc* )pEntity, tplOgre->mEnmityTime );
			}
		}
	}


	if( pEntity->IsPlayer() )
	{
		CPropertyPlayer* tpProPlayer = (CPropertyPlayer*)pEntity->GetProperty();
		
		// ����ǿ��ˢ��ÿ�պ�ÿ��ˢ��ʱ�䣬 ��ģ���OnCreatEntity����ֱ������ж��Ƿ���Ҫˢ������
		unsigned int tNow = time(0);
		tpProPlayer->SetLastDaylyDisposTime( tNow );
		tpProPlayer->SetLastWeeklyDisposTime( tNow );

		CEntityPlayer* pPlayer = (CEntityPlayer*)(pEntity);

		// �����������ߵģ��´�����ʱ(���������֮���)Ҫ�ر����߾�
		if ( vFirst &&pPlayer->GetNationality() != 0 && 
			pPlayer->GetNationality() != pPlayer->GetLineID() &&
			IS_REPETION_LINE_ID(pPlayer->GetLineID()) == false &&
			IS_NEUTRAL_LINE_ID(pPlayer->GetLineID()) == false && 
			IS_BATTLE_LINE_ID(pPlayer->GetLineID()) == false &&
			IS_GLOBAL_SCENESERVER(pPlayer->GetLineID()) == false )
		{
			// TODO: ����ڻ���ɽ�����ܴ�, ������Ҵ���ԭ��
			CTemplateBeginner* tpBeginner = (CTemplateBeginner*) CDataStatic::GetTemp( TEMP_BEGINNER );
			if ( tpBeginner != NULL )
			{
				if( pPlayer->GetMapID() != tpBeginner->mMapID )
				{
					CMapModule::GetSingletonPtr()->Teleport( pPlayer->GetNationality(), 
						CPropertyModule::GetSingleton().mBorderMapID,
						CPropertyModule::GetSingleton().mBorderPosX,
						CPropertyModule::GetSingleton().mBorderPosY,
						pEntity);				
				}
			}
		}

		// ������״ν��룬ˢһ���ٻ��ޣ� ����GetPetID���ص���petcreator id)
		CPetCreator* pPetCreator = (CPetCreator*) CSceneObjManager::GetSingletonPtr()->GetObject( pPlayer->GetPetCreatorID() ) ;
		if ( pPetCreator != NULL )
		{
			unsigned int tPetEntityID = 0;
			bool tbCreatSuc = CMapModule::GetSingleton( ).CreateNpc(
				pPlayer->GetLineID( ),
				pPlayer->GetMapID( ),
				pPlayer->GetMapIndex( ),
				pPetCreator,
				tPetEntityID );

			if( tbCreatSuc == true )
			{
				pPlayer->SetPetID( tPetEntityID );
			}

			pPlayer->SetPetCreatorID( INVALID_OBJ_ID );

			// ����pet creator
			CSceneObjManager::GetSingletonPtr()->DestroyObject( pPetCreator->get_id() );
		}
	
	}

}

CEntity* CSceneLogic::GetEntity( int vEntityID )
{
	return ( CEntity* )CSceneObjManager::GetSingletonPtr()->GetObject( vEntityID );;
}



int CSceneLogic::OnMessageLoadPlayerProperty( CMessage* pMessage )
{
	CMessageLoadPlayerPropertyResponse* pResPara = (CMessageLoadPlayerPropertyResponse*)pMessage->msgpara();

	int nCharID = pResPara->roleid();
	int nSessionID = pResPara->sessionid();

	LOG_DEBUG( "default", "player %d load property return, session %d ", nCharID, nSessionID );

	CSession* pSession = (CSession*)CSceneObjManager::GetSingletonPtr()->GetObject( nSessionID );
	if( pSession == NULL )
	{
		LOG_ERROR( "[%s:%d] can't find session %d", __FUNCTION__ , __LINE__, nSessionID );
		return 0;
	}


	CSceneObjManager::GetSingletonPtr()->DestroyObject( nSessionID );

	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( nCharID );
	if ( tFindIter == mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-2", 
			__LK_FILE__, __LINE__, nCharID );
		return -1;
	}

	CEntityPlayer* pPlayer = (CEntityPlayer*) CSceneLogic::GetSingletonPtr()->GetEntity( tFindIter->second );
	if(  pPlayer == NULL )
	{
		LOG_ERROR( "default", "[%s:%d] can't find entity %d", __FUNCTION__, __LINE__, tFindIter->second );
		return -1;
	}

#ifdef _DEBUG_
	LOG_DEBUG( "pro", "player %s:%d load iteminfo %s",  pPlayer->GetCharNameShow(), pPlayer->GetCharID(), pResPara->ShortDebugString().c_str());
#endif

	// ���뱣֤��һ������ݼ�����ɲ����½���
	if( (pPlayer->GetLoadState() & LSSTATE_CHARPROFILE) == 0 )
	{
		LOG_ERROR( "default", "player %s's charprofile is not ready ", pPlayer->GetCharNameShow() );
		return -1;
	}

	if( pResPara->resultcode( ) != SUCCESS )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ] Cannt Get Player( %d ) DB Data", __LK_FILE__, __LINE__, __FUNCTION__,
			pPlayer->GetCharID( ) );
		return pResPara->resultcode( );
	} 

	if( pResPara->has_property( ) == false )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ] Get Player( %d ) DB Data Msg Err", __LK_FILE__, __LINE__, __FUNCTION__,
			pPlayer->GetCharID( ) );
		return pResPara->resultcode( );

	}

	CPropertyPlayer* tpProperty = (CPropertyPlayer*)pPlayer->GetProperty( );
	CMessagePlayerProperty* tpLoad = pResPara->mutable_property( );

	// �ж��Ƿ����º�( �´�����ɫ��blob���� )
	if ( pPlayer->IsNewCharacter() == false )
	{
		tpProperty->SetCurHP( tpLoad->role_hp( ) );
		tpProperty->SetCurMP( tpLoad->role_mp( ) );
		tpProperty->SetCurAP( tpLoad->role_ap( ) );

		tpProperty->CreateBasicInfoFromTlv( tpLoad->mutable_role_basic( ) );
		tpProperty->CreateBuffListFromTlv2( tpLoad->mutable_role_buff( ) );
		tpProperty->GetSkillList( ).CreateFromTlv2( tpLoad->mutable_role_skill( ) );
		tpProperty->CreatePvPBlobInfoFromTlv( tpLoad->mutable_role_pvp( ) );
		tpProperty->CreateCDGroupFromTlv( tpLoad->mutable_role_cdgroup( ) );
		tpProperty->CreateActivityInfoFromTlv( tpLoad->mutable_role_activity( ) );

		tpProperty->CreateTitleInfoFromTlv( tpLoad->mutable_role_title( ) );
		tpProperty->CreateTalentInfoFromTlv( tpLoad->mutable_role_talent( ) );
		tpProperty->CreateMWInfoFromTlv( tpLoad->mutable_role_mw( ) );
		tpProperty->GetPlayerLifeSkill()->SetFromPB( *tpLoad->mutable_role_lifeskill( ) );
		tpProperty->CreateStatisticFromTlv( tpLoad->mutable_role_statistic( ) );
		tpProperty->CreateMonsterInfoFromTlv( tpLoad->mutable_role_monster_record( ) );
		tpProperty->CreateTelePosFromTlv( tpLoad->mutable_role_tele_pos( ) );
		tpProperty->GetWizard().CreateFromTlv( tpLoad->mutable_role_wizard( ) );
		tpProperty->CreateRoleClientInfoFromTlv( tpLoad->mutable_role_client( ) );
		tpProperty->CreateMatrixInfoFromTlv( tpLoad->mutable_role_matrix( ) );
		tpProperty->GetExpTimeInfo()->SetFromPB( *tpLoad->mutable_role_exptimeinfo() );
		tpProperty->GetTreasureBowlInfo()->SetFromPB( *tpLoad->mutable_role_treasurebowl() );
		tpProperty->GetSpiritInfo().SetFromPB(*(tpLoad->mutable_role_spiritinfo()));

		CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr( )->CreateObject( OBJTYPE_TASKLIST );	
		if ( pList == NULL ) // û��Դ��
		{
			LOG_ERROR("TASK", "not enough memroy for tasklist, charid=%d", pPlayer->GetCharID() );
			return -1;
		}

		CTaskLuaInterface::Set( pPlayer, pList );
		pList->CreateFromTlv2( tpLoad->mutable_role_task( ) );	// ��TLVBuffer�������

	
		pPlayer->SetTaskToken(pList->get_id());
		pList->SetOwnerEntityID(pPlayer->GetEntityID());

		CFriendItem friend_item;
		friend_item.CreateFromTlv2( tpLoad->mutable_role_friend( ) );			// ��TLVBuffer�������
		CFriendModule::GetSingleton().InsertFriendData( pPlayer->GetCharID(), friend_item );

		tpProperty->GetRepetion( )->PB2Repetion( tpLoad->mutable_role_repetion( ), pPlayer );
		tpProperty->GetGuideData()->CreateFromPB(tpLoad->mutable_role_guide());
		tpProperty->CreateCharmInfoFromTlv( tpLoad->mutable_role_charm() );
		tpProperty->CreateTimesInfoFromTlv( tpLoad->mutable_role_times() );
	}
	else
	{
		CFriendItem friend_item;
		CPropertyModule::GetSingletonPtr( )->SetDefaultValue( pPlayer );
		CFriendModule::GetSingleton().InsertFriendData( pPlayer->GetCharID(), friend_item );

	}

	pPlayer->SetLoadState( pPlayer->GetLoadState( ) | LSSTATE_PROPERTY );	
	pPlayer->SetLoadState( pPlayer->GetLoadState( ) | LSSTATE_TASK );
	pPlayer->SetLoadState( pPlayer->GetLoadState( ) | LSSTATE_FRIEND );
	pPlayer->SetLoadState( pPlayer->GetLoadState( ) | LSSTATE_REPETION );

	OnLoadPlayer_Final( pPlayer, pPlayer->GetCharID(), 0 );

	return 0;
}

int CSceneLogic::OnMessageSaveItemInfoToDBResponse( CMessage* pMessage )
{	
	CMessageSavePlayerItemInfoResponse* pResPara = (CMessageSavePlayerItemInfoResponse*)pMessage->msgpara();

	int nCharID = pResPara->charid();
	int nSessionID = pResPara->sessionid();
	int nErrorCode = pResPara->errcode();

	LOG_DEBUG( "default", "player %d save iteminfo return, session %d ", nCharID, nSessionID );

	CSession* pSession = (CSession*)CSceneObjManager::GetSingletonPtr()->GetObject( nSessionID );
	if( pSession == NULL )
	{
		LOG_ERROR( "[%s:%d] can't find session %d", __FUNCTION__ , __LINE__, nSessionID );
		return 0;
	}

	int nPlayerID = pSession->GetParam2();
	int nSaveCode = pSession->GetParam1();// TODO ������ˡ�������session�Ǹ�һ��

	CSceneObjManager::GetSingletonPtr()->DestroyObject( nSessionID );

	// ��������±��� ���⴦�� ��ʱû��EntityPlayer!
	if ( nSaveCode == RESAVE_FROMFILE )
	{
		if( pResPara->errcode( ) == CMessageSavePlayerItemInfoResponse::SUCCES ) // ����ɹ�
		{
			for ( int i =0; i < pResPara->packageidx_size(); ++i )
				OnResaveSuccess( nPlayerID, pResPara->packageidx(i) ); // ע�� ��charid
		}
		return 0;
	}

	CEntityPlayer* pPlayer = (CEntityPlayer*) CSceneLogic::GetSingletonPtr()->GetEntity( nPlayerID );
	if(  pPlayer == NULL )
	{
		LOG_ERROR( "default", "[%s:%d] can't find entity %d", __FUNCTION__, __LINE__, nPlayerID );
		return -1;
	}

	if( pResPara->errcode( ) != CMessageSavePlayerItemInfoResponse::SUCCES )
	{
		LOG_ERROR( "default", "[ %s : %d ] Save Item Fail, %d, %d", 
				 __FUNCTION__, __LINE__, pResPara->errcode( ), pResPara->packageidx_size() );

		SavePlayer( pPlayer, SAVE_FILE);
		return -1;
	}

	// ����װ���������������
	if(  pResPara->packageidx_size() == 3 )
	{
		LOG_DEBUG( "pro", "saveplayer_baggage session callback, now savestate is %04x", pPlayer->GetSaveState( ) );	
		pPlayer->SetSaveState( pPlayer->GetSaveState( ) | LSSTATE_BAGGAGE );
	}
	else if( pResPara->packageidx_size() == 1 )// ����ֿ�
	{
		LOG_DEBUG( "pro", "saveplayer_storage session callback, now savestate is %04x", pPlayer->GetSaveState( ) );
		pPlayer->SetSaveState( pPlayer->GetSaveState( ) | LSSTATE_STORAGE );
	}
	else
	{
		LOG_ERROR( "pro", "[%s:%d] no such pkgidx ", __FUNCTION__, __LINE__);
	}

	// TODO: ����Ҫ��һ��������ת��, �ӿ��ڲ�0��ʾʧ��
	OnSavePlayer( nSaveCode, pPlayer->GetEntityID(), nErrorCode == CMessageSavePlayerItemInfoResponse::SUCCES ? 1 : 0 );

	return 0;
}

void CSceneLogic::OnSavePlayer( int nSaveCode, int nEntityPlayerID, int nResultCode )
{
	CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( nEntityPlayerID );
	if ( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "[%s:%d] save player fail, playerid %d", __FUNCTION__, __LINE__, nEntityPlayerID );
		return;
	}

	// Save Error
	if( nResultCode == 0 )
	{
		LOG_FATAL( "default", "OnSavePlayer for [%s][%d] failed, so wirte sql to local file", 
			tpPlayer->GetCharNameShow(), tpPlayer->GetCharID() ); 

		// �����ϴδ�������
		tpPlayer->FinishSave();

		// ��player����д���ļ�
		SavePlayer( tpPlayer, SAVE_FILE );

		KickPlayerWithoutSave( tpPlayer, EM_SAVE2FILE );

		return;
	}

	// ���ȱ���κ�һ�����ͷ���
	if ( ( ( tpPlayer->GetSaveState( ) & LSSTATE_CHARPROFILE ) != LSSTATE_CHARPROFILE ) ||
		 ( ( tpPlayer->GetSaveState( ) & LSSTATE_PROPERTY ) != LSSTATE_PROPERTY ) ||
		 ( ( tpPlayer->GetSaveState( ) & LSSTATE_BAGGAGE ) != LSSTATE_BAGGAGE ) ||
		 ( ( tpPlayer->GetSaveState( ) & LSSTATE_STORAGE ) != LSSTATE_STORAGE ) ||
		 ( ( tpPlayer->GetSaveState( ) & LSSTATE_TASK ) != LSSTATE_TASK ) || 
		 ( ( tpPlayer->GetSaveState( ) & LSSTATE_FRIEND ) != LSSTATE_FRIEND ) ||
		 ( ( tpPlayer->GetSaveState( ) & LSSTATE_REPETION ) != LSSTATE_REPETION ) )
	{
		// ������������ߴ洢����Ҫ���ͻ��˷���Ϣ
		return;
	}

	tpPlayer->FinishSave();

	tpPlayer->SetSaveState( LSSTATE_NONE );

	LOG_NOTICE( "default", "OnSavePlayer,player [%s] save_code %d, comm_status %d", 
		tpPlayer->GetCharNameShow(), nSaveCode, tpPlayer->GetCommState() ); 

	EMLeaveReason emLeaveReason; 
	int tGlobalSceneWorldID = 0;
	switch ( nSaveCode )
	{
		// �����ɫ���ݺ󷵻�����
		case SAVE_RETURN2GATE:
		{
			// ֪ͨ��ģ������ʵ��
			DestroyEntity( (CEntityPlayer*)tpPlayer, nSaveCode );						
			emLeaveReason = EM_LEAVE_RETURN2GATE;

			break; 
		}
		// �����ɫ���ݺ�֪ͨ�ͻ���		
		case SAVE_FORCEEXIT:
		case SAVE_LEAVEGAME:
		{
			// �鿴�Ƿ���ȫ�ִ�����Ϣ
			CGlobalTeleInfo tTeleInfo;			
			CGlobalTeleInfo *tpInfo = CGlobalModule::GetSingleton().GetGlobalTeleInfo( tpPlayer->GetCharID() );
			if ( tpInfo != NULL )
			{
				tTeleInfo = *tpInfo;				
			}			

			// ֪ͨ��ģ������ʵ��
			DestroyEntity( (CEntityPlayer*)tpPlayer, nSaveCode );

			if( nSaveCode == SAVE_FORCEEXIT )
			{
				emLeaveReason = EM_LEAVE_CLOSESOCKET ;
			}
			else
			{
				emLeaveReason = EM_LEAVE_LEAVEGAME ;
			}
			
			// �����ȫ�ֿ���ض�������
			// ֪ͨ�ͻ��˿��ԶϿ�������			
			if ( tTeleInfo.mAddr.empty() == false )
			{
				CMessage						tMsg;
				CMessageRedirectGateNotice 	tMsgFact;				
				tMsgFact.set_address( tTeleInfo.mAddr.c_str() );	
				tMsgFact.set_logintoken( tTeleInfo.mLoginToken );
				tMsgFact.set_accountid( tpPlayer->GetAccountID() );
				//if ( tTeleInfo.mTeleType != EGLOBALTELE_TYPE_RETURNTOGATE )
				{
					tMsgFact.set_cleancskey( 1 );
				}				
				tGlobalSceneWorldID = tTeleInfo.mSceneWorldID;
				tMsg.mutable_msghead()->set_messageid( ID_L2C_NOTIFY_REDIRECTGATE );
				tMsg.set_msgpara( (uint32)&tMsgFact );

				LOG_NOTICE( "default", "[GlobalTele]Player[ %d : %s]Redirect Gate( %s ) End, Scene all Playe Count Is[%d]", 
					tpPlayer->GetCharID(), tpPlayer->GetCharNameShow(), tpInfo->mAddr.c_str(),
				CSceneLogic::GetSingletonPtr()->GetPlayerNumber( ) - 1 );
				CSceneLogic::GetSingletonPtr()->Send2Player( tpPlayer, &tMsg );
				CGlobalModule::GetSingleton().DeleteGlobalTeleInfo( tpPlayer->GetCharID() );				
			}
			else
			{
				CMessage tMsg;
				CMessageLeaveGameResponse tMsgFact;
				CMessageHead* tpHead = tMsg.mutable_msghead();
				tpHead->set_messageid( ID_S2C_RESPONSE_LEAVEGAME );
				tMsg.set_msgpara( (uint32)&tMsgFact );
				Send2Player( tpPlayer, &tMsg );
			}
			break;
		}
		// �����ɫ���ݺ�֪ͨ�ͻ���
		case SAVE_KICKOUT:
		{
			// ֪ͨ��ģ������ʵ��
			DestroyEntity( (CEntityPlayer*)tpPlayer, nSaveCode );
			emLeaveReason = EM_LEAVE_KICKOUT;

			// ֪ͨ�ͻ��˱���������
			CMessage tMsg;
			CMessageKickoutNotice tMsgFact;
			CMessageHead* tpHead = tMsg.mutable_msghead();
			tpHead->set_messageid( ID_S2C_NOTIFY_KICK );
			tMsgFact.set_reason( tpPlayer->GetKickoutReason() );

			if ( tpPlayer->GetKickoutReason() == EM_KICKOUT_RELOGIN )
			{
				tMsgFact.set_param(tpPlayer->GetClientInfo( )->mClientAddr);
			}

			tMsg.set_msgpara( (uint32)&tMsgFact );
			Send2Player( tpPlayer, &tMsg );
			break;
		}

		// �����ɫ���ݺ�������
		case SAVE_REDIRECT:
		{
			// ������ȫ������ɹ��Ժ��֪ͨ���ؿ����Ϣ
			CMessage tMessage;
			CMessagePlayerRedirectRequest tPlayerRedirect;
			tMessage.mutable_msghead()->set_messageid( ID_S2G_PLAYER_REDIRECT_REQUEST );
			tMessage.set_msgpara( (uint32)&tPlayerRedirect );
			tPlayerRedirect.set_lineid( tpPlayer->GetTLineID( ));
			tPlayerRedirect.set_mapid( tpPlayer->GetTMapID( ) );
			tPlayerRedirect.set_posx( tpPlayer->GetTX( ) ); 
			tPlayerRedirect.set_posy( tpPlayer->GetTY( ) ); 
			tPlayerRedirect.set_charid( tpPlayer->GetCharID() );
			tPlayerRedirect.set_accountid( tpPlayer->GetAccountID() );
			tPlayerRedirect.set_charname( tpPlayer->GetCharName() );
			tPlayerRedirect.set_gender( tpPlayer->GetSex() );
			tPlayerRedirect.set_metier( tpPlayer->GetMetier() );
			tPlayerRedirect.set_nationality( tpPlayer->GetNationality() );
			tPlayerRedirect.set_facetype( tpPlayer->GetFaceType() );
			tPlayerRedirect.set_charlevel( tpPlayer->GetLevel() );
			tPlayerRedirect.set_exp( tpPlayer->GetExp());
			tPlayerRedirect.set_lastlogin( tpPlayer->GetLastLoginTime());
			tPlayerRedirect.set_teamflag( tpPlayer->GetTeamFlag() );			// Я������״̬��Ϊ�ӳ���CharID
			tPlayerRedirect.set_teamlevel( tpPlayer->GetTeamLevel( ) );
			tPlayerRedirect.set_encryptkey( tpPlayer->GetKey( ), KEYLEN );
			
			// �����ǰ������ٻ���,��ô�����ٻ��޿���߼�
			CPropertyCharacter* tpProCharacter = (CPropertyCharacter*) tpPlayer->GetProperty();
			if ( tpProCharacter->GetPetID() != 0 )
			{
				CEntity* tpEntity = GetEntity( tpProCharacter->GetPetID() );
				if ( tpEntity != NULL )
				{
					if ( tpEntity->IsPet() )
					{
						CPropertyPet* tpProPet = (CPropertyPet*) tpEntity->GetProperty();
						CEntityPet* tpPet = (CEntityPet*) tpEntity;
						tPlayerRedirect.set_pettempid( tpProPet->GetPropertyTempID() );
						tPlayerRedirect.set_petonlinetime( tpPet->GetOnlineTime() );
						tPlayerRedirect.set_petmode( tpPet->GetCurMode() );
					}
				}
			}

			//CTeamModule::GetSingleton().CreatePbTeamInfo(tpPlayer, tPlayerRedirect.mutable_teaminfo());
			CSceneLogic::GetSingleton( ).Send2Gate( &tMessage );
			
			// ���ﴦ���߼��ͱ�Ĳ�һ�������������Ͽ�����Ҫ������ȷ�Ͽ�������
			// TODO: ����һ����������ʵ�壬�����ػ�Ӧ������

			return;
		}

		// ��ʱ�����������
		case SAVE_TIMETRIGER:
		{
			return;
		}
		
		default:
		{
			break;
		}
	}

	// ��������������е�����
	DestroyPlayerInstance( tpPlayer, emLeaveReason, EM_SAVE2DB, tGlobalSceneWorldID );

}

// ���׼���뿪
void CSceneLogic::OnPlayerLeave( CEntityPlayer *pPlayer, int nState )
{
	CModuleManager::GetSingleton().OnPlayerLeave( pPlayer, nState );
}

int CSceneLogic::DestroyPlayerInstance( CEntityPlayer* vpPlayer, EMLeaveReason emLeave, EMSaveResult emSave, int nGlobalSceneWorldID /* = 0 */ )
{

	CMessage tMsg;
	CMessagePlayerLeaveMapNotice tMsgFact;
	CMessageHead* tpHead = tMsg.mutable_msghead();

	tpHead->set_messageid( ID_S2G_PLAYER_LEAVE_MAP_NOTICE );
	tMsgFact.set_charid( vpPlayer->GetCharID() );
	tMsgFact.set_accountid( vpPlayer->GetAccountID());
	tMsgFact.set_charlevel( vpPlayer->GetLevel());
	tMsgFact.set_charmetier( vpPlayer->GetMetier());

	CPropertyPlayer * tpProperty = ((CPropertyPlayer*)vpPlayer->GetProperty());
	if ( tpProperty )
	{
		tMsgFact.set_money1(tpProperty->GetMoney() + tpProperty->GetStorageMoney());
		tMsgFact.set_money2(tpProperty->GetBindMoney() + tpProperty->GetStorageBindMoney());
		tMsgFact.set_exp( tpProperty->GetExp());
	}
	
	// �����Ҫȥ�����������¼WorldID
	if ( vpPlayer != NULL )
	{
		if ( vpPlayer->GetRoleWorldID() <= 0 || vpPlayer->GetRoleWorldID() != nGlobalSceneWorldID )
		{
			tMsgFact.set_globalsceneworldid( nGlobalSceneWorldID );
		}			
	}	
	
	tMsgFact.set_reason( emLeave ); 
	tMsgFact.set_saveflag ( emSave ); 
	tMsg.set_msgpara( (uint32)&tMsgFact );

	// �����ط���ʵ������֪ͨ
	Send2Gate( &tMsg );

	LogEventLogoutScene(vpPlayer, emLeave, emSave);

	//////////////////////////////////////////////////////////////////////////

	PLAYERNAME_MAP::iterator tNameIter = mPlayerNameIndex.find( vpPlayer->GetCharName() );
	PLAYERID_MAP::iterator tCommIter = mPlayerCommIndex.find( vpPlayer->GetCommHandle( ) );
	PLAYERID_MAP::iterator tFindIter = mPlayerContainer.find( vpPlayer->GetCharID() );
	PLAYERID_MAP::iterator tWaitIter = mPlayerInWait.find( vpPlayer->GetCharID() );


	// ɾ�������������
	if ( tNameIter != mPlayerNameIndex.end( ) )
	{
		mPlayerNameIndex.erase( tNameIter );
	}

	// ɾ����Ҷ˿�����
	if ( tCommIter != mPlayerCommIndex.end( ) )
	{
		if(  tCommIter->second == vpPlayer->get_id() )
		{
			mPlayerCommIndex.erase( tCommIter );
			//LOG_NOTICE( "default", "delete %d from comm map ", vpPlayer->GetClientInfo( )->mSockIndex);
		}
		else
		{
			LOG_ERROR( "default", "already find comm %d, but player id %d  not match %d ", 
				vpPlayer->GetCommHandle( ), tCommIter->second, vpPlayer->get_id() );
		}
	}

	// ɾ����ҽ�ɫID����, ��ʱ�������������������û�м�����ɣ���Щ�����н��Ҳ�����ң�
	// ������ҵ�socket�������еģ���ƾ���Ҳ�ǿ��԰���ҶϿ����ӵġ�
	if ( tFindIter != mPlayerContainer.end() )
	{
		mPlayerContainer.erase( tFindIter );
		LOG_NOTICE( "default" , "player %d|%s leave from game", vpPlayer->GetCharID(), vpPlayer->GetCharNameShow() );
	}

	// �������ڵȴ����У������
	if ( tWaitIter != mPlayerInWait.end())
	{
		mPlayerInWait.erase(tWaitIter);
		LOG_NOTICE( "default" , "player %d|%s is erased from wait queue", vpPlayer->GetCharID(), vpPlayer->GetCharNameShow() );
	}


	// ���ʱ�������������Ͽ�socket,�ɿͻ��˷������
	if ( vpPlayer->GetCommHandle() > 0 && emLeave != EM_LEAVE_REDIRECT && nGlobalSceneWorldID == 0 )
	{
		CMessage tMsg;
		CMessageDisconnectNotify tDisconnectMsg;
		tMsg.mutable_msghead()->set_messageid( ID_S2C_NOTIFY_DISCONNECT );
		tMsg.set_msgpara( (uint32)&tDisconnectMsg );
		CSceneLogic::GetSingletonPtr()->Send2Player( vpPlayer, &tMsg );
	}
	
	
	CSceneObjManager::GetSingletonPtr( )->DestroyObject( vpPlayer->get_id() );

	return SUCCESS;
}


// ***************************************************************
//  Function:		SavePlayer
//  Description:	����������ݵ����ݿ�
//	Input:			pPlayer - ָ��; vSaveCode - ������
//	OutPut:			��
//	Return:			��
//	Others:			ִ��sql���ǰ���Ȱ�blob���˳��ַ�����ʽ
//  Date:			10/27/2008
// 
// ***************************************************************

void CSceneLogic::SavePlayer( CEntityPlayer* pPlayer, int vSaveCode )
{
	LK_ASSERT( pPlayer != NULL, return );

	if ( vSaveCode != SAVE_TIMETRIGER )
	{
		if ( pPlayer->IsSaving()) 
		{
			LOG_ERROR("default", "role(%d:%s) is saving now, why recall SavePlayer?", 
				pPlayer->GetCharID(), pPlayer->GetCharNameShow());

			return;
		}

		//��ʼ����
		pPlayer->StartSave();
	}

	// ����CheckSum
	pPlayer->ResetCheckSum();

	if ( vSaveCode == SAVE_FILE )
	{
		LOG_INFO("default", "[%s:%d][%s] Save role(%d:%s) to file",
				__LK_FILE__, __LINE__, __FUNCTION__, pPlayer->GetCharID(), pPlayer->GetCharNameShow());
	}

	// ���ȫ��playersave��������
	ClearSavePlayerPropety();

	if ( OnSaveData( pPlayer, vSaveCode ) == false )
	{
			LOG_ERROR("default", "[%s:%d][%s] Save role(%d:%s) failure, save code(%d)",
				__LK_FILE__, __LINE__, __FUNCTION__, pPlayer->GetCharID(), pPlayer->GetCharNameShow(), vSaveCode);

			return;
	}
	
	return;
}

bool CSceneLogic::OnSaveData( CEntityPlayer* pPlayer, int vSaveCode )
{
	int tIsCallBack = SQL_NEED_CALLBACK;
	if ( vSaveCode == SAVE_TIMETRIGER )
		tIsCallBack = SQL_NONE;

	return SavePlayerInfo( pPlayer, vSaveCode, tIsCallBack ) && SavePlayerProperty( pPlayer, vSaveCode, tIsCallBack );

}


//************************************
// Method:    KickPlayer
// FullName:  SceneServer::CSceneLogic::KickPlayer
// Access:    public 
// Returns:   int
// Qualifier: ����������
// Parameter: int vCharID
// Parameter: int nReason
// Parameter: int nfrom 1.���������ʱ��nfrom��Ϊ����ҷ��صĴ���ţ� 2.������ظ���¼���ˣ�nfrom��ǰһ��IP
//************************************
int CSceneLogic::KickPlayer( int vCharID, int nReason /*= 0*/, int nfrom /* = 0 */)
{
	CEntityPlayer* tpPlayer = (CEntityPlayer*) GetPlayerByCharID( vCharID );
	if ( tpPlayer == NULL )
	{
		CSceneLogic::PLAYERID_MAP::iterator tFindIter = 
				CSceneLogic::GetSingletonPtr()->mPlayerInWait.find( vCharID );

		if ( tFindIter != CSceneLogic::GetSingletonPtr()->mPlayerInWait.end( ) )
		{
			tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
		}
	}

	
	if ( tpPlayer == NULL )  
	{
		return EM_KICKOUT_NOTHISCHAR;
	}

	tpPlayer->SetKickoutReason(nReason);

	LOG_INFO("default", "[%s:%d] player (%d:%s at sokfd = %d,%d,%d) status(%d) is force to leave, reason %d",
			__FUNCTION__, __LINE__, tpPlayer->GetCharID(), tpPlayer->GetCharNameShow(), 
			tpPlayer->GetClientInfo( )->mSockIndex, tpPlayer->GetCommHandle( ), tpPlayer->GetCommState(), 
			tpPlayer->GetCommState(), nReason);
	
	if ( nfrom != 0 )
	{
		if( nReason == EM_KICKOUT_RELOGIN )
		{
			tpPlayer->GetClientInfo( )->mClientAddr = nfrom;
		}
		else
		{
			tpPlayer->SetKickoutCode( nfrom );
		}
	}


	if ( tpPlayer->GetCommState() != CEntityPlayer::STATE_INWAIT
	&& tpPlayer->GetCommState() != CEntityPlayer::STATE_REDIRECT_INWAIT)
	{
		tpPlayer->SetCommState( CEntityPlayer::STATE_KICKOUT );
	}

	// �����뿪��Ϸ�ӿ�
	PlayerLeaveFromGame(tpPlayer);

	return 0;
}


//************************************
// Method:    KickPlayerWithoutSave
// FullName:  SceneServer::CSceneLogic::KickPlayerWithoutSave
// Access:    public 
// Returns:   void
// Qualifier: ֻ������ϴδ��̲���ȷ������ʱʹ�ã�����������̣���������ҵ�½��ֱ�������ߡ�
// Parameter: int vCharID
//************************************
void CSceneLogic::KickPlayerWithoutSave( CEntityPlayer* pPlayer, EMSaveResult emSave )
{
	LK_ASSERT ( pPlayer != NULL, return  );

	LOG_NOTICE( "default", "kick out (%d|%s) without save, may be some blob info crashed or template data changed",
		pPlayer->GetCharID(), pPlayer->GetCharNameShow() );

	pPlayer->SetCommState( CEntityPlayer::STATE_KICKOUT );

	// ��������˶�����Ϊ��������쳣(1.������ϵ���Ʒ��ģ�����Ҳ�����2.�������ʱ��������ݲ��ɹ�)
	CMessage tMsg;
	CMessageKickoutNotice tMsgFact;
	CMessageHead* tpHead = tMsg.mutable_msghead();
	tpHead->set_messageid( ID_S2C_NOTIFY_KICK );
	tMsgFact.set_param(pPlayer->GetClientInfo( )->mClientAddr);
	if ( emSave == EM_SAVE2FILE)
	{
		tMsgFact.set_reason( EM_KICKOUT_LOCKDATA );
	}
	else if( emSave == EM_NOSAVE )
	{
		tMsgFact.set_reason( EM_KICKOUT_DATACRASH );
	}

	tMsg.set_msgpara( (uint32)&tMsgFact );
	Send2Player( pPlayer, &tMsg );

	DestroyEntity( pPlayer, SAVE_KICKOUT );
	DestroyPlayerInstance( pPlayer, EM_LEAVE_KICKOUT,  emSave);

}


void CSceneLogic::KickAllExcept( unsigned int unCharID )
{
	PLAYERID_MAP::iterator tBegin =  mPlayerContainer.begin();
	int tCount = 0;

	for ( ; tBegin != mPlayerContainer.end(); ++ tBegin )
	{
		if( tBegin->first == (int)unCharID )
		{
			continue;
		}

		CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tBegin->second );

		if ( tpPlayer == NULL || tpPlayer->GetCommState() ==  CEntityPlayer::STATE_KICKOUT ) 
		{
			continue;
		}
	

		KickPlayer( tBegin->first, EM_KICKOUT_SERVERMAINTANCE );

		tCount++;

		// 30��һ��������1s
		if( tCount >= 30 ) break;
	}

	sleep(1);

}


int CSceneLogic::TeleAll( int nMapID, int nPosX, int nPosY )
{
	PLAYERID_MAP::iterator tBegin =  mPlayerContainer.begin();
	int tCount = 0;

	for ( ; tBegin != mPlayerContainer.end(); ++ tBegin )
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tBegin->second );

		if ( tpPlayer == NULL ) 
		{
			continue;
		}	
		CPropertyPlayer *tpPropertyPlayer = (CPropertyPlayer*)tpPlayer->GetProperty();
		if ( tpPropertyPlayer->GetStateParam( STATE_STONE ).mInState == true )
		{
			int tBuffID = tpPropertyPlayer->GetStateParam( STATE_STONE ).mIndex;
			tpPropertyPlayer->DetachState( STATE_STONE, 0, BUFF, 0, 0 );
			tpPlayer->EntityRemoveBuff( tBuffID );
		}		
		CMapModule::GetSingleton().Teleport( tpPlayer->GetNationality( ), nMapID, nPosX, nPosY, tpPlayer, 0 );

		tCount++;

		if( tCount >= 100 ) break;
	}

	if ( tBegin == mPlayerContainer.end() )
		return 0;
	else
		return 1;
}


//************************************
// Method:    DestroyMapNPC
// FullName:  CSceneLogic::DestroyMapNPC
// Access:    public 
// Returns:   int	���ٵ�NPC����
// Qualifier: ����ָ����ͼNPC, �κ���Ч�ʵ��£��Ǳ�Ҫ�����Ҫʹ��
// Parameter: int nMapID   ��ͼID 
// Parameter: int nMapIndex  ��ͼ������Ĭ����0
//************************************
int CSceneLogic::DestroyMapNPC( int nMapID, int nMapIndex /*= 0*/ )
{
	std::vector< CEntity* > tToBeDestroyNpc;

	PLAYERID_MAP::iterator tBegin =  mNpcContainer.begin();
	for ( ; tBegin != mNpcContainer.end(); ++ tBegin )
	{
		CEntity* tpNPC = (CEntity*) CSceneObjManager::GetSingletonPtr()->GetObject( tBegin->second );
		if ( tpNPC == NULL ) 
		{
			continue;
		}	
		
		if( tpNPC->GetMapID() == nMapID && tpNPC->GetMapIndex() == nMapIndex )
		{
			tToBeDestroyNpc.push_back( tpNPC );
		}
	}

	std::vector< CEntity* >::iterator it_npc = tToBeDestroyNpc.begin();
	for( ; it_npc != tToBeDestroyNpc.end(); ++it_npc )
	{
		// ���ٺ����ڲ����漰��mNpcContainer����ɾ�������Ա�������ʱtToBeDestroyNpc������
		DestroyEntity( *it_npc, SAVE_KICKOUT );
	}

	return tToBeDestroyNpc.size();
}


//************************************
// Method:    DestroyEntity
// FullName:  SceneServer::CSceneLogic::DestroyEntity
// Access:    public 
// Returns:   void
// Qualifier: ֪ͨ��ģ������ʵ��, �������ң���Ҫ���ٳ��������е�ʵ����
//			ǰ�����Ѿ�SavePlayer�ɹ�
// Parameter: CEntity * pEntity
// Parameter: int vSaveCode
//************************************
void CSceneLogic::DestroyEntity( CEntity* pEntity, int vSaveCode )
{
	LK_ASSERT( pEntity != NULL, return );

	// ������������
	if ( pEntity->IsPlayer() )
	{
		LOG_NOTICE( "default", "destroy player entityid=%d, charid=%d, charname=%s, pos(%d,%d) map(%d) code %d",
			pEntity->GetEntityID(), ((CEntityPlayer*)pEntity)->GetCharID(), 
			((CEntityPlayer*)pEntity)->GetCharNameShow(), pEntity->GetPosX(), pEntity->GetPosY(), pEntity->GetMapID(),
			vSaveCode);
		
		// ֪ͨ��ģ�飬ʵ��������
		CModuleManager::GetSingleton( ).DestroyEntity( pEntity, vSaveCode );

		// ֪ͨ����ң�����˳�
		NoticeApexProxy_UserLogout( ((CEntityPlayer*)pEntity)->GetCharID() );
	
		// �ر���ҵ���־
		((CEntityPlayer*)pEntity)->CloseLog();
	}
	else // �����NPC���� 
	{
		// ֪ͨ��ģ�飬ʵ��������
		CModuleManager::GetSingleton( ).DestroyEntity( pEntity, vSaveCode );

		// ɾ��NPC����
		PLAYERID_MAP::iterator tFindIter = mNpcContainer.find( pEntity->GetEntityID( ) );
		if ( tFindIter != mNpcContainer.end( ) )
		{
			CSceneObjManager::GetSingletonPtr()->DestroyObject( tFindIter->second );
			mNpcContainer.erase( tFindIter );
		}
	}
}

int CSceneLogic::GetPlayerNumber( ) const
{ 
	return (int) mPlayerContainer.size( ); 
}

// ������Ϣ�����ݷ�����
int CSceneLogic::Send2Data( BYTE* pMessage, unsigned short vLength  )
{
#ifdef _DEBUG_
	LOG_DEBUG( "default", "send2data, len %d", vLength );
#endif
	return CSceneServer::GetSingletonPtr( )->mProxyClient.GetSocket()->SendOneCode( vLength, pMessage );
}

int CSceneLogic::Send2Data( int nUin, CMessage& rMessage, int nDesGameID )
{
	// ǿ�Ƹ�дԭ��Ϣͷ
	rMessage.mutable_msghead()->set_srcfe( FE_SCENCESERVER );
	rMessage.mutable_msghead()->set_srcfe( FE_DATASERVER );
	rMessage.mutable_msghead()->set_srcid(  CSceneServer::GetSingleton().mThisServerID );
	rMessage.mutable_msghead()->set_dstid( 1 );	

	CProxyHead tProxyHead;
	tProxyHead.set_srcfe( CET_GAMESERVER );
	tProxyHead.set_dstfe( CET_DBSERVER );
	tProxyHead.set_srcid( CSceneServer::GetSingleton().mThisServerID );
	tProxyHead.set_dstid( 1 ); // TODO: ��ʱд�������ݿ������Ŀǰֻ��1̨
	// �� nUin ����dbsvrd����ִ���̵߳�key����֤һ��������в�������һ���߳�ִ��
	tProxyHead.set_uin( nUin );
	tProxyHead.set_srcgameid( mWorldID );
	tProxyHead.set_desgameid( nDesGameID );

	BYTE message_buffer[ PLAYER_DATALEN ] = {0};
	int message_length = pbmsg_setmsg<CProxyHead>(tProxyHead, rMessage, (char*)message_buffer, sizeof(message_buffer));      

	if (message_length > 0)        
	{
		char tszMessageid[16] = {0};
		snprintf( tszMessageid, sizeof(tszMessageid)-1, "%d->db", rMessage.mutable_msghead()->messageid() );
		PERF_FUNC( tszMessageid, ; );

		int nRet =  Send2Data( message_buffer, message_length );
		if( nRet < 0 )
		{
			LOG_ERROR( "default", "[%s:%d] send 2 dataserver len = %d failed %d ", __FUNCTION__, __LINE__, message_length, nRet );
			return -2;
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

// ��ȫ�ָ���������������Ϣ
int CSceneLogic::Send2GlobalDunServer( CMessage *pMessage )
{
	// ǿ�Ƹ�дԭ��Ϣͷ
	pMessage->mutable_msghead()->set_srcfe( FE_SCENCESERVER );
	pMessage->mutable_msghead()->set_srcfe( FE_DUNGEONSERVER );
	pMessage->mutable_msghead()->set_srcid( CSceneServer::GetSingleton().mThisServerID );
	pMessage->mutable_msghead()->set_dstid( 1 );

	CProxyHead tProxyHead;
	tProxyHead.set_srcfe( CET_GAMESERVER );
	tProxyHead.set_dstfe( CET_DUNGEON );
	tProxyHead.set_srcid( CSceneServer::GetSingleton().mThisServerID );
	tProxyHead.set_dstid( 1 ); 	
	tProxyHead.set_srcgameid( mWorldID );
	BYTE message_buffer[ PLAYER_DATALEN ] = {0};
	int message_length = pbmsg_setmsg<CProxyHead>(tProxyHead, *pMessage, (char*)message_buffer, sizeof(message_buffer));      

	if (message_length > 0)        
	{
		char tszMessageid[16] = {0};
		snprintf( tszMessageid, sizeof(tszMessageid)-1, "%d->dunserver", pMessage->mutable_msghead()->messageid() );
		PERF_FUNC( tszMessageid, ; );
			
#ifdef _DEBUG_
		LOG_DEBUG( "default", "send2dunserver, len %d", message_length );
#endif
		
		int tRet =  CSceneServer::GetSingletonPtr( )->mProxyClient.GetSocket()->SendOneCode( message_length, message_buffer );;
		if( tRet < 0 )
		{
			LOG_ERROR( "default", "[%s:%d] send2dunserver len = %d failed %d ", __FUNCTION__, __LINE__, message_length, tRet );
			return -2;
		}
		return 0;
	}
	else
	{
		return -1;
	}
}

// ͨ��Entity������Ϣ��ָ�����
void CSceneLogic::Send2Player( CEntity* pPlayer, CMessage* pMessage )
{
	if (pPlayer == NULL)
	{
		LOG_ERROR("default", "player has already exist, pls check it");
		return;
	}

	static std::vector<CEntityPlayer*> tPlayer(1);
	tPlayer[0] = (CEntityPlayer*)pPlayer ;

	char tszMessageid[16] = {0};
	snprintf( tszMessageid, sizeof(tszMessageid)-1, "%d->cli", pMessage->mutable_msghead()->messageid() );
	PERF_FUNC( tszMessageid, ; );

	CSceneServer::GetSingletonPtr( )->mClientHandle->Send( pMessage, &tPlayer);
}


void CSceneLogic::Send2Player( std::vector< CEntityPlayer*>* rEntityVec, CMessage* pMessage )
{
	char tszMessageid[16] = {0};
	snprintf( tszMessageid, sizeof(tszMessageid)-1, "%d->cli", pMessage->mutable_msghead()->messageid() );
	PERF_FUNC( tszMessageid, ; );

	CSceneServer::GetSingletonPtr( )->mClientHandle->Send( pMessage, rEntityVec );
}

// ������Ϣ������ͻ���
void CSceneLogic::Send2Player( CEntityPlayer* pPlayer, BYTE* pMessageBuff, int nLen, CMessage* pMessage )
{
	char tszMessageid[16] = {0};
	snprintf( tszMessageid, sizeof(tszMessageid)-1, "%d->cli", pMessage->mutable_msghead()->messageid() );
	PERF_FUNC( tszMessageid, ; );

	CSceneServer::GetSingletonPtr( )->mClientHandle->Send( pPlayer, pMessageBuff, nLen, pMessage );
}


// ͨ����ɫID������Ϣ��ָ�����
void CSceneLogic::Send2Player( int vCharID, CMessage* pMessage )
{
	CEntityPlayer* tpPlayer = GetPlayerByCharID( vCharID );
	// ������û���ҵ�,��ô���͸�����ת��
	if ( tpPlayer == NULL )
	{
		if ( vCharID != 0 )
		{
			if ( ( pMessage->msghead().messageid() & CMessageRouter::MSGROUTER ) != CMessageRouter::MSGROUTER  )
			{
				LOG_ERROR( "default", "[ %s : %d ][ %s ]Message[%x]Is Not a router Message, receve player is %d", __LK_FILE__, __LINE__, __FUNCTION__,
					pMessage->msghead().messageid(), vCharID );
				return;
			}

			Message* pUnknownMessage = (Message*) pMessage->msgpara();
			const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessage->GetDescriptor();
			const ::google::protobuf::Reflection*  pReflection = pUnknownMessage->GetReflection();

			if (pDescriptor == NULL || pReflection == NULL) return; 
			const ::google::protobuf::FieldDescriptor*  pFieldDescriptor = pDescriptor->FindFieldByNumber(1);
			if (pFieldDescriptor == NULL) return;

			const Message& tRouter = pReflection->GetMessage( *pUnknownMessage, pFieldDescriptor ); 		
			CMessageRouter* tpRouter = ( CMessageRouter* ) &tRouter;
			if (tpRouter->has_sendback()) return;

			Send2Gate( pMessage );
		}
		return;
	}

	Send2Player( tpPlayer, pMessage );
}

// ͨ����ɫ���Ʒ�����Ϣ��ָ����ң������Ҳ��ڸó�������ôͨ������ת��
void CSceneLogic::Send2Player( const char* pName, CMessage* pMessage )
{
	CEntityPlayer* tpPlayer = GetPlayerByName( pName );

	// ������û���ҵ�,��ô���͸�����ת��
	if ( tpPlayer == NULL )
	{
		if ( ( pMessage->msghead().messageid() & CMessageRouter::MSGROUTER ) !=  CMessageRouter::MSGROUTER )
		{
			LOG_ERROR( "default", "[ %s : %d ][ %s ]Message[ %d ] Is not a router message, receve is %s", 
					__LK_FILE__, __LINE__, __FUNCTION__, pMessage->msghead().messageid(),
					pName );
			return;
		}

		Message* pUnknownMessage = (Message*) pMessage->msgpara();
		const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessage->GetDescriptor();
		const ::google::protobuf::Reflection*  pReflection = pUnknownMessage->GetReflection();

		if (pDescriptor == NULL || pReflection == NULL) return; 
		const ::google::protobuf::FieldDescriptor*  pFieldDescriptor = pDescriptor->FindFieldByNumber(1);
		if (pFieldDescriptor == NULL) return;

		const Message& tRouter = pReflection->GetMessage( *pUnknownMessage, pFieldDescriptor ); 		
		CMessageRouter* tpRouter = ( CMessageRouter* ) &tRouter;
		if (tpRouter->has_sendback()) return;

		Send2Gate( pMessage );
		return;
	}

	// ���͸��������������
	Send2Player( tpPlayer, pMessage );
}

// �õ��ڳ����е�ָ�����( ͨ��ͨѶ�˿����� )
CEntityPlayer* CSceneLogic::GetPlayerByComm( int vCommHandle )
{
	PLAYERID_MAP::iterator tFindIter = mPlayerCommIndex.find( vCommHandle );
	if ( tFindIter == mPlayerCommIndex.end( ) )
		return NULL;

	return (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
}

// �õ��ڳ����е�ָ�����( ͨ��accountID���� )
CEntityPlayer* CSceneLogic::GetPlayerByAccountID( int nAccountID )
{	   
	PLAYERID_MAP::iterator tItor = 	mPlayerContainer.begin();
	for ( ; tItor != mPlayerContainer.end(); ++tItor )
	{
		CEntityPlayer *tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tItor->second );
		LK_ASSERT( tpPlayer != NULL, continue )
		if ( tpPlayer->GetAccountID() == ( unsigned int )nAccountID )
		{
			return tpPlayer;
		}		 		
	}
	return NULL;		
}

// �õ��ڳ����е�ָ�����( ͨ��CharID���� )
CEntityPlayer* CSceneLogic::GetPlayerByCharID( int vCharID )
{
	PLAYERID_MAP::iterator tFindIter = mPlayerContainer.find( vCharID );
	if ( tFindIter == mPlayerContainer.end( ) )
		return NULL;

	return (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
}

// ͨ����ɫ���ƣ��õ���ɫʵ��
CEntityPlayer* CSceneLogic::GetPlayerByName( const char* pCharName )
{
	PLAYERNAME_MAP::iterator tFindIter = mPlayerNameIndex.find( pCharName );
	if ( tFindIter == mPlayerNameIndex.end( ) )
		return NULL;

	return (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
}

// �õ��ȴ������е����
CEntityPlayer* CSceneLogic::GetWaitingPlayerByCharID( int vCharID )
{
	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( vCharID );
	if( tFindIter == mPlayerInWait.end() )
	{
		return NULL;
	}

	return (CEntityPlayer*)  CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
}

// ������Ϣ���������
void CSceneLogic::SendWorldMessage( CMessage* pMessage )
{
	SendCountryMessage( pMessage, -1);
}

// ������Ϣ��ĳ������( ͨ������ת�� )
void CSceneLogic::SendCountryMessage( CMessage* pMessage, int nCountryID )
{
	LK_ASSERT( pMessage != NULL, return )
	pMessage->mutable_msghead()->set_dstfe( FE_COUNTRY );
	pMessage->mutable_msghead()->set_dstid( nCountryID );
	Send2Gate( pMessage );
}

// ������Ϣ��ĳ������( ͨ������ת�� )
void CSceneLogic::SendFamilyMessage( CMessage* pMessage, int nFamilyID, bool bNeendSendToScene /* = false */ )
{
	LK_ASSERT( pMessage != NULL, return )		
	if ( bNeendSendToScene == true )
	{
		pMessage->mutable_msghead()->set_srcfe( FE_SCENCESERVER );
	}
	else
	{
		pMessage->mutable_msghead()->set_srcfe( FE_GATESERVER );
	}
	pMessage->mutable_msghead()->set_dstfe( FE_FAMILY );
	pMessage->mutable_msghead()->set_dstid( nFamilyID );
	Send2Gate( pMessage );
}


// ͨ��worldid������Ϣ�����շ�ΪĿ�����أ�
void CSceneLogic::Send2OtherGate( CMessage *pMessage, int nWorldID )
{
	LK_ASSERT( pMessage != NULL && nWorldID > 0, return )	
	pMessage->mutable_msghead()->set_dstfe( FE_OTHERGATE );
	pMessage->mutable_msghead()->set_dstid( nWorldID );
	Send2Gate( pMessage );
}

// ������Ϣ����������( ͨ������ת�� )
void CSceneLogic::SendCorpsMessage( CMessage* pMessage, int nCorpsID, bool bNeendSendToScene /* = false */ )
{
	LK_ASSERT( pMessage != NULL, return )
	if ( bNeendSendToScene == true )
	{
		pMessage->mutable_msghead()->set_srcfe( FE_SCENCESERVER );
	}
	else
	{
		pMessage->mutable_msghead()->set_srcfe( FE_GATESERVER );
	}	
	pMessage->mutable_msghead()->set_dstfe( FE_CORPS );
	pMessage->mutable_msghead()->set_dstid( nCorpsID );
	Send2Gate( pMessage );
}

// ������Ϣ����ǰ�����������
void CSceneLogic::SendSceneMessage( CMessage* pMessage, int CountryID, int vMapID )
{
	PLAYERID_MAP::iterator tBeginIter	= mPlayerContainer.begin( );
	PLAYERID_MAP::iterator tEndIter		= mPlayerContainer.end( );
	for ( ; tBeginIter != tEndIter; tBeginIter ++ )
	{
		CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tBeginIter->second );
		LK_ASSERT( tpPlayer != NULL, continue )
		if ( CountryID == -1 || CountryID == tpPlayer->GetNationality() )
		{
			if ( vMapID == 0 || vMapID == tpPlayer->GetMapID() )
			{
				Send2Player( tpPlayer, pMessage );
			}							
		}  									  		
	}
}

bool CSceneLogic::Send2Gate( CMessage* pMessage )
{
	CProxyHead tProxyHead;

	static BYTE buffer[ MAX_CODE_LEN ];
	unsigned short len = sizeof( buffer );

	LK_ASSERT(pMessage != NULL, return false);
	Message* pUnknownMessagePara = (Message*) pMessage->msgpara();
	LK_ASSERT( pUnknownMessagePara != NULL, return false);


	pbmsg_setproxy(&tProxyHead, CET_GAMESERVER, CET_OTHERSERVER, 
			CSceneServer::GetSingleton().mThisServerID, 2, TRANS_P2P, CMD_NULL);

	pMessage->mutable_msghead()->set_srcfe(FE_SCENCESERVER);
	pMessage->mutable_msghead()->set_srcid(CSceneServer::GetSingleton().mThisServerID);

	len = pbmsg_setmsg<CProxyHead>( tProxyHead, *pMessage, (char*)buffer, len );

	if( len <= 0 )
	{
		LOG_ERROR( "default", "Serialize for router message failed. %d", len );
		return false;
	}

	char tszMessageid[16] = {0};
	snprintf( tszMessageid, sizeof(tszMessageid)-1, "%d->gate", pMessage->mutable_msghead()->messageid() );
	PERF_FUNC( tszMessageid, ; );

#ifdef _DEBUG_
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessagePara->GetDescriptor();
	// CMessageGameHeartBeatNotice����ӡ ̫����
	if ( strcmp( pDescriptor->name().c_str(), "CMessageGameHeartBeatNotice") != 0 )
	{
		LOG_DEBUG("default", "Send2Gate(%d): MsgName[%s] ProxyHead[%d:%s] MsgHead[%s] MsgPara[%s]", len,
			pDescriptor->name().c_str(),  tProxyHead.ByteSize(),  tProxyHead.ShortDebugString().c_str(),
			pMessage->ShortDebugString().c_str(), pUnknownMessagePara->ShortDebugString().c_str());
	}

#endif

	int nRet = CSceneServer::GetSingletonPtr( )->mProxyClient.GetSocket()->SendOneCode( len, (BYTE*)buffer ) ;
	if ( nRet < 0 )
	{
		LOG_ERROR( "default", "[%s:%d] send 2 gate len = %d failed %d", __FUNCTION__, __LINE__, len, nRet );
	}

	return ( nRet == 0 );
}

// ������Ϣ����־������
void CSceneLogic::Send2Log( CMessage* pMessage, int nHandle, int nSplitor, int nDesGameID /* = 0 */ )
{
	CProxyHead tProxyHead;

	static BYTE buffer[ MAX_CODE_LEN ];
	unsigned short len = sizeof(buffer);

	LK_ASSERT( pMessage != NULL, return );
	Message* pUnknownMessagePara = (Message*) pMessage->msgpara( );
	LK_ASSERT( pUnknownMessagePara != NULL, return  );

	pbmsg_setproxy( &tProxyHead, CET_GAMESERVER, CET_OTHERSERVER, 
		CSceneServer::GetSingleton( ).mThisServerID, 3, TRANS_P2P, CMD_NULL );

	pMessage->mutable_msghead( )->set_srcfe( FE_SCENCESERVER );
	pMessage->mutable_msghead( )->set_srcid( CSceneServer::GetSingleton( ).mThisServerID );
	
	// ��ϷID
	tProxyHead.set_srcgameid( mWorldID );
	tProxyHead.set_desgameid( nDesGameID );

	// ����DstID �ֶ������洢��Ϣ�ķֱ�ԭ��
	pMessage->mutable_msghead( )->set_dstid( nSplitor );

	tProxyHead.set_uin( nHandle );

	len = pbmsg_setmsg<CProxyHead>( tProxyHead, *pMessage, (char*)buffer, len );

	if( len <= 0 )
	{
		LOG_ERROR( "default", "Serialize for log message failed. %d", len );
		return ;
	}

	char tszMessageid[16] = {0};
	snprintf( tszMessageid, sizeof(tszMessageid)-1, "%d->log", pMessage->mutable_msghead()->messageid() );
	PERF_FUNC( tszMessageid, ; );

#ifdef _DEBUG_
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessagePara->GetDescriptor( );
	LOG_DEBUG( "default", "Send2Log(%d): MsgName[%s] ProxyHead[%d:%s] MsgHead[%s] MsgPara[%s]", len,
		pDescriptor->name( ).c_str( ),  tProxyHead.ByteSize( ),  tProxyHead.ShortDebugString( ).c_str( ),
		pMessage->ShortDebugString( ).c_str( ), pUnknownMessagePara->ShortDebugString( ).c_str( ) );
#endif


	int nRet =	CSceneServer::GetSingletonPtr( )->mProxyClient.GetSocket( )->SendOneCode( len, (BYTE*)buffer );
	if( nRet < 0 )
	{
		LOG_ERROR( "default", "[%s:%d] send 2 log len = %d failed %d", __FUNCTION__, __LINE__, len ,nRet );
	}
}

void CSceneLogic::Launch( )
{
	// �������������ļ�
	//CSceneCfgManager::GetSingletonPtr()->Initialize( (char*)("../config/data/scene_config/sceneconfig.xml") );
	CSceneCfgManager::GetSingletonPtr()->Initialize( const_cast<char*>(CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(), const_cast<char*>("scene_config/sceneconfig.xml") )));

	// ��ʼ��ͳ����־
	INIT_ROLLINGFILE_LOG("Perf", "../log/perf.log", LEVEL_INFO );

	STAT_LOG* tpStat = CSceneCfgManager::GetSingletonPtr()->GetStat_log();
	if ( tpStat != NULL )
	{
		INIT_ROLLINGFILE_LOG( tpStat->mIdentifier, tpStat->mDirectory, (LogLevel)tpStat->mPriority, tpStat->mMaxfilesize, tpStat->mMaxbackupindex );
	}			 
	CDirtyWord* tpDirty = new CDirtyWord( );
	if ( tpDirty == NULL )
		printf("no dirty\n");
	

	//[������ʾ] ��Ҫ�ѱ��˵�ģ��ע�͵�, ���ԵĻ��ڱ��ش����ϸ�,��Ҫ�ϴ�
	LOG_INFO( "default", "Begin To Lauch LogicModule..." );

	CModuleManager::GetSingleton( ).RegisterModule( new CPropertyModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CNpcModule ); // npc������map֮ǰ����,�������´�����entity����״̬������
	CModuleManager::GetSingleton( ).RegisterModule( new CMapModule ); 
	CModuleManager::GetSingleton( ).RegisterModule( new CFriendModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CTeamModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CChatModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CMailModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CTradeModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CStallModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CRepetionModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CGMModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CActivityModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CFamilyModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CIbStoreModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CCorpsModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CRankModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CTaskModule );  // ����ģ�����������ĳЩ���� �ͷ�����
	CModuleManager::GetSingleton( ).RegisterModule( new CJudgeModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CWorldModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CAchieveModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CBourseModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CMarriageModule );
	CModuleManager::GetSingleton( ).RegisterModule( new CGlobalModule );


	LOG_INFO( "default", "Lauch LogicModule Complete..." );
	
	if ( CSceneServer::GetSingletonPtr( )->ReadConfig() < 0 )
	{
		printf( "Config file read failed, exit\n" );
		exit( 1 );
	}	

	// ������
	if( CSceneServer::GetSingletonPtr( )->ReadServerConfig( ) < 0 )
	{
		LOG_ERROR( "default", "Server Config File Error, Server Stop. Please Check it " );
		printf( "Read Server Config Faild, exit \n" );
		exit(1);
	}



	// ����������
	CModuleManager::GetSingleton( ).LaunchServer();

	if( CSceneServer::GetSingletonPtr( )->ConnectToServer() < 0 )
	{
		printf("connetct to server faild. so exit");
		exit(1);
	} 
	
	// ������ҵĸ�����־Ŀ¼
	CreatPlayerLog(); 

	// ע�����ü��صĻص�����
	const char* pcConfigPath = "../config/data/dirtyword";
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, ".txt", CSceneServer::LoadDirtyWordCallback);

	pcConfigPath = "../config/data/template/template_server.dat";
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CSceneServer::LoadTemplateCallback);

	pcConfigPath = CSceneLogic::GetSingleton().GetConfigDataFileNamePath(CSceneLogic::GetSingletonPtr()->GetGameID(), const_cast<char*>("scene_config/sceneconfig.xml"));
	CSceneServer::GetSingleton().RegisterLoadConfigCallback(pcConfigPath, CSceneServer::LoadSceneConfigCallback);
}

void CSceneLogic::Run(int nDaemon )
{

}

void CSceneLogic::Shutdown( )
{
	// ģ���ͷ��ڴ�
	CDataStatic::Finialize( );

	// �ͷ�����ڴ�
	CDirtyWord* pDirtyWord = CDirtyWord::GetSingletonPtr();
	if( pDirtyWord != NULL )
		delete pDirtyWord;

	// �ͷ���Ϣ�����ڴ�
	CMessageFactory* pFactory = CMessageFactory::GetSingletonPtr();
	if( pFactory != NULL )
		delete pFactory;

	// �ͷ����ù������ڴ�
	CSceneCfgManager* pCfgMng = CSceneCfgManager::GetSingletonPtr();
	if( pCfgMng != NULL )
		delete pCfgMng;

	// �ͷ�ģ��������ڴ�
	CModuleManager* pModuleMng = CModuleManager::GetSingletonPtr();
	if( pModuleMng != NULL )
		delete pModuleMng;

	// �ͷ���Ϣ�ַ��������ڴ�
	CMessageDispatcher* pDispatch = CMessageDispatcher::GetSingletonPtr();
	if( pDispatch != NULL )
		delete pDispatch;


	CModuleManager::GetSingleton( ).ExitServer( );
}

// ����������״̬����ֹ����
void CSceneLogic::OnCheckOnlieStateEvent( unsigned int vTickCount, unsigned int vTickOffset )
{
	if ( ! mStateCheckTimer.Elapse( vTickOffset ) )
	{
		return ;
	}

	time_t tNow = time(NULL);
	int nSavePlayerNumOnce = 0;

	PLAYERID_MAP::iterator tBegin = mPlayerContainer.begin();
	for ( ; tBegin != mPlayerContainer.end(); ++tBegin )
	{
		CEntityPlayer* tpPlayer = GetPlayerByCharID( tBegin->first );
		if( tpPlayer == NULL )
		{
			LOG_ERROR( "default", "player charid  %d didn't exist", tBegin->first );
			continue;
		}

		// active��ʱ ��λ�ǣ���
		if( (unsigned int)( tNow - tpPlayer->GetClientInfo( )->m_tLastActiveTime ) 
			>= CSceneCfgManager::GetSingletonPtr()->GetScenelogic_cfg()->mKicknonactivityplayertime )
		{	
			LOG_NOTICE( "default", "player %d has long time no action, so kick out", tBegin->first );


			KickPlayer(tBegin->first, EM_KICKOUT_TIMEOUT );
			continue;
		}

		switch( tpPlayer->GetCommState())
		{
			case CEntityPlayer::STATE_INMAP :
			{
				
				// ��ʱ����(��)
				if ( (unsigned int)(tNow - tpPlayer->GetLastSaveTimeStamp( )) 
						> CSceneCfgManager::GetSingletonPtr()->GetScenelogic_cfg()->mPlayersavedbtime)
				{
					// һ��ѭ������30��������˲�为�ع���
					if( ++nSavePlayerNumOnce >= 30 )
					{
						break;
					}

					tpPlayer->SetLastSaveTimeStamp( tNow );
					PERF_FUNC( "SavePlayer", CSceneLogic::GetSingletonPtr( )->SavePlayer( tpPlayer, SAVE_TIMETRIGER ) );
				}

				break;
			}

			case CEntityPlayer::STATE_REDIRECT:
			{
				if ( (unsigned int)( tNow - tpPlayer->GetRedirectTimeStamp()) >= 
					CSceneCfgManager::GetSingletonPtr()->GetScenelogic_cfg()->mPlayerredirecttimeout  )
				{
					tpPlayer->SetCommState(CEntityPlayer::STATE_INMAP);
				}
				break;
			}

			case CEntityPlayer::STATE_KICKOUT :
			case CEntityPlayer::STATE_RETURNTOGATE:
			case CEntityPlayer::STATE_LEAVEGAME:
			case CEntityPlayer::STATE_FORCEEXIT:
			{
				if ( (unsigned int)( tNow - tpPlayer->GetClientInfo()->m_tLastActiveTime) >= 60)
				{
					if ( tpPlayer->IsSaving())
					{
						SavePlayer(tpPlayer, SAVE_FILE);
						KickPlayerWithoutSave(tpPlayer, EM_SAVE2FILE);
					}else
					{
						KickPlayerWithoutSave(tpPlayer, EM_SAVE2DB);
					}
				}

				break;
			}

			default:
			{
				break;
			}
		}
	}
}

const char* CSceneServer::GetCountryName( unsigned short vLineID )
{
	if( vLineID == 0 || vLineID > sizeof( mCountryArrary ) / sizeof( mCountryArrary[ 0 ] ) )
	{
		return NULL;
	}

	return mCountryArrary[ vLineID - 1 ].mName;	
}


int CSceneServer::SendKeepAliveToProxy()
{
	CProxyHead tHead;
	char message_buffer[PLAYER_DATALEN];
	pbmsg_setproxy(&tHead, CET_GAMESERVER, CET_PROXYSERVER, mThisServerID, 1, TRANS_P2P, CMD_KEEPALIVE);

	unsigned short message_length  = tHead.ByteSize() + 4;
	*((unsigned short*) message_buffer)  = message_length;
	*((unsigned short*) (message_buffer+2))  = tHead.ByteSize();

	if(tHead.SerializeToArray(message_buffer+4, message_length - 4))
	{
#ifdef _DEBUG_
		LOG_DEBUG("default", "Send2Proxy %s on [%s]", tHead.ShortDebugString().c_str(), __FUNCTION__); 
#endif
		mProxyClient.GetSocket()->SendOneCode(message_length, (BYTE*)message_buffer);

	}else
	{
		LOG_ERROR("default", " [ %s : %d ][ %s ] error", __LK_FILE__, __LINE__, __FUNCTION__);
	}

	return 0;
}

void CSceneServer::SendKeepAliveToGate()
{
	CMessageGameHeartBeatNotice tHeartBeatMessage;	

	tHeartBeatMessage.set_serverid(mThisServerID);

	CMessage tMessage;
	tMessage.set_msgpara((uint32_t) &tHeartBeatMessage);
	pbmsg_sethead(&tMessage, ID_S2G_GAME_HEART_BEAT_NOTICE, 0, 0, 0, 0, 0, 0);

	// �����������2000-3000����Ҽ��㣬���л���Ĵ�С���ᳬ��12k
	for( CSceneLogic::PLAYERID_MAP::iterator it = CSceneLogic::GetSingletonPtr()->mPlayerContainer.begin();
			it != CSceneLogic::GetSingletonPtr()->mPlayerContainer.end();
			++it)
	{
		tHeartBeatMessage.add_charids( (unsigned int)(it->first) );
	}

	CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );
}

void CSceneLogic::OnFireSession( CMessage* pMessage )
{
	CMessageExecuteSqlResponse3* tpExecuteSql = (CMessageExecuteSqlResponse3*)pMessage->msgpara();
	if (tpExecuteSql == NULL)
	{
		LOG_ERROR( "default","FireSession Fail" );    
		return;                                                                                         
	}
	int nSessionID = tpExecuteSql->sessionid();
	CSession* pSession = (CSession*) CSceneObjManager::GetSingletonPtr()->GetObject( nSessionID );
	if (pSession == NULL)
	{
		LOG_ERROR( "default","Get SessionObj failure SessionID(%d) ", nSessionID );    
		return;                                                                                         
	}

	switch ( pSession->GetSessionType() )
	{
	case mailrecenothing:
		{
			CMailDBOperate::MailReceNothing( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case dbmailrece:
		{
			CMailDBOperate::DBMailRece( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}	
	case dbmsgrece:
		{
			CMailDBOperate::DbMsgRece( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case getmailcountrece:
		{
			CMailDBOperate::GetMailCountRece( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case checknewmail:
		{
			CMailDBOperate::CheckNewMailRece( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case addblackcallback:
		{
			CFriendModule::GetSingletonPtr()->AddBlackCallBack( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case commonsqlcallback:
		{
			CFriendModule::GetSingletonPtr()->CommonSqlCallBack( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case playeraddfriendcallback:
		{
			CFriendModule::GetSingletonPtr()->OnPlayerAddFriendCallBack( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case loadfriendscallback:
		{
			//CFriendModule::GetSingletonPtr()->LoadFriendsCallBack( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case loadfriendscallback2:
		{
			//CFriendModule::GetSingletonPtr()->LoadFriendsCallBack2( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case getmaildetailrece:
		{
			CMailDBOperate::GetMailDetailRece( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case saveplayer_charprofile:
		{
			// �����RESAVE��û�����ʵ�壡
			if ( pSession->GetParam1() == RESAVE_FROMFILE )
			{
				if ( tpExecuteSql->resultcode( ) != 0 ) // �ɹ�
					OnResaveSuccess( pSession->GetParam2(), SAVE_PLAYER_INFO );
				break;
			}
			CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( pSession->GetParam2() );
			if ( tpPlayer == NULL )
			{
				LOG_ERROR( "default", "[%s:%d] save player fail, can't find player %d", __FUNCTION__, __LINE__, pSession->GetParam2() );
				break;
			}

			LOG_DEBUG( "pro", "saveplayer_charprofile session callback, now savestate is %04x", tpPlayer->GetSaveState( ) );
			tpPlayer->SetSaveState( tpPlayer->GetSaveState( ) | LSSTATE_CHARPROFILE );
			OnSavePlayer( pSession->GetParam1(), pSession->GetParam2(), tpExecuteSql->resultcode( ) );
			break;
		}
	case saveplayer_property_all:
		{
			// �����RESAVE��û�����ʵ�壡
			if ( pSession->GetParam1() == RESAVE_FROMFILE )
			{
				if ( tpExecuteSql->resultcode( ) != 0 ) // �ɹ�
					OnResaveSuccess( pSession->GetParam2(), SAVE_PLAYER_PRO );
				break;
			}
			CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( pSession->GetParam2() );
			if ( tpPlayer == NULL )
			{
				LOG_ERROR( "default", "[%s:%d] save player fail, can't find player %d", __FUNCTION__, __LINE__, pSession->GetParam2() );
				break;
			}
			LOG_DEBUG( "pro", "saveplayer_property session callback, now savestate is %04x", tpPlayer->GetSaveState( ) );
			tpPlayer->SetSaveState( tpPlayer->GetSaveState( ) | LSSTATE_PROPERTY | LSSTATE_TASK |  LSSTATE_FRIEND 
				| LSSTATE_REPETION );
			OnSavePlayer(  pSession->GetParam1(), pSession->GetParam2(), tpExecuteSql->resultcode( ) );
			break;		
		}

	case loadplayerforlogin_charprofile:
		{
			OnLoadPlayer_CharProfile( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}

	case loadplayerforlogin_baggage:
		{
			OnLoadPlayer_Baggage( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case loadplayerforlogin_storage:
		{
			OnLoadPlayer_Storage( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}


	case loadplayerforlogin_yuanbao:
		{
			OnLoadPlayer_YuanBao( pMessage, pSession->GetParam1(), pSession->GetParam2());
			break;
		}
	case    em_dbsession_pay_amount:
		{
			CIbStoreModule::GetSingletonPtr()->OnSessionPlayerPayAmount(pMessage, pSession->GetParam1(), pSession->GetParam2());
			break;
		}
	case em_dbsession_achieve_save:
	case em_dbsession_achieve_query:
		{
			CAchieveModule::GetSingleton().OnDBSession( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case load_task_global:
		{
			CTaskModule::GetSingleton().OnLoadGlobalData( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case checkmailindb:
		{
			CMailModule::GetSingleton().OnSessionCheckIfMailInDB( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case em_dbsession_judge_query:
		{
			CJudgeModule::GetSingleton().OnDBSession( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case session_creatmarriageinfo:
		{
			CMarriageModule::GetSingleton().OnSessionCreatMarriageDBInfo( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
				
	case session_marriage_loadmarriagenum:
		{
			CMarriageModule::GetSingleton().OnSessionLoadMarriageCountFromDB( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
		
	case session_marriage_loadmarriageinfo:
		{
			CMarriageModule::GetSingleton().OnSessionLoadMarriageInfoFromDB( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case session_marriage_loadcampinfo:
		{
			CMarriageModule::GetSingleton().OnSessionLoadCampInfo( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case session_marriage_loadplayermarriageinfo:
		{
			CMarriageModule::GetSingleton().OnsessionLoadPlayerMarriageInfo( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case session_creatcampinfo:
		{
			CMarriageModule::GetSingleton().OnSessionCreatCampDBInfo( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
    case session_yaoqianshu_loadplayerinfo:
        {
            OnLoadPlayer_YaoQianShu( pMessage, pSession->GetParam1(), pSession->GetParam2() );
            break;
        }
    case session_yaoqianshu_loadplayerpick:
        {
            OnLoadPlayer_PickStoreBox( pMessage, pSession->GetParam1(), pSession->GetParam2() );
            break;
        }
    case session_yaoqianshu_loadplayerrankinfo:
        {
            CActivityYqsPlayerRankInfo::GetSingleton().OnSessionLoadPlayerRankInfoDB( pMessage, 0, 0 );
            break;
        }
    case session_yaoqianshu_updateplayerinfo:
        {
            break;
        }
	case yb_stall_exchange:
		{
			CStallModule::GetSingletonPtr()->OnSessionYbStallExchangeResponse( pMessage, 0, 0 );
			break;
		}
	case em_dbsession_pay_func:
		{
			CIbStoreModule::GetSingletonPtr()->OnSessionPlayerPayFunc(pMessage, pSession->GetParam1(), pSession->GetParam2());
			break;
		}
	case em_dbsession_getswornteam :
		{
			CFriendModule::GetSingleton().OnSessionGetSwornDBInfo( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	case em_dbsession_loadchatmsg:
		{
			CMailModule::GetSingleton().OnSessionLoadOffLineChatMsg( pMessage, pSession->GetParam1(), pSession->GetParam2() );
			break;
		}
	default:
		{
			LOG_ERROR( "default", "unkonwn session type %d", pSession->GetSessionType() );
			break;
		}
		
	}

	LOG_DEBUG( "default", "[%s:%d] destroy session %d", __FUNCTION__, __LINE__, nSessionID );
	CSceneObjManager::GetSingletonPtr()->DestroyObject( nSessionID );
	return;
}


// ����session��ʱ
void CSceneLogic::OnSessionTimeOut( int nSessionID )
{
	CSession* pSession = (CSession*)CSceneObjManager::GetSingletonPtr()->GetObject( nSessionID );
	if( pSession == NULL )
	{
		LOG_ERROR( "default", "[%s:%d] seesion id %d can't find", __FUNCTION__, __LINE__, nSessionID );
		return ;
	}

	switch ( pSession->GetSessionType() )
	{
		case saveplayer_charprofile:
		case saveplayer_property_all:
		case SESSION_SAVE_PLAYER_BAGGAGE:   // ��ʱ������,���Ժ��ٴ��޸�ʱ�����ɷ�֧
		{
			// ����Ǵ��ļ�����ʧ���ˣ�ֱ��return����
			if ( pSession->GetParam1() == RESAVE_FROMFILE )
				return;

			CEntityPlayer* pPlayer = (CEntityPlayer*) GetEntity( pSession->GetParam2() );
			if( pPlayer == NULL )
			{
				LOG_ERROR( "default", "player [entityid:%d] alreay logout", pSession->GetParam2() );
				return ;
			}

			LOG_FATAL( "pro", "player %d save %d timeout", pPlayer->GetCharID(), pSession->GetSessionType() );

			// �����ϴδ��̱�־
			pPlayer->FinishSave();
			

			// ֻ���˳���Ϸ��д�ļ�
			if( pPlayer->GetCommState() == CEntityPlayer::STATE_INMAP 
			|| pPlayer->GetCommState() == CEntityPlayer::STATE_REDIRECT)
			{
				return ;
			}

			// impossibal status
			if( pPlayer->GetCommState() == CEntityPlayer::STATE_INWAIT
			|| pPlayer->GetCommState() == CEntityPlayer::STATE_REDIRECT_INWAIT)
			{
				return;
			}
			
			SavePlayer( pPlayer, SAVE_FILE);

			KickPlayerWithoutSave( pPlayer, EM_SAVE2FILE );

			break;
		}
		case SESSION_LOAD_PLAYER_BAGGAGE:
			{
				OnTimeoutLoadPlayerItemInfoFromDB( pSession->GetParam1(), pSession->GetParam2() );
				break;
			}
			// ɾ���ʼ���ʱ
		case mailrecenothing:
			{
				CMailDBOperate::MailDelTimeout( pSession->GetParam1(), pSession->GetParam2() );
				break;
			}
		case bourse_inc_account:
		case bourse_dec_account:
		case bourse_load_by_account:
			{
				CBourseModule::GetSingletonPtr( )->DBSessionTimeOut( pSession );
			}
			break;
			// Ԫ�����ף������ʱ���ݿ�δ���أ���ʱ������Һ�����Ԫ���˻�����Ҫ������µ�½��Ϸȷ�ϡ�
		case yb_stall_exchange:
			{
				CStallModule::GetSingletonPtr()->OnSessionTimeoutYbStallExchange( pSession );
				break;
			}
		case em_dbsession_pay_amount:
			{
				// �����̳ǵ��߳�ʱ
				CIbStoreModule::GetSingletonPtr()->OnSeessionTimeoutPlayerPayAmount( pSession );
				break;
			}
		case em_dbsession_pay_func:
			{
				//���ܸ���ʱ ��ʱ
				CIbStoreModule::GetSingletonPtr()->OnSessionTimeoutPlayerPayFunc( pSession );
				break;

			}
		case em_dbsession_getswornteam:
			{
				CFriendModule::GetSingleton().OnTimeOutGetSwornDBInfo( pSession->GetParam1(), pSession->GetParam2() );
			}
	default:
		{
			break;
		}
	}
	
	return ;
}


// �����ķֲ���ȡ����
void CSceneLogic::OnLoadPlayer_CharProfile( CMessage* pMessage, int vParameter1, int vParameter2 )
{
	LK_ASSERT( pMessage != NULL, return );

	CMessageExecuteSqlResponse3* pSqlRes = (CMessageExecuteSqlResponse3*)pMessage->msgpara();

	if ( pSqlRes->resultcode() == 0 )
	{
        LOG_ERROR( "default", "[ %s:%d ][%s]Execute Sql For Player  Login failed", __LK_FILE__, __LINE__, __FUNCTION__  );
		return;
	}

	if( pSqlRes->rowcount() == 0 )
	{
		LOG_ERROR( "default", "[%s:%d] Execute Sql For Player Login 0 row, para1 %d, para2 %d", 
			__FUNCTION__, __LINE__, vParameter1, vParameter2  );
		return ;
	}

	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( vParameter1 );
	if ( tFindIter == mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-3",
			__LK_FILE__, __LINE__, vParameter1 );
		return;
	}

	CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
	if( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "In CSceneLogic::OnLoadPlayerForLogin(), can't FInd EntityPlayer ObjID=%d", tFindIter->second );
		return ;
	}

	//TODO: �����Ǹ�Ǳ���� ��������һ��Ҫ����select����е��������б仯���������ݻ���ز���
	// ���ȼ�������Ƿ���ڣ�����ɫ�ǽ������һ�ν��룬��ɫ���ݽ�������
	if ( pSqlRes->colcount() != 35 )
	{
		//TODO: ������ݿⷵ�ص�������һ�£�ֱ��������
		LOG_ERROR("default", "[%s:%d] data colcount %d is not match", __FUNCTION__, __LINE__, pSqlRes->colcount() );
		KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
		return;
	}


	// ��ȡ�������
	tpPlayer->SetCharID( ::atoi( pSqlRes->fieldvalue(0).c_str() ) );
	tpPlayer->SetAccountID( ::atoi( pSqlRes->fieldvalue(1).c_str() ) );
	tpPlayer->SetCharName( pSqlRes->fieldvalue(2).c_str() );
	tpPlayer->SetSex( ::atoi( pSqlRes->fieldvalue(3).c_str() ) );
	tpPlayer->SetMetier( ::atoi( pSqlRes->fieldvalue(4).c_str() ));
	tpPlayer->SetNationality( ::atoi( pSqlRes->fieldvalue(5).c_str() ) );
	tpPlayer->SetFaceType( ::atoi( pSqlRes->fieldvalue(6).c_str() ) );
	tpPlayer->SetLevel( ::atoi( pSqlRes->fieldvalue(9).c_str() ) );
	tpPlayer->SetExp( ::atoll( pSqlRes->fieldvalue(10).c_str() ) );

	// �����������½�Ļ�������Ч���꣬��ʼ�������ݿ������ꡣ ��Ϊ����ǿ�������Ļ��������Ѿ�����ǰ�ó���Чֵ�ˡ�
	if( (tpPlayer->GetPosX( ) == -1) && (tpPlayer->GetPosY( ) == -1) )
	{
		tpPlayer->SetPosX( ::atoi( pSqlRes->fieldvalue(12).c_str() ) );
		tpPlayer->SetPosY( ::atoi( pSqlRes->fieldvalue(13).c_str() ) );
		
		
		// ����������������ȴ���
		if ( CSceneLogic::GetSingleton().GetLineID() == tpPlayer->GetNationality() )
		{
			CTemplateMarriageConfig *tpMarriageConfig = ( CTemplateMarriageConfig * )CDataStatic::mMarriageConfig;
			if ( tpMarriageConfig != NULL )
			{
				for ( unsigned int i = 0; i < ARRAY_CNT( tpMarriageConfig->mWeddinInfo ); ++i )
				{
					if ( tpPlayer->GetMapID() == tpMarriageConfig->mWeddinInfo[i].mWeddingHallMapID )
					{
						tpPlayer->SetMapID( tpMarriageConfig->mMapID );
						tpPlayer->SetPosX( tpMarriageConfig->mPosX );
						tpPlayer->SetPosY( tpMarriageConfig->mPosY );
						break;
					}
				}
			}	
		}	
	}

	tpPlayer->SetAliveStatus( (EAliveType) (::atoi( pSqlRes->fieldvalue(14).c_str() )) );
	tpPlayer->SetLastLoginTime( ::time( NULL ) );
	tpPlayer->SetOnlineTime( ::atoi( pSqlRes->fieldvalue(16).c_str() ) );

	// ����ְҵ
	tpPlayer->GetProperty()->SetPropertyTempID( tpPlayer->GetMetier() );

	// ������º�
	if( tpPlayer->IsNewCharacter() == true ) 
	{
		CTemplateBeginner *pBeginner = (CTemplateBeginner*)CDataStatic::GetTemp( TEMP_BEGINNER );
		if ( pBeginner != NULL )
		{
			tpPlayer->SetPosX( pBeginner->mPosX2 );
			tpPlayer->SetPosY( pBeginner->mPosY2 );
		}

		// ������ºţ����ݿ�û�и���ҵĳɾ����ݼ�¼�����һ��
		CAchieveModule::GetSingleton().OnEventInitAchieveDB( tpPlayer );
	}
	else
	{
		if( CSceneCfgManager::GetSingletonPtr()->GetScenelogic_cfg()->mValidatedataintegrity == 1 )
		{
			// ��Ҫ�� save_code�Ǵ���ʱ�ı�־(��SAVE_TIMERTRIGER); save_bitflat�Ǵ���ʱ�ı�־λ(�磺LSSTATE_CHARPROFILE) 
			int nSaveCode = ::atoi( pSqlRes->fieldvalue(17).c_str() );
			int nSaveBitFlag = ::atoi( pSqlRes->fieldvalue(18).c_str() );

			if( nSaveCode == SAVE_TIMETRIGER || nSaveBitFlag != LSSTATE_CHARPROFILE )
			{
				LOG_FATAL( "default", "player %d last save is not complete(save_code = %d | save_bitflag = %d), so forbide login ...",
					tpPlayer->GetCharID(), nSaveCode, nSaveBitFlag );

				KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
				return ;
			}
		}
	}

	CPropertyPlayer* tpProperty = (CPropertyPlayer*)tpPlayer->GetProperty( );

	// set money data
	tpProperty->SetMoney( ::atoi( pSqlRes->fieldvalue( 11 ).c_str() ) );
	tpProperty->SetBindMoney( ::atoi( pSqlRes->fieldvalue( 19 ).c_str() ) );

	//// ����2������
	//if ( pSqlRes->fieldvalue( 20 ).length() > 0 )
	//{
	//	tpProperty->SetPassWord( pSqlRes->fieldvalue( 20 ).c_str() );
	//}			
	
	
	
	// ����MD5ֵ
	if ( pSqlRes->fieldvalue(21).length() > 0)
	{
		int nDBCheckSum  = atoi(pSqlRes->fieldvalue(21).c_str());
		int nCalCheckSum = tpPlayer->CalProfileCheckSum();

		if (nDBCheckSum != nCalCheckSum)
		{
			LOG_ERROR("default", "Role(%d:%s) 's profile is not valid,loaded(%d), but cal(%d)", 
				tpPlayer->GetCharID(), tpPlayer->GetCharNameShow(), nDBCheckSum, nCalCheckSum);

			//return;
		}
	}

	tpPlayer->SetRoleStatusParam( ::atoi( pSqlRes->fieldvalue(22).c_str() ) );

	// Set SilverYB
	tpProperty->SilverYB().set( ::atoi(pSqlRes->fieldvalue(23).c_str()));
	
	tpProperty->SetStorageMoney( ::atoi( pSqlRes->fieldvalue(24).c_str() ) );
	tpProperty->SetStorageBindMoney( ::atoi( pSqlRes->fieldvalue(25).c_str() ) );

	tpPlayer->SetGameID(GetGameID());
	tpPlayer->SetUserName(pSqlRes->fieldvalue(26).c_str());
	
	tpProperty->GetRolePassword()->SetProtectTimeLength( ::atoi( pSqlRes->fieldvalue(27).c_str() ) );

	// ��ȡ�ϴε�½ʱ��
	tpPlayer->SetRoleCreateTime( pSqlRes->fieldvalue(30).c_str() );	

	//tpProperty->GetRolePassword()->SetProtectTimeLength( ::atoi( pSqlRes->fieldvalue(27).c_str() ) );
	tpPlayer->SetMarriageID( ::atoi( pSqlRes->fieldvalue(31).c_str() ) );

	tpPlayer->SetChangeCampTime(::atoi(pSqlRes->fieldvalue(32).c_str()));
	tpPlayer->SetRoleStatus(::atoi(pSqlRes->fieldvalue(33).c_str()));
	tpPlayer->SetSwornID(::atoi(pSqlRes->fieldvalue(34).c_str()));
	tpPlayer->SetLoadState( tpPlayer->GetLoadState( ) | LSSTATE_CHARPROFILE );	
	OnLoadPlayer_Final( tpPlayer, tpPlayer->GetCharID(), vParameter2 );	 
}


//************************************
// Method:    OnLoadPlayer_Property
// FullName:  SceneServer::CSceneLogic::OnLoadPlayer_Property
// Access:    public 
// Returns:   void
// Qualifier: ������������ֶΣ�ǰ������ҽ�ɫ������Ϣ�Ѿ����سɹ�
// Parameter: CMessage * pMessage
// Parameter: int vParameter1
// Parameter: int vParameter2
//************************************
void CSceneLogic::OnLoadPlayer_Property( CMessage* pMessage, int vParameter1, int vParameter2 )
{
	LK_ASSERT( pMessage != NULL, return );

	CMessageExecuteSqlResponse3* pSqlRes = (CMessageExecuteSqlResponse3*)pMessage->msgpara();

	if ( pSqlRes->resultcode() == 0 )
	{
        LOG_ERROR( "default", "[ %s:%d ][%s]Execute Sql For Player  Login failed", __LK_FILE__, __LINE__, __FUNCTION__  );
		return;
	}

	if( pSqlRes->rowcount() == 0 )
	{
		LOG_ERROR( "default", "[%s:%d] Execute Sql For Player Login 0 row, para1 %d, para2 %d", 
			__FUNCTION__, __LINE__, vParameter1, vParameter2  );
		return ;
	}

	int tCharID		= vParameter1;

	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( tCharID );
	if ( tFindIter == mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-4",
			__LK_FILE__, __LINE__, tCharID );
		return;
	}

	CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
	if( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "In CSceneLogic::OnLoadPlayerForLogin(), can't FInd EntityPlayer ObjID=%d", tFindIter->second );
		return ;
	}

	// ���뱣֤��һ������ݼ�����ɲ����½���
	if( (tpPlayer->GetLoadState() & LSSTATE_CHARPROFILE) == 0 )
	{
		LOG_ERROR( "default", "player %s's charprofile is not ready ", tpPlayer->GetCharNameShow() );
		return ;
	}

	CPropertyPlayer* tpProperty = (CPropertyPlayer*)tpPlayer->GetProperty( );


	// �ж��Ƿ����º�( �´�����ɫ��blob���� )
	if ( tpPlayer->IsNewCharacter() == false )
	{
		//TODO: �����Ǹ�Ǳ���� ��������һ��Ҫ����select����е��������б仯���������ݻ���ز���
		// ���ȼ�������Ƿ���ڣ�����ɫ�ǽ������һ�ν��룬��ɫ���ݽ�������
		if ( pSqlRes->colcount() != 20 )
		{
			//TODO: ������ݿⷵ�ص�������һ�£�ֱ��������
			LOG_ERROR("pro", "[%s:%d] data colcount %d is not match", __FUNCTION__, __LINE__, pSqlRes->colcount() );
			KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
			return ;
		}

		// TODO: ����PB��ʽ�����ݿ��ȡ������ֵ
		tpProperty->SetCurHP( ::atoi(pSqlRes->fieldvalue(0).c_str()) );
		tpProperty->SetCurMP( ::atoi(pSqlRes->fieldvalue(1).c_str()) );
		tpProperty->SetCurAP( ::atoi(pSqlRes->fieldvalue(2).c_str()) );


		// ���ػ�������
		PBPlayerBasicInfo tPBPlayerBasic;
		if( tPBPlayerBasic.ParseFromArray( pSqlRes->fieldvalue(3).c_str(), (int)pSqlRes->fieldvaluelen(3) ) == true )
		{
			tpProperty->CreateBasicInfoFromTlv( &tPBPlayerBasic );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBProperty Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(3) );
			return ;
		}

		// ���ؼ���
		PBSkillList tPBSkill;
		if( tPBSkill.ParseFromArray( pSqlRes->fieldvalue(4).c_str(), (int)pSqlRes->fieldvaluelen(4) ) == true )
		{
			tpProperty->GetSkillList( ).CreateFromTlv2( &tPBSkill );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBSkillList Data Failed, Len %d", 
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(),(int)pSqlRes->fieldvaluelen(4) );
			return ;
		}

		// ����BuffList
		PBBuffList tPBBuff;
		if( tPBBuff.ParseFromArray( pSqlRes->fieldvalue(5).c_str(), (int)pSqlRes->fieldvaluelen(5) ) == true )
		{
			CBuffList *tpBuff = tpProperty->GetBuffList( );
			tpBuff->CreateFromTlv2( tpProperty, &tPBBuff );
			CPropertyModule::GetSingletonPtr( )->GetResultList()->Initialize();
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBBuffSkill Data Failed, Len %d", 
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(5) );
			return ;
		}

		//// ����װ��
		//PBItemBox tPBEquip;
		//if( tPBEquip.ParseFromArray( pSqlRes->fieldvalue(6).c_str(), (int)pSqlRes->fieldvaluelen(6) ) == true )
		//{
		//	//�������ʧ�ܣ�����������
		//	if( tpProperty->GetEquipment( )->CreateFromTlv2( &tPBEquip ) != true )
		//	{
		//		LOG_FATAL( "pro", "player %s : %d load equipment blob failed", tpPlayer->GetCharNameShow(),  tpPlayer->GetCharID() );
		//		KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
		//		return ;
		//	}
		//}
		//else
		//{
		//	LOG_ERROR( "pro", "player %s:%d Parse PBItemBox-Equipment Data Failed, Len %d",
		//		tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(),(int)pSqlRes->fieldvaluelen(6) );
		//	return ;
		//}

		// ����cd��
		PBPlayerCDGroupInfo tPBCDGroup;
		if( tPBCDGroup.ParseFromArray( pSqlRes->fieldvalue(6).c_str(), (int)pSqlRes->fieldvaluelen(6)  ) == true )
		{
			tpProperty->CreateCDGroupFromTlv( &tPBCDGroup );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBPlayerCDGroupInfo Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(),(int)pSqlRes->fieldvaluelen(6) );
			return;
		}

		// ����pvp
		PBPlayerPVPInfo tPBPvPInfo;
		if( tPBPvPInfo.ParseFromArray( pSqlRes->fieldvalue(7).c_str(), (int)pSqlRes->fieldvaluelen(7)  ) == true )
		{
			tpProperty->CreatePvPBlobInfoFromTlv( &tPBPvPInfo );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBPlayerPVPInfo Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(7) );
			return;
		}

		// ���سƺ�
		PBPlayerTitleInfo tPBTitleInfo;
		if( tPBTitleInfo.ParseFromArray( pSqlRes->fieldvalue(8).c_str(), (int)pSqlRes->fieldvaluelen(8)  ) == true )
		{
			tpProperty->CreateTitleInfoFromTlv( &tPBTitleInfo );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBPlayerTitleInfo Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(8) );
			return;
		}


		// ���ػ
		PBPlayerActivityInfo tPBActivity;
		if( tPBActivity.ParseFromArray( pSqlRes->fieldvalue(9).c_str(), (int)pSqlRes->fieldvaluelen(9)  ) == true )
		{
			tpProperty->CreateActivityInfoFromTlv( &tPBActivity );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBPlayerActivityInfo Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(9) );
			return;
		}

		// �����컯
		PBPlayerTalentInfo tPBTalent;
		if( tPBTalent.ParseFromArray( pSqlRes->fieldvalue(10).c_str(), (int)pSqlRes->fieldvaluelen(10)  ) == true )
		{
			tpProperty->CreateTalentInfoFromTlv( &tPBTalent );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBPlayerTalentInfo Data Failed, Len %d", 
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(10) );
			return;
		}

		// ���ط���
		PBPlayerMWInfo tPBMWInfo;
		if( tPBMWInfo.ParseFromArray( pSqlRes->fieldvalue(11).c_str(), (int)pSqlRes->fieldvaluelen(11)  ) == true )
		{
			tpProperty->CreateMWInfoFromTlv( &tPBMWInfo );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBPlayerMWInfo Data Failed, Len %d", 
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(11) );
			return;
		}

		// ���������
		PBLifeSkillBox tPBLifeSkill;
		if( tPBLifeSkill.ParseFromArray( pSqlRes->fieldvalue(12).c_str(), (int)pSqlRes->fieldvaluelen(12)  ) == true )
		{
			tpProperty->GetPlayerLifeSkill()->SetFromPB( tPBLifeSkill );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBLifeSkill Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(12) );
			return;
		}

		// ����ͳ����Ϣ
		PBPlayerStatisticInfo tPBStatistic;
		if( tPBStatistic.ParseFromArray( pSqlRes->fieldvalue(13).c_str(), (int)pSqlRes->fieldvaluelen(13)  ) == true )
		{
			tpProperty->CreateStatisticFromTlv( &tPBStatistic );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBPlayerStatisticInfo Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(13) );
			return;
		}	

		// ������ħ־
		PBMonsterRecordInfo tPBMonsterRecord;
		if( tPBMonsterRecord.ParseFromArray( pSqlRes->fieldvalue(14).c_str(), (int)pSqlRes->fieldvaluelen(14) ) == true )
		{
			tpProperty->CreateMonsterInfoFromTlv( &tPBMonsterRecord );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBMonsterRecordInfo Data Failed, Len %d", 
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(14) );
			return;
		}


		// ���ش�����Ϣ
		PBTelePosInfo tPBTelePos;
		if( tPBTelePos.ParseFromArray( pSqlRes->fieldvalue(15).c_str(), (int)pSqlRes->fieldvaluelen(15)  ) == true )
		{
			tpProperty->CreateTelePosFromTlv( &tPBTelePos );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBTelePosInfo Data Failed, Len %d", 
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(15) );
			return;
		}


		// ���زŻ�
		PBWizard tPBWizard;
		if( tPBWizard.ParseFromArray( pSqlRes->fieldvalue(16).c_str(), (int)pSqlRes->fieldvaluelen(16)  ) == true )
		{
			tpProperty->GetWizard().CreateFromTlv( &tPBWizard );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBWizard Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(16) );
			return;
		}

		// �ͻ�����Ϣ
		PBPlayerClientInfo tPBClientInfo;
		if( tPBClientInfo.ParseFromArray( pSqlRes->fieldvalue(17).c_str(), (int)pSqlRes->fieldvaluelen(17)  ) == true )
		{
			tpProperty->CreateRoleClientInfoFromTlv( &tPBClientInfo );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBPlayerClientInfo Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(17) );
			return;
		}

		// ���ش���
		PBMatrixInfo tPBMatrix;
		if( tPBMatrix.ParseFromArray( pSqlRes->fieldvalue(19).c_str(), (int)pSqlRes->fieldvaluelen(19)  ) == true )
		{
			tpProperty->CreateMatrixInfoFromTlv( &tPBMatrix );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBPlayerMatrix Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(19) );
			return;
		}
		
		// �������߾��鵤��Ϣ
		PBExpTimeInfo tPBTimeInfo;
		if ( tPBTimeInfo.ParseFromArray( pSqlRes->fieldvalue( 20 ).c_str(), (int)pSqlRes->fieldvaluelen(20) ) == true )
		{
			tpProperty->GetExpTimeInfo()->SetFromPB( tPBTimeInfo );
		}		
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBExpTimeInfo Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(20) );
		}		
		
		// ���ؾ۱�����Ϣ
		PBTreasureBowl tPBTreasureBowl;
		if ( tPBTreasureBowl.ParseFromArray( pSqlRes->fieldvalue( 21 ).c_str(), (int)pSqlRes->fieldvaluelen(21) ) == true )
		{
			tpProperty->GetTreasureBowlInfo()->SetFromPB( tPBTreasureBowl );
		}
		else
		{
			LOG_ERROR( "pro", "player %s:%d Parse PBTreasureBowl Data Failed, Len %d",
				tpPlayer->GetCharNameShow(), tpPlayer->GetCharID(), (int)pSqlRes->fieldvaluelen(21) );
		}
		

		// ��������ºţ���Ҫ�����̵�У
		if( CSceneCfgManager::GetSingletonPtr()->GetScenelogic_cfg()->mValidatedataintegrity == 1 )
		{
			// ��Ҫ�� save_code�Ǵ���ʱ�ı�־(��SAVE_TIMERTRIGER); save_bitflat�Ǵ���ʱ�ı�־λ(�磺LSSTATE_CHARPROFILE) 
			int nSaveBitFlag = ::atoi( pSqlRes->fieldvalue(18).c_str() );
			
			if( nSaveBitFlag != (LSSTATE_TOTAL_COMMPLTE - LSSTATE_CHARPROFILE - LSSTATE_YUANBAO) )
			{
				LOG_ERROR( "default", "player %d last save is not complete(save_bitflag = %d), so forbide login ...",
						tpPlayer->GetCharID(), nSaveBitFlag );
					
					KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
					return ;
			}
		}

	}
	else
	{	
		// �������Ĭ��ֵ
		CPropertyModule::GetSingletonPtr()->SetDefaultValue( tpPlayer );
	}

	tpPlayer->SetLoadState( tpPlayer->GetLoadState( ) | LSSTATE_PROPERTY );
	OnLoadPlayer_Final( tpPlayer, tCharID, vParameter2 );
}


void CSceneLogic::OnLoadPlayer_Baggage( CMessage* pMessage, int vParameter1, int vParameter2 )
{
	LK_ASSERT( pMessage != NULL, return );

	CMessageExecuteSqlResponse3* pSqlRes = (CMessageExecuteSqlResponse3*)pMessage->msgpara();

	if ( pSqlRes->resultcode() == 0 )
	{
		LOG_ERROR( "default", "Execute Sql For Player Login-Baggage failed"  );
		return;
	}

	if( pSqlRes->rowcount() == 0 )
	{
		LOG_ERROR( "default", "[%s:%d] Execute Sql For Player Login 0 row, para1 %d, para2 %d", 
			__FUNCTION__, __LINE__, vParameter1, vParameter2  );
		return ;
	}

	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( vParameter1 );
	if ( tFindIter == mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-5",
			__LK_FILE__, __LINE__, vParameter1 );
		return;
	}

	CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
	if( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "In CSceneLogic::OnLoadPlayerForLogin(), can't FInd EntityPlayer ObjID=%d", tFindIter->second );
		return ;
	}

	CPropertyPlayer* tpProperty = (CPropertyPlayer*)tpPlayer->GetProperty( );
	
	// �ж��Ƿ����º�( �´�����ɫ��blob���� )
	if ( tpPlayer->IsNewCharacter() == false )
	{
		// ���ȼ�������Ƿ���ڣ�����ɫ�ǽ������һ�ν��룬��ɫ���ݽ�������
		if ( pSqlRes->colcount() != 2 )
		{
			//TODO: ������ݿⷵ�ص�������һ�£�ֱ��������
			LOG_ERROR("pro", "[%s:%d] data colcount %d is not match", __FUNCTION__, __LINE__, pSqlRes->colcount() );
			KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
			return;
		}

		PBItemBox tPBBaggage;
		if( tPBBaggage.ParseFromArray( pSqlRes->fieldvalue(0).c_str(), (int)pSqlRes->fieldvaluelen(0) ) == true )
		{
			//�������ʧ�ܣ�����������
			if( tpProperty->GetBaggage( )->CreateFromTlv2( &tPBBaggage ) != true )
			{
				LOG_FATAL( "pro", "player %s : %d load baggate blob failed", tpPlayer->GetCharNameShow(),  tpPlayer->GetCharID() );
				KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
				return ;
			}

#ifdef _DEBUG_
			LOG_DEBUG( "pro", "Player[Char=%d, CharName=%s]  Data CreateFromPB [ %s ]", 
				tpPlayer->GetCharID(), tpPlayer->GetCharNameShow(), 
				tPBBaggage.DebugString().c_str() );
#endif
		}
		else
		{
			LOG_ERROR( "pro", "Parse PBItemBox-Baggage Data Failed, Len %d", (int)pSqlRes->fieldvaluelen(0) );
			return ;
		}

		PBItemBox tPBTask;
		if( tPBTask.ParseFromArray( pSqlRes->fieldvalue(1).c_str(), (int)pSqlRes->fieldvaluelen(1) ) == true )
		{
			//�������ʧ�ܣ�����������
			if( tpProperty->GetTaskBaggage( )->CreateFromTlv2( &tPBTask ) != true )
			{
				LOG_FATAL( "pro", "player %s : %d load task_baggage blob failed", tpPlayer->GetCharNameShow(),  tpPlayer->GetCharID() );
				KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
				return ;
			}
#ifdef _DEBUG_	
			LOG_DEBUG( "pro", "Player[Char=%d, CharName=%s]  Data CreateFromPB [ %s ]", 
				tpPlayer->GetCharID(), tpPlayer->GetCharNameShow(), tPBTask.DebugString().c_str() );
#endif
		}
		else
		{
			LOG_ERROR( "pro", "Parse PBItemBox-TaskBaggage Data Failed, Len %d", (int)pSqlRes->fieldvaluelen(1) );
			return ;
		}

		tpPlayer->CalDetailCheckSum(pSqlRes->fieldvalue(0).c_str(), pSqlRes->fieldvaluelen(0));

	}
	tpPlayer->SetLoadState( tpPlayer->GetLoadState( ) | LSSTATE_BAGGAGE );
	OnLoadPlayer_Final( tpPlayer, tpPlayer->GetCharID(), vParameter2 );
}


void CSceneLogic::OnLoadPlayer_Storage( CMessage* pMessage, int vParameter1, int vParameter2 )
{
	LK_ASSERT( pMessage != NULL, return );

	CMessageExecuteSqlResponse3* pSqlRes = (CMessageExecuteSqlResponse3*)pMessage->msgpara();
	LK_ASSERT( pSqlRes != NULL, return );


	if ( pSqlRes->resultcode() == 0 )
	{
		LOG_ERROR( "default", "Execute Sql For Player Login-Storage failed"  );
		return;
	}

	if( pSqlRes->rowcount() == 0 )
	{
		LOG_ERROR( "default", "[%s:%d] Execute Sql For Player Login 0 row, para1 %d, para2 %d", 
			__FUNCTION__, __LINE__, vParameter1, vParameter2  );
		return ;
	}

	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( vParameter1 );
	if ( tFindIter == mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-6", 
			__LK_FILE__, __LINE__, vParameter1 );
		return;
	}

	CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
	if( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "In CSceneLogic::OnLoadPlayerForLogin(), can't FInd EntityPlayer ObjID=%d", tFindIter->second );
		return ;
	}

	// ���뱣֤��һ������ݼ�����ɲ����½���
	if( (tpPlayer->GetLoadState() & LSSTATE_CHARPROFILE) == 0 )
	{
		LOG_ERROR( "default", "player %s's charprofile is not ready ", tpPlayer->GetCharNameShow() );
		return ;
	}

	CPropertyPlayer* tpProperty = (CPropertyPlayer*)tpPlayer->GetProperty( );

	// �ж��Ƿ����º�( �´�����ɫ��blob���� )
	if ( tpPlayer->IsNewCharacter() == false )
	{
		// ���ȼ�������Ƿ���ڣ�����ɫ�ǽ������һ�ν��룬��ɫ���ݽ�������
		if ( pSqlRes->colcount() != 1 )
		{
			//TODO: ������ݿⷵ�ص�������һ�£�ֱ��������
			LOG_ERROR("pro", "[%s:%d] data colcount %d is not match", __FUNCTION__, __LINE__, pSqlRes->colcount() );
			KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
			return ;		
		}

		PBItemBox tPBStorage;
		if( tPBStorage.ParseFromArray( pSqlRes->fieldvalue(0).c_str(), (int)pSqlRes->fieldvaluelen(0) ) == true )
		{
			//�������ʧ�ܣ�����������
			if ( tpProperty->GetStorage( )->CreateFromTlv2( &tPBStorage ) != true )
			{
				LOG_FATAL( "pro", "player %s : %d load storage blob failed", tpPlayer->GetCharNameShow(), tpPlayer->GetCharID() );
				KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
				return ;
			}
		}
		else
		{
			LOG_ERROR( "pro", "Parse PBItemBox-Storage Data Failed, Len %d", (int)pSqlRes->fieldvaluelen(0) );
			return ;			
		}

		tpPlayer->CalDetailCheckSum(pSqlRes->fieldvalue(0).c_str(), pSqlRes->fieldvaluelen(0));
	}

	tpPlayer->SetLoadState( tpPlayer->GetLoadState( ) | LSSTATE_STORAGE );
	OnLoadPlayer_Final( tpPlayer, tpPlayer->GetCharID(), vParameter2 );
}

void CSceneLogic::OnLoadPlayer_Task( CMessage* pMessage, int vParameter1, int vParameter2 )
{
	LK_ASSERT( pMessage != NULL, return );

	CMessageExecuteSqlResponse3* pSqlRes = (CMessageExecuteSqlResponse3*)pMessage->msgpara();
	LK_ASSERT( pSqlRes != NULL, return );


	if ( pSqlRes->resultcode() == 0 )
	{
        LOG_ERROR( "default", "[ %s:%d ][%s]Execute Sql For Player  Login failed", __LK_FILE__, __LINE__, __FUNCTION__  );
		return;
	}

	if( pSqlRes->rowcount() == 0 )
	{
		LOG_ERROR( "default", "[%s:%d] Execute Sql For Player Login 0 row, para1 %d, para2 %d", 
			__FUNCTION__, __LINE__, vParameter1, vParameter2  );
		return ;
	}

	int tCharID		= vParameter1;

	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( tCharID );
	if ( tFindIter == mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-7", 
			__LK_FILE__, __LINE__, tCharID );
		return;
	}

	CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
	if( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "In CSceneLogic::OnLoadPlayerForLogin(), can't FInd EntityPlayer ObjID=%d", tFindIter->second );
		return;
	}

	// ���뱣֤��һ������ݼ�����ɲ����½���
	if( (tpPlayer->GetLoadState() & LSSTATE_CHARPROFILE) == 0 )
	{
		LOG_ERROR( "default", "player %s's charprofile is not ready ", tpPlayer->GetCharNameShow() );
		return ;
	}

	// �����º�
	if ( tpPlayer->IsNewCharacter() == false ) 
	{
		// �����ºŵĻ����������ݣ�������ǳ�����
		if ( pSqlRes->colcount() != 1 )
		{
			//TODO: ������ݿⷵ�ص�������һ�£�ֱ��������
			LOG_ERROR("pro", "[%s:%d] data colcount %d is not match", __FUNCTION__, __LINE__, pSqlRes->colcount() );
			KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
			return ;
		}

		CTaskList* pList = (CTaskList*)CSceneObjManager::GetSingletonPtr( )->CreateObject( OBJTYPE_TASKLIST );	
		if ( pList == NULL ) // û��Դ��
		{
			LOG_ERROR("TASK", "not enough memroy for tasklist, charid=%d", tpPlayer->GetCharID() );
			return;
		}

		CTaskLuaInterface::Set( tpPlayer, pList );

		PBTaskList tPBTask;
		if( tPBTask.ParseFromArray( pSqlRes->fieldvalue(0).c_str(), (int)pSqlRes->fieldvaluelen(0) ) == true )
		{
			pList->CreateFromTlv2( &tPBTask );	// ��TLVBuffer�������
		}
		else
		{
			LOG_ERROR( "pro", "Parse PBTaskList Data Failed, Len %d", (int)pSqlRes->fieldvaluelen(0) );
			return ;
		}

		// ��������

		tpPlayer->SetTaskToken(pList->get_id());
		pList->SetOwnerEntityID(tpPlayer->GetEntityID());
	}

	tpPlayer->SetLoadState( tpPlayer->GetLoadState( ) | LSSTATE_TASK );
	OnLoadPlayer_Final( tpPlayer, tCharID, vParameter2 );
}



void CSceneLogic::OnLoadPlayer_Friend( CMessage* pMessage, int vParameter1, int vParameter2 )
{
	LK_ASSERT( pMessage != NULL, return );

	CMessageExecuteSqlResponse3* pSqlRes = (CMessageExecuteSqlResponse3*)pMessage->msgpara();

	if ( pSqlRes->resultcode() == 0 )
	{
        LOG_ERROR( "default", "[ %s:%d ][%s]Execute Sql For Player  Login failed", __LK_FILE__, __LINE__, __FUNCTION__  );
		return;
	}

	if( pSqlRes->rowcount() == 0 )
	{
		LOG_ERROR( "default", "[%s:%d] Execute Sql For Player Login 0 row, para1 %d, para2 %d", 
			__FUNCTION__, __LINE__, vParameter1, vParameter2  );
		return ;
	}

	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( vParameter1 );
	if ( tFindIter == mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-8",
			__LK_FILE__, __LINE__, vParameter1 );
		return;
	}

	CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
	if( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "In CSceneLogic::OnLoadPlayerForLogin(), can't FInd EntityPlayer ObjID=%d", tFindIter->second );
		return;
	}

	// ���뱣֤��һ������ݼ�����ɲ����½���
	if( (tpPlayer->GetLoadState() & LSSTATE_CHARPROFILE) == 0 )
	{
		LOG_ERROR( "default", "player %s's charprofile is not ready ", tpPlayer->GetCharNameShow() );
		return ;
	}

	CFriendItem friend_item;
	// �ж��Ƿ����º�( �´�����ɫ��blob���� )
	if ( tpPlayer->IsNewCharacter() == false )
	{
		// ���ȼ�������Ƿ���ڣ�����ɫ�ǽ������һ�ν��룬��ɫ���ݽ�������
		if ( pSqlRes->colcount() != 1 )
		{
			//TODO: ������ݿⷵ�ص�������һ�£�ֱ��������
			LOG_ERROR("pro", "[%s:%d] data colcount %d is not match", __FUNCTION__, __LINE__, pSqlRes->colcount() );
			KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
			return;
		}

		PBFriend tPBFriend;
		if( tPBFriend.ParseFromArray( pSqlRes->fieldvalue(0).c_str(), (int)pSqlRes->fieldvaluelen(0) ) == true )
		{
			friend_item.CreateFromTlv2( &tPBFriend );			// ��TLVBuffer�������
		}
		else
		{
			LOG_ERROR( "pro", "Parse PBFriendList Data Failed, Len %d", (int)pSqlRes->fieldvaluelen(0) );
			return ;	
		}
	}
	// �ǲ����ºŶ�Ҫ���� ��Ȼ����ϵͳ�޷�ʹ�ã�
	CFriendModule::GetSingleton().InsertFriendData( tpPlayer->GetCharID(), friend_item );

	tpPlayer->SetLoadState( tpPlayer->GetLoadState( ) | LSSTATE_FRIEND );
	OnLoadPlayer_Final( tpPlayer, tpPlayer->GetCharID(), vParameter2 );
}


void CSceneLogic::OnLoadPlayer_Repetion( CMessage* pMessage, int vParameter1, int vParameter2 )
{
	LK_ASSERT( pMessage != NULL, return );

	CMessageExecuteSqlResponse3* pSqlRes = (CMessageExecuteSqlResponse3*)pMessage->msgpara();

	if ( pSqlRes->resultcode() == 0 )
	{
		LOG_ERROR( "default", "Execute Sql For Player Login failed-Repetion" );
		return;
	}

	if( pSqlRes->rowcount() == 0 )
	{
		LOG_ERROR( "default", "[%s:%d] Execute Sql For Player Login 0 row, para1 %d, para2 %d", 
			__FUNCTION__, __LINE__, vParameter1, vParameter2  );
		return ;
	}

	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( vParameter1 );
	if ( tFindIter == mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-9", 
			__LK_FILE__, __LINE__, vParameter1 );
		return;
	}

	CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
	if( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "In CSceneLogic::OnLoadPlayerForLogin(), can't FInd EntityPlayer ObjID=%d", tFindIter->second );
		return;
	}

	// ���뱣֤��һ������ݼ�����ɲ����½���
	if( (tpPlayer->GetLoadState() & LSSTATE_CHARPROFILE) == 0 )
	{
		LOG_ERROR( "default", "player %s's charprofile is not ready ", tpPlayer->GetCharNameShow() );
		return ;
	}

	CPropertyPlayer* tpProperty = (CPropertyPlayer*)tpPlayer->GetProperty( );

	// �ж��Ƿ����º�( �´�����ɫ��blob���� )
	if ( tpPlayer->IsNewCharacter() == false )
	{
		// ���ȼ�������Ƿ���ڣ�����ɫ�ǽ������һ�ν��룬��ɫ���ݽ�������
		if ( pSqlRes->colcount() != 1 )
		{
			//TODO: ������ݿⷵ�ص�������һ�£�ֱ��������
			LOG_ERROR("pro", "[%s:%d] data colcount %d is not match", __FUNCTION__, __LINE__, pSqlRes->colcount() );
			KickPlayerWithoutSave( tpPlayer, EM_NOSAVE );
			return ;		
		}
		
		PBRepetion tPBRepetion;
		if( tPBRepetion.ParseFromArray( pSqlRes->fieldvalue(0).c_str(), (int)pSqlRes->fieldvaluelen(0) ) == true )
		{
			tpProperty->GetRepetion( )->PB2Repetion( &tPBRepetion, tpPlayer );		
		}
		else
		{
			LOG_ERROR( "pro", "Parse PBRepetion Data Failed, Len %d", (int)pSqlRes->fieldvaluelen(0) );	
			return;
		}
	}

	tpPlayer->SetLoadState( tpPlayer->GetLoadState( ) | LSSTATE_REPETION );
	OnLoadPlayer_Final( tpPlayer, tpPlayer->GetCharID(), vParameter2 );
}

void CSceneLogic::OnLoadPlayer_PickStoreBox( CMessage* pMessage, int nCharID, int nAccoutID )
{
    PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( nCharID );
    if ( tFindIter == mPlayerInWait.end( ) )
    {
        LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-10",
            __LK_FILE__, __LINE__, nCharID );
        return;
    }

    CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
    if( tpPlayer == NULL )
    {
        LOG_ERROR( "default", "In CSceneLogic::OnLoadPlayerForLogin(), can't FInd EntityPlayer ObjID=%d", tFindIter->second );
        return ;
    }
    tpPlayer->moYaoQianShu.OnMessageLoadPlayerPickStoreBoxInfo( pMessage, nCharID, nAccoutID );

    tpPlayer->SetLoadState( tpPlayer->GetLoadState( ) | LSSTATE_YAOQIANSHU2 );
    OnLoadPlayer_Final( tpPlayer, nCharID, nAccoutID );
}

void CSceneLogic::OnLoadPlayer_YuanBao( CMessage* pMessage, int nCharID, int nAccountID )
{
	LK_ASSERT(pMessage != NULL && pMessage->msgpara() != 0, return);
	CMessageExecuteSqlResponse3* pSqlRes = (CMessageExecuteSqlResponse3*)pMessage->msgpara();

	if ( pSqlRes->resultcode() == 0)
	{
        LOG_ERROR( "default", "[ %s:%d ][%s]Execute Sql For Player  Login failed", __LK_FILE__, __LINE__, __FUNCTION__  );
		return;
	}

	if( pSqlRes->rowcount() == 0 )
	{
		LOG_ERROR( "default", "[%s:%d] Execute Sql For Player Login 0 row, role(%d), accountid(%d)", 
			__FUNCTION__, __LINE__, nCharID, nAccountID  );
		return ;
	}

	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( nCharID );
	if ( tFindIter == mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-10",
			__LK_FILE__, __LINE__, nCharID );
		return;
	}

	CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
	if( tpPlayer == NULL )
	{
		LOG_ERROR( "default", "In CSceneLogic::OnLoadPlayerForLogin(), can't FInd EntityPlayer ObjID=%d", tFindIter->second );
		return ;
	}

	CPropertyPlayer* tpProperty = (CPropertyPlayer*)tpPlayer->GetProperty( );
	if (tpProperty == NULL)
	{
		LOG_ERROR("default", "player (%d) property is null!", nCharID);
		return;
	}

	if ( pSqlRes->colcount() != 2 )
	{
		LOG_ERROR("default", "%s load account(%d)'s YB from db error because invalid field count", __FUNCTION__, nAccountID);
		return;
	}

	tpProperty->GoldenYB().set(atoi(pSqlRes->fieldvalue(0).c_str()));
	tpPlayer->SetGmStatus((unsigned int) atoi(pSqlRes->fieldvalue(1).c_str()));

	tpPlayer->SetLoadState( tpPlayer->GetLoadState( ) | LSSTATE_YUANBAO );
	OnLoadPlayer_Final( tpPlayer, nCharID, nAccountID );
}

void CSceneLogic::OnLoadPlayer_Final( CEntityPlayer* pPlayer, int vCharID, int vCommHandle )
{
	// ���ȱ���κ�һ�����ͷ���
	if ( ( ( pPlayer->GetLoadState( ) & LSSTATE_CHARPROFILE ) != LSSTATE_CHARPROFILE ) ||
		( ( pPlayer->GetLoadState( ) & LSSTATE_PROPERTY ) != LSSTATE_PROPERTY ) ||
		( ( pPlayer->GetLoadState( ) & LSSTATE_BAGGAGE ) != LSSTATE_BAGGAGE ) ||
		( ( pPlayer->GetLoadState( ) & LSSTATE_STORAGE ) != LSSTATE_STORAGE ) ||
		( ( pPlayer->GetLoadState( ) & LSSTATE_TASK ) != LSSTATE_TASK ) ||
		( ( pPlayer->GetLoadState( ) & LSSTATE_FRIEND ) != LSSTATE_FRIEND ) ||
		( ( pPlayer->GetLoadState( ) & LSSTATE_REPETION ) != LSSTATE_REPETION ) ||
		( ( pPlayer->GetLoadState( ) & LSSTATE_YUANBAO ) != LSSTATE_YUANBAO ) ||
        ( ( pPlayer->GetLoadState( ) & LSSTATE_YAOQIANSHU1) != LSSTATE_YAOQIANSHU1) ||
        ( ( pPlayer->GetLoadState( ) & LSSTATE_YAOQIANSHU2) != LSSTATE_YAOQIANSHU2) )
	{
		// ������Ҫ���ͻ��˷���Ϣ
		return;
	}

	PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( vCharID );
	if ( tFindIter == mPlayerInWait.end( ) )
	{
		LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-11",
			__LK_FILE__, __LINE__, vCharID );
		return;
	}

	// �ı���ҵĴ�����ʽ
	pPlayer->SetCreatMethod( PLAYERCREAT_TELEPORT );
	

	// �������ͨѶ�˿�, ����ط���ֵ����
	// pPlayer->SetCommHandle( vCommHandle );

	// �жϵ�ͼ�Ƿ����
	CMapObject* tpMapObj = CMapObjManager::GetSingletonPtr( )->GetMapObject( 
			pPlayer->GetLineID(), pPlayer->GetMapID(), pPlayer->GetMapIndex());

	if ( tpMapObj == NULL)
	{
		LOG_ERROR("default", "The map line(%d) map(%d) mapindex(%d) does not exist.", 
				 pPlayer->GetLineID(), pPlayer->GetMapID(), pPlayer->GetMapIndex());

		PlayerLeaveFromGame(pPlayer);
		return;
	}

	// ����Ҵӵȴ�����ɾ��
	mPlayerInWait.erase( tFindIter );

	CMessage tMsg;
	CMessageLoginSceneResponse tMsgFact;
	CMessageHead* tpHead = tMsg.mutable_msghead();

	tpHead->set_messageid( ID_S2C_RESPONSE_LOINGSCENE );
	tMsgFact.set_csdialogid( pPlayer->get_id() );

	char tKey[ KEYLEN ] = { 0 };
	GetRandomKey( tKey, KEYLEN );

	tMsgFact.set_key(tKey,KEYLEN);
	tMsgFact.set_servertime( LINEKONG::GetTickCount() );
	tMsg.set_msgpara( (uint32)&tMsgFact );

	Send2Player( pPlayer, &tMsg );

	memcpy( pPlayer->GetKey( ), tKey, sizeof(tKey) );

	// ֪ͨ������ҽ���ȷ��

	CMessage tConfirMsg;
	CMessagePlayerEnterConfirmNotice tConfirMsgFact;
	CMessageHead* tpConfirHead = tConfirMsg.mutable_msghead();

	tpConfirHead->set_messageid( ID_S2G_PLAYER_ENTER_CONFIRM_NOTICE );
	tConfirMsgFact.set_accountid( pPlayer->GetAccountID() );
	tConfirMsgFact.set_charid( pPlayer->GetCharID() );
	tConfirMsgFact.set_charname( pPlayer->GetCharName() );
	tConfirMsgFact.set_lineid( pPlayer->GetLineID() );
	tConfirMsgFact.set_mapid( pPlayer->GetMapID() );
	tConfirMsgFact.set_face( pPlayer->GetFaceType() );
	tConfirMsgFact.set_metier( pPlayer->GetMetier() );
	tConfirMsgFact.set_sex( pPlayer->GetSex() );
	tConfirMsgFact.set_level( pPlayer->GetLevel() );
	tConfirMsgFact.set_nationality( pPlayer->GetNationality() );
	tConfirMsg.set_msgpara( (uint32)&tConfirMsgFact );
	tConfirMsgFact.set_cskey(tKey, sizeof(tKey));

	Send2Gate( &tConfirMsg );

	// �������ʵ��( �����µ�½�Ϳ����½ )
	CreateEntity( pPlayer, NULL, pPlayer->GetCommState() == CEntityPlayer::STATE_INWAIT ? true : false );	

	LOG_NOTICE( "default", "Account[%d]Use Charactor[%s] Charid %d Enter Into Game, state %d, socket(%d), socktime(%d)", 
		pPlayer->GetAccountID(), pPlayer->GetCharNameShow(), vCharID, pPlayer->GetCommState(), pPlayer->GetCommHandle(), pPlayer->GetClientInfo()->mSockTime );

	pPlayer->SetCommState( CEntityPlayer::STATE_INMAP );	

	// ��������ʱ�������ģ�ǿ�Ƹ���
	if ( pPlayer->GetAliveStatus( ) == ALIVE_DIE )
	{
		CPropertyModule::GetSingletonPtr()->PlayerRelive( pPlayer, RELIVE_WEAKGRAVE, 0, 0 );
	}
	
	// �ı���ҵĴ�����ʽ
	pPlayer->SetCreatMethod( PLAYERCREAT_MOVE );

	// ��ȫ��½�������ٸ��ͻ��˷��ͼ�������ʱ
	CPropertyModule::GetSingleton().OnEventNotifyPrisonTime( pPlayer );


	// ��������ȡ��Ϣ
	CWorldModule::GetSingleton().SendPlayInfoM2SRequest( pPlayer, NULL );


	// ֻҪ���벻����ʱ�䣬��������
	if( pPlayer->GetFcmStatus() != em_normal_rate )
	{
		SceneServer::CSceneLogic::GetSingletonPtr()->KickPlayer( pPlayer->GetCharID(), EM_KICKOUT_ANTIADDICTION );
	}

}

void CSceneLogic::Send2GMServer( CMessage* pMessage )
{

	CProxyHead tProxyHead;

	BYTE buffer[ MAX_CODE_LEN ];
	unsigned short len = sizeof(buffer);

	LK_ASSERT(pMessage != NULL, return);


	pbmsg_setproxy(&tProxyHead, CET_GAMESERVER, CET_OTHERSERVER, 
			CSceneServer::GetSingleton().mThisServerID, 1, TRANS_P2P, CMD_NULL);

	pMessage->mutable_msghead()->set_srcfe(FE_SCENCESERVER);
	pMessage->mutable_msghead()->set_srcid(CSceneServer::GetSingleton().mThisServerID);

	len = pbmsg_setmsg<CProxyHead>( tProxyHead, *pMessage, (char*)buffer, len );

	if( len <= 0 )
	{
		LOG_ERROR( "default", "Serialize for router message failed. %d", len );
		return ;
	}

	char tszMessageid[16] = {0};
	snprintf( tszMessageid, sizeof(tszMessageid)-1, "%d->gm", pMessage->mutable_msghead()->messageid() );
	PERF_FUNC( tszMessageid, ; );

#ifdef _DEBUG_
	Message* pUnknownMessagePara = (Message*) pMessage->msgpara();
	LK_ASSERT( pUnknownMessagePara != NULL, return  );
	const ::google::protobuf::Descriptor* pDescriptor= pUnknownMessagePara->GetDescriptor();

	LOG_DEBUG("default", "Send2Login: MsgName[%s] ProxyHead[%s] MsgHead[%s] MsgPara[%s]",
			pDescriptor->name().c_str(),    tProxyHead.ShortDebugString().c_str(),
			pMessage->ShortDebugString().c_str(), pUnknownMessagePara->ShortDebugString().c_str());
#endif

	int nRet =CSceneServer::GetSingletonPtr( )->mProxyClient.GetSocket()->SendOneCode( len, (BYTE*)buffer );
	if( nRet < 0 )
	{
		LOG_ERROR( "default", "[%s:%d] send 2 gmserver len=%d failed %d", __FUNCTION__, __LINE__, len, nRet );
	}
}

void CSceneLogic::CalcCurrentDay( )
{
	time_t tval;
	struct tm *now;        
	time(&tval);
	now = localtime(&tval);
	mCurrentDay = ( now->tm_year - 100 ) * 1000 + now->tm_yday;
}

int CSceneServer::SaveAllPlayer( int vSaveCode )
{
	CSceneObjManagerImp* pSceneneObjManagerImp = CSceneObjManager::GetSingletonPtr()->mSceneObjManagerImp;

	for( CSceneObjManagerImp::ObjMng_EntityPlayer::iterator tPlayerIt = 
			pSceneneObjManagerImp->mEntityPlayerPool.begin( );          
			tPlayerIt != pSceneneObjManagerImp->mEntityPlayerPool.end( );
			tPlayerIt++
	   )
	{   
		CEntityPlayer* tpSrcEntity = &( *tPlayerIt );
		CSceneLogic::GetSingletonPtr( )->SavePlayer( tpSrcEntity, vSaveCode );
	}

	return SUCCESS;
}

// �õ��������������
int CSceneLogic::GetPlayersInScene(std::vector<CEntityPlayer*>& rPlayers)
{
	for( PLAYERID_MAP::iterator it = mPlayerContainer.begin(); it != mPlayerContainer.end(); ++it )
	{
		CEntityPlayer* pPlayer = (CEntityPlayer*)GetEntity( it->second );
		LK_ASSERT( pPlayer != NULL, continue );
		rPlayers.push_back( pPlayer );
	}
	return 0;
}

// ����������־Ŀ¼
int CSceneLogic::CreatPlayerLog( )
{
	const char *pLogName = "../log/playerlog"; 	
	return CreatDir( pLogName, 0700 );
}

// ��֤�ͻ��˷�����Ϣ��Ƶ��
bool CSceneLogic::CheckMsgFrequency( CEntityPlayer *pPlayer )
{		
	LK_ASSERT( pPlayer != NULL, return false )	  	
	int tMsgLimitPerSec = CSceneCfgManager::GetSingleton().GetScenelogic_cfg()->mMsglimitpersec;  
	int tMsgCountLimit = CSceneCfgManager::GetSingleton().GetScenelogic_cfg()->mMsgcheckcountlimit;	  
	return pPlayer->CheckMsgFrequency( tMsgLimitPerSec, tMsgCountLimit );
}

int CSceneLogic::ReadConfig()
{
	return 0;
}

int CSceneServer::OnMessageCreateRepetion( CMessage* vpMessage )
{
#ifdef _FB_
	int tRtn = SUCCESS;
	CMessageCreateRepetionNotify* tpMsg = ( CMessageCreateRepetionNotify* )vpMessage->msgpara( );

//	CMapObject* tpMapObj = CMapObjManager::GetSingletonPtr( )->GetMapObject( tpMsg->lineid( ), tpMsg->mapid( ),
//		INVALID_MAP_INDEX, tpMsg->key( ) );

//	LOG_INFO( "default", "[ %s : %d ][ %s ] Create Repetion Map( %d : %lld ) Begin", __LK_FILE__, __LINE__, 
//		__FUNCTION__, tpMsg->mapid( ), tpMsg->key( ) );

//	if( tpMapObj == NULL )
//	{

//		tpMapObj = CMapObjManager::GetSingletonPtr( )->CreateMap( tpMsg->lineid( ), tpMsg->mapid( ), INVALID_MAP_INDEX,
//					"worldscene", tpMsg->key( ) );

//		if( tpMapObj == NULL )
//		{
//			LOG_ERROR( "default", "[ %s : %d ][ %s ] Cannt Create Repetion Map( %d : %lld ) " ,  __LK_FILE__, __LINE__, 
//				__FUNCTION__, tpMsg->mapid( ), tpMsg->key( ) );
//			tRtn = ERR_REPETION_CREATE_FULL;
//		}
//	}
//	else
//	{
//		LOG_ERROR( "default", "[ %s : %d ][ %s ] Create Repetion Map( %d : %lld ) Is Exist", __LK_FILE__, __LINE__,
//			__FUNCTION__, tpMsg->mapid( ), tpMsg->key( ) );
//		tRtn = ERR_REPETION_CREATE_EXIST;
//	}

	LOG_INFO( "default", "[ %s : %d ][ %s ] Create Repetion( %d : %lld ) Begin", __LK_FILE__, __LINE__, __FUNCTION__,
		tpMsg->repetionindex( ), tpMsg->key( ) );

	CRepetion* tpRepetion = CRepetionModule::GetSingletonPtr( )->CreateRepetion( tpMsg->repetionindex( ), 
		tpMsg->lineid( ), tpMsg->key( ), tpMsg->creator( ), tpMsg->removeitem( ) ,tpMsg->parame1(), tpMsg->parame2());


	if( tpRepetion == NULL )
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ] Cannt Create Repetion( %d : %lld )", __LK_FILE__, __LINE__,
			__FUNCTION__, tpMsg->repetionindex( ), tpMsg->key( ) );
		CMessage tMsg;
		CMessageCreateRepetionErr tErr;

		tErr.set_repetionindex( tpMsg->repetionindex( ) );
		tErr.set_key( tpMsg->key( ) );
		tErr.set_errcode( ERR_REPETION_CREATE_FULL );

		tMsg.set_msgpara( ( uint32_t ) &tErr );
		pbmsg_sethead( &tMsg, ID_S2G_CREATE_REPETION_ERR, 0, 0, 0, 0, 0, 0 );
		
		CSceneLogic::GetSingletonPtr( )->Send2Gate( &tMsg );
	}
	else
	{
		LOG_INFO( "default", "[ %s : %d ][ %s ] Create Repetion( %d : %d : %lld ) SUCCESS", __LK_FILE__, __LINE__,
			__FUNCTION__, tpRepetion->GetRepetionIndex( ), tpRepetion->get_id( ), tpRepetion->GetKey( ) );
	}


	LOG_INFO( "default", "[ %s : %d ][ %s ] Create Repetion( %d : %lld ) End", __LK_FILE__, __LINE__, 
		__FUNCTION__, tpMsg->repetionindex( ), tpMsg->key( ) );

	return tRtn;
#endif
	return SUCCESS;
}


bool CSceneLogic::LoadPlayerInfo( int vAccountID, int vPlayerCharID, int nDesGameID /* = 0 */ )
{
	int nSessionID = 0;
	CSession* pSession= (CSession*) CSceneObjManager::GetSingletonPtr()->CreateObject( OBJTYPE_SESSION );
	if( pSession == NULL) return false;
	nSessionID = pSession->get_id();
	pSession->assign( nSessionID, loadplayerforlogin_charprofile, vPlayerCharID, 0 );

	CMessageLoadPlayerInfoRequest msg;
	

	msg.set_sessionid(nSessionID);
	msg.set_roleid( vPlayerCharID );

	return SendMsg2Data( &msg, vAccountID, ID_S2D_LOADPLAYERINFO_REQUEST, nDesGameID );

}
bool CSceneLogic::LoadPlayerProperty( int nAccountID, int vPlayerCharID, int nDesGameID /* = 0 */ )
{
	int nSessionID = 0;
	CSession* pSession= (CSession*) CSceneObjManager::GetSingletonPtr()->CreateObject( OBJTYPE_SESSION );
	if( pSession == NULL) return false;
	nSessionID = pSession->get_id();
	pSession->assign( nSessionID, loadplayer_property_all, vPlayerCharID, 0 );


	CMessageLoadPlayerPropertyRequest msg;

	msg.set_detailid( nAccountID % 16 );
	msg.set_sessionid(nSessionID);
	msg.set_roleid( vPlayerCharID );

	return SendMsg2Data( &msg, nAccountID, ID_S2D_LOADPLAYERPROPERTY_REQUEST, nDesGameID );

}
bool CSceneLogic::SavePlayerProperty( CEntityPlayer* vpPlayer, int vSaveCode, int vCallBack )
{
	LK_ASSERT( vpPlayer != NULL, return false );	
	
	// ������Ƕ�ʱ�������ۼ���Ч����ʱ��
	if ( vSaveCode != SAVE_TIMETRIGER  )
	{
		CPropertyPlayer *tpProperty = ( CPropertyPlayer * )vpPlayer->GetProperty();
		tpProperty->GetExpTimeInfo()->AddEffectiveOffTimeLength( vpPlayer->GetLoginTime(), tpProperty->IsVip() );
	}	

	CMessageSavePlayerRequest tSaveRequest;

	if( CModuleManager::GetSingletonPtr( )->FillData( vpPlayer, vSaveCode ) == false )
	{
		LOG_ERROR("default", "[%s:%d][%s] Save role(%d:%s) failure, save code(%d)",
			__LK_FILE__, __LINE__, __FUNCTION__, vpPlayer->GetCharID(), vpPlayer->GetCharNameShow(), vSaveCode);
		return false;
	}

	int nSessionID = 0;
	if ( vCallBack & SQL_NEED_CALLBACK )
	{
		CSession* pSession= (CSession*) CSceneObjManager::GetSingletonPtr()->CreateObject( OBJTYPE_SESSION );
		if( pSession == NULL) return false;
		nSessionID = pSession->get_id();
		pSession->assign( nSessionID, saveplayer_property_all, vSaveCode, vpPlayer->get_id( ) );
	}

	tSaveRequest.set_detailid( vpPlayer->GetAccountID() % 16 );
	tSaveRequest.set_callback( vCallBack );
	tSaveRequest.set_roleid( vpPlayer->GetCharID( ) );
	tSaveRequest.mutable_property( )->CopyFrom( *GetSavePlayerProperty( ) );
	tSaveRequest.set_sessionid( nSessionID );

	if( vSaveCode == SAVE_FILE )
	{
		std::vector<std::string> tmp;
		Save2File( saveplayer_property_all,	vpPlayer->GetCharID( ),	&tSaveRequest, "saveplayer_property_all", tmp, vpPlayer->GetAccountID());
		return true;
	}

	return SendMsg2Data( &tSaveRequest, vpPlayer->GetAccountID( ), ID_S2D_SAVEPLAYER_REQUEST, vpPlayer->GetRoleWorldID() );
}

bool CSceneLogic::SavePlayerInfo( CEntityPlayer* vpPlayer, int vSaveCode, int vCallBack )
{
	LK_ASSERT( vpPlayer != NULL, return false );

	CMessageSavePlayerRequest tSaveRequest;
	CMessagePlayerInfo tInfo;

	int nSessionID = 0;
	if ( vCallBack & SQL_NEED_CALLBACK )
	{
		CSession* pSession= (CSession*) CSceneObjManager::GetSingletonPtr()->CreateObject( OBJTYPE_SESSION );
		if( pSession == NULL) return false;
		nSessionID = pSession->get_id();
		pSession->assign( nSessionID, saveplayer_charprofile, vSaveCode, vpPlayer->get_id( ) );
	}	

	tInfo.set_metier_id( vpPlayer->GetMetier( ) );
	tInfo.set_nationality_id( vpPlayer->GetNationality( ) );
	tInfo.set_line_id( vpPlayer->GetLineID( ) );
	tInfo.set_map_id( vpPlayer->GetMapID( ) );	
	tInfo.set_role_level( vpPlayer->GetLevel( ) );
	tInfo.set_role_expr( ((CPropertyPlayer*)vpPlayer->GetProperty())->GetExp( ) );
	tInfo.set_role_money( ((CPropertyPlayer*)vpPlayer->GetProperty())->GetMoney() );
	tInfo.set_bounded_money( ((CPropertyPlayer*)vpPlayer->GetProperty())->GetBindMoney( ) );
	tInfo.set_pos_x( vpPlayer->GetPosX() );
	tInfo.set_pos_y( vpPlayer->GetPosY() );
	tInfo.set_is_alive( vpPlayer->GetAliveStatus() );
	tInfo.set_online_duration( vpPlayer->GetOnlineTime() + (time( NULL ) - vpPlayer->GetLastLoginTime()) );

	tInfo.set_login_time( vpPlayer->GetLastLoginTime() );
	
	tInfo.set_save_status( vSaveCode );
	tInfo.set_save_bitflag( LSSTATE_CHARPROFILE );
	tInfo.set_check_sum( vpPlayer->CalProfileCheckSum() );
	tInfo.set_country_id( vpPlayer->GetCountryID() );
	tInfo.set_role_status_param( vpPlayer->GetRoleStatusParam() );
	tInfo.set_role_familyid( vpPlayer->GetFamilyID() );
	tInfo.set_role_corpsid( vpPlayer->GetCorpsID() );
	tInfo.set_storage_money( ((CPropertyPlayer*)vpPlayer->GetProperty())->GetStorageMoney() );
	tInfo.set_storage_bounded_money( ((CPropertyPlayer*)vpPlayer->GetProperty())->GetStorageBindMoney() );
	tInfo.set_role_protecttime( ((CPropertyPlayer*)vpPlayer->GetProperty())->GetRolePassword()->GetProtectTimeLength() );
	tInfo.set_role_password( ((CPropertyPlayer*)vpPlayer->GetProperty())->GetRolePassword()->GetPassword() );

	tInfo.set_role_vip_flag(  ((CPropertyPlayer*)vpPlayer->GetProperty())->GetVipFlag() );
	tInfo.set_role_vip_time( ((CPropertyPlayer*)vpPlayer->GetProperty())->GetVipTime() );
	tInfo.set_role_marriageid( vpPlayer->GetMarriageID() );
	tInfo.set_role_changecamp_time(vpPlayer->GetChangeCampTime());
	tInfo.set_role_status( vpPlayer->GetRoleStatus() );

	// �����ȫ�ַ�������������Ϊ���ִ�,�����¼���غ��޷����볡��
	if ( vSaveCode == SAVE_LEAVEGAME || vSaveCode == SAVE_RETURN2GATE || vSaveCode == SAVE_KICKOUT )
	{
		if ( IS_DUNGEONSERVER_LINE( GetLineID() ) == true  )
		{
			// ������ִ�ĵ�ͼ
			// ��¼ԭʼ����
			CPlayerRepetion* tpPlayerRepetion = ( ( CPropertyPlayer* )vpPlayer->GetProperty( ) )->GetRepetion( );
			tInfo.set_pos_x( tpPlayerRepetion->GetPosX() );
			tInfo.set_pos_y( tpPlayerRepetion->GetPosY() );
			tInfo.set_line_id( tpPlayerRepetion->GetBackLineID() );
			tInfo.set_map_id( tpPlayerRepetion->GetBackMapID( ) );				
		}
		else if ( IS_GLOBAL_SCENESERVER( GetLineID() ) == true )
		{
			CTemplateGlobalMapConfig *tpGlobalConfig = ( CTemplateGlobalMapConfig * )CDataStatic::GetTemp( TEMP_GLOBALMAPCONFIG );
			if ( tpGlobalConfig != NULL )
			{
				tInfo.set_pos_x( tpGlobalConfig->mOutX );
				tInfo.set_pos_y( tpGlobalConfig->mOutY );
				tInfo.set_line_id( vpPlayer->GetNationality() );
				tInfo.set_map_id(  tpGlobalConfig->mOutMap );	
			}
		}
	}	
	tInfo.set_role_swornid( vpPlayer->GetSwornID() );
	tSaveRequest.set_roleid( vpPlayer->GetCharID( ) );
	tSaveRequest.mutable_info( )->CopyFrom( tInfo );
	tSaveRequest.set_sessionid( nSessionID );
	tSaveRequest.set_callback( vCallBack );	
	tSaveRequest.set_detailid( vpPlayer->GetAccountID() % 16 );	
	
	if( vSaveCode == SAVE_FILE )
	{
		std::vector<std::string> tmp;
		Save2File( saveplayer_charprofile,	vpPlayer->GetCharID( ),	&tSaveRequest, "saveplayer_charprofile", tmp, vpPlayer->GetAccountID() );
		return true;
	}

	return SendMsg2Data( &tSaveRequest, vpPlayer->GetAccountID( ), ID_S2D_SAVEPLAYER_REQUEST, vpPlayer->GetRoleWorldID() );
}

bool CSceneLogic::SendMsg2Data( google::protobuf::Message* vpMsg, int Uid, int vMsgID, int nDesGameID /* = 0 */ )
{
	CMessage   tMessage;
	CProxyHead tProxyHead;

	tMessage.set_msgpara( (uint32_t) vpMsg );
	pbmsg_sethead(&tMessage, vMsgID, 0, 0, FE_SCENCESERVER, FE_DATASERVER, 
		CSceneServer::GetSingleton().mThisServerID, 1);
	tProxyHead.set_srcfe( CET_GAMESERVER );
	tProxyHead.set_dstfe( CET_DBSERVER );
	tProxyHead.set_srcid( CSceneServer::GetSingleton().mThisServerID );
	tProxyHead.set_dstid( 1 ); // TODO: ��ʱд�������ݿ������Ŀǰֻ��1̨
	// �� charid ����dbsvrd����ִ���̵߳�key����֤һ��������в�������һ���߳�ִ��
	tProxyHead.set_uin( Uid );
	
	// ����Դ��ϷID��Ŀ����ϷID
	tProxyHead.set_srcgameid( GetWorldID() );
	tProxyHead.set_desgameid( nDesGameID );

	BYTE message_buffer[ PLAYER_DATALEN ] = {0};
	int message_length = pbmsg_setmsg<CProxyHead>(tProxyHead, tMessage, (char*)message_buffer, sizeof(message_buffer));      

	if (message_length > 0)        
	{
		int nRet = Send2Data( message_buffer, message_length ) ;
		if( nRet < 0 )
		{
			LOG_ERROR( "default", "[%s:%d] player %d send 2 data failed %d", __FUNCTION__, __LINE__, 
				Uid, nRet );
		}
//		return true;
	}
	else                                                                                             
	{                                                                                                 
		LOG_ERROR("default", "pbmsg_setmsg encoding message (%x) error", tMessage.msghead().messageid());
		return false;
	} 

#ifdef _DEBUG_
	const ::google::protobuf::Descriptor* pDescriptor= vpMsg->GetDescriptor();
    LOG_DEBUG("default", "Send2Data: MsgName[%s] ProxyHead[%d:%s] MsgHead[%s] MsgPara[%s]",
    	pDescriptor->name().c_str(),  tProxyHead.ByteSize(),  tProxyHead.ShortDebugString().c_str(),
        tMessage.ShortDebugString().c_str(), vpMsg->ShortDebugString().c_str());
#endif

	return true;

}

int CSceneServer::OnMessageSceneGMMove( CMessage* vpMsg )
{
	CMessageSceneEntityGMMove* tpMsg = ( CMessageSceneEntityGMMove* )vpMsg->msgpara( );

	CEntityPlayer* vpPlayer = ( CEntityPlayer* )CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( tpMsg->roleid( ) );

	if( vpPlayer != NULL )
	{
		if( vpPlayer->IsAlive() == false )
		{
			CPropertyModule::GetSingletonPtr( )->PlayerRelive( vpPlayer, RELIVE_SYSTEM, 100, 100 );
		}
		
		CMapModule::GetSingletonPtr( )->Teleport( tpMsg->lineid( ), tpMsg->mapid( ), tpMsg->posx( ), tpMsg->posy( ),
			vpPlayer, 0, tpMsg->key( ) );
	}
	else
	{
		LOG_ERROR( "default", "[ %s : %d ][ %s ] Cannt Find Player, roleid %d", __LK_FILE__, __LINE__, __FUNCTION__,
			tpMsg->roleid( ) );
	}
	
	return SUCCESS;
}		 

int CSceneServer::OnMessageRoleMove( CMessage* vpMsg )
{
	CMessageG2SRoleMove* tpMsg = ( CMessageG2SRoleMove* )vpMsg->msgpara( );

	CEntityPlayer* tpPlayer = CSceneLogic::GetSingletonPtr( )->GetPlayerByName( tpMsg->desrole( ).c_str( ) );

	if( tpPlayer != NULL )
	{
		CMapObject* tpMapObj = tpPlayer->GetMapObject( );
		
		if( tpMapObj != NULL )
		{
			CMessageGateEntityGMMove tMove;
			CMessage        tMsg;

			tMove.set_rolename( tpMsg->srcrole( ).c_str( ) );
			tMove.set_lineid( tpMapObj->GetLineID( ) );
			tMove.set_mapid( tpMapObj->GetMapID( ) );
			tMove.set_posx( tpPlayer->GetPosX( ) );
			tMove.set_posy( tpPlayer->GetPosY( ) );
			tMove.set_key( tpMapObj->GetKey( ) );

			tMsg.mutable_msghead( )->set_messageid( ID_S2G_ENTITY_GM_MOVE );
			tMsg.set_msgpara( (uint32)&tMove );

			CSceneLogic::GetSingletonPtr()->Send2Gate( &tMsg );	
		}
	}

	return SUCCESS;	
}

// ���ط��͵���������������Ϣ
void CSceneServer::OnMessageResetPlayerPassword( CMessage* vpMsg )
{	
	LK_ASSERT( vpMsg != NULL, return )	
		CMessageResetRolePasswordNotify *tpMsg = ( CMessageResetRolePasswordNotify * )vpMsg->msgpara();
	LK_ASSERT( tpMsg != NULL, return )
		CEntityPlayer *tpPlayer = CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( tpMsg->roleid( ) );
	LK_ASSERT( tpPlayer != NULL, return )
		CPropertyPlayer *tpProperty = ( CPropertyPlayer * )tpPlayer->GetProperty();
	tpProperty->GetRolePassword()->ClearPassword();
}



// ֪ͨ���ط���ȫ�ر�
int CSceneServer::SendShutdownAck( )
{
	LOG_NOTICE( "default", "game shut down ok. now ack to gate" );

	CMessage tMessage;
	CMessgeSafeShutdownAck tSafeShutdownAck;

	tSafeShutdownAck.set_serverid( mThisServerID );

	tMessage.mutable_msghead()->set_messageid( ID_S2G_ACK_SAFE_SHUTDOWN );
	tMessage.set_msgpara( (uint32)&tSafeShutdownAck );

	CSceneLogic::GetSingletonPtr()->Send2Gate( &tMessage );	
	return 0;
}


void CSceneLogic::LogValuableEquip(int nRoleID, CItemObject* pItem)
{
	if (pItem == NULL) return;

	CTplItem *ptpl = (CTplItem *) CDataStatic::SearchTpl(pItem->GetItemID());
	if (ptpl == NULL) return;	

	if (ptpl->mItemType != ITEM_WEAPON &&  ptpl->mItemType != ITEM_ARMOR
			&&  ptpl->mItemType != ITEM_FASHION &&  ptpl->mItemType != ITEM_MAGICWEAPON)
	{
		return;
	}

	CMessageSavePlayerItemInfoRequest logmsg;
	logmsg.set_charid(nRoleID);
	logmsg.add_packageidx(0);

	PBItemBox* pItemBox = logmsg.add_itembox();
	if ( pItemBox )
	{
		PBItemObject* ppbItem = pItemBox->add_itemobjects();
		if ( ppbItem )
		{
			pItem->GetItemBinaryBuffer2(ppbItem, 1);

			CMessage tMessage;
			tMessage.set_msgpara( (int)&logmsg );
			tMessage.mutable_msghead()->set_messageid( ID_S2D_SAVEPLAYERITEMINFO_REQUEST);

			Send2Log(&tMessage, ID_S2D_SAVEPLAYERITEMINFO_REQUEST, nRoleID); 
		}
	}
}


// ��������֪ͨ�رշ�����
int CSceneServer::OnMessageShutdownNotify( CMessage* pMsg )
{
	LOG_NOTICE( "default", "recv gate notice shutdown server" );
	CSceneLogic::GetSingletonPtr()->SetServerStatus( EM_SERVERSTATUS_SHUDOWNING );
	return 0;
}




void SceneServer::CSceneLogic::LoadPlayerYaoQianShuInfoFromDB( int nAccountID, int nCharID )
{
    int liActiviyId = CActivityYqs::GetSingleton().GetActivtyId();
    int liSettlePhase = CActivityYqs::GetSingleton().GetSettlePhase();

    LOG_ERROR( "YaoQianShu", "[ %s:%d ][ %s ] Start LoadPlayerYaoQianShuInfoFromDB "
        "AccoutId(%d) CharId(%d) ActivityId(%d) SettlePhase(%d)", 
        __LK_FILE__, __LINE__, __FUNCTION__, nAccountID, nCharID, liActiviyId, liSettlePhase );

    // �����ݿ��в�ѯ�û�
    bool lbRet = CSceneLogic::GetSingletonPtr()->ExecuteSql( 
        session_yaoqianshu_loadplayerinfo, 
        nCharID, nAccountID,nCharID, SQL_NEED_CALLBACK, SELECT, 
        "select * from UMS_ACTIVITY_YQS_USERINFO where PlayerId=%d and AcitivityIndex=%d;", 
        nCharID, liActiviyId );
    if ( lbRet == false )
    {
        LOG_ERROR( "YaoQianShu", "[ %s:%d ][ %s ] LoadPlayerYaoQianShuInfoFromDB for "
            "AccoutId(%d) CharId(%d) ActivityId(%d) SettlePhase(%d) failed", 
            __LK_FILE__, __LINE__, __FUNCTION__, nAccountID, nCharID, liActiviyId, liSettlePhase );
    }
  

    LOG_ERROR( "YaoQianShu", "[ %s:%d ][ %s ] Finish LoadPlayerYaoQianShuInfoFromDB "
        "AccoutId(%d) CharId(%d) ActivityId(%d) SettlePhase(%d)", 
        __LK_FILE__, __LINE__, __FUNCTION__, nAccountID, nCharID, liActiviyId, liSettlePhase );
    return;
}

void SceneServer::CSceneLogic::LoadPlayerPickStoreBoxFromDB( int nAccountID, int nCharID )
{
    int liActiviyId = CActivityYqs::GetSingleton().GetActivtyId();
    int liSettlePhase = CActivityYqs::GetSingleton().GetSettlePhase();

    LOG_NOTICE( "YaoQianShu", "[ %s:%d ][ %s ] Start LoadPlayerPickStoreBoxFromDB "
        "AccoutId(%d) CharId(%d) ActiviyId(%d) SettlePhase(%d)", 
        __LK_FILE__, __LINE__, __FUNCTION__, nAccountID, nCharID,liActiviyId,liSettlePhase );

    bool lbRet = CSceneLogic::GetSingletonPtr()->ExecuteSql( 
        session_yaoqianshu_loadplayerpick, 
        nCharID, nAccountID,nCharID, SQL_NEED_CALLBACK, SELECT, 
        "select * from UMS_ACTIVITY_YQS_STOREBOXINFO where PlayerId=%d and ActivityIndex=%d and SettlePhase=%d;",
        nCharID, liActiviyId, liSettlePhase );
    if ( lbRet == false )
    {
        LOG_ERROR( "YaoQianShu", "[ %s:%d ][ %s ] LoadPlayerPickStoreBoxFromDB for "
            "AccoutId(%d) CharId(%d) ActivityId(%d) SettlePhase(%d) failed", 
            __LK_FILE__, __LINE__, __FUNCTION__, nAccountID, nCharID, liActiviyId, liSettlePhase );

    }
    

    LOG_NOTICE( "YaoQianShu", "[ %s:%d ][ %s ] Finish LoadPlayerPickStoreBoxFromDB "
        "AccoutId(%d) CharId(%d) ActiviyId(%d) SettlePhase(%d)", 
        __LK_FILE__, __LINE__, __FUNCTION__, nAccountID, nCharID,liActiviyId,liSettlePhase );
    return;
}

void CSceneLogic::OnLoadPlayer_YaoQianShu( CMessage* pMessage, int nCharID, int nAccoutID )
{
    PLAYERID_MAP::iterator tFindIter = mPlayerInWait.find( nCharID );
    if ( tFindIter == mPlayerInWait.end( ) )
    {
        LOG_ERROR( "default", "[%s:%d]player(charid %d) is not in waiting queue-10",
            __LK_FILE__, __LINE__, nCharID );
        return;
    }

    CEntityPlayer* tpPlayer = (CEntityPlayer*) CSceneObjManager::GetSingletonPtr()->GetObject( tFindIter->second );
    if( tpPlayer == NULL )
    {
        LOG_ERROR( "default", "In CSceneLogic::OnLoadPlayer_YaoQianShu(), can't FInd EntityPlayer ObjID=%d", tFindIter->second );
        return ;
    }
   tpPlayer->moYaoQianShu.OnMessageLoadPlayerInfo( pMessage, nCharID, nAccoutID );

    tpPlayer->SetLoadState( tpPlayer->GetLoadState( ) | LSSTATE_YAOQIANSHU1 );
    OnLoadPlayer_Final( tpPlayer, nCharID, nAccoutID );
}


//��ȡ config �����ļ���Ŀ¼
const char* CSceneLogic::GetConfigDataFileNamePath(int nGameID, const char * filename)
{
	memset(mConfigtmpbuf,0,1024);
	snprintf(mConfigtmpbuf, 1024, "../config/data_%d/%s",nGameID,filename);
	FILE* file = fopen( mConfigtmpbuf, "rb" );	
	if ( file )
	{
		return mConfigtmpbuf;
	}
	else
	{
		memset(mConfigtmpbuf,0,1024);
		snprintf(mConfigtmpbuf, 1024, "../config/data/%s",filename);
	}
	return mConfigtmpbuf;


}

//���� �ͻ�������ת��Ӫ
void CSceneServer::OnMessageInviteCamp( CEntityPlayer* pPlayer,CMessage* pMessage)
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageInviteCampRequest *tpMsg =  ( CMessageInviteCampRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );	
	//�ж��Ƿ��Ǳ��� 

	////�ж�npc����
	CEntityNpc* pNpc = dynamic_cast< CEntityNpc* >( CSceneObjManager::GetSingletonPtr( )->GetObject( 
		tpMsg->npcid() ));
	if( pNpc == NULL )
	{
		 CPropertyModule::GetSingletonPtr()->SendProErrorNotice( pPlayer, ERROR_MW_NPCINVALID );
		return ;
	}
	if( !pPlayer->IsWithinDistance( pNpc, MAX_NPC_TALK_GIRD) ) // �ںϷ�����֮�ڲ��ж�
	{
		 CPropertyModule::GetSingletonPtr()->SendProErrorNotice( pPlayer, ERROR_MW_NPCINVALID );
		return;
	}
	//��gateҪ ��ת��Ӫ�б���ͻ���
	CMessage tMsg;
	CMessageInviteCampRequest tInviteMsg;
	tInviteMsg.set_playerid(pPlayer->GetCharID());
	tMsg.mutable_msghead()->set_messageid( ID_C2S_REQUEST_INVITE_CAMP);
	tMsg.set_msgpara((uint32_t) &tInviteMsg);

	CSceneLogic::GetSingletonPtr()->Send2Gate( &tMsg );


}

//���� �ͻ���ת��Ӫ��Ϣ
void CSceneServer::OnMessageChangeSingleCamp(CEntityPlayer* pPlayer,CMessage* pMessage)
{

	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageChangeSingleCampRequest *tpMsg =  ( CMessageChangeSingleCampRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );	


	//�ж��Ƿ����
	CPropertyPlayer* pProperty = (CPropertyPlayer*) pPlayer->GetProperty();	
	if (pProperty == NULL)
	{
		return;
	}
	//�ж�npc ����
	CEntityNpc* pNpc = dynamic_cast< CEntityNpc* >( CSceneObjManager::GetSingletonPtr( )->GetObject( 
		tpMsg->npcid() ));
	if( pNpc == NULL )
	{
		 CPropertyModule::GetSingletonPtr()->SendProErrorNotice( pPlayer, ERROR_MW_NPCINVALID );
		return ;
	}
	if( !pPlayer->IsWithinDistance( pNpc, MAX_NPC_TALK_GIRD) ) // �ںϷ�����֮�ڲ��ж�
	{
		 CPropertyModule::GetSingletonPtr()->SendProErrorNotice( pPlayer, ERROR_MW_NPCINVALID );
		return;
	}
	//�Ƿ� �ﵽ�ȼ���30��
	if (pPlayer->GetLevel()< CHANGE_CAMP_LEVEL )
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_NO_ENOUGH_LEVEL);
		return;
	}
	//�ж��Ƿ���ת��Ӫ����	
	CTemPlateChangeCampCfg *tpConfig = (CTemPlateChangeCampCfg*)CDataStatic::GetTemp( TEMP_CHANGECAMP );
	if ( tpConfig == NULL )
		 return;
	int  haveitem = 0;
	CPropertyModule::GetSingletonPtr()->HasItem(  pPlayer->GetEntityID() ,tpConfig->m_itemId, 1 , haveitem, 0 );
	if ( haveitem == 0 )
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_NO_HAVE_ITEM);
		return;
	}

	//�ж��Ƿ���ת��Ӫcd
	time_t curtimr = time(0);
	if (pPlayer->GetChangeCampTime() >0 && (curtimr - pPlayer->GetChangeCampTime()) < (int)(tpConfig->m_cd_time * 24 * 3600))
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_CD);
		return;
	}

	//�Ƿ���ԭʼ��Ӫ
	if (pPlayer->GetNationality() == 0)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_NO_CAMP);
		return;
	}
	//�Ƿ� �� ת��ԭ����Ӫ
	if (pPlayer->GetNationality() == tpMsg->targetcampid())
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_SAME);
		return;
	}
	//�Ƿ�ת����߻��������Ӫ
	
	if(CWorldModule::GetSingleton().m_WeakProtecter.IsTopTotalscoreCampID(tpMsg->targetcampid()))
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_BEST);
		return;
	}

	//�Ƿ��ڽ���
	CTradeManager* ptr_TradeManager = CTradeManager::GetSingletonPtr();
	if ( ptr_TradeManager == NULL )
	{
		return ;
	}
	if( ptr_TradeManager->GetTrade( pPlayer->GetEntityID( ) ) != NULL )
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_TRDE);
		return;
	}

	//////�ж��Ƿ������
	if (pPlayer->GetTeamFlag() != 0)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_TEAM);
		return;
	}

	//////�ж��м���
	if (pPlayer->GetFamilyID() != 0)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_FAMILY);
		return;
	}
	//////�ж��Ƿ��й���
	if(pPlayer->GetCountryID() != COUNTRY_NONE)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_COUNTRY);
		return;
	}

	//�Ƿ���ʦͽ
	BOOL bMaster = false;
	for ( int i = 0; i < MAX_MASTER_NUM; i++ )
	{
		if ( pProperty->GetMasterID( i ) != 0 )
		{
			bMaster = true;
		}
	}
	if (bMaster || pProperty->mMatrixList.size() > 0)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_MASTER_PRENTICE);
		return;

	}

	//�Ƿ���
	if (pPlayer->GetMarriageID() != 0)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_MARRIAGE);
		return;
	}

	// �Ƿ��н��
	if ( pPlayer->GetSwornID() != 0 )
	{
		SendChangeCampErrorResponse( pPlayer,ERROR_CHANGE_CAMP_INSWORNTEAM );
		return;
	}
	

	////�Ƿ��и����ʼ�
	//CMail *tpMail = CMailManager::GetSingletonPtr( )->GetMail( pPlayer );	
	//LK_ASSERT( tpMail != NULL, return );		  
	//if(tpMail->IsHavePayMail())
	//{
	//	SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_PAYMAIL);
	//	return;
	//}

	//send camp change notice to gateserver
	CMessage tMsg;
	CMessageChangeSingleCampRequest tNoticeMsg;
	tNoticeMsg.set_playerid(pPlayer->GetCharID());
	tNoticeMsg.set_crrentcampid(pPlayer->GetNationality());
	tNoticeMsg.set_targetcampid(tpMsg->targetcampid());
	tMsg.mutable_msghead()->set_messageid( ID_C2S_REQUEST_CHANGE_CAMP);
	tMsg.set_msgpara((uint32_t) &tNoticeMsg);

	CSceneLogic::GetSingletonPtr()->Send2Gate( &tMsg );

}
//���� gateserver �ظ���ת��Ӫ��Ϣ
void CSceneServer::OnMessageChangCampResponse( CMessage* pMessage)
{
	LK_ASSERT(  pMessage != NULL, return );	

	CMessageChangeSingleCampResponse *tpMsg =  ( CMessageChangeSingleCampResponse * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );	
	if (tpMsg->errorcode() != SUCCESS)
	{
		return;
	}
	CEntityPlayer* pPlayer = ( CEntityPlayer* )CSceneLogic::GetSingletonPtr( )->GetPlayerByCharID( tpMsg->playerid() );

	if( pPlayer == NULL )
	{
		return;
	}
	//�ж��Ƿ����
	CPropertyPlayer* pProperty = (CPropertyPlayer*) pPlayer->GetProperty();	
	if (pProperty == NULL)
	{
		return;
	}
	//�۳�����
	CTemPlateChangeCampCfg *tpConfig = (CTemPlateChangeCampCfg*)CDataStatic::GetTemp( TEMP_CHANGECAMP );
	if ( tpConfig == NULL )
		return;
	uint64_t ullGUID = 0 ;
	int   haveItem = 0 ;
	int   vItemIndex =  CPropertyModule::GetSingletonPtr()->HasItem(pPlayer->GetEntityID() ,tpConfig->m_itemId, 1 , haveItem, 0 );
	if ( haveItem == 0 )
	{
		return ;
	}

	if ( vItemIndex != -1 )
	{
		//CPropertyModule::GetSingletonPtr()->PlayerRemoveItem( pPlayer, vItemIndex, 1, &ullGUID);
		if (CPropertyModule::GetSingletonPtr()->PlayerRemoveItem(  pPlayer, vItemIndex, 1, &ullGUID ) == 0)
		{
			LogEventLostItemByUse(pPlayer, ullGUID, tpConfig->m_itemId, 1);
		}

	}
	//����һ��ԭʼ��Ӫid
	int oldCampid =  pPlayer->GetNationality();
	//�����µ���Ӫid
	pPlayer->SetNationality(tpMsg->campid());

	//�����µ���Ӫcd
	pPlayer->SetChangeCampTime(time(0));


	//���ûسǵ�
	CTemplateBeginner* tpBeginner = (CTemplateBeginner*) CDataStatic::GetTemp( TEMP_BEGINNER );
	if ( tpBeginner == NULL )
		return ;
	pProperty->GetTownPos( )->mLineID = tpMsg->campid();
	pProperty->GetTownPos( )->mMapID = 1;
	pProperty->GetTownPos( )->mPos = CWTPoint( tpBeginner->mPosX1, tpBeginner->mPosY1 );
	pProperty->ClearPropTelet();
	/*for ( CPropertyPlayer::TELE_LIST_TYPE::iterator it = pProperty->GetPropTelet().begin(); it != pProperty->GetPropTelet().end(); ++it )
	{
		pProperty->GetPropTelet().erase(it);
	}*/

	//ԭʼ���踶���ʼ������µĳ���
	CMailModule::GetSingleton().ChangeCampMail(pPlayer,oldCampid,tpMsg->campid());

	//֪ͨgateserver �޸���Ӫid
	CMessage tMsg;
	CMessageChangeCamp2GateNotice tMsgNotic;

	tMsgNotic.set_playerid(pPlayer->GetCharID());
	tMsgNotic.set_campid(tpMsg->campid());
	tMsg.mutable_msghead()->set_messageid( ID_S2G_CHANGE_CAMP_NOTICE);
	tMsg.set_msgpara((uint32_t) &tMsgNotic);

	CSceneLogic::GetSingletonPtr()->Send2Gate( &tMsg );

	//���ʹ�����Ϣ
	CMapModule::GetSingleton().Teleport( tpMsg->campid(), 1, tpBeginner->mPosX1, tpBeginner->mPosY1, pPlayer );

	//���ת���������Ӫ ���Է���һ�������
	if (!CWorldModule::GetSingleton().m_WeakProtecter.IsWeakCamp(tpMsg->campid()))
	{
		return;
	}
	int nItemIDs[1] = {0};
	int nItemNums[1] = {0};
	for (int i = 0;i<1;i++)
	{
		nItemIDs[i]  =  tpConfig->m_giftId;
		nItemNums[i] = 1;
	}
	CMailModule::GetSingleton().SendSysMailBySysID( PRIZE_CHANGE_CAMP, pPlayer->GetCharName(), pPlayer->GetCharID()	
		,nItemIDs, nItemNums, 1, tpMsg->campid(), 0 ) ;
	//CItemObject* pInsItemPile = CPropertyModule::GetSingletonPtr()->PlayerInsertItem( pPlayer, giftid, 1, true);
	return;
}


//����ͻ��� ���Ͳ�ѯת����Ӫ����
void CSceneServer::OnMessageChangeCampConditionRequst(CEntityPlayer *pPlayer, CMessage* pMessage)
{
	LK_ASSERT( pPlayer != NULL && pMessage != NULL, return );	
	CMessageChangeCampConditionRequest *tpMsg =  ( CMessageChangeCampConditionRequest * )pMessage->msgpara();
	LK_ASSERT( tpMsg != NULL, return );

	//�ж��Ƿ����
	CPropertyPlayer* pProperty = (CPropertyPlayer*) pPlayer->GetProperty();	
	if (pProperty == NULL)
	{
		return;
	}
	//�ж�npc����
	CEntityNpc* pNpc = dynamic_cast< CEntityNpc* >( CSceneObjManager::GetSingletonPtr( )->GetObject( 
		tpMsg->npcid() ));
	if( pNpc == NULL )
	{
		 CPropertyModule::GetSingletonPtr()->SendProErrorNotice( pPlayer, ERROR_MW_NPCINVALID );
		return ;
	}

	if( !pPlayer->IsWithinDistance( pNpc, MAX_NPC_TALK_GIRD) ) // �ںϷ�����֮�ڲ��ж�
	{
		 CPropertyModule::GetSingletonPtr()->SendProErrorNotice( pPlayer, ERROR_MW_NPCINVALID );
		return;
	}
	// �ظ���Ϣ
	CMessage tMsg;
	CMessageChangeCampConditionResponse tMsgResponse;
	//////�ж��Ƿ������
	if (pPlayer->GetTeamFlag() != 0)
	{
		tMsgResponse.set_ishaveteam(true);
	}
	else{
		tMsgResponse.set_ishaveteam(false);
	}

	//////�ж��м���
	if (pPlayer->GetFamilyID() != 0)
	{
		tMsgResponse.set_ishavefamily(true);
	}
	else{
		tMsgResponse.set_ishavefamily(false);
	}

	//////�ж��Ƿ��й���
	if(pPlayer->GetCountryID() != COUNTRY_NONE)
	{
		tMsgResponse.set_ishavecountry(true);
	}
	else{
		tMsgResponse.set_ishavecountry(false);
	}

	//�Ƿ���ʦͽ
	//tMsgResponse.set_ishavemaster(false);
	//�Ƿ���ʦͽ
	BOOL bMaster = false;
	for ( int i = 0; i < MAX_MASTER_NUM; i++ )
	{
		if ( pProperty->GetMasterID( i ) != 0 )
		{
			bMaster = true;
		}
	}
	if (bMaster || pProperty->mMatrixList.size() > 0)
	{
		tMsgResponse.set_ishavemaster(true);

	}
	else
	{
		tMsgResponse.set_ishavemaster(false);
	}
	//�Ƿ���
	if (pPlayer->GetMarriageID() != 0)
	{
		tMsgResponse.set_ishavemarriage(true);
	}
	else{
		tMsgResponse.set_ishavemarriage(false);
	}
	//�Ƿ�ﵽ�ȼ�
	if (pPlayer->GetLevel() >= CHANGE_CAMP_LEVEL)
	{
		tMsgResponse.set_ishaveenoughlevel(true);
	}
	else{
		tMsgResponse.set_ishaveenoughlevel(false);
	}

	// �Ƿ��н��
	if ( pPlayer->GetSwornID() != 0 )
	{
		tMsgResponse.set_ishavesworn(true);
	}
	else
	{
		tMsgResponse.set_ishavesworn(false);
	}

	////�Ƿ��и����ʼ�
	//CMail *tpMail = CMailManager::GetSingletonPtr( )->GetMail( pPlayer );	
	//LK_ASSERT( tpMail != NULL, return );		  
	//if(tpMail->IsHavePayMail())
	//{
	//	tMsgResponse.set_ishavepaymail(true);
	//}
	//else{
	//	tMsgResponse.set_ishavepaymail(false);
	//}

	tMsgResponse.set_errorcode(SUCCESS);
	tMsg.mutable_msghead()->set_messageid( ID_S2C_RSPONSE_CHANGE_CAMP_CONDITION);
	tMsg.set_msgpara((uint32_t) &tMsgResponse);

	CSceneLogic::GetSingletonPtr()->Send2Player( pPlayer,&tMsg );
}

//����ת��Ӫ�ɹ� �㲥��Ϣ
void CSceneServer::OnMessageChangeCampSuccesBroadCast(CEntityPlayer *pPlayer, CMessage* pMessage)
{
	return;
	//LK_ASSERT( pMessage != NULL, return );

	//CMapModule::GetSingletonPtr()->MessageBroadCast( pPlayer, pMessage );

}
//���� ת��Ӫ���� ��Ϣ
void  CSceneServer::SendChangeCampErrorResponse(CEntityPlayer *pPlayer,ChangeCamp errorCode)
{
	CMessage tMsg;
	CMessageChangeSingleCampResponse tErrorMsg;

	tErrorMsg.set_errorcode(errorCode);
	tMsg.mutable_msghead()->set_messageid( ID_S2C_RSPONSE_CHANGE_CAMP);
	tMsg.set_msgpara((uint32_t) &tErrorMsg);

	CSceneLogic::GetSingletonPtr()->Send2Player( pPlayer, &tMsg );
}
//gm ǿ��ת����Ӫ
void CSceneServer::OnGMMessageChangeCamp(const char*  role_name,int campid)
{
	CEntityPlayer* pPlayer = CSceneLogic::GetSingletonPtr()->CSceneLogic::GetSingletonPtr()->GetPlayerByName(role_name); 

	if (pPlayer == NULL) return;

	//�ж��Ƿ����
	CPropertyPlayer* pProperty = (CPropertyPlayer*) pPlayer->GetProperty();	
	if (pProperty == NULL)
	{
		return;
	}

	//�Ƿ���ԭʼ��Ӫ
	if (pPlayer->GetNationality() == 0)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_NO_CAMP);
		return;
	}
	//�Ƿ� �� ת��ԭ����Ӫ
	if (pPlayer->GetNationality() == campid)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_SAME);
		return;
	}
	//�Ƿ��ڽ���
	CTradeManager* ptr_TradeManager = CTradeManager::GetSingletonPtr();
	if ( ptr_TradeManager == NULL )
	{
		return ;
	}
	if( ptr_TradeManager->GetTrade( pPlayer->GetEntityID( ) ) != NULL )
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_TRDE);
		return;
	}

	//////�ж��Ƿ������
	if (pPlayer->GetTeamFlag() != 0)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_TEAM);
		return;
	}

	//////�ж��м���
	if (pPlayer->GetFamilyID() != 0)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_FAMILY);
		return;
	}
	//////�ж��Ƿ��й���
	if(pPlayer->GetCountryID() != COUNTRY_NONE)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_COUNTRY);
		return;
	}

	//�Ƿ���ʦͽ
	BOOL bMaster = false;
	for ( int i = 0; i < MAX_MASTER_NUM; i++ )
	{
		if ( pProperty->GetMasterID( i ) != 0 )
		{
			bMaster = true;
		}
	}
	if (bMaster || pProperty->mMatrixList.size() > 0)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_MASTER_PRENTICE);
		return;

	}

	//�Ƿ���
	if (pPlayer->GetMarriageID() != 0)
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_IN_MARRIAGE);
		return;
	}

	// �Ƿ���
	if ( pPlayer->GetSwornID() != 0 )
	{
		SendChangeCampErrorResponse(pPlayer,ERROR_CHANGE_CAMP_INSWORNTEAM);		
		return;
	}
	

	//����һ��ԭʼ��Ӫid
	int oldCampid =  pPlayer->GetNationality();
	oldCampid = oldCampid;
	//�����µ���Ӫid
	pPlayer->SetNationality(campid);

	//�����µ���Ӫcd
	pPlayer->SetChangeCampTime(time(0));


	//���ûسǵ�
	CTemplateBeginner* tpBeginner = (CTemplateBeginner*) CDataStatic::GetTemp( TEMP_BEGINNER );
	if ( tpBeginner == NULL )
		return ;
	pProperty->GetTownPos( )->mLineID = campid;
	pProperty->GetTownPos( )->mMapID = 1;
	pProperty->GetTownPos( )->mPos = CWTPoint( tpBeginner->mPosX1, tpBeginner->mPosY1 );
	pProperty->ClearPropTelet();

	//֪ͨgateserver �޸���Ӫid
	CMessage tMsg;
	CMessageChangeCamp2GateNotice tMsgNotic;

	tMsgNotic.set_playerid(pPlayer->GetCharID());
	tMsgNotic.set_campid(campid);
	tMsg.mutable_msghead()->set_messageid( ID_S2G_CHANGE_CAMP_NOTICE);
	tMsg.set_msgpara((uint32_t) &tMsgNotic);

	CSceneLogic::GetSingletonPtr()->Send2Gate( &tMsg );

	//���ʹ�����Ϣ
	CMapModule::GetSingleton().Teleport( campid, 1, tpBeginner->mPosX1, tpBeginner->mPosY1, pPlayer );

}



